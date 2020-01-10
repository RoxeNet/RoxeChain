configure_file(${CMAKE_CURRENT_SOURCE_DIR}/actc-cc.cpp.in ${CMAKE_BINARY_DIR}/actc-cc.cpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/actc-cpp.cpp.in ${CMAKE_BINARY_DIR}/actc-cpp.cpp)

add_tool(actc-cc)
add_tool(actc-cpp)
