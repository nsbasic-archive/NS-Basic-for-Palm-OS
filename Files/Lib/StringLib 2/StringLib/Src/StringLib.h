 #ifndef __STRING_LIB_H__
#define __STRING_LIB_H__


// If we're actually compiling the library code, then we need to
// eliminate the trap glue that would otherwise be generated from
// this header file in order to prevent compiler errors in CW Pro 2.
#ifdef BUILDING_STRING_LIB
	#define STRING_LIB_TRAP(trapNum)
#else
	#define STRING_LIB_TRAP(trapNum) SYS_TRAP(trapNum)
#endif


// Palm OS common definitions
#include <PalmTypes.h>
#include <SystemResources.h>


/********************************************************************
 * Type and creator of Sample Library database
 ********************************************************************/
#define		stringLibCreatorID	'NSBz'				// Sample Library database creator
#define		stringLibTypeID		'libr'				// Standard library database type


/********************************************************************
 * Internal library name which can be passed to SysLibFind()
 ********************************************************************/
#define		stringLibName			"NSBStringLib"		


/************************************************************
 * String Library result codes
 * (appErrorClass is reserved for 3rd party apps/libraries.
 * It is defined in SystemMgr.h)
 *************************************************************/

#define stringErrParam		(appErrorClass | 1)		// invalid parameter
#define stringErrNotOpen	(appErrorClass | 2)		// library is not open
#define stringErrStillOpen	(appErrorClass | 3)		// returned from SampleLibClose() if
																		// the library is still open by others
#define stringErrMemory		(appErrorClass | 4)		// memory error occurred

//-----------------------------------------------------------------------------
// Sample library function trap ID's. Each library call gets a trap number:
//   sampleLibTrapXXXX which serves as an index into the library's dispatch table.
//   The constant sysLibTrapCustom is the first available trap number after
//   the system predefined library traps Open,Close,Sleep & Wake.
//
// WARNING!!! The order of these traps MUST match the order of the dispatch
//  table in SampleLibDispatch.c!!!
//-----------------------------------------------------------------------------

typedef enum {
	stingLibTrapGetLibAPIVersion = sysLibTrapCustom,
	stringLibReplace,
	stringLibStrReverse,
	stringLibSpace,
	stringLibString,
	stringLibMonthName,
	stringLibWeekdayName,
	stringLibInstrRev,
	stringLibLSet,
	stringLibRSet,
	stringLibFormatNumber,
	stringLibFormatTime,
	stringLibFormatDate,
	stringLibFormatPercent,
	stringLibFormatCurrency,
//	sampleLibTrapSetCornerDiameter,
//	sampleLibTrapGetCornerDiameter,
//	sampleLibTrapDrawRectangle,
//	stringLibJoin,
	stringLibTrapLast
	} StringLibTrapNumberEnum;

/********************************************************************
 * API Prototypes
 ********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


//--------------------------------------------------
// Standard library open, close, sleep and wake functions
//--------------------------------------------------

extern Err StringLibOpen(UInt16 refNum) 	STRING_LIB_TRAP(sysLibTrapOpen);
extern Err StringLibClose(UInt16 refNum)	STRING_LIB_TRAP(sysLibTrapClose);
extern Err StringLibSleep(UInt16 refNum)	STRING_LIB_TRAP(sysLibTrapSleep);
extern Err StringLibWake(UInt16 refNum)	STRING_LIB_TRAP(sysLibTrapWake);

//--------------------------------------------------
// Custom library API functions
//--------------------------------------------------
	
// Get our library API version
extern Err StringLibGetLibAPIVersion(UInt16 refNum, UInt32 * dwVerP)	STRING_LIB_TRAP(stringLibTrapGetLibAPIVersion);
//extern Err StringLibJoin(UInt16 refNum,char ** in, char* delim, char* out)	STRING_LIB_TRAP(stringLibJoin);
extern Err StringLibReplace(UInt16 refNum, char* in, char* find, char*  replacewith, UInt16 count, char* result) STRING_LIB_TRAP(stringLibReplace);
extern Err StringLibStrReverse(UInt16 refNum, char *expr, char *result) STRING_LIB_TRAP(stringLibStrReverse);
extern Err StringLibSpace(UInt16 refNum, UInt16 num, char *result) STRING_LIB_TRAP(stringLibSpace);
extern Err StringLibString(UInt16 refNum, UInt16 number, char* ch, char *result) STRING_LIB_TRAP(stringLibString);
extern Err StringLibMonthName(UInt16 refNum, UInt16 month, UInt16 abbreviate, char *result) STRING_LIB_TRAP(stringLibMonthName);
extern Err StringLibWeekdayName(UInt16 refNum, UInt16 weekday, UInt16 abbreviate, UInt16 firstdayofweek, char*result) STRING_LIB_TRAP(stringLibWeekdayName);
extern Err StringLibInstrRev(UInt16 refNum, char *expr, char* find, UInt16 start, UInt16 *result) STRING_LIB_TRAP(stringLibInstrRev);
extern Err StringLibLSet(UInt16 refNum, char* expr, char* replace) STRING_LIB_TRAP(stringLibLSet);
extern Err StringLibRSet(UInt16 refNum, char* expr, char* replace) STRING_LIB_TRAP(stringLibRSet);
extern Err StringLibFormatNumber (UInt16 refNum, double expr , UInt16 numDig , UInt16 format, char *result) STRING_LIB_TRAP(stringLibFormatNumber);
extern Err StringLibFormatTime(UInt16 ferNum, double _time, UInt16 namedFormat, char* result) STRING_LIB_TRAP(stringLibFormatTime);
extern Err StringLibFormatDate(UInt16 ferNum, double _date, UInt16 namedFormat, char* result) STRING_LIB_TRAP(stringLibFormatDate);
extern Err StringLibFormatPercent(UInt16 refNum, double expr, UInt16 numDig, UInt16 format, char* result) STRING_LIB_TRAP(stringLibFormatPercent);
extern Err StringLibFormatCurrency(UInt16 refNum, double expr, UInt16 numDig, UInt16 format, char* result) STRING_LIB_TRAP(stringLibFormatCurrency);

// For loading the library in Palm OS Mac emulation mode
extern Err StringLibInstall(UInt16 refNum, SysLibTblEntryPtr entryP);

#ifdef __cplusplus 
}
#endif


#endif	// __STRING_LIB_H__

