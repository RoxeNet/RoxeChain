#!/bin/bash

# Usage:
# Go into cmd loop: sudo ./clactc.sh
# Run single cmd:  sudo ./clactc.sh <clactc paramers>

PREFIX="docker-compose exec nodactcd clactc"
if [ -z $1 ] ; then
  while :
  do
    read -e -p "clactc " cmd
    history -s "$cmd"
    $PREFIX $cmd
  done
else
  $PREFIX "$@"
fi
