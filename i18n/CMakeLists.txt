
# Generate .qm files from .ts files.
#file(GLOB INSTALLER_TRANSLATION_TS
#     ${CMAKE_SOURCE_DIR}/i18n/installer-*.ts)
#set_source_files_properties(${INSTALLER_TRANSLATION_TS}
#                            PROPERTIES OUTPUT_LOCATION ${CMAKE_BINARY_DIR}/i18n)
#qt5_add_translation(INSTALLER_TRANSLATION_QM ${INSTALLER_TRANSLATION_TS})
#add_custom_target(installer-qm-update DEPENDS ${INSTALLER_TRANSLATION_QM})
