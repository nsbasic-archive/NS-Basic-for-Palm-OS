//
//    NSBSystemLib.c
//
#define UGLY_DOC
#define VERSION 2.01
// MANUFACTURER NSBasic Corporation
// INFHELP ""
// INFHELP "NSBSystemLib Shared Library"
// INFHELP ""
// INFHELP "This library provides support for calling system/PalmOS"
// INFHELP "API functions from NSBasic."
// INFHELP ""

#include <PalmOS.h>			// Includes all Palm OS headers
#include <PalmOSGlue.h>
#include <DLServer.h>

#define BUILDING_THIS_LIB	// Defined in this file only...
#include "NSBSystemLib.h"		// Library public definitions

#if defined(__GNUC__)
    #include "NSBSystemLibDispatch.c"
#endif

#define THIS_REQUIRES_GLOBALS
#ifdef THIS_REQUIRES_GLOBALS
    #include "NSBSystemLibGlobals.h"
#else
    #define THIS_ALLOCATE_GLOBALS
    #define THIS_FREE_GLOBALS
    #define THIS_ATTACH_GLOBALS
    #define THIS_DETACH_GLOBALS
#endif

#define bitDepthMask(depth)    (1L << (depth - 1))
#define bitMask(bit)           (1L << bit)

/********************************************************************
 *                    S y s V e r s i o n
 ********************************************************************/
static Boolean SysVersion(THIS_LibGlobalsPtr gP, UInt32 verMajor, UInt32 verMinor)
{
	UInt32 major;
	UInt32 minor;
	UInt32 ver;

	if (gP == NULL) {
        FtrGet(sysFtrCreator, sysFtrNumROMVersion, &ver);
    	major = sysGetROMVerMajor(ver);
	    minor = sysGetROMVerMinor(ver);
	}
	else {
	    major = gP->major;
	    minor = gP->minor;
	}
	if (major > verMajor)
	    return true;
	if (major == verMajor && minor >= verMinor)
	    return true;
	    
	return false;
}


/********************************************************************
 *      P r o g r e s s C a l l b a c k F u n c t i o n
 ********************************************************************/
Boolean ProgressCallbackFunction(PrgCallbackDataPtr cbP) {
    if (cbP->canceled)
        StrCopy(cbP->textP, "Cancelling...");
    else {
        StrNCopy(cbP->textP, cbP->message, cbP->textLen);
        cbP->textP[cbP->textLen] = '\0';
    }
    return true;
}

/********************************************************************
 *               S o r t C o m p a r e I n t e g e r
 ********************************************************************/
Int16 SortCompareInteger(Int32 *a, Int32 *b) {
    if (*a == *b)
        return 0;
    else
        if (*a > *b)
            return 1;
        else
            return -1;
}

/********************************************************************
 *               S o r t C o m p a r e D o u b l e
 ********************************************************************/
Int16 SortCompareDouble(double *a, double *b) {
    if (*a == *b)
        return 0;
    else
        if (*a > *b)
            return 1;
        else
            return -1;
}

/********************************************************************
 *               S o r t C o m p a r e F u n c t i o n
 ********************************************************************/
Int16 SortCompareFunction(void *a, void *b, Int32 other, 
                 SortRecordInfoPtr, SortRecordInfoPtr, MemHandle appInfoH) {
    Int16 compareResult;
    
    
    switch (other) {
        case 0:
        case 1:
            compareResult = StrCompare(*((char **) a), *((char **) b));
            break;
        case 10:
        case 11:
            compareResult = StrCaselessCompare(*((char **) a), *((char **) b));
            break;       
        case 100:
        case 101:
            compareResult = SortCompareInteger((Int32 *) *((Int32 **) a), (Int32 *) *((Int32 **) b));
            break;
        case 200:
        case 201:
            compareResult = SortCompareDouble((double *) *((double **) a), (double *) *((double **) b));
            break;
    }
    if (other & 1)
        compareResult = 0 - compareResult;
    return compareResult;
}

/********************************************************************
 *                    S o r t O t h e r V a l u e
 ********************************************************************/
Int32 SortOtherValue(UInt8 sortType, Boolean reverseSort, Boolean caselessSort) {
    if (sortType == 0)
        if (caselessSort)
            if (reverseSort)
                return 11;
            else
                return 10;
        else
            if (reverseSort)
                return 1;
            else
                return 0;
    else
        if (sortType == 1)
            if (reverseSort)
                return 101;
            else
                return 100;
        else
            if (reverseSort)
                return 201;
            else
                return 200;
    return 0;
}

/********************************************************************
 *                  L i s t P o i n t e r
 ********************************************************************/
ListType *ListPointer(Int32 objID) {
    FormPtr   formPtr;
    UInt16    listIndex;
    
    formPtr = FrmGetActiveForm();
    if (formPtr != NULL) {
        if (objID != 0)
            if (objID <= FrmGetNumberOfObjects(formPtr))
                listIndex = objID - 1;
            else
                listIndex = FrmGetObjectIndex(formPtr, (UInt16 ) objID);
        else
            listIndex = FrmGetFocus(formPtr);
        if (listIndex != noFocus)
            return FrmGetObjectPtr(formPtr, listIndex);
        else
            return NULL;
    }
    else
        return NULL;
}

/********************************************************************
 *                  C o n t r o l P o i n t e r
 ********************************************************************/
ControlType *ControlPointer(Int32 objID) {
    FormPtr   formPtr;
    UInt16    controlIndex;
    
    formPtr = FrmGetActiveForm();
    if (formPtr != NULL) {
        if (objID != 0)
            if (objID <= FrmGetNumberOfObjects(formPtr))
                controlIndex = objID - 1;
            else
                controlIndex = FrmGetObjectIndex(formPtr, (UInt16 ) objID);
        else
            controlIndex = FrmGetFocus(formPtr);
        if (controlIndex != noFocus)
            return FrmGetObjectPtr(formPtr, controlIndex);
        else
            return NULL;
    }
    else
        return NULL;
}

/********************************************************************
 *                     F i e l d P o i n t e r
 ********************************************************************/
FieldType *FieldPointer(Int32 objID) {
    FormPtr   formPtr;
    UInt16    fieldIndex;
    
    formPtr = FrmGetActiveForm();
    if (formPtr != NULL) {
        if (objID != 0)
            if (objID <= FrmGetNumberOfObjects(formPtr))
                fieldIndex = objID - 1;
            else
                fieldIndex = FrmGetObjectIndex(formPtr, (UInt16 ) objID);
        else
            fieldIndex = FrmGetFocus(formPtr);
        if (fieldIndex != noFocus)
            if (FrmGetObjectType(formPtr, fieldIndex) == frmFieldObj)
                return FrmGetObjectPtr(formPtr, fieldIndex);
            else
                return NULL;
        else
            return NULL;
    }
    else
        return NULL;
}

/********************************************************************
 *                    O b j e c t I n d e x
 ********************************************************************/
UInt16 ObjectIndex(Int32 objID, FormPtr *formPtr) {
    
    *formPtr = FrmGetActiveForm();
    if (*formPtr != NULL)
        if (objID != 0)
            if (objID <= FrmGetNumberOfObjects(*formPtr))
                return objID - 1;
            else    
                return FrmGetObjectIndex(*formPtr, (UInt16 ) objID);
        else
            return FrmGetFocus(*formPtr);
    else
        return noFocus;
}

/********************************************************************
 *                      F i n d P r o g r a m
 ********************************************************************/
Int32 FindProgram(char *pgmName, UInt32 *creatorID, UInt16 *cardNo, LocalID *pgmID, UInt16 refNum) {
    UInt16  i;
    LocalID dbID;
    THIS_ATTACH_GLOBALS

    if (StrCompare(pgmName, gP->pgmName) == 0) {
        if (creatorID != NULL)
            *creatorID = gP->pgmCreatorID;
        if (cardNo != NULL)
            *cardNo = gP->pgmCardNo;
        if (pgmID != NULL)
            *pgmID = gP->pgmID;
        THIS_DETACH_GLOBALS
        return 0;
    }
    else {
        for (i = 0; i < MemNumCards(); i++)
            if ((dbID = DmFindDatabase(i, pgmName)) != 0)
                break;
        if (dbID != 0) {
            if (DmDatabaseInfo(i, dbID, NULL, NULL, NULL, 
                               NULL, NULL, NULL, NULL, NULL, 
                               NULL, NULL, &gP->pgmCreatorID) == errNone) {
                StrCopy(gP->pgmName, pgmName);
                gP->pgmID = dbID;
                gP->pgmCardNo = i;
                if (pgmID != NULL)
                    *pgmID = dbID;
                if (cardNo != NULL)
                    *cardNo = i;
                if (creatorID != NULL)
                    *creatorID = gP->pgmCreatorID;
                THIS_DETACH_GLOBALS
                return 0;
            }
        }
    }
    
    StrCopy(gP->pgmName, "");
    THIS_DETACH_GLOBALS
    return -1;      // Program not found
}

/********************************************************************
 *                      D e c r y p t D a t a
 ********************************************************************/
UInt16 DecryptData(unsigned char *key, unsigned char *src, unsigned char *dst, 
                   UInt16 len, char replaceNulls) 
{
    UInt16          dstLen = 0;
    unsigned char   lastReplaced = 0;
    unsigned char   nextReplaced = 0;
    
    if (replaceNulls) {
	    while (1) {
    	    if (lastReplaced == 255 || lastReplaced >= len)
        	    break;
	        nextReplaced = src[lastReplaced];
    	    src[lastReplaced] = 0;
        	lastReplaced = nextReplaced;
	    }
	    len--;
        src++;
	}
	
    dst[0] = 0;
    while (dstLen < len) {
        EncDES(src, key, dst, 0);
        src += 8;
        dst += 8;
        dstLen += 8;
    } 
    
    if (replaceNulls)
        *dst = 0;
    return dstLen;
}

/********************************************************************
 *                     E n c r y p t D a t a
 ********************************************************************/
UInt16 EncryptData(unsigned char *key, unsigned char *src, unsigned char *dst, 
                   UInt16 len, char replaceNulls) 
{
    UInt16          dstLen = 0;
    unsigned char   i;
    unsigned char   n;
    unsigned char   lastReplaced = 0;

    if (replaceNulls) {
        dst[0] = 255;
        dstLen++;
        len++;
    }
    while (dstLen < len) {
        EncDES(src, key, dst + dstLen, 1);
        if (replaceNulls)
            for (n = 0; n < 8; n++) {
                i = dstLen + n;
                if (dst[i] == 0) {
                    dst[lastReplaced] = i;
                    lastReplaced = i;
                    dst[i] = 255;
                }
            }
        dstLen += 8;
        src +=8;
    }
    if (replaceNulls)
        dst[dstLen] = 0;
    return dstLen;
}

// SECTION Version Information
// DESC The version information functions provide information about
// DESC the version of the NSBSystemLib Shared Library and about the 
// DESC user's PalmOS System.

/********************************************************************
 *                     T H I S _ V e r s i o n
 ********************************************************************/
Err THIS_Version(UInt16 refNum, double *version) 
// DESC Returns the version number of the NSBSystemLib Shared Library.
{	

    *version = VERSION;
    return 0;
}

/********************************************************************
 *                 T H I S _ C o m p i l e I n f o
 ********************************************************************/
Err THIS_CompileInfo(UInt16 refNum, char *compileDateTime) 
// DESC Returns the date and time that the NSBSystemLib was compiled.
{	
    char dateTime[21];
	
    StrCopy(dateTime, __DATE__);
    StrCat(dateTime, " ");
    StrCat(dateTime, __TIME__);
    StrCopy(compileDateTime, dateTime);

    return 0;
}

/********************************************************************
 *                   S y s t e m V e r s i o n
 ********************************************************************/
Err THIS_SystemVersion(UInt16 refNum, double *version) 
// DESC Returns the version number of the PalmOS system.
// NOTES See also:  GlobalVersionMajor(), GlobalVersionMinor()
{
	Int32 major;
	Int32 minor;
	char  majorStr[16];
	char  minorStr[16];
	char  verStr[32];
	FlpCompDouble uDbl;
	UInt32 ver;
	
    FtrGet(sysFtrCreator, sysFtrNumROMVersion, &ver);
	major = sysGetROMVerMajor(ver);
	minor = sysGetROMVerMinor(ver);
    StrIToA(majorStr, major);
    StrIToA(minorStr, minor);
    StrCopy(verStr, majorStr);
    StrCat(verStr, ".");
    StrCat(verStr, minorStr);
    uDbl.fd = FlpAToF(verStr);
    
	*version = uDbl.d;
	return 0;
}

// SECTION Access To Shared Library Global Variables
// DESC Currently, shared libraries may return only one numeric
// DESC value from a function call.  A number of functions in
// DESC this library, however, have multiple numeric values that
// DESC they retrieve.  In order to make these values available,
// DESC they are stored as a library global variable.  The 
// DESC following functions return the values of these global
// DESC variables.
// DESC  
// DESC In general, the global access functions are used after
// DESC making a specific function call.

/********************************************************************
 *           T H I S _ G l o b a l V e r s i o n M a j o r
 ********************************************************************/
Err THIS_GlobalVersionMajor(UInt16 refNum, Int32 *gblMajor)
// DESC Returns the major version number portion of the PalmOS version.
// DESC This value is stored as a library global variable at library
// DESC load time. 
// NOTES See also:  SystemVersion()
{
    THIS_ATTACH_GLOBALS
    *gblMajor = gP->major;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *           T H I S _ G l o b a l V e r s i o n M i n o r
 ********************************************************************/
Err THIS_GlobalVersionMinor(UInt16 refNum, Int32 *gblMinor)
// DESC Returns the minor version number portion of the PalmOS version.
// DESC This value is stored as a library global variable at library
// DESC load time. 
// NOTES See also:  SystemVersion()
{
    THIS_ATTACH_GLOBALS
    *gblMinor = gP->minor;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *               T H I S _ G l o b a l X
 ********************************************************************/
Err THIS_GlobalX(UInt16 refNum, Int32 *x)
// DESC Returns the value of the global variable "x" in the
// DESC NSBSystemLib Shared Library.
{
    THIS_ATTACH_GLOBALS
    *x = gP->screenX;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *               T H I S _ G l o b a l Y
 ********************************************************************/
Err THIS_GlobalY(UInt16 refNum, Int32 *y)
// DESC Returns the value of the global variable "y" in the
// DESC NSBSystemLib Shared Library.
{
    THIS_ATTACH_GLOBALS
    *y = gP->screenY;
    THIS_DETACH_GLOBALS
    
    return 0;
}
    
/********************************************************************
 *              T H I S _ G l o b a l S t a r t X
 ********************************************************************/
Err THIS_GlobalStartX(UInt16 refNum, Int32 *startX)
// DESC Returns the value of the global variable "startX" in the
// DESC NSBSystemLib Shared Library.
{
    THIS_ATTACH_GLOBALS
    *startX = gP->startX;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *              T H I S _ G l o b a l S t a r t Y
 ********************************************************************/
Err THIS_GlobalStartY(UInt16 refNum, Int32 *startY)
// DESC Returns the value of the global variable "startY" in the
// DESC NSBSystemLib Shared Library.
{
    THIS_ATTACH_GLOBALS
    *startY = gP->startY;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *              T H I S _ G l o b a l E n d X
 ********************************************************************/
Err THIS_GlobalEndX(UInt16 refNum, Int32 *endX)
// DESC Returns the value of the global variable "endX" in the
// DESC NSBSystemLib Shared Library.
{
    THIS_ATTACH_GLOBALS
    *endX = gP->endX;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *              T H I S _ G l o b a l E n d Y
 ********************************************************************/
Err THIS_GlobalEndY(UInt16 refNum, Int32 *endY)
// DESC Returns the value of the global variable "endY" in the
// DESC NSBSystemLib Shared Library.
{
    THIS_ATTACH_GLOBALS
    *endY = gP->endY;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *           T H I S _ G l o b a l S t a r t P o s
 ********************************************************************/
Err THIS_GlobalStartPos(UInt16 refNum, Int32 *startPos)
// DESC Returns the value of the global variable "startPos" in the
// DESC NSBSystemLib Shared Library.
{
    THIS_ATTACH_GLOBALS
    *startPos = gP->startPos;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *           T H I S _ G l o b a l E n d P o s
 ********************************************************************/
Err THIS_GlobalEndPos(UInt16 refNum, Int32 *endPos)
// DESC Returns the value of the global variable "endPos" in the
// DESC NSBSystemLib Shared Library.
{
    THIS_ATTACH_GLOBALS
    *endPos = gP->endPos;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *           T H I S _ G l o b a l W i d t h
 ********************************************************************/
Err THIS_GlobalWidth(UInt16 refNum, Int32 *width)
// DESC Returns the value of the global variable "width" in the
// DESC NSBSystemLib Shared Library.
{
    THIS_ATTACH_GLOBALS
    *width = gP->width;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *           T H I S _ G l o b a l H e i g h t
 ********************************************************************/
Err THIS_GlobalHeight(UInt16 refNum, Int32 *height)
// DESC Returns the value of the global variable "height" in the
// DESC NSBSystemLib Shared Library.
{
    THIS_ATTACH_GLOBALS
    *height = gP->height;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *              T H I S _ G l o b a l H o u r
 ********************************************************************/
Err THIS_GlobalHour(UInt16 refNum, Int32 *gblHour)
// DESC Returns the value of the global variable "hour" in the
// DESC NSBSystemLib Shared Library.
// NOTES See also:  SelectOneTime()
{
    THIS_ATTACH_GLOBALS
    *gblHour = gP->hour;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *              T H I S _ G l o b a l M i n u t e
 ********************************************************************/
Err THIS_GlobalMinute(UInt16 refNum, Int32 *gblMinute)
// DESC Returns the value of the global variable "minute" in the
// DESC NSBSystemLib Shared Library.
// NOTES See also:  SelectOneTime()
{
    THIS_ATTACH_GLOBALS
    *gblMinute = gP->minute;
    THIS_DETACH_GLOBALS
    
    return 0;
}

// SECTION Alarm Functions
// DESC Alarms, under PalmOS, are implemented by the system calling
// DESC a program as a specially launched subprogram.  As such, a
// DESC program must be written specifically to be able to process
// DESC alarms.  Some of the requirements of such a program include
// DESC the acceptance of special launch codes and the inability to
// DESC access any global variables.  NSBasic programs can not currently
// DESC adhere to these requirements and thus, can not process alarms
// DESC by themselves.  NSBasic programs can, however, utilize alarms
// DESC by using alarm "proxy" programs.
// DESC
// DESC An alarm proxy program, as its name implies, acts on behalf of
// DESC an NSBasic program.  The alarm functions described here, are
// DESC intended to be used with the NSBAlarmProxy programs that are
// DESC distributed with this library.  Currently, PalmOS only supports
// DESC one active alarm for any one particular program.  For this reason,
// DESC there are 5 NSBAlarmProxy programs available.  With 5 proxy programs,
// DESC your single NSBasic program can set up to 5 active alarms, you
// DESC can have 5 NSBasic programs, each with 1 active alarm, or any
// DESC other combination.  If you are only setting one alarm, then you
// DESC only need to install one alarm proxy program.  The NSBAlarmProxy 
// DESC programs are named:
// DESC <<blockquote>>NSBAlarmProxy1, NSBAlarmProxy2, NSBAlarmProxy3, 
// DESC NSBAlarmProxy4, and NSBAlarmProxy5<</blockquote>>
// DESC The NSBAlarmProxy programs can do a number of different things
// DESC on behalf of your NSBasic program.  They can just simply 
// DESC wake up a device, sound an alarm, display an alert, start
// DESC a named program, or enqueue an event that can be detected
// DESC by a running NSBasic program.  Alarms can also be set to
// DESC automatically reset or reschedule themselves.  By using the
// DESC reset feature with event enqueueing, you can easily
// DESC implement a crude "interrupt timer".
// DESC
// DESC In most cases, when an alarm is triggered, the alarm proxy
// DESC program will write a "log" of its activity.  This log is
// DESC written to the proxy program's application preferences.  As
// DESC such, only the last activity will be available and no
// DESC separate database is created.  This information can be
// DESC used for a variety of purposes.  One of which is to determine
// DESC if your NSBasic program was started by a user or by an alarm.
// DESC This is done in your startup code by checking the alarm's 
// DESC log time against the current time.  If they are the same, or
// DESC reasonably close, and your program's name is also in the log,
// DESC then you can conclude that your program was started by an
// DESC alarm.  With this information, you can choose to have your
// DESC program start with a different form than normal or some
// DESC other alternate startup processing.

/********************************************************************
 *               T H I S _ S e t A l a r m R e s e t
 ********************************************************************/
Err THIS_SetAlarmReset(UInt16 refNum, UInt32 resetTime, Int32 resetLimit) 
// DESC Establishes an automatic alarm reset interval for the next 
// DESC alarm that is set.
// PARAM1 Reset interval in seconds
// PARAM1   0 = do not automatically reset alarm
// PARAM2 Limit to the number of automatic resets that can occur.
// PARAM2  -1 = resets are not limited - CancelAlarm() must be
// PARAM2       used to stop automatic resets.
// PARAM2   0 = do not automatically reset alarm
// NOTES If this feature is to be used, it must be called before
// NOTES each SetAlarm() function.
// NOTES
// NOTES Note:  Care should be taken when using automatic resets
// NOTES to avoid a potential infinite loop.  This is especially
// NOTES true when the alarm enqueues events.  An infinite loop
// NOTES can occur when alarms occur at a rate faster than they 
// NOTES can be processed.  In general, reset intervals should 
// NOTES not be less than 2 seconds.
// BEFORE
// BEFORE resetTime = 10
// BEFORE resetLimit = -1
{
    THIS_ATTACH_GLOBALS
    
    gP->resetTime = resetTime;
    gP->resetLimit = resetLimit;
    
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *                   T H I S _ S e t A l a r m
 ********************************************************************/
Err THIS_SetAlarm(UInt16 refNum, char *alarmPgm,
                  UInt32 alarmTime, Int32 alarmCmd,
                  char *alarmMsg, Int32 *status)
// DESC Sets an alarm for the specified program.  The alarm features
// DESC in this library are intended to be used only with the
// DESC NSBAlarmProxy programs.  While it is possible to use these
// DESC functions with other programs, it is highly discouraged.  
// DESC This is because these functions write to the program's 
// DESC application preferences.  Non-proxy programs that may use the
// DESC same preferences may become corrupt and require a hard
// DESC reset and restoration.  The program names have not been
// DESC restricted to allow for future additional alarm proxy programs.
// PARAM1 Alarm program.
// PARAM2 Absolute alarm time in system time format or a time
// PARAM2 increment in seconds from the current time.  This time
// PARAM2 is considered as an absolute time if its value is greater
// PARAM2 or equal to the value of the current system time minus 5 
// PARAM2 minutes.
// PARAM3 Alarm Command explanations:
// PARAM3   -32767 to -30001 = "Timer" commands
// PARAM3      These commands have the least amount of overhead
// PARAM3      associated with them.  They do not write to the
// PARAM3      alarm log information.  In addition, they automat-
// PARAM3      ically reset the alarm.  As such, they must be
// PARAM3      specifically cancelled using the CancelAlarm()
// PARAM3      function.
// PARAM3
// PARAM3      These commands queue an event which is the
// PARAM3      absolute (positive) value of the command.
// PARAM3
// PARAM3      The reset interval (seconds) used is calculated as:
// PARAM3           abs(cmd) - 30000
// PARAM3           example:  -30005 has a reset interval of 5
// PARAM3                            seconds and queues an event
// PARAM3                            with an event type of 30005.
// PARAM3   0 = enqueue a "nilEvent" - can be used to just simply
// PARAM3       wake up or turn on a PalmOS device
// PARAM3   1 = sound a system alarm sound only
// PARAM3   2 = sound a system alarm sound and produce an Alert
// PARAM3       with the message specified in the alarmMsg parameter.
// PARAM3   3 = start the program with the name specified in the
// PARAM3       alarmMsg parameter.  The alarmMsg parameter, in this
// PARAM3       case, is a coded string with the following format:
// PARAM3           <programName>[,<launcherWaitTime>][;<userInfo>]
// PARAM3           examples:  "Address"
// PARAM3                      "Address;started by MyProg"
// PARAM3                      "Address,6;started by MyProg"
// PARAM3           notes:  The launcherWaitTime is the time, in
// PARAM3                   in seconds to wait for the current program
// PARAM3                   to terminate - the default is 2 seconds.
// PARAM3                   The userInfo, as well as the entire string,
// PARAM3                   is written to the alarmLog.  It can be used
// PARAM3                   for any purpose you like.
// PARAM3    4 to 255 = enqueue a Key Event with a value equal to 
// PARAM3               the specified alarmCmd
// PARAM3    24832 to 30000 = enqueue a generic event with an event
// PARAM3                     type equal to the specified alarmCmd.
// PARAM4  A string of 80 characters or less that is used as the
// PARAM4  message for alarmCmd 2 or the program code for alarmCmd 3.
// PARAM4  It is also written to the alarm log to provide any info.
// PARAM4  that may be useful.
// RETURNS  0 = no error
// RETURNS -1 = specified alarm program is not installed
// RETURNS -2 = almErrorMemory - insufficient memory
// RETURNS -3 = almErrorFull - alarm queue is full
// RETURNS -4 = unexpected/unrecognized error
// BEFORE
// BEFORE alarmPgm = "NSBAlarmProxy1"
// BEFORE alarmTime = 3600    ' 1 hour from now
// BEFORE alarmCmd = 3
// BEFORE alarmMsg = "Hey Wake UP!"
// NOTES See also:  SystemTime()
// NOTES
// NOTES Note:  Care should be taken when using automatic resets
// NOTES to avoid a potential infinite loop.  This is especially
// NOTES true when the alarm enqueues events.  An infinite loop
// NOTES can occur when alarms occur at a rate faster than they 
// NOTES can be processed.  In general, reset intervals should 
// NOTES not be less than 2 seconds.
{
    UInt32  creatorId;
    LocalID alarmId;
    UInt32  curTime;
    UInt16  cardNo;
    AlarmLog alarmLog;
    UInt16  logSize;
	THIS_ATTACH_GLOBALS
	

	if ((*status = FindProgram(alarmPgm, &creatorId, &cardNo, &alarmId, refNum)) != 0) {
	    THIS_DETACH_GLOBALS
	    return 0;
	}
	    
	alarmLog.alarmTime = alarmTime;
	alarmLog.resetTime = gP->resetTime;
	alarmLog.resetLimit = gP->resetLimit;
	alarmLog.resetCount = 0;
	alarmLog.cmd = alarmCmd;
	gP->resetTime = 0;
	gP->resetLimit = 0;
	StrCopy(alarmLog.msg, alarmMsg);
    PrefSetAppPreferences(creatorId, alarmSetPrefID, alarmVersionNum, 
                          &alarmLog, sizeof(alarmLog), 0);

	logSize = sizeof(alarmLog);
    PrefGetAppPreferences(creatorId, alarmLogPrefID, 
                          &alarmLog, &logSize, false);
    alarmLog.resetCount = 0;
    PrefSetAppPreferences(creatorId, alarmLogPrefID, alarmVersionNum, 
                          &alarmLog, sizeof(alarmLog), 0);

	curTime = TimGetSeconds();
    if (alarmTime < (curTime - 300))
        alarmTime = curTime + alarmTime;                          
    *status = AlmSetAlarm(cardNo, alarmId, alarmCmd, alarmTime, 0);                          
    switch (*status) {
        case 0:
            break;
        case almErrMemory:
            *status = -2;
            break;
        case almErrFull:
            *status = -3;
            break;
        default:
            *status = -4;
            break;
    }

    THIS_DETACH_GLOBALS
	return 0;
}

/********************************************************************
 *              T H I S _ C a n c e l A l a r m
 ********************************************************************/
Err THIS_CancelAlarm(UInt16 refNum, char *alarmPgm, Int32 *status)
// DESC Cancel an alarm set, if any, for the specified program.  
// PARAM1 Alarm program.
// RETURNS  0 = no error
// RETURNS -1 = specified alarm program is not installed
// RETURNS -2 = almErrorMemory - insufficient memory
// RETURNS -3 = almErrorFull - alarm queue is full
// RETURNS -4 = unexpected/unrecognized error
// BEFORE
// BEFORE alarmPgm = "NSBAlarmProxy1"
{
    UInt32  creatorId;
    LocalID alarmId;
    UInt16  cardNo;
    AlarmLog alarmLog;
	
	if ((*status = FindProgram(alarmPgm, &creatorId, &cardNo, &alarmId, refNum)) != 0)
	    return 0;

	alarmLog.alarmTime = 0;
	alarmLog.resetTime = 0;
	alarmLog.resetLimit = 0;
	alarmLog.resetCount = 0;
	alarmLog.cmd = 0;
	alarmLog.msg[0] = 0;
    PrefSetAppPreferences(creatorId, alarmSetPrefID, alarmVersionNum, 
                          &alarmLog, sizeof(alarmLog), 0);
	               
    *status = AlmSetAlarm(cardNo, alarmId, 0, 0, 0);
    switch (*status) {
        case 0:
            break;
        case almErrMemory:
            *status = -2;
            break;
        case almErrFull:
            *status = -3;
            break;
        default:
            *status = -4;
            break;
    }

	return 0;
}

/********************************************************************
 *                  T H I S _ G e t A l a r m
 ********************************************************************/
Err THIS_GetAlarm(UInt16 refNum, char *alarmPgm,
                  char *alarmCmd, char *alarmMsg,
                  UInt32 *alarmTime) 
// DESC Retrieves information about a currently set alarm.
// PARAM1 Alarm program.
// PARAM2 AlarmCmd as a string.  This value is returned and
// PARAM2 must be initialized to a maximum length before calling
// PARAM2 the function.  This value should never be more than
// PARAM2 6 characters in length.
// PARAM3 Alarm message as a string.  This value is returned and
// PARAM3 must be initialized to a maximum length before calling
// PARAM3 the function.  This value should never be more than
// PARAM3 80 characters in length.
// RETURNS Alarm time in system time format.  This value is expressed
// RETURNS as the number of seconds since January 1st, 1904.
// NOTES See also:  StringDateTime(), StringDate(), StringTime()
// BEFORE
// BEFORE alarmPgm = "NSBAlarmProxy1"
// BEFORE alarmCmd = "123456"
// BEFORE alarmMsg = "1234567890123456789012345678901234567890" _
// BEFORE          + "1234567890123456789012345678901234567890"
{
    UInt32  creatorId;
    LocalID alarmId;
    UInt16  cardNo;
    Int32  alarmCommand;
    AlarmLog alarmLog;
    UInt16   logSize;
	

	if (FindProgram(alarmPgm, &creatorId, &cardNo, &alarmId, refNum) != 0) {
	    StrIToA(alarmCmd, -1);
	    StrCopy(alarmMsg, "");
	    *alarmTime = 0;
	    return 0;
	}
              
    *alarmTime = AlmGetAlarm(cardNo, alarmId, (UInt32 *) &alarmCommand);
    if (*alarmTime == 0)
        StrIToA(alarmCmd, -1);
    else
        StrIToA(alarmCmd, alarmCommand);
        
	logSize = sizeof(alarmLog);
    if (PrefGetAppPreferences(creatorId, alarmSetPrefID, 
                              &alarmLog, &logSize, false) != 0)
        alarmLog.msg[0] = 0;
    StrCopy(alarmMsg, alarmLog.msg);
    return 0;
}

/********************************************************************
 *               T H I S _ G e t A l a r m T i m e
 ********************************************************************/
Err THIS_GetAlarmTime(UInt16 refNum, char *alarmPgm,
                      UInt32 *alarmTime) 
// DESC Retrieves information about a currently set alarm.
// PARAM1 Alarm program.
// RETURNS Alarm time in system time format.  This value is expressed
// RETURNS as the number of seconds since January 1st, 1904.
// BEFORE
// BEFORE alarmPgm = "NSBAlarmProxy1"
// NOTES See also:  StringDateTime(), StringDate(), StringTime()
{
    LocalID alarmId;
    UInt16  cardNo;
    Int32  alarmCommand;
	

	if (FindProgram(alarmPgm, NULL, &cardNo, &alarmId, refNum) != 0) {
	    *alarmTime = 0;
	    return 0;
	}
              
    *alarmTime = AlmGetAlarm(cardNo, alarmId, (UInt32 *) &alarmCommand);
    return 0;
}

/********************************************************************
 *          T H I S _ G e t A l a r m R e s e t T i m e
 ********************************************************************/
Err THIS_GetAlarmResetTime(UInt16 refNum, char *alarmPgm,
                           UInt32 *resetTime) 
// DESC Retrieves information about a currently set alarm.
// PARAM1 Alarm program.
// RETURNS Alarm reset time in seconds.
// BEFORE
// BEFORE alarmPgm = "NSBAlarmProxy1"
{
    UInt32  creatorId;
    AlarmLog alarmLog;
    UInt16   logSize;
	

	if (FindProgram(alarmPgm, &creatorId, NULL, NULL, refNum) != 0) {
	    *resetTime = 0;
	    return 0;
	}
                      
	logSize = sizeof(alarmLog);
    if (PrefGetAppPreferences(creatorId, alarmSetPrefID, 
                              &alarmLog, &logSize, false) != 0)
        *resetTime = 0;
    else
        *resetTime = alarmLog.resetTime;
    return 0;
}

/********************************************************************
 *          T H I S _ G e t A l a r m R e s e t L i m i t
 ********************************************************************/
Err THIS_GetAlarmResetLimit(UInt16 refNum, char *alarmPgm,
                            Int32 *resetLimit) 
// DESC Retrieves information about a currently set alarm.
// PARAM1 Alarm program.
// RETURNS Alarm reset limit.
// BEFORE
// BEFORE alarmPgm = "NSBAlarmProxy1"
{
    UInt32  creatorId;
    AlarmLog alarmLog;
    UInt16   logSize;
	

	if (FindProgram(alarmPgm, &creatorId, NULL, NULL, refNum) != 0) {
	    *resetLimit = 0;
	    return 0;
	}
                      
	logSize = sizeof(alarmLog);
    if (PrefGetAppPreferences(creatorId, alarmSetPrefID, 
                              &alarmLog, &logSize, false) != 0)
        *resetLimit = 0;
    else
        *resetLimit = alarmLog.resetLimit;
    return 0;
}


/********************************************************************
 *            T H I S _ G e t A l a r m C o m m a n d
 ********************************************************************/
Err THIS_GetAlarmCommand(UInt16 refNum, char *alarmPgm,
                         Int32 *alarmCmd) 
// DESC Retrieves information about a currently set alarm.
// PARAM1 Alarm program.
// RETURNS Alarm command.
// BEFORE
// BEFORE alarmPgm = "NSBAlarmProxy1"
{
    LocalID alarmId;
    UInt16  cardNo;
    UInt32  alarmTime;
	

	if (FindProgram(alarmPgm, NULL, &cardNo, &alarmId, refNum) != 0) {
	    *alarmCmd = -1;
	    return 0;
	}
              
    alarmTime = AlmGetAlarm(cardNo, alarmId, (UInt32 *) alarmCmd);
    return 0;
}

/********************************************************************
 *              T H I S _ G e t A l a r m M e s s a g e
 ********************************************************************/
Err THIS_GetAlarmMessage(UInt16 refNum, char *alarmPgm,
                         char *alarmMsg) 
// DESC Retrieves information about a currently set alarm.
// PARAM1 Alarm program.
// RETURNS Alarm message.
// BEFORE
// BEFORE alarmPgm = "NSBAlarmProxy1"
{
    UInt32  creatorId;
    AlarmLog alarmLog;
    UInt16   logSize;
	

	if (FindProgram(alarmPgm, &creatorId, NULL, NULL, refNum) != 0) {
	    StrCopy(alarmMsg, "");
	    return 0;
	}
                      
	logSize = sizeof(alarmLog);
    if (PrefGetAppPreferences(creatorId, alarmSetPrefID, 
                              &alarmLog, &logSize, false) != 0)
        alarmLog.msg[0] = 0;
    StrCopy(alarmMsg, alarmLog.msg);
    return 0;
}

/********************************************************************
 *                  T H I S _ A l a r m L o g
 ********************************************************************/
Err THIS_AlarmLog(UInt16 refNum, char *alarmPgm,
                  char *alarmCmd, char *alarmMsg,
                  UInt32 *alarmTime) 
// DESC Retrieves information about an alarm that has already been
// DESC processed.
// PARAM1 Alarm program.
// PARAM2 AlarmCmd as a string.  This value is returned and
// PARAM2 must be initialized to a maximum length before calling
// PARAM2 the function.  This value should never be more than
// PARAM2 6 characters in length.
// PARAM3 Alarm message as a string.  This value is returned and
// PARAM3 must be initialized to a maximum length before calling
// PARAM3 the function.  This value should never be more than
// PARAM3 80 characters in length.
// RETURNS Alarm time in system time format.  This value is expressed
// RETURNS as the number of seconds since January 1st, 1904.
// NOTES See also:  StringDateTime(), StringDate(), StringTime()
// BEFORE
// BEFORE alarmPgm = "NSBAlarmProxy1"
// BEFORE alarmCmd = "123456"
// BEFORE alarmMsg = "1234567890123456789012345678901234567890" _
// BEFORE          + "1234567890123456789012345678901234567890"
{
    UInt32   creatorId;
    AlarmLog alarmLog;
    UInt16   logSize;
	
	if (FindProgram(alarmPgm, &creatorId, NULL, NULL, refNum) != 0) {
	    *alarmTime = 0;    // Unrecognized AlarmProxy program
	    StrCopy(alarmMsg, "");
	    StrCopy(alarmCmd, "0");
	    return 0;
	}
	   
	logSize = sizeof(alarmLog);
    if (PrefGetAppPreferences(creatorId, alarmLogPrefID, 
                              &alarmLog, &logSize, false) != 0) {
        alarmLog.alarmTime = 0;
        alarmLog.resetTime = 0;
        alarmLog.resetCount = 0;
        alarmLog.cmd = -1;
        alarmLog.msg[0] = 0;
    }
    
    StrIToA(alarmCmd, alarmLog.cmd);
    StrCopy(alarmMsg, alarmLog.msg);
    *alarmTime = alarmLog.alarmTime;
	return 0;
}

/********************************************************************
 *       T H I S _ A l a r m L o g A l a r m T i m e
 ********************************************************************/
Err THIS_AlarmLogAlarmTime(UInt16 refNum, char *alarmPgm,
                           UInt32 *alarmTime) 
// DESC Retrieves information about an alarm that has already been
// DESC processed.
// PARAM1 Alarm program.
// RETURNS Alarm time in system time format.  This value is expressed
// RETURNS as the number of seconds since January 1st, 1904.
// NOTES See also:  StringDateTime(), StringDate(), StringTime()
// BEFORE
// BEFORE alarmPgm = "NSBAlarmProxy1"
{
    UInt32   creatorId;
    AlarmLog alarmLog;
    UInt16   logSize;
	
	if (FindProgram(alarmPgm, &creatorId, NULL, NULL, refNum) != 0) {
	    *alarmTime = 0;    // Unrecognized AlarmProxy program
	    return 0;
	}
	   
	logSize = sizeof(alarmLog);
    if (PrefGetAppPreferences(creatorId, alarmLogPrefID, 
                              &alarmLog, &logSize, false) != 0)
        alarmLog.alarmTime = 0;
    
    *alarmTime = alarmLog.alarmTime;
	return 0;
}

/********************************************************************
 *       T H I S _ A l a r m L o g R e s e t T i m e
 ********************************************************************/
Err THIS_AlarmLogResetTime(UInt16 refNum, char *alarmPgm,
                           UInt32 *resetTime) 
// DESC Retrieves information about an alarm that has already been
// DESC processed.
// PARAM1 Alarm program.
// RETURNS Alarm time reset time in seconds.
// BEFORE
// BEFORE alarmPgm = "NSBAlarmProxy1"
{
    UInt32   creatorId;
    AlarmLog alarmLog;
    UInt16   logSize;
	
	if (FindProgram(alarmPgm, &creatorId, NULL, NULL, refNum) != 0) {
	    *resetTime = 0;    // Unrecognized AlarmProxy program
	    return 0;
	}
	   
	logSize = sizeof(alarmLog);
    if (PrefGetAppPreferences(creatorId, alarmLogPrefID, 
                              &alarmLog, &logSize, false) != 0)
        alarmLog.resetTime = 0;
    
    *resetTime = alarmLog.resetTime;
	return 0;
}

/********************************************************************
 *       T H I S _ A l a r m L o g R e s e t L i m i t
 ********************************************************************/
Err THIS_AlarmLogResetLimit(UInt16 refNum, char *alarmPgm,
                            Int32 *resetLimit) 
// DESC Retrieves information about an alarm that has already been
// DESC processed.
// PARAM1 Alarm program.
// RETURNS Alarm time reset limit.
// BEFORE
// BEFORE alarmPgm = "NSBAlarmProxy1"
{
    UInt32   creatorId;
    AlarmLog alarmLog;
    UInt16   logSize;
	
	if (FindProgram(alarmPgm, &creatorId, NULL, NULL, refNum) != 0) {
	    *resetLimit = 0;    // Unrecognized AlarmProxy program
	    return 0;
	}
	   
	logSize = sizeof(alarmLog);
    if (PrefGetAppPreferences(creatorId, alarmLogPrefID, 
                              &alarmLog, &logSize, false) != 0)
        alarmLog.resetLimit = 0;
    
    *resetLimit = alarmLog.resetLimit;
	return 0;
}

/********************************************************************
 *       T H I S _ A l a r m L o g R e s e t C o u n t
 ********************************************************************/
Err THIS_AlarmLogResetCount(UInt16 refNum, char *alarmPgm,
                            Int32 *resetCount) 
// DESC Retrieves information about an alarm that has already been
// DESC processed.
// PARAM1 Alarm program.
// RETURNS The number of times the alarm as been automatically reset.
// BEFORE
// BEFORE alarmPgm = "NSBAlarmProxy1"
{
    UInt32   creatorId;
    AlarmLog alarmLog;
    UInt16   logSize;
	
	if (FindProgram(alarmPgm, &creatorId, NULL, NULL, refNum) != 0) {
	    *resetCount = 0;    // Unrecognized AlarmProxy program
	    return 0;
	}
	   
	logSize = sizeof(alarmLog);
    if (PrefGetAppPreferences(creatorId, alarmLogPrefID, 
                              &alarmLog, &logSize, false) != 0)
        alarmLog.resetCount = 0;
    
    *resetCount = alarmLog.resetCount;
	return 0;
}

/********************************************************************
 *            T H I S _ A l a r m L o g C o m m a n d
 ********************************************************************/
Err THIS_AlarmLogCommand(UInt16 refNum, char *alarmPgm,
                         Int32 *alarmCmd) 
// DESC Retrieves information about an alarm that has already been
// DESC processed.
// PARAM1 Alarm program.
// RETURNS Alarm command.
// BEFORE
// BEFORE alarmPgm = "NSBAlarmProxy1"
{
    UInt32   creatorId;
    AlarmLog alarmLog;
    UInt16   logSize;
	
	if (FindProgram(alarmPgm, &creatorId, NULL, NULL, refNum) != 0) {
	    *alarmCmd = -1;     // Unrecognized AlarmProxy program
	    return 0;
	}
	   
	logSize = sizeof(alarmLog);
    if (PrefGetAppPreferences(creatorId, alarmLogPrefID, 
                              &alarmLog, &logSize, false) != 0)
        alarmLog.cmd = -1;
    
    *alarmCmd = alarmLog.cmd;
	return 0;
}

/********************************************************************
 *           T H I S _ A l a r m L o g M e s s a g e
 ********************************************************************/
Err THIS_AlarmLogMessage(UInt16 refNum, char *alarmPgm,
                         char *alarmMsg) 
// DESC Retrieves information about an alarm that has already been
// DESC processed.
// PARAM1 Alarm program.
// RETURNS Alarm message.
// BEFORE
// BEFORE alarmPgm = "NSBAlarmProxy1"
{
    UInt32   creatorId;
    AlarmLog alarmLog;
    UInt16   logSize;

	if (FindProgram(alarmPgm, &creatorId, NULL, NULL, refNum) != 0) {
	    StrCopy(alarmMsg, "");     // Unrecognized AlarmProxy program
	    return 0;
	}
	   
	logSize = sizeof(alarmLog);
    if (PrefGetAppPreferences(creatorId, alarmLogPrefID, 
                              &alarmLog, &logSize, false) != 0)
        alarmLog.msg[0] = 0;
    
    StrCopy(alarmMsg, alarmLog.msg);
	return 0;
}

/********************************************************************
 *               T H I S _ C l e a r A l a r m L o g
 ********************************************************************/
Err THIS_ClearAlarmLog(UInt16 refNum, char *alarmPgm) 
// DESC Clears the alarm log data for a specified alarm program.
// PARAM1 Alarm program.
// BEFORE
// BEFORE alarmPgm = "NSBAlarmProxy1"
{
    UInt32   creatorId;
    AlarmLog alarmLog;
	
	if (FindProgram(alarmPgm, &creatorId, NULL, NULL, refNum) != 0)
	    return 0;
	
	alarmLog.alarmTime = 0;
	alarmLog.resetTime = 0;
	alarmLog.cmd = -1;
	alarmLog.msg[0] = 0;   
    PrefSetAppPreferences(creatorId, alarmLogPrefID, alarmVersionNum, 
                          &alarmLog, sizeof(alarmLog), 0);
    
	return 0;
}

// SECTION Database Functions
// DESC The database functions provide methods for determining the
// DESC databases residing on the PalmOS device.  They also provide
// DESC information about these databases and allow some of this 
// DESC information to be changed.  These functions do not provide
// DESC methods for reading and writing the data actually contained
// DESC in a database.

/********************************************************************
 *                 T H I S _ F i n d D a t a b a s e
 ********************************************************************/
Err THIS_FindDatabase(UInt16 refNum, Int32 cardNo, char *dbName, Int32 *dbID)
// DESC Returns the database ID (LocalID) of the named database.
// PARAM1 This value will most likely be 0.
// PARAM2 Database name.
// RETURNS dbID if the named database is found.
// RETURNS 0 if the named database is not found.
// BEFORE
// BEFORE cardNo = 0
// BEFORE dbName = "NSBRuntime"
{
        
    *dbID = (Int32) DmFindDatabase((UInt16) cardNo, dbName); 
    
    return 0;
}

/********************************************************************
 *                 T H I S _ D a t a b a s e I n f o
 ********************************************************************/
Err THIS_DatabaseInfo(UInt16 refNum, Int32 cardNo, Int32 dbID, char *dbName)
// DESC Returns the database name for the specified card number and
// DESC database ID (LocalID).  It also retrieves many other fields of
// DESC database information.  See the example and notes for
// DESC for more information on how to access this data.
// NOTES  See also:  DatabaseName(), DatabaseAttributes(), 
// NOTES             DatabaseVersion(), DatabaseCreationDate(),
// NOTES             DatabaseModificationDate(), DatabaseBackupDate(),
// NOTES             DatabaseModificationNumber(), DatabaseType(),
// NOTES             DatabaseCreatorID()
// EXAMPLE Dim cardNo as Integer
// EXAMPLE Dim dbID as Integer
// EXAMPLE Dim dbName as String
// EXAMPLE Dim dbVersion as Integer
// EXAMPLE Dim dbCreationDate as Integer
// EXAMPLE Dim dbModificationDate as Integer
// EXAMPLE Dim dbBackupDate as Integer
// EXAMPLE Dim dbModificationNumber as Integer
// EXAMPLE Dim dbAppInfoID as Integer
// EXAMPLE Dim dbSortInfoID as Integer
// EXAMPLE Dim dbType as Integer
// EXAMPLE Dim dbCreatorID as Integer
// EXAMPLE
// EXAMPLE cardNo = 0
// EXAMPLE dbName = "NSBRuntime"
// EXAMPLE dbID = NSBNSL.FindDatabase(cardNo, dbName)
// EXAMPLE If dbID <> 0 Then
// EXAMPLE     dbName = NSL.DatabaseInfo(cardNo, dbID)
// EXAMPLE     If dbName <> "" Then
// EXAMPLE         dbVersion = NSL.DatabaseVersion()
// EXAMPLE         dbCreationDate = NSL.DatabaseCreationDate()
// EXAMPLE         dbModificationDate = NSL.DatabaseModificationDate()
// EXAMPLE         dbBackupDate = NSL.DatabaseBackupDate()
// EXAMPLE         dbModificationNumber = NSL.DatabaseModificationNumber()
// EXAMPLE         dbAppInfoID = NSL.DatabaseAppInfoID()
// EXAMPLE         dbSortInfoID = NSL.DatabaseSortInfoID()
// EXAMPLE         dbType = NSL.DatabaseType()
// EXAMPLE         dbCreatorID = NSL.DatabaseCreatorID()
// EXAMPLE     EndIf
// EXAMPLE EndIf
{
    THIS_ATTACH_GLOBALS
        
    if (DmDatabaseInfo((UInt16) cardNo, (LocalID) dbID, 
                       gP->dbName, &gP->dbAttributes, &gP->dbVersion, 
                       &gP->dbCreationDate, &gP->dbModificationDate, &gP->dbBackupDate, 
                       &gP->dbModificationNumber,
                       &gP->dbAppInfoID, &gP->dbSortInfoID, 
                       &gP->dbType, &gP->dbCreatorID) == errNone)
        StrCopy(dbName, gP->dbName);
    else
        StrCopy(dbName, "");

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *                 T H I S _ D a t a b a s e N a m e
 ********************************************************************/
Err THIS_DatabaseName(UInt16 refNum, char *dbName) 
// DESC Returns a database name that was previously retrieved by
// DESC a call to DatabaseInfo().
// EXAMPLE See the example provided with the DatabaseInfo() function.
{
    THIS_ATTACH_GLOBALS
    StrCopy(dbName, gP->dbName);
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *           T H I S _ D a t a b a s e A t t r i b u t e s
 ********************************************************************/
Err THIS_DatabaseAttributes(UInt16 refNum, Int32 *dbAttributes) 
// DESC Returns database attributes that were previously retrieved by
// DESC a call to DatabaseInfo().
// RETURNS The attributes value is a bitmapped value.  The following
// RETURNS list contains the bit mask values available:
// RETURNS     Bit  0  (0x0001) - dmHdrAttrResDB
// RETURNS     Bit  1  (0x0002) - dmHdrAttrReadOnly
// RETURNS     Bit  2  (0x0004) - dmHdrAttrAppInfoDirty
// RETURNS     Bit  3  (0x0008) - dmHdrAttrBackup
// RETURNS     Bit  4  (0x0010) - dmhdrAttrOKToInstallNewer
// RETURNS     Bit  5  (0x0020) - dmHdrAttrResetAfterInstall
// RETURNS     Bit  6  (0x0040) - dmHdrAttrCopyPrevention
// RETURNS     Bit  7  (0x0080) - dmHdrAttrStream
// RETURNS     Bit  8  (0x0100) - dmHdrAttrHidden
// RETURNS     Bit  9  (0x0200) - hmHdrAttrLaunchableData
// RETURNS     Bit 15  (0x8000) - dmHdrAttrOpen
// EXAMPLE See the example provided with the DatabaseInfo() function.
{
    THIS_ATTACH_GLOBALS
    *dbAttributes = (Int32) gP->dbAttributes;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *           T H I S _ D a t a b a s e V e r s i o n
 ********************************************************************/
Err THIS_DatabaseVersion(UInt16 refNum, Int32 *dbVersion) 
// DESC Returns the database version that was previously retrieved by
// DESC a call to DatabaseInfo().
// EXAMPLE See the example provided with the DatabaseInfo() function.
{
    THIS_ATTACH_GLOBALS
    *dbVersion = (Int32) gP->dbVersion;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *        T H I S _ D a t a b a s e C r e a t i o n D a t e
 ********************************************************************/
Err THIS_DatabaseCreationDate(UInt16 refNum, Int32 *dbCreationDate) 
// DESC Returns the database creation date that was previously 
// DESC retrieved by a call to DatabaseInfo().  This date is in
// DESC system time format.  It is expressed as the number of seconds
// DESC since January 1st, 1904.
// NOTES See also:  StringDateTime(), StringDate(), StringTime()
// EXAMPLE See the example provided with the DatabaseInfo() function.
{
    THIS_ATTACH_GLOBALS
    *dbCreationDate = (Int32) gP->dbCreationDate;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *    T H I S _ D a t a b a s e M o d i f i c a t i o n D a t e
 ********************************************************************/
Err THIS_DatabaseModificationDate(UInt16 refNum, Int32 *dbModificationDate) 
// DESC Returns the database modification date that was previously 
// DESC retrieved by a call to DatabaseInfo().  This date is in
// DESC system time format.  It is expressed as the number of seconds
// DESC since January 1st, 1904.
// NOTES See also:  StringDateTime(), StringDate(), StringTime()
// EXAMPLE See the example provided with the DatabaseInfo() function.
{
    THIS_ATTACH_GLOBALS
    *dbModificationDate = (Int32) gP->dbModificationDate;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *        T H I S _ D a t a b a s e B a c k u p D a t e
 ********************************************************************/
Err THIS_DatabaseBackupDate(UInt16 refNum, Int32 *dbBackupDate) 
// DESC Returns the database backup date that was previously 
// DESC retrieved by a call to DatabaseInfo().  This date is in
// DESC system time format.  It is expressed as the number of seconds
// DESC since January 1st, 1904.
// NOTES See also:  StringDateTime(), StringDate(), StringTime()
// EXAMPLE See the example provided with the DatabaseInfo() function.
{
    THIS_ATTACH_GLOBALS
    *dbBackupDate = (Int32) gP->dbBackupDate;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *   T H I S _ D a t a b a s e M o d i f i c a t i o n N u m b e r
 ********************************************************************/
Err THIS_DatabaseModificationNumber(UInt16 refNum, Int32 *dbModificationNumber) 
// DESC Returns the database modification number that was previously 
// DESC retrieved by a call to DatabaseInfo().  This number is
// DESC incremented every time that a record is added, modified, or
// DESC deleted.
// EXAMPLE See the example provided with the DatabaseInfo() function.
{
    THIS_ATTACH_GLOBALS
    *dbModificationNumber = (Int32) gP->dbModificationNumber;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *             T H I S _ D a t a b a s e A p p I n f o I D
 ********************************************************************/
Err THIS_DatabaseAppInfoID(UInt16 refNum, Int32 *dbAppInfoID) 
// DESC Returns the LocalID of the database Application Info block
// DESC that was previously retrieved by a call to DatabaseInfo().  
// RETURNS 0 if this optional block is not available.
// EXAMPLE See the example provided with the DatabaseInfo() function.
{
    THIS_ATTACH_GLOBALS
    *dbAppInfoID = (Int32) gP->dbAppInfoID;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *             T H I S _ D a t a b a s e S o r t I n f o I D
 ********************************************************************/
Err THIS_DatabaseSortInfoID(UInt16 refNum, Int32 *dbSortInfoID) 
// DESC Returns the LocalID of the database's sort table
// DESC that was previously retrieved by a call to DatabaseInfo().  
// RETURNS 0 if this optional sort table is not available.
// EXAMPLE See the example provided with the DatabaseInfo() function.
{
    THIS_ATTACH_GLOBALS
    *dbSortInfoID = (Int32) gP->dbSortInfoID;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *             T H I S _ D a t a b a s e T y p e
 ********************************************************************/
Err THIS_DatabaseType(UInt16 refNum, Int32 *dbType) 
// DESC Returns the database type that was previously retrieved 
// DESC by a call to DatabaseInfo().  
// NOTES See also:  IntToString4()
// EXAMPLE See the example provided with the DatabaseInfo() function.
{
    THIS_ATTACH_GLOBALS
    *dbType = (Int32) gP->dbType;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *             T H I S _ D a t a b a s e C r e a t o r I D
 ********************************************************************/
Err THIS_DatabaseCreatorID(UInt16 refNum, Int32 *dbCreatorID) 
// DESC Returns the database Creator ID that was previously retrieved
// DESC by a call to DatabaseInfo().  
// NOTES See also:  IntToString4()
// EXAMPLE See the example provided with the DatabaseInfo() function.
{
    THIS_ATTACH_GLOBALS
    *dbCreatorID = (Int32) gP->dbCreatorID;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *          T H I S _ D a t a b a s e T o t a l S i z e
 ********************************************************************/
Err THIS_DatabaseTotalSize(UInt16 refNum, Int32 cardNo, Int32 dbID, Int32 *dbTotalSize)
// DESC Returns the total database size, including overhead, for 
// DESC the specified card number and database ID.  It also 
// DESC retrieves the number of records and the size of just the
// DESC data in the database.  See the example and notes for
// DESC for more information on how to access this data.
// NOTES  See also:  DatabaseNumRecords(), DatabaseDataSize()
// EXAMPLE Dim cardNo as Integer
// EXAMPLE Dim dbID as Integer
// EXAMPLE Dim dbTotalSize as Integer
// EXAMPLE Dim dbNumRecords as Integer
// EXAMPLE Dim dbDataSize as Integer
// EXAMPLE
// EXAMPLE cardNo = 0
// EXAMPLE dbName = "NSBRuntime"
// EXAMPLE dbID = NSL.FindDatabase(cardNo, dbName)
// EXAMPLE If dbID <> 0 Then
// EXAMPLE     dbTotalSize = NSL.DatabaseSize(cardNo, dbID)
// EXAMPLE     dbNumRecords = NSL.DatabaseNumRecords()
// EXAMPLE     dbDataSize = NSL.DatabaseDataSize()
// EXAMPLE EndIf
{
    THIS_ATTACH_GLOBALS
        
    if (DmDatabaseSize((UInt16) cardNo, (LocalID) dbID, 
                       &gP->dbNumRecords, (UInt32 *) dbTotalSize, &gP->dbDataSize) != errNone)
        *dbTotalSize = -1;

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *             T H I S _ D a t a b a s e N u m R e c o r d s
 ********************************************************************/
Err THIS_DatabaseNumRecords(UInt16 refNum, Int32 *dbNumRecords) 
// DESC Returns the number of database records that was previously 
// DESC retrieved by a call to DatabaseTotalSize().  
// EXAMPLE See the example provided with the DatabaseTotalSize() function.
{
    THIS_ATTACH_GLOBALS
    *dbNumRecords = (Int32) gP->dbNumRecords;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *             T H I S _ D a t a b a s e D a t a S i z e
 ********************************************************************/
Err THIS_DatabaseDataSize(UInt16 refNum, Int32 *dbDataSize) 
// DESC Returns the database data size (minus overhead) that was 
// DESC previously retrieved by a call to DatabaseTotalSize().  
// EXAMPLE See the example provided with the DatabaseTotalSize() function.
{
    THIS_ATTACH_GLOBALS
    *dbDataSize = (Int32) gP->dbDataSize;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *                  T H I S _ D e l e t e D a t a b a s e
 ********************************************************************/
Err THIS_DeleteDatabase(UInt16 refNum, Int32 cardNo, Int32 dbID, Int32 *status)
// DESC Deletes the specified database. 
// NOTES  See also:  FindDatabase() 
// RETURNS 0 = successful
// RETURNS 257 = memErrChunkLocked
// RETURNS 258 = memErrNotEnoughSpace
// RETURNS 259 = memErrInvalidParam
// RETURNS 517 = dmErrDatabaseOpen
// RETURNS 518 = dmErrCantOpen
// RETURNS 519 = dmErrCantFind
// RETURNS 526 = dmErrROMBased
// EXAMPLE Dim cardNo as Integer
// EXAMPLE Dim dbID as Integer
// EXAMPLE Dim status as Integer
// EXAMPLE
// EXAMPLE cardNo = 0
// EXAMPLE dbName = "NSBAlarmProxy5"
// EXAMPLE dbID = NSL.FindDatabase(cardNo, dbName)
// EXAMPLE If dbID <> 0 Then
// EXAMPLE     status = NSL.DeleteDatabase(cardNo, dbID)
// EXAMPLE EndIf
{
    THIS_ATTACH_GLOBALS
        
    *status = (Int32) DmDeleteDatabase((UInt16) cardNo, (LocalID) dbID);

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 * T H I S _ G e t N e x t D a t a b a s e B y T y p e C r e a t o r
 ********************************************************************/
Err THIS_GetNextDatabaseByTypeCreator(UInt16 refNum, Int32 newSearch,
                        Int32 dbType, Int32 dbCreatorID, 
                        Int32 onlyLatestVersion, Int32 *dbID)
// DESC This function is used to retrieve a list of all the specified
// DESC databases on the device.
// PARAM1 0 = continue searching for databases
// PARAM1 1 = start a new search
// PARAM2 Integer database type.
// PARAM2 0 = wildcard search.
// PARAM3 Integer Creator ID.
// PARAM3 0 = wildcard search.
// PARAM4 0 = return all versions.
// PARAM4 1 = return only the latest database version for
// PARAM4     supplied type and Creator ID.
// RETURNS dbID (LocalID) of the database.
// NOTES See Also:  DatabaseCardNo(), DatabaseInfo()
// EXAMPLE Dim dbID as Integer
// EXAMPLE Dim newSearch as Integer
// EXAMPLE Dim dbType as Integer
// EXAMPLE Dim dbCreatorID as Integer
// EXAMPLE Dim onlyLatestVersion as Integer
// EXAMPLE Dim dbCardNo as Integer
// EXAMPLE Dim dbName as String
// EXAMPLE
// EXAMPLE onlyLatestVersion = 0
// EXAMPLE dbType = NSL.String4ToInt("libr")
// EXAMPLE dbCreatorID = 0
// EXAMPLE newSearch = 1
// EXAMPLE dbID = 1
// EXAMPLE Do While dbID <> 0
// EXAMPLE     dbID = NSL.GetNextDatabaseByTypeCreator(newSearch, _
// EXAMPLE                 dbType, dbCreatorID, onlyLatestVersion)
// EXAMPLE     If dbID <> 0 Then
// EXAMPLE         dbCardNo = NSL.DatabaseCardNo()
// EXAMPLE         dbName = NSL.DatabaseInfo(dbCardNo, dbID)
// EXAMPLE     End If
// EXAMPLE     newSearch = 0
// EXAMPLE Loop
{
    LocalID localID;
    THIS_ATTACH_GLOBALS
    
    if (DmGetNextDatabaseByTypeCreator((Boolean) newSearch, &gP->dbStateInfo, 
                                       (UInt32) dbType, (UInt32) dbCreatorID,
                                       (Boolean) onlyLatestVersion, 
                                       &gP->dbCardNo, &localID) == errNone)
        *dbID = (Int32) localID;
    else
        *dbID = 0;

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *             T H I S _ D a t a b a s e C a r d N o
 ********************************************************************/
Err THIS_DatabaseCardNo(UInt16 refNum, Int32 *dbCardNo) 
// DESC Returns the database card number that was previously 
// DESC retrieved by a call to GetNextDatabaseByTypeCreator().  
// EXAMPLE See the example provided with the 
// EXAMPLE GetNextDatabaseByTypeCreator() function.
{
    THIS_ATTACH_GLOBALS
    *dbCardNo = (Int32) gP->dbCardNo;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *                 T H I S _ N u m D a t a b a s e s
 ********************************************************************/
Err THIS_NumDatabases(UInt16 refNum, Int32 cardNo, Int32 *nbr)
// DESC This function is used to retrieve the number of databases
// DESC on the specified card number.
// NOTES This routine is helpful for getting a directory of all 
// NOTES databases on a card. The function GetDatabase() accepts
// NOTES an index from 0 to (NumDatabases -1) and returns a database
// NOTES ID by index. 
// NOTES See also: GetDatabase()
// BEFORE
// BEFORE cardNo = 0
{
    
    *nbr = (Int32) DmNumDatabases((UInt16) cardNo);

    return 0;
}

/********************************************************************
 *                    T H I S _ N u m C a r d s
 ********************************************************************/
Err THIS_NumCards(UInt16 refNum, Int32 *nbr)
// DESC This function returns the number of memory card slots in 
// DESC the system. Not all slots need to be populated. 
{
    
    *nbr = (Int32) MemNumCards();

    return 0;
}

/********************************************************************
 *                 T H I S _ G e t D a t a b a s e
 ********************************************************************/
Err THIS_GetDatabase(UInt16 refNum, Int32 cardNo, Int32 index, Int32 *dbID)
// DESC This function is used to retrieve a database ID for the 
// DESC supplied card number and index.
// NOTES See also: NumDatabases()
// RETURNS 0 = Invalid index
// EXAMPLE Dim nbr as Integer
// EXAMPLE Dim dbID as Integer
// EXAMPLE Dim cardNo as Integer
// EXAMPLE Dim index as Integer
// EXAMPLE Dim dbName as String
// EXAMPLE
// EXAMPLE cardNo = 0
// EXAMPLE nbr = NSL.NumDatabases(cardNo)
// EXAMPLE index = 0
// EXAMPLE Do While index < nbr
// EXAMPLE     dbID = NSL.GetDatabase(cardNo, index)
// EXAMPLE     If dbID <> 0 Then
// EXAMPLE         dbName = NSL.DatabaseInfo(cardNo, dbID)
// EXAMPLE     End If
// EXAMPLE     index = index + 1
// EXAMPLE Loop
{
    
    *dbID = (Int32) DmGetDatabase((UInt16) cardNo, (UInt16) index);

    return 0;
}

/********************************************************************
 *               T H I S _ S e t D a t a b a s e N a m e
 ********************************************************************/
Err THIS_SetDatabaseName(UInt16 refNum, Int32 cardNo, Int32 dbID, char *dbName, Int32 *status)
// DESC This function is used to change the name of the specified
// DESC database.
// RETURNS 0 = success
// RETURNS 515 = dmErrInvalidParam
// RETURNS 537 = dmErrAlreadyExists
// RETURNS 538 = InvalidDatabaseName
// EXAMPLE Dim status as Integer
// EXAMPLE Dim dbID as Integer
// EXAMPLE Dim cardNo as Integer
// EXAMPLE Dim dbName as String
// EXAMPLE
// EXAMPLE cardNo = 0
// EXAMPLE dbName = "NSBAlarmProxy5"
// EXAMPLE dbID = NSL.FindDatabase(cardNo, dbName)
// EXAMPLE dbName = "oldNSBAlarmProxy5"
// EXAMPLE status = NSL.SetDatabaseName(cardNo, dbID, dbName)
{
    
    *status = (Int32) DmSetDatabaseInfo((UInt16) cardNo, (LocalID) dbID,
                          dbName, NULL, NULL, NULL, NULL, NULL, NULL, 
                          NULL, NULL, NULL, NULL); 

    return 0;
}

/********************************************************************
 *        T H I S _ S e t D a t a b a s e A t t r i b u t e s
 ********************************************************************/
Err THIS_SetDatabaseAttributes(UInt16 refNum, Int32 cardNo, Int32 dbID, Int32 dbAttributes, Int32 *status)
// DESC This function is used to change the attributes of the specified
// DESC database.
// PARAM3 The attributes value is a bitmapped value.  The following
// PARAM3 list contains the bit mask values available:
// PARAM3     Bit  0  (0x0001) - dmHdrAttrResDB
// PARAM3     Bit  1  (0x0002) - dmHdrAttrReadOnly
// PARAM3     Bit  2  (0x0004) - dmHdrAttrAppInfoDirty
// PARAM3     Bit  3  (0x0008) - dmHdrAttrBackup
// PARAM3     Bit  4  (0x0010) - dmhdrAttrOKToInstallNewer
// PARAM3     Bit  5  (0x0020) - dmHdrAttrResetAfterInstall
// PARAM3     Bit  6  (0x0040) - dmHdrAttrCopyPrevention
// PARAM3     Bit  7  (0x0080) - dmHdrAttrStream
// PARAM3     Bit  8  (0x0100) - dmHdrAttrHidden
// PARAM3     Bit  9  (0x0200) - hmHdrAttrLaunchableData
// PARAM3     Bit 15  (0x8000) - dmHdrAttrOpen
// RETURNS 0 = success
// RETURNS 515 = dmErrInvalidParam
// RETURNS 537 = dmErrAlreadyExists
// RETURNS 538 = InvalidDatabaseName
// EXAMPLE Dim status as Integer
// EXAMPLE Dim dbID as Integer
// EXAMPLE Dim cardNo as Integer
// EXAMPLE Dim dbAttributes as Integer
// EXAMPLE
// EXAMPLE cardNo = 0
// EXAMPLE dbName = "NSBAlarmProxy5"
// EXAMPLE dbID = NSL.FindDatabase(cardNo, dbName)
// EXAMPLE dbAttributes = 2
// EXAMPLE status = NSL.SetDatabaseAttributes(cardNo, dbID, dbAttributes)
{
    UInt16 dbAttr;
    
    dbAttr = (UInt16) dbAttributes;
    *status = (Int32) DmSetDatabaseInfo((UInt16) cardNo, (LocalID) dbID,
                          NULL, &dbAttr, NULL, NULL, NULL, NULL, NULL, 
                          NULL, NULL, NULL, NULL); 

    return 0;
}

/********************************************************************
 *            T H I S _ S e t D a t a b a s e V e r s i o n
 ********************************************************************/
Err THIS_SetDatabaseVersion(UInt16 refNum, Int32 cardNo, Int32 dbID, Int32 dbVersion, Int32 *status)
// DESC This function is used to change the version number of the
// DESC specified database.
// RETURNS 0 = success
// RETURNS 515 = dmErrInvalidParam
// RETURNS 537 = dmErrAlreadyExists
// RETURNS 538 = InvalidDatabaseName
// EXAMPLE Dim status as Integer
// EXAMPLE Dim dbID as Integer
// EXAMPLE Dim cardNo as Integer
// EXAMPLE Dim dbVersion as Integer
// EXAMPLE
// EXAMPLE cardNo = 0
// EXAMPLE dbName = "NSBAlarmProxy5"
// EXAMPLE dbID = NSL.FindDatabase(cardNo, dbName)
// EXAMPLE dbVersion = 6
// EXAMPLE status = NSL.SetDatabaseVersion(cardNo, dbID, dbVersion)
{
    UInt16 dbVer;
    
    dbVer = (UInt16) dbVersion;
    *status = (Int32) DmSetDatabaseInfo((UInt16) cardNo, (LocalID) dbID,
                          NULL, NULL, &dbVer, NULL, NULL, NULL, NULL, 
                          NULL, NULL, NULL, NULL); 

    return 0;
}

/********************************************************************
 *       T H I S _ S e t D a t a b a s e C r e a t i o n D a t e
 ********************************************************************/
Err THIS_SetDatabaseCreationDate(UInt16 refNum, Int32 cardNo, Int32 dbID, 
                                 Int32 dbCreationDate, Int32 *status)
// DESC This function is used to change the creation date of the
// DESC specified database.
// RETURNS 0 = success
// RETURNS 515 = dmErrInvalidParam
// RETURNS 537 = dmErrAlreadyExists
// RETURNS 538 = InvalidDatabaseName
// EXAMPLE Dim status as Integer
// EXAMPLE Dim dbID as Integer
// EXAMPLE Dim cardNo as Integer
// EXAMPLE Dim dbCreationDate as Integer
// EXAMPLE
// EXAMPLE cardNo = 0
// EXAMPLE dbName = "NSBAlarmProxy5"
// EXAMPLE dbID = NSL.FindDatabase(cardNo, dbName)
// EXAMPLE dbCreationDate = NSL.SystemTime("", "", 0, 0)
// EXAMPLE status = NSL.SetDatabaseCreationDate(cardNo, dbID, _
// EXAMPLE                                     dbCreationDate)
{
    UInt32 dbDate;
    
    dbDate = (UInt32) dbCreationDate;
    *status = (Int32) DmSetDatabaseInfo((UInt16) cardNo, (LocalID) dbID,
                          NULL, NULL, NULL, &dbDate, NULL, NULL, NULL, 
                          NULL, NULL, NULL, NULL); 

    return 0;
}

/********************************************************************
 *  T H I S _ S e t D a t a b a s e M o d i f i c a t i o n D a t e
 ********************************************************************/
Err THIS_SetDatabaseModificationDate(UInt16 refNum, Int32 cardNo, Int32 dbID, 
                                 Int32 dbModificationDate, Int32 *status)
// DESC This function is used to change the modification date of the
// DESC specified database.
// RETURNS 0 = success
// RETURNS 515 = dmErrInvalidParam
// RETURNS 537 = dmErrAlreadyExists
// RETURNS 538 = InvalidDatabaseName
// EXAMPLE Dim status as Integer
// EXAMPLE Dim dbID as Integer
// EXAMPLE Dim cardNo as Integer
// EXAMPLE Dim dbModificationDate as Integer
// EXAMPLE
// EXAMPLE cardNo = 0
// EXAMPLE dbName = "NSBAlarmProxy5"
// EXAMPLE dbID = NSL.FindDatabase(cardNo, dbName)
// EXAMPLE dbModificationDate = NSL.SystemTime("", "", 0, 0)
// EXAMPLE status = NSL.SetDatabaseModificationDate(cardNo, dbID, _
// EXAMPLE                                         dbModificationDate)
{
    UInt32 dbDate;
    
    dbDate = (UInt32) dbModificationDate;
    *status = (Int32) DmSetDatabaseInfo((UInt16) cardNo, (LocalID) dbID,
                          NULL, NULL, NULL, NULL, &dbDate, NULL, NULL, 
                          NULL, NULL, NULL, NULL); 

    return 0;
}

/********************************************************************
 *        T H I S _ S e t D a t a b a s e B a c k u p D a t e
 ********************************************************************/
Err THIS_SetDatabaseBackupDate(UInt16 refNum, Int32 cardNo, Int32 dbID, 
                                 Int32 dbBackupDate, Int32 *status)
// DESC This function is used to change the backup date of the
// DESC specified database.
// RETURNS 0 = success
// RETURNS 515 = dmErrInvalidParam
// RETURNS 537 = dmErrAlreadyExists
// RETURNS 538 = InvalidDatabaseName
// EXAMPLE Dim status as Integer
// EXAMPLE Dim dbID as Integer
// EXAMPLE Dim cardNo as Integer
// EXAMPLE Dim dbBackupDate as Integer
// EXAMPLE
// EXAMPLE cardNo = 0
// EXAMPLE dbName = "NSBAlarmProxy5"
// EXAMPLE dbID = NSL.FindDatabase(cardNo, dbName)
// EXAMPLE dbBackupDate = NSL.SystemTime("", "", 0, 0)
// EXAMPLE status = NSL.SetDatabaseModificationDate(cardNo, dbID, _
// EXAMPLE                                         dbBackupDate)
{
    UInt32 dbDate;
    
    dbDate = (UInt32) dbBackupDate;
    *status = (Int32) DmSetDatabaseInfo((UInt16) cardNo, (LocalID) dbID,
                          NULL, NULL, NULL, NULL, NULL, &dbDate, NULL, 
                          NULL, NULL, NULL, NULL); 

    return 0;
}

/********************************************************************
 * T H I S _ S e t D a t a b a s e M o d i f i c a t i o n N u m b e r
 ********************************************************************/
Err THIS_SetDatabaseModificationNumber(UInt16 refNum, Int32 cardNo, Int32 dbID, 
                                 Int32 dbModificationNumber, Int32 *status)
// DESC This function is used to change the modification number of 
// DESC the specified database.
// RETURNS 0 = success
// RETURNS 515 = dmErrInvalidParam
// RETURNS 537 = dmErrAlreadyExists
// RETURNS 538 = InvalidDatabaseName
// EXAMPLE Dim status as Integer
// EXAMPLE Dim dbID as Integer
// EXAMPLE Dim cardNo as Integer
// EXAMPLE Dim dbModificationNumber as Integer
// EXAMPLE
// EXAMPLE cardNo = 0
// EXAMPLE dbName = "NSBAlarmProxy5"
// EXAMPLE dbID = NSL.FindDatabase(cardNo, dbName)
// EXAMPLE dbModificationNumber = 0
// EXAMPLE status = NSL.SetDatabaseModificationNumber(cardNo, dbID, _
// EXAMPLE                                           dbModificationNumber)
{
    UInt32 dbModNbr;
    
    dbModNbr = (UInt32) dbModificationNumber;
    *status = (Int32) DmSetDatabaseInfo((UInt16) cardNo, (LocalID) dbID,
                          NULL, NULL, NULL, NULL, NULL, NULL, &dbModNbr, 
                          NULL, NULL, NULL, NULL); 

    return 0;
}

/********************************************************************
 *       T H I S _ S e t D a t a b a s e A p p I n f o I D
 ********************************************************************/
Err THIS_SetDatabaseAppInfoID(UInt16 refNum, Int32 cardNo, Int32 dbID, 
                              Int32 dbAppInfoID, Int32 *status)
// DESC This function is used to change the Application Information
// DESC LocalID of the specified database.
// RETURNS 0 = success
// RETURNS 515 = dmErrInvalidParam
// RETURNS 537 = dmErrAlreadyExists
// RETURNS 538 = InvalidDatabaseName
// EXAMPLE Dim status as Integer
// EXAMPLE Dim dbID as Integer
// EXAMPLE Dim cardNo as Integer
// EXAMPLE Dim dbAppInfoID as Integer
// EXAMPLE
// EXAMPLE cardNo = 0
// EXAMPLE dbName = "NSBAlarmProxy5"
// EXAMPLE dbID = NSL.FindDatabase(cardNo, dbName)
// EXAMPLE dbAppInfoID = 0
// EXAMPLE status = NSL.SetDatabaseAppInfoID(cardNo, dbID, _
// EXAMPLE                                  dbAppInfoID)
{
    LocalID localID;
    
    localID = (LocalID) dbAppInfoID;
    *status = (Int32) DmSetDatabaseInfo((UInt16) cardNo, (LocalID) dbID,
                          NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
                          &localID, NULL, NULL, NULL); 

    return 0;
}

/********************************************************************
 *      T H I S _ S e t D a t a b a s e S o r t I n f o I D
 ********************************************************************/
Err THIS_SetDatabaseSortInfoID(UInt16 refNum, Int32 cardNo, Int32 dbID, 
                              Int32 dbSortInfoID, Int32 *status)
// DESC This function is used to change the Sort Table LocalID of 
// DESC the specified database.
// RETURNS 0 = success
// RETURNS 515 = dmErrInvalidParam
// RETURNS 537 = dmErrAlreadyExists
// RETURNS 538 = InvalidDatabaseName
// EXAMPLE Dim status as Integer
// EXAMPLE Dim dbID as Integer
// EXAMPLE Dim cardNo as Integer
// EXAMPLE Dim dbSortInfoID as Integer
// EXAMPLE
// EXAMPLE cardNo = 0
// EXAMPLE dbName = "NSBAlarmProxy5"
// EXAMPLE dbID = NSL.FindDatabase(cardNo, dbName)
// EXAMPLE dbSortInfoID = 0
// EXAMPLE status = NSL.SetDatabaseSortInfoID(cardNo, dbID, _
// EXAMPLE                                  dbSortInfoID)
{
    LocalID localID;
    
    localID = (LocalID) dbSortInfoID;
    *status = (Int32) DmSetDatabaseInfo((UInt16) cardNo, (LocalID) dbID,
                          NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
                          NULL, &localID, NULL, NULL); 

    return 0;
}

/********************************************************************
 *              T H I S _ S e t D a t a b a s e T y p e
 ********************************************************************/
Err THIS_SetDatabaseType(UInt16 refNum, Int32 cardNo, Int32 dbID, 
                              Int32 dbType, Int32 *status)
// DESC This function is used to change the database type of the
// DESC specified database.
// RETURNS 0 = success
// RETURNS 515 = dmErrInvalidParam
// RETURNS 537 = dmErrAlreadyExists
// RETURNS 538 = InvalidDatabaseName
// EXAMPLE Dim status as Integer
// EXAMPLE Dim dbID as Integer
// EXAMPLE Dim cardNo as Integer
// EXAMPLE Dim dbType as Integer
// EXAMPLE
// EXAMPLE cardNo = 0
// EXAMPLE dbName = "NSBAlarmProxy5"
// EXAMPLE dbID = NSL.FindDatabase(cardNo, dbName)
// EXAMPLE dbType = String4ToInt("appl")
// EXAMPLE status = NSL.SetDatabaseType(cardNo, dbID, dbType);
{
    UInt32 dbInt;
    
    dbInt = (UInt32) dbType;
    *status = (Int32) DmSetDatabaseInfo((UInt16) cardNo, (LocalID) dbID,
                          NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
                          NULL, NULL, &dbInt, NULL); 

    return 0;
}

/********************************************************************
 *         T H I S _ S e t D a t a b a s e C r e a t o r I D
 ********************************************************************/
Err THIS_SetDatabaseCreatorID(UInt16 refNum, Int32 cardNo, Int32 dbID, 
                              Int32 dbCreatorID, Int32 *status)
// DESC This function is used to change the Creator ID of the
// DESC specified database.
// RETURNS 0 = success
// RETURNS 515 = dmErrInvalidParam
// RETURNS 537 = dmErrAlreadyExists
// RETURNS 538 = InvalidDatabaseName
// EXAMPLE Dim status as Integer
// EXAMPLE Dim dbID as Integer
// EXAMPLE Dim cardNo as Integer
// EXAMPLE Dim dbCreatorID as Integer
// EXAMPLE
// EXAMPLE cardNo = 0
// EXAMPLE dbName = "NSBAlarmProxy5"
// EXAMPLE dbID = NSL.FindDatabase(cardNo, dbName)
// EXAMPLE dbCreatorID = String4ToInt("TEST")
// EXAMPLE status = NSL.SetDatabaseCreatorID(cardNo, dbID, dbCreatorID);
{
    UInt32 dbInt;
    
    dbInt = (UInt32) dbCreatorID;
    *status = (Int32) DmSetDatabaseInfo((UInt16) cardNo, (LocalID) dbID,
                          NULL, NULL, NULL, NULL, NULL, NULL, NULL, 
                          NULL, NULL, NULL, &dbInt); 

    return 0;
}

// SECTION Event Functions
// DESC The event functions are provided to give you more control
// DESC of event detection and processing than is currently available
// DESC using the standard NSBasic Events code section and
// DESC SysEventAvailable() function.

/********************************************************************
 *                  T H I S _ G e t E v e n t
 ********************************************************************/
Err THIS_GetEvent(UInt16 refNum, Int32 timeoutTicks, 
                  Int32 consumePenEvents, Int32 returnVirtualEvents,
                  Int32 *eventType)
// DESC Returns an system event type, if one is available.  The
// DESC timeoutTicks parameter is used to provide a "non-blocking"
// DESC delay.  If an event occurs before the timeout period expires
// DESC the function will return immediately.  This can be useful
// DESC for use with animation or game programming.
// NOTES If this function is used as part of a button's event code,
// NOTES you may want to flush pending key and pen events before
// NOTES calling this function.  This is because the "pen up" event
// NOTES resulting from the button push will cause this function to
// NOTES to return immediately.  See the example and FlushEvents()
// NOTES function.
// NOTES
// PARAM1 The number of system ticks to wait before 
// PARAM1 		returning.
// PARAM2 0 = do not consume pen events
// PARAM2 1 = consume pen events
// PARAM2   This function calls the PalmOS EvtGetEvent function.
// PARAM2   EvtGetEvent removes events from the events queue.  In
// PARAM2   order for these events to still be available for other
// PARAM2   processing, this shared library function requeues the
// PARAM2   events that it detects.  This may not be desired if 
// PARAM2   this function is used for capturing pen events for
// PARAM2   drawing.  When consumePenEvents is set to 1, the pen 
// PARAM2   events are not requeued but the pen data is still 
// PARAM2   available.
// PARAM3 0 = do not return with virtual key events
// PARAM3 1 = return with virtual key events
// PARAM3   Virtual key events are events generated by the PalmOS
// PARAM3   system or other third party system level features.
// PARAM3   These events include things like low battery warning,
// PARAM3   backlight change of state, etc.  For the most part,
// PARAM3   virtual key events should not be returned.  If they 
// PARAM3   are returned, it is probably wise to let the system
// PARAM3   handle them by calling this library's SysHandleEvent()
// PARAM3   function.
// RETURNS -1 if no event was available within the 
// RETURNS 		timeout specified.
// RETURNS 0 = nilEvent
// RETURNS 1 = penDownEvent
// RETURNS       Retrieve pen coordintates with:
// RETURNS           GlobalX(), and GlobalY()
// RETURNS 2 = penUpEvent
// RETURNS       Retrieve pen coordintates with:
// RETURNS           GlobalX(), GlobalY()
// RETURNS       Retrieve pen stroke coordinates with:
// RETURNS           GlobalStartX(), GlobalStartY(),
// RETURNS           GlobalEndX(), and GlobalEndY()
// RETURNS 3 = penMoveEvent
// RETURNS       Retrieve pen coordintates with:
// RETURNS           GlobalX(), and GlobalY()
// RETURNS 4 = keyDownEvent
// RETURNS       Retrieve key data with:
// RETURNS           KeyEventChr(), KeyEventKeyCode(),
// RETURNS           and KeyEventModifiers()
// RETURNS 5 = winEnterEvent
// RETURNS 6 = winExitEvent
// RETURNS 7 = ctlEnterEvent
// RETURNS 8 = ctlExitEvent
// RETURNS 9 = ctlSelectEvent
// RETURNS 10 = ctlRepeatEvent
// RETURNS 11 = lstEnterEvent
// RETURNS 12 = lstSelectEvent
// RETURNS 13 = lstExitEvent
// RETURNS 14 = popSelectEvent
// RETURNS 15 = fldEnterEvent
// RETURNS 16 = fldHeightChangedEvent
// RETURNS 17 = fldChangedEvent
// RETURNS 18 = tblEnterEvent
// RETURNS 19 = tblSelectEvent
// RETURNS 20 = daySelectEvent
// RETURNS 21 = menuEvent
// RETURNS 22 = appStopEvent
// RETURNS 21 = frmOpenEvent
// RETURNS 22 = frmGotoEvent
// RETURNS 23 = frmUpdateEvent
// RETURNS 24 = frmSaveEvent
// RETURNS 25 = frmCloseEvent
// RETURNS 26 = frmTitleEnterEvent
// RETURNS 27 = frmTitleSelectEvent
// RETURNS 28 = tblExitEvent
// RETURNS 29 = sclEnterEvent
// RETURNS 30 = sclExitEvent
// RETURNS 31 = sclRepeatEvent
// RETURNS 35 = tsmConfirmEvent
// RETURNS 36 = tsmFepButtonEvent
// RETURNS 37 = tsmFepModeEvent
// RETURNS	
// RETURNS 2048 = menuCmdBarOpenEvent
// RETURNS 2049 = menuOpenEvent
// RETURNS 2050 = menuCloseEvent
// RETURNS 2051 = frmGadgetEnterEvent
// RETURNS 2052 = frmGadgetMiscEvent
// RETURNS
// RETURNS 4096 = firstINetLibEvent
// RETURNS 4352 = firstWebLibEvent
// RETURNS	
// RETURNS 24576 = firstUserEvent
// EXAMPLE Dim eventType as Integer
// EXAMPLE Dim timeoutTicks as Integer
// EXAMPLE
// EXAMPLE NSL.FlushEvents()
// EXAMPLE eventType = 0
// EXAMPLE Do While eventType <= 0
// EXAMPLE     'do something
// EXAMPLE     eventType = NSL.GetEvent(timeoutTicks, 0, 0)
// EXAMPLE Loop
{
    Int32      saveType;
    UInt32     startTicks;
    eventsEnum requeueEvents;
    THIS_ATTACH_GLOBALS
    
    if (consumePenEvents)
        requeueEvents = 3;
    else
        requeueEvents = 0;
    if (timeoutTicks <= 0)
        timeoutTicks = 1;
    saveType = -1;
    startTicks = TimGetTicks();
    EvtGetEvent(&gP->event, timeoutTicks);
    if ((TimGetTicks() - startTicks) < timeoutTicks) {
        saveType = gP->event.eType;
        if ((returnVirtualEvents == 0) &&
            (saveType == keyDownEvent) &&
            (gP->event.data.keyDown.chr > 255) &&
            (gP->event.data.keyDown.modifiers & commandKeyMask)) {
                SysHandleEvent(&gP->event);
                saveType = 0;
        }
        else
            if (saveType > requeueEvents) {
                gP->event.eType = 0xffff;
	            EvtAddEventToQueue(&gP->event);
                gP->event.eType = (eventsEnum) saveType;
                while (gP->event.eType != 0xffff) {
    	            EvtAddEventToQueue(&gP->event);
                    EvtGetEvent(&gP->event, 0);
                }
            }
            else
                SysHandleEvent(&gP->event);
    }

    *eventType = saveType;
    switch (*eventType) {
        case keyDownEvent:
            gP->chr = gP->event.data.keyDown.chr;
            gP->keyCode = gP->event.data.keyDown.keyCode;
            gP->modifiers = gP->event.data.keyDown.modifiers;
            break;
        case sysEventPenUpEvent:
            gP->startX = gP->event.data.penUp.start.x;
            gP->startY = gP->event.data.penUp.start.y;
            gP->endX = gP->event.data.penUp.end.x;
            gP->endY = gP->event.data.penUp.end.y;
        case sysEventPenDownEvent:
	    case sysEventPenMoveEvent:
	        gP->screenX = gP->event.screenX;
	        gP->screenY = gP->event.screenY;
	        break;
    }
        
    THIS_DETACH_GLOBALS
	return 0 ;
}

/********************************************************************
 *            T H I S _ S y s H a n d l e E v e n t
 ********************************************************************/
Err THIS_SysHandleEvent(UInt16 refNum) 
// DESC Consume and handle the event most recently returned
// DESC by the GetEvent() function.  It does this by calling
// DESC EvtGetEvent() and then SysHandleEvent();
{
    EventType event;
    
    EvtGetEvent(&event, 0);
    SysHandleEvent(&event);
    
    return 0;
}

/********************************************************************
 *                 T H I S _ F l u s h E v e n t s
 ********************************************************************/
Err THIS_FlushEvents(UInt16 refNum) 
// DESC Flushes all pending key and pen events.  It does this by
// DESC calling the PalmOS EvtFlushKeyQueue() and 
// DESC EvtFlushPenQueue() functions.  It then empties and handles
// DESC all remaing events by calling EvtGetEvent() and
// DESC SysHandleEvent().
{
    Err       err;
    EventType event;
    
    err = EvtFlushKeyQueue();
    err = EvtFlushPenQueue();
    while (EvtEventAvail()) {
        EvtGetEvent(&event, 0);
        SysHandleEvent(&event);
    }
    
    return 0;
}

/********************************************************************
 *                 T H I S _ K e y E v e n t C h r
 ********************************************************************/
Err THIS_KeyEventChr(UInt16 refNum, Int32 *keyChr) 
// DESC Returns the "chr" data member of of a key event.  The
// DESC GetEvent() function must have returned an event type of
// DESC 4 (keyDownEvent) for this value to be valid.
{
    THIS_ATTACH_GLOBALS
    *keyChr = (Int32) gP->chr;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *            T H I S _ K e y E v e n t K e y C o d e
 ********************************************************************/
Err THIS_KeyEventKeyCode(UInt16 refNum, Int32 *keyCode) 
// DESC Returns the "keyCode" data member of of a key event.  The
// DESC GetEvent() function must have returned an event type of
// DESC 4 (keyDownEvent) for this value to be valid.
{
    THIS_ATTACH_GLOBALS
    *keyCode = (Int32) gP->keyCode;
    THIS_DETACH_GLOBALS
    
    return 0;
}

/********************************************************************
 *          T H I S _ K e y E v e n t M o d i f i e r s
 ********************************************************************/
Err THIS_KeyEventModifiers(UInt16 refNum, Int32 *modifiers) 
// DESC Returns the "modifiers" data member of of a key event.  The
// DESC GetEvent() function must have returned an event type of
// DESC 4 (keyDownEvent) for this value to be valid.
{
    THIS_ATTACH_GLOBALS
    *modifiers = (Int32) gP->modifiers;
    THIS_DETACH_GLOBALS
    
    return 0;
}

// SECTION Field and Form Functions
// DESC The field and form functions provide convenient methods for
// DESC manipulating field and form objects.  These functions allow
// DESC you to perform operations that aren't available using the
// DESC standard NSBasic language.  While many of these operations
// DESC can be performed with SysTrapSub and SysTrapFunc statements,
// DESC these functions provide a simpler interface.

/********************************************************************
 *           T H I S _ C o n t r o l H i t C o n t r o l
 ********************************************************************/
Err THIS_ControlHitControl(UInt16 refNum, Int32 objID)
// DESC Simulate tapping a control. This function adds a 
// DESC ctlSelectEvent to the event queue. 
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// BEFORE
// BEFORE objID = 1008
{
    ControlType *controlPtr;
    
    controlPtr = ControlPointer(objID);
    if (controlPtr != NULL)
        CtlHitControl(controlPtr);

    return 0;
}

/********************************************************************
 *                 T H I S _ F i e l d C o p y
 ********************************************************************/
Err THIS_FieldCopy(UInt16 refNum, Int32 objID)
// DESC Copy the current selection to the text clipboard. 
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// BEFORE
// BEFORE objID = 1008
{
    FieldType *fieldPtr;
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL)
        FldCopy(fieldPtr);

    return 0;
}

/********************************************************************
 *                 T H I S _ F i e l d C u t
 ********************************************************************/
Err THIS_FieldCut(UInt16 refNum, Int32 objID)
// DESC Copy the current selection to the text clipboard, delete 
// DESC the selection from the field, and redraw the field. 
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// BEFORE
// BEFORE objID = 1008
{
    FieldType *fieldPtr;
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL)
        FldCut(fieldPtr);

    return 0;
}

/********************************************************************
 *                 T H I S _ F i e l d I n s e r t
 ********************************************************************/
Err THIS_FieldInsert(UInt16 refNum, Int32 objID, char* insString)
// DESC Replace the current selection if any with the specified 
// DESC string and redraw the field. 
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// BEFORE
// BEFORE objID = 1008
// BEFORE insString = "Insert This!"
{
    FieldType *fieldPtr;
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL)
        FldInsert(fieldPtr, insString, StrLen(insString));

    return 0;
}

/********************************************************************
 *                 T H I S _ F i e l d P a s t e
 ********************************************************************/
Err THIS_FieldPaste(UInt16 refNum, Int32 objID)
// DESC Replace the current selection in the field, if any, with the
// DESC contents of the text clipboard. 
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// BEFORE
// BEFORE objID = 1008
{
    FieldType *fieldPtr;
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL)
        FldPaste(fieldPtr);

    return 0;
}

/********************************************************************
 *                 T H I S _ F i e l d U n d o
 ********************************************************************/
Err THIS_FieldUndo(UInt16 refNum, Int32 objID)
// DESC Undo the last change made to the field object, if any. 
// DESC Changes include paste and cut. 
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// BEFORE
// BEFORE objID = 1008
{
    FieldType *fieldPtr;
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL)
        FldUndo(fieldPtr);

    return 0;
}

/********************************************************************
 *        T H I S _ F i e l d G e t I n s P t P o s i t i o n
 ********************************************************************/
Err THIS_FieldGetInsPtPosition(UInt16 refNum, Int32 objID, Int32 *pos)
// DESC Returns the insertion point position within the string. 
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// BEFORE
// BEFORE objID = 1008
// NOTES The insertion point is to the left of the byte offset that
// NOTES this function returns. That is, if this function returns 0,
// NOTES the insertion point is to the left of the first character 
// NOTES in the string. In multiline fields, line feeds are counted
// NOTES as a single character in the string, and the byte offset 
// NOTES after the line feed character is the beginning of the next
// NOTES line. 
// NOTES See also: FieldSetInsertionPoint() and FieldSetInsPtPosition()
{
    FieldType *fieldPtr;
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL)
        *pos = (Int32) FldGetInsPtPosition(fieldPtr);
    else
        *pos = -1;

    return 0;
}

/********************************************************************
 *           T H I S _ F i e l d G e t S e l e c t i o n
 ********************************************************************/
Err THIS_FieldGetSelection(UInt16 refNum, Int32 objID, Int32 *startPos)
// DESC Retrieves the start and end position of a field's selected
// DESC text.  It only returns the start position.  To get the end
// DESC position, use the GlobalEndPos() funtion.
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// BEFORE Dim endPos as Integer
// BEFORE
// BEFORE objID = 1008
// AFTER endPos = NSL.GlobalEndPos()
{
    FieldType *fieldPtr;
    THIS_ATTACH_GLOBALS
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL) {
        FldGetSelection(fieldPtr, &gP->startPos, &gP->endPos);
        *startPos = (Int32) gP->startPos;
    }
    else
        *startPos = (Int32) -1;

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *             T H I S _ F i e l d A n y D i r t y
 ********************************************************************/
Err THIS_FieldAnyDirty(UInt16 refNum, Int32 *dirty)
// DESC Returns 1 if one or more of the active form's field values
// DESC have changed since the last time that they were set.
{
    FormPtr formPtr;
    FieldType *fieldPtr;
    UInt16 n;
    UInt16 index;
    FormObjectKind type;
    
    *dirty = 0;
    formPtr = FrmGetActiveForm();
    if (formPtr != NULL) {
        n = FrmGetNumberOfObjects(formPtr);
        for (index = 0; index < n; index++) {
            type = FrmGetObjectType(formPtr, index);
            if (type == frmFieldObj) {
                fieldPtr = FrmGetObjectPtr(formPtr, index);
                if (FldDirty(fieldPtr)) {
                    *dirty = 1;
                    break;
                }
            }
        }
    }

    return 0;
}

/********************************************************************
 *                 T H I S _ F i e l d D i r t y
 ********************************************************************/
Err THIS_FieldDirty(UInt16 refNum, Int32 objID, Int32 *dirty)
// DESC Returns 1 if the field's value has changed since the last
// DESC time that it was set.
// PARAM1 0 = check field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// BEFORE
// BEFORE objID = 1008 
{
    FieldType *fieldPtr;
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL)
        *dirty = (Int32) FldDirty(fieldPtr);
    else
        *dirty = 0;

    return 0;
}

/********************************************************************
 *              T H I S _ F i e l d S e t D i r t y
 ********************************************************************/
Err THIS_FieldSetDirty(UInt16 refNum, Int32 objID, Int32 dirty)
// DESC Sets a field's "dirty" property.  A field is considered as
// DESC dirty if its value has changed since the last time it was
// DESC set.
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// PARAM2 0 = not dirty
// PARAM2 1 = dirty
// BEFORE
// BEFORE objID = 1008
// BEFORE dirty = 1
{
    FieldType *fieldPtr;
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL)
        FldSetDirty(fieldPtr, (Boolean) dirty);

    return 0;
}

/********************************************************************
 *           T H I S _ F i e l d S e t A l l D i r t y
 ********************************************************************/
Err THIS_FieldSetAllDirty(UInt16 refNum, Int32 dirty)
// DESC Sets the "dirty" property of all of the active form's field
// DESC values.
// PARAM1 0 = not dirty
// PARAM1 1 = dirty
{
    FormPtr formPtr;
    FieldType *fieldPtr;
    UInt16 n;
    UInt16 index;
    FormObjectKind type;
    
    formPtr = FrmGetActiveForm();
    if (formPtr != NULL) {
        n = FrmGetNumberOfObjects(formPtr);
        for (index = 0; index < n; index++) {
            type = FrmGetObjectType(formPtr, index);
            if (type == frmFieldObj) {
                fieldPtr = FrmGetObjectPtr(formPtr, index);
                FldSetDirty(fieldPtr, (Boolean) dirty);
            }
        }
    }

    return 0;
}

/********************************************************************
 *           T H I S _ F i e l d S e t S e l e c t i o n
 ********************************************************************/
Err THIS_FieldSetSelection(UInt16 refNum, Int32 objID, Int32 startPos, Int32 endPos)
// DESC Set the current selection in a field and highlight the 
// DESC selection if the field is visible. 
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// BEFORE
// BEFORE objID = 1008
{
    FieldType *fieldPtr;
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL)
        FldSetSelection(fieldPtr, (UInt16) startPos, (UInt16) endPos);

    return 0;
}

/********************************************************************
 *        T H I S _ F i e l d S e t I n s e r t i o n P o i n t
 ********************************************************************/
Err THIS_FieldSetInsertionPoint(UInt16 refNum, Int32 objID, Int32 pos)
// DESC Set the location of the insertion point based on a 
// DESC specified string position. 
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// BEFORE
// BEFORE objID = 1008
// NOTES This routine differs from FieldldSetInsPtPosition in
// NOTES that it doesn't make the character position visible. 
// NOTES FieldSetInsertionPoint also doesn't make the field the 
// NOTES current focus of input if it was not already. 
// NOTES See Also:  FieldSetInsPtPosition() and FieldGetInsPtPosition()

{
    FieldType *fieldPtr;
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL)
        FldSetInsertionPoint(fieldPtr, (UInt16) pos);

    return 0;
}

/********************************************************************
 *        T H I S _ F i e l d S e t I n s P t P o s i t i o n
 ********************************************************************/
Err THIS_FieldSetInsPtPosition(UInt16 refNum, Int32 objID, Int32 pos)
// DESC Set the location of the insertion point based on a 
// DESC specified string position. 
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// BEFORE
// BEFORE objID = 1008
// NOTES If the position is beyond the visible text, the field is
// NOTES scrolled until the position is visible. 
// NOTES See also:  FieldSetInsertionPoint() and FieldGetInsPtPosition()

{
    FieldType *fieldPtr;
    FormPtr   formPtr;
    UInt16    fieldIndex;
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL) {
        fieldIndex = ObjectIndex(objID, &formPtr);
        FrmSetFocus(formPtr, fieldIndex);
        FldSetInsPtPosition(fieldPtr, (UInt16) pos);
    }
    
    return 0;
}

/********************************************************************
 *               F i e l d G e t A t t r i b u t e s
 ********************************************************************/
Err THIS_FieldGetAttributes(UInt16 refNum, Int32 objID, Int32 *attributes)
// DESC Returns a field's attributes as a bitmapped integer.  The
// DESC BitsNbytes shared library contains functions for manipulating
// DESC bit values.
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// RETURNS A bitmapped integer with the following values:
// RETURNS    bit 0 - reserved
// RETURNS    bit 1 - numeric
// RETURNS    bit 2 - hasScrollBar
// RETURNS    bit 3 - autoShift
// RETURNS    bits 4 and 5 - justification
// RETURNS        00 - leftAlign
// RETURNS        01 - centerAlign (may not be supported)
// RETURNS        10 - rightAlign
// RETURNS    bits 6 and 7 - underlined
// RETURNS        00 - noUnderline
// RETURNS        01 - grayUnderline
// RETURNS        10 - solidUnderline
// RETURNS    bit 8 - dirty
// RETURNS    bit 9 - insPtVisible
// RETURNS    bit 10 - dynamicSize
// RETURNS    bit 11 - hasFocus
// RETURNS    bit 12 - singleLine
// RETURNS    bit 13 - editable
// RETURNS    bit 14 - visible
// RETURNS    bit 15 - usable
// BEFORE
// BEFORE objID = 1008
{
    FieldType *fieldPtr;
    union {
        UInt16 uValue;
        FieldAttrType attrs;
    } valUnion;
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL) {
        FldGetAttributes(fieldPtr, &valUnion.attrs);
        *attributes = (Int32) valUnion.uValue;
    }
    else
        *attributes = (Int32) 0;

    return 0;
}

/********************************************************************
 *               F i e l d S e t A t t r i b u t e s
 ********************************************************************/
Err THIS_FieldSetAttributes(UInt16 refNum, Int32 objID, Int32 attributes)
// DESC Sets a field's attributes.  Attributes are specified as a 
// DESC bitmapped integer.  The BitsNbytes shared library contains 
// DESC functions for manipulating bit values.
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// PARAM2 A bitmapped integer with the following values:
// PARAM2    bit 0 - reserved
// PARAM2    bit 1 - numeric
// PARAM2    bit 2 - hasScrollBar
// PARAM2    bit 3 - autoShift
// PARAM2    bits 4 and 5 - justification
// PARAM2        00 - leftAlign
// PARAM2        01 - centerAlign (may not be supported)
// PARAM2        10 - rightAlign
// PARAM2    bits 6 and 7 - underlined
// PARAM2        00 - noUnderline
// PARAM2        01 - grayUnderline
// PARAM2        10 - solidUnderline
// PARAM2    bit 8 - dirty
// PARAM2    bit 9 - insPtVisible
// PARAM2    bit 10 - dynamicSize
// PARAM2    bit 11 - hasFocus
// PARAM2    bit 12 - singleLine
// PARAM2    bit 13 - editable
// PARAM2    bit 14 - visible
// PARAM2    bit 15 - usable
// BEFORE
// BEFORE objID = 1008
{
    FieldType *fieldPtr;
    union {
        UInt16 uValue;
        FieldAttrType attrs;
    } valUnion;
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL) {
        valUnion.uValue = (UInt16) attributes;
        FldSetAttributes(fieldPtr, &valUnion.attrs);
    }

    return 0;
}

/********************************************************************
 *                       F i e l d G e t F o n t
 ********************************************************************/
Err THIS_FieldGetFont(UInt16 refNum, Int32 objID, Int32 *fontId)
// DESC Returns a field's Font ID.
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// BEFORE
// BEFORE objID = 1008 
{
    FieldType *fieldPtr;
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL)
        *fontId = (Int32) FldGetFont(fieldPtr);
    else
        *fontId = (Int32) -1;

    return 0;
}

/********************************************************************
 *                       F i e l d S e t F o n t
 ********************************************************************/
Err THIS_FieldSetFont(UInt16 refNum, Int32 objID, Int32 fontId)
// DESC Sets a field's Font ID.
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// BEFORE
// BEFORE objID = 1008 
// BEFORE fontId = 2  'large font
{
    FieldType *fieldPtr;
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL)
        FldSetFont(fieldPtr, (FontID) fontId);

    return 0;
}

/********************************************************************
 *             F i e l d G e t S c r o l l P o s i t i o n
 ********************************************************************/
Err THIS_FieldGetScrollPosition(UInt16 refNum, Int32 objID, Int32 *position)
// DESC Returns a field's scroll position.  This is the offset of 
// DESC the first character in the first visible line of a field. 
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// BEFORE
// BEFORE objID = 1008 
{
    FieldType *fieldPtr;
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL)
        *position = (Int32) FldGetScrollPosition(fieldPtr);
    else
        *position = (Int32) -1;

    return 0;
}

/********************************************************************
 *             F i e l d S e t S c r o l l P o s i t i o n
 ********************************************************************/
Err THIS_FieldSetScrollPosition(UInt16 refNum, Int32 objID, Int32 position)
// DESC Sets a field's scroll position.  This is the offset of 
// DESC the first character in the first visible line of a field. 
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// BEFORE
// BEFORE objID = 1008 
// BEFORE position = 20
{
    FieldType *fieldPtr;
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL)
        FldSetScrollPosition(fieldPtr, (UInt16) position);

    return 0;
}

/********************************************************************
 *             F i e l d G e t S c r o l l V a l u e s
 ********************************************************************/
Err THIS_FieldGetScrollValues(UInt16 refNum, Int32 objID, Int32 *totalLines)
// DESC Returns a field's scroll values.  These are the values 
// DESC necessary to update a scroll bar.  This function retreives the
// DESC scroll position (offset line number), the text height (total lines required to display
// DESC the field's text), and the field's height.  Only the text height
// DESC (total lines) is returned.  Use GlobalStartPos() to return the
// DESC scroll position and GlobalHeight() to return the field's height.
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// BEFORE Dim position as Integer
// BEFORE Dim height as Integer
// BEFORE
// BEFORE objID = 1008 
// AFTER position = GlobalStartPos()
// AFTER height = GlobalHeight()
{
    FieldType *fieldPtr;
    UInt16 totLines;
    UInt16 height;
    THIS_ATTACH_GLOBALS
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL) {
        FldGetScrollValues(fieldPtr, &gP->startPos, &totLines, &height);
        *totalLines = (Int32) totLines;
        gP->height = (Coord) height;
    }
    else
        *totalLines = (Int32) -1;

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *             F i e l d G e t V i s i b l e L i n e s
 ********************************************************************/
Err THIS_FieldGetVisibleLines(UInt16 refNum, Int32 objID, Int32 *lines)
// DESC Return the number of lines that can be displayed within 
// DESC the visible bounds of the field. 
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// BEFORE
// BEFORE objID = 1008 
{
    FieldType *fieldPtr;
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL)
        *lines = (Int32) FldGetVisibleLines(fieldPtr);
    else
        *lines = (Int32) -1;

    return 0;
}

/********************************************************************
 *        F i e l d G e t N u m b e r O f B l a n k L i n e s
 ********************************************************************/
Err THIS_FieldGetNumberOfBlankLines(UInt16 refNum, Int32 objID, Int32 *lines)
// DESC Return the number of blank lines that are displayed at the 
// DESC bottom of a field. 
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// BEFORE
// BEFORE objID = 1008 
{
    FieldType *fieldPtr;
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL)
        *lines = (Int32) FldGetNumberOfBlankLines(fieldPtr);
    else
        *lines = (Int32) -1;

    return 0;
}

/********************************************************************
 *                  F i e l d S c r o l l a b l e
 ********************************************************************/
Err THIS_FieldScrollable(UInt16 refNum, Int32 objID, Int32 direction, Int32 *yesNo)
// DESC Returns 1 if the field is scrollable in the specified 
// DESC direction.  Otherwise, it returns 0
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// PARAM2 0 = up
// PARAM2 1 = down
// BEFORE
// BEFORE objID = 1008 
{
    FieldType *fieldPtr;
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL)
        *yesNo = (Int32) FldScrollable(fieldPtr, (WinDirectionType) direction);
    else
        *yesNo = (Int32) -1;

    return 0;
}

/********************************************************************
 *                  F i e l d S c r o l l F i e l d
 ********************************************************************/
Err THIS_FieldScrollField(UInt16 refNum, Int32 objID, Int32 nbrLines, Int32 direction)
// DESC Scroll a field up or down by the number of lines specified. 
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// PARAM3 0 = up
// PARAM3 1 = down
// BEFORE
// BEFORE objID = 1008 
{
    FieldType *fieldPtr;
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL) {
        FldScrollField(fieldPtr, (UInt16) nbrLines, (WinDirectionType) direction);
        FldSendChangeNotification(fieldPtr);
    }

    return 0;
}

/********************************************************************
 *                  F i e l d S e t B o u n d s
 ********************************************************************/
Err THIS_FieldSetBounds(UInt16 refNum, Int32 objID, 
                        Int32 topLeftX, Int32 topLeftY, 
                        Int32 width, Int32 height)
// DESC Change the position or size of a field.  
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// BEFORE
// BEFORE objID = 1008 
// NOTES May raise a fatal error message if the memory block that contains the word-wrapping information needs to be resized and there is not enough space to do so. 
{
    FieldType *fieldPtr;
    RectangleType rect;
    UInt16 objIndex;
    FormPtr formPtr;
    
    objIndex = ObjectIndex(objID, &formPtr);
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL) {
        rect.topLeft.x = topLeftX;
        rect.topLeft.y = topLeftY;
        rect.extent.x = width;
        rect.extent.y = height;
        FrmHideObject(formPtr, objIndex);
        FldSetBounds(fieldPtr, &rect);
        FrmShowObject(formPtr, objIndex);
    }
    return 0;
}

/********************************************************************
 *        T H I S _ F o r m G e t N u m b e r O f O b j e c t s
 ********************************************************************/
Err THIS_FormGetNumberOfObjects(UInt16 refNum, Int32 *nbr)
// DESC Retrieves the number of objects on the active form.
// RETURNS -1 if no form is active
{
    FormPtr formPtr;

    formPtr = FrmGetActiveForm();
    if (formPtr != NULL)
        *nbr = (Int32) FrmGetNumberOfObjects(formPtr);
    else
        *nbr = -1;    

    return 0;
}

/********************************************************************
 *          T H I S _ F o r m G e t O b j e c t B o u n d s
 ********************************************************************/
Err THIS_FormGetObjectBounds(UInt16 refNum, Int32 objID, Int32 *x)
// DESC Retrieves the x, y, width, and height values of a form
// DESC object.
// PARAM1 0 = use object that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// RETURNS -1 if the object is invalid or no object has focus
// BEFORE Dim y as Integer
// BEFORE Dim width as Integer
// BEFORE Dim height as Integer
// BEFORE
// BEFORE objID = 1008 
// AFTER y = NSL.GlobalY()
// AFTER width = NSL.GlobalWidth()
// AFTER height = NSL.GlobalHeight()
// NOTES This function only returns the x position.  Use
// NOTES the GlobalY(), GlobalWidth(), and GlobalHeight() functions
// NOTES to retrieve the other values.
{
    UInt16 objectIndex;
    RectangleType rect;
    FormPtr formPtr;
    THIS_ATTACH_GLOBALS
    
    objectIndex = ObjectIndex(objID, &formPtr);
    if (objectIndex != noFocus) {
        FrmGetObjectBounds(formPtr, objectIndex, &rect);
        gP->screenX = rect.topLeft.x;
        gP->screenY = rect.topLeft.y;
        gP->width = rect.extent.x;
        gP->height = rect.extent.y;
        *x = gP->screenX;
    }
    else
        *x = -1;

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *          T H I S _ F o r m G e t O b j e c t P o s i t i o n
 ********************************************************************/
Err THIS_FormGetObjectPosition(UInt16 refNum, Int32 objID, Int32 *x)
// DESC Retrieves the starting X and Y position values of a form
// DESC object.
// PARAM1 0 = use object that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// RETURNS -1 if the object is invalid or no object has focus
// BEFORE Dim y as Integer
// BEFORE
// BEFORE objID = 1008 
// AFTER y = NSL.GlobalY
// NOTES This function only returns the X position.  Use the
// NOTES GlobalY(), function to retrieve the Y position.
{
    UInt16 objectIndex;
    FormPtr formPtr;
    THIS_ATTACH_GLOBALS
    
    objectIndex = ObjectIndex(objID, &formPtr);
    if (objectIndex != noFocus) {
        FrmGetObjectPosition(formPtr, objectIndex, &gP->screenX, &gP->screenY);
        *x = gP->screenX;
    }
    else
        *x = -1;

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *          T H I S _ F o r m G e t O b j e c t T y p e
 ********************************************************************/
Err THIS_FormGetObjectType(UInt16 refNum, Int32 objID, Int32 *type)
// DESC Retrieves the object type of the specified object.
// PARAM1 0 = use object that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// RETURNS -1 if the object is invalid or no object has focus
// RETURNS  0 = frmFieldObj
// RETURNS  1 = frmControlObj
// RETURNS  2 = frmListObj
// RETURNS  3 = frmTableObj
// RETURNS  4 = frmBitmapObj
// RETURNS  5 = frmLineObj
// RETURNS  6 = frmFrameObj
// RETURNS  7 = frmRectangleObj
// RETURNS  8 = frmLabelObj
// RETURNS  9 = frmTitleObj
// RETURNS 10 = frmPopupObj
// RETURNS 11 = frmGraffitiStateObj
// RETURNS 12 = frmGadgetObj
// RETURNS 13 = frmScrollbarObj
// BEFORE objID = 1008 
// NOTES This function does not provide information regarding all the 
// NOTES different Control object types.  To retrieve a complete list of
// NOTES object types use the FormGetAllObjectTypes() function.
{
    UInt16 objectIndex;
    FormPtr formPtr;
    
    objectIndex = ObjectIndex(objID, &formPtr);
    if (objectIndex != noFocus) 
        *type = (Int32) FrmGetObjectType(formPtr, objectIndex);
    else
        *type = -1;

    return 0;
}


/********************************************************************
 *          T H I S _ F o r m S e t O b j e c t P o s i t i o n
 ********************************************************************/
Err THIS_FormSetObjectPosition(UInt16 refNum, Int32 objID, Int32 x, Int32 y)
// DESC Changes an object's current position.
// PARAM1 0 = use object that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// RETURNS -1 if the object is invalid or no object has focus
// BEFORE
// BEFORE objID = 1008 
// BEFORE x = 120
// BEFORE y = 40
{
    UInt16 objectIndex;
    FormPtr formPtr;
    
    objectIndex = ObjectIndex(objID, &formPtr);
    if (objectIndex != noFocus) {
        FrmHideObject(formPtr, objectIndex);
        FrmSetObjectPosition(formPtr, objectIndex, (Coord) x, (Coord) y);
        FrmShowObject(formPtr, objectIndex);
    }

    return 0;
}

/********************************************************************
 *              F o r m S e t O b j e c t B o u n d s
 ********************************************************************/
Err THIS_FormSetObjectBounds(UInt16 refNum, Int32 objID, 
                             Int32 topLeftX, Int32 topLeftY, 
                             Int32 width, Int32 height)
// DESC Set the bounds or position of an object.   
// PARAM1 0 = use object that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// BEFORE
// BEFORE objID = 1008 
{
    RectangleType rect;
    UInt16 objIndex;
    FormPtr formPtr;
    
    objIndex = ObjectIndex(objID, &formPtr);
    if (objIndex != noFocus) {
        rect.topLeft.x = topLeftX;
        rect.topLeft.y = topLeftY;
        rect.extent.x = width;
        rect.extent.y = height;
        FrmHideObject(formPtr, objIndex);
        FrmSetObjectBounds(formPtr, objIndex, &rect);
        FrmShowObject(formPtr, objIndex);
    }
    return 0;
}

/********************************************************************
 *                      F o r m G e t T i t l e
 ********************************************************************/
Err THIS_FormGetTitle(UInt16 refNum, char *title)
// DESC Returns the form's current title.
{
    FormPtr formPtr;
    
    formPtr = FrmGetActiveForm();
    if (formPtr != NULL)
        StrCopy(title, FrmGetTitle(formPtr));
    else
        StrCopy(title, "");
    
    return 0;
}

/********************************************************************
 *              F o r m R e p l a c e T i t l e
 ********************************************************************/
Err THIS_FormReplaceTitle(UInt16 refNum, char* title, Int32 forceLength)
// DESC Replace the current form's title.  The length of the title
// DESC string can not exceed the original title string length.  If
// DESC the forceLength parameter is 0, then the replacement string
// DESC will automatically be truncated to the current title length.
// DESC If you will vary the length of your title string, you should
// DESC use the FormGetTitle() function to retrieve the original title
// DESC string before you ever change it.  Then obtain its length using
// DESC the NSBasic Len() function.  Use this value as the forceLength
// DESC parameter for all subsequent title replacements.
{
    FormPtr formPtr;
    Int16 len;
    char  newTitle[128];
    
    formPtr = FrmGetActiveForm();
    if (formPtr != NULL) {
        if (forceLength == 0) {
            StrNCopy(newTitle, FrmGetTitle(formPtr), 127);
            newTitle[127] = '\0';
            len = StrLen(newTitle);
        }
        else
            len = (Int16) forceLength;
        StrNCopy(newTitle, title, len);
        newTitle[len] = '\0';
        FrmCopyTitle(formPtr, newTitle);
    }
    
    return 0;
}

/********************************************************************
 *                    L i s t G e t T o p I t e m
 ********************************************************************/
Err THIS_ListGetTopItem(UInt16 refNum, Int32 objID, Int32 *topItem)
// DESC Returns the top item number of the specified list box.
{
    ListType *listPtr;
    
    listPtr = ListPointer(objID);
    if (listPtr != NULL)
        *topItem = (Int32) LstGlueGetTopItem(listPtr);
    else
        *topItem = (Int32) -1;

    return 0;
}

/********************************************************************
 *                    L i s t S e t T o p I t e m
 ********************************************************************/
Err THIS_ListSetTopItem(UInt16 refNum, Int32 objID, Int32 topItem)
// DESC Sets the top item number of the specified list box.  The 
// DESC item cannot become the top item if it's on the last page. 

{
    ListType *listPtr;
    
    listPtr = ListPointer(objID);
    if (listPtr != NULL) {
        LstSetTopItem(listPtr, (Int16) topItem);
        LstDrawList(listPtr);
    }

    return 0;
}

/********************************************************************
 *              L i s t G e t V i s i b l e I t e m s
 ********************************************************************/
Err THIS_ListGetVisibleItems(UInt16 refNum, Int32 objID, Int32 *visibleItems)
// DESC Returns the number of visible items in the specified list box.
{
    ListType *listPtr;
    
    listPtr = ListPointer(objID);
    if (listPtr != NULL)
        *visibleItems = (Int32) LstGetVisibleItems(listPtr);
    else
        *visibleItems = (Int32) -1;

    return 0;
}

/********************************************************************
 *                 L i s t S c r o l l L i s t
 ********************************************************************/
Err THIS_ListScrollList(UInt16 refNum, Int32 objID, Int32 direction, 
                     Int32 nbrItems, Int32 *result)
// DESC Scroll the specified list box by the number of items and
// DESC in the direction indicated.
// PARAM2 0 = up
// PARAM2 1 = down
// RETURNS 0 = if the list box could not be scrolled
// RETURNS 1 = if the list box was scrolled successfully
{
    ListType *listPtr;
    
    listPtr = ListPointer(objID);
    if (listPtr != NULL)
        *result = (Int32) LstScrollList(listPtr, (WinDirectionType) direction, (Int16) nbrItems);
    else
        *result = (Int32) -1;

    return 0;
}

// SECTION Font Support
// DESC The Font Support functions provide support for determining
// DESC and changing the default font.  They also provide support
// DESC for working with the PalmOS variable width fonts.

/********************************************************************
 *                       F o n t G e t F o n t
 ********************************************************************/
Err THIS_FontGetFont(UInt16 refNum, Int32 *fontId)
// DESC Return the Font ID of the current font. 
{
    
    *fontId = (Int32) FntGetFont();

    return 0;
}

/********************************************************************
 *                       F o n t S e t F o n t
 ********************************************************************/
Err THIS_FontSetFont(UInt16 refNum, Int32 fontId, Int32 *oldFontId)
// DESC Set the current font. 
{

    *oldFontId = (Int32) FntSetFont((FontID) fontId);

    return 0;
}

/********************************************************************
 *                       F o n t S e l e c t
 ********************************************************************/
Err THIS_FontSelect(UInt16 refNum, Int32 *fontId)
// DESC Displays a dialog box in which the user can choose one of 
// DESC three system-supplied fonts, and returns a FontID value 
// DESC representing the user's choice. 
{

    UInt32 fntID;
    
    FtrGet(sysFtrCreator, sysFtrDefaultFont, &fntID);
    *fontId = (Int32) FontSelect((FontID) fntID);

    return 0;
}

/********************************************************************
 *                       F o n t C h a r W i d t h
 ********************************************************************/
Err THIS_FontCharWidth(UInt16 refNum, char *charString, Int32 *width)
// DESC Return the width of the specified character. If the specified
// DESC character does not exist within the current font, the Missing 
// DESC Character Symbol is substituted.
// DESC
// DESC Note:  Even though the parameter to this function is a string,
// DESC        only the first character of the string is evaluated.
{

    *width = (Int32) FntCharWidth(*charString);

    return 0;
}

/********************************************************************
 *                   F o n t C h a r s W i d t h
 ********************************************************************/
Err THIS_FontCharsWidth(UInt16 refNum, char *charString, Int32 optionalLen, Int32 *width)
// DESC Return the width of the specified character string. The Missing 
// DESC Character Symbol is substituted for any character which 
// DESC does not exist in the current font. 
// PARAM2 0 = use actual string length
{

    if (optionalLen <= 0)
        optionalLen = StrLen(charString);
    *width = (Int32) FntCharsWidth(charString, (Int16) optionalLen);

    return 0;
}

/********************************************************************
 *                   F o n t W i d t h T o O f f s e t
 ********************************************************************/
Err THIS_FontWidthToOffset(UInt16 refNum, char *charString, Int32 optionalLen, 
                           Int32 width, Int32 *offset)
// DESC Given a pixel position, return the offset of the character 
// DESC displayed at that location.  If the pixel position was on the
// DESC left side of the character, GlobalStartPos() will return 1,
// DESC otherwise, it will return 0.  GlobalWidth() will return the
// DESC pixel width of the text up to the returned offset.
// PARAM2 0 = use actual string length
{

    Boolean leadingEdge;
    Int16 truncWidth;
    THIS_ATTACH_GLOBALS
    
    if (optionalLen <= 0)
        optionalLen = StrLen(charString);
    *offset = (Int32) FntWidthToOffset(charString, (UInt16) optionalLen, (Int16) width,
                            &leadingEdge, &truncWidth);
    gP->startPos = (UInt16) leadingEdge;
    gP->width = (Coord) truncWidth;
    
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *                   F o n t C h a r s I n W i d t h
 ********************************************************************/
Err THIS_FontCharsInWidth(UInt16 refNum, char *charString, Int32 optionalLen, 
                          Int32 width, Int32 *length)
// DESC Find the length in bytes of the characters from a specified 
// DESC string that fit within a passed width.  GlobalWidth() will
// DESC return the actual pixel width of the characters that fit
// DESC within the passed width.  
// PARAM2 0 = use actual string length
// NOTES Spaces at the end of a string are ignored and removed. 
// NOTES Characters after a carriage return are ignored, the 
// NOTES string is considered truncated. 
{

    Boolean truncated;
    Int16 strLen;
    Int16 maxWidth;
    THIS_ATTACH_GLOBALS
    
    strLen = (Int16) optionalLen;
    if (strLen <= 0)
        strLen = StrLen(charString);
    maxWidth = (Int16) width;
    FntCharsInWidth(charString, &maxWidth, &strLen, &truncated);
    *length = (Int32) strLen;
    gP->width = (Coord) maxWidth;
    
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *                   F o n t W o r d W r a p
 ********************************************************************/
Err THIS_FontWordWrap(UInt16 refNum, char *charString, Int32 width, Int32 *length)
// DESC Given a string, determine how many bytes of text can be 
// DESC displayed within the specified width. 
// PARAM2 0 = use actual string length
{

    *length = (Int32) FntWordWrap(charString, (UInt16) width);

    return 0;
}

// SECTION HotSync Data
// DESC The HotSync data functions provide information from the
// DESC HotSync application.

/********************************************************************
 *                T H I S _ S y n c U s e r N a m e
 ********************************************************************/
Err THIS_SyncUserName(UInt16 refNum, char *userName)
// DESC Returns the HotSync user name.
{
    char uName[dlkUserNameBufSize];
    
    uName[0] = 0;
    DlkGetSyncInfo(NULL, NULL, NULL, uName, NULL, NULL);
    StrCopy(userName, uName);
    
    return 0;
}

/********************************************************************
 *          T H I S _ S u c c e s s f u l S y n c
 ********************************************************************/
Err THIS_SuccessfulSync(UInt16 refNum, Int32 *syncDate)
// DESC Returns the date, in system format, of the last successful
// DESC HotSync operation.  System format dates are expressed as
// DESC the number of seconds since January 1st, 1904.  Use the
// DESC StringDateTime(), StringDate(), or StringTime() functions
// DESC to retrieve a string representation of a system format date.
{
    UInt32 sDate;

    DlkGetSyncInfo(&sDate, NULL, NULL, NULL, NULL, NULL);
    *syncDate = (Int32) sDate;
    
    return 0;
}

/********************************************************************
 *                     T H I S _ L a s t S y n c
 ********************************************************************/
Err THIS_LastSync(UInt16 refNum, Int32 *syncDate)
// DESC Returns the date, in system format, of the last successful
// DESC or unsuccessful HotSync operation.  System format dates are
// DESC expressed as the number of seconds since January 1st, 1904.  
// DESC Use the StringDateTime(), StringDate(), or StringTime() 
// DESC functions to retrieve a string representation of a system 
// DESC format date.
{
    UInt32 sDate;

    DlkGetSyncInfo(NULL, &sDate, NULL, NULL, NULL, NULL);
    *syncDate = (Int32) sDate;
    
    return 0;
}

// SECTION Localization Functions
// DESC The localization functions are used to convert date and
// DESC number strings from Standard/US format to the user's 
// DESC preferred format as specified in the system preferences.
// DESC For instance, in some European countries, the "thousands"
// DESC separator in a number is a "." and the "decimal" separator
// DESC is a ",".  Dates are usually preferred in dd/mm/yy format.
// DESC These functions look up the user's set preference for these
// DESC formats and provide any conversion necessary.

/********************************************************************
 *                T H I S _ L o c a l i z e N u m b e r
 ********************************************************************/
Err THIS_LocalizeNumber(UInt16 refNum, char *stdNbrStr, char *localNbrStr)
// DESC Convert a number string in standard/US format to a 
// DESC localized format as determined by system preferences.
// PARAM2 Number string in standard/US format - example  4,123.56
// BEFORE
// BEFORE stdNbrStr = "4,123.56"
{
    UInt32 nbrFormat;
    char   thousandsSep[8];
    char   decimalSep[8];
    
    nbrFormat = PrefGetPreference(prefNumberFormat);

    LocGetNumberSeparators((NumberFormatType) nbrFormat, thousandsSep, decimalSep);
    StrCopy(localNbrStr, StrLocalizeNumber(stdNbrStr, *thousandsSep, *decimalSep));

    return 0;
}

/********************************************************************
 *              T H I S _ D e l o c a l i z e N u m b e r
 ********************************************************************/
Err THIS_DelocalizeNumber(UInt16 refNum, char *localNbrStr, char *stdNbrStr)
// DESC Convert a number string in a localized format to a
// DESC standard/US format as determined by system preferences.
// PARAM2 Number string in localized format - example  4.123,56
// BEFORE
// BEFORE locNbrStr = "4.123,56"
{ 

    UInt32 nbrFormat;
    char   thousandsSep[8];
    char   decimalSep[8];
    
    nbrFormat = PrefGetPreference(prefNumberFormat);

    LocGetNumberSeparators((NumberFormatType) nbrFormat, thousandsSep, decimalSep);
    StrCopy(stdNbrStr, StrDelocalizeNumber(localNbrStr, *thousandsSep, *decimalSep));

    return 0;
}

/********************************************************************
 *              T H I S _ L o c a l i z e D a t e
 ********************************************************************/
Err THIS_LocalizeDate(UInt16 refNum, char *stdDateStr, Int32 ToDateFormat,
                          Int32 longDateFormat, char *localDateStr)
// DESC Convert a date string in standard/US format to a localized
// DESC date format as determined by system preferences.
// PARAM1 The date string may also contain the time.  Time values
// PARAM1 will be ignored.
// PARAM2 0 = stdDateStr format is "MM/DD/YY[YY]"
// PARAM2 1 = stdDateStr format is "[YY]YY/MM/DD"
// PARAM3 0 = use short date format preference
// PARAM3 1 = user long date format preference
// BEFORE
// BEFORE stdDateStr = DateMMDDYY(Today())
// BEFORE ToDateFormat = 0
// BEFORE longDateFormat = 0
{
    UInt32   dateFormat;
    UInt32   sysTime;
    DateType dateT;
    char     dateStr[longDateStrLength + 1];
    
    THIS_SystemTime(refNum, stdDateStr, "", 0, ToDateFormat, &sysTime);
    DateSecondsToDate(sysTime, &dateT);

    if (longDateFormat)
        dateFormat = PrefGetPreference(prefLongDateFormat);
    else
        dateFormat = PrefGetPreference(prefDateFormat);

    DateToAscii((UInt8) dateT.month, (UInt8) dateT.day, (UInt16) (dateT.year + 1904), 
                (DateFormatType) dateFormat, dateStr);
    StrCopy(localDateStr, dateStr);
    
    return 0; 
}

// SECTION Preference Functions
// DESC Preferences are divided into two categories - System
// DESC Preferences and Application Preferences.  System Preferences
// DESC include such things as auto-off time, date formats, etc.
// DESC Application Preferences are used for storing information
// DESC about a particular application.  These preferences can be
// DESC used to store program state, registration codes, etc.  Using
// DESC application preferences can eliminate the need to create a
// DESC specific database for this purpose.  Application preferences
// DESC are not intended to contain very large amounts of data.

/********************************************************************
 *          T H I S _ G e t A p p P r e f e r e n c e s
 ********************************************************************/
Err THIS_GetAppPreferences(UInt16 refNum, char *pgmName, 
                           Int32 prefId, Int32 saved, char *data)
// DESC Get an application preference string.
// PARAM1 Program Name - This is case sensitive
// PARAM2 Preference ID
// PARAM3 0 = preference does not get restored after a hard reset
// PARAM3 1 = preference does get restored after a hard reset
// NOTES Currently preference strings are limited to 250 bytes or
// NOTES less.
// BEFORE
// BEFORE pgmName = "SysLibTest"
// BEFORE prefId = 1
// BEFORE saved = 0
{
    UInt32  creatorId;
    UInt16  prefSize;
    Err     status;
    char    d[256];

	if ((status = FindProgram(pgmName, &creatorId, NULL, NULL, refNum)) != 0) {
	    StrCopy(data, "");
	    return 0;
	}
	
    prefSize = sizeof(d) - 1;
    PrefGetAppPreferences(creatorId, (UInt16) prefId, 
                          d, &prefSize, (Boolean) saved);
    if (prefSize < (sizeof(d) - 1)) {
        PrefGetAppPreferences(creatorId, (UInt16) prefId, 
                              d, &prefSize, (Boolean) saved);
        StrCopy(data, d);
    }
    else
        StrCopy(data, "");
    
	
	return 0;
}
	    
/********************************************************************
 *          T H I S _ S e t A p p P r e f e r e n c e s
 ********************************************************************/
Err THIS_SetAppPreferences(UInt16 refNum, char *pgmName, 
                           Int32 prefId, char *data, Int32 saved, Int32 *status)
// DESC Set an application preference string.
// PARAM1 Program Name - This is case sensitive
// PARAM2 Preference ID
// PARAM4 0 = preference does not get restored after a hard reset
// PARAM4 1 = preference does get restored after a hard reset
// RETURNS  0 = Success
// RETURNS -1 = Invalid program name
// NOTES Currently preference strings are limited to 250 bytes or
// NOTES less.
// BEFORE
// BEFORE pgmName = "SysLibTest"
// BEFORE prefId = 1
// BEFORE data = "anything I want!"
// BEFORE saved = 0
{
    UInt32  creatorId;
    UInt16  prefSize;
    Err     err;

	if ((err = FindProgram(pgmName, &creatorId, NULL, NULL, refNum)) != 0) {
	    *status = -1;
	    return 0;
	}
	
    prefSize = StrLen(data) + 1;
    PrefSetAppPreferences(creatorId, (UInt16) prefId, 0, 
                          data, prefSize, (Boolean) saved);
    *status = 0;
	return 0;
}

/********************************************************************
 *          T H I S _ G e t S y s P r e f e r e n c e
 ********************************************************************/
Err THIS_GetSysPreference(UInt16 refNum, Int32 prefID, Int32 *data)
// DESC Get the value of a system preference.
// PARAM1  From Preferences.h in the PalmOS SDK:
// PARAM1  0 = prefVersion
// PARAM1  1 = prefCountry
// PARAM1  2 = prefDateFormat
// PARAM1  3 = prefLongDateFormat
// PARAM1  4 = prefWeekStartDay
// PARAM1  5 = prefTimeFormat
// PARAM1  6 = prefNumberFormat
// PARAM1  7 = prefAutoOffDuration
// PARAM1          prefAutoOffDurationSecs is now preferred 
// PARAM1          (prefAutoOffDuration is in minutes)
// PARAM1  8 = prefSysSoundLevelV20
// PARAM1  9 = prefGameSoundLevelV20
// PARAM1 10 = prefAlarmSoundLevelV20
// PARAM1 11 = prefHidePrivateRecordsV33
// PARAM1 12 = prefDeviceLocked
// PARAM1 13 = prefLocalSyncRequiresPassword
// PARAM1 14 = prefRemoteSyncRequiresPassword
// PARAM1 15 = prefSysBatteryKind
// PARAM1 16 = prefAllowEasterEggs
// PARAM1 17 = prefMinutesWestOfGMT
// PARAM1          deprecated old unsigned minutes EAST of GMT
// PARAM1 18 = prefDaylightSavings
// PARAM1          deprecated old daylight saving time rule
// PARAM1 19 = prefRonamaticChar
// PARAM1 20 = prefHard1CharAppCreator
// PARAM1          App creator for hard key #1
// PARAM1 21 = prefHard2CharAppCreator
// PARAM1 22 = prefHard3CharAppCreator
// PARAM1 23 = prefHard4CharAppCreator
// PARAM1 24 = prefCalcCharAppCreator
// PARAM1 25 = prefHardCradleCharAppCreator
// PARAM1 26 = prefLauncherAppCreator
// PARAM1 27 = prefSysPrefFlags
// PARAM1 28 = prefHardCradle2CharAppCreator
// PARAM1 29 = prefAnimationLevel
// PARAM1 
// PARAM1 Additions for PalmOS 3.0:
// PARAM1 -------------------------
// PARAM1 30 = prefSysSoundVolume
// PARAM1 	actual amplitude - error beeps and other 
// PARAM1         non-alarm/game sounds
// PARAM1 31 = prefGameSoundVolume
// PARAM1 32 = prefAlarmSoundVolume
// PARAM1 33 = prefBeamReceive
// PARAM1          not used - use ExgLibControl with ir(Get/Set)
// PARAM1          ScanningMode instead
// PARAM1 34 = prefCalibrateDigitizerAtReset
// PARAM1          True makes the user calibrate at soft reset time
// PARAM1 35 = prefSystemKeyboardID
// PARAM1          ID of the preferred keyboard resource
// PARAM1 36 = prefDefSerialPlugIn
// PARAM1          creator ID of the default serial plug-in
// PARAM1 
// PARAM1 Additions for PalmOS 3.1:
// PARAM1 -------------------------
// PARAM1 37 = prefStayOnWhenPluggedIn
// PARAM1 38 = prefStayLitWhenPluggedIn
// PARAM1 
// PARAM1 Additions for PalmOS 3.2:
// PARAM1 -------------------------
// PARAM1 39 = prefAntennaCharAppCreator
// PARAM1          App creator for antenna key
// PARAM1 
// PARAM1 Additions for PalmOS 3.3:
// PARAM1 -------------------------
// PARAM1 40 = prefMeasurementSystem
// PARAM1          English, Metric, etc.
// PARAM1 	
// PARAM1 Additions for PalmOS 3.5:
// PARAM1 -------------------------
// PARAM1 41 = prefShowPrivateRecords
// PARAM1          returns privateRecordViewEnum
// PARAM1 42 = prefAutoOffDurationSecs
// PARAM1 	
// PARAM1 Additions for PalmOS 4.0:
// PARAM1 -------------------------
// PARAM1 43 = prefTimeZone
// PARAM1          GMT offset in minutes, + for east of GMT, - for west
// PARAM1 44 = prefDaylightSavingAdjustment
// PARAM1          current DST adjustment in minutes (typically 0 or 60)
// PARAM1 45 = prefAutoLockType
// PARAM1           Never, on poweroff, after preset delay or at preset time.
// PARAM1 46 = prefAutoLockTime
// PARAM1           Auto lock preset time or delay.
// PARAM1 47 = prefAutoLockTimeFlag
// PARAM1           For Minutes or Hours.
// PARAM1 48 = prefLanguage
// PARAM1           Language spoken in country selected via 
// PARAM1           Setup app/Formats panel
// PARAM1 49 = prefLocale
// PARAM1           Locale for country selected via Setup app/Formats panel 
// PARAM1 50 = prefTimeZoneCountry
// PARAM1           Country used to specify time zone.
// PARAM1 51 = prefAttentionFlags
// PARAM1           User prefs for getting user's attention
// PARAM1 52 = prefDefaultAppCreator
// PARAM1           Default application launched on reset.
// BEFORE 
// BEFORE prefID = 7   'prefAutoOffDuration - in seconds
{
    *data = (Int32) PrefGetPreference((SystemPreferencesChoice) prefID);
    
    return 0;
}
 
/********************************************************************
 *          T H I S _ S e t S y s P r e f e r e n c e
 ********************************************************************/
Err THIS_SetSysPreference(UInt16 refNum, Int32 prefID, Int32 data)
// DESC Set the value of a system preference.
// PARAM1 See GetSysPreference() for preference ID values
// BEFORE 
// BEFORE prefID = 7   'prefAutoOffDuration - in minutes
// BEFORE data = 3     '3 minutes
{
    PrefSetPreference((SystemPreferencesChoice) prefID, (UInt32) data);
    
    return 0;
}

// SECTION Progress Manager Functions
// DESC The Progress Manager functions provide methods for providing
// DESC and updating a dialog that is displayed during long operations.
// DESC They provide feedback to the user about the progress of the
// DESC operation.

/********************************************************************
 *          T H I S _ P r o g r e s s S t a r t D i a l o g
 ********************************************************************/
Err THIS_ProgressStartDialog(UInt16 refNum, char* title)
// DESC Start a Progress Dialog.  The Progress Dialog functions are
// DESC used to display a special type of alert that informs the user
// DESC of the progress being made during operations that take a long
// DESC time.
// PARAM1 must be 20 characters or less.
// NOTES:  See also:  ProgressStopDialog(), ProgressUpdateDialog()
//                    ProgressUserCancel(), ProgressPercent(),
//                    ProgressPercentString()
// EXAMPLE Dim title as String
// EXAMPLE Dim message as String
// EXAMPLE Dim stage as Integer
// EXAMPLE Dim error as Integer
// EXAMPLE Dim force as Integer
// EXAMPLE Dim canceled as Integer
// EXAMPLE Dim strValue as String
// EXAMPLE Dim resolution as Integer
// EXAMPLE Dim completeChar as String
// EXAMPLE Dim incompleteChar as String
// EXAMPLE Dim percent as Integer
// EXAMPLE Dim count as Integer
// EXAMPLE    
// EXAMPLE completeChar = "|"
// EXAMPLE incompleteChar = "."
// EXAMPLE resolution = 5
// EXAMPLE count = 100
// EXAMPLE
// EXAMPLE title = "Progress Test..."
// EXAMPLE NSL.ProgressStartDialog title
// EXAMPLE Delay 1
// EXAMPLE error = 0
// EXAMPLE stage = 1
// EXAMPLE Do While stage <= count
// EXAMPLE     canceled = NSL.ProgressUserCancel()
// EXAMPLE     If canceled = 1 Then
// EXAMPLE         Exit Do
// EXAMPLE     End If
// EXAMPLE     percent = NSL.ProgressPercent(stage, count)
// EXAMPLE     strValue = NSL.ProgressPercentString(percent, resolution, _
// EXAMPLE                                          completeChar, incompleteChar)
// EXAMPLE     Message = strValue + Chr(10) + Str(percent) _
// EXAMPLE             + "% complete" + Chr(10) _
// EXAMPLE             + "stage = " + Str(stage)
// EXAMPLE     NSL.ProgressUpdateDialog error, message
// EXAMPLE     stage = stage + 1
// EXAMPLE     Delay 0.25
// EXAMPLE Loop
// EXAMPLE    
// EXAMPLE force = 0
// EXAMPLE Delay 1
// EXAMPLE NSL.ProgressStopDialog(force)
{
    THIS_ATTACH_GLOBALS
    
    if (StrLen(title) > progressMaxTitle)
       title[progressMaxTitle] = 0;
    if (gP->progressPtr != NULL)
        PrgStopDialog(gP->progressPtr, true);
    gP->progressPtr = PrgStartDialogV31(title, ProgressCallbackFunction);

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *          T H I S _ P r o g r e s s S t o p D i a l o g
 ********************************************************************/
Err THIS_ProgressStopDialog(UInt16 refNum, Int32 force)
// DESC Stops a Progress Dialog.  This function must be called to
// DESC make the dialog disappear.
// PARAM1 0 = do not force an immediate exit of the dialog
// PARAM1 1 = force an immediate exit of the dialog
// PARAM1     This parameter only has meaning if the dialog is
// PARAM1     in the process of displaying an error message.  If
// PARAM1     "force" is set to 0, then the user must press the
// PARAM1     "OK" button on the dialog before the dialog disappears.
// EXAMPLE See the example provided with ProgressStartDialog()
{
    THIS_ATTACH_GLOBALS
    
    if (gP->progressPtr != NULL)
        PrgStopDialog(gP->progressPtr, (Boolean) force);
    gP->progressPtr = NULL;

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *       T H I S _ P r o g r e s s U p d a t e D i a l o g
 ********************************************************************/
Err THIS_ProgressUpdateDialog(UInt16 refNum, Int32 error, char* message)
// DESC Update the message that is displayed in the Progress Dialog.
// PARAM1 0 = no error
// PARAM1 1 = use error processing
// PARAM1     if "error" is set to 1, the dialog will display the
// PARAM1     specified message and only present one button - "OK".
// PARAM2 Message string to display.  This string must be less than
// PARAM2 128 characters in length.
// EXAMPLE See the example provided with ProgressStartDialog().
{
    THIS_ATTACH_GLOBALS

    if (gP->progressPtr != NULL) {
        if (StrLen(message) > progressMaxMessage)
            message[progressMaxMessage] = 0;
        PrgUpdateDialog(gP->progressPtr, (UInt16) error, (UInt16) 0, message, true);
    }
    
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *       T H I S _ P r o g r e s s U s e r C a n c e l
 ********************************************************************/
Err THIS_ProgressUserCancel(UInt16 refNum, Int32 *canceled)
// DESC Returns 1 if the user pressed the "Cancel" button on the
// DESC Progress dialog.  If you have an operation that should not
// DESC or can not be canceled, then do not call this function.
// DESC The "Cancel" button will still be present, but it will not
// DESC do anything.  Currently, with PalmOS, this button can not
// DESC be made invisible or grayed out.
// EXAMPLE See the example provided with ProgressStartDialog().
{
    EventType event;
    THIS_ATTACH_GLOBALS
    
    if (gP->progressPtr != NULL) {
        *canceled = 0;
        while (EvtEventAvail()) {
            EvtGetEvent(&event, 0);
            PrgHandleEvent(gP->progressPtr, &event);
        }
        *canceled = (Int32) PrgUserCancel(gP->progressPtr);
    }
    else
        *canceled = 1;
        
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *             T H I S _ P r o g r e s s P e r c e nt
 ********************************************************************/
Err THIS_ProgressPercent(UInt16 refNum, Int32 current, Int32 count, Int32 *percent)
// DESC Calculates a percentage complete number based on the 
// DESC input values.  This function is not really part of the
// DESC Progress Manager API.  It is just provided as a convenient
// DESC way to calculate a percentage complete value that can be
// DESC included in your Progress Dialog message.
// PARAM1 Current iteration number of your process loop.
// PARAM2 Number of iterations required to be 100 percent complete.
// EXAMPLE See the example provided with ProgressStartDialog().
{
    *percent = (current * 100) / count;
    
    return 0;
}

/********************************************************************
 *       T H I S _ P r o g r e s s P e r c e n t S t r i n g
 ********************************************************************/
Err THIS_ProgressPercentString(UInt16 refNum, Int32 percent, Int32 resolution, 
                               char *completeChar, char *incompleteChar, char *strValue)
// DESC Constructs a string with characters representing the 
// DESC percentage complete and incomplete for your process loop.
// DESC This function is not really part of the Progress Manager 
// DESC API.  It is just provided as a convenient way to display
// DESC a crude "graphic" representation of your loop's progress. 
// DESC This string can be included as part of your Progress Dialog
// DESC message.
// PARAM1 Percent complete - see also ProgressPercent().
// PARAM2 The resolution size of the percent string.
// PARAM2   A resolution of 1 means that there will be 100
// PARAM2   characters in the percent string.  Every 1% change
// PARAM2   will be reflected in the percent string.  A 
// PARAM2   resolution of 5 means that there will be 20 
// PARAM2   characters in the percent string.  Every 5% change
// PARAM2   will be reflected in the percent string.
// PARAM2   As you can see, the total length of the percent
// PARAM2   string is calculated as (100 / resolution).  As such,
// PARAM2   resolution values should be one of the following:
// PARAM2       1, 2, 4, 5, 10, 20, 25, or 50
// PARAM3 The character to display for the percent completed.
// PARAM3     "|" is recommended.
// PARAM4 The character to display for the percent incomplete.
// PARAM4     "." is recommended.
// PARAM4   The "completeChar" and "incompleteChar" characters
// PARAM4   should probably be characters with the exact same
// PARAM4   pixel width.  Otherwise, the percent string display
// PARAM4   width will vary as the percentage complete changes.
// EXAMPLE See the example provided with ProgressStartDialog().
{
    char s[101];
    Int32 complete;
    UInt8 i;
    
    if (resolution == 0)
        resolution = 10;
    complete = percent / resolution;
    for (i = 0; i < complete; i++)
        s[i] = *completeChar;
    for (i = complete; i < (100 / resolution); i++)
        s[i] = *incompleteChar;
    s[(100 / resolution)] = 0;
    StrCopy(strValue, s);
            
    return 0;
}

// SECTION String Functions
// DESC The following string functions provide convenient methods
// DESC for manipulating strings for use with the other functions
// DESC in this library.

/********************************************************************
 *                    S t r i n g 4 T o I n t
 ********************************************************************/
Err THIS_String4ToInt(UInt16 refNum, char *fourByteString, UInt32 *intValue) 
// DESC Returns the integer value of a 4 byte string.  This function
// DESC is useful for calculating the integer value of Creator IDs,
// DESC Application Types, Resource Types, etc.
// BEFORE
// BEFORE fourByteString = "libr"
// NOTES See also:  IntToString4()
{
    if (StrLen(fourByteString) != 4)
        *intValue = 0;
    else
        *intValue = ((fourByteString[0] * 16777216)
                   + (fourByteString[1] * 65536)
                   + (fourByteString[2] * 256)
                   +  fourByteString[3]);
    return 0;
}

/********************************************************************
 *                    I n t T o S t r i n g 4
 ********************************************************************/
Err THIS_IntToString4(UInt16 refNum, UInt32 intValue, char *fourByteString) 
// DESC Returns a 4 byte string from an integer value.  This function
// DESC is useful for retrieving the string value of integer 
// DESC Creator IDs, Application Types, Resource Types, etc.
// BEFORE
// BEFORE intValue = 1818845810  '"libr"
// NOTES See also:  String4ToInt()
{
    union {
        UInt32 iVal;
        char   cVal[4];
    } x;
    char returnString[5];
    char i;
    
    x.iVal = intValue;
    for (i = 0; i < 4; i++)
        returnString[i] = x.cVal[i];
    returnString[4] = 0;
    StrCopy(fourByteString, returnString);
    return 0;
}

/********************************************************************
 *                     D e l i m i t e d I t e m
 ********************************************************************/
Err THIS_DelimitedItem(UInt16 refNum, 
                       char *inputStr, char *delimiter, Int32 nbr,
                       char *item) 
// DESC Returns a particular substring item from a string that
// DESC contains multiple items separated by a particular delimiter.
// PARAM1 A string containing delimited items.
// PARAM2 A string containing the delimiter character or characters.
// PARAM3 The item number to return.  Item numbers begin with 1.
// RETURNS The delimiter string will be returned if the requested
// RETURNS item is not present.
// NOTES The input string can not be longer than 250 characters.
// BEFORE
// BEFORE inputStr = "Joe;Mary;Jane"
// BEFORE delimiter = ";"
// BEFORE nbr = 2
// BEFORE 'Returns the string "Mary"
{
	char    *s;
	char    *e;
	Int16   i;
	Int16   len;
	
	len = StrLen(delimiter);
	s = inputStr;
	for (i = 1; i <= nbr; i++) {
	    if ((e = StrStr(s, delimiter)) == NULL) {
	        e = StrChr(s, '\0');
	        break;
	    }
	    if (i < nbr)
	        s = e + len;
	}
	if (i < nbr)
	    StrCopy(item, delimiter);
	else {
	    len = e - s;
    	StrNCopy(item, s, len);
	    item[len] = '\0';
	}
	return 0;
}

/********************************************************************
 *                F i x e d W i d t h S t r i n g
 ********************************************************************/
Err THIS_FixedWidthString(UInt16 refNum, char *origStr, Int32 width, 
                          Int32 options, char *fixedStr)
// DESC This function returns a fixed width string.  It can be used
// DESC to create columns of data that line up nicely in fields,
// DESC popups, or list boxes.  A combination of "wide" spaces 
// DESC (chr(25)) and "normal" spaces (chr(32)) are appended, if
// DESC necessary, to pad the string to the desired pixel width.
// DESC Strings that can not fit within the specified width are
// DESC truncated.
// DESC
// DESC A wide space is 5 pixels wide.  A normal space is 2 pixels
// DESC wide.  This function only works with the standard font - font
// DESC id 0. 
// PARAM1 Original string.
// PARAM2 Width in pixels.
// PARAM3 0 = left justify string
// PARAM3 1 = right justify string
// PARAM3 2 = left justify string and use ellipsis (...) if truncated
// PARAM3 3 = right justify string and use ellipsis (...) if truncated
// PARAM3 4 = center justify string and use ellipsis (...) if truncated
// PARAM3 5 = center justify string
// RETURNS Fixed width string
// BEFORE
// BEFORE origStr = "This is a test"
// BEFORE width = 80
// BEFORE options = 0
// NOTES Use the NormalSpacedString() function to translate a
// NOTES fixed width string back to a string containing only
// NOTES normal spaces.
{
    char str[251];
    Int16 origLen;
    Int16 strLen;
    Int16 pixelWidth;
    Boolean truncated;
    Boolean fits;
    Int16 i;
    Int16 nbr;
    Int16 rem;
    FontID saveFont;
    
    saveFont = FntSetFont(0);

    if (options > 1 && options < 5) {
        origLen = ((Int16) StrLen(origStr));
        pixelWidth = (Int16) width;
        FntCharsInWidth(origStr, &pixelWidth, &origLen, &fits);
        if (origLen < ((Int16) StrLen(origStr)))
            truncated = true;
        else
            truncated = false;
    }
    else
        truncated = false;
        
    if (truncated) {
        StrCopy(str, "\x85");    // ellipsis character
        StrCat(str, origStr);
        origLen = ((Int16) StrLen(str)) + 1;
        rem = 1;
        while (rem == 1 || rem == 3) {
            origLen--;
            pixelWidth = (Int16) width;
            FntCharsInWidth(str, &pixelWidth, &origLen, &fits);
            rem = width - pixelWidth;
        }    
    }
    else {
        origLen = ((Int16) StrLen(origStr)) + 1;
        rem = 1;
        while (rem == 1 || rem == 3) {
            origLen--;
            pixelWidth = (Int16) width;
            FntCharsInWidth(origStr, &pixelWidth, &origLen, &fits);
            rem = width - pixelWidth;
        }
    }

    if (options < 4) {
	    nbr = (width - pixelWidth) / 5;
	    rem = (width - pixelWidth) % 5;
	    if (rem == 1 || rem == 3) {
	        nbr--;
	        rem += 5;
	    }
	    if (options == 1 || options == 3) {
	        strLen = 0;
	        str[0] = 0;
	    }
	    else {
	        StrNCopy(str, origStr, origLen);
	        str[origLen] = '\0';
	        strLen = origLen;
	        if (truncated)
	            str[origLen - 1] = 0x85;   // ellipsis character
	    }
	    for (i = 0; i < nbr; i++)
	        str[strLen++] = 25;
	    for (i = 0; i < (rem / 2); i++)
	        str[strLen++] = 32;
	    str[strLen] = 0;
	    if (options == 1 || options == 3) {
	        StrNCat(str, origStr, origLen + strLen + 1);
	        if (truncated)
	            str[StrLen(str) - 1] = 0x85;  // ellipsis character
	    }
	    StrCopy(fixedStr, str);
	}
	else {
	    nbr = (width - pixelWidth) / 2;
	}
    
    saveFont = FntSetFont(saveFont);
    return 0;
}

/********************************************************************
 *                N o r m a l S p a c e d S t r i n g
 ********************************************************************/
Err THIS_NormalSpacedString(UInt16 refNum, char *origStr, char *normalStr)
// DESC Translates a fixed width string to a string containing
// DESC only normal spaces.  This function replaces all "wide" spaces
// DESC (chr(25)) with "normal" spaces (chr(32)).
// NOTES See also:  FixedWidthString()
{
    char str[251];
    UInt8 i;
    
    StrCopy(str, origStr);
    for (i = 0; i < StrLen(str); i++)
        if (str[i] == 25)
            str[i] = 32;
    StrCopy(normalStr, str);
    
    return 0;
}


// SECTION System Time Functions
// DESC The PalmOS system time format is an integer that contains
// DESC the number of seconds since January 1st, 1904.  Most of the
// DESC PalmOS API functions that have date and time parameters use
// DESC this format.  The system time functions provide methods for
// DESC creating and interpretting system time format values.

/********************************************************************
 *                      S e l e c t O n e T i m e
 ********************************************************************/
Err THIS_SelectOneTime(UInt16 refNum, Int32 defHour, Int32 defMinute,
                       char *title, Int32 *newTimeSelected)
// DESC Calls the SelectOneTime() PalmOS function to display a dialog
// DESC that allows a user to select 1 time value.  This function
// DESC returns 1 if a newTime was selected, otherwise it returns 0.
// DESC use the GlobalHour() and GlobalMinute() functions to retrieve
// DESC selected time values.
// PARAM1 Default hour for selection
// PARAM2 Default minute for selection
// BEFORE
// BEFORE defHour = 10
// BEFORE defMinute = 30
// BEFORE title = "Some Title"
// AFTER If newTimeSelected = 1 Then
// AFTER     defHour = NSL.GlobalHour()
// AFTER     defMinute = NSL.GlobalMinute()
// AFTER End If
{
    Int16 hr;
    Int16 mn;
    THIS_ATTACH_GLOBALS
    
    hr = (Int16) defHour;
    mn = (Int16) defMinute;
    *newTimeSelected = (Int32) SelectOneTime(&hr, &mn, title);
    gP->hour = hr;
    gP->minute = mn;
    
    THIS_DETACH_GLOBALS
    return 0;
}


/********************************************************************
 *                I n c r e m e n t S y s t e m T i m e
 ********************************************************************/
Err THIS_IncrementSystemTime(UInt16 refNum, UInt32 oldSysTime,
                            Int32 hours, Int32 minutes, Int32 seconds,
                            UInt32 *newSysTime) 
// DESC Returns a system time value that is incremented by the 
// DESC specified number of hours, minutes, and seconds.  A system
// DESC time value is an integer that is expressed as the number of
// DESC seconds since January 1st, 1904.
// PARAM1 0 = use current system time.
// BEFORE
// BEFORE oldSysTime = 0
// BEFORE hours = 0
// BEFORE minutes = 30
// BEFORE seconds = 0
// BEFORE 'Add 30 minutes
{

    if (oldSysTime == 0)
        *newSysTime = TimGetSeconds();
    else
        *newSysTime = oldSysTime;
    *newSysTime = *newSysTime + (hours * 3600) + (minutes * 60) + seconds;
    
    return 0;
}

/********************************************************************
 *                         S y s t e m T i m e
 ********************************************************************/
Err THIS_SystemTime(UInt16 refNum, 
                   char *strDate, char *strTime, Int32 seconds, 
                   Int32 ToDateFormat,
                   UInt32 *sysTime) 
// DESC Returns a "System Time" value.  This value is expressed as
// DESC the number of seconds since January 1st, 1904.  The time to
// DESC return is supplied as strings in the strDate and strTime
// DESC parameters.  The strDate parameter may contain only a date
// DESC value or both a date and a time value.  If the strTime 
// DESC parameter is blank (""), the time, if specified, in the 
// DESC strDate parameter will be used.  If both the strDate and the
// DESC strTime parameters are blank, the current system time will
// DESC be used. The additional seconds parameter is used to provide
// DESC an easy way to increment or decrement the returned system time.
// DESC For example:
// DESC     systemTime = NSL.SystemTime("", "", 5, 0)
// DESC returns the current time plus 5 seconds.
// PARAM1 See the ToDateFormat parameter for date string formats.
// PARAM2 The time string is specified as: "HH[:MM[:SS]][AM|PM|am|pm]"
// PARAM2 (actually, if the character 'P' or 'p' is present, the time
// PARAM2  will be interpreted as AM/PM format and the hour will be
// PARAM2  appropriately adjusted).
// PARAM3 Increment (or decrement, if negative) the returned systemTime
// PARAM3 by the specified number of seconds.
// PARAM4 0 = strDate string is in MM/DD/YYYY or MM/DD/YY format.
// PARAM4 1 = strDate string is in YYYY/MM/DD or YY/MM/DD format.
// RETURNS Integer time as expressed as the number of seconds since
// RETURNS January 1st, 1904.
// NOTES See also:  StringDateTime(), StringDate(), and StringTime()
// BEFORE
// BEFORE strDate = ""
// BEFORE strTime = ""
// BEFORE Seconds = 5
// BEFORE ToDateFormat = 0
{

    DateTimeType dt;
    char         tStr[32];
    char         *s;
    
    *sysTime = TimGetSeconds();
    TimSecondsToDateTime(*sysTime, &dt);
    
    if (StrLen(strDate) > 0) {
        if (ToDateFormat) {
	        THIS_DelimitedItem(refNum, strDate, "/", 1, tStr);
	        dt.year = StrAToI(tStr);
	        if (dt.year < 49)
	            dt.year = dt.year + 2000;
	        else
	            if (dt.year < 100)
	                dt.year = dt.year + 1900;
	        THIS_DelimitedItem(refNum, strDate, "/", 2, tStr);
	        dt.month = StrAToI(tStr);
	        THIS_DelimitedItem(refNum, strDate, "/", 3, tStr);
	        dt.day = StrAToI(tStr);
        }
        else {
	        THIS_DelimitedItem(refNum, strDate, "/", 1, tStr);
	        dt.month = StrAToI(tStr);
	        THIS_DelimitedItem(refNum, strDate, "/", 2, tStr);
	        dt.day = StrAToI(tStr);
	        THIS_DelimitedItem(refNum, strDate, "/", 3, tStr);
	        dt.year = StrAToI(tStr);
	        if (dt.year < 49)
	            dt.year = dt.year + 2000;
	        else
	            if (dt.year < 100)
	                dt.year = dt.year + 1900;
	    }
    }
        
    if (StrLen(strTime) == 0 && StrLen(strDate) > 0) {
        if ((s = StrChr(strDate, ' ')) != NULL)
            strTime = ++s;
    }
    
    if (StrLen(strTime) > 0) {
        if (!StrCompare(strTime, " ")) {
            dt.hour = 0;
            dt.minute = 0;
            dt.second = 0;
        }
        else {
	        THIS_DelimitedItem(refNum, strTime, ":", 1, tStr);
  	        dt.hour = StrAToI(tStr);
	        if (StrChr(strTime, 'p') || StrChr(strTime, 'P'))
               if (dt.hour < 12)
                   dt.hour = dt.hour + 12;
	        if (StrChr(strTime, 'a') || StrChr(strTime, 'A'))
               if (dt.hour == 12)
                   dt.hour = 0;
	        THIS_DelimitedItem(refNum, strTime, ":", 2, tStr);
	        dt.minute = StrAToI(tStr);
	        dt.second = 0;
    	    THIS_DelimitedItem(refNum, strTime, ":", 3, tStr);
	        if (tStr[0] != ':')
	            dt.second = StrAToI(tStr);
	    }
    }
    
    *sysTime = TimDateTimeToSeconds(&dt) + seconds;
    return 0;
}

/********************************************************************
 *                    S t r i n g D a t e T i m e
 ********************************************************************/
Err THIS_StringDateTime(UInt16 refNum, 
                        UInt32 sysTime,
                        Int32 ToDateFormat,
                        Int32 ToTimeFormat,
                        Int32 AMPMFormat,
                        char *strDateTime) 
// DESC Returns a string representation of the supplied "System Time"
// DESC value.  The sysTime value is an integer value expressed 
// DESC as the number of seconds since January 1st, 1904.  The
// DESC returned value is a string containing both the date and time.
// DESC If the sysTime parameter is specified as 0, the current system 
// DESC date and time will be returned.
// PARAM1 Integer time as expressed as the number of seconds since
// PARAM1 January 1st, 1904.
// PARAM2 0 = the date string will be in MM/DD/YY format.
// PARAM2 1 = the date string will be in YYYY/MM/DD format.
// PARAM2 2 = the date string will be in MM/DD/YYYY format.
// PARAM2 3 = the date string will be in YY/MM/DD format.
// PARAM3 0 = the time string will be in HH:MM format.
// PARAM3 1 = the time string will be in HH:MM:SS format.
// PARAM4 0 = no AM/PM indicators will be added.
// PARAM4 1 = " AM" or " PM" indicator will be added and the hour will
// PARAM4     will be adjusted appropriately.
// NOTES See also:  SystemTime(), StringDate(), and StringTime()
// BEFORE
// BEFORE sysTime = SystemTime("", "", 0, 0) 
{
    char         dtStr[32];
    char         tStr[32];
    
    dtStr[0] = 0;
    if (sysTime == 0)
        sysTime = TimGetSeconds();
    THIS_StringDate(refNum, sysTime, ToDateFormat, dtStr);
    THIS_StringTime(refNum, sysTime, ToTimeFormat, AMPMFormat, tStr);
    StrCat(dtStr, " ");
    StrCat(dtStr, tStr);

    StrCopy(strDateTime, dtStr);
    return 0;
}

/********************************************************************
 *                       S t r i n g D a t e
 ********************************************************************/
Err THIS_StringDate(UInt16 refNum, 
                    UInt32 sysTime,
                    Int32 ToDateFormat,
                    char *strDate) 
// DESC Returns a string representation of the supplied "System Time"
// DESC value.  The sysTime value is an integer value expressed 
// DESC as the number of seconds since January 1st, 1904.  The
// DESC returned value is a string containing only the date.
// DESC If the sysTime parameter is specified as 0, the current system 
// DESC date will be returned.
// PARAM1 Integer time as expressed as the number of seconds since
// PARAM1 January 1st, 1904.
// PARAM2 0 = the date string will be in MM/DD/YY format.
// PARAM2 1 = the date string will be in YYYY/MM/DD format.
// PARAM2 2 = the date string will be in MM/DD/YYYY format.
// PARAM2 3 = the date string will be in YY/MM/DD format.
// NOTES See also:  SystemTime(), StringDateTime(), and StringTime()
// BEFORE
// BEFORE sysTime = SystemTime("", "", 0, 0) 
{
    DateTimeType dt;
    char         dtStr[32];
    char         tStr[32];
    
    dtStr[0] = 0;
    if (sysTime == 0)
        sysTime = TimGetSeconds();
    TimSecondsToDateTime(sysTime, &dt);
    if (ToDateFormat == 1 || ToDateFormat == 3) {
        if (ToDateFormat == 3)
            if (dt.year > 1999)
                dt.year = dt.year - 2000;
            else
                dt.year = dt.year - 1900;
        StrIToA(tStr, dt.year);
        if (dt.year < 10)
            StrCat(dtStr, "0");
        StrCat(dtStr, tStr);
        StrCat(dtStr, "/");
        StrIToA(tStr, dt.month);
        if (dt.month < 10)
            StrCat(dtStr, "0");
        StrCat(dtStr, tStr);
        StrCat(dtStr, "/");
        StrIToA(tStr, dt.day);
        if (dt.day < 10)
            StrCat(dtStr, "0");
        StrCat(dtStr, tStr);
    }
    else {
        StrIToA(tStr, dt.month);
        if (dt.month < 10)
            StrCat(dtStr, "0");
        StrCat(dtStr, tStr);
        StrCat(dtStr, "/");
        StrIToA(tStr, dt.day);
        if (dt.day < 10)
            StrCat(dtStr, "0");
        StrCat(dtStr, tStr);
        StrCat(dtStr, "/");
        if (ToDateFormat == 0)
            if (dt.year > 1999)
                dt.year = dt.year - 2000;
            else
                dt.year = dt.year - 1900;
        StrIToA(tStr, dt.year);
        if (dt.year < 10)
            StrCat(dtStr, "0");
        StrCat(dtStr, tStr);
    }
            
    StrCopy(strDate, dtStr);
    return 0;
}

/********************************************************************
 *                       S t r i n g T i m e
 ********************************************************************/
Err THIS_StringTime(UInt16 refNum, 
                    UInt32 sysTime,
                    Int32 ToTimeFormat,
                    Int32 AMPMFormat,
                    char *strTime) 
// DESC Returns a string representation of the supplied "System Time"
// DESC value.  The sysTime value is an integer value expressed 
// DESC as the number of seconds since January 1st, 1904.  The
// DESC returned value is a string containing only the time.
// DESC If the sysTime parameter is specified as 0, the current system 
// DESC time will be returned.
// PARAM1 Integer time as expressed as the number of seconds since
// PARAM1 January 1st, 1904.
// PARAM2 0 = the time string will be in HH:MM format.
// PARAM2 1 = the time string will be in HH:MM:SS format.
// PARAM3 0 = no AM/PM indicators will be added.
// PARAM3 1 = " AM" or " PM" indicator will be added and the hour will
// PARAM3     will be adjusted appropriately.
// NOTES See also:  SystemTime(), StringDateTime(), and StringDate()
// BEFORE
// BEFORE sysTime = SystemTime("", "", 0, 0) 
{
    DateTimeType dt;
    char         dtStr[32];
    char         tStr[32];
    
    dtStr[0] = 0;
    if (sysTime == 0)
        sysTime = TimGetSeconds();
    TimSecondsToDateTime(sysTime, &dt);
    if (AMPMFormat) {
        if (dt.hour > 12)
            StrIToA(tStr, dt.hour - 12);
        else
            if (dt.hour == 0)
                StrCopy(tStr, "12");
            else
                StrIToA(tStr, dt.hour);
    }
    else
        StrIToA(tStr, dt.hour);
    if (StrLen(tStr) < 2)
        StrCat(dtStr, "0");
    StrCat(dtStr, tStr);
    StrCat(dtStr, ":");
    StrIToA(tStr, dt.minute);
    if (dt.minute < 10)
        StrCat(dtStr, "0");
    StrCat(dtStr, tStr);
    if (ToTimeFormat) {
        StrCat(dtStr, ":");
        StrIToA(tStr, dt.second);
        if (dt.second < 10)
            StrCat(dtStr, "0");
        StrCat(dtStr, tStr);
    }
    if (AMPMFormat)
        if (dt.hour > 11)
            StrCat(dtStr, " PM");
        else
            StrCat(dtStr, " AM");
            
    StrCopy(strTime, dtStr);
    return 0;
}

// SECTION Version 1.4 Changes and Additions
// DESC Version 1.4 contains additional options for the FixedWidthString,
// DESC StringDateTime, and StringDate functions.  
// DESC
// DESC The "rightJustify" parameter of the FixedWidthString function 
// DESC has been changed to "options".  This parameter still controls
// DESC justification but it is also now used to control whether an ellipsis
// DESC ("...") is appended to a string that had to be truncated.
// DESC
// DESC The StringDateTime and StringDate functions now have 2 new
// DESC option values for the "ToDateFormat" parameter.  These options
// DESC provide more flexibility in how the year is formatted.
// DESC
// DESC The following functions are new in this version of the 
// DESC NSBSystemLib shared library.  It would be wise to check
// DESC the NSBSystemLib version number to ensure that it is version
// DESC 1.4 or greater before using any of these new functions.

/********************************************************************
 *                     T H I S _ P o s t E v e n t
 ********************************************************************/
Err THIS_PostEvent(UInt16 refNum, Int32 eventNbr) 
// DESC Posts an event to the event queue by calling EvtAddEventToQueue.
// DESC The event number should be a custom event in the range of
// DESC 24576 to 32767.
// BEFORE eventNbr = 30000
{
    EventType event;
    
    event.eType = eventNbr;
    EvtAddEventToQueue(&event);
    
    return 0;
}

/********************************************************************
 *         T h i s _ F o r m G e t F o c u s
 ********************************************************************/
Err THIS_FormGetFocus(UInt16 refNum, Int32 *objID) 
// DESC Returns the object ID of the object that currently has focus.
// RETURNS -1 if no object has focus.
{
    FormPtr formPtr;
    UInt16  objIndex;
    
    formPtr = FrmGetActiveForm();
    if (formPtr != NULL) {
        objIndex = FrmGetFocus(formPtr);
        if (objIndex != noFocus)
            *objID = (Int32) FrmGetObjectId(formPtr, objIndex);
        else 
            *objID = -1;
    }
    else
        *objID = -1;
        
    return 0;
}

/********************************************************************
 *      T h i s _ F i e l d G e t T e x t L e n g t h
 ********************************************************************/
Err THIS_FieldGetTextLength(UInt16 refNum, Int32 objID, Int32 *txtLen)
// DESC Returns the length of a field's text.
// PARAM1 0 = use field that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// BEFORE
// BEFORE objID = 1008
{
    FieldType *fieldPtr;
    
    fieldPtr = FieldPointer(objID);
    if (fieldPtr != NULL)
        *txtLen = (Int32) FldGetTextLength(fieldPtr);
    else
        *txtLen = 0;

    return 0;
}

/********************************************************************
 *               T h i s _ R a n d o m N u m b e r
 ********************************************************************/
Err THIS_RandomNumber(UInt16 refNum, Int32 seed, Int32 minNbr, Int32 maxNbr, Int32 *nbr)
// DESC Returns a random integer number in the range from min to max.
// PARAM1 New seed value, use 0 to use the existing seed.
// PARAM2 Min must be >= 0 and less than Max
// PARAM3 Max must be <= 32767 and greater than Min
// BEFORE
// BEFORE minNbr = 1
// BEFORE maxNBR = 10
{
    Int16 rNbr;

    rNbr = SysRandom((UInt32) seed);
    *nbr = (Int32) (minNbr + (rNbr % ((maxNbr - minNbr) + 1)));
    return 0;
}

/********************************************************************
 *          T H I S _ R e s e t A u t o O f f T i m e r
 ********************************************************************/
Err THIS_ResetAutoOffTimer(UInt16 refNum) 
// DESC Reset the AutoOffTimer.  This function is typically called in a
// DESC loop to keep the auto off timer from turning off the device
// DESC during long running operations.
{

    EvtResetAutoOffTimer();
    
    return 0;
}

/********************************************************************
 *              T H I S _ S e t A u t o O f f T i m e
 ********************************************************************/
Err THIS_SetAutoOffTime(UInt16 refNum, Int32 newSeconds, Int32 *oldSeconds) 
// DESC Set the auto off time in seconds.  This function returns the
// DESC previous setting so that it can be restored when the program
// DESC or function ends.
// BEFORE
// BEFORE newSeconds = 600  '10 minutes
{

    *oldSeconds = (Int32) SysSetAutoOffTime((UInt16) newSeconds);
    
    return 0;
}

/********************************************************************
 *           T H I S _ P r o g r a m V e r s i o n S t r i n g
 ********************************************************************/
Err THIS_ProgramVersionString(UInt16 refNum, Int32 cardNbr, char *pgmName, char *verStr) 
// DESC Returns a program's version string by reading it's first 'tver'
// DESC resource.  If this resource is not available, the database version
// DESC number is returned.
// BEFORE
// BEFORE cardNbr = 0
// BEFORE pgmName = "NSBSystemLib"
{
    LocalID dbID;
    DmOpenRef dbRef;
    Int16 index;
    MemHandle resH;
    MemPtr resP;
    UInt16 ver;
    
    if (StrLen(pgmName) > 0)
        dbID = DmFindDatabase((UInt16) cardNbr, pgmName);
    else
        dbID = 0;
    if (dbID) {
        dbRef = DmOpenDatabase((UInt16) cardNbr, dbID, dmModeReadOnly);
        if (dbRef) {
	        index = DmFindResourceType(dbRef, 'tver', 0);
	        if (index >= 0) {
	            resH = DmGetResourceIndex(dbRef, index);
	            if (resH) {
	                resP = MemHandleLock(resH);
	                if (resP) {
	                    StrCopy(verStr, (char *) resP);
	                    MemHandleUnlock(resH);
	                }
	                else
	                    StrCopy(verStr, "");
	                DmReleaseResource(resH);
	            }
	            else
	                StrCopy(verStr, "");
	        }
	        else
	            StrCopy(verStr, "");
	        DmCloseDatabase(dbRef);
	    }
	    else
	        StrCopy(verStr, "");
    }
    else
        StrCopy(verStr, "");
    
    if (dbID != 0 && StrLen(verStr) == 0)
        if (DmDatabaseInfo ((UInt16) cardNbr, dbID, NULL, 
                            NULL, &ver, NULL, NULL, NULL, 
                            NULL, NULL, NULL, NULL, NULL) == errNone) {
            StrIToA(verStr, (Int32) ver);
        }
        
    return 0;
}

/********************************************************************
 *              T H I S _ D y n a m i c H e a p S i z e
 ********************************************************************/
Err THIS_DynamicHeapSize(UInt16 refNum, Int32 *heapSize) 
// DESC Returns the size of the Dynamic Heap.
{

    *heapSize = (Int32) MemHeapSize((UInt16) 0);
    
    return 0;
}

/********************************************************************
 *              T H I S _ D y n a m i c H e a p F r e e
 ********************************************************************/
Err THIS_DynamicHeapFree(UInt16 refNum, Int32 *freeSize) 
// DESC Returns the number of free bytes in the Dynamic Heap.
{
    UInt32 freeBytes;
    UInt32 maxChunk;
    
    MemHeapFreeBytes((UInt16) 0, &freeBytes, &maxChunk);
    *freeSize = (Int32) freeBytes;
    
    return 0;
}

/********************************************************************
 *         T H I S _ D y n a m i c H e a p M a x C h u n k
 ********************************************************************/
Err THIS_DynamicHeapMaxChunk(UInt16 refNum, Int32 *maxChunkSize) 
// DESC Returns the size of the largest chunk in the Dynamic Heap.
{
    UInt32 freeBytes;
    UInt32 maxChunk;
    
    MemHeapFreeBytes((UInt16) 0, &freeBytes, &maxChunk);
    *maxChunkSize = (Int32) maxChunk;
    
    return 0;
}

/********************************************************************
 *              T H I S _ S o r t I n i t
 ********************************************************************/
Err THIS_SortInit(UInt16 refNum, Int32 maxItems, char *itemType, Int32 *error) 
// DESC Initializes a sort array to be used with the SortQSort and
// DESC SortInsertionSort functions.  The maxItems parameter specifies
// DESC the maximum number of items to be sorted/added to the sort array.
// DESC This number does not have to be exact, but it must be equal to or
// DESC greater than the number of items actually added.  To free the 
// DESC memory used by a sort array, specify maxItems as 0.  The previous
// DESC sort array is automatically freed when the library is closed at
// DESC program termination or when a new sort array is initialized.
// DESC
// DESC When maxItems is > 0, the itemType parameter specifies the type
// DESC of data that will be sorted.  The itemType parameter is not case
// DESC sensitive and must be one of the following strings:  "string",
// DESC "integer", or "double".  After the sort array is initialized,
// DESC only data of the itemType specified may be added to or retrieved
// DESC from the sort array.
// PARAM1 The maximum number of data items to be added to the sort array.
// PARAM2 The data type to be sorted.
// PARAM2    Valid values are:  "string", "integer", or "double"
// RETURNS  0 = no error
// RETURNS -1 = insufficient dynamic memory
// RETURNS -2 = invalid itemType parameter
// EXAMPLE See either the SortQSort() or SortInsertionSort() functions.
{
    UInt16 i;
    THIS_ATTACH_GLOBALS
    
    gP->sortMaxItems = 0;
    if (gP->sortPtr) {
        for (i = 0; i < gP->sortItems; i++)
            MemPtrFree(gP->sortPtr[i]);
        MemPtrFree(gP->sortPtr); 
        gP->sortPtr = NULL;        
    }
    gP->sortItems = 0;
    if (maxItems <= 0) {
        *error = 0;    
        THIS_DETACH_GLOBALS
        return 0;
    }
    if (StrCaselessCompare(itemType, "string") == 0)
        gP->sortType = 0;
    else
        if (StrCaselessCompare(itemType, "integer") == 0)
            gP->sortType = 1;
        else
            if (StrCaselessCompare(itemType , "double") == 0)
                gP->sortType = 2;
            else {
                *error = -2;
                THIS_DETACH_GLOBALS
                return 0;
            }
    
    gP->sortPtr = MemPtrNew((UInt32) (maxItems * sizeof(MemPtr)));
    if (gP->sortPtr == NULL) 
        *error = -1;
    else {
        gP->sortMaxItems = maxItems;
        *error = 0;
    }
        
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *              T H I S _ S o r t A d d S t r i n g
 ********************************************************************/
Err THIS_SortAddString(UInt16 refNum, char *strItem, Int32 *error) 
// DESC Add a string data item to the sort array.
// PARAM1 String data to add.
// RETURNS  0 = no error
// RETURNS -1 = insufficient dynamic memory
// RETURNS -2 = sort array has not been initialized
// RETURNS -3 = sort array was not initialized for string data
// RETURNS -4 = exceeded the initialized number of items for 
// RETURNS      the sort array
// EXAMPLE See either the SortQSort() or SortInsertionSort() functions.
{
    THIS_ATTACH_GLOBALS
    
    *error = 0;
    if (!gP->sortPtr)
        *error = -2;
    else if (gP->sortType != 0)
        *error = -3;
    else if (gP->sortItems >= gP->sortMaxItems)
        *error = -4;
    if (*error != 0) {
        THIS_DETACH_GLOBALS
        return 0;
    }
    
    gP->sortPtr[gP->sortItems] = MemPtrNew(StrLen(strItem) + 1);
    if (gP->sortPtr[gP->sortItems]) {
        StrCopy((char *) gP->sortPtr[gP->sortItems], strItem);
        gP->sortItems++;
    }
    else
        *error = -1;
        
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *              T H I S _ S o r t A d d I n t e g e r
 ********************************************************************/
Err THIS_SortAddInteger(UInt16 refNum, Int32 intItem, Int32 *error) 
// DESC Add an integer data item to the sort array.
// PARAM1 String data to add.
// RETURNS  0 = no error
// RETURNS -1 = insufficient dynamic memory
// RETURNS -2 = sort array has not been initialized
// RETURNS -3 = sort array was not initialized for integer data
// RETURNS -4 = exceeded the initialized number of items for 
// RETURNS      the sort array
// EXAMPLE See either the SortQSort() or SortInsertionSort() functions.
{
    THIS_ATTACH_GLOBALS
    
    *error = 0;
    if (!gP->sortPtr)
        *error = -2;
    else if (gP->sortType != 1)
        *error = -3;
    else if (gP->sortItems >= gP->sortMaxItems)
        *error = -4;
    if (*error != 0) {
        THIS_DETACH_GLOBALS
        return 0;
    }
    
    gP->sortPtr[gP->sortItems] = MemPtrNew(sizeof(Int32));
    if (gP->sortPtr[gP->sortItems]) {
        MemMove(gP->sortPtr[gP->sortItems], &intItem, sizeof(Int32));
        gP->sortItems++;
    }
    else
        *error = -1;
        
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *              T H I S _ S o r t A d d D o u b l e
 ********************************************************************/
Err THIS_SortAddDouble(UInt16 refNum, double dblItem, Int32 *error) 
// DESC Add a double data item to the sort array.
// PARAM1 String data to add.
// RETURNS  0 = no error
// RETURNS -1 = insufficient dynamic memory
// RETURNS -2 = sort array has not been initialized
// RETURNS -3 = sort array was not initialized for double data
// RETURNS -4 = exceeded the initialized number of items for 
// RETURNS      the sort array
// EXAMPLE See either the SortQSort() or SortInsertionSort() functions.
{
    THIS_ATTACH_GLOBALS
    
    *error = 0;
    if (!gP->sortPtr)
        *error = -2;
    else if (gP->sortType != 2)
        *error = -3;
    else if (gP->sortItems >= gP->sortMaxItems)
        *error = -4;
    if (*error != 0) {
        THIS_DETACH_GLOBALS
        return 0;
    }
    
    gP->sortPtr[gP->sortItems] = MemPtrNew(8);
    if (gP->sortPtr[gP->sortItems]) {
        MemMove(gP->sortPtr[gP->sortItems], &dblItem, 8);
        gP->sortItems++;
    }
    else
        *error = -1;
        
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *              T H I S _ S o r t G e t S t r i n g
 ********************************************************************/
Err THIS_SortGetString(UInt16 refNum, Int32 index, char *strItem) 
// DESC Retrieve a string data item from the sort array.
// PARAM1 The index or subscript of a data item in the sort array.
// EXAMPLE See either the SortQSort() or SortInsertionSort() functions.
{
    Int32 error;
    THIS_ATTACH_GLOBALS
    
    error = 0;
    if (!gP->sortPtr)
        error = -2;
    else if (gP->sortType != 0)
        error = -3;
    else if (index < 1 || index > gP->sortItems)
        error = -4;
    if (error != 0) {
        StrCopy(strItem, "");
        THIS_DETACH_GLOBALS
        return 0;
    }
    
    StrCopy(strItem, (char *) gP->sortPtr[index - 1]);
        
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *              T H I S _ S o r t G e t I n t e g e r
 ********************************************************************/
Err THIS_SortGetInteger(UInt16 refNum, Int32 index, Int32 *intItem) 
// DESC Retrieve an integer data item from the sort array.
// PARAM1 The index or subscript of a data item in the sort array.
// EXAMPLE See either the SortQSort() or SortInsertionSort() functions.
{
    Int32 error;
    THIS_ATTACH_GLOBALS
    
    error = 0;
    if (!gP->sortPtr)
        error = -2;
    else if (gP->sortType != 1)
        error = -3;
    else if (index < 1 || index > gP->sortItems)
        error = -4;
    if (error != 0) {
        *intItem = 0;
        THIS_DETACH_GLOBALS
        return 0;
    }
    
    MemMove(intItem, gP->sortPtr[index - 1], sizeof(Int32));
        
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *              T H I S _ S o r t G e t D o u b l e
 ********************************************************************/
Err THIS_SortGetDouble(UInt16 refNum, Int32 index, double *dblItem) 
// DESC Retrieve a double data item from the sort array.
// PARAM1 The index or subscript of a data item in the sort array.
// EXAMPLE See either the SortQSort() or SortInsertionSort() functions.
{
    Int32 error;
    THIS_ATTACH_GLOBALS
    
    error = 0;
    if (!gP->sortPtr)
        error = -2;
    else if (gP->sortType != 2)
        error = -3;
    else if (index < 1 || index > gP->sortItems)
        error = -4;
    if (error != 0) {
        *dblItem = 0.0;
        THIS_DETACH_GLOBALS
        return 0;
    }
    
    MemMove(dblItem, gP->sortPtr[index - 1], 8);
        
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *                    T H I S _ S o r t Q S o r t
 ********************************************************************/
Err THIS_SortQSort(UInt16 refNum, Int32 reverseSort, Int32 caselessSort, Int32 *numItems) 
// DESC Performs a "quick sort" of the items in the sort array that was
// DESC initialized with SortInit() and populated with either SortAddString(),
// DESC SortAddInteger(), or SortAddDouble().  This function calls the
// DESC SysQSort PalmOS API function.  The SortInsertionSort function
// DESC can also be used.  Here is how the PalmOS SDK documentation
// DESC describes the SysQSort API function:
// DESC
// DESC Equal records can be in any position relative to each other
// DESC because a quick sort tends to scramble the ordering of 
// DESC records. As a result, calling SysQSort multiple times can 
// DESC result in a different order if the records are not 
// DESC completely unique. If you don't want this behavior, use the
// DESC insertion sort instead (see SysInsertionSort). 
// DESC
// DESC To pick the pivot point, the quick sort algorithm picks the
// DESC middle of three records picked from around the middle of 
// DESC all records. That way, the algorithm can take advantage of 
// DESC partially sorted data. 
// DESC
// DESC These optimizations are built in: 
// DESC
// DESC The routine contains its own stack to limit uncontrolled 
// DESC recursion. When the stack is full, an insertion sort is 
// DESC used because it doesn't require more stack space. 
// DESC
// DESC An insertion sort is also used when the number of records 
// DESC is low. This avoids the overhead of a quick sort which is 
// DESC noticeable for small numbers of records. 
// DESC
// DESC If the records seem mostly sorted, an insertion sort is 
// DESC performed to move only those few records that need to be 
// DESC moved.
// PARAM1 0 = list is sorted from lowest to highest values
// PARAM1 1 = list is sorted from highest to lowest values
// PARAM2 0 = sort is case sensitive
// PARAM2 1 = sort is not case sensitive
// RETURNS the number of items sorted
// RETURNS   Use the appropriate function (SortGetString(),
// RETURNS   SortGetInteger(), or SortGetDouble()) to return the
// RETURNS   items from the sort array.
// EXAMPLE Dim error as Integer
// EXAMPLE Dim maxItems as Integer
// EXAMPLE Dim itemType as String
// EXAMPLE Dim numItems as Integer
// EXAMPLE Dim reverseSort as Integer
// EXAMPLE Dim caselessSort as Integer
// EXAMPLE Dim i as Integer
// EXAMPLE Dim tmpStr as String
// EXAMPLE
// EXAMPLE maxItems = 100
// EXAMPLE itemType = "string"
// EXAMPLE error = NSL.SortInit(maxItems, itemType)
// EXAMPLE If error <> 0 Then
// EXAMPLE     MsgBox "SortInit error = " + Str(error)
// EXAMPLE     Exit Sub
// EXAMPLE End If
// EXAMPLE
// EXAMPLE For i = 1 to someNumber
// EXAMPLE     error = NSL.SortAddString(someStringArray(i))
// EXAMPLE     If error <> 0 Then
// EXAMPLE         MsgBox "SortAddString error = " + Str(error)
// EXAMPLE         Exit Sub
// EXAMPLE     End If
// EXAMPLE Next
// EXAMPLE
// EXAMPLE reverseSort = 0     'Sort from lowest to highest
// EXAMPLE caselessSort = 1    'Case insensitive sort
// EXAMPLE numItems = NSL.SortQSort(reverseSort, caselessSort)
// EXAMPLE
// EXAMPLE For i = 1 to numItems
// EXAMPLE    tmpStr = NSL.SortGetString(i)
// EXAMPLE    someStringArray(i) = tmpStr
// EXAMPLE Next
{
    Int32 other = 0;
    THIS_ATTACH_GLOBALS
    
    *numItems = 0;
    if (!gP->sortPtr)
        *numItems = -1;
    else if (gP->sortItems < 2)
        *numItems = -2;
    if (*numItems != 0) {
        THIS_DETACH_GLOBALS
        return 0;
    }
    
    other = SortOtherValue(gP->sortType, (Boolean) reverseSort, (Boolean) caselessSort);
    SysQSort((void *) gP->sortPtr, (Int16) gP->sortItems, 
             (Int16) sizeof(MemPtr), (CmpFuncPtr) SortCompareFunction, other); 

    *numItems = gP->sortItems;
        
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *            T H I S _ S o r t I n s e r t i o n S o r t
 ********************************************************************/
Err THIS_SortInsertionSort(UInt16 refNum, Int32 reverseSort, Int32 caselessSort, Int32 *numItems) 
// DESC Performs an "insertion sort" of the items in the sort array that was
// DESC initialized with SortInit() and populated with either SortAddString(),
// DESC SortAddInteger(), or SortAddDouble().  This function calls the
// DESC SysInsertionSort PalmOS API function.  The SortQSort function
// DESC can also be used.  Here is how the PalmOS SDK documentation
// DESC describes the SysInsertionSort API function:
// DESC
// DESC Only elements which are out of order move. Moved elements 
// DESC are moved to the end of the range of equal elements. If a 
// DESC large amount of elements are being sorted, try to use the 
// DESC quick sort (see SysQSort). 
// DESC
// DESC This is the insertion sort algorithm: Starting with the second 
// DESC element, each element is compared to the preceding element. Each 
// DESC element not greater than the last is inserted into sorted position
// DESC within those already sorted. A binary search for the insertion 
// DESC point is performed. A moved element is inserted after any other 
// DESC equal elements. 
// PARAM1 0 = list is sorted from lowest to highest values
// PARAM1 1 = list is sorted from highest to lowest values
// PARAM2 0 = sort is case sensitive
// PARAM2 1 = sort is not case sensitive
// RETURNS the number of items sorted
// RETURNS   Use the appropriate function (SortGetString(),
// RETURNS   SortGetInteger(), or SortGetDouble()) to return the
// RETURNS   items from the sort array.
// EXAMPLE Dim error as Integer
// EXAMPLE Dim maxItems as Integer
// EXAMPLE Dim itemType as String
// EXAMPLE Dim numItems as Integer
// EXAMPLE Dim reverseSort as Integer
// EXAMPLE Dim caselessSort as Integer
// EXAMPLE Dim i as Integer
// EXAMPLE Dim tmpStr as String
// EXAMPLE
// EXAMPLE maxItems = 100
// EXAMPLE itemType = "string"
// EXAMPLE error = NSL.SortInit(maxItems, itemType)
// EXAMPLE If error <> 0 Then
// EXAMPLE     MsgBox "SortInit error = " + Str(error)
// EXAMPLE     Exit Sub
// EXAMPLE End If
// EXAMPLE
// EXAMPLE For i = 1 to someNumber
// EXAMPLE     error = NSL.SortAddString(someStringArray(i))
// EXAMPLE     If error <> 0 Then
// EXAMPLE         MsgBox "SortAddString error = " + Str(error)
// EXAMPLE         Exit Sub
// EXAMPLE     End If
// EXAMPLE Next
// EXAMPLE
// EXAMPLE reverseSort = 0     'Sort from lowest to highest
// EXAMPLE caselessSort = 1    'Case insensitive sort
// EXAMPLE numItems = NSL.SortInsertionSort(reverseSort, caselessSort)
// EXAMPLE
// EXAMPLE For i = 1 to numItems
// EXAMPLE    tmpStr = NSL.SortGetString(i)
// EXAMPLE    someStringArray(i) = tmpStr
// EXAMPLE Next
{
    Int32 other = 0;
    THIS_ATTACH_GLOBALS
    
    *numItems = 0;
    if (!gP->sortPtr)
        *numItems = -1;
    else if (gP->sortItems < 2)
        *numItems = -2;
    if (*numItems != 0) {
        THIS_DETACH_GLOBALS
        return 0;
    }
    
    other = SortOtherValue(gP->sortType, (Boolean) reverseSort, (Boolean) caselessSort);
    SysInsertionSort((void *) gP->sortPtr, (Int16) gP->sortItems, 
             (Int16) sizeof(MemPtr), (CmpFuncPtr) SortCompareFunction, other); 

    *numItems = gP->sortItems;
        
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *                    T H I S _ L i s t Q S o r t
 ********************************************************************/
Err THIS_ListQSort(UInt16 refNum, Int32 objID, Int32 reverseSort, Int32 caselessSort, Int32 *numItems) 
// DESC Performs a "quick sort" of the items in an existing List 
// DESC object.  This routine uses the SysQSort PalmOS API function.
// DESC The ListInsertionSort function can also be used.  To compare
// DESC the differences between the quick sort and insertion sort 
// DESC algorythms, please review the descriptions of the SortQSort
// DESC and SortInsertionSort functions in this library.
// PARAM1 objectID of the list object
// PARAM1   Use 0 to specify the object that currently has focus.
// PARAM2 0 = list is sorted from lowest to highest values
// PARAM2 1 = list is sorted from highest to lowest values
// PARAM3 0 = sort is case sensitive
// PARAM3 1 = sort is not case sensitive
// RETURNS the number of items sorted
// BEFORE
// BEFORE objID = 1008
// BEFORE reverseSort = 0
// BEFORE caselessSort = 0
{
    Int32 other = 0;
    ListType *listPtr;
    Char **items;

    *numItems = 0;    
    listPtr = ListPointer(objID);
    
    if (!listPtr)
        *numItems = -1;
    else {
        *numItems = (Int32) LstGetNumberOfItems(listPtr);
        if (*numItems < 2)
	        *numItems = -2;
	    else
	        *numItems = 0;
	}
    if (*numItems != 0) {
        return 0;
    }
    
    *numItems = (Int32) LstGetNumberOfItems(listPtr);
    items = LstGlueGetItemsText(listPtr);
    other = SortOtherValue(0, (Boolean) reverseSort, (Boolean) caselessSort);
    SysQSort((void *) items, (Int16) *numItems, 
             (Int16) sizeof(MemPtr), (CmpFuncPtr) SortCompareFunction, other);
    LstSetListChoices(listPtr, items, (UInt16) *numItems); 
    LstDrawList(listPtr);
    *numItems = (Int32) LstGetNumberOfItems(listPtr);
    return 0;
}

/********************************************************************
 *                    T H I S _ L i s t I n s e r t i o n S o r t
 ********************************************************************/
Err THIS_ListInsertionSort(UInt16 refNum, Int32 objID, Int32 reverseSort, Int32 caselessSort, Int32 *numItems) 
// DESC Performs an "insertion sort" of the items in an existing List 
// DESC object.  This routine uses the SysInsertionSort PalmOS API function.
// DESC The ListQSort function can also be used.  To compare
// DESC the differences between the quick sort and insertion sort 
// DESC algorythms, please review the descriptions of the SortQSort
// DESC and SortInsertionSort functions in this library.
// PARAM1 objectID of the list object
// PARAM1   Use 0 to specify the object that currently has focus.
// PARAM2 0 = list is sorted from lowest to highest values
// PARAM2 1 = list is sorted from highest to lowest values
// PARAM3 0 = sort is case sensitive
// PARAM3 1 = sort is not case sensitive
// RETURNS the number of items sorted
// BEFORE
// BEFORE objID = 1008
// BEFORE reverseSort = 0
// BEFORE caselessSort = 0
{
    Int32 other = 0;
    ListType *listPtr;
    Char **items;
    
    *numItems = 0;    
    listPtr = ListPointer(objID);
    
    if (!listPtr)
        *numItems = -1;
    else {
        *numItems = (Int32) LstGetNumberOfItems(listPtr);
        if (*numItems < 2)
	        *numItems = -2;
	    else
	        *numItems = 0;
	}
    if (*numItems != 0) {
        return 0;
    }
    
    *numItems = (Int32) LstGetNumberOfItems(listPtr);
    items = LstGlueGetItemsText(listPtr);
    other = SortOtherValue(0, (Boolean) reverseSort, (Boolean) caselessSort);
    SysInsertionSort((void *) items, (Int16) *numItems, 
             (Int16) sizeof(MemPtr), (CmpFuncPtr) SortCompareFunction, other); 
    LstSetListChoices(listPtr, items, (UInt16) *numItems); 
    LstDrawList(listPtr);
    *numItems = (Int32) LstGetNumberOfItems(listPtr);
        
    return 0;
}

// SECTION Version 2.0 Changes and Additions
// DESC Version 2.0 contains additional options for the FixedWidthString,
// DESC StringDateTime, and StringDate functions.  
// DESC
// DESC The "rightJustify" parameter of the FixedWidthString function 
// DESC has been changed to "options".  This parameter still controls
// DESC justification but it is also now used to control whether an ellipsis
// DESC ("...") is appended to a string that had to be truncated.
// DESC
// DESC The following functions are new in this version of the 
// DESC NSBSystemLib shared library.  It would be wise to check
// DESC the NSBSystemLib version number to ensure that it is version
// DESC 2.0 or greater before using any of these new functions.

/********************************************************************
 *       T H I S _ F o r m G e t A l l O b j e c t T y p e s
 ********************************************************************/
Err THIS_FormGetAllObjectTypes(UInt16 refNum, Int32 objID, Int32 *type)
// DESC Retrieves the object type of the specified object.
// PARAM1 0 = use object that currently has focus
// PARAM1     objID may be either an Object ID or an Object Index.
// PARAM1     If the value of objID is between 1 and the number of
// PARAM1     objects on the form, objID is assumed to be an Object
// PARAM1     Index, otherwise, it is assumed to be an Object ID.
// RETURNS -1 if the object is invalid or no object has focus
// RETURNS  0 = frmFieldObj
// RETURNS  2 = frmListObj
// RETURNS  3 = frmTableObj
// RETURNS  4 = frmBitmapObj
// RETURNS  5 = frmLineObj
// RETURNS  6 = frmFrameObj
// RETURNS  7 = frmRectangleObj
// RETURNS  8 = frmLabelObj
// RETURNS  9 = frmTitleObj
// RETURNS 10 = frmPopupObj
// RETURNS 11 = frmGraffitiStateObj
// RETURNS 12 = frmGadgetObj
// RETURNS 13 = frmScrollbarObj
// RETURNS 100 = buttonCtl
// RETURNS 101 = pushButtonCtl
// RETURNS 102 = checkboxCtl
// RETURNS 103 = popupTriggerCtl
// RETURNS 104 = selectorTriggerCtl
// RETURNS 105 = repeatingButtonCtl
// RETURNS 106 = sliderCtl
// RETURNS 107 = feedbackSliderCtl
// BEFORE objID = 1008 
// NOTES This function differs from FormGetObjectType() in that it interprets
// NOTES the individual Control object types rather than just retuning a type
// NOTES of frmControlObj (value 1).
{
    UInt16 objectIndex;
    FormPtr formPtr;
    ControlPtr ctlPtr;
    ControlStyleType style;
    
    objectIndex = ObjectIndex(objID, &formPtr);
    if (objectIndex != noFocus) {
        *type = (Int32) FrmGetObjectType(formPtr, objectIndex);
        if (*type == (Int32) frmControlObj) {
            ctlPtr = FrmGetObjectPtr(formPtr, objectIndex);
            style = CtlGlueGetControlStyle(ctlPtr);
            *type = (Int32) style + 100;
        }
    }
    else
        *type = -1;

    return 0;
}

/********************************************************************
 *             T H I S _ F i e l d C l e a r A l l
 ********************************************************************/
Err THIS_FieldClearAll(UInt16 refNum)
// DESC Clears/erases the text from all the fields on a form.
{
    FormPtr formPtr;
    FieldType *fieldPtr;
    UInt16 n;
    UInt16 index;
    FormObjectKind type;
    MemHandle oldTextH;
    
    formPtr = FrmGetActiveForm();
    if (formPtr != NULL) {
        n = FrmGetNumberOfObjects(formPtr);
        for (index = 0; index < n; index++) {
            type = FrmGetObjectType(formPtr, index);
            if (type == frmFieldObj) {
                fieldPtr = FrmGetObjectPtr(formPtr, index);
                oldTextH = FldGetTextHandle(fieldPtr);
                FldSetTextHandle(fieldPtr, NULL);
                FldDrawField(fieldPtr);
                if (oldTextH)
                    MemHandleFree(oldTextH);
            }
        }
    }

    return 0;
}

/********************************************************************
 *             T H I S _ O b j e c t W i t h P o i n t
 ********************************************************************/
Err THIS_ObjectWithPoint(UInt16 refNum, Int32 x, Int32 y, 
                         Int32 returnType, Int32 searchOption, Int32 *obj)
// DESC Returns the first object that has the x and y coordinates within
// DESC it's bounds.
// PARAM1 x coordinate
// PARAM2 y coordinate
// PARAM3 0 = return the object's ID
// PARAM3 1 = return the object's index
// PARAM3     This index is in the range of 1 to number of objects
// PARAM3     on the form. It is the PalmOS index incremented by 1
// PARAM3     so that it can be used with other functions in this
// PARAM3     library.  If you use this value with a Systrap, you
// PARAM3     must subtract 1 from the index.
// PARAM3 2 = return the object's pointer (use variant as the return type)
// PARAM4 0 = search for objects that are usable, visible, and enabled/editable
// PARAM4 1 = search for objects that are usable and visible
// PARAM4 2 = search for all objects
// RETURNS object as either an object ID, index, or pointer
// RETURNS -1 or NULL (0 if returning a pointer) when no object was found
{
    FormPtr formPtr;
    UInt16 n;
    UInt16 index;
    RectangleType rect;
    Boolean objUsable;
    FieldType *fieldPtr;
    FieldAttrType attrs;

    formPtr = FrmGetActiveForm();
    objUsable = true;
    if (returnType == 2)
        *obj = (Int32) NULL;
    else
        *obj = -1;
    if (formPtr != NULL) {
        n = FrmGetNumberOfObjects(formPtr);
        for (index = 0; index < n; index++) {
            FrmGetObjectBounds(formPtr, index, &rect);
            if (RctPtInRectangle((Coord) x, (Coord) y, &rect)) {
                objUsable = FrmGlueGetObjectUsable(formPtr, index);
                if (((searchOption == 0 || searchOption == 1) && objUsable) ||
                    (searchOption == 2)) {
                    if ((searchOption == 0 || searchOption ==1) && FrmGetObjectType(formPtr, index) == frmFieldObj) {
                    	fieldPtr = FrmGetObjectPtr(formPtr, index);
                    	if (fieldPtr != NULL) {
					        FldGetAttributes(fieldPtr, &attrs);
					        if (searchOption == 0) {
						        if (attrs.editable == 0 || attrs.visible == 0)
						            continue;
						    }
						    else
						    	if (attrs.visible == 0)
						    		continue;
					    }
					    else
					    	continue;
                    }
                    if (returnType == 2)
                        *obj = (Int32) FrmGetObjectPtr(formPtr, index);
                    else
                        if (returnType == 1)
                            *obj = (Int32) index + 1;
                        else
                            *obj = (Int32) FrmGetObjectId(formPtr, index);
                    break;
                }
            }
        }
    }

    return 0;
}

// VICTORY

/********************************************************************
 *                T H I S _ A N D I n t
 ********************************************************************/
Err THIS_ANDInt(UInt16 refNum, Int32 int1, Int32 int2, Int32 *result)
// DESC Returns a bitwise AND of the int1 and int2 parameters.
{
    *result = int1 & int2;
    
    return 0;
}

/********************************************************************
 *                T H I S _ O R I n t
 ********************************************************************/
Err THIS_ORInt(UInt16 refNum, Int32 int1, Int32 int2, Int32 *result)
// DESC Returns a bitwise OR of the int1 and int2 parameters.
{
    *result = int1 | int2;
    
    return 0;
}

/********************************************************************
 *                T H I S _ X O R I n t
 ********************************************************************/
Err THIS_XORInt(UInt16 refNum, Int32 int1, Int32 int2, Int32 *result)
// DESC Returns a bitwise XOR of the int1 and int2 parameters.
{
    *result = int1 ^ int2;
    
    return 0;
}

/********************************************************************
 *             T H I S _ O n e s C o m p l e m e n t
 ********************************************************************/
Err THIS_OnesComplement(UInt16 refNum, Int32 intValue, Int32 *result)
// DESC Returns the "one's complement" of the intValue parameter.
// DESC This essentially turns all 1 bits to 0 and all 0 bits to 1.
{
    *result = ~intValue;
    
    return 0;
}

/********************************************************************
 *                T H I S _ B i t V a l u e
 ********************************************************************/
Err THIS_BitValue(UInt16 refNum, Int32 intValue, Int32 bitNumber, Int32 *result)
// DESC Returns 1 if the specified bit number is 1, otherwise it
// DESC returns 0.
// PARAM2 Bits are numbered from right to left from 0 to 31.
{
    if (bitNumber < 0)
        bitNumber = 0;
    if (bitNumber > 31)
        bitNumber = 31;
    if (intValue & bitMask(bitNumber))
        *result = 1;
    else
        *result = 0;
    
    return 0;
}

/********************************************************************
 *                T H I S _ B i t s V a l u e
 ********************************************************************/
Err THIS_BitsValue(UInt16 refNum, Int32 intValue, Int32 startBit, Int32 endBit, Int32 *result)
// DESC Returns the integer value of the specified bits.  The bits
// DESC retrieved include the starting and ending bit numbers.
// DESC Therefore, BitsValue(intValue, 5, 7) returns the
// DESC value of bits 5, 6, and 7.
// PARAM2 Bits are numbered from right to left from 0 to 31.
// PARAM3 Bits are numbered from right to left from 0 to 31.
{
    Int32 numberOfBits;
    
    numberOfBits = (endBit - startBit) + 1;
    if (endBit < 0)
        endBit = 0;
    if (endBit > 31)
        endBit = 31;
    if ((endBit - numberOfBits) < 0)
        numberOfBits = endBit + 1;
    if (numberOfBits <= 0) {
        *result = 0;
    }
    *result = (intValue >> (endBit + 1 - numberOfBits)) & ~(~0 << numberOfBits);
    
    return 0;
}

/********************************************************************
 *                T H I S _ S e t B i t V a l u e
 ********************************************************************/
Err THIS_SetBitValue(UInt16 refNum, Int32 intValue, Int32 bitNumber, 
                  Int32 bitValue, Int32 *result)
// DESC Sets the bit specified by bitNumber to the specified
// DESC bit value.
// PARAM2 Bits are numbered from right to left from 0 to 31.
{
    if (bitNumber < 0)
        bitNumber = 0;
    if (bitNumber > 31)
        bitNumber = 31;
    if (bitValue)
        *result = (intValue | bitMask(bitNumber));
    else
        *result = (intValue & ~(bitMask(bitNumber)));
    
    return 0;
}

/********************************************************************
 *                T H I S _ S e t B i t s V a l u e
 ********************************************************************/
Err THIS_SetBitsValue(UInt16 refNum, Int32 intValue, Int32 bitsValue, 
                      Int32 startBit, Int32 endBit, Int32 *result)
// DESC Sets the specified bits to the integer value  
// DESC specified by bitValue.  The bits set include the starting and ending
// DESC bits.  Therefore, SetBitsValue(intValue, 3, 5, 7) sets the value of 
// DESC bits 5, 6, and 7.
// PARAM2 Bits are numbered from right to left from 0 to 31.
// PARAM3 Bits are numbered from right to left from 0 to 31.
{
    Int8 i;
    Int8 n;
    Int32 numberOfBits;
    
    numberOfBits = (endBit - startBit) + 1;
    if (endBit < 0)
        endBit = 0;
    if (endBit > 31)
        endBit = 31;
    if ((endBit - numberOfBits) < 0)
        numberOfBits = endBit + 1;
    if (numberOfBits <= 0) {
        *result = intValue;
        return 0;
    }
    *result = intValue;
    n = numberOfBits - 1;
    for (i = endBit; i > (endBit - numberOfBits); i--)
        if (bitsValue & bitMask(n--))
            *result = (*result | bitMask(i));
        else
            *result = (*result & ~(bitMask(i)));
                
    return 0;
}

/********************************************************************
 *                T H I S _ I n t T o H e x
 ********************************************************************/
Err THIS_IntToHex(UInt16 refNum, Int32 intValue, Int32 trimLeading, char *hexValue)
// DESC Convert the specified integer value to a hexadecimal string.
// PARAM2 0 = do not trim leading zeros from result string
// PARAM2 1 = trim leading zeros from result string.
{
    char hexV[9];
    char *s;
    
    StrIToH(hexV, (UInt32) intValue);
    if (trimLeading) {
        s = hexV;
        while (*s == '0')
            s++;
        if (StrLen(s) == 0)
            StrCopy(hexValue, "0");
        else
            StrCopy(hexValue, s);
    }
    else
        StrCopy(hexValue, hexV);    
    return 0;
}

/********************************************************************
 *                T H I S _ H e x T o I n t
 ********************************************************************/
Err THIS_HexToInt(UInt16 refNum, char *hexValue, Int32 *intValue)
// DESC Convert the specified hexadecimal string to an integer value.
{
    char   hexV[10];
    Int8   i;
    UInt32 multiplier = 1;
    char   *s;
    UInt16 len;
    
    len = StrLen(hexValue);
    if ((s = StrChr(hexValue, ' ')) != NULL)
        len = (UInt16) (s - hexValue);
    hexV[0] = 0;
    for (i = 0; i < 8 - len; i++)
        hexV[i] = '0';
    hexV[i] = 0;
    StrNCat(hexV, hexValue, 9);
    hexV[8] = 0;
    
    for (i = 0; i < 8; i++)
        if (hexV[i] >= '0' && hexV[i] <= '9')
            hexV[i] = hexV[i] - '0';
        else
            if (hexV[i] >= 'a' && hexV[i] <= 'f')
                hexV[i] = (hexV[i] - 'a') + 10;
            else
                if (hexV[i] >= 'A' && hexV[i] <= 'F')
                    hexV[i] = (hexV[i] - 'A') + 10;
                else {
                    *intValue = 0;
                    return 0;
                }
                
    *intValue = 0;
    for (i = 7; i >= 0; i--) {
        *intValue = *intValue + (hexV[i] * multiplier);
        multiplier = multiplier * 16;
    }
    
    return 0;
}

/********************************************************************
 *                T H I S _ I n t T o B i n
 ********************************************************************/
Err THIS_IntToBin(UInt16 refNum, Int32 intValue, Int32 trimLeading, char *binValue)
// DESC Convert the specified integer value to a binary string.
// PARAM2 0 = do not trim leading zeros from result string
// PARAM2 1 = trim leading zeros from result string.
{
    Int8 i;
    Int8 n = 0;
    char binV[33];
    
    for (i = 31; i >= 0; i--)
        if ((UInt32) intValue & bitMask(i)) {
            binV[n++] = '1';
            trimLeading = 0;
        }
        else
            if (trimLeading == 0)
                binV[n++] = '0';
    binV[n] = 0;
    StrCopy(binValue, binV);
    
    return 0;
}

/********************************************************************
 *                T H I S _ B i n T o I n t
 ********************************************************************/
Err THIS_BinToInt(UInt16 refNum, char *binValue, Int32 *intValue)
// DESC Convert the specified binary string to an integer value.
{
    char   binV[34];
    Int8   i;
    UInt32 multiplier = 1;
    char   *s;
    UInt32 intV;
    UInt16 len;
    
    len = StrLen(binValue);
    if ((s = StrChr(binValue, ' ')) != NULL)
        len = (UInt16) (s - binValue);
    binV[0] = 0;
    for (i = 0; i < 32 - len; i++)
        binV[i] = '0';
    binV[i] = 0;
    StrNCat(binV, binValue, 33);
    binV[32] = 0;

    intV = 0;   
    for (i = 31; i >= 0; i--)
        if (binV[(0 - i) + 31] != '0')
            intV = (intV | bitMask(i));

    *intValue = (Int32) intV;
    return 0;
}

// SECTION Screen and Color Functions

/********************************************************************
 *          T H I S _ G e t S u p p o r t e d D e p t h s
 ********************************************************************/
Err THIS_GetSupportedDepths(UInt16 refNum, Int32 *depths)
// DESC	Returns a bitmapped integer with each bit indicating a
// DESC	bitmap depth supported by the PalmOS device.
// NOTE	The bit manipulation functions in this library or the 
// NOTE NS Basic Shared Library "BitsNBytes" probably provide
// NOTE	the best suited functions for evaluating the returned value
// NOTE	from this function.
{
    Err err;
    UInt32 supportedDepthMap;
    
    err = WinScreenMode(winScreenModeGetSupportedDepths, 
                        NULL, NULL, &supportedDepthMap, NULL);
    *depths = (Int32) supportedDepthMap;
    
	return 0 ;
}

/********************************************************************
 *             T H I S _ D e p t h S u p p o r t e d
 ********************************************************************/
Err THIS_DepthSupported(UInt16 refNum, Int32 depth, Int32 *boolean)
// DESC	Returns 1 if the specified depth is supported by the
// DESC	PalmOS device.  Otherwise, it returns 0.
// BEFORE
// BEFORE depth = 4
{
    Err err;
    UInt32 supportedDepthMap;
    
    err = WinScreenMode(winScreenModeGetSupportedDepths, 
                        NULL, NULL, &supportedDepthMap, NULL);
    if (supportedDepthMap & bitDepthMask(depth))
        *boolean = 1;
    else
    	*boolean = 0;
    	
	return 0;
}

/********************************************************************
 *               T H I S _ C o l o r S u p p o r t e d
 ********************************************************************/
Err THIS_ColorSupported(UInt16 refNum, Int32 *boolean) 
// DESC	Returns 1 if the PalmOS device has color capabilities.
// DESC	Otherwise, it returns 0.
{
    Err err;
    Boolean supportsColor;
    
    err = WinScreenMode(winScreenModeGetSupportsColor, 
                        NULL, NULL, NULL, &supportsColor);
    *boolean = (Int32) supportsColor;
	return 0;
}

/********************************************************************
 *                   T H I S _ S e t D e p t h
 ********************************************************************/
Err THIS_SetDepth(UInt16 refNum, Int32 depth) 
// DESC	Sets the screen mode to support the specified bitmap 
// DESC	bit depth.
// BEFORE
// BEFORE depth = 4
{
    Err    err;
    UInt32 requestedDepth;
    
    requestedDepth = (UInt32) depth;
    err = WinScreenMode(winScreenModeSet, 
                        NULL, NULL, &requestedDepth, NULL);
	return 0;
}

/********************************************************************
 *                   T H I S _ S e t C o l o r
 ********************************************************************/
Err THIS_SetColor(UInt16 refNum, Int32 boolean) 
// DESC	Sets the screen mode to support color bitmaps.
// PARAM1 1 = support color
// PARAM1 0 = do not support color
// BEFORE
// BEFORE boolean = 1
{
    Err     err;
    Boolean setColor;
    
    setColor = (Boolean) boolean;
    err = WinScreenMode(winScreenModeSet, 
                        NULL, NULL, NULL, &setColor);
    return 0;
}

/********************************************************************
 *               T H I S _ S a v e S c r e e n M o d e
 ********************************************************************/
Err THIS_SaveScreenMode(UInt16 refNum) 
// DESC	Saves the current screen mode parameters.  These parameters
// DESC	can later be restored by calling "RestoreScreenMode".  It is
// DESC	suggested that the current screen mode parameters be saved before
// DESC	any changes are requested and that these saved parameters
// DESC	are restored when the program exits.
{
    Err err;
    THIS_ATTACH_GLOBALS
        
    err = WinScreenMode(winScreenModeGet, 
                        NULL, NULL, &gP->depth, &gP->color);
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *           T H I S _ R e s t o r e S c r e e n M o d e
 ********************************************************************/
Err THIS_RestoreScreenMode(UInt16 refNum) 
// DESC	Restores saved screen mode parameters.  These parameters
// DESC	must have been saved by calling "SaveScreenMode".  It is
// DESC	suggested that the current screen mode parameters be saved before
// DESC	any changes are requested and that these saved parameters
// DESC	are restored when the program exits.
{
    Err err;
    THIS_ATTACH_GLOBALS
        
    err = WinScreenMode(winScreenModeSet, 
                        NULL, NULL, &gP->depth, &gP->color);
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *                 T H I S _ C u r r e n t D e p t h
 ********************************************************************/
Err THIS_CurrentDepth(UInt16 refNum, Int32 *depth) 
// DESC	Returns the current bitmap depth.
{
    Err err;
        
    err = WinScreenMode(winScreenModeGet, 
                        NULL, NULL, (UInt32 *) depth, NULL);
    return 0;
}

/********************************************************************
 *                 T H I S _ C u r r e n t C o l o r
 ********************************************************************/
Err THIS_CurrentColor(UInt16 refNum, Int32 *boolean) 
// DESC	Returns 1 if the PalmOS Device's screen mode is currently
// DESC	set to support color.   Otherwise, it returns 0.
{
    Err err;
    Boolean color;
        
    err = WinScreenMode(winScreenModeGet, 
                        NULL, NULL, NULL, &color);
    *boolean = (Int32) color;
    return 0;
}

/********************************************************************
 *                 T H I S _ S e t T o D e f a u l t s
 ********************************************************************/
Err THIS_SetToDefaults(UInt16 refNum) 
// DESC	Sets all screen mode parameters to their default values.
{
    Err err;
        
    err = WinScreenMode(winScreenModeSetToDefaults, 
                        NULL, NULL, NULL, NULL);
    return 0;
}

/********************************************************************
 *                 T H I S _ D e f a u l t D e p t h
 ********************************************************************/
Err THIS_DefaultDepth(UInt16 refNum, Int32 *depth) 
// DESC	Returns the default bitmap depth.
{
    Err err;
        
    err = WinScreenMode(winScreenModeGetDefaults, 
                        NULL, NULL, (UInt32 *) depth, NULL);
    return 0;
}

/********************************************************************
 *                 T H I S _ D e f a u l t C o l o r
 ********************************************************************/
Err THIS_DefaultColor(UInt16 refNum, Int32 *boolean) 
// DESC	Returns 1 if the PalmOS Device's screen mode default is
// DESC	set to support color.   Otherwise, it returns 0.
{
    Err err;
    Boolean color;
        
    err = WinScreenMode(winScreenModeGetDefaults, 
                        NULL, NULL, NULL, &color);
    *boolean = (Int32) color;
    return 0;
}

/********************************************************************
 *         T H I S _ G e t T a b l e E n t r y I n d e x
 ********************************************************************/
Err THIS_GetTableEntryIndex(UInt16 refNum, Int32 which, Int32 *index) 
// DESC	This function calls the PalmOS UIColorGetTableEntryIndex
// DESC	function.  It returns the index value for a UI color for the 
// DESC	current system palette.
// PARAM1 UIObjectFrame = 0,
// PARAM1 UIObjectFill = 1
// PARAM1 UIObjectForeground = 2
// PARAM1 UIObjectSelectedFill = 3
// PARAM1 UIObjectSelectedForeground = 4
// PARAM1
// PARAM1 UIMenuFrame = 5
// PARAM1 UIMenuFill = 6
// PARAM1 UIMenuForeground = 7
// PARAM1 UIMenuSelectedFill = 8
// PARAM1 UIMenuSelectedForeground = 9
// PARAM1
// PARAM1 UIFieldBackground = 10
// PARAM1 UIFieldText = 11
// PARAM1 UIFieldTextLines = 12
// PARAM1 UIFieldCaret = 13
// PARAM1 UIFieldTextHighlightBackground = 14
// PARAM1 UIFieldTextHighlightForeground = 15
// PARAM1 UIFieldFepRawText = 16
// PARAM1 UIFieldFepRawBackground = 17
// PARAM1 UIFieldFepConvertedText = 18
// PARAM1 UIFieldFepConvertedBackground = 19
// PARAM1 UIFieldFepUnderline = 20
// PARAM1
// PARAM1 UIFormFrame = 21
// PARAM1 UIFormFill = 22
// PARAM1
// PARAM1 UIDialogFrame = 23
// PARAM1 UIDialogFill = 24
// PARAM1
// PARAM1 UIAlertFrame = 25
// PARAM1 UIAlertFill = 26
// PARAM1
// PARAM1 UIOK = 27
// PARAM1 UICaution = 28
// PARAM1 UIWarning = 29
// RETURNS -1 = PalmOS version is less than 3.5
// BEFORE
// BEFORE which = 11   'UIFieldText
// NOTES This function requires PalmOS version 3.5 or greater.
{
        
    if (SysVersion(NULL, 3, 5)) 
        *index = (Int32) UIColorGetTableEntryIndex((UIColorTableEntries) which);
    else
        *index = -1;
        
    return 0;
}

/********************************************************************
 *            T H I S _ G e t T a b l e E n t r y R G B
 ********************************************************************/
Err THIS_GetTableEntryRGB(UInt16 refNum, Int32 which, Int32 *index) 
// DESC	This function calls the PalmOS UIColorGetTableEntryRGB function.
// DESC	It retrieves the RGB values for the UI Color.  RGB Values are
// DESC	returned in a structure called "RGBColorType".  It contains the 
// DESC	following fields:
// DESC		index, red, green, blue.
// DESC	This function retrieves all these values, but only returns
// DESC	the index.  To get the red, green, and blue values, call this
// DESC	function first and then call GetRGBRed, GetRGBGreen, and 
// DESC	GetRGBBlue.  See the example for more information.
// PARAM1 (see the GetTableEntryIndex function for
// PARAM1  a list of valid "Which" values")
// RETURNS -1 = PalmOS version is less than 3.5
// BEFORE Dim red as Integer
// BEFORE Dim green as Integer
// BEFORE Dim blue as Integer
// BEFORE
// BEFORE which = 11   'UIFieldText
// AFTER red = SL.GetRGBRed()
// AFTER green = SL.GetRGBGreen()
// AFTER blue = SL.GetRGBBlue()
// NOTES This function requires PalmOS version 3.5 or greater.
{
    THIS_ATTACH_GLOBALS

    if (SysVersion(gP, 3, 5)) {       
        UIColorGetTableEntryRGB((UIColorTableEntries) which, &gP->RGB);
        *index = (Int32) WinRGBToIndex(&gP->RGB);
        gP->RGB.index = (UInt8) *index;
    }
    else
        *index = -1;
        
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *                 T H I S _ G e t R G B I n d e x
 ********************************************************************/
Err THIS_GetRGBIndex(UInt16 refNum, Int32 *index) 
// DESC	RGB Values are returned in a structure called "RGBColorType".  
// DESC	It contains the following fields:
// DESC		index, red, green, blue.
// DESC
// DESC	This function returns the index value that was previously
// DESC	retrieved by either the GetTableEntryRGB or IndexToRGB functions.
{
    THIS_ATTACH_GLOBALS
        
    *index = (Int32) gP->RGB.index;
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *                     T H I S _ G e t R G B R e d
 ********************************************************************/
Err THIS_GetRGBRed(UInt16 refNum, Int32 *red) 
// DESC	RGB Values are returned in a structure called "RGBColorType".  
// DESC	It contains the following fields:
// DESC		index, red, green, blue.
// DESC
// DESC	This function returns the red value that was previously
// DESC	retrieved by either the GetTableEntryRGB or IndexToRGB functions.
// EXAMPLE See the example provided with either the GetTableEntryRGB or 
// EXAMPLE IndexToRGB functions.
{
    THIS_ATTACH_GLOBALS
        
    *red = (Int32) gP->RGB.r;
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *                   T H I S _ G e t R G B G r e e n
 ********************************************************************/
Err THIS_GetRGBGreen(UInt16 refNum, Int32 *green) 
// DESC	RGB Values are returned in a structure called "RGBColorType".  
// DESC	It contains the following fields:
// DESC		index, red, green, blue.
// DESC
// DESC	This function returns the green value that was previously
// DESC	retrieved by either the GetTableEntryRGB or IndexToRGB functions.
// EXAMPLE See the example provided with either the GetTableEntryRGB or 
// EXAMPLE IndexToRGB functions.
{
    THIS_ATTACH_GLOBALS
        
    *green = (Int32) gP->RGB.g;
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *                   T H I S _ G e t R G B B l u e
 ********************************************************************/
Err THIS_GetRGBBlue(UInt16 refNum, Int32 *blue) 
// DESC	RGB Values are returned in a structure called "RGBColorType".  
// DESC	It contains the following fields:
// DESC		index, red, green, blue.
// DESC
// DESC	This function returns the blue value that was previously
// DESC	retrieved by either the GetTableEntryRGB or IndexToRGB functions.
// EXAMPLE See the example provided with either the GetTableEntryRGB or 
// EXAMPLE IndexToRGB functions.
{
    THIS_ATTACH_GLOBALS
        
    *blue = (Int32) gP->RGB.b;
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *           T H I S _ S e t T a b l e E n t r y I n d e x
 ********************************************************************/
Err THIS_SetTableEntryIndex(UInt16 refNum, Int32 which, Int32 index) 
// DESC	This subroutine calls the PalmOS IndexToRGB function and then 
// DESC it calls UIColorSetTableEntry.	It changes a value in the UI 
// DESC Color list.
// NOTE	Some changes aren't reflected until the object or form is
// NOTE	redrawn with the "Redraw" statement.  Even then, some changes
// NOTE	like the form background (UIFormFill - 22) aren't reflected
// NOTE	until until you change forms with a "NextScreen" statement.
// NOTE	You might want to set some table entries in either the
// NOTE	programs "Startup" code or just before you use the "NextScreen"
// NOTE	statement.
// NOTE
// NOTE This function requires PalmOS version 3.5 or greater.
// PARAM1 (see the GetTableEntryIndex function for
// PARAM1  a list of valid "Which" values")
{ 
    Err err;
    RGBColorType RGB;

    if (SysVersion(NULL, 3, 5)) {
        WinIndexToRGB((IndexedColorType) index, &RGB);    
        err = UIColorSetTableEntry((UIColorTableEntries) which, &RGB);
    }

    return 0;
}

/********************************************************************
 *             T H I S _ S e t T a b l e E n t r y R G B
 ********************************************************************/
Err THIS_SetTableEntryRGB(UInt16 refNum, Int32 which, 
                       Int32 red, Int32 green, Int32 blue) 
// DESC	This subroutine calls the PalmOS UIColorSetTableEntry function.
// DESC	It changes a value in the UI Color list.
// NOTE	Some changes aren't reflected until the object or form is
// NOTE	redrawn with the "Redraw" statement.  Even then, some changes
// NOTE	like the form background (UIFormFill - 22) aren't reflected
// NOTE	until until you change forms with a "NextScreen" statement.
// NOTE	You might want to set some table entries in either the
// NOTE	programs "Startup" code or just before you use the "NextScreen"
// NOTE	statement.
// NOTE
// NOTE This function requires PalmOS version 3.5 or greater.
// PARAM1 (see the GetTableEntryIndex function for
// PARAM1  a list of valid "Which" values")
// PARAM4 Red, Green, Blue valid values are 0 to 255
{
    Err err;
    RGBColorType RGB;
        
    RGB.r = (UInt8) red;
    RGB.g = (UInt8) green;
    RGB.b = (UInt8) blue;

    if (SysVersion(NULL, 3, 5)) {    
        err = UIColorSetTableEntry((UIColorTableEntries) which, &RGB);
    }
    return 0;
}

/********************************************************************
 *           T H I S _ B r i g h t n e s s A d j u s t
 ********************************************************************/
Err THIS_BrightnessAdjust(UInt16 refNum) 
// DESC	This subroutine calls the PalmOS UIBrightnessAdjust function.  
// DESC	It displays the "Brightness Adjust" dialog.
// NOTES This function requires PalmOS version 3.5 or greater.
{ 
    if (SysVersion(NULL, 3, 5))
        UIBrightnessAdjust();
    return 0;
}

/********************************************************************
 *               T H I S _ C o n t r a s t A d j u s t
 ********************************************************************/
Err THIS_ContrastAdjust(UInt16 refNum) 
// DESC	This subroutine calls the PalmOS UIContrastAdjust function.  
// DESC	It displays the "Contrast Adjust" dialog.
// NOTE	The PalmOS documentation states that this function only works
// NOTE	on the "Palm V Connected Organizer".
// NOTE
// NOTE This function requires PalmOS version 3.5 or greater.
{
    if (SysVersion(NULL, 3, 5))
        UIContrastAdjust();
    return 0;
}

/********************************************************************
 *              T H I S _ P i c k C o l o r I n d e x
 ********************************************************************/
Err THIS_PickColorIndex(UInt16 refNum, Int32 index, Char *title, Int32 *changed) 
// DESC	This function calls the PalmOS UIPickColor function.  It
// DESC	displays a Palette dialog to allow a user to select a
// DESC	color.  The selected index and RGB values can be retrieved
// DESC	by calling the GetRGBIndex, GetRGBRed, GetRGBGreen and 
// DESC	GetRGBBlue functions.
// PARAM1 Suggested index
// PARAM2 Title to display on dialog
// RETURNS -1 = PalmOS version is less than v3.5
// RETURNS  0 = User cancelled or chose suggested index
// RETURNS  1 = User chose a new index
// NOTES This function requires PalmOS version of 3.5 or greater.
{
    IndexedColorType idx;
    THIS_ATTACH_GLOBALS

    if (SysVersion(gP, 3, 5)) {
        idx = (IndexedColorType) index;
        *changed = (Int32) UIPickColor(&idx, &gP->RGB, UIPickColorStartPalette, title, "");
        gP->RGB.index = idx;
    }
    else
        *changed = -1;
        
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *              T H I S _ P i c k C o l o r R G B
 ********************************************************************/
Err THIS_PickColorRGB(UInt16 refNum, Int32 red, Int32 green, Int32 blue, Char *title, Int32 *changed) 
// DESC	This function calls the PalmOS UIPickColor function.  It
// DESC	displays an RGB dialog to allow a user to select a
// DESC	color.  The selected index and RGB values can be retrieved
// DESC	by calling the GetRGBIndex, GetRGBRed, GetRGBGreen and 
// DESC	GetRGBBlue functions.
// PARAM3 Suggested Red, Green, Blue values (0 to 255)
// PARAM4 Title to display on dialog
// RETURNS -1 = PalmOS version is less than 3.5
// RETURNS  0 = User cancelled or chose suggested colors
// RETURNS  1 = User chose a new index
// NOTES This function requires PalmOS version 3.5 or greater.
{
    IndexedColorType idx;
    THIS_ATTACH_GLOBALS
        
    if (SysVersion(gP, 3, 5)) {
        gP->RGB.r = (UInt8) red;
        gP->RGB.g = (UInt8) green;
        gP->RGB.b = (UInt8) blue;
        *changed = (Int32) UIPickColor(&idx, &gP->RGB, UIPickColorStartRGB, title, "");
        gP->RGB.index = idx;
    }
    else
        *changed = -1;
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *                   T H I S _ I n d e x T o R G B
 ********************************************************************/
Err THIS_IndexToRGB(UInt16 refNum, Int32 index) 
// DESC	This subroutine calls the PalmOS WinIndexToRGB function.  It
// DESC	converts an index in the currently active color table to an
// DESC	RGB value.  RGB Values are returned in a structure called 
// DESC	"RGBColorType".  It contains the following fields:
// DESC		index, red, green, blue.
// DESC	To get the actual index, red, green, and blue values, call this
// DESC	function first and then call GetRGBIndex, GetRGBRed, GetRGBGreen,
// DESC	and GetRGBBlue.  See the example for more information.
// NOTES This function requires PalmOS version 3.5 or greater.
{
    THIS_ATTACH_GLOBALS

    if (SysVersion(gP, 3, 5))
        WinIndexToRGB((IndexedColorType) index, &gP->RGB);
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *               T H I S _ R G B T o I n d e x
 ********************************************************************/
Err THIS_RGBToIndex(UInt16 refNum, Int32 red, Int32 green, Int32 blue,
                    Int32 *index) 
// DESC	This function calls the PalmOS WinRGBToIndex function.  It 
// DESC	converts RGB values to the index of the closest color in the
// DESC	currently active color lookup table (CLUT).
// PARAM3 Red, Green, Blue valid values are 0 to 255
// RETURNS -1 = PalmOS version is less than 3.5
// NOTES This function requires PalmOS version 3.5 or greater.
{
    RGBColorType RGB;
        
    RGB.r = (UInt8) red;
    RGB.g = (UInt8) green;
    RGB.b = (UInt8) blue;
    
    if (SysVersion(NULL, 3, 5))
        *index = (Int32) WinRGBToIndex(&RGB);
    else
        *index = -1;
    return 0;
}

/********************************************************************
 *                   T H I S _ S e t F o r e C o l o r
 ********************************************************************/
Err THIS_SetForeColor(UInt16 refNum, Int32 newIndex, Int32 *oldIndex) 
// DESC	This function calls the PalmOS WinSetForeColor function.  It
// DESC	sets the foreground color to use in subsequent draw operations.
// NOTE	Colors set with this function appear to be reset to default
// NOTE	values when switching between forms or when a form is redrawn.
// NOTE	It is probably best to call this function in the form's
// NOTE	"After" code section.
// NOTE
// NOTE This function requires PalmOS version 3.5 or greater.
// RETURNS Previous foreground index
// RETURNS -1 = PalmOS version is less than 3.5
{
        
    if (SysVersion(NULL, 3, 5)) 
        *oldIndex = (Int32) WinSetForeColor((IndexedColorType) newIndex);
    else
        *oldIndex = -1;
        
    return 0;
}

/********************************************************************
 *                   T H I S _ S e t B a c k C o l o r
 ********************************************************************/
Err THIS_SetBackColor(UInt16 refNum, Int32 newIndex, Int32 *oldIndex) 
// DESC	This function calls the PalmOS WinSetBackColor function.  It
// DESC	sets the background color to use in subsequent draw operations.
// NOTE	Colors set with this function appear to be reset to default
// NOTE	values when switching between forms or when a form is redrawn.
// NOTE	It is probably best to call this function in the form's
// NOTE	"After" code section.
// NOTE
// NOTE This function requires PalmOS version 3.5 or greater.
// RETURNS Previous background index
// RETURNS -1 = PalmOS version is less than 3.5
{

    if (SysVersion(NULL, 3, 5))
        *oldIndex = (Int32) WinSetBackColor((IndexedColorType) newIndex);
    else
        *oldIndex = -1;
    return 0;
}

/********************************************************************
 *                   T H I S _ S e t T e x t C o l o r
 ********************************************************************/
Err THIS_SetTextColor(UInt16 refNum, Int32 newIndex, Int32 *oldIndex) 
// DESC	This function calls the PalmOS WinSetTextColor function.  It
// DESC	sets the color to use for drawing characters in subsequent draw 
// DESC	operations.
// NOTE	Colors set with this function appear to be reset to default
// NOTE	values when switching between forms or when a form is redrawn.
// NOTE	It is probably best to call this function in the form's
// NOTE	"After" code section.
// NOTE
// NOTE This function requires PalmOS version 3.5 or greater.
// RETURNS Previous text color index
// RETURNS -1 = PalmOS version is less than 3.5
{
        
    if (SysVersion(NULL, 3, 5))        
        *oldIndex = (Int32) WinSetTextColor((IndexedColorType) newIndex);
    else
        *oldIndex = -1;
        
    return 0;
}

/********************************************************************
 *                  T H I S _ D r a w L i n e
 ********************************************************************/
Err THIS_DrawLine(UInt16 refNum, Int32 x1, Int32 y1, Int32 x2, Int32 y2) 
// DESC	This soubroutine calls the PalmOS WinDrawLine function.  It 
// DESC	draws a line in the draw window using the current foreground 
// DESC	color.
// NOTE	This function was provided for completeness only.  The
// NOTE	built-in DrawLine NSBasic statement produces the same result.
{
        
    WinDrawLine((Coord) x1, (Coord) y1, (Coord) x2, (Coord) y2);
    return 0;
}

/********************************************************************
 *                  T H I S _ D r a w G r a y L i n e
 ********************************************************************/
Err THIS_DrawGrayLine(UInt16 refNum, Int32 x1, Int32 y1, Int32 x2, Int32 y2) 
// DESC	This subroutine calls the PalmOS WinDrawGrayLine function.  It
// DESC	does not draw in a gray color, but rather draws with
// DESC	alternating foreground and background colors.
{
        
    WinDrawGrayLine((Coord) x1, (Coord) y1, (Coord) x2, (Coord) y2);
    return 0;
}

/********************************************************************
 *                  T H I S _ E r a s e L i n e
 ********************************************************************/
Err THIS_EraseLine(UInt16 refNum, Int32 x1, Int32 y1, Int32 x2, Int32 y2) 
// DESC	This subroutine calls the PalmOS WinEraseLine function.  It
// DESC	draws a line in the draw window using the current background
// DESC	color.
{
        
    WinEraseLine((Coord) x1, (Coord) y1, (Coord) x2, (Coord) y2);
    return 0;
}

/********************************************************************
 *                  T H I S _ I n v e r t L i n e
 ********************************************************************/
Err THIS_InvertLine(UInt16 refNum, Int32 x1, Int32 y1, Int32 x2, Int32 y2) 
// DESC	This subroutine calls the PalmOS WinInvertLine function.  It
// DESC	draws an inverted line in the draw window.
{
        
    WinInvertLine((Coord) x1, (Coord) y1, (Coord) x2, (Coord) y2);
    return 0;
}

/********************************************************************
 *                  T H I S _ D r a w P i x e l
 ********************************************************************/
Err THIS_DrawPixel(UInt16 refNum, Int32 x, Int32 y) 
// DESC	This subroutine calls the PalmOS WinDrawPixel function.  It
// DESC	draws a pixel in the draw window using the current foreground
// DESC	color.
{
        
    WinDrawPixel((Coord) x, (Coord) y);
    return 0;
}

/********************************************************************
 *                  T H I S _ E r a s e P i x e l
 ********************************************************************/
Err THIS_ErasePixel(UInt16 refNum, Int32 x, Int32 y) 
// DESC	This subroutine calls the PalmOS WinErasePixel function.  It
// DESC	draws a pixel in the draw window using the current background
// DESC	color.
{
        
    WinErasePixel((Coord) x, (Coord) y);
    return 0;
}

/********************************************************************
 *                  T H I S _ I n v e r t P i x e l
 ********************************************************************/
Err THIS_InvertPixel(UInt16 refNum, Int32 x, Int32 y) 
// DESC	This subroutine calls the PalmOS WinInvertPixel function.  It
// DESC	draws an inverted pixel in the draw window.
{
        
    WinInvertPixel((Coord) x, (Coord) y);
    return 0;
}

/********************************************************************
 *                  T H I S _ G e t P i x e l
 ********************************************************************/
Err THIS_GetPixel(UInt16 refNum, Int32 x, Int32 y, Int32 *index) 
// DESC	This function calls the PalmOS WinGetPixel function.  It
// DESC	returns the color of the specified a pixel in the draw window.
{
        
    *index = (Int32) WinGetPixel((Coord) x, (Coord) y);
    return 0;
}

/********************************************************************
 *                  T H I S _ S c r e e n L o c k
 ********************************************************************/
Err THIS_ScreenLock(UInt16 refNum, Int32 mode, Int32 *success) 
// DESC	This function calls the PalmOS WinScreenLock function.  It 
// DESC	"locks" the current screen by switching the UI concept of the 
// DESC	screen base address to an area that is not reflected on the
// DESC	display.  This routine can be used to "freeze" the display 
// DESC	while doing lengthy drawing operations to avoid a flickering
// DESC	effect.  Call ScreenUnlock to unlock the display and cause
// DESC	it to be updated with any changes.  The screen must be unlocked
// DESC	as many times as it is locked to actually update the display.
// PARAM1 winLockCopy = 0 - copy old screen to new
// PARAM1 winLockErase = 1 - erase new screen to white
// PARAM1 winLockDontCare = 2 - don't do anything
// RETURNS -1 = PalmOS version is less than 3.5
// RETURNS  1 = success
// RETURNS  0 = failure
// NOTES This function requires PalmOS version 3.5 or greater.
{
    UInt8 *baseAddress;
    
    if (SysVersion(NULL, 3, 5)) {
        baseAddress = WinScreenLock((WinLockInitType) mode);
        if (baseAddress == NULL)
            *success = 0;
        else
            *success = 1;
    }
    else
        *success = -1;
        
    return 0;
}

/********************************************************************
 *                  T H I S _ S c r e e n U n l o c k
 ********************************************************************/
Err THIS_ScreenUnlock(UInt16 refNum) 
// DESC	This subroutine calls the PalmOS WinScreenUnlock function.  Call 
// DESC	ScreenUnlock to unlock the display and cause it to be updated 
// DESC	with any changes.  The screen, which was locked by calling
// DESC	ScreenLock, must be unlocked as many times as it is locked to 
// DESC	actually update the display.
// NOTES This function requires PalmOS version 3.5 or greater.
{
    
    if (SysVersion(NULL, 3, 5))
        WinScreenUnlock();
    
    return 0;
}

/********************************************************************
 *                T H I S _ W i n S a v e B i t s
 ********************************************************************/
Err THIS_WinSaveBits(UInt16 refNum, Int32 index, Int32 x, Int32 y,
                                    Int32 width, Int32 height) 
{
    RectangleType rect;
    UInt16 err;
    THIS_ATTACH_GLOBALS
    
    if (index < 0  || index >= SAVEBITSMAX) {
        THIS_DETACH_GLOBALS
        return 0;
    }
    
    if (gP->saveBits[index])
        WinDeleteWindow(gP->saveBits[index], false);

    rect.topLeft.x = (Coord) x;
    rect.topLeft.y = (Coord) y;
    rect.extent.x = (Coord) width;
    rect.extent.y = (Coord) height;
    gP->saveBits[index] = WinSaveBits(&rect, &err);
    
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *            T H I S _ W i n R e s t o r e B i t s
 ********************************************************************/
Err THIS_WinRestoreBits(UInt16 refNum, Int32 index, Int32 x, Int32 y)
{
    THIS_ATTACH_GLOBALS
    
    if (index < 0  || index >= SAVEBITSMAX) {
        THIS_DETACH_GLOBALS
        return 0;
    }
    
    if (gP->saveBits[index])
        WinRestoreBits(gP->saveBits[index], (Coord) x, (Coord) y);

    gP->saveBits[index] = NULL;
    
    THIS_DETACH_GLOBALS
    return 0;
}

// SECTION Sleep and Wake Event Functions
// DESC The following functions provide the ability to determine when and if
// DESC your system has gone to sleep or has been awakened - either through
// DESC the use of the power button or because of the system's "Auto Off" 
// DESC feature.  The primary uses of this fuction would include determining
// DESC if you should end your program or prompt for a password during an 
// DESC extended period of inactivity.

/********************************************************************
 *            T H I S _ S e t S l e e p E v e n t
 ********************************************************************/
Err THIS_SetSleepEvent(UInt16 refNum, Int32 eventNbr)
// DESC Sets an event number to post when the device is powered off, either
// DESC through an AutoOff or by the user pressing the power button.
// DESC In General, the event number should be a custom event in the range of
// DESC 24576 to 32767; however, any non-zero event number can be used.  A 
// DESC particularly useful event number is the appStopEvent (event number 22).
// DESC This will cause the program to terminate and the "Termination Code"
// DESC section will be called.  Using an event number of 22 (appStopEvent)
// DESC may be necessary when a program must absolutely terminate.  This is
// DESC because displayed things like MsgBoxes and Alerts have their own
// DESC event loops and may ignore custom events.
// PARAM1 Use 0 to cause no event to be posted.
// BEFORE eventNbr = 30000
// NOTES See the GetSleepEvent(), SetWakeEvent(), and GetWakeEvent() functions.
{
    PrefSetAppPreferences(THIS_LibCreatorID, libSleepEventID, 0, 
                          &eventNbr, sizeof(eventNbr), 0);
    return 0;
}

/********************************************************************
 *                T H I S _ S e t W a k e E v e n t
 ********************************************************************/
Err THIS_SetWakeEvent(UInt16 refNum, Int32 eventNbr)
// DESC Sets an event number to post when the device is powered on while
// DESC this library is loaded (ie. your NSBasic program is running and 
// DESC is using this library).  In General, the event number should be a 
// DESC custom event in the range of 24576 to 32767; however, any non-zero 
// DESC event number can be used.  A particularly useful event number is the 
// DESC appStopEvent (event number 22).  This will cause the program to 
// DESC terminate and the "Termination Code" section will be called.  Using an 
// DESC event number of 22 (appStopEvent) may be necessary when a program must 
// DESC absolutely terminate.  This is because displayed things like MsgBoxes 
// DESC and Alerts have their own event loops and may ignore custom events.
// PARAM1 Use 0 to cause no event to be posted.
// BEFORE eventNbr = 30001
// NOTES Also see the GetWakeEvent(), SetSleepEvent(), and GetSleepEvent() functions.
{
    PrefSetAppPreferences(THIS_LibCreatorID, libWakeEventID, 0, 
                          &eventNbr, sizeof(eventNbr), 0);
    return 0;
}

/********************************************************************
 *            T H I S _ G e t S l e e p E v e n t
 ********************************************************************/
Err THIS_GetSleepEvent(UInt16 refNum, Int32 *eventNbr)
// DESC Returns the event number that gets posted when the device is powered
// DESC off either through an AutoOff or by the user pressing the power button.
// DESC Note that a value of 0 means that no event is posted.
// NOTES Also see the SetSleepEvent(), SetWakeEvent(), GetWakeEvent(),
// NOTES GetSleepEventTime(), and GetWakeEventTime() functions.
{
	UInt16 returnSize;
	
    returnSize = sizeof(Int32);
    if (PrefGetAppPreferences(THIS_LibCreatorID, libSleepEventID, 
                              eventNbr, &returnSize, false) != 0)
        *eventNbr = 0;
    return 0;
}

/********************************************************************
 *                T H I S _ G e t W a k e E v e n t
 ********************************************************************/
Err THIS_GetWakeEvent(UInt16 refNum, Int32 *eventNbr)
// DESC Returns the event number that gets posted when the device is powered
// DESC on while this library is loaded (ie. your NSBasic program is running and 
// DESC is using this library).
// DESC Note that a value of 0 means that no event is posted.
// NOTES Also see the GetWakeEvent(), SetSleepEvent(), GetSleepEvent(),
// NOTES GetSleepEventTime(), and GetWakeEventTime() functions.
{
	UInt16 returnSize;
	
    returnSize = sizeof(Int32);
    if (PrefGetAppPreferences(THIS_LibCreatorID, libWakeEventID, 
                              eventNbr, &returnSize, false) != 0)
        *eventNbr = 0;
    return 0;
}

/********************************************************************
 *           T H I S _ G e t S l e e p E v e n t T i m e
 ********************************************************************/
Err THIS_GetSleepEventTime(UInt16 refNum, Int32 *eventTime)
// DESC Returns the event time that gets saved when the device is powered
// DESC off either through an AutoOff or by the user pressing the power button.
// DESC Note that this time only gets saved if an event number has been registered using
// DESC the SetSleepEvent() function. A value of 0 means that no event has been posted.
// RETURNS eventTime in system time format.  This value is expressed
// RETURNS as the number of seconds since January 1st, 1904.
// NOTES Also see the SetSleepEvent(), SetWakeEvent(), GetWakeEvent(), GetWakeEventTime(),
// NOTES StringDateTime(), StringDate(), and StringTime() functions.

{
	UInt16 returnSize;
	
    returnSize = sizeof(Int32);
    if (PrefGetAppPreferences(THIS_LibCreatorID, libSleepTimeID, 
                              eventTime, &returnSize, false) != 0)
        *eventTime = 0;
    return 0;
}

/********************************************************************
 *             T H I S _ G e t W a k e E v e n t T i m e
 ********************************************************************/
Err THIS_GetWakeEventTime(UInt16 refNum, Int32 *eventTime)
// DESC Returns the event time that gets saved when the device is powered on.
// DESC Note that this time only gets saved if an event number has been registered using
// DESC the SetWakeEvent() function. A value of 0 means that no event has been posted.
// RETURNS eventTime in system time format.  This value is expressed
// RETURNS as the number of seconds since January 1st, 1904.
// NOTES Also see the SetSleepEvent(), SetWakeEvent(), GetWakeEvent(), GetSleepEventTime(),
// NOTES StringDateTime(), StringDate(), and StringTime() functions.
{
	UInt16 returnSize;
	
    returnSize = sizeof(Int32);
    if (PrefGetAppPreferences(THIS_LibCreatorID, libWakeTimeID, 
                              eventTime, &returnSize, false) != 0)
        *eventTime = 0;
    return 0;
}

// SECTION String Encryption and Decryption Functions
// DESC The following functions provide encryption and decryption capabilities
// DESC for string values.  These functions use the PalmOS EncDES() function which
// DESC may or may not be available on all PalmOS devices.  Furthermore, the
// DESC length of these strings, currently, can not be longer than 248 characters.
// DESC Consideration of these restrictions should be carefully evaluated before
// DESC using these functions.
// DESC
// DESC There is a Windows component of the EncryptDESString() and DecryptDESString()
// DESC functions. This component is implemented as a Windows DLL file and can be 
// DESC called from Visual Basic/VBA and Visual C/C++. Its purpose is to allow a 
// DESC conduit or other Palm Database utility to be able to encrypt or decrypt 
// DESC data using the same algorythms as the NSBSystemLib routines.
// DESC 
// DESC To use it, the EncDec.dll file must be placed in a system directory or 
// DESC some directory that is currently in your PATH. For Visual Basic/VBA, 
// DESC include the EncDec.bas module. For Visual C/C++, include the EncDec.h 
// DESC header file and link with the EncDec.lib library (note that the EncDec.dll
// DESC is still required). 
// DESC
// DESC The EncDec DLL functions have the same restrictions as their NSBSystemLib
// DESC library counterparts. The main differences are that you specify the 
// DESC encryption key with every function call and that the functions return the
// DESC length of the returned string. 
// DESC
// DESC VB/VBA Example:
// DESC \
// DESC Dim KeyStr As String
// DESC Dim DecryptedStr As String
// DESC Dim EncryptedStr As String
// DESC Dim StrLen As Integer
// DESC 
// DESC KeyStr = "secret"
// DESC DecryptedStr = "The quick brown fox jumps over the lazy dog!"
// DESC StrLen = EncryptData(KeyStr, DecryptedStr, EncryptedStr)
// DESC DecryptedStr = ""
// DESC StrLen = DecryptData(KeyStr, EncryptedStr, DecryptedStr)
// DESC /
// DESC C++ Example:
// DESC \
// DESC char keyStr[25];
// DESC char decryptedStr[251];
// DESC char encryptedStr[251];
// DESC int  len;
// DESC
// DESC strcpy(keyStr, "secret");
// DESC strcpy(decryptedStr, "The quick brown fox jumps over the lazy dog!");
// DESC len = encryptData(keyStr, decryptedStr, encryptedStr);
// DESC strcpy(decryptedStr, "");
// DESC len = decryptData(keyStr, encryptedStr, decryptedStr);
// DESC /

/********************************************************************
 *             T H I S _ E n c r y p t D E S S t r i n g
 ********************************************************************/
Err THIS_EncryptDESString(UInt16 refNum, char* decryptedStr, char *encryptedStr) 
// DESC Returns the encrypted value of the plainText string. The plainText string
// DESC can not be more than 248 characters in length. The length of the encrypted
// DESC string may be up to 9 characters longer than the plainText string. Note: 
// DESC the SetDESKey subroutine must have been called at least once prior to 
// DESC calling this function. 
{
    UInt16 n;
    UInt16 len = 0;
    char  padAmt = 0;
	THIS_ATTACH_GLOBALS

    StrNCopy((char *) gP->src, decryptedStr, 255);
    gP->src[255] = 0;
    if ((len = StrLen((char *) gP->src)) == 0) {
        StrCopy(encryptedStr, "");
        THIS_DETACH_GLOBALS
        return 0;
    }
    padAmt = len % 8;
    if (padAmt > 0) {
        padAmt = 8 - padAmt;
        n = len + padAmt;
        for (; len < n; len++)
            gP->src[len] = ' ';
    }
    if (gP->key[1] != NULL) {
        len = EncryptData(gP->key[0], gP->src, gP->dst, len, 0);
        len = DecryptData(gP->key[1], gP->dst, gP->src, len, 0);
        len = EncryptData(gP->key[2], gP->src, gP->dst, len, 1);
    }
    else
        len = EncryptData(gP->key[0], gP->src, gP->dst, len, 1);
    gP->dst[len++] = padAmt + 1;
    gP->dst[len] = 0;
    
    StrCopy(encryptedStr, (char *) gP->dst);
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *             T H I S _ D E c r y p t D E S S t r i n g
 ********************************************************************/
Err THIS_DecryptDESString(UInt16 refNum, char* encryptedStr, char *decryptedStr)
// DESC Returns the plain text value of the encryptedText string. The encryptedText
// DESC string can not be more than 250 characters in length. Note: the SetDESKey
// DESC subroutine must have been called at least once prior to calling this function. 
{
    UInt16 len = 0;
    char   padAmt = 0;
	THIS_ATTACH_GLOBALS
	
    StrNCopy((char *) gP->src, encryptedStr, 255);
    gP->src[255] = 0;
    if ((len = StrLen((char *) gP->src)) == 0) {
        StrCopy(decryptedStr, "");
        THIS_DETACH_GLOBALS
        return 0;
    }

    padAmt = len % 8;
    if (padAmt == 1)
        padAmt = 0;
    else
        padAmt = gP->src[--len] - 1;
    gP->src[len] = 0;
    if (gP->key[1] != NULL) {
        len = DecryptData(gP->key[2], gP->src, gP->dst, len, 1);
        len = EncryptData(gP->key[1], gP->dst, gP->src, len, 0);
        len = DecryptData(gP->key[0], gP->src, gP->dst, len, 0);
    }
    else
        len = DecryptData(gP->key[0], gP->src, gP->dst, len, 1);
    len -= padAmt;
    gP->dst[len] = 0;
    
    StrCopy(decryptedStr, (char *) gP->dst);
    
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *                    T H I S _ S e t D E S K e y
 ********************************************************************/
Err THIS_SetDESKey(UInt16 refNum, char* keyStr) 
// DESC Establishes the encryption or decryption key to be used with the 
// DESC EncryptDESString() and DecryptDESString() functions. This key value 
// DESC must be set before using these functions. Once set, it will be used for 
// DESC all subsequent operations or until the program ends. If the length of 
// DESC the key is 8 characters or less, standard DES encryption will be used. 
// DESC If the key length is from 9 to 24 characters, Triple-DES encryption is used. 
{
    UInt16 i;
    UInt16 n;
	THIS_ATTACH_GLOBALS

    StrNCopy((char *) gP->keys, keyStr, 24);
    gP->keys[24] = 0;
    for (n = 1; n < 3; n++)
        gP->key[n] = NULL;
    gP->key[0] = gP->keys;
    if (StrLen((char *) gP->keys) > 8) {
        gP->key[1] = gP->keys + 8;
        if (StrLen((char *) gP->keys) > 16)
            gP->key[2] = gP->keys + 16;
    }
    if (gP->key[2] == NULL && gP->key[1] != NULL)
        gP->key[2] = gP->key[0];
 	for (n = 0; n < 3; n++)
        if (gP->key[n] != NULL)
            for (i = StrLen((char *) gP->key[n]); i < 8; i++)
                gP->key[n][i] = (unsigned char) i; 

    THIS_DETACH_GLOBALS;
    return 0;
}

/*###################################################################
 #       S t a n d a r d ,  R E Q U I R E D    F u n c t i o n s
 #*/

Err THIS_LibOpen(UInt16 refNum) {
    Err err = 0;
    Int32 eventNbr;
    THIS_ALLOCATE_GLOBALS	// Define local variables before this
    
    eventNbr = 0;
    PrefSetAppPreferences(THIS_LibCreatorID, libSleepEventID, 0, 
                          &eventNbr, sizeof(eventNbr), 0);
    PrefSetAppPreferences(THIS_LibCreatorID, libWakeEventID, 0, 
                          &eventNbr, sizeof(eventNbr), 0);	
    PrefSetAppPreferences(THIS_LibCreatorID, libSleepTimeID, 0, 
                          &eventNbr, sizeof(eventNbr), 0);
    PrefSetAppPreferences(THIS_LibCreatorID, libWakeTimeID, 0, 
                          &eventNbr, sizeof(eventNbr), 0);	
    return err;
}

Err THIS_LibClose(UInt16 refNum) {
    Err err = 0;
    THIS_FREE_GLOBALS	// Define local variables before this

    return err;
}

Err THIS_LibSleep(UInt16 refNum) {
    EventType event;
    Int32     eventNbr;
    UInt16    returnSize;
    UInt32     currTime;
    
    returnSize = sizeof(Int32);
    if (PrefGetAppPreferences(THIS_LibCreatorID, libSleepEventID, 
                              &eventNbr, &returnSize, false) != 0)
        eventNbr = 0;
    if (eventNbr) {
        event.eType = eventNbr;
        currTime = TimGetSeconds();
        PrefSetAppPreferences(THIS_LibCreatorID, libSleepTimeID, 0, 
                              &currTime, sizeof(currTime), 0);
        EvtAddEventToQueue(&event);
    }
    
    return 0;
}

Err THIS_LibWake(UInt16 refNum) {
    EventType event;
    Int32     eventNbr;
    UInt16    returnSize;
    UInt32    currTime;
    
    returnSize = sizeof(Int32);
    if (PrefGetAppPreferences(THIS_LibCreatorID, libWakeEventID, 
                              &eventNbr, &returnSize, false) != 0)
        eventNbr = 0;
    if (eventNbr) {
        event.eType = eventNbr;
        currTime = TimGetSeconds();
        PrefSetAppPreferences(THIS_LibCreatorID, libWakeTimeID, 0, 
                              &currTime, sizeof(currTime), 0);
        EvtAddEventToQueue(&event);
    }
    
    return 0;
}

/*###################################################################*/
