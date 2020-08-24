#!/bin/sh

NPROC="$(grep -E -c "^processor" /proc/cpuinfo)"
PW="${PWD}"

mkdir ../../clientBuild/
cd ../../clientBuild
qmake ../wayPreview/wayPreviewClient/wayPreviewClient.pro || exit 1
make -j$NPROC || exit 1

cd "${PW}"

mkdir ../../serverBuild/
cd ../../serverBuild
qmake ../wayPreview/wayPreviewServer/wayPreviewServer.pro || exit 1
make -j$NPROC || exit 1

cd "${PW}"
