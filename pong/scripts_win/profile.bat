@echo off
call parametros.bat
gcc -pg %parametros%
cd ../../bin
%nome%
gprof --brief -q %nome%.exe
del gmon.out
cd ../%nome%/scripts_win