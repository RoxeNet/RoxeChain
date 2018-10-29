#!/bin/bash

# Usage:
# Go into cmd loop: sudo ./cldcc.sh
# Run single cmd:  sudo ./cldcc.sh <cldcc paramers>

PREFIX="docker-compose exec noddccd cldcc"
if [ -z $1 ] ; then
  while :
  do
    read -e -p "cldcc " cmd
    history -s "$cmd"
    $PREFIX $cmd
  done
else
  $PREFIX "$@"
fi
