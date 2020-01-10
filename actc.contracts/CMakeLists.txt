cmake_minimum_required(VERSION 3.5)

project(actc_contracts)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 8)
set(VERSION_PATCH 3)
#set(VERSION_SUFFIX develop)

if (VERSION_SUFFIX)
   set(VERSION_FULL "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}-${VERSION_SUFFIX}")
else()
   set(VERSION_FULL "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
endif()

include(ExternalProject)

find_package(actc.cdt)

message(STATUS "Building actc.contracts v${VERSION_FULL}")

set(ACTC_CDT_VERSION_MIN "1.0")
set(ACTC_CDT_VERSION_SOFT_MAX "1.0")
#set(ACTC_CDT_VERSION_HARD_MAX "")

### Check the version of actc.cdt
set(VERSION_MATCH_ERROR_MSG "")
ACTC_CHECK_VERSION(VERSION_OUTPUT "${ACTC_CDT_VERSION}"
                                   "${ACTC_CDT_VERSION_MIN}"
                                   "${ACTC_CDT_VERSION_SOFT_MAX}"
                                   "${ACTC_CDT_VERSION_HARD_MAX}"
                                   VERSION_MATCH_ERROR_MSG)
if(VERSION_OUTPUT STREQUAL "MATCH")
   message(STATUS "Using actc.cdt version ${ACTC_CDT_VERSION}")
elseif(VERSION_OUTPUT STREQUAL "WARN")
   message(WARNING "Using actc.cdt version ${ACTC_CDT_VERSION} even though it exceeds the maximum supported version of ${ACTC_CDT_VERSION_SOFT_MAX}; continuing with configuration, however build may fail.\nIt is recommended to use actc.cdt version ${ACTC_CDT_VERSION_SOFT_MAX}.x")
else() # INVALID OR MISMATCH
   message(FATAL_ERROR "Found actc.cdt version ${ACTC_CDT_VERSION} but it does not satisfy version requirements: ${VERSION_MATCH_ERROR_MSG}\nPlease use actc.cdt version ${ACTC_CDT_VERSION_SOFT_MAX}.x")
endif(VERSION_OUTPUT STREQUAL "MATCH")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
   set(TEST_BUILD_TYPE "Debug")
   set(CMAKE_BUILD_TYPE "Release")
else()
   set(TEST_BUILD_TYPE ${CMAKE_BUILD_TYPE})
endif()

ExternalProject_Add(
   contracts_project
   SOURCE_DIR ${CMAKE_SOURCE_DIR}/contracts
   BINARY_DIR ${CMAKE_BINARY_DIR}/contracts
   CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${ACTC_CDT_ROOT}/lib/cmake/actc.cdt/ActcWasmToolchain.cmake
   UPDATE_COMMAND ""
   PATCH_COMMAND ""
   TEST_COMMAND ""
   INSTALL_COMMAND ""
   BUILD_ALWAYS 1
)

if (APPLE)
   set(OPENSSL_ROOT "/usr/local/opt/openssl")
elseif (UNIX)
   set(OPENSSL_ROOT "/usr/include/openssl")
endif()
set(SECP256K1_ROOT "/usr/local")

if (APPLE)
   set(OPENSSL_ROOT "/usr/local/opt/openssl")
elseif (UNIX)
   set(OPENSSL_ROOT "/usr/include/openssl")
endif()
set(SECP256K1_ROOT "/usr/local")

string(REPLACE ";" "|" TEST_PREFIX_PATH "${CMAKE_PREFIX_PATH}")
string(REPLACE ";" "|" TEST_FRAMEWORK_PATH "${CMAKE_FRAMEWORK_PATH}")
string(REPLACE ";" "|" TEST_MODULE_PATH "${CMAKE_MODULE_PATH}")

set(BUILD_TESTS FALSE CACHE BOOL "Build unit tests")

if(BUILD_TESTS)
   message(STATUS "Building unit tests.")
   ExternalProject_Add(
     contracts_unit_tests
     LIST_SEPARATOR | # Use the alternate list separator
     CMAKE_ARGS -DCMAKE_BUILD_TYPE=${TEST_BUILD_TYPE} -DCMAKE_PREFIX_PATH=${TEST_PREFIX_PATH} -DCMAKE_FRAMEWORK_PATH=${TEST_FRAMEWORK_PATH} -DCMAKE_MODULE_PATH=${TEST_MODULE_PATH} -DACTC_ROOT=${ACTC_ROOT} -DLLVM_DIR=${LLVM_DIR} -DBOOST_ROOT=${BOOST_ROOT}
     SOURCE_DIR ${CMAKE_SOURCE_DIR}/tests
     BINARY_DIR ${CMAKE_BINARY_DIR}/tests
     BUILD_ALWAYS 1
     TEST_COMMAND   ""
     INSTALL_COMMAND ""
   )
else()
   message(STATUS "Unit tests will not be built. To build unit tests, set BUILD_TESTS to true.")
endif()
