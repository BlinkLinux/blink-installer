
set(SOURCE_FILES
    fs.cpp
    fs.h
    shell.cpp
    shell.h
    )

add_executable(blink-installer-unsquashfs
    main.cpp
    ${SOURCE_FILES}
    )
target_link_libraries(blink-installer-unsquashfs
    Qt${QT_VERSION_MAJOR}::Core

    installer-base
    installer-config
    )

## Installation
install(TARGETS blink-installer-unsquashfs
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    )