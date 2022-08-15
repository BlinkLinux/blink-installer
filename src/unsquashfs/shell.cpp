// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "unsquashfs/shell.h"

#include <QCoreApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QDateTime>
#include <QString>

namespace installer {

namespace {

const int kExitOk = 0;
const int kExitErr = 1;

constexpr const char kAppName[] = "deepin-installer-unsquashfs";
constexpr const char kAppDesc[] = "Tool to extract squashfs filesystem";
constexpr const char kAppVersion[] = "0.0.1";

}  // namespace

int runShell(int argc, char** argv) {
  // Parse args
  // Mount squashfs file
  // Copy files to target
  // Unmount from mount-point

  // NOTE(xushaohua): "LANG" might not set in some live environment.
  // Set locale to en_US.UTF-8, or else, mounted squashfs will display invalid
  // character code.
  qputenv("LC_ALL", kDefaultLang);
  qputenv("LANG", kDefaultLang);
  (void) setlocale(LC_ALL, kDefaultLang);

  QCoreApplication::setApplicationName(kAppName);
  QCoreApplication::setApplicationVersion(kAppVersion);
  QCoreApplication app(argc, argv);

  QCommandLineParser parser;
  const QCommandLineOption dest_option(
      "dest", "extract to <pathname>, default \"squashfs-root\"",
      "pathname", kDefaultDest);
  parser.addOption(dest_option);
  const QCommandLineOption progress_option(
      "progress","print progress info to <file>",
      "file", "");
  parser.addOption(progress_option);
  parser.setApplicationDescription(kAppDesc);
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("file", "squashfs filesystem to be extracted");

  if (!parser.parse(QCoreApplication::arguments())) {
    parser.showHelp(kExitErr);
  }

  if (parser.isSet("version") || parser.isSet("help")) {
    // Show help and exit.
    parser.showHelp(kExitOk);
  }

  const QStringList positional_args = parser.positionalArguments();
  if (positional_args.length() != 1) {
    fprintf(stderr, "Too many files to extract, expect one!\n");
    parser.showHelp(kExitErr);
  }

  const QString src(positional_args.at(0));
  const QFile src_file(src);
  if (!src_file.exists()) {
    fprintf(stderr, "File not found: %s\n", src.toLocal8Bit().constData());
    parser.showHelp(kExitErr);
  }
  if (src_file.size() == 0) {
    fprintf(stderr, "Filesystem is empty: %s\n", src.toLocal8Bit().constData());
    parser.showHelp(kExitErr);
  }

  struct utsname uname_buf;
  if (uname(&uname_buf) == 0) {
    // Do not use sendfile() on "sw" platform, as do_sendfile() always crashes!
    g_use_sendfile = (strncmp(uname_buf.machine, "sw", 2) != 0);
  } else {
    g_use_sendfile = false;
  }
  fprintf(stdout, "use_sendfile: %s\n", g_use_sendfile ? "yes" : "no");

  const qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
  const QString mount_point(QString(kMountPointTmp).arg(timestamp));

  const QString dest_dir = parser.value(dest_option);
  const QString progress_file = parser.value(progress_option);

  if (!MountFs(src, mount_point)) {
    fprintf(stderr, "Mount %s to %s failed!\n",
            src.toLocal8Bit().constData(),
            mount_point.toLocal8Bit().constData());
    exit(kExitErr);
  }

  const bool ok = CopyFiles(mount_point, dest_dir, progress_file);
  if (!ok) {
    fprintf(stderr, "Copy files failed!\n");
  }

  // Commit filesystem caches to disk.
//  sync();

  for (int retry = 0; retry < 5; ++retry) {
    if (!UnMountFs(mount_point)) {
      fprintf(stderr, "Unmount %s failed\n",
              mount_point.toLocal8Bit().constData());
      sleep(static_cast<unsigned int>(retry * 2 + 1));
    } else {
      break;
    }
  }

  exit(ok ? kExitOk : kExitErr);
}

}  // namespace installer