// Copyright (c) 2022 Xu Shaohua <shaohua@biofan.org>. All rights reserved.
// Use of this source is governed by GNU General Public License
// that can be found in the LICENSE file.

#ifndef BLINK_INSTALLER_SRC_CONTROLLERS_MAIN_CONTROLLER_H_
#define BLINK_INSTALLER_SRC_CONTROLLERS_MAIN_CONTROLLER_H_

#include <QObject>

namespace installer {

class MainController : public QObject {
  Q_OBJECT
 public:
  explicit MainController(QObject* parent = nullptr);
};

}  // namespace installer

#endif  // BLINK_INSTALLER_SRC_CONTROLLERS_MAIN_CONTROLLER_H_
