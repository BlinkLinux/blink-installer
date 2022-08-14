// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "controllers/main_controller.h"

#include <QApplication>
#include <QDebug>
#include <QTranslator>

#include "config/config.h"
#include "service/installer_args_parser.h"
#include "service/languages.h"
#include "service/log_manager.h"
#include "service/power_manager.h"
#include "service/settings_manager.h"
#include "sysinfo/users.h"

namespace installer {

MainController::MainController(QObject* parent)
    : QObject(parent),
      main_window_(new MainWindow()) {
  this->initConnections();
}

MainController::~MainController() {
  main_window_->deleteLater();
}

void MainController::initConnections() {
  connect(main_window_, &MainWindow::requestReloadTranslator,
          this, &MainController::reloadTranslator);
  connect(main_window_, &MainWindow::requestShutdownSystem,
          this, &MainController::shutdownSystem);
  connect(main_window_, &MainWindow::requestRebootSystem,
          this, &MainController::rebootSystem);
}

void MainController::reloadTranslator() {
  // Set language.
  auto* translator = new QTranslator(this);
  const QString locale(ReadLocale());
  translator->load(GetLocalePath(locale));
  qApp->installTranslator(translator);
}

void MainController::shutdownSystem() {
  this->saveLogFile();

#ifndef NDEBUG
  // Do not shutdown system in debug.
  main_window_->close();
  qApp->quit();
  return;
#endif

  if (!ShutdownSystemWithMagicKey()) {
    qWarning() << "ShutdownSystem() failed!";
    if (!ShutdownSystem()) {
      qWarning() << "ShutdownSystemWithMagicKey() failed!";
    }
  }
}

void MainController::rebootSystem() {
  this->saveLogFile();

#ifndef NDEBUG
  // Do not shutdown system in debug.
  main_window_->close();
  qApp->quit();
  return;
#endif

  if (!RebootSystemWithMagicKey()) {
    qWarning() << "RebootSystem failed!";
    if (!RebootSystem()) {
      qWarning() << "RebootSystemWithMagicKey() failed!";
    }
  }
}

void MainController::saveLogFile() {
  // Copy log file.
  CopyLogFile(log_file_);
}

bool MainController::init() {
  // Parse argument list.
  InstallerArgsParser args_parser;
  // Returns false if failed to parse arguments.
  if (!args_parser.parse(QApplication::arguments())) {
    return false;
  }

  // Initialize log service.
  constexpr const char* kLogFileName = "blink-installer.log";
  QString log_file;
  if (!HasRootPrivilege()) {
    qCritical() << "Root privilege is required!";
    log_file = QString("/tmp/%1").arg(kLogFileName);
  } else {
    log_file = QString("/var/log/%1").arg(kLogFileName);
  }

#ifdef NDEBUG
  RedirectLog(log_file);
#endif

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
  log_file_ = args_parser.getLogFile();

  // Notify background thread to scan device info.
  main_window_->scanDevicesAndTimezone();
  main_window_->fullscreen();

  return true;
}

}  // namespace installer