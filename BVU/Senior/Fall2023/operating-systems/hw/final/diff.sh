#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 directory1 directory2"
    exit 1
fi

directory1="$1"
directory2="$2"

# Check if the provided paths are directories
if [ ! -d "$directory1" ] || [ ! -d "$directory2" ]; then
    echo "Error: Both arguments must be valid directories."
    exit 1
fi

diff -rs "$directory1" "$directory2"

echo "Comparison completed."
