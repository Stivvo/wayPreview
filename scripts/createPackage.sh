#!/bin/bash

[ -z "$1" ] && echo "please provide a version tag" && exit

RELEASEDIR="wayPreview_universal_$1"

# creating package dir
mkdir "../../$RELEASEDIR"
cd "../../$RELEASEDIR"

# copying binaries
mkdir clientBuild serverBuild
cp ../clientBuild/wayPreviewClient clientBuild/wayPreviewClient
cp ../serverBuild/wayPreviewServer serverBuild/wayPreviewServer

# copying scripts
mkdir wayPreview wayPreview/scripts
cp ../wayPreview/scripts/install.sh wayPreview/scripts/install.sh
cp ../wayPreview/scripts/installConfig.sh wayPreview/scripts/installConfig.sh
cp ../wayPreview/scripts/uninstall.sh uninstall.sh

# copying config files and documentation
cp -r ../wayPreview/config wayPreview/
cp -r ../wayPreview/wrappers wayPreview/
cp ../wayPreview/README.md wayPreview/README.md

# creating install.sh that runs wayPreview/scripts/install.sh
echo "#!/bin/bash" > install.sh
echo "cd wayPreview/scripts/" >> install.sh
echo "./install.sh install program" >> install.sh

# creating installConfig.sh that runs wayPreview/scripts/installConfig.sh
echo "#!/bin/bash" > installConfig.sh
echo "cd wayPreview/scripts/" >> installConfig.sh
echo "./install.sh install config" >> installConfig.sh

cd ..
rm "${RELEASEDIR}.zip"
zip -r "${RELEASEDIR}.zip" "$RELEASEDIR"
echo "universal package created: ${RELEASEDIR}.zip"
