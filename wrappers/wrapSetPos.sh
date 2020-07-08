#!/bin/bash

sleep 0.001s
swaymsg focus floating
swaymsg move position $1 $2
