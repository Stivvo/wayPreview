#!/bin/sh

NPROC="$(grep -E -c "^processor" /proc/cpuinfo)"
PW="${PWD}"

mkdir ../../clientBuild/
cd ../../clientBuild
qmake ../wayPreview/wayPreviewClient/wayPreviewClient.pro
make -j$NPROC

cd "${PW}"

mkdir ../../serverBuild/
cd ../../serverBuild
qmake ../wayPreview/wayPreviewServer/wayPreviewServer.pro
make -j$NPROC

cd "${PW}"
