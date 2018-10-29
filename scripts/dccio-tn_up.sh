#!/bin/bash
#
# dccio-tn_up is a helper script used to start a node that was previously stopped.
# It is not intended to be run stand-alone; it is a companion to the
# dccio-tn_bounce.sh and dccio-tn_roll.sh scripts.

connected="0"

rundir=programs/noddcc
prog=noddcc

# Quote any args that are "*", so they are not expanded
qargs=`echo "$*" | sed -e 's/ \* / "*" /' -e 's/ \*$/ "*"/'`

if [ "$PWD" != "$dccIO_HOME" ]; then
    echo $0 must only be run from $dccIO_HOME
    exit -1
fi

if [ ! -e $rundir/$prog ]; then
    echo unable to locate binary for noddcc
    exit -1
fi

if [ -z "$dccIO_NODE" ]; then
    echo data directory not set
    exit -1
fi

datadir=var/lib/node_$dccIO_NODE
now=`date +'%Y_%m_%d_%H_%M_%S'`
log=stderr.$now.txt
touch $datadir/$log
rm $datadir/stderr.txt
ln -s $log $datadir/stderr.txt

relaunch() {
    echo "$rundir/$prog $qargs $* --data-dir $datadir --config-dir etc/dccio/node_$dccIO_NODE > $datadir/stdout.txt  2>> $datadir/$log "
    nohup $rundir/$prog $qargs $* --data-dir $datadir --config-dir etc/dccio/node_$dccIO_NODE > $datadir/stdout.txt  2>> $datadir/$log &
    pid=$!
    echo pid = $pid
    echo $pid > $datadir/$prog.pid

    for (( a = 10; $a; a = $(($a - 1)) )); do
        echo checking viability pass $((11 - $a))
        sleep 2
        running=$(pgrep $prog | grep -c $pid)
        echo running = $running
        if [ -z "$running" ]; then
            break;
        fi
        connected=`grep -c "net_plugin.cpp:.*connection" $datadir/$log`
        if [ "$connected" -ne 0 ]; then
            break;
        fi
    done
}

if [ -z "$dccIO_LEVEL" ]; then
    echo starting with no modifiers
    relaunch
    if [ "$connected" -eq 0 ]; then
        dccIO_LEVEL=replay
    else
        exit 0
    fi
fi

if [ "$dccIO_LEVEL" == replay ]; then
    echo starting with replay
    relaunch --hard-replay-blockchain
    if [  "$connected" -eq 0 ]; then
        dccIO_LEVEL=resync
    else
        exit 0
    fi
fi
if [ "$dccIO_LEVEL" == resync ]; then
    echo starting with delete-all-blocks
    relaunch --delete-all-blocks
fi
