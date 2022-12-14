// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "unsquashfs/fs.h"

#undef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500  // Required by nftw().
#include <climits>
#include <cstdlib>
#include <fcntl.h>
#include <ftw.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/xattr.h>
#include <unistd.h>

#include <QDir>
#include <QFile>
#include <QtMath>

#include "base/command.h"
#include "base/file_util.h"

namespace installer {

namespace {

// TODO(Shaohua): R3e
#define S_IMODE 07777

// Maximum number of opened file descriptors.
// See /proc/self/limits for more information.
const int kMaxOpenFd = 512;

// File descriptor of progress file.
FILE* g_progress_fd = nullptr;

// Global references to src_dir and dest_dir.
QString g_src_dir;
QString g_dest_dir;

// Total number of files in squashfs filesystem.
int g_total_files = 0;
// Number of files has been copied.
int g_current_files = 0;

// Use sendfile() system call or not.
bool g_use_sendfile = true;

}  // namespace

void WriteProgress(int progress) {
  if (g_progress_fd) {
    fseek(g_progress_fd, 0, SEEK_SET);
    fprintf(g_progress_fd, "%d", progress);
  } else {
    fprintf(stdout, "\r%d", progress);
  }
}

bool SendFile(const char* src_file, const char* dest_file, ssize_t file_size) {
  int src_fd;
  int dest_fd;
  src_fd = open(src_file, O_RDONLY);
  if (src_fd == -1) {
    fprintf(stderr, "SendFile() Failed to open src file: %s\n", src_file);
    perror("Open src file failed!");
    return false;
  }

  // TODO(xushaohua): handles umask
  dest_fd = open(dest_file, O_CREAT | O_RDWR, S_IREAD | S_IWRITE);
  if (dest_fd == -1) {
    fprintf(stderr, "SendFile() Failed to open dest file: %s\n", dest_file);
    perror("Open dest file failed!");
    return false;
  }

  bool ok = true;
  if (g_use_sendfile) {
    size_t num_to_read = size_t(file_size);
    while (num_to_read > 0) {
      const ssize_t num_sent = sendfile(dest_fd, src_fd, nullptr, num_to_read);
      if (num_sent <= 0) {
        fprintf(stderr, "sendfile() error: %s\nSkip %s\n",
                strerror(errno), src_file);
        // NOTE(xushaohua): Skip sendfile() error.
        // xz uncompress error, Input/output error.
        // squashfs file might have some defects.
//      ok = false;
        ok = true;
        break;
      }
      num_to_read -= num_sent;
    }
  } else {
    const size_t kBufSize = 32 * 1024;  // 32k
    char buf[kBufSize];
    ssize_t num_read;
    while ((num_read = read(src_fd, buf, kBufSize)) > 0) {
      // TODO(xushaohua): write() may write less buf.
      if (write(dest_fd, buf, (size_t) num_read) != num_read) {
        ok = false;
        break;
      }
    }
    if (num_read < 0) {
      ok = false;
    }
  }

  close(src_fd);
  close(dest_fd);

  return ok;
}

bool CopySymLink(const char* src_file, const char* link_path) {
  char buf[PATH_MAX];
  ssize_t link_len = readlink(src_file, buf, PATH_MAX);
  if (link_len <= 0) {
    fprintf(stderr, "CopySymLink() readlink() failed: %s\n", src_file);
    perror("readlink() error");
    return false;
  }

  char target[link_len + 1];
  strncpy(target, buf, (size_t) link_len);
  target[link_len] = '\0';
  if (symlink(target, link_path) != 0) {
    fprintf(stderr, "CopySymLink() symlink() failed, %s (%s -> %s)\n",
            strerror(errno), link_path, target);
    // Ignores EEXIST.
    return (errno == EEXIST);
  } else {
    return true;
  }
}

bool CopyXAttr(const char* src_file, const char* dest_file) {
  bool ok = true;
  // size of extended attribute list, 64k.
  char list[XATTR_LIST_MAX];
  char value[XATTR_NAME_MAX];
  ssize_t xlist_len = llistxattr(src_file, list, XATTR_LIST_MAX);
  if (xlist_len < 0) {
    // Check errno.
    if (errno == ENOTSUP) {
      // Target filesystem does not support extended attributes.
      ok = true;
    } else {
      fprintf(stdout, "CopyXAttr() llistxattr() failed: %s, %s\n", src_file,
              strerror(errno));
      ok = false;
    }
  } else {
    ssize_t value_len;
    for (int ns = 0; ns < xlist_len; ns += strlen(&list[ns] + 1)) {
      value_len = lgetxattr(src_file, &list[ns], value, XATTR_NAME_MAX);
      if (value_len == -1) {
        fprintf(stdout, "CopyXAttr() could not get value: %s\n", src_file);
        break;
      } else {
        if (lsetxattr(dest_file, &list[ns], value, size_t(value_len), 0) != 0) {
          fprintf(stdout, "CopyXAttr() setxattr() failed: %s, %s, %s, %s\n",
                  dest_file, &list[ns], value, strerror(errno));
          ok = false;
          break;
        }
      }
    }
  }

  return ok;
}

int CountItem(const char* fpath, const struct stat* sb, int typeflag, struct FTW* ftwbuf) {
  Q_UNUSED(fpath);
  Q_UNUSED(sb);
  Q_UNUSED(typeflag);
  Q_UNUSED(ftwbuf);
  g_total_files ++;
  return 0;
}

int CopyItem(const char* fpath, const struct ::stat* sb, int typeflag, struct FTW* ftwbuf) {
  Q_UNUSED(sb);
  Q_UNUSED(typeflag);
  Q_UNUSED(ftwbuf);

  struct ::stat st;
  if (lstat(fpath, &st) != 0) {
    fprintf(stderr, "CopyItem() call lstat() failed: %s\n", fpath);
    perror("lstat()");
    return 1;
  }

  QString relative_path(fpath);
  relative_path.remove(g_src_dir);
  if (relative_path.startsWith('/')) {
    relative_path = relative_path.mid(1);
  }
  const QString dest_filepath =
      QDir(g_dest_dir).absoluteFilePath(relative_path);

  // Create parent dirs.
  CreateParentDirs(dest_filepath);

  const std::string std_dest_filepath(dest_filepath.toStdString());
  const char* dest_file = std_dest_filepath.c_str();

  // Get file mode.
  const mode_t mode = st.st_mode & S_IMODE;
  bool ok = true;

  // Remove dest_file if it exists.
  struct ::stat dest_stat;
  if (::stat(dest_file, &dest_stat) == 0) {
    if (!S_ISDIR(dest_stat.st_mode)) {
      unlink(dest_file);
    }
  }

  if (S_ISLNK(st.st_mode)) {
    // Symbolic link
    ok = CopySymLink(fpath, dest_file);
  } else if (S_ISREG(sb->st_mode)) {
    // Regular file
    ok = SendFile(fpath, dest_file, st.st_size);
  } else if (S_ISDIR(st.st_mode)) {
    // Directory
    ok = CreateDirs(dest_filepath);
  } else if (S_ISCHR(st.st_mode)) {
    // Character device
    ok = (mknod(dest_file, mode | S_IFCHR, st.st_dev) == 0);
  } else if (S_ISBLK(st.st_mode)) {
    // For block device.
    ok = (mknod(dest_file, mode | S_IFBLK, st.st_dev) == 0);
  } else if (S_ISFIFO(st.st_mode)) {
    // FIFO
    ok = (mknod(dest_file, mode | S_IFIFO, st.st_dev) == 0);
  } else if (S_ISSOCK(st.st_mode)) {
    // Socket
    ok = (mknod(dest_file, mode | S_IFSOCK, st.st_dev) == 0);
  } else {
    fprintf(stderr, "CopyItem() Unknown file mode: %d\n", st.st_mode);
  }

  if (!ok) {
    fprintf(stderr, "Failed to copy item: %s\n", dest_file);
    // Ignore copy file error.
    // Return if error occurs
//    return 1;
  }

  // Update ownership first, or chmod() might ignore SUID/SGID or sticky flag.
  if (lchown(dest_file, st.st_uid, st.st_gid) != 0) {
    fprintf(stderr, "CopyItem() lchown() failed: %s, %d, %d\n",
            dest_file, st.st_uid, st.st_gid);
    perror("lchown()");
    // Ignores copy file error.
//    ok = false;
  }
  // Update permissions.
  if (!S_ISLNK(st.st_mode)) {
    if (chmod(dest_file, mode) != 0) {
      fprintf(stderr, "CopyItem() chmod failed: %s, %ul\n", dest_file, mode);
      perror("chmod()");
      // Ignores chmod error.
//      ok = false;
    }
  }

  if (!CopyXAttr(fpath, dest_file)) {
    // NOTE(xushaohua): Do not exit when failed to copy file capacities.
    // This may be happen in Alpha based computer.
    fprintf(stderr, "CopyXAttr() failed: %s\n", fpath);
//    ok = false;
  }

  g_current_files++;
  const int progress = qFloor(g_current_files * 100.0 / g_total_files);
  WriteProgress(progress);

  return ok ? 0 : 1;
}

bool CopyFiles(const QString& src_dir, const QString& dest_dir,
               const QString& progress_file) {
  if (!CreateDirs(dest_dir)) {
    fprintf(stderr, "CopyFiles() failed to create dest dir: %s\n",
            dest_dir.toLocal8Bit().constData());
    return false;
  }

  // Save current umask.
  const mode_t old_mask = umask(0);

  if (!progress_file.isEmpty()) {
    // Set progress file descriptor.
    g_progress_fd = fopen(progress_file.toStdString().c_str(), "w");
    if (g_progress_fd == nullptr) {
      perror("fopen() Failed to open progress file");
    }
  }

  g_src_dir = src_dir;
  g_dest_dir = dest_dir;

  // Count file numbers.
  bool ok = (::nftw(src_dir.toUtf8().data(),
                  CountItem, kMaxOpenFd, FTW_PHYS) == 0);
  if (!ok || (g_total_files == 0)) {
    fprintf(stderr, "CopyFiles() Failed to count file number!\n");
  } else {
    ok = (::nftw(src_dir.toUtf8().data(), CopyItem, kMaxOpenFd, FTW_PHYS) == 0);
  }

  // Reset umask.
  umask(old_mask);

  if (ok) {
    WriteProgress(100);
  }

  if (g_progress_fd) {
    fclose(g_progress_fd);
  }

  return ok;
}

bool MountFs(const QString& src, const QString& mount_point) {
  if (!CreateDirs(mount_point)) {
    fprintf(stderr, "MountFs() failed to create folder: %s\n",
            mount_point.toLocal8Bit().constData());
    return false;
  }
  QString output;
  QString err;
  const bool ok = SpawnCmd("mount", {src, mount_point}, output, err);
  if (!ok) {
    fprintf(stderr, "MountFs() err: %s\n", err.toLocal8Bit().constData());
  }

  // TODO(xushaohua): Check |mount_point| dir is not empty.
  return ok;
}

bool UnMountFs(const QString& mount_point) {
  const bool ok = SpawnCmd("umount", {"-R", mount_point});
  if (!ok) {
    fprintf(stderr, "Umount %s failed!", mount_point.toLocal8Bit().constData());
  }
  return ok;
}

}  // namespace installer