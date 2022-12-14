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

#ifndef DEEPIN_INSTALLER_SYSINFO_RELEASE_VERSION_H
#define DEEPIN_INSTALLER_SYSINFO_RELEASE_VERSION_H

#include <QString>

namespace installer {

struct ReleaseVersion {
  QString version;
  QString type;
};

ReleaseVersion GetReleaseVersion();

QString GetTargetDistribution();

}  // namespace installer

#endif  // DEEPIN_INSTALLER_SYSINFO_RELEASE_VERSION_H
