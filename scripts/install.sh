#!/bin/bash

# executables
install -Dm755 "${PWD}/../../clientBuild/wayPreviewClient" /usr/bin/wayPreviewClient
install -Dm755 "${PWD}/../../serverBuild/wayPreviewServer" /usr/bin/wayPreviewServer

# wrappers
install -Dm755 "${PWD}/../wrappers/wrapWayPclient.sh" /usr/bin/wrapWayPclient.sh
install -Dm755 "${PWD}/../wrappers/wrapWayPserver.sh" /usr/bin/wrapWayPserver.sh
install -Dm755 "${PWD}/../wrappers/wrapSetPos.sh" /usr/bin/wrapSetPos.sh

# default configs
cp "${PWD}/../config/wrapWayPclient.sh" /etc/wayPreview/wrapWayPclient.sh
cp "${PWD}/../config/wrapWayPserver.sh" /etc/wayPreview/wrapWayPserver.sh
cp "${PWD}/../config/wrapSetPos.sh" /etc/wayPreview/wrapSetPos.sh
echo "default configuration scripts installed to /etc/wayPreview"

# documentation
install -Dm644 "${PWD}/../README.md" /usr/share/doc/wayPreview/README.md
