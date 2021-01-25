file(GLOB HEADERS "include/roxe/cross_plugin/*.hpp")
add_library( http_plugin
        cross_plugin.cpp
             ${HEADERS} )

target_link_libraries( cross_plugin roxe_chain appbase fc )
target_include_directories( cross_plugin PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )
