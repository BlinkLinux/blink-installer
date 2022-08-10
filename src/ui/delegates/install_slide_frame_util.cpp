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

#include "ui/delegates/install_slide_frame_util.h"

#include <QDebug>

#include "base/file_util.h"
#include "resources/slide/slide.h"
#include "service/settings_manager.h"

namespace installer {

QStringList GetOemSlideFiles(const QString& locale) {
  QDir oem_dir(GetOemDir());

  // Check existence of folders one by one.
  QDir slide_dir(oem_dir.absoluteFilePath(locale));
  if (!slide_dir.exists()) {
    return {};
  }

  // List all png files in slide folder.
  QStringList slide_files;
  QString filepath;
  for (const QString& filename : slide_dir.entryList({"*.png"}, QDir::Files)) {
    filepath = slide_dir.absoluteFilePath(filename);
    if (QFile::exists(filepath)) {
      slide_files.append(filepath);
    }
  }
  return slide_files;
}

QStringList GetSlideFiles(const QString& locale) {
  QStringList slide_files = GetOemSlideFiles(locale);
  if (slide_files.isEmpty()) {
    if (locale == "zh_CN") {
      for (const auto* name: kSlideListZhCN) {
        slide_files.append(name);
      }
    } else if (locale == "zh_TW") {
      for (const auto* name: kSlideListZhTW) {
        slide_files.append(name);
      }
    } else {
      for (const auto* name: kSlideListDefault) {
        slide_files.append(name);
      }
    }
  }
  return slide_files;
}

}  // namespace installer
