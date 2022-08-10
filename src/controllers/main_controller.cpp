// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "controllers/main_controller.h"

#include <QApplication>
#include <QDebug>

#include "config/config.h"
#include "service/installer_args_parser.h"
#include "service/log_manager.h"
#include "service/settings_manager.h"
#include "sysinfo/users.h"

namespace installer {

MainController::MainController(QObject* parent)
    : QObject(parent),
      main_window_(new MainWindow()) {

}

MainController::~MainController() {
  main_window_->deleteLater();
}

bool MainController::init() {
  // Parse argument list.
  InstallerArgsParser args_parser;
  // Returns false if failed to parse arguments.
  if (!args_parser.parse(QApplication::arguments())) {
    return false;
  }

  // Initialize log service.
  constexpr const char kLogFileName[] = "blink-installer.log";
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

  main_window_->setEnableAutoInstall(args_parser.isAutoInstallSet());
  main_window_->setLogFile(args_parser.getLogFile());

  // Notify background thread to scan device info.
  main_window_->scanDevicesAndTimezone();
  main_window_->fullscreen();

  return true;
}

}  // namespace installer