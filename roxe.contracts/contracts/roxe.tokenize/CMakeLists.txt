add_contract(roxe.tokenize roxe.tokenize ${CMAKE_CURRENT_SOURCE_DIR}/src/roxe.tokenize.cpp)

target_include_directories(roxe.tokenize
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(roxe.tokenize
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ricardian/roxe.tokenize.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/roxe.tokenize.contracts.md @ONLY )

target_compile_options( roxe.tokenize PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
