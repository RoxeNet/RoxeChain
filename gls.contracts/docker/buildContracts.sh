#!/bin/bash
set -e # exit on failure of any "simple" command (excludes &&, ||, or | chains)
cd /gls.contracts
./build.sh -c /usr/opt/actc.cdt -e /opt/actc -t -y
cd build
tar -pczf /artifacts/contracts.tar.gz *
