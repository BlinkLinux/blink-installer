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

#include "ui/delegates/partition_util.h"

#include <cmath>

#include <QFileInfo>
#include <QRegularExpression>

#include "partman/os_prober.h"
#include "partman/utils.h"
#include "resources/images/images.h"
#include "service/settings_manager.h"
#include "service/settings_name.h"
#include "sysinfo/proc_meminfo.h"
#include "sysinfo/proc_mounts.h"

namespace installer {

namespace {

// Maximum length of partition label.
constexpr const int kLabelMaxLen = 25;

// Mount points of live system in use currently.
constexpr const char* kCasperMountPoint = "/cdrom";
constexpr const char* kLiveMountPoint = "/lib/live/mount/medium";

// Get distribution description at partition |path| if it contains an OS.
QString GetOsDescription(const QString& path) {
  const OsProberItems items = GetOsProberItems();
  for (const OsProberItem& item : items) {
    if (item.path == path) {
      return item.description;
    }
  }
  return "";
}

}  // namespace

void AlignPartition(Partition& partition) {
  const qint64 oneMebiByteSector = 1 * kMebiByte / partition.sector_size;

  // Align to nearest MebiBytes.
  const int start_size = static_cast<int>(
      ceil(partition.start_sector * 1.0 / oneMebiByteSector));
  const int end_size = static_cast<int>(
      floor((partition.end_sector + 1) * 1.0 / oneMebiByteSector));
  partition.start_sector = start_size * oneMebiByteSector;
  partition.end_sector = end_size * oneMebiByteSector - 1;
}

int AllocLogicalPartitionNumber(const Device& device) {
  int num = device.max_prims;
  for (const Partition& partition : device.partitions) {
    if (partition.partition_number >= num) {
      num = partition.partition_number;
    }
  }
  return num + 1;
}

int AllocPrimaryPartitionNumber(const Device& device) {
  for (int num = 1; num <= device.max_prims; num++) {
    bool in_use = false;
    for (const Partition& partition : device.partitions) {
      if (num == partition.partition_number) {
        in_use = true;
        break;
      }
    }

    if (!in_use) {
      return num;
    }
  }
  return -1;
}

// Filter installation device from device list.
DeviceList FilterInstallerDevice(const DeviceList& devices) {
  if (!GetSettingsBool(kPartitionHideInstallationDevice)) {
    return devices;
  }

  DeviceList filtered_devices;
  const QString installer_device_path(GetInstallerDevicePath());
  for (const Device& device : devices) {
    if (!installer_device_path.startsWith(device.path)) {
      filtered_devices.append(device);
    } else {
      qDebug() << "Filtered device:" << device;
    }
  }

  return filtered_devices;
}

FsType GetDefaultFsType() {
  const QString default_fs_name = GetSettingsString(kPartitionDefaultFs);
  return GetFsTypeByName(default_fs_name);
}

QString GetDeviceModelAndCap(const Device& device) {
  const int gibi_size = ToGigByte(device.getByteLength());
  return QString("%1 (%2G)").arg(device.model).arg(gibi_size);
}

QString GetDeviceModelCapAndPath(const Device& device) {
  const int gibi_size = ToGigByte(device.getByteLength());
  const QString name(QFileInfo(device.path).fileName());
  return QString("%1 %2G(%3)").arg(device.model).arg(gibi_size).arg(name);
}

QString GetInstallerDevicePath() {
  const MountItemList list(ParseMountItems());

  // Parse symbolic link to mount point.
  QString casper_path(kCasperMountPoint);
  QFileInfo casper_info(kCasperMountPoint);
  if (casper_info.exists()) {
    casper_path = casper_info.canonicalFilePath();
  }
  QString live_path(kLiveMountPoint);
  QFileInfo live_info(kLiveMountPoint);
  if (live_info.exists()) {
    live_path = live_info.canonicalFilePath();
  }

  for (const MountItem& item : list) {
    if (item.mount == casper_path || item.mount == live_path) {
      return item.path;
    }
  }

  // Returns an empty string if not found.
  return {};
}

QString GetLocalFsTypeName(FsType fs_type) {
  switch (fs_type) {
    case FsType::Btrfs: return "btrfs";
    case FsType::EFI: return "efi";
    case FsType::Empty: return QObject::tr("Do not use this partition");
    case FsType::Ext2: return "ext2";
    case FsType::Ext3: return "ext3";
    case FsType::Ext4: return "ext4";
    case FsType::Fat16: return "fat16";
    case FsType::Fat32: return "fat32";
    case FsType::Hfs: return "hfs";
    case FsType::HfsPlus: return "hfs+";
    case FsType::Jfs: return "jfs";
    case FsType::Nilfs2: return "nilfs2";
    case FsType::NTFS: return "ntfs";
    case FsType::Reiser4: return "reiser4";
    case FsType::Reiserfs: return "reiserfs";
    case FsType::LinuxSwap: return QObject::tr("Swap partition");
    case FsType::Xfs: return "xfs";
    default: return QObject::tr("Unknown");
  }
}

QString GetOsTypeIcon(OsType os_type) {
  switch (os_type) {
    case OsType::Linux: {
      return kImageDriverLinux32Png;
    }
    case OsType::Mac: {
      return kImageDriverMac32Png;
    }
    case OsType::Windows: {
      return kImageDriverWindows32Png;
    }
    default: {
      return kImageDriver32Png;
    }
  }
}

QString GetOsTypeLargeIcon(OsType os_type) {
  switch (os_type) {
    case OsType::Linux: {
      return kImageDriverLinux128Png;
    }
    case OsType::Mac: {
      return kImageDriverMac128Png;
    }
    case OsType::Windows: {
      return kImageDriverWindows128Png;
    }
    default: {
      return kImageDriver128Png;
    }
  }
}

QString GetPartitionLabel(const Partition& partition) {
  switch (partition.type) {
    case PartitionType::Unallocated: {
      return QObject::tr("Freespace");
    }
    case PartitionType::Normal:  // pass through
    case PartitionType::Logical: {
      // If partition is created, returns its path name only.
      if (partition.status == PartitionStatus::New) {
        return GetPartitionName(partition.path);
      }

      const QString os_description = GetOsDescription(partition.path);
      if (!os_description.isEmpty()) {
        return TrimText(os_description, kLabelMaxLen);
      }
      // Check partition label before partition name.
      if (!partition.label.isEmpty()) {
        return TrimText(partition.label, kLabelMaxLen);
      }
      if (!partition.name.isEmpty()) {
        return TrimText(partition.name, kLabelMaxLen);
      }
      return GetPartitionName(partition.path);
    }
    default: {
      return {};
    }
  }
}

QString GetPartitionLabelAndPath(const Partition& partition) {
  switch (partition.type) {
    case PartitionType::Unallocated: {
      return QObject::tr("Freespace");
    }
    case PartitionType::Normal:  // pass through
    case PartitionType::Logical: {
      // If partition is created, returns its path name only.
      if (partition.status == PartitionStatus::New) {
        return GetPartitionName(partition.path);
      }

      const QString os_description = GetOsDescription(partition.path);
      const QString name = GetPartitionName(partition.path);
      if (!os_description.isEmpty()) {
        const QString label = TrimText(os_description, kLabelMaxLen);
        return QString("%1(%2)").arg(label).arg(name);
      }
      if (!partition.label.isEmpty()) {
        const QString label = TrimText(partition.label, kLabelMaxLen);
        return QString("%1(%2)").arg(label).arg(name);
      }
      if (!partition.name.isEmpty()) {
        const QString label = TrimText(partition.name, kLabelMaxLen);
        return QString("%1(%2)").arg(label).arg(name);
      }
      return name;
    }
    default: {
      return {};
    }
  }
}

QString GetPartitionName(const QString& path) {
  return QFileInfo(path).fileName();
}

QString GetPartitionUsage(const Partition& partition) {
  qint64 total, used;
  if ((partition.length > 0) && (partition.length >= partition.freespace)) {
    total = partition.length;
    used = total - partition.freespace;
  } else {
    total = partition.getByteLength();
    used = 0;
  }

  if (total < 1 * kGibiByte) {
    return QString("%1/%2M").arg(ToMebiByte(used)).arg(ToMebiByte(total));
  } else {
    return QString("%1/%2G").arg(ToGigByte(used)).arg(ToGigByte(total));
  }
}

int GetPartitionUsageValue(const Partition& partition) {
  qint64 total, used;
  if ((partition.length > 0) && (partition.length >= partition.freespace)) {
    total = partition.length;
    used = total - partition.freespace;
  } else {
    total = partition.getByteLength();
    used = 0;
  }
  if (total > 0 && used >= 0 && total >= used) {
    return int(100.0 * used / total);
  } else {
    return 0;
  }
}

bool IgnoreUEFI(const DeviceList& devices) {
  // Check in UEFI mode or not.
  if (IsEfiEnabled()) {
    for (const Device& device : devices) {
      // Check partition table type.
      if (device.table != PartitionTableType::GPT) {
        for (const Partition& partition : device.partitions) {
          if (partition.os != OsType::Empty) {
            return true;
          }
        }
      }
    }
  }
  return false;
}

bool IsEfiEnabled() {
  return QDir("/sys/firmware/efi").exists();
}

bool IsMBRPreferred(const DeviceList& devices) {
  if (IsEfiEnabled()) {
    return IgnoreUEFI(devices);
  } else {
    return true;
  }
}

// Returns true if |fs_type| may be mounted to system with customized
// mount point.
bool IsMountPointSupported(FsType fs_type) {
  return (fs_type != FsType::EFI &&
          fs_type != FsType::LinuxSwap &&
          fs_type != FsType::Empty &&
          fs_type != FsType::Unknown);
}

bool IsPartitionTableMatch(PartitionTableType type) {
  // If EFI is not enabled, always returns true.
  if (!IsEfiEnabled()) {
    return true;
  }

  // If partition table is empty(a raw disk device), returns true.
  if (type == PartitionTableType::Empty) {
    return true;
  }

  return type == PartitionTableType::GPT;
}

bool IsPartitionTableMatch(const DeviceList& devices,
                           const QString& device_path) {
  if (IgnoreUEFI(devices)) {
    return true;
  }

  const int device_index = DeviceIndex(devices, device_path);
  if (device_index == -1) {
    qCritical() << "Failed to find device:" << device_path;
    return false;
  }
  PartitionTableType table = devices.at(device_index).table;
  return IsPartitionTableMatch(table);
}

bool IsSwapAreaNeeded() {
  const MemInfo mem_info = GetMemInfo();
  const qint64 mem_threshold =
      GetSettingsInt(kPartitionMemoryThresholdForSwapArea) * kGibiByte;
  return mem_info.mem_total <= mem_threshold;
}

int ToGigByte(qint64 size) {
  const double m_size = double(size) / kKibiByte;
  return int(round(m_size / kMebiByte));
}

int ToMebiByte(qint64 size) {
  return int(round(double(size) / kMebiByte));
}

QString TrimText(const QString& text, int max_len) {
  if (text.length() > max_len) {
    return text.left(max_len) + "..";
  } else {
    return text;
  }
}

qint64 ParsePartitionSize(const QString& size, qint64 device_length) {
  QRegularExpression pattern("(\\d+)(mib|gib|%)", QRegularExpression::CaseInsensitiveOption);
  const QRegularExpressionMatch match = pattern.match(size);
  if (match.hasMatch()) {
    bool ok;
    const int num = match.captured(1).toInt(&ok, 10);
    if (!ok || num < 0) {
      qCritical() << "Invalid size:" << num;
      return -1;
    }

    const QString unit = match.captured(2).toLower();
    if (unit == "mib") {
      return num * kMebiByte;
    } else if (unit == "gib") {
      return num * kGibiByte;
    } else if (unit == "%") {
      return num * device_length;
    } else {
      qCritical() << Q_FUNC_INFO << "Invalid unit found:" << num;
      return -1;
    }
  }
  return -1;
}

}  // namespace installer