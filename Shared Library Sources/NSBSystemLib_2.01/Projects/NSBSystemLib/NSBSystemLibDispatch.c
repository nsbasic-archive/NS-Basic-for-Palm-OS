//
//    NSBSystemLibDispatch.c
//

#if defined(__GNUC__)
    //***************************************************
    //***  M O D I F Y  *  T H I S  *  S E C T I O N  ***
    //**                                               **
    //**    If you are building this library with      **
    //**    GNU C/PRCTools, you must update the        **
    //**    following CUSTOM_FUNCTION_COUNT            **
    //**    definition.  This value is the count of    **
    //**    "custom" functions in your library.  This  **
    //**    count does not include the 4 "standard"    **
    //**    library functions (LibOpen, LibClose,      **
    //**    LibSleep, or LibWake).  This number is     **
    //**    also the same as the last entry number in  **
    //**    CUSTOM_FUNCTION_ENTRY section below.       **

    #define CUSTOM_FUNCTION_COUNT   233

    //**                                               **
    //***           S E C T I O N  *  E N D           ***
    //***************************************************
#else
    #define CUSTOM_FUNCTION_COUNT   (THIS_TrapEnumLast - sysLibTrapCustom)
#endif

#define START_OF_ENTRIES            (2 * (CUSTOM_FUNCTION_COUNT + 5))
#define STANDARD_FUNCTION_OFFSET(n) (START_OF_ENTRIES + ((n - 1) * 4))
#define CUSTOM_FUNCTION_OFFSET(n)   (START_OF_ENTRIES + ((n + 3) * 4))
#define LIBNAME_OFFSET              CUSTOM_FUNCTION_OFFSET(CUSTOM_FUNCTION_COUNT + 1)

#if defined(__GNUC__)
    #define _VALUE(v)                  #v
    #define DEFINE_VALUE(v)            _VALUE(v)
    #define LIBNAME_ENTRY              "dc.w " DEFINE_VALUE(LIBNAME_OFFSET) ";"
    #define LIBNAME_ADDRESS(name)	   ".asciz	\"" name "\";"  ".even;"::);
    #define STANDARD_FUNCTION_ENTRY(v) "dc.w " DEFINE_VALUE(STANDARD_FUNCTION_OFFSET(v)) ";"
    #define CUSTOM_FUNCTION_ENTRY(v)   "dc.w " DEFINE_VALUE(CUSTOM_FUNCTION_OFFSET(v)) ";"
    #define FUNCTION_ADDRESS(func)     "jmp "  DEFINE_VALUE(func) "(%%pc);"

    static UInt32 start(UInt16 refNum, SysLibTblEntryPtr entryP);
    void jump_table(void);

    static UInt32 start(UInt16 refNum, SysLibTblEntryPtr entryP) {
        entryP->dispatchTblP = (MemPtr) jump_table;
        entryP->globalsP = NULL;
        return 0;

        __asm __volatile("jump_table:;"
#else
    #define LIBNAME_ENTRY              dc.w  LIBNAME_OFFSET
    #define LIBNAME_ADDRESS(name)      dc.b  name
    #define STANDARD_FUNCTION_ENTRY(x) dc.w  STANDARD_FUNCTION_OFFSET(x)
    #define CUSTOM_FUNCTION_ENTRY(x)   dc.w  CUSTOM_FUNCTION_OFFSET(x)
    #define FUNCTION_ADDRESS(func)     jmp   func
    #ifndef PILOT_PRECOMPILED_HEADERS_OFF
        #define PILOT_PRECOMPILED_HEADERS_OFF
    #endif
    #if __PALMOS_TRAPS__
        #define EMULATION_LEVEL EMULATION_NONE
    #endif
    #undef __PALMOS_TRAPS__
    #define __PALMOS_TRAPS__    0
    #define	USE_TRAPS           0

    #include <PalmOS.h>
    //***************************************************
    //***  M O D I F Y  *  T H I S  *  S E C T I O N  ***
    //**                                               **
    //**    Include Application Header file.           **

    #include "NSBSystemLib.h"

    //**                                               **
    //***           S E C T I O N  *  E N D           ***
    //***************************************************

    Err __Startup__(UInt16 refNum, SysLibTblEntryPtr entryP);
    static MemPtr asm jump_table(void);

    Err __Startup__(UInt16 refNum, SysLibTblEntryPtr entryP) {
	    entryP->dispatchTblP = (MemPtr *) jump_table();
        entryP->globalsP = 0;
        return 0;
    }

    static MemPtr asm jump_table(void) {
        LEA     @Table, A0
        RTS
        @Table:
#endif


        // Offset to library name:
        LIBNAME_ENTRY

        // Offset to standard library functions:
        STANDARD_FUNCTION_ENTRY(1)  // THIS_LibOpen
        STANDARD_FUNCTION_ENTRY(2)  // THIS_LibClose
        STANDARD_FUNCTION_ENTRY(3)  // THIS_LibSleep
        STANDARD_FUNCTION_ENTRY(4)  // THIS_LibWake

        // Offset to custom library functions:
        //***************************************************
        //***  M O D I F Y  *  T H I S  *  S E C T I O N  ***
        //**                                               **
        //**    You need to have 1 entry for each "custom" **
        //**    library function in your library.  The     **
        //**    "standard" library functions (LibOpen,     **
        //**    LibClose, LibSleep, and LibWake) are not   **
        //**    considered as "custom" library functions.  **
        //**    Entry numbers begin with 1 and are         **
        //**    incremented by 1 with each entry.  If you  **
        //**    are building this library with GNU C /     **
        //**    PRCTools, you must also update the         **
        //**    CUSTOM_FUNCTION_COUNT definition at the    **
        //**    top of this file.  The function count will **
        //**    be the same as the last entry number.      **

        CUSTOM_FUNCTION_ENTRY(1)  // THIS_Version 
        CUSTOM_FUNCTION_ENTRY(2)  // THIS_CompileInfo 
        CUSTOM_FUNCTION_ENTRY(3)  // THIS_SystemVersion 
        CUSTOM_FUNCTION_ENTRY(4)  // THIS_GlobalVersionMajor 
        CUSTOM_FUNCTION_ENTRY(5)  // THIS_GlobalVersionMinor 
        CUSTOM_FUNCTION_ENTRY(6)  // THIS_GlobalX 
        CUSTOM_FUNCTION_ENTRY(7)  // THIS_GlobalY 
        CUSTOM_FUNCTION_ENTRY(8)  // THIS_GlobalStartX 
        CUSTOM_FUNCTION_ENTRY(9)  // THIS_GlobalStartY 
        CUSTOM_FUNCTION_ENTRY(10)  // THIS_GlobalEndX 
        CUSTOM_FUNCTION_ENTRY(11)  // THIS_GlobalEndY 
        CUSTOM_FUNCTION_ENTRY(12)  // THIS_GlobalStartPos 
        CUSTOM_FUNCTION_ENTRY(13)  // THIS_GlobalEndPos 
        CUSTOM_FUNCTION_ENTRY(14)  // THIS_GlobalWidth 
        CUSTOM_FUNCTION_ENTRY(15)  // THIS_GlobalHeight 
        CUSTOM_FUNCTION_ENTRY(16)  // THIS_GlobalHour 
        CUSTOM_FUNCTION_ENTRY(17)  // THIS_GlobalMinute 
        CUSTOM_FUNCTION_ENTRY(18)  // THIS_SetAlarmReset 
        CUSTOM_FUNCTION_ENTRY(19)  // THIS_SetAlarm 
        CUSTOM_FUNCTION_ENTRY(20)  // THIS_CancelAlarm 
        CUSTOM_FUNCTION_ENTRY(21)  // THIS_GetAlarm 
        CUSTOM_FUNCTION_ENTRY(22)  // THIS_GetAlarmTime 
        CUSTOM_FUNCTION_ENTRY(23)  // THIS_GetAlarmResetTime 
        CUSTOM_FUNCTION_ENTRY(24)  // THIS_GetAlarmResetLimit 
        CUSTOM_FUNCTION_ENTRY(25)  // THIS_GetAlarmCommand 
        CUSTOM_FUNCTION_ENTRY(26)  // THIS_GetAlarmMessage 
        CUSTOM_FUNCTION_ENTRY(27)  // THIS_AlarmLog 
        CUSTOM_FUNCTION_ENTRY(28)  // THIS_AlarmLogAlarmTime 
        CUSTOM_FUNCTION_ENTRY(29)  // THIS_AlarmLogResetTime 
        CUSTOM_FUNCTION_ENTRY(30)  // THIS_AlarmLogResetLimit 
        CUSTOM_FUNCTION_ENTRY(31)  // THIS_AlarmLogResetCount 
        CUSTOM_FUNCTION_ENTRY(32)  // THIS_AlarmLogCommand 
        CUSTOM_FUNCTION_ENTRY(33)  // THIS_AlarmLogMessage 
        CUSTOM_FUNCTION_ENTRY(34)  // THIS_ClearAlarmLog 
        CUSTOM_FUNCTION_ENTRY(35)  // THIS_FindDatabase 
        CUSTOM_FUNCTION_ENTRY(36)  // THIS_DatabaseInfo 
        CUSTOM_FUNCTION_ENTRY(37)  // THIS_DatabaseName 
        CUSTOM_FUNCTION_ENTRY(38)  // THIS_DatabaseAttributes 
        CUSTOM_FUNCTION_ENTRY(39)  // THIS_DatabaseVersion 
        CUSTOM_FUNCTION_ENTRY(40)  // THIS_DatabaseCreationDate 
        CUSTOM_FUNCTION_ENTRY(41)  // THIS_DatabaseModificationDate 
        CUSTOM_FUNCTION_ENTRY(42)  // THIS_DatabaseBackupDate 
        CUSTOM_FUNCTION_ENTRY(43)  // THIS_DatabaseModificationNumber 
        CUSTOM_FUNCTION_ENTRY(44)  // THIS_DatabaseAppInfoID 
        CUSTOM_FUNCTION_ENTRY(45)  // THIS_DatabaseSortInfoID 
        CUSTOM_FUNCTION_ENTRY(46)  // THIS_DatabaseType 
        CUSTOM_FUNCTION_ENTRY(47)  // THIS_DatabaseCreatorID 
        CUSTOM_FUNCTION_ENTRY(48)  // THIS_DatabaseTotalSize 
        CUSTOM_FUNCTION_ENTRY(49)  // THIS_DatabaseNumRecords 
        CUSTOM_FUNCTION_ENTRY(50)  // THIS_DatabaseDataSize 
        CUSTOM_FUNCTION_ENTRY(51)  // THIS_DeleteDatabase 
        CUSTOM_FUNCTION_ENTRY(52)  // THIS_GetNextDatabaseByTypeCreator 
        CUSTOM_FUNCTION_ENTRY(53)  // THIS_DatabaseCardNo 
        CUSTOM_FUNCTION_ENTRY(54)  // THIS_NumDatabases 
        CUSTOM_FUNCTION_ENTRY(55)  // THIS_NumCards 
        CUSTOM_FUNCTION_ENTRY(56)  // THIS_GetDatabase 
        CUSTOM_FUNCTION_ENTRY(57)  // THIS_SetDatabaseName 
        CUSTOM_FUNCTION_ENTRY(58)  // THIS_SetDatabaseAttributes 
        CUSTOM_FUNCTION_ENTRY(59)  // THIS_SetDatabaseVersion 
        CUSTOM_FUNCTION_ENTRY(60)  // THIS_SetDatabaseCreationDate 
        CUSTOM_FUNCTION_ENTRY(61)  // THIS_SetDatabaseModificationDate 
        CUSTOM_FUNCTION_ENTRY(62)  // THIS_SetDatabaseBackupDate 
        CUSTOM_FUNCTION_ENTRY(63)  // THIS_SetDatabaseModificationNumber 
        CUSTOM_FUNCTION_ENTRY(64)  // THIS_SetDatabaseAppInfoID 
        CUSTOM_FUNCTION_ENTRY(65)  // THIS_SetDatabaseSortInfoID 
        CUSTOM_FUNCTION_ENTRY(66)  // THIS_SetDatabaseType 
        CUSTOM_FUNCTION_ENTRY(67)  // THIS_SetDatabaseCreatorID 
        CUSTOM_FUNCTION_ENTRY(68)  // THIS_GetEvent 
        CUSTOM_FUNCTION_ENTRY(69)  // THIS_SysHandleEvent 
        CUSTOM_FUNCTION_ENTRY(70)  // THIS_FlushEvents 
        CUSTOM_FUNCTION_ENTRY(71)  // THIS_KeyEventChr 
        CUSTOM_FUNCTION_ENTRY(72)  // THIS_KeyEventKeyCode 
        CUSTOM_FUNCTION_ENTRY(73)  // THIS_KeyEventModifiers 
        CUSTOM_FUNCTION_ENTRY(74)  // THIS_ControlHitControl 
        CUSTOM_FUNCTION_ENTRY(75)  // THIS_FieldCopy 
        CUSTOM_FUNCTION_ENTRY(76)  // THIS_FieldCut 
        CUSTOM_FUNCTION_ENTRY(77)  // THIS_FieldInsert 
        CUSTOM_FUNCTION_ENTRY(78)  // THIS_FieldPaste 
        CUSTOM_FUNCTION_ENTRY(79)  // THIS_FieldUndo 
        CUSTOM_FUNCTION_ENTRY(80)  // THIS_FieldGetInsPtPosition 
        CUSTOM_FUNCTION_ENTRY(81)  // THIS_FieldGetSelection 
        CUSTOM_FUNCTION_ENTRY(82)  // THIS_FieldAnyDirty 
        CUSTOM_FUNCTION_ENTRY(83)  // THIS_FieldDirty 
        CUSTOM_FUNCTION_ENTRY(84)  // THIS_FieldSetDirty 
        CUSTOM_FUNCTION_ENTRY(85)  // THIS_FieldSetAllDirty 
        CUSTOM_FUNCTION_ENTRY(86)  // THIS_FieldSetSelection 
        CUSTOM_FUNCTION_ENTRY(87)  // THIS_FieldSetInsertionPoint 
        CUSTOM_FUNCTION_ENTRY(88)  // THIS_FieldSetInsPtPosition 
        CUSTOM_FUNCTION_ENTRY(89)  // THIS_FieldGetAttributes 
        CUSTOM_FUNCTION_ENTRY(90)  // THIS_FieldSetAttributes 
        CUSTOM_FUNCTION_ENTRY(91)  // THIS_FieldGetFont 
        CUSTOM_FUNCTION_ENTRY(92)  // THIS_FieldSetFont 
        CUSTOM_FUNCTION_ENTRY(93)  // THIS_FieldGetScrollPosition 
        CUSTOM_FUNCTION_ENTRY(94)  // THIS_FieldSetScrollPosition 
        CUSTOM_FUNCTION_ENTRY(95)  // THIS_FieldGetScrollValues 
        CUSTOM_FUNCTION_ENTRY(96)  // THIS_FieldGetVisibleLines 
        CUSTOM_FUNCTION_ENTRY(97)  // THIS_FieldGetNumberOfBlankLines 
        CUSTOM_FUNCTION_ENTRY(98)  // THIS_FieldScrollable 
        CUSTOM_FUNCTION_ENTRY(99)  // THIS_FieldScrollField 
        CUSTOM_FUNCTION_ENTRY(100)  // THIS_FieldSetBounds 
        CUSTOM_FUNCTION_ENTRY(101)  // THIS_FormGetNumberOfObjects 
        CUSTOM_FUNCTION_ENTRY(102)  // THIS_FormGetObjectBounds 
        CUSTOM_FUNCTION_ENTRY(103)  // THIS_FormGetObjectPosition 
        CUSTOM_FUNCTION_ENTRY(104)  // THIS_FormGetObjectType 
        CUSTOM_FUNCTION_ENTRY(105)  // THIS_FormSetObjectPosition 
        CUSTOM_FUNCTION_ENTRY(106)  // THIS_FormSetObjectBounds 
        CUSTOM_FUNCTION_ENTRY(107)  // THIS_FormGetTitle 
        CUSTOM_FUNCTION_ENTRY(108)  // THIS_FormReplaceTitle 
        CUSTOM_FUNCTION_ENTRY(109)  // THIS_ListGetTopItem 
        CUSTOM_FUNCTION_ENTRY(110)  // THIS_ListSetTopItem 
        CUSTOM_FUNCTION_ENTRY(111)  // THIS_ListGetVisibleItems 
        CUSTOM_FUNCTION_ENTRY(112)  // THIS_ListScrollList 
        CUSTOM_FUNCTION_ENTRY(113)  // THIS_FontGetFont 
        CUSTOM_FUNCTION_ENTRY(114)  // THIS_FontSetFont 
        CUSTOM_FUNCTION_ENTRY(115)  // THIS_FontSelect 
        CUSTOM_FUNCTION_ENTRY(116)  // THIS_FontCharWidth 
        CUSTOM_FUNCTION_ENTRY(117)  // THIS_FontCharsWidth 
        CUSTOM_FUNCTION_ENTRY(118)  // THIS_FontWidthToOffset 
        CUSTOM_FUNCTION_ENTRY(119)  // THIS_FontCharsInWidth 
        CUSTOM_FUNCTION_ENTRY(120)  // THIS_FontWordWrap 
        CUSTOM_FUNCTION_ENTRY(121)  // THIS_SyncUserName 
        CUSTOM_FUNCTION_ENTRY(122)  // THIS_SuccessfulSync 
        CUSTOM_FUNCTION_ENTRY(123)  // THIS_LastSync 
        CUSTOM_FUNCTION_ENTRY(124)  // THIS_LocalizeNumber 
        CUSTOM_FUNCTION_ENTRY(125)  // THIS_DelocalizeNumber 
        CUSTOM_FUNCTION_ENTRY(126)  // THIS_LocalizeDate 
        CUSTOM_FUNCTION_ENTRY(127)  // THIS_GetAppPreferences 
        CUSTOM_FUNCTION_ENTRY(128)  // THIS_SetAppPreferences 
        CUSTOM_FUNCTION_ENTRY(129)  // THIS_GetSysPreference 
        CUSTOM_FUNCTION_ENTRY(130)  // THIS_SetSysPreference 
        CUSTOM_FUNCTION_ENTRY(131)  // THIS_ProgressStartDialog 
        CUSTOM_FUNCTION_ENTRY(132)  // THIS_ProgressStopDialog 
        CUSTOM_FUNCTION_ENTRY(133)  // THIS_ProgressUpdateDialog 
        CUSTOM_FUNCTION_ENTRY(134)  // THIS_ProgressUserCancel 
        CUSTOM_FUNCTION_ENTRY(135)  // THIS_ProgressPercent 
        CUSTOM_FUNCTION_ENTRY(136)  // THIS_ProgressPercentString 
        CUSTOM_FUNCTION_ENTRY(137)  // THIS_String4ToInt 
        CUSTOM_FUNCTION_ENTRY(138)  // THIS_IntToString4 
        CUSTOM_FUNCTION_ENTRY(139)  // THIS_DelimitedItem 
        CUSTOM_FUNCTION_ENTRY(140)  // THIS_FixedWidthString 
        CUSTOM_FUNCTION_ENTRY(141)  // THIS_NormalSpacedString 
        CUSTOM_FUNCTION_ENTRY(142)  // THIS_SelectOneTime 
        CUSTOM_FUNCTION_ENTRY(143)  // THIS_IncrementSystemTime 
        CUSTOM_FUNCTION_ENTRY(144)  // THIS_SystemTime 
        CUSTOM_FUNCTION_ENTRY(145)  // THIS_StringDateTime 
        CUSTOM_FUNCTION_ENTRY(146)  // THIS_StringDate 
        CUSTOM_FUNCTION_ENTRY(147)  // THIS_StringTime 
        CUSTOM_FUNCTION_ENTRY(148)  // THIS_PostEvent 
        CUSTOM_FUNCTION_ENTRY(149)  // THIS_FormGetFocus 
        CUSTOM_FUNCTION_ENTRY(150)  // THIS_FieldGetTextLength 
        CUSTOM_FUNCTION_ENTRY(151)  // THIS_RandomNumber 
        CUSTOM_FUNCTION_ENTRY(152)  // THIS_ResetAutoOffTimer 
        CUSTOM_FUNCTION_ENTRY(153)  // THIS_SetAutoOffTime 
        CUSTOM_FUNCTION_ENTRY(154)  // THIS_ProgramVersionString 
        CUSTOM_FUNCTION_ENTRY(155)  // THIS_DynamicHeapSize 
        CUSTOM_FUNCTION_ENTRY(156)  // THIS_DynamicHeapFree 
        CUSTOM_FUNCTION_ENTRY(157)  // THIS_DynamicHeapMaxChunk 
        CUSTOM_FUNCTION_ENTRY(158)  // THIS_SortInit 
        CUSTOM_FUNCTION_ENTRY(159)  // THIS_SortAddString 
        CUSTOM_FUNCTION_ENTRY(160)  // THIS_SortAddInteger 
        CUSTOM_FUNCTION_ENTRY(161)  // THIS_SortAddDouble 
        CUSTOM_FUNCTION_ENTRY(162)  // THIS_SortGetString 
        CUSTOM_FUNCTION_ENTRY(163)  // THIS_SortGetInteger 
        CUSTOM_FUNCTION_ENTRY(164)  // THIS_SortGetDouble 
        CUSTOM_FUNCTION_ENTRY(165)  // THIS_SortQSort 
        CUSTOM_FUNCTION_ENTRY(166)  // THIS_SortInsertionSort 
        CUSTOM_FUNCTION_ENTRY(167)  // THIS_ListQSort 
        CUSTOM_FUNCTION_ENTRY(168)  // THIS_ListInsertionSort 
        CUSTOM_FUNCTION_ENTRY(169)  // THIS_FormGetAllObjectTypes 
        CUSTOM_FUNCTION_ENTRY(170)  // THIS_FieldClearAll 
        CUSTOM_FUNCTION_ENTRY(171)  // THIS_ObjectWithPoint 
        CUSTOM_FUNCTION_ENTRY(172)  // THIS_ANDInt 
        CUSTOM_FUNCTION_ENTRY(173)  // THIS_ORInt 
        CUSTOM_FUNCTION_ENTRY(174)  // THIS_XORInt 
        CUSTOM_FUNCTION_ENTRY(175)  // THIS_OnesComplement 
        CUSTOM_FUNCTION_ENTRY(176)  // THIS_BitValue 
        CUSTOM_FUNCTION_ENTRY(177)  // THIS_BitsValue 
        CUSTOM_FUNCTION_ENTRY(178)  // THIS_SetBitValue 
        CUSTOM_FUNCTION_ENTRY(179)  // THIS_SetBitsValue 
        CUSTOM_FUNCTION_ENTRY(180)  // THIS_IntToHex 
        CUSTOM_FUNCTION_ENTRY(181)  // THIS_HexToInt 
        CUSTOM_FUNCTION_ENTRY(182)  // THIS_IntToBin 
        CUSTOM_FUNCTION_ENTRY(183)  // THIS_BinToInt 
        CUSTOM_FUNCTION_ENTRY(184)  // THIS_GetSupportedDepths 
        CUSTOM_FUNCTION_ENTRY(185)  // THIS_DepthSupported 
        CUSTOM_FUNCTION_ENTRY(186)  // THIS_ColorSupported 
        CUSTOM_FUNCTION_ENTRY(187)  // THIS_SetDepth 
        CUSTOM_FUNCTION_ENTRY(188)  // THIS_SetColor 
        CUSTOM_FUNCTION_ENTRY(189)  // THIS_SaveScreenMode 
        CUSTOM_FUNCTION_ENTRY(190)  // THIS_RestoreScreenMode 
        CUSTOM_FUNCTION_ENTRY(191)  // THIS_CurrentDepth 
        CUSTOM_FUNCTION_ENTRY(192)  // THIS_CurrentColor 
        CUSTOM_FUNCTION_ENTRY(193)  // THIS_SetToDefaults 
        CUSTOM_FUNCTION_ENTRY(194)  // THIS_DefaultDepth 
        CUSTOM_FUNCTION_ENTRY(195)  // THIS_DefaultColor 
        CUSTOM_FUNCTION_ENTRY(196)  // THIS_GetTableEntryIndex 
        CUSTOM_FUNCTION_ENTRY(197)  // THIS_GetTableEntryRGB 
        CUSTOM_FUNCTION_ENTRY(198)  // THIS_GetRGBIndex 
        CUSTOM_FUNCTION_ENTRY(199)  // THIS_GetRGBRed 
        CUSTOM_FUNCTION_ENTRY(200)  // THIS_GetRGBGreen 
        CUSTOM_FUNCTION_ENTRY(201)  // THIS_GetRGBBlue 
        CUSTOM_FUNCTION_ENTRY(202)  // THIS_SetTableEntryIndex 
        CUSTOM_FUNCTION_ENTRY(203)  // THIS_SetTableEntryRGB 
        CUSTOM_FUNCTION_ENTRY(204)  // THIS_BrightnessAdjust 
        CUSTOM_FUNCTION_ENTRY(205)  // THIS_ContrastAdjust 
        CUSTOM_FUNCTION_ENTRY(206)  // THIS_PickColorIndex 
        CUSTOM_FUNCTION_ENTRY(207)  // THIS_PickColorRGB 
        CUSTOM_FUNCTION_ENTRY(208)  // THIS_IndexToRGB 
        CUSTOM_FUNCTION_ENTRY(209)  // THIS_RGBToIndex 
        CUSTOM_FUNCTION_ENTRY(210)  // THIS_SetForeColor 
        CUSTOM_FUNCTION_ENTRY(211)  // THIS_SetBackColor 
        CUSTOM_FUNCTION_ENTRY(212)  // THIS_SetTextColor 
        CUSTOM_FUNCTION_ENTRY(213)  // THIS_DrawLine 
        CUSTOM_FUNCTION_ENTRY(214)  // THIS_DrawGrayLine 
        CUSTOM_FUNCTION_ENTRY(215)  // THIS_EraseLine 
        CUSTOM_FUNCTION_ENTRY(216)  // THIS_InvertLine 
        CUSTOM_FUNCTION_ENTRY(217)  // THIS_DrawPixel 
        CUSTOM_FUNCTION_ENTRY(218)  // THIS_ErasePixel 
        CUSTOM_FUNCTION_ENTRY(219)  // THIS_InvertPixel 
        CUSTOM_FUNCTION_ENTRY(220)  // THIS_GetPixel 
        CUSTOM_FUNCTION_ENTRY(221)  // THIS_ScreenLock 
        CUSTOM_FUNCTION_ENTRY(222)  // THIS_ScreenUnlock 
        CUSTOM_FUNCTION_ENTRY(223)  // THIS_WinSaveBits 
        CUSTOM_FUNCTION_ENTRY(224)  // THIS_WinRestoreBits 
        CUSTOM_FUNCTION_ENTRY(225)  // THIS_SetSleepEvent 
        CUSTOM_FUNCTION_ENTRY(226)  // THIS_SetWakeEvent 
        CUSTOM_FUNCTION_ENTRY(227)  // THIS_GetSleepEvent 
        CUSTOM_FUNCTION_ENTRY(228)  // THIS_GetWakeEvent 
        CUSTOM_FUNCTION_ENTRY(229)  // THIS_GetSleepEventTime 
        CUSTOM_FUNCTION_ENTRY(230)  // THIS_GetWakeEventTime 
        CUSTOM_FUNCTION_ENTRY(231)  // THIS_EncryptDESString 
        CUSTOM_FUNCTION_ENTRY(232)  // THIS_DecryptDESString 
        CUSTOM_FUNCTION_ENTRY(233)  // THIS_SetDESKey 

        //**                                               **
        //***           S E C T I O N  *  E N D           ***
        //***************************************************

        // JMP addresses to standard library functions:
        FUNCTION_ADDRESS(THIS_LibOpen)
        FUNCTION_ADDRESS(THIS_LibClose)
        FUNCTION_ADDRESS(THIS_LibSleep)
        FUNCTION_ADDRESS(THIS_LibWake)

        //***************************************************
        //***  M O D I F Y  *  T H I S  *  S E C T I O N  ***
        //**                                               **
        //**    You need to have 1 entry for each "custom" **
        //**    library function in your library.  The     **
        //**    "standard" library functions (LibOpen,     **
        //**    LibClose, LibSleep, and LibWake) are not   **
        //**    considered as "custom" library functions.  **
        //**    Entries are added in the same order as     **
        //**    as the corresponding function TRAP enums.  **

        FUNCTION_ADDRESS(THIS_Version)
        FUNCTION_ADDRESS(THIS_CompileInfo)
        FUNCTION_ADDRESS(THIS_SystemVersion)
        FUNCTION_ADDRESS(THIS_GlobalVersionMajor)
        FUNCTION_ADDRESS(THIS_GlobalVersionMinor)
        FUNCTION_ADDRESS(THIS_GlobalX)
        FUNCTION_ADDRESS(THIS_GlobalY)
        FUNCTION_ADDRESS(THIS_GlobalStartX)
        FUNCTION_ADDRESS(THIS_GlobalStartY)
        FUNCTION_ADDRESS(THIS_GlobalEndX)
        FUNCTION_ADDRESS(THIS_GlobalEndY)
        FUNCTION_ADDRESS(THIS_GlobalStartPos)
        FUNCTION_ADDRESS(THIS_GlobalEndPos)
        FUNCTION_ADDRESS(THIS_GlobalWidth)
        FUNCTION_ADDRESS(THIS_GlobalHeight)
        FUNCTION_ADDRESS(THIS_GlobalHour)
        FUNCTION_ADDRESS(THIS_GlobalMinute)
        FUNCTION_ADDRESS(THIS_SetAlarmReset)
        FUNCTION_ADDRESS(THIS_SetAlarm)
        FUNCTION_ADDRESS(THIS_CancelAlarm)
        FUNCTION_ADDRESS(THIS_GetAlarm)
        FUNCTION_ADDRESS(THIS_GetAlarmTime)
        FUNCTION_ADDRESS(THIS_GetAlarmResetTime)
        FUNCTION_ADDRESS(THIS_GetAlarmResetLimit)
        FUNCTION_ADDRESS(THIS_GetAlarmCommand)
        FUNCTION_ADDRESS(THIS_GetAlarmMessage)
        FUNCTION_ADDRESS(THIS_AlarmLog)
        FUNCTION_ADDRESS(THIS_AlarmLogAlarmTime)
        FUNCTION_ADDRESS(THIS_AlarmLogResetTime)
        FUNCTION_ADDRESS(THIS_AlarmLogResetLimit)
        FUNCTION_ADDRESS(THIS_AlarmLogResetCount)
        FUNCTION_ADDRESS(THIS_AlarmLogCommand)
        FUNCTION_ADDRESS(THIS_AlarmLogMessage)
        FUNCTION_ADDRESS(THIS_ClearAlarmLog)
        FUNCTION_ADDRESS(THIS_FindDatabase)
        FUNCTION_ADDRESS(THIS_DatabaseInfo)
        FUNCTION_ADDRESS(THIS_DatabaseName)
        FUNCTION_ADDRESS(THIS_DatabaseAttributes)
        FUNCTION_ADDRESS(THIS_DatabaseVersion)
        FUNCTION_ADDRESS(THIS_DatabaseCreationDate)
        FUNCTION_ADDRESS(THIS_DatabaseModificationDate)
        FUNCTION_ADDRESS(THIS_DatabaseBackupDate)
        FUNCTION_ADDRESS(THIS_DatabaseModificationNumber)
        FUNCTION_ADDRESS(THIS_DatabaseAppInfoID)
        FUNCTION_ADDRESS(THIS_DatabaseSortInfoID)
        FUNCTION_ADDRESS(THIS_DatabaseType)
        FUNCTION_ADDRESS(THIS_DatabaseCreatorID)
        FUNCTION_ADDRESS(THIS_DatabaseTotalSize)
        FUNCTION_ADDRESS(THIS_DatabaseNumRecords)
        FUNCTION_ADDRESS(THIS_DatabaseDataSize)
        FUNCTION_ADDRESS(THIS_DeleteDatabase)
        FUNCTION_ADDRESS(THIS_GetNextDatabaseByTypeCreator)
        FUNCTION_ADDRESS(THIS_DatabaseCardNo)
        FUNCTION_ADDRESS(THIS_NumDatabases)
        FUNCTION_ADDRESS(THIS_NumCards)
        FUNCTION_ADDRESS(THIS_GetDatabase)
        FUNCTION_ADDRESS(THIS_SetDatabaseName)
        FUNCTION_ADDRESS(THIS_SetDatabaseAttributes)
        FUNCTION_ADDRESS(THIS_SetDatabaseVersion)
        FUNCTION_ADDRESS(THIS_SetDatabaseCreationDate)
        FUNCTION_ADDRESS(THIS_SetDatabaseModificationDate)
        FUNCTION_ADDRESS(THIS_SetDatabaseBackupDate)
        FUNCTION_ADDRESS(THIS_SetDatabaseModificationNumber)
        FUNCTION_ADDRESS(THIS_SetDatabaseAppInfoID)
        FUNCTION_ADDRESS(THIS_SetDatabaseSortInfoID)
        FUNCTION_ADDRESS(THIS_SetDatabaseType)
        FUNCTION_ADDRESS(THIS_SetDatabaseCreatorID)
        FUNCTION_ADDRESS(THIS_GetEvent)
        FUNCTION_ADDRESS(THIS_SysHandleEvent)
        FUNCTION_ADDRESS(THIS_FlushEvents)
        FUNCTION_ADDRESS(THIS_KeyEventChr)
        FUNCTION_ADDRESS(THIS_KeyEventKeyCode)
        FUNCTION_ADDRESS(THIS_KeyEventModifiers)
        FUNCTION_ADDRESS(THIS_ControlHitControl)
        FUNCTION_ADDRESS(THIS_FieldCopy)
        FUNCTION_ADDRESS(THIS_FieldCut)
        FUNCTION_ADDRESS(THIS_FieldInsert)
        FUNCTION_ADDRESS(THIS_FieldPaste)
        FUNCTION_ADDRESS(THIS_FieldUndo)
        FUNCTION_ADDRESS(THIS_FieldGetInsPtPosition)
        FUNCTION_ADDRESS(THIS_FieldGetSelection)
        FUNCTION_ADDRESS(THIS_FieldAnyDirty)
        FUNCTION_ADDRESS(THIS_FieldDirty)
        FUNCTION_ADDRESS(THIS_FieldSetDirty)
        FUNCTION_ADDRESS(THIS_FieldSetAllDirty)
        FUNCTION_ADDRESS(THIS_FieldSetSelection)
        FUNCTION_ADDRESS(THIS_FieldSetInsertionPoint)
        FUNCTION_ADDRESS(THIS_FieldSetInsPtPosition)
        FUNCTION_ADDRESS(THIS_FieldGetAttributes)
        FUNCTION_ADDRESS(THIS_FieldSetAttributes)
        FUNCTION_ADDRESS(THIS_FieldGetFont)
        FUNCTION_ADDRESS(THIS_FieldSetFont)
        FUNCTION_ADDRESS(THIS_FieldGetScrollPosition)
        FUNCTION_ADDRESS(THIS_FieldSetScrollPosition)
        FUNCTION_ADDRESS(THIS_FieldGetScrollValues)
        FUNCTION_ADDRESS(THIS_FieldGetVisibleLines)
        FUNCTION_ADDRESS(THIS_FieldGetNumberOfBlankLines)
        FUNCTION_ADDRESS(THIS_FieldScrollable)
        FUNCTION_ADDRESS(THIS_FieldScrollField)
        FUNCTION_ADDRESS(THIS_FieldSetBounds)
        FUNCTION_ADDRESS(THIS_FormGetNumberOfObjects)
        FUNCTION_ADDRESS(THIS_FormGetObjectBounds)
        FUNCTION_ADDRESS(THIS_FormGetObjectPosition)
        FUNCTION_ADDRESS(THIS_FormGetObjectType)
        FUNCTION_ADDRESS(THIS_FormSetObjectPosition)
        FUNCTION_ADDRESS(THIS_FormSetObjectBounds)
        FUNCTION_ADDRESS(THIS_FormGetTitle)
        FUNCTION_ADDRESS(THIS_FormReplaceTitle)
        FUNCTION_ADDRESS(THIS_ListGetTopItem)
        FUNCTION_ADDRESS(THIS_ListSetTopItem)
        FUNCTION_ADDRESS(THIS_ListGetVisibleItems)
        FUNCTION_ADDRESS(THIS_ListScrollList)
        FUNCTION_ADDRESS(THIS_FontGetFont)
        FUNCTION_ADDRESS(THIS_FontSetFont)
        FUNCTION_ADDRESS(THIS_FontSelect)
        FUNCTION_ADDRESS(THIS_FontCharWidth)
        FUNCTION_ADDRESS(THIS_FontCharsWidth)
        FUNCTION_ADDRESS(THIS_FontWidthToOffset)
        FUNCTION_ADDRESS(THIS_FontCharsInWidth)
        FUNCTION_ADDRESS(THIS_FontWordWrap)
        FUNCTION_ADDRESS(THIS_SyncUserName)
        FUNCTION_ADDRESS(THIS_SuccessfulSync)
        FUNCTION_ADDRESS(THIS_LastSync)
        FUNCTION_ADDRESS(THIS_LocalizeNumber)
        FUNCTION_ADDRESS(THIS_DelocalizeNumber)
        FUNCTION_ADDRESS(THIS_LocalizeDate)
        FUNCTION_ADDRESS(THIS_GetAppPreferences)
        FUNCTION_ADDRESS(THIS_SetAppPreferences)
        FUNCTION_ADDRESS(THIS_GetSysPreference)
        FUNCTION_ADDRESS(THIS_SetSysPreference)
        FUNCTION_ADDRESS(THIS_ProgressStartDialog)
        FUNCTION_ADDRESS(THIS_ProgressStopDialog)
        FUNCTION_ADDRESS(THIS_ProgressUpdateDialog)
        FUNCTION_ADDRESS(THIS_ProgressUserCancel)
        FUNCTION_ADDRESS(THIS_ProgressPercent)
        FUNCTION_ADDRESS(THIS_ProgressPercentString)
        FUNCTION_ADDRESS(THIS_String4ToInt)
        FUNCTION_ADDRESS(THIS_IntToString4)
        FUNCTION_ADDRESS(THIS_DelimitedItem)
        FUNCTION_ADDRESS(THIS_FixedWidthString)
        FUNCTION_ADDRESS(THIS_NormalSpacedString)
        FUNCTION_ADDRESS(THIS_SelectOneTime)
        FUNCTION_ADDRESS(THIS_IncrementSystemTime)
        FUNCTION_ADDRESS(THIS_SystemTime)
        FUNCTION_ADDRESS(THIS_StringDateTime)
        FUNCTION_ADDRESS(THIS_StringDate)
        FUNCTION_ADDRESS(THIS_StringTime)
        FUNCTION_ADDRESS(THIS_PostEvent)
        FUNCTION_ADDRESS(THIS_FormGetFocus)
        FUNCTION_ADDRESS(THIS_FieldGetTextLength)
        FUNCTION_ADDRESS(THIS_RandomNumber)
        FUNCTION_ADDRESS(THIS_ResetAutoOffTimer)
        FUNCTION_ADDRESS(THIS_SetAutoOffTime)
        FUNCTION_ADDRESS(THIS_ProgramVersionString)
        FUNCTION_ADDRESS(THIS_DynamicHeapSize)
        FUNCTION_ADDRESS(THIS_DynamicHeapFree)
        FUNCTION_ADDRESS(THIS_DynamicHeapMaxChunk)
        FUNCTION_ADDRESS(THIS_SortInit)
        FUNCTION_ADDRESS(THIS_SortAddString)
        FUNCTION_ADDRESS(THIS_SortAddInteger)
        FUNCTION_ADDRESS(THIS_SortAddDouble)
        FUNCTION_ADDRESS(THIS_SortGetString)
        FUNCTION_ADDRESS(THIS_SortGetInteger)
        FUNCTION_ADDRESS(THIS_SortGetDouble)
        FUNCTION_ADDRESS(THIS_SortQSort)
        FUNCTION_ADDRESS(THIS_SortInsertionSort)
        FUNCTION_ADDRESS(THIS_ListQSort)
        FUNCTION_ADDRESS(THIS_ListInsertionSort)
        FUNCTION_ADDRESS(THIS_FormGetAllObjectTypes)
        FUNCTION_ADDRESS(THIS_FieldClearAll)
        FUNCTION_ADDRESS(THIS_ObjectWithPoint)
        FUNCTION_ADDRESS(THIS_ANDInt)
        FUNCTION_ADDRESS(THIS_ORInt)
        FUNCTION_ADDRESS(THIS_XORInt)
        FUNCTION_ADDRESS(THIS_OnesComplement)
        FUNCTION_ADDRESS(THIS_BitValue)
        FUNCTION_ADDRESS(THIS_BitsValue)
        FUNCTION_ADDRESS(THIS_SetBitValue)
        FUNCTION_ADDRESS(THIS_SetBitsValue)
        FUNCTION_ADDRESS(THIS_IntToHex)
        FUNCTION_ADDRESS(THIS_HexToInt)
        FUNCTION_ADDRESS(THIS_IntToBin)
        FUNCTION_ADDRESS(THIS_BinToInt)
        FUNCTION_ADDRESS(THIS_GetSupportedDepths)
        FUNCTION_ADDRESS(THIS_DepthSupported)
        FUNCTION_ADDRESS(THIS_ColorSupported)
        FUNCTION_ADDRESS(THIS_SetDepth)
        FUNCTION_ADDRESS(THIS_SetColor)
        FUNCTION_ADDRESS(THIS_SaveScreenMode)
        FUNCTION_ADDRESS(THIS_RestoreScreenMode)
        FUNCTION_ADDRESS(THIS_CurrentDepth)
        FUNCTION_ADDRESS(THIS_CurrentColor)
        FUNCTION_ADDRESS(THIS_SetToDefaults)
        FUNCTION_ADDRESS(THIS_DefaultDepth)
        FUNCTION_ADDRESS(THIS_DefaultColor)
        FUNCTION_ADDRESS(THIS_GetTableEntryIndex)
        FUNCTION_ADDRESS(THIS_GetTableEntryRGB)
        FUNCTION_ADDRESS(THIS_GetRGBIndex)
        FUNCTION_ADDRESS(THIS_GetRGBRed)
        FUNCTION_ADDRESS(THIS_GetRGBGreen)
        FUNCTION_ADDRESS(THIS_GetRGBBlue)
        FUNCTION_ADDRESS(THIS_SetTableEntryIndex)
        FUNCTION_ADDRESS(THIS_SetTableEntryRGB)
        FUNCTION_ADDRESS(THIS_BrightnessAdjust)
        FUNCTION_ADDRESS(THIS_ContrastAdjust)
        FUNCTION_ADDRESS(THIS_PickColorIndex)
        FUNCTION_ADDRESS(THIS_PickColorRGB)
        FUNCTION_ADDRESS(THIS_IndexToRGB)
        FUNCTION_ADDRESS(THIS_RGBToIndex)
        FUNCTION_ADDRESS(THIS_SetForeColor)
        FUNCTION_ADDRESS(THIS_SetBackColor)
        FUNCTION_ADDRESS(THIS_SetTextColor)
        FUNCTION_ADDRESS(THIS_DrawLine)
        FUNCTION_ADDRESS(THIS_DrawGrayLine)
        FUNCTION_ADDRESS(THIS_EraseLine)
        FUNCTION_ADDRESS(THIS_InvertLine)
        FUNCTION_ADDRESS(THIS_DrawPixel)
        FUNCTION_ADDRESS(THIS_ErasePixel)
        FUNCTION_ADDRESS(THIS_InvertPixel)
        FUNCTION_ADDRESS(THIS_GetPixel)
        FUNCTION_ADDRESS(THIS_ScreenLock)
        FUNCTION_ADDRESS(THIS_ScreenUnlock)
        FUNCTION_ADDRESS(THIS_WinSaveBits)
        FUNCTION_ADDRESS(THIS_WinRestoreBits)
        FUNCTION_ADDRESS(THIS_SetSleepEvent)
        FUNCTION_ADDRESS(THIS_SetWakeEvent)
        FUNCTION_ADDRESS(THIS_GetSleepEvent)
        FUNCTION_ADDRESS(THIS_GetWakeEvent)
        FUNCTION_ADDRESS(THIS_GetSleepEventTime)
        FUNCTION_ADDRESS(THIS_GetWakeEventTime)
        FUNCTION_ADDRESS(THIS_EncryptDESString)
        FUNCTION_ADDRESS(THIS_DecryptDESString)
        FUNCTION_ADDRESS(THIS_SetDESKey)

        //**                                               **
        //***           S E C T I O N  *  E N D           ***
        //***************************************************

        // Library name:
        LIBNAME_ADDRESS(THIS_LibName)
    }

