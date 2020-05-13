#! /bin/bash

NAME=$1
CDT_PREFIX=${PREFIX}/${SUBPREFIX}
mkdir -p ${PREFIX}/bin/
mkdir -p ${PREFIX}/lib/cmake/${PROJECT}
mkdir -p ${CDT_PREFIX}/bin 
mkdir -p ${CDT_PREFIX}/include
mkdir -p ${CDT_PREFIX}/lib/cmake/${PROJECT}
mkdir -p ${CDT_PREFIX}/cmake
mkdir -p ${CDT_PREFIX}/scripts
mkdir -p ${CDT_PREFIX}/licenses

#echo "${PREFIX} ** ${SUBPREFIX} ** ${CDT_PREFIX}"

# install binaries 
cp -R ${BUILD_DIR}/bin/* ${CDT_PREFIX}/bin 
cp -R ${BUILD_DIR}/licenses/* ${CDT_PREFIX}/licenses

# install cmake modules
sed "s/_PREFIX_/\/${SPREFIX}/g" ${BUILD_DIR}/modules/RoxeCDTMacrosPackage.cmake &> ${CDT_PREFIX}/lib/cmake/${PROJECT}/RoxeCDTMacros.cmake
sed "s/_PREFIX_/\/${SPREFIX}/g" ${BUILD_DIR}/modules/RoxeWasmToolchainPackage.cmake &> ${CDT_PREFIX}/lib/cmake/${PROJECT}/RoxeWasmToolchain.cmake
sed "s/_PREFIX_/\/${SPREFIX}\/${SSUBPREFIX}/g" ${BUILD_DIR}/modules/${PROJECT}-config.cmake.package &> ${CDT_PREFIX}/lib/cmake/${PROJECT}/${PROJECT}-config.cmake

# install scripts
cp -R ${BUILD_DIR}/scripts/* ${CDT_PREFIX}/scripts 

# install misc.
cp ${BUILD_DIR}/roxe.imports ${CDT_PREFIX}

# install wasm includes
cp -R ${BUILD_DIR}/include/* ${CDT_PREFIX}/include

# install wasm libs
cp ${BUILD_DIR}/lib/*.a ${CDT_PREFIX}/lib

# make symlinks
pushd ${PREFIX}/lib/cmake/${PROJECT} &> /dev/null
ln -sf ../../../${SUBPREFIX}/lib/cmake/${PROJECT}/${PROJECT}-config.cmake ${PROJECT}-config.cmake
ln -sf ../../../${SUBPREFIX}/lib/cmake/${PROJECT}/RoxeWasmToolchain.cmake RoxeWasmToolchain.cmake
ln -sf ../../../${SUBPREFIX}/lib/cmake/${PROJECT}/RoxeCDTMacros.cmake RoxeCDTMacros.cmake
popd &> /dev/null

create_symlink() {
   pushd ${PREFIX}/bin &> /dev/null
   ln -sf ../${SUBPREFIX}/bin/$1 $2
   popd &> /dev/null
}

create_symlink "roxe-cc roxe-cc"
create_symlink "roxe-cpp roxe-cpp"
create_symlink "roxe-ld roxe-ld"
create_symlink "roxe-pp roxe-pp"
create_symlink "roxe-init roxe-init"
create_symlink "roxe-abigen roxe-abigen"
create_symlink "roxe-wasm2wast roxe-wasm2wast"
create_symlink "roxe-wast2wasm roxe-wast2wasm"

tar -cvzf $NAME ./${PREFIX}/*
rm -r ${PREFIX}
