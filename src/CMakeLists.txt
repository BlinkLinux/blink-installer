
add_subdirectory(third_party)

if (CMAKE_BUILD_TYPE MATCHES Debug)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Werror -Wextra")
  # -fno-rtti, Disable real-time type information
  # -fno-exceptions Disable exceptions
  # -fsanitize=address Enable memory sanitize plugin
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Werror -Wextra -fno-exceptions")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-implicit-fallthrough")

  # Enable Qt builtin debug mode
  add_definitions("-DQT_MESSAGELOGCONTEXT")
else()
  # -Wl, -O2 Enable linker optimizations
  #-Wl, --gc-sections Remove unused code resulting from -fdsta-sections and -ffunction-sections
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O2 -Wl,-O1 -Wl,--gc-sections")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -Wl,-O1 -Wl,--gc-sections -Wno-unused-result")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set current directory as root of header files.
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Defines path to resource directories
if (CMAKE_BUILD_TYPE MATCHES Debug)
  add_definitions("-DBUILTIN_HOOKS_DIR=\"${CMAKE_SOURCE_DIR}/hooks\"")
  add_definitions("-DI18N_DIR=\"${CMAKE_BINARY_DIR}/i18n\"")
  add_definitions("-DRESOURCES_DIR=\"${CMAKE_SOURCE_DIR}/resources\"")
  add_definitions("-DTOOLS_DIR=\"${CMAKE_SOURCE_DIR}/tools\"")
else()
  add_definitions("-DN_DEBUG")
  add_definitions("-DBUILTIN_HOOKS_DIR=\"${INSTALLER_SHARE_DIR}/hooks\"")
  add_definitions("-DI18N_DIR=\"${INSTALLER_SHARE_DIR}/i18n\"")
  add_definitions("-DRESOURCES_DIR=\"${INSTALLER_SHARE_DIR}/resources\"")
  add_definitions("-DTOOLS_DIR=\"${INSTALLER_SHARE_DIR}/tools\"")
endif()

find_package(Qt5 5.12 COMPONENTS
    Network
    Widgets
    X11Extras
    Xml
    REQUIRED
    )

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(PkgConfig REQUIRED)
#pkg_check_modules(X11 REQUIRED IMPORTED_TARGET x11)
#pkg_check_modules(X11Ext REQUIRED IMPORTED_TARGET xext)
#pkg_check_modules(X11Tst REQUIRED IMPORTED_TARGET xtst)
#pkg_check_modules(X11RandR REQUIRED IMPORTED_TARGET xrandr)
#
#set(LINK_LIBS
#    Qt5::Gui
#    Qt5::Network
#    Qt5::Widgets
#    Qt5::X11Extras
#    Qt5::Xml
#
#    PkgConfig::Parted
#    PkgConfig::X11
#    PkgConfig::X11Ext
#    PkgConfig::X11Tst
#    PkgConfig::X11RandR
#
#    global_shortcut
#    qrencode
#    qtermwidget5
#    zlib_wrapper
#    )

set(INSTALLER_SHARE_DIR ${CMAKE_INSTALL_PREFIX}/share/blink-installer)

add_subdirectory(base)
add_subdirectory(partman)
add_subdirectory(service)
add_subdirectory(sysinfo)
add_subdirectory(ui)

# Set/get ini files.
#add_executable(deepin-installer-settings
#               app/deepin_installer_settings.cpp)
#
#target_link_libraries(deepin-installer-settings ${QtCore_LIBS})
#
#add_executable(deepin-installer-simpleini
#               app/deepin_installer_simpleini.cpp)
#
#target_link_libraries(deepin-installer-simpleini
#                      ${QtCore_LIBS}
#                      simpleini)
#
#
## Reboot setup
#add_executable(deepin-installer-first-boot
#               app/deepin_installer_first_boot.cpp
#               ui/first_boot_setup_window.cpp
#               ui/first_boot_setup_window.h
#
#               ${BASE_FILES}
#               ${PARTMAN_FILES}
#               ${SERVICE_FILES}
#               ${SYSINFO_FILES}
#               ${UI_FILES}
#               )
#target_link_libraries(deepin-installer-first-boot
#                      ${LINK_LIBS}
#                      global_shortcut
#                      )
#
#add_executable(deepin-installer-user-form
#               app/deepin_installer_user_form.cpp
#               ${BASE_FILES}
#
#               service/settings_manager.cpp
#               service/settings_manager.h
#               service/settings_name.h
#
#               sysinfo/keyboard.cpp
#               sysinfo/keyboard.h
#               sysinfo/users.cpp
#               sysinfo/users.h
#               sysinfo/validate_hostname.cpp
#               sysinfo/validate_hostname.h
#               sysinfo/validate_password.cpp
#               sysinfo/validate_password.h
#               sysinfo/validate_username.cpp
#               sysinfo/validate_username.h
#
#               ui/user_form_window.cpp
#               ui/user_form_window.h
#               ui/delegates/avatar_list_delegate.cpp
#               ui/delegates/avatar_list_delegate.h
#               ui/delegates/frameless_list_delegate.cpp
#               ui/delegates/frameless_list_delegate.h
#               ui/frames/system_info_frame.cpp
#               ui/frames/system_info_frame.h
#               ui/frames/inner/system_info_avatar_frame.cpp
#               ui/frames/inner/system_info_avatar_frame.h
#               ui/frames/inner/system_info_form_frame.cpp
#               ui/frames/inner/system_info_form_frame.h
#               ui/frames/inner/system_info_keyboard_frame.cpp
#               ui/frames/inner/system_info_keyboard_frame.h
#               ui/models/keyboard_layout_model.cpp
#               ui/models/keyboard_layout_model.h
#               ui/models/keyboard_layout_variant_model.cpp
#               ui/models/keyboard_layout_variant_model.h
#               ui/views/frameless_list_view.cpp
#               ui/views/frameless_list_view.h
#               ui/views/pointer_list_view.cpp
#               ui/views/pointer_list_view.h
#               ui/widgets/avatar_button.cpp
#               ui/widgets/avatar_button.h
#               ui/widgets/comment_label.cpp
#               ui/widgets/comment_label.h
#               ui/widgets/flat_button.cpp
#               ui/widgets/flat_button.h
#               ui/widgets/line_edit.cpp
#               ui/widgets/line_edit.h
#               ui/widgets/nav_button.cpp
#               ui/widgets/nav_button.h
#               ui/widgets/pointer_button.cpp
#               ui/widgets/pointer_button.h
#               ui/widgets/system_info_tip.cpp
#               ui/widgets/system_info_tip.h
#               ui/widgets/title_label.cpp
#               ui/widgets/title_label.h
#               ui/utils/widget_util.cpp
#               ui/utils/widget_util.h
#               ui/utils/xutil.cpp
#               ui/utils/xutil.h
#
#               ui/images/images.qrc
#               ui/styles/styles.qrc
#               )
#target_link_libraries(deepin-installer-user-form ${LINK_LIBS})
#
## deepin-installer-oem
#add_executable(deepin-installer-oem
#               app/deepin_installer_oem.cpp
#               oem/oem_window.cpp
#               oem/oem_window.h
#
#               service/settings_name.h
#               service/system_language.cpp
#               service/system_language.h
#
#               ${BASE_FILES}
#               ${OEM_FILES}
#               ${SYSINFO_FILES}
#               )
#target_link_libraries(deepin-installer-oem ${Qt_LIBS})
#
#add_executable(deepin-installer-unsquashfs
#
#               app/deepin_installer_unsquashfs.cpp
#               ${BASE_FILES}
#               )
#target_link_libraries(deepin-installer-unsquashfs ${Qt_LIBS})
#
## xrandr-switchy
#add_executable(deepin-installer-xrandr-switchy
#               ui/tests/xrandr_switchy.cpp
#
#               ${BASE_FILES}
#               ui/xrandr/xrandr_wrapper.cpp
#               ui/xrandr/xrandr_wrapper.h
#               )
#target_link_libraries(deepin-installer-xrandr-switchy
#                      ${QtCore_LIBS}
#
#                      ${X11_LIBRARIES}
#                      ${X11EXT_LIBRARIES}
#                      ${X11TST_LIBRARIES}
#                      ${X11RandR_LIBRARIES}
#                      )
#
## Unsquashfs progress
##add_executable(deepin-installer-unsquashfs-progress
##
##               app/unsquashfs_progress.cpp
##               ${BASE_FILES}
##               )
##target_link_libraries(deepin-installer-unsquashfs-progress ${QtCore_LIBS})
#
#
## test reboot system
#add_executable(reboot-system
#               app/reboot_system.cpp
#
#               ${BASE_FILES}
#               service/power_manager.cpp
#               service/power_manager.h
#               )
#target_link_libraries(reboot-system ${QtCore_LIBS})
#
## Combobox test
#add_executable(combobox-test
#               ui/tests/combobox_test.cpp
#
#               ${BASE_FILES}
#               ui/delegates/table_combo_box_delegate.cpp
#               ui/delegates/table_combo_box_delegate.h
#               ui/utils/widget_util.cpp
#               ui/utils/widget_util.h
#               ui/widgets/table_combo_box.cpp
#               ui/widgets/table_combo_box.h
#
#               ui/images/images.qrc
#               ui/styles/styles.qrc
#               )
#target_link_libraries(combobox-test ${Qt_LIBS})
#
#
## locale manager test
#add_executable(locale-manager-test
#               service/timezone_manager_test.cpp
#
#               ${BASE_FILES}
#
#               service/backend/wifi_inspect_worker.cpp
#               service/backend/wifi_inspect_worker.h
#               service/backend/geoip_request_worker.cpp
#               service/backend/geoip_request_worker.h
#               service/timezone_manager.cpp
#               service/timezone_manager.h
#
#               ${SYSINFO_FILES}
#               )
#target_link_libraries(locale-manager-test ${Qt_LIBS})
#
#
## QR widget test
#add_executable(qr-widget-test
#               ui/tests/qr_widget_test.cpp
#
#               base/file_util.cpp
#               base/file_util.h
#               third_party/zlib_wrapper/zip_util.cpp
#               third_party/zlib_wrapper/zip_util.h
#               ui/widgets/qr_widget.cpp
#               ui/widgets/qr_widget.h
#               )
#target_link_libraries(qr-widget-test
#                      ${Qt_LIBS}
#                      ${ZLib_LIBRARIES}
#
#                      qrencode
#                      )
#
## progress bar test
#add_executable(qprogressbar_test
#               ui/tests/progressbar_test.cpp
#               ui/widgets/rounded_progress_bar.cpp
#               ui/widgets/rounded_progress_bar.h
#               )
#target_link_libraries(qprogressbar_test ${Qt_LIBS})
#
## spinner test
#add_executable(spinner-test
#               ui/tests/spinner_test.cpp
#
#               ui/widgets/spinner_label.cpp
#               ui/widgets/spinner_label.h
#
#               ui/widgets/spinner/spinner.qrc
#               )
#target_link_libraries(spinner-test ${Qt_LIBS})
#
#
## system info tip test
#add_executable(system_info_tip_test
#               ui/tests/system_info_tip_test.cpp
#
#               ui/widgets/system_info_tip.cpp
#               ui/widgets/system_info_tip.h
#
#               ${BASE_FILES}
#               ui/images/images.qrc
#               ui/styles/styles.qrc
#               )
#target_link_libraries(system_info_tip_test ${Qt_LIBS})
#
## timezone frame test
#add_executable(timezone-frame-test
#               ui/tests/timezone_frame_test/timezone_frame_test.cpp
#
#               ${BASE_FILES}
#
#               service/settings_manager.cpp
#               service/settings_manager.h
#               service/settings_name.h
#               service/timezone_manager.cpp
#               service/timezone_manager.h
#               service/backend/geoip_request_worker.cpp
#               service/backend/geoip_request_worker.h
#               service/backend/wifi_inspect_worker.cpp
#               service/backend/wifi_inspect_worker.h
#
#               partman/os_prober.cpp
#               partman/os_prober.h
#               partman/structs.cpp
#               partman/structs.h
#
#               sysinfo/machine.cpp
#               sysinfo/machine.h
#               sysinfo/timezone.cpp
#               sysinfo/timezone.h
#               sysinfo/users.cpp
#               sysinfo/users.h
#
#               ui/delegates/popup_menu_delegate.cpp
#               ui/delegates/popup_menu_delegate.h
#               ui/delegates/timezone_map_util.cpp
#               ui/delegates/timezone_map_util.h
#               ui/frames/consts.h
#               ui/frames/timezone_frame.cpp
#               ui/frames/timezone_frame.h
#               ui/widgets/comment_label.cpp
#               ui/widgets/comment_label.h
#               ui/widgets/flat_button.cpp
#               ui/widgets/flat_button.h
#               ui/widgets/nav_button.cpp
#               ui/widgets/nav_button.h
#               ui/widgets/pointer_button.cpp
#               ui/widgets/pointer_button.h
#               ui/widgets/popup_menu.cpp
#               ui/widgets/popup_menu.h
#               ui/widgets/timezone_map.cpp
#               ui/widgets/timezone_map.h
#               ui/widgets/title_label.cpp
#               ui/widgets/title_label.h
#               ui/widgets/tooltip_pin.cpp
#               ui/widgets/tooltip_pin.h
#
#               ui/images/images.qrc
#               ui/styles/styles.qrc
#               )
#target_link_libraries(timezone-frame-test ${Qt_LIBS})
#
#add_executable(ctl-btn-test
#               ui/tests/ctl_btn_test.cpp
#
#               base/file_util.cpp
#               base/file_util.h
#               ui/widgets/pointer_button.cpp
#               ui/widgets/pointer_button.h
#
#               ui/images/images.qrc
#               ui/styles/styles.qrc
#               )
#target_link_libraries(ctl-btn-test ${Qt_LIBS})
#
#add_executable(partition-util-test
#               ui/tests/partition_util_test.cpp
#               )
#target_link_libraries(partition-util-test ${Qt_LIBS})
#
## Unittest
#add_executable(deepin-installer-tests
#               app/unittest_main.cpp
#
#               ${BASE_FILES}
#               ${PARTMAN_FILES}
#               ${SYSINFO_FILES}
#               ${UNITTEST_FILES}
#
#               service/settings_manager.cpp
#               service/settings_manager.h
#
#               ui/delegates/installer_args_parser.cpp
#               ui/delegates/installer_args_parser.h
#               ui/delegates/install_slide_frame_util.cpp
#               ui/delegates/install_slide_frame_util.h
#               ui/delegates/timezone_map_util.cpp
#               ui/delegates/timezone_map_util.h
#               )
#target_link_libraries(deepin-installer-tests
#                      ${LINK_LIBS}
#                      gtest
#                      )
#
## Unittest with root privilege
#add_executable(deepin-installer-root-tests
#               app/root_unittest_main.cpp
#
#               ${BASE_FILES}
#               ${PARTMAN_FILES}
#               ${SYSINFO_FILES}
#               ${ROOT_UNITTEST_FILES}
#               )
#target_link_libraries(deepin-installer-root-tests
#                      ${LINK_LIBS}
#                      gtest
#                      )
#
#
## Unsuqashfs progress window test
#add_definitions("-DUNSQUASHFS_SH=\"${CMAKE_CURRENT_SOURCE_DIR}/misc/unsquashfs_gui/unsquashfs.sh\"")
#add_executable(unsquashfs_gui
#
#               ui/tests/unsquashfs_gui/unsquashfs_gui.cpp
#               ui/tests/unsquashfs_gui/unsquashfs_progress_window.cpp
#               ui/tests/unsquashfs_gui/unsquashfs_progress_window.h
#
#               ${BASE_FILES}
#               ui/tests/unsquashfs_gui/worker.cpp
#               ui/tests/unsquashfs_gui/worker.h
#               )
#target_link_libraries(unsquashfs_gui ${Qt_LIBS})
#
#
### Installation
#install(PROGRAMS
#        ${CMAKE_CURRENT_SOURCE_DIR}/app/deepin-installer-auto-install
#        ${CMAKE_CURRENT_SOURCE_DIR}/app/deepin-installer-first-boot-pkexec
#        ${CMAKE_CURRENT_SOURCE_DIR}/app/deepin-installer-pkexec
#        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
#        )
#
#install(TARGETS
#        deepin-installer
#        deepin-installer-first-boot
#        deepin-installer-oem
#        deepin-installer-settings
#        deepin-installer-simpleini
#        deepin-installer-unsquashfs
#        deepin-installer-user-form
#        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
#        )
#
#install(
#    DIRECTORY ${CMAKE_BINARY_DIR}/i18n
#    DESTINATION ${INSTALLER_SHARE_DIR}
#    FILES_MATCHING PATTERN "*"
#)
