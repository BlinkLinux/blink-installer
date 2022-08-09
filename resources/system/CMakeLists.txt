install(
    FILES deepin-installer.conf
    DESTINATION /etc/live/config.conf.d/
)

install(
    DIRECTORY live-boot
    DESTINATION /lib/live/boot
    FILES_MATCHING PATTERN "*"
    PERMISSIONS OWNER_READ OWNER_EXECUTE
                GROUP_READ GROUP_EXECUTE
                WORLD_READ WORLD_EXECUTE
)

install(
    FILES lightdm-installer-greeter.desktop
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/xgreeters/
)

option(USE_SYSTEMD "bootup as a systemd service" FALSE)
message("USE_SYSTEMD: ${USE_SYSTEMD}")
if (USE_SYSTEMD)
    install(
        DIRECTORY systemd
        DESTINATION /lib/systemd/system
        FILES_MATCHING PATTERN "*"
    )
else()
    install(
        DIRECTORY live-config
        DESTINATION /lib/live/config
        FILES_MATCHING PATTERN "*"
        PERMISSIONS OWNER_READ OWNER_EXECUTE
                    GROUP_READ GROUP_EXECUTE
                    WORLD_READ WORLD_EXECUTE
    )
endif()

# Install PolicyKit file.
install(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/com.deepin.pkexec.installer.policy
    ${CMAKE_CURRENT_SOURCE_DIR}/com.deepin.pkexec.installer-first-boot.policy
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/polkit-1/actions/
)
