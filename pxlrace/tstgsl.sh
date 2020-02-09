#!/bin/bash
if [ -z $1 ]
then
echo "Usage: $0 rng_name"
echo "Example: $0 taus2"
echo "To see list of RNG names"
echo "$0 ?"
exit 1
fi
GSL_RNG_TYPE="$1"
export GSL_RNG_TYPE
gslrace
