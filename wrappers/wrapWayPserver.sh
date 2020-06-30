#!/bin/bash

# starts the server and the first client, which opens the first image with
# default options

wayPreviewServer &
while [ ! -S /tmp/wayPreview ]
do
    sleep 0.1s
done
swaymsg focus tiling # remove focus from floating window (sway wm only)
wrapWayPclient.sh "$1"
