


#include <PalmOS.h>
#include <PalmTypes.h>
#include <PalmCompatibility.h>
#define nil 0
#include <Form.h>
#include <FatalAlert.h>
#include <DataMgr.h>
#include <MemoryMgr.h>
#include <StringMgr.h>
#include <ScrollBar.h>
#include <Event.h>
#include <SysEvtMgr.h>
#include <SerialMgr.h>
#include <SerialMgrOld.h>
#include <ErrorBase.h>                   //05212003
#include <SoundMgr.h>					 //01192004
#include <Control.h>
#include <window.h>
#include <mathlib.h>

#include "NSBPNOShared.h"				//06.20.2005 GWH
#include "copy.h"

#include <ModemMgr.h>
#include <PalmOSGlue.h>  //GHGlue

unsigned long debuggerFindInteger(char*s , int length);  //added 04012005
extern void redrawGrid(struct ObjectData * objPtr); //09242003
double misc_int(double x);

void SetFieldText( UInt nFieldID, const CharPtr pSrcText, Int nMaxSize, Boolean bRedraw);
extern void dbugx(double* x,char*identifier);
void FreeListValues(VoidPtr pold,int noItems ); //added 5.21.2000
VoidHand saveObjectHandle;                     //added 5.21.2000

struct ObjectData * locateObjectPtr(Word id);  //added 5.21.2000

typedef long DATE; /*Julian dates*/
void restore_integ_value(int i,struct dataelem * arg,double * arg_ad,
unsigned int arg_occ1,unsigned int arg_occ2,unsigned int arg_occ3) ;  
extern int           applVersionInteg;
extern int           applVersionFrac;
extern void misc_text_abort( char * msg );

extern  void UpdateScrollbar(FieldPtr field, ScrollBarPtr scroll);
extern misc_stodbl(struct dataelem *d,  unsigned int sub1,unsigned int sub2,unsigned int sub3, double  *result);
extern misc_stostr1(char *s);
extern misc_stostr2(char *s);
extern misc_stostr3(char *s);
extern misc_stostr4(char *s);
extern misc_stostr5(char *s);
void misc_fix(int i, char *res, int num);
extern struct dataelem *find_arg_nosubs(unsigned int *s1,unsigned int *s2, unsigned int *s3);
extern double misc_floor(double x);
int misc_format_number(struct dataelem* v, double* n , char * s);
struct dataelem *find_arg(unsigned int* s1, unsigned int* s2,  unsigned int *s3,
                                struct dataelem**sde1, struct dataelem** sde2, struct dataelem** sde3);
void misc_stodbl1(double* x);
void misc_stodbl2(double* x);
void misc_stodbl3(double* x);
void misc_stodbl5(double* x);
void DoubleToStr (double val, CharPtr str);
int misc_format_number(struct dataelem* v, double* n , char * s);
extern int integ_value( struct dataelem *  arg, double *    arg_ad);        /*---calc integ value of data elem__*/
double misc_fabs(double x);
UInt16 miscFrmGetObjectIdFromPtr(const FormType *formP, void *objP);  //GH  01.10.2002

void restore4(int i);
void test_debug(char *msg);
void store4( double *d);
void storestr4( char *s);

extern void verb_signatureErase();
void verb_signatureStartCapture();
void verb_signatureDisplay();

void commonStartCapture(FormPtr frmPtr, int controlid);
void commonErase(FormPtr frmPtr, int controlid);

void commonSignatureDisplay(FormPtr frmPtr, int controlid, struct dataelem* argx, char *argx_val);

int getx();
int gety();
extern misc_stodbl(struct dataelem *d,  unsigned int sub1,unsigned int sub2,unsigned int sub3, double  *result);
extern void verb_function_doit (unsigned int it);
int more_processing();
extern void misc_errmsg( char * the_msg);
extern void setupADataelem(int i);
void function_doit(unsigned int it);
void setSerErr(Err err);
void serialWakeupHandler(UInt32 refCon);									//03.06.02 GH
ULong serialReceiveAfterEvent(Char *outBuf, UInt32 outSize);				//03.06.02 GH
static Err DoReceiveWindowOpen(UInt16 portId, UInt8 **bufPP, UInt32 *sizeP);//03.06.02 GH
static Err DoReceiveWindowClose(UInt16 portId, UInt32 bytesPulled);			//03.06.02 GH
void serialSetState(UInt8 state);	//03.06.02 GH

void dbGetSome(void* from,int len,void*to);
extern struct dataelem *elem_tbl_ptr(unsigned int de_no) ;
void chkMathlibOpen();
void debug_addr( char *  x);
int ExitHousekeeping();
int launchPgm();
int dbugKind(char*s);
void function_doit(unsigned int it);
extern misc_getint(struct dataelem *d,  unsigned int sub1,
unsigned int sub2,unsigned int sub3,  unsigned int  *result);
void dbug(char*s);

void calendar_date(DATE jdate, int *day, int *month, int *year);
int valid_date(int day, int month, int year);
int day_of_week(DATE jdate );

extern int maxVarsInDynamHeap;    //06012002  max # of vars to alloc in dymam heap
extern int       fldToUpdate;
extern unsigned int find_integer();                   /**/
struct file_entry * locate_file_by_no( unsigned long n );
struct dict_entry * locate_dict_by_no( unsigned long n );
struct dict_entry * find_dict_entry();
struct file_entry * find_file_entry();
unsigned long long_integ_value(struct dataelem *arg, double *arg_ad);        /*---calc integ value of data elem__*/

extern int integ_value(struct dataelem * arg, double* arg_ad);      
extern void verb_func_getGeneralPropertyNumeric();
extern void verb_func_getGeneralPropertyString();
void set_sub(int n, struct dataelem *arg, unsigned int* sub_val, struct dataelem *sub_de);
unsigned char find_char();

void setDbErr(int err);
void setDbOK();
void setDbRes(int err);

extern void store_reg(double *r1,struct dataelem* de, double*elem_ad,
      unsigned int  elem_occ1,unsigned int elem_occ2,unsigned int elem_occ3)   ;     /*-------store reg to data elem---*/
		   /**/
unsigned long long_integ_value(struct dataelem *arg, double *arg_ad);        /*---calc integ value of data elem__*/
extern void round_reg(double *reg,struct dataelem* de)   ;
extern misc_stostr(struct dataelem * *d,  unsigned int sub1,unsigned int sub2,unsigned int sub3, char *result);
extern misc_stostr1(char*s);
extern misc_stostr2(char*s);
extern misc_stostr3(char*s);
extern misc_stostr4(char*s);
extern misc_stostr5(char*s);
extern misc_getdbl(struct dataelem *d, unsigned int sub1 ,unsigned int sub2,unsigned int sub3, double *result);
extern void EventLoop();
void find_arg_1();
void find_arg_2();
void find_arg_3();
void find_arg_4();
void find_arg_5();
void find_arg_6();
void find_arg_1_2();
void find_arg_1_3();
void find_arg_1_4();
//void find_arg_1_5();
void find_arg_1_nosubs();
void find_arg_2_nosubs();
void find_arg_3_nosubs();
void find_arg_4_nosubs();
void find_arg_5_nosubs();
extern unsigned int find_offset();
char *misc_allocate(unsigned int , char*);
void misc_getstr(struct dataelem* arg,int occ,char*name);
extern void move_it(char *to_ad,unsigned  to_len,char * from_ad,unsigned from_len);

unsigned long find_long_integer();                     /*---find next integer in code--*/
unsigned long misc_getlongint(struct dataelem  *,unsigned long ,unsigned long * );

Int database_compare(void* a, void *b,Int oth,SortRecordInfoPtr j,SortRecordInfoPtr k, VoidHand appInfoH);
struct dbType *getDatabasePtr( ) ;
void  setDatabasePtr(double* a,DmOpenRef dbref);
void readDbFields(struct dbType* db,VoidHand recHand,struct dataelem* * keyarg,
unsigned int sub1,unsigned int sub2,unsigned int sub3  );
int writeDbFields(struct dbType *db,VoidHand* recHand,char*key,int other,char addUpdt ,UInt recno) ;  //05282003
void chkDbOpen(struct dbType *);
Boolean find_ctlid(Boolean abortSw);
void dbfind_arg(int n);
void misc_stodbl1(double* x);
void misc_stodbl3(double* x);
void misc_stodbl2(double *x);
void misc_stodbl5(double* x);
int keyCompare(char* key, VoidPtr rec, int oth);
void cleareleedArgs();
void end_all_move_args();
void verb_setscrollbar();
void clearLockedArgs();
        void verb_generalVerb();
        void verb_setGeneralProperty();
        //void verb_controlssettext();
        void verb_seteventhandled();
        void verb_assign_bitmap();
        void verb_start_function();
        void verb_alert();
        void verb_sound();
        void verb_playsound();
        void verb_fillrectangle();
        void verb_drawrectangle();
        void verb_drawline();
        void verb_drawchars();
        void verb_erasewindow();
        void verb_destroywindow();
        void verb_createwindow();
        void verb_setcurwindow();
        void verb_dbposition();
        void verb_dbput();
        void verb_dbget();
        void verb_dbputnew();
        void verb_dbgetnew();
        void verb_dbclose();
        void verb_dbopen();
        void verb_dbcreate();
        void verb_dberase();
        void verb_dbreadnext();
        void verb_dbreadprev();
        void verb_dbgetnorecs();
        void verb_dbinsert();
        void verb_dbdelete();
        void verb_dbupdate();
        void verb_dbread();
        void verb_dbreset();
        void verb_dbfind();
        void verb_dbcreatedatabasefromresource();	//03.24.02 GH
        void verb_draw_bitmap();
        void verb_dowhile();
        void verb_dountil();
        void verb_menureset();
        void verb_menudraw();
        void verb_menuerase();
        void verb_user_func();
        void verb_sub();
        void verb_end_sub();
        void verb_end_function();
        void verb_call();
        void verb_controlsetstatus();
        void verb_controlsetstatusNew();
        void verb_controlsetlabel();
        void verb_controlhideorshow();
        void verb_fieldsettext();
        void verb_fieldsetmaxchars();
        void verb_listadditem();
        void verb_listclear();
        void verb_listdeleteitem();
        void verb_listsetselected();
        void verb_transfertoprogram();
        
        void verb_initAVariableValue ();
//#ifdef ORG_SWB
        void verb_setnumvarsfromheap();   //added 06102002
//#endif

        
        void verb_clearscreentextfields();    //added 06102002


        //void verb_mem_debug()       ;
        void verb_start_debug();
        void verb_end_debug();
        void verb_negate();
        void verb_add ()            ;
        void verb_display()         ;
        void verb_divide()          ;
        void verb_return()          ;
        void verb_if()              ;
        void verb_multiply ()       ;
        void verb_gosub()         ;
        void verb_stop ()           ;
        void verb_subtract()        ;
        void verb_return()          ;
        void verb_goto()            ;
        void verb_serialSend();
        void verb_serialReceive();
        void verb_serialSet();
        void verb_serialSetOld();			//03.04.02 GH
        void verb_serialDial();
        void verb_serialHangUp();
        void verb_serialReceiveWithEvent();	//02.26.02 GH
        void verb_beep();
        void verb_popupclear();
        void  verb_delay ()   ;
        void verb_exponentiation()    ;
        void verb_not_logic_oper()    ;
        void  verb_relat_logic_oper()  ;
        void  verb_logic_class_tests() ;
        void verb_and()               ;
        void verb_or()                ;
        void  verb_special_arith_store() ;
           
        void verb_getPen();
        void verb_compute()             ;
        void verb_check_on_size_error() ;
        void  verb_clear_frac_dgts()     ;
        void verb_nextscreen();
        
		void verb_nextscreenwithvariable();  //added 06102002
		void verb_redraw();
        void  verb_cursor_id();
        void  verb_redraw_id();
        
        void  verb_concat_two_strings();
        
        void verb_startfor();
        void verb_continuefor();
        void verb_next();
        void verb_do();
        void verb_until();
        void  verb_while();
        void verb_loop();
        void verb_exitdo();
        void verb_exitfor();
        void verb_launchprogram();
        void  verb_cursor();
        void  verb_errmsg();
        
        void  verb_end_logic_cond();
        void  verb_function();
        void verb_start_new_parag() ;
        void verb_start_new_stmt()  ;
        void illegal_op_code();

void OutOfMemory(int i);                //inserted 05212003
unsigned int serialBufferSize;
char*   serialBufferPtr;
typedef void opCodeFunc();
opCodeFunc *  op_func[256];



Word lastSubOrFunctionId;
int      dbNo;
Boolean  mathLibOpenSw=false;
char*    firstString=0;
int      debug_on;  //0=off 1=on

UInt     serRef;
Boolean  gOldSerialManager;						//02.27.02 GH	
UInt8    gSerialState;							//03.06.02 GH	

EventPtr evptr;
char     dummyCode[15];
char*    p3;
VoidHand h3;
extern char terminationAction;
extern int  mem_debug_sw;
extern long automated_redraw_time;
extern char automated_redraw_sw;
extern struct view_record * automated_view;
extern DmOpenRef CallerDB;


DATE julian_date(int day, int month , int year );

#define MAX_ARITH_PLUS_1          arith_work_de_max+1
#define MAX_ARITH_STRING_PLUS_1   arith_work_de_max+string_work_de_max+1

unsigned char op_code;
extern    int logic_value;

unsigned long load_index_occ;

extern char master_quit_sw;
int         btrieve_cur_rec_len;

    char *ad;

MdmInfoType modemInfo;    //info about modem parameters


 long moduleCntr;
 VoidHand forHandle;
 //06102002VoidHand forHandleSave;
 VoidPtr forPtrSave;
#ifdef ORG_NSB
#include "nsbasic.c"
#endif

/********************************************************************************************/
void verb_function()
{  
	 
// Cleaned up this section // 01/29/2001 MMD
	unsigned it = find_integer();
	unsigned no = find_integer();
	funcNoParams = no;
	
    


//StrPrintF(debug,"verb_func it=%d no=%d",it,no);
//SysFatalAlert(debug);
	// Nested these calls for speed // 01/29/2001 MMD
	// These are the arguments
	if( no > 0 )
	{
    	find_arg_1();
    	if( no > 1 )
    	{
    		find_arg_2();
			if( no > 2 )
			{
				find_arg_3();
				if( no > 3 )
				{
					find_arg_5();
				}
			}
		}
	}

	// This is the return value
	find_arg_4();

	if( ( it > 399 ) && ( it < 499 ) )
		find_ctlid(true);
	if( ( it > 499 ) && ( it < 600 ) )
		chkMathlibOpen();
	if( ( it > 599 ) && ( it < 649 ) )		// 02/27/2001 MMD
		find_ctlid(true);  //actually table id
	verb_function_doit( it );
	
} // verb_function

//just a transfer call to avoid 32k limit
void restore_int_val(int res,struct dataelem* arg1,double *arg1_val,
       unsigned int  arg1_occ1,unsigned int arg1_occ2,unsigned int arg1_occ3)
{
    restore_integ_value( res, arg1,(double *)arg1_val, arg1_occ1, arg1_occ2, arg1_occ3);

}
/********************************************************************************************/
void chkMathlibOpen()
{
  Err error;
  if(!mathLibOpenSw)
  {
      error=SysLibFind(MathLibName,&MathLibRef);
      if(error)
      {
         error=SysLibLoad(LibType , MathLibCreator,&MathLibRef);
         if(error)
         {
             SysFatalAlert("Can't find MathLib");
         }
      }   
      error=MathLibOpen(MathLibRef,MathLibVersion);
      if(error)
      {
          SysFatalAlert("Can't open MathLib");
      }
  }
  mathLibOpenSw=true;
}
/********************************************************************************************/
int codeexec(Word objId,unsigned long offset)
{               
		int sz;
		int result;
		VoidHand newCodeHand;
		struct codeBlock*  newCodePtr;
		VoidHand h2;
		VoidPtr p2;
		UInt idx2;
		VoidPtr tempPtr;
		void code_initialize();
		int err;
		 unsigned int debug_instr_ctr;
		 
		 lastSubOrFunctionId=objId;
		 

		//StrPrintF(debug,"at codeexec id =%d codePtr=%lu",objId,codePtr);
		//SysFatalAlert(debug);


	  testSw=2;
      if(objId==0)  return(0);
      if(init_first_time==0)
      {
         code_initialize();  /* *******go init to begin******** */
      }
//StrPrintF(debug," more processing for id=%d",objId);
//SysFatalAlert(debug);

      clearLockedArgs();
      if(codeBlockPtr->id==50000) instr_ctr=0;  //dummy control for root level
      sz=sizeof(sampleCodeBlock);
//if(debug_sw){
//StrPrintF(debug,"sz=%d",sz);
//SysFatalAlert(debug);      
//}
      newCodeHand=MemHandleNew(sz);
      if(newCodeHand==0) OutOfMemory(6043);    //05282003
      newCodePtr=(struct codeBlock*)MemHandleLock(newCodeHand);
      newCodePtr->prevCodePtr=codeBlockPtr;
      
      
      if(codeBlockPtr != 0)      					//added 04012005
      {                         					//added 04012005 
         codeBlockPtr->cur_stmt_no = cur_stmt_no;   //added 04012005
//StrPrintF(debug,"setting cur_stmt_no to %d",cur_stmt_no);
//SysFatalAlert(debug);
      }                          					//added 04012005
      codeBlockPtr=newCodePtr;
      
      codeBlockPtr->id=objId;
      codeBlockPtr->offset=offset;
      codeBlockPtr->p3=p3;
      codeBlockPtr->h3=h3;
      codeBlockPtr->numberParas=numberParas;
      codeBlockPtr->paragTbl=paragTbl;
      codeBlockPtr->codePtr=codePtr;
      codeBlockPtr->instr_ctr=instr_ctr;
//if(debug_sw){
//StrPrintF(debug,"setting codeblockptr=%lu codeptr=%lu instr_ctr=%d",
//(unsigned long)(codeBlockPtr),(unsigned long)(codePtr),instr_ctr);
//SysFatalAlert(debug);
//}
      codeBlockPtr->oldOffset=theCodeOffset;
      h3=DmGetResource(rscTag,(ULong)objId);  
      if(h3==0)
      {
//StrPrintF(debug,"no code for %d",objId);
//SysFatalAlert(debug);
         //no obj code
         h3=codeBlockPtr->h3;
         codeBlockPtr=(struct codeBlock*)codeBlockPtr->prevCodePtr;
         MemPtrUnlock(newCodePtr);
         MemHandleFree(newCodeHand);
         return(0);

      }
      
//StrPrintF(debug,"found code for %d",objId);
//SysFatalAlert(debug);
      ++moduleCntr;
      p3=(char*)MemHandleLock(h3);

      codeBlockPtr->newp3=p3;
      codeBlockPtr->newh3=h3;
      numberParas=*( (int*)p3);
      paragTbl=(char*)p3+*((unsigned int*)((char*)p3+2)); //pts to para offsets  //3132001
      theCodeOffset=offset;

      codePtr=(char*)p3+offset;
//if(debug_sw){
//StrPrintF(debug,"in codeexec p3=%lu offset=%lu codeptr=%lu",
//(unsigned long)p3,offset,(unsigned long)codePtr);
//SysFatalAlert(debug);      
//}

    if(*((char*)codePtr)==0x00)
    {
//StrPrintF(debug,"1st char of obj code was 0 -- exiting");
//SysFatalAlert(debug);
         goto getOutA;
    }

//dbug("codeexec --going to more processing");

    result=more_processing( );

getOutA:

//if(debug_sw){
//dbug("basc--after code executed");
//}
      h3=codeBlockPtr->newh3;
      p3=(char*)codeBlockPtr->newp3;
      MemPtrUnlock(p3);
      DmReleaseResource(h3);
      tempPtr=codeBlockPtr;
      p3=(char*)codeBlockPtr->p3;
      h3=codeBlockPtr->h3;

      numberParas=codeBlockPtr->numberParas;
      paragTbl=(char*)codeBlockPtr->paragTbl;
      theCodeOffset=codeBlockPtr->oldOffset;
      codePtr=(char*)codeBlockPtr->codePtr;
      instr_ctr=codeBlockPtr->instr_ctr;
      codeBlockPtr=(struct codeBlock*)codeBlockPtr->prevCodePtr;
      MemPtrUnlock(tempPtr);
      MemPtrFree(tempPtr);

      --moduleCntr;
      return(1);
}
/********************************************************************************************/
int basc_integ_value(struct dataelem * arg, double* arg_ad)
{
  return(integ_value( arg,  arg_ad));
}
/********************************************************************************************/
extern struct dataelem *find_arg_nosubs(unsigned int *s1,unsigned int *s2,
                                        unsigned int *s3)
{
    struct dataelem *arg;
    //03012002 struct dataelem *find_data_elem_no();
    //03012002 arg = find_data_elem_no();
    //03012002 --from find_data_elem_no
    unsigned int i;
    //03012002 struct dataelem *de=(struct dataelem *)null_ptr;
    unsigned char the_char;
    unsigned char *ad1;
    //03012002 unsigned the_integ;
    
  
    //03012002 i = find_integer();
    ad1 = (unsigned char *) &i;

    //03012002*ad1 = find_char();
    *ad1 = *((unsigned char*)(codePtr)+instr_ctr++);
    
    //03012002 *(ad1+1)=find_char();
    *(ad1+1) = *((unsigned char*)(codePtr)+instr_ctr++);
    
    //06/01/2002 if ( i == 0 )
     //06/01/2002   arg= (struct dataelem *)null_ptr ;
    //06/01/2002  else
      arg = elem_tbl_ptr(i);
    
    
             *s1=0;
             *s2=0;
             *s3=0;
    return(arg);
}
/********************************************************************************************/
void tooLarge(  int tbl_no,unsigned int sub, unsigned int max)
{
  char msg[128];
  StrPrintF(msg,"Subscript too large..variable=%d sub=%lu max=%lu",
     tbl_no,sub , max );
  misc_text_abort(msg); 
}
/********************************************************************************************/
extern unsigned int find_subscript()                /*---find next subscript in code---*/
{
    unsigned int sub;
    sub = find_integer();
    return(sub);
}
                                  /*-------set any argument-------*/
/********************************************************************************************/
extern struct dataelem *find_arg(unsigned int* s1, unsigned int* s2,unsigned int *s3,
                                 struct dataelem** s1_de, struct dataelem** s2_de,struct dataelem* *s3_de)
{
    int sub;
    char  msg[80];
    
    
    
//if(debug_sw){
//}
    //03012002arg = find_data_elem_no();
    
    
      struct dataelem *arg=(struct dataelem*)null_ptr;
    //03012002 struct dataelem *find_data_elem_no();
   
    //03012002 arg = find_data_elem_no();
    //03012002 --from find_data_elem_no
    unsigned int i;
    //03012002 struct dataelem *de=(struct dataelem *)null_ptr;
    unsigned char the_char;
    unsigned char *ad1;
    //03012002 unsigned the_integ;
//StrPrintF(debug,"in find arg");
    
    
    //03012002 i = find_integer();
    ad1 = (unsigned char *) &i;

    //03012002*ad1 = find_char();
    *ad1 = *((unsigned char*)(codePtr)+instr_ctr++);
    
    //03012002 *(ad1+1)=find_char();
    *(ad1+1) = *((unsigned char*)(codePtr)+instr_ctr++);
//dbug("aaa");    
     //06/01/2002 if ( i == 0 )
     //06/01/2002 {
     //06/01/2002 arg= (struct dataelem *)null_ptr ;
     //06/01/2002 }
     //06/01/2002 else
     //06/01/2002 {
      arg = elem_tbl_ptr(i);
     //06/01/2002 }
    //03012002 end of includes--
//dbug("bbb");    
    
    *s1=0;
    *s2=0;
    *s3=0;
    *s1_de=0;
    *s2_de=0;
    *s3_de=0;
    if( (arg != null_ptr ) && ( arg->max_no_values1>1) )
    {
//dbug("ccc");
            sub=find_subscript();
//dbug("ddd");
            if(sub==0) //  means that used array w/o subs
            {
//dbug("found array w/o sub");
              *s1=0;
              *s2=0;
              *s3=0;
              if(arg->max_no_values2>1) find_subscript();
              if(arg->max_no_values3>1) find_subscript();
              goto getOutB;
            }
//StrPrintF(debug,"looking for subs --got elem#=%d",sub);
//SysFatalAlert(debug);
            *s1_de  = elem_tbl_ptr(sub);
            set_sub(1, arg, s1, *s1_de );
             
            if((*s1 > (arg->max_no_values1 ) ) )
            {
               tooLarge( arg->tbl_no,((*s1)+1) ,  arg->max_no_values1 );
            }
            if( (arg != null_ptr ) && ( arg->max_no_values2>1) )
            {
              
              sub=find_subscript();
              if(sub==0)
              {
                 if(arg->max_no_values3>1) find_subscript();
                 goto getOutB;
              }
              *s2_de  = elem_tbl_ptr(sub);
              set_sub(2, arg, s2, *s2_de );
              
              if((*s2 > (arg->max_no_values2 - 1) ) )
              {
                tooLarge( arg->tbl_no,((*s2)+1) ,  arg->max_no_values2 );
              }
              if( (arg != null_ptr ) && ( arg->max_no_values3>1) )
              {
                sub=find_subscript();
                if(sub==0) goto getOutB;
                *s3_de  = elem_tbl_ptr(sub);
                set_sub(3, arg, s3, *s3_de );
                 
                if((*s3 > (arg->max_no_values3 - 1) ) )
                {
                   tooLarge(   arg->tbl_no,((*s3)+1) ,  arg->max_no_values3 );
                }
              }
            }
    }
getOutB:
    
//dbug("fff");     
    return(arg);
}
/********************************************************************************************/
extern void set_sub(int n, struct dataelem*arg, unsigned int*sub_val,struct dataelem* sub_de)         /*--set a sub from code--*/
    
{
//char test[80];
    char msg[81];

    
    unsigned int  reg_value;
    
        
        if(sub_de!=null_ptr) 
        {
           misc_getint(sub_de,0,0,0,&reg_value);
           if((reg_value)<=0)
           {
               StrPrintF(msg,"Found illegal subscript = %u",reg_value);
               misc_text_abort( msg );
               
           }
           else *sub_val = reg_value - 1;        
        }
        else *sub_val=0;
        
        return;
}
/********************************************************************************************/
int basc_dbGetInt(char* ptr)
{
  int i;
   char* p=ptr;
  *((char*)&i)=*p;
  ++p;
  *(((char*)&i)+1)=*p;
  return(i);
}

/********************************************************************************************/
void verb_divide()                          /*---------divide-------------*/
{
    char round_sw;
    find_arg_1_3();
    round_sw=find_char();
    reg_c=*((double*)arg1_val);
    reg_b=*((double*)arg2_val);

    if(reg_c==0.0)
    {
          misc_errmsg("Error divide by 0");
	  reg_a = 0;
    }
    else reg_a=reg_b / reg_c;
    
    misc_stodbl3(&reg_a);
    find_arg_4(); /* remainder (if there, save for later) */

    return;
}
//comment out starting here 09242003
/*int more_processing()
{
    struct dataelem* tempde;
    unsigned int     debug_instr_ctr;
    int   i;
    char *theInstruc;
    unsigned int instr_ctr_save=instr_ctr;
    
    logic_value=0;
    instr_ctr=0; //skip length on front
---end of comment out 09242003 */


//insertions start here 09242003
int more_processing()
{

    int res;
    instr_ctr=0; //skip length on front 
    res=    executeSomeCode();
    return(res);
}
int executeSomeCode()
{
     Err err;
    LocalID lid;
    UInt cdNo;
    DmSearchStateType st;
    struct dataelem* tempde;
    unsigned int     debug_instr_ctr;
    int   i;
    char *theInstruc;
    unsigned int instr_ctr_save=instr_ctr;
    
    logic_value=0;


//end of additions 09242003


    
//debug_instr_ctr=instr_ctr;
//if(debug_sw){
//StrPrintF(debug,"in more-proc instr_ctr=%d",instr_ctr);
//SysFatalAlert(debug);
//}
    theInstruc=(char*)codePtr+instr_ctr;

//if(debug_sw){
//StrPrintF(debug,"1st op code is %d at offset=%d",*((char*)theInstruc),instr_ctr);
//SysFatalAlert(debug);
//}

    if(*(theInstruc)==0x00)
    {
getOutB:
       instr_ctr=instr_ctr_save;
	 return(0);
    }
/*-----
StrPrintF(debug,"first_para_ptr=%p",first_para_tbl_ptr);
SysFatalAlert(debug);
-------*/
process_code :                  /*-------main processing loop------*/
    op_code = find_char();
    if(op_code==0x00)  //this means 00 wont be caught as illegal op code
    {
quitIt:
       clearLockedArgs();
       return(logic_value);  /*done*/
    }
     if (op_code==0xff)  goto quitIt;
     //additions 09242003
      if (op_code==0x5d)
     {
//02042006 SysFatalAlert("Found 5d op-code to end where clause");
         goto quitIt;        //bindToDatabase --end of a where clause 
     }
     //end of additions 09242003
    /*now use op code to choose a function address from */
    /* array of function pointers (op_func)             */
    /*An illegal op-code will go to "illegal_op_code"    */

//StrPrintF(debug,"going to exec opcode=%d ahead=%d",op_code,*((char*)codePtr+184));
//SysFatalAlert(debug);

    
    /*now use op code to choose a function address from */
    /* array of function pointers (op_func)             */
    /*An illegal op-code will go to "illegal_op_code"    */

    (*op_func[ (int)op_code ] )() ; /*this calls the function */

    clearLockedArgs();

    goto process_code;
}
/********************************************************************************************/
void clearArgs()
{
  arg1=(struct dataelem*)null_ptr;
  arg2=(struct dataelem*)null_ptr;
  arg3=(struct dataelem*)null_ptr;
  arg4=(struct dataelem*)null_ptr;
  arg5=(struct dataelem*)null_ptr;
  arg6=(struct dataelem*)null_ptr;
  
//SysFatalAlert("in clear args--arg3 follows");
//debug_addr((char*)arg3);
}

/********************************************************************************************/
void clearLockedArgs()
{
    if (arg1 !=(struct dataelem*)null_ptr) 
    { 
      
      arg1=(struct dataelem*)null_ptr;
    }
    if (arg2 !=(struct dataelem*)null_ptr) 
    {
//dbug("clearing 2");
       //MemPtrUnlock(arg2);
       arg2=(struct dataelem*)null_ptr;
    }
    if (arg3 !=(struct dataelem*)null_ptr) 
    {
       
       arg3=(struct dataelem*)null_ptr; 
    }
    if (arg4 !=(struct dataelem*)null_ptr) 
    { 
       
       arg4=(struct dataelem*)null_ptr;
    }
    if (arg5 !=(struct dataelem*)null_ptr) 
    {
       
       arg5=(struct dataelem*)null_ptr;
    }
    if (arg6 !=(struct dataelem*)null_ptr) 
    {
       
       arg6=(struct dataelem*)null_ptr;
    }
    
}
/********************************************************************************************/
void illegal_op_code()   /* if op_code no good, this func is performed */
{

    char msg[80];
   

//SysFatalAlert("at illeg op code");
   StrPrintF(msg,"Illegal op code=%d at offset%d ",op_code,instr_ctr);
    misc_text_abort(msg);
    return;
}


/********************************************************************************************/
extern int compare_args(struct dataelem*arg1, double* input_arg1_val,
      struct dataelem*arg2, double* input_arg2_val, int oper)
    
{
    char * ad_2cnd=(char*)null_ptr;

    int jj;
    double* arg1_val= (double*)input_arg1_val;
    double* arg2_val= (double*)input_arg2_val;
    char *ad1=(char*)null_ptr;
    char *ad2=(char*)null_ptr;
    char *ad3=(char*)null_ptr;
    char chr;

    char *ad4=(char*)null_ptr;
    struct dataelem *temp_arg=(struct dataelem*)null_ptr;
    int argum_switch;
    int i,j;
    int l1,l2;
    char msg[162];

/*--------
StrPrintF(debug,"at compare_args arg1_kind=%c arg2_kind=%c oper=%i",arg1->kind,arg2->kind,oper);
test_debug(debug);
--------*/
    argum_switch=0;


    if (arg1->kind !='s')
	   goto comp_num;
    else goto comp_alnum;
comp_num :
    if(arg2==(struct dataelem*)null_ptr) goto comp_num_null;
     if (arg2->kind!='s')
	   goto comp_num_num;
    else goto comp_num_alnum;
comp_num_num :
   
    reg_a=*((double*)arg1_val);
    reg_b=*((double*)arg2_val);
/*----
StrPrintF(debug,"comparing num-to-num  %lf to %lf",reg_a,reg_b);
test_debug(debug);
-----*/
    if( *arg1_val>*arg2_val ) goto comp_1hi;
    else if(*arg1_val<*arg2_val) goto comp_1low;
    else goto comp_1_2_equal;
comp_alnum:
/*---------test_debug("at alnum compare");--------*/
    if( arg2 == null_ptr ) goto comp_alnum_null;

    if(arg2->kind!='s')
	   goto comp_alnum_num;
    goto comp_two_alpha;
comp_num_alnum :

compare_one_num_one_not:
    
    StrPrintF(msg,"Illegal compare of string var. to numeric var. (%d) (%d)",
    arg1->tbl_no,arg2->tbl_no);
    misc_errmsg(msg);
    goto comp_1_2_equal;
comp_alnum_num :
    temp_arg = arg2;  /*reverse arg1 and arg2 */
    arg2 = arg1;
    arg1 = temp_arg;

    ad4 = (char*)arg2_val;
    arg2_val = arg1_val;
    arg1_val = (double*)ad4;

    argum_switch = 1;
    goto compare_one_num_one_not;
comp_two_alpha :
    ad1 = (char*)arg1_val;
    ad2 = (char*)arg2_val;
/*-------
StrPrintF(debug,"compare two alpha %s / %s",ad1,ad2);
test_debug(debug);
-------*/
    l1=StrLen((char *)arg1_val);
    l2=StrLen((char*)arg2_val);
//StrPrintF(debug,"comparing %s to %s  l1=%d  l2=%d",ad1,ad2,l1,l2);
//SysFatalAlert(debug);    
    if(l1>=l2) i=l2; else i=l1;
    for(jj=0;jj<i;++jj)
    {
        if ( *(ad1+jj)<*(ad2+jj)) 
        {
//dbug("low");
            goto comp_1low;
        }
        if( *(ad1+jj)>*(ad2+jj))
        {
//dbug("hi");
            goto comp_1hi;
        }    
    } 



    if(l1==l2) 
    {
//dbug("equal");
        goto comp_1_2_equal;
    }
    if(l1>l2)
      goto comp_1hi;  //12172001
    else              //12172001
      goto comp_1low; //12172001  
    
    

comp_num_null :
   if( ( oper != 12 ) && ( oper != 13 ) )
      reg_a = *( (double*)arg1_val );

    if(oper==14) { /*pos*/
	if(reg_a>=0) return(1); else return(0);
    }
    if(oper==15) { /*notpos*/
	if(reg_a<0) return(0); else return(1);
    }
    if(oper==16) { /*neg*/
	if(reg_a<0) return(1); else return(0);
    }
    if(oper==17) { /*not neg*/
	if(reg_a>=0) return(0); else return(1);
    }
    if( (oper==18) || (oper==19) ) {
	if(reg_a==0)  {
	    if(oper==18) return(0); else return(1);
	}
	if(oper==18) return(1); else return(0);
    }
    if( (oper==12) || (oper==13) ) ;
    else
    {
       StrPrintF(msg,"illegal compare operation code %i",oper);
       misc_text_abort(msg);
    }
    ad1 = (char*)arg1_val;
    while ( *ad1 != 0x00) {
	if((*ad1=='+') ||(*ad1=='-'))  {
	    if  (ad1==(char*)arg1_val) {
		++ad1;
		continue;
	    }
	    else {
		     if(oper==12) return(0); else return(1);
	    }
	}
	if( (*ad1 >= '0') && (*ad1 <= '9') ) {
	    ++ad1;
	    continue;
	}
	if(*ad1=='.')
	{
	   ++ad1;
	   continue;
	}
	if(oper==12) return(0); else return(1);
    }
    if(oper==12) return(1); else return(0);
comp_alnum_null :
comp_numed_null :
comp_alphab_null :
comp_alphaed_null :
    if( (oper==10) || (oper==11)) goto comp_if_alphab;
comp_if_numeric :
    ad1 = (char*)arg1_val;
    while ( *ad1 != 0x00 )  {
	if( (*ad1 < '0') || (*ad1 > '9') ) {
	    if(oper==12) return(0); else return(1);
	}
	++ad1;
    }
    if(oper==12) return(1); else return(0);
comp_if_alphab :
    ad1 = (char*)arg1_val;
    while (*ad1 != 0x00 ) {
	if ( ( (*ad1>='a') && (*ad1<='z')) || (*ad1==' ') ||
	     ( (*ad1>='A') && (*ad1<='Z') ) ) {
	     ++ad1;
	     continue;
	}
	else {
	     if(oper==10) return(0); else return(1);
	}
   }
    if(oper==10) return(1); else return(0);
comp_1low :
    if(argum_switch == 1) goto comp_1high_set;
comp_1low_set:
    if( (oper==3) || (oper==4) || (oper==2)
     || (oper==7) || (oper==8)             ) return(1);else return(0);
comp_1hi  :
    if(argum_switch == 1) goto comp_1low_set;
comp_1high_set :
    if( (oper==3) || (oper==1) || (oper==5)
     || (oper==9) || (oper==6)             ) return(1);else return(0);
comp_1_2_equal :
    if( (oper==0) || (oper==4) || (oper==5)
     || (oper==7) || (oper==6)             ) return(1);else return(0);
}


			      

/********************************************************************************************/
extern char *devel_address(struct dataelem *arg, unsigned int s1,unsigned int s2,unsigned int s3)
		      /*this rtn develops the address for the */
		      /*data pointed to by a data element #   */
		      /*and up to three subscripts            */
		      /*it returns a ptr to the addr of byte 1*/
{
   char *ad ;
   char*p;  //06/01/2002
   long i;
   //06/01/2002unsigned int curoffset;
      
//char test[80] ;
/*----
StrPrintF(test,"at devel_addr occurs=%i s1=%i ",
arg->no_values,s1);
test_debug(test);
----*/
   i = (s3) * arg->max_no_values2 * arg->max_no_values1
      + (s2) * arg->max_no_values1
      + (s1);
        
   if(arg->kind=='s')
   {
      p=(char *)arg + DELEN + i * 2 ;
      //curoffset = *( (int*)( p) );
      //if( curoffset == 0 )
      if( (unsigned int)(*( (int*)( p) )) == 0 )
         ad = &aNullStringConstant;
      else
         ad = (char*)arg + ( *(int *)( p ) );  //06/01/2002
	}
	else
      ad = (char*)arg + DELEN + i * 8;

   return ad;
}

/********************************************************************************************/
extern struct dataelem *elem_tbl_ptr(unsigned int de_no)       /*--data elem tbl calc */
                                    /*tbl # of a data elem */
{
    char* ad;   //06/01/2002
    //06/01/2002 struct dataelem *d1=(struct dataelem*)null_ptr;
    
    
    //if(de_no==0) return((struct dataelem*)null_ptr);

    //if(*((long*)(((char*)deListPtr+de_no*4)))==0)
    //{
    //   setupADataelem(de_no);
    //}
    //hData=*((VoidHand*)((char*)deListPtr+de_no*4));    
    //d1=*((VoidPtr*)((char*)deListPtr+de_no*4));    
   
    if(de_no!=0)  											//06/01/2002
    {														//06/01/2002
        ad=(char*)deListPtr+de_no*4;						//06/01/2002			
        if(*((long*)ad)==0)     					      //06/01/2002
        {												  //06/01/2002
           setupADataelem(de_no);						  //06/01/2002
        }											      //06/01/2002		
        //hData=*((VoidHand*)ad);   					      //06/01/2002 
        return((struct dataelem*)(*((VoidPtr*)ad)));     	  //06/01/2002
    }														//06/01/2002
    else return((struct dataelem*)null_ptr);       		  //06/01/2002
    
}
/********************************************************************************************/
extern unsigned char find_char()             /*--find next char in code file */
{
    unsigned char the_char;
//if(debug_sw){
//StrPrintF(debug,"find_char codePtr=%lu i.c.=%d",codePtr,instr_ctr);
//SysFatalAlert(debug);
//}
    the_char = *((unsigned char*)(codePtr)+instr_ctr++);
    return(the_char);
}
/********************************************************************************************/
/*03012002 
extern struct dataelem *find_data_elem_no()   **find data elem # code**
{
    unsigned int i;
    struct dataelem *de=(struct dataelem *)null_ptr;
    i = find_integer();

//StrPrintF(debug,"in find_data_elem_no  deno=%d",i);
//SysFatalAlert(debug);
    if ( i == 0 ) return( (struct dataelem *)null_ptr );
    de = elem_tbl_ptr(i);
    return(de);
}
*/
/********************************************************************************************/
extern unsigned int find_integer()                     /*---find next integer in code--*/
{
    unsigned char find_char();
    unsigned char *ad1=(unsigned char*)null_ptr;
    unsigned the_integ;
    ad1 = (unsigned char *) &the_integ;
    *ad1 = find_char();
    *(ad1+1)=find_char();
    return(the_integ);
}

/********************************************************************************************/
extern unsigned int find_offset()
{
   int i;
   unsigned int j;
   char *ad;
   i=find_integer();   //have parag #
//StrPrintF(debug,"found para tbl#=%d",i);
//SysFatalAlert(debug);
   ad=paragTbl+(i-1)*2;
   j=*((unsigned int*)ad)-theCodeOffset;     //3/13/2001
//if(debug_on==1)
//{
//StrPrintF(debug,"found para tbl#=%d offset=%u theCodeOffset=%u  paragTbl=%lu",i,j,theCodeOffset,paragTbl);
//SysFatalAlert(debug);
//}

     return(j);
}

/********************************************************************************************/
extern void find_string( char *result, int max )
    
{

    char *ad=(char*)null_ptr;
     int len;

    ad = result;
    len = 0;

    while( len < max ) {
	 *ad = find_char();
         if(*ad++ == 0x00 ) break;
	++len;
    }

    return;
}




/********************************************************************************************/
extern void find_arg_1_2()                      /*--set args 1 and 2 from code--*/
{
    find_arg_1();
    find_arg_2();
    return;
}
/********************************************************************************************/
extern void find_arg_1_3()                      /*--set args 1,2,and3 from code--*/
{
    find_arg_1_2();
    find_arg_3();
    return;
}
/********************************************************************************************/
extern void find_arg_1_4()                      /*--set args 1 thru 4 from code--*/
{
    find_arg_1_3();
    find_arg_4();
    return;
}

/********************************************************************************************/
extern void find_arg_1_nosubs()            /*--set arg 1 from code-----------*/
{
   arg1_sde1=0;
   arg1_sde2=0;
   arg1_sde3=0;

   arg1 = find_arg_nosubs( &arg1_occ1,&arg1_occ2,&arg1_occ3);
   if( arg1 != null_ptr )
      arg1_val = devel_address(arg1, 0,0,0);
}

/********************************************************************************************/
extern void find_arg_1()                    /*--set arg 1 from code-----------*/
{
   arg1 = find_arg( &arg1_occ1, &arg1_occ2,&arg1_occ3,&arg1_sde1,&arg1_sde2,&arg1_sde3);
   if( arg1 != null_ptr )
      arg1_val = devel_address(arg1, arg1_occ1,arg1_occ2,arg1_occ3);
}

/********************************************************************************************/
extern  void find_arg_2_nosubs()            /*--set arg 2 from code-----------*/
{
   arg2_sde1=0;
   arg2_sde2=0;
   arg2_sde3=0;

   arg2 = find_arg_nosubs( &arg2_occ1,&arg2_occ2,&arg2_occ3 );
   if( arg2 != null_ptr )
      arg2_val = devel_address(arg2, 0,0,0);
}

/********************************************************************************************/
extern void find_arg_2()                   /*--set arg 2 from code-----------*/
{
   arg2=find_arg( &arg2_occ1, &arg2_occ2,&arg2_occ3,&arg2_sde1,&arg2_sde2,&arg2_sde3);
   if( arg2 != null_ptr )
      arg2_val = devel_address(arg2, arg2_occ1,arg2_occ2,arg2_occ3);
}

/********************************************************************************************/
extern void find_arg_3_nosubs()
{
   arg3_sde1=0;
   arg3_sde2=0;
   arg3_sde3=0;

   arg3 = find_arg_nosubs( &arg3_occ1, &arg3_occ2,&arg3_occ3);
   if( arg3 != null_ptr )
      arg3_val = devel_address(arg3, 0,0,0);
}

/********************************************************************************************/
extern void find_arg_3()                    /*--set arg 3 from code-----------*/
{
   arg3= find_arg(&arg3_occ1, &arg3_occ2,&arg3_occ3,&arg3_sde1,&arg3_sde2,&arg3_sde3);
   if( arg3 != null_ptr )
      arg3_val = devel_address(arg3, arg3_occ1,arg3_occ2,arg3_occ3);
}

/********************************************************************************************/
extern void find_arg_4_nosubs()
{
   arg4_sde1=0;
   arg4_sde2=0;
   arg4_sde3=0;

   arg4 = find_arg_nosubs( &arg4_occ1,&arg4_occ2,&arg4_occ3);
   if( arg4 != null_ptr )
      arg4_val = devel_address(arg4, 0,0,0);
}

/********************************************************************************************/
extern void find_arg_4()                        /*--set arg 4 from code-----------*/
{
   arg4= find_arg(&arg4_occ1,&arg4_occ2,&arg4_occ3 ,&arg4_sde1,&arg4_sde2,&arg4_sde3);
   if( arg4 != null_ptr )
      arg4_val = devel_address(arg4, arg4_occ1,arg4_occ2,arg4_occ3);
}

/********************************************************************************************/
extern void find_arg_5_nosubs()
{
   arg5_sde1=0;
   arg5_sde2=0;
   arg5_sde3=0; 

   arg5 = find_arg_nosubs( &arg5_occ1, &arg5_occ2,&arg5_occ3);
   if( arg5 != null_ptr )
      arg5_val = devel_address(arg5, 0,0,0);
}

/********************************************************************************************/
extern void find_arg_5()                    /*--set arg 5 from code-----------*/
{
   arg5= find_arg(&arg5_occ1,  &arg5_occ2,&arg5_occ3,&arg5_sde1,&arg5_sde2,&arg5_sde3);
   if( arg5 != null_ptr)
      arg5_val = devel_address(arg5, arg5_occ1,arg5_occ2,arg5_occ3);
}

/********************************************************************************************/
extern void find_arg_6_nosubs()
{
    arg6_sde1=0;
    arg6_sde2=0;
    arg6_sde3=0;

   arg6 = find_arg_nosubs( &arg6_occ1, &arg6_occ2,&arg6_occ3);
   if( arg6 != null_ptr )
      arg6_val = devel_address(arg6, 0,0,0);
}

/********************************************************************************************/
extern void find_arg_6()                    /*--set arg 6 from code-----------*/
{
   arg6= find_arg(&arg6_occ1,&arg6_occ2,&arg6_occ3,&arg6_sde1,&arg6_sde2,&arg6_sde3);
   if( arg6 != null_ptr )
      arg6_val = devel_address(arg6, arg6_occ1,arg6_occ2,arg6_occ3);
}
				   /*-------set any argument-------*/

//void verb_mem_debug()
//{
//   char c;
//   c=find_char();
//   if(c==0x00) mem_debug_sw=0;
//   else        mem_debug_sw=2;
//   return;
//}

/********************************************************************************************/
void verb_cursor()
{
    find_arg_1_2();
    InsPtEnable(true);
    InsPtSetLocation(basc_integ_value(arg1,(double*)arg1_val),basc_integ_value(arg2,(double*)arg2_val));
    return;
}
/********************************************************************************************/
void verb_delay()
{
    double one_num;
    int seconds;
    unsigned ticks;

    find_arg_1();
    misc_getdbl(arg1,arg1_occ1,arg1_occ2,arg1_occ3,&one_num);
    EvtResetAutoOffTimer();  //keep sys from going to sleep
    ticks=one_num*sysTicksPerSecond;
    if (ticks<=0) return;
    SysTaskDelay(ticks);
    return;
}
/********************************************************************************************/
void verb_errmsg()  //really verb_msgbox
{


     find_arg_1();
     misc_errmsg((char *)arg1_val);
    return;
}
/********************************************************************************************/
void verb_end_logic_cond()
{                /*used for logic conditions */

    unsigned int i;
char work[80];
    i=find_integer();    /*last log var set by code*/
/*------
StrPrintF(work,"at end logic var=%i value=%i",i,logic_var[i]);
test_debug(work);
------*/
    if(logic_var[i] ==1)  /*true*/
    {
	   logic_value=1;
    }
    else
    {
	   logic_value=0;
    }
    return;
}
/********************************************************************************************/
void verb_display()
{
    int color_text,color_bkgrnd;
    char str[128];
    int i;int ii;
    unsigned char it;
    int x;
    
    x=getx();
    it=find_char();
    if(it==0x00) ;
    else
    {
	    find_arg_1();
        
        arg1=(struct dataelem*)null_ptr; 
        
    }
    it=find_char();
    if(it==0x00) ;
    else
    {
    	find_arg_1();
	    
	    arg1=(struct dataelem*)null_ptr; 
       
    }
    it=find_char();
    while(it)
    {
	  if(arg1 != (struct dataelem*)null_ptr) 
	  {
	     
	     arg1=(struct dataelem*)null_ptr;
	  } 
	  find_arg_1();
      if(arg1->kind=='s')
      {
          StrCopy((char*)str,(char*)arg1_val);
      }
      else
      {
	       misc_format_number(arg1,(double*)arg1_val,str);
      }
      while(1)
      {
        if( str[0] ==0x00) break;
        if((x+FntCharsWidth(str,StrLen(str)))>SCREEN_MAX_X)
        {
          str[StrLen(str)-1] =0x00;
        }
        else break;
      }
      WinDrawChars(str,StrLen(str),x,gety());
      x+=FntCharsWidth(str,StrLen(str));
      
      it=find_char();
    }

     return;
}




/********************************************************************************************/
//04012005 void verb_start_new_parag()            /*---start new para-----*/
//04012005 {
//04012005       /*now process cur para */
  
//04012005    return;
//04012005 }
/********************************************************************************************/
void verb_start_new_stmt()                  /*---start new statement-------*/
{
   char work[25];
   char msg[500];
   char s[7];
   unsigned int s1;
   unsigned int  s2;
   unsigned int  s3;
   unsigned int  varID;
   long wklong;
   int zeroInt = 0;
   unsigned long stackNo;
  struct codeBlock* stackCodePtr;
   
//Trace("\n\rNew stmt//");
    cur_module_id = find_integer();    //04012005
    cur_stmt_no = find_integer();
    
    
//SysFatalAlert("got start of a stmt");
//start insertions 04012005
   if( *((unsigned char*)(codePtr)+instr_ctr )==0xf2)  
    {
    		//had to do this to get call stack to show sub/func entry 
    		//entering a sub or func, so set stmt # of entry point
  //SysFatalAlert("recognized f2");
    		codeBlockPtr->subFuncEntry_stmt_no = cur_stmt_no;  //save the stmt no of this FUNC stmt
    		++instr_ctr;
 //StrPrintF(debug,"next instr = %c", *((unsigned char*)(codePtr)+instr_ctr ));
 //SysFatalAlert(debug);
 
    } 
  
#ifdef _DEBUGGER
	//tell the IDE what statement about to execute
	MemMove(msg,"stmt",4);
	MemMove(work,"00000",5);
	StrPrintF(work+5,"%d",cur_module_id);
	MemMove(msg+4,work+StrLen(work)-5,5);
	MemMove(work,"00000",5);
	StrPrintF(work+5,"%d",cur_stmt_no);
	
	MemMove(msg+9,work+StrLen(work)-5,6);   //HAS ENDING NULL TOO
	
	
resendAMessage:	
	debuggerSend(msg);
//Trace(msg);
//SysFatalAlert("sent msg");
	
	debuggerGetReturnMessage(msg);
//SysFatalAlert("got return msg");
	if( MemCmp(msg,"quit",4) == 0) 
	{
		//07262005 SysFatalAlert("The program was stopped from the debugging menu");
		debuggerClose();
 		SysReset();    //07262005
		return;
	}
	
	if( MemCmp(msg,"var",3)==0)
	{

		 wklong=debuggerFindInteger(msg+3,6);
 		 varID = wklong;
		
		 s1=debuggerFindInteger(msg+9,6);

		  
		 
		 s2=debuggerFindInteger(msg+15,6);
 
		 
		 s3=debuggerFindInteger(msg+21,6);
 
	
	//StrPrintF(debug,"msg=%s ----asking for var = %u s1=%u s2=%u s3=%u",msg,varID,s1,s2,s3);	 
	//SysFatalAlert(debug);
		  arg1 = elem_tbl_ptr(varID);
	//StrPrintF(debug,"arg1.kind=%c",arg1->kind);
	//SysFatalAlert(debug);
		  --s1;
		  --s2;
		  --s3;
		  arg1_val = devel_address(arg1,s1,s2,s3);
	//StrPrintF(debug,"xxxx");	 
	//SysFatalAlert(debug);
		 if( arg1->kind == 's')
		 {
	//StrPrintF(debug,"arg=string=%s",arg1_val);
	//SysFatalAlert(debug);
		     StrCopy(msg+27,arg1_val);
		 }
		 else 
		 {
	//StrPrintF(debug,"numeric");
	//SysFatalAlert(debug);
		 	 misc_format_number(arg1,(double*)arg1_val ,s);
		 	 StrCopy(msg+27,s );
//if((s1==1)&&(s2==1)&&(s3==1))
//{
//StrPrintF(debug,"2x2x2 numeric s1=%d s2=%d s3=%d s=%s",s1,s2,s3,s);
//SysFatalAlert(debug);		 	 
//}
	
		 }
//StrPrintF(debug,"msg going back to ide is %s",msg);
//SysFatalAlert(debug);
		 goto resendAMessage;
		 
	}
	if( MemCmp(msg,"watch",5)==0)
	{

		 wklong=debuggerFindInteger(msg+11,6);
 		 varID = wklong;
		
		 s1=debuggerFindInteger(msg+17,6)-1;

		  
		 
		 s2=debuggerFindInteger(msg+23,6)-1;
 
		 
		 s3=debuggerFindInteger(msg+29,6)-1;
 
	
	//StrPrintF(debug,"msg=%s ----asking for var = %u s1=%u s2=%u s3=%u",msg,varID,s1,s2,s3);	 
	//SysFatalAlert(debug);
		  arg1 = elem_tbl_ptr(varID);
	//StrPrintF(debug,"arg1.kind=%c",arg1->kind);
	//SysFatalAlert(debug);
		  arg1_val = devel_address(arg1,s1,s2,s3);
	//StrPrintF(debug,"xxxx");	 
	//SysFatalAlert(debug);
		 if( arg1->kind == 's')
		 {
//StrPrintF(debug,"watch arg=string=%s",arg1_val);
///SysFatalAlert(debug);
		     StrCopy(msg+35,arg1_val);
		 }
		 else 
		 {

		 	 misc_format_number(arg1,(double*)arg1_val ,s);
//if( (s1==1) && (s2==1) && (s3==1))
//{
//StrPrintF(debug,"2x2x2 numeric=%s",s);
//SysFatalAlert(debug);
//}
        	 StrCopy(msg+35,s );
		 	 
	
		 }
//StrPrintF(debug,"msg going back to ide is %s",msg);
//SysFatalAlert(debug);
		 goto resendAMessage;
		 
	}
	if( MemCmp(msg,"stack",5) == 0)
	{
		//wants stack member
		
		stackNo =  debuggerFindInteger(msg+5,4);
		 
		stackCodePtr = codeBlockPtr;
		while(1)
		{
			if((stackCodePtr == 0) || (stackCodePtr->id==50000))
			{
				//there aren't anymore in the stack
				MemMove(work,"00000",5);
	            StrPrintF(work+5,"%d",zeroInt);
	            MemMove(msg+9,work+StrLen(work)-5,5);
	 
			    MemMove(work,"00000",5);
	            StrPrintF(work+5,"%d",zeroInt);
	            MemMove(msg+14,work+StrLen(work)-5,5);
	            
	            MemMove(work,"00000",5);
	            StrPrintF(work+5,"%d",zeroInt);
	            MemMove(msg+19,work+StrLen(work)-5,5);
	            
			     
			    MemMove(work,"00000",5);
	            StrPrintF(work+5,"%d",zeroInt);
	            MemMove(msg+24,work+StrLen(work)-5,5);
			    
			    goto resendAMessage;	
			}
			--stackNo;
			if(	stackNo==0)
			{
			    //got the one we want
			    MemMove(work,"00000",5);
	            StrPrintF(work+5,"%d",stackCodePtr->id);    //id of called stm
	            MemMove(msg+9,work+StrLen(work)-5,5);
	 
			    MemMove(work,"00000",5);
	            StrPrintF(work+5,"%d",stackCodePtr->subFuncEntry_stmt_no);   //called SUB/FUNC stmt no
	            MemMove(msg+14,work+StrLen(work)-5,5);
	            
	           if((stackCodePtr->prevCodePtr == 0)||(stackCodePtr->prevCodePtr->id==50000))
			   {
			   	 	MemMove(work,"00000",5);
	            	StrPrintF(work+5,"%d",zeroInt);
	           		MemMove(msg+19,work+StrLen(work)-5,5);
	            
			     
			    	MemMove(work,"00000",5);
	            	StrPrintF(work+5,"%d",zeroInt);
	            	MemMove(msg+24,work+StrLen(work)-5,5);
	            }
	            else
	            {
	                MemMove(work,"00000",5);
	            	StrPrintF(work+5,"%d",stackCodePtr->prevCodePtr->id);  //id of calling pgm
	           		MemMove(msg+19,work+StrLen(work)-5,5);
	            
			     
			    	MemMove(work,"00000",5);
	            	StrPrintF(work+5,"%d",stackCodePtr->prevCodePtr->cur_stmt_no);  //stmt # that called
	            	MemMove(msg+24,work+StrLen(work)-5,5);
	            } 
			    
			    
			    goto resendAMessage;
			}
			stackCodePtr=stackCodePtr->prevCodePtr;
			
		}
		
	}
	//--------------------------------------------------------------------------
	if( MemCmp(msg,"cont",4) != 0)
	{
		StrPrintF(debug,"Got illegal message(%s) from the debug controller",msg);
		SysFatalAlert(debug);
	}
		
#endif       
//end insertions 04012005    
    return;
}
/********************************************************************************************/
void draw_redraw()
{
   FormPtr frmPtr;

       
       chkFldUpdate();         //added 5.21.2000
       resetToDesignState=false;    //08142002
       executeFormRedraw();    //added 5.21.2000
}
/********************************************************************************************/
void verb_redraw()
{
    draw_redraw();
}

/********************************************************************************************/
void verb_return()
{
   VoidHand tempHand;
   VoidPtr perf;
        if(perfHand!=0)
        {
          perf=MemHandleLock(perfHand);
          instr_ctr=*(UInt*)perf;
          tempHand=*((VoidHand*)((char*)(perf)+2));
          MemPtrUnlock(perf);
          MemPtrFree(perf);
//StrPrintF(debug,"ret ic=%d",instr_ctr);
//SysFatalAlert(debug);
          perfHand=tempHand;
        }
}

		     
/********************************************************************************************/
void verb_add()                /*--------------add--------------------*/
{
    char round_sw;
//char work[266];

    //find_arg_1_3();  //06012002
    find_arg_1();
    find_arg_2();
    find_arg_3();
    round_sw = find_char();
    //reg_b=*((double*)arg1_val);
    //reg_a=*((double*)arg2_val);

    //reg_a=reg_b+reg_a;         /*sum in a*/
    reg_a=*((double*)arg1_val)+*((double*)arg2_val);  //06012002
    //misc_stodbl3(&reg_a);                           //06012002
    misc_stodbl(arg3,arg3_occ1,arg3_occ2,arg3_occ3,&reg_a);

    return;
}


/********************************************************************************************/
void verb_clear_frac_dgts() /*clears all fractional dgts of a fld*/
{
//char work[266];
    double d;
    find_arg_1();

    
    reg_a=*((double*)arg1_val);
   
    d=misc_floor(misc_fabs(reg_a));
    if(reg_a<0) d= -d;

    misc_stodbl1(&d);
    return;
}

/********************************************************************************************/
void verb_compute()                      /*------compute-------------*/
{
    verb_special_arith_store();   /*nothing else special*/
}

/********************************************************************************************/
void verb_exponentiation()              /*-----exponentiation----*/
{
    char round_sw;
    find_arg_1_3();
    round_sw = find_char();
    
    chkMathlibOpen();   //added 5.20.2000
    reg_b=*((double*)arg1_val);
    reg_a=*((double*)arg2_val) ;
    
    reg_c=pow(reg_b , reg_a);
   
    misc_stodbl3(&reg_c);
    return;
}

/********************************************************************************************/
void verb_multiply()                  /*-------multiply-----------------*/
{
   char round_sw;

    find_arg_1_3();
    round_sw = find_char();
    
    reg_a=*((double*)arg1_val);
    reg_b=*((double*)arg2_val);

    reg_c=reg_a*reg_b;

    
    misc_stodbl3(&reg_c);
}

/********************************************************************************************/
void verb_concat_two_strings()
{
    int j,len;
    char *temp;
    VoidHand h;  //05282003

    find_arg_1_3();
 
    len= StrLen((char*)arg1_val)+StrLen((char*)arg2_val);

    //05282003 temp=(char*)MemHandleLock(MemHandleNew(len+1));
    h=MemHandleNew(len+1);         //05282003
    if(h==0) OutOfMemory(6045);    //05282003
    temp=(char*)MemHandleLock(h);  //05282003
    
    StrCopy(temp,(char*)arg1_val);

    StrCat(temp,(char*)arg2_val);
   
//StrPrintF(debug,"resize tbl1=%d tbl2=%d tbl3=%d len=%d s1=%s s2=%s",arg1->tbl_no,arg2->tbl_no,arg3->tbl_no,StrLen(temp),(char*)arg1_val,(char*)arg2_val);
//SysFatalAlert(debug);
//StrPrintF(debug,"concat 1=%s 2=%s 3=%s tbl_no=%d",arg1_val,arg2_val,temp,arg3->tbl_no);
//SysFatalAlert(debug);
    misc_stostr3(temp);

    MemPtrUnlock(temp);
    MemPtrFree(temp);
}
/********************************************************************************************/
void verb_special_arith_store()           /*---store arith w/ round/size-*/
{

    char round;
    int i;
//dbug("compute-find args");
    find_arg_1_2();
//dbug("find over");
    round = find_char();



    if(arg2->kind=='s')
    {
//dbug("storing string");
       misc_stostr2(arg1_val);

       return;
    }
    reg_a=*((double*)arg1_val);

    
//dbugx(((double*)arg1_val),"in arithstore");
//StrPrintF(debug,"in arithstore tbin=%d tblout=%d",arg1->tbl_no,arg2->tbl_no);
//SysFatalAlert(debug);
 
//dbug("compute-store result"); 
    misc_stodbl2(&reg_a);
}
/********************************************************************************************/
void verb_negate()
{
  find_arg_1_2();
  reg_c=0.0-*((double*)arg1_val);
  
  misc_stodbl2(&reg_c);
}
/********************************************************************************************/
void subFuncXferArgument()
{
    int kk,mm,nn;
    //moves the value of one argument from the calling pgm to the sub/func
    if (arg1->kind=='s')
    {
       if(arg2->kind!='s')  MiscFatalAlert("Mis-matched args");
       
    }
    else
    {
       if(arg2->kind=='s')  MiscFatalAlert("Mis-matched args");
       
    }
//StrPrintF(debug,"xfer arg1=%d %d %d %d  max=%d %d %d arg2=%d %d %d %d  max=%d %d %d",arg1->tbl_no,arg1_occ1,arg1_occ2,arg1_occ3,arg1->max_no_values1,arg1->max_no_values2,arg1->max_no_values3,arg2->tbl_no,arg2_occ1,arg2_occ2,arg2_occ3,arg2->max_no_values1,arg2->max_no_values2,arg2->max_no_values3);
//SysFatalAlert(debug);
    //if((arg1->max_no_values1>1)&&(arg1_occ1==0))   
    if( (arg2->max_no_values1<2)
    &&( ((arg1->max_no_values1>1) && (arg1_sde1==0))
      ||((arg1->max_no_values2>1) && (arg1_sde2==0))
      ||((arg1->max_no_values3>1) && (arg1_sde3==0)) ))
    {
           MiscFatalAlert("Passed an entire array to a subroutine not expecting it.");
    }
    if (arg2->max_no_values1>1)
    {
        //calling param should be an array name without a subscript
        //  (but maybe a typedef member of an array, so there may be other preceding subscripts)
        
        //need to move all values of the array
        if(arg2->max_no_values3>1)
        {
          //sub arg has 3 levels of subs
          if(arg1_sde1!=0) MiscFatalAlert("Too many levels of subscripting.");
          if( (arg1->max_no_values1 != arg2->max_no_values1)
          ||  (arg1->max_no_values2 != arg2->max_no_values2)
          ||  (arg1->max_no_values3 != arg2->max_no_values3) )
             MiscFatalAlert("Subroutine and calling program array bounds do not match."); 
          for( kk=0;kk<arg2->max_no_values1;++kk)
          {
            for( mm=0;mm<arg2->max_no_values2;++mm)
            {
              for( nn=0;nn<arg2->max_no_values3;++nn)
              {
//StrPrintF(debug,"storing arrays  %u %u %u",kk,mm,nn);
//SysFatalAlert(debug);
                 arg1_val = devel_address(arg1, kk,mm,nn);
                 arg2_val = devel_address(arg2, kk,mm,nn);
                 arg2_occ1=kk;
                 arg2_occ2=mm;
                 arg2_occ3=nn;
                      if (arg1->kind=='s')
                 {
                      
                      misc_stostr2(arg1_val);
                 }
                 else
                 {
                      misc_stodbl2((double*)arg1_val);
                 }
              }
            }
          }   
        }
        else
        {
          if(arg2->max_no_values2>1) 
          {
            //sub arg has 2 levels of subs
            if(arg1_sde2!=0) MiscFatalAlert("Too many levels of subscripting.");
            if(arg1_sde1==0)
            {
              if( (arg1->max_no_values1 != arg2->max_no_values1)
              ||  (arg1->max_no_values2 != arg2->max_no_values2))
                  MiscFatalAlert("Subroutine and calling program array bounds do not match."); 
            }
            else
            {
              if( (arg1->max_no_values2 != arg2->max_no_values1)
              ||  (arg1->max_no_values3 != arg2->max_no_values2))
                  MiscFatalAlert("Subroutine and calling program array bounds do not match.");   
            }
            for( kk=0;kk<arg2->max_no_values1;++kk)
            {
              for( mm=0;mm<arg2->max_no_values2;++mm)
              {
                
//StrPrintF(debug,"storing arrays  %u %u %u",kk,mm,nn);
//SysFatalAlert(debug);
                if(arg1_sde1==0)
                {
                   arg1_val = devel_address(arg1, kk,mm,0);
                   arg2_val = devel_address(arg2, kk,mm,0);
                   arg2_occ1=kk;
                   arg2_occ2=mm;
                   arg2_occ3=0;
                }
                else
                {
                   arg1_val = devel_address(arg1, arg1_occ1,kk,mm);
                   arg2_val = devel_address(arg2, kk,mm,0);
                   arg2_occ1=kk;
                   arg2_occ2=mm;
                   arg2_occ3=0;
                }
                if (arg1->kind=='s')
                {
                      misc_stostr2(arg1_val);
                }
                else
                {
                      misc_stodbl2((double*)arg1_val);
                }
                
              }
            } 
          
          }
          else
          {
            //sub arg has 1 levels of subs
            if(arg1_sde3!=0) MiscFatalAlert("Too many levels of subscripting.");
            if(arg1_sde1==0)
            {
              if( (arg1->max_no_values1 != arg2->max_no_values1))
                  MiscFatalAlert("Subroutine and calling program array bounds do not match."); 
            }
            else
            {
              if(arg1_sde2==0)
              {
                if (arg1->max_no_values2 != arg2->max_no_values1)
                  MiscFatalAlert("Subroutine and calling program array bounds do not match.");   
              }
              else
              {
                if (arg1->max_no_values3 != arg2->max_no_values1)
                  MiscFatalAlert("Subroutine and calling program array bounds do not match.");  
              }
            }
            for( kk=0;kk<arg2->max_no_values1;++kk)
            {
                             
//StrPrintF(debug,"storing arrays  %u %u %u",kk,mm,nn);
//SysFatalAlert(debug);
                if(arg1_sde1==0)
                {
                   arg1_val = devel_address(arg1, kk,0,0);
                   arg2_val = devel_address(arg2, kk,0,0);
                   arg2_occ1=kk;
                   arg2_occ2=0;
                   arg2_occ3=0;
                }
                else
                {
                  if(arg1_sde2==0)
                  {
                     arg1_val = devel_address(arg1, arg1_occ1,kk,0);
                     arg2_val = devel_address(arg2, kk,0,0);
                     arg2_occ1=kk;
                     arg2_occ2=0;
                     arg2_occ3=0;
                  }
                  else
                  {
                     arg1_val = devel_address(arg1, arg1_occ1,arg1_occ2,kk);
                     arg2_val = devel_address(arg2, kk,0,0);
                     arg2_occ1=kk;
                     arg2_occ2=0;
                     arg2_occ3=0;
                  }
                }
                if (arg1->kind=='s')
                {
                      misc_stostr2(arg1_val);
                }
                else
                {
                      misc_stodbl2((double*)arg1_val);
                }
      
            } 
          }
        }
    }       
    else
    {
      //its only a single-valued (non-array) data element
      if (arg1->kind=='s')
      {
        misc_stostr2(arg1_val);
      }
      else
      {
         misc_stodbl2((double*)arg1_val);
      }
    }  
}
/********************************************************************************************/
void verb_subtract()                       /*-------subtract-----------*/
{
   char round_sw;
    find_arg_1_3();
    round_sw = find_char();
    
    reg_b=*((double*)arg1_val);
    reg_a=*((double*)arg2_val);


    reg_c=reg_a - reg_b;
    

    
    misc_stodbl3(&reg_c);
}

		  
/********************************************************************************************/
void verb_and()                     /*----------and----------*/
{
    unsigned int  a,b,c;
    a=find_integer();
    b=find_integer();
    c=find_integer();
    if( (logic_var[a] ==1) && (logic_var[b] ==1) )
	 logic_var[c] =1;
    else logic_var[c] =0;
}
/********************************************************************************************/
void verb_goto()                           /*-----------goto-------------*/
{
    instr_ctr = find_offset();
}
/********************************************************************************************/
void verb_if()                             /*--------------- if ---------*/
{
   
    unsigned int if_false_offset;
    unsigned int if_true_offset;
    unsigned int if_endif_offset;
    unsigned int log_var;
    int  if_oper;
    char if_or_code;


    if_false_offset =  find_offset();
    if_true_offset = find_offset();
    if_endif_offset =find_offset();
    log_var = find_integer();
//StrPrintF(debug,"  instr_ctr=%d false=%d true=%d endif=%d logic=%d",instr_ctr
//,if_false_offset,if_true_offset,if_endif_offset,logic_var[log_var]);
//SysFatalAlert(debug);
    if(logic_var [log_var] == 1) {
       
       instr_ctr = if_true_offset;

//StrPrintF(debug,"at true-para#=%i  instr_ctr=%d",if_true_offset,instr_ctr);
//SysFatalAlert(debug);

	    return;
    }
    /* result is false */
   
    instr_ctr = if_false_offset;

//StrPrintF(debug,"at false-using logvar=%i,para#=%i  instr=%d",log_var,if_false_offset,instr_ctr);
//SysFatalAlert(debug);
}
/********************************************************************************************/
void verb_startfor()
{
    unsigned int offset;
    
    int forno;
    int i,j,k;
    VoidHand h;   //05282003  
    
    find_arg_1_4(); //1=ctl,2=start,3=end,4=step
    forno=find_integer();

    reg_a=*((double*)arg2_val)-*((double*)arg4_val);
//StrPrintF(debug,"startfor offset=%d",offset);
//SysFatalAlert(debug);

    misc_stodbl1(&reg_a);
    //06102002forHandleSave=forHandle;
    forPtrSave=forptr;  //06102002 added
    //06102002forHandle=MemHandleNew(sizeof(struct forStruct));
    //06102002if (forHandle==0) SysFatalAlert("out of memory"); 
    //06102002forptr=(struct forStruct*)MemHandleLock(forHandle);
    //05282003 forptr=(struct forStruct*)MemHandleLock(MemHandleNew(sizeof(struct forStruct))); //06102002 
    h=MemHandleNew(sizeof(struct forStruct));    //05282003
    if(h==0)  OutOfMemory(6047);                 //05282003
    forptr=(struct forStruct*)MemHandleLock(h);
    //05282003 if (forptr==0)                    //modified 05212003
    //05282003 {                                 //inserted 05212003
    //05282003     SysFatalAlert("out of memory"); 
    //05282003     ErrThrow(-1);                 //inserted 05212003
    //05282003 }                                 //inserted 05212003    
      forptr->number=forno;
      forptr->moduleCntr=moduleCntr;
      forptr->ToValue=*((double*)arg3_val);
      forptr->StepValue=*((double*)arg4_val);
      //06102002forptr->prevHandle=forHandleSave; 
      forptr->prevForPtr=forPtrSave;   //06102002
    //06102002MemPtrUnlock(forptr);
}

/********************************************************************************************/
void verb_continuefor()
{
    unsigned int offset;
    
    int forno;
    

    find_arg_1();
    forno=find_integer();
    offset=find_offset();
    
loop:
    //06102002if(forHandle==0) SysFatalAlert("Internal error--for processing");
    if(forptr==0)                                //modified 05212003
    {                                            //inserted 05212003
                   SysFatalAlert("Internal error--for processing");  //inserted 05212003
                   ErrThrow(-1);                 //inserted 05212003
    }                                            //inserted 05212003
    
    //06102002forptr=(struct forStruct*)MemHandleLock(forHandle);
    if((forptr->moduleCntr!=moduleCntr)||(forptr->number!=forno))
    {
       //06102002forHandleSave=forHandle;
       forPtrSave=forptr;  //06102002
       //06102002forptr=(struct forStruct *)MemHandleLock(forHandle);
       //06102002forHandle=forptr->prevHandle;
       forptr=forptr->prevForPtr;  //06102002
       //06102002MemPtrUnlock(forptr);
       //06102002MemHandleFree(forHandleSave);
       MemPtrFree(forPtrSave);  //06102002
       goto loop; 
    }
    //reg_b=forptr->ToValue;
    //reg_c=forptr->StepValue;
      
       
    reg_a=*((double*)arg1_val) + forptr->StepValue;
    misc_stodbl1(&reg_a);
    if (forptr->StepValue>0.0)    //step is pos
    {

       if (reg_a > forptr->ToValue)
       {
          
          goto deleteCurrentLoop;
       }
    }
    else   //step is neg
    {
       if (reg_a < forptr->ToValue)
       {
          
          goto deleteCurrentLoop;
       }
    }
    //06102002MemPtrUnlock(forptr);
    return;
deleteCurrentLoop:
       //06102002MemPtrUnlock(forptr);
       //06102002forHandleSave=forHandle;
       forPtrSave=forptr;  //06102002
       //06102002forptr=(struct forStruct *)MemHandleLock(forHandle);
       //06102002forHandle=forptr->prevHandle;
       forptr=forptr->prevForPtr;  //06102002
       //06102002MemPtrUnlock(forptr);
       //06102002MemHandleFree(forHandleSave);
       MemPtrFree(forPtrSave);
       instr_ctr=offset;    
}

/********************************************************************************************/
void verb_next()
{
  UInt offset;
  offset=find_offset();
  instr_ctr=offset;
}

/********************************************************************************************/
void verb_dowhile()
{
   
    unsigned int while_false_offset, while_true_offset;
    unsigned int while_endwhile_offset;
    unsigned int log_var;
			     /**/
    while_false_offset = find_offset();
    while_true_offset = find_offset();
    while_endwhile_offset = find_offset();
    log_var = find_integer();
    if(logic_var [log_var] == 1) {
         instr_ctr = while_true_offset;
/*------
StrPrintF(debug,"at true-para#=%i p=%p instr_ctr=%p",if_true_para,p,instr_ctr);
test_debug(debug);
-----*/
	return;
    }
    /* result is false */
    
    instr_ctr = while_false_offset;
/*------
StrPrintF(debug,"at false-using logvar=%i,para#=%i p=%p instr=%p",log_var,if_true_para,p,instr_ctr);
test_debug(debug);
-------*/
}

/********************************************************************************************/
void verb_dountil()
{
   
    unsigned int while_false_offset, while_true_offset;
    unsigned int while_endwhile_offset;
    unsigned int log_var;
			     /**/
    while_false_offset = find_offset();
    while_true_offset = find_offset();
    while_endwhile_offset = find_offset();
    log_var = find_integer();
    if(logic_var [log_var] == 0) {
         instr_ctr = while_true_offset;
/*------
StrPrintF(debug,"at true-para#=%i p=%p instr_ctr=%p",if_true_para,p,instr_ctr);
test_debug(debug);
-----*/
	return;
    }
    /* result is false */
    instr_ctr = while_false_offset;
/*------
StrPrintF(debug,"at false-using logvar=%i,para#=%i p=%p instr=%p",log_var,if_true_para,p,instr_ctr);
test_debug(debug);
-------*/
}

/********************************************************************************************/
void verb_do()
{
   
    unsigned int while_false_offset, while_true_offset;
    unsigned int while_endwhile_offset;
    unsigned int log_var;
			     /**/
    while_false_offset = find_offset();
    while_true_offset = find_offset();
    while_endwhile_offset = find_offset();
    log_var = find_integer();
    
/*------
StrPrintF(debug,"at false-using logvar=%i,para#=%i p=%p instr=%p",log_var,if_true_para,p,instr_ctr);
test_debug(debug);
-------*/
}

/********************************************************************************************/
void verb_loop()
{
   instr_ctr = find_offset();
}

/********************************************************************************************/
void verb_exitfor()
{
   instr_ctr=find_offset();
}

/********************************************************************************************/
void verb_exitdo()
{
   instr_ctr = find_offset();
}

/********************************************************************************************/
void verb_logic_class_tests()              /*---class tests-------*/
{
     int if_oper;
     unsigned int log_var;
    find_arg_1();
    if_oper = (int) find_char();
    log_var = find_integer();
    arg2 = (struct dataelem*)null_ptr;  arg2_val = (char*)null_ptr;
    if(compare_args(arg1,(double*)arg1_val,arg2,(double*)arg2_val,if_oper)==1)
    {
	   logic_var[log_var] =1;
    }
    else
    {
       logic_var[log_var] =0;
    }
}
//added this whole routine on 06102002
/********************************************************************************************/
void verb_nextscreenwithvariable()   //nextform using form name in variable  //06102002
{
   
    int i;
    char*ad;
    char *p2;
    VoidHand h;   //05282003
    VoidHand h2;
    char name[256];
    unsigned int ID;
    find_arg_1();
    

	h2=MiscDmGetResource(rscTag,(ULong)9907,"vtoc");  //read the view tbl-of-contents record
    if(h2==0)
    {
       SysFatalAlert("Can't find view TOC record");
       ErrThrow(-1);                 //inserted 05212003
    }
    p2=MiscHandleLock(h2);

    for(i=0;i<view_cnt;++i)  //for each view
    {
      ID=basc_dbGetInt( (char*)p2);  //get id of view from the vtoc record
      p2+=2;   //06102002
      ad=&name[0];
      							//06102002
			//read form name	//06102002
			while(1)				//06102002
   			{						//06102002
   				*ad=*p2;			//06102002
   				if((*p2)==0x00) break; //06102002
   				++ad;				//06102002
   				++p2;				//06102002
   				
  			}						//06102002
  	  								//06102002
  	  		++p2;					//06102002
//StrPrintF(debug,"comparing %s to %s",name,arg1_val);
//dbug(debug);      
      if(StrCaselessCompare(name,arg1_val)==0)
      {
          goto matchedName;
      } 
      
//dbug("loading form   in vtoc processing:");
          
   }
   StrPrintF(debug,"Illegal form name used = %s",arg1_val);
   SysFatalAlert(debug);
   ErrThrow(-1);                 //inserted 05212003
matchedName:
    MemHandleUnlock(h2);      
    DmReleaseResource(h2);  
    
    
    if(MenuGetActiveMenu()!=NULL) 
    {
//dbug("erasing menu");
      MenuEraseStatus(NULL);
      MenuSetActiveMenu(NULL);
      FrmSetMenu(FrmGetActiveForm(),0);
      MenuDispose(menuPtr);
      menuPtr=(MenuBarType*)null_ptr; 
    }
    frmNo=ID;
//StrPrintF(debug,"nextscreen %d",ID);
//SysFatalAlert(debug);
    //05282003 evptr=(EventType*)MemHandleLock(MemHandleNew(sizeof(EventType)));
    h=MemHandleNew(sizeof(EventType));              //05282003
    if(h==0) OutOfMemory(6048);                     //05282003
    evptr=(EventType*)MemHandleLock(h);             //05282003 
    evptr->eType=firstUserEvent;
    evptr->data.generic.datum[0] =frmNo;
    evptr->data.generic.datum[1] =1;
    evptr->data.generic.datum[2] =find_integer();  //08142002 get option to reset to design state from code
    if (frmNo == FrmGetActiveFormID())
    {
        //going to same form to clear it
//SysFatalAlert("erasing");
        FrmEraseForm(FrmGetActiveForm());   //erase form to avoid os err msg
    }                       
   EvtAddEventToQueue(evptr);   //09302002
    //MemPtrUnlock(evptr);
    MemPtrFree(evptr);   //08032002
//StrPrintF(debug,"form load event is addr=%lu  size=%d",(unsigned long)evptr,sizeof(EventType));
//SysFatalAlert(debug);    
}

/********************************************************************************************/
void verb_nextscreen()   //nextform   //08142002 (old before RESET option)
{
   
    unsigned int ID;
    VoidHand h;  //05282003
    
    ID=find_integer();
//dbug("in old next screen");
//StrPrintF(debug,"found id %d",ID);
//SysFatalAlert(debug);
    //9/22/2001if(menuPtr!=null_ptr) 
    if(MenuGetActiveMenu()!=NULL) 
    {
//dbug("erasing menu");
      MenuEraseStatus(NULL);
      MenuSetActiveMenu(NULL);
      FrmSetMenu(FrmGetActiveForm(),0);
      MenuDispose(menuPtr);
      menuPtr=(MenuBarType*)null_ptr; 
    }
    frmNo=ID;
//StrPrintF(debug,"nextscreen %d",ID);
//SysFatalAlert(debug);
    //05282003 evptr=(EventType*)MemHandleLock(MemHandleNew(sizeof(EventType)));
    h=MemHandleNew(sizeof(EventType));    //05282003
    if(h==0) OutOfMemory(6049);           //05282003
    evptr=(EventType*)MemHandleLock(h);   //05282003
    
    evptr->eType=firstUserEvent;
    evptr->data.generic.datum[0] =frmNo;
    evptr->data.generic.datum[1] =1;
    if(applVersionInteg>=300)   //chk for new reset option         //08142002
    {															  //08142002	
        evptr->data.generic.datum[2] =find_integer();             //08142002 get option to reset to design state from code
        if (frmNo == FrmGetActiveFormID())
	    {
	        //going to same form to clear it
//SysFatalAlert("erasing");
	        FrmEraseForm(FrmGetActiveForm());   //erase form to avoid os err msg
//SysFatalAlert("Done");
	    } 
    }															  //08142002
    else evptr->data.generic.datum[2] =0;                         //08142002 dont reset to design state
//StrPrintF(debug,"nextscreen %d  restore=%d",ID,evptr->data.generic.datum[2]);
//SysFatalAlert(debug);    
    
    EvtAddEventToQueue(evptr);
    //MemPtrUnlock(evptr);
    MemPtrFree(evptr);  //08032002
}

/********************************************************************************************/
void verb_not_logic_oper()    /* handle -not- logic -----------------*/
{
    unsigned int i, j;
    i = find_integer();
    j = find_integer();
    if(logic_var[i] ) logic_var[j] = 0;
    else              logic_var[j] = 1;
}

/********************************************************************************************/
void verb_or()                      /*----------or-----------*/
{
    unsigned int a,b,c;
    a=find_integer();
    b=find_integer();
    c=find_integer();
    if( (logic_var[a] ==1) || (logic_var[b] ==1) )
	 logic_var[c] =1;
    else logic_var[c] =0;
}

/********************************************************************************************/
void verb_gosub()                          /*-------gosub-----------*/
{
    VoidHand perfTemp;
    VoidPtr perf;
    unsigned int offset;                     /**/
    offset = find_offset();
    perfTemp=MemHandleNew(6);
    if(perfTemp==0) OutOfMemory(6050);  //05282003
    perf=MemHandleLock(perfTemp);
    *((UInt *)perf)=instr_ctr;
    *((VoidHand*)((char*)(perf)+2))=perfHand;
//StrPrintF(debug,"gosub ic=%d off=%d",instr_ctr,offset);
//SysFatalAlert(debug);
    perfHand=perfTemp;
    MemPtrUnlock(perf);
    instr_ctr =  offset;
}

/********************************************************************************************/
void verb_relat_logic_oper()     /*-------relational logic operators---*/
{
//char work[266];
     unsigned if_oper;
     unsigned int log_var;
    find_arg_1_2();
    if_oper=find_integer();
    log_var=find_integer();
    if(compare_args(arg1,(double*)arg1_val,arg2,(double*)arg2_val,if_oper)==1)
		logic_var[log_var] =1;
    else        logic_var[log_var] =0;
/*-------
StrPrintF(work,"at relat logic oper test =%i using logvar=%i",logic_var[log_var],log_var);
test_debug(work);
---------*/
}

/********************************************************************************************/
void verb_stop()                               /*--------------stop--------*/
{
	
    //ch'd 2/7/00 to use code to enqueue a launchChr
    EventType  newEvent;
    newEvent.eType = keyDownEvent;
    newEvent.data.keyDown.chr=launchChr;  //enqueue a char to force launcher to come up
    newEvent.data.keyDown.modifiers=commandKeyMask;
    EvtAddEventToQueue(&newEvent);        //add event and it will trigger the launcher to appear
}

/********************************************************************************************/
void commonSetFocus(FormPtr frmPtr, int the_one)
{
    Word i;
    
    //back out this chg on 04302003 chkFldUpdate();  //04072003
    //also if we come back to this, it should chk that the field which has focus is not the one getting focus again,because
    //it should not fire in that case
    for(i=0;i<FrmGetNumberOfObjects(frmPtr);++i)
    {
        if(FrmGetObjectId(frmPtr,i) != the_one ) continue;
        FrmSetFocus(frmPtr,noFocus);   //09092002 may reset to avoid losing focus if fld already had(bug213)
        FrmSetFocus(frmPtr,i);
        fldToUpdate=the_one;   //added 5.20.2000
        break;
    }
}
/********************************************************************************************/
void verb_cursor_id()
{
    
    Word the_one;
    FormPtr frmPtr;
   
    the_one=find_integer();
    frmPtr=FrmGetActiveForm();
    commonSetFocus(frmPtr,the_one);

}
/***************************************************************************************************/
void commonRedrawId(FormPtr frmPtr, int the_one)
{
   int theType;
    
    Word i;
    int w;
   
    
  Word idx;              //added 5.20.2000  
  
  VoidHand oldHand;
  VoidHand h;
  VoidPtr p;
  struct ObjectData * objPtr;    //added 09242003
    
    //the_one=find_integer();
    //theType=find_char();
//w=the_one;     
//StrPrintF(debug,"redraw-id =%d   #objects=%d  w=%d",the_one,FrmGetNumberOfObjects(FrmGetActiveForm()),w);
//SysFatalAlert(debug);
    for(i=0;i<FrmGetNumberOfObjects(frmPtr);++i)
    {
//StrPrintF(debug,"comparing =%d to =%d",the_one,FrmGetObjectId(FrmGetActiveForm(),i));
//SysFatalAlert(debug);
        if(FrmGetObjectId(frmPtr,i) != the_one ) continue;
//dbug("hide/reshow");
        
        theType=FrmGetObjectType(frmPtr, i);
        if (theType==frmControlObj)
        {
redrawCtl:
           CtlDrawControl ((ControlType*)FrmGetObjectPtr(frmPtr,i));
           return ;
        }
        if (theType==frmListObj)
        {
           LstDrawList ((ListType*)FrmGetObjectPtr(frmPtr,i));
           return;
        }   
        if (theType==frmFieldObj)
        {
            FldDrawField ((FieldType*)FrmGetObjectPtr(frmPtr,i));
            //frmPtr= FrmGetActiveForm();                                                   //added 12172001
//SysFatalAlert("re-showing field");
            //see if any attached scrollbars that need updated                            //added 12172001
            
            if( i<FrmGetNumberOfObjects(frmPtr)-1)                                      //added 12172001
            {                                                                             //added 12172001
                if(FrmGetObjectType(frmPtr, i+1)==frmScrollBarObj)                      //added 12172001
                {                                                                         //added 12172001 
                   //have an attached scrollbar                                           //added 12172001
                   
//SysFatalAlert("updating scrollbar at show");
                   UpdateScrollbar((FieldType*)FrmGetObjectPtr(frmPtr,i),    //added 12172001
                      (ScrollBarPtr )(FrmGetObjectPtr(frmPtr, i+1)));                   //added 12172001
                }                                                                         //added 12172001
            }                                                                             //added 12172001
            return;
        }
        //09242003 if (theType==frmTableObj)
        //09242003 {
        //09242003    TblDrawTable ((TableType*)FrmGetObjectPtr(frmPtr,i));        
        //09242003    return;
        //09242003 }
        if (theType==frmPopupObj)
        {

           CtlSetLabel((ControlType*)FrmGetObjectPtr(frmPtr,i), 
                       LstGetSelectionText((ListType*) FrmGetObjectPtr(frmPtr,i+1),
                                            LstGetSelection((ListType*)FrmGetObjectPtr(frmPtr,i+1))));
           //CtlSetLabel(FrmGetObjectPtr(FrmGetActiveForm(),i), "thisisatest");
           goto redrawCtl;            
        }
        //09242003  added
        if (theType==frmTableObj)
        {
           //FormatATableObject(FrmGetActiveForm(),locateObjectPtr(the_one),i);  //format the table first
           //TblDrawTable ((TableType*)FrmGetObjectPtr(FrmGetActiveForm(),i));  //then, redraw it      
//StrPrintF(debug," redraw id %d=redraw tbl",the_one);
//dbug(debug);
           objPtr=locateObjectPtr(the_one);

           redrawGrid(objPtr);
//dbug("back from draw table");
           //freeObjectPtr();                 
           return;
        }
        //09242003 endof additions 
        FrmHideObject(frmPtr,i);
        FrmShowObject(frmPtr,i);
        break;
 
    }
}
/***************************************************************************************************/
void verb_redraw_id()
{
    char theType;
    Word the_one;
    FormPtr frmPtr;
    
    
    the_one=find_integer();
    theType=find_char();
    frmPtr=FrmGetActiveForm();
    commonRedrawId(frmPtr, the_one);

}
/***********************************************************************************************/
void verb_preceedSubFunc()             //added 04012005
{
SysFatalAlert("in preceed!!!!!!!!!!!!!!");
	cur_module_id = find_integer();    //04012005
    cur_stmt_no = find_integer();	
}

/********************************************************************************************/
void code_initialize()
{
	int sz;
	VoidHand newCodeHand;
	struct codeBlock*  newCodePtr;
	VoidHand h2;
	VoidPtr p2;
	UInt idx2;
	VoidPtr tempPtr;
	void verb_function();
	char *temp = (char*)null_ptr;
	double wkdbl = 0;
	int i;
	int j;
	int fno;
	init_first_time = 1;

	for( i = 0; i < 256; ++i )						// 01/29/2001 MMD
	{														// 01/29/2001 MMD
#ifdef ORG_NSB											// 01/29/2001 MMD
		if( op_func[i] == NULL )					// 01/29/2001 MMD
#endif													// 01/29/2001 MMD
			op_func[i] = &illegal_op_code;		// 01/29/2001 MMD
	}														// 01/29/2001 MMD

	// This section cleaned up // 01/29/2001 MMD
	op_func[0x04] = &verb_add;    
	op_func[0x05] = &verb_beep;
	op_func[0x07] = &verb_seteventhandled;
	op_func[0x06] = &verb_popupclear;
	op_func[0x09] = &verb_display;
	op_func[0x0a] = &verb_divide;
	op_func[0x0c] = &verb_if;
	op_func[0x0e] = &verb_multiply;

	op_func[0x10] = &verb_gosub;
	op_func[0x11] = &verb_call;
	op_func[0x12] = &verb_sub;
	op_func[0x13] = &verb_user_func;
	op_func[0x18] = &verb_stop;
	op_func[0x19] = &verb_initAVariableValue;
	op_func[0x1a] = &verb_subtract;
	op_func[0x1b] = &verb_negate;
	op_func[0x1c] = &verb_dbread;
	op_func[0x1d] = &verb_return;
	op_func[0x1e] = &verb_goto;
	op_func[0x1f] = &verb_dbgetnorecs;

	op_func[0x20] = &verb_menuerase;
	op_func[0x21] = &verb_menudraw;
	op_func[0x22] = &verb_menureset;
	op_func[0x23] = &verb_dbfind;
	op_func[0x24] = &verb_dbread;
	op_func[0x25] = &verb_dbupdate;
	op_func[0x26] = &verb_dbdelete;
	op_func[0x27] = &verb_dbinsert;
	op_func[0x28] = &verb_dbreadnext;
	op_func[0x29] = &verb_dberase;
	op_func[0x2a] = &verb_dbcreate;
	op_func[0x2b] = &verb_dbopen;
	op_func[0x2c] = &verb_dbclose;
	op_func[0x2d] = &verb_dbget;
	op_func[0x2e] = &verb_dbput;
	op_func[0x2f] = &verb_dbposition;

	op_func[0x30] = &verb_controlsetstatus;
	op_func[0x31] = &verb_controlhideorshow;
	op_func[0x32] = &verb_fieldsettext;
	op_func[0x33] = &verb_fieldsetmaxchars;
	op_func[0x34] = &verb_listadditem;
	op_func[0x35] = &verb_listdeleteitem;
	op_func[0x36] = &verb_listsetselected;
	//op_func[0x37] = &verb_controlssettext;
	
	op_func[0x3b] = &verb_controlsetstatusNew;
	
	op_func[0x3d] = &verb_assign_bitmap;
	op_func[0x3e] = &verb_controlsetlabel;
	op_func[0x3f] = &verb_setscrollbar;

	op_func[0x40] = &verb_createwindow;
	op_func[0x41] = &verb_destroywindow;
	op_func[0x42] = &verb_erasewindow;
	op_func[0x43] = &verb_drawchars;
	op_func[0x44] = &verb_drawline;
	op_func[0x45] = &verb_drawrectangle;
	op_func[0x46] = &verb_fillrectangle;
	op_func[0x47] = &verb_setcurwindow;
	op_func[0x48] = &verb_draw_bitmap;
	op_func[0x49] = &verb_dbreadprev;
	op_func[0x4a] = &verb_delay;
	op_func[0x4b] = &verb_sound;
	op_func[0x4c] = &verb_getPen;
	op_func[0x4d] = &verb_listclear;
	op_func[0x4e] = &verb_playsound;

	op_func[0x50] = &verb_exponentiation;
	op_func[0x51] = &verb_not_logic_oper;
	op_func[0x52] = &verb_relat_logic_oper;
	op_func[0x53] = &verb_logic_class_tests;
	op_func[0x54] = &verb_and;
	op_func[0x55] = &verb_or;
	op_func[0x57] = &verb_special_arith_store;
	
	op_func[0x59] = &verb_compute;
	
	op_func[0x5b] = &verb_clear_frac_dgts;
//reserve 5c and 5d for bindToDatabase    09242003

	
	
	//70-74 used by nsbasic
	op_func[0x75] = &verb_signatureErase;
	op_func[0x76] = &verb_signatureStartCapture;
	op_func[0x77] = &verb_signatureDisplay;

	op_func[0x80] = &verb_nextscreen;
	op_func[0x81] = &verb_clearscreentextfields;   //added 06102002
	op_func[0x82] = &verb_redraw;
	op_func[0x83] = &verb_nextscreenwithvariable;   //added 06102002
	op_func[0x84] = &verb_cursor_id;
	op_func[0x85] = &verb_redraw_id;
	op_func[0x86] = &verb_dbputnew;
	op_func[0x87] = &verb_dbgetnew;
	op_func[0x88] = &verb_generalVerb;      //added08222002
	op_func[0x89] = &verb_setGeneralProperty;        //added08222002
	op_func[0x8a] = &verb_func_getGeneralPropertyNumeric;      //added08222002
	op_func[0x8b] = &verb_func_getGeneralPropertyString;      //added08222002
	op_func[0x90] = &verb_concat_two_strings;   
	

	op_func[0xa1] = &verb_startfor;
	op_func[0xa2] = &verb_continuefor;
	op_func[0xa3] = &verb_next;
	op_func[0xa7] = &verb_do;
	op_func[0xa8] = &verb_dountil;
	op_func[0xa9] = &verb_dowhile;
	op_func[0xaa] = &verb_loop;
	op_func[0xab] = &verb_exitdo;
	op_func[0xac] = &verb_exitfor;

	op_func[0xb2] = &verb_launchprogram;
	op_func[0xb3] = &verb_transfertoprogram;

	op_func[0xc0] = &verb_setnumvarsfromheap;   //added 06102002
	op_func[0xc1] = &verb_alert;
	op_func[0xc2] = &verb_start_function;

	op_func[0xd2] = &verb_cursor;
	op_func[0xd3] = &verb_errmsg;
	
	op_func[0xdc] = &verb_dbreset;
	op_func[0xdd] = &verb_end_logic_cond;
	op_func[0xde] = &verb_function;

	//04012005 op_func[0xf0] = &verb_start_new_parag;
	op_func[0xf1] = &verb_start_new_stmt;
	op_func[0xf2] = &verb_preceedSubFunc;  //added 04012005
	op_func[0xf8] = &verb_end_sub;
	op_func[0xf9] = &verb_end_function;
	op_func[0xfd] = &verb_start_debug;
	op_func[0xfe] = &verb_end_debug;

	for( i = 0; i < 15; ++i )
		dummyCode[i] = 0x00; 
	clearArgs();
	debug_sw = 0;
           /**/

	sz = sizeof(sampleCodeBlock);
	newCodeHand = MemHandleNew(sz);
	if(newCodeHand==0)  OutOfMemory(6051);  //05282003
	newCodePtr = (struct codeBlock*)MemHandleLock(newCodeHand);
	newCodePtr->prevCodePtr = null_ptr;
	codeBlockPtr = newCodePtr;

	codeBlockPtr->id = 50000;
	codeBlockPtr->p3 = null_ptr;
	codeBlockPtr->h3 = 0;
	codeBlockPtr->numberParas = 0;
	codeBlockPtr->paragTbl = null_ptr;
	codeBlockPtr->codePtr = &dummyCode[0];
	codePtr = &dummyCode[0];

	codeBlockPtr->instr_ctr = 0;
	codeBlockPtr->oldOffset = 0;
	codeBlockPtr->functionLinkNo=0;
	h3 = 0;
	p3 = (char*)null_ptr;
//StrPrintF(debug,"in init codeBlockPtr=%lu codePtr=%lu",codeBlockPtr,codePtr);
//SysFatalAlert(debug);
}

/********************************************************************************************/
int getx()
{
   short x,y;
   InsPtGetLocation(&x,&y);
   return(x);
}

/********************************************************************************************/
int gety()
{
  short x,y;
  InsPtGetLocation(&x,&y);
  return(y);
}

/********************************************************************************************/
void debug_addr( char * x)
{
/*---
unsigned char x1;
unsigned char x2;
unsigned char x3;
unsigned char x4;
x1=*((char*)&x);
x2=*((char*)&x+1);
x3=*((char*)&x+2);
x4=*((char*)&x+3);
StrPrintF(debug,"address is %d %d %d %d",x1,x2,x3,x4);
-*/
//StrPrintF(debug,"address is %lu",((unsigned long)x) );
//SysFatalAlert(debug);
}

/********************************************************************************************/
void verb_alert()
{
  //Note:  ldm 09132004 had to add a save of arg1 before calling sys function because
  //           it is destroying arg1 address.  Don't know why
  struct dataelem* arg1Save;   //ldm 09132004
  VoidPtr ptr;
  VoidHand hView;
  int res;
  int cnt;
  char rest[900];
  int howMany;
  //AlertResourceType al;
  struct  //GHGlue
  {
		UInt16		alertType;
		UInt16		helpRscID;
		UInt16		numButtons;
		UInt16		defaultButton;
  } al;  //GHGlue

  find_arg_1_4();     //result button
                      //title
                      //message
                      //type
  cnt=0;
  StrCopy(rest,"");
  al.alertType=basc_integ_value(arg4,(double*)arg4_val);
  al.numButtons=0;
  al.defaultButton=0;
  al.helpRscID=0;
  cnt=8;   //will fill in 1st 8 later
  MemMove(rest+cnt,arg2_val,StrLen(arg2_val)+1);    
  cnt+=StrLen(arg2_val)+1;
  
  howMany=StrLen(arg3_val);
  if(howMany>800) howMany=800;
  MemMove(rest+cnt,arg3_val,howMany+1);
  rest[cnt+howMany]=0x00;
  cnt +=howMany+1;

  while(1)
  {    
     find_arg_2();
     if (arg2==null_ptr) break;

     MemMove(rest+cnt,arg2_val,StrLen(arg2_val)+1);
     cnt=cnt+StrLen(arg2_val)+1;
     al.numButtons+=1;
  }
  MemMove(rest,&al,8);

  res=DmFindResource(VbRscDB,(ULong)'Talt',(ULong)1,nil);
  if(res != -1) DmRemoveResource(VbRscDB,res); //delete alert if there
  
  hView=DmNewResource(VbRscDB,(ULong)'Talt',(ULong)1,cnt);

  if(hView==0) SysFatalAlert("Out of Memory-alert");
  ptr=MemHandleLock(hView);
//StrPrintF(debug,"verb-alert= %s",rest);
//SysFatalAlert(debug);      
  DmWrite(ptr,0,rest,cnt);
  MemHandleUnlock(hView);

//StrPrintF(debug,"alert arg1=%lu",arg1);
//SysFatalAlert(debug);
  arg1Save = arg1;     //ldm 09132004
  msgboxOrAlertUp=true;  //stops penup from triggering object under msgbox 
  res=FrmAlert(1);
  msgboxOrAlertUp=false;
  ignoreNextPenup=true;
  
 //StrPrintF(debug,"alert arg1=%lu",arg1);
 //SysFatalAlert(debug);
 arg1=arg1Save;   //ldm 09132004
  restore_int_val(res,arg1, (double*)arg1_val, arg1_occ1,arg1_occ2,arg1_occ3);
}

/********************************************************************************************/
void verb_sound()
{
   SndCommandType s;
  int wait;
  Boolean waitsw;

   find_arg_1_3();  //freq,duration,amplitude
   wait=find_char();
   
   if(romVersion<0x03000000)
   {
        if(PrefGetPreference(prefGameSoundLevelV20)==slOff) return;  //prior to v3.0 -- exit if game sound off
   }
   else
   {
        if(PrefGetPreference(prefGameSoundVolume)==0) return;        //v3.0 and up -- exit if game sound volume=0
   }
   
   if (wait==0x00) waitsw=false;
   else            waitsw=true;
   s.cmd=sndCmdFreqDurationAmp;
   s.param1=*((double*)arg1_val);
   s.param2=*((double*)arg2_val);
   s.param3=*((double*)arg3_val);
   SndDoCmd(0,&s,waitsw);   //play the sound
}
/********************************************************************************************/
void verb_playsound()
{
    int 		theSoundId;
    VoidHand	theResourceHandle;
	SndPtr		theSoundPtr;
	Int32 		ampScale;
	UInt32 		flags;
	UInt32		version;
	
	if (!FtrGet(sysFileCSoundMgr,sndFtrIDVersion,&version))
	{
	    find_arg_1();
//SysFatalAlert("at playsound");
	    find_arg_2();
	    find_arg_3();	
		theSoundId=basc_integ_value(arg1,(double*)arg1_val);
	    ampScale=basc_integ_value(arg2,(double*)arg2_val);
		flags=basc_integ_value(arg3,(double*)arg3_val);
		// Grab the handle to our Sound resource
		theResourceHandle = DmGetResource( sysResTSound, theSoundId );
		if (theResourceHandle==nil)
		{                               
		   SysFatalAlert("Can't find a sound to play.");
		   ErrThrow(-1);                
		}                                //inserted 05212003
		// Lock down the handle so we can get the pointer to the bitmap
		theSoundPtr = (BitmapType*)MemHandleLock( theResourceHandle );
	//SysFatalAlert("at SndPlayReource");
		ErrTry{
		SndPlayResource(theSoundPtr,ampScale, flags);  //Sony device may have the feature, but not this function
		}
		ErrCatch (inErr) ErrEndCatch;
		// Unlock the handle to the bitmap
		MemHandleUnlock( theResourceHandle );

		// Finally, release the resource
		DmReleaseResource( theResourceHandle );
	}
}


/********************************************************************************************/
void formRect(RectangleType *r)
{
  r->topLeft.x=*((double*)arg1_val);
  r->topLeft.y=*((double*)arg2_val);
  r->extent.x=*((double*)arg3_val);
  r->extent.y=*((double*)arg4_val);
}

/********************************************************************************************/
void verb_fillrectangle()
{
  UInt16 cornerDiam;
  unsigned char pen;
  RectangleType r;
  UInt custPatternBlack[8] ={ 0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff};
  UInt custPatternWhite[8] ={ 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000};
  UInt custPatternGray[8] ={ 0xaa55,0xaa55,0xaa55,0xaa55,0xaa55,0xaa55,0xaa55,0xaa55};
  find_arg_1_4();    //1=topleft  x  2=topleft y 3=wodth  4=height
  find_arg_5();      //corner diam
  pen=find_char();      //pen
  cornerDiam=basc_integ_value(arg5,(double*)arg5_val);
  
//StrPrintF(debug,"setting patern %d",pen);
//SysFatalAlert(debug);  
  if (pen==0x00)
  {
//dbug("drawBlack");
    
     WinSetPattern((CustomPatternType*)(&custPatternBlack));
  }
  else
  {
     if(pen==0x01)
     {
//dbug("drawWhite");
       
        WinSetPattern((CustomPatternType*)(&custPatternWhite));
     }
     else
     {
       if(pen==0x02)
       {
          
//dbug("draw gray");
          WinSetPattern((CustomPatternType*)(&custPatternGray));
       }
     }
    
  }
  formRect(&r);
//StrPrintF(debug, "fillRect x=%d y=%d w=%d ht=%d corner=%d patt=%d",r.topLeft.x,r.topLeft.y,r.extent.x,r.extent.y,cornerDiam,WinGetPatternType());
//SysFatalAlert(debug);


  
  if(romVersion>=(unsigned long)(0x03500000)) WinSetPatternType(customPattern);
  
  WinFillRectangle(&r,cornerDiam);
}

/********************************************************************************************/
void verb_drawrectangle()
{
  RectangleType r;
  FrameBitsType	frameBits;
  unsigned char pen;
  find_arg_1_4();    //1=topleft  x  2=topleft y 3=wodth  4=height
  find_arg_5();      //corner diam
  pen=find_char();      //pen
  
  frameBits.word = 0;					// initialize the entire structure
	frameBits.bits.cornerDiam = basc_integ_value(arg5,(double*)arg5_val);
	frameBits.bits.threeD = 0;
	frameBits.bits.shadowWidth = 0;
	frameBits.bits.width = 1;
	if (pen==0x00)
  {
     formRect(&r);
     r.topLeft.x+=1;
     r.topLeft.y+=1;
     r.extent.x -=2;
     r.extent.y -=2;
     WinDrawRectangleFrame(frameBits.word,&r);
  }
  else
  {
    if(pen==0x01)
    {
       formRect(&r);
       r.topLeft.x+=1;
       r.topLeft.y+=1;
       r.extent.x -=2;
       r.extent.y -=2;
       WinEraseRectangleFrame(frameBits.word,&r);
    }
    else
    {
       formRect(&r);
       r.topLeft.x+=1;
       r.topLeft.y+=1;
       r.extent.x -=2;
       r.extent.y -=2;
       WinDrawGrayRectangleFrame(frameBits.word,&r);
    }
  }
}

/********************************************************************************************/
void verb_drawline()
{
  unsigned char pen;

  find_arg_1_4();    //1=topleft  x  2=topleft y 3=endx  4=endy
  pen=find_char();      //pen
  if (pen==0x00) WinDrawLine(*((double*)arg1_val),
                               *((double*)arg2_val),
                               *((double*)arg3_val),
                               *((double*)arg4_val));
  else
  {
    if(pen==0x01) WinEraseLine(*((double*)arg1_val),
                                 *((double*)arg2_val),
                                 *((double*)arg3_val),
                                 *((double*)arg4_val));
    else           WinDrawGrayLine(*((double*)arg1_val),
                                   *((double*)arg2_val),
                                   *((double*)arg3_val),
                                   *((double*)arg4_val));

  }
  
}

/********************************************************************************************/
void verb_drawchars()
{
  unsigned char pen;
  find_arg_1_3();   //1=chars , 2=x , 3=y
  pen=find_char();
  if (pen==0x00) WinDrawChars(arg1_val,StrLen(arg1_val),
                                 *((double*)arg2_val),*((double*)arg3_val));
  else           WinDrawInvertedChars(arg1_val,StrLen(arg1_val),
                                 *((double*)arg2_val),*((double*)arg3_val));

}

/********************************************************************************************/
void verb_erasewindow()
{
  WinSetDrawWindow(DrawWin); 
  WinSetActiveWindow(DrawWin);
  WinEraseWindow();
}

/********************************************************************************************/
Handle findNewWindow()
{
   VoidHand         h;
   struct DrawWinStruct *p;
   VoidHand nameH;
   char *  nameP;
   find_arg_1();  //win name string
   h=winRoot;
   while(1)
   {
      if(h==0)
      {
           //create new window
           h=MemHandleNew(sizeof(struct DrawWinStruct));
           if(h==0) OutOfMemory(6052);  //05282003
           p=(struct DrawWinStruct*)MemHandleLock(h);
           p->next=winRoot;
           nameH=MemHandleNew(StrLen(arg1_val)+1);
           if(nameH==0) OutOfMemory(6053);  //05282003
           nameP=(char*)MemHandleLock(nameH);
           StrCopy(nameP,arg1_val);
           MemHandleUnlock(nameH);
           p->nameHandle=(Handle)nameH;
           winRoot=(Handle)h;
           MemPtrUnlock(p);
           return((Handle)h);
       }
        p=(struct DrawWinStruct*)MemHandleLock(h);
        nameP=(char*)MemHandleLock(p->nameHandle);
        if( StrCaselessCompare(nameP,arg1_val)==0)
        {
            MemPtrUnlock(nameP);
            MemPtrUnlock(p);
            return((Handle)h);
        }
        
       MemPtrUnlock(nameP);
       h=p->next;
       MemPtrUnlock(p);
   }
}

/********************************************************************************************/
Handle findOldWindow()
{
   char wk[128];
   Handle         h;
   char *nameP;
   struct DrawWinStruct *p;
   find_arg_1();  //win name string
   h=winRoot;
   while(1)
   {
      if(h==0) 
      {
        StrCopy(wk,"Can't locate draw window=");
        StrCat(wk,arg1_val);
        SysFatalAlert(wk);
        ErrThrow(-1);                 //inserted 05212003
      }
      p=(struct DrawWinStruct*)MemHandleLock(h);
      nameP=(char*)MemHandleLock(p->nameHandle);
      if(StrCaselessCompare(nameP,arg1_val)==0)
      {
          MemHandleUnlock(p->nameHandle);
          MemHandleUnlock(h);
          return(h);            
      }
      MemHandleUnlock(p->nameHandle); 
      h=p->next;
      MemPtrUnlock(p);
   }
}

/********************************************************************************************/
void verb_setcurwindow()
{
  RectangleType r;
  char wk[128];
  Handle          tempH;
  struct DrawWinStruct * tempP; 
  tempH=findOldWindow();
  if(tempH==0)
  {
      StrCopy(wk,"Accessed an unknown window=");
      StrCat(wk,arg1_val);
      SysFatalAlert(wk);
      ErrThrow(-1);                 //inserted 05212003 
  }
  tempP=(struct DrawWinStruct*)MemHandleLock(tempH); 
  DrawWin=tempP->win;
  WinSetActiveWindow(DrawWin);
  
  WinSetDrawWindow(DrawWin);                
  WinGetWindowBounds(&r);
  r.topLeft.x=0;                            
  r.topLeft.y=0;                            
  WinSetClip(&r);        
  MemHandleUnlock(tempH);  
}

/********************************************************************************************/
void verb_destroywindow()
{
  char wk[128];
  Handle          tempH;
  struct DrawWinStruct * tempP;
  Handle          h;
  struct DrawWinStruct * p;
  Handle          prevH;
  struct DrawWinStruct * prevPtr;
  WinHandle saveWin;
  RectangleType r;
  
  tempH=findOldWindow();
  if(tempH==0)
  {
      StrCopy(wk,"Accessed an unknown window=");
      StrCat(wk,arg1_val);
      SysFatalAlert(wk);
      ErrThrow(-1);                 //inserted 05212003 
  }

  tempP=(struct DrawWinStruct*)MemHandleLock(tempH);
  saveWin=tempP->win;

  WinSetDrawWindow(tempP->prevWin);
  WinSetActiveWindow(tempP->prevWin);
  WinDeleteWindow(tempP->win,true);
  WinGetWindowBounds(&r);
  WinSetClip(&r);
  
  MemPtrUnlock(tempP);
 
  h=winRoot;
  prevH=0;
  while(1)
  {
     if(h==tempH)
     {

         FrmEraseForm(FrmGetActiveForm());

         
  
         //??doesn't work WinSetDrawWindow(&(FrmGetActiveForm()->window));                //6.28
         p=(struct DrawWinStruct*)MemHandleLock(h);
         if(prevH==0)
         {

            winRoot=p->next;
             
         }
         else 
         {

             prevPtr=(struct DrawWinStruct *)MemHandleLock(prevH);
             prevPtr->next=p->next;
             MemPtrUnlock(prevPtr);
         }

         MemHandleFree(p->nameHandle);
         MemPtrUnlock(p);
        
         FrmDrawForm(FrmGetActiveForm()); 

         MemHandleFree(h);

         return;
     } 
     else 
     {

        prevH=h;
        p=(struct DrawWinStruct*)MemHandleLock(h);
        h=p->next;
        MemPtrUnlock(p);
     }
  }
}

/********************************************************************************************/
void verb_createwindow()
{
  RectangleType r;
  UInt err;
  struct DrawWinStruct*   tempP;
  Handle tempH; 
  tempH=findNewWindow();
  find_arg_1_4();   // 1=topleft x, 2=topleft y, 3=width, 4=height
   
  r.topLeft.x=*((double*)arg1_val);
  r.topLeft.y=*((double*)arg2_val);
  r.extent.x=*((double*)arg3_val);
  r.extent.y=*((double*)arg4_val);
 
  tempP=(struct DrawWinStruct*)MemHandleLock(tempH);
  tempP->prevWin=WinGetDrawWindow();
  DrawWin=WinCreateWindow(&r,1,false,false,&err);
  
  WinSetActiveWindow(DrawWin);
  
  WinSetDrawWindow(DrawWin);                //6.28
  r.topLeft.x=0;                            //6.28
  r.topLeft.y=0;                            //6.28
  WinSetClip(&r);                            //6.28
  tempP->win=DrawWin;
  MemHandleUnlock(tempH); 
}

/********************************************************************************************/
void verb_sub()
{
  UInt instr_ctr_save;
  char *saveCodePtr;
  UInt callerInstrCtrSave;
  int kk,mm,nn;
  
  Int ix;
  int id;
  
  Err err;
  VoidHand newHand;
  VoidPtr newPtr;
  ULong wkl;
  int wk1;
//if(debug_sw){
//dbug("verb_sub");
//}
   
   
  verbOrFunction='s';
  callerInstrCtrSave=codeBlockPtr->instr_ctr;
//StrPrintF(debug,"callers codePtr=%lu  callers-instr-ctr=%u instr_ctr=%d curCodePtr=%lu",(unsigned long)(codeBlockPtr->codePtr),codeBlockPtr->instr_ctr,instr_ctr,(unsigned long)codePtr);
//SysFatalAlert(debug); 

  
  codeBlockPtr->argsOffset=instr_ctr; //save called args ptr
  instr_ctr_save=instr_ctr;
//StrPrintF(debug,"sub start saving called pgms args offset=%d",instr_ctr);
//SysFatalAlert(debug);

  while (1)
  {
//if(debug_sw){
//dbug("3");
//}
    instr_ctr_save=instr_ctr;
    saveCodePtr=codePtr;
    codePtr=(char*)codeBlockPtr->codePtr;
    instr_ctr=codeBlockPtr->instr_ctr;
//if(debug_sw){
//StrPrintF(debug,"ss  instr_ctr=%d codeblockptr=%lu codePtr=%lu",instr_ctr,codeBlockPtr,codePtr);
//SysFatalAlert(debug);
//}
    find_arg_1();
//if(debug_sw){
//dbug("past ss");
//}
    codeBlockPtr->instr_ctr=instr_ctr;
    codePtr=saveCodePtr;
    instr_ctr=instr_ctr_save;

    find_arg_2();

     if (arg1==null_ptr)
    {

      if (arg2 != null_ptr)
      {
wrong_no:
         MiscFatalAlert("Wrong number of func args");
      }
      else break;
    }
//dbug("caller not null");
    if (arg2==null_ptr)
    {
//dbug("func is null");
        goto wrong_no;
    }
//StrPrintF(debug,"arg2#=%d s1=%d s2=%d s3=%d  offset=%d",arg2->tbl_no,arg2->max_no_values1,arg2->max_no_values2, arg2->max_no_values3,instr_ctr); 
//SysFatalAlert(debug);
    subFuncXferArgument();
  }
  
no_args:



goahead:
//if(debug_sw){
//dbug("e");
//}
   codeBlockPtr->instr_ctr=callerInstrCtrSave;  //reset caller so can reuse later

    //copy the current work var handles
//StrPrintF(debug,"init wk vars id=%d",lastSubOrFunctionId);  
//SysFatalAlert(debug); 
   userFunctionSequentialNo+=1;  //bump the count of nested user functions
   codeBlockPtr->functionLinkNo=lastSubOrFunctionId;
//StrPrintF(debug,"new sub increm seqno=%d   id=%d",userFunctionSequentialNo,lastSubOrFunctionId);
//SysFatalAlert(debug);     
   wkl=work_de_max*4;   //need to copy all work variable handles
   id=codeBlockPtr->functionLinkNo;
   
   while(1)
   {
      ix=DmFindResource(VbRscDB,(ULong)'fwrk',id,NIL); 
      if(ix!= -1)
      {
//dbug("got old sub rec");
        newHand=MiscDmGetResourceIndex(VbRscDB,ix,"rescwk"); 
        newPtr=MiscHandleLock(newHand);
        if( (*((int*)newPtr) != codeBlockPtr->functionLinkNo) || (*(unsigned int*)((char*)newPtr+2) != codeBlockPtr->offset))
        {
           MiscHandleUnlock(newHand);
           MiscDmReleaseResource(newHand);
           id+=50;                        //increm recno by 50 to try again
        }
        else
        {
           break;
        }    
      }
      else
      {
//dbug("got new sub rec");
        newHand=MiscDmNewResource(VbRscDB,(ULong)'fwrk',id,wkl+4,"rescwk"); //setup a new resource for the new copy
        if(newHand==0) OutOfMemory(6101);    //inserted 05282003
        newPtr=MiscHandleLock(newHand);  
        break;
      }
   }   
//StrPrintF(debug,"find linkNo=%d rsc=%d ",id,ix);
//SysFatalAlert(debug);
                              //point to the new wk var record

//dbug("verb sub");
   DmWrite(newPtr,0,&codeBlockPtr->functionLinkNo,2);
 
   DmWrite(newPtr,2,&codeBlockPtr->offset,2);
 
   DmWrite(newPtr,4,(char*)deListPtr+4,wkl);  //copy the record

   MiscPtrUnlock(newPtr);

   err=MiscDmReleaseResource(newHand);                             //release the new record 
   if(err) MiscFatalAlert("Internal error-Can't release work record.");
 
   
   //old wk var handles saved, now zero them all for new func
   
    DmSet(deListPtr,4,wkl,0x00); 
//dbug("leaving sub init");    
    return;
}

/********************************************************************************************/
void verb_start_function()
{
  UInt instr_ctr_save;
  int kk,mm,nn;
  char *codePtrSave;
  UInt callerInstrCtrSave=codeBlockPtr->instr_ctr;
  
  Int ix;
  int id;
  Err err;
  VoidHand newHand;
  VoidPtr newPtr;
  ULong wkl;
  int wk1;
  
  verbOrFunction='f';
  
  
  codeBlockPtr->argsOffset=instr_ctr;  //save called args ptr  
//dbug("copying args");
  while (1)   //copy args to internal vars
  {

    instr_ctr_save=instr_ctr;
    codePtrSave=codePtr;
    codePtr=(char*)codeBlockPtr->codePtr;
    instr_ctr=codeBlockPtr->instr_ctr;
//StrPrintF(debug,"moving one arg instr-ctr=%ui",instr_ctr);
//SysFatalAlert(debug);    
    find_arg_1();
    codeBlockPtr->instr_ctr=instr_ctr;
    codePtr=codePtrSave;
    instr_ctr=instr_ctr_save;
    find_arg_2();
     if (arg1==null_ptr)
    {

      if (arg2 != null_ptr)
      {
wrong_no:
         MiscFatalAlert("Wrong number of func args");
      }
      else break;
    }
//dbug("caller not null");
    if (arg2==null_ptr)
    {
//dbug("func is null");
        goto wrong_no;
    }
//StrPrintF(debug,"arg2#=%d s1=%d s2=%d s3=%d  offset=%d",arg2->tbl_no,arg2->max_no_values1,arg2->max_no_values2, arg2->max_no_values3,instr_ctr); 
//SysFatalAlert(debug);
    subFuncXferArgument();
  }
//dbug("args done");
   
    find_arg_2();   //name of func dataname to put result in   ??used or not

    codeBlockPtr->instr_ctr=callerInstrCtrSave;  //reset caller so can reuse later
    
   //copy the current work var handles
   
   userFunctionSequentialNo+=1;  //bump the count of nested user functions
   codeBlockPtr->functionLinkNo=lastSubOrFunctionId;
//StrPrintF(debug,"function increm seqno=%d   id=%d",userFunctionSequentialNo,lastSubOrFunctionId);
//SysFatalAlert(debug);   
   wkl=work_de_max*4;   //need to copy all work variable handles
   id=codeBlockPtr->functionLinkNo;
   
   while(1)
   {
      ix=DmFindResource(VbRscDB,(ULong)'fwrk',id,NIL); 
      if(ix!= -1)
      {
//dbug("got old func rec");
        newHand=MiscDmGetResourceIndex(VbRscDB,ix,"rescwk"); 
        newPtr=MiscHandleLock(newHand);
        if( (*((int*)newPtr) != codeBlockPtr->functionLinkNo) || (*(unsigned int*)((char*)newPtr+2) != codeBlockPtr->offset))
        {
           MiscHandleUnlock(newHand);
           MiscDmReleaseResource(newHand);
           id+=50;                        //increm recno by 50 to try again
        }
        else
        {
           break;
        }   
      }
      else
      {
//dbug("got new func rec");
        newHand=MiscDmNewResource(VbRscDB,(ULong)'fwrk',id,wkl+4,"rescwk"); //setup a new resource for the new copy
        if(newHand==0) OutOfMemory(6102);    //inserted 05282003
        newPtr=MiscHandleLock(newHand);  
        break;
      }
   }   
//StrPrintF(debug,"find linkNo=%d rsc=%d ",id,ix);
//SysFatalAlert(debug);
                              //point to the new wk var record
//dbug("start function");
   DmWrite(newPtr,0,&codeBlockPtr->functionLinkNo,2);
   DmWrite(newPtr,2,&codeBlockPtr->offset,2);
   DmWrite(newPtr,4,(char*)deListPtr+4,wkl);  //copy the record
   
   MiscPtrUnlock(newPtr);
   err=MiscDmReleaseResource(newHand);                             //release the new record 
   if(err) MiscFatalAlert("Internal error-Can't release work record.");
   
   //old wk var handles saved, now zero them all for new func
//dbug("zeroing wk var ptrs");
   
   DmSet(deListPtr,4,wkl,0x00); 
}

/********************************************************************************************/
void verb_dbgetnorecs()
{
  struct dbType *db;
  
  int res;
  UInt i;
  double d;
  DmOpenRef dbr;
  
   dbfind_arg(2); //1=result,2=db
   
   db=getDatabasePtr( );
   dbr=db->dm;
   chkDbOpen(db);
   
   i=DmNumRecords(dbr);
   d=i;
   misc_stodbl1(&d);
   
}
/********************************************************************************************/
void verb_dbposition()
{
  struct dbType *db;
  VoidHand recHand;
  VoidPtr  recPtr;
  int res;
  char nullbyte[2] = {0x00,0x00};
  
  UInt i;
  UInt index;
  DmOpenRef dbr;
  int err;
  dbfind_arg(4); //1=errcode,2=db,3=where,4=offset
   
   db=getDatabasePtr( );
   dbr=db->dm;
   chkDbOpen(db);
   index=basc_integ_value(arg3,(double*)arg3_val)-1;
   i=DmNumRecords(dbr);
   while( DmNumRecords(dbr) < (index+1) )
   {
       i++;
       
       //create new record
       recHand=DmNewRecord(dbr,&i,1);
       if(recHand==0)      //inserted 05282003
       {                   //inserted 05282003
          setDbErr(dmErrMemError);      //inserted 05282003
          return;          //inserted 05282003  
       }                   //inserted 05282003
       recPtr=MemHandleLock(recHand);
      
       DmWrite(recPtr,0,&nullbyte[0],1);  //make a null
  //StrPrintF(debug," dbposition=%s len=%d",recPtr,StrLen(recPtr));
  //SysFatalAlert(debug);     
        
       MemHandleUnlock(recHand);
       DmReleaseRecord(dbr,i,true);
       
   }
   recHand=DmGetRecord(dbr,index);
   db->LastDbRecordRead=index;
   db->offset=basc_integ_value(arg4,(double*)arg4_val);
//recPtr=MemHandleLock(recHand);
//StrPrintF(debug,"offset=%u rec=%s",db->offset,recPtr);
//SysFatalAlert(debug);
//MemHandleUnlock(recHand);
   db->curHand=recHand;
   DmReleaseRecord(dbr,index,false);
   setDbOK();
}

/********************************************************************************************/
void verb_dbclose()
{
//09242003  int err;
  struct dbType *db;
//09242003  VoidHand recHand;
//09242003  VoidPtr  recPtr;
  int res;
//09242003  DmOpenRef dbr;

  dbfind_arg(2);
  db=getDatabasePtr();
  res=commonDbcloseLogic(db);   //added 09242003
  if (res==0) setDbOK();        //added 09242003
  else        setDbErr(res);    //added 09242003
}  
//additions 09242003
int commonDbcloseLogic(struct dbType *db)
{
  int err;
  VoidHand recHand;
  VoidPtr  recPtr;
  DmOpenRef dbr;

//end of additions 09242003 
  dbr=db->dm;
  if (db->openSw!='o') 
  {
      //09242003 setDbErr(dmErrInvalidParam);
      return(dmErrInvalidParam) ;   //modified 09242003
  }

  err=DmCloseDatabase(dbr);

   db->openSw='c';
   db->LastDbRecordRead=-1;
   db->curHand=0;
   db->offset=0;
   

   //09242003 if (err==0) setDbOK();
   //09242003 else        setDbErr(err);
   return(err);           //added 09242003
}
   

/********************************************************************************************/
void verb_dbopen()
{
  struct dbType *db;
  VoidHand recHand;
  VoidPtr  recPtr;
  int res;
  DmOpenRef dbr;
  int err;
  DmOpenRef dbref;

   dbfind_arg(4);
   db=getDatabasePtr();
   db->lid=DmFindDatabase( *((double*)arg4_val),arg3_val);
   if(db->lid==0)
   {
      setDbErr(DmGetLastErr());
      return;
   }
   dbref=DmOpenDatabase(*((double*)arg4_val),db->lid,dmModeReadWrite);
   if(dbref==0)
   {
         dbref=DmOpenDatabase(*((double*)arg4_val),db->lid,dmModeReadOnly);//02.20.02 GH
         if(dbref==0)
         {                                                        //02.20.02 GH
          setDbErr(DmGetLastErr()); // not opened
          return;
      }
      else setDbRes(3); //opened in read only mode                            //02.20.02 GH
   }
   else setDbOK();        //opened in read write mode

   db->openSw='o';
   db->dm=dbref;
   db->LastDbRecordRead=-1;
   db->curHand=0;
   db->offset=0;
   db->cardno=*((double*)arg4_val);
   //setDbOK();            //02.20.02 GH
}



/********************************************************************************************/
void verb_dbcreate()
{
  struct dbType *db;
  VoidHand recHand;
  VoidPtr  recPtr;
  int res;
  DmOpenRef *dbr;
  UInt cardno;
  ULong creator;
  ULong types;
  int err;
  LocalID lid;
  UInt attrib;

   dbfind_arg(4); //1=res,2=db,3=name,4=cardno,5=creator
   find_arg_5();
   cardno=*((double*)arg4_val);
   err=DmCreateDatabase(cardno,arg3_val,*((ULong *)arg5_val),
          (ULong)'data',false);
//StrPrintF(debug,"cardno=%d err=%d",cardno,err);
//SysFatalAlert(debug);
	if (err==0) {
   		lid=DmFindDatabase( cardno, arg3_val);
   		DmDatabaseInfo( cardno, lid, nil,&attrib,nil,nil,nil,nil,
                                nil,nil,nil,nil,nil);
   		attrib=attrib | dmHdrAttrBackup;    //set to hotsync 
   		DmSetDatabaseInfo( cardno, lid, nil,&attrib,nil,nil,nil,nil,
                                nil,nil,nil,nil,nil); 
   }   
                            
   setDbRes(err);
}

/********************************************************************************************/
void verb_dberase()
{
  struct dbType *db;
  VoidHand recHand;
  VoidPtr  recPtr;
  int res;
  DmOpenRef dbr;
  int err;
  dbfind_arg(2);
  db=getDatabasePtr();
  

  err=DmDeleteDatabase( db->cardno,db->lid);
  if(err!=0) setDbErr(err);
  else      setDbOK();;
   

}
/********************************************************************************************/
void verb_dbreset() //reset back to the 1st rec on next read
{
  struct dbType *db;
  VoidHand recHand;
  VoidPtr  recPtr;
  DmOpenRef dbr;
  int err;
  int res;
  
  dbfind_arg(2);   //result and dbref
  db=getDatabasePtr();
  dbr=db->dm;
  chkDbOpen(db);
  db->LastDbRecordRead=-1;
  setDbOK();
  

}  
/********************************************************************************************/
void verb_dbreadnext()
{
  struct dbType *db;
  VoidHand recHand;
  VoidPtr  recPtr;
  DmOpenRef dbr;
  int err;
  int res;
  dbfind_arg(3);

  db=getDatabasePtr();

  dbr=db->dm;
  chkDbOpen(db);

  res=db->LastDbRecordRead+1;
//StrPrintF(debug,"readnxt=%d dbcnt=%d ",res,DmNumRecords(dbr));
//SysFatalAlert(debug);
  if (res>=DmNumRecords(dbr))
  {
//dbug("skip params");
     //skip parameters
     while(1)
     {
       find_arg_5();
       if(arg5==null_ptr) break;
     }
     res=1;
     goto getOut3;
  }
//StrPrintF(debug,"finding rec %d",res);
//SysFatalAlert(debug);  
  recHand=DmGetRecord(dbr,res);
  
//StrPrintF(debug,"reading rec flds %d");
  readDbFields(db,recHand,&arg3,arg3_occ1,arg3_occ2,arg3_occ3);

  
  DmReleaseRecord(dbr,res,false);
//dbug("record released");
  res=0;
  db->LastDbRecordRead+=1;   //this stmt need to be moved
getOut3:
  setDbRes(res);
}
/********************************************************************************************/
void verb_dbreadprev()
{
  struct dbType *db;
  VoidHand recHand;
  VoidPtr  recPtr;
  DmOpenRef dbr;
  int err;
  int res;
  dbfind_arg(3);
  db=getDatabasePtr();
  dbr=db->dm;
  chkDbOpen(db);
  
//StrPrintF(debug,"readnxt=%d dbcnt=%d lastrec=%u",res,DmNumRecords(dbr),db->LastDbRecordRead);
//SysFatalAlert(debug);
  if ((db->LastDbRecordRead==0)||(db->LastDbRecordRead==65535))  //65535 equiv to -1 in unsigned fld
  {
//dbug("skip params");
     //skip parameters
     while(1)
     {
       find_arg_5();
       if(arg5==null_ptr) break;
     }
     res=1;
     setDbRes(res);
     return;
  }
//dbug("found rec");  
  res=db->LastDbRecordRead-1;  //position to prev rec
  recHand=DmGetRecord(dbr,res);
  
//dbug("reading rec flds");
  readDbFields(db,recHand,&arg3,arg3_occ1,arg3_occ2,arg3_occ3);

  //db->LastDbRecordRead=res;
  DmReleaseRecord(dbr,res,false);
//dbug("record released");
  res=0;
getOut3:
  setDbRes(res);

  db->LastDbRecordRead-=1;
}
/********************************************************************************************/
void verb_dbinsert()
{
  struct dbType *db;
  SortRecordInfoType srtinfo;
  VoidHand recHand;
  VoidPtr  recPtr;
  UInt res;
  DmOpenRef dbr;
  int err;
  int kindInt;
  int result;   //inserted 05282003

  dbfind_arg(3);  //1=result, 2=dbno,3=key

  db=getDatabasePtr();
  dbr=db->dm;

  chkDbOpen(db);  
//StrPrintF(debug,"d key=%s",arg3_val);
//SysFatalAlert(debug);
  kindInt=0;
  *((char*)(&kindInt))=arg3->kind;
  *((char*)(&kindInt)+1)=arg3->flags;
//StrPrintF(debug,"in dbinsert--  kind=%c flags=%d kindint= %d",arg3->kind,arg3->flags,kindInt);
//SysFatalAlert(debug); 
  res=DmFindSortPosition(dbr,arg3_val,&srtinfo,database_compare,kindInt);
//StrPrintF(debug,"e  res=%d len=%d key=%s",res,StrLen(arg3_val),arg3_val);
//SysFatalAlert(debug);
  //see if rec  already there and err if so
  res-=1;
  if (res>=DmNumRecords(dbr) )
  {
     goto OKtoAdd;
  }
  
  recHand=DmGetRecord(dbr,res);
  recPtr=MemHandleLock(recHand);
  
  if (keyCompare(arg3_val,recPtr,kindInt)==0) 
  {
     MemHandleUnlock(recHand);
     DmReleaseRecord(dbr,res,false);
getOut7:                           //inserted 05282003
     setDbRes(1);  //rec already on file(or mem error)  //05282003
     while(1)     /*skip rest of args */
     {
        find_arg_5();
        if (arg5==null_ptr) break;
     }
     
     return;
  } 
  MemHandleUnlock(recHand);
  DmReleaseRecord(dbr,res,false);
OKtoAdd:
  res+=1;
  
  recHand=DmNewRecord(dbr,&res,1); //1/9/2000 //just get 1 bytes & it will resize later
  if(recHand==0)                   //inserted 05282003
  {                                //inserted 05282003
          goto getOut7;//out-of-mem//inserted 05282003
  }                                //inserted 05282003
//StrPrintF(debug,"in dbinsert size=%lu",MemHandleSize(recHand));
//SysFatalAlert(debug);
  
     result=writeDbFields(db,&recHand,arg3_val,(int)kindInt,'a',res);   //mod 05282003
     if(result==1)                      //inserted 05282003
     {                                  //inserted 05282003
          DmReleaseRecord(dbr,res,false); //inserted 05282003
          DmRemoveRecord (dbr,res);     //inserted 05282003 delete the newly created record
          goto getOut7;   //outOfMem     //inserted 05282003  note:may need to skip args again
     }                                   //inserted 05282003
     db->LastDbRecordRead=res;


     setDbRes(0);
   
   
   setDbOK();
   DmReleaseRecord(dbr,res,true);

}
/********************************************************************************************/
void verb_dbdelete()
{
  struct dbType *db;
  SortRecordInfoType srtinfo;
  VoidHand recHand;
  VoidPtr  recPtr;
  int res;
  UInt rec;
  int kindInt;
  DmOpenRef dbr;
  int err;
  dbfind_arg(3);  //1=result, 2=dbno,3=key
  db=getDatabasePtr();
  dbr=db->dm;
  chkDbOpen(db);
  if(DmNumRecords(dbr) ==0)
  {
     res=1;
     goto getOut5;
  }
//StrPrintF(debug,"#recs=%d",DmNumRecords(dbr));
//SysFatalAlert(debug);  
  kindInt=0;
  *((char*)(&kindInt))=arg3->kind;
  *((char*)(&kindInt)+1)=arg3->flags;
  rec=DmFindSortPosition(dbr,arg3_val,&srtinfo,database_compare,kindInt);
  
  if (rec>DmNumRecords(dbr) )
  {
//StrPrintF(debug,"too high =%s",arg3_val);
//SysFatalAlert(debug);
    res=1;
    goto getOut5;
  }
  rec-=1;
  if(rec==(-1)) 
  {
     res=1;
     goto getOut5;
  }
//StrPrintF(debug,"get rec#=%d  key=%s",rec,arg3_val);
//SysFatalAlert(debug);
  recHand=DmGetRecord(dbr,rec);
  if(recHand==0)
  {
//dbug("not found");
     res=1;
     goto getOut5;
  }
  recPtr=MemHandleLock(recHand);
  if (keyCompare(arg3_val,recPtr,kindInt)==0)
  {
     MemHandleUnlock(recHand);
     DmReleaseRecord(dbr,rec,true);
     DmRemoveRecord(dbr,rec);
     db->LastDbRecordRead=rec-1;
     res=0;
  }
  else
  {
//StrPrintF(debug,"no match =%s   compare-to=%s",arg3_val,recPtr);
//SysFatalAlert(debug);
     MemHandleUnlock(recHand);
     DmReleaseRecord(dbr,rec,false);
     res=1;
  }  
getOut5:
  setDbRes(res);
  
}
/********************************************************************************************/
void verb_dbupdate()
{
  struct dbType *db;
  SortRecordInfoType srtinfo;
  int kindInt;
  VoidHand recHand;
  VoidPtr  recPtr;
  UInt res;
  DmOpenRef dbr;
  int err;
  int result;                    //05282003
//dbug("in updt rtn");
  dbfind_arg(3);  //1=result, 2=dbno,3=key
  db=getDatabasePtr();
  dbr=db->dm;
  chkDbOpen(db);
  kindInt=0;
  *((char*)(&kindInt))=arg3->kind;
  *((char*)(&kindInt)+1)=arg3->flags;
  res=DmFindSortPosition(dbr,arg3_val,&srtinfo,database_compare,kindInt);
//StrPrintF(debug,"getting rec1=%d key=%s  numRecs=%d",res,arg3_val,DmNumRecords(dbr));
//SysFatalAlert(debug);  
 
  
  //deleted 05082003 if ( res>=DmNumRecords(dbr) )    //modified 04242003
  //deleted 05192003 if((res==0) && DmNumRecords(dbr)==0)              //added 05082003
   if(res==0)                             //05192003 added (key lower than any record on file)
   {

    res=1;
    while(1)    //skip rest of args 
     {
        find_arg_5();
        if (arg5==null_ptr) break;
     }
    goto getOut2;
  }
  
 
  res-=1;
//StrPrintF(debug,"getting rec2=%d key=%s",res,arg3_val);
//SysFatalAlert(debug);
  recHand=DmGetRecord(dbr,res);
  recPtr=MemHandleLock(recHand);
  
  if (keyCompare(arg3_val,recPtr,kindInt)==0)
  {
//dbug("matched");
     MemHandleUnlock(recHand);
//dbug("going to write");
     result=writeDbFields(db,&recHand,arg3_val,kindInt,'u',res);  //mod 05282003
     if(result==1) goto getOut8;  //out of mem      05282003
     
//dbug("back from write");
     db->LastDbRecordRead=res;
     
     DmReleaseRecord(dbr,res,true);
     res=0;
   
  }
  else
  {
getOut8:                       //inserted 05282003                     

//dbug("unmatched");
    MemHandleUnlock(recHand);
    DmReleaseRecord(dbr,res,false);

    res=1;
    while(1)     /*skip rest of args */
     {
        find_arg_5();
        if (arg5==null_ptr) break;
     }
  }
getOut2:
  setDbRes(res);

}

/********************************************************************************************/
void verb_dbread()
{
  struct dbType *db;
  SortRecordInfoType srtinfo;
  int kindInt;
  VoidHand recHand;
  VoidPtr  recPtr;
  UInt tempRes;
  UInt res;
  DmOpenRef dbr;
  int err;
  unsigned int instr_ctr_save;

  dbfind_arg(3);  //1=result, 2=dbno,3=key
  db=getDatabasePtr();
  dbr=db->dm;
  chkDbOpen(db);
  kindInt=0;
  *((char*)(&kindInt))=arg3->kind;
  *((char*)(&kindInt)+1)=arg3->flags;
  res=DmFindSortPosition(dbr,arg3_val,&srtinfo,database_compare,kindInt);
//StrPrintF(debug,"res=%d",res);
//SysFatalAlert(debug);
  
  if (res>DmNumRecords(dbr) )
  {
    //skip parameters
     res=1;
skipParams:
     while(1)
     {
       find_arg_5();
       if(arg5==null_ptr) break;
     }
   
    goto getOut2;
  }
  if(res==0)
  {
     goto readNextHigher;
  }
  res-=1;
  tempRes=res;
  recHand=DmGetRecord(dbr,res);
  recPtr=MemHandleLock(recHand); 
  
  if (keyCompare(arg3_val,recPtr,kindInt)==0)
  {
     MemHandleUnlock(recHand);
     
     readDbFields(db,recHand,&arg3,arg3_occ1,arg3_occ2,arg3_occ3);
     db->LastDbRecordRead=res;
     res=0;
  }
  else
  {
      MemHandleUnlock(recHand);
      DmReleaseRecord(dbr,tempRes,false);
      res+=1;
readNextHigher:
      if(res==DmNumRecords(dbr)) 
      {
          res=1;
          goto skipParams;
      }
      
      tempRes=res;
      recHand=DmGetRecord(dbr,res);
      
      readDbFields(db,recHand,&arg3,arg3_occ1,arg3_occ2,arg3_occ3);
      db->LastDbRecordRead=res;
      res=2;    //2 says returning next higher record
      
  }    
      
 
  
  DmReleaseRecord(dbr,tempRes,false);
getOut2:
  setDbRes(res);
  
}

/********************************************************************************************/
void verb_dbfind()
{
  struct dbType *db;
  SortRecordInfoType srtinfo;
  int kindInt;
  VoidHand recHand;
  VoidPtr  recPtr;
  
  unsigned int rec;
  UInt res;
  DmOpenRef dbr;
  int err;

  dbfind_arg(3);  //1=result, 2=dbno,3=key
  db=getDatabasePtr();
  dbr=db->dm;
  chkDbOpen(db);
  kindInt=0;
  *((char*)(&kindInt))=arg3->kind;
  *((char*)(&kindInt)+1)=arg3->flags;
  rec=DmFindSortPosition(dbr,arg3_val,&srtinfo,database_compare,kindInt);
//StrPrintF(debug,"find key=%s posit=%d",arg3_val,rec);
//SysFatalAlert(debug);
  
  if ((rec==0)||(rec>DmNumRecords(dbr))||(DmNumRecords(dbr)==0) )
  {
    res=1;
    goto getOut;
  }
  rec-=1;
  recHand=DmGetRecord(dbr,rec);
  recPtr=MemHandleLock(recHand);
  
  if(keyCompare(arg3_val,recPtr,kindInt)==0) res=0;
  else  res=1;
  
  MemHandleUnlock(recHand);
  DmReleaseRecord(dbr,rec,false);
getOut:
  setDbRes(res);
   
}
/********************************************************************************************/

void dbfind_arg(int n)
{
    find_arg_1();
    dbNo=find_integer()-1;
    if(n>2) find_arg_3();
    if(n>3) find_arg_4();
    if(n>4) find_arg_5();
    if(n>5) find_arg_6();
   
}

/********************************************************************************************/
void verb_dbcreatedatabasefromresource()	//03.24.02 GH
{
	Err res;
	Int resID;
	VoidHand imageHandle;
   
	resID= long_integ_value(arg2,(double*)arg2_val);
	imageHandle = DmGetResource(*(DmResType *) arg1_val, (DmResID) resID);
	if(imageHandle==0) {setSerErr(DmGetLastErr());return;}
   
	res = DmCreateDatabaseFromImage(MemHandleLock(imageHandle));
	MemHandleUnlock(imageHandle);
	DmReleaseResource(imageHandle);

  	setSerErr(res);
}

/********************************************************************************************/
void readOneDbField(struct dbType * db,VoidPtr recPtr,UInt *theOffset)
{
    UInt offset=*theOffset;
    char b[2];
  unsigned long theLen;
  int theShort;
  long theInteger;
  float theSingle;
  double theData;   
  char wk[50];
  
  if (arg5->kind== 's')
    {

      if(arg5->flags&0x80)
      {
        b[0] =*((char*)recPtr+offset);
        b[1] =0x00;
         misc_stostr5(b);
         offset+=1;
      }
      else
     {     
       misc_stostr5((char*)recPtr+offset);
       offset+=StrLen((char*)(recPtr)+offset)+1;
     }
    }
    else
    {
     if(arg5->flags&0x80)   //integer
     {
       theLen=4; 
       dbGetSome((char*)(recPtr)+offset,theLen,&theInteger);
       theData=theInteger;
//StrPrintF(debug,"read integer =%lu going to readit",theInteger);
//SysFatalAlert(debug);
       goto readIt;
     }
     if(arg5->flags&0x40)  //float/double
     {
       theLen=8; 
       dbGetSome((char*)(recPtr)+offset,theLen,&theData);
 //theInteger=theData*100;
 //StrPrintF(debug,"temp=%lu",theInteger);
 //SysFatalAlert(debug);
       goto readIt;
     } 
     if(arg5->flags&0x20)   //single float
     {
       theLen=4; 
        dbGetSome((char*)(recPtr)+offset,theLen,&theSingle);
       theData=theSingle;
       goto readIt;
     }
     if(arg5->flags&0x10)   //2-byte integer
     {
       theLen=2;
        dbGetSome((char*)(recPtr)+offset,theLen,&theShort);
       theData=theShort;
        goto readIt;
     }
readIt:  
      
       misc_stodbl5(&theData);
       offset+=theLen;
    }
  *theOffset=offset;
      
}
/********************************************************************************************/
void readOneDbArgument(struct dbType * db,VoidPtr recPtr,UInt *theOffset)
{
   int ii,jj,kk;
    
    
    //writes out one passed argument which might be an array name which means write out several values
    if( (arg5->max_no_values3 > 1) && (arg5_sde3==0)) 
    {
       if( (arg5->max_no_values2 > 1) && (arg5_sde2==0))
       {
         if( (arg5->max_no_values1 > 1) && (arg5_sde1==0))
         { 
            for(ii=0;ii<arg5->max_no_values1;++ii)
            {
               for(jj=0;jj<arg5->max_no_values2;++jj)
               {
                 for(kk=0;kk<arg5->max_no_values3;++kk)
                 {
                     arg5_occ1=ii;
                     arg5_occ2=jj;
                     arg5_occ3=kk;
                     readOneDbField( db,recPtr,theOffset);
                     
                 }
               }
             }
             
         }
         else
         {
                for(jj=0;jj<arg5->max_no_values2;++jj)
                {
                  for(kk=0;kk<arg5->max_no_values3;++kk)
                  {
                     
                     arg5_occ2=jj;
                     arg5_occ3=kk;
                     readOneDbField( db,recPtr,theOffset);
                  }
                }
         }
                                         
       }
       else
       {
               for(kk=0;kk<arg5->max_no_values1;++kk)
                {
                  
                     
                     arg5_occ3=kk;
                     readOneDbField( db,recPtr,theOffset);
                }
       }
    }
    else
    {
       
       if( (arg5->max_no_values2 > 1) && (arg5_sde2==0))
       {
         if( (arg5->max_no_values1 > 1) && (arg5_sde1==0))
         { 
            for(ii=0;ii<arg5->max_no_values1;++ii)
            {
               for(jj=0;jj<arg5->max_no_values2;++jj)
               {
                     arg5_occ1=ii;
                     arg5_occ2=jj;
                     
                     readOneDbField( db,recPtr,theOffset);
               }
             }
             
         }
         else
         {
                for(jj=0;jj<arg5->max_no_values2;++jj)
                {
                     arg5_occ2=jj;
                     
                     readOneDbField( db,recPtr,theOffset);
                 }
         }
                                         
       } 
       else
       {
          if( (arg5->max_no_values1 > 1) && (arg5_sde1==0))
         { 
            for(ii=0;ii<arg5->max_no_values1;++ii)
            {
                     arg5_occ1=ii;
                     readOneDbField( db,recPtr,theOffset);
            }
             
         }
         else
         {
                 //arg5_val OK because all levels of subscripting there
                  readOneDbField( db,recPtr,theOffset);
          }
        }
    }      
}

/********************************************************************************************/
void readDbFields(struct dbType * db,VoidHand recHand,
                  struct dataelem* *keyarg,unsigned int keysub1,
                  unsigned int keysub2,unsigned int keysub3)
{
  char b[2];
  unsigned long theLen;
  int theShort;
  long theInteger;
  float theSingle;
  double theData;   
  UInt offset;
  VoidPtr recPtr;
  char wk[50];
  

  recPtr=MemHandleLock(recHand);

  if((*keyarg)->kind=='s')
  {
     if( (*keyarg)->flags&0x80) 
     {
          theLen=1;
          b[0] =*((char*)recPtr);
          b[1] =0x00;
          misc_stostr(keyarg,keysub1,keysub2,keysub3,b);
     }
     else 
     {
       misc_stostr(keyarg,keysub1,keysub2,keysub3,(char*)recPtr);
       theLen=StrLen((char*)recPtr)+1;
     } 
  }
  else
  {
     
         if( (*keyarg)->flags& 0x80) //long
         {  theLen=4; 
           dbGetSome((char*)(recPtr),theLen,&theInteger);
           theData=theInteger;
           goto keySet;
         }
         if((*keyarg)->flags& 0x40)  //double
         {
           theLen=8; 
           dbGetSome((char*)(recPtr),theLen,&theData);
           goto keySet;
         }
         if((*keyarg)->flags& 0x20)  //single float
         {
           theLen=4; 
           dbGetSome((char*)(recPtr),theLen,&theSingle);
           theData=theSingle;
           goto keySet;
         }
         if((*keyarg)->flags& 0x10)  //int      
         {
           theLen=2;
           dbGetSome((char*)(recPtr),theLen,&theShort);
           theData=theShort;
           goto keySet;
         }
keySet: 
          
          
     
storeKeyNum:
      misc_stodbl( *keyarg, keysub1,keysub2,keysub3,&theData);
   }
   offset=theLen;

   while(1)
   {
      find_arg_5();

      if (arg5==null_ptr) break;
      readOneDbArgument(db,recPtr,&offset);
   }
   MemHandleUnlock(recHand);
}

/********************************************************************************************/
int write_one_dbField(struct dbType *db,
                    VoidHand * recHand,
                     UInt index ,ULong *theOffset)
{
  ULong offset=*theOffset;
  double temp;
  int err;
  
  VoidPtr ptr;
  unsigned int theLen;
  int theShort;
  long theInteger;
  float theSingle;
  void *theData;
  int klm;
  double z;
  double wkdbl;
  
  char nullbyte=0x00;

           if (arg5->kind == 's')
          {
            if(arg5->flags&0x80)
            {
               //07312002*recHand=DmResizeRecord(db->dm,index,
               //07312002        (ULong)(MemHandleSize(*recHand)+1));
               if(MemHandleSize(*recHand)<(offset+1))   //08142002
               {
                 *recHand=DmResizeRecord(db->dm,index,
                       (ULong)(offset+1));
                 if(*recHand==0) return(1);     //inserted 05282003      
               }
               ptr=MemHandleLock(*recHand); 
               
               DmWrite(ptr,offset,((char*)(arg5_val)),1);
              
               offset+=1;
            }
            else
            {
               //07312002*recHand=DmResizeRecord(db->dm,index,
               //07312002        (ULong)(MemHandleSize(*recHand)+StrLen(arg5_val)+1));
               if(MemHandleSize(*recHand)<(offset+StrLen(arg5_val)+1))   //08142002
               {
                   *recHand=DmResizeRecord(db->dm,index,
                       (ULong)(offset+StrLen(arg5_val)+1));
                   if(*recHand==0) return(1);     //inserted 05282003    
               }
               ptr=MemHandleLock(*recHand);
//StrPrintF(debug,"new lenmgth=%d",MemPtrSize(ptr));
//SysFatalAlert(debug);
      
//StrPrintF(debug,"copying string reclen=%d len=%d  rec=%s len=%d x=%x %x",MemHandleSize(*recHand)-StrLen(arg5_val)-1,StrLen(arg5_val),ptr,StrLen(ptr),*((char*)ptr+1),*((char*)ptr+2));
//SysFatalAlert(debug);

               err=DmStrCopy(ptr,offset,arg5_val);
//StrPrintF(debug,"err after StrCopy=%d",err);
//SysFatalAlert(debug);
               
               //06102002offset+=StrLen(arg5_val)+1;
               //07312002offset+=StrLen(arg5_val);             //06102002  to elim double nulls following string
               offset+=StrLen(arg5_val)+1;         //07312002            
            }
          }
          else
          {
          
            if(arg5->flags&0x80)   //integer
            { 

               theLen=4; 
               wkdbl=*((double*)arg5_val);  
             /*03092002
               if(arg5->kind=='i')          //02022002 added
               {                         //02022002 added
                 if(wkdbl<0)    z=wkdbl-0.5;      //02022002 added
                 else           z=wkdbl+0.5;      //02022002 added
                 wkdbl=misc_int(z);      //02022002 added
               }                         //02022002 added
               else              ;    //02022002 added
             */
               theInteger=wkdbl;
               theData=&theInteger;
//StrPrintF(debug,"write integer =%lu",theInteger);
//SysFatalAlert(debug);
               goto writeIt;
            }
            if(arg5->flags&0x40)  //float/double
            {
               theLen=8; 
               theData=(double*)arg5_val;
 
               goto writeIt;
            } 
            if(arg5->flags&0x20)   //single float
            {
               theLen=4; 
       
               theSingle=*((double*)arg5_val);
               theData=&theSingle;
               goto writeIt;
            }
            if(arg5->flags&0x10)   //2-byte integer
            {
              theLen=2;
              wkdbl=*((double*)arg5_val);  
               /*03092002
               if(arg5->kind=='i')          //02022002 added
               {                         //02022002 added
                 if(wkdbl<0)    z=wkdbl-0.5;      //02022002 added
                 else           z=wkdbl+0.5;      //02022002 added
                 wkdbl=misc_int(z);      //02022002 added
               }                         //02022002 added
               else              ;    //02022002 added
              */
               theShort=wkdbl;
               
              theData=&theShort;
              goto writeIt;
            }
writeIt:
            //07312002*recHand=DmResizeRecord(db->dm,index,
           //07312002                       (ULong)(MemHandleSize(*recHand)+theLen));
            if(MemHandleSize(*recHand)<(offset+theLen))   //08142002
            {
                *recHand=DmResizeRecord(db->dm,index,
                                  (ULong)(offset+theLen));
                if(*recHand==0) return(1);     //inserted 05282003                   
            }
            ptr=MemHandleLock(*recHand);
//StrPrintF(debug,"resizing rec in writedb to len=%lu",MemPtrSize(ptr));
//SysFatalAlert(debug);
            DmWrite(ptr,offset,theData,theLen);
            
            offset+=theLen;
          }
  //06102002 DmWrite(ptr,offset,&nullbyte,1);     commented out to elim the ending null ptr    
  MemHandleUnlock(*recHand);        
  *theOffset=offset;
  return 0;                      //inserted 05282003          
}
/********************************************************************************************/
int writeOutOneDbArgument(struct dbType *db,
                    VoidHand * recHand,
                     UInt index ,ULong *theOffset)
{
    int ii,jj,kk;
    int res;               //inserted 05282003
    
    //writes out one passed argument which might be an array name which means write out several values
    if( (arg5->max_no_values3 > 1) && (arg5_sde3==0)) 
    {
       if( (arg5->max_no_values2 > 1) && (arg5_sde2==0))
       {
         if( (arg5->max_no_values1 > 1) && (arg5_sde1==0))
         { 
            for(ii=0;ii<arg5->max_no_values1;++ii)
            {
               for(jj=0;jj<arg5->max_no_values2;++jj)
               {
                 for(kk=0;kk<arg5->max_no_values3;++kk)
                 {
                     arg5_val = devel_address(arg5, ii,jj,kk);
                     res=write_one_dbField(db, recHand,  index ,theOffset) ;   //modified 05282003
                     if(res!=0) return(1);      //outOfMemory   inserted 05282003
                 }
               }
             }
             
         }
         else
         {
                for(jj=0;jj<arg5->max_no_values2;++jj)
                {
                  for(kk=0;kk<arg5->max_no_values3;++kk)
                  {
                     arg5_val = devel_address(arg5,arg5_occ1 ,jj,kk);
                     res=write_one_dbField(db, recHand, index ,theOffset) ;   //modified 05282003
                     if(res!=0) return(1);      //outOfMemory   inserted 05282003
                  }
                }
         }
                                         
       }
       else
       {
               for(kk=0;kk<arg5->max_no_values1;++kk)
                {
                  
                     arg5_val = devel_address(arg5,arg5_occ1 ,arg5_occ2,kk);
                     res=write_one_dbField(db, recHand,  index ,theOffset) ;   //mod 05282003
                     if(res!=0) return(1);      //outOfMemory   inserted 05282003
                }
       }
    }
    else
    {
       
       if( (arg5->max_no_values2 > 1) && (arg5_sde2==0))
       {
         if( (arg5->max_no_values1 > 1) && (arg5_sde1==0))
         { 
            for(ii=0;ii<arg5->max_no_values1;++ii)
            {
               for(jj=0;jj<arg5->max_no_values2;++jj)
               {
                     arg5_val = devel_address(arg5, ii,jj,arg5_occ3);
                     res=write_one_dbField(db, recHand,  index ,theOffset) ;  //mod 05282003
                     if(res!=0) return(1);      //outOfMemory   inserted 05282003
               }
             }
             
         }
         else
         {
                for(jj=0;jj<arg5->max_no_values2;++jj)
                {
                    arg5_val = devel_address(arg5,arg5_occ1 ,jj,arg5_occ3);
                    res= write_one_dbField(db, recHand,   index ,theOffset) ;  //mod 05282003
                    if(res!=0) return(1);      //outOfMemory   inserted 05282003
                 }
         }
                                         
       } 
       else
       {
          if( (arg5->max_no_values1 > 1) && (arg5_sde1==0))
         { 
            for(ii=0;ii<arg5->max_no_values1;++ii)
            {
                     arg5_val = devel_address(arg5, ii,arg5_occ2,arg5_occ3);
                     res=write_one_dbField(db, recHand,  index ,theOffset) ;  //mod 05282003
                     if(res!=0) return(1);      //outOfMemory   inserted 05282003
            }
             
         }
         else
         {
                 //arg5_val OK because all levels of subscripting there
                  res=write_one_dbField(db, recHand, index ,theOffset) ;  //mod 05282003
                  if(res!=0) return(1);      //outOfMemory   inserted 05282003
          }
        }
    }
    return 0;      
}

/********************************************************************************************/
int writeDbFields(struct dbType *db,                                   //mod 05282003
                    VoidHand * recHand,char*key,int other,char addUpdt,
                     UInt index )
{
  double temp;
  ULong offset;
  VoidPtr ptr;
  unsigned int theLen;
  int theShort;
  long theInteger;
  float theSingle;
  void *theData;
  ULong keylen;
  struct 
  {
     char kind;
     char flags;
  } theKind;
  char wk[50]; 
  int ii,jj,kk;
  double wkdbl;
  double z;
  char nullbyte=0x00;
  int res;                   //05282003
   
  *((int*)&theKind)=other;
//StrPrintF(debug,"in writewflds kind=%c flags=%d",theKind.kind,theKind.flags);
//SysFatalAlert(debug);
  if( theKind.kind=='s')
  {
        if( theKind.flags&0x80) keylen=1;
        else keylen= StrLen((char*)key)+1;
  }
  else
  {
        
           if( theKind.flags& 0x80) keylen=4;
           else
           {
             if(theKind.flags& 0x40) keylen=8;
             else
             {
               if(theKind.flags& 0x20) keylen=4;
               else
               {
                 if(theKind.flags& 0x10) keylen=2;
               }
             }
           }
  }  
//StrPrintF(debug,"in writedbfields -----THE KEYLEN=%lu",keylen);
//SysFatalAlert(debug);
 
     
      *recHand=DmResizeRecord(db->dm,index,keylen+1);    //leave 1 extra null byte  //1/9/2001
      if(*recHand==0)   return(1);      //outOfMem       //inserted 05282003
//StrPrintF(debug,"in write dbflds --key=%s len=%d rec#=%d",key,StrLen(key),index);  
//SysFatalAlert(debug);
//StrPrintF(debug,"in writefields entry size=%lu",MemHandleSize(*recHand));
//SysFatalAlert(debug);

//StrPrintF(debug,"in writefields after key resize size=%lu",MemHandleSize(*recHand));
//SysFatalAlert(debug);

 ptr=MemHandleLock(*recHand); 
 DmWrite(ptr,keylen,&nullbyte,1);          //make last byte null  1/9/2001
 if (theKind.kind == 's')
 {

      if(theKind.flags&0x80)
      {
         DmWrite(ptr,0,((char*)(key)),1);
      }
      else
      {
         DmStrCopy(ptr,0,(char*)key);
      }
 }
 else
 {
          
     if(theKind.flags&0x80)   //integer
     {

       theLen=4; 
       wkdbl=*((double*)key);  
             /*03092002
               if(arg5->kind=='i')          //02022002 added
               {                         //02022002 added
                 if(wkdbl<0)    z=wkdbl-0.5;      //02022002 added
                 else           z=wkdbl+0.5;      //02022002 added
                 wkdbl=misc_int(z);      //02022002 added
               }                         //02022002 added
               else              ;    //02022002 added
             */
               theInteger=wkdbl;
       
       theData=&theInteger;
//StrPrintF(debug,"write integer =%lu",theInteger);
//SysFatalAlert(debug);
       goto writeKey;
     }
     if(theKind.flags&0x40)  //float/double
     {
       theLen=8; 
       theData=(double*)key;
 
       goto writeKey;
     } 
     if(theKind.flags&0x20)   //single float
     {
       theLen=4; 
       
       theSingle=*((double*)key);
       theData=&theSingle;
       goto writeKey;
     }
     if(theKind.flags&0x10)   //2-byte integer
     {
       theLen=2;
       wkdbl=*((double*)key);  
              /*03092002
               if(arg5->kind=='i')          //02022002 added
               {                         //02022002 added
                 if(wkdbl<0)    z=wkdbl-0.5;      //02022002 added
                 else           z=wkdbl+0.5;      //02022002 added
                 wkdbl=misc_int(z);      //02022002 added
               }                         //02022002 added
               else              ;    //02022002 added
              */
               theShort=wkdbl;
               
       theData=&theShort;
//StrPrintF(debug,"writing key of int type=%d",theShort);
//SysFatalAlert(debug);
        goto writeKey;
     }
writeKey:
      
       DmWrite(ptr,0,theData,theLen);
  }    


  MemHandleUnlock(*recHand);
  offset=keylen;
  while(1)
  {
    find_arg_5();
    if (arg5==null_ptr) break;
//StrPrintF(debug,"ready to copy offset=%d kind=%c",offset,arg5->kind);
//SysFatalAlert(debug);
   
     res=writeOutOneDbArgument(db, recHand,  index ,&offset);   //mod 05282003
     if(res==1) return(1);    //outOfMem  05282003
  }
  return(0);                             //05282003
}
/********************************************************************************************/
void verb_dbgetnew()   //this is the new dbget which gets multiple fields
{
  struct dbType *db;
  VoidHand recHand;
  VoidPtr  recPtr;
  int res;
  DmOpenRef dbr;
  char b[2];
  unsigned long theLen;
  double theData;
  float theSingle;
  
  unsigned int theShort;       //added 5.20.2000  
  
  unsigned long theInteger;    //added 5.20.2000
  int err;
  err=0;
  
  dbfind_arg(2);  //1=errcode,2=db,5=singlevar
  
  db=getDatabasePtr();
  dbr=db->dm;
  chkDbOpen(db);
//dbug("aaa");
  if(db->curHand==0)
  {
        setDbErr(err);
        while(1)
        {
            find_arg_5();
            if (arg5==null_ptr) break;   //skip all remaining flds
        }
        goto getOut3;
  }
  db->curHand=DmGetRecord(dbr,db->LastDbRecordRead);
  recPtr=MemHandleLock(db->curHand);

  
  while(1)
  {
    
     find_arg_5();
     if(arg5==null_ptr) break;
     if(db->offset>=(MemPtrSize(recPtr)))
     {
        setDbErr(err);
        while(1)
        {
            find_arg_5();
            if (arg5==null_ptr) break;   //skip all remaining flds
        }
        goto getOut2;
     }

   
   readOneDbArgument        ( db,recPtr,&(db->offset));
  }   
  setDbOK();
getOut2:
  MemHandleUnlock(db->curHand);
  DmReleaseRecord(dbr,db->LastDbRecordRead,false);

getOut3:
   ;
}
/********************************************************************************************/
void verb_dbget()  //this is the old dbget which got only one field
{
  struct dbType *db;
  VoidHand recHand;
  VoidPtr  recPtr;
  int res;
  DmOpenRef dbr;
  char b[2];
  unsigned long theLen;
  double theData;
  float theSingle;
  
  unsigned int theShort;       //added 5.20.2000  
  
  unsigned long theInteger;    //added 5.20.2000
  int err;
  err=0;
  
  dbfind_arg(2);  //1=errcode,2=db,5=singlevar
  find_arg_5();
  db=getDatabasePtr();
  dbr=db->dm;
  chkDbOpen(db);

  if(db->curHand==0)
  {
       setDbErr(err);
       goto getOut3;
  }
  db->curHand=DmGetRecord(dbr,db->LastDbRecordRead);
  recPtr=MemHandleLock(db->curHand);

  
     if(db->offset>=(MemPtrSize(recPtr)))
     {
        setDbErr(err);
        goto getOut2;
     }

   readOneDbField( db,recPtr,&(db->offset));  
     
  setDbOK();
getOut2:
  MemHandleUnlock(db->curHand);
  DmReleaseRecord(dbr,db->LastDbRecordRead,false);

getOut3:
    ;
}
/********************************************************************************************/
void verb_dbputnew()    //this is the new dbput which puts out multiple fields 
{
   UInt index;
   struct dbType *db;
   VoidHand recHand;
  VoidPtr  recPtr;
  unsigned long theLen;
  int theShort;
  
  ULong offset;
  long theInteger;
  float theSingle;
  void *theData;   
  int res;
  DmOpenRef dbr;
 
  int err;
  err=1;
  
  
  dbfind_arg(2);   //1=errcode,2=db,5=singlevar
 
  db=getDatabasePtr();
  dbr=db->dm;
  chkDbOpen(db);
  //if(db->curHand==0)      //deleted 04242003
  if((db->curHand==0) || (db->LastDbRecordRead<0) || (db->LastDbRecordRead>=(DmNumRecords(dbr)))) //inserterd 04242003
  {
       setDbErr(err);
       while(1)
       {
          find_arg_5();
          if(arg5==null_ptr) break;  //skip flds
       }
       goto getOut3;
  }
   
  recHand=DmGetRecord(dbr,db->LastDbRecordRead); //03242002
 
  offset=db->offset;
  while(1)
  {
      find_arg_5();
      if (arg5==null_ptr) break;
      writeOutOneDbArgument(db, &(db->curHand), db->LastDbRecordRead ,&offset);
  }
  db->offset=offset;
 
  
  setDbOK();
  
getOut2:
  
  DmReleaseRecord(dbr,db->LastDbRecordRead,true);
getOut3:
    ;
}
/********************************************************************************************/
void verb_dbput()    //this is the old dbput which put only one field out
{
   UInt index;
   struct dbType *db;
   VoidHand recHand;
  VoidPtr  recPtr;
  unsigned long theLen;
  int theShort;
  
  ULong offset;
  long theInteger;
  float theSingle;
  void *theData;   
  int res;
  DmOpenRef dbr;
 
  int err;
  err=1;
  
  
  dbfind_arg(2);   //1=errcode,2=db,5=singlevar
  find_arg_5();
  db=getDatabasePtr();
  dbr=db->dm;
  chkDbOpen(db);
  if(db->curHand==0)
  {
       setDbErr(err);
       goto getOut3;
  }
  
 recHand=DmGetRecord(dbr,db->LastDbRecordRead); //03242002
  offset=db->offset;
  writeOutOneDbArgument(db, &(db->curHand), db->LastDbRecordRead ,&offset);
  db->offset=offset;

  
  setDbOK();
  
getOut2:
  
  DmReleaseRecord(dbr,db->LastDbRecordRead,true);
getOut3:
   ;
}

/********************************************************************************************/
void chkDbOpen(struct dbType *db)
{
  if (db->openSw!='o') 
  {                                        //inserted 05212003
      SysFatalAlert("accessing an unopened database");
      ErrThrow(-1);                 //inserted 05212003
  }                                        //inserted 05212003    
}

/********************************************************************************************/
void setDbOK()
{
  setDbRes(0);
}

/********************************************************************************************/
void setDbErr(err)
{
//StrPrintF(debug,"err=%d",DmGetLastErr());
//SysFatalAlert(debug);
#ifdef ORG_SWB
  setDbRes(1);
#endif
#ifdef ORG_NSB
  setDbRes(err);
#endif  
}

/********************************************************************************************/
void setDbRes(int err)
{
   double d;
   d=err;
   misc_stodbl1(&d);
}

/********************************************************************************************/
Int database_compare(void* a, void *b,Int oth,SortRecordInfoPtr j,SortRecordInfoPtr k, VoidHand appInfoH)
{
   int res;
   res=keyCompare((char*)a , (VoidPtr)b, oth);
   return(res);
}

/********************************************************************************************/
int keyCompare(char* a, VoidPtr b, int oth)
{   
   int res;
   int ci;
   long cl;
   double cd;
   float cf;
   
   struct 
   {
     char kind;
     char flags;
   } theKind;  
   char wks[50];
   
//dbug("at compare");
//DoubleToStr(*((double*)a),wks);
//StrPrintF(debug, "at db comp a=%s b=%d ",wks,(int*)b);
//SysFatalAlert(debug);

  *((int*)&theKind)=oth;
//StrPrintF(debug,"in keyComp  kind=%c flags=%i",theKind.kind, theKind.flags);
//SysFatalAlert(debug);
  if(theKind.kind=='s')
  {
     if(theKind.flags&0x80)
     {
         if( *((char*)a) < *((char*)b) ) res=-1;
         else
         {
            if( *((char*)a) > *((char*)b) ) res=1;
            else res=0;
         }
     }
     else res=StrCompare((char*)a,(char*)b);
//dbug("got compare");
  }
  else
  {
    
       if( theKind.flags& 0x80)  //integers (long -- 4-byte)
       {
         cl=*((double*)a);
         if ( cl < *((long*)b) ) res=-1;
         else
         {
           if   ( cl > *((long*)b) ) res=1;
           else res=0;
         }
         goto compOver;
       }
       if( theKind.flags&  0x40)     //numeric compare of two double args
       {
        if ( *((double*)a) < *((double*)b) ) res=-1;
        else
        {
           if   ( *((double*)a) > *((double*)b) ) res=1;
           else res=0;
        }
         goto compOver; 
       }
       
       if(theKind.flags&  0x20)  //single floatpt
       {
         cf=*((double*)a);
         if ( cf < *((float*)b) ) res=-1;
         else
         {
           
           if   ( cf > *((float*)b) ) res=1;
           else res=0;
         }
         goto compOver;
      }
      if(theKind.flags&  0x10)  //2-byte integers
      {
        ci=*((double*)a);
        if ( ci < *((int*)b) ) res=-1;
        else
        {
           if   ( ci > *((int*)b) ) res=1;
           else res=0;
        }
        goto compOver;
      }
      
        res=0;
         
  }
compOver:  

//StrPrintF(debug,"leaving compare res=%d",res);
//SysFatalAlert(debug);

  return(res);
}

/********************************************************************************************/
struct dbType *getDatabasePtr( )
{
  VoidPtr p;
  struct dbType db_example;
  VoidPtr q;
  
  int s=sizeof(db_example);
  UInt offset=s*dbNo;
//StrPrintF(debug,"dbno=%d len=%d dboffset=%d",dbNo,s,offset);
//SysFatalAlert(debug);
  
  p= (char*)dbElemsPtr + offset;
  return((struct dbType*)p);
}

/********************************************************************************************/
void verb_menureset()
{
   if (menuPtr!=null_ptr)
   {
     MenuEraseStatus(menuPtr);
   }
}

/********************************************************************************************/
void verb_menudraw()
{
   
   if(MenuGetActiveMenu()!=NULL)
   {
      MenuEraseStatus(NULL);
      MenuSetActiveMenu(NULL);
      FrmSetMenu(FrmGetActiveForm(),0);
      MenuDispose(menuPtr);
      menuPtr=(MenuBarType*)null_ptr; 
   }
   menuId=find_integer();
   menuPtr=MenuInit(menuId);
   MenuSetActiveMenu(menuPtr);
   MenuDrawMenu(menuPtr);
}

/********************************************************************************************/
void verb_menuerase()
{
  
  if( MenuGetActiveMenu() != NULL )
  {
     MenuDispose(menuPtr);
     menuPtr=(MenuBarType*)null_ptr;
  }
}

/********************************************************************************************/
void verb_initAVariableValue ()
{
    //initializes all occurrences of a variable's value to null-values if a string var and 0 if any other kind
    int wki;
    double d=0;
    int ii,jj,kk;
//dbug("init");    
    find_arg_1();
    if(arg1->max_no_values1<2)
    {
       if(arg1->kind=='s')  misc_stostr1("");
       else                 misc_stodbl1(&d);
    }
    else
    {
      if(arg1->kind!='s')  DmSet(arg1,DELEN,8*arg1->max_no_values1*arg1->max_no_values2*arg1->max_no_values3,0x00);
      else
      { 
           hData=MemPtrRecoverHandle(arg1);
           MemHandleUnlock(hData);
           hData=DmResizeResource(hData,DELEN+2*arg1->max_no_values1*arg1->max_no_values2*arg1->max_no_values3);
           if(hData==0) OutOfMemory(6004);     //inserted 05282003
           arg1=(struct dataelem*)MemHandleLock(hData);
//StrPrintF(debug,"verb-INITAVARIABLEVALUE= %d",arg1->tbl_no);
//SysFatalAlert(debug);
           
           DmWrite(deListPtr,arg1->tbl_no*4,&arg1,4);  //store handle in de list

           wki=DELEN+2*arg1->max_no_values1*arg1->max_no_values2*arg1->max_no_values3;;
           updti(arg1,&arg1->firstData,&wki);
           DmSet(arg1,DELEN,2*arg1->max_no_values1*arg1->max_no_values2*arg1->max_no_values3,0x00);
         goto skipOld;   
       
       
         for(ii=0;ii<arg1->max_no_values3;++ii)
         {
           for(jj=0;jj<arg1->max_no_values2;++jj)
           {
             for(kk=0;kk<arg1->max_no_values1;++kk)
             {
               
                    arg1_occ1=kk;
                    arg1_occ2=jj;
                    arg1_occ3=ii;
                    misc_stostr1("");
               
             }
           }

         }  
skipOld:
        ;
      }
    }
//dbug("leaving init");    
}

/********************************************************************************************/
void getModIDandOffset(UInt seqno,UInt*id,UInt*offset)
{
 int id2;
 int err;
 VoidHand h2;
 VoidPtr p2;
//dbug("at getmodid");

 if (parag_cnt >0)
 {
  
      h2=DmGetResource(rscTag,(ULong)9910);
      if(h2==0)
      {
         SysFatalAlert("Can't find program's parag record");
         ErrThrow(-1);                 //inserted 05212003
         //05212003 return;

      }

   p2=MemHandleLock(h2);

      //these are really link records for ext sub/func calls
//StrPrintF(debug,"getting id & offset for seqno=%d",seqno);
//SysFatalAlert(debug);
      id2=basc_dbGetInt( (char*)p2+(seqno-1)*4);
      *id=(unsigned short)id2;
      *offset=(unsigned short)basc_dbGetInt( (char*)p2+(seqno-1)*4+2);
//StrPrintF(debug,"got id=%d offset=%d",*id,*offset);
//SysFatalAlert(debug);
   MemHandleUnlock(h2);
   DmReleaseResource(h2);
 }
 else
  {
//dbug("no offset");
      *id=0;
      *offset=0;
  }
//StrPrintF(debug,"getmodid cnt=%d seqno=%d id=%d offset=%d",parag_cnt,seqno,*id,*offset);
//SysFatalAlert(debug);

}


/********************************************************************************************/
void verb_user_func()
{
  Err err;
  char resourceId[5]; //added 5.27.2000  4 + null (the null is ignored
  ULong rscLong;

  VoidHand newHand;  //added 5.27.2000
  VoidPtr newPtr;    //added 5.27.2000
  VoidPtr oldPtr;    //added 5.27.2000
  
  UInt idno;
  UInt shortOffset;
  unsigned long offset;
  VoidHand hand;
  VoidPtr ptr;
  Int i;
  UInt iy;
  ULong wkl;
  Int wki;

  
  
  
//dbug("a");
  iy=find_integer();
  getModIDandOffset(iy,&idno,&shortOffset);
  offset=shortOffset;
  

notNow:
//StrPrintF(debug,"going to user func idno=%d offset=%lu",idno,offset);
//SysFatalAlert(debug);
  codeexec(idno,offset);
}

/********************************************************************************************/
void verb_call()
{
  UInt idno;
  UInt shortOffset;
  unsigned long offset;
  
  UInt i;
  i=find_integer();
  getModIDandOffset(i,&idno,&shortOffset);
  offset=shortOffset;
//dbug("verb-call going to codeexec");
  codeexec(idno,offset);

  
}

/********************************************************************************************/
void verb_transfertoprogram()
{
	int cardno;
	int err;
	LocalID pgm;
	char work[120];

	find_arg_1();
	cardno = integ_value( arg1, (double *)arg1_val );
	find_arg_2();
	pgm=DmFindDatabase( cardno, arg2_val );

	if( pgm != 0 )
	{
		terminationAction='s';  //tell that switching apps
		err = SysUIAppSwitch( cardno, pgm, sysAppLaunchCmdNormalLaunch, NULL );  
	}

	if( pgm == 0 || err != 0 )
	{
		StrPrintF( work, "Can't find program '%s'", arg2_val );
		misc_errmsg( work );
	}
} // verb_transfertoprogram


/********************************************************************************************/
void verb_launchprogram()
{
   
   LocalID lid;
   LocalID basc;
   int cdno, err;
   char noCmd=0x00;
   struct basc_pref
   {
     char name[32];
     UInt cardNo;
   } bp; 
   char work[200];
   find_arg_1();   //program name
   
   find_arg_3();   //cardno
   
   cdno=basc_integ_value(arg3,(double*)arg3_val);
   lid=DmFindDatabase(cdno,arg1_val);
   if(lid==0)
   {
      StrCopy(work,"Can't find program=");
      StrCat(work,arg1_val);
      misc_errmsg(work);
   }   
   else
   {
     StrCopy(bp.name,arg1_val);
     bp.cardNo=cdno;
//SysFatalAlert("setting prefs");
#ifdef ORG_SWB
     PrefSetAppPreferences( (DWord)'basc',0,0,&bp,36,0);
#endif
#ifdef ORG_NSB
     PrefSetAppPreferences( (DWord)'NSBp',0,0,&bp,36,0);
#endif
//SysFatalAlert("going to launch");//
     
     ExitHousekeeping();
     launchPgm();
     
   } 
exitIt:
   return;
}






/********************************************************************************************/
void commonShowHide(int what, FormPtr frmPtr, int controlid)
{
  struct ObjectData * objPtr;    //added 09242003
  int j;
//StrPrintF(debug,"in show/hide  what=%c",what);
//SysFatalAlert(debug);
        for(j=0;j<FrmGetNumberOfObjects((FormType*)frmPtr);++j)
      {
//StrPrintF(debug,"compare j=%d ctl=%d obj=%d",j,controlid,FrmGetObjectId(frmPtr,j)   );
//SysFatalAlert(debug);
              
        if( FrmGetObjectId((FormType*)frmPtr,j)==controlid)
        {
            
            goto foundId;
        }
      }

notFoundCtlId:  
//StrPrintF(debug,"not found");
//SysFatalAlert(debug);
   return;
foundId:
  objPtr=locateObjectPtr(controlid);     //added 09242003
//StrPrintF(debug,"found j=%d",j);
//SysFatalAlert(debug);
  if (what==0x00)
  {
     FrmHideObject((FormType*)frmPtr,j);
     objPtr->hidden=true;                  //added 09242003
     //added 09092002 to also hide the scrollbar
     //09242003 if(FrmGetObjectType(frmPtr,j)==frmFieldObj) //must be a fld obj
     if((FrmGetObjectType(frmPtr,j)==frmFieldObj)   //added 09242003   must be fld or grid
     || (FrmGetObjectType(frmPtr,j)==frmTableObj) ) //added 09242003
	  {			
//SysFatalAlert("re-showing field");
            //see if any attached scrollbars that need updated                            //added 12172001
                                                  //added 12172001
            if( j<FrmGetNumberOfObjects(frmPtr)-1)                                      //added 12172001
            {                                                                             //added 12172001
                if(FrmGetObjectType(frmPtr, j+1)==frmScrollBarObj)                      //added 12172001
                {                                                                         //added 12172001 
//SysFatalAlert("hiding  scrollbar in basc"); 
                   //have an attached scrollbar                                           //added 12172001
                   FrmHideObject((FormType*)frmPtr,j+1);  //09092002 hide scrollbar
//SysFatalAlert("done hiding  scrollbar in basc");                   
                   
                }                                                                        //added 12172001
            }
            if(FrmGetObjectType(frmPtr,j)==frmTableObj)  redrawGrid(objPtr); //added 09242003
            }
      }
  else 
  {
       objPtr->hidden=false;                  //added 09242003
      FrmShowObject((FormType*)frmPtr,j);
      
      //09242003 if(FrmGetObjectType(frmPtr,j)==frmFieldObj) //must be a fld obj
      if((FrmGetObjectType(frmPtr,j)==frmFieldObj)    //added 09242003
      || (FrmGetObjectType(frmPtr,j)==frmTableObj) )  //added 09242003
	  {			
//SysFatalAlert("re-showing field");
            //see if any attached scrollbars that need updated                            //added 12172001
                                                  //added 12172001
            if( j<FrmGetNumberOfObjects(frmPtr)-1)                                      //added 12172001
            {                                                                             //added 12172001
                if(FrmGetObjectType(frmPtr, j+1)==frmScrollBarObj)                      //added 12172001
                {                                                                         //added 12172001 
                   //have an attached scrollbar                                           //added 12172001
                   
//SysFatalAlert("updating scrollbar at show");
                  
                   FrmShowObject((FormType*)frmPtr,j);   //added 09092002 show scrollbar too
                   
                   if(FrmGetObjectType(frmPtr,j)==frmFieldObj)
                   UpdateScrollbar((FieldType*)FrmGetObjectPtr(frmPtr,j),    //added 12172001
                      (ScrollBarPtr )(FrmGetObjectPtr(frmPtr, j+1)));                   //added 12172001
                }                                                                         //added 12172001
            }
      }
                      
      if(FrmGetObjectType(frmPtr,j)==frmTableObj)  redrawGrid(objPtr); //added 09242003      
  }
}
/********************************************************************************************/
void verb_controlhideorshow()
{
  char res;
  Word j;
  VoidPtr frmPtr;
  
  find_ctlid(true);
  res=find_char();
  
  frmPtr=FrmGetActiveForm();   //pt to form
  if(frmPtr==NULL) return;   //???says frm not loaded
//StrPrintF(debug,"got form=%d #objs=%d",wkid,  FrmGetNumberOfObjects(frmPtr));
//SysFatalAlert(debug);
  commonShowHide(res,frmPtr,controlid);
  return;
}
/********************************************************************************************/
void commonSetFieldTextRoutine(FieldPtr controlPtr,Word controlId, char*s)
{
  FormPtr frmPtr;        // added 5.20.2000
  Word idx;              //added 5.20.2000  
 
  VoidHand oldHand;
  VoidHand h;
  VoidPtr p;
  FieldAttrType attr;
  
  int res;
  int i;
  
  oldHand=FldGetTextHandle((FieldPtr)controlPtr);  //get handle to the field's current content
  
  i=StrLen(s)+1;
  h=MiscHandleNew(i,"setTxt");  //get new memory for the fld text
  p=MiscHandleLock(h);          //and lock a pointer to it
  StrCopy((char*)p,s);   //and copy text into new area
  
//StrPrintF(debug,"Setting field text to %s",p);
//dbug(debug);  
  
  //now go change the field's text but don't redraw                          //added 5.31.2000
  //temp SetFieldText(controlid, p, FldGetMaxChars((FieldPtr)controlPtr)+1,false);  //added 5.31.2000

  MiscPtrUnlock(p);           // and unlock the new text pointer
  //FldSetTextHandle((FieldPtr)controlPtr,(Handle)h);  //temp
  FldSetText((FieldPtr)controlPtr,(Handle)h,0,MemHandleSize(h)); 
  if(oldHand) MemHandleFree(oldHand);  //0803 m2000
  
  //FldDrawField ((FieldPtr)controlPtr);

  frmPtr= FrmGetActiveForm();
  if(frmPtr==0) return;                                                 //added 5.20.2000
//StrPrintF(debug,"active form=%d controlId=%d",FrmGetActiveFormID(),controlId);
//dbug(debug);
  
  for(idx=0;idx<FrmGetNumberOfObjects(frmPtr);++idx)
  {
//StrPrintF(debug,"comparing id=%d to %d",FrmGetObjectId(frmPtr,idx),controlId);
//dbug(debug);
     if(FrmGetObjectId(frmPtr,idx)==controlId)  //see if fld on cur form
     {
//dbug("redrawing");
       //see if hidden and if so exit
       FldGetAttributes((FieldPtr)FrmGetObjectPtr(frmPtr,idx) ,&attr);	   
       if(attr.visible==0)  return;
         //see if any attached scrollbars that need updated                          //added 5.20.2000
       FldDrawField ((FieldPtr)controlPtr);
       if(FrmGetObjectType(frmPtr, idx+1)==frmScrollBarObj)                      //added 5.20.2000
       {                                                                         //added 5.20.2000 
          //have an attached scrollbar                                           //added 5.20.2000
       
//SysFatalAlert("updating scrollbar");
          UpdateScrollbar((FieldPtr)controlPtr                      ,            //added 5.20.2000
                      (ScrollBarPtr )(FrmGetObjectPtr(frmPtr, idx+1)));       //added 5.20.2000
          return;            
       }                                                                         //added 5.20.2000
     }                                                                           //added 5.20.2000
   }

}
/********************************************************************************************/
void verb_fieldsettext()
{
  find_ctlid(true);
  find_arg_1(); //text
//dbug("in fld set text -- going to common");  
  commonSetFieldTextRoutine((FieldPtr)controlPtr,controlid,arg1_val);
}



/********************************************************************************************/
void verb_draw_bitmap()
{
    //from Palm Dev Support
    int theBitmapId;
    VoidHand		theResourceHandle;
	BitmapPtr	theBitmapPtr;
	int x;
	int y;
//SysFatalAlert("at draw bitmap");
    find_arg_1();
    find_arg_2();
    find_arg_3();	
	theBitmapId=basc_integ_value(arg1,(double*)arg1_val);
	x=basc_integ_value(arg2,(double*)arg2_val);
	y=basc_integ_value(arg3,(double*)arg3_val);
	// Grab the handle to our bitmap resource
	theResourceHandle = DmGetResource( bitmapRsc, theBitmapId );
	if (theResourceHandle==nil)
	{                                //inserted 05212003   
	   SysFatalAlert("Can't find a bitmap to draw.");
	   ErrThrow(-1);                 //inserted 05212003
	}                                //inserted 05212003
	// Lock down the handle so we can get the pointer to the bitmap
	theBitmapPtr = (BitmapType*)MemHandleLock( theResourceHandle );
//SysFatalAlert("at draw bitmap");
	WinDrawBitmap( theBitmapPtr, x, y );
	
	// Unlock the handle to the bitmap
	MemHandleUnlock( theResourceHandle );

	// Finally, release the resource
	DmReleaseResource( theResourceHandle );
}
/********************************************************************************************/

void verb_assign_bitmap()
{
   FormBitmapType * BitmapPtr;
  
   find_ctlid(true);
   find_arg_2();  //bitmap rscid
   BitmapPtr=(FormBitmapType*)controlPtr;
   //BitmapPtr->rscID=basc_integ_value(arg2,(double*)arg2_val); //GHGlue: AFAIK, this is never called.
   
}




/********************************************************************************************/
Boolean find_ctlid(Boolean abortSw)
{
   char work[100];
   int err;
   Word idx2;
   VoidHand h2;
   char* p2;
   char *savep2;
   int wkint;
   int wkcnt;
   int wk0,wk1,wk2,wk3;
   int i;
   UInt wkid;
   VoidPtr frmPtr;
   int j;
   Boolean retVal;

   controlid=find_integer();
   
      h2=DmGetResource(rscTag,(ULong)9907);
      if(h2==0)
      {
         SysFatalAlert("Can't find view record");
         ErrThrow(-1);                 //inserted 05212003
         //05212003 return;
      }

   p2=MemHandleLock(h2);
   savep2=p2;
//StrPrintF(debug,"-4  view_cnt=%d",view_cnt);
//SysFatalAlert(debug);
    wkint=0;
    wkcnt=0;
   
                           //06102002
   for(i=0;i<view_cnt;++i)
   {
      wkid=basc_dbGetInt( (char*)p2); //06102002(modified) /*get id of view*/
      p2=(VoidPtr)((char*)p2+2); 
      if (applVersionInteg >= 300)    //06102002
      {								//06102002
//dbug("skipping");
			//skip over form name	//06102002
			while(1)				//06102002
   			{						//06102002
   				if((*p2)==0x00)
   				{
   				 ++p2;
   				 break; //06102002
  				}
  				++p2;				//06102002
  			}						//06102002
  	        //++p2;							//06102002
  	  }								//06102002
  	  
//StrPrintF(debug,"got form=%d ",wkid);
//SysFatalAlert(debug);
      frmPtr=FrmGetFormPtr(wkid);   //pt to form
      if(frmPtr==NULL) continue;   //???says frm not loaded
//StrPrintF(debug,"got form=%d #objs=%d",wkid,  FrmGetNumberOfObjects(frmPtr));
//SysFatalAlert(debug);
      for(j=0;j<FrmGetNumberOfObjects((FormType*)frmPtr);++j)
      {
//StrPrintF(debug,"compare j=%d ctl=%d obj=%d",j,controlid,FrmGetObjectId(frmPtr,j)   );
//SysFatalAlert(debug);
                
        wkcnt=wkcnt+1;
        wkint=wkint+FrmGetObjectId((FormType*)frmPtr,j);
        if( FrmGetObjectId((FormType*)frmPtr,j)==controlid)
        {
          controlPtr=FrmGetObjectPtr((FormType*)frmPtr,j);
          retVal=true;
          goto foundId;
        }
      }
      //++p2;
   }
notFoundCtlId:   
    if (abortSw==true)
    {
      StrPrintF(work,"can't find control object #=%d cnt=%d TOT=%d ",
              controlid,wkcnt,wkint);
      SysFatalAlert(work);
      ErrThrow(-1);                 //inserted 05212003
      //05212003 retVal=false;
    }
    else
    {
        retVal=false;
    }  
foundId:
//SysFatalAlert("found id");
   MemPtrUnlock(savep2);
   DmReleaseResource(h2);
   return(retVal);
}



/********************************************************************************************/
void verb_getPen()
{
  find_arg_1();  //current x
  find_arg_2();  //current y
  find_arg_3();  //pen up/down

  restore_int_val(currentX,arg1, (double*)arg1_val, arg1_occ1,arg1_occ2,arg1_occ3);
  restore_int_val(currentY,arg2, (double*)arg2_val, arg2_occ1,arg2_occ2,arg2_occ3);
  if(penDown==true)  restore_int_val(2,arg3, (double*)arg3_val, arg3_occ1,arg3_occ2,arg3_occ3);
  else               restore_int_val(3,arg3, (double*)arg3_val, arg3_occ1,arg3_occ2,arg3_occ3);
}

/********************************************************************************************/
void verb_start_debug()
{
  debug_on=1;
}

/********************************************************************************************/
void verb_end_debug()
{
  debug_on=0;
}

/********************************************************************************************/
void verb_end_sub()
{
   VoidHand newHand;
   VoidHand oldHand;
   VoidPtr oldPtr;
   VoidPtr newPtr;
   Int ix;
   int id;
   Int i;
   int kk;
   int res;
   UInt finalInstrCtr=instr_ctr;
   struct dataelem* de;
   

    //remove any work var recs created for this function
   for(kk=1;kk<=work_de_max;++kk)
   {
       de=*((VoidPtr*)((char*)deListPtr+4*kk));
       if( de!=0)
       {
          if((de->flags3 & 0x02)==0x02)  //08032002
          {
             MemPtrFree(de);
          }
          else
          {
           res=DmFindResource(VbRscDB,(ULong)'WkVr',work_de_max*userFunctionSequentialNo+kk,nil);
           if(res!= -1)
           {
//StrPrintF(debug,"removing wkvar %d",work_de_max*userFunctionSequentialNo+kk);
//SysFatalAlert(debug);
               DmRemoveResource(VbRscDB,res); //delete  if there
           }
         }   
       }
   }
//dbug("re-estab wk vars");

   
   id=codeBlockPtr->functionLinkNo;
   while(1)
   {
//StrPrintF(debug,"searching for rec=%d offset=&%d",codeBlockPtr->functionLinkNo, codeBlockPtr->offset);
//SysFatalAlert(debug);
     ix=DmFindResource(VbRscDB,(ULong)'fwrk',id,NIL); 
      if(ix!= -1)
      {
//dbug("got old func rec");
        oldHand=MiscDmGetResourceIndex(VbRscDB,ix,"rescwk"); 
        oldPtr=MiscHandleLock(oldHand);
//StrPrintF(debug,"got id=%d offset=%d",*((int*)oldPtr),*((unsigned int*)((char*)oldPtr+2)));
//SysFatalAlert(debug);

        if( (*((int*)oldPtr) != codeBlockPtr->functionLinkNo) || (*((unsigned int*)((char*)oldPtr+2)) != codeBlockPtr->offset))
        {
           MiscHandleUnlock(oldHand);
           MiscDmReleaseResource(oldHand);
           id+=50;                        //increm recno by 50 to try again
        }
        else
        {
          break;               //found the record we want
        } 
      }
      else
      {
          MiscFatalAlert("internal error exiting a function.");
      }
   }   
//StrPrintF(debug,"find linkNo=%d rsc=%d ",id,ix);
//SysFatalAlert(debug);
   MemMove((char*)deListPtr+4,(char*)oldPtr+4,work_de_max*4);        //and copy the handles
   MemHandleUnlock(oldHand);
   MiscDmReleaseResource(oldHand);
   
   userFunctionSequentialNo-=1;  //reduce count of nested user function calls
   
   
   instr_ctr=codeBlockPtr->argsOffset; //reset called args ptr
//dbug("in verb end rtn");
//StrPrintF(debug,"sub-end=%d resetting instr_ctr to %d",codeBlockPtr->id,instr_ctr);
//SysFatalAlert(debug);

   end_all_move_args();
   instr_ctr=finalInstrCtr;
//dbug("leaving verb_end_sub");
}

//------------------------------------------------------------------------------
//     end of a user defined function
//------------------------------------------------------------------------------
void verb_end_function()
{
     char resourceId[5];        //added 5.27.2000
     ULong rscLong;

     VoidHand newHand;          //added 5.27.2000
     VoidHand oldHand;          //added 5.27.2000
     VoidPtr  oldPtr;           //added 5.27.2000
     VoidPtr  newPtr;           //added 5.27.2000 
     Int ix;                    //added 5.27.2000 
     int id;
     Int i;                     //added 5.27.2000    
     DmOpenRef dbr; 
     int kk,mm,nn; 
     int res;
     
      
     UInt instr_ctr_save;
     char *codePtrSave;
     UInt finalInstrCtr=instr_ctr;
//dbug("in end of user func");
     struct dataelem* de;
 
    //remove any work var recs created for this function
   for(kk=1;kk<=work_de_max;++kk)
   {
       de=*((VoidPtr*)((char*)deListPtr+4*kk));
       if( de!=0)
       {
          if((de->flags3 & 0x02)==0x02)  //08032002
          {
             MemPtrFree(de);
          }
          else
          {
           res=DmFindResource(VbRscDB,(ULong)'WkVr',work_de_max*userFunctionSequentialNo+kk,nil);
           if(res!= -1)
           {
//dbug("removing wkvar");
               DmRemoveResource(VbRscDB,res); //delete  if there
           }
         }   
       }
   }
   id=codeBlockPtr->functionLinkNo;
   
   while(1)
   {
      ix=DmFindResource(VbRscDB,(ULong)'fwrk',id,NIL); 
      if(ix!= -1)
      {
//dbug("got old func rec");
        oldHand=MiscDmGetResourceIndex(VbRscDB,ix,"rescwk"); 
        oldPtr=MiscHandleLock(oldHand);
        if( (*((int*)oldPtr) != codeBlockPtr->functionLinkNo) || (*(unsigned int*)((char*)oldPtr+2) != codeBlockPtr->offset))
        {
           MiscHandleUnlock(oldHand);
           MiscDmReleaseResource(oldHand);
           id+=50;                        //increm recno by 50 to try again
        }
        else
        {
          break;               //found the record we want
        } 
      }
      else
      {
          MiscFatalAlert("internal error exiting a function.");
      }
   }   
//StrPrintF(debug,"find linkNo=%d rsc=%d ",id,ix);
//SysFatalAlert(debug);
                              //point to the new wk var record
   
                          //point to the old copy of the wk var handles
   MemMove((char*)deListPtr+4,(char*)oldPtr+4,work_de_max*4);        //and copy the handles
   MemHandleUnlock(oldHand);
   MiscDmReleaseResource(oldHand);
   
   userFunctionSequentialNo-=1;  //reduce count of nested user function calls
     
     
       
    instr_ctr=codeBlockPtr->argsOffset; //reset called args ptr
    end_all_move_args();
 skip:
    find_arg_2();   //name of func dataname to put result in   ??used or not
  


    instr_ctr_save=instr_ctr;
    codePtrSave=codePtr;
    codePtr=(char*)codeBlockPtr->codePtr;
    instr_ctr=codeBlockPtr->instr_ctr;
//StrPrintF(debug,"moving one arg instr-ctr=%ui",instr_ctr);
//SysFatalAlert(debug);    
    find_arg_1();  //called func name ref
    codeBlockPtr->instr_ctr=instr_ctr;
    codePtr=codePtrSave;
    instr_ctr=instr_ctr_save;
    
   instr_ctr=finalInstrCtr;
   

  
}
/********************************************************************************************/
void end_all_move_args()
{
   UInt instr_ctr_save;
   char *codePtrSave;
   int kk,mm,nn;

  while (1)   //copy args to internal vars
  {

    instr_ctr_save=instr_ctr;
    codePtrSave=codePtr;
    codePtr=(char*)codeBlockPtr->codePtr;
    instr_ctr=codeBlockPtr->instr_ctr;
//StrPrintF(debug,"moving one arg codePtr=%lu instr-ctr=%u",(unsigned long)(codePtr),instr_ctr);
//SysFatalAlert(debug);    
    find_arg_1();
    codeBlockPtr->instr_ctr=instr_ctr;
    codePtr=codePtrSave;
    instr_ctr=instr_ctr_save;
 //StrPrintF(debug,"2cnd arg codePtr=%lu instr_ctr=%d",(unsigned long)(codePtr),instr_ctr);
 //SysFatalAlert(debug);
    find_arg_2();
    if (arg1==null_ptr)
    {
//dbug("caller is null");
      if (arg2 != null_ptr)
      {
wrong_no:
         SysFatalAlert("Wrong number of func args");
         ErrThrow(-1);                 //inserted 05212003
      }
      else break;
    }
//dbug("caller not null");
    if (arg2==null_ptr)
    {
//dbug("func is null");
        goto wrong_no;
    }
//dbug("********moving it*");
     
if((arg2->max_no_values1>1)&&(arg2_occ1==0))
    {
        //looks like an array name without a subscript
        
        //need to move all values of the array
        for( kk=0;kk<arg2->max_no_values1;++kk)
        {
           for( mm=0;mm<arg2->max_no_values2;++mm)
           {
              for( nn=0;nn<arg2->max_no_values3;++nn)
              {
                 arg1_val = devel_address(arg1, kk,mm,nn);
                 arg2_val = devel_address(arg2, kk,mm,nn);
                 arg1_occ1=kk;
                 arg1_occ2=mm;
                 arg1_occ3=nn;
                 if (arg1->kind=='s')
                 {
                      misc_stostr1(arg2_val);
                 }
                 else
                 {
                      misc_stodbl1((double*)arg2_val);
                 }
              }
           }
        }   
      }
      else
      {
        if (arg1->kind=='s')
        {
           misc_stostr1(arg2_val);
        }
        else
        {
           misc_stodbl1((double*)arg2_val);
        }
     }  
  }
//dbug("args done");
   

}

/********************************************************************************************/
void verb_beep()
{
    if(romVersion<0x03000000)
    {
        if(PrefGetPreference(prefSysSoundLevelV20)==slOff) return;  //prior to v3.0 -- exit if sound off
    }
    else
    {
        if(PrefGetPreference(prefSysSoundVolume)==0) return;        //v3.0 and up -- exit if sound volume=0
    }
    SndPlaySystemSound(sndError);
}



/********************************************************************************************/
void verb_seteventhandled()
{
   eventHandled=1;
   if ( eventType==3)
   {
       //penUp, so clear the pen event queue
       EvtFlushPenQueue();
   }
}

/********************************************************************************************/
void dbGetSome(void* from,int len,void*to)
{
  int i;
  char*f=(char*)from;
  char*t=(char*)to;
  for (i=0;i<len;++i)
  {
     *(t++)=*(f++);
  }
}

/********************************************************************************************/
void verb_serialOpen()
{
   Err err;
   //UInt port;											//12.05.02 GH
   ULong port;											//12.05.02 GH
   ULong baud;
   VoidHand h;
   
   //port=basc_integ_value(arg1,(double*)arg1_val);
   port=long_integ_value(arg1,(double*)arg1_val);		//12.05.02 GH
   baud=long_integ_value(arg2,(double*)arg2_val);
   
   modemInfo.initialBaud=baud;
   modemInfo.cmdTimeOut=mdmDefCmdTimeOut;
   modemInfo.dtWaitSec=mdmDefDTWaitSec;
   modemInfo.dcdWaitSec=mdmDefDCDWaitSec;
   modemInfo.volume=mdmDefSpeakerVolume;
   modemInfo.pulse=false;
   modemInfo.hwHShake=false;
   modemInfo.autoBaud=true;
   modemInfo.canProcP=NULL;
   modemInfo.curStage=0;
   
   serialBufferSize=512;
   if(gOldSerialManager)  								//02.27.02 GH
   {
   	   SysLibFind("Serial Library", &serRef);			//02.27.02 GH
  	   modemInfo.portID=serRef;							//02.27.02 GH
   	   err=SerOpen(serRef, (UInt16) port, baud);		//12.05.02 GH
   }
   else
   {
       if(port==0) port=0x8000; //hotSync port           //02.27.02 GH
   	   err=SrmOpen(port, baud, &serRef);				 //02.27.02 GH
  	   modemInfo.portID=serRef;							 //02.27.02 GH
   }
   setSerErr(err);
   if(err==0)
   {
       //05282003serialBufferPtr=MemHandleLock(MemHandleNew(serialBufferSize+1+32));
       h=MemHandleNew(serialBufferSize+1+32);  //05282003
       if(h==0) OutOfMemory(6054);             //05282003
       serialBufferPtr=MemHandleLock(h);       //05282003
       
       //05282003 if(serialBufferPtr==0)             //modified 05212003
       //05282003 {                                  //inserted 05212003
       //05282003      SysFatalAlert("Not enough memory for serial buffer.");
       //05282003      ErrThrow(-1);                 //inserted 05212003
       //05282003 }                                  //inserted 05212003
       if (gOldSerialManager) SerSetReceiveBuffer(serRef,serialBufferPtr,serialBufferSize+1+32);
       else SrmSetReceiveBuffer(serRef,serialBufferPtr,serialBufferSize+1+32);
   }
   serialSetState(kSerialNoAsync);
}

/**************************************************************************************************/
void verb_serialClose()
{
  Err err;
//StrPrintF(debug,"at serclose serRef=%d",serRef);
//SysFatalAlert(debug);
  
  if(serRef>0) 
  {
		if (gOldSerialManager) err=SerClose(serRef);	//02.27.02 GH
  	else err=SrmClose(serRef);						//02.27.02 GH
  }
  else err=serErrNotOpen;
  serRef=0;
//StrPrintF(debug,"at serclose err=%d",err);
//SysFatalAlert(debug);
   if(err==0) 
   {
   MemPtrFree(serialBufferPtr);
   serialSetState(kSerialNoAsync);
   setSerErr(err);
   }
}

/**************************************************************************************************/
void verb_serialSet()								//03.04.02 GH - for newSerialManager
{
   Err err;
   char in[50];
   Int i;
   Int32 i32;
   UInt16 size_i32=sizeof(i32);
   UInt32 ui32;
   UInt16 size_ui32=sizeof(ui32);
   Boolean b;
   UInt16 size_b=sizeof(b);
   VoidHand h;  //05282003
   
   if(StrCaselessCompare(arg1_val,"heapvariablecount")==0)      //08012002
   {															//08012002
       maxVarsInDynamHeap=integ_value(arg2,(double*)arg2_val);  //08012002
       return;
   }
   
   
   if(StrCaselessCompare(arg1_val,"timer")==0)  				//08032005    			
   {															
		int unsigned long t;
		t=long_integ_value(arg2,(double*)arg2_val);
		if( t==0 ) 
			{
			    timerExpirationTime = 0;   //kill timer
			}
			else
			{
			    t=t*SysTicksPerSecond();
			    t=t/1000;
			    timerExpirationTime= t + TimGetTicks();
			}
		return;
   }
   
   
   if(gOldSerialManager) {verb_serialSetOld(); return;}
   
   StrCopy(in,arg1_val);
   StrToLower(in,in);
   
       if (StrCompare(in,"baudrate")==0)
       {
			i32=long_integ_value(arg2,(double*)arg2_val);
            err=SrmControl(serRef, srmCtlSetBaudRate, &i32, &size_i32);
            modemInfo.initialBaud=i32;
            goto processed;
       }      
       if (StrCompare(in,"stopbits")==0) 
       {    
            i=basc_integ_value(arg2,(double*)arg2_val);
            err=SrmControl(serRef, srmCtlGetFlags, &ui32, &size_ui32);
            if(i==1) ui32 &= ~srmSettingsFlagStopBits1;
            else if(i==2) ui32 |= srmSettingsFlagStopBits2;
            goto setIt;
       }     
       if (StrCompare(in,"parity")==0)
       {
            i=basc_integ_value(arg2,(double*)arg2_val);
            err=SrmControl(serRef, srmCtlGetFlags, &ui32, &size_ui32);
                        
            if (i==1) 		//odd
            {
            	ui32 |= srmSettingsFlagParityOnM;
           	    ui32 &= ~srmSettingsFlagParityEvenM;
            }
            else if (i==2) //even
            {	
            	ui32 |= srmSettingsFlagParityOnM; 
            	ui32 |= srmSettingsFlagParityEvenM;
            }
           
            else if (i==3) //none
            {
           	   ui32 &= ~srmSettingsFlagParityOnM;
           	   ui32 &= ~srmSettingsFlagParityEvenM;
            }
            goto setIt;        
       }        
       if (StrCompare(in,"xonxoff")==0)
       {
            i=basc_integ_value(arg2,(double*)arg2_val);
            err=SrmControl(serRef, srmCtlGetFlags, &ui32, &size_ui32);
            if (i==1) ui32 |= srmSettingsFlagXonXoffM; //on
            else if (i==2) ui32 &= ~srmSettingsFlagXonXoffM; //off
            goto setIt; 
       }      
       if (StrCompare(in,"rtsauto")==0)
       {
            i=basc_integ_value(arg2,(double*)arg2_val);
            err=SrmControl(serRef, srmCtlGetFlags, &ui32, &size_ui32);
            if (i==1) ui32 |= srmSettingsFlagRTSAutoM; //on
            else if (i==2) ui32 &= ~srmSettingsFlagRTSAutoM; //off
            goto setIt; 
       }     
       if (StrCompare(in,"ctsauto")==0)
       {
            i=basc_integ_value(arg2,(double*)arg2_val);
            err=SrmControl(serRef, srmCtlGetFlags, &ui32, &size_ui32);
            if (i==1) ui32 |= srmSettingsFlagCTSAutoM; //on
            else if (i==2) ui32 &= ~srmSettingsFlagCTSAutoM; //off
            goto setIt; 
       }     
       if (StrCompare(in,"bitsperchar")==0)
       {
            i=basc_integ_value(arg2,(double*)arg2_val);
            err=SrmControl(serRef, srmCtlGetFlags, &ui32, &size_ui32);
            ui32 &= ~srmSettingsFlagBitsPerCharM;
            if(i==5) ui32 |= srmSettingsFlagBitsPerChar5;
            else if(i==6) ui32 |= srmSettingsFlagBitsPerChar6;
            else if(i==7) ui32 |= srmSettingsFlagBitsPerChar7;
            else if(i==8) ui32 |= srmSettingsFlagBitsPerChar8;
            goto setIt;            
       }
       if (StrCompare(in,"ir")==0)
       {
            i=basc_integ_value(arg2,(double*)arg2_val);
            if (i==0)
            {
            err=SrmControl(serRef, srmCtlIrDADisable,(void *)NULL, (UInt16 *)NULL);
            err=SrmControl(serRef, srmCtlRxDisable,(void *)NULL, (UInt16 *)NULL);
            }
            else if (i==1) //receive IR
            {
            err=SrmControl(serRef, srmCtlIrDAEnable,(void *)NULL, (UInt16 *)NULL);
            err=SrmControl(serRef, srmCtlRxEnable,(void *)NULL, (UInt16 *)NULL);
            }
            else if (i==2) //transmit IR
            {
            err=SrmControl(serRef, srmCtlIrDAEnable,(void *)NULL, (UInt16 *)NULL);
            err=SrmControl(serRef, srmCtlRxDisable,(void *)NULL, (UInt16 *)NULL);
            }
            goto processed; 
       }     
       if (StrCompare(in,"ctstimeout")==0)
       {
            i32=*((double*)arg2_val)*sysTicksPerSecond;
            err=SrmControl(serRef, srmCtlSetCtsTimeout, &i32, &size_i32);
            goto processed;
       }
       if (StrCompare(in,"dtrassert")==0)
       {
            i=basc_integ_value(arg2,(double*)arg2_val);
            b=(i==1);
            err=SrmControl(serRef, srmCtlSetDTRAsserted, &b, &size_b);
            goto processed;
       }
       if (StrCompare(in,"dtwait")==0)
       {
            modemInfo.dtWaitSec=integ_value(arg2,(double*)arg2_val);
            err=0;
            goto processed;
       }
       if (StrCompare(in,"dcdwait")==0)
       {
            modemInfo.dcdWaitSec=integ_value(arg2,(double*)arg2_val);
            err=0;
            goto processed;
       }
       if (StrCompare(in,"dialtone")==0)
       {
            i=integ_value(arg2,(double*)arg2_val);
            if(i==0) modemInfo.pulse=true;
            else     modemInfo.pulse=false; 
            err=0;
            goto processed;
       }
       if (StrCompare(in,"handshake")==0)
       {
            modemInfo.hwHShake=integ_value(arg2,(double*)arg2_val);
            err=0;
            goto processed;
       }
       if (StrCompare(in,"autobaud")==0)
       {
            modemInfo.autoBaud=integ_value(arg2,(double*)arg2_val);
            err=0;
            goto processed;
       }
       if (StrCompare(in,"cmdtimeout")==0)
       {
            modemInfo.cmdTimeOut=integ_value(arg2,(double*)arg2_val);
            err=0;
            goto processed;
       }
       if (StrCompare(in,"volume")==0)
       {
            modemInfo.volume=integ_value(arg2,(double*)arg2_val);
            err=0;
            goto processed;
       }
       if (StrCompare(in,"buffersize")==0)
       {
            serialBufferSize=integ_value(arg2,(double*)arg2_val);
            if(serialBufferPtr) MemPtrFree(serialBufferPtr);
            //05282003 serialBufferPtr=MemHandleLock(MemHandleNew(serialBufferSize+1+32));
            h=MemHandleNew(serialBufferSize+1+32);  //05282003
            if(h==0) OutOfMemory(6055);             //05282003
            serialBufferPtr=MemHandleLock(h);       //05282003

            //05282003 if(serialBufferPtr==0)            //modified 05212003
            //05282003 {                                 //inserted 05212003
            //05282003      SysFatalAlert("Not enough memory for serial buffer.");
            //05282003      ErrThrow(-1);                 //inserted 05212003
            //05282003 }                                  //inserted 05212003
            SrmSetReceiveBuffer(serRef,serialBufferPtr,serialBufferSize+1+32);
       
            err=0;
            goto processed;
       }
       if (StrCompare(in,"portid")==0)
       {
            serRef=integ_value(arg2,(double*)arg2_val);       
            err=0;
            goto processed;
       }
       if (StrCompare(in,"coordinatesystem")==0)  //GWH 2003.03.27
       {
            if (romVersion>=0x05000000)
            {
//dbug("setting double density");
                WinSetCoordinateSystem(integ_value(arg2,(double*)arg2_val));
            }
            err=0;    
            goto processed;
       }
       StrPrintF(debug,"Unrecognizable set parameter=%s",in);
       SysFatalAlert(debug);
       ErrThrow(-1);                 //inserted 05212003     
  	   //05212003 return;
setIt:
       err=SrmControl(serRef, srmCtlSetFlags, &ui32, &size_ui32);
processed:
    setSerErr(err);
}
/**************************************************************************************************/
void verb_serialSetOld()
{
   VoidHand h;  //05282003 
   Err err;
   char in[50];
   char z;
   double dbl;
   int x;
   int i;
   SerSettingsType s;
   err=SerGetSettings( serRef,&s);
   setSerErr(err);
   if (err) {return;}
   StrCopy(in,arg1_val);
   StrToLower(in,in);
   
       if (StrCompare(in,"baudrate")==0)
       {
           
            s.baudRate=long_integ_value(arg2,(double*)arg2_val);
            modemInfo.initialBaud=s.baudRate;
            goto setIt;
       }      
       if (StrCompare(in,"stopbits")==0) 
       {    
            i=basc_integ_value(arg2,(double*)arg2_val);
            if(i==1) s.flags=s.flags  & 0xfffe;
            if(i==2) s.flags=s.flags  | 0x0001;
            goto setIt;
       }     
       if (StrCompare(in,"parity")==0)
       {
            z=basc_integ_value(arg2,(double*)arg2_val);
            if (z==1) //odd
            {
               s.flags &= 0xfff9;
               s.flags |= 0x0002;
               goto setIt;
            }
            if (z==2) //even
            {
               s.flags &= 0xfff9;
               s.flags |= 0x0006;		//11.29.00 gh
               goto setIt;
            }
            if (z==3) //none
            {
               s.flags &= 0xfff9;
               goto setIt;
            }
            goto setIt;        
       }
        
       if (StrCompare(in,"xonxoff")==0)
       {
             z=basc_integ_value(arg2,(double*)arg2_val);
            if (z==1) //on
            {
               
               s.flags |= 0x0008;
               goto setIt;
            }
            if (z==2) //off
            {
               s.flags &= 0xfff7;
               goto setIt;
            }
            goto setIt; 
       }      
       if (StrCompare(in,"rtsauto")==0)
       {
            z=basc_integ_value(arg2,(double*)arg2_val);
            if (z==1) //on
            {
               
               s.flags |= 0x0010;
               goto setIt;
            }
            if (z==2) //off
            {
               s.flags &= 0xffef;
               goto setIt;
            }
            goto setIt; 
       }     
       if (StrCompare(in,"ctsauto")==0)
       {
            z=basc_integ_value(arg2,(double*)arg2_val);
            if (z==1) //on
            {
               
               s.flags |= 0x0020;
               goto setIt;
            }
            if (z==2) //off
            {
               s.flags &= 0xffdf;
               goto setIt;
            }
            goto setIt;
       }     
       if (StrCompare(in,"bitsperchar")==0)
       {
       

            i=basc_integ_value(arg2,(double*)arg2_val);
            if(i==5) {s.flags &= 0xff3f;goto setIt;}
            if(i==6) {s.flags &= 0xff3f;s.flags |= 0x0040;goto setIt;}
            if(i==7) {s.flags &= 0xff3f;s.flags |= 0x0080;goto setIt;}
            if(i==8) {s.flags &= 0xff3f;s.flags |= 0x00c0;goto setIt;}
            
       }
       if (StrCompare(in,"ctstimeout")==0)
       {

            dbl=*((double*)arg2_val)*sysTicksPerSecond;
            
            s.ctsTimeout=dbl;
            goto setIt;
       }
       if (StrCompare(in,"dtwait")==0)
       {
            modemInfo.dtWaitSec=integ_value(arg2,(double*)arg2_val);
            err=0;
            goto processed;
       }
       if (StrCompare(in,"dcdwait")==0)
       {
            modemInfo.dcdWaitSec=integ_value(arg2,(double*)arg2_val);
            err=0;
            goto processed;
       }
       if (StrCompare(in,"dialtone")==0)
       {
            x=integ_value(arg2,(double*)arg2_val);
            if(x==0) modemInfo.pulse=true;
            else     modemInfo.pulse=false; 
            err=0;
            goto processed;
       }
       if (StrCompare(in,"handshake")==0)
       {
            modemInfo.hwHShake=integ_value(arg2,(double*)arg2_val);
            err=0;
            goto processed;
       }
       if (StrCompare(in,"autobaud")==0)
       {
            modemInfo.autoBaud=integ_value(arg2,(double*)arg2_val);
            err=0;
            goto processed;
       }
       if (StrCompare(in,"cmdtimeout")==0)
       {
            modemInfo.cmdTimeOut=integ_value(arg2,(double*)arg2_val);
            err=0;
            goto processed;
       }
       if (StrCompare(in,"volume")==0)
       {
            modemInfo.volume=integ_value(arg2,(double*)arg2_val);
            err=0;
            goto processed;
       }
       if (StrCompare(in,"buffersize")==0)
       {
            serialBufferSize=integ_value(arg2,(double*)arg2_val);
            if(serialBufferPtr) MemPtrFree(serialBufferPtr);
            //05282003 serialBufferPtr=MemHandleLock(MemHandleNew(serialBufferSize+1+32));
            if(serialBufferPtr==0) OutOfMemory(5001);    //05212003
            h=MemHandleNew(serialBufferSize+1+32);  //05282003
            if(h==0) OutOfMemory(6055);             //05282003
            serialBufferPtr=MemHandleLock(h);       //05282003
            
            SerSetReceiveBuffer(serRef,serialBufferPtr,serialBufferSize+1+32);
       
            err=0;
            goto processed;
       }
       if( StrCompare( in, "ir" ) == 0 )							//11.29.00 gh
       {															//11.29.00 gh
          z = integ_value( arg2, (double *)arg2_val );				//11.29.00 gh
          if( z == 0 )												//11.29.00 gh
             err = SerControl( serRef, serCtlIrDADisable, 0, 0 );	//11.29.00 gh
          else														//11.29.00 gh
             err = SerControl( serRef, serCtlIrDAEnable, 0, 0 );	//11.29.00 gh
          goto processed;											//11.29.00 gh
       }															//11.29.00 gh
       if (StrCompare(in,"portid")==0)
       {
            serRef=integ_value(arg2,(double*)arg2_val);       
            err=0;
            goto processed;
       }
       StrPrintF(debug,"Unrecognizable serial set parameter=%s",in);
       SysFatalAlert(debug);
       ErrThrow(-1);                 //inserted 05212003     
   
   return;
setIt:
    err=SerSetSettings( serRef,&s);       
processed:
    setSerErr(err);
    return;
}

/**************************************************************************************************/
void verb_serialSend()
{
    Err err;
    ULong bytes;
    ULong actBytes;
    char *pRcvBuf;
    int zz;
    int wkint;
    double d;
    VoidHand h;  //05282003
    
    
    bytes=long_integ_value(arg2,(double*)arg2_val);
    
//StrPrintF(debug,"sending %lu bytes =%s",bytes,arg1_val);
//SysFatalAlert(debug);    
    if(gOldSerialManager) SerReceiveFlush(serRef,0);  //flush any response bytes	//02.27.02 GH
    else SrmReceiveFlush(serRef,0);														//02.27.02 GH
    
    if(arg1->kind=='s')
    {
        //send a string
        if(gOldSerialManager) actBytes=SerSend(serRef, arg1_val, bytes, &err);		//02.27.02 GH
        else actBytes=SrmSend(serRef, arg1_val, bytes, &err);							//02.27.02 GH
    }
    else
    {
       //send an integer byte array (send only the low order byte of each integer)
       bytes=long_integ_value(arg2,(double*)arg2_val);
       if(bytes>(serialBufferSize))  bytes=serialBufferSize;  //limit to our work buf size(OS needs another 32 chars)
       if(bytes>arg1->max_no_values1) bytes=arg1->max_no_values1;  //limit to size of array
       //05282003 pRcvBuf=MemHandleLock(MemHandleNew(bytes+1));
       h=MemHandleNew(bytes+1);        //05282003
       if(h==0) OutOfMemory(6056);     //05282003
       pRcvBuf=MemHandleLock(h);       //05282003
            
       for(zz=0;zz<bytes;++zz)
       {
         d=*((double*)((char*)arg1+DELEN+zz*8));
         wkint=d;
//StrPrintF(debug,"sending char %d",wkint);
//SysFatalAlert(debug);  
         *((char*)pRcvBuf+zz)=*((char*)&wkint+1);
       }
//for(zz=0;zz<bytes;++zz)
//{
//StrPrintF(debug,"sending char %x",*((char*)pRcvBuf+zz));
//SysFatalAlert(debug); 
//}    
       if(gOldSerialManager) actBytes=SerSend(serRef,pRcvBuf, bytes, &err);			//02.27.02 GH
       else actBytes=SrmSend(serRef,pRcvBuf, bytes, &err);								//02.27.02 GH
       MemPtrFree(pRcvBuf);
    }
    
    if(gOldSerialManager) SerSendWait(serRef,bytes*SysTicksPerSecond()/300); //use lowest speed //02.27.02 GH
    else SrmSendWait(serRef);															//02.27.02 GH
//StrPrintF(debug,"actual=%lu  meant=%lu",actBytes,bytes);
//SysFatalAlert(debug);
    setSerErr(err);
    return;
}

/**************************************************************************************************/
void verb_serialReceive()
{
    Err err;
    double dbl;
    double theBytes;
    ULong actBytes;
    ULong bytes;
    Long timeout;
    int err1;
    int i;
    Err saveErr;
    char *pRcvBuf;
    int zz;
    int wkint;
    ULong saveBytes;
    VoidHand h;  //05282003

     //arguments are 1=buffer,2=#bytes,3=timeout
    bytes=long_integ_value(arg2,(double*)arg2_val);
    if(bytes>(serialBufferSize)) bytes=serialBufferSize;  //limit to our work buf size(OS needs another 32 chars)

    if(arg1->kind!='s')
    {
        //receive an integ byte array
        if(bytes>arg1->max_no_values1) bytes=arg1->max_no_values1;  //limit to size of array
//StrPrintF(debug,"trying to recv %lu bytes  maxOccurs=%d",bytes,arg1->max_no_values1);
//SysFatalAlert(debug);
    }
    
    dbl=*((double*)arg3_val)*sysTicksPerSecond;
    timeout=(long)dbl;
    //05282003 pRcvBuf=MemHandleLock(MemHandleNew(bytes+1)); 
    h=MemHandleNew(bytes+1);        //05282003
    if(h==0) OutOfMemory(6057);     //05282003
    pRcvBuf=MemHandleLock(h);       //05282003
            
    saveBytes=bytes;
    
    if(gSerialState==kSerialNoAsync)  
    {  	//************************** Normal serialReceive without events
retryReceive:
    //wait for entire response to arrive
    for( i=0;i<10; i++)
    {
	      //wait for max # of bytes. If the response is shorter, then timeout.
      bytes=saveBytes;
	      if(gOldSerialManager) err=SerReceiveWait(serRef, bytes, timeout);				 //02.27.02 GH
	      else err=SrmReceiveWait(serRef, bytes, timeout);				 //02.27.02 GH
	      
	      if( (err==0) || (err==serErrTimeOut)) break;   //normal case--all chars are in the receive queue or timeout received
	      else
	      {
	         if(err==serErrLineErr) 
	         {
	         	if(gOldSerialManager) SerReceiveFlush(serRef,SysTicksPerSecond()/50);	//02.27.02 GH
	         	else SrmReceiveFlush(serRef,SysTicksPerSecond()/50);	//02.27.02 GH
	         }   
      }   
    }
    saveErr=err;
    
getIt:
	    if(gOldSerialManager) err=SerReceiveCheck(serRef, &actBytes);					//02.27.02 GH
	    else err=SrmReceiveCheck(serRef, &actBytes);									//02.27.02 GH
	    
    if(actBytes>bytes) actBytes=bytes;  //limit to our req # chars
	    
	    if(gOldSerialManager) SerReceive(serRef, pRcvBuf, actBytes, 0, &err);			//02.27.02 GH
	    else SrmReceive(serRef, pRcvBuf, actBytes, 0, &err);						//02.27.02 GH
	    
    if(err==0) err=saveErr;   //may return timeout error
    setSerErr(err);
    }  	//*************************** End Normal serialReceive without events
    
    
    else if(gSerialState==kSerialDataWaiting)
    {  	//*************************** serial receive with events
    	actBytes=serialReceiveAfterEvent(pRcvBuf, bytes);
    	serialSetState(kSerialNoAsync);
    	setSerErr(0);
    }  	//*************************** End serialReceive with events
    else setSerErr(2); // shouldn't happen
    
    
    pRcvBuf[actBytes] =0x00;
    if(arg1->kind=='s') misc_stostr1(pRcvBuf);
    else
    {
//StrPrintF(debug,"read %lu chars",actBytes);
//SysFatalAlert(debug);
        for (zz=0;zz<actBytes;++zz)
        {
            *((char*)(&wkint))=0x00;
            *((char*)(&wkint)+1)=*((char*)pRcvBuf+zz);
            restore_integ_value(wkint,arg1,(double*)arg1_val,zz,0,0);
        }
        theBytes=actBytes;
        //06012002if( arg2->isConstant!=0x01) misc_stodbl2(&theBytes);  //can only do if not a constant
        if( arg2->flags3 & 0x01)  ;          //is  it a constant                      //06012002
        else misc_stodbl2(&theBytes);  //can only do if not a constant  //06012002
    }   
    MemPtrFree(pRcvBuf);
}

void verb_serialDial()
{
    int err;
    err=MdmDial(&modemInfo, NULL,arg2_val,arg1_val);
    setSerErr(err);    
}
/**************************************************************************************************/
void verb_serialHangUp()
{
   int err;
   err=MdmHangUp(&modemInfo);
   setSerErr(err);
}

/**************************************************************************************************/
void verb_serialReceiveWithEvent()	//03.06.02 GH
{
  Err err;
  if(gSerialState!=kSerialNoAsync)
  {
  	setSerErr(2);  //state error - call issued while receive in progress
  	return;
  }
  if (gOldSerialManager) 
  {
	err=SerSetWakeupHandler(serRef, serialWakeupHandler, (UInt32) &gSerialState);
  	err=SerPrimeWakeupHandler(serRef, 1);
  }
  else 
  {
	err=SrmSetWakeupHandler(serRef, (WakeupHandlerProcPtr)serialWakeupHandler, (UInt32) &gSerialState);
  	err=SrmPrimeWakeupHandler(serRef, 1);
  }
  setSerErr(err);
}

/**************************************************************************************************/
void serialWakeupHandler(UInt32 refCon)	//03.06.02 GH
{
	Boolean *serialStatePtr = (UInt8 *) refCon;
//dbug("serialWakeupHandler");
	*serialStatePtr = kSerialWaitingForData;
//	EvtEnqueueKey('S', 1, commandKeyMask);  //2004.10.06 GWH magic values used in keyDownEvent
	EvtWakeup();
}

/**************************************************************************************************/
ULong serialReceiveAfterEvent(Char *outBuf, UInt32 outSize)	//03.06.02 GH
{
	Err	err;
	UInt8	*bytePtr;
	UInt32	size;
	ULong	totalAmtRead = 0;
//StrPrintF(debug,"serialRecieveAfterEvent Char=%d",outSize);
//SysFatalAlert(debug);
	
	serialSetState(kSerialReadingData);
	do {
		err = DoReceiveWindowOpen(serRef, &bytePtr, &size);
		if (err == 0) {
			UInt32 amtToMove = size;
			
			if (amtToMove > outSize)
				amtToMove = outSize;
			MemMove(outBuf, bytePtr, amtToMove);
			outBuf += amtToMove;
			outSize -= amtToMove;
			totalAmtRead += amtToMove;
			DoReceiveWindowClose(serRef, size);
		}
	} while (err == 0 && size > 0);
	return totalAmtRead;
}

/**************************************************************************************************/
void serialSetState(UInt8 state)	//03.06.02 GH
{
//StrPrintF(debug,"Setting serial state to %hu ",state);
//SysFatalAlert(debug);
	gSerialState=state;
	return;
}

/**************************************************************************************************/
static Err DoReceiveWindowOpen(UInt16 portId, UInt8 **bufPP, UInt32 *sizeP)
{
	if (gOldSerialManager)
		return SerReceiveWindowOpen(portId, bufPP, sizeP);
	else
		return SrmReceiveWindowOpen(portId, bufPP, sizeP);
}

/******************************************************************************/
static Err DoReceiveWindowClose(UInt16 portId, UInt32 bytesPulled)
{
	if (gOldSerialManager)
		return SerReceiveWindowClose(portId, bytesPulled);
	else
		return SrmReceiveWindowClose(portId, bytesPulled);
}

/**************************************************************************************************/
void setSerErr(Err err)
{
   double d;
   d=err;
   store4(&d);
}

/**************************************************************************************************/
struct ObjectData * locateObjectPtr(Word id)
{
   
   struct ViewData * viewPtr;
   VoidPtr objectsPtr;
   struct ObjectData * thisObjPtr;
   int j;
   int i;
   
   
  
   for(i=0;i<view_cnt;++i)
   {
       viewPtr=(struct ViewData*)((char*)viewElemsPtr+i*sizeof(viewExample));  //point to this view's data 
       if(viewPtr->cnt==0) goto skipView;    //added 5.24.2000
       
       objectsPtr=viewPtr->objectsPtr;
       for(j=0;j<viewPtr->cnt;++j)
       {
          thisObjPtr=(struct ObjectData*)((char*)objectsPtr+j*sizeof(objectExample));  //point to this object's data
          if(thisObjPtr->id==id)
          {
             saveObjectHandle=viewPtr->objectsHand; //save handle to unlock later after thru with thisObjPtr
             goto foundIt;
          }
       }
                
skipView:                                        //added 5.24.2000
       ;                                         //added 5.24.2000     
   }
   //should not fall thru
foundIt:
   
   return(thisObjPtr);
}

/**************************************************************************************************/
void FreeListValues(VoidPtr pold,int noItems )
{
      
    
      VoidPtr p;
      
      int i;
//dbug("in freeListValues");
      
      if(pold==0) return;
      //if( MemHandleOwner( MemPtrRecoverHandle(pold))==0) return;  //system owns it
      for(i=0;i<noItems;++i)
      {
//StrPrintF(debug,"freeing a string #=%d  this=%d",noItems,i);
//SysFatalAlert(debug);
         p=*((VoidPtr*)( (char*)pold+4*i));
         
//StrPrintF(debug,"freeing list element=%s   of length=%d",p,StrLen(p));
//SysFatalAlert(debug);         
         if(  p!=0) 
         {
             if(StrLen(p)==0) return;  //avoid mem problems --just exit
             MiscPtrFree( p);  //free one string
         }     

      }
//dbug("freeing the list ptr");
      
       MiscPtrFree(pold);   //and free the pointer list
}
/**************************************************************************************************/
//#ifdef ORG_SWB
void verb_setnumvarsfromheap()   //added 06102002
{
   find_arg_1();
   maxVarsInDynamHeap=integ_value(arg1,(double*)arg1_val);
}
//#endif

/**************************************************************************************************/
void verb_clearscreentextfields()   //added 06102002  
{
    //sets all fields in the form to empty strings
    UInt ID;
  
   
   VoidPtr frmPtr;
   struct ViewData * viewPtr;
   VoidPtr objectsPtr;
   struct ObjectData * thisObjPtr;
   int j;
   int i;
   int n;
   char empty[]="";
      
    ID=find_integer();
    frmPtr=FrmGetFormPtr(ID);
//StrPrintF(debug,"clearTextFields for id=%d   viewCnt=%d",ID,view_cnt);
//dbug(debug);
   for(i=0;i<view_cnt;++i)
   {
     viewPtr=(struct ViewData*)((char*)viewElemsPtr+i*sizeof(viewExample));  //point to this view's data 
     if(viewPtr->cnt==0) goto noObjs;
     if(viewPtr->id==ID)
     {
//StrPrintF(debug,"found viewptr  cnt=%d",viewPtr->cnt);
//dbug(debug);
       objectsPtr=viewPtr->objectsPtr;
       for(j=0;j<viewPtr->cnt;++j)
       {
//dbug("object");
          thisObjPtr=(struct ObjectData*)((char*)objectsPtr+j*sizeof(objectExample));  //point to this object's data
          //if(thisObjPtr->dataPtr!=0)
          //{
//StrPrintF(debug,"objtype=%d",thisObjPtr->type);
//dbug(debug);
              switch(thisObjPtr->type)
              {
                  case frmFieldObj:

                    
                    //p=MiscHandleLock((VoidHand)(thisObjPtr->dataPtr));                                           
//StrPrintF(debug,"setting fields fld=%d ",thisObjPtr->id);
//SysFatalAlert(debug);
                    //SetFieldText(thisObjPtr->id,empty,FldGetMaxChars((FieldPtr)(FrmGetObjectPtr(frmPtr,j)))+1,true);
                    //MiscPtrUnlock(p);                                                                              
                    for(n=0;n<FrmGetNumberOfObjects((FormType*)frmPtr);++n)
      				{
//StrPrintF(debug,"compare j=%d ctl=%d obj=%d",j,controlid,FrmGetObjectId(frmPtr,j)   );
//SysFatalAlert(debug);
                
        				if( FrmGetObjectId((FormType*)frmPtr,n)==thisObjPtr->id)
        				{
          					controlPtr=FrmGetObjectPtr((FormType*)frmPtr,n);
          					controlid=FrmGetObjectId((FormType*)frmPtr,n);
          					goto foundId;
        				}
      				}
foundId:
      				commonSetFieldTextRoutine((FieldPtr)controlPtr,controlid,empty);
                    break;
	              case frmControlObj:
                  case frmListObj:
                  case frmLabelObj:
	              case frmLineObj:
	              case frmRectangleObj:
	              case frmBitmapObj:
	              case frmTableObj:
	              case frmTitleObj:
	              case frmPopupObj:
	              case frmGraffitiStateObj:
	              case frmGadgetObj:
	              case frmScrollBarObj:
	                     
                  default:
                          break;     
              }
          //}
dontDoIt:
         ;
       }
       
       goto endTheLoop;  //only process the one matching form
     }
noObjs:
     ;
   }
endTheLoop:
   ;
}
/**************************************************************************************************/

void commonSetScrollbar(char c,FormPtr frmPtr, struct dataelem*arg, double* arg_val)
{
  
  int res;
  SWord val;
  SWord min;
  SWord max;
  SWord pag;
  res=basc_integ_value(arg,(double*)arg_val);
  SclGetScrollBar((ScrollBarPtr)controlPtr,&val,&min,&max,&pag);
  if (c==0x01)      val=res;
  else if (c==0x02) min=res;
  else if (c==0x03) max=res;
  else if (c==0x04) pag=res;  
    
  SclSetScrollBar((ScrollBarPtr)controlPtr,val,min,max,pag);
  if(FrmGetActiveForm()==frmPtr)  SclDrawScrollBar( (ScrollBarPtr)controlPtr );  
}
/**************************************************************************************************/
void verb_setscrollbar()
{
  int res;
  char c;
  c=find_char();
  find_ctlid(true);
  find_arg_2(); //value
  commonSetScrollbar(c,FrmGetActiveForm(),arg2,(double*)arg2_val);
}
/**************************************************************************************************/

void commonSetMaxChars( struct dataelem*arg, double* arg_val)
{
    FldSetMaxChars((FieldType*)controlPtr,basc_integ_value( arg,arg_val));
}
/**************************************************************************************************/
void verb_fieldsetmaxchars()
{
  
  find_ctlid(true);
  find_arg_2(); //#chars
  
  commonSetMaxChars(arg2,(double*)arg2_val);
}
/**************************************************************************************************/
void commonSetSelected( FormPtr frm,ControlPtr controlPtr,int controlType, int where)
{
  int res;
  int i;
  
  ControlPtr popupObjPtr;
  struct ObjectData *objectPtr;
  VoidHand h;
  VoidPtr p;
  //res=basc_integ_value(arg2,(double*)arg2_val)-1;
  res=where-1;if(res<(-1))res=-1;
  LstSetSelection((ListPtr)controlPtr,res);
  
  for(i=0;i<FrmGetNumberOfObjects(frm);++i)
  {
      if( FrmGetObjectType(frm, i)==frmControlObj)
      {
          popupObjPtr=FrmGetObjectPtr(frm,i);
          if (CtlGlueGetControlStyle(popupObjPtr)==3)
          {
              //the assoc popup will have an id = one less than the listbox
              //if(popupObjPtr->id==(((ListPtr)controlPtr)->id-1))  goto gotTheAssocPopup;  //found the associated popup for this list ctl
              //if(FrmGetObjectId(frm,i)==FrmGetObjectId(frm,FrmGetObjectIndexFromPtr(frm,(ListPtr)controlPtr))-1)  //GHGlue
              if(FrmGetObjectId(frm,i)==miscFrmGetObjectIdFromPtr(frm,(ListPtr)controlPtr)-1)  //GHGlue
              	goto gotTheAssocPopup;  //found the associated popup for this list ctl
          }
      }
  }
  //there isn't a popup so its a real listBox control
  
  if(frm==FrmGetActiveForm()) LstDrawList ((ListPtr)controlPtr);  //1120
  return;

gotTheAssocPopup:
  //set the popup's label and redraw it
  if( res==(-1))
  {
     h=MiscHandleNew(1,"lab");
     p=MiscHandleLock(h);
     *((char*)p)=0x00;
     CtlSetLabel((ControlPtr)popupObjPtr,p); 
  }
  else
  {
     h=MiscHandleNew(StrLen(LstGetSelectionText((ListPtr)controlPtr,res))+1,"lab");
     p=MiscHandleLock(h);
     StrCopy((char*)p,LstGetSelectionText((ListPtr)controlPtr,res));
     CtlSetLabel((ControlPtr)popupObjPtr,p);
  }
  
  //objectPtr=locateObjectPtr(popupObjPtr->id);
  //objectPtr=locateObjectPtr(FrmGetObjectId(frm,FrmGetObjectIndexFromPtr(frm,(ListPtr)popupObjPtr)));  //GHGlue
  objectPtr=locateObjectPtr(miscFrmGetObjectIdFromPtr(frm,(ListPtr)popupObjPtr));  //GHGlue
  if(objectPtr->dataPtr!=0)
  {
      MiscPtrFree(objectPtr->dataPtr);   
      
  }
  objectPtr->dataPtr=p;
  
  if(frm==FrmGetActiveForm()) CtlDrawControl((ControlPtr)popupObjPtr);  
  
}
/**************************************************************************************************/

void verb_listsetselected()
{
  int res;
  FormPtr frm;
  
  find_ctlid(true);
  find_arg_2(); //where
  frm=FrmGetActiveForm();
  commonSetSelected(frm,controlPtr,frmListObj,basc_integ_value(arg2,(double*)arg2_val));
  
  
}

/**************************************************************************************************/
 void commonSetText(FormPtr frmPtr,int controlType, char*text)
 {
  struct ObjectData * objectPtr;
  VoidHand h;
  VoidPtr p;
 
  RectangleType r; 
  FontID curFont;
  VoidPtr oldPtr;
  RectangleType r1;  //GHGlue
  
   
  
  Word idx;              //added 5.20.2000  
 
  VoidHand oldHand;
  int res;
  int i;
  //FormPtr frmPtr;        //added 5.20.2000
   if(controlType==frmControlObj)
   {
      goto itsAControl;
   }
   if(controlType==frmLabelObj)
   {
//dbug("yes--its a label");
      goto itsALabel;
   }
   if(controlType==frmFieldObj)
   {
      goto itsAField;
   }
   return;
itsAControl:   
   h=MiscHandleNew(StrLen(text)+1,"setLab");
  p=MiscHandleLock(h);
  StrCopy((char*)p,text);

//StrPrintF(debug,"setting label now to %s",text);
//SysFatalAlert(debug);
  
  oldPtr=(VoidPtr)CtlGetLabel((ControlType*)controlPtr);   //5.10.2000
  CtlSetLabel((ControlType*)controlPtr,(char*)p);
  
  objectPtr=locateObjectPtr(controlid);
  if( objectPtr->dataPtr!=0)
  {
     MiscPtrFree(objectPtr->dataPtr);
  }
  objectPtr->dataPtr=p; 
  
  
  
  CtlDrawControl ((ControlType*)controlPtr);

  return ;
itsALabel:
  //treat label ctls differently
  //the rule is that a label control cannot have its string length exceeded
  //also, you have to erase the labels bounded area to get rid of old label
  //curFont = FntSetFont(((FormLabelType*)controlPtr)->fontID); //GHGlue
  curFont = FntSetFont(FrmGlueGetLabelFont(FrmGetActiveForm(), controlid)); //GHGlue
  
  
  FrmGetObjectBounds(frmPtr, FrmGetObjectIndex(frmPtr,controlid), &r1);

  RctSetRectangle(&r,r1.topLeft.x,
                     r1.topLeft.y,
                     FntCharsWidth(FrmGetLabel(frmPtr, controlid),
                            StrLen(FrmGetLabel(frmPtr, controlid))),
                     FntCharHeight());
  WinEraseRectangle(&r,0);
  FntSetFont(curFont);
 
  h=MiscHandleNew(StrLen(FrmGetLabel(frmPtr,controlid))+1,"setLab2");
  p=MiscHandleLock(h);
  MemSet(p,MemPtrSize(p)-1,0x20);  //set to spaces
  MemSet((char*)p+MemPtrSize(p)-1,1,0x00);
  if( StrLen(text)<MemPtrSize(p))  MemMove(p,text,StrLen(text));
  else                                 MemMove(p,text,MemPtrSize(p)-1);


//StrPrintF(debug,"newstring=%s  len=%d",p,StrLen(p));
//SysFatalAlert(debug);

  FrmCopyLabel( frmPtr,controlid, (char*)p);

  objectPtr=locateObjectPtr(controlid);
  if( objectPtr->dataPtr!=0)
  {
     MiscPtrFree(objectPtr->dataPtr);
  }
  objectPtr->dataPtr=p; 
  return;
itsAField:
   commonSetFieldTextRoutine(controlPtr,controlid,text);
/*  oldHand=FldGetTextHandle((FieldPtr)controlPtr);  //get handle to the field's current content
  
  i=StrLen(text)+1;
  h=MiscHandleNew(i,"setTxt");  //get new memory for the fld text
  p=MiscHandleLock(h);          //and lock a pointer to it
  StrCopy((char*)p,text);   //and copy text into new area
  
  
  
  //now go change the field's text but don't redraw                          //added 5.31.2000
  //temp SetFieldText(controlid, p, FldGetMaxChars((FieldPtr)controlPtr)+1,false);  //added 5.31.2000

  MiscPtrUnlock(p);           // and unlock the new text pointer
  FldSetTextHandle((FieldPtr)controlPtr,(Handle)h);  //temp
  
  if(oldHand) MemHandleFree(oldHand);  //6.1.2000
  
  FldDrawField ((FieldPtr)controlPtr);

  //frmPtr= FrmGetActiveForm();                                                 //added 5.20.2000
  //see if any attached scrollbars that need updated                          //added 5.20.2000
  idx=FrmGetObjectIndex(frmPtr,controlid);               //added 5.20.2000
  if( idx<FrmGetNumberOfObjects(frmPtr)-1)                                    //added 5.20.2000
  {                                                                           //added 5.20.2000
    if(FrmGetObjectType(frmPtr, idx+1)==frmScrollBarObj)                      //added 5.20.2000
    {                                                                         //added 5.20.2000 
       //have an attached scrollbar                                           //added 5.20.2000
       
//SysFatalAlert("updating scrollbar");
       UpdateScrollbar((FieldPtr)controlPtr                      ,            //added 5.20.2000
                      (ScrollBarPtr )(FrmGetObjectPtr(frmPtr, idx+1)));       //added 5.20.2000
    }                                                                         //added 5.20.2000
  }                                                                           //added 5.20.2000
*/   
  
  
}

/**************************************************************************************************/
/*
//void verb_controlssettext()
//{
//   //sets the text of a screen control given its position on the current form
//   
//  int controlType;
//  int pos;
//  FormPtr frmPtr;        //added 5.20.2000 
//dbug("in set text");   
//   find_arg_2();      //position of control
//   find_arg_1();       //text to set
//   
//   pos = integ_value( arg2, (double *)arg2_val ); 
/   frmPtr=FrmGetActiveForm();
   if(pos>FrmGetNumberOfObjects(frmPtr)-1)
   {
       SysFatalAlert("Control position too high.");
   }
   
   controlPtr=((ControlType*)FrmGetObjectPtr(frmPtr,pos));
   controlid=FrmGetObjectId(frmPtr,pos);
   controlType=FrmGetObjectType(frmPtr,pos);
   commonSetText(controlType, text);
 }  
 */
/**************************************************************************************************/
 void verb_controlsetlabel()  //also controlsettext
{
  struct ObjectData * objectPtr;
  VoidHand h;
  VoidPtr p;
  char ctlType;
  int controlType;
  RectangleType r; 
  FontID curFont;
  VoidPtr oldPtr;
  RectangleType r1;  //GHGlue
  int pos;
  FormPtr frmPtr;
  
  
  find_ctlid(true);
//StrPrintF(debug,"at ctlsetlabel id=%d",controlid);
//SysFatalAlert(debug);
  find_arg_1();
  ctlType=find_char();
  frmPtr=FrmGetActiveForm();
  pos=FrmGetObjectIndex(frmPtr,controlid);
  controlType=FrmGetObjectType(frmPtr,pos);
  
  
      //if( ctlType=='l') controlType=??;  //label
      //if( ctlType=='l') controlType=??;  //
  commonSetText(frmPtr,controlType,arg1_val);
  
/*  if( ctlType=='l' ) goto itsALabel;
  h=MiscHandleNew(StrLen(arg1_val)+1,"setLab");
  p=MiscHandleLock(h);
  StrCopy((char*)p,arg1_val);

//StrPrintF(debug,"setting label now to %s",arg1_val);
//SysFatalAlert(debug);
  
  oldPtr=(VoidPtr)CtlGetLabel((ControlType*)controlPtr);   //5.10.2000
  CtlSetLabel((ControlType*)controlPtr,(char*)p);
  
  objectPtr=locateObjectPtr(controlid);
  if( objectPtr->dataPtr!=0)
  {
     MiscPtrFree(objectPtr->dataPtr);
  }
  objectPtr->dataPtr=p; 
  
  
  
  CtlDrawControl ((ControlType*)controlPtr);

  return ;
itsALabel:
  //treat label ctls differently
  //the rule is that a label control cannot have its string length exceeded
  //also, you have to erase the labels bounded area to get rid of old label
  //curFont = FntSetFont(((FormLabelType*)controlPtr)->fontID); //GHGlue
  curFont = FntSetFont(FrmGlueGetLabelFont(FrmGetActiveForm(), controlid)); //GHGlue
  
  
  FrmGetObjectBounds(FrmGetActiveForm(), FrmGetObjectIndex(FrmGetActiveForm(),controlid), &r1);

  RctSetRectangle(&r,r1.topLeft.x,
                     r1.topLeft.y,
                     FntCharsWidth(FrmGetLabel(FrmGetActiveForm(), controlid),
                            StrLen(FrmGetLabel(FrmGetActiveForm(), controlid))),
                     FntCharHeight());
  WinEraseRectangle(&r,0);
  FntSetFont(curFont);
 
  h=MiscHandleNew(StrLen(FrmGetLabel(FrmGetActiveForm(),controlid))+1,"setLab2");
  p=MiscHandleLock(h);
  MemSet(p,MemPtrSize(p)-1,0x20);  //set to spaces
  MemSet((char*)p+MemPtrSize(p)-1,1,0x00);
  if( StrLen(arg1_val)<MemPtrSize(p))  MemMove(p,arg1_val,StrLen(arg1_val));
  else                                 MemMove(p,arg1_val,MemPtrSize(p)-1);


//StrPrintF(debug,"newstring=%s  len=%d",p,StrLen(p));
//SysFatalAlert(debug);

  FrmCopyLabel( FrmGetActiveForm(),controlid, (char*)p);

  objectPtr=locateObjectPtr(controlid);
  if( objectPtr->dataPtr!=0)
  {
     MiscPtrFree(objectPtr->dataPtr);
  }
  objectPtr->dataPtr=p; 
  
*/  

  
}
/**************************************************************************************************/
void commonSetStatus(FormPtr frmPtr,int controlType, int stat)
{
    CtlSetValue((ControlType*)controlPtr,stat);
    if(frmPtr==FrmGetActiveForm()) CtlDrawControl ((ControlType*)controlPtr);
}
/**************************************************************************************************/
void verb_controlsetstatus()
{
  int res;
  find_ctlid(true);
  res=find_integer();
  commonSetStatus(FrmGetActiveForm(),frmControlObj,res);
}
/**************************************************************************************************/

void verb_controlsetstatusNew()
{
  //same as regular verb_controlsetstatus except a varname is used
  int res;
  find_ctlid(true);
  find_arg_1();
  res=basc_integ_value( arg1,(double*)arg1_val);
  commonSetStatus(FrmGetActiveForm(),frmControlObj,res);
}

/**************************************************************************************************/
/*void verb_controlssetstatus()
{
   //sets the text of a screen control given its position on the current form
   
  int controlType;
  int pos;
  int res;
  FormPtr frmPtr;        //added 5.20.2000 
//dbug("in set text");   
   find_arg_2();      //position of control
   res=find_Integer();       //status
   
   pos = integ_value( arg2, (double *)arg2_val ); 
   frmPtr=FrmGetActiveForm();
   if(pos>FrmGetNumberOfObjects(frmPtr)-1)
   {
       SysFatalAlert("Control position too high.");
   }
   
   controlPtr=((ControlType*)FrmGetObjectPtr(frmPtr,pos));
   controlid=FrmGetObjectId(frmPtr,pos);
   controlType=FrmGetObjectType(frmPtr,pos);
   if(controlType != frmControlObj) return;
   
   commonSetStatus(res);
 }
 */  
/**************************************************************************************************/

/**************************************************************************************************/
void commonErrorWrongType(char *typ)
{
    char msg[256];
    StrPrintF(msg,"Wrong type of variable used in call to set property for '%s'",typ);
    SysFatalAlert(msg);
    ErrThrow(-1);                 //inserted 05212003 
}
/**************************************************************************************************/
void commonErrorWrongTypeOnGet(char *typ)
{
    char msg[256];
    StrPrintF(msg,"Wrong type of variable used in call to get property for '%s'",typ);
    SysFatalAlert(msg);
    ErrThrow(-1);                 //inserted 05212003 
}
/**************************************************************************************************/
commonErrorWrongCtltype(char * propName,int controlType)
{
  char msg[256];
  StrPrintF(msg,"Cannot set property (%s) on control type %d",propName,controlType);
  SysFatalAlert(msg);
  ErrThrow(-1);                 //inserted 05212003 
}
/**************************************************************************************************/
commonErrorWrongCtltypeOnGet(char * propName,int controlType)
{
  char msg[256];
  StrPrintF(msg,"Cannot get property (%s) on control type %d",propName,controlType);
  SysFatalAlert(msg);
  ErrThrow(-1);                 //inserted 05212003 
}
/**************************************************************************************************/
FormPtr  findFormTheControlIsOn(int ctlid)
{
    Word j;
    Word i;
    int new_x,new_y;
    struct ViewData * viewPtr;  
    FormPtr frmPtr;
    for(j=0;j<view_cnt;++j)
    {
       viewPtr=(struct ViewData*)((char*)viewElemsPtr+j*sizeof(viewExample));  //point to this view's data
       frmPtr=FrmGetFormPtr(viewPtr->id);
/*---
StrPrintF(debug,"looking for obj ident %lf %d",*arg1_ad,the_one);
test_debug(debug);
----*/
       for(i=0;i<FrmGetNumberOfObjects(frmPtr);++i)
       {
//StrPrintF(debug,"comparing ids 1=%d 2=%d",FrmGetObjectId(frmPtr,i),ctlid);
//dbug(debug);
         if(FrmGetObjectId(frmPtr,i) != ctlid ) continue;
         return(frmPtr);
         
      }
   }
   return(0);
      
}
/**************************************************************************************************/
int findControlsPositionOnForm(FormPtr * frmPtr,char * controlname)
{
    
    int cnt;
    int i;
    int j;
    char*ad;
    char *p2;
    VoidHand h2;
    char name[256];
    unsigned int ID;
    //find_arg_1();   //name of control
//StrPrintF(debug,"ctlname to search for=%s",arg1_val);
//dbug(debug);
	//frmPtr=FrmGetActiveForm();
	
    int new_x,new_y;
    struct ViewData * viewPtr;  
    
    for(j=0;j<view_cnt;++j)
    {
       viewPtr=(struct ViewData*)((char*)viewElemsPtr+j*sizeof(viewExample));  //point to this view's data
       *frmPtr=FrmGetFormPtr(viewPtr->id);
       
    
    
	    h2=MiscDmGetResource('olst',viewPtr->id,"olst");  //read the forms object list of names
	    if(h2==0)
	    {
	       goto cantFindCtl;
	    }
	    p2=MiscHandleLock(h2);

	    cnt=basc_dbGetInt( (char*)p2);  //get id of view from the vtoc record
	    p2+=2;   //06102002
	//StrPrintF(debug,"ctl cnt=%d",cnt);
	//dbug(debug);
	    for(i=0;i<cnt;++i)  //for each object
	    {
	            ad=&name[0];
	   			//read object name	//06102002
				while(1)				//06102002
	   			{						//06102002
	   				*ad=*p2;			//06102002
	   				if((*p2)==0x00) break; //06102002
	   				++ad;				//06102002
	   				++p2;				//06102002
	   				
	  			}						//06102002
	  	  								//06102002
	  	  							//06102002
//StrPrintF(debug,"comparing ctlname from record=%s to search=%s",name,arg1_val);
//dbug(debug);      
	     
	      if(StrCaselessCompare(name,controlname)==0)
	      {
	          goto matchedName;
	      } 
	      
	//dbug("loading form   in vtoc processing:");
	         ++p2;  //skip over null 
	   }
	   //12182002goto cantFindCtl;
	    MemHandleUnlock(h2);      //added 01262003
	    DmReleaseResource(h2);    //added 01262003
	    goto nextView;     //added 12182002
matchedName:

	//dbug("name matched");
	    MemHandleUnlock(h2);      
	    DmReleaseResource(h2);
	//dbug("setting result");
	    if (FrmGetTitle(*frmPtr) != 0) return(i+1); //must return 1 higher if form has a title
	    else                  return(i);  //return the control's position
nextView:  ;              //added 12182002   
   }
cantFindCtl:
  StrPrintF(debug,"Illegal object name used = %s",controlname);
  SysFatalAlert(debug);
  ErrThrow(-1);                 //inserted 05212003   	    
}
/**************************************************************************************************/
void verb_setGeneralProperty()
{
  UInt16 minValue;  //added 04012005
  UInt16 maxValue;  //added 04012005
  UInt16 pageSize;  //added 04012005
  UInt16 curValue;  //added 04012005
  ControlStyleType type;  //added 04012005 
                                           
  struct ObjectData *obj;         //07052005
                                           int controlType;
  int pos;
  char c;
  int propId;
  Boolean found;
  RectangleType bounds;  //added 04012005
  
  FormPtr frmPtr;        //added 5.20.2000 
//dbug("in set text");   
   c=find_char();   //type of control identifier
   switch(c)
   {
      case 'i':  //ctlid
        found=find_ctlid(true);
        //if(found==false) return;  //probably a bitmap that can't use by id
        frmPtr=findFormTheControlIsOn(controlid);
        pos=FrmGetObjectIndex(frmPtr,controlid);
        break;
      case 'v':  //variable containing name
        find_arg_2();      //variable containing name
        frmPtr=FrmGetActiveForm();
        pos=findControlsPositionOnForm(&frmPtr,arg2_val);
//StrPrintF(debug,"name=%s posOnForm=%d",arg2_val,pos);
//dbug(debug);
        goto havePosition;
        break;
      case 'p':  //position of ctl on form
        find_arg_2();      //position of control on form
        pos = integ_value( arg2, (double *)arg2_val ); 
        frmPtr=FrmGetActiveForm();
havePosition:
        
	    if(pos>FrmGetNumberOfObjects(frmPtr)-1)
	    {
	       SysFatalAlert("Control position too high.");
	       ErrThrow(-1);                 //inserted 05212003
	    }
	   
	    controlPtr=((ControlType*)FrmGetObjectPtr(frmPtr,pos));
	    controlid=FrmGetObjectId(frmPtr,pos);
	    break;
   }
   obj= locateObjectPtr(controlid);   //07052005
   controlType=FrmGetObjectType(frmPtr,pos);
   propId=find_integer();          //property type identifier #
   find_arg_3();          //new property value to assign
   switch(propId)
   {
       case 0:  //text
//StrPrintF(debug,"set text  type=%d  text=%s",controlType,arg3_val);
//dbug(debug);
          //09242003 if( (controlType!=frmControlObj)&&(controlType!=frmFieldObj)&&(controlType!=frmLabelObj))commonErrorWrongCtltype("text",controlType);
          if( (controlType!=frmControlObj)&&(controlType!=frmFieldObj)   //added 09242003
          &&(controlType!=frmLabelObj)&&(controlType!=frmTableObj))      //added 09242003 
              commonErrorWrongCtltype("text",controlType);               //added 09242003
          else
          {
            if(arg3->kind == 's')
            {
//dbug("going to commonsettext");
               if(controlType!=frmTableObj)                        //added 09242003
               commonSetText( frmPtr,controlType, arg3_val);
               else  gridSetSelectedText(   frmPtr,controlPtr, arg3_val); //added 09242003       
            }
            else commonErrorWrongType("text");
          }
          break; 
       case 1:  //status
          if(controlType  != frmControlObj) commonErrorWrongCtltype("status",controlType);
          else
          {
            if(arg3->kind != 's') commonSetStatus( frmPtr,controlType, basc_integ_value( arg3,(double*)arg3_val));
            else commonErrorWrongType("status");
	      }
	      break; 
       case 2:  //selected
          if( (controlType!=frmListObj)&&(controlType!=frmControlObj))commonErrorWrongCtltype("selectd",controlType);
          else
          {
            if(arg3->kind != 's')
            {
                if (controlType==frmListObj) commonSetSelected( frmPtr,controlPtr,controlType, basc_integ_value(arg3,(double*)arg3_val));       
                else
                {
                     //must point to list part of popup
                     controlPtr=((ControlType*)FrmGetObjectPtr(frmPtr,pos+1));
	                 controlid=FrmGetObjectId(frmPtr,pos+1);
                     commonSetSelected( frmPtr,controlPtr,controlType, basc_integ_value(arg3,(double*)arg3_val));
                }     
            }    
            else commonErrorWrongType("selected");
          }
          break;
       case 3:  //maxChars
          if(controlType  != frmFieldObj) commonErrorWrongCtltype("maxChars",controlType);
          else
          {
            if(arg3->kind != 's') commonSetMaxChars(arg3,(double*)arg3_val );
            else commonErrorWrongType("maxChars");
          }
          break;
       case 4:  //current
       case 94:        //added 07062005  must allow both 4 and 94
           //modified 04012005
          
           //07122005 type = CtlGlueGetControlStyle((ControlType*)(controlPtr)); 
           //07122005 if  ((controlType==frmControlObj)&&((type==sliderCtl) || (type==feedbackSliderCtl) ))   //added 09242003
           //07122005 {
           //07122005     //it's a slider ctl
           //07122005     if(arg3->kind != 's')
           //07122005     {
           //07122005        CtlGetSliderValues ((ControlType*)(controlPtr),
           //07122005                                 &minValue, &maxValue,
           //07122005                                 &pageSize, &curValue); 
           //07122005        curValue =  basc_integ_value(arg3,(double*)arg3_val);
           //07122005        CtlSetSliderValues ((ControlType*)(controlPtr),
           //07122005                                 &minValue, &maxValue,
           //07122005                                 &pageSize, &curValue);
		   //07122005 	   }
           //07122005     else commonErrorWrongType("curValue");
           //07122005  
           //07122005 }
           //07122005 else
           //07122005 {
          		if(controlType  != frmScrollBarObj) commonErrorWrongCtltype("current",controlType);
          		else
         		{
            		if(arg3->kind != 's') commonSetScrollbar(0x01,frmPtr,arg3,(double*)arg3_val);
            		else commonErrorWrongType("current");
          		}
          //07122005 }
          break; 
       case 5:  //min
       case 95:        //added 07062005  must allow both 5 and 95             
//Trace("in set min");            
           //08292005 type = CtlGlueGetControlStyle((ControlType*)(controlPtr)); 
           if  ((controlType==frmControlObj)&&((CtlGlueGetControlStyle((ControlType*)(controlPtr))==sliderCtl) || (CtlGlueGetControlStyle((ControlType*)(controlPtr))==feedbackSliderCtl) ))   //added 09242003
           {
//Trace("setting min");
               //it's a slider ctl
               if(arg3->kind != 's')
               {
                  CtlGetSliderValues ((ControlType*)(controlPtr),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue); 
                  minValue =  basc_integ_value(arg3,(double*)arg3_val);
                  CtlSetSliderValues ((ControlType*)(controlPtr),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue);
			   }
               else commonErrorWrongType("minValue");
            
          }
          else
          {
          	  if(controlType  != frmScrollBarObj ) commonErrorWrongCtltype("min",controlType);
          	  else
              {
                 if(arg3->kind != 's') commonSetScrollbar(0x02,frmPtr,arg3,(double*)arg3_val);
                 else commonErrorWrongType("min");
              }
          }
          break; 
       case 6:  //max                  //modified 07062005
       case 96:        //added 07062005  must allow both 6 and 96
            
           //08292005 type = CtlGlueGetControlStyle((ControlType*)(controlPtr)); 
           if  ((controlType==frmControlObj)&&((CtlGlueGetControlStyle((ControlType*)(controlPtr))==sliderCtl) || (CtlGlueGetControlStyle((ControlType*)(controlPtr))==feedbackSliderCtl) ))   //added 09242003
           {
 
               //it's a slider ctl
               if(arg3->kind != 's')
               {
                  CtlGetSliderValues ((ControlType*)(controlPtr),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue); 
                  maxValue =  basc_integ_value(arg3,(double*)arg3_val);
                  CtlSetSliderValues ((ControlType*)(controlPtr),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue);
			   }
               else commonErrorWrongType("maxValue");
            
          }
          else
          {
          		if(controlType  != frmScrollBarObj) commonErrorWrongCtltype("max",controlType);
          		else
          		{
            		if(arg3->kind != 's') commonSetScrollbar(0x03,frmPtr,arg3,(double*)arg3_val);
            		else commonErrorWrongType("max");
          		}
          }
          break; 
       case 7:  //pageSize
       case 97:        //added 07062005  must allow both 7 and 97
            
           
           //08292005 type = CtlGlueGetControlStyle((ControlType*)(controlPtr)); 
           if  (  (controlType==frmControlObj)&&(CtlGlueGetControlStyle((ControlType*)(controlPtr))==sliderCtl) || (CtlGlueGetControlStyle((ControlType*)(controlPtr))==feedbackSliderCtl) )   //added 09242003
           {
               //it's a slider ctl
               if(arg3->kind != 's')
               {
                  CtlGetSliderValues ((ControlType*)(controlPtr),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue); 
                  pageSize =  basc_integ_value(arg3,(double*)arg3_val);
                  CtlSetSliderValues ((ControlType*)(controlPtr),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue);
			   }
               else commonErrorWrongType("pageSize");
            
          }
          else
          {
          		if(controlType  != frmScrollBarObj) commonErrorWrongCtltype("pageSize",controlType);
          		else
          		{
            		if(arg3->kind != 's') commonSetScrollbar(0x04,frmPtr,arg3,(double*)arg3_val);
            		else commonErrorWrongType("pageSize");
         		}
          }		
          break; 
        //start additions 09242003
         case 48:  //selectedCol
          if(controlType  != frmTableObj) commonErrorWrongCtltype("Col",controlType);
          else
          {
            if(arg3->kind != 's') gridSetSelectedCol(frmPtr,controlPtr,(double*)arg3_val);
            else commonErrorWrongType("Col");
          }
          break;
        /*
        case 49:  //selectedCol
          if(controlType  != frmTableObj) commonErrorWrongCtltype("Cols",controlType);
          else
          {
            if(arg3->kind != 's') gridSetCols(frmPtr,controlPtr,arg3,(double*)arg3_val);
            else commonErrorWrongType("Cols");
          }
          break;
        */
        case 50:  //ColWidth
          if(controlType  != frmTableObj) commonErrorWrongCtltype("ColWidth",controlType);
          else
          {
            if(arg3->kind != 's') gridSetColWidth(frmPtr,controlPtr,(double*)arg3_val);
            else commonErrorWrongType("ColWidth");
          }
          break;
        case 51:  //selectedRow
          if(controlType  != frmTableObj) commonErrorWrongCtltype("Row",controlType);
          else
          {
            if(arg3->kind != 's') gridSetSelectedRow(frmPtr,controlPtr,(double*)arg3_val);
            else commonErrorWrongType("Row");
          }
          break;
        case 52:  //Rows
          if(controlType  != frmTableObj) commonErrorWrongCtltype("Rows",controlType);
          else
          {
            if(arg3->kind != 's') gridSetRows(frmPtr,controlPtr,(double*)arg3_val);
            else commonErrorWrongType("Rows");
          }
          break;
        /*
        case 53:  //VisibleRows
          if(controlType  != frmTableObj) commonErrorWrongCtltype("VisibleRows",controlType);
          else
          {
            if(arg3->kind != 's') gridSetVisibleRows(frmPtr,controlPtr,arg3,(double*)arg3_val);
            else commonErrorWrongType("VisibleRows");
          }
          break;
        */
        case 54:  //cellMatrix
          if(controlType  != frmTableObj) commonErrorWrongCtltype("cellMatrix",controlType);
          else
          {
            //note:arg3 is row#
//StrPrintF(debug,"setting cell text -- arg3=%s",arg3_val);
//SysFatalAlert(debug);
            if(arg3->kind != 's') gridSetCellMatrix(frmPtr,controlPtr, arg3_val);
            else commonErrorWrongType("cellMatrix");
          }
          break;
        case 55: //valueMatrix
          if(controlType  != frmTableObj) commonErrorWrongCtltype("valueMatrix",controlType);
          else
          {
            if(arg3->kind != 's') gridSetValueMatrix(frmPtr,controlPtr ,(double*)arg3_val);
            else commonErrorWrongType("valueMatrix");
          }
          break;
        case 56:  //value
           //start additions 07122005
           if  (controlType==frmControlObj)
           {
               type = CtlGlueGetControlStyle((ControlType*)(controlPtr)); 
               if ((type==sliderCtl) || (type==feedbackSliderCtl)  )    
               {
                   //it's a slider ctl
                   if(arg3->kind != 's')
                   {
                      CtlGetSliderValues ((ControlType*)(controlPtr),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue); 
                      curValue =  basc_integ_value(arg3,(double*)arg3_val);
                      CtlSetSliderValues ((ControlType*)(controlPtr),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue);
			       }
                   else commonErrorWrongType("Value");   
               }   
            
          }
          else
          {
                if(controlType  == frmScrollBarObj)  
                {
                	if(arg3->kind != 's') commonSetScrollbar(0x01,frmPtr,arg3,(double*)arg3_val);
            		else commonErrorWrongType("Value");
          		}
          		else
          		{
          		//end additions 07122005
          if(controlType  != frmTableObj) commonErrorWrongCtltype("Value",controlType);
          else
          {
            if(arg3->kind != 's') gridSetSelectedValue(frmPtr,controlPtr, (double*)arg3_val);
            else commonErrorWrongType("Value");
          }
                }                                //07122005
          }                                      //07122005
          
          break;
        case 57:  //rowData
          if(controlType  != frmTableObj) commonErrorWrongCtltype("rowData",controlType);
          else
          {
            if(arg3->kind != 's') gridSetRowData(frmPtr,controlPtr, (double*)arg3_val);
            else commonErrorWrongType("RowData");
          }
          break;
          //start additions 02062004
        case 58:  //toprow
          if(controlType  != frmTableObj) commonErrorWrongCtltype("topRow",controlType);
          else
          {
            if(arg3->kind != 's') gridSetTopRow(frmPtr,controlPtr, (double*)arg3_val);
            else commonErrorWrongType("TopRow");
          }
          break;
          //end additions 02062004
       //start additions 04012005
        
         case 59: //fontMatrix
          if(controlType  != frmTableObj) commonErrorWrongCtltype("fontMatrix",controlType);
          else
          {
            if(arg3->kind != 's') gridSetFontMatrix(frmPtr,controlPtr ,(double*)arg3_val);
            else commonErrorWrongType("fontMatrix");
          }
          break;
        case 80:  //left
        
            if(arg3->kind != 's')
            {
                FrmGetObjectBounds (frmPtr,pos,&bounds);
                  if(FrmGetObjectType(frmPtr,pos)==frmTableObj)            //07052005
                  {                                                        //07052005
                      WinEraseRectangle (&bounds,0);                       //07052005
                  }                                                        //07052005 
                  commonShowHide(0x00,frmPtr,FrmGetObjectId(frmPtr,pos));  //07052005
                  
                bounds.topLeft.x=basc_integ_value(arg3,(double*)arg3_val);
                   if( obj->type == frmTableObj)                           //07052005
                   {                                                       //07052005
                         obj->origGridBounds.topLeft.x = bounds.topLeft.x; //07052005
                   }                                                       //07052005
                FrmSetObjectBounds (frmPtr,pos, &bounds);
                
                  commonShowHide(0x01,frmPtr,FrmGetObjectId(frmPtr,pos));  //07052005   
            }
            else commonErrorWrongType("Left");     //modified 07062005
            break; 
        case 81:  //top
             if(arg3->kind != 's')
            {
                FrmGetObjectBounds ( frmPtr,pos,&bounds);
                bounds.topLeft.y=basc_integ_value(arg3,(double*)arg3_val);
                if(FrmGetObjectType(frmPtr,pos)==frmTableObj)            //07052005
                {                                                        //07052005
                    WinEraseRectangle (&bounds,0);                       //07052005
                }                                                        //07052005 
                commonShowHide(0x00,frmPtr,FrmGetObjectId(frmPtr,pos));  //07052005
                if( obj->type == frmTableObj)                           //07052005
                   {                                                       //07052005
                         obj->origGridBounds.topLeft.y = bounds.topLeft.y; //07052005
                   }                                                       //07052005
                FrmSetObjectBounds (frmPtr,pos, &bounds);
                commonShowHide(0x01,frmPtr,FrmGetObjectId(frmPtr,pos));  //07052005                
            }
            else commonErrorWrongType("Top");    //modified 07062005
            break; 
        	 
        case 82:   //width
            if(arg3->kind != 's')
            {
                FrmGetObjectBounds ( frmPtr,pos,&bounds);
                bounds.extent.x=basc_integ_value(arg3,(double*)arg3_val);
                if(FrmGetObjectType(frmPtr,pos)==frmTableObj)            //07052005
                {                                                        //07052005
                    WinEraseRectangle (&bounds,0);                       //07052005
                }                                                        //07052005 
                commonShowHide(0x00,frmPtr,FrmGetObjectId(frmPtr,pos));  //07052005
                if( obj->type == frmTableObj)                           //07052005
                   {                                                       //07052005
                         obj->origGridBounds.extent.x = bounds.extent.x; //07052005
                   }                                                       //07052005
                FrmSetObjectBounds (frmPtr,pos, &bounds);
                commonShowHide(0x01,frmPtr,FrmGetObjectId(frmPtr,pos));  //07052005
            }
            else commonErrorWrongType("Width");     //modified 07062005
            break; 
        case 83:  //height
            if(arg3->kind != 's')
            {
                FrmGetObjectBounds ( frmPtr,pos,&bounds);
                bounds.extent.y=basc_integ_value(arg3,(double*)arg3_val);
                if(FrmGetObjectType(frmPtr,pos)==frmTableObj)            //07052005
                {                                                        //07052005
                    WinEraseRectangle (&bounds,0);                       //07052005
                }                                                        //07052005 
                commonShowHide(0x00,frmPtr,FrmGetObjectId(frmPtr,pos));  //07052005
                if( obj->type == frmTableObj)                           //07052005
                   {                                                    //07052005
                         obj->origGridBounds.extent.y = bounds.extent.y; //07052005
                   }                                                     //07052005
                FrmSetObjectBounds (frmPtr,pos, &bounds);
                commonShowHide(0x01,frmPtr,FrmGetObjectId(frmPtr,pos));  //07052005  
            }
            else commonErrorWrongType("Height");     //modified 07062005
            break;    
         //Note: DO NOT USE case values 94-99 because they are used above
          //end additions 04012005                 
      //end additions 09242003
          
       }     
	   
   //if(controlType != frmControlObj) return;
}
/********************************************************************************************/
void commonDeleteItem(FormPtr frmPtr,ControlPtr controlPtr, int controlid, struct dataelem *argn, double* argn_val)
{
    struct ObjectData * objectPtr;
  int oldNoItems;
 
  int where;
  VoidHand hnew;
  VoidPtr pnew;
  VoidPtr pold;
  VoidPtr oldptr;
  
  objectPtr=locateObjectPtr(controlid);                   //locate our own object info ptr
   
  pold=  objectPtr->dataPtr;                              //point to the old list of text ptrs
  oldNoItems=objectPtr->numItems;                         //set the # of items in the old list
  where=basc_integ_value(argn,(double*)argn_val);         //get the integer # of the item to delete
//StrPrintF(debug,"in listdeleteItem   where=%d  old#=%d   ",where,objectPtr->numItems);
//dbug(debug);
  if ((where>oldNoItems) || (where<=0) )                  //if # specified to delete is too high or too low
  {
//dbug("out-of-bounds");               
         return;                                          //can't delete, so exit 
  }
  
   
 
  if (oldNoItems==1)
  {
     if( objectPtr->dataPtr!=0)
     {

         FreeListValues(objectPtr->dataPtr,oldNoItems);   //free up the old list and each text string

     }
     pnew=0;
     LstSetListChoices( (ListPtr)controlPtr, 0,0 );       //set the screen list object empty
     goto redraw;
  }

  oldptr=*( (char**)((char*)(objectPtr->dataPtr)+(where-1)*4));   //point to the old text string
  MemPtrFree(oldptr);                                         //and free it up

  hnew=MemHandleNew( ( objectPtr->numItems-1)*4);  //allocate a new list of text pointers one smaller than old list
  if(hnew==0) OutOfMemory(6058);  //05282003
  pnew=MemHandleLock(hnew);                                 //and lock it down

  if(where==1)                 //deleting the 1st item
  {
       MemMove((char*)pnew,(char*)pold+4, (oldNoItems-1)*4);      //move all old ptrs except 1st one
  }
  else
  {
      if(where==oldNoItems)     //deleting the last item
      {
           MemMove((char*)pnew,(char*)pold, (where-1)*4);    //move all old ptrs except last one 
      }
      else                    //deleting an item in the middle
      {
          MemMove((char*)pnew,pold, (where-1)*4);                                        //move  the preceeding old pointers into the list of pointers
          MemMove((char*)pnew+(where-1)*4,(char*)pold+(where)*4, (oldNoItems-where)*4);  //move  the succeeding old pointers into the list of pointers
      }
  }
//dbug("deleting list item");   
  LstSetListChoices( (ListPtr)controlPtr, (char**)pnew, oldNoItems-1 );  //set the screen object to have the new list of text items
  
  MiscPtrFree(pold);   //and free the pointer list   added this stmt 12162003 LDM  ******************

redraw:
  objectPtr->dataPtr=pnew;            //save the new ptr to the list in our own area
  objectPtr->numItems=oldNoItems-1;   //and save the new # of items
  

  
  if(frmPtr==FrmGetActiveForm()) LstDrawList((ListPtr) controlPtr);  //redraw the list on the screen
  
}
/********************************************************************************************/
void verb_listdeleteitem()
{
  FormPtr frmPtr;
  
  
 
  find_ctlid(true);                                           //find the ptr to the List object
  find_arg_2();                                           //the position in the list to delete
  frmPtr=FrmGetActiveForm();
  commonDeleteItem(frmPtr,controlPtr,controlid,arg2,(double*)arg2_val);
  
  
}
     
/********************************************************************************************/
void commonAddItem(FormPtr frmPtr,ControlPtr controlPtr, int controlid,struct dataelem *argn, double*argn_val,struct dataelem* args, char*args_val, char redrawChar)
{ 
  struct ObjectData * objectPtr;
  unsigned int i;
  unsigned int j;

  
  
  int oldNoItems;
  
  int where;
  VoidHand hnew;
  VoidPtr pnew;
  VoidPtr pold;
  VoidHand hitem;
  VoidPtr itemPtr;
  VoidPtr oldptr;
  VoidPtr newptr;
 


  //controlPtr=FrmGetObjectPtr(frmPtr,controlid);
  //GHGlue next 3 lines
  //if(arg2==null_ptr) where=((ListPtr)controlPtr)->numItems+1;  //if didn't specify optional position in list at which to add,
  //                                                             //then, add to end of list

  if(argn==null_ptr) where=LstGetNumberOfItems((ListPtr)controlPtr)+1;  //if didn't specify optional position in list at which to add,
                                                               //then, add to end of list
  else where=basc_integ_value(argn,(double*)argn_val);         //otherwise, get integer # of position to add at
  objectPtr=locateObjectPtr(controlid);                      //point to our own internal object info
//StrPrintF(debug,"in listdeleteItaddtem   where=%d  old#=%d   ",where,objectPtr->numItems);
//dbug(debug);
 
   if(where<=0) where=1;    //GH added 10092002
  if((where<=0)||(where>(objectPtr->numItems+1)))              //if specified a position too high or too low 
  {
                                      //can't add , so exit                                
      //theChar=find_char();      //must bypass the char in code to avoid abort
      StrPrintF(debug,"index (%d) is invalid for list.add operation.",where);
      SysFatalAlert(debug);
      ErrThrow(-1);                 //inserted 05212003
      //05212003 return;
  }
  
//StrPrintF(debug,"addItem id=%d where=%d val=%s",controlid,where,args_val);
//dbug(debug);
  hnew=MiscHandleNew( ( objectPtr->numItems+1)*4,"addLst");  //allocate a new list of text pointers one larger than old list
  pnew=MiscHandleLock(hnew);                                 //and lock it down

  pold=  objectPtr->dataPtr;                   //point to old list of text ptrs
  oldNoItems=objectPtr->numItems;              //and how many were in the list 
  
 
  itemPtr=args_val;                           //the item to add  

  newptr=(char*)MiscHandleLock(MiscHandleNew(StrLen((char*) itemPtr)+1 ,"addLst3"));  //alloc new meme for the text string

  MemMove(newptr,itemPtr,StrLen((char*) itemPtr)+1);                                  //and move the text to it to save it

  if(where==1)                //adding to the beginning of the list
  {
      *( (char**)((char*)pnew)) =(char*)newptr;   //set 1st ptr to the new item text
      MemMove((char*)pnew+4,pold, oldNoItems*4);  //move all the old pointers into the list of pointers
  }
  else
  {
     if( where>oldNoItems)   //adding to the end of the list
     {
          MemMove((char*)pnew,pold, oldNoItems*4);  //move all the old pointers into the list of pointers
          *( (char**)((char*)pnew+oldNoItems*4)) =(char*)newptr;   //set last ptr to the new item text
     }
     else                    //adding in the middle of the list
     {
          MemMove((char*)pnew,pold, (where-1)*4);                                          //move  the preceeding old pointers into the list of pointers
          *( (char**)((char*)pnew+(where-1)*4)) =(char*)newptr;                            //set middle ptr to the new item text
          MemMove((char*)pnew+(where)*4,(char*)pold+(where-1)*4, (oldNoItems-where+1)*4);  //move  the succeeding old pointers into the list of pointers
     }
  }

  LstSetListChoices( (ListPtr)controlPtr,(char**) pnew, oldNoItems+1);  //set the new list in the screen object
  if( objectPtr->dataPtr!=0)
  {
          MiscPtrFree(objectPtr->dataPtr);                      //free up the old list of pointers
          //FreeListValues(objectPtr->dataPtr,oldNoItems);
  }
  objectPtr->dataPtr=pnew;                                      //and save the new list of ptrs in our own mem area
  objectPtr->numItems=oldNoItems+1;                             //and save how many in the list as well
//StrPrintF(debug,"setting noItems to %d",oldNoItems+1);
//SysFatalAlert(debug);
  
 
  //redrawChar=find_char();                                 //get the char which tells whether to redraw or not 
  if(frmPtr==0) return;
  if(redrawChar==0x01)   //redraw if asked for and on current active form
  {
      //12172001 make sure ctl on cur activeform                                                                             //12172001cause may be on some other form
      for(i=0;i<FrmGetNumberOfObjects(FrmGetActiveForm());++i)
      {
         if (FrmGetObjectPtr(FrmGetActiveForm(),i)==controlPtr)
         {

             LstDrawList((ListPtr) controlPtr);  //was being done w/o check for cur form

             break;
         }    
      }   
  } 
}      
/********************************************************************************************/
void verb_listadditem()
{
  char theChar;
  FormPtr frmPtr;
  
  frmPtr=FrmGetActiveForm(); 
  find_ctlid(true);      //find ptr to the List screen object 

  find_arg_1();      //text string of item to be added
  find_arg_2();      //position in the list to add this new item at
  theChar=find_char();
  commonAddItem(frmPtr,controlPtr, controlid, arg2,(double*)arg2_val,arg1,arg1_val,theChar);
}


/********************************************************************************************/

void commonClear(ControlPtr controlPtr,int objType,FormPtr frmPtr, int controlid)
{
   
   VoidPtr pold;
   int oldNoItems;
   
    struct ObjectData *objectPtr;
    int i;
    if(objType==frmListObj) goto listClear;
    if(objType==frmPopupObj) goto listClear;
    return;
popupClear:
  
//dbug("in popup clear");
   LstSetListChoices( (ListType*)controlPtr, 0,0);
   
   objectPtr=locateObjectPtr(controlid);
   if( objectPtr->dataPtr!=0)
   {
     FreeListValues(objectPtr->dataPtr,objectPtr->numItems);
   }
   objectPtr->dataPtr=0;
   objectPtr->numItems=0; 
   
  
   if(frmPtr==FrmGetActiveForm()) LstDrawList(  (ListPtr)controlPtr  );
   return; 
    
listClear: 
//dbug("in commonlist clear");
      LstSetListChoices( (ListPtr)controlPtr, 0, 0); //set list of item text ptrs to nothing
      
      objectPtr=locateObjectPtr(controlid);          //now update our own internal pointers
//dbug("xxxxx");
      if( objectPtr->dataPtr!=0)
      {
         FreeListValues(objectPtr->dataPtr,objectPtr->numItems);  //and free up the old text strings and ptr list
      }
      objectPtr->dataPtr=0;                         //new list is empty
      objectPtr->numItems=0;                        //with zero items in it

      //12172001 make sure ctl on cur activeform  before redrawing                                                                           include <172001cause may be on some other form
      for(i=0;i<FrmGetNumberOfObjects(FrmGetActiveForm());++i)
      {
         if (FrmGetObjectPtr(FrmGetActiveForm(),i)==controlPtr)
         {
//dbug("redrawing list");
             LstDrawList((ListPtr) controlPtr);  //was being done w/o check for cur form
             break;
         }    
      }         
}
/********************************************************************************************/
void verb_popupclear()
{
   
   FormPtr frmPtr;   
   
   find_ctlid(true);
   frmPtr=FrmGetActiveForm();
   commonClear(controlPtr,frmPopupObj,frmPtr,controlid);

}
/********************************************************************************************/
void verb_listclear()
{
    FormPtr frmPtr;
    
            
      find_ctlid(true);                                  //find ptr to the List object
      frmPtr=FrmGetActiveForm();
//dbug("verb_listclear");
     commonClear(controlPtr,frmListObj,frmPtr,controlid);
     
} 
/********************************************************************************************/
void verb_generalVerb()
{
  
  int controlType;
  int pos;
  char c;
  int verbId;
  Boolean found;
  char theChar;    //09302002
  
  FormPtr frmPtr;        //added 5.20.2000 
//dbug("in set text");   
  found=true;
   c=find_char();   //type of control identifier
   switch(c)
   {
      case 'i':  //ctlid
        found=find_ctlid(false);
//StrPrintF(debug,"ctlid=%d",controlid);
//dbug(debug);
        if(found==false) break;  //probably a bitmap that can't use by id
        frmPtr=findFormTheControlIsOn(controlid);
        pos=FrmGetObjectIndex(frmPtr,controlid);
//StrPrintF(debug,"ctlid=%d  pos=%d",controlid,pos);
//dbug(debug);
        break;
      case 'v':  //variable containing name
        find_arg_2();      //variable containing name
        frmPtr=FrmGetActiveForm();
        pos=findControlsPositionOnForm(&frmPtr,arg2_val);
        goto havePosition;
        break;
      case 'p':  //position of ctl on form
        find_arg_2();      //position of control on form
        pos = integ_value( arg2, (double *)arg2_val ); 
        frmPtr=FrmGetActiveForm();
havePosition:
        
	    if(pos>FrmGetNumberOfObjects(frmPtr)-1)
	    {
	       SysFatalAlert("Control position too high.");
	       ErrThrow(-1);                 //inserted 05212003
	    }
	   
	    controlPtr=((ControlType*)FrmGetObjectPtr(frmPtr,pos));
	    controlid=FrmGetObjectId(frmPtr,pos);
	    break;
   }
   
   if(found==true)controlType=FrmGetObjectType(frmPtr,pos);
   verbId=find_integer();          //property type identifier #
   
   switch(verbId)
   {
       case 0:  //hide
          
            if (found==false) return;
            commonShowHide(0x00,frmPtr,controlid);
            break; 
       case 1:  //show
             if (found==false) return;
             commonShowHide(0x01,frmPtr,controlid);
	        break; 
       case 2:  //additem
//StrPrintF(debug,"in additem id=%d ",controlid);
//dbug(debug);
          

          if( (controlType!=frmListObj)&&(controlType!=frmControlObj))commonErrorWrongCtltype("additem",controlType);
          else
          {
            find_arg_3();  //text
            find_arg_2();  //position in list
            theChar=find_char();             //09302002
            
            if(arg3->kind == 's') 
            {
                if (controlType==frmListObj) commonAddItem( frmPtr,controlPtr,controlid,   arg2, (double*)arg2_val,arg3,arg3_val,theChar);       
                else
                {
                     //must point to list part of popup
                     controlPtr=((ControlType*)FrmGetObjectPtr(frmPtr,pos+1));
	                 controlid=FrmGetObjectId(frmPtr,pos+1);
                     commonAddItem( frmPtr,controlPtr,controlid, arg2, (double*)arg2_val,arg3,arg3_val,theChar);
                }     
            }
            else commonErrorWrongType("additem");
          }
          break;
       case 3:  //clear
          //09242003 if( (controlType!=frmListObj)&&(controlType!=frmControlObj))
          if( (controlType!=frmListObj)&&(controlType!=frmControlObj)&&(controlType!=frmTableObj))  //added 09242003
          {
              commonErrorWrongCtltype("clear",controlType);
          }
          else
          {
                if (controlType==frmListObj)
                {
                
//StrPrintF(debug,"clearing list obj id=%d",controlid);
//dbug(debug); 
                   commonClear(controlPtr,frmListObj,frmPtr,controlid);       
                }
                else
                {
                   if (controlType==frmTableObj)
                   {
                        gridClear(frmPtr,controlPtr);
                }
                else
                {
                     //must point to list part of popup
                     controlPtr=((ControlType*)FrmGetObjectPtr(frmPtr,pos+1));
	                 controlid=FrmGetObjectId(frmPtr,pos+1);
                     commonClear(controlPtr,frmPopupObj,frmPtr,controlid);
                }
                }
                
           
          }
          break;
       case 4:  //deleteitem
          if( (controlType!=frmListObj)&&(controlType!=frmControlObj))commonErrorWrongCtltype("deleteitem",controlType);
          else
          {
            find_arg_3();    //index
            if(arg3->kind != 's')
            {
                if (controlType==frmListObj) commonDeleteItem( frmPtr,controlPtr,controlid,   arg3, (double*)arg3_val);       
                else
                {
//dbug("recognized popup delete");
                     //must point to list part of popup
                     controlPtr=((ControlType*)FrmGetObjectPtr(frmPtr,pos+1));
	                 controlid=FrmGetObjectId(frmPtr,pos+1);
                     commonDeleteItem( frmPtr,controlPtr,controlid, arg3, (double*)arg3_val);
                }     
            }
            else commonErrorWrongType("deleteitem");
          }
          break; 
       case 5:  //startCapture
          if(controlType  != frmGadgetObj) commonErrorWrongCtltype("startCapture",controlType);
          else
          {
            commonStartCapture(frmPtr,controlid);
          }
          break; 
       case 6:  //erase
          if(controlType  != frmGadgetObj) commonErrorWrongCtltype("startCapture",controlType);
          else
          {
            commonErase(frmPtr,controlid);
          }
          break;
       
        case 7:  //display signature
          if(controlType  != frmGadgetObj) commonErrorWrongCtltype("startCapture",controlType);
          else
          {
            find_arg_3();  
            commonSignatureDisplay(frmPtr,  controlid, arg3, arg3_val);
          }
          break; 
        case 8:  //redraw/refresh ctl
          //if(controlType  != frmGadgetObj) commonErrorWrongCtltype("refresh",controlType);
          //else
          //{
            if(found==false)  break;   //may be shift indic that can't redraw
            if(controlType==frmGraffitiStateObj)  break;  //shift indic can't redraw
            commonRedrawId(frmPtr,  controlid);
          //}
          break; 
        case 9:  //setfocus
          if(controlType  != frmFieldObj) commonErrorWrongCtltype("setFocus",controlType);
          else
          {
            
            commonSetFocus(frmPtr,  controlid);
          }
          break;      
        //start of additions 09242003   
        case 70:  //addItem
          if(controlType  != frmTableObj) commonErrorWrongCtltype("Add",controlType);
          else
          {
            
            gridAdd(frmPtr,  controlPtr);
          }
          break;
        case 71:  //delete
          if(controlType  != frmTableObj) commonErrorWrongCtltype("Delete",controlType);
          else
          {
            
            gridDelete(frmPtr,  controlPtr);
          }
          break;    
        case 72:  //colType
          if(controlType  != frmTableObj) commonErrorWrongCtltype("ColType",controlType);
          else
          {
//SysFatalAlert("basc--found colType");            
            gridColType(frmPtr,  controlPtr);
          }
          break;
        case 73:  //bindToDatabase
          if(controlType  != frmTableObj) commonErrorWrongCtltype("BindToDatabase",controlType);
          else
          {
            
            gridBindToDatabase(frmPtr,  controlPtr);
          }
          break;    
        //start additions 02062004
        /*
        case 74:  //bindToDatabase
          if(controlType  != frmTableObj) commonErrorWrongCtltype("SetTopRow",controlType);
          else
          {
            
            gridSetTopRow(frmPtr,  controlPtr);
          }
          break;    
        */
        //end additions 02062004 //end additions 09242003
                
        //start additions 08152004
        case 75:  //hideGridLines
          if(controlType  != frmTableObj) commonErrorWrongCtltype("ColType",controlType);
          else
          {
//SysFatalAlert("basc--found colType");            
            gridHideGridLines(frmPtr,  controlPtr);
          }
          break; 
        case 76:  //showGridLines
          if(controlType  != frmTableObj) commonErrorWrongCtltype("ColType",controlType);
          else
          {
//SysFatalAlert("basc--found colType");            
            gridShowGridLines(frmPtr,  controlPtr);
          }
          break; 
        //end additions 08152004        
       }     
	   
   //if(controlType != frmControlObj) return;

} 
