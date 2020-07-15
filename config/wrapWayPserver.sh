#!/bin/bash

# starts the server with default options and opens the first image

wayPreviewServer "$1" --fit --wsize 0.5 && rm /tmp/wayPreview &
