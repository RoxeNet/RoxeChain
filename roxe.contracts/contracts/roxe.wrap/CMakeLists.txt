add_contract(roxe.wrap roxe.wrap ${CMAKE_CURRENT_SOURCE_DIR}/src/roxe.wrap.cpp)

target_include_directories(roxe.wrap
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(roxe.wrap
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/roxe.wrap.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/roxe.wrap.contracts.md @ONLY )

target_compile_options( roxe.wrap PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
