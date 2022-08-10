// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#include "controllers/shell.h"

#include <QApplication>
#include <QIcon>
#include <QScopedPointer>

#include "config/config.h"
#include "controllers/main_controller.h"
#include "resources/icons/icons.h"

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
  QApplication::setWindowIcon(QIcon(kIconsBlinkInstallerSvg));

  QScopedPointer<MainController> controller(new MainController);
  if (!controller->init()) {
    return 1;
  }

  return QApplication::exec();
}

}  // namespace installer