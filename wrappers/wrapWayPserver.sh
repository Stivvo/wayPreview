#!/bin/bash

# starts the server and the first client, which opens the first image with
# default options

wayPreviewServer "$1" --fit --wsize 0.5 &

while [ ! -S /tmp/wayPreview ]
do
    sleep 0.1s
done

swaymsg focus tiling # remove focus from floating window (sway wm only)
