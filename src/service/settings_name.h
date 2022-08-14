/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 * Copyright (C) 2022 Xu Shaohua <shaohua@biofan.org>
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

#ifndef INSTALLER_SERVICE_SETTINGS_NAME_H
#define INSTALLER_SERVICE_SETTINGS_NAME_H

namespace installer {

// Keys used in settings ini file.

// Pages
constexpr const char* kSkipDiskSpaceInsufficientPage = "skip_disk_space_insufficient_page";
constexpr const char* kSkipVirtualMachinePage = "skip_virtual_machine_page";
constexpr const char* kSkipSelectLanguagePage = "skip_select_language_page";
constexpr const char* kSkipSystemInfoPage = "skip_system_info_page";
constexpr const char* kSkipTimezonePage = "skip_timezone_page";
constexpr const char* kSkipPartitionPage = "skip_partition_page";

// System Language List
constexpr const char* kSelectLanguageDefaultLocale = "select_language_default_locale";

// System Info
constexpr const char* kSystemInfoDebianVersion = "system_info_debian_version";
constexpr const char* kSystemInfoLsbRelease = "system_info_lsb_release";
constexpr const char* kSystemInfoVendorName = "system_info_vendor_name";
constexpr const char* kSystemInfoSetupAfterReboot = "system_info_setup_after_reboot";
constexpr const char* kSystemInfoDefaultUsername = "system_info_default_username";
constexpr const char* kSystemInfoLockUsername = "system_info_lock_username";
constexpr const char* kSystemInfoUsernameMinLen = "system_info_username_min_len";
constexpr const char* kSystemInfoUsernameMaxLen = "system_info_username_max_len";
constexpr const char* kSystemInfoDefaultHostname = "system_info_default_hostname";
constexpr const char* kSystemInfoLockHostname = "system_info_lock_hostname";
constexpr const char* kSystemInfoHostnameAutoSuffix = "system_info_hostname_auto_suffix";
constexpr const char* kSystemInfoHostnameReserved = "system_info_hostname_reserved";
constexpr const char* kSystemInfoDefaultPassword = "system_info_default_password";
constexpr const char* kSystemInfoLockPassword = "system_info_lock_password";
constexpr const char* kSystemInfoPasswordMinLen = "system_info_password_min_len";
constexpr const char* kSystemInfoPasswordMaxLen = "system_info_password_max_len";
constexpr const char* kSystemInfoPasswordRequireNumber =
    "system_info_password_require_number";
constexpr const char* kSystemInfoPasswordRequireLowerCase =
    "system_info_password_require_lower_case";
constexpr const char* kSystemInfoPasswordRequireUpperCase =
    "system_info_password_require_upper_case";
constexpr const char* kSystemInfoPasswordRequireSpecialChar =
    "system_info_password_require_special_const char*";
constexpr const char* kSystemInfoDefaultAvatar = "system_info_default_avatar";
constexpr const char* kSystemInfoDdeAvatarDir = "system_info_dde_avatar_dir";
constexpr const char* kSystemInfoDisableAvatarPage = "system_info_disable_avatar_page";

constexpr const char* kSystemInfoDefaultKeyboardLayout =
    "system_info_default_keyboard_layout";
constexpr const char* kSystemInfoDefaultKeyboardLayoutVariant =
    "system_info_default_keyboard_layout_variant";
constexpr const char* kSystemInfoDisableKeyboardPage =
    "system_info_disable_keyboard_page";

// Timezone
constexpr const char* kTimezoneDefault = "timezone_default";
constexpr const char* kTimezoneUseWindowsTime = "timezone_use_windows_time";
constexpr const char* kTimezoneUseGeoIp = "timezone_use_geoip";
constexpr const char* kTimezoneUseRegDomain = "timezone_use_regdomain";

// Partition
constexpr const char* kPartitionSkipFullDiskPartitionPage =
    "partition_skip_full_disk_partition_page";
constexpr const char* kPartitionSkipSimplePartitionPage =
    "partition_skip_simple_partition_page";
constexpr const char* kPartitionEnableSwapFile = "partition_enable_swap_file";
constexpr const char* kPartitionEnableSwapFileInAdvancedPage =
    "partition_enable_swap_file_in_advanced_page";
constexpr const char* kPartitionForceSwapFileInSimplePage =
    "partition_force_swap_file_in_simple_page";
constexpr const char* kPartitionMemoryThresholdForSwapArea =
    "partition_memory_threshold_for_swap_area";
constexpr const char* kPartitionSwapPartitionSize = "partition_swap_partition_size";
constexpr const char* kPartitionMinimumDiskSpaceRequired =
    "partition_minimum_disk_space_required";
constexpr const char* kPartitionRecommendedDiskSpace =
    "partition_recommended_disk_space";
constexpr const char* kPartitionDefaultBootSpace = "partition_default_boot_space";
constexpr const char* kPartitionDefaultEFISpace = "partition_default_efi_space";
constexpr const char* kPartitionEFIMinimumSpace = "partition_efi_minimum_space";
constexpr const char* kPartitionSupportedFs = "partition_supported_fs";
constexpr const char* kPartitionDefaultFs = "partition_default_fs";
constexpr const char* kPartitionDoAutoPart = "partition_do_auto_part";
constexpr const char* kPartitionMountPoints = "partition_mount_points";
constexpr const char* kPartitionFormattedMountPoints =
    "partition_formatted_mount_points";
constexpr const char* kPartitionBootOnFirstPartition =
    "partition_boot_on_first_partition";
constexpr const char* kPartitionPreferLogicalPartition =
    "partition_prefer_logical_partition";
constexpr const char* kPartitionBootPartitionFs = "partition_boot_partition_fs";
constexpr const char* kPartitionEnableOsProber = "partition_enable_os_prober";
constexpr const char* kPartitionHideInstallationDevice =
    "partition_hide_installation_device";

constexpr const char* kPartitionFullDiskLargeDiskThreshold =
    "partition_full_disk_large_disk_threshold";
constexpr const char* kPartitionFullDiskSmallLegacyPolicy =
    "partition_full_disk_small_legacy_policy";
constexpr const char* kPartitionFullDiskSmallUEFIPolicy =
    "partition_full_disk_small_uefi_policy";
constexpr const char* kPartitionFullDiskLargeLegacyPolicy =
    "partition_full_disk_large_legacy_policy";
constexpr const char* kPartitionFullDiskLargeUEFIPolicy =
    "partition_full_disk_large_uefi_policy";
constexpr const char* kPartitionFullDiskLargeRootPartRange =
    "partition_full_disk_large_root_part_range";

// Install progress page
constexpr const char* kInstallProgressPageDisableSlide =
    "install_progress_page_disable_slide";
constexpr const char* kInstallProgressPageDisableSlideAnimation =
    "install_progress_page_disable_slide_animation";
constexpr const char* kInstallProgressPageAnimationDuration =
    "install_progress_page_animation_duration";

// Install failed page
constexpr const char* kInstallFailedFeedbackServer = "install_failed_feedback_server";
constexpr const char* kInstallFailedQRErrMsgLen = "install_failed_qr_err_msg_len";
constexpr const char* kInstallFailedErrMsgLen = "install_failed_err_msg_len";

// Misc
constexpr const char* kScreenDefaultBrightness = "screen_default_brightness";

}  // namespace installer

#endif  // INSTALLER_SERVICE_SETTINGS_NAME_H
