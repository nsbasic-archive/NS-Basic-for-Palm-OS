//
//    ShlibTemplateGlobals.h
//

/*******************************************************************
 * THIS Library's globals structure
 *******************************************************************/
typedef struct THIS_LibGlobalsType {
    Int16 openCount;    // library open count
	
    // Add other library global fields here
    UInt32     major;
    UInt32     minor;
    EventType  event;
	WChar      chr;
	UInt16     keyCode;
	UInt16     modifiers;
    Coord      screenX;
    Coord      screenY;
    Coord      startX;
    Coord      startY;
    Coord      endX;
    Coord      endY;
    Coord      width;
    Coord      height;
    UInt16     startPos;
    UInt16     endPos;
    Int16      hour;
    Int16      minute;
    Char       truncated;
    char       dbName[dmDBNameLength + 1];
    UInt16     dbAttributes;
    UInt16     dbVersion;
    UInt32     dbCreationDate;
    UInt32     dbModificationDate;
    UInt32     dbBackupDate;
    UInt32     dbModificationNumber;
    LocalID    dbAppInfoID;
    LocalID    dbSortInfoID;
    UInt32     dbType;
    UInt32     dbCreatorID;
    UInt32     dbNumRecords;
    UInt32     dbDataSize;
    UInt16     dbCardNo;
    UInt32     resetTime;
    Int32      resetLimit;
    Char       pgmName[48];
    LocalID    pgmID;
    UInt16     pgmCardNo;
    UInt32     pgmCreatorID;
    UInt32     depth;
    Boolean    color;
    RGBColorType RGB;
    DmSearchStateType dbStateInfo;
    ProgressPtr       progressPtr;
    WinHandle  saveBits[SAVEBITSMAX];
    MemPtr      **sortPtr;
    UInt16      sortItems;
    UInt16      sortMaxItems;
    UInt8       sortType;
    unsigned char   src[256];
    unsigned char   dst[256];
    unsigned char   keys[25];
    unsigned char   *key[3];

} THIS_LibGlobalsType;

typedef THIS_LibGlobalsType*    THIS_LibGlobalsPtr;

/********************************************************************
 * Internally used routines
 ********************************************************************/
static THIS_LibGlobalsPtr PrvMakeGlobals(UInt16 refNum);
static void PrvFreeGlobals(UInt16 refNum);
static THIS_LibGlobalsPtr PrvLockGlobals(UInt16 refNum);
static Boolean SysVersion(THIS_LibGlobalsPtr gP, UInt32 verMajor, UInt32 verMinor);

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
#define THIS_FREE_GLOBALS                                       \
    THIS_LibGlobalsPtr  gP;                                     \
    Int16               openCount;                              \
    UInt16              i;                                      \
                                                                \
    gP = PrvLockGlobals(refNum);                                \
    if (!gP)                                                    \
        return 0;                                               \
    gP->openCount--;                                            \
    ErrFatalDisplayIf(gP->openCount < 0,                        \
                      "Shared lib open count underflow");       \
    openCount = gP->openCount;                                  \
    if (openCount == 0) {                                       \
        if (gP->sortPtr) {                                      \
            for (i = 0; i < gP->sortItems; i++)                 \
                MemPtrFree(gP->sortPtr[i]);                     \
            MemPtrFree(gP->sortPtr);                            \
            gP->sortPtr = NULL;                                 \
            gP->sortItems = 0;                                  \
        }                                                       \
    }                                                           \
    PrvUnlockGlobals(gP);                                       \
    if (openCount <= 0) {                                       \
        PrvFreeGlobals(refNum);                                 \
    }                                                           \
    else                                                        \
        err = THIS_ErrStillOpen;
		
/********************************************************************
 *            T H I S _ A T T A C H _ G L O B A L S          
 ********************************************************************/
#define THIS_ATTACH_GLOBALS                                     \
    THIS_LibGlobalsPtr  gP;                                     \
    gP = (THIS_LibGlobalsPtr) MemHandleLock((MemHandle) (((SysLibTblEntryPtr) SysLibTblEntry(refNum))->globalsP));
//                                                            \
//    gP = PrvLockGlobals(refNum);

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
	UInt32              ver;


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
	
    FtrGet(sysFtrCreator, sysFtrNumROMVersion, &ver);
    gP->major = sysGetROMVerMajor(ver);
	gP->minor = sysGetROMVerMinor(ver);
	
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
    MemHandle           gH;
    THIS_LibGlobalsPtr  gP = NULL;
    SysLibTblEntryPtr   libEntryP;


    libEntryP = SysLibTblEntry(refNum);  // get system library table entry
    if (libEntryP)
        gH = (MemHandle)(libEntryP->globalsP);  // get globals handle from the entry
    if (gH)
        gP = (THIS_LibGlobalsPtr)MemHandleLock(gH);  // lock globals


    return(gP);
}

