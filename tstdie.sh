#!/bin/bash
if [ -z $1 ]
then
echo "Usage: $0 Dieharder_RNG_number"
echo "Example: $0 208"
echo "To get Dieharder_RNG_number,"
echo "dieharder -g -l"
exit 1
fi
dieharder -g $1 -t 1000000 -o | gendie $1 >coords.txt
#
off_trans -T 0.5,0.5,0.5 cube | \
off_color -v invisible -f invisible >cube_frame.off
#
off_trans -S 1/32 coords.txt | \
off_util - cube_frame.off | \
off_trans -R 30,20,20 | \
antiview -v 0.01
