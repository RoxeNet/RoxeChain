add_contract(actc.bios actc.bios ${CMAKE_CURRENT_SOURCE_DIR}/src/actc.bios.cpp)

target_include_directories(actc.bios
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(actc.bios
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/actc.bios.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/actc.bios.contracts.md @ONLY )

target_compile_options( actc.bios PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
