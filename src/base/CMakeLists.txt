
set(SOURCE_FILES
    command.cpp
    command.h
    file_util.cpp
    file_util.h
    string_util.cpp
    string_util.h
    thread_util.cpp
    thread_util.h
    )

set(TEST_FILES
    command_test.cpp
    file_util_test.cpp
    string_util_test.cpp
    )

add_library(installer-base STATIC
    ${SOURCE_FILES}
    )
target_link_libraries(installer-base
    Qt5::Core
    )