//
//    NSBPinMgrDispatch.c
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

    #define CUSTOM_FUNCTION_COUNT   17

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

    #include "NSBPinMgr.h"

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
        CUSTOM_FUNCTION_ENTRY(3)  // THIS_PINMgrAPIVersion 
        CUSTOM_FUNCTION_ENTRY(4)  // THIS_PINMgrAPIMajorMinor 
        CUSTOM_FUNCTION_ENTRY(5)  // THIS_RegisterNotifyEvents 
        CUSTOM_FUNCTION_ENTRY(6)  // THIS_WinGetDisplayExtent 
        CUSTOM_FUNCTION_ENTRY(7)  // THIS_WinSetDisplayExtent 
        CUSTOM_FUNCTION_ENTRY(8)  // THIS_FrmGetDIAPolicy 
        CUSTOM_FUNCTION_ENTRY(9)  // THIS_FrmSetDIAPolicy 
        CUSTOM_FUNCTION_ENTRY(10)  // THIS_PINGetDIAState 
        CUSTOM_FUNCTION_ENTRY(11)  // THIS_PINSetDIAState 
        CUSTOM_FUNCTION_ENTRY(12)  // THIS_PINGetInputTriggerState 
        CUSTOM_FUNCTION_ENTRY(13)  // THIS_PINSetInputTriggerState 
        CUSTOM_FUNCTION_ENTRY(14)  // THIS_SysGetOrientation 
        CUSTOM_FUNCTION_ENTRY(15)  // THIS_SysSetOrientation 
        CUSTOM_FUNCTION_ENTRY(16)  // THIS_SysGetOrientationTriggerState 
        CUSTOM_FUNCTION_ENTRY(17)  // THIS_SysSetOrientationTriggerState 

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
        FUNCTION_ADDRESS(THIS_PINMgrAPIVersion)
        FUNCTION_ADDRESS(THIS_PINMgrAPIMajorMinor)
        FUNCTION_ADDRESS(THIS_RegisterNotifyEvents)
        FUNCTION_ADDRESS(THIS_WinGetDisplayExtent)
        FUNCTION_ADDRESS(THIS_WinSetDisplayExtent)
        FUNCTION_ADDRESS(THIS_FrmGetDIAPolicy)
        FUNCTION_ADDRESS(THIS_FrmSetDIAPolicy)
        FUNCTION_ADDRESS(THIS_PINGetDIAState)
        FUNCTION_ADDRESS(THIS_PINSetDIAState)
        FUNCTION_ADDRESS(THIS_PINGetInputTriggerState)
        FUNCTION_ADDRESS(THIS_PINSetInputTriggerState)
        FUNCTION_ADDRESS(THIS_SysGetOrientation)
        FUNCTION_ADDRESS(THIS_SysSetOrientation)
        FUNCTION_ADDRESS(THIS_SysGetOrientationTriggerState)
        FUNCTION_ADDRESS(THIS_SysSetOrientationTriggerState)

        //**                                               **
        //***           S E C T I O N  *  E N D           ***
        //***************************************************

        // Library name:
        LIBNAME_ADDRESS(THIS_LibName)
    }

