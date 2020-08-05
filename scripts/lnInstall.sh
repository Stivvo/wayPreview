#!/bin/bash

# binaries
ln -sf "${pwd}/../../clientbuild/waypreviewclient" /usr/bin/waypreviewclient
ln -sf "${pwd}/../../serverbuild/waypreviewserver" /usr/bin/waypreviewserver

# wrappers
ln -sf "${PWD}/../wrappers/wrapWayPclient.sh" /usr/bin/wrapWayPclient.sh
ln -sf "${PWD}/../wrappers/wrapWayPserver.sh" /usr/bin/wrapWayPserver.sh
ln -sf "${PWD}/../wrappers/wrapSetPos.sh" /usr/bin/wrapSetPos.sh

# default configs
mkdir /etc/wayPreview
ln -sf "${PWD}/../config/wrapWayPclient.sh" /etc/wayPreview/wrapWayPclient.sh
ln -sf "${PWD}/../config/wrapWayPserver.sh" /etc/wayPreview/wrapWayPserver.sh
ln -sf "${PWD}/../config/wrapSetPos.sh" /etc/wayPreview/wrapSetPos.sh
echo "default configuration scripts installed to /etc/wayPreview"

# documentation
mkdir -p /usr/share/doc/wayPreview
ln -sf "${PWD}/../README.md" /usr/share/doc/wayPreview/README.md

WAYPCONF="${XDG_CONFIG_HOME:=${HOME}/.config}/wayPreview/"
mkdir -p $WAYPCONF
echo "config dir: $WAYPCONF"

ln -sf "${PWD}/../config/wrapWayPclient.sh" "${WAYPCONF}wrapWayPclient.sh"
ln -sf "${PWD}/../config/wrapWayPserver.sh" "${WAYPCONF}wrapWayPserver.sh"
ln -sf "${PWD}/../config/wrapSetPos.sh" "${WAYPCONF}wrapSetPos.sh"

