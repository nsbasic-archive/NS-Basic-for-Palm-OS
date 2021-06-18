//
//    NSBPinMgrPrototypes.h
//

#ifndef __NSBPinMgrPrototypes_H__
#define __NSBPinMgrPrototypes_H__

typedef enum {
    THIS_TrapVersion = sysLibTrapCustom,
    THIS_TrapCompileInfo,
    THIS_TrapRegisterNotifyEvents,
    THIS_TrapWinGetDisplayExtent,
    THIS_TrapWinSetDisplayExtent,
    THIS_TrapFrmGetDIAPolicy,
    THIS_TrapFrmSetDIAPolicy,
    THIS_TrapPINGetDIAState,
    THIS_TrapPINSetDIAState,
    THIS_TrapPINGetInputTriggerState,
    THIS_TrapPINSetInputTriggerState,

    THIS_TrapEnumLast
} THIS_TrapEnum;

#ifdef __cplusplus
extern "C" {
#endif

extern Int32 THIS_Version(UInt16 refNum, double *version)
                THIS_LIB_TRAP(THIS_TrapVersion);

extern Int32 THIS_CompileInfo(UInt16 refNum, char *compileDateTime)
                THIS_LIB_TRAP(THIS_TrapCompileInfo);

extern Int32 THIS_RegisterNotifyEvents(UInt16 refNum, Int32 displayResized,
                                               Int32 DIAOpened,
                                               Int32 DIAClosed)
                THIS_LIB_TRAP(THIS_TrapRegisterNotifyEvents);

extern Int32 THIS_WinGetDisplayExtent(UInt16 refNum, Int32 *  x, Int32 *  y)
                THIS_LIB_TRAP(THIS_TrapWinGetDisplayExtent);

extern Int32 THIS_WinSetDisplayExtent(UInt16 refNum, Int32 size)
                THIS_LIB_TRAP(THIS_TrapWinSetDisplayExtent);

extern Int32 THIS_FrmGetDIAPolicy(UInt16 refNum, Int32 *value)
                THIS_LIB_TRAP(THIS_TrapFrmGetDIAPolicy);

extern Int32 THIS_FrmSetDIAPolicy(UInt16 refNum, Int32 value)
                THIS_LIB_TRAP(THIS_TrapFrmSetDIAPolicy);

extern Int32 THIS_PINGetDIAState(UInt16 refNum, Int32 *value)
                THIS_LIB_TRAP(THIS_TrapPINGetDIAState);

extern Int32 THIS_PINSetDIAState(UInt16 refNum, Int32 value)
                THIS_LIB_TRAP(THIS_TrapPINSetDIAState);

extern Int32 THIS_PINGetInputTriggerState(UInt16 refNum, Int32 *value)
                THIS_LIB_TRAP(THIS_TrapPINGetInputTriggerState);

extern Int32 THIS_PINSetInputTriggerState(UInt16 refNum, Int32 value)
                THIS_LIB_TRAP(THIS_TrapPINSetInputTriggerState);

#ifdef __cplusplus
}
#endif

#endif	// __NSBPinMgrPrototypes_H__

