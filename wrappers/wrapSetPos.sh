#!/bin/bash

swaymsg focus floating
swaymsg move position "$1" "$2" 2> /dev/null
swaymsg focus tiling 2> /dev/null
