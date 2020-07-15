#!/bin/bash

WAYPCONF="${XDG_CONFIG_HOME:=${HOME}/.config}/wayPreview/"
mkdir -p $WAYPCONF

cp "${PWD}/../config/serverConf.sh" $WAYPCONF
cp "${PWD}/../config/clientConf.sh" $WAYPCONF
cp "${PWD}/../config/setPosConf.sh" $WAYPCONF

echo "configuration files in $WAYPCONF"
