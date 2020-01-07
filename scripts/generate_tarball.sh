#! /bin/bash

NAME=$1
actc_PREFIX=${PREFIX}/${SUBPREFIX}
mkdir -p ${PREFIX}/bin/
#mkdir -p ${PREFIX}/lib/cmake/${PROJECT}
mkdir -p ${actc_PREFIX}/bin
mkdir -p ${actc_PREFIX}/licenses/actc
#mkdir -p ${actc_PREFIX}/include
#mkdir -p ${actc_PREFIX}/lib/cmake/${PROJECT}
#mkdir -p ${actc_PREFIX}/cmake
#mkdir -p ${actc_PREFIX}/scripts

# install binaries 
cp -R ${BUILD_DIR}/bin/* ${actc_PREFIX}/bin

# install licenses
cp -R ${BUILD_DIR}/licenses/actc/* ${actc_PREFIX}/licenses

# install libraries
#cp -R ${BUILD_DIR}/lib/* ${actc_PREFIX}/lib

# install cmake modules
#sed "s/_PREFIX_/\/${SPREFIX}/g" ${BUILD_DIR}/modules/actcTesterPackage.cmake &> ${actc_PREFIX}/lib/cmake/${PROJECT}/actcTester.cmake
#sed "s/_PREFIX_/\/${SPREFIX}\/${SSUBPREFIX}/g" ${BUILD_DIR}/modules/${PROJECT}-config.cmake.package &> ${actc_PREFIX}/lib/cmake/${PROJECT}/${PROJECT}-config.cmake

# install includes
#cp -R ${BUILD_DIR}/include/* ${actc_PREFIX}/include

# make symlinks
#pushd ${PREFIX}/lib/cmake/${PROJECT} &> /dev/null
#ln -sf ../../../${SUBPREFIX}/lib/cmake/${PROJECT}/${PROJECT}-config.cmake ${PROJECT}-config.cmake
#ln -sf ../../../${SUBPREFIX}/lib/cmake/${PROJECT}/actcTester.cmake actcTester.cmake
#popd &> /dev/null

pushd ${PREFIX}/bin &> /dev/null
for f in `ls ${BUILD_DIR}/bin/`; do
   bn=$(basename $f)
   ln -sf ../${SUBPREFIX}/bin/$bn $bn
done
popd &> /dev/null

tar -cvzf $NAME ./${PREFIX}/*
rm -r ${PREFIX}
