#!/bin/bash
mkdir -p asm
mkdir -p obj
mkdir -p args
gcc -O2 src/a.c src/b.c -o a.out
gcc -O2 -c src/a.c -o   obj/a.o
gcc -O2 -c src/b.c -o   obj/b.o

echo "ld args to link two object files"
ld -dynamic-linker /lib64/ld-linux-x86-64.so.2 \
    /usr/lib/crt1.o \
    /usr/lib/crti.o \
    obj/a.o \
    obj/b.o \
    -lc \
    /usr/lib/crtn.o

echo "dump crt1.o crti.o crtn.o"
objdump -D /usr/lib/crt1.o -Mintel > asm/crt1.txt
objdump -D /usr/lib/crtn.o -Mintel > asm/crtn.txt
objdump -D /usr/lib/crti.o -Mintel > asm/crti.txt

echo "write ld detailed args to detail.txt"
gcc -Wl,--verbose obj/b.o obj/a.o -o a1.out > args/detail.txt
file obj/a.o && file obj/b.o
objdump -D -Mintel obj/a.o > asm/a.txt
objdump -D -Mintel obj/b.o > asm/b.txt
objdump -D -Mintel a.out > asm/c.txt
