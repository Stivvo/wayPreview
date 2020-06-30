#!/bin/bash

chmod +x "${PWD}/../wrappers/wrapWayPclient.sh"
chmod +x "${PWD}/../wrappers/wrapWayPserver.sh"
sudo ln -sf "${PWD}/../../clientBuild/wayPreviewClient" /usr/bin/wayPreviewClient
sudo ln -sf "${PWD}/../../serverBuild/wayPreviewServer" /usr/bin/wayPreviewServer
sudo ln -sf "${PWD}/../wrappers/wrapWayPclient.sh" /usr/bin/wrapWayPclient.sh
sudo ln -sf "${PWD}/../wrappers/wrapWayPserver.sh" /usr/bin/wrapWayPserver.sh
