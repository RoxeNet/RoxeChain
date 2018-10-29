#! /bin/bash

NAME=$1
dcc_PREFIX=${PREFIX}/${SUBPREFIX}
mkdir -p ${PREFIX}/bin/
#mkdir -p ${PREFIX}/lib/cmake/${PROJECT}
mkdir -p ${dcc_PREFIX}/bin 
mkdir -p ${dcc_PREFIX}/licenses/dccio
#mkdir -p ${dcc_PREFIX}/include
#mkdir -p ${dcc_PREFIX}/lib/cmake/${PROJECT}
#mkdir -p ${dcc_PREFIX}/cmake
#mkdir -p ${dcc_PREFIX}/scripts

# install binaries 
cp -R ${BUILD_DIR}/bin/* ${dcc_PREFIX}/bin 

# install licenses
cp -R ${BUILD_DIR}/licenses/dccio/* ${dcc_PREFIX}/licenses

# install libraries
#cp -R ${BUILD_DIR}/lib/* ${dcc_PREFIX}/lib

# install cmake modules
#sed "s/_PREFIX_/\/${SPREFIX}/g" ${BUILD_DIR}/modules/dccioTesterPackage.cmake &> ${dcc_PREFIX}/lib/cmake/${PROJECT}/dccioTester.cmake
#sed "s/_PREFIX_/\/${SPREFIX}\/${SSUBPREFIX}/g" ${BUILD_DIR}/modules/${PROJECT}-config.cmake.package &> ${dcc_PREFIX}/lib/cmake/${PROJECT}/${PROJECT}-config.cmake

# install includes
#cp -R ${BUILD_DIR}/include/* ${dcc_PREFIX}/include

# make symlinks
#pushd ${PREFIX}/lib/cmake/${PROJECT} &> /dev/null
#ln -sf ../../../${SUBPREFIX}/lib/cmake/${PROJECT}/${PROJECT}-config.cmake ${PROJECT}-config.cmake
#ln -sf ../../../${SUBPREFIX}/lib/cmake/${PROJECT}/dccioTester.cmake dccioTester.cmake
#popd &> /dev/null

pushd ${PREFIX}/bin &> /dev/null
for f in `ls ${BUILD_DIR}/bin/`; do
   bn=$(basename $f)
   ln -sf ../${SUBPREFIX}/bin/$bn $bn
done
popd &> /dev/null

tar -cvzf $NAME ./${PREFIX}/*
rm -r ${PREFIX}
