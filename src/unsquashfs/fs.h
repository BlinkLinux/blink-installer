// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef BLINK_INSTALLER_SRC_UNSQUASHFS_FS_H_
#define BLINK_INSTALLER_SRC_UNSQUASHFS_FS_H_

#include <QString>

namespace installer {
// Write progress value to file.
void WriteProgress(int progress);


// Copy regular file with sendfile() system call, from |src_file| to
// |dest_file|. Size of |src_file| is |file_size|.
bool SendFile(const char* src_file, const char* dest_file, ssize_t file_size);

// Update xattr (access control lists and file capabilities)
bool CopyXAttr(const char* src_file, const char* dest_file);

// Tree walk handler. Copy one item from |fpath|.
int CopyItem(const char* fpath, const struct stat* sb, int typeflag, struct FTW* ftwbuf);

// Copy files from |mount_point| to |dest_dir|, keeping xattrs.
bool CopyFiles(const QString& src_dir, const QString& dest_dir,
               const QString& progress_file);

// Mount filesystem at |src| to |mount_point|
bool MountFs(const QString& src, const QString& mount_point);

// Umount filesystem from |mount_point|.
bool UnMountFs(const QString& mount_point);

}  // namespace installer

#endif  // BLINK_INSTALLER_SRC_UNSQUASHFS_FS_H_
