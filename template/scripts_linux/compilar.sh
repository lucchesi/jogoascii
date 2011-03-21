#!/bin/sh
. ./parametros.sh
cp ../../bin/libjogoascii.so ./
gcc -g $parametros
rm ./libjogoascii.so