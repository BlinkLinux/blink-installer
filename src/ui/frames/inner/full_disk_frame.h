/*
 * Copyright (C) 2018 Deepin Technology Co., Ltd.
 * Copyright (C) 2022 Xu Shaohua <shaohua@biofan.org>.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DEEPIN_INSTALLER_UI_FRAMES_INNER_FULL_DISK_FRAME_H
#define DEEPIN_INSTALLER_UI_FRAMES_INNER_FULL_DISK_FRAME_H

#include <QFrame>
class QAbstractButton;
class QButtonGroup;
class QGridLayout;
class QLabel;
class QShowEvent;

namespace installer {

class FullDiskDelegate;


class FullDiskFrame : public QFrame {
 public:
  explicit FullDiskFrame(FullDiskDelegate* delegate, QWidget* parent = nullptr);
  ~FullDiskFrame() override;

  bool validate() const;

 public slots:
  void onDeviceRefreshed();
  void onPartitionButtonToggled(QAbstractButton* button, bool checked);

 protected:
  void changeEvent(QEvent* event) override;

 private:
  void initConnections();
  void initUI();

  // Repaint partition list.
  void repaintDevices();

  // Show install_tip at bottom of |button|.
  void showInstallTip(QAbstractButton* button);

  // Show install_tip at bottom of |button|.
//  void showInstallTip(QAbstractButton* button);

  FullDiskDelegate* delegate_ = nullptr;
  QButtonGroup* button_group_ = nullptr;
  QFrame* install_tip_ = nullptr;
  QLabel* tip_label_ = nullptr;
  QGridLayout* grid_layout_ = nullptr;
  QFrame* grid_wrapper_ = nullptr;
};

}  // namespace installer

#endif  // DEEPIN_INSTALLER_UI_FRAMES_INNER_FULL_DISK_FRAME_H
