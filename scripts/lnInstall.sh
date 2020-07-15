#!/bin/bash

chmod +x "${PWD}/../wrappers/wrapWayPclient.sh"
chmod +x "${PWD}/../wrappers/wrapWayPserver.sh"
chmod +x "${PWD}/../wrappers/wrapSetPos.sh"

ln -sf "${PWD}/../../clientBuild/wayPreviewClient" /usr/bin/wayPreviewClient
ln -sf "${PWD}/../../serverBuild/wayPreviewServer" /usr/bin/wayPreviewServer
ln -sf "${PWD}/../wrappers/wrapWayPclient.sh" /usr/bin/wrapWayPclient.sh
ln -sf "${PWD}/../wrappers/wrapWayPserver.sh" /usr/bin/wrapWayPserver.sh
ln -sf "${PWD}/../wrappers/wrapSetPos.sh" /usr/bin/wrapSetPos.sh

WAYPCONF="${XDG_CONFIG_HOME:=${HOME}/.config}/wayPreview/"
mkdir -p $WAYPCONF
echo "config dir: $WAYPCONF"

ln -sf "${PWD}/../config/serverConf.sh" "${WAYPCONF}serverConf.sh"
ln -sf "${PWD}/../config/clientConf.sh" "${WAYPCONF}clientConf.sh"
ln -sf "${PWD}/../config/setPosConf.sh" "${WAYPCONF}setPosConf.sh"

