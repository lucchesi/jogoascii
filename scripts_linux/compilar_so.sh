#!/bin/sh
gcc -fpic -shared -g -std=c99 -pedantic -Wall -I/usr/include/ncurses/lncurses ../src/key/*.c ../src/*.c -o ../bin/libjogoascii.so