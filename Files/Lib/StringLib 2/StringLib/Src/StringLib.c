#include <PalmOS.h>			// Includes all Palm OS headers

// Our library public definitions (library API)
#define BUILDING_STRING_LIB
#include "StringLib.h"

// Our library private definitions (library globals, etc.)
#include "StringLibPrv.h"

#include "CW.c"
/********************************************************************
 * Internally used routines
 ********************************************************************/
static StringLibGlobalsPtr PrvMakeGlobals(UInt16 refNum);
static void PrvFreeGlobals(UInt16 refNum);
static StringLibGlobalsPtr PrvLockGlobals(UInt16 refNum);
static Boolean PrvIsLibOpen(UInt16 refNum);

/********************************************************************
 * Internally used macros
 ********************************************************************/
// Unlock globals
#define PrvUnlockGlobals(gP)	MemPtrUnlock(gP)
#define prvStringLibVersion		1	


/********************************************************************
 * String Library API Routines
 ********************************************************************/
 Err StringLibOpen(UInt16 refNum)
{
	StringLibGlobalsPtr		gP;
	Err						err = 0;
	Int16					originalOpenCount = 0;
	
	// Get library globals
	gP = PrvLockGlobals(refNum);										// lock our library globals
	// Check if already open
	if (!gP)
		{
		// Allocate and initialize our library globals.
		gP = PrvMakeGlobals(refNum);									// returns locked globals on success
		if ( !gP ) err = stringErrMemory;
		}
	// If we have globals, create a client context, increment open count, and unlock our globals
	if ( gP )
		{
		originalOpenCount = gP->openCount;							// save original open count for error handling
		if ( !err )	gP->openCount++;									// increment open count on success
		PrvUnlockGlobals(gP);										// unlock our library globals
		
		// If there was an error creating a client context and there are no other clients,
		// free our globals
		if ( err && (originalOpenCount == 0) )
			PrvFreeGlobals(refNum);
		}
	return( err );
}

Err StringLibClose(UInt16 refNum)
{
	StringLibGlobalsPtr		gP;
	Int16				openCount;
	Err					err = 0;

	gP = PrvLockGlobals(refNum);	// lock our globals
	// If not open, return
	if (!gP) { return 0;}						// MUST return zero here to get around a bug in system v1.x that
											// would cause SysLibRemove to fail.

	// Decrement our library open count
	gP->openCount--;
	// Error check for open count underflow
	ErrFatalDisplayIf(gP->openCount < 0, "String lib open count underflow");
	// Save the new open count and the context count
	openCount = gP->openCount;
	PrvUnlockGlobals(gP);			// unlock our globals
	// If open count reached zero, free our library globals
	if ( openCount <= 0 )
		{
		// Free our library globals
		PrvFreeGlobals(refNum);
		}
	else
		err = stringErrStillOpen;	// return this error code to inform the caller
											// that others are still using this library
	return err;
}

Err StringLibSleep(UInt16 refNum)
{
	return( 0 );
}
Err StringLibWake(UInt16 refNum)
{
	return( 0 );
}

#define MAX_LEN_STR	255
Err StringLibGetLibAPIVersion(UInt16 refNum, UInt32 * dwVerP)
{
	
	// Error-check our parameters
	ErrFatalDisplayIf(dwVerP == NULL, "null pointer argument");
	*dwVerP = prvStringLibVersion;
	return( 0 );
}

//Err StringLibJoin(UInt16 refNum,char ** in, char* delim, char* out){	return( 0 ); }

#define stringErrExpression	-1
#define stringErrToken		-2
Err StringLibReplace(UInt16 refNum, char* in, char* token, char*  replacewith, UInt16 num, char* result)
{
 char *pos, *prevPos=in;
 if (!StrLen(in)) {*result=0; return stringErrExpression;}
 if (!StrLen(token)) { StrCopy(result,in); return stringErrToken;}
// if (StrLen(in) < start) return (0);
 if (!num) {StrCopy(result,in); return (0);}

 *result=0;
 do
 {
  pos = StrStr(prevPos,token);
  if (pos == NULL) break;//{StrCat(result,prevPos); return (0);}
  StrNCat(result, prevPos, StrLen(result) + 1 + pos - prevPos);
  StrCat(result,  replacewith);
  prevPos=pos+StrLen(token);
 } while( --num);
 
 StrCat(result,prevPos);
 return( 0 );
}

Err StringLibStrReverse(UInt16 refNum, char *expr, char *result)
{
 UInt16 i, len;
 if ( expr == NULL) {result = NULL; return (0);}
 len = StrLen(expr);
 result[len]=0;
 for( i=0; i<len;i++){result[i] = expr[len- i -1];}
 return (0);
}

Err StringLibSpace(UInt16 refNum, UInt16 num, char *result)
{
 if ( num > MAX_LEN_STR ) {*result=0; return (0);}
 result[num]=0;  while (num--) result[num]=' ';
 return (0);
}

Err StringLibString(UInt16 refNum, UInt16 number, char* ch, char *result)
{
 *result=0; 
 if (ch == NULL)  return (0);
 if (number*StrLen(ch) > MAX_LEN_STR) return (0);
 while (number--) StrCat(result,ch);
 return (0); 
}

Err StringLibMonthName(UInt16 refNum, UInt16 month, UInt16 abbreviate, char *result)
{
 char mn[12][10]= {
 {'J','a','n','u','a','r','y',  0,  0,  0},
 {'F','e','b','r','u','a','r','y',  0,   0},
 {'M','a','r','c','h',  0,  0,  0, 0, 0},
 {'A','p','r','i','l',  0,  0,  0,  0,  0},
 {'M','a','y',  0,  0,  0, 0, 0, 0, 0},
 {'J','u','n','e',  0,  0,  0, 0, 0, 0},
 {'J','u','l','y',  0,  0,  0,  0, 0, 0},
 {'A','u','g','u','s','t',  0,  0, 0, 0},
 {'S','e','p','t','e','m','b','e','r', 0},
 {'O','c','t','o','b','e','r',  0,  0, 0},
 {'N','o','v','e','m','b','e','r',  0, 0},
 {'D','e','c','e','m','b','e','r',  0, 0},
 };
 *result=0;
 if (!month) return (0);
 if (abbreviate) StrNCat(result,mn[(month-1)%12],4);
                else StrCat(result,mn[(month-1)%12]);
return (0);
}

Err StringLibWeekdayName(UInt16 refNum, UInt16 weekday, UInt16 abbreviate, UInt16 firstdayofweek, char*result)
{
 char dn[7][10]={
 {'S','u','n','d','a','y',  0,  0,  0,0},
 {'M','o','n','d','a','y',  0,  0,  0,0},
 {'T','u','e','s','d','a','y',  0,  0, 0},
 {'W','e','d','n','e','s','d','a','y', 0},
 {'T','h','u','r','s','d','a','y',  0,  0},
 {'F','r','i','d','a','y',  0,  0,  0,  0},
 {'S','a','t','u','r','d','a','y',  0,  0}
 };
 *result=0;
 if (!firstdayofweek) firstdayofweek = (UInt16) PrefGetPreference(prefWeekStartDay)+1;
 if (firstdayofweek>7 || weekday>7 || !weekday) return(0);
 if (abbreviate) StrNCat(result,dn[(weekday+firstdayofweek-2)%7],4);
  		else  StrCat(result,dn[(weekday+firstdayofweek-2)%7]);
 return (0);
}

Err StringLibInstrRev(UInt16 refNum, char *expr, char* find, UInt16 start, UInt16 *result)
{
UInt16 exprLen,findLen,i;
if ((expr == NULL) || (find == NULL) ) {result = NULL; return (0);}
exprLen = StrLen(expr);
findLen = StrLen(find);
if (!findLen) {*result=start; return (0);}
if (!exprLen || (start<findLen)) {*result = 0; return (0);}

if (start>exprLen-findLen+1) start=exprLen-findLen+1; else start=start-findLen;
for (i = start; i>=0; i--) if (!StrNCompare ( expr+i, find, findLen)) { *result = i+1; return (0); }
*result = 0;
return (0);
}
Err StringLibLSet(UInt16 refNum, char* expr, char* replace)
{
 UInt16  i;
 if (expr == NULL || replace == NULL) return (0);
 if (!StrLen(expr)) return (0);
 for ( i=0; i<StrLen(expr); i++) if (i<StrLen(replace)) expr[i]=replace[i]; else expr[i]=0x20;
 return (0); 
}

Err StringLibRSet(UInt16 refNum, char* expr, char* replace)
{
 Int16 exprLen, replaceLen;
 if (expr == NULL || replace == NULL) return (0);
 if (!StrLen(expr)) return (0);
 exprLen= StrLen(expr)-1;
 replaceLen = StrLen(replace)-1;
 for (;exprLen>=0; exprLen--,replaceLen--) if (replaceLen>=0) expr[exprLen]=replace[replaceLen]; else expr[exprLen] = 0x20;
 return (0); 
}



#define REG_FORMAT 64
#define REG_LONG_FORMAT 65
Err StringLibFormatTime(UInt16 refNum,double _time , UInt16 namedFormat, char* result)
{

 FlpCompDouble _t;
 UInt32 mT;
 Int16 expT,signT;
 UInt8 hours, minutes; 
 _t.d=_time;
 FlpBase10Info(_t.fd, &mT, &expT, &signT);
 mT/=100;
 mT/=100;//seconds
 minutes = mT%100;
 mT/=100;//minuts
 hours = mT%100;
 if (namedFormat == REG_FORMAT)  namedFormat = PrefGetPreference(prefTimeFormat);
 TimeToAscii(hours, minutes, (TimeFormatType)namedFormat, result);
 return (0);
}

Err StringLibFormatDate(UInt16 refNum, double _date, UInt16 namedFormat, char* result)
{
 FlpCompDouble _d;
 UInt32 mD;
 Int16 expD,signD,years;
 UInt8 months, days;
 _d.d=_date;
 FlpBase10Info(_d.fd, &mD, &expD, &signD);
 mD/=10;
 days = mD%100;
 mD/=100;//days
 months = mD%100;
 mD/=100;//months
 years = mD+1900;
 
 if (namedFormat == REG_FORMAT)  namedFormat = PrefGetPreference(prefDateFormat);
 else if (namedFormat == REG_LONG_FORMAT)  namedFormat = PrefGetPreference(prefLongDateFormat);
 DateToAscii(months, days, years, (DateFormatType) namedFormat, result);
 return (0);
}

#define FP_ALL_DEFAULT								0
#define FP_INCLUDE_LEADING_DIGIT_FALSE					1
#define FP_INCLUDE_LEADING_DIGIT_TRUE					2
#define FP_USE_PARENTS_FOR_NEGATIVE_NUMBER_FALSE	4
#define FP_USE_PARENTS_FOR_NEGATIVE_NUMBER_TRUE		8
#define FP_GROUP_DIGIT_FALSE							16
#define FP_GROUP_DIGIT_TRUE							32

#define COUNT_DIG	8

static void FormatNumber(UInt16 refNum,double expr, UInt16 numDig, UInt16 format, char* result, Int16 addExp)
{
 FlpCompDouble _d;
 UInt32 m;
 Int16 exp,sign,i,j,rNumDig,zeroNum;
 UInt8	fp_ILD,fp_UPFNN,fp_GD;
 char gs, fs;
 char mStr[64],pfs[]={'%','l','u',0};
 Int32 okr[]={5,50,500,5000,50000, 500000, 5000000, 50000000};
 NumberFormatType pNF;
 
 if (format&FP_INCLUDE_LEADING_DIGIT_FALSE) fp_ILD =0; else if (format&FP_INCLUDE_LEADING_DIGIT_TRUE) fp_ILD =1; else fp_ILD =1;
 if (format&FP_USE_PARENTS_FOR_NEGATIVE_NUMBER_FALSE) fp_UPFNN =0; else if (format&FP_USE_PARENTS_FOR_NEGATIVE_NUMBER_TRUE) fp_UPFNN =1; else fp_UPFNN =0;
 if (format&FP_GROUP_DIGIT_FALSE) fp_GD=0; else if (format&FP_GROUP_DIGIT_TRUE) fp_GD=1;else fp_GD=0;
 pNF = PrefGetPreference(prefNumberFormat);
 
 switch(pNF)
 {
 case nfCommaPeriod: 		gs=',';	fs='.';
  break;
 case nfPeriodComma:		gs='.';	fs=',';
  break;
 case nfSpaceComma:		gs=0x20;	fs=',';
  break;
 case nfApostrophePeriod:	gs=39;	fs='.';
  break;
 case nfApostropheComma:	gs=39;	fs=',';
  break;
 default:					gs=0x20;	fs='.';
  break;  
 }
 _d.d=expr;
 FlpBase10Info(_d.fd, &m, &exp, &sign);
 if (m==0) sign = 0;
 i=StrLen(result);j=0;
 exp+=addExp;
 exp+=7;
 rNumDig = COUNT_DIG - exp-1 - numDig;
 if ( rNumDig>0 && rNumDig<=8) 
 	if ( m%(okr[rNumDig-1]*2) >= okr[rNumDig-1] ) 
 		{m+= okr[rNumDig-1]*2; if ( m/(okr[7]*2) ) exp++;}
 zeroNum =  - exp-1;
 StrPrintF(mStr,pfs,m);
 if (sign == 1){ if (fp_UPFNN) result[i++]='('; else result[i++]='-';}
 if (exp<0 && !fp_ILD && !numDig) result[i++]='0';
 if ( exp<0 && fp_ILD)  result[i++]='0';
 while (exp>=0) 
 {
  if (j<StrLen(mStr)) {result[i++] = mStr[j++];} else {result[i++]='0';}
  if (fp_GD && exp && !(exp%3)) result[i++]=gs; 
  exp--;
 }
 if (numDig)
 {
  result[i++]=fs;
  while(numDig>0)
  {
   if (zeroNum>0) {result[i++]='0'; zeroNum--;} else
   {  if (j<StrLen(mStr)) result[i++] = mStr[j++]; else result[i++]='0';} 
   numDig--;
  }
 }
 if (sign == 1) if (fp_UPFNN) result[i++]=')';

 result[i]=0; 
 return;
}

Err StringLibFormatNumber (UInt16 refNum, double expr , UInt16 numDig , UInt16 format, char *result)
{
*result=0;
 FormatNumber(refNum, expr, numDig, format, result,0);
return (0);
}

Err StringLibFormatPercent(UInt16 refNum, double expr, UInt16 numDig, UInt16 format, char* result)
{
 Int16 len;
*result=0;
 FormatNumber(refNum, expr, numDig, format, result,2);
 len = StrLen(result);
 result[len]='%';
 result[len+1]=0; 
 return (0);
}

Err StringLibFormatCurrency(UInt16 refNum, double expr, UInt16 numDig, UInt16 format, char* result)
{
 Int16 len;
 result[0]='$';
 result[1]=0;
 FormatNumber(refNum, expr, numDig, format, result,0);
 len = StrLen(result);
 result[len+1]=0; 
 return (0);
}


static StringLibGlobalsPtr PrvMakeGlobals(UInt16 refNum)
{
	StringLibGlobalsPtr		gP = NULL;							// our globals pointer
	MemHandle			gH;									// our globals handle
	SysLibTblEntryPtr		libEntryP;							// pointer to our library table entry


	// Get library globals
	libEntryP = SysLibTblEntry(refNum);						// get our system library table entry
	ErrFatalDisplayIf(libEntryP == NULL, "invalid String lib refNum");
	
	// Error check to make sure the globals don't already exist
	ErrFatalDisplayIf(libEntryP->globalsP, "String lib globals already exist");
	
	// Allocate and initialize our library globals.
	gH = MemHandleNew(sizeof(StringLibGlobalsType));
	if ( !gH )		return( NULL );											// memory allocation error
	
	// Save the handle of our library globals in the system library table entry so we
	// can later retrieve it using SysLibTblEntry().
	libEntryP->globalsP = (void*)gH;

	// Lock our globals
	gP = PrvLockGlobals(refNum);				// this should not fail
	ErrFatalDisplayIf(gP == NULL, "failed to lock String lib globals");
		
	// Set the owner of our globals memory chunk to "system" (zero), so it won't get
	// freed automatically by Memory Manager when the first application to call
	// SampleLibOpen exits.  This is important if the library is going to stay open
	// between apps.
	MemPtrSetOwner(gP, 0);
	
	// Initialize our library globals
	MemSet(gP, sizeof(StringLibGlobalsType), 0);
	gP->thisLibRefNum = refNum;		// for convenience and debugging (althouth not used in this sample library)
	gP->openCount = 0;					// initial open count
	return( gP );							// return a pointer to our *locked* globals
}

static void PrvFreeGlobals(UInt16 refNum)
{
	MemHandle					gH;									// our globals handle
	SysLibTblEntryPtr		libEntryP;							// pointer to our library table entry

	// Get our library globals handle
	libEntryP = SysLibTblEntry(refNum);						// get our system library table entry
	ErrFatalDisplayIf(libEntryP == NULL, "invalid String lib refNum");
	
	gH = (MemHandle)(libEntryP->globalsP);					// get our globals handle from the entry
	
	// Free our library globals
	if ( gH )
		{
		libEntryP->globalsP = NULL;							// clear our globals reference
		MemHandleFree(gH);										// free our globals
		}
}

static StringLibGlobalsPtr PrvLockGlobals(UInt16 refNum)
{
	StringLibGlobalsPtr	gP = NULL;
	MemHandle		gH;
	SysLibTblEntryPtr	libEntryP;

	libEntryP = SysLibTblEntry(refNum);						// get our system library table entry
	if ( libEntryP )
		gH = (MemHandle)(libEntryP->globalsP);				// get our globals handle from the entry
	if ( gH )
		gP = (StringLibGlobalsPtr)MemHandleLock(gH);		// lock our globals
	return( gP );
}


static Boolean PrvIsLibOpen(UInt16 refNum)
{
	StringLibGlobalsPtr	gP;
	Boolean	isOpen = false;
	
	gP = PrvLockGlobals(refNum);
	
	if ( gP )
		{
		isOpen = true;
		PrvUnlockGlobals(gP);
		}
	
	return( isOpen );
}

