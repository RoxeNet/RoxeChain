#!/bin/bash
set -e # exit on failure of any "simple" command (excludes &&, ||, or | chains)
# expected places to find ROXE CMAKE in the docker container, in ascending order of preference
[[ -e /usr/lib/roxe/lib/cmake/roxe/roxe-config.cmake ]] && export CMAKE_FRAMEWORK_PATH="/usr/lib/roxe"
[[ -e /opt/roxe/lib/cmake/roxe/roxe-config.cmake ]] && export CMAKE_FRAMEWORK_PATH="/opt/roxe"
[[ ! -z "$ROXE_ROOT" && -e $ROXE_ROOT/lib/cmake/roxe/roxe-config.cmake ]] && export CMAKE_FRAMEWORK_PATH="$ROXE_ROOT"
# fail if we didn't find it
[[ -z "$CMAKE_FRAMEWORK_PATH" ]] && exit 1
# export variables
echo "" >> /roxe.contracts/docker/environment.Dockerfile # necessary if there is no '\n' at end of file
echo "ENV CMAKE_FRAMEWORK_PATH=$CMAKE_FRAMEWORK_PATH" >> /roxe.contracts/docker/environment.Dockerfile
echo "ENV ROXE_ROOT=$CMAKE_FRAMEWORK_PATH" >> /roxe.contracts/docker/environment.Dockerfile