#include <PalmOS.h>
#include <PalmTypes.h>
#include <PalmCompatibility.h>

#include <SysUtils.h>
#include <SysEvtMgr.h>
#include <FatalAlert.h>
#include <FloatMgr.h> 
#include <SystemMgr.h>
#include <ScrollBar.h>
#include <FrmGlue.h> 
 
#include "MathLib.h"

#include "NSBPNOShared.h"
#include "copy.h" 
#include "NSBPNOGlue.h"

#ifndef __MC68K__
#include "endianutils.h"
#endif

#ifdef __MC68K__

void formatDateWithString(  double* n,char * fmt,  char separator, char * result);
void formatTimeWithString(  double* n,char * fmt,  char separator, char * result);
 
void misc_stringfix(int i, char *res, int num) ;
extern void misc_fmtno(char *fmt,char *wk,int bef,int aft,int decpt, char *result);
extern int      dbNo;
void redrawGrid(struct ObjectData * objPtr);
#else
void redrawGrid(PNOBlock *pnoP, struct ObjectData *objPtr);
#endif
#ifdef __MC68K__
void gridDrawCallback (VoidPtr grid, short row, short col, RectanglePtr bounds )
;
struct ObjectData * locateObjectPtr(Word id);
char* gridTextPtr(struct ObjectData * objPtr,struct gridColInfo* cptr, int row
                 ,char *workString, TableType*grid,   int *coltype);
double gridValue(struct ObjectData * objPtr,struct gridColInfo* cptr, int row
                 , TableType*grid,   int *coltype);                 
//struct dbType * setDbPtr(int dbno);
struct dbType* getDatabasePtr();
ULong locateDbField(struct dbType*db, struct dbField * dbFld,  VoidPtr recPtr,  Boolean sortSw);
ULong locateDbFieldContent(struct dbType*db, struct dbField * dbFld,  VoidPtr recPtr,  Boolean sortSw);
struct dbField *  locateDbFieldPtr(struct dbType*db);
#else
struct ObjectData * locateObjectPtr(PNOBlock *pnoP, Word id);
char* gridTextPtr(PNOBlock *pnoP, struct ObjectData * objPtr,struct gridColInfo* cptr, Int16 row
                 ,char *workString, TableType*grid,   Int16 *coltype);
double gridValue(PNOBlock *pnoP, struct ObjectData * objPtr,struct gridColInfo* cptr, Int16 row
                 , TableType*grid,   Int16 *coltype);                 
#endif
#ifdef __MC68K__
void gridFormat( struct ObjectData *objPtr);
struct dbType *getDatabasePtr( );
Int16 gridCommonAddRow(struct ObjectData *objPtr, int controlid);
#else
void gridFormat(PNOBlock *pnoP, struct ObjectData *objPtr);
struct dbType *getDatabasePtr(PNOBlock *pnoP);
Int16 gridCommonAddRow(struct ObjectData *objPtr, int controlid);
#endif

VoidPtr resizePtr(VoidPtr p,  long additional);

#ifndef __MC68K__
#define MiscFatalAlert(s) SysFatalAlert(s)
#endif

#ifdef __MC68K__
Int16 gridCommonRemoveRow(struct ObjectData *objPtr, Int16 controlid,Int16 row);       
Int32 find_long_integ_arg();
extern UInt16 find_integer();                     /*---find next integer in code--*/
Int16 executeSomeCode();
extern UInt16 find_offset();
#else
Int16 gridCommonRemoveRow(PNOBlock *pnoP, struct ObjectData *objPtr, Int16 controlid,Int16 row);       
Int32 find_long_integ_arg(PNOBlock *pnoP);
extern UInt16 find_integer(PNOBlock *pnoP); //EMP
extern void readOneDbArgument(PNOBlock *pnoP, Arg *arg5, struct dbType * db,VoidPtr recPtr,UInt16 *theOffset);
Int16 executeSomeCode(PNOBlock *pnoP);     // EMP
extern UInt16 find_offset(PNOBlock *pnoP);   // EMP
#endif

#ifdef __MC68K__
unsigned long positionToDbField(struct dbType*db,struct dbField * dbFld,char* recPtr);
#else
unsigned long positionToDbField(PNOBlock *pnoP, struct dbType*db,struct dbField * dbFld,char* recPtr);
#endif


void freeCellContents( struct ObjectData* objPtr);	//4/28/04

DoubleToStr(double val, CharPtr ans);

//**************************************************************************
//
//**************************************************************************
struct dbField * setDbField(struct dbType*db, int colNo)
{
    struct dbField * dbFld;
   
    
    dbFld=db->ptrFields;      
#ifndef __MC68K__
	dbFld = (struct dbField *)ByteSwap32(dbFld);
#endif
    dbFld=((struct dbField*)((char*)dbFld+sizeof(dbFldExample)*colNo));   
    return(dbFld);
}

    
//**************************************************************************
//
//**************************************************************************
UInt16 getGridIndexFromPtr(FormPtr frm, VoidPtr    controlPtr)
{
    UInt16 pos;
     
    
    for(pos=0;pos<FrmGetNumberOfObjects(frm);++pos )
    {
        if(FrmGetObjectPtr(frm,pos)==controlPtr) goto foundIt;
    }
    SysFatalAlert("Cannot locate object on form");
    pos=0;
foundIt:    
     
    return(pos);
}

#ifdef __MC68K__
//**************************************************************************
//
//**************************************************************************
double cvtPalmInternalDateToDouble(DateType *dt )
{
  
  double d;
//StrPrintF(debug,"in datetodouble y=%d m=%d d=%d",dt->year,dt->month,dt->day);
//dbug(debug);  
  d=cvt_date_to_dbl(dt->year+1904,dt->month,dt->day);
  return(d);
}
//**************************************************************************
//
//**************************************************************************
double cvtPalmInternalTimeToDouble( unsigned char*tm )
{
  double t;
  
  t=cvt_time_to_dbl(*tm,*(tm+1),*(tm+2));
  return(t);
}
//**************************************************************************
//
//**************************************************************************
void cvtDoubleToPalmInternalDate(double dt, DateType* d )
{
 
  int yr;
  int mo;
  int da;
  
  cvt_date_to_ymd( dt,&yr, &mo,  &da);
//StrPrintF(debug,"cvt dbl to palm-- y=%d m=%d d=%d",yr,mo,da);
//dbug(debug);
  d->year=yr-1904;
  d->month=mo;
  d->day=da;
}
//**************************************************************************
//
//**************************************************************************
void cvtDoubleToPalmInternalTime(double tm ,unsigned char *t)
{
  //note...changed 2/9/2000 from using a 2-byte internal Palm timetype format 
  //to a 3-byte field to also carry seconds
  int hr;
  int min;
  int sec;
  cvt_time_to_hms(tm,&hr,&min,&sec);
  *t=*((unsigned char *)(&hr)+1);
  *(t+1)=*((unsigned char *)(&min)+1);
  *(t+2)=*((unsigned char *)(&sec)+1);
  
}
#endif

//-------------------------------------------------------------------------------
//   read a datbase record and seperate field values
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridSetDatabaseFields(struct dbType *db,DmOpenRef dbr,UInt16 dbRecNo)
#else
void gridSetDatabaseFields(PNOBlock *pnoP, struct dbType *db,DmOpenRef dbr,UInt16 dbRecNo)
#endif
{
  struct dbField* dbFld;
  VoidHand recHand;
  VoidPtr  recPtr;
  UInt offset=0;
  Int16 i;
#ifdef __MC68K__
 struct dataelem *elem_tbl_ptr(UInt16 de_no);       /*--data elem tbl calc */
#else
 struct dataelem *elem_tbl_ptr(PNOBlock *pnoP, UInt16 de_no);      // EMP
#endif
#ifdef __MC68K__
 char *devel_address(struct dataelem *arg, UInt16 s1,UInt16 s2,UInt16 s3);
#else
 char *devel_address(PNOBlock *pnoP, struct dataelem *arg, UInt16 s1,UInt16 s2,UInt16 s3); //EMP
#endif
    
   recHand=DmGetRecord(dbr,dbRecNo);
   recPtr=MemHandleLock(recHand);
   
//StrPrintF(debug,"reading rec flds %d",dbRecNo);
//SysFatalAlert(debug);
  
// //start insertions 02042004
//  if(db->keyFldNo !=0)
//  {
//SysFatalAlert("reading key");
//         //get key field value
//         arg5= elem_tbl_ptr(db->keyFldNo);
//	     arg5_occ1=0;
//	     arg5_occ2=0;
//	     arg5_occ3=0;
//	     arg5_sde1=0;
//	     arg5_sde2=0;
//	     arg5_sde3=0;
//	     arg5_val = devel_address(arg5, arg5_occ1,arg5_occ2,arg5_occ3);
//	     readOneDbArgument(db,recPtr,&offset);
//  }
//  //end insertion 02042004

#ifdef __MC68K__
  dbFld=db->ptrFields;
  for(i=0;i<db->noFields;++i)
#else
  dbFld=(struct dbField *)ByteSwap32(db->ptrFields);
  for(i=0;i<ByteSwap16(db->noFields);++i)
#endif
  {
//StrPrintF(debug,"reading dbfld %d into dataelem#=%d",i,dbFld->tblNo);
//SysFatalAlert(debug);
#ifdef __MC68K__
     arg5= elem_tbl_ptr(dbFld->tblNo);
     arg5_occ1=0;
     arg5_occ2=0;
     arg5_occ3=0;
     arg5_sde1=0;
     arg5_sde2=0;
     arg5_sde3=0;
     arg5_val = devel_address(arg5, arg5_occ1,arg5_occ2,arg5_occ3);
            
     //??need to go by the type in dbfld and do own store into arg5
     readOneDbArgument(db,recPtr,&offset);
      
     dbFld = (struct dbField*)((char*)dbFld + sizeof( dbFldExample));
#else
	 Arg arg5;

     arg5.dataElem = elem_tbl_ptr(pnoP, ByteSwap16(dbFld->tblNo));
     arg5.occ1=0;
     arg5.occ2=0;
     arg5.occ3=0;
     arg5.sde1=0;
     arg5.sde2=0;
     arg5.sde3=0;
     arg5.val = devel_address(pnoP, arg5.dataElem, arg5.occ1, arg5.occ2, arg5.occ3);
            
     //??need to go by the type in dbfld and do own store into arg5
     readOneDbArgument(pnoP, &arg5, db,recPtr,&offset);

     dbFld = (struct dbField*)((char*)dbFld + sizeof( dbFldExample));
#endif
   } 

  MemHandleUnlock(recHand);
  DmReleaseRecord(dbr,dbRecNo,false);
}

//-------------------------------------------------------------------------------
//   formatting
//-------------------------------------------------------------------------------
void commonFormatCode( char *wk, char * fmtString,char*result)
{
  int i;
  
  int bef;
  int aft;
  char s[256];
  int decpt;
 
  char sepThous=',';   //separator char for decimal point position 
  char sepDec='.';      //separator char for thousands positions
  
    decpt=-1;
    bef=0;
    aft=0;
    for(i=0;i<StrLen(wk);++i)
    {
      if (wk[i]=='-') ;
      else
      {
         if (wk[i]=='.') {decpt=i;continue;}
         if(decpt==-1)bef+=1;
         else         aft+=1; 
      }
    }
 
    //GetNumberSeparators(sysPrefs.numberFormat, &sepThous, &sepDec);          //get thousands and decimal separator chars
//StrPrintF(debug,"got separators=%d %c %c",sysPrefs.numberFormat,sepThous,sepDec);
//dbug(debug);
    //formatNumberWithFormatString(fmtString,wk,bef,aft,decpt,result,sepThous,sepDec);  //use new formatting routine
    misc_fmtno(fmtString,wk,bef,aft,decpt,result); 

    return;
 
}
//-------------------------------------------------------------------------------
//   check to see if format contains yes/no type format request
//-------------------------------------------------------------------------------
int chkFormatYesNo( double* n,  char *fmt, char *s)
{
	double d = *n;
#ifndef __MC68K__
	d = SwapDouble(d);
#endif
    if (StrCaselessCompare(fmt,"yes/no")==0)
    {
        if(d==0.0) StrCopy(s,"NO");
        else         StrCopy(s,"YES");
        return(1);
    }
    if (StrCaselessCompare(fmt,"true/false")==0)
    {
        if(d==0.0) StrCopy(s,"FALSE");
        else         StrCopy(s,"TRUE");
        return(1);
    }
    if (StrCaselessCompare(fmt,"on/off")==0)
    {
        if(d==0.0) StrCopy(s,"OFF");
        else         StrCopy(s,"ON");
        return(1);
    }
    return(0);    //was not one of the special formats
     
}

//-------------------------------------------------------------------------------
//   check to see if db record is marked as deleted
//-------------------------------------------------------------------------------

Int16 dbRecIsDeleted( DmOpenRef dbr, UInt theRec)
{
    //this rtn checks to see if a database record is deleted
    //returns 1 if deleted,   0 if not
    UInt16 recInfo;
    
    DmRecordInfo(dbr,theRec,&recInfo,NIL,NIL);

#ifndef __MC68K__
	recInfo = ByteSwap16(recInfo);
#endif

    if( (recInfo & 0x80 ) !=0x00) return(1);
    return(0);
}

//-------------------------------------------------------------------------------
//   find offset to a field in database record
//----------------------------------------------------------------------------------------------------------
#ifdef __MC68K__
unsigned long positionToDbField(struct dbType*db,struct dbField * dbFld,char* recPtr)
#else
unsigned long positionToDbField(PNOBlock *pnoP, struct dbType*db,struct dbField * dbFld,char* recPtr)
#endif
{
    DmOpenRef dbr;
    ULong offset;
    char* p;
    Word i;
    struct dbField* tempcol;
    Int16 max;
     
    Int16 tempInt;

	dbr = db->dm;
	
#ifndef __MC68K__
	dbr = (DmOpenRef)ByteSwap32(dbr);
#endif

#ifdef __MC68K__    
      if(db->LastDbRecordRead<1)
      {
         p=MemHandleLock(db->hName);
         StrPrintF(debug,"Attempt to reference column data without a current record for database=%s",p);
         MemHandleUnlock(db->hName);
         MiscFatalAlert(debug);
      }
      if(db->LastDbRecordRead>DmNumRecords(dbr))
      {
          p=MemHandleLock(db->hName);
          StrPrintF(debug,"Attempt to read past end-of-file for database=%s",p);
          MemHandleUnlock(db->hName);
          MiscFatalAlert(debug);
      }
//StrPrintF(debug,"x3  reading back record %u",db->LastDbRecordRead);
//dbug(debug);
      if ( dbRecIsDeleted(dbr,db->LastDbRecordRead-1) )
      {
         p=MemHandleLock(db->hName);
         StrPrintF(debug,"Attempt to access deleted record for database=%s",p);
         MemHandleUnlock(db->hName);
         MiscFatalAlert(debug);
      }
#else
	  if (ByteSwap16(db -> LastDbRecordRead) < 1)
      {
      	 char debug[100];
      	 char *b;
         p=MemHandleLock((MemHandle)ByteSwap16(db->hName));
         strcpy(debug,"Attempt to reference column data without a current record for database=");
         b = debug;
         while (*b) ++b;
         strcpy(b, p);
         MemHandleUnlock((MemHandle)ByteSwap16(db->hName));
         SysFatalAlert(debug);
      }
      if(ByteSwap16(db->LastDbRecordRead)>DmNumRecords(dbr))
      {
      	 char debug[100];
      	 char *b;
         p=MemHandleLock((MemHandle)ByteSwap16(db->hName));
         strcpy(debug,"Attempt to read past end-of-file for database=");
         b = debug;
         while (*b) ++b;
         strcpy(b, p);
         MemHandleUnlock((MemHandle)ByteSwap16(db->hName));
         SysFatalAlert(debug);
      }
//StrPrintF(debug,"x3  reading back record %u",db->LastDbRecordRead);
//dbug(debug);
      if ( dbRecIsDeleted(dbr,ByteSwap16(db->LastDbRecordRead)-1) )
      {
      	 char debug[100];
      	 char *b;
         p=MemHandleLock((MemHandle)ByteSwap16(db->hName));
         strcpy(debug,"Attempt to access deleted record for database=");
         b = debug;
         while (*b) ++b;
         strcpy(b, p);
         MemHandleUnlock((MemHandle)ByteSwap16(db->hName));
         SysFatalAlert(debug);
      }
#endif
    
    offset=0;
    
    max = dbFld->colNo;
#ifndef __MC68K__
	max = ByteSwap16(max);

#endif
    for( i=0;i<max;++i)
    {
//StrPrintF(debug,"advancing to column %d",i);
//dbug(debug);
        //loop thru cols to position to the data of interest
        tempcol=db->ptrFields; 
#ifndef __MC68K__ 
		tempcol= (struct dbField *)ByteSwap32(tempcol);
#endif   
        tempcol=((struct dbField*)((char*)tempcol+sizeof(dbFldExample)*i));
//StrPrintF(debug,"colNo=%d dbcolType=%d",i,tempcol->type);
//SysFatalAlert(debug);


#ifdef __MC68K__
        switch(tempcol->type)
#else

		switch(ByteSwap16(tempcol->type))
#endif
        {
          case dbFldTypeString:  //string
//dbug("string");
            offset+=StrLen((char*)recPtr+offset)+1;
            break;
          case dbFldTypeLongInt:    //long integ
            offset+=4;
            break;  
          case dbFldTypeDouble:    //double
//dbug("double");
            offset+=8;
            break;
          case dbFldTypeDate:  //date
//dbug("date");          
            offset+=8;
            break;
          case dbFldTypeTime:  //time
            
            offset+=8;
            break;
          case dbFldTypeShortInt:  
            offset+=2;
            break;
          case dbFldTypeSingle:  
            offset+=4;
            break; 
          case dbFldTypeByte:  
            offset+= 1;
            break;     
          default:
            //should not occur 
            ;
        }
        //801 MiscHandleUnlock(db->hColInfo);         
    }    
//StrPrintF(debug,"returning dboffset =%lu  for fld=%d",offset,dbFld->colNo);
//SysFatalAlert(debug);

    return(offset);
}
   
//-----------------------------------------------------------------------------------------------------------
//  ckeck if row # is within assigned # rows
//-------------------------------------------------------------------------------
Boolean isGridRowValid( struct ObjectData *objPtr, Int16 row)
{
#ifdef __MC68K__
    if( (row<objPtr->numItems) && (row>=0) ) return(true);
#else
    if( (row<ByteSwap16(objPtr->numItems)) && (row>=0) ) return(true);
#endif
    else                                     return(false);
}
//-------------------------------------------------------------------------------
//  ckeck if col # is within defined # columns
//-------------------------------------------------------------------------------
Boolean isGridColumnValid( struct ObjectData *objPtr, Int16 col)
{
#ifdef __MC68K__
    if((col<objPtr->cols) && (col>=0) )      return(true);
#else
    if((col<ByteSwap16(objPtr->cols)) && (col>=0) )      return(true);
#endif
    else                                     return(false);
}

//-------------------------------------------------------------------------------
//  check if row is currently visible
//-------------------------------------------------------------------------------
Boolean isGridRowVisible( struct ObjectData *objPtr, Int16 row)
{
#ifdef __MC68K__
    if(  (row<objPtr->firstRow) || (row>=objPtr->firstRow+objPtr->visibleRows) ) return(false);
#else
    if(  (row<ByteSwap16(objPtr->firstRow)) 
    	|| (row>=ByteSwap16(objPtr->firstRow)+ByteSwap16(objPtr->visibleRows)) ) return(false);
#endif
    else                                                                         return(true);
}

//-------------------------------------------------------------------------------
// return largest free memory chunk
//-------------------------------------------------------------------------------

unsigned long calcFreeMemory()
{
    unsigned long free;
    unsigned long biggest;
    MemHeapCompact(0);
    MemHeapFreeBytes(0, &free, &biggest);//-------------------------------------------------------------------------------
    return(biggest);
}

//-------------------------------------------------------------------------------
//   resize a memory block
//-------------------------------------------------------------------------------
VoidPtr resizePtr(VoidPtr p,  long additional)
{
     VoidPtr p2;
     Handle h;
     
     h=MemPtrRecoverHandle(p);
     MemHandleUnlock(h);
     MemHandleResize(h,MemHandleSize(h)+additional);
     if(h==0) MiscFatalAlert("Out of memory.");
     p2=MemHandleLock(h);
     return (p2);
}

//-------------------------------------------------------------------------------
//   returen a ptr to column info
//-------------------------------------------------------------------------------
struct gridColInfo* locateGridColInfo(struct ObjectData* objPtr,  Int16 col)
{
#ifdef __MC68K__
  return( ((struct gridColInfo*) ((char*)objPtr->colInfo+col*sizeof(gridColInfoExample))));
#else
  return( ((struct gridColInfo*) ((char*)ByteSwap32(objPtr->colInfo)
  	+col*sizeof(gridColInfoExample))));
#endif

}

//-------------------------------------------------------------------------------
//   returen a ptr 
//-------------------------------------------------------------------------------
//struct gridColInfo* locateGridColumnPtr(objPtr, col )
//{
//    MiscFatalAlert(" undefined");
//}
//-------------------------------------------------------------------------------
//  returns a ptr to a cell's text ptr
//-------------------------------------------------------------------------------
char** gridCellPtr(struct ObjectData* objPtr, Int16 row, Int16 col)
{
#ifdef __MC68K__
   return(  (char**)((char*)objPtr->gridContent+4*(row*(objPtr->cols-objPtr->howManyColsInBind)+(col-objPtr->howManyColsInBind))) );
#else
   return(  (char**)((char*)ByteSwap32(objPtr->gridContent)
   	+4*(row*(ByteSwap16(objPtr->cols)
   	-ByteSwap16(objPtr->howManyColsInBind))+(col-ByteSwap16(objPtr->howManyColsInBind)))) );

#endif
}

//------------------------------------------------------------------------------------------
//    opens the database used by bound grid
//
//       returns 0 on success;    1 on error
//------------------------------------------------------------------------------------------
DmOpenRef gridOpenDb(struct dbType*db )
{
  
  VoidHand recHand;
  VoidPtr  recPtr;
  int res;
  
  int err;
  DmOpenRef dbref;
  char*p;
   //dbfind_arg(4);  //cardNo
   //db=getDatabasePtr();
#ifdef __MC68K__
   p=MemHandleLock(db->hName);
#else
   p = MemHandleLock((MemHandle) ByteSwap32(db -> hName));
#endif
//StrPrintF(debug,"trying to open database %s",p);
//SysFatalAlert(debug);
   db->lid=DmFindDatabase( 0,p);
#ifdef __MC68K__
   MemHandleUnlock(db->hName);
#else
   db->lid = ByteSwap32(db->lid);
   MemHandleUnlock((MemHandle) ByteSwap32(db->hName));
#endif
   if(db->lid==0)
   {
     return(0);
   }
#ifdef __MC68K__
   dbref=DmOpenDatabase(0,db->lid,dmModeReadOnly);
#else
	dbref = DmOpenDatabase(0, (LocalID) ByteSwap32(db -> lid),dmModeReadOnly);
#endif
   if(dbref==0)
   {
     return(0);                           //02.20.02 GH
   }
    
   db->openSw='o';
#ifdef __MC68K__
   db->dm=dbref;
#else
   db -> dm = (DmOpenRef) ByteSwap32(dbref);
#endif
   db->LastDbRecordRead=-1;
   db->curHand=0;
   db->offset=0;
   db->cardno=0;
   return(dbref);
}

#ifdef __MC68K__

//------------------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------------
void initializeGrid(struct ObjectData * objPtr,FormPtr frm )
{
    struct gridColInfo* cptr;
    
    int col;
    int row;
    char blankText[]=" ";
    void* p; 
    
//SysFatalAlert("in initializeGrid");       
    objPtr->colInfo=MemHandleLock(MemHandleNew(
	                                     TblGlueGetNumberOfColumns(
	                             (TableType*)FrmGetObjectPtr(FrmGetFormPtr (objPtr->frmId),objPtr->index))
	                                  *sizeof(gridColInfoExample)));
	                                  
    objPtr->cols =  TblGlueGetNumberOfColumns ((TableType*)FrmGetObjectPtr(frm,objPtr->index));
    objPtr->visibleRows=TblGetNumberOfRows((TableType*)FrmGetObjectPtr(frm,objPtr->index));
    objPtr->numItems=objPtr->visibleRows;
    
//StrPrintF(debug,"cols=%d rows=%d items=%d",objPtr->cols,objPtr->visibleRows,objPtr->numItems);
//SysFatalAlert(debug);    
    
    objPtr->wantGridLines = 'y';  //added 08232004
	objPtr->howManyColsInBind=0;
	                              
    objPtr->firstRow=0; 
    
	objPtr->scrollMin=0;                          
    objPtr->scrollMax=objPtr->visibleRows-1;
    objPtr->scrollPagesize=objPtr->visibleRows;
//SysFatalAlert("b");
    objPtr->gridContent=MemHandleLock(MemHandleNew(4*objPtr->visibleRows*objPtr->cols)); 
    objPtr->itemData   =MemHandleLock(MemHandleNew(4*objPtr->visibleRows));

//SysFatalAlert("c"); 
    objPtr->bindToDbHasWhereClause=false;
    objPtr->refreshFromDatabase=true;
    objPtr->dbNo=0;
    
    objPtr->currentCol=-2;   //because return code adds 1 to it
    objPtr->currentRow=-2;   
//SysFatalAlert("init columns");                                   	                   
#ifndef __MC68K__
// Swap everything
	objPtr -> colInfo = (MemPtr)ByteSwap32(objPtr -> colInfo);
	objPtr -> cols = ByteSwap16(objPtr -> cols);
	objPtr -> visibleRows = ByteSwap16(objPtr -> visibleRows);
	objPtr -> numItems = ByteSwap16(objPtr -> numItems);
	objPtr -> scrollMax = ByteSwap16(objPtr -> scrollMax);
	objPtr -> scrollPageSize = ByteSwap16(objPtr -> scrollPageSize);
	objPtr -> gridContent = (MemPtr) ByteSwap32(objPtr -> gridContent);
	objPtr -> itemData = (MemPtr) ByteSwap32(objPtr -> itemData);
	objPtr -> currentCol = ByteSwap16(objPtr -> currentCol);
	objPtr -> currentRow = ByteSwap16(objPtr -> currentRow);
#endif 

#ifdef __MC68K__
    for(col=0;col<objPtr->cols;++col)
	{
	    cptr=locateGridColInfo(objPtr, col);   
	    cptr->dbSupplied = false;          
	    
	    cptr->dbColNo=0;
	    
	    cptr->colNo=col;           
	    cptr->type='s';    
	    cptr->format=0;   
   }
#else
    for(col=0;col<ByteSwap16(objPtr->cols);++col)
	{
	    cptr=locateGridColInfo(objPtr, col);   
	    cptr->dbSupplied = false;          
	    
	    cptr->dbColNo=0;
	    
	    cptr->colNo=ByteSwap16(col);           
	    cptr->type='s';    
	    cptr->format=0;   
   }
#endif
//SysFatalAlert("init rows");

#ifdef __MC68K__ 
   for(row=0;row<objPtr->visibleRows;++row)
   {
       for(col=0;col<objPtr->cols;++col)
       {
	       //p =MemHandleLock(MemHandleNew(2));
	       //StrCopy(p ,blankText);
           *(gridCellPtr(objPtr,row,col))=0 ;
           TblSetItemFont((TableType*)FrmGetObjectPtr(FrmGetFormPtr (objPtr->frmId),objPtr->index),row,col,0);   //06072004 
       }
   }
      //get the original grid bounds 050104
   TblGetBounds((TableType*)FrmGetObjectPtr(FrmGetFormPtr (objPtr->frmId),objPtr->index),&(objPtr->origGridBounds));
#else
   for(row=0;row<ByteSwap16(objPtr->visibleRows);++row)
   {
       for(col=0;col<ByteSwap16(objPtr->cols);++col)
       {
	       //p =MemHandleLock(MemHandleNew(2));
	       //StrCopy(p ,blankText);
           *(gridCellPtr(objPtr,row,col))=0 ; 
           TblSetItemFont((TableType*)FrmGetObjectPtr(FrmGetFormPtr 
           		ByteSwap16(objPtr->frmId),
           		ByteSwap16(objPtr->index)),row,col,0);   //06072004 
       }
   }
      //get the original grid bounds 050104
   TblGetBounds((TableType*)FrmGetObjectPtr(FrmGetFormPtr (ByteSwap16(objPtr->frmId)),
   	ByteSwap16(objPtr->index),&(objPtr->origGridBounds));
#endif

//("done with initGrid");   
//StrPrintF(debug,"leaving init cols=%d",objPtr->cols);
//SysFatalAlert(debug);  
}
#endif
 
 //-------------------------------------------------------------------------------
//  releases all of the memory used by a grid
//-------------------------------------------------------------------------------
void releaseGridMemory( struct ObjectData * objPtr)
{
  
   void * textP;
   Int16 row;
   Int16 col;
   
   struct gridColInfo* cptr;     
   
   
   //free item data
   if(objPtr->itemData)  
   {
#ifdef __MC68K__
     MemPtrFree(objPtr->itemData);
#else
	 MemPtrFree((MemPtr)ByteSwap32(objPtr -> itemData));
#endif
     objPtr->itemData=0;
   }   
   
   
   
   //free cell text ptrs
   if(objPtr->gridContent)  
   {
   		freeCellContents(objPtr); //050104
        //for(row=0;row<objPtr->numItems;++row)
        //{
        //   for(col=objPtr->howManyColsInBind;col<objPtr->cols;++col)
        //   {
        //     
        //     textP=*( gridCellPtr(objPtr,row,col));
        //     if(textP)      MemPtrFree( textP);
        //   }
        //}
      
#ifdef __MC68K__        
        MemPtrFree(objPtr->gridContent); 
#else
        MemPtrFree((MemPtr)ByteSwap32(objPtr->gridContent)); 
#endif
        objPtr->gridContent=0;      
   }
   if(objPtr->colInfo!=0) 
   {
#ifdef __MC68K__
       for(col=0;col<objPtr->cols;++col)
#else
		for (col = 0; col < ByteSwap16(objPtr -> cols); ++col);
#endif
		{
#ifdef __MC68K__
		    cptr=locateGridColInfo(objPtr, col);   
		    if(cptr->format!=0) MemPtrFree(cptr->format);   
		    cptr->format=0;   
#else
		    cptr=locateGridColInfo(objPtr, col);   
		    if(cptr->format!=0) MemPtrFree((MemPtr)ByteSwap32(cptr->format));   
		    cptr->format=0;   
#endif		    
		     
	   }
	   
	   // 050104
#ifdef __MC68K__
	  if(objPtr->colInfo) MemPtrFree(objPtr->colInfo);
#else
	  if(objPtr->colInfo) MemPtrFree((MemPtr)ByteSwap32(objPtr->colInfo));
#endif
	  objPtr->colInfo = 0;

	   //MemPtrFree(objPtr->colInfo);
   }
#ifdef __MC68K__
   initializeGrid(objPtr,FrmGetActiveForm());
#else
   initializeGrid(pnoP, objPtr,FrmGetActiveForm());
#endif
   objPtr->numItems=0;           
     
}

//-------------------------------------------------------------------------------
//  common rtn to set the text of some grid cell
//-------------------------------------------------------------------------------
#ifdef __MC68K__
commonGridSetText(struct ObjectData *objPtr,Int16 row,Int16 col,char dontDisplaySw,char*t)
#else
commonGridSetText(PNOBlock *pnoP, struct ObjectData *objPtr,Int16 row,Int16 col,char dontDisplaySw,char*t)
#endif
{  
   struct gridColInfo* cptr;
   char* * cellMatrix;
   char str[512];
        
  if(  (isGridRowValid(objPtr,row))      //must have valid row and col #'s
    && (isGridColumnValid(objPtr,col)))
  {
      cptr=locateGridColInfo(objPtr, col );            
       //02062004 if(cptr->dbSupplied==false)        //can only set text if column not bound to database    
       //02062004{
          
          cellMatrix=gridCellPtr(objPtr,row,col);  //point to the pointer to the cell's text
          
          if( *cellMatrix)  MemPtrFree(*cellMatrix); //release current cell's text memory
          
          
          
        	 *cellMatrix=MemPtrNew(StrLen(t)+1);
         	 StrCopy(*cellMatrix,t);
      	  
       
          //redraw if row is visible and not in "before draw" rtn
          if( (PNO(typeOfScript)!='b') && (dontDisplaySw==0x00))  
          {
//SysFatalAlert("common text change");
              if( isGridRowVisible(objPtr,row) )
              {
//SysFatalAlert( "redraw on text chg");
#ifdef __MC68K__
                  redrawGrid(objPtr);   
#else
                  redrawGrid(pnoP, objPtr);   
#endif
              }
          }
      //02062004}    
  }    

                
}

//-------------------------------------------------------------------------------
//  common rtn to set the numeric value of some grid cell
//-------------------------------------------------------------------------------
#ifdef __MC68K__
commonGridSetValue(struct ObjectData *objPtr,int row,int col,char dontDisplaySw,double value)
#else
commonGridSetValue(PNOBlock *pnoP, struct ObjectData *objPtr,int row,int col,char dontDisplaySw,double value)
#endif
{  
   struct gridColInfo* cptr;
   double**   cellMatrix;
    
   char str[512];
      
//StrPrintF(debug,"in set value  row=%d  col=%d ",row,col);
//SysFatalAlert(debug);
  if(  (isGridRowValid(objPtr,row))      //must have valid row and col #'s
    && (isGridColumnValid(objPtr,col)))
  {
 
      cptr=locateGridColInfo(objPtr, col );            
      //02062004 if((cptr->dbSupplied==false)        //can only set value if column not bound to database    
      //02062004 && (cptr->type != 's'))            //and not text column
       
       if (cptr->type != 's')    //insert 02062004 //can only set value if column not text column
      {
           
          cellMatrix=(double**)gridCellPtr(objPtr,row,col);  //point to the pointer to the cell's text
          
          if( *cellMatrix==0)   
          {
//SysFatalAlert("getting mem for  cell value");          
          
        	 *cellMatrix=MemPtrNew(8);
	      }
#ifndef __MC68K__
		  else
		  {
		  	 *cellMatrix=(double *)ByteSwap32(*cellMatrix);
		  }
#endif 
//SysFatalAlert("setting cell value");      
          MemMove(*cellMatrix,&value,8);
#ifndef __MC68K__
		  *cellMatrix=(double *)ByteSwap32(*cellMatrix);
#endif 

//SysFatalAlert("redrawing");      	   
          //redraw if row is visible and not in "before draw" rtn
          if( (PNO(typeOfScript)!='b') && (dontDisplaySw==0x00))  
          {
              if( isGridRowVisible(objPtr,row) )
              {
#ifdef __MC68K__
                  redrawGrid(objPtr);   
#else
                  redrawGrid(pnoP, objPtr);   
#endif
              }
          }
      }    
  }    

}

//-------------------------------------------------------------------------------
// return the # of columns of the grid  
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridGetCols(FormPtr frm,VoidPtr controlPtr)
#else
void gridGetCols(PNOBlock *pnoP, Arg *arg4, FormPtr frm, VoidPtr controlPtr)
#endif
{
   struct ObjectData * objPtr;
  
   PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
#ifdef __MC68K__
   objPtr=locateObjectPtr(PNO(controlid));  //get the ptr to our obj data
   restore4(objPtr->cols);             //return the grid # of cols    
#else
	objPtr = locateObjectPtr(pnoP, PNO(controlid));
    {
        double d = ByteSwap16(objPtr -> cols);
        d = SwapDouble(d);
        misc_stodbl(pnoP, arg4 -> dataElem, arg4 -> occ1, arg4 -> occ2, arg4 -> occ3, &d);
	}
#endif
    
} 

//-------------------------------------------------------------------------------
// return the number of rows in the grid
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridGetRows(FormPtr frm,VoidPtr controlPtr)
#else
void gridGetRows(PNOBlock *pnoP, Arg *arg4, FormPtr frm, VoidPtr controlPtr)
#endif
{
  
  struct ObjectData *objPtr;
   
  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
#ifdef __MC68K__
  objPtr=locateObjectPtr(PNO(controlid));   //get the ptr to our obj data        
  restore4(objPtr->numItems);          //return the # of rows
#else
  objPtr=locateObjectPtr(pnoP, PNO(controlid));   //get the ptr to our obj data        
    {
        double d = ByteSwap16(objPtr -> numItems);
        d = SwapDouble(d);
        misc_stodbl(pnoP, arg4 -> dataElem, arg4 -> occ1, arg4 -> occ2, arg4 -> occ3, &d);
	}
#endif
       
}


//-------------------------------------------------------------------------------
// return the selected column no of the grid
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridGetSelectedCol(FormPtr frm,VoidPtr controlPtr)
#else
void gridGetSelectedCol(PNOBlock *pnoP, Arg *arg4, FormPtr frm, VoidPtr controlPtr)
#endif
{
  struct ObjectData *objPtr;
    
  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
#ifdef __MC68K__
  objPtr=locateObjectPtr(PNO(controlid));  //get the ptr to our obj data  
  restore4(objPtr->currentCol+1);         //return the sel col (1-based)  
#else
	objPtr = locateObjectPtr(pnoP, PNO(controlid));
	{
        double d = ByteSwap16(objPtr->currentCol)+1;
        d = SwapDouble(d);
        misc_stodbl(pnoP, arg4 -> dataElem, arg4 -> occ1, arg4 -> occ2, arg4 -> occ3, &d);
	} 
#endif
}

//-------------------------------------------------------------------------------
// set value of rowData for a row
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridSetRowData(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
{
    
    int row;
    unsigned long value;
    struct ObjectData *objPtr;
    
    row  =*paramPtr-1;                     //row #  
    value=find_long_integ_arg();                  //item data value to assign
    PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));                            
    objPtr=locateObjectPtr(PNO(controlid));      //and locate the obj ptr for the grid                
    
    
     
    if(isGridRowValid(objPtr,row) )                          //if row is valid
    {
        *((ULong*)((char*)(objPtr->itemData)+4*row))=value;  //assign value for row      
    }
}
#else
void gridSetRowData(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr,double* paramPtr)
{
    
    Int16 row;
    UInt32 value;
    struct ObjectData *objPtr;
    
    row  =ReadUnaligned64((char *)paramPtr)-1;                     //row #  
    value=find_long_integ_arg(pnoP);                  //item data value to assign
    PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));                            
    objPtr=locateObjectPtr(pnoP, PNO(controlid));      //and locate the obj ptr for the grid                
    
    
     
    if(isGridRowValid(objPtr,row) )                          //if row is valid
    {
        *((ULong*)((char*)ByteSwap32(objPtr->itemData)+4*row))=ByteSwap32(value);  //assign value for row      
    }
}
#endif

//-------------------------------------------------------------------------------
// set the selected column of a grid
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridSetSelectedCol(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
#else
void gridSetSelectedCol(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr,double* paramPtr)
#endif
{
  
  Int16 row;
  Int16 col;
  Int16 actualRow; 
  struct ObjectData *objPtr;  
  
  col=*paramPtr-1;                //get the column arg 
  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
#ifdef __MC68K__
  objPtr=locateObjectPtr(PNO(controlid));               
#else
  objPtr=locateObjectPtr(pnoP, PNO(controlid));               
#endif  
               
  
//StrPrintF(debug,"set col = %d  scriptType=%c firstRow=%d currentRow=%d",col,PNO(typeOfScript),objPtr->firstRow,objPtr->currentRow);
//SysFatalAlert(debug);
  if(isGridColumnValid(objPtr,col))      //if grid column # is a valid col #
  {
#ifdef __MC68K__
      objPtr->currentCol=col;                //remembewr the selected col #
#else
	  objPtr->currentCol = ByteSwap16(col);
#endif
      if( PNO(typeOfScript)!='b')   
      {
#ifdef __MC68K__
		  if (objPtr->currentRow >= 0)
		  {
          actualRow=objPtr->currentRow - objPtr->firstRow;    //calc row in visible grid
          //select the cell by row and column
          TblSelectItem((TableType*)FrmGetObjectPtr(FrmGetFormPtr(objPtr->frmId),
                         objPtr->index),actualRow,objPtr->currentCol); //select the cell
		  }
#else
		  if (ByteSwap16(objPtr->currentRow >= 0))
		  {
          actualRow=ByteSwap16(objPtr->currentRow) - ByteSwap16(objPtr->firstRow);    //calc row in visible grid
          //select the cell by row and column
          TblSelectItem((TableType*)FrmGetObjectPtr(FrmGetFormPtr(ByteSwap16(objPtr->frmId)),
                         ByteSwap16(objPtr->index)),actualRow,ByteSwap16(objPtr->currentCol)); //select the cell
		  }
#endif
      }
  }
  
}

//-------------------------------------------------------------------------------
// return the selected row no of the grid
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridGetSelectedRow(FormPtr frm,VoidPtr controlPtr)
#else
void gridGetSelectedRow(PNOBlock *pnoP, Arg *arg4, FormPtr frm,VoidPtr controlPtr)
#endif
{
  struct ObjectData *objPtr;
   
  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));

#ifdef __MC68K__
  objPtr=locateObjectPtr(PNO(controlid));  //get the ptr to our obj data  
  restore4(objPtr->currentRow+1);         //return the sel col (1-based)  
#else
	objPtr = locateObjectPtr(pnoP, PNO(controlid));
	{
        double d = ByteSwap16(objPtr->currentRow)+1;
        d = SwapDouble(d);
        misc_stodbl(pnoP, arg4 -> dataElem, arg4 -> occ1, arg4 -> occ2, arg4 -> occ3, &d);
	} 
#endif
}

//-------------------------------------------------------------------------------
// return the number of visible rows in the grid
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridGetVisibleRows(FormPtr frm,VoidPtr controlPtr)
#else
void gridGetVisibleRows(PNOBlock *pnoP, Arg *arg4, FormPtr frm, VoidPtr controlPtr)
#endif
{
  struct ObjectData * objPtr;
 
  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
#ifdef __MC68K__
  objPtr=locateObjectPtr(PNO(controlid));  //get the ptr to our obj data 
  restore4(objPtr->visibleRows);      //return # of visible cols     
#else
  objPtr=locateObjectPtr(pnoP, PNO(controlid));  //get the ptr to our obj data 
	{
        double d = ByteSwap16(objPtr->visibleRows);
        d = SwapDouble(d);
        misc_stodbl(pnoP, arg4 -> dataElem, arg4 -> occ1, arg4 -> occ2, arg4 -> occ3, &d);
	} 
#endif
}

//-------------------------------------------------------------------------------
// set a row as the currently selected row
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridSetSelectedRow(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
#else
void gridSetSelectedRow(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr,double* paramPtr)
#endif
{
 
  
  Int16 row;
  Int16 col;
  struct ObjectData *objPtr;
   
#ifdef __MC68K__  
  row=*paramPtr-1;
  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));                                    //ctlid is 1st arg
  objPtr=locateObjectPtr(PNO(controlid));              //get the ptr to our obj data             
#else
  row=ReadUnaligned64((char *)paramPtr)-1;
  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));                                    //ctlid is 1st arg
  objPtr=locateObjectPtr(pnoP, PNO(controlid));              //get the ptr to our obj data             
#endif
  
                          //calc the row # as integer (1-based)
  if( (row == -2) || (isGridRowValid(  objPtr,  row)) ) //modified 07122004 //if row is valid
  {
#ifdef __MC68K__
      objPtr->currentRow=row;                         //save as the selected row
#else
	  objPtr->currentRow = ByteSwap16(row);
#endif
    
      if(isGridRowVisible(objPtr,row) || (row==-2) )
      {
         //row is outside the visible grid
#ifdef __MC68K__
         if(row>=0) objPtr->firstRow=row;     //modified 07122004 //set as beginning row to display
         else       objPtr->firstRow = 0;     //added    07122004
         objPtr->refreshFromDatabase=true;                 //and tell to reload visible grid
     
         if( PNO(typeOfScript) != 'b' )  redrawGrid(objPtr);  //if not in "before draw" rtn, then redraw
#else
         if(row>=0) objPtr->firstRow=ByteSwap16(row);                    //set as beginning row to display
         else       objPtr->firstRow = 0;     //added    07122004
         objPtr->refreshFromDatabase=true;                 //and tell to reload visible grid
     
         if( PNO(typeOfScript) != 'b' )  redrawGrid(pnoP, objPtr);  //if not in "before draw" rtn, then redraw
#endif
      }
      else
      {
         //row is in the visible grid
         if( PNO(typeOfScript) != 'b' )          //if not in "before draw" rtn,
         {
#ifdef __MC68K__
              TblSelectItem((TableType*)FrmGetObjectPtr(FrmGetFormPtr(objPtr->frmId),
                  objPtr->index),objPtr->currentRow-objPtr->firstRow,objPtr->currentCol);    //mark row as selected
#else
              TblSelectItem((TableType*)FrmGetObjectPtr(FrmGetFormPtr(ByteSwap16(objPtr->frmId)),
                  ByteSwap16(objPtr->index)),ByteSwap16(objPtr->currentRow)-ByteSwap16(objPtr->firstRow),ByteSwap16(objPtr->currentCol));    //mark row as selected
#endif
         } 
      }
  }
}

//-------------------------------------------------------------------------------
//  return an integer argument's value
//-------------------------------------------------------------------------------
#ifdef __MC68K__
int find_integ_arg()
{
    find_arg_1();
    return( integ_value(arg1,(double*)arg1_val)  );
}
#else
Int16 find_integ_arg(PNOBlock *pnoP)
{
    Arg arg1;
    double d;
    find_arg_PNO(pnoP, &arg1);
    
    d = ReadUnaligned64(arg1.val);
    return (Int16) d;
}
#endif

//-------------------------------------------------------------------------------
//  return an integer argument's value
//-------------------------------------------------------------------------------
#ifdef __MC68K__
Int32 find_long_integ_arg()
{
    find_arg_1();
    return( long_integ_value(arg1,(double*)arg1_val) );
}
#else
Int32 find_long_integ_arg(PNOBlock *pnoP)
{
    Arg arg1;
    double d;
    find_arg_PNO(pnoP, &arg1);
    
    d = ReadUnaligned64(arg1.val);
    return (Int32) d;
}
#endif


//-------------------------------------------------------------------------------
//set # rows
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridSetRows(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
#else
void gridSetRows(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr,double* paramPtr)
#endif
{
   struct ObjectData *objPtr;
#ifdef __MC68K__
   Int16 newRows = *paramPtr;
#else
	Int16 newRows = ReadUnaligned64((char *)paramPtr);
#endif
   
   PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));

#ifdef __MC68K__  
   objPtr=locateObjectPtr(PNO(controlid)); 
   while( newRows> objPtr->numItems )
   {
//StrPrintF(debug,"adding row want=%d  have=%d",newRows,objPtr->numItems);
//SysFatalAlert(debug);
        gridCommonAddRow(objPtr, PNO(controlid));
   }
   while(  newRows< objPtr->numItems)
   {
//StrPrintF(debug,"deleting row   want=%d  have=%d",newRows,objPtr->numItems);
//SysFatalAlert(debug);
       gridCommonRemoveRow(objPtr, PNO(controlid), objPtr->numItems-1);
   }
   if(PNO(typeOfScript)!='b')  redrawGrid(objPtr);
#else
   objPtr=locateObjectPtr(pnoP, PNO(controlid)); 
   while( newRows> ByteSwap16(objPtr->numItems) )
   {
//StrPrintF(debug,"adding row want=%d  have=%d",newRows,objPtr->numItems);
//SysFatalAlert(debug);
        gridCommonAddRow(objPtr, PNO(controlid));
   }
   while(  newRows< ByteSwap16(objPtr->numItems))
   {
//StrPrintF(debug,"deleting row   want=%d  have=%d",newRows,objPtr->numItems);
//SysFatalAlert(debug);
       gridCommonRemoveRow(pnoP, objPtr, PNO(controlid), ByteSwap16(objPtr->numItems)-1);
   }
   if(PNO(typeOfScript)!='b')  redrawGrid(pnoP, objPtr);
#endif    
}


#ifdef __MC68K__
//-------------------------------------------------------------------------------
//set # Cols
//-------------------------------------------------------------------------------
/*   !!!not implemented
void gridSetCols(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
{


//??


}
*/
#endif

//-------------------------------------------------------------------------------
//set column width
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridSetColWidth(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
#else
void gridSetColWidth(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr,double* paramPtr)
#endif
{

  Int16 w;
  struct gridColInfo* lastColPtr;
  struct ObjectData *objPtr;
  Int16 row;
  Int16 col;
  Int16 val = 0;	// 050104 
  struct gridColInfo*  colPtr;  
  Int16 oldWidth;
  Int16 totWidth = 0;
  Int16 ijk;
  Int16 newWidth;

  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  
#ifdef __MC68K__
  objPtr=locateObjectPtr(PNO(controlid));               
#else
  objPtr = locateObjectPtr(pnoP, PNO(controlid));
#endif  

#ifdef __MC68K__
  col=*paramPtr-1;                //get the column arg
  val=find_integ_arg(); 
#else
  {
  	double d;
  	d = ReadUnaligned64((char *)paramPtr);
  	col=((Int16) d)-1;                //get the column arg
  }
  val=find_integ_arg(pnoP); 
#endif

//StrPrintF(debug,"set col width   col=%d  val=%d",col,val);
//SysFatalAlert(debug);  
  if(isGridColumnValid(objPtr,col))      //if grid column # is a valid col #
  {  
      //02062004 if(col==objPtr->cols-1)
      //02062004 {
      //02062004     SysFatalAlert("Cannot set column width of last column (it is automatically set by changes to any other column's width.");
      //02062004     
      //02062004 }
      //02062004 else
      //02062004 {
#ifdef __MC68K__
	      objPtr->currentCol=col;                //remembewr the selected col #
	      colPtr=locateGridColInfo(  objPtr,    col);
	      // 050103 lastColPtr=locateGridColInfo(objPtr,objPtr->cols-1);
#else
		  objPtr -> currentCol = ByteSwap16(col);
	      colPtr=locateGridColInfo(  objPtr,    col);
	      // 050103 lastColPtr=locateGridColInfo(objPtr,ByteSwap16(objPtr->cols)-1);
#endif
	     
	        
	       /* inserted  02062004
	       oldWidth=colPtr->width;
	       if(lastColPtr->width-val+oldWidth<=0)
	       {
	          SysFatalAlert("Column width change would make final column width <= 0.");
	       }  
	       //now, adj width of last column to keep grid the same size
	       TblSetColumnWidth (controlPtr, objPtr->cols-1,lastColPtr->width-val+oldWidth);
	       lastColPtr->width-=val-oldWidth;
	       */    //inserted 02062004
#ifdef __MC68K__
	       colPtr->width=val;
#else
		   colPtr->width = ByteSwap16(val);
#endif
	       TblSetColumnWidth (controlPtr,col, val);  //set this column's new width
	      
#ifdef __MC68K__
	      //re-instituted some of this code 06072004  
		  //sum up all columns width
		 
		  for( ijk=0;ijk<objPtr->cols;++ijk)
		  {
		      lastColPtr=locateGridColInfo(objPtr,ijk);
		      totWidth += lastColPtr->width;
		  }
		  
	      lastColPtr=locateGridColInfo(objPtr,objPtr->cols-1);   
	      
	      if( totWidth != objPtr->origGridBounds.extent.x - 1*objPtr->cols)
	      {
	       	   //if changing last column would not make it 0 or less,
		       newWidth = lastColPtr->width - (totWidth - objPtr->origGridBounds.extent.x + 1*objPtr->cols);
		       if(newWidth > 0)
		       {
		          //then, adj width of last column to keep grid the same size
		           TblSetColumnWidth (controlPtr, objPtr->cols-1,newWidth);
		           lastColPtr->width = newWidth;
	      	   }
	      }
	      //end of changes 06072004
#else
	      //re-instituted some of this code 06072004  
		  //sum up all columns width
		 
		  for( ijk=0;ijk<ByteSwap16(objPtr->cols);++ijk)
		  {
		      lastColPtr=locateGridColInfo(objPtr,ijk);
		      totWidth += ByteSwap16(lastColPtr->width);
		  }
		  
	      lastColPtr=locateGridColInfo(objPtr,ByteSwap16(objPtr->cols)-1);   
	      
	      if( totWidth != objPtr->origGridBounds.extent.x - 1*ByteSwap16(objPtr->cols))
	      {
	       	   //if changing last column would not make it 0 or less,
		       newWidth = ByteSwap16(lastColPtr->width) - 
		       	(totWidth - ByteSwap16(objPtr->origGridBounds.extent.x) + 1*ByteSwap16(objPtr->cols));
		       if(newWidth > 0)
		       {
		          //then, adj width of last column to keep grid the same size
		           TblSetColumnWidth (controlPtr, ByteSwap16(objPtr->cols)-1,newWidth);
		           lastColPtr->width = ByteSwap16(newWidth);
	      	   }
	      }
	      //end of changes 06072004
#endif

	      if( PNO(typeOfScript)!='b')   
	      {
#ifdef __MC68K__
	           redrawGrid(objPtr);
#else
			   redrawGrid(pnoP, objPtr);
#endif
	      }
      //02062004 }
  }
}

//-------------------------------------------------------------------------------
//get col width
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridGetColWidth(FormPtr frm,VoidPtr controlPtr)
#else
void gridGetColWidth(PNOBlock *pnoP, Arg *arg4, FormPtr frm, VoidPtr controlPtr)
#endif
{

  struct ObjectData *objPtr;
  int row;
  int col;
  int val; 
  struct gridColInfo*  colPtr;  
  
  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
#ifdef __MC68K__
  objPtr=locateObjectPtr(PNO(controlid));                  
  col=find_integ_arg()-1;                //get the column arg 
#else
  objPtr = locateObjectPtr(pnoP, PNO(controlid));
  col=find_integ_arg(pnoP)-1;                //get the column arg 
#endif
  
 
  if(isGridColumnValid(objPtr,col))      //if grid column # is a valid col #
  {  
       
      colPtr=locateGridColInfo(  objPtr,    col);
  
#ifdef __MC68K__      
      restore4(colPtr->width);
#else
    {
        double d = ByteSwap16(colPtr -> width);
        d = SwapDouble(d);
        misc_stodbl(pnoP, arg4 -> dataElem, arg4 -> occ1, arg4 -> occ2, arg4 -> occ3, &d);
	}
#endif
 
      return;
  }
#ifdef __MC68K__      
  restore4(-1);
#else
    {
        double d = -1;
        d = SwapDouble(d);
        misc_stodbl(pnoP, arg4 -> dataElem, arg4 -> occ1, arg4 -> occ2, arg4 -> occ3, &d);
	}
#endif
}
#ifdef __MC68K__
//-------------------------------------------------------------------------------
//set # visible rows
//-------------------------------------------------------------------------------
/*    !!!not implemented
void gridSetVisibleRows(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
{
  int oldNoVisible;
  
  
  
  oldNoVisible=objPtr->visibleRows;
}
*/
#endif

//-------------------------------------------------------------------------------
//set valueMatrix
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridSetValueMatrix(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
#else
void gridSetValueMatrix(PNOBlock *pnoP,FormPtr frm,VoidPtr controlPtr,double* paramPtr)
#endif
{

struct ObjectData *objPtr;
 
  Int16 row;
  Int16 col;
//char wks [128]; 
//char wkt [128]; 
//VoidPtr valueP;
  char dontDisplaySw=0x00;
#ifndef __MC68K__
  Arg arg;
#endif

  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
#ifdef __MC68K__
  objPtr=locateObjectPtr(PNO(controlid));
  row=*paramPtr-1;        //row
  col=find_integ_arg()-1;        //column
  find_arg_1();                  //value
  
  //dontDisplaySw=find_char();  //0x01=no display 0x00=display
//DoubleToStr(*((double*)arg1_val), wks);

 
  commonGridSetValue(objPtr,row,col,dontDisplaySw,*((double*)arg1_val));
#else
  objPtr=locateObjectPtr(pnoP, PNO(controlid));
  row = ReadUnaligned64((char *)paramPtr) - 1;
  col = find_integ_arg(pnoP) - 1;
  
  find_arg_PNO(pnoP, &arg);
  commonGridSetValue(pnoP, objPtr,row,col,dontDisplaySw,*((double*)arg.val));
#endif
  
//valueP=*((VoidPtr*)((char*)objPtr->gridContent+4*(row*(objPtr->cols-objPtr->howManyColsInBind)+(col-objPtr->howManyColsInBind))));   
//DoubleToStr(*((double*)valueP),wkt);
//StrPrintF(debug,"setting cell value row=%d col=%d val=%s newValue=%s",row+1, col+1,wks,wkt);
//SysFatalAlert(debug);   
}

//set valueMatrix
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridSetFontMatrix(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
#else
void gridSetFontMatrix(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr,double* paramPtr)
#endif
{

struct ObjectData *objPtr;
 
  int row;
  int col;
  FontID fontID ;
//char wks [128]; 
//char wkt [128]; 
//VoidPtr valueP;
  //char dontDisplaySw=0x00;
  FontID oldFontID = FntGetFont();   //08022005

  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
#ifdef __MC68K__
  objPtr=locateObjectPtr(PNO(controlid));
  row=*paramPtr-1;        //row
  col=find_integ_arg()-1;        //column
  //find_arg_1();                  //font
  fontID = find_integ_arg();
#else
  objPtr=locateObjectPtr(pnoP, PNO(controlid));
  row=*paramPtr-1;        //row
  col=find_integ_arg(pnoP)-1;        //column
  //find_arg_1();                  //font
  fontID = find_integ_arg(pnoP);
#endif
  //dontDisplaySw=find_char();  //0x01=no display 0x00=display
//DoubleToStr(*((double*)arg1_val), wks);

 TblSetItemFont ((TableType*)controlPtr,row,col, fontID);
 
  FntSetFont(oldFontID);             //08022005
  
//valueP=*((VoidPtr*)((char*)objPtr->gridContent+4*(row*(objPtr->cols-objPtr->howManyColsInBind)+(col-objPtr->howManyColsInBind))));   
//DoubleToStr(*((double*)valueP),wkt);
//StrPrintF(debug,"setting cell value row=%d col=%d val=%s newValue=%s",row+1, col+1,wks,wkt);
//SysFatalAlert(debug);   
}
//-------------------------------------------------------------------------------
//get fontMatrix
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridGetFontMatrix(FormPtr frm,VoidPtr controlPtr)
#else
void gridGetFontMatrix(PNOBlock *pnoP, Arg *arg4, FormPtr frm,VoidPtr controlPtr)
#endif
{
  char wk[512];
  char emptyString[1]="";
  
  struct ObjectData *objPtr;
  struct gridColInfo* cptr;
  int ctype;
  double d=0;
  VoidPtr valueP=&d;
  int row;
  int col;

  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
#ifdef __MC68K__
  objPtr=locateObjectPtr(PNO(controlid));
  find_arg_1();
  row=integ_value(arg1,(double*)arg1_val)-1;   //get row integ
  find_arg_2();
  col=integ_value(arg2,(double*)arg2_val)-1;   //get column integ
#else
  objPtr=locateObjectPtr(pnoP, PNO(controlid));
  row = find_integ_arg(pnoP);
  col = find_integ_arg(pnoP);
#endif
                                 
  
  if ( isGridRowValid(objPtr,row)                //must have valid row and col #'s
    && isGridColumnValid(objPtr,col) ) 
  { 
	  d = TblGetItemFont ((TableType*)controlPtr,row,col );
 	   
  } 
#ifdef __MC68K__
  store4(&d);   
#else
   d = SwapDouble(d);
   misc_stodbl(pnoP, arg4 -> dataElem, arg4 -> occ1, arg4 -> occ2, arg4 -> occ3, &d);
#endif
}
//end additions 04012005

//-------------------------------------------------------------------------------
//get valueMatrix
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridGetValueMatrix(FormPtr frm,VoidPtr controlPtr)
#else
void gridGetValueMatrix(PNOBlock *pnoP, Arg *arg4, FormPtr frm,VoidPtr controlPtr)
#endif
{
  char wk[512];
  char emptyString[1]="";
  
  struct ObjectData *objPtr;
  struct gridColInfo* cptr;
  Int16 ctype;
  double d=0;
  VoidPtr valueP=&d;
  Int16 row;
  Int16 col;
#ifndef __MC68K__
	Arg arg1, arg2;
#endif

  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  
#ifdef __MC68K__
  objPtr=locateObjectPtr(PNO(controlid));               //get ctl's object ptr 
#else
	objPtr = locateObjectPtr(pnoP, PNO(controlid));
#endif                                 


#ifdef __MC68K__  
  find_arg_1();
  row=integ_value(arg1,(double*)arg1_val)-1;   //get row integ
  find_arg_2();
  col=integ_value(arg2,(double*)arg2_val)-1;   //get column integ
#else
	find_arg_PNO(pnoP, &arg1);
	find_arg_PNO(pnoP, &arg2);
	row = ReadUnaligned64(arg1.val) - 1;
	col = ReadUnaligned64(arg2.val) - 1;
#endif
  
  if ( isGridRowValid(objPtr,row)                //must have valid row and col #'s
    && isGridColumnValid(objPtr,col) ) 
  { 
	   cptr=locateGridColInfo(objPtr, col);        //point to col's information   
	   if(cptr->type != 's')
	   { 
	      if(cptr->dbSupplied)
	      {
#ifdef __MC68K__
	         d=gridValue( objPtr, cptr, row-objPtr->firstRow, (TableType*)controlPtr,&ctype);
#else
	         d=gridValue(pnoP, objPtr, cptr, row-objPtr->firstRow, (TableType*)controlPtr,&ctype);
#endif
	        
	      }
	      else
	      {
#ifdef __MC68K__
	         valueP=*((VoidPtr*)((char*)objPtr->gridContent+4*(row*(objPtr->cols-objPtr->howManyColsInBind)+(col-objPtr->howManyColsInBind))));   
	         if(valueP!=0)     d=*((double*)valueP);
#else
			 char *gc = (char *)ByteSwap32(objPtr->gridContent);
			 void **vpp;
	         vpp = (void **)(gc+4*(row*(ByteSwap16(objPtr->cols)-
	         	ByteSwap16(objPtr->howManyColsInBind))+(col-ByteSwap16(objPtr->howManyColsInBind))));
	         valueP = *(void **)(vpp);
	         valueP = (void *)ByteSwap32(valueP); 
	         if(valueP!=0)     d=ReadUnaligned64(valueP);
#endif
	      }             
       } 
  }
#ifdef __MC68K__
  store4(&d);   
#else
   d = SwapDouble(d);
   misc_stodbl(pnoP, arg4 -> dataElem, arg4 -> occ1, arg4 -> occ2, arg4 -> occ3, &d);
#endif
}

#ifdef __MC68K__
//-------------------------------------------------------------------------------
//set selected value
//-------------------------------------------------------------------------------
void gridSetSelectedValue(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
{
  int row;
  int col;
 
   
  struct ObjectData *objPtr;
 
   
  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  
  //03052004 find_arg_1();                          // text to assign
   
  objPtr=locateObjectPtr(PNO(controlid));      
  row=objPtr->currentRow;
  col=objPtr->currentCol;
   
  commonGridSetValue(objPtr,row,col,0x00,*paramPtr);

 
}
#endif

//-------------------------------------------------------------------------------
// get the text of a grid cell by its row and column  
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridGetCellMatrix(FormPtr frm,VoidPtr controlPtr)  
#else
void gridGetCellMatrix(PNOBlock *pnoP, Arg *arg4, FormPtr frm, VoidPtr controlPtr)
#endif
{
    
  char wk[512];
  char emptyString[1]="";
  VoidPtr textP;
  struct ObjectData *objPtr;
  struct gridColInfo* cptr;
#ifdef __MC68K__
 int ctype;
#else
 Int16 ctype;
#endif

  int row;
  int col;

#ifndef __MC68K__
	Arg arg1, arg2;
	double d;
#endif

//SysFatalAlert("2"); 
  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
//SysFatalAlert("3");

#ifdef __MC68K__
  objPtr=locateObjectPtr(PNO(controlid));               //get ctl's object ptr 
#else
  objPtr=locateObjectPtr(pnoP, PNO(controlid));               //get ctl's object ptr 
#endif

  textP=&emptyString;                              //init to null string
//SysFatalAlert("4");  
#ifdef __MC68K__
  find_arg_1();
  row=integ_value(arg1,(double*)arg1_val)-1;   //get row integ
  find_arg_2();
  col=integ_value(arg2,(double*)arg2_val)-1;   //get column integ
#else
  find_arg_PNO(pnoP, &arg1);
	row=((Int16) ReadUnaligned64(arg1.val)) - 1;
  find_arg_PNO(pnoP, &arg2);
    col=((Int16) ReadUnaligned64(arg2.val)) - 1;
#endif

//StrPrintF(debug,"row=%d col=%d",row,col);
//SysFatalAlert(debug);


  if ( isGridRowValid(objPtr,row)                //must have valid row and col #'s
    && isGridColumnValid(objPtr,col) ) 
  { 
      cptr=locateGridColInfo(objPtr, col);        //point to col's information   
//SysFatalAlert("5");
      if(cptr->dbSupplied)
      {
#ifdef __MC68K__
         textP=gridTextPtr(objPtr, cptr, row-objPtr->firstRow,&wk[0],(TableType*)controlPtr,&ctype);
#else
#ifndef __MC68K__
		pnoP -> dumm3 = 1;
#endif
         textP=gridTextPtr(pnoP, objPtr, cptr, row-objPtr->firstRow,&wk[0],(TableType*)controlPtr,&ctype);
#ifndef __MC68K__
		pnoP -> dumm3 = 0;
#endif
#endif
		// DIKEO textP is not returning right
      }
      else
      {
 //SysFatalAlert("7");
#ifdef __MC68K__
         textP=*((VoidPtr*)((char*)objPtr->gridContent+4*(row*(objPtr->cols-objPtr->howManyColsInBind)+(col-objPtr->howManyColsInBind))));   
#else
		 char *gc = (char *)ByteSwap32(objPtr->gridContent);
		 void **vpp;
         vpp = (void **)(gc+4*(row*(ByteSwap16(objPtr->cols)-
         	ByteSwap16(objPtr->howManyColsInBind))+(col-ByteSwap16(objPtr->howManyColsInBind))));
         textP = *(void **)(vpp);
         textP = (void *)ByteSwap32(textP);
         
#endif
      }
 //SysFatalAlert("8");
      if(textP==0)               textP=&emptyString;  //no text data yet
  } 
//SysFatalAlert("9");
#ifdef __MC68K__
  storestr4(textP);
#else
  misc_stostr(pnoP, &(arg4 -> dataElem), arg4 -> occ1, arg4 -> occ2, arg4 -> occ3, textP);
#endif
}

//-------------------------------------------------------------------------------
//   get the text of the selected cell
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridGetSelectedText(FormPtr frm,VoidPtr controlPtr)
#else
void gridGetSelectedText(PNOBlock *pnoP, Arg *arg4, FormPtr frm,VoidPtr controlPtr)
#endif
{
  char wk[512];
  char emptyString[1]="";
  VoidPtr textP;
  struct gridColInfo* cptr;
  struct ObjectData *objPtr;

#ifdef __MC68K__
  int ctype; 
#else
  Int16 ctype;
#endif
  
  int row;   
  int col;
      
  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
#ifdef __MC68K__
  objPtr=locateObjectPtr(PNO(controlid));               //get ctl's object ptr 
#else
  objPtr=locateObjectPtr(pnoP, PNO(controlid));               //get ctl's object ptr 
#endif
                            //init to null string
//SysFatalAlert("3");    
  row=objPtr->currentRow;
  col=objPtr->currentCol;
  textP=&emptyString;   
//SysFatalAlert("4");
 
  if ( isGridRowValid(objPtr,row)                //must have valid row and col #'s
    && isGridColumnValid(objPtr,col) ) 
  { 
//SysFatalAlert("5");  
      cptr=locateGridColInfo(objPtr, col);        //point to col's information   
//SysFatalAlert("6");      
      if(cptr->dbSupplied) 
      {
//SysFatalAlert("7");
#ifdef __MC68K__ 
          textP=gridTextPtr( objPtr, cptr, row-objPtr->firstRow,&wk[0],(TableType*)controlPtr,&ctype);
#else
          textP=gridTextPtr(pnoP, objPtr, cptr, row-objPtr->firstRow,&wk[0],(TableType*)controlPtr,&ctype);
#endif

      }
      else
      {
//SysFatalAlert("8");
#ifdef __MC68K__
          textP=*((VoidPtr*)((char*)objPtr->gridContent+4*(row*(objPtr->cols-objPtr->howManyColsInBind)+(col-objPtr->howManyColsInBind))));   
#else
		 char *gc = (char *)ByteSwap32(objPtr->gridContent);
		 void **vpp;
         vpp = (void **)(gc+4*(row*(ByteSwap16(objPtr->cols)-
         	ByteSwap16(objPtr->howManyColsInBind))+(col-ByteSwap16(objPtr->howManyColsInBind))));
         textP = *(void **)(vpp);
         textP = (void *)ByteSwap32(textP); 
#endif
     
      }
//SysFatalAlert("9");  
      if(textP==0)               textP=&emptyString;  //no text data yet
        
  } 
//SysFatalAlert("10");

#ifdef __MC68K__
  storestr4(textP);
#else
  misc_stostr(pnoP, &(arg4 -> dataElem), arg4 -> occ1, arg4 -> occ2, arg4 -> occ3, textP);
#endif
}

//-------------------------------------------------------------------------------
//get selected value
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridGetSelectedValue(FormPtr frm,VoidPtr controlPtr)
#else
void gridGetSelectedValue(PNOBlock *pnoP, Arg *arg4, FormPtr frm,VoidPtr controlPtr)
#endif
{
  char wk[512];
  char emptyString[1]="";
  
  struct ObjectData *objPtr;
  struct gridColInfo* cptr;
  Int16 ctype; 
  double d=0;
  VoidPtr valueP=&d;
  Int16 row;   
  Int16 col;
  
  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));

#ifdef __MC68K__
  objPtr=locateObjectPtr(PNO(controlid));               //get ctl's object ptr 
#else
  objPtr=locateObjectPtr(pnoP, PNO(controlid));               //get ctl's object ptr 
#endif
                                 //init to null string
  
  row=objPtr->currentRow;
  col=objPtr->currentCol;
  
  if ( isGridRowValid(objPtr,row)                //must have valid row and col #'s
    && isGridColumnValid(objPtr,col) ) 
  { 
      cptr=locateGridColInfo(objPtr, col);        //point to col's information   
      if(cptr->type != 's')
      {

#ifdef __MC68K__
	      if(cptr->dbSupplied) d=gridValue (objPtr, cptr, row-objPtr->firstRow, (TableType*)controlPtr,&ctype);
#else
	      if(cptr->dbSupplied) d=gridValue (pnoP, objPtr, cptr, row-objPtr->firstRow, (TableType*)controlPtr,&ctype);
#endif
	      else
	      {
#ifdef __MC68K__
	          valueP=*((VoidPtr*)((char*)objPtr->gridContent+4*(row*(objPtr->cols-objPtr->howManyColsInBind)+(col-objPtr->howManyColsInBind))));   
	          if(valueP!=0)      d=*((double*)valueP);  //no data yet 
#else
			 char *gc = (char *)ByteSwap32(objPtr->gridContent);
			 void **vpp;
	         vpp = (void **)(gc+4*(row*(ByteSwap16(objPtr->cols)-
	         	ByteSwap16(objPtr->howManyColsInBind))+(col-ByteSwap16(objPtr->howManyColsInBind))));
	         valueP = *(void **)(vpp);
	         valueP = (void *)ByteSwap32(valueP); 
	         if(valueP!=0)     d=ReadUnaligned64(valueP);
#endif
	      } 
	  }       
  } 

#ifdef __MC68K__
  store4(&d);   
#else
   d = SwapDouble(d);
   misc_stodbl(pnoP, arg4 -> dataElem, arg4 -> occ1, arg4 -> occ2, arg4 -> occ3, &d);
   
#endif
    
}

//-------------------------------------------------------------------------------
// return the item data value for a grid row
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridGetRowData(FormPtr frm,VoidPtr controlPtr)
#else
void gridGetRowData(PNOBlock *pnoP, Arg *arg4, FormPtr frm,VoidPtr controlPtr)
#endif
{
    
    unsigned long value;
    double reg;
    Int16 row;
    struct ObjectData *objPtr;
#ifndef __MC68K__
	Arg arg1;
#endif
          
    PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
#ifdef __MC68K__
    objPtr=locateObjectPtr(PNO(controlid));         
#else
    objPtr=locateObjectPtr(pnoP, PNO(controlid));         
#endif

#ifdef __MC68K__
    find_arg_1();
    row=basc_integ_value(arg1,(double*)arg1_val)-1;   //get the row #
#else
	find_arg_PNO(pnoP, &arg1);                  //value
	row=((Int16) ReadUnaligned64(arg1.val)) - 1;
#endif
          
   if(isGridRowValid(objPtr,row))          //if row # valid
    {
#ifdef __MC68K__
      value=*((unsigned long*)((char*)objPtr->itemData+4*row));  //return item data value
#else
	  value=*((unsigned long*)((char*)ByteSwap32(objPtr->itemData)+4*row));
	  value = ByteSwap32(value);
#endif
    }
    else value=0;                         //return 0 on invalid row

   reg=value;
#ifdef __MC68K__
   store_reg(&reg, arg4,(double*) arg4_val, arg4_occ1,arg4_occ2,arg4_occ3);
#else
	reg = SwapDouble(reg);
    misc_stodbl(pnoP, arg4 -> dataElem, arg4 -> occ1, arg4 -> occ2, arg4 -> occ3, &reg);
#endif
}


//-------------------------------------------------------------------------------
//  clear all rows from a grid
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridClear(FormPtr frm,VoidPtr controlPtr)
#else
void gridClear(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr)
#endif
{
	int row, col;

   struct ObjectData *objPtr;

   PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
#ifdef __MC68K__
   objPtr=locateObjectPtr(PNO(controlid));
   
   //06072004 releaseGridMemory(objPtr);
 
        
 //start additions 06072004  
   
   //free item data
   if(objPtr->itemData)  
   {
     MemPtrFree(objPtr->itemData);
     objPtr->itemData=0;
   }   
   
   
  
   //free cell text ptrs
   if(objPtr->gridContent)  
   {
         freeCellContents(objPtr);
        
      
        
        MemPtrFree(objPtr->gridContent); 
        objPtr->gridContent=0;      
   }
   /*
   if(objPtr->colInfo!=0) 
   {
       for(col=0;col<objPtr->cols;++col)
		{
		    cptr=locateGridColInfo(objPtr, col);   
		    if(cptr->format!=0) MemPtrFree(cptr->format);   
		    cptr->format=0;   
		    
		     
	   }
	  if(objPtr->colInfo) MemPtrFree(objPtr->colInfo);
	  objPtr->colInfo = 0;
   }
   */
   //initializeGrid(objPtr,FrmGetActiveForm());
   objPtr->numItems=0;
   objPtr->howManyColsInBind = 0;
    objPtr->gridContent=MemHandleLock(MemHandleNew(4*objPtr->visibleRows*objPtr->cols)); 
    objPtr->itemData   =MemHandleLock(MemHandleNew(4*objPtr->visibleRows));
    
    for(row=0;row<objPtr->visibleRows;++row)
   {
       for(col=0;col<objPtr->cols;++col)
       {
	       //p =MemHandleLock(MemHandleNew(2));
	       //StrCopy(p ,blankText);
           *(gridCellPtr(objPtr,row,col))=0; 
           //TblSetItemFont((TableType*)FrmGetObjectPtr(FrmGetFormPtr (objPtr->frmId),objPtr->index),row,col,0);        //06072004 
       }
   } 
   
//end of additions 06072004         
   //if in "before draw" rtn, don't redraw the grid
   if(PNO(typeOfScript)=='b') gridFormat(  objPtr ); 
   else                       redrawGrid(objPtr);
#else
   objPtr=locateObjectPtr(pnoP, PNO(controlid));
   
   //06072004 releaseGridMemory(objPtr);
 
        
 //start additions 06072004  
   
   //free item data
   if(objPtr->itemData)  
   {
     MemPtrFree((MemPtr) ByteSwap32(objPtr->itemData));
     objPtr->itemData=0;
   }   
   
   
  
   //free cell text ptrs
   if(objPtr->gridContent)  
   {
         freeCellContents(objPtr);
        
      
        
        MemPtrFree((MemPtr) ByteSwap32(objPtr->gridContent)); 
        objPtr->gridContent=0;      
   }
   /*
   if(objPtr->colInfo!=0) 
   {
       for(col=0;col<objPtr->cols;++col)
		{
		    cptr=locateGridColInfo(objPtr, col);   
		    if(cptr->format!=0) MemPtrFree(cptr->format);   
		    cptr->format=0;   
		    
		     
	   }
	  if(objPtr->colInfo) MemPtrFree(objPtr->colInfo);
	  objPtr->colInfo = 0;
   }
   */
   //initializeGrid(objPtr,FrmGetActiveForm());
   objPtr->numItems=0;
   objPtr->howManyColsInBind = 0;
    objPtr->gridContent=MemHandleLock(MemHandleNew(4*objPtr->visibleRows*objPtr->cols));
    objPtr -> gridContent = (char **) ByteSwap32(objPtr -> gridContent);
    objPtr->itemData   =MemHandleLock(MemHandleNew(4*objPtr->visibleRows));
    objPtr -> itemData = (UInt32 *) ByteSwap32(objPtr -> itemData);
    
    for(row=0;row<ByteSwap16(objPtr->visibleRows);++row)
   {
       for(col=0;col<ByteSwap16(objPtr->cols);++col)
       {
	       //p =MemHandleLock(MemHandleNew(2));
	       //StrCopy(p ,blankText);
           *(gridCellPtr(objPtr,row,col))=0; 
           //TblSetItemFont((TableType*)FrmGetObjectPtr(FrmGetFormPtr (objPtr->frmId),objPtr->index),row,col,0);        //06072004 
       }
   } 
   
//end of additions 06072004         
   //if in "before draw" rtn, don't redraw the grid
   if(PNO(typeOfScript)=='b') gridFormat(pnoP,  objPtr ); 
   else                       redrawGrid(pnoP, objPtr);
#endif
        
}



//-------------------------------------------------------------------------------
//   set the text of the selected cell
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridSetSelectedText(FormPtr frm,VoidPtr controlPtr,char* paramPtr)
#else
void gridSetSelectedText(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr,char* paramPtr)
#endif
{
  Int16 row;
  Int16 col;
 
  char dontDisplaySw=0x00;
  
  struct ObjectData *objPtr;
 
//StrPrintF(debug,"setting text=%s",paramPtr);
//SysFatalAlert(debug);   
  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  //find_arg_1();                          // text to assign
  //dontDisplaySw=find_char();             //switch to redisplay grid or not
#ifdef __MC68K__
  objPtr=locateObjectPtr(PNO(controlid));      
 
  row=objPtr->currentRow;
  col=objPtr->currentCol;
  commonGridSetText(objPtr,row,col,dontDisplaySw,paramPtr);
#else
  objPtr=locateObjectPtr(pnoP, PNO(controlid));      
 
  row=ByteSwap16(objPtr->currentRow);
  col=ByteSwap16(objPtr->currentCol);
  commonGridSetText(pnoP, objPtr,row,col,dontDisplaySw,paramPtr);
#endif
 
}

//-------------------------------------------------------------------------------
//   set the text for a given row & col
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridSetCellMatrix(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
#else
void gridSetCellMatrix(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr,double* paramPtr)
#endif
{
  
  struct ObjectData *objPtr;
  Int16 row;
  Int16 col;
#ifndef __MC68K__
  Arg arg1;
#endif
 
  char dontDisplaySw=0x00;

  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
#ifdef __MC68K__
  objPtr=locateObjectPtr(PNO(controlid));
  row=*paramPtr-1;        //row
#else
  objPtr = locateObjectPtr(pnoP, PNO(controlid));
  row=ReadUnaligned64((char *)paramPtr)-1;        //row
#endif
  
#ifdef __MC68K__ 
  col=find_integ_arg()-1;        //column
  find_arg_1();                  //value
//StrPrintF(debug,"set cell text row=%d col=%d s=%s",row,col,arg1_val);
//SysFatalAlert(debug);
  if(arg1->kind!='s') 
#else
  col=find_integ_arg(pnoP)-1;        //column
  find_arg_PNO(pnoP, &arg1);                  //value
//StrPrintF(debug,"set cell text row=%d col=%d s=%s",row,col,arg1_val);
//SysFatalAlert(debug);
  if(arg1.dataElem->kind!='s') 
#endif
              commonErrorWrongType("CellMatrix");
  //dontDisplaySw=find_char();  //0x01=no display 0x00=display
//StrPrintF(debug,"going to commonSetText  donDisplay=%c",dontDisplaySw);
//SysFatalAlert(debug);
#ifdef __MC68K__
  commonGridSetText(objPtr,row,col,dontDisplaySw,arg1_val);
#else
  commonGridSetText(pnoP, objPtr,row,col,dontDisplaySw,arg1.val);
#endif
}  
//-------------------------------------------------------------------------------
//  remove a specified row from the grid
//-------------------------------------------------------------------------------

#ifdef __MC68K__
void gridDelete(FormPtr frm,VoidPtr controlPtr)
#else
void gridDelete(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr)
#endif
{
 
  Int16 row;
  struct ObjectData *objPtr;
 
  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
#ifdef __MC68K__
  objPtr=locateObjectPtr(PNO(controlid));  
  row=find_integ_arg()-1;
#else
  objPtr = locateObjectPtr(pnoP, PNO(controlid));
  row=find_integ_arg(pnoP)-1;
#endif
//StrPrintF(debug,"deleteingf row=%d",row);
//dbug(debug);
#ifdef __MC68K__
  gridCommonRemoveRow(objPtr, PNO(controlid), row);
#else
  gridCommonRemoveRow(pnoP, objPtr, PNO(controlid), row);
#endif
//SysFatalAlert("back from common delete -- redrawing");
#ifdef __MC68K__
  if(PNO(typeOfScript)!='b')  redrawGrid(objPtr);
#else
  if(PNO(typeOfScript)!='b')  redrawGrid(pnoP, objPtr);
#endif
//SysFatalAlert("leaving delete code");
}

//-------------------------------------------------------------------------------
//  common row removal
//-------------------------------------------------------------------------------
#ifdef __MC68K__
Int16 gridCommonRemoveRow(struct ObjectData *objPtr, Int16 controlid,Int16 row)        
#else
Int16 gridCommonRemoveRow(PNOBlock *pnoP, struct ObjectData *objPtr, Int16 controlid,Int16 row)        
#endif
{
  
  int col;
  
   
  VoidPtr op;
  VoidPtr np;

   if( objPtr->howManyColsInBind==0)               //can only remove if not db bound
   {
      if(!isGridRowValid(objPtr,row) )
      {
           
          return;                           //exit if row invalid
      }
       
       
#ifdef __MC68K__     
      for(col=objPtr->howManyColsInBind;col<objPtr->cols;++col)
#else
      for(col=ByteSwap16(objPtr->howManyColsInBind);col<ByteSwap16(objPtr->cols);++col)
#endif
      {
          if(*(gridCellPtr(objPtr,row,col)))
          {
              MemPtrFree(*(gridCellPtr(objPtr,row,col))); 
          }  
 
      }
#ifdef __MC68K__
       if (objPtr->numItems>(row+1))
#else
	  if (ByteSwap16(objPtr -> numItems) > (row + 1))
#endif
      {
         //handle remaining items

#ifdef __MC68K__ 
          op=(char*)(objPtr->itemData)+4*(row+1);
#else
          op=(char*)ByteSwap32(objPtr->itemData)+4*(row+1);
#endif
         np=(char*)op-4;
#ifdef __MC68K__
         MemMove(np,op,(objPtr->numItems-(row+1))*4);
#else
         MemMove(np,op,(ByteSwap16(objPtr->numItems)-(row+1))*4);
#endif     
 
#ifdef __MC68K__ 
         (char*)op=(char*)(objPtr->gridContent)
                  +4*(row+1)*(objPtr->cols-objPtr->howManyColsInBind); 
         (char*)np=((char*)op
                  -4*(objPtr->cols-objPtr->howManyColsInBind));                  
         MemMove(np,op,
            (objPtr->numItems-(row+1))*4*(objPtr->cols-objPtr->howManyColsInBind));
#else
         (char*)op=(char*)ByteSwap32(objPtr->gridContent)
                  +4*(row+1)*(ByteSwap16(objPtr->cols)
                  	-ByteSwap16(objPtr->howManyColsInBind)); 
         (char*)np=((char*)op
                  -4*(ByteSwap16(objPtr->cols)-ByteSwap16(objPtr->howManyColsInBind)));                  
         MemMove(np,op,
            (ByteSwap16(objPtr->numItems)-(row+1))*4
            *(ByteSwap16(objPtr->cols)-ByteSwap16(objPtr->howManyColsInBind)));
#endif
 
        
    
      }

#ifdef __MC68K__
       if( objPtr->numItems>1)  
      {
           objPtr->gridContent=(char**)(resizePtr( (void**)objPtr->gridContent,
                            -4*(objPtr->cols-objPtr->howManyColsInBind)));                      
      }
      else
      {
         for(col=0;col<(objPtr->cols-objPtr->howManyColsInBind);++col)
	    {
 	        np=MemHandleLock(MemHandleNew(2 ));
	        *((char*)np)=' ';
	        *((char*)np+1)=0x00;
            *((char**)( (char*)(objPtr->gridContent)+4*col))=np; 
	    }
      }
       objPtr->numItems-=1;       
      if (objPtr->firstRow>=objPtr->numItems)
          objPtr->firstRow=objPtr->numItems-1;
#else
       if(ByteSwap16(objPtr->numItems)>1)  
      {
           objPtr->gridContent=(char**)(resizePtr( (void**)ByteSwap32(objPtr->gridContent),
                            -4*(ByteSwap16(objPtr->cols)-ByteSwap16(objPtr->howManyColsInBind))));                      
		   objPtr -> gridContent = (MemPtr)ByteSwap32(objPtr -> gridContent);
      }
      else
      {
         for(col=0;col<(ByteSwap16(objPtr->cols)-ByteSwap16(objPtr->howManyColsInBind));++col)
	    {
 	        np=MemHandleLock(MemHandleNew(2 ));
	        *((char*)np)=' ';
	        *((char*)np+1)=0x00;
            *((char**)( (char*)ByteSwap32(objPtr->gridContent)+4*col))=np; 
	    }
      }
      
       objPtr->numItems = ByteSwap16(objPtr -> numItems) - 1;
       objPtr -> numItems = ByteSwap16(objPtr -> numItems);       
      if (ByteSwap16(objPtr->firstRow)>=ByteSwap16(objPtr->numItems))
      {
          objPtr->firstRow=ByteSwap16(objPtr->numItems)-1;
          objPtr -> firstRow = ByteSwap16(objPtr->numItems);
	  }
#endif
      
  }
 }

//------------------------------------------------------------------------------- 
//    bind grid to database   
//-------------------------------------------------------------------------------
#ifdef __MC68K__
Int16 gridBindToDatabase(FormPtr frm,VoidPtr controlPtr)
#else
Int16 gridBindToDatabase(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr)
#endif
{
     MemHandle           newContentHandle;   //added 08152004
     char*               dbName;
     Int16               logvarNo;
     struct ObjectData * objPtr;
     struct gridColInfo* cptr;
     Int16               nBound=0;          //#cols bound to db
     struct dbType *     db;  //database ptr 
     Int16               err;
     struct dbField *    dbFld;
     Boolean             dbWasOpened;
     Int32               whereClause;
     UInt16      		 flags;
     UInt16        		 dbRecNo;
     UInt32       		 newLength;
     DmOpenRef           dbr;
     Int16               colNo;
     Int16 				 fldNo;
//SysFatalAlert("bind 0");

     PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
#ifdef __MC68K__
     objPtr = locateObjectPtr(PNO(controlid)); 
#else
     objPtr = locateObjectPtr(pnoP, PNO(controlid));
#endif
     objPtr->refreshFromDatabase=true;
     objPtr->numItems=0;
     objPtr->firstRow=0;     

#ifdef __MC68K__
     objPtr->dbNo=   find_integer()-1;
     PNO(dbNo)=objPtr->dbNo;
#else
	 PNO(dbNo) = find_integer(pnoP);
	 objPtr -> dbNo = ByteSwap16(PNO(dbNo))-1;
#endif
//StrPrintF(debug,"got dbno=%d",dbNo);
//SysFatalAlert(debug);

#ifdef __MC68K__
     db=getDatabasePtr();
#else
	 db = getDatabasePtr(pnoP);
#endif
//StrPrintF(debug,"entering 'bind' --instr_ctr=%u",instr_ctr);
//SysFatalAlert(debug);
//SysFatalAlert("bind 1");    
     while(1)   //for each db fld bound to database
     {
//SysFatalAlert("bind 2");  
#ifdef __MC68K__  
         fldNo=find_integer();
#else
		 fldNo=find_integer(pnoP);
#endif
         if(fldNo==1000) break;
#ifdef __MC68K__
         if(++nBound >  objPtr->cols)
#else
	     if (++nBound > ByteSwap16(objPtr -> cols))
#endif
         {
             //SysFatalAlert("Trying to bind more db fields to grid than there are columns of the grid.");
             return(0);
         }    
//SysFatalAlert("bind 3");               
         //set flds of grid column 
         cptr=locateGridColInfo(objPtr, nBound-1);
#ifdef __MC68K__            
         cptr->dbColNo=fldNo;
         cptr->dbSupplied=true;              
    }
    
    objPtr->howManyColsInBind =nBound; 
#else
		cptr->dbColNo = ByteSwap16(fldNo);
		cptr -> dbSupplied = true;
    }
    
    objPtr->howManyColsInBind = ByteSwap16(nBound); 
#endif

    
    if(db->openSw!='o') 
    {
//SysFatalAlert("bind 4");    
         dbWasOpened=true;
         if(! gridOpenDb(db))
         {
#ifdef __MC68K__
           dbName=MemHandleLock(db->hName);
           StrPrintF(debug,"The database '%s' linked to a bound grid cannot be opened",dbName);
           MemHandleUnlock(db->hName);
           MiscFatalAlert(debug);
#else
		   {
		   	char debug[100];
		   	char *d = debug;
            dbName=MemHandleLock((MemHandle) ByteSwap32(db->hName));
		   	strcpy(d, "The database '");
		   	while (*d) ++d;
		   	strcpy(d, dbName);
		   	while (*d) ++d;
		   	strcpy(d, "linked to a bound grid cannot be opened");
            MemHandleUnlock((MemHandle) ByteSwap32(db->hName));
            MiscFatalAlert(debug);
		   }
#endif
           goto skipWhere;
         }  
    }
    dbr=db->dm;
#ifndef __MC68K__
	dbr = (DmOpenRef) ByteSwap32(dbr);
#endif
    whereClause=PNO(instr_ctr);
//SysFatalAlert("after whereclause");    
    if(*((char*)PNO(codePtr)+PNO(instr_ctr))==0x5c)   //if a where clause
    {
//SysFatalAlert("there is a where clause");
//StrPrintF(debug,"there is a where clause --instr_ctr=%u",instr_ctr);
//SysFatalAlert(debug);
        objPtr->bindToDbHasWhereClause=true;   
    }
//SysFatalAlert("bind 5");   
//StrPrintF(debug,"no recs=%d",DmNumRecords(dbr));
//SysFatalAlert(debug);
    if( DmNumRecords(dbr) )
    {
//SysFatalAlert("6");
       objPtr->numItems=0;
       for(dbRecNo=0; dbRecNo < DmNumRecords(dbr); ++dbRecNo )  //step thru all records
       {
//SysFatalAlert("proc rec 1"); 
          DmRecordInfo(dbr,dbRecNo,&flags,NIL,NIL);
          if(flags & 0x80) continue;              //skip -- it's a delet4ed record
//SysFatalAlert("proc rec 2");            
          
          if(*((char*)PNO(codePtr)+PNO(instr_ctr))==0x5c)   //if a where clause
          {
//SysFatalAlert("executing where clause");
#ifdef __MC68K__
           gridSetDatabaseFields(db,dbr,dbRecNo);
#else
           gridSetDatabaseFields(pnoP, db,dbr,dbRecNo);
#endif
            db->LastDbRecordRead=dbRecNo+1;  
#ifndef __MC68K__
			db -> LastDbRecordRead = ByteSwap16(db -> LastDbRecordRead);
#endif
            PNO(instr_ctr)+=3;     
#ifdef __MC68K__
            executeSomeCode(); 
#else
			{
				// executeSomeCode(pnoP);
				UInt16 oldExCodeLevel = PNO(exCodeLevel);
				++PNO(exCodeLevel);
				((*PNO(mainPNOP))(PNO(emulStateP), pnoP, PNO(call68KFuncP)));
				PNO(exCodeLevel) = oldExCodeLevel;
			}
#endif

#ifdef __MC68K__               
            logvarNo=find_integer();
#else
			logvarNo=find_integer(pnoP);
#endif
               
            if(PNO(logic_var)[logvarNo] == 0)
            {
//StrPrintF(debug,"DID NOT select rec=%dVar=%d  log", dbRecNo+1,logvarNo);
//SysFatalAlert(debug);
                  goto recordAgain;  //skip -- record did not meet where clause
            }      
          }

//StrPrintF(debug,"selected rec=%d logVarNo=%d", dbRecNo+1,logvarNo);
//SysFatalAlert(debug);                          
        
          //add new row's user data
#ifdef __MC68K__
          if((MemPtrSize(objPtr->itemData)/4) <= (objPtr->numItems)) 
          {
              objPtr->itemData=resizePtr(objPtr->itemData,400);
          }
          *((ULong*)((char*)(objPtr->itemData)+4*(objPtr->numItems )))=dbRecNo+1;  //02062004 modified 
#else
          if((MemPtrSize((MemPtr) ByteSwap32(objPtr->itemData))/4) <= 
          	ByteSwap16(objPtr->numItems)) 
          {
              objPtr->itemData=resizePtr((MemPtr)ByteSwap32(objPtr->itemData),400);
		  	  objPtr -> itemData = (MemPtr)ByteSwap32(objPtr -> itemData);
          }
          WriteUnaligned32(((ULong*)((char*)ByteSwap32(objPtr->itemData)+4*ByteSwap16(objPtr->numItems))), dbRecNo+1);  //02062004 modified 
#endif
          //add new row's cell content
#ifdef __MC68K__
          if( (objPtr->cols) > (objPtr->howManyColsInBind))
          {
            if(objPtr->gridContent==0)
            {
                objPtr->gridContent=MemHandleLock( MemHandleNew(4*(objPtr->cols-objPtr->howManyColsInBind))); 
#else
          if( ByteSwap16(objPtr->cols) > ByteSwap16(objPtr->howManyColsInBind))
          {
            if(objPtr->gridContent==0)
            {
                objPtr->gridContent=MemHandleLock( MemHandleNew(4*(ByteSwap16(objPtr->cols)-ByteSwap16(objPtr->howManyColsInBind)) )); 
				objPtr -> gridContent = (MemPtr) ByteSwap32(objPtr -> gridContent);
#endif
            }
            else
            {
#ifdef __MC68K__
                objPtr->gridContent=resizePtr(objPtr->gridContent,4*(objPtr->cols-objPtr->howManyColsInBind));      
#else
                objPtr->gridContent=resizePtr((MemPtr)ByteSwap32(objPtr->gridContent),
                	4*(ByteSwap16(objPtr->cols)-ByteSwap16(objPtr->howManyColsInBind)));      
				objPtr -> gridContent = (MemPtr) ByteSwap32(objPtr -> gridContent);
#endif     
            }
#ifdef __MC68K__
            for(colNo=objPtr->howManyColsInBind;colNo<objPtr->cols;++colNo)
            {
               newLength=4l*((long) ( (objPtr->numItems*(objPtr->cols-objPtr->howManyColsInBind) 
               	+ colNo-objPtr->howManyColsInBind )));
               *((VoidPtr*)((char*)(objPtr->gridContent)+newLength))=0;                                           
            }
#else
            for(colNo=ByteSwap16(objPtr->howManyColsInBind);colNo<ByteSwap16(objPtr->cols);++colNo)
            {
               newLength=4l*((long) ( (ByteSwap16(objPtr->numItems)*
               	(ByteSwap16(objPtr->cols)-ByteSwap16(objPtr->howManyColsInBind)) 
               	+ colNo-ByteSwap16(objPtr->howManyColsInBind) )));
               *((VoidPtr*)((char*)ByteSwap32(objPtr->gridContent)+newLength))=0;                                           
            }
#endif 
          }  
 
#ifdef __MC68K__
          objPtr->numItems+=1;
#else
		  {
		  	Int16 t = objPtr->numItems;
		  	t = ByteSwap16(t);
		  	++t;
		  	objPtr -> numItems = ByteSwap16(t);
		  }
#endif
recordAgain:      
          PNO(instr_ctr)=whereClause;  //reposition to where clause
      }  
    } 
//SysFatalAlert("processed all db recs"); 
    if (dbWasOpened)  commonDbcloseLogic(db);   
skipWhere:   
    //skip where clause code if there
    if(*((char*)PNO(codePtr)+PNO(instr_ctr))==0x5c)   //skip where clause
    {
//SysFatalAlert("skipping 5c at end lof load");
          PNO(instr_ctr) += 1;
#ifdef __MC68K__               
		  PNO(instr_ctr) = find_offset();
#else
          PNO(instr_ctr) =  find_offset(pnoP); 
#endif
//StrPrintF(debug,"leaving 'bind' --instr_ctr=%u",instr_ctr);
//SysFatalAlert(debug);            
    } 
   
        
    if(PNO(typeOfScript)=='b') 
    {
#ifdef __MC68K__
        gridFormat( objPtr ); 
#else
		gridFormat(pnoP, objPtr);
#endif
    }
    else
    {
#ifdef __MC68K__
        redrawGrid(objPtr);
#else
		redrawGrid(pnoP, objPtr);
#endif
    }
  
}

#ifdef __MC68K__
//-------------------------------------------------------------------------------
//   
//-------------------------------------------------------------------------------
struct dbField *  locateDbFieldPtr(struct dbType*db)
{
    struct dbField*cptr;
    char*p; 
    int col;
     
     
 
                 find_arg_5();                
                 if(arg5==0)  return(0);
                 for (col=0;col<db->noFields;++col)   
                 {
                     cptr=setDbField(db,col);
                     p=MemHandleLock(cptr->hName);
//StrPrintF(debug,"Comparing colnames [%s] to [%s]",arg5_val,p);
//SysFatalAlert(debug);
                     if (StrCaselessCompare(arg5_val,p)==0)
                     {
//SysFatalAlert("colnames match");
                             MemHandleUnlock(cptr->hName);
                             return(setDbField(db,col));
                     }
                     MemHandleUnlock(cptr->hName);
                } 
                StrPrintF(debug,"Error,  used invalid column name = %s",arg5_val);
                MiscFatalAlert(debug);
                return( (struct dbField * )null_ptr);
      
}    
//-------------------------------------------------------------------------------
//   
//-------------------------------------------------------------------------------
  
void ScrollGrid(TableType* grid ,Int16 idx, Int16 lines)
{
    struct ObjectData *objPtr;

#ifdef __MC68K__ 
    objPtr=locateObjectPtr(FrmGetObjectId(FrmGetActiveForm(),idx));
    objPtr->firstRow=objPtr->firstRow+lines;    //noLines may be + or -
    
    if(objPtr->firstRow<0) objPtr->firstRow=0;    
    if (objPtr->firstRow>(objPtr->numItems-1)) objPtr->firstRow=objPtr->numItems-1;   
    objPtr->refreshFromDatabase=true;
#else
    objPtr=locateObjectPtr(FrmGetObjectId(FrmGetActiveForm(),idx));
    objPtr->firstRow=ByteSwap16(objPtr->firstRow)+lines;    //noLines may be + or -
    
    if(objPtr->firstRow<0) objPtr->firstRow=0;    
    if (objPtr->firstRow>(ByteSwap16(objPtr->numItems)-1)) 
    	objPtr->firstRow=ByteSwap16(objPtr->numItems)-1;   
    objPtr -> firstRow = ByteSwap16(objPtr->firstRow);
    objPtr->refreshFromDatabase=true;
#endif
                              
    redrawGrid( objPtr);                         
}
#endif

//-------------------------------------------------------------------------------
//  add a row to a grid
//-------------------------------------------------------------------------------

#ifdef __MC68K__
void gridAdd(FormPtr frm,VoidPtr controlPtr)
#else
void gridAdd(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr)
#endif
{
  struct ObjectData *objPtr; 
  int stat;
 

  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
#ifdef __MC68K__
  objPtr=locateObjectPtr(PNO(controlid));                 //locate our own info about this table display object
  stat=gridCommonAddRow( objPtr, PNO(controlid));
#else
  objPtr = locateObjectPtr(pnoP, PNO(controlid));
  stat=gridCommonAddRow( objPtr, PNO(controlid));
#endif
 

#ifdef __MC68K__
  if(PNO(typeOfScript)!='b')  redrawGrid(objPtr);
#else
  if(PNO(typeOfScript)!='b')  redrawGrid(pnoP, objPtr);
#endif
    
}

Int16 gridCommonAddRow(struct ObjectData *objPtr, int controlid)
{
   VoidPtr p;
   
  VoidHand theHand;
  char * textP;
  char blankText[]=" ";
   Err err;
  
  Int16 row;
  Int16 col;
  Int16 res;
        
  if( objPtr->howManyColsInBind==0)                     //can only add rows to non-bound grid
  {
   
#ifdef __MC68K__
    if( (calcFreeMemory()<4*(objPtr->cols-objPtr->howManyColsInBind)*(objPtr->numItems+1))
    ||  (calcFreeMemory()<(4*(objPtr->numItems+1))))
#else
    if( (calcFreeMemory()<4*(ByteSwap16(objPtr->cols)-ByteSwap16(objPtr->howManyColsInBind))
    	*(ByteSwap16(objPtr->numItems)+1))
    ||  (calcFreeMemory()<(4*(ByteSwap16(objPtr->numItems)+1))))
#endif
    {
memAllocError:
          
           misc_text_abort("Not enough memory to load grid data");
        
    }    
    //expand grid content to handle another row of col ptrs
#ifdef __MC68K__
    if(!objPtr->gridContent)
    {
       objPtr->gridContent=MemHandleLock(MemHandleNew(4*(objPtr->numItems+1)*(objPtr->cols-objPtr->howManyColsInBind))); 
    }
    else
    {
       objPtr->gridContent=resizePtr( objPtr->gridContent, 4*(objPtr->cols-objPtr->howManyColsInBind) );                         
    }
#else
    if(!objPtr->gridContent)
    {
       objPtr->gridContent=
       	MemHandleLock(MemHandleNew(4*(ByteSwap16(objPtr->numItems)+1)
       		*(ByteSwap16(objPtr->cols)-ByteSwap16(objPtr->howManyColsInBind)))); 
    }
    else
    {
       objPtr->gridContent=resizePtr((MemPtr)ByteSwap32(objPtr->gridContent), 
       	4*(ByteSwap16(objPtr->cols)-ByteSwap16(objPtr->howManyColsInBind)) );                         
    }
    objPtr -> gridContent = (MemPtr) ByteSwap32(objPtr -> gridContent);
#endif


#ifdef __MC68K__    
    row=objPtr->numItems;
    objPtr->numItems = row + 1;
#else
    row=ByteSwap16(objPtr->numItems);
    objPtr->numItems = ByteSwap16(row + 1);
#endif
      
#ifdef __MC68K__    
     for(col=objPtr->howManyColsInBind;col<objPtr->cols;++col)
     {
       p=gridCellPtr(objPtr,row,col);
       *((VoidPtr*)p)=0;
    }


    if((MemPtrSize(objPtr->itemData) ) <= 4*objPtr->numItems) 
    {
       objPtr->itemData=resizePtr(objPtr->itemData, 500);
 
    }
 
    *((ULong*)((char*)(objPtr->itemData)+4*objPtr->numItems))=0l; //set item data to 0
 
                       
    res=objPtr->numItems;
#else
     for(col=ByteSwap16(objPtr->howManyColsInBind);col<ByteSwap16(objPtr->cols);++col)
     {
       p=gridCellPtr(objPtr,row,col);
       *((VoidPtr*)p)=0;
    }


    if((MemPtrSize((MemPtr) ByteSwap32(objPtr->itemData)) ) <= 
    	4*ByteSwap16(objPtr->numItems)) 
    {
       objPtr->itemData=resizePtr((MemPtr) ByteSwap32(objPtr->itemData), 500);
       objPtr -> itemData = (MemPtr) ByteSwap32(objPtr -> itemData);
 
    }
 
    *((ULong*)((char*)ByteSwap32(objPtr->itemData)+4*ByteSwap16(objPtr->numItems)))=0l; //set item data to 0
 
                       
    res=ByteSwap16(objPtr->numItems);
#endif                   
 
    return(res);
  }
}

#ifdef __MC68K__
void gridShowGridLines( FormPtr frm,VoidPtr controlPtr )
{
      struct ObjectData * objPtr;
            
      PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
      objPtr=locateObjectPtr(PNO(controlid)); 
  

      objPtr->wantGridLines = 'y';
}
void gridHideGridLines( FormPtr frm,VoidPtr controlPtr )
{
      struct ObjectData * objPtr;
 
      PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));

      objPtr=locateObjectPtr(PNO(controlid)); 
  
    
      objPtr->wantGridLines = 'n';
}
#else
void gridShowGridLines(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr )
{
      struct ObjectData * objPtr;
      
      PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
      objPtr=locateObjectPtr(pnoP, PNO(controlid)); 
  

      objPtr->wantGridLines = 'y';
}
void gridHideGridLines(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr )
{
      struct ObjectData * objPtr;
      
      PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
      objPtr=locateObjectPtr(pnoP, PNO(controlid)); 
  
    
      objPtr->wantGridLines = 'n';
}
#endif

//------------------------------------------------------------------------------- 
//     record the type of column format to use     
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridColType(FormPtr frm,VoidPtr controlPtr )
#else
void gridColType(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr )
#endif
{
  char oldColumnType;	// 050104
  Int16  col;
   char* textP;	// 050104
		    Int16 rowX;	// 050104
		    Int16 colX; // 050104
  char colType;
  struct gridColInfo* cptr;
  struct ObjectData * objPtr;
#ifndef __MC68K__
  Arg arg1, arg3;
#endif;
 
#ifdef __MC68K__
  col=find_integ_arg()-1;
#else
  col = find_integ_arg(pnoP) - 1;
#endif   
  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  
#ifdef __MC68K__
  objPtr=locateObjectPtr(PNO(controlid));   
  find_arg_1();                        //type
  find_arg_3();                        //format string                       
#else
  	objPtr=locateObjectPtr(pnoP, PNO(controlid));   
	find_arg_PNO(pnoP, &arg1);
	find_arg_PNO(pnoP, &arg3);
#endif
  
//StrPrintF(debug,"col=%d type=%s  format=%s",col,arg1_val,arg3_val);
//SysFatalAlert(debug);  
  if(isGridColumnValid(objPtr,col))
  {
    cptr=locateGridColInfo(objPtr, col);            
	oldColumnType=cptr->type;
#ifdef __MC68K__
    if(cptr->format != 0) MemPtrFree(cptr->format);
    cptr->format=MemHandleLock(MemHandleNew(StrLen(arg3_val)+1 )); 
    StrCopy(cptr->format,arg3_val);             
    if(StrCaselessCompare(arg1_val,"numeric")==0)
    {
        cptr->type='n';
        goto ok;
    }
    if(StrCaselessCompare(arg1_val,"checkbox")==0) 
    {
        cptr->type='c';
        goto ok;
    }
    if(StrCaselessCompare(arg1_val,"date")==0) 
    {
        cptr->type='d';
        goto ok;
    }
    if(StrCaselessCompare(arg1_val,"time")==0) 
    {
        cptr->type='t';
        goto ok;
    }
    if(StrCaselessCompare(arg1_val,"text")==0) 
    {
//StrPrintF(debug,"setting col=%d to type=0xff",col+1);
//SysFatalAlert(debug);       
        cptr->type='s';
        goto ok;
    }
#else
    if(cptr->format != 0) MemPtrFree((MemPtr) ByteSwap32(cptr->format));
    cptr->format=MemHandleLock(MemHandleNew(StrLen(arg3.val)+1 )); 
    StrCopy(cptr->format,arg3.val);
    cptr -> format = (char *)ByteSwap32(cptr -> format);
                 
    if(StrCaselessCompare(arg1.val,"numeric")==0)
    {
        cptr->type='n';
        goto ok;
    }
    if(StrCaselessCompare(arg1.val,"checkbox")==0) 
    {
        cptr->type='c';
        goto ok;
    }
    if(StrCaselessCompare(arg1.val,"date")==0) 
    {
        cptr->type='d';
        goto ok;
    }
    if(StrCaselessCompare(arg1.val,"time")==0) 
    {
        cptr->type='t';
        goto ok;
    }
    if(StrCaselessCompare(arg1.val,"text")==0) 
    {
//StrPrintF(debug,"setting col=%d to type=0xff",col+1);
//SysFatalAlert(debug);       
        cptr->type='s';
        goto ok;
    }
#endif

#ifdef __MC68K__
    StrPrintF(debug,"Illegal column type (%s) used",arg1_val);
    SysFatalAlert(debug);
#else
	{
		char debug[100];
		char *d;
		strcpy(debug, "Illegal column type (");
		d = debug;
		while (*d) ++d;
		strcpy(d, arg1.val);
		while (*d) ++d;
		strcpy(debug, ") used");
		SysFatalAlert(debug);
	}
#endif
ok: 
	// begin additions 050104 
  	if( (cptr->type=='s') && (oldColumnType!='s'))
  	{
  	       //changing to text from non-text col type
  	       freeCellContents(objPtr);
  	       
		    
  	}
  	else
  	{
  			if( (cptr->type!='s') && (oldColumnType=='s'))
  			{
  			    //changing to numer from text col type
  			    freeCellContents(objPtr);
  			    
  			}
  	}
  	// end additions 050104
  	
  }
      
}

//-------------------------------------------------------------------------------
//         redraws a grid object
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void redrawGrid(struct ObjectData * objPtr)
#else
void redrawGrid(PNOBlock *pnoP, struct ObjectData * objPtr)
#endif
{
    TableType* grid;
    int i;

    RectangleType bounds;
    
//StrPrintF(debug,"in redraw --hidden=%d",objPtr->hidden);
//SysFatalAlert(debug);
  
#ifdef __MC68K__
	grid=(TableType*)FrmGetObjectPtr(FrmGetFormPtr(objPtr->frmId),objPtr->index);
	
	TblEraseTable((TableType*) FrmGetObjectPtr(FrmGetFormPtr(objPtr->frmId), objPtr->index) );   
#else
	grid=(TableType*)FrmGetObjectPtr(FrmGetFormPtr(ByteSwap16(objPtr->frmId)),
		ByteSwap16(objPtr->index));
	
	TblEraseTable((TableType*) FrmGetObjectPtr(FrmGetFormPtr(ByteSwap16(objPtr->frmId)), 
		ByteSwap16(objPtr->index)) );   
#endif    
        
    // 050104  TblGetBounds (grid, &bounds);
    //bounds.extent.x+=2;
    //bounds.extent.x-=2; 
//SysFatalAlert("past erase tbl");
	objPtr->refreshFromDatabase=true;
	if(! objPtr->hidden )
	{
#ifdef __MC68K__
	 	gridFormat( objPtr );      
#else
		gridFormat(pnoP, objPtr);
#endif
//SysFatalAlert("back from gridFormat");

#ifdef __MC68K__    
    	TblDrawTable((TablePtr)(FrmGetObjectPtr(FrmGetFormPtr(objPtr->frmId),objPtr->index))); 
//SysFatalAlert("after tableDraw");    
    	if( (objPtr->currentRow>=objPtr->firstRow)&&((objPtr->currentRow-objPtr->firstRow)<objPtr->visibleRows))
        	  TblSelectItem((TableType*)FrmGetObjectPtr(FrmGetFormPtr(objPtr->frmId),objPtr->index),objPtr->currentRow-objPtr->firstRow,objPtr->currentCol);
#else
    	TblDrawTable((TablePtr)(FrmGetObjectPtr(FrmGetFormPtr(ByteSwap16(objPtr->frmId)),
    		ByteSwap16(objPtr->index)))); 
//SysFatalAlert("after tableDraw");
    	if( (ByteSwap16(objPtr->currentRow)>=ByteSwap16(objPtr->firstRow))&&
    		((ByteSwap16(objPtr->currentRow)-ByteSwap16(objPtr->firstRow))<
    			ByteSwap16(objPtr->visibleRows)))
        TblSelectItem((TableType*)FrmGetObjectPtr(FrmGetFormPtr(ByteSwap16(objPtr->frmId)),
        	ByteSwap16(objPtr->index)),ByteSwap16(objPtr->currentRow)
        		-ByteSwap16(objPtr->firstRow),ByteSwap16(objPtr->currentCol));
#endif    
//SysFatalAlert("getting bounds");        
    	TblGetBounds (grid, &bounds);
#ifndef __MC68K__
		 bounds.extent.x = ByteSwap16(bounds.extent.x);
		 bounds.extent.y = ByteSwap16(bounds.extent.y);
#endif
    
    	bounds.extent.x=0;

#ifdef __MC68K__
    	for(i=0;i<objPtr->cols;++i) 
#else
		for(i=0;i<ByteSwap16(objPtr->cols);++i)
#endif
    	{ 
            bounds.extent.x += (locateGridColInfo(objPtr, i))->width+1 ;
   		}
   		bounds.extent.y=0;
#ifdef __MC68K__
    	for(i=0;i<objPtr->visibleRows;++i) 
#else
		for (i = 0; i < ByteSwap16(objPtr->visibleRows); ++i)
#endif
    	{ 
            bounds.extent.y += 12;
   		}      
//SysFatalAlert("DrawingFrame");
//StrPrintF(debug,"bounds.x=%d",bounds.extent.x);
//SysFatalAlert(debug);
    	bounds.extent.x-=1;
    	bounds.extent.y-=1;
#ifndef __MC68K__
		 bounds.extent.x = ByteSwap16(bounds.extent.x);
		 bounds.extent.y = ByteSwap16(bounds.extent.y);
#endif
    	if(objPtr->wantGridLines == 'y'  )  //added 08232004 only draw bounding rectangle if want grids
    	{                //added 08232004

#ifdef __MC68K__
//added following IF on 04242004  modified EMP 050103
		 if( (bounds.topLeft.x+bounds.extent.x) <= (objPtr->origGridBounds.topLeft.x+objPtr->origGridBounds.extent.x))
#else
//added following IF on 04242004
    	 if( (ByteSwap16(bounds.topLeft.x)+ByteSwap16(bounds.extent.x)) 
    	 	<= (ByteSwap16(objPtr->origGridBounds.topLeft.x)+ByteSwap16(objPtr->origGridBounds.extent.x)))

#endif
		//SysFatalAlert("draw frame");
    	WinDrawRectangleFrame(simpleFrame,&bounds);
    	else
    	{
			bounds.topLeft.x = objPtr->origGridBounds.topLeft.x;   //added 06072004 
    		bounds.topLeft.y = objPtr->origGridBounds.topLeft.y;   //added 06072004
#ifdef __MC68K__
    		bounds.extent.x = objPtr->origGridBounds.extent.x -1;     //added 06072004
    		bounds.extent.y = objPtr->origGridBounds.extent.y-1;        //added 06072004
#else
			bounds.extent.x = ByteSwap16(objPtr->origGridBounds.extent.x);
			--bounds.extent.x;
			bounds.extent.x = ByteSwap16(bounds.extent.x);
			
			bounds.extent.y = ByteSwap16(objPtr->origGridBounds.extent.y);
			--bounds.extent.y;
			bounds.extent.y = ByteSwap16(bounds.extent.y);
			
#endif
    		//06072004 WinDrawRectangleFrame(simpleFrame,&objPtr->origGridBounds);  // EMP added 051204 to make demo look good
    		WinDrawRectangleFrame(simpleFrame,&bounds);  //06072004 // EMP added 051204 to make demo look good
		}
		}
    }
    else
    {
/*commented out 06072004
         //grid is hidden
         TblGetBounds (grid, &bounds); //added 02062004
#ifdef __MC68K__
         bounds.extent.x-=1;  //added 02062004
    	 bounds.extent.y-=1;  //added 02062004
//added following IF on 04242004
    	 if( (bounds.topLeft.x+bounds.extent.x-1) <= (objPtr->origGridBounds.topLeft.x+objPtr->origGridBounds.extent.x))
#else
		 bounds.extent.x = ByteSwap16(bounds.extent.x);
		 --bounds.extent.x;
		 bounds.extent.x = ByteSwap16(bounds.extent.x);
		 bounds.extent.y = ByteSwap16(bounds.extent.y);
		 --bounds.extent.y;
		 bounds.extent.y = ByteSwap16(bounds.extent.y);
//added following IF on 04242004  modified EMP 050103

    	 if( (ByteSwap16(bounds.topLeft.x)+ByteSwap16(bounds.extent.x)-1) 
    	 	<= (ByteSwap16(objPtr->origGridBounds.topLeft.x)+ByteSwap16(objPtr->origGridBounds.extent.x)))
#endif
		//SysFatalAlert("erase frame");
         WinEraseRectangleFrame (simpleFrame,&bounds );
    	else
    	WinDrawRectangleFrame(simpleFrame,&objPtr->origGridBounds);  // EMP added 051204 to make demo look good
*/
//start of insertions 06072004
		   	TblGetBounds (grid, &bounds);
    
    	bounds.extent.x=0;
#ifdef __MC68K__
    	for(i=0;i<objPtr->cols;++i) 
    	{ 
            bounds.extent.x += (locateGridColInfo(objPtr, i))->width+1 ;
   		}
#else
    	for(i=0;i<ByteSwap16(objPtr->cols);++i) 
    	{
    		bounds.extent.x = ByteSwap16(bounds.extent.x);
            bounds.extent.x += ByteSwap16((locateGridColInfo(objPtr, i))->width)+1 ;
    		bounds.extent.x = ByteSwap16(bounds.extent.x);
   		}
#endif 		 
   		bounds.extent.y=0;
#ifdef __MC68K__
    	for(i=0;i<objPtr->visibleRows;++i) 
    	{
            bounds.extent.y += 12;
   		}
#else
    	for(i=0;i<ByteSwap16(objPtr->visibleRows);++i) 
    	{
    		bounds.extent.y = ByteSwap16(bounds.extent.y);
            bounds.extent.y += 12;
    		bounds.extent.y = ByteSwap16(bounds.extent.y);
  		}
#endif
//SysFatalAlert("DrawingFrame");
//StrPrintF(debug,"bounds.x=%d",bounds.extent.x);
//SysFatalAlert(debug);

#ifndef __MC68K__
	bounds.extent.x = ByteSwap16(bounds.extent.x);
	bounds.extent.y = ByteSwap16(bounds.extent.y);
#endif
        bounds.extent.x-=1;
    	bounds.extent.y-=1;
#ifndef __MC68K__
	bounds.extent.x = ByteSwap16(bounds.extent.x);
	bounds.extent.y = ByteSwap16(bounds.extent.y);
#endif
#ifdef __MC68K__    	
    	 //added following IF on 04242004
    	 //06072004 if( (bounds.topLeft.x+bounds.extent.x-1) <= (objPtr->origGridBounds.topLeft.x+objPtr->origGridBounds.extent.x))
    	 if( (bounds.topLeft.x+bounds.extent.x) <= (objPtr->origGridBounds.topLeft.x+objPtr->origGridBounds.extent.x))
    	    WinEraseRectangleFrame( simpleFrame,&bounds);
    	else
    	{
    		bounds.topLeft.x = objPtr->origGridBounds.topLeft.x;   //added 06072004 
    		bounds.topLeft.y = objPtr->origGridBounds.topLeft.y;   //added 06072004
    		bounds.extent.x = objPtr->origGridBounds.extent.x -1;     //added 06072004
    		bounds.extent.y = objPtr->origGridBounds.extent.y-1;        //added 06072004
    		//WinEraseRectangleFrame(simpleFrame,&objPtr->origGridBounds);  // EMP added 051204 to make demo look good
    		WinEraseRectangleFrame(simpleFrame,&bounds);  
    	}
#else
    	 //added following IF on 04242004
    	 //06072004 if( (bounds.topLeft.x+bounds.extent.x-1) <= (objPtr->origGridBounds.topLeft.x+objPtr->origGridBounds.extent.x))
    	 if( (ByteSwap16(bounds.topLeft.x)+ByteSwap16(bounds.extent.x)) <= 
    	 	(ByteSwap16(objPtr->origGridBounds.topLeft.x)+ByteSwap16(objPtr->origGridBounds.extent.x)))
    	    WinEraseRectangleFrame( simpleFrame,&bounds);
    	else
    	{
    		bounds.topLeft.x = objPtr->origGridBounds.topLeft.x;   //added 06072004 
    		bounds.topLeft.y = objPtr->origGridBounds.topLeft.y;   //added 06072004
    		bounds.extent.x = ByteSwap16(ByteSwap16(objPtr->origGridBounds.extent.x) -1);     //added 06072004
    		bounds.extent.y = ByteSwap16(ByteSwap16(objPtr->origGridBounds.extent.y)-1);        //added 06072004
    		//WinEraseRectangleFrame(simpleFrame,&objPtr->origGridBounds);  // EMP added 051204 to make demo look good
    		WinEraseRectangleFrame(simpleFrame,&bounds);  
    	}
#endif
//end insertions 06072004
    }
}

//-------------------------------------------------------------------------------
//  
//-------------------------------------------------------------------------------

#ifdef __MC68K__
void gridFormat( struct ObjectData *objPtr)
#else
void gridFormat(PNOBlock *pnoP, struct ObjectData *objPtr)
#endif
{
   TablePtr          grid;
#ifdef __MC68K__
   FormPtr           frmPtr = FrmGetFormPtr(objPtr->frmId);
#else
   FormPtr           frmPtr = FrmGetFormPtr(ByteSwap16(objPtr->frmId));
#endif
   ScrollBarType *   scr=0;
#ifdef __MC68K__
   Int16               idx=objPtr->index;
#else
   Int16			idx = ByteSwap16(objPtr -> index);
#endif
    
   Int16           row;
   Int16           col;
   grid=(TablePtr)(FrmGetObjectPtr(frmPtr,idx));
   //09242003 grid->attr.editable=1;   
//SysFatalAlert("gridFormat----start rows");  
#ifdef __MC68K__
   for(row=0;row<objPtr->visibleRows;++row)
#else
   for(row=0;row<ByteSwap16(objPtr->visibleRows);++row)
#endif
   {
   
         FntSetFont(TblGetItemFont (grid,  row, 0));
         TblSetRowHeight           (grid,row,FntLineHeight()+1);
         TblSetRowUsable           (grid, row,true);
         TblSetRowSelectable       (grid, row,true);
         
                       
#ifdef __MC68K__
	     for(col=0;col<objPtr->cols;++col)
#else
		 for(col=0;col<ByteSwap16(objPtr->cols);++col)
#endif
         {
	         if(row==0)
	         {
//StrPrintF(debug,"setting callback id=%d col=%d",objPtr->id,col);
//SysFatalAlert(debug);
#ifdef __MC68K__
	              TblSetCustomDrawProcedure(grid, col, gridDrawCallback);
#else
				  TblSetCustomDrawProcedure(grid, col, (void *)ByteSwap32(PNO(gridDrawCallback)));
#endif
             }
             TblSetColumnUsable(grid, col,true);
	         TblSetItemStyle   (grid, row,col,customTableItem);
         }
                    
    }
//SysFatalAlert("gridFormat-------done rows");
    objPtr->scrollMin=0;
#ifdef __MC68K__
    objPtr->scrollMax=objPtr->numItems-objPtr->visibleRows;
    if (objPtr->scrollMax<0) objPtr->scrollMax=1;
#else
    objPtr->scrollMax=ByteSwap16(objPtr->numItems)-ByteSwap16(objPtr->visibleRows);
    if (objPtr->scrollMax<0) objPtr->scrollMax=1;
    objPtr->scrollMax = ByteSwap16(objPtr->scrollMax);
#endif   
#ifdef __MC68K__
    if(objPtr->index<(FrmGetNumberOfObjects(FrmGetActiveForm()))-1)
    {
       if(FrmGetObjectType(FrmGetActiveForm(),objPtr->index+1)==frmScrollBarObj)
       {
//SysFatalAlert("yess--format says there is a scrollbar");
                scr=FrmGetObjectPtr(frmPtr,idx+1);   
       }
       else
       {
//SysFatalAlert("no----no scrollbar present");
            scr=0;
       } 
    }   
#else
    if(ByteSwap16(objPtr->index)<(FrmGetNumberOfObjects(FrmGetActiveForm()))-1)
    {
       if(FrmGetObjectType(FrmGetActiveForm(),ByteSwap16(objPtr->index)+1)==frmScrollBarObj)
       {
//SysFatalAlert("yess--format says there is a scrollbar");
                scr=FrmGetObjectPtr(frmPtr,idx+1);   
       }
       else
       {
//SysFatalAlert("no----no scrollbar present");
            scr=0;
       } 
    }   
#endif
#ifdef __MC68K__
    if( (objPtr->firstRow+objPtr->visibleRows)>objPtr->numItems)
	{
	     objPtr->firstRow= objPtr->numItems-objPtr->visibleRows;
	     if(objPtr->firstRow<0) objPtr->firstRow=0;
	}
#else
    if( (ByteSwap16(objPtr->firstRow)+ByteSwap16(objPtr->visibleRows))>ByteSwap16(objPtr->numItems))
	{
	     objPtr->firstRow= ByteSwap16(objPtr->numItems)-ByteSwap16(objPtr->visibleRows);
	     if(objPtr->firstRow<0) objPtr->firstRow=0;
		 objPtr -> firstRow = ByteSwap16(objPtr -> firstRow);
	}
#endif
#ifdef __MC68K__
	if(  (objPtr->numItems)<=objPtr->visibleRows)
#else
	if(  ByteSwap16(objPtr->numItems)<= ByteSwap16(objPtr->visibleRows))
#endif
	{
//SysFatalAlert("hiding scrollbar");
		 if (PNO(romVersion) < 0x03400000)
         {
           if(scr!=0)
           {
              SclSetScrollBar( ((ScrollBarPtr)scr),0,0,0,0);  
           }  
         }
         else     
         {
           if(scr!=0)
           {       
#ifdef __MC68K__  
              FrmHideObject(FrmGetActiveForm(),objPtr->index+1);  
#else
              FrmHideObject(FrmGetActiveForm(),ByteSwap16(objPtr->index)+1);  
#endif
           }  
         } 	                                   
    }
	else
	{
	     if(scr!=0)
         {
//SysFatalAlert("showing scrollbar");
#ifdef __MC68K__
                FrmShowObject(FrmGetActiveForm(),objPtr->index+1); 
	            SclDrawScrollBar(scr);
                SclSetScrollBar(scr, objPtr->firstRow,objPtr->scrollMin,objPtr->scrollMax,objPtr->scrollPagesize); 
#else
                FrmShowObject(FrmGetActiveForm(),ByteSwap16(objPtr->index)+1); 
	            SclDrawScrollBar(scr);
                SclSetScrollBar(scr, ByteSwap16(objPtr->firstRow),
                	ByteSwap16(objPtr->scrollMin),
                	ByteSwap16(objPtr->scrollMax),
                	ByteSwap16(objPtr->scrollPagesize)); 
#endif
         }    
    }
    
}


#ifdef __MC68K__
//-------------------------------------------------------------------------------
//          
//-------------------------------------------------------------------------------
void gridDrawCallback (VoidPtr grid, short row, short col2, RectanglePtr bounds )
{
    
    double d=0;
    double tempDbl;
    char oneChar;
    FontID fntSave;
    struct ObjectData * objPtr;
    struct gridColInfo* cptr;
    
    RectangleType chkBounds;
     
    char *valuePtr;
  
    char workString[256];
    int cnt;
    Int w;
    Int cntThatWillFit;
    Boolean truncFlag;
    char asterisks[50];
 
    char* *cell;
    int coltype;
    int err;
    int i;
    int j;
    int k;
    double val;
    char wk[64];
    int col=col2;
    union 
       {
            FlpDouble q;
            double d;
       } x;
    char s[64];
    FontID oldFontID = FntGetFont();          //08022005
   
    objPtr=locateObjectPtr( FrmGetObjectId (FrmGetActiveForm(),  getGridIndexFromPtr(FrmGetActiveForm(), 
                                                                           (TablePtr)grid)));
    
    FntSetFont(TblGetItemFont ((TablePtr) grid,  row,  col));     
//StrPrintF(debug,"callback %d %d %d %d",bounds->topLeft.x,bounds->topLeft.y,bounds->extent.x,bounds->extent.y);
//SysFatalAlert(debug);
    
     
    if( (bounds->topLeft.x+bounds->extent.x-2) > (objPtr->origGridBounds.topLeft.x+objPtr->origGridBounds.extent.x))
    {
//SysFatalAlert("recognized overflow of x bounds");
    	//user has changed col widths to exceed grid, so restrict to rightmost end of grod bounds
    	chkBounds.topLeft.x = objPtr->origGridBounds.topLeft.x+objPtr->origGridBounds.extent.x - 1;
    	chkBounds.extent.x=0;
    }
    else
    {
        chkBounds.topLeft.x=bounds->topLeft.x;
        //additions 06072004
#ifdef __MC68K__
        if( (chkBounds.topLeft.x + chkBounds.extent.x) > (objPtr->origGridBounds.topLeft.x+objPtr->origGridBounds.extent.x - 1))
        {
        	chkBounds.extent.x = (objPtr->origGridBounds.topLeft.x+objPtr->origGridBounds.extent.x -1 - chkBounds.topLeft.x);
        }
        else
#else
        if( (ByteSwap16(chkBounds.topLeft.x) + ByteSwap16(chkBounds.extent.x)) > 
        	(ByteSwap16(objPtr->origGridBounds.topLeft.x)+ByteSwap16(objPtr->origGridBounds.extent.x) - 1))
        {
        	chkBounds.extent.x = (ByteSwap16(objPtr->origGridBounds.topLeft.x)+
        		ByteSwap16(objPtr->origGridBounds.extent.x) -1 - ByteSwap16(chkBounds.topLeft.x));
			chkBounds.extent.x = ByteSwap16(chkBounds.extent.x);
        }
        else
#endif
        //end additions 06072004
        chkBounds.extent.x=bounds->extent.x;
    }
    
    chkBounds.topLeft.y=bounds->topLeft.y;
    
    chkBounds.extent.y=bounds->extent.y;
   
                          
    
    
    WinSetUnderlineMode( noUnderline);                  
    //04242004 objPtr=locateObjectPtr( FrmGetObjectId (FrmGetActiveForm(),  getGridIndexFromPtr(FrmGetActiveForm(), (TablePtr)grid)));
    if(objPtr->hidden) return;   //02062004

    
    
    cptr=locateGridColInfo(objPtr, col);           
    cptr->width=bounds->extent.x;                     
//SysFatalAlert("callback -- 6");
//StrPrintF(debug,"setting col width=%d",  cptr->width);
//SysFatalAlert(debug);  
//StrPrintF(debug,"drawback   col=%d type=c",col,  cptr->type);
//SysFatalAlert(debug);   
    if( (objPtr->firstRow+row)<objPtr->numItems)
    {
        if(cptr->dbSupplied)
        {
             if(cptr->type=='s')
             {
             	valuePtr=gridTextPtr( objPtr, cptr, row,&workString[0],grid,&coltype);
             }
             else
             {
                 d= gridValue ( objPtr, cptr, row,  grid,&coltype);
                 valuePtr=(char*)(&d);
                 if(valuePtr==0) goto cellEmpty;
             }
        }
        else
        {

             cell= (char* *)((char*)(objPtr->gridContent) + 4*((objPtr->firstRow+row)*(objPtr->cols-objPtr->howManyColsInBind)
                              +(col-objPtr->howManyColsInBind)));     
////if( cptr->type=='s')
//{
//StrPrintF(debug,"callback text -- ptr =%lu",*cell);
//SysFatalAlert(debug);
//} 
             if(*(cell)==0)   goto cellEmpty;
             valuePtr=*((char**)cell);
            
        }
 

        switch(cptr->type)
        {
          
         
          case 'c':   //checkbox  
               //if(StrCompare( valuePtr , "0")==0)
//SysFatalAlert("callback checkbox");
               if(*((double*)valuePtr)==0)
               {
                      oneChar=0x00;    //unchecked               }
               }
               else 
               {
                 oneChar=0x01;    //checked 
               }
               fntSave=FntGetFont();                                        
               FntSetFont((FontID)4);                                       
 
               WinDrawChars(&oneChar,1,bounds->topLeft.x,bounds->topLeft.y);  
               FntSetFont(fntSave);                                          
               w=bounds->extent.x-12;
               cntThatWillFit=StrLen(cptr->format);
               FntCharsInWidth(cptr->format,&w,&cntThatWillFit,&truncFlag);   
               WinDrawChars( cptr->format,cntThatWillFit,bounds->topLeft.x+12,bounds->topLeft.y); 
                                       
  
               break;
         case 'n':    //numeric
//SysFatalAlert("callback numeric");
               DoubleToStr(*((double*)valuePtr),wk);             
 
               commonFormatCode(wk,cptr->format,workString);  
              
               
               //if(cptr->dbSupplied==true)   
              // {
                    w=bounds->extent.x;
                    cntThatWillFit=StrLen(workString);
                    FntCharsInWidth(workString,&w,&cntThatWillFit,&truncFlag);   
                    if(cntThatWillFit<StrLen(workString))
                    {
                        asterisks[0]=0x00;
                        for(i=0;i<StrLen(workString);++i)
                        {
                           StrCat(asterisks,"*");
                           w=bounds->extent.x;
                           cntThatWillFit=StrLen(asterisks);
                           FntCharsInWidth(asterisks,&w,&cntThatWillFit,&truncFlag);   
                           if(cntThatWillFit<i) break; 
                        }
                        asterisks[i]=0x00;
                        WinDrawChars( asterisks,cntThatWillFit,bounds->topLeft.x,bounds->topLeft.y);   
                    }
                    else
                    {
               //WinDrawChars( workString,cntThatWillFit,bounds->topLeft.x,bounds->topLeft.y);
                        //06072004 changed to right justify numeric vcalues in column
                        WinDrawChars( workString,  cntThatWillFit,                         //06072004
                              bounds->topLeft.x+bounds->extent.x - w ,bounds->topLeft.y);//06072004   
                             }
               //}   
               break; 
         case 'd':           //date
               //DoubleToStr(*((double*)valuePtr),wk);             
               //commonFormatCode(wk,cptr->format,workString);  

//DoubleToStr(*((double*)valuePtr), s);
//StrPrintF(debug,"date=%s  ",s);
//SysFatalAlert(debug);
 
               tempDbl=*((double*)valuePtr);
 
               formatDateWithString(&tempDbl, cptr->format,'/', workString);
     
               //if(cptr->dbSupplied==true)   
              // {
                    w=bounds->extent.x;
                    cntThatWillFit=StrLen(workString);
                    FntCharsInWidth(workString,&w,&cntThatWillFit,&truncFlag);   
                    if(cntThatWillFit<StrLen(workString))
                    {
                        asterisks[0]=0x00;
                        for(i=0;i<StrLen(workString);++i)
                        {
                           StrCat(asterisks,"*");
                           w=bounds->extent.x;
                           cntThatWillFit=StrLen(asterisks);
                           FntCharsInWidth(asterisks,&w,&cntThatWillFit,&truncFlag);   
                           if(cntThatWillFit<i) break; 
                        }
                        asterisks[i]=0x00;
                        WinDrawChars( asterisks,cntThatWillFit,bounds->topLeft.x,bounds->topLeft.y);   
                    }
                    else
                    {
                        WinDrawChars( workString,cntThatWillFit,bounds->topLeft.x,bounds->topLeft.y);   
                    }
                    break;
                     
         case 't':           //time      
               formatTimeWithString((double*)valuePtr, cptr->format,'/', workString);
     
               //if(cptr->dbSupplied==true)   
              // {
                    w=bounds->extent.x;
                    cntThatWillFit=StrLen(workString);
                    FntCharsInWidth(workString,&w,&cntThatWillFit,&truncFlag);   
                    if(cntThatWillFit<StrLen(workString))
                    {
                        asterisks[0]=0x00;
                        for(i=0;i<StrLen(workString);++i)
                        {
                           StrCat(asterisks,"*");
                           w=bounds->extent.x;
                           cntThatWillFit=StrLen(asterisks);
                           FntCharsInWidth(asterisks,&w,&cntThatWillFit,&truncFlag);   
                           if(cntThatWillFit<i) break; 
                        }
                        asterisks[i]=0x00;
                        WinDrawChars( asterisks,cntThatWillFit,bounds->topLeft.x,bounds->topLeft.y);   
                    }
                    else
                    {
                        WinDrawChars( workString,cntThatWillFit,bounds->topLeft.x,bounds->topLeft.y);   
                    }
                    break;
                     
               
         case 's':           //text string
                
//SysFatalAlert("callback text");
//StrPrintF(debug,"in callback text=%s",valuePtr);
//SysFatalAlert(debug);               
                    w=bounds->extent.x;
                    cntThatWillFit=StrLen(valuePtr);
                    FntCharsInWidth(valuePtr,&w,&cntThatWillFit,&truncFlag);   
                    WinDrawChars( valuePtr,cntThatWillFit,bounds->topLeft.x, bounds->topLeft.y);   
               
               
               break;    
        }                 

    }
  
cellEmpty:
//SysFatalAlert("callback -- exiting");
   
   
   //draw box araound cell if want a grid
   if(objPtr->wantGridLines == 'n'){}           //08152004
   else                                 //08152004
   WinDrawRectangleFrame( simpleFrame,&chkBounds);          
     
    
    FntSetFont(oldFontID);    //08022005 
    return ;
}
#endif

//-------------------------------------------------------------------------------
//  
//-------------------------------------------------------------------------------
#ifdef __MC68K__
// WARNING!
// Caller is responsible for releasing this pointer!
char* gridTextPtr(struct ObjectData * objPtr,struct gridColInfo* cptr, int row
                 ,char *workString, TableType*grid,   int*coltype)
#else
char* gridTextPtr(PNOBlock *pnoP, struct ObjectData * objPtr,struct gridColInfo* cptr, Int16 row
                 ,char *workString, TableType*grid,   Int16*coltype)
#endif
{
 
  struct dbType *db;
  struct dbField *dbColPtr;
  DmOpenRef dbr;
  unsigned long dbDataOffset;
  VoidHand recHand;
  VoidPtr  recPtr;

  
  Int16 ct;
  Int16 i;
  Int16 j;
  Int16 k; 
  UInt16 shortInt;
  float f;
  char  b[2];  
  ULong ui;
  Long  l;
  ULong index;
  char*dbName;                //insert 02052004
  Boolean dbWasOpened=false;  //insert 02052004
  double val;
  char *valuePtr;
  double t;
  UInt16 flags;
  char wk[128];
  unsigned char tm[3];
  DateType dt;
  struct dataelem  dummy;
  

           //db=setDbPtr(objPtr->dbNo);          
//SysFatalAlert("getTextPtr 1");
#ifdef __MC68K__
           PNO(dbNo)=objPtr->dbNo;
           db=getDatabasePtr();
#else
           PNO(dbNo)=ByteSwap16(objPtr->dbNo);
           db=getDatabasePtr(pnoP);
#endif
           if(db->openSw!='o')
           {
             //02052004 if(gridOpenDb(db)==0) MiscFatalAlert("Database needed for grid cannot be opened.");dbWasOpened=true;
             //begin insertions 02052004
             dbWasOpened = false;
             if(! gridOpenDb(db))
             {
             	MemHandle hName = db -> hName;
#ifndef __MC68K__
				char debug[100];
				hName = (MemHandle)ByteSwap32(hName);
	
#endif
		           dbName=MemHandleLock(hName);
		           StrCopy(debug,"The database linked to a bound grid cannot be opened");
		           MemHandleUnlock(hName);
		           MiscFatalAlert(debug);
		           goto exitNow;
		     }      
           }
           else
           {
           dbWasOpened = true;
           }
             //end insertions 02052004
           dbr=db->dm;
#ifndef __MC68K__
			dbr = (DmOpenRef)ByteSwap32(dbr);
#endif
      
           if(objPtr->bindToDbHasWhereClause) 
           {
#ifdef __MC68K__
                index=*((ULong*)((char*)(objPtr->itemData)+4*(row+objPtr->firstRow)))-1; //02062004 modified
#else
                index=*((ULong*)((char*)ByteSwap32(objPtr->itemData)
                	+4*(row+ByteSwap16(objPtr->firstRow)))); //02062004 modified
                index=ByteSwap32(index);
                --index;
#endif
           }
           else
           {
#ifdef __MC68K__
                     index=row+objPtr->firstRow;      
#else
                     index=row+ByteSwap16(objPtr->firstRow);      
#endif
           }
//StrPrintF(debug,"getTextPtr 2   -- index=%d",index);
//SysFatalAlert(debug);
           if( (index>=DmNumRecords(dbr))
           ||  (DmNumRecords(dbr)==0))
           {
               valuePtr=0;
               goto exitNow;              
           }
//SysFatalAlert("getTextPtr 3");
            
           DmRecordInfo(dbr,index,&flags,NIL,NIL);
           if(flags & 0x80) 
           {
               valuePtr=0;     
               //02052004 return(valuePtr);

               goto exitNow;               //inserted 02052004
           }    
           recHand=DmGetRecord(dbr,index);
#ifdef __MC68K__    
           db->LastDbRecordRead=index+1;
#else
           db->LastDbRecordRead=ByteSwap16(index+1);
#endif
          

#ifdef __MC68K__
           dbColPtr=setDbField(db,cptr->dbColNo);
#else
		   dbColPtr=setDbField(db, ByteSwap16(cptr->dbColNo));
#endif
           recPtr=MemHandleLock(recHand); 
#ifdef __MC68K__         
           dbDataOffset=positionToDbField(db,dbColPtr, recPtr );
#else
           dbDataOffset=positionToDbField(pnoP, db,dbColPtr, recPtr );
#endif
           *coltype=dbColPtr->type;        

//SysFatalAlert("getTextPtr 8");
           switch(*coltype)          
           {
             case dbFldTypeString:  
               valuePtr=(char*)recPtr+dbDataOffset;
               break;
             case dbFldTypeLongInt:  
               MemMove(&ui,(char*)recPtr+dbDataOffset,4);
#ifndef __MC68K__
			   ui = ByteSwap32(ui);
#endif
               val=ui;   
#ifndef __MC68K__
				val = SwapDouble(val);
#endif

               dummy.kind='n';
#ifdef __MC68K__
               dummy.dgt_bef=16;
#else
			   dummy.dgt_bef = ByteSwap16(16);
#endif
               dummy.dgt_aft=0;
               
               goto formatIt;            
               
             case dbFldTypeDouble:   
               MemMove(&val,(char*)recPtr+dbDataOffset,8);
              
               dummy.kind='n';
#ifdef __MC68K__
               dummy.dgt_bef=16;
               dummy.dgt_aft=16;
#else
               dummy.dgt_bef=ByteSwap16(16);
               dummy.dgt_aft=ByteSwap16(16);
#endif
               
formatIt:
               if(cptr->type=='c')
               {
                  if(chkFormatYesNo(&val,cptr->format,workString)!=1)
    	       	  {
#ifdef __MC68K__
     			      DoubleToStr(val,wk);             
#else
     			      DoubleToStr(SwapDouble(val),wk);             
#endif
                      commonFormatCode(wk,cptr->format,workString);   
                   }
               }
               else
               { 
                 if(cptr->type=='n')   
                 {
 #ifdef __MC68K__
     			      DoubleToStr(val,wk);             
#else
     			      DoubleToStr(SwapDouble(val),wk);             
#endif
                      commonFormatCode(wk,"0",workString);    
                 }
                 else misc_format_number(&dummy, &val ,workString);
                   
               }  
               valuePtr=&workString[0];
               break;
             case dbFldTypeDate:     
               MemMove(&val,(char*)recPtr+dbDataOffset,8);
               //val=cvtPalmInternalDateToDouble(&dt);
               misc_format_date(&dummy,&val,workString);   
               valuePtr=&workString[0];
               break;
             case dbFldTypeTime:  
               MemMove(&val,(char*)recPtr+dbDataOffset,8);
               //val=cvtPalmInternalTimeToDouble(&tm[0]);
               misc_format_time(&dummy,&val,workString);    
               valuePtr=&workString[0];
               break;
             case dbFldTypeShortInt:  
	            MemMove( &shortInt,(char*)recPtr+dbDataOffset,2);
	             val=shortInt;   
#ifndef __MC68K__
				 val = SwapDouble(val);
#endif

               dummy.kind='n';
#ifdef __MC68K__
               dummy.dgt_bef=16;
#else
               dummy.dgt_bef=ByteSwap16(16);
#endif
               dummy.dgt_aft=0;
               
               goto formatIt; 
                
	          case dbFldTypeSingle:  
	           MemMove(&f,(char*)recPtr+dbDataOffset,4);
	           val=f;
#ifndef __MC68K__
				 val = SwapDouble(val);
#endif
	           
               dummy.kind='n';
#ifdef __MC68K__
               dummy.dgt_bef=16;
               dummy.dgt_aft=16;
#else
               dummy.dgt_bef=ByteSwap16(16);
               dummy.dgt_aft=ByteSwap16(16);
#endif
	            goto formatIt; 
	          case dbFldTypeByte:  
	           MemMove(&b[0] ,(char*)recPtr+dbDataOffset,1);
	           b[1]=0x00;
	           valuePtr=&b[0];
	            break;   
             default:
//StrPrintF(debug,"TextPtr illeg col type=%d  for colNo=%d cptrDBCol#=%d",dbColPtr->type,cptr->colNo,cptr->dbColNo);
//SysFatalAlert(debug);
               MiscFatalAlert("Grid column format is illegal");
           }
           
 //SysFatalAlert("getTextPtr 44");
  
           MemHandleUnlock(recHand);
           DmReleaseRecord(dbr,index,false);
 
exitNow: 
//SysFatalAlert("getTextPtr 50");
           if (!dbWasOpened)  commonDbcloseLogic(db);   //02052004

           return(valuePtr);     
}

//-------------------------------------------------------------------------------
//  
//-------------------------------------------------------------------------------
#ifdef __MC68K__
double gridValue(struct ObjectData * objPtr,struct gridColInfo* cptr, int row
                 , TableType*grid,   int*coltype)
#else
double gridValue(PNOBlock *pnoP, struct ObjectData * objPtr,struct gridColInfo* cptr, Int16 row
                 , TableType*grid,   Int16*coltype)
#endif
{
 
  
  struct dbType *db;
  struct dbField *dbColPtr;
  DmOpenRef dbr;
  unsigned long dbDataOffset;
  VoidHand recHand;
  VoidPtr  recPtr;
  
  
  Int16 i;
  Int16 j;
  Int16 k; 
    
  UInt16 shortInt;
  float f;
  ULong ui;
  Long  l;
  ULong index;
  
  double val=0;
  //double *valuePtr=0;
  double t;
  UInt16 flags;
  //char wk[128];
  unsigned char tm[3];
  //DateType dt;
  double dt;
  //struct dataelem  dummy;
           //db=setDbPtr(objPtr->dbNo);          
//SysFatalAlert("getValuePtr 1");
   
  
           PNO(dbNo)=objPtr->dbNo;
          
#ifdef __MC68K__
           db=getDatabasePtr();
#else
			db=getDatabasePtr(pnoP);
#endif           
           if(db->openSw!='o') if(gridOpenDb(db)==0) MiscFatalAlert("Database needed for grid cannot be opened.");
           dbr=db->dm;
#ifndef __MC68K__
		   dbr = (DmOpenRef)ByteSwap32(dbr);
#endif
//SysFatalAlert("getValuePtr 3");     
           if(objPtr->bindToDbHasWhereClause==true) 
                         index=*((ULong*)((char*)(objPtr->itemData)+4*(row+objPtr->firstRow)))-1; //02062004 modified
           else          index=row+objPtr->firstRow;      
//StrPrintF(debug,"getValuePtr 5   --index=%d",index);
//SysFatalAlert(debug);

           if( (index>=DmNumRecords(dbr))
           ||  (DmNumRecords(dbr)==0))
           {
               goto exitNow;              
           }
            
           DmRecordInfo(dbr,index,&flags,NIL,NIL);
           if(flags & 0x80) 
           {
               goto exitNow;
           }    
           recHand=DmGetRecord(dbr,index);    
           db->LastDbRecordRead=index+1;
//StrPrintF(debug,"getValuePtr cptrDbColNo=%d",cptr->dbColNo);
//SysFatalAlert(debug);
             

           dbColPtr=setDbField(db,cptr->dbColNo);    
           recPtr=MemHandleLock(recHand);  
           
           
#ifdef __MC68K__          
           dbDataOffset=positionToDbField(db,dbColPtr, recPtr );
#else
           dbDataOffset=positionToDbField(pnoP, db,dbColPtr, recPtr );

#endif   
//SysFatalAlert("getValuePtr 10");   
           *coltype=dbColPtr->type;        
           switch(dbColPtr->type)          
           {
             case dbFldTypeString: //text
               //text does not have value
               break;
             case dbFldTypeLongInt:  //integ
               MemMove(&ui,(char*)recPtr+dbDataOffset,4);
               val=ui;   

                break;            
               
             case dbFldTypeDouble:   //double
               MemMove(&val,(char*)recPtr+dbDataOffset,8);
                
               break;
             case dbFldTypeDate:  //date   
           
                MemMove(&val,(char*)recPtr+dbDataOffset,8);
               //val=cvtPalmInternalDateToDouble(&dt);
//SysFatalAlert("got date value ptr");                   
               break;
             case dbFldTypeTime:  //time
               MemMove(&val,(char*)recPtr+dbDataOffset,8);
               //val=cvtPalmInternalTimeToDouble(&tm[0]);
                
               break;
             case dbFldTypeShortInt:
               MemMove(&shortInt,(char*)recPtr+dbDataOffset,2);
               val=shortInt;   
               break;
             case dbFldTypeSingle:
               MemMove(&f,(char*)recPtr+dbDataOffset,4);
               val=f;   
               break; 
             case dbFldTypeByte:
                 break; 
             default:
//StrPrintF(debug,"ptrValue illeg col type=%d  for colNo=%d cptrDBCol#=%d",dbColPtr->type,cptr->colNo,cptr->dbColNo);
//SysFatalAlert(debug);
               MiscFatalAlert("Grid column format is illegal");
           }
//SysFatalAlert("getValuePtr 20");   
           //valuePtr=&val;
           MemHandleUnlock(recHand);
           DmReleaseRecord(dbr,index,false);

 
exitNow: 
//SysFatalAlert("getValuePtr 50");
          if(db->openSw=='o') commonDbcloseLogic(db);   //inserted 02052004
          return(val );

              
}

#ifdef __MC68K__
//-------------------------------------------------------------------------------
//   locate DB Field
//-------------------------------------------------------------------------------
ULong locateDbField(struct dbType*db, struct dbField * dbFld,  VoidPtr recPtr,  Boolean sortSw)
{
    DmOpenRef dbr=db->dm;
    ULong offset;
    char* p;
    Word i;
    
    
    int tempInt;

    
    if(sortSw==false)   
    {
      if(db->LastDbRecordRead<1)
      {
         p=MemHandleLock(db->hName);         
         strcpy(debug,"No current record for database");
         MemHandleUnlock(db->hName);
         MiscFatalAlert(debug);
      }
      if(db->LastDbRecordRead>DmNumRecords(dbr))
      {
          p=MemHandleLock(db->hName);
          strcpy(debug,"End-of-file for database");
          MemHandleUnlock(db->hName);
          MiscFatalAlert(debug);
      }
 
      if ( dbRecIsDeleted(dbr,db->LastDbRecordRead-1) )
      {
        MiscFatalAlert("Grid formatting accessed a deleted database" );
         
      }
    }
    offset=0;
     
    for( i=1;i<dbFld->colNo;++i)
    {
       
       
        switch(dbFld->type)
        {
          case dbFldTypeString:          //string
            offset+=StrLen((char*)recPtr+offset)+1;
            break;
          case dbFldTypeLongInt:         //long integ
            offset+=4;
            break;  
          case dbFldTypeDouble:         //double
            offset+=8;
            break;
          case dbFldTypeDate:         //date
            offset+=8;
            break;
          case dbFldTypeTime:         //time
            offset+=8;
            break;
          case dbFldTypeShortInt:          
            offset+=2;
            break;
          case dbFldTypeSingle:
            offset+=4;
            break;
          case dbFldTypeByte:  
            offset+=1;
            break;  
          default:
                      ;
        }
         
    }    
    return(offset);
}


//******************************************************************************
//             formatDate with string 
//
//******************************************************************************
void formatDateWithString(  double* n,char * fmt,  char separator, char * result)
{
    int yrno,mono,dano;
    int dayOfTheWeek;
    char yr[3];
    char yrlong[5];
    char mo[4];
    char da[3];
    char moAbrev[12][4]={ "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    char moName[12][10]={"January","February","March","April","May","June","July","August","September","October","November","December"};
    char dayAbrev[7][4]={ "Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    char dayName[7][10]={ "Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    
    int f;
    int i;
    int len=StrLen(fmt);
//char s[128];
//DoubleToStr(*n, s);
//StrPrintF(debug,"date in formatDatewIthString=%s  >>>>>separator=%c format=%s",s,separator,fmt);
//SysFatalAlert(debug);    

     cvt_date_to_ymd(*n,&yrno,&mono,&dano);
    dayOfTheWeek=DayOfWeek(mono,dano,yrno);
    misc_stringfix(yrno-(yrno/100)*100,yr,2);
    misc_stringfix(yrno,yrlong,4);
    misc_stringfix(mono,mo,2);
    misc_stringfix(dano,da,2);
    f=0;
    i=0;
//StrPrintF(debug,"in formatDate == format=%s  yr=%d mo=%d da=%d",fmt,yrno,mono,dano);
//SysFatalAlert(debug);    


    while(fmt[f]!=0x00)
    {
        switch( fmt[f] )
        {
          case 'd':
             if(len>=(f+4))
            {
               if (MemCmp(&fmt[f],"dddd",4)==0)
               {
                  MemMove(&result[i],dayName[dayOfTheWeek],StrLen(dayName[dayOfTheWeek]));
                  i+=StrLen(dayName[dayOfTheWeek]);
                  f+=4;
                  break;
               }
            }
            if(len>=(f+3))
            {
               if(MemCmp(&fmt[f],"ddd",3)==0)
               {
                  MemMove(&result[i],dayAbrev[dayOfTheWeek],StrLen(dayAbrev[dayOfTheWeek]));
                  i+=StrLen(dayAbrev[dayOfTheWeek]);
                  f+=3;
                  break;
               } 
            }
            if(len>=(f+2))
            {
               if(MemCmp(&fmt[f],"dd",2)==0)
               {
                 MemMove(&result[i],da,2);
                 i+=2;
                 f+=2;
                 break;
               }
            }
            
            StrPrintF(&result[i],"%d",dano);
            i+=StrLen(&result[i]);
            f+=1;
            break;   
          case 'm':
            if(len>=(f+4))
            {
               if (MemCmp(&fmt[f],"mmmm",4)==0)
               {
                  MemMove(&result[i],moName[mono-1],StrLen(moName[mono-1]));
                  i+=StrLen(moName[mono-1]);
                  f+=4;
                  break;
               }
            }
            if(len>=(f+3))
            {
               if(MemCmp(&fmt[f],"mmm",3)==0)
               {
                  MemMove(&result[i],moAbrev[mono-1],StrLen(moAbrev[mono-1]));
                  i+=StrLen(moAbrev[mono-1]);
                  f+=3;
                  break;
               } 
            }
            if(len>=(f+2))
            {
               if(MemCmp(&fmt[f],"mm",2)==0)
               {
                 MemMove(&result[i],mo,2);
                 i+=2;
                 f+=2;
                 break;
               }  
            }
            StrPrintF(&result[i],"%d",mono);
            i+=StrLen(&result[i]);
            f+=1;
            break;   
          case 'y':
 
            if(len>=(f+4))
            {
               if (MemCmp(&fmt[f],"yyyy",4)==0)
               {
                  MemMove(&result[i],yrlong,4);
                  i+=4;
                  f+=4;
                  break;
               }
            }
            if(len>=(f+2))
            {
               if(MemCmp(&fmt[f],"yy",2)==0)
               {
                 MemMove(&result[i],yr,2);
                 i+=2;
                 f+=2;
                 break;
               }  
            }
            result[i++]='y';
            ++f;
            break;   
          case '/':
 
            result[i++]=separator;
            ++f;
            break;
          case '\\':
            if(len>=(f+2))
            {
                result[i++]=fmt[f+1];
                f+=2;
                break;
            }
            ++f;
            break;    
            
          default:
            result[i++]=fmt[f++]; 
        }
    }
    
    result[i]=0x00;
}
//******************************************************************************
//             formatTime with string 
//
//******************************************************************************
void formatTimeWithString( double* n,char * fmt,  char separator, char * result)
{
    int f;
    int i;
    int hrno,secno,minno;
    char hr[3];
    char min[3];
    char sec[3];
    int hrno12;
    char hr12[3];
    int len=StrLen(fmt);
    //int ampmUsed=0;
    
    
    
    cvt_time_to_hms(*n,&hrno,&minno,&secno);
    
    if(hrno>11) hrno12=hrno-12;
    else        hrno12=hrno;
    if(hrno12==0) hrno12=12;  //make hour 00 read as 12
    misc_stringfix(hrno,hr,2);
    misc_stringfix(minno,min,2);
    misc_stringfix(secno,sec,2);
    misc_stringfix(hrno12,hr12,2);
    
    
    //f=0;
    //look ahead to see if am/pm is used anywhere in format
    //while(fmt[f]!=0x00)
    //{
    //   switch( fmt[f] )
    //    {
    //      case 'a':
    //      case 'A':
    //      case 'p':
    //      case 'P':
    //        if(hrno12==0) hrno12=12;   //make 00 hour read as 12
    //        ampmUsed=1;
    //        break;
    //    }
    //    ++f;             
    //}
    
    
    
    i=0;
    f=0;
    while(fmt[f]!=0x00)
    {
        switch( fmt[f] )
        {
          case 'h':
            if(len>=(f+2))
            {
              if(MemCmp(&fmt[f],"hh",2)==0)
              {
                 MemMove(&result[i],hr,2);
                 i+=2;
                 f+=2;
                 break;
              }
            }  
            StrPrintF(&result[i],"%d",hrno);
            i+=StrLen(&result[i]);
            ++f;
            break;
          case 'H':
            if(len>=(f+2))
            {
              if(MemCmp(&fmt[f],"HH",2)==0)
              {
                 MemMove(&result[i],hr12,2);
                 i+=2;
                 f+=2;
                 break;
              }
            }  
            StrPrintF(&result[i],"%d",hrno12);
            i+=StrLen(&result[i]);
            ++f;
            break;
          case 'm':
            if(len>=(f+2))
            {
              if(MemCmp(&fmt[f],"mm",2)==0)
              {
                 MemMove(&result[i],min,2);
                 i+=2;
                 f+=2;
                 break;
              }
            }  
            StrPrintF(&result[i],"%d",minno);
            i+=StrLen(&result[i]);
            ++f;
            break;
          case 's':
            if(len>=(f+2))
            {
              if(MemCmp(&fmt[f],"ss",2)==0)
              {
                 MemMove(&result[i],sec,2);
                 i+=2;
                 f+=2;
                 break;
              }
            }  
            StrPrintF(&result[i],"%d",secno);
            i+=StrLen(&result[i]);
            ++f;
            break;
          case 'A':
            if(len>=(f+5))
            {
              if(MemCmp(&fmt[f],"AM/PM",5)==0)
              {  
                 if(hrno>=12) MemMove(&result[i],"PM",2);
                 else         MemMove(&result[i],"AM",2);
                 i+=2;
                 f+=5;
                 break;
              }
            }  
            if(len>=(f+3))
            {
              if(MemCmp(&fmt[f],"A/P",3)==0)
              {  
                 if(hrno>=12) MemMove(&result[i],"P",1);
                 else         MemMove(&result[i],"A",1);
                 i+=1;
                 f+=3;
                 break;
              }
            } 
            if(len>=(f+2))
            {
              if(MemCmp(&fmt[f],"AM",2)==0)
              {  
                 if(hrno>=12) MemMove(&result[i],"  ",2);
                 else         MemMove(&result[i],"AM",2);
                 i+=2;
                 f+=2;
                 break;
              }
            }
            result[i++]='A';
            ++f;
            break;  
          case 'a':
            if(len>=(f+5))
            {
              if(MemCmp(&fmt[f],"am/pm",5)==0)
              {  
                 if(hrno>=12) MemMove(&result[i],"pm",2);
                 else         MemMove(&result[i],"am",2);
                 i+=2;
                 f+=5;
                 break;
              }
            }  
            if(len>=(f+3))
            {
              if(MemCmp(&fmt[f],"a/p",3)==0)
              {  
                 if(hrno>=12) MemMove(&result[i],"p",1);
                 else         MemMove(&result[i],"a",1);
                 i+=1;
                 f+=3;
                 break;
              }
            } 
            if(len>=(f+2))
            {
              if(MemCmp(&fmt[f],"am",2)==0)
              {  
                 if(hrno>=12) MemMove(&result[i],"  ",2);
                 else         MemMove(&result[i],"am",2);
                 i+=2;
                 f+=2;
                 break;
              }
            }
            result[i++]='a';
            ++f;
            break;    
           case 'p':
            if(len>=(f+2))
            {
              if(MemCmp(&fmt[f],"pm",2)==0)
              {  
                 if(hrno>=12) MemMove(&result[i],"pm",2);
                 else         MemMove(&result[i],"  ",2);
                 i+=2;
                 f+=2;
                 break;
              }
            }
            result[i++]='p';
            ++f;
            break;  
          case 'P':
            if(len>=(f+2))
            {
              if(MemCmp(&fmt[f],"PM",2)==0)
              {  
                 if(hrno>=12) MemMove(&result[i],"PM",2);
                 else         MemMove(&result[i],"  ",2);
                 i+=2;
                 f+=2;
                 break;
              }
            }
            result[i++]='P';
            ++f;
            break; 
          case ':':
            result[i++]=separator;
            ++f;
            break;
          case '\\':
            if(len>=(f+2))
            {
               result[i++]=fmt[f+1];
               f+=2;
               break;
            }
            ++f;
            break;
          default:
            result[i++]=fmt[f++];
        }
    }
    result[i]=0x00;          
}
#endif

//start additions 02062004
//-------------------------------------------------------------------------------
// return the number of the topRow being displayed in the grid
//-------------------------------------------------------------------------------
#ifdef __MC68K__
void gridGetTopRow(FormPtr frm,VoidPtr controlPtr)
#else
void gridGetTopRow(PNOBlock *pnoP, Arg *arg4, FormPtr frm,VoidPtr controlPtr)
#endif
{
  struct ObjectData *objPtr;
   
  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
#ifdef __MC68K__
  objPtr=locateObjectPtr(PNO(controlid));   //get the ptr to our obj data        
  restore4(objPtr->firstRow+1);          //return the top rows
#else
	objPtr = locateObjectPtr(pnoP, PNO(controlid));
	{
        double d = ByteSwap16(objPtr -> firstRow) + 1;
        d = SwapDouble(d);
        misc_stodbl(pnoP, arg4 -> dataElem, arg4 -> occ1, arg4 -> occ2, arg4 -> occ3, &d);
	}

#endif
}
//-------------------------------------------------------------------------------
// set the topRow being displayed in the grid
//-------------------------------------------------------------------------------

#ifdef __MC68K__
void gridSetTopRow(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
#else
void gridSetTopRow(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr, double* paramPtr)
#endif
{
  Int16 toprow;
  
  struct ObjectData *objPtr;
   
  
  toprow=*paramPtr-1; 
  PNO(controlid)= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));                                    //ctlid is 1st arg

#ifdef __MC68K__
  objPtr=locateObjectPtr(PNO(controlid));              //get the ptr to our obj data             
#else
  objPtr=locateObjectPtr(pnoP, PNO(controlid));              //get the ptr to our obj data             
#endif  
                          //calc the row # as integer (1-based)
  
  if(isGridRowValid(  objPtr,  toprow))         //if row is valid
  {
#ifdef __MC68K__
      objPtr->firstRow=toprow;                         //save as the top row
#else
	  objPtr->firstRow = ByteSwap16(toprow);
#endif

      objPtr->refreshFromDatabase=true;                 //and tell to reload visible grid
     
      if( PNO(typeOfScript) != 'b' )
#ifdef __MC68K__
      	redrawGrid(objPtr);  // redraw
#else
		redrawGrid(pnoP, objPtr);
#endif       
  }
}

void freeCellContents( struct ObjectData* objPtr)
{
	    char* textP;
	    int row;
	    int col;
#ifdef __MC68K__
	    for(row=0;row<objPtr->numItems;++row)
        {
           for(col=objPtr->howManyColsInBind;col<objPtr->cols;++col)
#else
	    for(row=0;row<ByteSwap16(objPtr->numItems);++row)
        {
           for(col=ByteSwap16(objPtr->howManyColsInBind);col<ByteSwap16(objPtr->cols);++col)
#endif
           {
             
             textP=*( gridCellPtr(objPtr,row,col));
             if(textP)      MemPtrFree( textP);
             *( gridCellPtr(objPtr,row,col))=0;
           }
        }
}


#ifdef __MC68K__
//end of additions 02062004
 /*
 






//-------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------





//-------------------------------------------------------------------------------
//
//-------------------------------------------------------------------------------
void gridSetScrollPagesize()
{
      struct ObjectData* objPtr;
      find_ctlid();
      find_arg_2(); //pagesize
  
      objPtr=locateObjectPtr(controlid);  
     
      objPtr->scrollPagesize=basc_integ_value(arg2,(double*)arg2_val); 
   
     
 }




        


*/

#endif