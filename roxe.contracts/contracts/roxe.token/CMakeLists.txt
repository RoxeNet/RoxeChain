add_contract(roxe.token roxe.token ${CMAKE_CURRENT_SOURCE_DIR}/src/roxe.token.cpp)

target_include_directories(roxe.token
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(roxe.token
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/roxe.token.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/roxe.token.contracts.md @ONLY )

target_compile_options( roxe.token PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
