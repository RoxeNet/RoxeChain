add_contract(actc.wrap actc.wrap ${CMAKE_CURRENT_SOURCE_DIR}/src/actc.wrap.cpp)

target_include_directories(actc.wrap
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(actc.wrap
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/actc.wrap.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/actc.wrap.contracts.md @ONLY )

target_compile_options( actc.wrap PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
