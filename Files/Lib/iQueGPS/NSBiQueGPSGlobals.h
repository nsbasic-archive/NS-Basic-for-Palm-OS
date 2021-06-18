//
//    ShlibTemplateGlobals.h
//

/*******************************************************************
 * THIS Library's globals structure
 *******************************************************************/
typedef struct THIS_LibGlobalsType {
    Int16 openCount;    // library open count
	
    // Add other library global fields here
	UInt16              GPSLibRef;
	UInt16              PWRLibRef;
	UInt16              MathLibRef;
	UInt32              nCreatorID;
	Boolean             libLoaded;
	Boolean             IloadedPWR;
	Boolean             mathLibLoaded;
	Int32               enabled;
	Int32               lat;
	Int32               lon;
	UInt32              penMgrAPIVersion;
	Boolean             penMgrAvailable;
	LocalID             thisLibID;
	UInt16              thisLibCard;
    Int32 				locationChange;
    Int32 				statusChange;
    Int32 				lostFix;
    Int32 				satDataChange;
    Int32 				modeChange;
    Int32 				displayResized;
} THIS_LibGlobalsType;

typedef THIS_LibGlobalsType*    THIS_LibGlobalsPtr;

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
#define THIS_ALLOCATE_GLOBALS                                  \
    THIS_LibGlobalsPtr  gP;                                    \
                                                               \
    gP = PrvLockGlobals(refNum);                               \
    if (!gP) {                                                 \
        gP = PrvMakeGlobals(refNum);                           \
        if (!gP)                                               \
            err = THIS_ErrMemory;                              \
    }                                                          \
    if (gP) {                                                  \
        gP->openCount++;                                       \
        PrvUnlockGlobals(gP);                                  \
    }

/********************************************************************
 *              T H I S _ F R E E _ G L O B A L S          
 ********************************************************************/
#define THIS_FREE_GLOBALS                                           \
    THIS_LibGlobalsPtr  gP;                                         \
    Int16               openCount;                                  \
    UInt16              mathLibOpenCount;                           \
    Err                 err;                                        \
                                                                    \
    gP = PrvLockGlobals(refNum);                                    \
    if (!gP)                                                        \
        return 0;                                                   \
                                                                    \
    if (gP->locationChange != 0 ||                                  \
        gP->statusChange != 0 ||                                    \
        gP->lostFix != 0 ||                                         \
        gP->satDataChange != 0 ||                                   \
        gP->modeChange != 0)                                        \
        SysNotifyUnregister(gP->thisLibCard, gP->thisLibID,         \
                            sysNotifyGPSDataEvent,                  \
                            sysNotifyNormalPriority);               \
                                                                    \
    if (gP->displayResized != 0)                                    \
        SysNotifyUnregister(gP->thisLibCard, gP->thisLibID,         \
                            sysNotifyDisplayResizedEvent,           \
                            sysNotifyNormalPriority);               \
                                                                    \
    gP->openCount--;                                                \
    ErrFatalDisplayIf(gP->openCount < 0,                            \
                      "Shared lib open count underflow");           \
    openCount = gP->openCount;                                      \
    if (gP->libLoaded) {                                            \
        err = GPSClose(gP->GPSLibRef);                              \
        if (err != gpsErrStillOpen)                                 \
            SysLibRemove(gP->GPSLibRef);                            \
    }                                                               \
    if (gP->nCreatorID != 0xFFFFFFFF) {                             \
        if (gP->IloadedPWR) {                                       \
            if (gP->enabled == 1)                                   \
     	        gP->IloadedPWR = PwrSetLowPowerMode(gP->PWRLibRef,  \
	                                                gP->nCreatorID, \
	                                                false);         \
            SysLibRemove(gP->PWRLibRef);                            \
        }                                                           \
        else                                                        \
            if (gP->enabled == 1)                                   \
     	        gP->IloadedPWR = PwrSetLowPowerMode(gP->PWRLibRef,  \
	                                                gP->nCreatorID, \
	                                                false);         \
    }                                                               \
	err = MathLibClose(gP->MathLibRef, &mathLibOpenCount);          \
	if (mathLibOpenCount == 0)                                      \
    	SysLibRemove(gP->MathLibRef);                               \
    PrvUnlockGlobals(gP);                                           \
    if (openCount <= 0)                                             \
        PrvFreeGlobals(refNum);                                     \
    else                                                            \
        err = THIS_ErrStillOpen;
		
/********************************************************************
 *            T H I S _ A T T A C H _ G L O B A L S          
 ********************************************************************/
#define THIS_ATTACH_GLOBALS                                     \
    THIS_LibGlobalsPtr  gP;                                     \
                                                                \
    gP = PrvLockGlobals(refNum);

/********************************************************************
 *             T H I S _ D E T A C H _ G L O B A L S          
 ********************************************************************/
#define THIS_DETACH_GLOBALS    MemPtrUnlock(gP);

/********************************************************************
 *                P r v M a k e G l o b a l s
 ********************************************************************/
static THIS_LibGlobalsPtr PrvMakeGlobals(UInt16 refNum) {
    THIS_LibGlobalsPtr  gP = NULL;  // globals pointer
    MemHandle           gH;         // globals handle
    SysLibTblEntryPtr   libEntryP;  // pointer to library table entry


    // Get THIS Library's globals
    libEntryP = SysLibTblEntry(refNum);  // get THIS Library's table entry
    ErrFatalDisplayIf(libEntryP == NULL, "Invalid Shared lib refNum");
	
    // Error check to make sure the globals don't already exist
    ErrFatalDisplayIf(libEntryP->globalsP, "Shared lib's globals already exist");
	
    // Allocate and initialize THIS Library's globals.
    gH = MemHandleNew(sizeof(THIS_LibGlobalsType));
    if (!gH)
        return(NULL);    // memory allocation error
	
    // Save the handle of THIS Library's globals in the system library
    // table entry so it can later be retrieved using SysLibTblEntry().
    libEntryP->globalsP = (void*) gH;

    // Lock the globals
    gP = PrvLockGlobals(refNum);    // this should not fail
    ErrFatalDisplayIf(gP == NULL, "Failed to lock Shared lib's globals");
	
    // Set the owner of the globals memory chunk to "system" (zero), 
    // so it won't get freed automatically by Memory Manager when 
    // the first application to call THIS_LibOpen exits.  This is 
    // important if the library is going to stay open between apps.
    MemPtrSetOwner(gP, 0);
	
    // Initialize THIS Library's globals
    MemSet(gP, sizeof(THIS_LibGlobalsType), 0);
    gP->openCount = 0;    // initial open count
    gP->nCreatorID = 0xFFFFFFFF;
    gP->IloadedPWR = false;
    gP->enabled = 0;
	
    return(gP);           // return a pointer to these *locked* globals
}

/********************************************************************
 *                   P r v F r e e G l o b a l s
 ********************************************************************/
static void PrvFreeGlobals(UInt16 refNum) {
    MemHandle          gH;         // globals handle
    SysLibTblEntryPtr  libEntryP;  // pointer to library table entry
    
    // Get THIS Library's globals handle
    libEntryP = SysLibTblEntry(refNum);     // get system library table entry
    ErrFatalDisplayIf(libEntryP == NULL, "Invalid Shared lib refNum");
	
    gH = (MemHandle)(libEntryP->globalsP);  // get globals handle from entry
	
    // Free THIS Library's globals
    if (gH) {
        libEntryP->globalsP = NULL;         // clear globals reference
        MemHandleFree(gH);                  // free globals
    }

}

/********************************************************************
 *                 P r v L o c k G l o b a l s
 ********************************************************************/
static THIS_LibGlobalsPtr PrvLockGlobals(UInt16 refNum) {
    THIS_LibGlobalsPtr  gP = NULL;
    MemHandle           gH;
    SysLibTblEntryPtr   libEntryP;


    libEntryP = SysLibTblEntry(refNum);  // get system library table entry
    if (libEntryP)
        gH = (MemHandle)(libEntryP->globalsP);  // get globals handle from the entry
    if (gH)
        gP = (THIS_LibGlobalsPtr)MemHandleLock(gH);  // lock globals

    return(gP);
}

