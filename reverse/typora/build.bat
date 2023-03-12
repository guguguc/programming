@echo off
python convert.py
clang++ -c ../hack.cc
clang++ -c ../utils.cc
llvm-rc icon.rc
clang++ hack.o utils.o icon.res -o typora.exe
del hack.o utils.o icon.res