/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
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

#ifndef INSTALLER_MISC_UNSQUASHFS_PROGRESS_WINDOW_H
#define INSTALLER_MISC_UNSQUASHFS_PROGRESS_WINDOW_H

#include <QFrame>
#include <QLineEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QTimer>

#include "unsquashfs_gui/worker.h"

namespace installer {

class UnsquashfsProgressWindow : public QFrame {
 Q_OBJECT

 public:
  explicit UnsquashfsProgressWindow(QWidget* parent = nullptr);

 private slots:
  void onFileChooserButtonClicked();

  void onCtrlButtonClicked();

  void onReadProgressTimeout();

 private:
  void initConnections();

  void initUI();

  void startWork(const QString& filepath);

  void cancelWork();

  QLineEdit* filepath_edit_ = nullptr;
  QPushButton* file_chooser_button_ = nullptr;
  QPushButton* ctrl_button_ = nullptr;
  QProgressBar* progress_bar_ = nullptr;
  bool work_running_ = false;
  QTimer* timer_ = nullptr;
};

}  // namespace installer

#endif  // INSTALLER_MISC_UNSQUASHFS_PROGRESS_WINDOW_H
