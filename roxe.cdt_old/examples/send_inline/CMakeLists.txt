include(ExternalProject)
# if no cdt root is given use default path
if(ROXE_CDT_ROOT STREQUAL "" OR NOT ROXE_CDT_ROOT)
   find_package(roxe.cdt)
endif()

ExternalProject_Add(
   send_inline_project
   SOURCE_DIR ${CMAKE_SOURCE_DIR}/src
   BINARY_DIR ${CMAKE_BINARY_DIR}/send_inline
   CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${ROXE_CDT_ROOT}/lib/cmake/roxe.cdt/RoxeWasmToolchain.cmake
   UPDATE_COMMAND ""
   PATCH_COMMAND ""
   TEST_COMMAND ""
   INSTALL_COMMAND ""
   BUILD_ALWAYS 1
)