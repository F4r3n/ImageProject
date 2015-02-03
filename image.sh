#!/bin/bash
avconv -i $1 -vsync 1 -r 15 -an -y $2/'videoframe-%3d.jpeg'

