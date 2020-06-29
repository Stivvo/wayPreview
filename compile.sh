#!/bin/bash

PW="${PWD}"

mkdir ../clientBuild/
cd ../clientBuild
qmake ../wayPreview/wayPreviewClient/wayPreviewClient.pro
make -j2

cd "${PW}"

mkdir ../serverBuild/
cd ../serverBuild
qmake ../wayPreview/wayPreviewServer/wayPreviewServer.pro
make -j2

cd "${PW}"
