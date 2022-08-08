
pkg_check_modules(X11 REQUIRED IMPORTED_TARGET x11)
pkg_check_modules(X11Ext REQUIRED IMPORTED_TARGET xext)
pkg_check_modules(X11Tst REQUIRED IMPORTED_TARGET xtst)
pkg_check_modules(X11RandR REQUIRED IMPORTED_TARGET xrandr)

set(SOURCE_FILES
    delegates/advanced_partition_animations.cpp
    delegates/advanced_partition_animations.h
    delegates/advanced_partition_delegate.cpp
    delegates/advanced_partition_delegate.h
    delegates/advanced_validate_state.h
    delegates/avatar_list_delegate.cpp
    delegates/avatar_list_delegate.h
    delegates/frameless_list_delegate.cpp
    delegates/frameless_list_delegate.h
    delegates/full_disk_delegate.cpp
    delegates/full_disk_delegate.h
    delegates/installer_args_parser.cpp
    delegates/installer_args_parser.h
    delegates/install_slide_frame_util.cpp
    delegates/install_slide_frame_util.h
    delegates/language_delegate.cpp
    delegates/language_delegate.h
    delegates/main_window_util.cpp
    delegates/main_window_util.h
    delegates/partition_util.cpp
    delegates/partition_util.h
    delegates/popup_menu_delegate.cpp
    delegates/popup_menu_delegate.h
    delegates/simple_partition_delegate.cpp
    delegates/simple_partition_delegate.h
    delegates/table_combo_box_delegate.cpp
    delegates/table_combo_box_delegate.h
    delegates/timezone_map_util.cpp
    delegates/timezone_map_util.h

    frames/consts.h
    frames/inner/advanced_partition_frame.cpp
    frames/inner/advanced_partition_frame.h
    frames/inner/edit_partition_frame.cpp
    frames/inner/edit_partition_frame.h
    frames/inner/full_disk_frame.cpp
    frames/inner/full_disk_frame.h
    frames/inner/install_progress_slide_frame.cpp
    frames/inner/install_progress_slide_frame.h
    frames/inner/new_partition_frame.cpp
    frames/inner/new_partition_frame.h
    frames/inner/new_table_loading_frame.cpp
    frames/inner/new_table_loading_frame.h
    frames/inner/new_table_warning_frame.cpp
    frames/inner/new_table_warning_frame.h
    frames/inner/partition_loading_frame.cpp
    frames/inner/partition_loading_frame.h
    frames/inner/partition_number_limitation_frame.cpp
    frames/inner/partition_number_limitation_frame.h
    frames/inner/partition_table_warning_frame.cpp
    frames/inner/partition_table_warning_frame.h
    frames/inner/prepare_install_frame.cpp
    frames/inner/prepare_install_frame.h
    frames/inner/select_bootloader_frame.cpp
    frames/inner/select_bootloader_frame.h
    frames/inner/simple_partition_frame.cpp
    frames/inner/simple_partition_frame.h
    frames/inner/system_info_avatar_frame.cpp
    frames/inner/system_info_avatar_frame.h
    frames/inner/system_info_form_frame.cpp
    frames/inner/system_info_form_frame.h
    frames/inner/system_info_keyboard_frame.cpp
    frames/inner/system_info_keyboard_frame.h
    frames/timezone_frame.cpp
    frames/timezone_frame.h

    frames/confirm_quit_frame.cpp
    frames/confirm_quit_frame.h
    frames/control_panel_frame.cpp
    frames/control_panel_frame.h
    frames/disk_space_insufficient_frame.cpp
    frames/disk_space_insufficient_frame.h
    frames/first_boot_loading_frame.cpp
    frames/first_boot_loading_frame.h
    frames/install_failed_frame.cpp
    frames/install_failed_frame.h
    frames/install_progress_frame.cpp
    frames/install_progress_frame.h
    frames/install_success_frame.cpp
    frames/install_success_frame.h
    frames/partition_frame.cpp
    frames/partition_frame.h
    frames/privilege_error_frame.cpp
    frames/privilege_error_frame.h
    frames/select_language_frame.cpp
    frames/select_language_frame.h
    frames/system_info_frame.cpp
    frames/system_info_frame.h
    frames/virtual_machine_frame.cpp
    frames/virtual_machine_frame.h

    models/bootloader_list_model.cpp
    models/bootloader_list_model.h
    models/fs_model.cpp
    models/fs_model.h
    models/keyboard_layout_model.cpp
    models/keyboard_layout_model.h
    models/keyboard_layout_variant_model.cpp
    models/keyboard_layout_variant_model.h
    models/language_list_model.cpp
    models/language_list_model.h
    models/mount_point_model.cpp
    models/mount_point_model.h
    models/partition_model.cpp
    models/partition_model.h
    models/partition_type_model.cpp
    models/partition_type_model.h

    utils/widget_util.cpp
    utils/widget_util.h
    utils/xutil.cpp
    utils/xutil.h

    views/frameless_list_view.cpp
    views/frameless_list_view.h
    views/pointer_list_view.cpp
    views/pointer_list_view.h

    widgets/advanced_partition_button.cpp
    widgets/advanced_partition_button.h
    widgets/advanced_partition_error_label.cpp
    widgets/advanced_partition_error_label.h
    widgets/avatar_button.cpp
    widgets/avatar_button.h
    widgets/comment_label.cpp
    widgets/comment_label.h
    widgets/device_model_label.cpp
    widgets/device_model_label.h
    widgets/expanded_nav_button.cpp
    widgets/expanded_nav_button.h
    widgets/flat_button.cpp
    widgets/flat_button.h
    widgets/icon_button.cpp
    widgets/icon_button.h
    widgets/line_edit.cpp
    widgets/line_edit.h
    widgets/nav_button.cpp
    widgets/nav_button.h
    widgets/page_indicator.cpp
    widgets/page_indicator.h
    widgets/partition_size_slider.cpp
    widgets/partition_size_slider.h
    widgets/pointer_button.cpp
    widgets/pointer_button.h
    widgets/popup_menu.cpp
    widgets/popup_menu.h
    widgets/qr_widget.cpp
    widgets/qr_widget.h
    widgets/rounded_progress_bar.cpp
    widgets/rounded_progress_bar.h
    widgets/simple_disk_button.cpp
    widgets/simple_disk_button.h
    widgets/simple_partition_button.cpp
    widgets/simple_partition_button.h
    widgets/spinner_label.cpp
    widgets/spinner_label.h
    widgets/system_info_tip.cpp
    widgets/system_info_tip.h
    widgets/table_combo_box.cpp
    widgets/table_combo_box.h
    widgets/timezone_map.cpp
    widgets/timezone_map.h
    widgets/title_label.cpp
    widgets/title_label.h
    widgets/tooltip_pin.cpp
    widgets/tooltip_pin.h
    widgets/wallpaper_item.cpp
    widgets/wallpaper_item.h

    xrandr/multi_head_manager.cpp
    xrandr/multi_head_manager.h
    xrandr/multi_head_worker.cpp
    xrandr/multi_head_worker.h
    xrandr/xrandr_wrapper.cpp
    xrandr/xrandr_wrapper.h

    images/images.qrc
    styles/styles.qrc

    # Required by SpinnerLabel.
    widgets/spinner/spinner.qrc

    main_window.cpp
    main_window.h
    )

set(TEST_FILES
    delegates/installer_args_parser_test.cpp
    delegates/install_slide_frame_util_test.cpp
    delegates/timezone_map_util_test.cpp
    )

set(LINK_LIBS
    Qt5::Widgets
    Qt5::X11Extras

    PkgConfig::X11
    PkgConfig::X11Ext
    PkgConfig::X11Tst
    PkgConfig::X11RandR

    global_shortcut
    qrencode
    qtermwidget5
    zlib_wrapper

    installer-partman
    installer-service
    installer-sysinfo
    )

add_library(installer-ui STATIC
    ${SOURCE_FILES}
    )
target_link_libraries(installer-ui
    ${LINK_LIBS}
    )