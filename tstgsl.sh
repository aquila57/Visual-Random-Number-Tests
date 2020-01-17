#!/bin/bash
if [ -z $1 ]
then
echo "Usage: $0 GSL_RNG_TYPE"
echo "Example: $0 taus2"
echo "Example: $0 mt19937"
echo "Example: $0 ranlxd2"
exit 1
fi
GSL_RNG_TYPE="$1"
export GSL_RNG_TYPE
gsldots $1 | more
