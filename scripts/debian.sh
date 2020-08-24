#!/bin/sh

[ -z "$1" ] && echo "please provide a version tag" && exit
[ -z "$2" ] && echo "please provide a version number" && exit

RELEASEDIR="wayPreview_debian_$1"

# creating package dir
mkdir "../../$RELEASEDIR"
cd "../../$RELEASEDIR"
mkdir -p usr/bin etc/wayPreview usr/share/doc/wayPreview

# copying files
cp ../clientBuild/wayPreviewClient usr/bin/
cp ../serverBuild/wayPreviewServer usr/bin/
cp -r ../wayPreview/wrappers/* etc/wayPreview/
cp ../wayPreview/README.md usr/share/doc/wayPreview/

# debian sutff
mkdir DEBIAN
echo "Package: wayPreview
Version: $2
Section: custom
Priority: optional
Architecture: all
Essential: no
Maintainer: Stivvo
Description: A client server, wayland native, terminal emulator independent image previewer" >> DEBIAN/control

cd ..
dpkg-deb --build "$RELEASEDIR"
