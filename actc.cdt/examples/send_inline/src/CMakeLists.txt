project(send_inline)

set(ACTC_WASM_OLD_BEHAVIOR "Off")
find_package(actc.cdt)

add_contract( send_inline send_inline send_inline.cpp )
target_include_directories( send_inline PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_include_directories( send_inline PUBLIC ${CMAKE_SOURCE_DIR}/../../hello/include )
target_ricardian_directory( send_inline ${CMAKE_SOURCE_DIR}/../ricardian )
