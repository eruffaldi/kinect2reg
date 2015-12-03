#!/bin/bash
ffmpeg -r 30 -pattern_type glob -i "$1/*.jpg" $1/$3