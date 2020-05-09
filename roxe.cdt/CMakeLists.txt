cmake_minimum_required(VERSION 3.5)
project(roxe_cdt)

find_program(SCCACHE_FOUND sccache)
if (SCCACHE_FOUND)
   message(STATUS "Using sccache")
   set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE sccache)
else()
   find_program(CCACHE_FOUND ccache)
   if (CCACHE_FOUND)
      message(STATUS "Using ccache")
      set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
   endif()
endif()


set(VERSION_MAJOR 1)
set(VERSION_MINOR 6)
set(VERSION_PATCH 3)
#set(VERSION_SUFFIX rc2)

if (VERSION_SUFFIX)
   set(VERSION_FULL "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}-${VERSION_SUFFIX}")
else()
   set(VERSION_FULL "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
endif()

set(CDT_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/roxe.cdt)

include(GNUInstallDirs)

include(modules/ClangExternalProject.txt)
include(modules/ToolsExternalProject.txt)

set(WASM_SDK_BUILD true)

### Configure the RoxeWasmToolchain.cmakes
set(CDT_ROOT_DIR ${CMAKE_BINARY_DIR})

configure_file(${CMAKE_SOURCE_DIR}/modules/roxe.cdt-config.cmake ${CMAKE_BINARY_DIR}/lib/cmake/roxe.cdt/roxe.cdt-config.cmake @ONLY)
configure_file(${CMAKE_SOURCE_DIR}/modules/RoxeCDTMacros.cmake.in ${CMAKE_BINARY_DIR}/lib/cmake/roxe.cdt/RoxeCDTMacros.cmake @ONLY)
configure_file(${CMAKE_SOURCE_DIR}/modules/RoxeWasmToolchain.cmake.in ${CMAKE_BINARY_DIR}/lib/cmake/roxe.cdt/RoxeWasmToolchain.cmake @ONLY)

set(CDT_ROOT_DIR ${CDT_INSTALL_PREFIX})

configure_file(${CMAKE_SOURCE_DIR}/modules/roxe.cdt-config.cmake ${CMAKE_BINARY_DIR}/modules/roxe.cdt-config.cmake @ONLY)
configure_file(${CMAKE_SOURCE_DIR}/modules/RoxeCDTMacros.cmake.in ${CMAKE_BINARY_DIR}/modules/RoxeCDTMacros.cmake @ONLY)
configure_file(${CMAKE_SOURCE_DIR}/modules/RoxeWasmToolchain.cmake.in ${CMAKE_BINARY_DIR}/modules/RoxeWasmToolchain.cmake @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/modules/RoxeCDTMacros.cmake DESTINATION ${CDT_INSTALL_PREFIX}/lib/cmake/roxe.cdt)

set(CDT_ROOT_DIR "_PREFIX_")
configure_file(${CMAKE_SOURCE_DIR}/modules/RoxeCDTMacros.cmake.in ${CMAKE_BINARY_DIR}/modules/RoxeCDTMacrosPackage.cmake @ONLY)
configure_file(${CMAKE_SOURCE_DIR}/modules/RoxeWasmToolchain.cmake.in ${CMAKE_BINARY_DIR}/modules/RoxeWasmToolchainPackage.cmake @ONLY)
configure_file(${CMAKE_SOURCE_DIR}/modules/roxe.cdt-config.cmake ${CMAKE_BINARY_DIR}/modules/roxe.cdt-config.cmake.package @ONLY)

include(modules/LibrariesExternalProject.txt)

include(modules/InstallCDT.cmake)

configure_file(${CMAKE_SOURCE_DIR}/imports/roxe.imports.in ${CMAKE_BINARY_DIR}/roxe.imports COPYONLY)
install(FILES ${CMAKE_BINARY_DIR}/roxe.imports DESTINATION ${CDT_INSTALL_PREFIX})

configure_file(${CMAKE_SOURCE_DIR}/scripts/ricardroxe/ricardroxe.py ${CMAKE_BINARY_DIR}/scripts/ricardroxe.py COPYONLY)
install(FILES ${CMAKE_BINARY_DIR}/scripts/ricardroxe.py DESTINATION ${CDT_INSTALL_PREFIX}/scripts)

# section for package construction
set(VENDOR "block.one")
set(PROJECT_NAME "roxe.cdt")
set(DESC "Toolchain and supporting tools for the ROXE.IO platform")
set(URL "https://github.com/roxe/roxe.cdt")
set(EMAIL "support@block.one")
configure_file(${CMAKE_SOURCE_DIR}/scripts/generate_package.sh.in ${CMAKE_BINARY_DIR}/packages/generate_package.sh @ONLY)
configure_file(${CMAKE_SOURCE_DIR}/scripts/generate_deb.sh ${CMAKE_BINARY_DIR}/packages/generate_deb.sh COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/scripts/generate_bottle.sh ${CMAKE_BINARY_DIR}/packages/generate_bottle.sh COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/scripts/generate_rpm.sh ${CMAKE_BINARY_DIR}/packages/generate_rpm.sh COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/scripts/generate_tarball.sh ${CMAKE_BINARY_DIR}/packages/generate_tarball.sh COPYONLY)

# add licenses
configure_file(${CMAKE_SOURCE_DIR}/roxe_llvm/LICENSE.TXT ${CMAKE_BINARY_DIR}/licenses/llvm.license COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/libraries/boost/boost.license ${CMAKE_BINARY_DIR}/licenses/boost.license COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/tools/external/wabt/LICENSE ${CMAKE_BINARY_DIR}/licenses/wabt.license COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/tools/jsoncons/LICENSE ${CMAKE_BINARY_DIR}/licenses/jsoncons.license COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/LICENSE ${CMAKE_BINARY_DIR}/licenses/roxe.cdt.license COPYONLY)

include(modules/TestsExternalProject.txt)

include(CTest)
enable_testing()
add_subdirectory(tests)
