// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#ifndef DEEPIN_INSTALLER_REBORN_UI_FRAMES_INSTALL_FAILED_FRAME_H
#define DEEPIN_INSTALLER_REBORN_UI_FRAMES_INSTALL_FAILED_FRAME_H

#include <QFrame>

namespace ui {

class InstallFailedFrame : public QFrame {
  Q_OBJECT

 public:
  explicit InstallFailedFrame(QWidget* parent = nullptr);

 signals:
  // Emitted when poweroff button is clocked.
  void finished();
};

}  // namespace ui

#endif  // DEEPIN_INSTALLER_REBORN_UI_FRAMES_INSTALL_FAILED_FRAME_H