add_contract(gls.msig gls.msig ${CMAKE_CURRENT_SOURCE_DIR}/src/gls.msig.cpp)

target_include_directories(gls.msig
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(gls.msig
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/gls.msig.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/gls.msig.contracts.md @ONLY )

target_compile_options( gls.msig PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
