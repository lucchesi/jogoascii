@echo off
call nome.bat
cd ../../scripts_win/
call compilar_dll.bat
cd ../%nome%/scripts_win