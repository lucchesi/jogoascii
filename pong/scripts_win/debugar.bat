@echo off
call nome.bat
cd ../../bin
gdb %nome%
cd ../%nome%/scripts_win