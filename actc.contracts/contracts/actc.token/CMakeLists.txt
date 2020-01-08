add_contract(actc.token actc.token ${CMAKE_CURRENT_SOURCE_DIR}/src/actc.token.cpp)

target_include_directories(actc.token
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(actc.token
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/actc.token.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/actc.token.contracts.md @ONLY )

target_compile_options( actc.token PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
