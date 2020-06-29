#!/bin/bash

# starts the server and the first client, which sets default options and opens
# the first image

wayPreviewServer &
CO=true
while [ $CO == true ]
do
    sleep 0.01s
    ls /tmp/wayPreview 2> /dev/null && CO=false
done
swaymsg focus tiling
wayPreviewClient "$1" --fit
