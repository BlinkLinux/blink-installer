// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#ifndef DEEPIN_INSTALLER_REBORN_UI_FRAMES_PARTITION_TABLE_WARNING_FRAME_H
#define DEEPIN_INSTALLER_REBORN_UI_FRAMES_PARTITION_TABLE_WARNING_FRAME_H

#include <QFrame>

namespace ui {

class PartitionTableWarningFrame : public QFrame {
  Q_OBJECT

 public:
  explicit PartitionTableWarningFrame(QWidget* parent = nullptr);

 signals:
  // Emitted when reboot button is clicked.
  void declined();

  // Emitted when continue button is clicked.
  void accepted();
};

}  // namespace ui

#endif  // DEEPIN_INSTALLER_REBORN_UI_FRAMES_PARTITION_TABLE_WARNING_FRAME_H