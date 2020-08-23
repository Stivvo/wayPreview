#!/bin/sh

case $1 in
"program")
    rm /usr/local/bin/wayPreviewClient
    rm /usr/local/bin/wayPreviewServer

    rm -r /usr/local/etc/wayPreview
    rm -r /usr/local/share/doc/wayPreview
;;

"config")
    rm -r $HOME/.local/bin/wrapSetPos.sh
    rm -r $HOME/.local/bin/wrapWayPclient.sh
    rm -r $HOME/.local/bin/wrapWayPserver.sh
;;

*)
    echo "values accepted as parameter: 'program', 'config'"
