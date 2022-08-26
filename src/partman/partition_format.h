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

#ifndef INSTALLER_PARTMAN_PARTITION_FORMAT_H
#define INSTALLER_PARTMAN_PARTITION_FORMAT_H

#include <QString>

#include "partman/partition.h"

namespace installer {

// Format filesystem.
bool Mkfs(const Partition& partition);

bool FormatBtrfs(const QString& path, const QString& label);

bool FormatExt2(const QString& path, const QString& label);

bool FormatExt3(const QString& path, const QString& label);

bool FormatExt4(const QString& path, const QString& label);

bool FormatF2fs(const QString& path, const QString& label);

bool FormatFat16(const QString& path, const QString& label);

bool FormatFat32(const QString& path, const QString& label);

bool FormatHfsPlus(const QString& path, const QString& label);

bool FormatJfs(const QString& path, const QString& label);

bool FormatLinuxSwap(const QString& path, const QString& label);

bool FormatNilfs2(const QString& path, const QString& label);

bool FormatNTFS(const QString& path, const QString& label);

bool FormatReiser4(const QString& path, const QString& label);

bool FormatReiserfs(const QString& path, const QString& label);

bool FormatXfs(const QString& path, const QString& label);

}  // namespace installer

#endif  // INSTALLER_PARTMAN_PARTITION_FORMAT_H
