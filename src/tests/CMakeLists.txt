
set(SOURCES
    qt_test_main.cpp
    )

if (BUILD_TESTING)
  find_package(GTest REQUIRED)
  add_library(installer-tests STATIC
      ${SOURCES}
      )
  target_link_libraries(installer-tests
      Qt5::Core
      Qt5::Gui
      Qt5::Widgets

      gtest
      -lpthread
      )
endif()
