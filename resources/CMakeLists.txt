
set(SOURCE_FILES
    icons/icons.h
    images/images.h
    misc/misc.h
    slide/slide.h
    styles/styles.h
    )

add_library(installer-resources STATIC
    ${SOURCE_FILES}
    )
set_target_properties(installer-resources
    PROPERTIES LINKER_LANGUAGE CXX
    )
target_include_directories(installer-resources
    PUBLIC ${CMAKE_SOURCE_DIR}
    )

install(
    FILES icons/blink-installer.desktop
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications
)

install(
    FILES icons/blink-installer.svg
    DESTINATION ${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/scalable/apps
)

# Install default_settings.ini based on current architecture.
install(FILES settings/default_settings_${CMAKE_SYSTEM_PROCESSOR}.ini
        DESTINATION ${INSTALLER_SHARE_DIR}/resources
        RENAME default_settings.ini
        )
