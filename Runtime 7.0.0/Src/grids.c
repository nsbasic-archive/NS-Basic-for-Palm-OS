#include <PalmOS.h>
#include <PalmTypes.h>
#include <PalmCompatibility.h>

 
#include <MathLib.h>
#include <SysUtils.h>
#include <SysEvtMgr.h>
#include <FatalAlert.h>
#include <FloatMgr.h> 
#include <SystemMgr.h>
#include <ScrollBar.h>
#include <FrmGlue.h> 
#include "copy.h" 
 
void formatDateWithString(  double* n,char * fmt,  char separator, char * result);
void formatTimeWithString(  double* n,char * fmt,  char separator, char * result);
 
void misc_stringfix(int i, char *res, int num) ;
extern void misc_fmtno(char *fmt,char *wk,int bef,int aft,int decpt, char *result);
extern int      dbNo;
void redrawGrid(struct ObjectData * objPtr);
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
void gridFormat( struct ObjectData *objPtr);
DoubleToStr(double val, CharPtr ans);
VoidPtr resizePtr(VoidPtr p,  long additional);
void freeCellContents( struct ObjectData* objPtr);
//**************************************************************************
//
//**************************************************************************
struct dbField * setDbField(struct dbType*db, int colNo)
{
    struct dbField * dbFld;
   
    
    dbFld=db->ptrFields;      
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
//-------------------------------------------------------------------------------
//   read a datbase record and seperate field values
//-------------------------------------------------------------------------------
void gridSetDatabaseFields(struct dbType *db,DmOpenRef dbr,unsigned int dbRecNo);
void gridSetDatabaseFields(struct dbType *db,DmOpenRef dbr,unsigned int dbRecNo)
{
  struct dbField* dbFld;
  VoidHand recHand;
  VoidPtr  recPtr;
  UInt offset=0;
  int i;
  void readOneDbArgument(struct dbType * db,VoidPtr recPtr,UInt *theOffset);
  extern char *devel_address(struct dataelem *arg, unsigned int s1,unsigned int s2,unsigned int s3);
  extern struct dataelem *elem_tbl_ptr(unsigned int de_no);
    
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
  dbFld=db->ptrFields;
  for(i=0;i<db->noFields;++i)
  {
//StrPrintF(debug,"reading dbfld %d into dataelem#=%d",i,dbFld->tblNo);
//SysFatalAlert(debug);
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
  SystemPreferencesType sysPrefs;      
    
  PrefGetPreferences(&sysPrefs);      //get user's preferences 
  
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
    if (StrCaselessCompare(fmt,"yes/no")==0)
    {
        if( *n==0.0) StrCopy(s,"NO");
        else         StrCopy(s,"YES");
        return(1);
    }
    if (StrCaselessCompare(fmt,"true/false")==0)
    {
        if( *n==0.0) StrCopy(s,"FALSE");
        else         StrCopy(s,"TRUE");
        return(1);
    }
    if (StrCaselessCompare(fmt,"on/off")==0)
    {
        if( *n==0.0) StrCopy(s,"OFF");
        else         StrCopy(s,"ON");
        return(1);
    }
    return(0);    //was not one of the special formats
     
}
//-------------------------------------------------------------------------------
//   check to see if db record is marked as deleted
//-------------------------------------------------------------------------------

int dbRecIsDeleted( DmOpenRef dbr, UInt theRec)
{
    //this rtn checks to see if a database record is deleted
    //returns 1 if deleted,   0 if not
    unsigned short recInfo;
    
    DmRecordInfo(dbr,theRec,&recInfo,NIL,NIL);
 
    if( (recInfo & 0x80 ) !=0x00) return(1);
    return(0);
}
//-------------------------------------------------------------------------------
//   find offset to a field in database record
//----------------------------------------------------------------------------------------------------------
unsigned long positionToDbField(struct dbType*db,struct dbField * dbFld,char* recPtr)
{
    DmOpenRef dbr=db->dm;
    ULong offset;
    char* p;
    Word i;
    struct dbField* tempcol;
     
    int tempInt;

 //StrPrintF(debug,"Entering positionToDBField  --   dbFld col# = %d",dbFld->colNo);
 //SysFatalAlert(debug);  
    
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
    
    offset=0;
    
    for( i=0;i<dbFld->colNo;++i)
    {
//StrPrintF(debug,"advancing to column %d",i);
//dbug(debug);
        //loop thru cols to position to the data of interest
        tempcol=db->ptrFields; 
        tempcol=((struct dbField*)((char*)tempcol+sizeof(dbFldExample)*i));
//StrPrintF(debug,"colNo=%d dbcolType=%d",i,tempcol->type);
//SysFatalAlert(debug);
        switch(tempcol->type)
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
Boolean isGridRowValid( struct ObjectData *objPtr, int row)
{
    if( (row<objPtr->numItems) && (row>=0) ) return(true);
    else                                     return(false);
}
//-------------------------------------------------------------------------------
//  ckeck if col # is within defined # columns
//-------------------------------------------------------------------------------
Boolean isGridColumnValid( struct ObjectData *objPtr, int col)
{
    if((col<objPtr->cols) && (col>=0) )      return(true);
    else                                     return(false);
}

//-------------------------------------------------------------------------------
//  check if row is currently visible
//-------------------------------------------------------------------------------
Boolean isGridRowVisible( struct ObjectData *objPtr, int row)
{
    if(  (row<objPtr->firstRow) || (row>=(objPtr->firstRow + objPtr->visibleRows)) ) return(false);  ///06/07/2004
    else                                                                           return(true);
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
struct gridColInfo* locateGridColInfo(struct ObjectData* objPtr,  int col)
{
  return( ((struct gridColInfo*) ((char*)objPtr->colInfo+col*sizeof(gridColInfoExample))));

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
char** gridCellPtr(struct ObjectData* objPtr, int row, int col)
{
   return(  (char**)((char*)objPtr->gridContent+4*(row*(objPtr->cols-objPtr->howManyColsInBind)+(col-objPtr->howManyColsInBind))) );

}
//------------------------------------------------------------------------------------------
//    opens the database used by bound grid
//
//       returns 0 on success;    1 on error
//------------------------------------------------------------------------------------------
DmOpenRef gridOpenDb( struct dbType*db )
{
  
  VoidHand recHand;
  VoidPtr  recPtr;
  int res;
  
  int err;
  DmOpenRef dbref;
  char*p;

   //dbfind_arg(4);  //cardNo
   //db=getDatabasePtr();

   p=MemHandleLock(db->hName);
//StrPrintF(debug,"trying to open database %s",p);
//SysFatalAlert(debug);
   db->lid=DmFindDatabase( 0,p);
   MemHandleUnlock(db->hName);
   if(db->lid==0)
   {
     return(0);
   }
   dbref=DmOpenDatabase(0,db->lid,dmModeReadOnly);
   if(dbref==0)
   {
     return(0);                           //02.20.02 GH
   }
    

   db->openSw='o';
   db->dm=dbref;
   db->LastDbRecordRead=-1;
   db->curHand=0;
   db->offset=0;
   db->cardno=0;
   return(dbref);
}


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
    for(col=0;col<objPtr->cols;++col)
	{
	    cptr=locateGridColInfo(objPtr, col);   
	    cptr->colNo=col;            
	    cptr->dbSupplied = false;          
	    
	    cptr->dbColNo=0;
	    
	    cptr->colNo=col;           
	    cptr->type='s';    
	    cptr->format=0;   
	    
	     
   }
//SysFatalAlert("init rows"); 
   for(row=0;row<objPtr->visibleRows;++row)
   {
       for(col=0;col<objPtr->cols;++col)
       {
	       //p =MemHandleLock(MemHandleNew(2));
	       //StrCopy(p ,blankText);
           *(gridCellPtr(objPtr,row,col))=0; 
           TblSetItemFont((TableType*)FrmGetObjectPtr(FrmGetFormPtr (objPtr->frmId),objPtr->index),row,col,0);   //06072004 
       }
   } 
   
   //get the original grid bounds
   TblGetBounds((TableType*)FrmGetObjectPtr(FrmGetFormPtr (objPtr->frmId),objPtr->index),&(objPtr->origGridBounds));

    

//("done with initGrid");   
//StrPrintF(debug,"leaving init cols=%d",objPtr->cols);
//SysFatalAlert(debug);  
}
 
 //-------------------------------------------------------------------------------
//  releases all of the memory used by a grid
//-------------------------------------------------------------------------------
void releaseGridMemory( struct ObjectData * objPtr)
{
  
   void * textP;
   int row;
   int col;
   
   struct gridColInfo* cptr;     
   
   
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
   initializeGrid(objPtr,FrmGetActiveForm());
   objPtr->numItems=0;           
     
}
//-------------------------------------------------------------------------------
//  common rtn to set the text of some grid cell
//-------------------------------------------------------------------------------
commonGridSetText(struct ObjectData *objPtr,int row,int col,char dontDisplaySw,char*t)
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
          if( (typeOfScript!='b') && (dontDisplaySw==0x00))  
          {
//SysFatalAlert("common text change");
              if( isGridRowVisible(objPtr,row) )
              {
//SysFatalAlert( "redraw on text chg");
                  redrawGrid(objPtr);   
              }
          }
      //02062004}    
  }    

                
}
//-------------------------------------------------------------------------------
//  common rtn to set the numeric value of some grid cell
//-------------------------------------------------------------------------------
commonGridSetValue(struct ObjectData *objPtr,int row,int col,char dontDisplaySw,double value)
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
//SysFatalAlert("setting cell value");      
          MemMove(*cellMatrix,&value,8);
      	  
//SysFatalAlert("redrawing");      	   
          //redraw if row is visible and not in "before draw" rtn
          if( (typeOfScript!='b') && (dontDisplaySw==0x00))  
          {
              if( isGridRowVisible(objPtr,row) )
              {
                  redrawGrid(objPtr);   
              }
          }
      }    
  }    

}
//-------------------------------------------------------------------------------
// return the # of columns of the grid  
//-------------------------------------------------------------------------------
void gridGetCols(FormPtr frm,VoidPtr controlPtr)
{
   struct ObjectData * objPtr;
  
   controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
   objPtr=locateObjectPtr(controlid);  //get the ptr to our obj data
   restore4(objPtr->cols);             //return the grid # of cols    
    
} 

//-------------------------------------------------------------------------------
// return the number of rows in the grid
//-------------------------------------------------------------------------------
void gridGetRows(FormPtr frm,VoidPtr controlPtr)
{
  
  struct ObjectData *objPtr;
   
  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  objPtr=locateObjectPtr(controlid);   //get the ptr to our obj data        
  restore4(objPtr->numItems);          //return the # of rows
       
}

//-------------------------------------------------------------------------------
// return the selected column no of the grid
//-------------------------------------------------------------------------------
void gridGetSelectedCol(FormPtr frm,VoidPtr controlPtr)
{
  struct ObjectData *objPtr;
    
  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  objPtr=locateObjectPtr(controlid);  //get the ptr to our obj data  
  restore4(objPtr->currentCol+1);         //return the sel col (1-based)  
}
//-------------------------------------------------------------------------------
// set value of rowData for a row
//-------------------------------------------------------------------------------
void gridSetRowData(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
{
    
    int row;
    unsigned long value;
    struct ObjectData *objPtr;
    
    row  =*paramPtr-1;                     //row #  
    value=find_long_integ_arg();                  //item data value to assign
    controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));                            
    objPtr=locateObjectPtr(controlid);      //and locate the obj ptr for the grid                
    
    
     
    if(isGridRowValid(objPtr,row) )                          //if row is valid
    {
        *((ULong*)((char*)(objPtr->itemData)+4*row))=value;  //assign value for row      
    }
}
 
//-------------------------------------------------------------------------------
// set the selected column of a grid
//-------------------------------------------------------------------------------
void gridSetSelectedCol(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
{
  
  int row;
  int col;
  int actualRow; 
  struct ObjectData *objPtr;  
  
  col=*paramPtr-1;                //get the column arg 
  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  objPtr=locateObjectPtr(controlid);               
  
               
  
//StrPrintF(debug,"set col = %d  scriptType=%c firstRow=%d currentRow=%d",col,typeOfScript,objPtr->firstRow,objPtr->currentRow);
//SysFatalAlert(debug);
  if(isGridColumnValid(objPtr,col))      //if grid column # is a valid col #
  {  
      objPtr->currentCol=col;                //remembewr the selected col #
      if( typeOfScript!='b')   
      {
         if( objPtr->currentRow >= 0 )  //addded 06072004
         {                               //addded 06072004
         	actualRow=objPtr->currentRow - objPtr->firstRow;    //calc row in visible grid
          	//select the cell by row and column
          	TblSelectItem((TableType*)FrmGetObjectPtr(FrmGetFormPtr(objPtr->frmId),
                         objPtr->index),actualRow,objPtr->currentCol); //select the cell
      	 }    //addded 06072004
  	  }
  }	
  
}
//-------------------------------------------------------------------------------
// return the selected row no of the grid
//-------------------------------------------------------------------------------
void gridGetSelectedRow(FormPtr frm,VoidPtr controlPtr)
{
  struct ObjectData *objPtr;
   
  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  objPtr=locateObjectPtr(controlid);  //get the ptr to our obj data 
  restore4(objPtr->currentRow+1);         //return the sel row (1-based)   
}

//-------------------------------------------------------------------------------
// return the number of visible rows in the grid
//-------------------------------------------------------------------------------
void gridGetVisibleRows(FormPtr frm,VoidPtr controlPtr)
{
  struct ObjectData * objPtr;
 
  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  objPtr=locateObjectPtr(controlid);  //get the ptr to our obj data 
  restore4(objPtr->visibleRows);      //return # of visible cols     
}

//-------------------------------------------------------------------------------
// set a row as the currently selected row
//-------------------------------------------------------------------------------
void gridSetSelectedRow(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
{
 
  
  int row;
  int col;
  struct ObjectData *objPtr;
   
  
  row=*paramPtr-1; 
  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));                                    //ctlid is 1st arg
  objPtr=locateObjectPtr(controlid);              //get the ptr to our obj data             
  
                          //calc the row # as integer (1-based)
//StrPrintF(debug,"row=%d",row);
//SysFatalAlert(debug);
  
  if( (row == -2) || (isGridRowValid(  objPtr,  row)) ) //modified 07202005 //if row is valid
  {
      objPtr->currentRow=row;                         //save as the selected row
//StrPrintF(debug,"row=%d noVis=%d top=%d", row, objPtr->visibleRows, objPtr->firstRow);
//SysFatalAlert(debug);
    
      if(!isGridRowVisible(objPtr,row) || (row==-2))  //07202005
      {
        //row is outside the visible grid
         if(row>=0) objPtr->firstRow=row;     //modified 07122004 //set as beginning row to display
         else       objPtr->firstRow = 0;     //added    07122004
         objPtr->refreshFromDatabase=true;                 //and tell to reload visible grid
     
         if( typeOfScript != 'b' )
         {
//SysFatalAlert("redrawing");
              redrawGrid(objPtr);  //if not in "before draw" rtn, then redraw
          }
      }
      else
      {
         //row is in the visible grid
         if( typeOfScript != 'b' )          //if not in "before draw" rtn,
         {
             if( objPtr->currentCol >= 0 )       //addded 06072004
             {                                   //addded 06072004
                 TblSelectItem((TableType*)FrmGetObjectPtr(FrmGetFormPtr(objPtr->frmId),
                  objPtr->index),objPtr->currentRow-objPtr->firstRow,objPtr->currentCol);    //mark row as selected
        	 }                                   //addded 06072004
         } 
      }
  }
}
//-------------------------------------------------------------------------------
//  return an integer argument's value
//-------------------------------------------------------------------------------
int find_integ_arg()
{
    find_arg_1();
    return( integ_value(arg1,(double*)arg1_val)  );
}
//-------------------------------------------------------------------------------
//  return an integer argument's value
//-------------------------------------------------------------------------------
int find_long_integ_arg()
{
    find_arg_1();
    return( long_integ_value(arg1,(double*)arg1_val) );
}


//-------------------------------------------------------------------------------
//set # rows
//-------------------------------------------------------------------------------
void gridSetRows(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
{
   struct ObjectData *objPtr;
   int newRows = *paramPtr;
   
   controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
   objPtr=locateObjectPtr(controlid); 
  
   while( newRows> objPtr->numItems )
   {
//StrPrintF(debug,"adding row want=%d  have=%d",newRows,objPtr->numItems);
//SysFatalAlert(debug);
        gridCommonAddRow(objPtr, controlid);
   }
   while(  newRows< objPtr->numItems)
   {
//StrPrintF(debug,"deleting row   want=%d  have=%d",newRows,objPtr->numItems);
//SysFatalAlert(debug);
       gridCommonRemoveRow(objPtr, controlid, objPtr->numItems-1);
   }
   if(typeOfScript!='b')  redrawGrid(objPtr);
    
}
//-------------------------------------------------------------------------------
//set # Cols
//-------------------------------------------------------------------------------
/*   !!!not implemented
void gridSetCols(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
{


//??


}
*/
//-------------------------------------------------------------------------------
//set column width
//-------------------------------------------------------------------------------
void gridSetColWidth(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
{

  int w;
  struct gridColInfo* lastColPtr;
  struct ObjectData *objPtr;
  int row;
  int col;
  int val=0; 
  struct gridColInfo*  colPtr;  
  int oldWidth;
  int totWidth = 0;
  int ijk;
  int newWidth;
  
  
  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  objPtr=locateObjectPtr(controlid);               

  col=*paramPtr-1;                //get the column arg
  
//StrPrintF(debug,"set col width   col=%d  val=%d",col,val);
//SysFatalAlert(debug);             

  val=find_integ_arg(); 
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
	      objPtr->currentCol=col;                //remembewr the selected col #
//SysFatalAlert("991");
	      colPtr=locateGridColInfo(  objPtr,    col);
//SysFatalAlert("992");
	      
	     
	        

	       colPtr->width=val;
//SysFatalAlert("993");
	       TblSetColumnWidth (controlPtr,col, val);  //set this column's new width
								 
//SysFatalAlert("994");
	       
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
	      
	      
	      if( typeOfScript!='b')   
	      {
	           redrawGrid(objPtr);
	      }
      //02062004 }
  }
 


}
//-------------------------------------------------------------------------------
//get col width
//-------------------------------------------------------------------------------
void gridGetColWidth(FormPtr frm,VoidPtr controlPtr)
{

  struct ObjectData *objPtr;
  int row;
  int col;
  int val; 
  struct gridColInfo*  colPtr;  
  
  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  objPtr=locateObjectPtr(controlid);               
  
              
   
  col=find_integ_arg()-1;                //get the column arg 
 
  if(isGridColumnValid(objPtr,col))      //if grid column # is a valid col #
  {  
       
      colPtr=locateGridColInfo(  objPtr,    col);
  
      
      restore4(colPtr->width);
 
      return;
  }
  restore4(-1);
}
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
//-------------------------------------------------------------------------------
//set valueMatrix
//-------------------------------------------------------------------------------
void gridSetValueMatrix(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
{

struct ObjectData *objPtr;
 
  int row;
  int col;
//char wks [128]; 
//char wkt [128]; 
//VoidPtr valueP;
  char dontDisplaySw=0x00;

  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  objPtr=locateObjectPtr(controlid);
  row=*paramPtr-1;        //row
  col=find_integ_arg()-1;        //column
  find_arg_1();                  //value
  
  //dontDisplaySw=find_char();  //0x01=no display 0x00=display
//DoubleToStr(*((double*)arg1_val), wks);

 
  commonGridSetValue(objPtr,row,col,dontDisplaySw,*((double*)arg1_val));
  
//valueP=*((VoidPtr*)((char*)objPtr->gridContent+4*(row*(objPtr->cols-objPtr->howManyColsInBind)+(col-objPtr->howManyColsInBind))));   
//DoubleToStr(*((double*)valueP),wkt);
//StrPrintF(debug,"setting cell value row=%d col=%d val=%s newValue=%s",row+1, col+1,wks,wkt);
//SysFatalAlert(debug);   
}
//start additions 04012005
//-------------------------------------------------------------------------------
//set valueMatrix
//-------------------------------------------------------------------------------
void gridSetFontMatrix(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
{

struct ObjectData *objPtr;
 
  int row;
  int col;
  FontID fontID ;
  FontID oldFontID = FntGetFont();   //08022005
//char wks [128]; 
//char wkt [128]; 
//VoidPtr valueP;
  //char dontDisplaySw=0x00;

  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  objPtr=locateObjectPtr(controlid);
  row=*paramPtr-1;        //row
  col=find_integ_arg()-1;        //column
  //find_arg_1();                  //font
  fontID = find_integ_arg();
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
void gridGetFontMatrix(FormPtr frm,VoidPtr controlPtr)
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

  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  objPtr=locateObjectPtr(controlid);               //get ctl's object ptr 
                                 
  
  find_arg_1();
  row=integ_value(arg1,(double*)arg1_val)-1;   //get row integ
  find_arg_2();
  col=integ_value(arg2,(double*)arg2_val)-1;   //get column integ
  
  if ( isGridRowValid(objPtr,row)                //must have valid row and col #'s
    && isGridColumnValid(objPtr,col) ) 
  { 
	  d = TblGetItemFont ((TableType*)controlPtr,row,col );
 	   
  } 
  store4(&d);               //return value    
}
//end additions 04012005

//-------------------------------------------------------------------------------
//get valueMatrix
//-------------------------------------------------------------------------------
void gridGetValueMatrix(FormPtr frm,VoidPtr controlPtr)
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

  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  objPtr=locateObjectPtr(controlid);               //get ctl's object ptr 
                                 
  
  find_arg_1();
  row=integ_value(arg1,(double*)arg1_val)-1;   //get row integ
  find_arg_2();
  col=integ_value(arg2,(double*)arg2_val)-1;   //get column integ
  
  if ( isGridRowValid(objPtr,row)                //must have valid row and col #'s
    && isGridColumnValid(objPtr,col) ) 
  { 
	   cptr=locateGridColInfo(objPtr, col);        //point to col's information   
	   if(cptr->type != 's')
	   { 
	      if(cptr->dbSupplied)
	      {
	         d=gridValue( objPtr, cptr, row-objPtr->firstRow, (TableType*)controlPtr,&ctype);
	        
	      }
	      else
	      {
	         valueP=*((VoidPtr*)((char*)objPtr->gridContent+4*(row*(objPtr->cols-objPtr->howManyColsInBind)+(col-objPtr->howManyColsInBind))));   
	         if(valueP!=0)     d=*((double*)valueP);
	      }             
       } 
  } 
  store4(&d);               //return value    
}
//-------------------------------------------------------------------------------
//set selected value
//-------------------------------------------------------------------------------
void gridSetSelectedValue(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
{
  int row;
  int col;
 
   
  struct ObjectData *objPtr;
 
   
  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  
  //03052004 find_arg_1();                          // text to assign
    
  objPtr=locateObjectPtr(controlid);      
  row=objPtr->currentRow;
  col=objPtr->currentCol;
   
  commonGridSetValue(objPtr,row,col,0x00,*paramPtr);

 
}
//-------------------------------------------------------------------------------
// get the text of a grid cell by its row and column  
//-------------------------------------------------------------------------------
void gridGetCellMatrix(FormPtr frm,VoidPtr controlPtr)  
{
    
  char wk[512];
  char emptyString[1]="";
  VoidPtr textP;
  struct ObjectData *objPtr;
  struct gridColInfo* cptr;
 int ctype;

  int row;
  int col;
  

//SysFatalAlert("2"); 
  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
//SysFatalAlert("3");
  objPtr=locateObjectPtr(controlid);               //get ctl's object ptr 
  textP=&emptyString;                              //init to null string
//SysFatalAlert("4");  
  find_arg_1();
  row=integ_value(arg1,(double*)arg1_val)-1;   //get row integ
  find_arg_2();
  col=integ_value(arg2,(double*)arg2_val)-1;   //get column integ
//StrPrintF(debug,"row=%d col=%d",row,col);
//SysFatalAlert(debug);
  if ( isGridRowValid(objPtr,row)                //must have valid row and col #'s
    && isGridColumnValid(objPtr,col) ) 
  { 
      cptr=locateGridColInfo(objPtr, col);        //point to col's information   
//SysFatalAlert("5");    
      if(cptr->dbSupplied)
      {
         textP=gridTextPtr( objPtr, cptr, row-objPtr->firstRow,&wk[0],(TableType*)controlPtr,&ctype);
      }
      else
      {
 //SysFatalAlert("7");
         textP=*((VoidPtr*)((char*)objPtr->gridContent+4*(row*(objPtr->cols-objPtr->howManyColsInBind)+(col-objPtr->howManyColsInBind))));   
      }
 //SysFatalAlert("8");
      if(textP==0)               textP=&emptyString;  //no text data yet
        
  } 
//SysFatalAlert("9");
  storestr4(textP);               //return ptr to text       
 
}

//-------------------------------------------------------------------------------
//   get the text of the selected cell
//-------------------------------------------------------------------------------
void gridGetSelectedText(FormPtr frm,VoidPtr controlPtr)
{
  char wk[512];
  char emptyString[1]="";
  VoidPtr textP;
  struct gridColInfo* cptr;
  struct ObjectData *objPtr;
  
  int ctype; 
  
  int row;   
  int col;
  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  objPtr=locateObjectPtr(controlid);               //get ctl's object ptr 
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
          textP=gridTextPtr( objPtr, cptr, row-objPtr->firstRow,&wk[0],(TableType*)controlPtr,&ctype);

      }
      else
      {
//SysFatalAlert("8");
          textP=*((VoidPtr*)((char*)objPtr->gridContent+4*(row*(objPtr->cols-objPtr->howManyColsInBind)+(col-objPtr->howManyColsInBind))));   
     
      }
//SysFatalAlert("9");  
      if(textP==0)               textP=&emptyString;  //no text data yet
        
  } 
//SysFatalAlert("10");
  storestr4(textP);          
    
}
//-------------------------------------------------------------------------------
//get selected value
//-------------------------------------------------------------------------------
void gridGetSelectedValue(FormPtr frm,VoidPtr controlPtr)
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
  
  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));

  objPtr=locateObjectPtr(controlid);               //get ctl's object ptr 
                                 //init to null string
  
  row=objPtr->currentRow;
  col=objPtr->currentCol;
  
  if ( isGridRowValid(objPtr,row)                //must have valid row and col #'s
    && isGridColumnValid(objPtr,col) ) 
  { 
      cptr=locateGridColInfo(objPtr, col);        //point to col's information   
      if(cptr->type != 's')
      {
	      if(cptr->dbSupplied) d=gridValue ( objPtr, cptr, row-objPtr->firstRow, (TableType*)controlPtr,&ctype);
	      else
	      {
	          valueP=*((VoidPtr*)((char*)objPtr->gridContent+4*(row*(objPtr->cols-objPtr->howManyColsInBind)+(col-objPtr->howManyColsInBind))));   
	          if(valueP!=0)      d=*((double*)valueP);  //no data yet 
	      } 
	  }       
  } 
  store4(&d);   
    
}



//-------------------------------------------------------------------------------
// return the item data value for a grid row
//-------------------------------------------------------------------------------
void gridGetRowData(FormPtr frm,VoidPtr controlPtr)
{
    
    unsigned long value;
    int row;
    double reg;
    struct ObjectData *objPtr;
     
    controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
    objPtr=locateObjectPtr(controlid);         

    find_arg_1();
    row=basc_integ_value(arg1,(double*)arg1_val)-1;   //get the row #
    
    if(isGridRowValid(objPtr,row))          //if row # valid
    {
      value=*((unsigned long*)((char*)objPtr->itemData+4*row));  //return item data value
    }
    else value=0l;                         //return 0 on invalid row

   reg=value;
   store_reg(&reg, arg4,(double*) arg4_val, arg4_occ1,arg4_occ2,arg4_occ3);
}

//-------------------------------------------------------------------------------
//  clear all rows from a grid
//-------------------------------------------------------------------------------
void gridClear(FormPtr frm,VoidPtr controlPtr)
{
   
   int row, col;
   
   //struct gridColInfo* cptr;     
   
    struct ObjectData *objPtr;
     
   controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
   objPtr=locateObjectPtr(controlid);
   
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
   if(typeOfScript=='b') gridFormat(  objPtr ); 
   else                       redrawGrid(objPtr);
      
       
}


//-------------------------------------------------------------------------------
//   set the text of the selected cell
//-------------------------------------------------------------------------------
void gridSetSelectedText(FormPtr frm,VoidPtr controlPtr,char* paramPtr)
{
  int row;
  int col;
 
  char dontDisplaySw=0x00;
  
  struct ObjectData *objPtr;
 
//StrPrintF(debug,"setting text=%s",paramPtr);
//SysFatalAlert(debug);   
  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  //find_arg_1();                          // text to assign
  //dontDisplaySw=find_char();             //switch to redisplay grid or not
  objPtr=locateObjectPtr(controlid);      
 
  row=objPtr->currentRow;
  col=objPtr->currentCol;
  commonGridSetText(objPtr,row,col,dontDisplaySw,paramPtr);
 
}
//-------------------------------------------------------------------------------
//   set the text for a given row & col
//-------------------------------------------------------------------------------
void gridSetCellMatrix(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
{
  
  struct ObjectData *objPtr;
 
  int row;
  int col;
 
  char dontDisplaySw=0x00;

  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  objPtr=locateObjectPtr(controlid);
  row=*paramPtr-1;        //row
  col=find_integ_arg()-1;        //column
  find_arg_1();                  //value
//StrPrintF(debug,"set cell text row=%d col=%d s=%s",row,col,arg1_val);
//SysFatalAlert(debug);
  if(arg1->kind!='s') 
              commonErrorWrongType("CellMatrix");
  //dontDisplaySw=find_char();  //0x01=no display 0x00=display
//StrPrintF(debug,"going to commonSetText  donDisplay=%c",dontDisplaySw);
//SysFatalAlert(debug);
  commonGridSetText(objPtr,row,col,dontDisplaySw,arg1_val);
}  
//-------------------------------------------------------------------------------
//  remove a specified row from the grid
//-------------------------------------------------------------------------------

void gridDelete(FormPtr frm,VoidPtr controlPtr)
{
 
  int row;
  struct ObjectData *objPtr;
 
  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  objPtr=locateObjectPtr(controlid);  
  row=find_integ_arg()-1;
//StrPrintF(debug,"deleteingf row=%d",row);
//dbug(debug);
  gridCommonRemoveRow(objPtr, controlid, row);
//SysFatalAlert("back from common delete -- redrawing");
  if(typeOfScript!='b')  redrawGrid(objPtr);
//SysFatalAlert("leaving delete code");
}   
//-------------------------------------------------------------------------------
//  common row removal
//-------------------------------------------------------------------------------
int gridCommonRemoveRow(struct ObjectData *objPtr, int controlid,int row)        
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
       
   
     
      for(col=objPtr->howManyColsInBind;col<objPtr->cols;++col)
      {
 
          if(*(gridCellPtr(objPtr,row,col)))
          {
              MemPtrFree(*(gridCellPtr(objPtr,row,col))); 
          }  
 
      }
       if (objPtr->numItems>(row+1)) 
      {
         //handle remaining items
 
          op=(char*)(objPtr->itemData)+4*(row+1);
         np=(char*)op-4;
         MemMove(np,op,(objPtr->numItems-(row+1))*4);
     
 
 
         (char*)op=(char*)(objPtr->gridContent)
                  +4*(row+1)*(objPtr->cols-objPtr->howManyColsInBind); 
         (char*)np=((char*)op
                  -4*(objPtr->cols-objPtr->howManyColsInBind));                  
         MemMove(np,op,
            (objPtr->numItems-(row+1))*4*(objPtr->cols-objPtr->howManyColsInBind));

 
        
    
      }
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

      
  }
 }

//------------------------------------------------------------------------------- 
//    bind grid to database   
//-------------------------------------------------------------------------------
int gridBindToDatabase(FormPtr frm,VoidPtr controlPtr)
{
     MemHandle           newContentHandle;   //added 08152004
     char*               dbName;
     int                 logvarNo;
     struct ObjectData * objPtr;
     struct gridColInfo* cptr;
     int                 nBound=0;          //#cols bound to db
     struct dbType *     db;  //database ptr 
     int                 err;
     struct dbField *    dbFld;
     Boolean             dbWasOpened;
     long                whereClause;
     unsigned short      flags;
     unsigned int        dbRecNo;
     unsigned long       newLength;
     DmOpenRef           dbr;
     int                 colNo;
     int fldNo;
     char* name;
//SysFatalAlert("entering bind 0");       
     controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
     objPtr=locateObjectPtr(controlid); 
     objPtr->numItems=0;
     objPtr->firstRow=0;     
     objPtr->refreshFromDatabase=true;
     
//SysFatalAlert("aa");
     objPtr->dbNo=   find_integer()-1;  //modified 06112005
      
     dbNo=objPtr->dbNo;
//StrPrintF(debug,"got dbno=%d controlid=%d formID=%d",dbNo,controlid,FrmGetFormId(frm));
//SysFatalAlert(debug);
     db=getDatabasePtr();

//StrPrintF(debug,"entering 'bind' --instr_ctr=%u",instr_ctr);
//SysFatalAlert(debug);

//name=MemHandleLock(db->hName);
//StrPrintF(debug,"got database #=%d dbMemPtr=%lu lid=%lu noFields=%d name=%s keyFldNo=%d",dbNo,db,db->lid,db->noFields,name,db->keyFldNo);
//SysFatalAlert(debug);    
//MemHandleUnlock(db->hName);
     
     while(1)   //for each db fld bound to database
     {
//SysFatalAlert("bind 2");    
         fldNo=find_integer();
         if(fldNo==1000) break;
         if(++nBound >  objPtr->cols)
         {
             SysFatalAlert("Trying to bind more db fields to grid than there are columns of the grid.");
             return(0);
         }    
//SysFatalAlert("bind 3");               
         //set flds of grid column 
         cptr=locateGridColInfo(objPtr, nBound-1);            
         cptr->dbColNo=fldNo;
//StrPrintF(debug,"col#=%d",fldNo);
//SysFatalAlert(debug);
         cptr->dbSupplied=true;              
    }
    
    objPtr->howManyColsInBind =nBound; 
//SysFatalAlert("past cols bind");
   
    if(db->openSw!='o') 
    {
//SysFatalAlert("had to open db");    
         dbWasOpened=true;
         if(! gridOpenDb(db))
         {
           dbName=MemHandleLock(db->hName);
           StrPrintF(debug,"The database '%s' linked to a bound grid cannot be opened",dbName);
           MemHandleUnlock(db->hName);
           MiscFatalAlert(debug);
           goto skipWhere;
         }  
    }
    else
    {
//SysFatalAlert("db already open");    
    }
//SysFatalAlert("past db open");
    dbr=db->dm;
    
    whereClause=instr_ctr;    
    if(*((char*)codePtr+instr_ctr)==0x5c)   //if a where clause
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
//StrPrintF(debug,"dbr=%lu No of db records = %d",dbr,DmNumRecords(dbr));
//SysFatalAlert(debug);
//SysFatalAlert("6");
       objPtr->numItems=0;
       for(dbRecNo=0; dbRecNo < DmNumRecords(dbr); ++dbRecNo )  //step thru all records
       {
//SysFatalAlert("proc rec 1"); 
          DmRecordInfo(dbr,dbRecNo,&flags,NIL,NIL);
          if(flags & 0x80) continue;              //skip -- it's a delet4ed record
//SysFatalAlert("proc rec 2");            
          
          if(*((char*)codePtr+instr_ctr)==0x5c)   //if a where clause
          {
//SysFatalAlert("executing where clause");                 
           gridSetDatabaseFields(db,dbr,dbRecNo);
            
            db->LastDbRecordRead=dbRecNo+1;  
            instr_ctr+=3;              
            executeSomeCode(); 
               
            logvarNo=find_integer();
               
            if(logic_var [logvarNo] == 0)
            {
//StrPrintF(debug,"DID NOT select rec=%dVar=%d  log", dbRecNo+1,logvarNo);
//SysFatalAlert(debug);
                  goto recordAgain;  //skip -- record did not meet where clause
            }      
          }  
//StrPrintF(debug,"selected rec=%d logVarNo=%d", dbRecNo+1,logvarNo);
//SysFatalAlert(debug);                          
        
          //add new row's user data
          if((MemPtrSize(objPtr->itemData)/4) <= (objPtr->numItems)) 
          {
              objPtr->itemData=resizePtr(objPtr->itemData,400);
          }
          *((ULong*)((char*)(objPtr->itemData)+4*(objPtr->numItems )))=dbRecNo+1;  //02062004 modified 
//SysFatalAlert("proc rec 3");           
          //add new row's cell content
          if( objPtr->cols > objPtr->howManyColsInBind)
          {
            if(objPtr->gridContent==0)
            {
                objPtr->gridContent=MemHandleLock(MemHandleNew(4*(objPtr->cols-objPtr->howManyColsInBind) )); 
           	} 
            else
            {
                 
                objPtr->gridContent=resizePtr(objPtr->gridContent,4*(objPtr->cols-objPtr->howManyColsInBind));      
            }
            for(colNo=objPtr->howManyColsInBind;colNo<objPtr->cols;++colNo)
            {
               newLength= 4l*((long) ( (objPtr->numItems*(objPtr->cols-objPtr->howManyColsInBind) 
                        + colNo-objPtr->howManyColsInBind )));
               *((VoidPtr*)((char*)(objPtr->gridContent)+newLength))=0;                                           
            }
 
          }  
 
//if(objPtr->numItems>8500)
//{
//StrPrintF(debug,"Record # %d", objPtr->numItems);
//SysFatalAlert(debug);                  
//}
                     
          objPtr->numItems+=1;
recordAgain:      
          instr_ctr=whereClause;  //reposition to where clause
      }  
    } 
//SysFatalAlert("processed all db recs"); 
    if (dbWasOpened)  commonDbcloseLogic(db);   
skipWhere:   
    //skip where clause code if there
    if(*((char*)codePtr+instr_ctr)==0x5c)   //skip where clause
    {
//SysFatalAlert("skipping 5c at end lof load");
          instr_ctr += 1;               
          instr_ctr =  find_offset(); 
//StrPrintF(debug,"leaving 'bind' --instr_ctr=%u",instr_ctr);
//SysFatalAlert(debug);            
    } 
   
        
//

//StrPrintF(debug,"exiting bind logic #recs=%d",objPtr->numItems);
//SysFatalAlert(debug);     
    
   
    
    
    
    if(typeOfScript=='b') 
    {
//SysFatalAlert("formatting");
        gridFormat( objPtr ); 
    }
    else
    {
//SysFatalAlert("redrawing");
        redrawGrid(objPtr);
    }
  
}
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
  
void ScrollGrid(TableType* grid ,int idx, int lines)
{
    struct ObjectData *objPtr;
 
//SysFatalAlert("in scroll grid routine");
    objPtr=locateObjectPtr(FrmGetObjectId(FrmGetActiveForm(),idx));
    objPtr->firstRow=objPtr->firstRow+lines;    //noLines may be + or -
    
    if(objPtr->firstRow<0) objPtr->firstRow=0;    
    if (objPtr->firstRow>(objPtr->numItems-1)) objPtr->firstRow=objPtr->numItems-1;   
    objPtr->refreshFromDatabase=true;
                              
    redrawGrid( objPtr);                         
}

//-------------------------------------------------------------------------------
//  add a row to a grid
//-------------------------------------------------------------------------------

void gridAdd(FormPtr frm,VoidPtr controlPtr)
{
  struct ObjectData *objPtr; 
  int stat;
 

  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  objPtr=locateObjectPtr(controlid);                 //locate our own info about this table display object
 
  stat=gridCommonAddRow( objPtr, controlid);
 
  if(typeOfScript!='b')  redrawGrid(objPtr);
    
}
int gridCommonAddRow(struct ObjectData *objPtr, int controlid)
{
   VoidPtr p;
   
  VoidHand theHand;
  char * textP;
  char blankText[]=" ";
   Err err;
  
  int row;
  int col;
  int res;
        
  if( objPtr->howManyColsInBind==0)                     //can only add rows to non-bound grid
  {
   
    if( (calcFreeMemory()<4*(objPtr->cols-objPtr->howManyColsInBind)*(objPtr->numItems+1))
    ||  (calcFreeMemory()<(4*(objPtr->numItems+1))))
    {
memAllocError:
          
           misc_text_abort("Not enough memory to load grid data");
        
    }    
    //expand grid content to handle another row of col ptrs
    if(!objPtr->gridContent)
    {
       objPtr->gridContent=MemHandleLock(MemHandleNew(4*(objPtr->numItems+1)*(objPtr->cols-objPtr->howManyColsInBind))); 
    }
    else
    {
       objPtr->gridContent=resizePtr( objPtr->gridContent, 4*(objPtr->cols-objPtr->howManyColsInBind) );                         
    }

    
    row=objPtr->numItems;
    objPtr->numItems +=1;

      
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
 
    return(res);
  }
}

void gridShowGridLines( FormPtr frm,VoidPtr controlPtr )
{
      struct ObjectData * objPtr;
      
      controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
      objPtr=locateObjectPtr(controlid); 
  

      objPtr->wantGridLines = 'y';
}
void gridHideGridLines( FormPtr frm,VoidPtr controlPtr )
{
      struct ObjectData * objPtr;
      
      controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
      objPtr=locateObjectPtr(controlid); 
  
    
      objPtr->wantGridLines = 'n';
}
//------------------------------------------------------------------------------- 
//     record the type of column format to use     
//-------------------------------------------------------------------------------
void gridColType(FormPtr frm,VoidPtr controlPtr )
{
  char oldColumnType;
  int  col;
   char* textP;
		    int rowX;
		    int colX;
  char colType;
  struct gridColInfo* cptr;
  struct ObjectData * objPtr;
 
  col=find_integ_arg()-1;   
  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  objPtr=locateObjectPtr(controlid);   
  
 
  find_arg_1();                        //type
  find_arg_3();                        //format string                       
  
//StrPrintF(debug,"col=%d type=%s  format=%s",col,arg1_val,arg3_val);
//SysFatalAlert(debug);  
  if(isGridColumnValid(objPtr,col))
  {
    
    cptr=locateGridColInfo(objPtr, col);            
    oldColumnType=cptr->type;
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
    StrPrintF(debug,"Illegal column type (%s) used",arg1_val);
    SysFatalAlert(debug);
ok:    
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
  	
  	
  }
      
}


//-------------------------------------------------------------------------------
//         redraws a grid object
//-------------------------------------------------------------------------------
void redrawGrid(struct ObjectData * objPtr)
{
    TableType* grid;
    
    int i;
     
         
    RectangleType bounds;
//StrPrintF(debug,"in redraw --hidden=%d",objPtr->hidden);
//SysFatalAlert(debug);
 
//SysFatalAlert("in redrawGrid");
	grid=(TableType*)FrmGetObjectPtr(FrmGetFormPtr(objPtr->frmId),objPtr->index);
	 
	
	TblEraseTable((TableType*) FrmGetObjectPtr(FrmGetFormPtr(objPtr->frmId), objPtr->index) );   
    //04242004 TblGetBounds (grid, &bounds);
    //bounds.extent.x+=2;
    //bounds.extent.x-=2; 
//SysFatalAlert("past erase tbl");
	objPtr->refreshFromDatabase=true;
	if(! objPtr->hidden )
	{
	 	gridFormat( objPtr );      
//SysFatalAlert("back from gridFormat");    
    	TblDrawTable((TablePtr)(FrmGetObjectPtr(FrmGetFormPtr(objPtr->frmId),objPtr->index))); 
//SysFatalAlert("after tableDraw");    
    	if( (objPtr->currentRow>=objPtr->firstRow)&&((objPtr->currentRow-objPtr->firstRow)<objPtr->visibleRows))
        	  TblSelectItem((TableType*)FrmGetObjectPtr(FrmGetFormPtr(objPtr->frmId),objPtr->index),objPtr->currentRow-objPtr->firstRow,objPtr->currentCol);
    
   		 
//SysFatalAlert("getting bounds");        
    	TblGetBounds (grid, &bounds);
    
    	bounds.extent.x=0;
    	for(i=0;i<objPtr->cols;++i) 
    	{ 
            bounds.extent.x += (locateGridColInfo(objPtr, i))->width+1 ;
   		}
   		 
   		bounds.extent.y=0;
    	for(i=0;i<objPtr->visibleRows;++i) 
    	{ 
            bounds.extent.y += 12;
   		}      
//SysFatalAlert("DrawingFrame");
//StrPrintF(debug,"bounds.x=%d",bounds.extent.x);
//SysFatalAlert(debug);
    	 
        bounds.extent.x-=1;
    	bounds.extent.y-=1;
    	
    	if(objPtr->wantGridLines == 'y'  )  //added 08232004 only draw bounding rectangle if want grids
    	{                //added 08232004
    	   //added following IF on 04242004
    	   //06072004 if( (bounds.topLeft.x+bounds.extent.x-1) <= (objPtr->origGridBounds.topLeft.x+objPtr->origGridBounds.extent.x))
    	   if( (bounds.topLeft.x+bounds.extent.x) <= (objPtr->origGridBounds.topLeft.x+objPtr->origGridBounds.extent.x))
    	        WinDrawRectangleFrame( simpleFrame,&bounds);
    	   else
    	  {
    		bounds.topLeft.x = objPtr->origGridBounds.topLeft.x;   //added 06072004 
    		bounds.topLeft.y = objPtr->origGridBounds.topLeft.y;   //added 06072004
    		bounds.extent.x = objPtr->origGridBounds.extent.x -1;     //added 06072004
    		bounds.extent.y = objPtr->origGridBounds.extent.y-1;        //added 06072004
    		//06072004 WinDrawRectangleFrame(simpleFrame,&objPtr->origGridBounds);  // EMP added 051204 to make demo look good
    		WinDrawRectangleFrame(simpleFrame,&bounds);  //06072004 // EMP added 051204 to make demo look good
    	  }
    	}  //added 08232004
    }
    else
    {
/*commented out 06072004
         //grid is hidden
         TblGetBounds (grid, &bounds); //added 02062004
         bounds.extent.x-=1;  //added 02062004
    	 bounds.extent.y-=1;  //added 02062004
    	 //added following IF on 04242004
    	 //06072004 if( (bounds.topLeft.x+bounds.extent.x-1) <= (objPtr->origGridBounds.topLeft.x+objPtr->origGridBounds.extent.x))
    	 if( (bounds.topLeft.x+bounds.extent.x) <= (objPtr->origGridBounds.topLeft.x+objPtr->origGridBounds.extent.x))
    	     	WinEraseRectangleFrame (simpleFrame,&bounds );
    	else
    	{
SysFatalAlert("Erasing 1");
    	    //changed 06072004 from winDRAW to winERASE (ldm)
    	    WinEraseRectangleFrame(simpleFrame,&objPtr->origGridBounds);  // EMP added 051204 to make demo look good
 		}
*/

//start of insertions 06072004
		TblGetBounds (grid, &bounds);
    
    	bounds.extent.x=0;
    	for(i=0;i<objPtr->cols;++i) 
    	{ 
            bounds.extent.x += (locateGridColInfo(objPtr, i))->width+1 ;
   		}
   		 
   		bounds.extent.y=0;
    	for(i=0;i<objPtr->visibleRows;++i) 
    	{ 
            bounds.extent.y += 12;
   		}      
//SysFatalAlert("DrawingFrame");
//StrPrintF(debug,"bounds.x=%d",bounds.extent.x);
//SysFatalAlert(debug);
    	 
        bounds.extent.x-=1;
    	bounds.extent.y-=1;
    	
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
//end insertions 06072004
    }
}


//-------------------------------------------------------------------------------
//  
//-------------------------------------------------------------------------------

void gridFormat( struct ObjectData *objPtr)
{
   TablePtr          grid;
   FormPtr           frmPtr = FrmGetFormPtr(objPtr->frmId);
   ScrollBarType *   scr=0;
   int               idx=objPtr->index;
    
   int           row;
   int           col;
   
   
   
   grid=(TablePtr)(FrmGetObjectPtr(frmPtr,idx));
   //09242003 grid->attr.editable=1;   
//SysFatalAlert("gridFormat----start rows");  
   for(row=0;row<objPtr->visibleRows;++row)
   {
         //04012005 FntSetFont(TblGetItemFont (grid,  row, 0));
         TblSetRowHeight           (grid,row,FntLineHeight()+1);
         TblSetRowUsable           (grid, row,true);
         TblSetRowSelectable       (grid, row,true);
         
                       
	     for(col=0;col<objPtr->cols;++col)
         {
	         if(row==0)
	         {
//StrPrintF(debug,"setting callback id=%d col=%d",objPtr->id,col);
//SysFatalAlert(debug);
	              TblSetCustomDrawProcedure(grid, col, gridDrawCallback);
             }            
             FntSetFont(TblGetItemFont (grid,  row,col));  //added 04012005
             TblSetColumnUsable(grid, col,true);
	         TblSetItemStyle   (grid, row,col,customTableItem);
         }
                    
    }   
//SysFatalAlert("gridFormat-------done rows");
    objPtr->scrollMin=0;
    objPtr->scrollMax=objPtr->numItems-objPtr->visibleRows;   
    if (objPtr->scrollMax<0) objPtr->scrollMax=1;
   
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
    if( (objPtr->firstRow+objPtr->visibleRows)>objPtr->numItems)
	{
	     objPtr->firstRow= objPtr->numItems-objPtr->visibleRows;
	     if(objPtr->firstRow<0) objPtr->firstRow=0;
	}
	if(  (objPtr->numItems)<=objPtr->visibleRows)
	{
//SysFatalAlert("hiding scrollbar");
         if(  romVersion < 0x03400000)
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
              FrmHideObject(FrmGetActiveForm(),objPtr->index+1);  
           }  
         } 	                                   
    }
	else
	{
	     if(scr!=0)
         {
//SysFatalAlert("showing scrollbar");
                FrmShowObject(FrmGetActiveForm(),objPtr->index+1); 
	            SclDrawScrollBar(scr);
                SclSetScrollBar(scr, objPtr->firstRow,objPtr->scrollMin,objPtr->scrollMax,objPtr->scrollPagesize); 
         }    
    }
    
}
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
        if( (chkBounds.topLeft.x + chkBounds.extent.x) > (objPtr->origGridBounds.topLeft.x+objPtr->origGridBounds.extent.x - 1))
        {
        	chkBounds.extent.x = (objPtr->origGridBounds.topLeft.x+objPtr->origGridBounds.extent.x -1 - chkBounds.topLeft.x);
        }
        else
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
             if(cptr->type=='s')        //modified 07122005
             {                          //inserted 07122005
                       valuePtr=gridTextPtr( objPtr, cptr, row,&workString[0],grid,&coltype);
                       if( valuePtr ==0) goto cellEmpty;          //inserted 07122005
             }                                                    //inserted 07122005
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
   if(objPtr->wantGridLines == 'n');           //08152004
   else                                 //08152004
       WinDrawRectangleFrame( simpleFrame,&chkBounds);          
     
    FntSetFont(oldFontID);    //08022005 
    return ;
}
//-------------------------------------------------------------------------------
//  
//-------------------------------------------------------------------------------
char* gridTextPtr(struct ObjectData * objPtr,struct gridColInfo* cptr, int row
                 ,char *workString, TableType*grid,   int*coltype)
{
 
  struct dbType *db;
  struct dbField *dbColPtr;
  DmOpenRef dbr;
  unsigned long dbDataOffset;
  VoidHand recHand;
  VoidPtr  recPtr;
  
  
  int i;
  int j;
  int k; 
  unsigned int shortInt;
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
  unsigned short flags;
  char wk[128];
  unsigned char tm[3];
  DateType dt;
  struct dataelem  dummy;
           //db=setDbPtr(objPtr->dbNo);          
//SysFatalAlert("getTextPtr 1");
           dbNo=objPtr->dbNo;
           db=getDatabasePtr();
           if(db->openSw!='o')
           {
             //02052004 if(gridOpenDb(db)==0) MiscFatalAlert("Database needed for grid cannot be opened.");dbWasOpened=true;
             //begin insertions 02052004
             if(! gridOpenDb(db))
             {
		           dbName=MemHandleLock(db->hName);
		           StrPrintF(debug,"The database '%s' linked to a bound grid cannot be opened",dbName);
		           MemHandleUnlock(db->hName);
		           MiscFatalAlert(debug);
		           goto exitNow;
		     }      
           }
             //end insertions 02052004
           dbr=db->dm;
      
           if(objPtr->bindToDbHasWhereClause==true) 
           {
                   index=*((ULong*)((char*)(objPtr->itemData)+4*(row+objPtr->firstRow)))-1; //02062004 modified
           }
           else
           {
                     index=row+objPtr->firstRow;      
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
           db->LastDbRecordRead=index+1;
          

           dbColPtr=setDbField(db,cptr->dbColNo);    
           recPtr=MemHandleLock(recHand);          
           dbDataOffset=positionToDbField(db,dbColPtr, recPtr );   
           *coltype=dbColPtr->type;        
//SysFatalAlert("getTextPtr 8");
           switch(dbColPtr->type)          
           {
             case dbFldTypeString:  
               valuePtr=(char*)recPtr+dbDataOffset;
               break;
             case dbFldTypeLongInt:  
               MemMove(&ui,(char*)recPtr+dbDataOffset,4);
               val=ui;   

               dummy.kind='n';
               dummy.dgt_bef=16;
               dummy.dgt_aft=0;
               
               goto formatIt;            
               
             case dbFldTypeDouble:   
               MemMove(&val,(char*)recPtr+dbDataOffset,8);
               dummy.kind='n';
               dummy.dgt_bef=16;
               dummy.dgt_aft=16;
               
formatIt:
               if(cptr->type=='c')
               {
                  if(chkFormatYesNo(&val,cptr->format,workString)!=1)
    	       	  {
     			      DoubleToStr(val,wk);             
                      commonFormatCode(wk,cptr->format,workString);   
                   }
               }
               else
               { 
                 if(cptr->type=='n')   
                 {
                      DoubleToStr(val,wk);            
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

               dummy.kind='n';
               dummy.dgt_bef=16;
               dummy.dgt_aft=0;
               
               goto formatIt; 
                
	          case dbFldTypeSingle:  
	           MemMove(&f,(char*)recPtr+dbDataOffset,4);
	           val=f;
               dummy.kind='n';
               dummy.dgt_bef=16;
               dummy.dgt_aft=16;
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
           if (db->openSw=='o')  commonDbcloseLogic(db);   //02052004 
          return(valuePtr);

              
}

//-------------------------------------------------------------------------------
//  
//-------------------------------------------------------------------------------
double gridValue(struct ObjectData * objPtr,struct gridColInfo* cptr, int row
                 , TableType*grid,   int*coltype)
{
 
  
  struct dbType *db;
  struct dbField *dbColPtr;
  DmOpenRef dbr;
  unsigned long dbDataOffset;
  VoidHand recHand;
  VoidPtr  recPtr;
  
  
  int i;
  int j;
  int k; 
    
  unsigned int shortInt;
  float f;
  ULong ui;
  Long  l;
  ULong index;
  
  double val=0;
  //double *valuePtr=0;
  double t;
  unsigned short flags;
  //char wk[128];
  unsigned char tm[3];
  //DateType dt;
  double dt;
  //struct dataelem  dummy;
           //db=setDbPtr(objPtr->dbNo);          
//SysFatalAlert("getValuePtr 1");
   
  
           dbNo=objPtr->dbNo;
           db=getDatabasePtr();
           if(db->openSw!='o') if(gridOpenDb(db)==0) MiscFatalAlert("Database needed for grid cannot be opened.");
           dbr=db->dm;
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
           
           
                  
           dbDataOffset=positionToDbField(db,dbColPtr, recPtr );   
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
         StrPrintF(debug,"No current record for database=%s",p);
         MemHandleUnlock(db->hName);
         MiscFatalAlert(debug);
      }
      if(db->LastDbRecordRead>DmNumRecords(dbr))
      {
          p=MemHandleLock(db->hName);
          StrPrintF(debug,"End-of-file for database=%s",p);
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
//start additions 02062004
//-------------------------------------------------------------------------------
// return the number of the topRow being displayed in the grid
//-------------------------------------------------------------------------------
void gridGetTopRow(FormPtr frm,VoidPtr controlPtr)
{
  
  struct ObjectData *objPtr;
   
  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));
  objPtr=locateObjectPtr(controlid);   //get the ptr to our obj data        
  restore4(objPtr->firstRow+1);          //return the top rows
       
}
//-------------------------------------------------------------------------------
// set the topRow being displayed in the grid
//-------------------------------------------------------------------------------

void gridSetTopRow(FormPtr frm,VoidPtr controlPtr,double* paramPtr)
{
 
  
  int toprow;
  
  struct ObjectData *objPtr;
   
  
  toprow=*paramPtr-1; 
  controlid= FrmGetObjectId(frm,getGridIndexFromPtr(frm,controlPtr));                                    //ctlid is 1st arg
  objPtr=locateObjectPtr(controlid);              //get the ptr to our obj data             
  
                          //calc the row # as integer (1-based)
  
  if(isGridRowValid(  objPtr,  toprow))         //if row is valid
  {
      objPtr->firstRow=toprow;                         //save as the top row
    
      objPtr->refreshFromDatabase=true;                 //and tell to reload visible grid
     
      if( typeOfScript != 'b' )  redrawGrid(objPtr);  // redraw
       
  }
}
void freeCellContents( struct ObjectData* objPtr)
{
	    char* textP;
	    int row;
	    int col;
	    for(row=0;row<objPtr->numItems;++row)
        {
           for(col=objPtr->howManyColsInBind;col<objPtr->cols;++col)
           {
             
             textP=*( gridCellPtr(objPtr,row,col));
             if(textP)      MemPtrFree( textP);
             *( gridCellPtr(objPtr,row,col))=0;
           }
        }
}

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
