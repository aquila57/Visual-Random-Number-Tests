#!/bin/bash
fibogen >coords.txt
#
off_trans -T 0.5,0.5,0.5 cube | \
off_color -v invisible -f invisible >cube_frame.off
#
off_trans -S 1/32 coords.txt | \
off_util - cube_frame.off | \
off_trans -R 30,20,20 | \
antiview -v 0.01
