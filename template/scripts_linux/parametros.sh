#!/bin/sh
. ./nome.sh
export parametros="-std=c99 -pedantic -Wall -lncurses ./libjogoascii.so ../*c -o ../../bin/$nome.bin"