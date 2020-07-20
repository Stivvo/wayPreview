#!/bin/bash

[ -z "$1" ] && echo "please provide a version tag" && exit
[ -z "$2" ] && echo "please provide a version number" && exit

RELEASEDIR="wayPreview_$1"

# creating package dir
mkdir "../../$RELEASEDIR"
cd "../../$RELEASEDIR"

# copying binaries
mkdir -p usr/bin
cp ../clientBuild/wayPreviewClient usr/bin/wayPreviewClient
cp ../serverBuild/wayPreviewServer usr/bin/wayPreviewServer

# copying config files and documentation
cp -r ../wayPreview/wrappers/* usr/bin/
mkdir -p etc/wayPreview
cp -r ../wayPreview/config/* etc/wayPreview/
mkdir -p usr/share/doc/wayPreview
cp ../wayPreview/README.md usr/share/doc/wayPreview/README.md

# debian stff
mkdir DEBIAN
echo "Package: wayPreview" > DEBIAN/control
echo "Version: $2" >> DEBIAN/control
echo "Section: custom" >> DEBIAN/control
echo "Priority: optional" >> DEBIAN/control
echo "Architecture: all" >> DEBIAN/control
echo "Essential: no" >> DEBIAN/control
echo "Maintainer: Stivvo" >> DEBIAN/control
echo "Description: A client server, wayland native, terminal emulator independent image previewer" >> DEBIAN/control

cd ..
dpkg-deb --build "$RELEASEDIR"
