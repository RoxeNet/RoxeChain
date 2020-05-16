# will be implictly used for any compilation unit if not overrided by SYSTEM_INCLUDE_FOLDERS parameter
# these directories go as -isystem <dir> to avoid warnings from code of third-party libraries

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/roxe.bios/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/roxe.bios/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/roxe.msig/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/roxe.msig/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/roxe.system/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/roxe.system/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/roxe.token/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/roxe.token/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/roxe.wrap/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/roxe.wrap/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/old_versions/v1.6.0-rc3/roxe.bios/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/old_versions/v1.6.0-rc3/roxe.bios/)
