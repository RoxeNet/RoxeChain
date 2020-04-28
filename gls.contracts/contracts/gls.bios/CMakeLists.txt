add_contract(gls.bios gls.bios ${CMAKE_CURRENT_SOURCE_DIR}/src/gls.bios.cpp)

target_include_directories(gls.bios
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(gls.bios
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/gls.bios.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/gls.bios.contracts.md @ONLY )

target_compile_options( gls.bios PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
