
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(DRESOURCES_DIR "${CMAKE_SOURCE_DIR}/resources")
else()
    set(RESOURCES_DIR "${INSTALLER_SHARE_DIR}/resources")
endif()

function(generate_config_file)
  set(INSTALLER_VERSION ${PROJECT_VERSION})

  execute_process(
      COMMAND git rev-parse --short HEAD
      OUTPUT_VARIABLE INSTALLER_BUILD_ID
      OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  message("INSTALLER_BUILD_ID: ${INSTALLER_BUILD_ID}")
  string(TIMESTAMP INSTALLER_BUILD_DATE "%Y%m%d")
  configure_file(config.h.in
      ${CMAKE_CURRENT_BINARY_DIR}/config.h
      @ONLY
      )
endfunction()

generate_config_file()

## Custom library
set(GENERATED_CONFIG_FILES
    ${CMAKE_CURRENT_BINARY_DIR}/config.h
    )

add_custom_command(OUTPUT ${GENERATED_CONFIG_FILES}
    DEPENDS config.h.in
    )

add_custom_target(installer-generate-config-files
    DEPENDS ${GENERATED_CONFIG_FILES}
    )

add_library(installer-config STATIC
    ${GENERATED_CONFIG_FILES}
    )
add_dependencies(installer-config
    installer-generate-config-files
    )
set_target_properties(installer-config
    PROPERTIES LINKER_LANGUAGE CXX
    )
target_include_directories(installer-config
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/..
    )
