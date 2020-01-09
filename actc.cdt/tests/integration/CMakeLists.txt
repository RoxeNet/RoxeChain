cmake_minimum_required( VERSION 3.5 )

set(ACTC_VERSION_MIN "1.4")
set(ACTC_VERSION_SOFT_MAX "1.4")
#set(ACTC_VERSION_HARD_MAX "")

find_package(actc)

### Check the version of actc
set(VERSION_MATCH_ERROR_MSG "")
ACTC_CHECK_VERSION(VERSION_OUTPUT "${ACTC_VERSION}"
                                   "${ACTC_VERSION_MIN}"
                                   "${ACTC_VERSION_SOFT_MAX}"
                                   "${ACTC_VERSION_HARD_MAX}"
                                   VERSION_MATCH_ERROR_MSG)
if(VERSION_OUTPUT STREQUAL "MATCH")
   message(STATUS "Using actc version ${ACTC_VERSION}")
elseif(VERSION_OUTPUT STREQUAL "WARN")
   message(WARNING "Using actc version ${ACTC_VERSION} even though it exceeds the maximum supported version of ${ACTC_VERSION_SOFT_MAX}; continuing with configuration, however build may fail.\nIt is recommended to use actc version ${ACTC_VERSION_SOFT_MAX}.x")
else() # INVALID OR MISMATCH
   message(FATAL_ERROR "Found actc version ${ACTC_VERSION} but it does not satisfy version requirements: ${VERSION_MATCH_ERROR_MSG}\nPlease use actc version ${ACTC_VERSION_SOFT_MAX}.x")
endif(VERSION_OUTPUT STREQUAL "MATCH")


enable_testing()

configure_file(${CMAKE_SOURCE_DIR}/contracts.hpp.in ${CMAKE_BINARY_DIR}/contracts.hpp)

include_directories(${CMAKE_BINARY_DIR})

file(GLOB INT_TESTS "*.cpp" "*.hpp")

add_actc_test( integration_tests ${INT_TESTS} )
