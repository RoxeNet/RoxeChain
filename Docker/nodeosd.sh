#!/bin/sh
cd /opt/actc/bin

if [ ! -d "/opt/actc/bin/data-dir" ]; then
    mkdir /opt/actc/bin/data-dir
fi

if [ -f '/opt/actc/bin/data-dir/config.ini' ]; then
    echo
  else
    cp /config.ini /opt/actc/bin/data-dir
fi

if [ -d '/opt/actc/bin/data-dir/contracts' ]; then
    echo
  else
    cp -r /contracts /opt/actc/bin/data-dir
fi

while :; do
    case $1 in
        --config-dir=?*)
            CONFIG_DIR=${1#*=}
            ;;
        *)
            break
    esac
    shift
done

if [ ! "$CONFIG_DIR" ]; then
    CONFIG_DIR="--config-dir=/opt/actc/bin/data-dir"
else
    CONFIG_DIR=""
fi

exec /opt/actc/bin/nodactc $CONFIG_DIR "$@"
