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

#include "service/languages.h"

#include <QDebug>
#include <QFile>

namespace installer {

namespace {

constexpr const char kDefaultLanguageFile[] = ":i18n/installer-en_US.qm";
constexpr const char kLanguageFileTpl[] = ":i18n/installer-%1.qm";

}  // namespace

QString GetLocalePath(const QString& locale) {
  QString filepath = QString(kLanguageFileTpl).arg(locale);
  if (QFile::exists(filepath)) {
    return filepath;
  }

  // Get language region only. e.g. ru_RU => ru
  const int underscore_index = locale.indexOf('_');
  filepath = QString(kLanguageFileTpl).arg(locale.left(underscore_index));
  if (QFile::exists(filepath)) {
    return filepath;
  }

  return kDefaultLanguageFile;
}

}  // namespace installer