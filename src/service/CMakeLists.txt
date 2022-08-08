
set(SOURCE_FILES
    backend/chroot.cpp
    backend/chroot.h
    backend/geoip_request_worker.cpp
    backend/geoip_request_worker.h
    backend/hooks_pack.cpp
    backend/hooks_pack.h
    backend/hook_worker.cpp
    backend/hook_worker.h
    backend/wifi_inspect_worker.cpp
    backend/wifi_inspect_worker.h

    first_boot_hook_worker.cpp
    first_boot_hook_worker.h
    hooks_manager.cpp
    hooks_manager.h
    log_manager.cpp
    log_manager.h
    power_manager.cpp
    power_manager.h
    process_util.cpp
    process_util.h
    screen_brightness.cpp
    screen_brightness.h
    settings_manager.cpp
    settings_manager.h
    system_language.cpp
    system_language.h
    settings_name.h
    timezone_manager.cpp
    timezone_manager.h
    )

add_library(installer-service STATIC
    ${SOURCE_FILES}
    )
target_link_libraries(installer-service
    Qt5::Core
    )