#!/bin/sh

PREF="/usr/local/"

install -Dm755 --directory ${PREF}share/doc/wayPreview
install -Dm755 --directory ${PREF}etc/wayPreview
install -Dm755 --directory ${PREF}bin

case $1 in
"install")
    IBIN="install -Dm755"
    IDOC="install -Dm644"
;;

"link")
    IBIN="ln -sf"
    IDOC="ln -sf"
;;

*)
    echo "values accepted as first parameter: 'install', 'link'"
    exit
;;
esac

case $2 in
"program")
    # binaries
    $IBIN "${PWD}/../../clientBuild/wayPreviewClient" ${PREF}bin/ &&
    $IBIN "${PWD}/../../serverBuild/wayPreviewServer" ${PREF}bin/ &&
    echo "binaries -> ${PREF}bin/"

    # default configs
    $IBIN ${PWD}/../wrappers/*.sh ${PREF}etc/wayPreview/ &&
    echo "default wrappers -> ${PREF}etc/wayPreview/"

    # documentation
    $IDOC ${PWD}/../README.md ${PREF}share/doc/wayPreview/ &&
    echo "documentation -> ${PREF}share/doc/wayPreview/"
;;

"wrappers")
    WAYPCONF="$HOME/.local/bin/"
    mkdir -p "$WAYPCONF"

    $IBIN ${PWD}/../wrappers/*.sh ${WAYPCONF} &&
    echo "user wrappers -> $WAYPCONF"
;;

*)
    echo "values accepted as second parameter: 'program', 'wrappers'"
    exit
;;
esac
