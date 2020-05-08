file(GLOB HEADERS "*.hpp"
                  "*.h")

add_library(roxe
            roxelib.cpp
            crypto.cpp
            ${HEADERS})

add_library(roxe_malloc
            malloc.cpp
            ${HEADERS})

add_library(roxe_dsm
            simple_malloc.cpp
            ${HEADERS})

add_library(roxe_cmem
            memory.cpp
            ${HEADERS})

add_native_library(native_roxe
                   roxelib.cpp
                   crypto.cpp
                   malloc.cpp
                   ${HEADERS})

set_target_properties(roxe_malloc PROPERTIES LINKER_LANGUAGE C)

target_include_directories(roxe PUBLIC
                                 ${CMAKE_SOURCE_DIR}/libc/musl/include
                                 ${CMAKE_SOURCE_DIR}/libc/musl/src/internal
                                 ${CMAKE_SOURCE_DIR}/libc/musl/src/crypt
                                 ${CMAKE_SOURCE_DIR}/libc/musl/arch/roxe
                                 ${CMAKE_SOURCE_DIR}/libcxx/include
                                 ${CMAKE_SOURCE_DIR}
                                 ${CMAKE_SOURCE_DIR}/boost/include)

target_link_libraries( roxe c c++ )
add_dependencies( native_roxe roxe )

add_custom_command( TARGET roxe POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:roxe> ${BASE_BINARY_DIR}/lib )
add_custom_command( TARGET roxe_malloc POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:roxe_malloc> ${BASE_BINARY_DIR}/lib )
add_custom_command( TARGET roxe_dsm POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:roxe_dsm> ${BASE_BINARY_DIR}/lib )
add_custom_command( TARGET roxe_cmem POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:roxe_cmem> ${BASE_BINARY_DIR}/lib )
add_custom_command( TARGET native_roxe POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:native_roxe> ${BASE_BINARY_DIR}/lib )

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../roxelib DESTINATION ${BASE_BINARY_DIR}/include FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp")
