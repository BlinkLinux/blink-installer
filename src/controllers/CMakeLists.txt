
set(SOURCE_FILES
    main_controller.cpp
    main_controller.h
    shell.cpp
    shell.h
    )
add_library(installer-controllers STATIC
    ${SOURCE_FILES}
    )
target_link_libraries(installer-controllers
    Qt5::Widgets

    installer-config
    installer-sysinfo
    installer-ui
    )