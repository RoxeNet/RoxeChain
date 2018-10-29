#!/bin/sh
cd /opt/dccio/bin

if [ ! -d "/opt/dccio/bin/data-dir" ]; then
    mkdir /opt/dccio/bin/data-dir
fi

if [ -f '/opt/dccio/bin/data-dir/config.ini' ]; then
    echo
  else
    cp /config.ini /opt/dccio/bin/data-dir
fi

if [ -d '/opt/dccio/bin/data-dir/contracts' ]; then
    echo
  else
    cp -r /contracts /opt/dccio/bin/data-dir
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
    CONFIG_DIR="--config-dir=/opt/dccio/bin/data-dir"
else
    CONFIG_DIR=""
fi

exec /opt/dccio/bin/noddcc $CONFIG_DIR "$@"
