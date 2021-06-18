rem This batch file re registers all NSB controls
rem It should be used if NSB gets Error 429 after normal installation.
rem If any message other than 'suceeded' appears, 
rem contact support@Nsbasic.com

regsvr32 /s cmax40.dll
regsvr32 /s cmax40m.dll
regsvr32 /s cmdlgd6.dll
regsvr32 /s comdlg32.ocx
regsvr32 /s emulink.ocx
regsvr32 /s mscomctl.ocx
regsvr32 /s msflxgrd.ocx
regsvr32 /s msvbvm60.dll
regsvr32 /s mswinsck.ocx
regsvr32 /s oleaut32.dll
regsvr32 /s palmcntl.ocx
regsvr32 /s ssubtmr6.dll
regsvr32 /s sysinfo.ocx
regsvr32 /s vbalIcoM.dll
regsvr32 /s vbalIcoM6.dll

