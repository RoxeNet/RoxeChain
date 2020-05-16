project(multi_index_example)

set(ROXE_WASM_OLD_BEHAVIOR "Off")
find_package(roxe.cdt)

add_contract( multi_index_example multi_index_example multi_index_example.cpp )
target_include_directories( multi_index_example PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( multi_index_example ${CMAKE_SOURCE_DIR}/../ricardian )