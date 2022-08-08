CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0)

PROJECT(GlobalShortcut)

find_package(Qt5Core REQUIRED)
find_package(Qt5X11Extras REQUIRED)
find_package(PkgConfig REQUIRED)

set(CMAKE_AUTOMOC ON)

pkg_check_modules(X11 REQUIRED IMPORTED_TARGET x11)
pkg_check_modules(X11Ext REQUIRED IMPORTED_TARGET xext)

SET(LIB_FILES
    global_shortcut.cpp
    global_shortcut.h
    keyboard_event_filter.cpp
    keyboard_event_filter.h
    )

set(LINK_LIBS
    Qt5::Core
    Qt5::X11Extras
    PkgConfig::X11
    PkgConfig::X11Ext
    )

ADD_LIBRARY(global-shortcut STATIC ${LIB_FILES})
target_link_libraries(global-shortcut ${LINK_LIBS})