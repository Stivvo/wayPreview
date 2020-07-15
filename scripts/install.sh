#!/bin/bash

# executables
install -Dm755 "${PWD}/../../clientBuild/wayPreviewClient" /usr/bin/wayPreviewClient
install -Dm755 "${PWD}/../../serverBuild/wayPreviewServer" /usr/bin/wayPreviewServer

# wrappers
install -Dm755 "${PWD}/../wrappers/wrapWayPclient.sh" /usr/bin/wrapWayPclient.sh
install -Dm755 "${PWD}/../wrappers/wrapWayPserver.sh" /usr/bin/wrapWayPserver.sh
install -Dm755 "${PWD}/../wrappers/wrapSetPos.sh" /usr/bin/wrapSetPos.sh

# documentation
install -Dm644 "${PWD}/../README.md" /usr/share/doc/wayPreview/README.md
