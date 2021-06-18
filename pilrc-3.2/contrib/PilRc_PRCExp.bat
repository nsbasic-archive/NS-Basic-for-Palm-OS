C:\cygwin\bin\pilrc.exe -ro %1 %TEMP%\pilrc2PRCExpTmp.prc
cd C:\Palm\PRCExplorer
PRCExplorer.exe %TEMP%\pilrc2PRCExpTmp.prc
del %TEMP%\pilrc2PRCExpTmp.prc
exit
