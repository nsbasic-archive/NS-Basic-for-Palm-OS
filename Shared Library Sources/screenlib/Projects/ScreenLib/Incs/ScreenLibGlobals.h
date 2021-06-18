/********************************************************************
 * SHARED LIBRARY GLOBALS:
 *
 * IMPORTANT:
 * ==========
 * Shared Libraries are *not* allowed to have global or static 
 * variables.  Instead, they allocate a memory chunk to hold their 
 * persistent data, and save a handle to it in the library's system
 * library table entry.  The following functions below demostrate 
 * how the library "globals" chunk is set up, saved, and accessed.
 *
 * A movable memory chunk is used for this library globals to
 * minimize dynamic heap fragmentation.  The library globals are 
 * locked only when needed and unlocked as soon as possible.  This
 * behavior is critical for healthy system performance.
 *
 * This file, "THIS_LibGlobals.h", file departs from the usual C 
 * language usage for header files by actually including executable
 * code, not just prototypes and definitions.  It was created this 
 * way to allow it to be one of the files in the project but not 
 * actually compiled during "Make", as a separate C file.  It is 
 * only compiled when "#include'd" by a .c file.  This is for 
 * convenience only - so that you can easily edit the file by 
 * double-clicking on the file in the CodeWarrior project list.
 *
 ********************************************************************/

// THIS Library's globals structure
typedef struct THIS_LibGlobalsType {
	Int16	openCount;	// library open count
	
    UInt32  depth;
    Boolean color;
    RGBColorType RGB;
	} THIS_LibGlobalsType;

typedef THIS_LibGlobalsType*		THIS_LibGlobalsPtr;

/********************************************************************
 * Internally used routines
 ********************************************************************/
static THIS_LibGlobalsPtr PrvMakeGlobals(UInt16 refNum);
static void PrvFreeGlobals(UInt16 refNum);
static THIS_LibGlobalsPtr PrvLockGlobals(UInt16 refNum);

/********************************************************************
 *              P r v _ U n l o c k _ G l o b a l s          
 ********************************************************************/
#define PrvUnlockGlobals(gP)	MemPtrUnlock(gP)

/********************************************************************
 *          T H I S _ A L L O C A T E _ G L O B A L S          
 ********************************************************************/
#define THIS_ALLOCATE_GLOBALS							\
	THIS_LibGlobalsPtr	gP;								\
														\
	gP = PrvLockGlobals(refNum);						\
	if (!gP) {											\
		gP = PrvMakeGlobals(refNum);					\
		if (!gP)										\
			err = THIS_ErrMemory;						\
	}													\
	if (gP)	{											\
 		gP->openCount++;								\
		PrvUnlockGlobals(gP);							\
	}

/********************************************************************
 *              T H I S _ F R E E _ G L O B A L S          
 ********************************************************************/
#define THIS_FREE_GLOBALS								\
	THIS_LibGlobalsPtr	gP;								\
	Int16				openCount;						\
														\
	gP = PrvLockGlobals(refNum);						\
	if (!gP)											\
		return 0;										\
	gP->openCount--;									\
	ErrFatalDisplayIf(gP->openCount < 0, 				\
			"Sample lib open count underflow");			\
	openCount = gP->openCount;							\
	PrvUnlockGlobals(gP);								\
	if (openCount <= 0)									\
		PrvFreeGlobals(refNum);							\
	else												\
		err = THIS_ErrStillOpen;
		
/********************************************************************
 *            T H I S _ A T T A C H _ G L O B A L S          
 ********************************************************************/
#define THIS_ATTACH_GLOBALS								\
	THIS_LibGlobalsPtr	gP;								\
														\
	gP = PrvLockGlobals(refNum);

/********************************************************************
 *             T H I S _ D E T A C H _ G L O B A L S          
 ********************************************************************/
#define THIS_DETACH_GLOBALS	MemPtrUnlock(gP);

/********************************************************************
 *                P r v M a k e G l o b a l s
 ********************************************************************/
static THIS_LibGlobalsPtr PrvMakeGlobals(UInt16 refNum) {
	THIS_LibGlobalsPtr	gP = NULL;	// globals pointer
	MemHandle			gH;			// globals handle
	SysLibTblEntryPtr	libEntryP;	// pointer to library table entry


	// Get THIS Library's globals
	libEntryP = SysLibTblEntry(refNum);	// get THIS Library's table entry
	ErrFatalDisplayIf(libEntryP == NULL, "invalid THIS lib refNum");
	
	// Error check to make sure the globals don't already exist
	ErrFatalDisplayIf(libEntryP->globalsP, "THIS lib's globals already exist");
	
	// Allocate and initialize THIS Library's globals.
	gH = MemHandleNew(sizeof(THIS_LibGlobalsType));
	if (!gH)
		return(NULL);		// memory allocation error
	
	// Save the handle of THIS Library's globals in the system library
	// table entry so it can later be retrieved using SysLibTblEntry().
	libEntryP->globalsP = (void*) gH;

	// Lock the globals
	gP = PrvLockGlobals(refNum);			// this should not fail
	ErrFatalDisplayIf(gP == NULL, "failed to lock THIS lib's globals");
	
		
	// Set the owner of the globals memory chunk to "system" (zero), 
	// so it won't get freed automatically by Memory Manager when 
	// the first application to call THIS_LibOpen exits.  This is 
	// important if the library is going to stay open between apps.
	MemPtrSetOwner(gP, 0);
	
	// Initialize THIS Library's globals
	MemSet(gP, sizeof(THIS_LibGlobalsType), 0);
	gP->openCount = 0;	// initial open count
	
	return(gP);		// return a pointer to these *locked* globals
}

/********************************************************************
 *                   P r v F r e e G l o b a l s
 ********************************************************************/
static void PrvFreeGlobals(UInt16 refNum) {
	MemHandle			gH;			// globals handle
	SysLibTblEntryPtr	libEntryP;	// pointer to library table entry


	// Get THIS Library's globals handle
	libEntryP = SysLibTblEntry(refNum);		// get system library table entry
	ErrFatalDisplayIf(libEntryP == NULL, "invalid Sample lib refNum");
	
	gH = (MemHandle)(libEntryP->globalsP);	// get globals handle from entry
	
	// Free THIS Library's globals
	if (gH) {
		libEntryP->globalsP = NULL;		// clear globals reference
		MemHandleFree(gH);				// free globals
	}

}

/********************************************************************
 *                 P r v L o c k G l o b a l s
 ********************************************************************/
static THIS_LibGlobalsPtr PrvLockGlobals(UInt16 refNum) {
	THIS_LibGlobalsPtr	gP = NULL;
	MemHandle			gH;
	SysLibTblEntryPtr	libEntryP;


	libEntryP = SysLibTblEntry(refNum);		// get system library table entry
	if (libEntryP)
		gH = (MemHandle)(libEntryP->globalsP);	// get globals handle from the entry
	if (gH)
		gP = (THIS_LibGlobalsPtr)MemHandleLock(gH);		// lock globals


	return(gP);
}

