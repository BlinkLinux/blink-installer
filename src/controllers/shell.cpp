// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "controllers/shell.h"

#include <QApplication>
#include <QDebug>
#include <QIcon>

#include "config/config.h"
#include "service/log_manager.h"
#include "service/settings_manager.h"
#include "sysinfo/users.h"
#include "ui/delegates/installer_args_parser.h"
#include "ui/main_window.h"

namespace installer {

int initShell(int argc, char** argv) {
  // Reset LC_ALL to en_US.UTF-8.
  // NOTE(shaohua): "LANG" might not set in some live environment.
  qputenv("LC_ALL", kDefaultLang);
  qputenv("LANG", kDefaultLang);

  QApplication app(argc, argv);
  QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QApplication::setApplicationDisplayName(kAppDisplayName);
  QApplication::setApplicationName(kAppName);
  QApplication::setApplicationVersion(kAppVersion);
  QApplication::setOrganizationDomain("biofan.org");
  QApplication::setWindowIcon(QIcon(":/icons/blink-installer.svg"));

  // Parse argument list.
  InstallerArgsParser args_parser;
  // Returns false if failed to parse arguments.
  if (!args_parser.parse(QApplication::arguments())) {
    return 1;
  }

  // Initialize log service.
  const char kLogFileName[] = "blink-installer.log";
  QString log_file;
  if (!HasRootPrivilege()) {
    qCritical() << "Root privilege is required!";
    log_file = QString("/tmp/%1").arg(kLogFileName);
  } else {
    log_file = QString("/var/log/%1").arg(kLogFileName);
  }
  RedirectLog(log_file);

  // Delete old settings file and generate a new one.
  DeleteConfigFile();
  AddConfigFile();

  qDebug() << "Version:" << kAppVersion << ", build id:" << kAppBuildId << ", built at:" << kAppBuildDate;

  const QString conf_file(args_parser.getConfFile());
  // Append customized configurations.
  if (!conf_file.isEmpty()) {
    if (!AppendConfigFile(conf_file)) {
      qCritical() << "Failed to append conf file:" << conf_file;
    }
  }

  MainWindow main_window;
  main_window.setEnableAutoInstall(args_parser.isAutoInstallSet());
  main_window.setLogFile(args_parser.getLogFile());
  // Notify background thread to scan device info.
  main_window.scanDevicesAndTimezone();
  main_window.fullscreen();

  return QApplication::exec();
}

}  // namespace installer