
set(SOURCE_FILES
    icons/icons.h
    misc/misc.h
    slide/slide.h
    )

add_library(installer-resources STATIC
    ${SOURCE_FILES}
    )
set_target_properties(installer-resources
    PROPERTIES LINKER_LANGUAGE CXX
    )

install(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/icons/blink-installer.desktop
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications
)

install(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/icons/blink-installer.svg
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/scalable/apps
)

# Install default_settings.ini based on current architecture.
set(INSTALLER_BUILD_ARCH "")
execute_process(COMMAND uname -m
                OUTPUT_VARIABLE INSTALLER_BUILD_ARCH)
message("build arch: ${INSTALLER_BUILD_ARCH}")

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/default_settings_${INSTALLER_BUILD_ARCH}.ini
        DESTINATION ${CMAKE_INSTALL_PREFIX}/share/blink-installer/resources
        RENAME default_settings.ini
        )
