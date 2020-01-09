file(GLOB HEADERS "*.hpp"
                  "*.h")

add_library(actc
            actclib.cpp
            crypto.cpp
            ${HEADERS})

add_library(actc_malloc
            malloc.cpp
            ${HEADERS})

add_library(actc_dsm
            simple_malloc.cpp
            ${HEADERS})

add_library(actc_cmem
            memory.cpp
            ${HEADERS})

add_native_library(native_actc
                   actclib.cpp
                   crypto.cpp
                   malloc.cpp
                   ${HEADERS})

set_target_properties(actc_malloc PROPERTIES LINKER_LANGUAGE C)

target_include_directories(actc PUBLIC
                                 ${CMAKE_SOURCE_DIR}/libc/musl/include
                                 ${CMAKE_SOURCE_DIR}/libc/musl/src/internal
                                 ${CMAKE_SOURCE_DIR}/libc/musl/src/crypt
                                 ${CMAKE_SOURCE_DIR}/libc/musl/arch/actc
                                 ${CMAKE_SOURCE_DIR}/libcxx/include
                                 ${CMAKE_SOURCE_DIR}
                                 ${CMAKE_SOURCE_DIR}/boost/include)

target_link_libraries( actc c c++ )
add_dependencies( native_actc actc )

add_custom_command( TARGET actc POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:actc> ${BASE_BINARY_DIR}/lib )
add_custom_command( TARGET actc_malloc POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:actc_malloc> ${BASE_BINARY_DIR}/lib )
add_custom_command( TARGET actc_dsm POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:actc_dsm> ${BASE_BINARY_DIR}/lib )
add_custom_command( TARGET actc_cmem POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:actc_cmem> ${BASE_BINARY_DIR}/lib )
add_custom_command( TARGET native_actc POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:native_actc> ${BASE_BINARY_DIR}/lib )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../actclib DESTINATION ${BASE_BINARY_DIR}/include FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
