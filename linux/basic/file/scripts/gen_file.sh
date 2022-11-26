#!/bin/bash
# gen_file.sh -> 1024K

if [ $# -eq 1 ]; then
    count=1024 ** 4
    file=test.txt
fi

for i in {1 .. $count}; do
    echo -n A >> $file
done
