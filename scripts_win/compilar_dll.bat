@echo off
gcc -g -shared -std=c99 -pedantic -Wall ../src/key/*.c ../src/*.c -o ../bin/jogoascii.dll