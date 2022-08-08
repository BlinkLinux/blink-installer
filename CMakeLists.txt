cmake_minimum_required(VERSION 3.1)
project(blink-installer
    LANGUAGES C CXX
    VERSION 3.1.0
    )

# Only generate Debug and Release configuration types.
set(CMAKE_CONFIGURATION_TYPES Debug Release)
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Generate compile_commands.json project file.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (BUILD_TESTING)
  # Enable CTest
  enable_testing()
endif ()

add_custom_target(installer-generate-deps
    COMMAND mkdir -pv ${CMAKE_BINARY_DIR}/deps
    COMMAND cmake --graphviz=deps/deps.dot ..
    COMMAND dot -Tsvg -o deps/deps.svg deps/deps.dot
    COMMAND setsid xdg-open deps/deps.svg
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

# Import folders
add_subdirectory(docs)
add_subdirectory(hooks)
add_subdirectory(i18n)
add_subdirectory(resources)
add_subdirectory(src)
add_subdirectory(tools)
