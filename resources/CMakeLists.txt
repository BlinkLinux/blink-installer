
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

## Install default_settings.ini based on current architecture.
#set(INSTALLER_BUILD_ARCH "")
#execute_process(COMMAND uname -m
#                OUTPUT_VARIABLE INSTALLER_BUILD_ARCH)
#message("build arch: ${INSTALLER_BUILD_ARCH}")
#
#if (${INSTALLER_BUILD_ARCH} MATCHES "x86")
#  set(IS_PROFESSIONAL FALSE)
#  if (EXISTS "/etc/deepin-version")
#    file(STRINGS "/etc/deepin-version" IS_PROFESSIONAL REGEX "Type *= *Professional")
#  endif()
#  if (IS_PROFESSIONAL)
#    # Install professional settings.
#    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/professional_default_settings.ini
#            DESTINATION ${CMAKE_INSTALL_PREFIX}/share/deepin-installer/resources
#            RENAME default_settings.ini
#            )
#  else()
#    # Install default settings.
#    install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/default_settings.ini
#            DESTINATION ${CMAKE_INSTALL_PREFIX}/share/deepin-installer/resources
#            )
#  endif()
#elseif(${INSTALLER_BUILD_ARCH} MATCHES "sw")
#  install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/sw_default_settings.ini
#          DESTINATION  ${CMAKE_INSTALL_PREFIX}/share/deepin-installer/resources
#          RENAME default_settings.ini
#          )
#elseif(${INSTALLER_BUILD_ARCH} MATCHES "mips")
#  install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/loongson_default_settings.ini
#          DESTINATION  ${CMAKE_INSTALL_PREFIX}/share/deepin-installer/resources
#          RENAME default_settings.ini
#          )
#elseif (${INSTALLER_BUILD_ARCH} MATCHES "aarch64")
#  install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/arm_default_settings.ini
#          DESTINATION ${CMAKE_INSTALL_PREFIX}/share/deepin-installer/resources
#          RENAME default_settings.ini
#          )
#else()
#  message(FATAL_ERROR "Not supportted architecture: ${INSTALLER_BUILD_ARCH}")
#endif ()