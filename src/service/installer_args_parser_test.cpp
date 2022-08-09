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

#include <gtest/gtest.h>

#include "installer_args_parser.h"

namespace installer {
namespace {

TEST(InstallerArgsParserTest, Parse) {
  InstallerArgsParser parser;
  const QString conf_file("/tmp/installer.conf");
  const QString log_file("/tmp/installer.log");
  QStringList args;
  args << "app-name" << "--conf" << conf_file
       << "--log" << log_file << "--auto-install";
  EXPECT_TRUE(parser.parse(args));
  EXPECT_TRUE(parser.isAutoInstallSet());
  EXPECT_EQ(parser.getConfFile(), conf_file);
  EXPECT_EQ(parser.getLogFile(), log_file);
}

}  // namespace
}  // namespace installer