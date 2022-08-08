
set(RESOURCE_FILES
    # Also include color-schems used in qtermwidget.
    ../third_party/qtermwidget/lib/color-schemes/color-schemes.qrc
    ../third_party/qtermwidget/lib/kb-layouts/kb-layouts.qrc
    )

add_executable(blink-installer
    deepin_installer.cpp
    )
target_link_libraries(blink-installer
    installer-controllers
    )