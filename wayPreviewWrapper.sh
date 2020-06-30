#!/bin/bash

# starts the server and the first client, which sets default options and opens
# the first image

wayPreviewServer &
while [ ! -S /tmp/wayPreview ]
do
    sleep 0.1s
done
swaymsg focus tiling # remove focus from floating window (sway wm only)
wayPreviewClient "$1" --fit --wsize 0.5
