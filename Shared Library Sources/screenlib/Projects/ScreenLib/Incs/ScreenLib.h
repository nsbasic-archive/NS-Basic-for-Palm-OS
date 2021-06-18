#ifndef __THIS_LIB_H__
#define __THIS_LIB_H__


#ifdef BUILDING_THIS_LIB
	#define THIS_LIB_TRAP(trapNum)
#else
	#define THIS_LIB_TRAP(trapNum) SYS_TRAP(trapNum)
#endif


// Palm OS common definitions
#include <PalmTypes.h>
#include <SystemResources.h>


/********************************************************************
 * Creator ID, Type, and Name of THIS Shared Library
 ********************************************************************/
#define		THIS_LibCreatorID	'NSBS'
#define		THIS_LibTypeID		'libr'
#define		THIS_LibName		"ScreenLib.lib"		


/************************************************************
 * Library result codes:
 * (appErrorClass is reserved for 3rd party apps/libraries.
 * It is defined in SystemMgr.h)
 *************************************************************/

#define THIS_ErrParam		(appErrorClass | 1)		// invalid parameter
#define THIS_ErrNotOpen 	(appErrorClass | 2)		// library is not open
#define THIS_ErrStillOpen	(appErrorClass | 3)		// returned from THIS_LibClose() if
													// the library is still open by others
#define THIS_ErrMemory		(appErrorClass | 4)		// memory error occurred


#include "ScreenLibPrototypes.h"

/*###################################################################
 #      S t a n d a r d ,  R E Q U I R E D    P r o t o t y p e s
 #
 #   You should not need to modify these prototypes.  Put your
 #   library's custom prototypes before these to separate your
 #   custom code from the standard, required code.  This way,
 #   the code you need to modify is easily found at the top of the
 #   file and you can "ignore" the standard, required, code at the
 #   end of the file.
 ###################################################################*/

extern Err THIS_LibOpen(UInt16 refNum)
				THIS_LIB_TRAP(sysLibTrapOpen);
				
extern Err THIS_LibClose(UInt16 refNum)
				THIS_LIB_TRAP(sysLibTrapClose);

extern Err THIS_LibSleep(UInt16 refNum)
				THIS_LIB_TRAP(sysLibTrapSleep);

extern Err THIS_LibWake(UInt16 refNum)
				THIS_LIB_TRAP(sysLibTrapWake);

// For loading the library in Palm OS Mac emulation mode
extern Err THIS_LibInstall(UInt16 refNum, SysLibTblEntryPtr entryP);

/*###################################################################*/

#ifdef __cplusplus 
}
#endif

#endif	// __THIS_LIB_H__

