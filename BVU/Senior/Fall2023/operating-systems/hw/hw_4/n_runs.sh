#!/bin/bash

if [[ $# -ne 2 ]]; then
    echo "Usage: $0 <executable> <num times to run>"
    exit 1
fi

if [[ ! -e $1 ]]; then
    echo "$1 does not exist"
    echo "Usage: $0 <executable> <num times to run>"
    exit 1
fi

if [[ $2 -lt 1 ]]; then
    echo "Num times to run must be greater than 1"
    echo "Usage: $0 <executable> <num times to run>"
    exit 1
fi

i = 0
while [[ $i -lt $2 ]]; do
    echo "run $i"
    ./$1
    let i=i+1
done




