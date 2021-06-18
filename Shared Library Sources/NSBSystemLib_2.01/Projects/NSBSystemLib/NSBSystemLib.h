//
//    NSBSystemLib.h
//

#ifndef __NSBSystemLib_H__
#define __NSBSystemLib_H__

// Palm OS common definitions
#include <PalmTypes.h>
#include <SystemResources.h>

/********************************************************************
 * Creator ID, Type, and Name of THIS Shared Library
 ********************************************************************/
#define    THIS_LibCreatorID    'NSBy'
#define    THIS_LibTypeID       'libr'
#define    THIS_LibName          "NSBSystemLib"

#define    SAVEBITSMAX          10

/************************************************************
 * Library result codes:
 * (appErrorClass is reserved for 3rd party apps/libraries.
 * It is defined in SystemMgr.h)
 *************************************************************/

#define THIS_ErrParam        (appErrorClass | 1)    // invalid parameter
#define THIS_ErrNotOpen      (appErrorClass | 2)    // library is not open
#define THIS_ErrStillOpen    (appErrorClass | 3)    // returned from THIS_LibClose() if
                                                    // the library is still open by others
#define THIS_ErrMemory       (appErrorClass | 4)    // memory error occurred

#ifdef BUILDING_THIS_LIB
    #define THIS_LIB_TRAP(trapNum)
#else
    #define THIS_LIB_TRAP(trapNum) SYS_TRAP(trapNum)
#endif

#define alarmVersionNum           0x00
#define alarmSetPrefID            0x00
#define alarmLogPrefID            0x01
#define libSleepEventID           0x02
#define libWakeEventID            0x03
#define libSleepTimeID            0x04
#define libWakeTimeID             0x05

typedef struct {
    UInt32 alarmTime;
    UInt32 resetTime;
    Int32  resetCount;
    Int32  resetLimit;
    Int32  cmd;
    Char   msg[81];
} AlarmLog;

Boolean ProgressCallbackFunction(PrgCallbackDataPtr cbP);
Int32 FindProgram(char *pgmName, UInt32 *creatorID, UInt16 *cardNo, LocalID *pgmID, UInt16 refNum);
ListType *ListPointer(Int32 objID);
ControlType *ControlPointer(Int32 objID);
FieldType *FieldPointer(Int32 objID);
UInt16 ObjectIndex(Int32 objID, FormPtr *formPtr);
Int16 SortCompareFunction(void *a, void *b, Int32 other, 
                 SortRecordInfoPtr, SortRecordInfoPtr, MemHandle appInfoH);
Int32 SortOtherValue(UInt8 sortType, Boolean reverseSort, Boolean caselessSort);
Int16 SortCompareInteger(Int32 *a, Int32 *b);
Int16 SortCompareDouble(double *a, double *b);
UInt16 DecryptData(unsigned char *key, unsigned char *src, unsigned char *dst,
                   UInt16 len, char replaceNulls);
UInt16 EncryptData(unsigned char *key, unsigned char *src, unsigned char *dst,
                   UInt16 len, char replaceNulls);

#include "NSBSystemLibPrototypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/*###################################################################
 #      S t a n d a r d ,  R E Q U I R E D    P r o t o t y p e s
 #*/

extern Err THIS_LibOpen(UInt16 refNum)
               THIS_LIB_TRAP(sysLibTrapOpen);
				
extern Err THIS_LibClose(UInt16 refNum)
               THIS_LIB_TRAP(sysLibTrapClose);

extern Err THIS_LibSleep(UInt16 refNum)
               THIS_LIB_TRAP(sysLibTrapSleep);

extern Err THIS_LibWake(UInt16 refNum)
               THIS_LIB_TRAP(sysLibTrapWake);

/*###################################################################*/

#ifdef __cplusplus 
}
#endif

#endif	// __NSBSystemLib_H__

