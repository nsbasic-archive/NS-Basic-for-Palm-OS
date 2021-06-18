//LogicTracer.c
//
 
 //following allows tracing to memoPad file
 //(comment out this line for production release)
 
 #define _TRACE on
 
 
 
//to use in code to output a TRACE message to memoPad file, 
//      Trace("format string",variables );
//      (just like using StrPrint format and variable parameters)

//#include <Pilot.h>
#include  <PalmOS.h>
#include  <PalmTypes.h>
#include  <PalmOSGlue.h>
#include  <PalmCompatibility.h>
#include <unix_stdio.h>
#include <unix_string.h>
#include "LogicTracer.h"
#include <StringMgr.h>

//Globals
int g_iIntlzd = 0 ;     //0 == not initialized, 1 == initialized
int g_iTrcRecFull = 0 ; //0 == room to add more trace, 1 == no more room
UInt g_uiRecIndex = 0;  //index of the record tracing to.  usu. set to 0
UInt g_uiRecOffset = 0; //Current offset writing to 
#define g_sTracePreamble "Tracing NSBasic RT\n"
#define g_sMemoPadDbName "MemoDB"

//////////////////////////////////////////////////////
//Routine to find a database on the palm.  Written
//to search for the Memo Pad db "MemoDB".
//
int iFindDb 
	( const char *lpszDbWanted, //db searcing for e.g. "MemoDB" for Memo Pads db
	  LocalID *pli )   //If found, id of db
{
	int iResult = 0 ;
	char sTmp [100] ;		
	int i, i2 ;

	char sDbName [33] ;
	UInt uiNumDbs = 0;
	LocalID uiDbId = 0;
	VoidHand vhRecHdl = 0;
	ULong ulDbType = 0;
	
	//Initialize caller var.
	*pli = 0 ;
	
	uiNumDbs = DmNumDatabases (0) ;
	StrPrintF(sTmp,"iInitMemoPad():%d dbs on Palm, searching for %s", 
		uiNumDbs, lpszDbWanted);
	//dbug (sTmp) ;
	
	for (i=0; i<uiNumDbs; i++)
	{
		//Get the dbs id
		uiDbId = DmGetDatabase (0, i) ;
		if (!uiDbId)
		{
			dbug ("AuditDbs ():DmGetDatabase error") ;
			continue ;
		} ;
		
		//extract some info
		if (DmDatabaseInfo 
		 (0,      //-> cardNo
		  uiDbId, //-> dbID
		  
		  sDbName,//<- nameP
		  0,      //<- attributesP
		  0,      //<- versionP
		  0,      //<- crDateP
		  0,      //<- modDateP
		  0,      //<- bckUpDateP
		  0,      //<- modNumP
		  0,      //<- appInfoIDP
		  0,      //<- sortInfoIDP
		  &ulDbType,      //<- typeP
		  0      //<- creatorP
		  ) != 0)
	  {
			StrPrintF(sTmp,"AuditDbs ():erroring calling DmDatabaseInfo on %d", uiDbId) ;
			dbug (sTmp) ;
	  }
	  else
	  {
		   i2 = StrCompare(sDbName, lpszDbWanted) ;
	  		StrPrintF (sTmp, "Comparing >%s< to >%s<, result is %d", sDbName, lpszDbWanted, i2) ;
	  		//dbug (sTmp) ;
  			
			StrPrintF(sTmp,"AuditDbs ():DmDatabaseInfo return name of >%s<, Type is %d", sDbName, ulDbType) ;
			//dbug (sTmp) ;
 
			if (i2 == 0)
			{
				iResult = 1 ;
				*pli = uiDbId ;
				StrPrintF(sTmp,"AuditDbs ():found %s", lpszDbWanted) ;
				//dbug (sTmp) ;
				break ;
			} ;
	  } ;
	  
	} ;
	
	return iResult ;
}
//////////////////////////////////////////////////////
//
int iAddStrToDb 
	(const DmOpenRef MemoPadDB,  //Open DB reference to add to
	 const UInt uiRecIndex,      //Record index in db.
	 const char *sRecTxt,        //Text to append
	 UInt *puiRecOffset)         //Offset to append from.
{
	int iResult = 1 ;

	char sTmp [100] ;
	CharPtr		recText;
	ULong ulRecSz ;
	VoidHand vhRecHdl = 0;
	
	//Resize the record for the new next
	ulRecSz = *puiRecOffset + strlen (sRecTxt) + 1 ;
	
	vhRecHdl = DmResizeRecord (MemoPadDB, uiRecIndex, ulRecSz) ;
	if (!vhRecHdl)
	{
		dbug ("iAddStrToDb():DmGetRecord error, Could not get new memopad record");
		iResult = 0 ;
		goto exit ;
	}
	else
	{
		StrPrintF(sTmp,"iAddStrToDb():DmGetRecord obtained record %d", uiRecIndex);
		//dbug (sTmp) ;
	} ;
	

	StrPrintF(sTmp,"iAddStrToDb():calling MemHandleLock on %x", vhRecHdl);
	//dbug (sTmp) ;
	recText = MemHandleLock(vhRecHdl);

	if (DmWrite (recText, *puiRecOffset, sRecTxt, strlen (sRecTxt)+1) != 0)
	{
		StrPrintF(sTmp,"iAddStrToDb():DmWrite error writing %s", sRecTxt);
		dbug (sTmp) ;
		iResult = 0 ;
		goto exit ;
	} ;
	*puiRecOffset += strlen (sRecTxt) ;	  	
	StrPrintF(sTmp,"iAddStrToDb():DmWrite just wrote %s, *puiRecOffset == %d", sRecTxt, *puiRecOffset);
	//dbug (sTmp) ;

	if (MemHandleUnlock (vhRecHdl) != 0)
	{
		StrPrintF(sTmp,"iAddStrToDb():MemHandleUnlock error");
		dbug (sTmp) ;
		iResult = 0 ;
	} ;
 	//if (DmReleaseRecord (MemoPadDB, uiRecIndex, true) != 0)
	//{
	//	StrPrintF(sTmp,"iAddStrToDb():DmReleaseRecord error");
	//	dbug (sTmp) ;
	//	iResult = 0 ;
	//} ;
 
exit: ;	
	return iResult ;	 
}	  
//////////////////////////////////////////////////////
//Append a string to the end of the specified string
//record.
//
int iAddStrToDbRec 
	( const char *sDbWanted,  //Name of db e.g. "MemoDB"
	  const UInt uiRecIndex,  //Record # in db
	  const char *sRecTxt,    //Text to append
	  UInt *puiRecOffset)     //The offset to append at.
{
	int iResult = 1 ;
	
	char sTmp [100] ;
	LocalID	dbID;				
	DmOpenRef DB = 0;				// P5. handle for database
	
	if (!iFindDb (sDbWanted, &dbID))
	{
		StrPrintF(sTmp,"iAddStrToDbRec ():error find %s db", sDbWanted) ;
		dbug (sDbWanted) ; 	
		iResult = 0 ;
		goto exit ;
	} ;

	DB = DmOpenDatabase (0, dbID, dmModeReadWrite) ;
	if (!DB)
	{
		StrPrintF(sTmp,"iAddStrToDbRec ():error opening db %d", dbID) ;
		dbug (sTmp) ;
		iResult = 0 ;
		goto exit ;
	} ;

	if (!iAddStrToDb
	 ( DB,
	   uiRecIndex,
	   sRecTxt,
	   puiRecOffset))
	{
		dbug ("iAddStrToDbRec ():error calling iAddStrToDb") ;
		iResult = 0 ;
		goto exit ;
	} ;
	
exit: ;	
	if (DB)
	{
		DmCloseDatabase (DB) ;	
		DB = 0 ;
	} ;
	return iResult ;
}
//////////////////////////////////////////////////////
//Remove all previous traces.
//
int iRemoveAllTraceRecs ()
{
	int iResult = 1 ;

	int i, i2 ;
	char sTmp [300] ;
	char sTmp2 [50] ;
	LocalID	dbID;				
	DmOpenRef MemoPadDB = 0;
	VoidHand vhRecHdl = 0;
	CharPtr recText;

	if (!iFindDb (g_sMemoPadDbName, &dbID))
	{
		StrPrintF(sTmp,"iRemoveAllTraceRecs():error find %d db", g_sMemoPadDbName) ;
		dbug (sTmp) ; 	
		iResult = 0 ;
		goto exit ;
	} ;

	MemoPadDB = DmOpenDatabase (0, dbID, dmModeReadWrite) ;
	if (!MemoPadDB)
	{
		StrPrintF(sTmp,"iRemoveAllTraceRecs ():error opening db %d", dbID) ;
		dbug (sTmp) ;
		iResult = 0 ;
		goto exit ;
	} ;
	
	//Try tracing records
	i = 0 ;
	while (1)
	{
		vhRecHdl = DmQueryRecord (MemoPadDB, i) ;
		if (!vhRecHdl)
		{
			break ;
		} ;
		recText = MemHandleLock (vhRecHdl) ;
		
		i2 = strlen (g_sTracePreamble) ;
		//StrPrintF(sTmp,"i2 = %d", i2) ;
		//dbug (sTmp) ;
		
		StrNCopy (sTmp2, (char*)recText, i2) ;
		sTmp2 [i2] = 0 ;
		//StrCopy (sTmp2, (char*)recText) ;
		//dbug (recText) ;
		//dbug (sTmp2) ;
		MemHandleUnlock (vhRecHdl) ;
		vhRecHdl = 0 ;			

		//StrPrintF(sTmp,"iRemoveAllTraceRecs ():compare >%s< to >%s<",sTmp2, g_sTracePreamble) ;
		//dbug (sTmp) ;
		
		if (StrCompare (sTmp2, g_sTracePreamble) == 0)
		{
			//StrPrintF(sTmp,"iRemoveAllTraceRecs ():deleting record %d", i) ;
			//dbug (sTmp) ;
		
			//delete this record
			if (DmDeleteRecord (MemoPadDB, i) != 0)
			{
				StrPrintF(sTmp,"iRemoveAllTraceRecs ():error deleting record %d", i) ;
				dbug (sTmp) ;
				iResult = 0 ;
				goto exit ;
			} ;
		} ;
		i++ ;
	} ;

exit: ;
	if (MemoPadDB)	
	{
		DmCloseDatabase (MemoPadDB) ;
		MemoPadDB = 0 ;
	} ;
	return iResult ;
}
//////////////////////////////////////////////////////
//Routine to find the Memo Pad db and create
//a new trace record at the top.
//
int iInitMemoPad ()
{
	int iResult = 1 ;

	CharPtr recText;
	int i ;
	char sTmp [100] ;		
	LocalID	dbID;				
	ULong ulRecSz ;
	VoidHand vhRecHdl = 0;

	DmOpenRef MemoPadDB = 0;				// P5. handle for database

	if (!iRemoveAllTraceRecs ())
	{
		StrPrintF(sTmp,"iInitMemoPad():error deleting previous traces") ;
		dbug (sTmp) ; 	
		iResult = 0 ;
		goto exit ;
	} ;
		
	if (!iFindDb (g_sMemoPadDbName, &dbID))
	{
		StrPrintF(sTmp,"iInitMemoPad():error find %d db", g_sMemoPadDbName) ;
		dbug (sTmp) ; 	
		iResult = 0 ;
		goto exit ;
	} ;
	
	MemoPadDB = DmOpenDatabase (0, dbID, dmModeReadWrite) ;
	if (!MemoPadDB)
	{
		StrPrintF(sTmp,"iInitMemoPad():error opening db %d", dbID) ;
		dbug (sTmp) ;
		iResult = 0 ;
		goto exit ;
	} ;
	
	StrPrintF (sTmp, "iInitMemoPad(), Opened existing memopad db %x", MemoPadDB) ;
	// (sTmp) ;

	//Try tracing records
	i = 0 ;
	while (1)
	{
		vhRecHdl = DmQueryRecord (MemoPadDB, i) ;
		if (!vhRecHdl)
		{
			break ;
		} ;
		recText = MemHandleLock (vhRecHdl) ;
		MemHandleUnlock (vhRecHdl) ;
		vhRecHdl = 0 ;			
		i++ ;
	} ;
		
	//Create a zero sized recordd
	StrPrintF(sTmp,"iInitMemoPad():calling DmNewRecord on %x", MemoPadDB);
	//dbug (sTmp) ;
	
	//Create a new trace record, we'll resize the record as needed
	g_uiRecIndex = 0 ;
	g_uiRecOffset = 0 ;
	vhRecHdl = DmNewRecord (MemoPadDB, &g_uiRecIndex, g_uiRecOffset+1) ;
	if (!vhRecHdl)
	{
		dbug ("iInitMemoPad():DmNewRecord error, Could not get new memopad record");
		iResult = 0 ;
		goto exit ;
	}
	else
	{
		StrPrintF(sTmp,"iInitMemoPad():DmNewRecord created new record %d", g_uiRecIndex);
		//dbug (sTmp) ;
	} ;
	if (DmReleaseRecord (MemoPadDB, g_uiRecIndex, true) != 0)
	{
		 dbug ("iInitMemoPad():DmReleaseRecord error") ;
	}
	else
	{
		 //dbug ("iInitMemoPad():DmReleaseRecord success") ;	
	} ;
	vhRecHdl = 0 ;

	if (!iAddStrToDb
	 ( MemoPadDB,
	   g_uiRecIndex,
	   g_sTracePreamble,
	   &g_uiRecOffset))
	{
		dbug ("iInitMemoPad():error calling iAddStrToDb") ;
		iResult = 0 ;
		goto exit ;
	} ;

exit: ;

	if (MemoPadDB != 0)
	{
		DmCloseDatabase (MemoPadDB) ;	
		MemoPadDB = 0 ;
	} ;
	
	StrPrintF(sTmp,"iInitMemoPad():returns %d", iResult);
	//dbug (sTmp) ;
	
	return iResult ;
}
/////////////////////////////////////////////////////////////////////////////////
//
void TraceDlg (const char *formatStr, ...) 
{
#ifdef _TRACE
	char string[512];
	va_list args = 0;

	
	//Make a formatted string with all the arguments
	//passed in.  
	/*Example from Palm OS doc:
	void MyPrintF(Char* s, Char* formatStr, ...)
	{
		va_list args;
		Char text[0x100];
		va_start(args, formatStr);
		StrVPrintF(text, formatStr, args);
		va_end(args);
		MyPutS(text);
	}
	*/	
	
	va_start(args, formatStr);
	StrVPrintF (string, formatStr, args);
	va_end(args);
	
	//StrCopy (string, lpszFormat) ;
	dbug (string) ;
	
#endif

	return ;
}
//////////////////////////////////////////////////////
//add trace to all the trace devices.  Beware,
//don't pass in more than three params.
//
/* Example from Palm OS doc:

void MyPrintF(Char* s, Char* formatStr, ...)
{
	va_list args;
	Char text[0x100];
	va_start(args, formatStr);
	StrVPrintF(text, formatStr, args);
	va_end(args);
	MyPutS(text);
}

*/	
void Trace (const char *formatStr, ...) 
{

#ifdef _TRACE

	char string[512];
	va_list args = 0;
	CharPtr		recText;
	Int			textLen ;
//dbug("at trace");	
	if (g_iTrcRecFull == 1)
	{
		//Jump out if memo pad record is full.
		return ;
	} ;
//dbug("not full");
	
	if (g_iIntlzd == 0)
	{
//dbug("initializing");
		//do 1 time intialization
		g_iIntlzd = 1 ;
		
		//dbug ("Trace(): Initializing Memo Pad Trace") ;
		if (!iInitMemoPad ())
		{
			 dbug ("Trace()Error opening memo db") ;
			 g_iTrcRecFull = 1 ;
			 return ;
		} ;
		
		//Call this to show a message box indicating trace.
		//dbug ("Tracing NSBasic RT to Memo Pad") ;
	} ;
	
	//Make a formatted string with all the arguments
	//passed in.  
	va_start(args, formatStr);
	StrVPrintF (string, formatStr, args);
	va_end(args);
//dbug(string);	
	if (!iAddStrToDbRec (g_sMemoPadDbName, g_uiRecIndex, string, &g_uiRecOffset))
	{
		//When the palm fills up, stop tracing
		dbug ("Trace(): Trace Record full, trace disabled") ;
		g_iTrcRecFull = 1 ;
	} ;
	
#endif

	return ;
}

