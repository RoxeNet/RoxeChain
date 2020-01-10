include(ExternalProject)
# if no cdt root is given use default path
if(ACTC_CDT_ROOT STREQUAL "" OR NOT ACTC_CDT_ROOT)
   find_package(actc.cdt)
endif()

ExternalProject_Add(
   multi_index_example_project
   SOURCE_DIR ${CMAKE_SOURCE_DIR}/src
   BINARY_DIR ${CMAKE_BINARY_DIR}/multi_index_example
   CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${ACTC_CDT_ROOT}/lib/cmake/actc.cdt/ActcWasmToolchain.cmake
   UPDATE_COMMAND ""
   PATCH_COMMAND ""
   TEST_COMMAND ""
   INSTALL_COMMAND ""
   BUILD_ALWAYS 1
)