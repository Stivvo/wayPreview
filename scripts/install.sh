#!/bin/sh

PREF="/usr/local/"

case $1 in
"install")
    IBIN="install -Dm755"
    IDOC="install -Dm644"
    CBIN="cp"
;;

"link")
    IBIN="ln -sf"
    IDOC="ln -sf"
    CBIN="ln -sf"
;;

*)
    echo "values accepted as first parameter: 'install', 'link'"
    exit
;;
esac

case $2 in
"program")
    # binaries
    $IBIN "${PWD}/../../clientBuild/wayPreviewClient" ${PREF}bin/wayPreviewClient
    $IBIN "${PWD}/../../serverBuild/wayPreviewServer" ${PREF}bin/wayPreviewServer

    # default configs
    mkdir /etc/wayPreview
    $IBIN "${PWD}/../wrappers/wrapWayPclient.sh" ${PREF}etc/wayPreview/wrapWayPclient.sh
    $IBIN "${PWD}/../wrappers/wrapWayPserver.sh" ${PREF}etc/wayPreview/wrapWayPserver.sh
    $IBIN "${PWD}/../wrappers/wrapSetPos.sh" ${PREF}etc/wayPreview/wrapSetPos.sh
    echo "default configuration scripts installed to ${PREF}etc/wayPreview"

    # documentation
    mkdir /usr/share/doc/wayPreview
    $IDOC "${PWD}/../README.md" ${PREF}share/doc/wayPreview/README.md
    echo "documentation installed to ${PREF}share/doc/wayPreview/README.md"
;;

"config")
    WAYPCONF="$HOME/.local/bin/"
    mkdir -p "$WAYPCONF"

    $CBIN "${PWD}/../wrappers/wrapWayPclient.sh" "${WAYPCONF}wrapWayPclient.sh"
    $CBIN "${PWD}/../wrappers/wrapWayPserver.sh" "${WAYPCONF}wrapWayPserver.sh"
    $CBIN "${PWD}/../wrappers/wrapSetPos.sh" "${WAYPCONF}wrapSetPos.sh"
    echo "user configuration files in $WAYPCONF"
;;

*)
    echo "values accepted as second parameter: 'program', 'config'"
    exit
;;
esac
