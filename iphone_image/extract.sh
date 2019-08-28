#!/bin/sh

ffmpeg -i $1 -f image2 $2'/'image-%3d.jpeg
