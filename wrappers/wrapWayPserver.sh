#!/bin/bash

# starts the server and the first client, which opens the first image with
# default options

wayPreviewServer "$1" --fit --wsize 0.5 --wx 500 --wy 20 && rm /tmp/wayPreview &

while [ ! -S /tmp/wayPreview ]
do
    sleep 0.01s
done

swaymsg focus tiling # remove focus from floating window (sway wm only)
