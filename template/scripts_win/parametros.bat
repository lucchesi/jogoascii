@echo off
call nome.bat

set parametros=-std=c99 -pedantic -Wall ../../bin/jogoascii.dll ../*c -o ../../bin/%nome%