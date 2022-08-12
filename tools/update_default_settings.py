#!/usr/bin/env python3
#
# Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
# Copyright (C) 2022 Xu Shaohua <shaohua@biofan.org>.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

# Generate default settings for non x86_64 platforms.
# Execute this program after updating options in resources/settings.default_settings.ini.

import configparser
import os
import shutil
import sys

SEC_NAME = "General"
BASE_DIR = "resources/settings"

def update_settings(settings_filename, settings):
    src_settings = os.path.join(BASE_DIR, "default_settings.ini")
    target_settings = os.path.join(BASE_DIR, settings_filename)
    if not os.path.exists(src_settings):
        print("Failed to find", src_settings)
        sys.exit(1)
    shutil.copy(src_settings, target_settings)

    parser = configparser.ConfigParser()
    parser.read(target_settings)
    for key, value in settings:
        parser.set(SEC_NAME, key, value)
    with open(target_settings, "w") as fh:
        parser.write(fh)

    parser = configparser.ConfigParser()
    parser.read(target_settings)
    for key, value in settings:
        parser.set(SEC_NAME, key, value)
    with open(target_settings, "w") as fh:
        parser.write(fh)

def main():
    x86_64_file = "default_settings_x86_64.ini"
    aarch64_file = "default_settings_aarch64.ini"
    mips64_file = "default_settings_mips64.ini"
    sw64_file = "default_settings_sw64.ini"

    x86_64_settings = []

    aarch64_settings = (
        ("skip_virtual_machine_page", "true"),
    )

    mips64_settings = (
        ("skip_virtual_machine_page", "true"),
        ("skip_select_language_page", "true"),
        ("skip_timezone_page", "true"),
        ("select_language_default_locale", "zh_CN"),
        ("system_info_disable_keyboard_page", "true"),
        ("system_info_default_keyboard_layout", '"us"'),
        ("timezone_default", '"Asia/Shanghai"'),
        ("timezone_use_regdomain", "false"),
        ("partition_skip_simple_partition_page", "true"),
        ("partition_enable_simple_disk_page", "true"),
        ("partition_enable_swap_file", "false"),
        ("partition_formatted_mount_points", '"/;/tmp;/var"'),
        ("partition_enable_os_prober", "false"),
        ("partition_boot_on_first_partition", "true"),
        ("partition_supported_fs", '"ext4;ext3;ext2;efi;linux-swap"'),
        ("partition_prefer_logical_partition", "false"),
    )

    sw64_settings = (
        ("skip_virtual_machine_page", "true"),
        ("skip_select_language_page", "true"),
        ("skip_timezone_page", "true"),
        ("select_language_default_locale", "zh_CN"),
        ("system_info_disable_keyboard_page", "true"),
        ("system_info_default_keyboard_layout", '"us"'),
        ("timezone_default", '"Asia/Shanghai"'),
        ("timezone_use_regdomain", "false"),
        ("partition_enable_swap_file", "false"),
        ("partition_swap_partition_size", "8192"),
        ("partition_skip_simple_partition_page", "true"),
        ("partition_enable_simple_disk_page", "true"),
        ("partition_enable_swap_file", "false"),
        ("partition_formatted_mount_points", '"/;/tmp;/var"'),
        ("partition_enable_os_prober", "false"),
        ("partition_boot_on_first_partition", "true"),
        ("partition_supported_fs", '"ext4;ext3;ext2;efi;linux-swap"'),
        ("partition_prefer_logical_partition", "false"),
    )

    update_settings(x86_64_file, x86_64_settings)
    update_settings(aarch64_file, aarch64_settings)
    update_settings(mips64_file, mips64_settings)
    update_settings(sw64_file, sw64_settings)

if __name__ == "__main__":
    main()
