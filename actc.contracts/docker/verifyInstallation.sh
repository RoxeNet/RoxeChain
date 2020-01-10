#!/bin/bash
set -e # exit on failure of any "simple" command (excludes &&, ||, or | chains)
# expected places to find ACTC CMAKE in the docker container, in ascending order of preference
[[ -e /usr/lib/actc/lib/cmake/actc/actc-config.cmake ]] && export CMAKE_FRAMEWORK_PATH="/usr/lib/actc"
[[ -e /opt/actc/lib/cmake/actc/actc-config.cmake ]] && export CMAKE_FRAMEWORK_PATH="/opt/actc"
[[ ! -z "$ACTC_ROOT" && -e $ACTC_ROOT/lib/cmake/actc/actc-config.cmake ]] && export CMAKE_FRAMEWORK_PATH="$ACTC_ROOT"
# fail if we didn't find it
[[ -z "$CMAKE_FRAMEWORK_PATH" ]] && exit 1
# export variables
echo "" >> /actc.contracts/docker/environment.Dockerfile # necessary if there is no '\n' at end of file
echo "ENV CMAKE_FRAMEWORK_PATH=$CMAKE_FRAMEWORK_PATH" >> /actc.contracts/docker/environment.Dockerfile
echo "ENV ACTC_ROOT=$CMAKE_FRAMEWORK_PATH" >> /actc.contracts/docker/environment.Dockerfile