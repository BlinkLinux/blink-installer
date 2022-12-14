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

#include "ui/frames/partition_frame.h"

#include <QButtonGroup>
#include <QEvent>
#include <QHBoxLayout>
#include <QStackedLayout>

#include "base/file_util.h"
#include "resources/styles/styles.h"
#include "service/settings_manager.h"
#include "service/settings_name.h"
#include "ui/delegates/advanced_partition_delegate.h"
#include "ui/delegates/partition_util.h"
#include "ui/delegates/simple_partition_delegate.h"
#include "ui/frames/consts.h"

namespace installer {

namespace {

constexpr const char* kLeftBtn = "left_frame_button";
constexpr const char* kMidBtn = "mid_frame_button";
constexpr const char* kRightBtn = "right_frame_button";
constexpr const char* kSoloBtn = "solo_frame_button";

}  // namespace

PartitionFrame::PartitionFrame(QWidget* parent)
    : QFrame(parent),
      partition_model_(new PartitionModel(this)),
      advanced_delegate_(new AdvancedPartitionDelegate(this)),
      full_disk_delegate_(new FullDiskDelegate(this)),
      simple_partition_delegate_(new SimplePartitionDelegate(this)) {
  this->setObjectName("partition_frame");

  this->initUI();
  this->initConnections();
}

void PartitionFrame::autoPart() {
  partition_model_->autoPart();
}

void PartitionFrame::scanDevices() const {
  partition_model_->scanDevices();
}

void PartitionFrame::changeEvent(QEvent* event) {
  if (event->type() == QEvent::LanguageChange) {
    title_label_->setText(tr("Select Installation Location"));
    comment_label_->setText(
        tr("Please make sure important data were made a backup, "
           "then select the disk to install"));
    simple_frame_button_->setText(tr("Simple"));
    advanced_frame_button_->setText(tr("Advanced"));
    next_button_->setText(tr("Start installation"));
  } else {
    QFrame::changeEvent(event);
  }
}

void PartitionFrame::initConnections() {
  connect(full_disk_frame_button_, &QPushButton::toggled,
          this, &PartitionFrame::onFullDiskFrameButtonToggled);
  connect(simple_frame_button_, &QPushButton::toggled,
          this, &PartitionFrame::onSimpleFrameButtonToggled);
  connect(advanced_frame_button_, &QPushButton::toggled,
          this, &PartitionFrame::onAdvancedFrameButtonToggled);
  connect(next_button_, &QPushButton::clicked,
          this, &PartitionFrame::onNextButtonClicked);

  // Show main frame when device is refreshed.
  connect(partition_model_, &PartitionModel::deviceRefreshed,
          this, &PartitionFrame::showMainFrame);
  connect(partition_model_, &PartitionModel::autoPartDone,
          this, &PartitionFrame::autoPartDone);
  connect(partition_model_, &PartitionModel::manualPartDone,
          this, &PartitionFrame::onManualPartDone);

  connect(advanced_partition_frame_,
          &AdvancedPartitionFrame::requestEditPartitionFrame,
          this, &PartitionFrame::showEditPartitionFrame);
  connect(advanced_partition_frame_,
          &AdvancedPartitionFrame::requestNewPartitionFrame,
          this, &PartitionFrame::showNewPartitionFrame);
  connect(advanced_partition_frame_, &AdvancedPartitionFrame::requestNewTable,
          this, &PartitionFrame::showPartitionTableWarningFrame);
  connect(advanced_partition_frame_,
          &AdvancedPartitionFrame::requestPartitionNumberLimitationFrame,
          this, &PartitionFrame::showPartitionNumberLimitationFrame);
  connect(advanced_partition_frame_,
          &AdvancedPartitionFrame::requestSelectBootloaderFrame,
          this, &PartitionFrame::showSelectBootloaderFrame);

  connect(edit_partition_frame_, &EditPartitionFrame::finished,
          this, &PartitionFrame::showMainFrame);
  connect(new_partition_frame_, &NewPartitionFrame::finished,
          this, &PartitionFrame::showMainFrame);

  connect(new_table_warning_frame_, &NewTableWarningFrame::canceled,
          this, &PartitionFrame::showMainFrame);
  connect(new_table_warning_frame_, &NewTableWarningFrame::confirmed,
          this, &PartitionFrame::showNewTableLoadingFrame);
  connect(new_table_warning_frame_, &NewTableWarningFrame::confirmed,
          partition_model_, &PartitionModel::createPartitionTable);

  connect(partition_number_limitation_frame_,
          &PartitionNumberLimitationFrame::finished,
          this, &PartitionFrame::showMainFrame);

  connect(partition_table_warning_frame_, &PartitionTableWarningFrame::canceled,
          this, &PartitionFrame::showMainFrame);
  connect(partition_table_warning_frame_,
          &PartitionTableWarningFrame::confirmed,
          this, &PartitionFrame::showNewTableWarningFrame);
  connect(partition_table_warning_frame_, &PartitionTableWarningFrame::reboot,
          this, &PartitionFrame::reboot);

  connect(prepare_install_frame_, &PrepareInstallFrame::aborted,
          this, &PartitionFrame::showMainFrame);
  connect(prepare_install_frame_, &PrepareInstallFrame::finished,
          this, &PartitionFrame::onPrepareInstallFrameFinished);

  connect(select_bootloader_frame_, &SelectBootloaderFrame::bootloaderUpdated,
          advanced_partition_frame_,
          &AdvancedPartitionFrame::setBootloaderPath);
  connect(select_bootloader_frame_, &SelectBootloaderFrame::bootloaderUpdated,
          advanced_delegate_, &AdvancedPartitionDelegate::setBootloaderPath);
  connect(select_bootloader_frame_, &SelectBootloaderFrame::finished,
          this, &PartitionFrame::showMainFrame);
  connect(advanced_delegate_, &AdvancedPartitionDelegate::deviceRefreshed,
          select_bootloader_frame_, &SelectBootloaderFrame::deviceRefreshed);

  connect(partition_model_, &PartitionModel::deviceRefreshed,
          advanced_delegate_, &AdvancedPartitionDelegate::onDeviceRefreshed);

  if (!GetSettingsBool(kPartitionSkipSimplePartitionPage)) {
    connect(partition_model_, &PartitionModel::deviceRefreshed,
            simple_partition_delegate_,
            &SimplePartitionDelegate::onDeviceRefreshed);

  }
  if (!GetSettingsBool(kPartitionSkipFullDiskPartitionPage)) {
    connect(partition_model_, &PartitionModel::deviceRefreshed,
            full_disk_delegate_, &FullDiskDelegate::onDeviceRefreshed);
  }

  // TODO(Shaohua): Show warning page both in full-disk frame and
  // simple-partition frame.
  connect(simple_partition_frame_, &SimplePartitionFrame::requestNewTable,
          this, &PartitionFrame::showPartitionTableWarningFrame);
}

void PartitionFrame::initUI() {
  advanced_partition_frame_ =
      new AdvancedPartitionFrame(advanced_delegate_, this);
  edit_partition_frame_ = new EditPartitionFrame(advanced_delegate_, this);
  full_disk_partition_frame_ = new FullDiskFrame(full_disk_delegate_, this);
  new_partition_frame_ = new NewPartitionFrame(advanced_delegate_, this);
  new_table_loading_frame_ = new NewTableLoadingFrame(this);
  new_table_warning_frame_ = new NewTableWarningFrame(this);
  partition_loading_frame_ = new PartitionLoadingFrame(this);
  partition_number_limitation_frame_ = new PartitionNumberLimitationFrame(this);
  partition_table_warning_frame_ = new PartitionTableWarningFrame(this);
  prepare_install_frame_ = new PrepareInstallFrame(this);
  select_bootloader_frame_ = new SelectBootloaderFrame(this);
  simple_partition_frame_ =
      new SimplePartitionFrame(simple_partition_delegate_, this);

  title_label_ = new TitleLabel(tr("Select Installation Location"));
  comment_label_ = new CommentLabel(
      tr("Please make sure important data were made a backup, "
         "then select the disk to install"));
  auto* comment_layout = new QHBoxLayout();
  comment_layout->setContentsMargins(0, 0, 0, 0);
  comment_layout->setSpacing(0);
  comment_layout->addWidget(comment_label_);

  auto* button_group = new QButtonGroup(this);
  full_disk_frame_button_ = new PointerButton(tr("Full Disk"));
  full_disk_frame_button_->setCheckable(true);
  full_disk_frame_button_->setFlat(true);
  full_disk_frame_button_->setMinimumWidth(86);
  simple_frame_button_ = new PointerButton(tr("Simple"));
  simple_frame_button_->setCheckable(true);
  simple_frame_button_->setFlat(true);
  simple_frame_button_->setMinimumWidth(86);
  advanced_frame_button_ = new PointerButton(tr("Advanced"));
  advanced_frame_button_->setCheckable(true);
  advanced_frame_button_->setMinimumWidth(86);
  advanced_frame_button_->setFlat(true);

  button_group->addButton(full_disk_frame_button_);
  button_group->addButton(simple_frame_button_);
  button_group->addButton(advanced_frame_button_);
  auto* button_layout = new QHBoxLayout();
  button_layout->setContentsMargins(0, 0, 0, 0);
  button_layout->setSpacing(0);
  button_layout->addStretch();
  button_layout->addWidget(full_disk_frame_button_, 0, Qt::AlignRight);
  button_layout->addWidget(simple_frame_button_, 0, Qt::AlignRight);
  button_layout->addWidget(advanced_frame_button_, 0, Qt::AlignLeft);
  button_layout->addStretch();

  partition_stacked_layout_ = new QStackedLayout();
  partition_stacked_layout_->setContentsMargins(0, 0, 0, 0);
  partition_stacked_layout_->setSpacing(0);
  if (GetSettingsBool(kPartitionSkipFullDiskPartitionPage)) {
    full_disk_frame_button_->hide();
    full_disk_frame_button_->setChecked(false);
    simple_frame_button_->setObjectName(kLeftBtn);
    simple_frame_button_->setChecked(true);
    full_disk_partition_frame_->hide();
  } else {
    full_disk_frame_button_->setChecked(true);
    full_disk_frame_button_->setObjectName(kLeftBtn);
    simple_frame_button_->setObjectName(kMidBtn);
    partition_stacked_layout_->addWidget(full_disk_partition_frame_);
  }

  if (GetSettingsBool(kPartitionSkipSimplePartitionPage)) {
    simple_frame_button_->hide();
    simple_frame_button_->setChecked(false);
    simple_partition_frame_->hide();
  } else {
    partition_stacked_layout_->addWidget(simple_partition_frame_);
  }

  if (GetSettingsBool(kPartitionSkipFullDiskPartitionPage) &&
      GetSettingsBool(kPartitionSkipSimplePartitionPage)) {
    advanced_frame_button_->setObjectName(kSoloBtn);
  } else {
    advanced_frame_button_->setObjectName(kRightBtn);
  }
  partition_stacked_layout_->addWidget(advanced_partition_frame_);

  auto* partition_stacked_wrapper_layout = new QHBoxLayout();
  partition_stacked_wrapper_layout->setContentsMargins(0, 0, 0, 0);
  partition_stacked_wrapper_layout->setSpacing(0);
  partition_stacked_wrapper_layout->addStretch();
  partition_stacked_wrapper_layout->addLayout(partition_stacked_layout_);
  partition_stacked_wrapper_layout->addStretch();

  // and advanced partition page.
  next_button_ = new NavButton(tr("Start installation"));
  auto* next_layout = new QHBoxLayout();
  next_layout->setContentsMargins(0, 0, 0, 0);
  next_layout->addWidget(next_button_);

  auto* layout = new QVBoxLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
  layout->addWidget(title_label_, 0, Qt::AlignHCenter);
  layout->addSpacing(kMainLayoutSpacing);
  layout->addLayout(comment_layout);
  layout->addSpacing(kMainLayoutSpacing);
  if ((!GetSettingsBool(kPartitionSkipSimplePartitionPage) ||
       !GetSettingsBool(kPartitionSkipFullDiskPartitionPage))) {
    // Add control button groups only if both simple mode and advanced mode
    // are enabled.
    layout->addLayout(button_layout);
  }
  layout->addSpacing(20 + kMainLayoutSpacing);
  layout->addLayout(partition_stacked_wrapper_layout);
  layout->addLayout(next_layout);

  main_frame_ = new QFrame();
  main_frame_->setContentsMargins(0, 0, 0, 0);
  main_frame_->setLayout(layout);
  main_frame_->setStyleSheet(ReadFile(kStylePartitionMainFrameCss));

  main_layout_ = new QStackedLayout();
  main_layout_->setContentsMargins(0, 0, 0, 0);
  main_layout_->addWidget(partition_loading_frame_);
  main_layout_->addWidget(main_frame_);
  main_layout_->addWidget(edit_partition_frame_);
  main_layout_->addWidget(new_partition_frame_);
  main_layout_->addWidget(new_table_loading_frame_);
  main_layout_->addWidget(new_table_warning_frame_);
  main_layout_->addWidget(partition_number_limitation_frame_);
  main_layout_->addWidget(partition_table_warning_frame_);
  main_layout_->addWidget(prepare_install_frame_);
  main_layout_->addWidget(select_bootloader_frame_);

  this->setLayout(main_layout_);
  this->setContentsMargins(0, 0, 0, 0);
}

bool PartitionFrame::isFullDiskPartitionMode() {
  QWidget* current_widget = partition_stacked_layout_->currentWidget();
  return current_widget == full_disk_partition_frame_;
}

bool PartitionFrame::isSimplePartitionMode() {
  QWidget* current_widget = partition_stacked_layout_->currentWidget();
  return current_widget == simple_partition_frame_;
}

void PartitionFrame::onFullDiskFrameButtonToggled() {
  partition_stacked_layout_->setCurrentWidget(full_disk_partition_frame_);
}

void PartitionFrame::onSimpleFrameButtonToggled() {
  partition_stacked_layout_->setCurrentWidget(simple_partition_frame_);
}

void PartitionFrame::onAdvancedFrameButtonToggled() {
  qDebug() << "on advanced button toggled";
  // Refresh device list before showing advanced partition frame.
  // Because mount-point of partitions might have be updated.
  advanced_delegate_->refreshVisual();
  partition_stacked_layout_->setCurrentWidget(advanced_partition_frame_);
}

void PartitionFrame::onNextButtonClicked() {
  if (this->isSimplePartitionMode()) {
    // Validate simple partition frame.
    if (!simple_partition_frame_->validate()) {
      return;
    }
  } else if (this->isFullDiskPartitionMode()) {
    if (!full_disk_partition_frame_->validate()) {
      return;
    }
  } else {
    // Validate advanced partition frame.
    if (!advanced_partition_frame_->validate()) {
      return;
    }
  }

  QStringList descriptions;
  if (this->isSimplePartitionMode()) {
    descriptions = simple_partition_delegate_->getOptDescriptions();
  } else if (this->isFullDiskPartitionMode()) {
    descriptions = full_disk_delegate_->getOptDescriptions();
  } else {
    descriptions = advanced_delegate_->getOptDescriptions();
  }

  prepare_install_frame_->updateDescription(descriptions);
  main_layout_->setCurrentWidget(prepare_install_frame_);
}

void PartitionFrame::onManualPartDone(bool ok, const DeviceList& devices) {
  if (ok) {
    // Write settings to file.
    if (this->isSimplePartitionMode()) {
      simple_partition_delegate_->onManualPartDone(devices);
    } else if (this->isFullDiskPartitionMode()) {
      full_disk_delegate_->onManualPartDone(devices);
    } else {
      advanced_delegate_->onManualPartDone(devices);
    }
  }

  emit this->manualPartDone(ok);
}

void PartitionFrame::onPrepareInstallFrameFinished() {
  // First, update boot flag.
  bool found_boot;
  if (this->isSimplePartitionMode()) {
    found_boot = simple_partition_delegate_->setBootFlag();
  } else if (this->isFullDiskPartitionMode()) {
    found_boot = full_disk_delegate_->setBootFlag();
  } else {
    found_boot = advanced_delegate_->setBootFlag();
  }

  if (!found_boot) {
    qCritical() << "No boot partition found, we shall never reach here!";
    return;
  }

  // Get operation list.
  OperationList operations;
  if (this->isSimplePartitionMode()) {
    operations = simple_partition_delegate_->operations();
  } else if (this->isFullDiskPartitionMode()) {
    operations = full_disk_delegate_->operations();
  } else {
    operations = advanced_delegate_->operations();
  }

  if (operations.isEmpty()) {
    qCritical() << "Operation list is empty";
    return;
  } else {
    partition_model_->manualPart(operations);
    emit this->finished();
  }
}

void PartitionFrame::showEditPartitionFrame(const Partition& partition) {
  edit_partition_frame_->setPartition(partition);
  main_layout_->setCurrentWidget(edit_partition_frame_);
}

void PartitionFrame::showMainFrame() {
  main_layout_->setCurrentWidget(main_frame_);
}

void PartitionFrame::showNewPartitionFrame(
    const Partition& partition) {
  new_partition_frame_->setPartition(partition);
  main_layout_->setCurrentWidget(new_partition_frame_);
}

void PartitionFrame::showNewTableLoadingFrame() {
  main_layout_->setCurrentWidget(new_table_loading_frame_);
}

void PartitionFrame::showNewTableWarningFrame(const QString& device_path) {
  DeviceList devices;
  if (this->isSimplePartitionMode()) {
    devices = simple_partition_delegate_->real_devices();
  } else if (this->isFullDiskPartitionMode()) {
    qCritical() << "Never show new table warning frame for simple disk frame";
    return;
  } else {
    devices = advanced_delegate_->real_devices();
  }

  const int device_index = DeviceIndex(devices, device_path);
  Q_ASSERT(device_index > -1);
  if (device_index == -1) {
    qCritical() << "Failed to find device at:" << device_path;
    return;
  }
  const Device& device = devices.at(device_index);
  const QString device_info = GetDeviceModelCapAndPath(device);

  new_table_warning_frame_->setDevicePath(device_path, device_info);
  main_layout_->setCurrentWidget(new_table_warning_frame_);
}

void PartitionFrame::showPartitionNumberLimitationFrame() {
  main_layout_->setCurrentWidget(partition_number_limitation_frame_);
}

void PartitionFrame::showPartitionTableWarningFrame(
    const QString& device_path) {
  partition_table_warning_frame_->setDevicePath(device_path);
  main_layout_->setCurrentWidget(partition_table_warning_frame_);
}

void PartitionFrame::showSelectBootloaderFrame() {
  main_layout_->setCurrentWidget(select_bootloader_frame_);
}

}  // namespace installer
