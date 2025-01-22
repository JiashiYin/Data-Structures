#!/bin/bash

# Check if a file is provided
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <file>"
  exit 1
fi

# Input file
file="$1"

# Perform replacements using sed
sed -i \
    -e 's/\bPush_back\b/push_back/g' \
    -e 's/\bErase\b/erase/g' \
    -e 's/\bGetSize\b/size/g' \
    -e 's/\bPop_Front\b/pop_front/g' \
    -e 's/\bClear\b/clear/g' \
    -e 's/\bInsert\b/insert/g' \
    "$file"

# Notify the user
echo "Replacements completed in $file"
