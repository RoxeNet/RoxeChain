add_contract(gls.token gls.token ${CMAKE_CURRENT_SOURCE_DIR}/src/gls.token.cpp)

target_include_directories(gls.token
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(gls.token
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/gls.token.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/gls.token.contracts.md @ONLY )

target_compile_options( gls.token PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
