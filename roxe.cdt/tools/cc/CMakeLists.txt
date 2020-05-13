configure_file(${CMAKE_CURRENT_SOURCE_DIR}/roxe-cc.cpp.in ${CMAKE_BINARY_DIR}/roxe-cc.cpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/roxe-cpp.cpp.in ${CMAKE_BINARY_DIR}/roxe-cpp.cpp)

add_tool(roxe-cc)
add_tool(roxe-cpp)
