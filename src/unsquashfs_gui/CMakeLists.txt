
set(SOURCE_FILES
    progress_window.cpp
    progress_window.h
    worker.cpp
    worker.h
    )

add_executable(blink-installer-unsquashfs
    unsquashfs_gui.cpp
    ${SOURCE_FILES}
    )
target_link_libraries(blink-installer-unsquashfs
    Qt5::Widgets

    installer-base
    )