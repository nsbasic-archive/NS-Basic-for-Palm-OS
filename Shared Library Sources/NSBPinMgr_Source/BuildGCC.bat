@echo off
REM  NOTE:  Your PATH must contain the directories where the
REM         following files can be found:
REM
REM         shlib.exe
REM         m68k-palmos-gcc
REM         obj-res
REM         build-prc

cls

set BASENAME=NSBPinMgr
set CREATORID=NPin

if exist %BASENAME%.prc del %BASENAME%.prc
if exist %BASENAME%*.o del %BASENAME%*.o
if exist %BASENAME%*.grc del %BASENAME%*.grc

echo Shlib %BASENAME% - Generating Prototypes and Dispatch Code ...
shlib %BASENAME%
if %ERRORLEVEL% NEQ 0 goto errors found

echo Compiling %BASENAME%.c ...
m68k-palmos-gcc -g -palmos3.5 -c %BASENAME%.c -MD
if %ERRORLEVEL% NEQ 0 goto errors_found

echo Removing startfiles from %BASENAME%.o ...
m68k-palmos-gcc -nostdlib -shared %BASENAME%.o -palmos3.5 -g -o %BASENAME%_tmp.o -lgcc
if %ERRORLEVEL% NEQ 0 goto errors_found

echo Postprocessing %BASENAME%.o
obj-res %BASENAME%_tmp.o
if %ERRORLEVEL% NEQ 0 goto errors_found
if exist *0000.%BASENAME%_tmp.o.grc del *0000.%BASENAME%_tmp.o.grc
if exist libr0000.%BASENAME%_tmp.grc del libr0000.%BASENAME%_tmp.grc
if exist code0001.%BASENAME%_tmp.o.grc ren code0001.%BASENAME%_tmp.o.grc libr0000.%BASENAME%.grc

echo Building %BASENAME%.prc ...
build-prc  -t libr -o %BASENAME%.prc -n "%BASENAME%" -c %CREATORID% libr0000.%BASENAME%.grc 
if %ERRORLEVEL% NEQ 0 goto errors_found
goto no_errors_found

:errors_found
    echo FAILURE:
    echo FAILURE:  Errors found - files have not been generated.
    echo FAILURE:
    goto end_of_file

:no_errors_found
    if exist %BASENAME%.d del %BASENAME%.d
    if exist %BASENAME%*.o del %BASENAME%*.o
    if exist libr0000.%BASENAME%.grc del libr0000.%BASENAME%.grc
    echo SUCCESS:
    echo SUCCESS:  %BASENAME%.prc has been built.
    echo SUCCESS:

:end_of_file

