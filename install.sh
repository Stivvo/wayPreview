#!/bin/bash

chmod +x "${PWD}/wrapWayPclient.sh"
chmod +x "${PWD}/wrapWayPserver.sh"
sudo ln -sf "${PWD}/../clientBuild/wayPreviewClient" /usr/bin/wayPreviewClient
sudo ln -sf "${PWD}/../serverBuild/wayPreviewServer" /usr/bin/wayPreviewServer
sudo ln -sf "${PWD}/wrapWayPclient.sh" /usr/bin/wrapWayPclient.sh
sudo ln -sf "${PWD}/wrapWayPserver.sh" /usr/bin/wrapWayPserver.sh
