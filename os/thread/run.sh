#!/bin/bash
mkdir -p bin
gcc sum-0.c -o bin/sum-0.out
gcc sum-0.c -O1 -o bin/sum-0-gccO1.out
gcc sum-0.c -O2 -o bin/sum-0-gccO2.out
gcc sum-1.c -o bin/sum-1.out
gcc sum-2.c spinlock.c -o bin/sum-2.out
