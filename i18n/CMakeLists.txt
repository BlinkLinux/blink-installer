
find_package(Qt5LinguistTools REQUIRED)

# Generate .qm files from .ts files.
file(GLOB TS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/installer*.ts)
qt5_add_translation(QM_FILES ${TS_FILES})
add_custom_target(installer-generate-qm-files DEPENDS ${QM_FILES})

set(I18N_RESOURCES "")
foreach (qm_file ${QM_FILES})
  get_filename_component(qm_file_alias ${qm_file} NAME)
  set(I18N_RESOURCES "${I18N_RESOURCES}\n    <file alias=\"${qm_file_alias}\">${qm_file}</file>")
endforeach ()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/installer.qrc.in
    ${CMAKE_CURRENT_BINARY_DIR}/installer.qrc
    @ONLY)
