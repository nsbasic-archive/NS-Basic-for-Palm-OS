#ifndef PILOT_PRECOMPILED_HEADERS_OFF
#define	PILOT_PRECOMPILED_HEADERS_OFF
#endif

// Define EMULATION_LEVEL.  __PALMOS_TRAPS__ was pre-defined by MW C Compiler
// Test it before we blow it away so we can properly define EMULATION_LEVEL.
#if __PALMOS_TRAPS__
		#define EMULATION_LEVEL		EMULATION_NONE		// building Pilot executable
#endif

// Now clear __PALMOS_TRAPS__ and define USE_TRAPS so headers do the right thing
// That is, we need to be able to get the addresses of StringLibrary routines.
// Other modules will access the routines through traps.
#undef __PALMOS_TRAPS__
#define __PALMOS_TRAPS__ 	0
#define	USE_TRAPS 	0

// Include Pilot headers
#include <PalmOS.h>

// Our library public definitions (library API)
#include "StringLib.h"

// Our library private definitions (library globals, etc.)
#include "StringLibPrv.h"

// Private routines
#if EMULATION_LEVEL == EMULATION_NONE
	#define StringLibInstall		__Startup__
#endif

// Local prototypes
Err StringLibInstall(UInt16 refNum, SysLibTblEntryPtr entryP);
static MemPtr	asm StringLibDispatchTable(void);

/************************************************************************/
Err StringLibInstall(UInt16 refNum, SysLibTblEntryPtr entryP)
{
	// Install pointer to our dispatch table
	entryP->dispatchTblP = (MemPtr*)StringLibDispatchTable();
	
	// Initialize globals pointer to zero (we will set up our library
	// globals in the library "open" call).
	entryP->globalsP = 0;

	return 0;
}
/************************************************************************/

// First, define the size of the jump instruction
#define prvJmpSize		4					// Palm OS presently uses short jumps


// Now, define a macro for offset list entries
#define libDispatchEntry(index)		(kOffset+((index)*prvJmpSize))

// Finally, define the size of the dispatch table's offset list --
// it is equal to the size of each entry (which is presently 2 bytes) times
// the number of entries in the offset list (***including the @Name entry***).
//
#define	kOffset		(2*20)						// NOTE: This is empirical!!!!!! - number functions + 1 
														// Will change when table changes!!

static MemPtr	asm StringLibDispatchTable(void)
{
	LEA		@Table, A0								// table ptr
	RTS													// exit with it

@Table:
	// Offset to library name
	DC.W		@Name
	// Standard traps
	DC.W		libDispatchEntry(0)					// Open
	DC.W		libDispatchEntry(1)					// Close
	DC.W		libDispatchEntry(2)					// Sleep
	DC.W		libDispatchEntry(3)					// Wake
	// Start of the Custom traps
	DC.W		libDispatchEntry(4)					// GetLibAPIVersion
	DC.W		libDispatchEntry(5)					// Replace
	DC.W		libDispatchEntry(6)					// StrReverse
	DC.W		libDispatchEntry(7)					// Space
	DC.W		libDispatchEntry(8)					// String
	DC.W		libDispatchEntry(9)					// MonthName
	DC.W		libDispatchEntry(10)					// WeekdayName
	DC.W		libDispatchEntry(11)					// StringLibInstrRev
	DC.W		libDispatchEntry(12)					// StringLibLSet
	DC.W		libDispatchEntry(13)					// StringLibRSet
	DC.W		libDispatchEntry(14)					// StringLibFormatNumber
	DC.W		libDispatchEntry(15)					// StringLibFormatTime
	DC.W		libDispatchEntry(16)					// StringLibFormatDate
	DC.W		libDispatchEntry(17)					// StringLibFormatPercent
	DC.W		libDispatchEntry(18)					// StringLibFormatCurrency
//	DC.W		libDispatchEntry(5)					// Join
// Standard library function handlers
@GotoOpen:
	JMP 		StringLibOpen
@GotoClose:
	JMP 		StringLibClose
@GotoSleep:
	JMP 		StringLibSleep
@GotoWake:
	JMP 		StringLibWake
	
// Customer library function handlers
@GotoGetLibAPIVersion:
	JMP 		StringLibGetLibAPIVersion
@GotoReplace:
	JMP 		StringLibReplace
@GotoStrReverse:
	JMP 		StringLibStrReverse
@GotoSpace:
	JMP 		StringLibSpace
@GotoString:
	JMP 		StringLibString
@GotoMonthName:
	JMP 		StringLibMonthName
@GotoWeekdayName:
	JMP 		StringLibWeekdayName
@GotoInstrRev:
	JMP 		StringLibInstrRev
@GotoLSet:
	JMP 		StringLibLSet
@GotoRSet:
	JMP 		StringLibRSet
@GotoFormatNumber:
	JMP 		StringLibFormatNumber
@GotoFormatTime:
	JMP 		StringLibFormatTime
@GotoFormatDate:
	JMP 		StringLibFormatDate
@GotoFormatPercent:
	JMP 		StringLibFormatPercent
@GotoFormatCurrency:
	JMP 		StringLibFormatCurrency
//@GotoJoin:
//	JMP 		StringLibJoin
@Name:
	DC.B		stringLibName							// This name identifies the library.  Apps
															// can pass it to SysLibFind() to check if the
															// library is already installed
}
