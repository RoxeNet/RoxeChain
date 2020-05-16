cmake_minimum_required( VERSION 3.5 )

set(ROXE_VERSION_MIN "1.4")
set(ROXE_VERSION_SOFT_MAX "1.4")
#set(ROXE_VERSION_HARD_MAX "")

find_package(roxe)

### Check the version of roxe
set(VERSION_MATCH_ERROR_MSG "")
ROXE_CHECK_VERSION(VERSION_OUTPUT "${ROXE_VERSION}"
                                   "${ROXE_VERSION_MIN}"
                                   "${ROXE_VERSION_SOFT_MAX}"
                                   "${ROXE_VERSION_HARD_MAX}"
                                   VERSION_MATCH_ERROR_MSG)
if(VERSION_OUTPUT STREQUAL "MATCH")
   message(STATUS "Using roxe version ${ROXE_VERSION}")
elseif(VERSION_OUTPUT STREQUAL "WARN")
   message(WARNING "Using roxe version ${ROXE_VERSION} even though it exceeds the maximum supported version of ${ROXE_VERSION_SOFT_MAX}; continuing with configuration, however build may fail.\nIt is recommended to use roxe version ${ROXE_VERSION_SOFT_MAX}.x")
else() # INVALID OR MISMATCH
   message(FATAL_ERROR "Found roxe version ${ROXE_VERSION} but it does not satisfy version requirements: ${VERSION_MATCH_ERROR_MSG}\nPlease use roxe version ${ROXE_VERSION_SOFT_MAX}.x")
endif(VERSION_OUTPUT STREQUAL "MATCH")


enable_testing()

configure_file(${CMAKE_SOURCE_DIR}/contracts.hpp.in ${CMAKE_BINARY_DIR}/contracts.hpp)

include_directories(${CMAKE_BINARY_DIR})

file(GLOB INT_TESTS "*.cpp" "*.hpp")

add_roxe_test( integration_tests ${INT_TESTS} )
