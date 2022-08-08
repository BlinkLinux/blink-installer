cmake_minimum_required(VERSION 3.1)
project(blink-installer
    LANGUAGES C CXX
    VERSION 3.1.0
    )

# Import folders
add_subdirectory(data)
add_subdirectory(docs)
add_subdirectory(hooks)
add_subdirectory(resources)
add_subdirectory(src)
add_subdirectory(tools)
