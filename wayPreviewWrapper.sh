#!/bin/bash

wayPreviewServer &
CO=true
while [ $CO == true ]
do
    sleep 0.01s
    ls /tmp/wayPreview && CO=false
done
swaymsg focus tiling
wayPreviewClient "$1" --fit
