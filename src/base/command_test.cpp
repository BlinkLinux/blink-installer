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

#include "base/command.h"
#include "base/file_util.h"

namespace installer {
namespace {

TEST(CommandTest, RunScriptFile) {
  const QString script_file = "/tmp/installer-command-test.sh";
  EXPECT_TRUE(WriteTextFile(script_file, "ls /"));
  EXPECT_TRUE(RunScriptFile({script_file}));
}

TEST(CommandTest, SpawnCmd) {
  QString output;
  QString err;
  const bool ok = SpawnCmd("ls", {"-h", "/"}, output, err);
  EXPECT_TRUE(ok);
  EXPECT_GT(output.length(), 0);
  EXPECT_GT(output.indexOf("root"), 0);
}

}  // namespace
}  // namespace installer