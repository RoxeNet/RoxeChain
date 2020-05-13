add_contract(roxe.system roxe.system
   ${CMAKE_CURRENT_SOURCE_DIR}/src/roxe.system.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/delegate_bandwidth.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/exchange_state.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/native.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/producer_pay.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/rex.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/src/voting.cpp
)

target_include_directories(roxe.system
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include
   ${CMAKE_CURRENT_SOURCE_DIR}/../roxe.token/include)

set_target_properties(roxe.system
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

add_contract(rex.results rex.results ${CMAKE_CURRENT_SOURCE_DIR}/src/rex.results.cpp)

target_include_directories(rex.results
   PUBLIC
   ${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(rex.results
   PROPERTIES
   RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/.rex")

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/ricardian/roxe.system.contracts.md.in ${CMAKE_CURRENT_BINARY_DIR}/ricardian/roxe.system.contracts.md @ONLY )

target_compile_options( roxe.system PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )
