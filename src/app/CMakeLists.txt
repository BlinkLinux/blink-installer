
set(RESOURCE_FILES
    # Also include color-schems used in qtermwidget.
    ../third_party/qtermwidget/lib/color-schemes/color-schemes.qrc
    ../third_party/qtermwidget/lib/kb-layouts/kb-layouts.qrc
    )

add_executable(blink-installer
    blink_installer.cpp
    )
target_link_libraries(blink-installer
    Qt5::Widgets

    installer-ui
    )