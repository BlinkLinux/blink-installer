
set(RESOURCE_FILES
    ${CMAKE_SOURCE_DIR}/resources/icons/icons.qrc
    ${CMAKE_SOURCE_DIR}/resources/images/images.qrc
    ${CMAKE_SOURCE_DIR}/resources/misc/misc.qrc
    ${CMAKE_SOURCE_DIR}/resources/slide/slide.qrc
    ${CMAKE_SOURCE_DIR}/resources/spinner/spinner.qrc
    ${CMAKE_SOURCE_DIR}/resources/styles/styles.qrc
    ${CMAKE_BINARY_DIR}/i18n/installer.qrc
    )

add_executable(blink-installer
    blink_installer.cpp
    ${RESOURCE_FILES}
    )
target_link_libraries(blink-installer
    Qt${QT_VERSION_MAJOR}::Widgets

    installer-controllers
    )

add_executable(blink-installer-settings
    blink_installer_settings.cpp
    )
target_link_libraries(blink-installer-settings
    Qt${QT_VERSION_MAJOR}::Core
    )

if (BUILD_TESTING)
  add_executable(installer-combobox-test
      combobox_test.cpp
      )
  target_link_libraries(installer-combobox-test
      installer-resources
      installer-ui
      )
  add_executable(installer-control-button-test
      control_button_test.cpp
      ${RESOURCE_FILES}
      )
  target_link_libraries(installer-control-button-test
      installer-ui
      )

  add_executable(installer-progress-bar-test
      progressbar_test.cpp
      )
  target_link_libraries(installer-progress-bar-test
      installer-ui
      )

  add_executable(installer-qr-widget-test
      qr_widget_test.cpp
      )
  target_link_libraries(installer-qr-widget-test
      installer-ui
      )

  add_executable(installer-spinner-test
      spinner_test.cpp
      ${RESOURCE_FILES}
      )
  target_link_libraries(installer-spinner-test
      installer-ui
      )

  add_executable(installer-timezone-frame-test
      timezone_frame_test.cpp
      )
  target_link_libraries(installer-timezone-frame-test
      installer-ui
      )
endif()

# Installation
install(TARGETS
        blink-installer
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        )
