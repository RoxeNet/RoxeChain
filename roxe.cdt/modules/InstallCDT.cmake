add_custom_command( TARGET RoxeClang POST_BUILD COMMAND mkdir -p ${CMAKE_BINARY_DIR}/bin )
macro( roxe_clang_install file )
   set(BINARY_DIR ${CMAKE_BINARY_DIR}/roxe_llvm/bin)
   add_custom_command( TARGET RoxeClang POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${BINARY_DIR}/${file} ${CMAKE_BINARY_DIR}/bin/ )
   install(FILES ${BINARY_DIR}/${file}
      DESTINATION ${CDT_INSTALL_PREFIX}/bin
      PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
endmacro( roxe_clang_install )

macro( roxe_clang_install_and_symlink file symlink )
   set(BINARY_DIR ${CMAKE_BINARY_DIR}/roxe_llvm/bin)
   add_custom_command( TARGET RoxeClang POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${BINARY_DIR}/${file} ${CMAKE_BINARY_DIR}/bin/ )
   add_custom_command( TARGET RoxeClang POST_BUILD COMMAND cd ${CMAKE_BINARY_DIR}/bin && ln -sf ${file} ${symlink} )
   install(FILES ${BINARY_DIR}/${file}
      DESTINATION ${CDT_INSTALL_PREFIX}/bin
      PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
   install(CODE "execute_process( COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_INSTALL_PREFIX}/bin)")
   install(CODE "execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink ${CDT_INSTALL_PREFIX}/bin/${file} ${CMAKE_INSTALL_PREFIX}/bin/${symlink})")
endmacro( roxe_clang_install_and_symlink )

macro( roxe_tool_install file )
   set(BINARY_DIR ${CMAKE_BINARY_DIR}/tools/bin)
   add_custom_command( TARGET RoxeTools POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${BINARY_DIR}/${file} ${CMAKE_BINARY_DIR}/bin/ )
   install(FILES ${BINARY_DIR}/${file}
      DESTINATION ${CDT_INSTALL_PREFIX}/bin
      PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
endmacro( roxe_tool_install )

macro( roxe_tool_install_and_symlink file symlink )
   set(BINARY_DIR ${CMAKE_BINARY_DIR}/tools/bin)
   add_custom_command( TARGET RoxeTools POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${BINARY_DIR}/${file} ${CMAKE_BINARY_DIR}/bin/ )
   install(FILES ${BINARY_DIR}/${file}
      DESTINATION ${CDT_INSTALL_PREFIX}/bin
      PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
   install(CODE "execute_process( COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_INSTALL_PREFIX}/bin)")
   install(CODE "execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink ${CDT_INSTALL_PREFIX}/bin/${file} ${CMAKE_INSTALL_PREFIX}/bin/${symlink})")
endmacro( roxe_tool_install_and_symlink )

macro( roxe_cmake_install_and_symlink file symlink )
   set(BINARY_DIR ${CMAKE_BINARY_DIR}/modules)
   install(CODE "execute_process( COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_INSTALL_PREFIX}/lib/cmake/roxe.cdt)")
   install(CODE "execute_process( COMMAND ${CMAKE_COMMAND} -E create_symlink ${CDT_INSTALL_PREFIX}/lib/cmake/roxe.cdt/${file} ${CMAKE_INSTALL_PREFIX}/lib/cmake/roxe.cdt/${symlink})")
endmacro( roxe_cmake_install_and_symlink )

macro( roxe_libraries_install)
   execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/lib)
   execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/include)
   install(DIRECTORY ${CMAKE_BINARY_DIR}/lib/ DESTINATION ${CDT_INSTALL_PREFIX}/lib)
   install(DIRECTORY ${CMAKE_BINARY_DIR}/include/ DESTINATION ${CDT_INSTALL_PREFIX}/include)
endmacro( roxe_libraries_install )

roxe_clang_install_and_symlink(llvm-ranlib roxe-ranlib)
roxe_clang_install_and_symlink(llvm-ar roxe-ar)
roxe_clang_install_and_symlink(llvm-nm roxe-nm)
roxe_clang_install_and_symlink(llvm-objcopy roxe-objcopy)
roxe_clang_install_and_symlink(llvm-objdump roxe-objdump)
roxe_clang_install_and_symlink(llvm-readobj roxe-readobj)
roxe_clang_install_and_symlink(llvm-readelf roxe-readelf)
roxe_clang_install_and_symlink(llvm-strip roxe-strip)

roxe_clang_install(opt)
roxe_clang_install(llc)
roxe_clang_install(lld)
roxe_clang_install(ld.lld)
roxe_clang_install(ld64.lld)
roxe_clang_install(clang-7)
roxe_clang_install(wasm-ld)

roxe_tool_install_and_symlink(roxe-pp roxe-pp)
roxe_tool_install_and_symlink(roxe-wast2wasm roxe-wast2wasm)
roxe_tool_install_and_symlink(roxe-wasm2wast roxe-wasm2wast)
roxe_tool_install_and_symlink(roxe-cc roxe-cc)
roxe_tool_install_and_symlink(roxe-cpp roxe-cpp)
roxe_tool_install_and_symlink(roxe-ld roxe-ld)
roxe_tool_install_and_symlink(roxe-abigen roxe-abigen)
roxe_tool_install_and_symlink(roxe-abidiff roxe-abidiff)
roxe_tool_install_and_symlink(roxe-init roxe-init)

roxe_clang_install(../lib/LLVMRoxeApply${CMAKE_SHARED_LIBRARY_SUFFIX})
roxe_clang_install(../lib/LLVMRoxeSoftfloat${CMAKE_SHARED_LIBRARY_SUFFIX})
roxe_clang_install(../lib/roxe_plugin${CMAKE_SHARED_LIBRARY_SUFFIX})

roxe_cmake_install_and_symlink(roxe.cdt-config.cmake roxe.cdt-config.cmake)
roxe_cmake_install_and_symlink(RoxeWasmToolchain.cmake RoxeWasmToolchain.cmake)
roxe_cmake_install_and_symlink(RoxeCDTMacros.cmake RoxeCDTMacros.cmake)

roxe_libraries_install()
