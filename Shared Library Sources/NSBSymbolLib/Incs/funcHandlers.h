extern Err NSB_SSMLibOpen(UInt16 refNum   )
				SAMPLE_LIB_TRAP(sysLibTrapOpen);
extern Err NSB_SSMLibClose(UInt16 refNum  )
				SAMPLE_LIB_TRAP(sysLibTrapClose);
extern Err NSB_SSMLibSleep(UInt16 refNum  )
				SAMPLE_LIB_TRAP(sysLibTrapSleep);
extern Err NSB_SSMLibWake(UInt16 refNum   )
				SAMPLE_LIB_TRAP(sysLibTrapWake);
extern Err NSB_SSMLibIsPalmSymbolUnit(UInt16 refNum, UInt32 *isit )
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 0);
extern Err NSB_SSMLibCmdScanEnable(UInt16 refNum  )
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 1);
extern Err NSB_SSMLibCmdScanDisable(UInt16 refNum )
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 2);
extern Err NSB_SSMLibCmdScanSetTriggeringModes(UInt16 refNum, UInt32 modes )
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 3);
extern Err NSB_SSMLibCmdScanSetBarcodeEnabled(UInt16 refNum, UInt32 barCode, UInt32 whether )
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 4);
extern Err NSB_SSMLibCmdSendParams(UInt16 refNum, UInt32 beepo )
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 5);
extern Err NSB_SSMLibCmdStartDecode(UInt16 refNum )
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 6);
extern Err NSB_SSMLibCmdStopDecode(UInt16 refNum )
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 7);
extern Err NSB_SSMLibGetDecodedData(UInt16 refNum, UInt8 *buffer )
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 8);
extern Err NSB_SSMLibGetLastScanData(UInt16 refNum, UInt8 *out  )
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 9);
extern Err NSB_SSMLibGetBarType(UInt16 refNum, UInt32 *barType  )
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 10);
extern Err NSB_SSMLibCmdScanLedOn(UInt16 refNum  )
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 11);
extern Err NSB_SSMLibCmdScanLedOff(UInt16 refNum  )
				SAMPLE_LIB_TRAP(sysLibTrapCustom + 12);
