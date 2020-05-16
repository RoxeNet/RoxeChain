add_contract(roxe.msig roxe.msig ${CMAKE_CURRENT_SOURCE_DIR}/src/roxe.msig.cpp)

target_include_directories(roxe.msig
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(roxe.msig
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/roxe.msig.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/roxe.msig.contracts.md @ONLY )

target_compile_options( roxe.msig PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
