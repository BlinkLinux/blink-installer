
set(RESOURCE_FILES
    ../../resources/images/images.qrc
    ../../resources/spinner/spinner.qrc
    ../../resources/styles/styles.qrc

    # Also include color-schems used in qtermwidget.
    ../third_party/qtermwidget/lib/color-schemes/color-schemes.qrc
    ../third_party/qtermwidget/lib/kb-layouts/kb-layouts.qrc
    )

add_executable(blink-installer
    blink_installer.cpp
    ${RESOURCE_FILES}
    )
target_link_libraries(blink-installer
    Qt5::Widgets

    installer-ui
    )

install(TARGETS
        blink-installer
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        )
