add_contract(roxe.bios roxe.bios ${CMAKE_CURRENT_SOURCE_DIR}/src/roxe.bios.cpp)

target_include_directories(roxe.bios
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(roxe.bios
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/roxe.bios.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/roxe.bios.contracts.md @ONLY )

target_compile_options( roxe.bios PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
