#!/bin/bash
set -e # exit on failure of any "simple" command (excludes &&, ||, or | chains)
cd /roxe.contracts
./build.sh -c /usr/opt/roxe.cdt -e /opt/roxe -t -y
cd build
tar -pczf /artifacts/contracts.tar.gz *
