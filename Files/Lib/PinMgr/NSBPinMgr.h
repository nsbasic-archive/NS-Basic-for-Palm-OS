//
//    NSBPinMgr.h
//

#ifndef __NSBPinMgr_H__
#define __NSBPinMgr_H__

// Palm OS common definitions
#include <PalmTypes.h>
#include <SystemResources.h>

/********************************************************************
 * Creator ID, Type, and Name of THIS Shared Library
 ********************************************************************/
#define    THIS_LibCreatorID    'NPin'
#define    THIS_LibTypeID       'libr'
#define    THIS_LibName          "NSBPinMgr"


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

#include "NSBPinMgrPrototypes.h"

Err DIANotificationCallback(SysNotifyParamType *notifyParamsP);
Int32 PinMgrAvailable(Int32 *pinMgrAvailable, UInt32 *pinMgrAPIVersion,
                      UInt32 *pinMgrMajor, UInt32 *pinMgrMinor);
Int32 LibID(Int32 *libCard, Int32 *libID);


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

#endif	// __NSBPinMgr_H__

