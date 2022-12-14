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

#include "ui/widgets/advanced_partition_button.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QStyle>

#include "base/file_util.h"
#include "resources/styles/styles.h"
#include "ui/delegates/partition_util.h"
#include "ui/utils/widget_util.h"
#include "ui/widgets/rounded_progress_bar.h"

namespace installer {

namespace {

constexpr const int kBtnSize = 24;

constexpr const char* kCtlBtnState = "ctlState";
constexpr const char* kCtlBtnStateDelete = "delete";
constexpr const char* kCtlBtnStateEdit = "edit";
constexpr const char* kCtlBtnStateNew = "new";
constexpr const char* kCtlBtnStateHide = "hide";

}  // namespace

AdvancedPartitionButton::AdvancedPartitionButton(const Partition& partition,
                                                 QWidget* parent)
    : PointerButton(parent),
      partition_(partition),
      editable_(false) {
  this->setObjectName("advanced_partition_button");

  this->initUI();
  this->initConnections();
}

const Partition& AdvancedPartitionButton::partition() const {
  return partition_;
}

void AdvancedPartitionButton::setEditable(bool editable) {
  this->editable_ = editable;
  this->updateStatus();
}

void AdvancedPartitionButton::initConnections() {
  connect(control_button_, &QPushButton::clicked,
          this, &AdvancedPartitionButton::onControlButtonClicked);
  connect(this, &QPushButton::toggled,
          this, &AdvancedPartitionButton::onToggled);
}

void AdvancedPartitionButton::initUI() {
  auto* os_label = new QLabel();
  os_label->setObjectName("os_label");
  os_label->setPixmap(GetOsTypeIcon(partition_.os));

  // partition label name
  auto* name_label = new QLabel();
  name_label->setObjectName("name_label");
  name_label->setText(GetPartitionLabel(partition_));

  // partition path
  auto* path_label = new QLabel();
  path_label->setObjectName("path_label");
  if (partition_.type != PartitionType::Unallocated) {
    const QString name = GetPartitionName(partition_.path);
    path_label->setText(QString("(%1)").arg(name));
  }

  auto* path_layout = new QHBoxLayout();
  path_layout->setContentsMargins(0, 0, 0, 0);
  path_layout->setSpacing(10);
  path_layout->addWidget(os_label);
  path_layout->addWidget(name_label);
  path_layout->addWidget(path_label);
  path_layout->addStretch();
  auto* path_frame = new QFrame();
  path_frame->setObjectName("path_frame");
  path_frame->setContentsMargins(0, 0, 0, 0);
  path_frame->setLayout(path_layout);
  path_frame->setFixedWidth(220);

  // partition space usage
  auto* usage_label = new QLabel();
  usage_label->setObjectName("usage_label");
  usage_label->setText(GetPartitionUsage(partition_));
  usage_label->setFixedWidth(64);

  QProgressBar* usage_bar = new RoundedProgressBar();
  usage_bar->setValue(GetPartitionUsageValue(partition_));
  usage_bar->setFixedSize(100, 6);

  // mount point
  auto* mount_point_label = new QLabel();
  mount_point_label->setObjectName("mount_point_label");
  mount_point_label->setText(partition_.mount_point);
  mount_point_label->setFixedWidth(64);

  // tip
  auto* tip_label = new QLabel();
  tip_label->setObjectName("tip_label");
  tip_label->setFixedWidth(112);
  if (partition_.mount_point == kMountPointRoot) {
    tip_label->setText(tr("Install here"));
  } else if (partition_.status == PartitionStatus::Format ||
             partition_.status == PartitionStatus::New) {
    tip_label->setText(tr("To be formatted"));
  }

  // filesystem name
  auto* fs_label = new QLabel();
  fs_label->setObjectName("fs_label");
  if (partition_.type == PartitionType::Normal ||
      partition_.type == PartitionType::Logical) {
    fs_label->setText(GetFsTypeName(partition_.fs));
  }
  fs_label->setFixedWidth(80);

  auto* control_button_wrapper = new QFrame();
  control_button_wrapper->setObjectName("control_button_wrapper");
  control_button_wrapper->setContentsMargins(0, 0, 0, 0);
  control_button_wrapper->setFixedSize(kBtnSize, kBtnSize);

  control_button_ = new PointerButton(control_button_wrapper);
  control_button_->setObjectName("control_button");
  control_button_->setFlat(true);
  control_button_->setFixedSize(kBtnSize, kBtnSize);
  control_button_->setProperty(kCtlBtnState, kCtlBtnStateHide);

  auto* layout = new QHBoxLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
  layout->addSpacing(20);
  layout->addWidget(path_frame);
  layout->addStretch();
  layout->addWidget(usage_label);
  layout->addWidget(usage_bar);
  layout->addStretch();
  layout->addWidget(mount_point_label);
  layout->addStretch();
  layout->addWidget(tip_label);
  layout->addStretch();
  layout->addWidget(fs_label);
  layout->addStretch();
  layout->addWidget(control_button_wrapper);
  layout->addSpacing(15);

  this->setContentsMargins(0, 0, 0, 0);
  this->setLayout(layout);
  this->setFixedHeight(60);
  this->setCheckable(true);
  this->setChecked(false);
  this->setFlat(true);
  this->setStyleSheet(ReadFile(kStyleAdvancedPartitionButtonCss));
}

void AdvancedPartitionButton::updateStatus() {
  control_status_ = ControlStatus::Hide;

  if (editable_) {
    if (partition_.type == PartitionType::Normal ||
        partition_.type == PartitionType::Logical) {
      control_status_ = ControlStatus::Delete;
      control_button_->setProperty(kCtlBtnState, kCtlBtnStateDelete);
    }
  } else if (this->isChecked()) {
    if (partition_.type == PartitionType::Normal ||
        partition_.type == PartitionType::Logical) {
      control_status_ = ControlStatus::Edit;
      control_button_->setProperty(kCtlBtnState, kCtlBtnStateEdit);
    } else if (partition_.type == PartitionType::Unallocated) {
      control_status_ = ControlStatus::New;
      control_button_->setProperty(kCtlBtnState, kCtlBtnStateNew);
    }
  } else {
    control_button_->setProperty(kCtlBtnState, kCtlBtnStateHide);
  }

  control_button_->setVisible(control_status_ != ControlStatus::Hide);
  control_button_->style()->unpolish(control_button_);
  control_button_->style()->polish(control_button_);
  control_button_->update();
}

void AdvancedPartitionButton::onControlButtonClicked() {
  switch (control_status_) {
    case ControlStatus::Delete: {
      emit this->deletePartitionTriggered(partition_);
      break;
    }
    case ControlStatus::Edit: {
      emit this->editPartitionTriggered(partition_);
      break;
    }
    case ControlStatus::New: {
      emit this->newPartitionTriggered(partition_);
      break;
    }
    default: {
      // Never reach here.
      break;
    }
  }
}

void AdvancedPartitionButton::onToggled() {
  this->updateStatus();
}

}  // namespace installer