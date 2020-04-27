# will be implictly used for any compilation unit if not overrided by SYSTEM_INCLUDE_FOLDERS parameter
# these directories go as -isystem <dir> to avoid warnings from code of third-party libraries

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/actc.bios/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/actc.bios/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/actc.msig/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/actc.msig/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/actc.system/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/actc.system/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/actc.token/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/actc.token/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/actc.wrap/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/actc.wrap/)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/old_versions/v1.6.0-rc3/actc.bios/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/old_versions/v1.6.0-rc3/actc.bios/)
