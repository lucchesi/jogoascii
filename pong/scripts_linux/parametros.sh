#!/bin/sh
. ./nome.sh
export parametros="-std=c99 -pedantic -Wall -lm -lncurses ./libjogoascii.so ../*c -o ../../bin/$nome.bin"
