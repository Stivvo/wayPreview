#!/bin/sh

[ -z "$1" ] && echo "please provide a version tag" && exit

RELEASEDIR="wayPreview_universal_$1"

# creating package dir
mkdir "../../$RELEASEDIR"
cd "../../$RELEASEDIR"

# copying binaries
mkdir clientBuild serverBuild
cp ../clientBuild/wayPreviewClient clientBuild/
cp ../serverBuild/wayPreviewServer serverBuild/

# copying scripts
mkdir -p wayPreview/scripts
cp ../wayPreview/scripts/*stall.sh wayPreview/scripts/

# copying config files and documentation
cp -r ../wayPreview/wrappers wayPreview/
cp ../wayPreview/README.md wayPreview/

# creating install.sh that runs wayPreview/scripts/install.sh
echo "#!/bin/sh" > install.sh
echo "cd wayPreview/scripts/ && sudo ./install.sh install program &&
./install.sh install wrappers" >> install.sh

# creating uninstall.sh that runs wayPreview/scripts/uninstall.sh
echo "#!/bin/sh" > uninstall.sh
echo "cd wayPreview/scripts/ && sudo ./uninstall.sh program
./uninstall.sh wrappers" >> uninstall.sh

cd ..
rm "${RELEASEDIR}.zip"
zip -r "${RELEASEDIR}.zip" "$RELEASEDIR"
echo "universal package created: ${RELEASEDIR}.zip"
