#!/bin/bash

chmod +x "${PWD}/../wrappers/wrapWayPclient.sh"
chmod +x "${PWD}/../wrappers/wrapWayPserver.sh"
chmod +x "${PWD}/../wrappers/wrapSetPos.sh"
sudo cp "${PWD}/../../clientBuild/wayPreviewClient" /usr/bin/wayPreviewClient
sudo cp "${PWD}/../../serverBuild/wayPreviewServer" /usr/bin/wayPreviewServer
sudo cp "${PWD}/../wrappers/wrapWayPclient.sh" /usr/bin/wrapWayPclient.sh
sudo cp "${PWD}/../wrappers/wrapWayPserver.sh" /usr/bin/wrapWayPserver.sh
sudo cp "${PWD}/../wrappers/wrapSetPos.sh" /usr/bin/wrapSetPos.sh
