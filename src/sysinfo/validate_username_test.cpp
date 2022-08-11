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

#include "resources/misc/misc.h"
#include "sysinfo/validate_username.h"

namespace installer {
namespace {

TEST(ValidateUsernameTest, ValidateUsername) {
  EXPECT_EQ(ValidateUsername("root", kMiscReservedUsernames, 1, 10),
            ValidateUsernameState::ReservedError);
  EXPECT_EQ(ValidateUsername("", kMiscReservedUsernames, 1, 10),
            ValidateUsernameState::EmptyError);
  EXPECT_EQ(ValidateUsername("AbcUser", kMiscReservedUsernames, 1, 10),
            ValidateUsernameState::FirstCharError);
  EXPECT_EQ(ValidateUsername("a:invalid", kMiscReservedUsernames, 1, 10),
            ValidateUsernameState::InvalidCharError);
  EXPECT_EQ(ValidateUsername("hello_world", kMiscReservedUsernames, 1, 5),
            ValidateUsernameState::TooLongError);
  EXPECT_EQ(ValidateUsername("hello", kMiscReservedUsernames, 6, 10),
            ValidateUsernameState::TooShortError);
  EXPECT_EQ(ValidateUsername("not-used-username", kMiscReservedUsernames,
                             1, 24),
            ValidateUsernameState::Ok);
}

}  // namespace
}  // namespace installer
