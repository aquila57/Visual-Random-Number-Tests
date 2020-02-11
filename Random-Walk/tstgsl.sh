#!/bin/bash
if [ -z $1 ]
then
echo "Random walk with GNU Scientific Library"
echo "random number generators"
echo "Usage: $0 generator"
echo "Example: $0 taus2"
echo "For a list of GSL generators, type:"
echo "$0 ?"
exit 1
fi
GSL_RNG_TYPE="$1"
export GSL_RNG_TYPE
gslwlk $1
