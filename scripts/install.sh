#!/bin/sh

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
    $IBIN "${PWD}/../../clientBuild/wayPreviewClient" /usr/bin/wayPreviewClient
    $IBIN "${PWD}/../../serverBuild/wayPreviewServer" /usr/bin/wayPreviewServer

    # wrappers
    $IBIN "${PWD}/../wrappers/wrapWayPclient.sh" /usr/bin/wrapWayPclient.sh
    $IBIN "${PWD}/../wrappers/wrapWayPserver.sh" /usr/bin/wrapWayPserver.sh
    $IBIN "${PWD}/../wrappers/wrapSetPos.sh" /usr/bin/wrapSetPos.sh
    echo "binaries and wrappers installed to /usr/bin"

    # default configs
    mkdir /etc/wayPreview
    $IBIN "${PWD}/../config/wrapWayPclient.sh" /etc/wayPreview/wrapWayPclient.sh
    $IBIN "${PWD}/../config/wrapWayPserver.sh" /etc/wayPreview/wrapWayPserver.sh
    $IBIN "${PWD}/../config/wrapSetPos.sh" /etc/wayPreview/wrapSetPos.sh
    echo "default configuration scripts installed to /etc/wayPreview"

    # documentation
    mkdir /usr/share/doc/wayPreview
    $IDOC "${PWD}/../README.md" /usr/share/doc/wayPreview/README.md
    echo "documentation installed to /usr/share/doc/wayPreview/README.md"
;;

"config")
    WAYPCONF="${XDG_CONFIG_HOME:=${HOME}/.config}/wayPreview/"
    mkdir -p "$WAYPCONF"

    $CBIN "${PWD}/../config/wrapWayPclient.sh" "${WAYPCONF}wrapWayPclient.sh"
    $CBIN "${PWD}/../config/wrapWayPserver.sh" "${WAYPCONF}wrapWayPserver.sh"
    $CBIN "${PWD}/../config/wrapSetPos.sh" "${WAYPCONF}wrapSetPos.sh"

    echo "user configuration files in $WAYPCONF"
;;

*)
    echo "values accepted as second parameter: 'program', 'config'"
    exit
;;
esac
