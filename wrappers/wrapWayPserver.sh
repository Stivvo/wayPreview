#!/bin/bash

# starts the server and the first client, which opens the first image with
# default options

wayPreviewServer "$1" --fit --wsize 0.5 && rm /tmp/wayPreview &
