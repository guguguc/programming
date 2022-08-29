#!/bin/bash

# =====================================================
echo "first arg $1"
echo "total arg $*"

# =====================================================
cnt=0
for a in "$@"; do
    echo "arg $cnt -> $a"
    cnt=$((cnt+1))
done
