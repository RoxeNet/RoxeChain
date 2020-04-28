add_contract(actc.msig actc.msig ${CMAKE_CURRENT_SOURCE_DIR}/src/actc.msig.cpp)

target_include_directories(actc.msig
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(actc.msig
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/actc.msig.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/actc.msig.contracts.md @ONLY )

target_compile_options( actc.msig PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
