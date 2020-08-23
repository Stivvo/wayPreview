#!/bin/sh

sleep 0.001s
[ "$1" != "-1" ]  && [ "$2" != "-1" ] && swaymsg --quiet focus floating && swaymsg move position "$1" "$2"
swaymsg --quiet focus tiling # remove focus from floating window (sway wm only)
