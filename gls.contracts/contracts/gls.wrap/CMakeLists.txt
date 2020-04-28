add_contract(gls.wrap gls.wrap ${CMAKE_CURRENT_SOURCE_DIR}/src/gls.wrap.cpp)

target_include_directories(gls.wrap
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(gls.wrap
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/gls.wrap.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/gls.wrap.contracts.md @ONLY )

target_compile_options( gls.wrap PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
