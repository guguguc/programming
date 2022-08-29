#!/bin/bash
mkdir -p bin
gcc -g sum-0.c -o bin/sum-0.out
gcc -g sum-0.c -O1 -o bin/sum-0-gccO1.out
gcc -g sum-0.c -O2 -o bin/sum-0-gccO2.out
gcc -g sum-1.c -o bin/sum-1.out
gcc -g sum-2.c spinlock.c -o bin/sum-2.out
