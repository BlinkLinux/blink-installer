
set(SOURCE_FILES
    dev_disk.cpp
    dev_disk.h
    iso3166.cpp
    iso3166.h
    keyboard.cpp
    keyboard.h
    machine.cpp
    machine.h
    proc_meminfo.cpp
    proc_meminfo.h
    proc_mounts.cpp
    proc_mounts.h
    proc_partitions.cpp
    proc_partitions.h
    proc_swaps.cpp
    proc_swaps.h
    release_version.cpp
    release_version.h
    timezone.cpp
    timezone.h
    users.cpp
    users.h
    validate_hostname.cpp
    validate_hostname.h
    validate_password.cpp
    validate_password.h
    validate_username.cpp
    validate_username.h
    virtual_machine.cpp
    virtual_machine.h
    )

set(TEST_FILES
    dev_disk_test.cpp
    iso3166_test.cpp
    keyboard_test.cpp
    proc_meminfo_test.cpp
    proc_mounts_test.cpp
    proc_partitions_test.cpp
    proc_swaps_test.cpp
    timezone_test.cpp
    users_test.cpp
    validate_hostname_test.cpp
    validate_password_test.cpp
    validate_username_test.cpp
    )

add_library(installer-sysinfo STATIC
    ${SOURCE_FILES}
    )
target_link_libraries(installer-sysinfo
    Qt5::Core
    Qt5::Xml

    installer-base
    )