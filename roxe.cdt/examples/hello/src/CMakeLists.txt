project(hello)

set(ROXE_WASM_OLD_BEHAVIOR "Off")
find_package(roxe.cdt)

add_contract( hello hello hello.cpp )
target_include_directories( hello PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( hello ${CMAKE_SOURCE_DIR}/../ricardian )
