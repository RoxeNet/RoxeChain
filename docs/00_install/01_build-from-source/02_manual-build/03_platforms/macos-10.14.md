---
content_title: MacOS 10.14
---

This section contains shell commands to manually download, build, install, test, and uninstall ROXE and dependencies on MacOS 10.14.

[[info | Building ROXE is for Advanced Developers]]
| If you are new to ROXE, it is recommended that you install the [ROXE Prebuilt Binaries](../../../00_install-prebuilt-binaries.md) instead of building from source.

Select a task below, then copy/paste the shell commands to a Unix terminal to execute:

* [Download ROXE Repository](#download-roxe-repository)
* [Install ROXE Dependencies](#install-roxe-dependencies)
* [Build ROXE](#build-roxe)
* [Install ROXE](#install-roxe)
* [Test ROXE](#test-roxe)
* [Uninstall ROXE](#uninstall-roxe)

[[info | Building ROXE on another OS?]]
| Visit the [Build ROXE from Source](../../index.md) section.

## Download ROXE Repository
These commands set the ROXE directories, install git, and clone the ROXE repository.
```sh
# set ROXE directories
export ROXE_LOCATION=~/roxe/roxe
export ROXE_INSTALL_LOCATION=$ROXE_LOCATION/../install
mkdir -p $ROXE_INSTALL_LOCATION
# install git
brew update && brew install git
# clone ROXE repository
git clone https://github.com/ROXE/roxe.git $ROXE_LOCATION
cd $ROXE_LOCATION && git submodule update --init --recursive
```

## Install Dependencies
These commands install the ROXE software dependencies. Make sure to [Download the ROXE Repository](#download-roxe-repository) first and set the ROXE directories.
```sh
# install dependencies
brew install cmake python libtool libusb graphviz automake wget gmp pkgconfig doxygen openssl@1.1 jq boost || :
export PATH=$ROXE_INSTALL_LOCATION/bin:$PATH
# install mongodb
mkdir -p $ROXE_INSTALL_LOCATION/bin
cd $ROXE_INSTALL_LOCATION && curl -OL https://fastdl.mongodb.org/osx/mongodb-osx-ssl-x86_64-3.6.3.tgz
    tar -xzf mongodb-osx-ssl-x86_64-3.6.3.tgz && rm -f mongodb-osx-ssl-x86_64-3.6.3.tgz && \
    mv $ROXE_INSTALL_LOCATION/mongodb-osx-x86_64-3.6.3/bin/* $ROXE_INSTALL_LOCATION/bin/ && \
    rm -rf $ROXE_INSTALL_LOCATION/mongodb-osx-x86_64-3.6.3 && rm -rf $ROXE_INSTALL_LOCATION/mongodb-osx-ssl-x86_64-3.6.3.tgz
# install mongo-c-driver from source
cd $ROXE_INSTALL_LOCATION && curl -LO https://github.com/mongodb/mongo-c-driver/releases/download/1.13.0/mongo-c-driver-1.13.0.tar.gz && \
    tar -xzf mongo-c-driver-1.13.0.tar.gz && cd mongo-c-driver-1.13.0 && \
    mkdir -p cmake-build && cd cmake-build && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$ROXE_INSTALL_LOCATION -DENABLE_BSON=ON -DENABLE_SSL=DARWIN -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF -DENABLE_STATIC=ON -DENABLE_ICU=OFF -DENABLE_SASL=OFF -DENABLE_SNAPPY=OFF .. && \
    make -j $(getconf _NPROCESSORS_ONLN) && \
    make install && \
    rm -rf $ROXE_INSTALL_LOCATION/mongo-c-driver-1.13.0.tar.gz $ROXE_INSTALL_LOCATION/mongo-c-driver-1.13.0
# install mongo-cxx-driver from source
cd $ROXE_INSTALL_LOCATION && curl -L https://github.com/mongodb/mongo-cxx-driver/archive/r3.4.0.tar.gz -o mongo-cxx-driver-r3.4.0.tar.gz && \
    tar -xzf mongo-cxx-driver-r3.4.0.tar.gz && cd mongo-cxx-driver-r3.4.0/build && \
    cmake -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$ROXE_INSTALL_LOCATION .. && \
    make -j $(getconf _NPROCESSORS_ONLN) VERBOSE=1 && \
    make install && \
    rm -rf $ROXE_INSTALL_LOCATION/mongo-cxx-driver-r3.4.0.tar.gz $ROXE_INSTALL_LOCATION/mongo-cxx-driver-r3.4.0
```

## Build ROXE
These commands build the ROXE software on the specified OS. Make sure to [Install ROXE Dependencies](#install-roxe-dependencies) first.

[[caution | `ROXE_BUILD_LOCATION` environment variable]]
| Do NOT change this variable. It is set for convenience only. It should always be set to the `build` folder within the cloned repository.

```sh
export ROXE_BUILD_LOCATION=$ROXE_LOCATION/build
mkdir -p $ROXE_BUILD_LOCATION
cd $ROXE_BUILD_LOCATION && cmake -DCMAKE_BUILD_TYPE='Release' -DCMAKE_INSTALL_PREFIX=$ROXE_INSTALL_LOCATION -DBUILD_MONGO_DB_PLUGIN=true $ROXE_LOCATION
cd $ROXE_BUILD_LOCATION && make -j$(getconf _NPROCESSORS_ONLN)
```

## Install ROXE
This command installs the ROXE software on the specified OS. Make sure to [Build ROXE](#build-roxe) first.
```sh
cd $ROXE_BUILD_LOCATION && make install
```

## Test ROXE
These commands validate the ROXE software installation on the specified OS. This task is optional but recommended. Make sure to [Install ROXE](#install-roxe) first.
```sh
$ROXE_INSTALL_LOCATION/bin/mongod --fork --logpath $(pwd)/mongod.log --dbpath $(pwd)/mongodata
cd $ROXE_BUILD_LOCATION && make test
```

## Uninstall ROXE
These commands uninstall the ROXE software from the specified OS.
```sh
xargs rm < $ROXE_BUILD_LOCATION/install_manifest.txt
rm -rf $ROXE_BUILD_LOCATION
```
