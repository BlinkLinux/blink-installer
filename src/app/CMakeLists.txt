
set(RESOURCE_FILES
    ${CMAKE_SOURCE_DIR}/resources/icons/icons.qrc
    ${CMAKE_SOURCE_DIR}/resources/images/images.qrc
    ${CMAKE_SOURCE_DIR}/resources/misc/misc.qrc
    ${CMAKE_SOURCE_DIR}/resources/spinner/spinner.qrc
    ${CMAKE_SOURCE_DIR}/resources/styles/styles.qrc
    ${CMAKE_BINARY_DIR}/i18n/installer.qrc

    # Also include color-schemes used in qtermwidget.
    ../third_party/qtermwidget/lib/color-schemes/color-schemes.qrc
    ../third_party/qtermwidget/lib/kb-layouts/kb-layouts.qrc
    )

add_executable(blink-installer
    blink_installer.cpp
    ${RESOURCE_FILES}
    )
target_link_libraries(blink-installer
    Qt5::Widgets

    installer-controllers
    )

add_executable(blink-installer-settings
    blink_installer_settings.cpp
    )
target_link_libraries(blink-installer-settings
    Qt5::Core
    )

# Installation
install(TARGETS
        blink-installer
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        )
