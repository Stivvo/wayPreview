#!/bin/bash

WAYPCONF="${XDG_CONFIG_HOME:=${HOME}/.config}/wayPreview/"
mkdir -p $WAYPCONF

cp "${PWD}/../config/wrapWayPclient.sh" $WAYPCONF
cp "${PWD}/../config/wrapWayPserver.sh" $WAYPCONF
cp "${PWD}/../config/wrapSetPos.sh" $WAYPCONF

echo "configuration files in $WAYPCONF"
