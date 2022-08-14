
set(SOURCES
    qt_test_main.cpp
    )

if (BUILD_TESTING)
  find_package(GTest REQUIRED)
  add_library(installer-tests STATIC
      ${SOURCES}
      )
  target_link_libraries(installer-tests
      Qt${QT_VERSION_MAJOR}::Core
      Qt${QT_VERSION_MAJOR}::Gui
      Qt${QT_VERSION_MAJOR}::Widgets

      gtest
      -lpthread
      )
endif()
