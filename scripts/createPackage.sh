#!/bin/bash

[ -z "$1" ] && echo "please provide a version tag" && exit

# creating package dir
mkdir "../../$1"
cd "../../$1"

# copying binaries
mkdir clientBuild serverBuild
cp ../clientBuild/wayPreviewClient clientBuild/wayPreviewClient
cp ../serverBuild/wayPreviewServer serverBuild/wayPreviewServer

# copying scripts
mkdir wayPreview wayPreview/scripts
cp ../wayPreview/scripts/install.sh wayPreview/script/install.sh
cp ../wayPreview/scripts/installConfig.sh wayPreview/script/installConfig.sh
cp ../wayPreview/scripts/uninstall.sh uninstall.sh

# copying config files and documentation
cp -r ../wayPreview/config wayPreview/
cp -r ../wayPreview/wrappers wayPreview/
cp ../wayPreview/README.md wayPreview/README.md

# creating install.sh that runs wayPreview/script/install.sh
echo "#!/bin/bash" > install.sh
echo "cd wayPreview/script/" >> install.sh
echo "./install.sh" >> install.sh

# creating installConfig.sh that runs wayPreview/script/installConfig.sh
echo "#!/bin/bash" > installConfig.sh
echo "cd wayPreview/script/" >> installConfig.sh
echo "./installConfig.sh" >> installConfig.sh
