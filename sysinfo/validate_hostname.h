// Copyright (c) 2016 Deepin Ltd. All rights reserved.
// Use of this source is governed by General Public License that can be found
// in the LICENSE file.

#ifndef DEEPIN_INSTALLER_REBORN_SYSINFO_VALIDATE_HOSTNAME_H
#define DEEPIN_INSTALLER_REBORN_SYSINFO_VALIDATE_HOSTNAME_H

#include <QString>

namespace sysinfo {

// Check hostname (machine name) based on the following rules:
//   * Only letters(a-z, A-Z) and numbers(0-9) can be used as prefix/suffix;
//   * Dot(.) is used to separate domain and sub-domain;
//   * Underscore(_) and dash(-) are used to concat letters and numbers.
bool ValidateHostname(const QString& hostname);

// Validate part of hostname.
// Use this function when |hostname| is being edited.
bool ValidateHostnameTemp(const QString& hostname);

}  // namespace sysinfo

#endif  // DEEPIN_INSTALLER_REBORN_SYSINFO_VALIDATE_HOSTNAME_H