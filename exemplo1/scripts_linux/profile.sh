#!/bin/sh
. ./parametros.sh
gcc -pg $parametros
cd ../../bin/
./$nome.bin
gprof --brief -q ./$nome.bin
rm gmon.out
cd ../$nome/scripts_linux