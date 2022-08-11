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
constexpr char kSkipDiskSpaceInsufficientPage[] =
    "skip_disk_space_insufficient_page";
constexpr char kSkipVirtualMachinePage[] = "skip_virtual_machine_page";
constexpr char kSkipSelectLanguagePage[] = "skip_select_language_page";
constexpr char kSkipSystemInfoPage[] = "skip_system_info_page";
constexpr char kSkipTimezonePage[] = "skip_timezone_page";
constexpr char kSkipPartitionPage[] = "skip_partition_page";

// System Language List
constexpr char kSelectLanguageDefaultLocale[] = "select_language_default_locale";

// System Info
constexpr char kSystemInfoDeepinVersion[] = "system_info_deepin_version";
constexpr char kSystemInfoLsbRelease[] = "system_info_lsb_release";
constexpr char kSystemInfoVendorName[] = "system_info_vendor_name";
constexpr char kSystemInfoSetupAfterReboot[] = "system_info_setup_after_reboot";
constexpr char kSystemInfoDefaultUsername[] = "system_info_default_username";
constexpr char kSystemInfoLockUsername[] = "system_info_lock_username";
constexpr char kSystemInfoUsernameMinLen[] = "system_info_username_min_len";
constexpr char kSystemInfoUsernameMaxLen[] = "system_info_username_max_len";
constexpr char kSystemInfoDefaultHostname[] = "system_info_default_hostname";
constexpr char kSystemInfoLockHostname[] = "system_info_lock_hostname";
constexpr char kSystemInfoHostnameAutoSuffix[] = "system_info_hostname_auto_suffix";
constexpr char kSystemInfoHostnameReserved[] = "system_info_hostname_reserved";
constexpr char kSystemInfoDefaultPassword[] = "system_info_default_password";
constexpr char kSystemInfoLockPassword[] = "system_info_lock_password";
constexpr char kSystemInfoPasswordMinLen[] = "system_info_password_min_len";
constexpr char kSystemInfoPasswordMaxLen[] = "system_info_password_max_len";
constexpr char kSystemInfoPasswordRequireNumber[] =
    "system_info_password_require_number";
constexpr char kSystemInfoPasswordRequireLowerCase[] =
    "system_info_password_require_lower_case";
constexpr char kSystemInfoPasswordRequireUpperCase[] =
    "system_info_password_require_upper_case";
constexpr char kSystemInfoPasswordRequireSpecialChar[] =
    "system_info_password_require_special_char";
constexpr char kSystemInfoDefaultAvator[] = "system_info_default_avatar";
constexpr char kSystemInfoDdeAvatarDir[] = "system_info_dde_avatar_dir";
constexpr char kSystemInfoDisableAvatorPage[] = "system_info_disable_avatar_page";

constexpr char kSystemInfoDefaultKeyboardLayout[] =
    "system_info_default_keyboard_layout";
constexpr char kSystemInfoDefaultKeyboardLayoutVariant[] =
    "system_info_default_keyboard_layout_variant";
constexpr char kSystemInfoDisableKeyboardPage[] =
    "system_info_disable_keyboard_page";

// Timezone
constexpr char kTimezoneDefault[] = "timezone_default";
constexpr char kTimezoneUseWindowsTime[] = "timezone_use_windows_time";
constexpr char kTimezoneUseGeoIp[] = "timezone_use_geoip";
constexpr char kTimezoneUseRegdomain[] = "timezone_use_regdomain";

// Partition
constexpr char kPartitionSkipFullDiskPartitionPage[] =
    "partition_skip_full_disk_partition_page";
constexpr char kPartitionSkipSimplePartitionPage[] =
    "partition_skip_simple_partition_page";
constexpr char kPartitionEnableSwapFile[] = "partition_enable_swap_file";
constexpr char kPartitionEnableSwapFileInAdvancedPage[] =
    "partition_enable_swap_file_in_advanced_page";
constexpr char kPartitionForceSwapFileInSimplePage[] =
    "partition_force_swap_file_in_simple_page";
constexpr char kPartitionMemoryThresholdForSwapArea[] =
    "partition_memory_threshold_for_swap_area";
constexpr char kPartitionSwapPartitionSize[] = "partition_swap_partition_size";
constexpr char kPartitionMinimumDiskSpaceRequired[] =
    "partition_minimum_disk_space_required";
constexpr char kPartitionRecommendedDiskSpace[] =
    "partition_recommended_disk_space";
constexpr char kPartitionDefaultBootSpace[] = "partition_default_boot_space";
constexpr char kPartitionDefaultEFISpace[] = "partition_default_efi_space";
constexpr char kPartitionEFIMinimumSpace[] = "partition_efi_minimum_space";
constexpr char kPartitionSupportedFs[] = "partition_supported_fs";
constexpr char kPartitionDefaultFs[] = "partition_default_fs";
constexpr char kPartitionDoAutoPart[] = "partition_do_auto_part";
constexpr char kPartitionMountPoints[] = "partition_mount_points";
constexpr char kPartitionFormattedMountPoints[] =
    "partition_formatted_mount_points";
constexpr char kPartitionBootOnFirstPartition[] =
    "partition_boot_on_first_partition";
constexpr char kPartitionPreferLogicalPartition[] =
    "partition_prefer_logical_partition";
constexpr char kPartitionBootPartitionFs[] = "partition_boot_partition_fs";
constexpr char kPartitionEnableOsProber[] = "partition_enable_os_prober";
constexpr char kPartitionHideInstallationDevice[] =
    "partition_hide_installation_device";

constexpr char kPartitionFullDiskLargeDiskThreshold[] =
    "partition_full_disk_large_disk_threshold";
constexpr char kPartitionFullDiskSmallLegacyPolicy[] =
    "partition_full_disk_small_legacy_policy";
constexpr char kPartitionFullDiskSmallUEFIPolicy[] =
    "partition_full_disk_small_uefi_policy";
constexpr char kPartitionFullDiskLargeLegacyPolicy[] =
    "partition_full_disk_large_legacy_policy";
constexpr char kPartitionFullDiskLargeUEFIPolicy[] =
    "partition_full_disk_large_uefi_policy";
constexpr char kPartitionFullDiskLargeRootPartRange[] =
    "partition_full_disk_large_root_part_range";

// Install progress page
constexpr char kInstallProgressPageDisableSlide[] =
    "install_progress_page_disable_slide";
constexpr char kInstallProgressPageDisableSlideAnimation[] =
    "install_progress_page_disable_slide_animation";
constexpr char kInstallProgressPageAnimationDuration[] =
    "install_progress_page_animation_duration";

// Install failed page
constexpr char kInstallFailedFeedbackServer[] = "install_failed_feedback_server";
constexpr char kInstallFailedQRErrMsgLen[] = "install_failed_qr_err_msg_len";
constexpr char kInstallFailedErrMsgLen[] = "install_failed_err_msg_len";

// Misc
constexpr char kScreenDefaultBrightness[] = "screen_default_brightness";

}  // namespace installer

#endif  // INSTALLER_SERVICE_SETTINGS_NAME_H
