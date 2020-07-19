#!/bin/bash

mkdir "../../$1"
cd "../../$1"

mkdir clientBuild serverBuild
cp ../clientBuild/wayPreviewClient clientBuild/wayPreviewClient
cp ../serverBuild/wayPreviewServer serverBuild/wayPreviewServer

mkdir wayPreview wayPreview/script
cp ../wayPreview/scripts/install.sh wayPreview/script/install.sh
cp ../wayPreview/scripts/installConfig.sh wayPreview/script/installConfig.sh
cp ../wayPreview/scripts/uninstall.sh uninstall.sh
cp -r ../wayPreview/config wayPreview/
cp -r ../wayPreview/wrappers wayPreview/

echo "#!/bin/bash" > install.sh
echo "wayPreview/script/./install.sh" >> install.sh
