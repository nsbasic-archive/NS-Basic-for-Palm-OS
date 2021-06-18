/******************************************************************************
 *
 * Copyright (c) 2006 InfosystemsPro LLC All rights reserved.
 * Contact: Carmine Castiglia - ccastiglia@infosystemspro.com
 * File: SharedLib.h
 *
 * Description:
 *	  This is the header defining the contents of the shared library.
 *
 *****************************************************************************/

#ifndef SHARED_LIB_H
#define SHARED_LIB_H

#include <LibTraps.h>

/* 
 * Note that the following trap number definitions must be evaluated by 
 * the preprocessor using #defines not enum values.  
 */

#define SharedLib_Version_trapNum sysLibTrapCustom
#define SharedLib_CompileInfo_trapNum sysLibTrapCustom+1
#define SharedLib_GetPhoneType_trapNum	sysLibTrapCustom+2
#define SharedLib_GetRadioPowerStatus_trapNum	sysLibTrapCustom+3
#define SharedLib_GetPhnLibRefNum_trapNum	sysLibTrapCustom+4
#define SharedLib_GetPhnRoamMode_trapNum	sysLibTrapCustom+5
#define SharedLib_SetPhnRoamMode_trapNum	sysLibTrapCustom+6
#define SharedLib_TurnRadioOn_trapNum	sysLibTrapCustom+7
#define SharedLib_GetDeviceID_trapNum sysLibTrapCustom+8
#define SharedLib_GetRoamWarnings_trapNum sysLibTrapCustom+9
#define SharedLib_SetRoamWarnings_trapNum sysLibTrapCustom+10
#define SharedLib_SetModulePower_trapNum sysLibTrapCustom+11
#define SharedLib_GetRingProfile_trapNum sysLibTrapCustom+12
#define SharedLib_SetRingProfile_trapNum sysLibTrapCustom+13
#define SharedLib_GetLifeTimer_trapNum sysLibTrapCustom+14

#ifndef SHARED_LIB_TRAP
#define SHARED_LIB_TRAP(trapNum)	SYS_TRAP(trapNum)
#endif


/* Function declarations */

extern Err SharedLib_Open(UInt16 refNum)
	SHARED_LIB_TRAP(sysLibTrapOpen);
	
extern Err SharedLib_Close(UInt16 refNum)
	SHARED_LIB_TRAP(sysLibTrapClose);

extern Err SharedLib_Sleep(UInt16 refNum)
	SHARED_LIB_TRAP(sysLibTrapSleep);
	
extern Err SharedLib_Wake(UInt16 refNum)
	SHARED_LIB_TRAP(sysLibTrapWake);

extern Int32 SharedLib_Version(UInt16 refNum, double *version)
				SHARED_LIB_TRAP(SharedLib_Version_trapNum);

extern Int32 SharedLib_CompileInfo(UInt16 refNum, char *compileDate, char *compileTime)
	SHARED_LIB_TRAP(SharedLib_CompileInfo_trapNum);

extern Int32 SharedLib_GetPhoneType(UInt16 refNum, UInt32 *result)
	SHARED_LIB_TRAP(SharedLib_GetPhoneType_trapNum);

extern Int32 SharedLib_GetRadioPowerStatus(UInt16 refNum, Int16 *result)
	SHARED_LIB_TRAP(SharedLib_GetRadioPowerStatus_trapNum);

extern Int32 SharedLib_GetPhnLibRefNum(UInt16 refNum, UInt16 *result)
	SHARED_LIB_TRAP(SharedLib_GetPhnLibRefNum_trapNum);

extern Int32 SharedLib_GetPhnRoamMode(UInt16 refNum, Int16 *result )
	SHARED_LIB_TRAP(SharedLib_GetPhnRoamMode_trapNum);
	
extern Int32 SharedLib_SetPhnRoamMode(UInt16 refNum, Int16 mode, Int16 *result )
	SHARED_LIB_TRAP(SharedLib_SetPhnRoamMode_trapNum);
	
extern Int32 SharedLib_TurnRadioOn(UInt16 refNum, Int16 *result)
	SHARED_LIB_TRAP(SharedLib_TurnRadioOn_trapNum);

extern Int32 SharedLib_GetDeviceID(UInt16 refNum, char *company, char *device)
	SHARED_LIB_TRAP(SharedLib_GetDeviceID_trapNum);

extern Int32 SharedLib_GetRoamWarnings(UInt16 refNum, Int16 *result)
	SHARED_LIB_TRAP(SharedLib_GetRoamWarnings_trapNum);

extern Int32 SharedLib_SetRoamWarnings(UInt16 refNum, UInt16 warnings, Int16 *result)
	SHARED_LIB_TRAP(SharedLib_SetRoamWarnings_trapNum);

extern Int32 SharedLib_SetModulePower(UInt16 refNum, char *offOn, Int16 *result)
	SHARED_LIB_TRAP(SharedLib_SetModulePower_trapNum);

extern Int32 SharedLib_GetRingProfile(UInt16 refNum, UInt16 profile, Int16 *vol, Int16 *vib, Int16 *result )
	SHARED_LIB_TRAP(SharedLib_GetRingProfile_trapNum);

extern Int32 SharedLib_SetRingProfile(UInt16 refNum, UInt16 profile, Int16 vol, Int16 vib, Int16 *result )
	SHARED_LIB_TRAP(SharedLib_SetRingProfile_trapNum);

extern Int32 SharedLib_GetLifeTimer(UInt16 refNum, char *s)
	SHARED_LIB_TRAP(SharedLib_GetLifeTimer_trapNum);

#endif
