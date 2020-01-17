#!/bin/bash
if [ -z $1 ]
then
echo "Usage: $0 GSL_RNG_Name"
echo "Example: $0 taus2"
echo "Example: $0 mt19937"
echo "Example: $0 ranlxd2"
echo "To see a list of GSL random number generators:"
echo "$0 ?"
exit 1
fi
GSL_RNG_TYPE="$1"
export GSL_RNG_TYPE
gslgen >coords.txt
if [ ! $? = 0 ]
then
exit 1
fi
#
off_trans -T 0.5,0.5,0.5 cube | \
off_color -v invisible -f invisible >cube_frame.off
#
off_trans -S 1/32 coords.txt | \
off_util - cube_frame.off | \
off_trans -R 30,20,20 | \
antiview -v 0.01
