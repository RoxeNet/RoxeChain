#!/usr/bin/env bash
set -eo pipefail

NAME=$1
ROXE_PREFIX=${PREFIX}/${SUBPREFIX}
mkdir -p ${PREFIX}/bin/
#mkdir -p ${PREFIX}/lib/cmake/${PROJECT}
mkdir -p ${ROXE_PREFIX}/bin
mkdir -p ${ROXE_PREFIX}/licenses/roxe
#mkdir -p ${ROXE_PREFIX}/include
#mkdir -p ${ROXE_PREFIX}/lib/cmake/${PROJECT}
#mkdir -p ${ROXE_PREFIX}/cmake
#mkdir -p ${ROXE_PREFIX}/scripts

# install binaries 
cp -R ${BUILD_DIR}/bin/* ${ROXE_PREFIX}/bin  || exit 1

# install licenses
cp -R ${BUILD_DIR}/licenses/roxe/* ${ROXE_PREFIX}/licenses || exit 1

# install libraries
#cp -R ${BUILD_DIR}/lib/* ${ROXE_PREFIX}/lib

# install cmake modules
#sed "s/_PREFIX_/\/${SPREFIX}/g" ${BUILD_DIR}/modules/RoxeTesterPackage.cmake &> ${ROXE_PREFIX}/lib/cmake/${PROJECT}/RoxeTester.cmake
#sed "s/_PREFIX_/\/${SPREFIX}\/${SSUBPREFIX}/g" ${BUILD_DIR}/modules/${PROJECT}-config.cmake.package &> ${ROXE_PREFIX}/lib/cmake/${PROJECT}/${PROJECT}-config.cmake

# install includes
#cp -R ${BUILD_DIR}/include/* ${ROXE_PREFIX}/include

# make symlinks
#pushd ${PREFIX}/lib/cmake/${PROJECT} &> /dev/null
#ln -sf ../../../${SUBPREFIX}/lib/cmake/${PROJECT}/${PROJECT}-config.cmake ${PROJECT}-config.cmake
#ln -sf ../../../${SUBPREFIX}/lib/cmake/${PROJECT}/RoxeTester.cmake RoxeTester.cmake
#popd &> /dev/null

for f in $(ls "${BUILD_DIR}/bin/"); do
   bn=$(basename $f)
   ln -sf ../${SUBPREFIX}/bin/$bn ${PREFIX}/bin/$bn || exit 1
done
echo "Generating Tarball $NAME.tar.gz..."
tar -cvzf $NAME.tar.gz ./${PREFIX}/* || exit 1
rm -r ${PREFIX} || exit 1
