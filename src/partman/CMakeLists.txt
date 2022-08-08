
set(SOURCE_FILES
    device.cpp
    device.h
    fs.cpp
    fs.h
    libparted_util.cpp
    libparted_util.h
    operation.cpp
    operation.h
    os_prober.cpp
    os_prober.h
    partition.cpp
    partition.h
    partition_format.cpp
    partition_format.h
    partition_manager.cpp
    partition_manager.h
    partition_usage.cpp
    partition_usage.h
    structs.cpp
    structs.h
    utils.cpp
    utils.h
    )

set(TEST_FILES
    libparted_util_test.cpp
    operation_test.cpp
    os_prober_test.cpp
    partition_manager_test.cpp
    partition_test.cpp
    partition_usage_test.cpp
)

add_library(installer-partman STATIC
    ${SOURCE_FILES}
    )
target_link_libraries(installer-partman
    Qt5::Core
    )
