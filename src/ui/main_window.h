/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 * Copyright (C) 2022 Xu Shaohua <shaohua@biofan.org>
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

#ifndef INSTALLER_UI_MAIN_WINDOW_H
#define INSTALLER_UI_MAIN_WINDOW_H

#include <QCloseEvent>
#include <QHash>
#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>
#include <QShortcut>
#include <QStackedLayout>
#include <QWidget>

#include "third_party/global_shortcut/global_shortcut.h"
#include "ui/delegates/main_window_util.h"
#include "ui/frames/confirm_quit_frame.h"
#include "ui/frames/control_panel_frame.h"
#include "ui/frames/disk_space_insufficient_frame.h"
#include "ui/frames/install_failed_frame.h"
#include "ui/frames/install_progress_frame.h"
#include "ui/frames/install_success_frame.h"
#include "ui/frames/partition_frame.h"
#include "ui/frames/privilege_error_frame.h"
#include "ui/frames/select_language_frame.h"
#include "ui/frames/system_info_frame.h"
#include "ui/frames/timezone_frame.h"
#include "ui/frames/virtual_machine_frame.h"
#include "ui/utils/widget_util.h"
#include "ui/widgets/page_indicator.h"
#include "ui/widgets/pointer_button.h"
#include "ui/xrandr/multi_head_manager.h"

namespace installer {

// MainWindow is a fullscreen window of installer.
// All of ui frames are placed in MainWindow.
// It does following jobs:
//   * draw window background with a blur image;
//   * handles keyboard shortcut like Ctrl+P and Ctrl+L;
//   * handles window navigation (by providing a content area);
//   * quit / abort installation process.
class MainWindow : public QWidget {
  Q_OBJECT

 public:
  explicit MainWindow();

  // Show fullscreen.
  void fullscreen();

  // Notify background thread to scan disk devices if needed.
  // And read current timezone.
  void scanDevicesAndTimezone();

  // Enable auto-install mode.
  void setEnableAutoInstall(bool auto_install);

 signals:
  void requestReloadTranslator();
  void requestShutdownSystem();
  void requestRebootSystem();

 protected:
  // Switch to abort page on close-event received.
  void closeEvent(QCloseEvent* event) override;

  // Move close button to appropriate position when window is resized.
  void resizeEvent(QResizeEvent* event) override;

 private slots:
  // Go next page when current page index is changed in ControlPanelFrame.
  void onCurrentPageChanged(int index);

  // Show ConfirmQuitFrame when close_button_ is clicked.
  void onCloseButtonClicked();

  // Move main window to primary screen when it is changed to |geometry|.
  void onPrimaryScreenChanged(const QRect& geometry);

  void goNextPage();

 private:
  enum PageId {
    NullId,  // page not set.

    ConfirmQuitId,
    DiskSpaceInsufficientId,
    InstallFailedId,
    InstallProgressId,
    InstallSuccessId,
    PartitionId,
    PrivilegeErrorId,
    SelectLanguageId,
    SystemInfoId,
    TimezoneId,
    VirtualMachineId,
  };

  void initConnections();
  void initPages();
  void initUI();
  void registerShortcut();

  // Switch frame page based on name.
  void setCurrentPage(PageId page_id);

  void updateBackground();

  QLabel* background_label_ = nullptr;
  QPushButton* close_button_ = nullptr;
  PageIndicator* page_indicator_ = nullptr;
  // All of frame pages are stored in this layout.
  // And they are referenced by id in |pages_|.
  QStackedLayout* stacked_layout_ = nullptr;

  ConfirmQuitFrame* confirm_quit_frame_ = nullptr;
  ControlPanelFrame* control_panel_frame_ = nullptr;
  DiskSpaceInsufficientFrame* disk_space_insufficient_frame_ = nullptr;
  InstallFailedFrame* install_failed_frame_ = nullptr;
  InstallProgressFrame* install_progress_frame_ = nullptr;
  InstallSuccessFrame* install_success_frame_ = nullptr;
  PartitionFrame* partition_frame_ = nullptr;
  PrivilegeErrorFrame* privilege_error_frame_ = nullptr;
  SelectLanguageFrame* select_language_frame_ = nullptr;
  SystemInfoFrame* system_info_frame_ = nullptr;
  TimezoneFrame* timezone_frame_ = nullptr;
  VirtualMachineFrame* virtual_machine_frame_ = nullptr;
  MultiHeadManager* multi_head_manager_ = nullptr;

  // To store frame pages, page_name => page_id.
  QHash<PageId, int> pages_;

  // Keep previous page id. It is used by ConfirmQuitPage.
  PageId prev_page_;
  PageId current_page_;

  // Shortcut used to toggle visibility of log-viewer.
  QShortcut* control_panel_shortcut_ = nullptr;

  // Shortcut used to switch mirror modes.
  GlobalShortcut* monitor_mode_shortcut_ = nullptr;

  // Shortcut for screen brightness.
  QShortcut* brightness_increase_shortcut_ = nullptr;
  QShortcut* brightness_decrease_shortcut_ = nullptr;

  bool auto_install_;
};

}  // namespace installer

#endif  // INSTALLER_UI_MAIN_WINDOW_H
