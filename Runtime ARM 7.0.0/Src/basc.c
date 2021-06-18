#ifdef __MC68K__   
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

#include <window.h>
#include <mathlib.h>
#endif

#ifndef __MC68K__
#include "PACEInterfaceLib.h"
#include <PalmCompatibility.h>
#include <endianutils.h>
#endif
#include "NSBPNOShared.h"               //EMP
#include "NSBPNOGlue.h"
#include "copy.h"

#include <ModemMgr.h>
#include <PalmOSGlue.h>  //GHGlue

#ifdef __MC68K__
void gridGetFontMatrix(FormPtr frm,VoidPtr controlPtr);
#else
void gridGetFontMatrix(PNOBlock *pnoP, Arg *arg4, FormPtr frm,VoidPtr controlPtr);
#endif

#ifdef __MC68K__
extern void redrawGrid(struct ObjectData * objPtr); //09242003
#else
extern void redrawGrid(PNOBlock *pnoP, struct ObjectData *objPtr);
#endif
double misc_int(double x);

void SetFieldText( UInt nFieldID, const CharPtr pSrcText, Int nMaxSize, Boolean bRedraw);
extern void dbugx(double* x,char*identifier);
void FreeListValues(VoidPtr pold,Int16 noItems ); //added 5.21.2000
#ifndef ARM
VoidHand saveObjectHandle;                     //added 5.21.2000
#endif

#ifdef __MC68K__
struct ObjectData * locateObjectPtr(Word id);  //added 5.21.2000
#else
struct ObjectData *locateObjectPtr(PNOBlock *pnoP, Word id);  //EMP
#endif

typedef long DATE; /*Julian dates*/
#ifdef __MC68K__
void restore_integ_value(int i,struct dataelem * arg,double * arg_ad,
unsigned int arg_occ1,unsigned int arg_occ2,unsigned int arg_occ3) ;  
#else
void restore_integ_value(PNOBlock *pnoP, Int16 i,struct dataelem * arg,double * arg_ad,
UInt16 arg_occ1,UInt16 arg_occ2,UInt16 arg_occ3) ;
#endif
#ifndef ARM 
extern Int16           applVersionInteg;
extern Int16           applVersionFrac;
#endif
#ifdef __MC68K__
extern void misc_text_abort( char * msg );
#else
extern void misc_text_abort(PNOBlock *pnoP, char *msg);
#endif

extern  void UpdateScrollbar(FieldPtr field, ScrollBarPtr scroll);
#ifdef __MC68K__
extern misc_stodbl(struct dataelem *d,  unsigned int sub1,unsigned int sub2,unsigned int sub3, double  *result);
extern misc_stostr1(char *s);
extern misc_stostr2(char *s);
extern misc_stostr3(char *s);
extern misc_stostr4(char *s);
extern misc_stostr5(char *s);
void misc_fix(int i, char *res, int num);
extern struct dataelem *find_arg_nosubs(unsigned int *s1,unsigned int *s2, unsigned int *s3);
extern double misc_floor(double x);
Int16 misc_format_number(struct dataelem* v, double* n , char * s);
struct dataelem *find_arg(unsigned int* s1, unsigned int* s2,  unsigned int *s3,
                                struct dataelem**sde1, struct dataelem** sde2, struct dataelem** sde3);
#else
Int16 misc_format_number(PNOBlock *pnoP, struct dataelem* v, double* n , char * s);
extern void misc_stostr(PNOBlock *pnoP, struct dataelem * *d,
        UInt16 sub1,UInt16 sub2,UInt16 sub3, char *result);
extern void misc_stodbl(PNOBlock *pnoP, struct dataelem *d,
      UInt16 sub1,UInt16 sub2,UInt16 sub3, double  *result);
#endif
#ifdef __MC68K__
void misc_stodbl1(double* x);
void misc_stodbl2(double* x);
void misc_stodbl3(double* x);
void misc_stodbl5(double* x);
#else
void misc_stodbl1(PNOBlock *pnoP, double *x);
void misc_stodbl2(PNOBlock *pnoP, double *x);
void misc_stodbl3(PNOBlock *pnoP, double *x);
void misc_stodbl5(PNOBlock *pnoP, double *x);
#endif
#ifdef __MC68K__
void DoubleToStr (double val, CharPtr str);
Int16 misc_format_number(struct dataelem* v, double* n , char * s);
extern int integ_value( struct dataelem *  arg, double *    arg_ad);        /*---calc integ value of data elem__*/
double misc_fabs(double x);
#else
void DoubleToStr (PNOBlock *pnoP, double val, CharPtr ans);
Int16 misc_format_number(PNOBlock *pnoP, struct dataelem* v, double* n , char * s);
#endif
UInt16 miscFrmGetObjectIdFromPtr(const FormType *formP, void *objP);  //GH  01.10.2002

#ifdef __MC68K__
void restore4(int i);
void test_debug(char *msg);
void store4( double *d);
void storestr4( char *s);

extern void verb_signatureErase();
void verb_signatureStartCapture();
void verb_signatureDisplay();
#endif

#ifdef __MC68K__
void commonStartCapture(FormPtr frmPtr, int controlid);
void commonErase(FormPtr frmPtr, int controlid);

void commonSignatureDisplay(FormPtr frmPtr,char *argx_val, int controlid); // EMP
void commonEndCapture(FormPtr frmPtr, struct dataelem **de, Int16 occ1, Int16 occ2, Int16 occ3, Int16 controlid);

Int16 getx();
Int16 gety();
extern misc_stodbl(struct dataelem *d,  unsigned int sub1,unsigned int sub2,unsigned int sub3, double  *result);
extern void verb_function_doit (UInt16 it);
#ifdef ARM
extern void function_doit_from_PNO(void);
#endif
#else
Int16 getx();
Int16 gety();
extern void verb_function_doit (PNOBlock *pnoP, UInt16 it);  // EMP
#endif
#ifdef __MC68K__
Int16 more_processing();
Int16 executeSomeCode();	// 04292003
#else
Int16 more_processing(PNOBlock *pnoP);
Int16 executeSomeCode(PNOBlock *pnoP);	// 04292003
void find_arg_PNO(PNOBlock *pnoP, Arg *argRet);
#endif
#ifdef __MC68K__
extern void misc_errmsg( char * the_msg);
#else
extern void misc_errmsg(PNOBlock *pnoP, char * the_msg);
#endif
#ifdef __MC68K__
extern void setupADataelem(int i);
void function_doit(unsigned int it);
void setSerErr(Err err);
void serialWakeupHandler(UInt32 refCon);									//03.06.02 GH
ULong serialReceiveAfterEvent(Char *outBuf, UInt32 outSize);				//03.06.02 GH
static Err DoReceiveWindowOpen(UInt16 portId, UInt8 **bufPP, UInt32 *sizeP);//03.06.02 GH
static Err DoReceiveWindowClose(UInt16 portId, UInt32 bytesPulled);			//03.06.02 GH
void serialSetState(UInt8 state);	//03.06.02 GH
#endif

void dbGetSome(void* from,Int16 len,void*to);
#ifdef __MC68K__
extern struct dataelem *elem_tbl_ptr(UInt16 de_no) ;
#else
extern struct dataelem *elem_tbl_ptr(PNOBlock *pnoP, UInt16 de_no) ;
#endif
#ifdef __MC68K__
void chkMathLibOpen();
void debug_addr( char *  x);
int ExitHousekeeping();
int launchPgm();
int dbugKind(char*s);
void function_doit(unsigned int it);
#endif

#ifdef __MC68K__
extern misc_getint(struct dataelem *d,  UInt16 sub1,
UInt16 sub2,UInt16 sub3,  UInt16  *result);
void dbug(char*s);
#else
extern void misc_getint(PNOBlock *pnoP, struct dataelem *d,  UInt16 sub1,
UInt16 sub2,UInt16 sub3,  UInt16  *result);
#endif
void calendar_date(DATE jdate, Int16 *day, Int16 *month, Int16 *year);
Int16 valid_date(Int16 day, Int16 month, Int16 year);

#ifdef __MC68K__


int day_of_week(DATE jdate );

extern Int16 maxVarsInDynamHeap;    //06012002  max # of vars to alloc in dymam heap
extern Int16       fldToUpdate;
#endif

#ifdef __MC68K__
extern UInt16 find_integer();                   /**/
#else
extern UInt16 find_integer(PNOBlock *pnoP);     // EMP
#endif

#ifdef __MC68K__
struct file_entry * locate_file_by_no( unsigned long n );
struct dict_entry * locate_dict_by_no( unsigned long n );
struct dict_entry * find_dict_entry();
struct file_entry * find_file_entry();
unsigned long long_integ_value(struct dataelem *arg, double *arg_ad);        /*---calc integ value of data elem__*/
extern int integ_value(struct dataelem * arg, double* arg_ad);      
extern void verb_func_getGeneralPropertyNumeric();
#endif
#ifdef __MC68K__
extern void verb_func_getGeneralPropertyString();
#else
extern void verb_func_getGeneralPropertyString(PNOBlock *pnoP);
#endif

#ifdef __MC68K__
void set_sub(Int16 n, struct dataelem *arg, UInt16* sub_val, struct dataelem *sub_de);
#else
void set_sub(PNOBlock *pnoP, Int16 n, struct dataelem *arg, UInt16* sub_val, struct dataelem *sub_de);
#endif

#ifdef __MC68K__
unsigned char find_char();
#else
unsigned char find_char(PNOBlock *pnoP);    // EMP 092603
#endif

#ifdef __MC68K__

void setDbErr(int err);
void setDbOK();
void setDbRes(int err);
#else
#define setDbOK() {double d = 0; d = SwapDouble(d); misc_stodbl(pnoP, arg1.dataElem, arg1.occ1, arg1.occ2, arg1.occ3, &d);}
#define setDbErr(err) {double d = err; d = SwapDouble(d); misc_stodbl(pnoP, arg1.dataElem, arg1.occ1, arg1.occ2, arg1.occ3, &d);}
#define setDbRes(err) {double d = err; d = SwapDouble(d); misc_stodbl(pnoP, arg1.dataElem, arg1.occ1, arg1.occ2, arg1.occ3, &d);}
#endif

#ifdef __MC68K__
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
#endif

#ifdef __MC68K__
extern misc_getdbl(struct dataelem *d, unsigned int sub1 ,UInt16 sub2,UInt16 sub3, double *result);
extern void EventLoop();
#else
extern misc_getdbl(PNOBlock *pnoP, struct dataelem *d, UInt16 sub1 ,UInt16 sub2, UInt16 sub3, double *result);
#endif

#ifdef __MC68K__
void find_arg_1();
void find_arg_2();
void find_arg_3();
void find_arg_4();
void find_arg_5();
void find_arg_6();
void find_arg_1_2();
void find_arg_1_3();
void find_arg_1_4();
#else
void find_arg_1_3(PNOBlock *pnoP);
void find_arg_1_4(PNOBlock *pnoP);
#endif

#ifdef __MC68K__
//void find_arg_1_5();
void find_arg_1_nosubs();
void find_arg_2_nosubs();
void find_arg_3_nosubs();
void find_arg_4_nosubs();
void find_arg_5_nosubs();
#else
void find_arg_1_4(PNOBlock *pnoP);
#endif

#ifdef __MC68K__
extern UInt16 find_offset();
#else
extern UInt16 find_offset(PNOBlock *pnoP);    // EMP
#endif

#ifdef __MC68K__
char *misc_allocate(unsigned int , char*);
void misc_getstr(struct dataelem* arg,int occ,char*name);
extern void move_it(char *to_ad,unsigned  to_len,char * from_ad,unsigned from_len);

unsigned long find_long_integer();                     /*---find next integer in code--*/
unsigned long misc_getlongint(struct dataelem  *,unsigned long ,unsigned long * );

Int database_compare(void* a, void *b,Int oth,SortRecordInfoPtr j,SortRecordInfoPtr k, VoidHand appInfoH);
#endif

#ifdef __MC68K__
struct dbType *getDatabasePtr( ) ;
void  setDatabasePtr(double* a,DmOpenRef dbref);
void readDbFields(struct dbType* db,VoidHand recHand,struct dataelem* * keyarg,
unsigned int sub1,unsigned int sub2,unsigned int sub3  );
int writeDbFields(struct dbType *db,VoidHand* recHand,char*key,int other,char addUpdt ,UInt recno) ;  //05282003
void chkDbOpen(struct dbType *);
#else
void readDbFields(PNOBlock *pnoP, struct dbType* db,VoidHand recHand,struct dataelem**keyarg,
UInt16 sub1,UInt16 sub2,UInt16 sub3);
struct dbType *getDatabasePtr(PNOBlock *pnoP);
Int16 writeDbFields(PNOBlock *pnoP, struct dbType *db,VoidHand* recHand,char*key,Int16 other,char addUpdt ,UInt16 recno) ;  //05282003
void chkDbOpen(PNOBlock *pnoP, struct dbType *);
#endif

#ifdef __MC68K__
Boolean find_ctlid(Boolean abortSw);
#else
Boolean find_ctlid(PNOBlock *pnoP, Boolean abortSw);
#endif

#ifdef __MC68K__
void dbfind_arg(int n);
void misc_stodbl1(double* x);
void misc_stodbl3(double* x);
void misc_stodbl2(double *x);
void misc_stodbl5(double* x);
#endif
Int16 keyCompare(char* key, VoidPtr rec, Int16 oth);

#ifdef __MC68K__
void cleareleedArgs();
void end_all_move_args();
void verb_setscrollbar();
void clearLockedArgs();
#else
void end_all_move_args(PNOBlock *pnoP);
void clearLockedArgs(PNOBlock *pnoP);
#endif


#ifdef __MC68K__
#else
#endif

#ifdef __MC68K__
        void verb_generalVerb();
        void verb_setGeneralProperty();
#else
        void verb_generalVerb(PNOBlock *pnoP);
        void verb_setscrollbar(PNOBlock *pnoP);
        void verb_setGeneralProperty(PNOBlock *pnoP);
#endif

#ifdef __MC68K__
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
#else
        void verb_start_function(PNOBlock *pnoP);
        void verb_seteventhandled(PNOBlock *pnoP);
        void verb_alert(PNOBlock *pnoP);
        void verb_drawline(PNOBlock *pnoP);
        void verb_drawchars(PNOBlock *pnoP);
        void verb_erasewindow(PNOBlock *pnoP);
        void verb_destroywindow(PNOBlock *pnoP);
        void verb_createwindow(PNOBlock *pnoP);
        void verb_setcurwindow(PNOBlock *pnoP);
#endif
        
        
#ifdef __MC68K__
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
#else
        void verb_dbreadnext(PNOBlock *pnoP);
        void verb_dbposition(PNOBlock *pnoP);
        void verb_dbgetnew(PNOBlock *pnoP);
        void verb_dbputnew(PNOBlock *pnoP);
        void verb_dbclose(PNOBlock *pnoP);
        void verb_dbopen(PNOBlock *pnoP);
        void verb_dbcreate(PNOBlock *pnoP);
        void verb_dberase(PNOBlock *pnoP);
        void verb_dbreadnext(PNOBlock *pnoP);
        void verb_dbreadprev(PNOBlock *pnoP);
        void verb_dbgetnorect(PNOBlock *pnoP);
#endif

#ifdef __MC68K__
        void verb_dbinsert();
        void verb_dbdelete();
        void verb_dbupdate();
        void verb_dbread();
        void verb_dbreset();
        void verb_dbfind();
        void verb_dbcreatedatabasefromresource();	//03.24.02 GH
#else
        void verb_dbdelete(PNOBlock *pnoP);
        void verb_dbinsert(PNOBlock *pnoP);
        void verb_dbreset(PNOBlock *pnoP);
        void verb_dbfind(PNOBlock *pnoP);
        void verb_dbupdate(PNOBlock *pnoP);
#endif
        

#ifdef __MC68K__        
        void verb_draw_bitmap();
#else
        void verb_draw_bitmap(PNOBlock *pnoP);
#endif

#ifdef __MC68K__
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
#else
        void verb_dowhile(PNOBlock *pnoP);
        void verb_dountil(PNOBlock *pnoP);
        void verb_menureset(PNOBlock *pnoP);
        void verb_menuerase(PNOBlock *pnoP);
        void verb_menudraw(PNOBlock *pnoP);
        void verb_sub(PNOBlock *pnoP);
        void verb_end_sub(PNOBlock *pnoP);
        void verb_call(PNOBlock *pnoP);
        void verb_end_function(PNOBlock *pnoP);
#endif

#ifdef __MC68K__
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
#else
        void verb_controlsetstatus(PNOBlock *pnoP);
        void verb_controlsetstatusNew(PNOBlock *pnoP);
        void verb_controlsetlabel(PNOBlock *pnoP);
        void verb_controlhideorshow(PNOBlock *pnoP);
        void verb_fieldsettext(PNOBlock *pnoP);
        void verb_fieldsetmaxchars(PNOBlock *pnoP);
        void verb_listadditem(PNOBlock *pnoP);
        void verb_listsetselected(PNOBlock *pnoP);
        void verb_initAVariableValue(PNOBlock *pnoP);
#endif

//#ifdef ORG_SWB
        void verb_setnumvarsfromheap();   //added 06102002
//#endif


        void verb_clearscreentextfields();    //added 06102002


        //void verb_mem_debug()       ;
        void verb_start_debug();
        void verb_end_debug();
        
#ifdef __MC68K__
        void verb_negate();
#else
        void verb_negate(PNOBlock *pnoP);
#endif
        
#ifdef __MC68K__
        void verb_add ()            ;
        void verb_display()         ;
        void verb_divide()          ;
        void verb_return()          ;
        void verb_if()              ;
        void verb_multiply ()       ;
        void verb_gosub()         ;
        void verb_stop ()           ;
#else
        void verb_add (PNOBlock *pnoP)            ;
        void verb_display(PNOBlock *pnoP)         ;
        void verb_divide(PNOBlock *pnoP)          ;
        void verb_if(PNOBlock *pnoP)              ;
        void verb_multiply(PNOBlock *pnoP)       ;
        void verb_gosub(PNOBlock *pnoP)         ;
        void verb_stop(PNOBlock *pnoP)           ;
#endif

#ifdef __MC68K__
        void verb_subtract()        ;
        void verb_return()          ;
        void verb_goto()            ;
#else
        void verb_subtract(PNOBlock *pnoP)        ;
        void verb_return(PNOBlock *pnoP)          ;
        void verb_goto(PNOBlock *pnoP);
#endif

#ifdef __MC68K__
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
#else
        void verb_beep(PNOBlock *pnoP);
        void verb_popupclear(PNOBlock *pnoP);
        void verb_delay(PNOBlock *pnoP);
#endif

#ifdef __MC68K__
        void verb_exponentiation()    ;
        void verb_not_logic_oper()    ;
        void  verb_relat_logic_oper()  ;
        void  verb_logic_class_tests() ;
        void verb_and()               ;
        void verb_or()                ;
#else
        void verb_exponentiation(PNOBlock *pnoP)    ;  // EMP
        void verb_not_logic_oper(PNOBlock *pnoP)    ;  // EMP
        void verb_relat_logic_oper(PNOBlock *pnoP);  // EMP
        void  verb_logic_class_tests(PNOBlock *pnoP) ;
        void verb_and(PNOBlock *pnoP);  // EMP
        void verb_or(PNOBlock *pnoP);  // EMP
#endif

#ifdef __MC68K__
        void  verb_special_arith_store() ;
        void verb_getPen();
        void verb_compute()             ;
        void verb_check_on_size_error() ;
#else
        void  verb_special_arith_store(PNOBlock *pnoP) ;
        void verb_getPen(PNOBlock *pnoP);
        void  verb_compute(PNOBlock *pnoP) ;
#endif           

#ifdef __MC68K__
        void  verb_clear_frac_dgts()     ;
        void verb_nextscreen();
		void verb_nextscreenwithvariable();  //added 06102002
		void verb_redraw();
        void  verb_cursor_id();
        void  verb_redraw_id();
#else
        void  verb_clear_frac_dgts(PNOBlock *pnoP)     ;
        void verb_nextscreen(PNOBlock *pnoP);
		void verb_nextscreenwithvariable();  //added 06102002
		void verb_redraw(PNOBlock *pnoP);
        void  verb_cursor_id(PNOBlock *pnoP);
        void  verb_redraw_id(PNOBlock *pnoP);
#endif

#ifdef __MC68K__
        void  verb_concat_two_strings();
        void verb_startfor();
        void verb_continuefor();
        void verb_next();
#else
        void verb_concat_two_strings(PNOBlock *pnoP);
        void verb_startfor(PNOBlock *pnoP);
        void verb_continuefor(PNOBlock *pnoP);
        void verb_next(PNOBlock *pnoP);
#endif
#ifdef __MC68K__
        void verb_do();
        void verb_until();
        void  verb_while();
        void verb_loop();
        void verb_exitdo();
        void verb_exitfor();
#else
        void verb_do(PNOBlock *pnoP);
        void verb_until(PNOBlock *pnoP);
        void  verb_while(PNOBlock *pnoP);
        void verb_loop(PNOBlock *pnoP);
        void verb_exitdo(PNOBlock *pnoP);
        void verb_exitfor(PNOBlock *pnoP);
#endif
#ifdef __MC68K__
        void verb_launchprogram();
        void  verb_cursor();
#endif


#ifdef __MC68K__
        void  verb_errmsg();
#else
        void verb_errmsg(PNOBlock *pnoP);
#endif
        
#ifdef __MC68K__
        void  verb_end_logic_cond();
        void  verb_function();
        void verb_start_new_parag() ;
        void verb_start_new_stmt()  ;
        void illegal_op_code();
#else
        void  verb_end_logic_cond(PNOBlock *pnoP);

#endif

// Grid function prototypes

#ifdef __MC68K__

void SetFieldText( UInt nFieldID, const CharPtr pSrcText, Int nMaxSize, Boolean bRedraw);
extern void dbugx(double* x,char*identifier);
           void gridGetValueMatrix(FormPtr,VoidPtr);    
			void gridGetCellMatrix(FormPtr frm,VoidPtr controlPtr);  
void gridSetColWidth(FormPtr frm,VoidPtr controlPtr,double* paramPtr);
void gridSetSelectedRow(FormPtr frm,VoidPtr controlPtr,double* paramPtr);
void gridSetSelectedCol(FormPtr frm,VoidPtr controlPtr,double* paramPtr);
void gridSetSelectedText(FormPtr frm,VoidPtr controlPtr,char* paramPtr);
void gridSetRows(FormPtr frm,VoidPtr controlPtr,double* paramPtr);
void gridSetCellMatrix(FormPtr frm,VoidPtr controlPtr,double* paramPtr);
void gridGetRowData(FormPtr frm,VoidPtr controlPtr);
void gridGetSelectedRow(FormPtr frm,VoidPtr controlPtr);
void gridGetSelectedCol(FormPtr frm,VoidPtr controlPtr);
void gridGetRows(FormPtr frm, VoidPtr controlPtr);
void gridGetSelectedValue(FormPtr frm,VoidPtr controlPtr);
extern void gridGetSelectedText(FormType* frmPtr,VoidPtr controlPtr);      //added 09242003
void gridClear(FormPtr frm,VoidPtr controlPtr);
void gridSetRowData(FormPtr frm,VoidPtr controlPtr,double* paramPtr);
void gridAdd(FormPtr frm,VoidPtr controlPtr);
Int16 gridBindToDatabase(FormPtr frm,VoidPtr controlPtr);
void gridColType(FormPtr frm,VoidPtr controlPtr );
#else
extern void redrawGrid(PNOBlock *pnoP, struct ObjectData *objPtr);  // 09242003
void gridSetCellMatrix(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr,double* paramPtr);
void gridSetColWidth(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr,double* paramPtr);
void gridSetDatabaseFields(PNOBlock *pnoP, struct dbType *db,DmOpenRef dbr,UInt16 dbRecNo);
void gridSetSelectedRow(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr,double* paramPtr);
void gridSetSelectedCol(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr,double* paramPtr);
void gridSetSelectedText(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr,char* paramPtr);
void gridSetRows(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr,double* paramPtr);
void gridGetColWidth(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr);
void gridGetCols(PNOBlock *pnoP, Arg *arg4, FormPtr frm, VoidPtr controlPtr);
void gridGetRowData(PNOBlock *pnoP, Arg *arg4, FormPtr frm,VoidPtr controlPtr);
void gridGetSelectedRow(PNOBlock *pnoP, Arg *arg4, FormPtr frm,VoidPtr controlPtr);
void gridGetSelectedCol(PNOBlock *pnoP, Arg *arg4, FormPtr frm,VoidPtr controlPtr);
void gridGetRows(PNOBlock *pnoP, Arg *arg4, FormPtr frm, VoidPtr controlPtr);
void gridGetSelectedValue(PNOBlock *pnoP, Arg *arg4, FormPtr frm,VoidPtr controlPtr);
extern void gridGetSelectedText(PNOBlock *pnoP, Arg *outArg, FormType* frmPtr,VoidPtr controlPtr);      //added 09242003
void gridClear(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr);
void gridSetRowData(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr,double* paramPtr);
void gridAdd(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr);
Int16 gridBindToDatabase(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr);
void gridColType(PNOBlock *pnoP, FormPtr frm,VoidPtr controlPtr );
           void gridGetValueMatrix(PNOBlock *, Arg *arg4, FormPtr,VoidPtr);    
			void gridGetCellMatrix(PNOBlock *, Arg *arg4, FormPtr frm,VoidPtr controlPtr);
#endif

#ifdef __MC68K__
extern char *devel_address(struct dataelem *arg, UInt16 s1,UInt16 s2,UInt16 s3);
#else
extern char *devel_address(PNOBlock *pnoP, struct dataelem *arg, UInt16 s1,UInt16 s2,UInt16 s3);
#endif


#ifdef __MC68K__

void OutOfMemory(int i);                //inserted 05212003
unsigned int serialBufferSize;
char*   serialBufferPtr;

#ifndef ARM
typedef void opCodeFunc();
opCodeFunc *  PNO(op_func)[256];
#endif


#ifndef ARM
Word lastSubOrFunctionId;
#endif

#ifndef ARM
Int16      dbNo;
#endif

char*    firstString=0;
#ifndef ARM
extern Int16      debug_on;  //0=off 1=on
extern UInt     serRef;
#endif

Boolean  gOldSerialManager;						//02.27.02 GH	

#ifndef ARM
extern UInt8    gSerialState;							//03.06.02 GH	
#endif

EventPtr evptr;
char     dummyCode[15];
#ifndef ARM
char *   codePtr;
char*    p3;
VoidHand h3;
#endif
extern char terminationAction;
extern int  mem_debug_sw;
extern long automated_redraw_time;
extern char automated_redraw_sw;
extern struct view_record * automated_view;
extern DmOpenRef CallerDB;


DATE julian_date(int day, int month , int year );

#define MAX_ARITH_PLUS_1          arith_work_de_max+1
#define MAX_ARITH_STRING_PLUS_1   arith_work_de_max+string_work_de_max+1

#ifndef ARM
unsigned char op_code;
extern    Int16 logic_value;
#endif

unsigned long load_index_occ;

extern char master_quit_sw;
int         btrieve_cur_rec_len;

    char *ad;

MdmInfoType modemInfo;    //info about modem parameters


#ifndef ARM
 long moduleCntr;
#endif

 VoidHand forHandle;
 //06102002VoidHand forHandleSave;
#ifndef ARM
extern VoidPtr forPtrSave;
#endif
#ifdef ORG_NSB
#include "nsbasic.c"
#endif

#endif

#ifdef __MC68K__

#endif


/********************************************************************************************/
#ifdef __MC68K__
void verb_function()
#else
void verb_function(PNOBlock *pnoP)  // EMP
#endif
{  
	// Cleaned up this section // 01/29/2001 MMD
#ifdef __MC68K__
	UInt16 it = find_integer();
	UInt16 no = find_integer();
#else
	UInt16 it;
	UInt16 no;
	Arg args[5];

    it = find_integer(pnoP);
	no = find_integer(pnoP);
#endif

//StrPrintF(debug,"verb_func it=%d no=%d",it,no);
//SysFatalAlert(debug);
	// Nested these calls for speed // 01/29/2001 MMD
	// These are the arguments
#ifdef __MC68K__
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
#else
    PNO(args) = args;
	if( no > 0 )
	{
    	find_arg_PNO(pnoP, &(PNO(args)[0]));
    	if( no > 1 )
    	{
    	    find_arg_PNO(pnoP, &(PNO(args)[1]));
			if( no > 2 )
			{
    	        find_arg_PNO(pnoP, &(PNO(args)[2]));
				if( no > 3 )
				{
    	            find_arg_PNO(pnoP, &(PNO(args)[4]));
				}
			}
		}
	}
#endif

#ifdef __MC68K__
	// This is the return value
	find_arg_4();
#else
    find_arg_PNO(pnoP, &(PNO(args)[3]));
#endif
#ifdef __MC68K__
	if( ( it > 399 ) && ( it < 499 ) )
		find_ctlid(true);
	if( ( it > 499 ) && ( it < 600 ) )
		chkMathLibOpen();
	if( ( it > 599 ) && ( it < 649 ) )		// 02/27/2001 MMD
		find_ctlid(true);  //actually table id
#else
	if( ( it > 399 ) && ( it < 499 ) )
		find_ctlid(pnoP, true);
	if( ( it > 499 ) && ( it < 600 ) )
		Glue_chkMathLibOpen(pnoP);
	if( ( it > 599 ) && ( it < 649 ) )		// 02/27/2001 MMD
		find_ctlid(pnoP, true);  //actually table id
#endif

#ifdef __MC68K__
	verb_function_doit( it );
#else
    PNO(nArgs) = no;
    verb_function_doit(pnoP, it);
#endif
} // verb_function

#ifdef __MC68K__
//just a transfer call to avoid 32k limit
// EMP changed to avoid problems with macros
void restore_int_val(int res,struct dataelem* arg1x,double *arg1_valx,
       unsigned int  arg1_occ1x,unsigned int arg1_occ2x,unsigned int arg1_occ3x)
{
    restore_integ_value( res, arg1x,(double *)arg1_valx, arg1_occ1x, arg1_occ2x, arg1_occ3x);

}
#endif

/********************************************************************************************/
#ifdef __MC68K__
Int16 codeexec2(Word objId,unsigned long offset)  // EMP
#else
Int16 codeexec2(PNOBlock *pnoP, Word objId,unsigned long offset)   
#endif
{
		Int16 sz;
		Int16 result;
		VoidHand newCodeHand;
		struct codeBlock*  newCodePtr;
		VoidHand h2;
		VoidPtr p2;
		UInt idx2;
		VoidPtr tempPtr;
		Int16 err;
		//UInt16 debug_instr_ctr;
		unsigned short s;
						
		PNO(lastSubOrFunctionId) = objId;
		 
		//StrPrintF(debug,"at codeexec id =%d codePtr=%lu",objId,PNO(codePtr));
		//SysFatalAlert(debug);


	  if(objId==0)
	  {
	  	return(0);

	  }
//StrPrintF(debug," more processing for id=%d",objId);
//SysFatalAlert(debug);


#ifdef __MC68K__
      clearLockedArgs();
#else
      clearLockedArgs(pnoP);
#endif

      if(PNO(codeBlockPtr)->id==50000) PNO(instr_ctr)=0;  //dummy control for root level
      sz=sizeof(struct codeBlock);
//if(debug_sw){
//StrPrintF(debug,"sz=%d",sz);
//SysFatalAlert(debug);      
//}


      newCodeHand=MemHandleNew(sz);
      if(newCodeHand==0) OutOfMemory(6043);    //05282003
      newCodePtr=(struct codeBlock*)MemHandleLock(newCodeHand);
      newCodePtr->prevCodePtr=PNO(codeBlockPtr);
 
#ifndef __MC68K__
	  /* Put old codeblock back to 68K alignment */
      SwapCodeBlock(PNO(codeBlockPtr));
#endif

      if(PNO(codeBlockPtr) != 0)      					//added 04012005
      {                         					//added 04012005 
         PNO(codeBlockPtr)->cur_stmt_no = PNO(cur_stmt_no);   //added 04012005
//StrPrintF(debug,"setting cur_stmt_no to %d",cur_stmt_no);
//SysFatalAlert(debug);
      }                          					//added 04012005

      
      PNO(codeBlockPtr)=newCodePtr;
      PNO(codeBlockPtr)->id=objId;
      PNO(codeBlockPtr)->offset=offset;
      PNO(codeBlockPtr)->p3=PNO(p3);
      PNO(codeBlockPtr)->h3=PNO(h3);
      PNO(codeBlockPtr)->numberParas=PNO(numberParas);
      PNO(codeBlockPtr)->paragTbl=PNO(paragTbl);
      PNO(codeBlockPtr)->codePtr=PNO(codePtr);
      PNO(codeBlockPtr)->instr_ctr=PNO(instr_ctr);

//if(debug_sw){
//StrPrintF(debug,"setting PNO(codeBlockPtr)=%lu codeptr=%lu PNO(instr_ctr)=%d",
//(unsigned long)(PNO(codeBlockPtr)),(unsigned long)(PNO(codePtr)),PNO(instr_ctr));
//SysFatalAlert(debug);
//}

      PNO(codeBlockPtr)->oldOffset=PNO(theCodeOffset);
      PNO(h3)=(MemHandle)DmGetResource(rscTag,(ULong)objId);

      if(PNO(h3)==0)
      {

//StrPrintF(debug,"no code for %d",objId);
         //no obj code
         PNO(h3)=PNO(codeBlockPtr)->h3;
         PNO(codeBlockPtr)=(struct codeBlock*)PNO(codeBlockPtr)->prevCodePtr;
#ifndef __MC68K__
      	SwapCodeBlock(PNO(codeBlockPtr));  // Put it back to Strongarm
#endif
         MemPtrUnlock(newCodePtr);
         MemHandleFree(newCodeHand);
         return(0);

      }

//StrPrintF(debug,"found code for %d",objId);
//SysFatalAlert(debug);
      ++PNO(moduleCntr);
      PNO(p3)=(char*)MemHandleLock(PNO(h3));
      PNO(codeBlockPtr)->newp3=PNO(p3);
      PNO(codeBlockPtr)->newh3=PNO(h3);
      PNO(numberParas)=*( (Int16*)PNO(p3));
#ifdef __MC68K__
      PNO(paragTbl)=(char*)PNO(p3)+*((UInt16*)((char*)PNO(p3)+2)); //pts to para offsets  //3132001
#else
      s = *((UInt16*)((char*)PNO(p3)+2));
      PNO(paragTbl)=(char*)PNO(p3)+ByteSwap16(s); //pts to para offsets  //3132001
#endif
     PNO(theCodeOffset)=offset;

      PNO(codePtr)=(char*)PNO(p3)+offset;
//if(debug_sw){
//StrPrintF(debug,"in codeexec p3=%lu offset=%lu codeptr=%lu",
//(unsigned long)p3,offset,(unsigned long)codePtr);
//SysFatalAlert(debug);      
//}

    if(*((char*)PNO(codePtr))==0x00)
    {
//StrPrintF(debug,"1st char of obj code was 0 -- exiting");
//SysFatalAlert(debug);
         goto getOutA;
    }

//dbug("codeexec --going to more processing");

#ifdef __MC68K__

    result=more_processing( );

#else
	result=more_processing(pnoP);
#endif

getOutA:

//if(debug_sw){
//dbug("basc--after code executed");
//}
      PNO(h3)=PNO(codeBlockPtr)->newh3;
      PNO(p3)=(char*)PNO(codeBlockPtr)->newp3;
      MemHandleUnlock(PNO(h3));
      DmReleaseResource(PNO(h3));
      tempPtr=PNO(codeBlockPtr);
      PNO(p3)=(char*)PNO(codeBlockPtr)->p3;
      PNO(h3)=PNO(codeBlockPtr)->h3;

      PNO(numberParas)=PNO(codeBlockPtr)->numberParas;
      PNO(paragTbl)=(char*)PNO(codeBlockPtr)->paragTbl;
      PNO(theCodeOffset)=PNO(codeBlockPtr)->oldOffset;
      PNO(codePtr)=(char*)PNO(codeBlockPtr)->codePtr;
      PNO(instr_ctr)=PNO(codeBlockPtr)->instr_ctr;
      PNO(codeBlockPtr)=(struct codeBlock*)PNO(codeBlockPtr)->prevCodePtr;
#ifndef __MC68K__
      SwapCodeBlock(PNO(codeBlockPtr));
#endif
      MemPtrUnlock(tempPtr);
      MemPtrFree(tempPtr);

      --PNO(moduleCntr);
            
      return(1);
}

#ifdef __MC68K__
/* EMP Glue because I don't think that the flp functions work from PACE */
Int16 flpftoa(double a, Char *s);
Int16 flpatof(Char *s, double *a);
Int32 serialreceivecheck(UInt16 serRef);
UInt16 wingetcoordinatesystem(void);
UInt32 datetodays(UInt16 year, UInt16 month, UInt16 day);
#endif

extern void gridDrawCallback (VoidPtr grid, short row, short col2, RectanglePtr bounds );

/********************************************************************************************/

#ifdef __MC68K__
Int16 codeexec(Word objId,unsigned long offset)  // EMP
{
	void code_initialize();

	PNO(lastSubOrFunctionId) = objId;
    if(objId==0)  return(0);
    if(init_first_time==0)
    {
        code_initialize();  /* *******go init to begin******** */
    }

#ifdef ARM

    if (mainPNOH && PNO(applVersionInteg) >= 400)
    {

        pnoP -> args = aac.allArgs;
        pnoP -> flpftoa = flpftoa;
        pnoP -> flpatof = flpatof;
        pnoP -> serialreceivecheck = serialreceivecheck;
        pnoP -> wingetcoordinatesystem = wingetcoordinatesystem;
        pnoP -> datetodays = datetodays;
        pnoP -> function_doit_from_PNO = function_doit_from_PNO;
        pnoP -> database_compare = database_compare;
        pnoP -> codeexec = (void *) codeexec2;
        pnoP -> setupADataelem = setupADataelem;
        pnoP -> CtlGlueGetControlStyle = CtlGlueGetControlStyle;
        pnoP -> FrmGlueGetLabelFont = FrmGlueGetLabelFont;
        pnoP -> CtlGlueGetControlStyle = CtlGlueGetControlStyle;
        pnoP -> chkMathLibOpen = chkMathLibOpen;
        pnoP -> commonEndCapture = commonEndCapture;
        pnoP -> commonErase = commonErase;
        pnoP -> commonSignatureDisplay = commonSignatureDisplay;
        pnoP -> commonStartCapture = commonStartCapture;
        pnoP -> gridDrawCallback = gridDrawCallback;
   
        pnoP -> objId = objId;
        pnoP -> offset = offset;

        return PnoCall(&mainPNOD, pnoP);
    }
    else
    {
        return codeexec2(objId, offset);
	}
#else

    return codeexec2(objId, offset);

#endif
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
    *ad1 = *((unsigned char*)(PNO(codePtr))+PNO(instr_ctr)++);
    
    //03012002 *(ad1+1)=find_char();
    *(ad1+1) = *((unsigned char*)(PNO(codePtr))+PNO(instr_ctr)++);
    
    //06/01/2002 if ( i == 0 )
     //06/01/2002   arg= (struct dataelem *)null_ptr ;
    //06/01/2002  else
      arg = elem_tbl_ptr(i);
    
    
             *s1=0;
             *s2=0;
             *s3=0;
    return(arg);
}
#endif

/********************************************************************************************/
#ifdef __MC68K__
void tooLarge(Int16 tbl_no, UInt16 sub, UInt16 max)
#else
void tooLarge(PNOBlock *pnoP, Int16 tbl_no, UInt16 sub, UInt16 max)
#endif
{
#ifdef __MC68K__
  char msg[128];
  StrPrintF(msg,"Subscript too large..variable=%d sub=%lu max=%lu",
     tbl_no,sub , max );
  misc_text_abort(msg);
#endif
}

#ifdef __MC68K__
/********************************************************************************************/
#endif

#ifdef __MC68K__
extern UInt16 find_subscript()                /*---find next subscript in code---*/
#else
extern UInt16 find_subscript(PNOBlock *pnoP)
#endif
{
    UInt16 sub;
#ifdef __MC68K__
    sub = find_integer();
#else
    sub = find_integer(pnoP);
#endif
    return(sub);
}

/********************************************************************************************/
#ifndef __MC68K__
/**
    EMP
    Works like find_arg, but stuffs it into an arg, including the val, and keeps
    the struct PNO-aligned
  */
void find_arg_PNO(PNOBlock *pnoP, Arg *argRet)
{
    UInt16 sub;
    char  msg[80];
    struct dataelem *arg=(struct dataelem*)NULL;
    UInt16 i, lo, hi;
    unsigned char the_char;
    unsigned char *ad1;
    UInt16 mv1;
    UInt32 l;
    struct dataelem *sde;

    /* Get the arg */
    hi = *((unsigned char*)(PNO(codePtr))+PNO(instr_ctr)++);
    lo = *((unsigned char*)(PNO(codePtr))+PNO(instr_ctr)++);
    i = (hi << 8) + lo;


    arg = elem_tbl_ptr(pnoP, i);
    

    /* Zero everything */
    argRet -> occ1 = 0;
    argRet -> occ2 = 0;
    argRet -> occ3 = 0;
    argRet -> sde1 = 0;
    argRet -> sde2 = 0;
    argRet -> sde3 = 0;

    mv1 = arg ? arg -> max_no_values1 : 0;
    mv1 = ByteSwap16(mv1);

    if( (arg != NULL) && (mv1 > 1) )
    {
        UInt16 mv2, occ1;
        mv2 = arg -> max_no_values2;

        mv2 = ByteSwap16(mv2);
        
        sub = find_subscript(pnoP);

        if(sub == 0) //  means that used array w/o subs
        {
            UInt16 mv3;

            mv3 = arg -> max_no_values3;
            mv3 = ByteSwap16(mv3);

            argRet -> occ1 = 0;
            argRet -> occ2 = 0;
            argRet -> occ3 = 0;
            if(mv2>1) find_subscript(pnoP);
            if(mv3>1) find_subscript(pnoP);

            argRet -> dataElem = arg;
            if(arg != NULL)
                argRet -> val = devel_address(pnoP, arg, 0, 0, 0);
            return;
        }
        
        argRet -> sde1 = sde = elem_tbl_ptr(pnoP, sub);
        set_sub(pnoP, 1, arg, &occ1, sde);
        argRet -> occ1 = occ1;
        
        {
           tooLarge(pnoP, arg->tbl_no, occ1 + 1, mv1);
        }
        
        if( (arg != NULL ) && (mv2 > 1))
        {
            UInt16 mv3 = arg -> max_no_values3;
            UInt16 occ2;
            mv3 = ByteSwap16(mv3);

            sub = find_subscript(pnoP);

            if(sub == 0)
            {
                if(mv3 > 1) find_subscript(pnoP);
                argRet -> dataElem = arg;
                if(arg != NULL)
                    argRet -> val = devel_address(pnoP, arg, occ1, 0, 0);
                return;
            }
            argRet -> sde2 = sde = elem_tbl_ptr(pnoP, sub);
            set_sub(pnoP, 2, arg, &occ2, sde);
            argRet -> occ2 = occ2;

            if(occ2 > (mv2 - 1))
            {
                tooLarge(pnoP, arg->tbl_no,(occ2 + 1), mv2);
            }
            if( (arg != NULL) && (mv3 > 1))
            {
                UInt16 occ3 = argRet -> occ3;
                occ3 = ByteSwap16(occ3);            
                sub = find_subscript(pnoP);
                
                if(sub==0)
                {
                    argRet -> dataElem = arg;
                    if(arg != NULL)
                        argRet -> val = devel_address(pnoP, arg, occ1, occ2, 0);
                    return;
                }

                argRet -> sde3 = sde = elem_tbl_ptr(pnoP, sub);
                set_sub(pnoP, 3, arg, &occ3, sde);
                argRet -> occ3 = occ3;
                
                if(occ3 > (mv3 - 1))
                {
                    tooLarge(pnoP, arg->tbl_no, occ3 + 1, mv3);
                }
                argRet -> dataElem = arg;
                if(arg != NULL)
                    argRet -> val = devel_address(pnoP, arg, occ1, occ2, occ3);
                return;
            }
            else
            {
                argRet -> dataElem = arg;
                if (arg != NULL)
                    argRet -> val = devel_address(pnoP, arg, occ1, occ2, 0);
                return;
            }
        }
        else
        {
            argRet -> dataElem = arg;
            if (arg != NULL)
                argRet -> val = devel_address(pnoP, arg, occ1, 0, 0);
            return;
        }
    }

    argRet -> dataElem = arg;
    if(arg != NULL)
        argRet -> val = devel_address(pnoP, arg, 0, 0, 0);
    return;
}
#endif

                                  /*-------set any argument-------*/

#ifdef __MC68K__
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
    *ad1 = *((unsigned char*)(PNO(codePtr))+PNO(instr_ctr)++);
    
    //03012002 *(ad1+1)=find_char();
    *(ad1+1) = *((unsigned char*)(PNO(codePtr))+PNO(instr_ctr)++);
    
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
                   tooLarge(arg->tbl_no,((*s3)+1) ,  arg->max_no_values3 );
                }
              }
            }
    }
getOutB:
    
//dbug("fff");     
    return(arg);
    
}
#endif


/********************************************************************************************/
#ifdef __MC68K__
extern void set_sub(Int16 n, struct dataelem*arg, UInt16 *sub_val,struct dataelem* sub_de)         /*--set a sub from code--*/
#else
extern void set_sub(PNOBlock *pnoP, Int16 n, struct dataelem*arg, UInt16 *sub_val,struct dataelem* sub_de)         /*--set a sub from code--*/
#endif
{
//char test[80];
    char msg[81];

    UInt16 reg_value;
    
    if(sub_de!=NULL) 
    {
#ifdef __MC68K__
       misc_getint(sub_de,0,0,0,&reg_value);
#else
       misc_getint(pnoP, sub_de,0,0,0,&reg_value);
#endif

       if((reg_value)<=0)
       {
#ifdef __MC68K__
           StrPrintF(msg,"Found illegal subscript = %u",reg_value);
           misc_text_abort( msg );
#else
           char *b = strcpy(msg, "Found illegal subscript = ");
           StrIToA(b, reg_value);
           misc_text_abort(pnoP, msg );
#endif
           
       }
       else *sub_val = reg_value - 1;        
    }
    else *sub_val=0;
    
    return;
}

/********************************************************************************************/
Int16 basc_dbGetInt(char* ptr)  // EMP
{
    UInt16 hi, lo;
    
    hi = *(unsigned char *)ptr;
    lo = *(unsigned char *)(ptr + 1);
    return (hi << 8) | lo;
}

#ifdef __MC68K__
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
#else
void verb_divide(PNOBlock *pnoP)
{
    char round_sw;
    double reg_a, reg_b;
    Arg arg1, arg2, arg3, arg4;

    find_arg_PNO(pnoP, &arg1);
    find_arg_PNO(pnoP, &arg2);
    find_arg_PNO(pnoP, &arg3);
    
    round_sw = find_char(pnoP);

    reg_b = ReadUnaligned64(arg1.val);
    reg_a = ReadUnaligned64(arg2.val);
    
    if (reg_b == 0.0)
    {
        misc_errmsg(pnoP, "Error divide by 0");
        reg_a = 0.0;
    }
    else
        reg_a /= reg_b;
        
    reg_a = SwapDouble(reg_a);
    
	misc_stodbl(pnoP, arg3.dataElem, arg3.occ1, arg3.occ2, arg3.occ3, &reg_a);
	
	// EMP I don't understand this, why another arg?
    find_arg_PNO(pnoP, &arg4);
}

#endif

#ifdef __MC68K__
Int16 more_processing()
#else
Int16 more_processing(PNOBlock *pnoP)     // EMP
#endif
{
	Int16 retVal;
    PNO(instr_ctr)=0; //skip length on front

#ifdef __MC68K__
    retVal = executeSomeCode();
#else
	retVal = executeSomeCode(pnoP);
#endif
	return retVal;
}

#ifdef __MC68K__
Int16 executeSomeCode()
#else
Int16 executeSomeCode(PNOBlock *pnoP)     // EMP
#endif
{
    //UInt16     debug_instr_ctr;
    UInt16 instr_ctr_save=PNO(instr_ctr);
#ifndef __MC68K__
    Int32 verbOffset;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
    unsigned long offset;
    
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);
#endif

    PNO(logic_value)=0;
//debug_instr_ctr=PNO(instr_ctr);
//if(debug_sw){
//StrPrintF(debug,"in more-proc PNO(instr_ctr)=%d",PNO(instr_ctr));
//SysFatalAlert(debug);
//}

//if(debug_sw){
//StrPrintF(debug,"1st op code is %d at offset=%d",*((char*)theInstruc),PNO(instr_ctr));
//SysFatalAlert(debug);
//}

    if(*((char*)PNO(codePtr)+PNO(instr_ctr))==0x00)
    {
getOutB:
       PNO(instr_ctr)=instr_ctr_save;
	 return(0);
    }
/*-----
StrPrintF(debug,"first_para_ptr=%p",first_para_tbl_ptr);
SysFatalAlert(debug);
-------*/
process_code :                  /*-------main processing loop------*/
#ifdef __MC68K__
    PNO(op_code) = find_char();
#else
    PNO(op_code) = find_char(pnoP);
#endif


    if(PNO(op_code)==0x00)  //this means 00 wont be caught as illegal op code
    {
quitIt:
#ifdef __MC68K__
       clearLockedArgs();
#else
       clearLockedArgs(pnoP);
#endif
       return(PNO(logic_value));  /*done*/
    }
     if (PNO(op_code)==0xff)  goto quitIt;
      if (PNO(op_code)==0x5d)
     {
//02042006 SysFatalAlert("Found 5d op-code to end where clause");
         goto quitIt;        //bindToDatabase --end of a where clause 
     }
    /*now use op code to choose a function address from */
    /* array of function pointers (PNO(op_func))             */
    /*An illegal op-code will go to "illegal_op_code"    */

//StrPrintF(debug,"going to exec opcode=%d ahead=%d",PNO(op_code),*((char*)codePtr+184));
//SysFatalAlert(debug);

#if 0
	//if (PNO(debugTest))
    {
        char cb[30];
        unsigned long l = (unsigned long) PNO(op_code);

        StrIToA(cb, l);
        WinDrawChars("    ", 4, 60, 1);
        WinDrawChars(cb, StrLen(cb), 60, 1);
    }
#endif

#ifdef __MC68K__
    /*now use op code to choose a function address from */
    /* array of function pointers (PNO(op_func))             */
    /*An illegal op-code will go to "illegal_op_code"    */
    (*PNO(op_func)[ (Int16)PNO(op_code) ] )() ; /*this calls the function */
#else

    /* EMP If there is a PNO function, do it, else fall back to 68K */
    offset = pnoP -> op_func_PNO[PNO(op_code)];
	
    if (offset)
    {
        VerbType verb;
        verb = /*__ARMlet_Take_Func_Addr__*/((void *) (offset + BASIS));
        (*verb)(pnoP);
    }
    else 
    {
        unsigned long ret;
        /* Maybe it's in the verb PNO? */
        ret = ((*PNO(verbPNO))(PNO(emulStateP), pnoP, PNO(call68KFuncP)));
        
        if (!ret)
        {
        	/* Maybe it's in the DB PNO? */
        	ret = ((*PNO(dbPNO))(PNO(emulStateP), pnoP, PNO(call68KFuncP)));
        }
        
        if (!ret)
        {
            void *p;
            char buf[1];     // Dummy buffer
         
#if 0
           if (0 &&
                PNO(op_code) != 5 &&   // Beep doesn't seem to work from PNO
                PNO(op_code) != 69 &&  // FillRectangle uses unsafe structs
                PNO(op_code) != 70 &&  // DrawRectangle uses unsafe structs
                1)
             {
                char cb[30];
                unsigned long l = (unsigned long) PNO(op_code);

                WinDrawChars("        ", 8, 60, 1);
                StrIToA(cb, l);
                WinDrawChars(cb, strlen(cb), 60, 1);
            }
#endif

            p = PNO(op_func)[PNO(op_code)];
            p = (void *)ByteSwap32((unsigned long)p);

            SwapCodeBlock(PNO(codeBlockPtr));
            SwapUserData(pnoP);
            ((call68KFuncP)(emulStateP, 
                (unsigned long) p, 
                buf,
                0));
            SwapUserData(pnoP);
            SwapCodeBlock(PNO(codeBlockPtr));
        }
    }
#endif

#ifdef __MC68K__
    clearLockedArgs();
#else
    clearLockedArgs(pnoP);
#endif

    goto process_code;
}

#ifdef __MC68K__
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
#endif

/********************************************************************************************/

#ifdef __MC68K__
void clearLockedArgs()
{
    if (arg1 !=(struct dataelem*)null_ptr) 
    { 
      arg1=(struct dataelem*)null_ptr;
    }
    if (arg2 !=(struct dataelem*)null_ptr) 
    {
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
#else
void clearLockedArgs(PNOBlock *pnoP)    // EMP
{
}
#endif


/********************************************************************************************/
// EMP changed to avoid conflicting with macros
#ifdef __MC68K__
extern Int16 compare_args(struct dataelem*arg1x, double* input_arg1_val,
      struct dataelem*arg2x, double* input_arg2_val, Int16 oper)
#else
extern Int16 compare_args(PNOBlock *pnoP, struct dataelem*arg1x, double* input_arg1_val,
      struct dataelem*arg2x, double* input_arg2_val, Int16 oper)
#endif
    
{
    char * ad_2cnd=(char*)NULL;

    Int16 jj;
    double* arg1_valx= (double*)input_arg1_val;
    double* arg2_valx= (double*)input_arg2_val;
    char *ad1=(char*)NULL;
    char *ad2=(char*)NULL;
    char *ad3=(char*)NULL;
    char chr;

    char *ad4=(char*)NULL;
    struct dataelem *temp_arg=(struct dataelem*)NULL;
    Int16 argum_switch;
    Int16 i,j;
    Int16 l1,l2;
    char msg[162];
#ifndef __MC68K__
    double reg_a, reg_b;
#endif

/*--------
StrPrintF(debug,"at compare_args arg1_kind=%c arg2_kind=%c oper=%i",arg1->kind,arg2->kind,oper);
test_debug(debug);
--------*/
    argum_switch=0;


    if (arg1x->kind !='s')
	   goto comp_num;
    else goto comp_alnum;
comp_num :
    if(arg2x==(struct dataelem*)NULL) goto comp_num_null;
     if (arg2x->kind!='s')
	   goto comp_num_num;
    else goto comp_num_alnum;
comp_num_num :

#ifdef __MC68K__   
    reg_a=*((double*)arg1_valx);
    reg_b=*((double*)arg2_valx);
#else
    reg_a = ReadUnaligned64((char *) arg1_valx);
    reg_b = ReadUnaligned64((char *) arg2_valx);
#endif

/*----
StrPrintF(debug,"comparing num-to-num  %lf to %lf",reg_a,reg_b);
test_debug(debug);
-----*/
    if( reg_a > reg_b) goto comp_1hi;
    else if(reg_a < reg_b) goto comp_1low;
    else goto comp_1_2_equal;
comp_alnum:
/*---------test_debug("at alnum compare");--------*/
    if(arg2x == NULL ) goto comp_alnum_null;

    if(arg2x->kind!='s')
	   goto comp_alnum_num;
    goto comp_two_alpha;
comp_num_alnum :

compare_one_num_one_not:

#ifdef __MC68K__
    StrPrintF(msg,"Illegal compare of string var. to numeric var. (%d) (%d)",
    arg1x->tbl_no,arg2x->tbl_no);
    misc_errmsg(msg);
#else
    SysFatalAlert("Illegal comparison between string var and numeric var");
#endif
    goto comp_1_2_equal;
comp_alnum_num :
    temp_arg = arg2x;  /*reverse arg1 and arg2 */
    arg2x = arg1x;
    arg1x = temp_arg;

    ad4 = (char*)arg2_valx;
    arg2_valx = arg1_valx;
    arg1_valx = (double*)ad4;

    argum_switch = 1;
    goto compare_one_num_one_not;
comp_two_alpha :
    ad1 = (char*)arg1_valx;
    ad2 = (char*)arg2_valx;
/*-------
StrPrintF(debug,"compare two alpha %s / %s",ad1,ad2);
test_debug(debug);
-------*/
#ifdef __MC68K__
    l1=StrLen((char *)arg1_valx);
    l2=StrLen((char*)arg2_valx);
#else
    l1=strlen((char *)arg1_valx);
    l2=strlen((char*)arg2_valx);
#endif
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
#ifdef __MC68K__
      reg_a = *( (double*)arg1_valx );
#else
      reg_a = ReadUnaligned64((char *) arg1_valx);
#endif
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
#ifdef __MC68K__
       StrPrintF(msg,"illegal compare operation code %i",oper);
       misc_text_abort(msg);
#else
       char *ds;
       ds = msg;
       strcpy(ds, "Illegal comparison code ");
       while (*ds) ++ds;
       StrIToA(ds, oper);
#endif
    }
    ad1 = (char*)arg1_valx;
    while ( *ad1 != 0x00) {
	if((*ad1=='+') ||(*ad1=='-'))  {
	    if  (ad1==(char*)arg1_valx) {
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
    ad1 = (char*)arg1_valx;
    while ( *ad1 != 0x00 )  {
	if( (*ad1 < '0') || (*ad1 > '9') ) {
	    if(oper==12) return(0); else return(1);
	}
	++ad1;
    }
    if(oper==12) return(1); else return(0);
comp_if_alphab :
    ad1 = (char*)arg1_valx;
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
#ifdef __MC68K__
extern char *devel_address(struct dataelem *arg, UInt16 s1,UInt16 s2,UInt16 s3)
#else
extern char *devel_address(PNOBlock *pnoP, struct dataelem *arg, UInt16 s1,UInt16 s2,UInt16 s3) //EMP
#endif
		      /*this rtn develops the address for the */
		      /*data pointed to by a data element #   */
		      /*and up to three subscripts            */
		      /*it returns a ptr to the addr of byte 1*/
{
   char *ad ;
   char*p;  //06/01/2002
   long i;
   static char aNullStringConstant = '\0';  // EMP
#ifndef __MC68K__
    UInt16 mnov2, mnov1;
#endif
   //06/01/2002unsigned int curoffset;
      
//char test[80] ;
/*----
StrPrintF(test,"at devel_addr occurs=%i s1=%i ",
arg->no_values,s1);
test_debug(test);
----*/
#ifndef __MC68K__
#define DELEN ((ULong)&(arg -> flags3))-((ULong)arg)+1
#endif

#ifdef __MC68K__
   i = (s3) * arg->max_no_values2 * arg->max_no_values1
      + (s2) * arg->max_no_values1
      + (s1);
#else
    mnov2 = arg -> max_no_values2;
    mnov2 = ByteSwap16(mnov2);
    
    mnov1 = arg -> max_no_values1;
    mnov1 = ByteSwap16(mnov1);

   i = (s3) * mnov2 * mnov1
      + (s2) * mnov1
      + (s1);

#endif
        
   if(arg->kind=='s')
   {
      p=(char *)arg + DELEN + i * 2 ;
      //curoffset = *( (int*)( p) );
      //if( curoffset == 0 )
      if( (UInt16)(*( (Int16*)( p) )) == 0 )
         ad = &aNullStringConstant;
      else
      {
#ifdef __MC68K__
         ad = (char*)arg + ( *(int *)( p ) );  //06/01/2002
#else
         Int16 ip = *(Int16 *)p;
         ip = ByteSwap16(ip);
         ad = (char*)arg + ip;
#endif
      }
	}
	else
      ad = (char*)arg + DELEN + i * 8;
      
   return ad;
   
#ifndef __MC68K__
#undef DELEN
#endif

}

/********************************************************************************************/

#ifdef __MC68K__
extern struct dataelem *elem_tbl_ptr(UInt16 de_no)       /*--data elem tbl calc */
#else
extern struct dataelem *elem_tbl_ptr(PNOBlock *pnoP, UInt16 de_no)      // EMP
#endif
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
    {
#ifndef __MC68K__
        struct dataelem *retVal;
#endif
        ad=(char*)PNO(deListPtr);
        
        ad += de_no * 4;
        
        if(*((long*)ad)==0)     					      //06/01/2002
        {  
#ifdef __MC68K__
           setupADataelem(de_no);						  //06/01/2002
#else
            Glue_setupADataelem(pnoP, de_no);
#endif
        }	
        //hData=*((VoidHand*)ad);   					      //06/01/2002 
#ifdef __MC68K__
        return((struct dataelem*)(*((VoidPtr*)ad)));     	  //06/01/2002
#else
        retVal = ((struct dataelem*)(*((VoidPtr*)ad)));
        return (struct dataelem *) ByteSwap32((unsigned long) retVal);
#endif
    }														//06/01/2002
    else return((struct dataelem*)NULL);       		  //06/01/2002
    
}
/********************************************************************************************/


#ifdef __MC68K__
extern unsigned char find_char()             /*--find next char in code file */
#else
extern unsigned char find_char(PNOBlock *pnoP) // EMP
#endif
{
    unsigned char the_char;
//if(debug_sw){
//StrPrintF(debug,"find_char codePtr=%lu i.c.=%d",codePtr,PNO(instr_ctr));
//SysFatalAlert(debug);
//}
    the_char = *((unsigned char*)(PNO(codePtr))+PNO(instr_ctr)++);
    return(the_char);
}

#ifdef __MC68K__
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
#endif

#ifdef __MC68K__
extern UInt16 find_integer()                     /*---find next integer in code--*/
#else
extern UInt16 find_integer(PNOBlock *pnoP) //EMP
#endif
{
#ifdef __MC68K__
    unsigned char find_char();
    unsigned char *ad1=(unsigned char*)0;
    unsigned the_integ;
    ad1 = (unsigned char *) &the_integ;
    *ad1 = find_char();
    *(ad1+1)=find_char();
    return(the_integ);
#else
    unsigned char find_char();
    UInt16 lo, hi;
    hi = find_char(pnoP);
    lo = find_char(pnoP);
    return lo | (hi << 8);
#endif
}

/********************************************************************************************/
#ifdef __MC68K__
extern UInt16 find_offset()
#else
extern UInt16 find_offset(PNOBlock *pnoP)   // EMP
#endif
{
   Int16 i;
   UInt16 j;
   char *ad;
#ifdef __MC68K__
   i=find_integer();   //have parag #
#else
    i = find_integer(pnoP);
#endif
//StrPrintF(debug,"found para tbl#=%d",i);
//SysFatalAlert(debug);
   ad=PNO(paragTbl)+(i-1)*2;
#ifdef __MC68K__
   j=*((UInt16 *)ad)-PNO(theCodeOffset);     //3/13/2001
#else
   j=*((UInt16 *)ad);
   j = ByteSwap16(j);
   j -= PNO(theCodeOffset);     //3/13/2001

#endif
//if(debug_on==1)
//{
//StrPrintF(debug,"found para tbl#=%d offset=%u theCodeOffset=%u  paragTbl=%lu",i,j,theCodeOffset,paragTbl);
//SysFatalAlert(debug);
//}
     return(j);
}

#ifdef __MC68K__
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
#endif

/********************************************************************************************/
#ifdef __MC68K__
extern void find_arg_1_2()                      /*--set args 1 and 2 from code--*/
{
    find_arg_1();
    find_arg_2();
    return;
}
#endif

/********************************************************************************************/
#ifdef __MC68K__
extern void find_arg_1_3()                      /*--set args 1,2,and3 from code--*/
{
    find_arg_1_2();
    find_arg_3();
    return;
}
#endif

/********************************************************************************************/
#ifdef __MC68K__
extern void find_arg_1_4()                      /*--set args 1 thru 4 from code--*/
{
    find_arg_1_3();
    find_arg_4();
    return;
}
#endif

#ifdef __MC68K__
/********************************************************************************************/
extern void find_arg_1_nosubs()            /*--set arg 1 from code-----------*/
{
   arg1_sde1=0;  // EMP
   arg1_sde2=0;
   arg1_sde3=0;

   arg1 = find_arg_nosubs( &arg1_occ1,&arg1_occ2,&arg1_occ3);
   if( arg1 != null_ptr )
      arg1_val = devel_address(arg1, 0,0,0);
}
#endif


/********************************************************************************************/
#ifdef __MC68K__
extern void find_arg_1()                    /*--set arg 1 from code-----------*/
{
   arg1 = find_arg( &arg1_occ1, &arg1_occ2,&arg1_occ3,&arg1_sde1,&arg1_sde2,&arg1_sde3);

   if( arg1 != null_ptr )
      arg1_val = devel_address(arg1, arg1_occ1,arg1_occ2,arg1_occ3);
}
#endif

/********************************************************************************************/
#ifdef __MC68K__
extern void find_arg_2()                    /*--set arg 2 from code-----------*/
{
   arg2 = find_arg( &arg2_occ1, &arg2_occ2,&arg2_occ3,&arg2_sde1,&arg2_sde2,&arg2_sde3);

   if( arg2 != null_ptr )
      arg2_val = devel_address(arg2, arg2_occ1,arg2_occ2,arg2_occ3);
}
#endif


#ifdef __MC68K__
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
extern void find_arg_3_nosubs()
{
   arg3_sde1=0;
   arg3_sde2=0;
   arg3_sde3=0;

   arg3 = find_arg_nosubs( &arg3_occ1, &arg3_occ2,&arg3_occ3);
   if( arg3 != null_ptr )
      arg3_val = devel_address(arg3, 0,0,0);
}
#endif

/********************************************************************************************/
#ifdef __MC68K__
extern void find_arg_3()                    /*--set arg 3 from code-----------*/
{
   arg3= find_arg(&arg3_occ1, &arg3_occ2,&arg3_occ3,&arg3_sde1,&arg3_sde2,&arg3_sde3);
   if( arg3 != null_ptr )
      arg3_val = devel_address(arg3, arg3_occ1,arg3_occ2,arg3_occ3);
}
#endif

#ifdef __MC68K__
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
#endif


/********************************************************************************************/
#ifdef __MC68K__
void verb_cursor()
#else
void verb_cursor(PNOBlock *pnoP)
#endif
{
#ifdef __MC68K__
    find_arg_1_2();
    InsPtEnable(true);
    InsPtSetLocation(basc_integ_value(arg1,(double*)arg1_val),basc_integ_value(arg2,(double*)arg2_val));
#else
    Arg arg1, arg2;
    double d1, d2;
    find_arg_PNO(pnoP, &arg1);
    find_arg_PNO(pnoP, &arg2);
    d1 = ReadUnaligned64(arg1.val);
    d2 = ReadUnaligned64(arg2.val);
    InsPtEnable(true);
    InsPtSetLocation((Int16) d1, (Int16) d2);
#endif
}
/********************************************************************************************/


#ifdef __MC68K__
void verb_delay()
#else
void verb_delay(PNOBlock *pnoP)    // EMP
#endif
{
    double one_num;
    Int32 ticks;
#ifndef __MC68K__
    Arg arg1;
#endif 

#ifdef __MC68K__
    find_arg_1();
    misc_getdbl(arg1,arg1_occ1,arg1_occ2,arg1_occ3,&one_num);
#else
    find_arg_PNO(pnoP, &arg1);
    misc_getdbl(pnoP, arg1.dataElem,arg1.occ1,arg1.occ2,arg1.occ3,&one_num);
#endif
    EvtResetAutoOffTimer();  //keep sys from going to sleep
    ticks= one_num * SysTicksPerSecond();
    if (ticks <= 0) return;
    SysTaskDelay(ticks);
    return;
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_errmsg()  //really verb_msgbox
#else
void verb_errmsg(PNOBlock *pnoP) // EMP
#endif
{
#ifdef __MC68K__
    find_arg_1();
    misc_errmsg((char *)arg1_val);
#else
    Arg arg1;
    
    find_arg_PNO(pnoP, &arg1);
    misc_errmsg(pnoP, (char *)arg1.val);
#endif
    return;
}
/********************************************************************************************/
#ifdef __MC68K__
void verb_end_logic_cond()
#else
void verb_end_logic_cond(PNOBlock *pnoP)
#endif
{                /*used for logic conditions */

    UInt16 i;
#ifdef __MC68K__
    i=find_integer();    /*last log var set by code*/
#else
    i=find_integer(pnoP);    /*last log var set by code*/
#endif

#ifdef __MC68K__
    if(logic_var[i] != 0)  /*true*/
#else
    if(PNO(logic_var)[i] != 0)  /*true*/
#endif
    {
	   PNO(logic_value)=1;
    }
    else
    {
	   PNO(logic_value)=0;
    }
    return;
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_display()
#else
void verb_display(PNOBlock *pnoP)  // EMP this routine makes no sense, rewriting
#endif
{
    Int16 color_text,color_bkgrnd;
    char str2[128];
    char *str;
    Int16 i;Int16 ii;
    unsigned char it;
    Int16 x;
#ifndef __MC68K__
    Arg arg1;
#endif
    
    x=getx();
#ifdef __MC68K__
    it=find_char();
#else
    it = find_char(pnoP);
#endif

    if(it==0x00) ;
    else
    {
#ifdef __MC68K__
	    find_arg_1();  
        arg1=(struct dataelem*)NULL; 
#else
        find_arg_PNO(pnoP, &arg1);
        arg1.dataElem = NULL;
#endif
        
    }
#ifdef __MC68K__
    it=find_char();
#else
    it=find_char(pnoP);
#endif
    if(it==0x00) ;
    else
    {
#ifdef __MC68K__
	    find_arg_1();  
        arg1=(struct dataelem*)NULL; 
#else
        find_arg_PNO(pnoP, &arg1);
        arg1.dataElem = NULL;
#endif
    }
#ifdef __MC68K__
    it=find_char();
#else
    it = find_char(pnoP);
#endif
    while(it)
    {
      Int16 sl;
#ifdef __MC68K__
	  find_arg_1();
      if(arg1->kind=='s')
#else
      find_arg_PNO(pnoP, &arg1);
      if(arg1.dataElem->kind=='s')
#endif
      {
          // arg1=((char*)str,(char*)arg1_val);  EMP makes no sense
#ifdef __MC68K__
          str = (char *)arg1_val;
#else
          str = (char *)arg1.val;
#endif
      }
      else
      {
#ifdef __MC68K__
	       misc_format_number(arg1,(double*)arg1_val,str2);
#else
	       misc_format_number(pnoP, arg1.dataElem,(double*)arg1.val,str2);
#endif
	       str = str2;
      }
#ifdef __MC68K__
        sl = StrLen(str);
#else
        sl = strlen(str);
#endif        
      if( str[0] !=0x00)
      {
        if((x+FntCharsWidth(str,sl))>SCREEN_MAX_X)
        {
          str[sl-1] =0x00;
        }
      }
      WinDrawChars(str,sl,x,gety());
      x+=FntCharsWidth(str,sl);
      
#ifdef __MC68K__
    it=find_char();
#else
    it = find_char(pnoP);
#endif
    }

     return;
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_start_new_parag()            /*---start new para-----*/
#else
void verb_start_new_parag(PNOBlock *pnoP)    // EMP
#endif
{
       /*now process cur para */
    return;
}
/********************************************************************************************/
#ifdef __MC68K__
void verb_start_new_stmt()                  /*---start new statement-------*/
#else
void verb_start_new_stmt(PNOBlock *pnoP)   // EMP
#endif
{
#ifdef __MC68K__
	PNO(cur_module_id) = find_integer();
    PNO(cur_stmt_no) = find_integer();
#else
	PNO(cur_module_id) = find_integer(pnoP);
    PNO(cur_stmt_no) = find_integer(pnoP);
#endif

   if( *((unsigned char*)(PNO(codePtr))+PNO(instr_ctr) )==0xf2)  
    {
    		//had to do this to get call stack to show sub/func entry 
    		//entering a sub or func, so set stmt # of entry point
  //SysFatalAlert("recognized f2");
    		PNO(codeBlockPtr)->subFuncEntry_stmt_no = PNO(cur_stmt_no);  //save the stmt no of this FUNC stmt
    		++PNO(instr_ctr);
 //StrPrintF(debug,"next instr = %c", *((unsigned char*)(codePtr)+instr_ctr ));
 //SysFatalAlert(debug);
 
    } 

    return;
}


/********************************************************************************************/
#ifdef __MC68K__
void draw_redraw()  
#else
void draw_redraw(PNOBlock *pnoP)  // EMP
#endif
{
    FormPtr frmPtr;


    chkFldUpdate();         //added 5.21.2000
    resetToDesignState=false;    //08142002
    executeFormRedraw();    //added 5.21.2000
}
/********************************************************************************************/
#ifdef __MC68K__
void verb_redraw()
{
    draw_redraw();
}
#else
void verb_redraw(PNOBlock *pnoP)   // EMP
{
    draw_redraw(pnoP);
}
#endif

/********************************************************************************************/
#ifdef __MC68K__
void verb_return()
#else
void verb_return(PNOBlock *pnoP)
#endif
{
    VoidHand tempHand;
    VoidPtr perf;
    UInt16 s;
    if(PNO(perfHand)!=0)
    {
        perf=MemHandleLock(PNO(perfHand));
#ifdef __MC68K__
        PNO(instr_ctr)=*(UInt*)perf;
        tempHand=*((VoidHand*)((char*)(perf)+2));
#else
        s = *(UInt*)perf;
        PNO(instr_ctr) = ByteSwap16(s);
        tempHand = (VoidHand) ReadUnaligned32(((VoidHand*)((char*)(perf)+2)));
#endif
        MemPtrUnlock(perf);
        MemPtrFree(perf);
        PNO(perfHand)=tempHand;
    }
}
		     
/********************************************************************************************/
#ifdef __MC68K__
void verb_add()                /*--------------add--------------------*/
#else
void verb_add(PNOBlock *pnoP)   // EMP
#endif
{
    char round_sw;
#ifndef __MC68K__
    Arg arg1, arg2, arg3;
    double reg_a, reg_b;
#endif
//char work[266];

#ifdef __MC68K__
    find_arg_1();
    find_arg_2();
    find_arg_3();
    round_sw = find_char();
#else
    find_arg_PNO(pnoP, &arg1);
    find_arg_PNO(pnoP, &arg2);
    find_arg_PNO(pnoP, &arg3);
    round_sw = find_char(pnoP);
#endif
    //reg_b=*((double*)arg1_val);
    //reg_a=*((double*)arg2_val);

    //reg_a=reg_b+reg_a;         /*sum in a*/
#ifdef __MC68K__
    reg_a=*((double*)arg1_val)+*((double*)arg2_val);  //06012002
    misc_stodbl(arg3,arg3_occ1,arg3_occ2,arg3_occ3,&reg_a);
#else
    reg_a = ReadUnaligned64(arg1.val);
    reg_b = ReadUnaligned64(arg2.val);
    reg_a += reg_b;
    reg_a = SwapDouble(reg_a);
    misc_stodbl(pnoP, arg3.dataElem, arg3.occ1, arg3.occ2, arg3.occ3, &reg_a);

#endif

    return;
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_clear_frac_dgts() /*clears all fractional dgts of a fld*/
#else
void verb_clear_frac_dgts(PNOBlock *pnoP)  // EMP
#endif
{
//char work[266];
#ifdef __MC68K__
    double d;
    find_arg_1();
    
    reg_a=*((double*)arg1_val);
   
    d=misc_floor(misc_fabs(reg_a));
    if(reg_a<0) d= -d;

    misc_stodbl1(&d);
#else
    Arg arg1;
    double d, r;
    find_arg_PNO(pnoP, &arg1);
    
    r = ReadUnaligned64(arg1.val);
    
    if (r < 0.0)
    {
        UInt32 l = -r;
        d = l;
        d = -d;
    }
    else
    {
        UInt32 l = r;
        d = l;
    }
    misc_stodbl(pnoP, arg1.dataElem, arg1.occ1, arg1.occ2, arg1.occ3, &d);
    
#endif
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_compute()                      /*------compute-------------*/
#else
void verb_compute(PNOBlock *pnoP)   // EMP
#endif
{
#ifdef __MC68K__
    verb_special_arith_store();   /*nothing else special*/
#else
    verb_special_arith_store(pnoP);   /*nothing else special*/
#endif
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_exponentiation()              /*-----exponentiation----*/
#else
void verb_exponentiation(PNOBlock *pnoP)              // EMP
#endif
{
    char round_sw;
#ifdef __MC68K__
    find_arg_1_3();
    round_sw = find_char();
#else
    Arg arg1, arg2, arg3;
    double reg_b, reg_a, reg_c;
    find_arg_PNO(pnoP, &arg1);
    find_arg_PNO(pnoP, &arg2);
    find_arg_PNO(pnoP, &arg3);
    round_sw = find_char(pnoP);
#endif
        
#ifdef __MC68K__
    chkMathLibOpen();   //added 5.20.2000
#else
    Glue_chkMathLibOpen(pnoP);
#endif

#ifdef __MC68K__
    reg_b=*((double*)arg1_val);
    reg_a=*((double*)arg2_val) ;
#else
    reg_b = ReadUnaligned64(arg1.val);
    reg_a = ReadUnaligned64(arg2.val);
#endif

#ifdef __MC68K__
    reg_c = pow(reg_b , reg_a);
#else
    reg_c = GluePow(pnoP, reg_b, reg_a);
#endif

#ifdef __MC68K__
    misc_stodbl3(&reg_c);
#else
    reg_c = SwapDouble(reg_c);
	misc_stodbl(pnoP, arg3.dataElem, arg3.occ1, arg3.occ2, arg3.occ3, &reg_c);
#endif
    return;
}

/********************************************************************************************/
#ifdef __MC68K__
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
#else
void verb_multiply(PNOBlock *pnoP)
{
    char round_sw;
    double reg_a, reg_b;
    Arg arg1, arg2, arg3;

    find_arg_PNO(pnoP, &arg1);
    find_arg_PNO(pnoP, &arg2);
    find_arg_PNO(pnoP, &arg3);
    
    round_sw = find_char(pnoP);
    
    reg_a = ReadUnaligned64(arg1.val);
    reg_b = ReadUnaligned64(arg2.val);
    
    reg_a *= reg_b;
    reg_a = SwapDouble(reg_a);
    
	misc_stodbl(pnoP, arg3.dataElem, arg3.occ1, arg3.occ2, arg3.occ3, &reg_a);
} 
#endif

/********************************************************************************************/
#ifdef __MC68K__
void verb_concat_two_strings()
#else
void verb_concat_two_strings(PNOBlock *pnoP)    // EMP
#endif
{
    Int16 j,len;
    char *temp;
    VoidHand h;  //05282003
#ifdef __MC68K__

    find_arg_1_3();
#else
    char *b;
    Arg arg1, arg2, arg3;
    find_arg_PNO(pnoP, &arg1);
    find_arg_PNO(pnoP, &arg2);
    find_arg_PNO(pnoP, &arg3);
#endif
 
#ifdef __MC68K__
    len= StrLen((char*)arg1_val)+StrLen((char*)arg2_val);
#else
    len= strlen((char*)arg1.val)+strlen((char*)arg2.val);
#endif

    //05282003 temp=(char*)MemHandleLock(MemHandleNew(len+1));
    h=MemHandleNew(len+1);         //05282003
    if(h==0) OutOfMemory(6045);    //05282003
    temp=(char*)MemHandleLock(h);  //05282003

#ifdef __MC68K__
    StrCopy(temp,(char*)arg1_val);
    StrCat(temp,(char*)arg2_val);
#else
    b = strcpy(temp, (char*)arg1.val);
    strcpy(b, (char*)arg2.val);
#endif

//StrPrintF(debug,"resize tbl1=%d tbl2=%d tbl3=%d len=%d s1=%s s2=%s",arg1->tbl_no,arg2->tbl_no,arg3->tbl_no,StrLen(temp),(char*)arg1_val,(char*)arg2_val);
//SysFatalAlert(debug);
//StrPrintF(debug,"concat 1=%s 2=%s 3=%s tbl_no=%d",arg1_val,arg2_val,temp,arg3->tbl_no);
//SysFatalAlert(debug);
#ifdef __MC68K__
    misc_stostr3(temp);
#else
    misc_stostr(pnoP, &(arg3.dataElem), arg3.occ1, arg3.occ2, arg3.occ3, temp);
#endif

    MemPtrUnlock(temp);
    MemPtrFree(temp);
}


/********************************************************************************************/
#ifdef __MC68K__
void verb_special_arith_store()           /*---store arith w/ round/size-*/
#else
void verb_special_arith_store(PNOBlock *pnoP)  //EMP
#endif
{

    char round;
    Int16 i;
#ifndef __MC68K__
    double reg_a;
    Arg arg1, arg2;
#endif

#ifdef __MC68K__
    find_arg_1_2();
    round = find_char();
#else
    find_arg_PNO(pnoP, &arg1);
    find_arg_PNO(pnoP, &arg2);
    round = find_char(pnoP);
#endif

#ifdef __MC68K__
    if(arg2->kind=='s')
#else
    if (arg2.dataElem -> kind == 's')
#endif
    {
//dbug("storing string");
#ifdef __MC68K__
        misc_stostr2(arg1_val);
#else
        misc_stostr(pnoP, &(arg2.dataElem), arg2.occ1, arg2.occ2, arg2.occ3, arg1.val);
#endif

      return;
    }
    
#ifdef __MC68K__
    reg_a=*((double*)arg1_val);
    misc_stodbl2(&reg_a);
#else
    reg_a = ReadUnaligned64(arg1.val);
    reg_a = SwapDouble(reg_a);
    misc_stodbl(pnoP, arg2.dataElem, arg2.occ1, arg2.occ2, arg2.occ3, &reg_a);
#endif
    
}


/********************************************************************************************/
#ifdef __MC68K__
void verb_negate()
{
  find_arg_1_2();
  reg_c=0.0-*((double*)arg1_val);
  
  misc_stodbl2(&reg_c);
}
#else
void verb_negate(PNOBlock *pnoP)
{
    double reg;
    Arg arg1, arg2;
    
    find_arg_PNO(pnoP, &arg1);
    find_arg_PNO(pnoP, &arg2);

    reg = ReadUnaligned64(arg1.val);
    reg = - reg;
    reg = SwapDouble(reg);
    misc_stodbl(pnoP, arg2.dataElem, arg2.occ1, arg2.occ2, arg2.occ3, &reg);
}
#endif


/********************************************************************************************/
#ifdef __MC68K__
void subFuncXferArgument()
#else
void subFuncXferArgument(PNOBlock *pnoP, Arg *arg1, Arg *arg2)
#endif
{
    Int16 kk,mm,nn;
#ifndef __MC68K__
    UInt16 mv11, mv12, mv13, mv21, mv22, mv23;
    struct dataelem *de1, *de2;
    de1 = arg1 -> dataElem;
    de2 = arg2 -> dataElem;
#endif

    //moves the value of one argument from the calling pgm to the sub/func
#ifdef __MC68K__
    if (arg1->kind=='s')
    {
       if(arg2->kind!='s')  MiscFatalAlert("Mis-matched args");
    }
    else
    {
       if(arg2->kind=='s')  MiscFatalAlert("Mis-matched args");
    }
#else
    if (de1 -> kind=='s')
    {
       if(de2 -> kind!='s')  SysFatalAlert("Mis-matched args");
    }
    else
    {
       if(de2 -> kind=='s')  SysFatalAlert("Mis-matched args");
    }
    
    mv11 = de1 -> max_no_values1;
    mv12 = de1 -> max_no_values2;
    mv13 = de1 -> max_no_values3;
    mv21 = de2 -> max_no_values1;
    mv22 = de2 -> max_no_values2;
    mv23 = de2 -> max_no_values3;
    
    mv11 = ByteSwap16(mv11);
    mv12 = ByteSwap16(mv12);
    mv13 = ByteSwap16(mv13);
    mv21 = ByteSwap16(mv21);
    mv22 = ByteSwap16(mv22);
    mv23 = ByteSwap16(mv23);
#endif

//StrPrintF(debug,"xfer arg1=%d %d %d %d  max=%d %d %d arg2=%d %d %d %d  max=%d %d %d",arg1->tbl_no,arg1_occ1,arg1_occ2,arg1_occ3,arg1->max_no_values1,arg1->max_no_values2,arg1->max_no_values3,arg2->tbl_no,arg2_occ1,arg2_occ2,arg2_occ3,arg2->max_no_values1,arg2->max_no_values2,arg2->max_no_values3);
//SysFatalAlert(debug);
    //if((arg1->max_no_values1>1)&&(arg1_occ1==0))
#ifdef __MC68K__   
    if( (arg2->max_no_values1<2)
    &&( ((arg1->max_no_values1>1) && (arg1_sde1==0))
      ||((arg1->max_no_values2>1) && (arg1_sde2==0))
      ||((arg1->max_no_values3>1) && (arg1_sde3==0)) ))
#else
    if( (mv21<2)
    &&( ((mv11>1) && (arg1 -> sde1==0))
      ||((mv12>1) && (arg1 -> sde2==0))
      ||((mv13>1) && (arg1 -> sde3==0)) ))
#endif
    {
#ifdef __MC68K__
           MiscFatalAlert("Passed an entire array to a subroutine not expecting it.");
#else
           SysFatalAlert("Passed an entire array to a subroutine not expecting it.");
#endif
    }

#ifdef __MC68K__
    if (arg2->max_no_values1>1)
#else
    if (mv21>1)
#endif
    {
        //calling param should be an array name without a subscript
        //  (but maybe a typedef member of an array, so there may be other preceding subscripts)

        //need to move all values of the array
#ifdef __MC68K__
        if(arg2->max_no_values3>1)
#else
        if(mv23>1)
#endif
        {
          //sub arg has 3 levels of subs
#ifdef __MC68K__
          if(arg1_sde1!=0) MiscFatalAlert("Too many levels of subscripting.");
          if( (arg1->max_no_values1 != arg2->max_no_values1)
          ||  (arg1->max_no_values2 != arg2->max_no_values2)
          ||  (arg1->max_no_values3 != arg2->max_no_values3) )
             MiscFatalAlert("Subroutine and calling program array bounds do not match."); 
#else
          if(arg1 -> sde1!=0) SysFatalAlert("Too many levels of subscripting.");
          if( (mv11 != mv21)
          ||  (mv12 != mv22)
          ||  (mv13 != mv23) )
             SysFatalAlert("Subroutine and calling program array bounds do not match."); 
#endif

#ifdef __MC68K__
          for( kk=0;kk<arg2->max_no_values1;++kk)
          {
            for( mm=0;mm<arg2->max_no_values2;++mm)
            {
              for( nn=0;nn<arg2->max_no_values3;++nn)
              {
#else
          for( kk=0;kk<mv21;++kk)
          {
            for( mm=0;mm<mv22;++mm)
            {
              for( nn=0;nn<mv23;++nn)
              {
#endif
//StrPrintF(debug,"storing arrays  %u %u %u",kk,mm,nn);
//SysFatalAlert(debug);

#ifdef __MC68K__
                 arg1_val = devel_address(arg1, kk,mm,nn);
                 arg2_val = devel_address(arg2, kk,mm,nn);
                 arg2_occ1=kk;
                 arg2_occ2=mm;
                 arg2_occ3=nn;
                      if (arg1->kind=='s')
#else           
                 arg2 -> val = devel_address(pnoP, de2, kk, mm, nn);
                 arg1 -> val = devel_address(pnoP, de1, kk, mm, nn);
                 
                 arg2 -> occ1 = (kk);
                 arg2 -> occ2 = (mm);
                 arg2 -> occ3 = (nn);
                 
                 if (de1 -> kind == 's')
#endif
                 {
                      
#ifdef __MC68K__
                      misc_stostr2(arg1_val);
#else
                      misc_stostr(pnoP, &(arg2 -> dataElem), arg2 -> occ1, arg2 -> occ2, arg2 -> occ3, arg1 -> val);
#endif
                 }
                 else
                 {
#ifdef __MC68K__
                      misc_stodbl2((double*)arg1_val);
#else
	                  misc_stodbl(pnoP, (arg2 -> dataElem), arg2 -> occ1, arg2 -> occ2, arg2 -> occ3,(double *) (arg1 -> val));
#endif
                 }
              }
            }
          }   
        }
        else
        {
#ifdef __MC68K__
          if(arg2->max_no_values2>1)
#else
          if (mv22 > 1)
#endif
          {
#ifdef __MC68K__
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
#else
            if(arg1 -> sde2!=0) SysFatalAlert("Too many levels of subscripting.");
            if(arg1 -> sde1==0)
            {
              if( (mv11 != mv21)
              ||  (mv12 != mv22))
                  SysFatalAlert("Subroutine and calling program array bounds do not match."); 
            }
            else
            {
              if( (mv12 != mv21)
              ||  (mv13 != mv22))
                  SysFatalAlert("Subroutine and calling program array bounds do not match.");   
            }
#endif

#ifdef __MC68K__
            for( kk=0;kk<arg2->max_no_values1;++kk)
            {
              for( mm=0;mm<arg2->max_no_values2;++mm)
              {
#else
            for( kk=0;kk<mv21;++kk)
            {
              for( mm=0;mm<mv22;++mm)
              {
#endif                

//StrPrintF(debug,"storing arrays  %u %u %u",kk,mm,nn);
//SysFatalAlert(debug);
#ifdef __MC68K__
                if(arg1_sde1==0)
                {
                   arg2_val = devel_address(arg2, kk,mm,0);
                   arg1_val = devel_address(arg1, kk,mm,0);
                   arg2_occ1=kk;
                   arg2_occ2=mm;
                   arg2_occ3=0;
                }
                else
                {
                   arg2_val = devel_address(arg2, kk,mm,0);
                   arg1_val = devel_address(arg1, arg1_occ1,kk,mm);
                   arg2_occ1=kk;
                   arg2_occ2=mm;
                   arg2_occ3=0;
                }
#else
                if(arg1 -> sde1==0)
                {
                   arg2 -> val = devel_address(pnoP, de2, kk,mm,0);
                   arg1 -> val = devel_address(pnoP, de1, kk,mm,0);
                   arg2 -> occ1= kk;
                   arg2 -> occ2= mm;
                   arg2 -> occ3=0;
                }
                else
                {
                   arg2 -> val = devel_address(pnoP, de2, kk,mm,0);
                   arg1 -> val = devel_address(pnoP, de1, arg1 -> occ1, kk,mm);
                   arg2 -> occ1 = kk;
                   arg2 -> occ2 = mm;
                   arg2 -> occ3=0;
                }
#endif
#ifdef __MC68K__
                if (arg1->kind=='s')
                {
                      misc_stostr2(arg1_val);
                }
                else
                {
                      misc_stodbl2((double*)arg1_val);
                }
#else
                if (de1->kind=='s')
                {
                      misc_stostr(pnoP, &(arg2 -> dataElem), arg2 -> occ1, arg2 -> occ2, arg2 -> occ3, arg1 -> val);
                }
                else
                {
	                  misc_stodbl(pnoP, (arg2 -> dataElem), arg2 -> occ1, arg2 -> occ2, arg2 -> occ3,(double *) (arg1 -> val));
                }
#endif                
              }
            } 
          
          }
          else
          {
#ifdef __MC68K__
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
#else
            //sub arg has 1 levels of subs
            if(arg1 -> sde3!=0) SysFatalAlert("Too many levels of subscripting.");
            if(arg1 -> sde1==0)
            {
              if( (mv11 != mv21))
                  SysFatalAlert("Subroutine and calling program array bounds do not match."); 
            }
            else
            {
              if(arg1 -> sde2==0)
              {
                if (mv12 != mv21)
                  SysFatalAlert("Subroutine and calling program array bounds do not match.");   
              }
              else
              {
                if (mv13 != mv21)
                  SysFatalAlert("Subroutine and calling program array bounds do not match.");  
              }
            }
#endif
#ifdef __MC68K__
            for( kk=0;kk<arg2->max_no_values1;++kk)
#else
            for( kk=0;kk<mv21;++kk)
#endif
            {
                             
//StrPrintF(debug,"storing arrays  %u %u %u",kk,mm,nn);
//SysFatalAlert(debug);
#ifdef __MC68K__
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
#else
                if(arg1 -> sde1==0)
                {
                   arg2 -> val = devel_address(pnoP, de2, kk,0,0);
                   arg1 -> val = devel_address(pnoP, de1, kk,0,0);
                   arg2 -> occ1= (kk);
                   arg2 -> occ2=0;
                   arg2 -> occ3=0;
                }
                else
                {
                  if(arg1 -> sde2==0)
                  {
                   arg2 -> val = devel_address(pnoP, de2, kk,0,0);
                   arg1 -> val = devel_address(pnoP, de1, arg1 -> occ1,kk,0);
                   arg2 -> occ1= (kk);
                   arg2 -> occ2=0;
                   arg2 -> occ3=0;
                  }
                  else
                  {
                   arg2 -> val = devel_address(pnoP, de2, kk,0,0);
                   arg1 -> val = devel_address(pnoP, de1, arg1 -> occ1, arg1 -> occ2, kk);
                   arg2 -> occ1= (kk);
                   arg2 -> occ2=0;
                   arg2 -> occ3=0;
                  }
                }
#endif
#ifdef __MC68K__
                if (arg1->kind=='s')
                {
                      misc_stostr2(arg1_val);
                }
                else
                {
                      misc_stodbl2((double*)arg1_val);
                }
#else
                if (de1->kind=='s')
                {
                      misc_stostr(pnoP, &(arg2 -> dataElem), arg2 -> occ1, arg2 -> occ2, arg2 -> occ3, arg1 -> val);
                }
                else
                {
	                  misc_stodbl(pnoP, (arg2 -> dataElem), arg2 -> occ1, arg2 -> occ2, arg2 -> occ3,(double *) (arg1 -> val));
                }
#endif      
            } 
          }
        }
    }       
    else
    {
#ifdef __MC68K__
      //its only a single-valued (non-array) data element
      if (arg1->kind=='s')
      {
         misc_stostr2(arg1_val);
      }
      else
      {
         misc_stodbl2((double*)arg1_val);
      }
#else
      //its only a single-valued (non-array) data element
      if (de1->kind=='s')
      {
          misc_stostr(pnoP, &(arg2 -> dataElem), arg2 -> occ1, arg2 -> occ2, arg2 -> occ3, arg1 -> val);
      }
      else
      {
	      misc_stodbl(pnoP, (arg2 -> dataElem), arg2 -> occ1, arg2 -> occ2, arg2 -> occ3,(double *) (arg1 -> val));
      }
#endif
    }  

}

/********************************************************************************************/
#ifdef __MC68K__
void verb_subtract()                       /*-------subtract-----------*/
{
   char round_sw;
   double reg_a, reg_b, reg_c;
   char *v1, *v2;
    find_arg_1_3();
    round_sw = find_char();

    reg_b=*((double*)arg1_val);
    reg_a=*((double*)arg2_val);

    reg_c=reg_a - reg_b;

    misc_stodbl3(&reg_c);
}
#else
void verb_subtract(PNOBlock *pnoP)
{
    char round_sw;
    double reg_a, reg_b, reg_c;
    char *v1, *v2;
    Arg arg1, arg2, arg3;

    find_arg_PNO(pnoP, &arg1);
    find_arg_PNO(pnoP, &arg2);
    find_arg_PNO(pnoP, &arg3);
    
    round_sw = find_char(pnoP);
    
    v1 = arg1.val;
    v2 = arg2.val;

    reg_b = ReadUnaligned64(v1);
    reg_a = ReadUnaligned64(v2);
    
    reg_c = reg_a - reg_b;
    reg_c = SwapDouble(reg_c);
    
	misc_stodbl(pnoP, arg3.dataElem, arg3.occ1, arg3.occ2, arg3.occ3, &reg_c);
}
#endif

#ifdef __MC68K__	  
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
#else
void verb_and(PNOBlock *pnoP)  // EMP
{
    UInt16 a,b,c;
    a=find_integer(pnoP);
    b=find_integer(pnoP);
    c=find_integer(pnoP);
    if( (PNO(logic_var)[a] != 0) && (PNO(logic_var)[b] != 0) )
	 PNO(logic_var)[c] = 256;  // pre-swapped
    else PNO(logic_var)[c] =0;
}
#endif

/********************************************************************************************/
#ifdef __MC68K__
void verb_goto()                           /*-----------goto-------------*/
{
    PNO(instr_ctr) = find_offset();
}
#else
void verb_goto(PNOBlock *pnoP)    // EMP
{
    PNO(instr_ctr) = find_offset(pnoP);
}
#endif

/********************************************************************************************/
#ifdef __MC68K__
void verb_if()                             /*--------------- if ---------*/
#else
void verb_if(PNOBlock *pnoP)    // EMP
#endif
{
   
    UInt16 if_false_offset;
    UInt16 if_true_offset;
    UInt16 if_endif_offset;
    UInt16 log_var;
    Int16  if_oper;
    char if_or_code;

#ifdef __MC68K__
    if_false_offset =  find_offset();
    if_true_offset = find_offset();
    if_endif_offset =find_offset();
    log_var = find_integer();
#else
    if_false_offset =  find_offset(pnoP);
    if_true_offset = find_offset(pnoP);
    if_endif_offset =find_offset(pnoP);
    log_var = find_integer(pnoP);
#endif
    
//StrPrintF(debug,"  PNO(instr_ctr)=%d false=%d true=%d endif=%d logic=%d",PNO(instr_ctr)
//,if_false_offset,if_true_offset,if_endif_offset,logic_var[log_var]);
//SysFatalAlert(debug);
#ifdef __MC68K__
    if(logic_var [log_var] != 0) {
#else
    if(PNO(logic_var)[log_var] != 0) {
#endif       
       PNO(instr_ctr) = if_true_offset;

//StrPrintF(debug,"at true-para#=%i  PNO(instr_ctr)=%d",if_true_offset,PNO(instr_ctr));
//SysFatalAlert(debug);

	    return;
    }
    /* result is false */
   
    PNO(instr_ctr) = if_false_offset;

//StrPrintF(debug,"at false-using logvar=%i,para#=%i  instr=%d",log_var,if_false_offset,PNO(instr_ctr));
//SysFatalAlert(debug);
}


/********************************************************************************************/
#ifdef __MC68K__
void verb_startfor()
#else
void verb_startfor(PNOBlock *pnoP)
#endif
{
    double reg_a;
    double reg_b;
    UInt16 offset;
    Int16 forno;
    Int16 i,j,k;
    VoidHand h;   //05282003
#ifndef __MC68K__
    UInt32 l;
    Arg arg1, arg2, arg3, arg4;
#endif
    
#ifdef __MC68K__
    find_arg_1_4(); //1=ctl,2=start,3=end,4=step
    forno=find_integer();
#else
    find_arg_PNO(pnoP, &arg1);
    find_arg_PNO(pnoP, &arg2);
    find_arg_PNO(pnoP, &arg3);
    find_arg_PNO(pnoP, &arg4);
    forno = find_integer(pnoP);
#endif

#ifdef __MC68K__
    reg_a = *((double*)arg2_val);
    reg_b = *((double*)arg4_val);
#else
    reg_a = ReadUnaligned64(arg2.val);
    reg_b = ReadUnaligned64(arg4.val);
#endif
    reg_a -= reg_b;

#ifdef __MC68K__
    misc_stodbl1(&reg_a);
#else
    reg_a = SwapDouble(reg_a);
	misc_stodbl(pnoP, arg1.dataElem, arg1.occ1, arg1.occ2, arg1.occ3, &reg_a);
#endif

    PNO(forPtrSave)=PNO(forptr);  //06102002 added
    h=MemHandleNew(sizeof(struct forStruct));    //05282003
    if(h==0)  OutOfMemory(6047);                 //05282003
    PNO(forptr)=(struct forStruct*)MemHandleLock(h);

#ifdef __MC68K__
    PNO(forptr)->number=forno;
    PNO(forptr)->moduleCntr=PNO(moduleCntr);
    PNO(forptr)->ToValue=*((double*)arg3_val);
    PNO(forptr)->StepValue=*((double*)arg4_val);
    PNO(forptr)->prevForPtr=PNO(forPtrSave);   //06102002
#else
    PNO(forptr)->number = ByteSwap16(forno);
    l = PNO(moduleCntr);
    PNO(forptr)->moduleCntr = ByteSwap32(l);
    reg_a = ReadUnaligned64(arg3.val);
    PNO(forptr)->ToValue = SwapDouble(reg_a);
    reg_a = ReadUnaligned64(arg4.val);
    PNO(forptr)->StepValue = SwapDouble(reg_a);
    l = (UInt32) PNO(forPtrSave);
    PNO(forptr)->prevForPtr = (struct forStruct *) ByteSwap32(l);
#endif

}

/********************************************************************************************/
#ifdef __MC68K__
void verb_continuefor()
#else
void verb_continuefor(PNOBlock *pnoP)    // EMP 092603
#endif
{
    UInt16 offset;
    Int16 forno;
    double reg_a;
#ifndef __MC68K__
    double reg_b, sv, sc;
    UInt32 l;
    UInt32 moduleCntr;
    UInt16 number;
    void *addr;
    Arg arg1;
#endif
    
            
#ifdef __MC68K__
    find_arg_1();
    forno=find_integer();
    offset=find_offset();
#else
    find_arg_PNO(pnoP, &arg1);
    forno=find_integer(pnoP);
    offset=find_offset(pnoP);
#endif

loop:
    //06102002if(forHandle==0) SysFatalAlert("Internal error--for processing");
    if(PNO(forptr)==0)                                //modified 05212003
    {                                            //inserted 05212003
#ifdef __MC68K__
        SysFatalAlert("Internal error--for processing");  //inserted 05212003
        ErrThrow(-1);                 //inserted 05212003
#else
        SysFatalAlert("Internal error--for processing");  //inserted 05212003
        GlueErrThrow(pnoP, -1);
#endif
    }                                            //inserted 05212003
    
    //06102002forptr=(struct forStruct*)MemHandleLock(forHandle);
#ifdef __MC68K__
    if((PNO(forptr)->moduleCntr!=PNO(moduleCntr)||(PNO(forptr)->number!=forno)))
#else
    moduleCntr = PNO(forptr) -> moduleCntr;
    moduleCntr = ByteSwap32(moduleCntr);
    number = PNO(forptr) -> number;
    number = ByteSwap16(number);
    if((moduleCntr!=PNO(moduleCntr)||(number!=forno)))
#endif
    {
       //06102002forHandleSave=forHandle;
       PNO(forPtrSave)=PNO(forptr);  //06102002
       //06102002forptr=(struct forStruct *)MemHandleLock(forHandle);
       //06102002forHandle=forptr->prevHandle;
#ifdef __MC68K__
       PNO(forptr)=PNO(forptr)->prevForPtr;  //06102002
#else
       l = (UInt32) (PNO(forptr) -> prevForPtr);
       PNO(forptr)= (struct forStruct *)ByteSwap32(l);
#endif
       //06102002MemPtrUnlock(forptr);
       //06102002MemHandleFree(forHandleSave);
       MemPtrFree(PNO(forPtrSave));  //06102002
       goto loop; 
    }
    //reg_b=forptr->ToValue;
    //reg_c=forptr->StepValue;

#ifdef __MC68K__
    reg_a = *((double*)arg1_val) + PNO(forptr)->StepValue;
    misc_stodbl1(&reg_a);

    if (PNO(forptr)->StepValue>0.0)    //step is pos
    {
       if (reg_a > PNO(forptr)->ToValue)
       {
          
          goto deleteCurrentLoop;
       }
    }
    else   //step is neg
    {
       if (reg_a < PNO(forptr)->ToValue)
       {
          
          goto deleteCurrentLoop;
       }
    }
#else
    sv = PNO(forptr) -> StepValue;
    sv = SwapDouble(sv);
    
    sc = ReadUnaligned64(arg1.val);

    reg_a = sc + sv;
    reg_b = SwapDouble(reg_a);

	misc_stodbl(pnoP, arg1.dataElem, arg1.occ1, arg1.occ2, arg1.occ3, &reg_b);
    
    if (SwapDouble(PNO(forptr)->StepValue)>0.0)    //step is pos
    {
       if (reg_a > SwapDouble(PNO(forptr)->ToValue))
       {
          
          goto deleteCurrentLoop;
       }
    }
    else   //step is neg
    {
       if (reg_a < SwapDouble(PNO(forptr)->ToValue))
       {
          
          goto deleteCurrentLoop;
       }
    }
#endif

    //06102002MemPtrUnlock(forptr);
    return;
deleteCurrentLoop:
       //06102002MemPtrUnlock(forptr);
       //06102002forHandleSave=forHandle;
       PNO(forPtrSave)=PNO(forptr);  //06102002
       //06102002forptr=(struct forStruct *)MemHandleLock(forHandle);
       //06102002forHandle=forptr->prevHandle;
#ifdef __MC68K__
       PNO(forptr)=PNO(forptr)->prevForPtr;  //06102002
#else
       l = (UInt32) (PNO(forptr) -> prevForPtr);
       PNO(forptr)= (struct forStruct *)ByteSwap32(l);
#endif
       //06102002MemPtrUnlock(forptr);
       //06102002MemHandleFree(forHandleSave);
       MemPtrFree(PNO(forPtrSave));
       PNO(instr_ctr)=offset;
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_next()
#else
void verb_next(PNOBlock *pnoP) // EMP
#endif
{
  UInt offset;
#ifdef __MC68K__
  offset=find_offset();
#else
  offset = find_offset(pnoP);
#endif
  PNO(instr_ctr)=offset;
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_dowhile()
{
   
    UInt16 while_false_offset, while_true_offset;
    UInt16 while_endwhile_offset;
    UInt16 log_var;
			     /**/
    while_false_offset = find_offset();
    while_true_offset = find_offset();
    while_endwhile_offset = find_offset();
    log_var = find_integer();
    if(logic_var [log_var] == 1) {
         PNO(instr_ctr) = while_true_offset;
/*------
StrPrintF(debug,"at true-para#=%i p=%p PNO(instr_ctr)=%p",if_true_para,p,PNO(instr_ctr));
test_debug(debug);
-----*/
	return;
    }
    /* result is false */
    
    PNO(instr_ctr) = while_false_offset;
/*------
StrPrintF(debug,"at false-using logvar=%i,para#=%i p=%p instr=%p",log_var,if_true_para,p,PNO(instr_ctr));
test_debug(debug);
-------*/
}
#else
void verb_dowhile(PNOBlock *pnoP)    // EMP
{
    UInt16 while_false_offset, while_true_offset;
    UInt16 while_endwhile_offset;
    UInt16 log_var;

    while_false_offset = find_offset(pnoP);
    while_true_offset = find_offset(pnoP);
    while_endwhile_offset = find_offset(pnoP);
    log_var = find_integer(pnoP);
    if(PNO(logic_var)[log_var] != 0)
    {
         PNO(instr_ctr) = while_true_offset;
    }
    else
    {
        PNO(instr_ctr) = while_false_offset;
    }
}
#endif


/********************************************************************************************/
#ifdef __MC68K__
void verb_dountil()
#else
void verb_dountil(PNOBlock *pnoP)   // EMP
#endif
{
   
    UInt16 while_false_offset, while_true_offset;
    UInt16 while_endwhile_offset;
    UInt16 log_var;
			     /**/
		
#ifdef __MC68K__
    while_false_offset = find_offset();
    while_true_offset = find_offset();
    while_endwhile_offset = find_offset();
    log_var = find_integer();
#else
    while_false_offset = find_offset(pnoP);
    while_true_offset = find_offset(pnoP);
    while_endwhile_offset = find_offset(pnoP);
    log_var = find_integer(pnoP);

#endif    
    
#ifdef __MC68K__
    if(logic_var [log_var] == 0) {
#else
    if(PNO(logic_var)[log_var] == 0) {
#endif
         PNO(instr_ctr) = while_true_offset;
/*------
StrPrintF(debug,"at true-para#=%i p=%p PNO(instr_ctr)=%p",if_true_para,p,PNO(instr_ctr));
test_debug(debug);
-----*/
	return;
    }
    /* result is false */
    PNO(instr_ctr) = while_false_offset;
/*------
StrPrintF(debug,"at false-using logvar=%i,para#=%i p=%p instr=%p",log_var,if_true_para,p,PNO(instr_ctr));
test_debug(debug);
-------*/
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_do()
#else
void verb_do(PNOBlock *pnoP)     // EMP
#endif
{
   
    UInt32 while_false_offset, while_true_offset;
    UInt32 while_endwhile_offset;
    UInt32 log_var;
			     /**/
			     
#ifdef __MC68K__			     
    while_false_offset = find_offset();
    while_true_offset = find_offset();
    while_endwhile_offset = find_offset();
    log_var = find_integer();
#else
    while_false_offset = find_offset(pnoP);
    while_true_offset = find_offset(pnoP);
    while_endwhile_offset = find_offset(pnoP);
    log_var = find_integer(pnoP);
#endif    
/*------
StrPrintF(debug,"at false-using logvar=%i,para#=%i p=%p instr=%p",log_var,if_true_para,p,PNO(instr_ctr));
test_debug(debug);
-------*/
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_loop()
{
   PNO(instr_ctr) = find_offset();
}
#else
void verb_loop(PNOBlock *pnoP)
{
   PNO(instr_ctr) = find_offset(pnoP);
}
#endif

/********************************************************************************************/
#ifdef __MC68K__
void verb_exitfor()
{
   PNO(instr_ctr) = find_offset();
}
#else
void verb_exitfor(PNOBlock *pnoP)
{
   PNO(instr_ctr) = find_offset(pnoP);
}
#endif

/********************************************************************************************/
#ifdef __MC68K__
void verb_exitdo()
{
   PNO(instr_ctr) = find_offset();
}
#else
void verb_exitdo(PNOBlock *pnoP)
{
   PNO(instr_ctr) = find_offset(pnoP);
}
#endif

/********************************************************************************************/
#ifdef __MC68K__
void verb_logic_class_tests()              /*---class tests-------*/
#else
void verb_logic_class_tests(PNOBlock *pnoP)    // EMP
#endif
{
    Int16 if_oper;
    UInt16 log_var;

#ifdef __MC68K__
    find_arg_1();
    if_oper = (int) find_char();
    log_var = find_integer();
#else
    Arg arg1;
    find_arg_PNO(pnoP, &arg1);
    if_oper = (Int16) find_char(pnoP);
    log_var = find_integer(pnoP);
#endif

#ifdef __MC68K__
    arg2 = (struct dataelem*)null_ptr;  arg2_val = (char*)null_ptr;
    if(compare_args(arg1,(double*)arg1_val,arg2,(double*)arg2_val,if_oper)==1)
    {
	   logic_var[log_var] =1;
    }
    else
    {
       logic_var[log_var] =0;
    }
#else
    if(compare_args(pnoP, arg1.dataElem,(double*)arg1.val,NULL, NULL,if_oper)!= 0)
    {
	   PNO(logic_var)[log_var] = 256;    // Pre-swapped
    }
    else
    {
       PNO(logic_var)[log_var] = 0;    // Pre-swapped
    }
#endif
}

//added this whole routine on 06102002
/********************************************************************************************/
#ifdef __MC68K__
void verb_nextscreenwithvariable()   //nextform using form name in variable  //06102002
#else
void verb_nextscreenwithvariable(PNOBlock *pnoP)   // EMP
#endif
{
   
    Int16 i;
    char*ad;
    char *p2;
    VoidHand h;   //05282003
    VoidHand h2;
    char name[256];
    UInt16 ID;
#ifdef __MC68K__
    find_arg_1();
#else
    Arg arg1;
    Int16 x;
    EventPtr evptr;
    find_arg_PNO(pnoP, &arg1);
#endif

#ifdef __MC68K__
	h2=MiscDmGetResource(rscTag,(ULong)9907,"vtoc");  //read the view tbl-of-contents record
    if(h2==0)
    {
       SysFatalAlert("Can't find view TOC record");
       ErrThrow(-1);                 //inserted 05212003
    }
    p2=MiscHandleLock(h2);
#else
	h2 = DmGetResource(rscTag,(ULong)9907);  //read the view tbl-of-contents record
    if(h2==0)
    {
       SysFatalAlert("Can't find view TOC record");
       GlueErrThrow(pnoP, -1);                 //inserted 05212003
    }
    p2=MemHandleLock(h2);
#endif

    for(i=0;i< PNO(view_cnt);++i)  //for each view
    {
        ID = basc_dbGetInt( (char*)p2);  //get id of view from the vtoc record
        p2+=2;   //06102002
        ad = &name[0];
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
#ifdef __MC68K__
      if(StrCaselessCompare(name,arg1_val)==0)
#else
      if(StrCaselessCompare(name,arg1.val)==0)
#endif
      {
          goto matchedName;
      } 
      
//dbug("loading form   in vtoc processing:");
          
   }
#ifdef __MC68K__
   StrPrintF(debug,"Illegal form name used = %s",arg1_val);
   SysFatalAlert(debug);
   ErrThrow(-1);                 //inserted 05212003
#else
    {
        char *b;
        char debug[60];
        b = strcpy(debug, "Illegal form name used = ");
        strcpy(b, arg1.val);
        SysFatalAlert(debug);
        GlueErrThrow(pnoP, -1);
    }
#endif
matchedName:
    MemHandleUnlock(h2);      
    DmReleaseResource(h2);  
    
    if(MenuGetActiveMenu()!=NULL) 
    {
//dbug("erasing menu");
      MenuEraseStatus(NULL);
      MenuSetActiveMenu(NULL);
      FrmSetMenu(FrmGetActiveForm(),0);
      MenuDispose(PNO(menuPtr));
      PNO(menuPtr)=(MenuBarType*)NULL; 
    }
    PNO(frmNo)=ID;
//StrPrintF(debug,"nextscreen %d",ID);
//SysFatalAlert(debug);
    //05282003 evptr=(EventType*)MemHandleLock(MemHandleNew(sizeof(EventType)));
    h=MemHandleNew(sizeof(EventType));              //05282003
    if(h==0) OutOfMemory(6048);                     //05282003
    evptr=(EventType*)MemHandleLock(h);             //05282003 
#ifdef __MC68K__
    evptr->eType=firstUserEvent;
    evptr->data.generic.datum[0] =PNO(frmNo);
    evptr->data.generic.datum[1] =1;
    evptr->data.generic.datum[2] =find_integer();  //08142002 get option to reset to design state from code
#else
    evptr -> eType = ByteSwap16(firstUserEvent);
    evptr -> data.generic.datum[0] = ByteSwap16(ID);
    evptr -> data.generic.datum[1] = ByteSwap16(1);
    x = find_integer(pnoP);
    evptr->data.generic.datum[2] = ByteSwap16(x);
#endif
    if (PNO(frmNo) == FrmGetActiveFormID())
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
#ifdef __MC68K__
void verb_not_logic_oper()    /* handle -not- logic -----------------*/
#else
void verb_not_logic_oper(PNOBlock *pnoP)    /* handle -not- logic -----------------*/
#endif
{
    UInt16 i, j;
#ifdef __MC68K__
    i = find_integer();
    j = find_integer();
    if(logic_var[i] ) logic_var[j] = 0;
    else              logic_var[j] = 1;
#else
    i = find_integer(pnoP);
    j = find_integer(pnoP);
    if(PNO(logic_var)[i] ) PNO(logic_var)[j] = 0;
    else                   PNO(logic_var)[j] = 1;
#endif
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_or()                      /*----------or-----------*/
{
    UInt16 a,b,c;
    a=find_integer();
    b=find_integer();
    c=find_integer();
    if( (logic_var[a] ==1) || (logic_var[b] ==1) )
	 logic_var[c] =1;
    else logic_var[c] =0;
}
#else
void verb_or(PNOBlock *pnoP)  // EMP
{
    UInt16 a,b,c;
    a=find_integer(pnoP);
    b=find_integer(pnoP);
    c=find_integer(pnoP);
    if( (PNO(logic_var)[a] != 0) || (PNO(logic_var)[b] != 0) )
	 PNO(logic_var)[c] = 256;  // pre-swapped
    else PNO(logic_var)[c] =0;
}
#endif

/********************************************************************************************/
#ifdef __MC68K__
void verb_gosub()                          /*-------gosub-----------*/
#else
void verb_gosub(PNOBlock *pnoP)    // EMP
#endif
{
    VoidHand perfTemp;
    VoidPtr perf;
    UInt16 offset;                     /**/
#ifdef __MC68K__
    offset = find_offset();
#else
    UInt16 s;
    offset = find_offset(pnoP);
#endif
    perfTemp=MemHandleNew(6);
    if(perfTemp==0) OutOfMemory(6050);  //05282003
    perf=MemHandleLock(perfTemp);
#ifdef __MC68K__
    *((UInt16 *)perf) = PNO(instr_ctr);
    *((VoidHand*)((char*)(perf)+2))=PNO(perfHand);
#else
    s = PNO(instr_ctr);
    *((UInt16 *)perf) = ByteSwap16(s);
    
    WriteUnaligned32(((VoidHand*)((char*)(perf)+2)), PNO(perfHand));
#endif
//StrPrintF(debug,"gosub ic=%d off=%d",PNO(instr_ctr),offset);
//SysFatalAlert(debug);
    PNO(perfHand)=perfTemp;
    MemPtrUnlock(perf);
    PNO(instr_ctr) =  offset;
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_relat_logic_oper()     /*-------relational logic operators---*/
#else
void verb_relat_logic_oper(PNOBlock *pnoP)     // EMP
#endif
{
//char work[266];
    Int16 if_oper;
    UInt16 log_var;
#ifdef __MC68K__
    find_arg_1_2();
    if_oper=find_integer();
    log_var=find_integer();
#else
    Arg arg1, arg2;
    find_arg_PNO(pnoP, &arg1);
    find_arg_PNO(pnoP, &arg2);
    if_oper = find_integer(pnoP);
    log_var = find_integer(pnoP);
#endif

#ifdef __MC68K__
    if(compare_args(arg1,(double*)arg1_val,arg2,(double*)arg2_val,if_oper)==1)
        logic_var[log_var] =1;
    else
        logic_var[log_var] =0;
#else
    if(compare_args(pnoP, arg1.dataElem,(double*)arg1.val,
                          arg2.dataElem,(double*)arg2.val,if_oper)==1)
        PNO(logic_var)[log_var] = 256;   // EMP byte swapped
    else
        PNO(logic_var)[log_var] =0;
#endif
/*-------
StrPrintF(work,"at relat logic oper test =%i using logvar=%i",logic_var[log_var],log_var);
test_debug(work);
---------*/
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_stop()                               /*--------------stop--------*/
#else
void verb_stop(PNOBlock *pnoP) // EMP
#endif
{
	
    //ch'd 2/7/00 to use code to enqueue a launchChr
    EventType  newEvent;
#ifdef __MC68K__
    newEvent.eType = keyDownEvent;
    newEvent.data.keyDown.chr=launchChr;  //enqueue a char to force launcher to come up
    newEvent.data.keyDown.modifiers=commandKeyMask;
#else
    //newEvent.eType = ByteSwap16(keyDownEvent);
    //newEvent.data.keyDown.chr=ByteSwap16(launchChr);  //enqueue a char to force launcher to come up
    //newEvent.data.keyDown.modifiers=ByteSwap16(commandKeyMask);
    newEvent.eType = ByteSwap16(appStopEvent);
#endif
    EvtAddEventToQueue(&newEvent);        //add event and it will trigger the launcher to appear
}

/********************************************************************************************/
#ifdef __MC68K__
void commonSetFocus(FormPtr frmPtr, Int16 the_one)
#else
void commonSetFocus(PNOBlock *pnoP, FormPtr frmPtr, Int16 the_one)
#endif
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
        PNO(fldToUpdate)=the_one;   //added 5.20.2000
        break;
    }
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_cursor_id()
#else
void verb_cursor_id(PNOBlock *pnoP)
#endif
{
    
    Word the_one;
    FormPtr frmPtr;

#ifdef __MC68K__
    the_one=find_integer();
#else
    the_one = find_integer(pnoP);
#endif
    frmPtr=FrmGetActiveForm();
#ifdef __MC68K__
    commonSetFocus(frmPtr,the_one);
#else
    commonSetFocus(pnoP, frmPtr,the_one);
#endif

}

/***************************************************************************************************/
#ifdef __MC68K__
void commonRedrawId(FormPtr frmPtr, Int16 the_one)
#else
void commonRedrawId(PNOBlock *pnoP, FormPtr frmPtr, Int16 the_one)
#endif
{
   Int16 theType;
    
    Word i;
    Int16 w;
   
    
  Word idx;              //added 5.20.2000  
  
  VoidHand oldHand;
  VoidHand h;
  VoidPtr p;
    
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
        if (theType==frmTableObj)
        {
           //FormatATableObject(FrmGetActiveForm(),locateObjectPtr(the_one),i);  //format the table first
           //TblDrawTable ((TableType*)FrmGetObjectPtr(FrmGetActiveForm(),i));  //then, redraw it      
//StrPrintF(debug," redraw id %d=redraw tbl",the_one);
//dbug(debug);
			struct ObjectData * objPtr;
#ifdef __MC68K__
           objPtr=locateObjectPtr(the_one);
           redrawGrid(objPtr);
#else
		   objPtr=locateObjectPtr(pnoP, the_one);
           redrawGrid(pnoP, objPtr);
#endif

//dbug("back from draw table");
           //freeObjectPtr();                 
           return;
        }
        FrmHideObject(frmPtr,i);
        FrmShowObject(frmPtr,i);
        break;
 
    }
}

/***************************************************************************************************/
#ifdef __MC68K__
void verb_redraw_id()
#else
void verb_redraw_id(PNOBlock *pnoP)
#endif
{
    char theType;
    Word the_one;
    FormPtr frmPtr;
    
#ifdef __MC68K__
    the_one=find_integer();
    theType=find_char();
#else
    the_one=find_integer(pnoP);
    theType=find_char(pnoP);
#endif
    frmPtr=FrmGetActiveForm();
#ifdef __MC68K__
    commonRedrawId(frmPtr, the_one);
#else
	commonRedrawId(pnoP, frmPtr, the_one);
#endif
}

#ifdef __MC68K__
void verb_preceedSubFunc()
#else
void verb_preceedSubFunc(PNOBlock *pnoP)   // EMP
#endif
{
#ifdef __MC68K__
	PNO(cur_module_id) = find_integer();
    PNO(cur_stmt_no) = find_integer();
#else
	PNO(cur_module_id) = find_integer(pnoP);
    PNO(cur_stmt_no) = find_integer(pnoP);
#endif
}


#ifdef __MC68K__
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
		if( PNO(op_func)[i] == NULL )					// 01/29/2001 MMD
#endif													// 01/29/2001 MMD
			PNO(op_func)[i] = &illegal_op_code;		// 01/29/2001 MMD
	}														// 01/29/2001 MMD

	// This section cleaned up // 01/29/2001 MMD
	PNO(op_func)[0x04] = &verb_add;    
	PNO(op_func)[0x05] = &verb_beep;            // EMP does not seem to work from PNO
	PNO(op_func)[0x07] = &verb_seteventhandled;
	PNO(op_func)[0x06] = &verb_popupclear;
	PNO(op_func)[0x09] = &verb_display;
	PNO(op_func)[0x0a] = &verb_divide;
	PNO(op_func)[0x0c] = &verb_if;
	PNO(op_func)[0x0e] = &verb_multiply;

	PNO(op_func)[0x10] = &verb_gosub;
	PNO(op_func)[0x11] = &verb_call;
	PNO(op_func)[0x12] = &verb_sub;
	PNO(op_func)[0x13] = &verb_user_func;       // EMP what is this?
	PNO(op_func)[0x18] = &verb_stop;
	PNO(op_func)[0x19] = &verb_initAVariableValue;
	PNO(op_func)[0x1a] = &verb_subtract;
	PNO(op_func)[0x1b] = &verb_negate;
	PNO(op_func)[0x1c] = &verb_dbread;
	PNO(op_func)[0x1d] = &verb_return;
	PNO(op_func)[0x1e] = &verb_goto;
	PNO(op_func)[0x1f] = &verb_dbgetnorecs;

	PNO(op_func)[0x20] = &verb_menuerase;
	PNO(op_func)[0x21] = &verb_menudraw;
	PNO(op_func)[0x22] = &verb_menureset;
	PNO(op_func)[0x23] = &verb_dbfind;
	PNO(op_func)[0x24] = &verb_dbread;
	PNO(op_func)[0x25] = &verb_dbupdate;        // DIKEO need test for this
	PNO(op_func)[0x26] = &verb_dbdelete;
	PNO(op_func)[0x27] = &verb_dbinsert;
	PNO(op_func)[0x28] = &verb_dbreadnext;
	PNO(op_func)[0x29] = &verb_dberase;
	PNO(op_func)[0x2a] = &verb_dbcreate;
	PNO(op_func)[0x2b] = &verb_dbopen;
	PNO(op_func)[0x2c] = &verb_dbclose;
	PNO(op_func)[0x2d] = &verb_dbget;           // EMP Appears not to be used
	PNO(op_func)[0x2e] = &verb_dbput;           // EMP Appears not to be used
	PNO(op_func)[0x2f] = &verb_dbposition;

	PNO(op_func)[0x30] = &verb_controlsetstatus;
	PNO(op_func)[0x31] = &verb_controlhideorshow;
	PNO(op_func)[0x32] = &verb_fieldsettext;
	PNO(op_func)[0x33] = &verb_fieldsetmaxchars;
	PNO(op_func)[0x34] = &verb_listadditem;
	PNO(op_func)[0x35] = &verb_listdeleteitem;
	PNO(op_func)[0x36] = &verb_listsetselected;
	//PNO(op_func)[0x37] = &verb_controlssettext;
	
	PNO(op_func)[0x3b] = &verb_controlsetstatusNew;
	
	PNO(op_func)[0x3d] = &verb_assign_bitmap;   // EMP DIKEO delay
	PNO(op_func)[0x3e] = &verb_controlsetlabel;
	PNO(op_func)[0x3f] = &verb_setscrollbar;

	PNO(op_func)[0x40] = &verb_createwindow;
	PNO(op_func)[0x41] = &verb_destroywindow;
	PNO(op_func)[0x42] = &verb_erasewindow;
	PNO(op_func)[0x43] = &verb_drawchars;
	PNO(op_func)[0x44] = &verb_drawline;
	PNO(op_func)[0x45] = &verb_drawrectangle;   // EMP uses unsafe memory access
	PNO(op_func)[0x46] = &verb_fillrectangle;
	PNO(op_func)[0x47] = &verb_setcurwindow;
	PNO(op_func)[0x48] = &verb_draw_bitmap;
	PNO(op_func)[0x49] = &verb_dbreadprev;
	PNO(op_func)[0x4a] = &verb_delay;
	PNO(op_func)[0x4b] = &verb_sound;           // EMP sound doesn't work properly from pno
	PNO(op_func)[0x4c] = &verb_getPen;
	PNO(op_func)[0x4d] = &verb_listclear;
	PNO(op_func)[0x4e] = &verb_playsound;       

	PNO(op_func)[0x50] = &verb_exponentiation;
	PNO(op_func)[0x51] = &verb_not_logic_oper;
	PNO(op_func)[0x52] = &verb_relat_logic_oper;
	PNO(op_func)[0x53] = &verb_logic_class_tests;
	PNO(op_func)[0x54] = &verb_and;
	PNO(op_func)[0x55] = &verb_or;
	PNO(op_func)[0x57] = &verb_special_arith_store;
	
	PNO(op_func)[0x59] = &verb_compute;
	
	PNO(op_func)[0x5b] = &verb_clear_frac_dgts;
//reserve 5c and 5d for bindToDatabase    09242003

	
	
	//70-74 used by nsbasic
	PNO(op_func)[0x75] = &verb_signatureErase;  // EMP what to do with these?
	PNO(op_func)[0x76] = &verb_signatureStartCapture;
	PNO(op_func)[0x77] = &verb_signatureDisplay;

	PNO(op_func)[0x80] = &verb_nextscreen;
	PNO(op_func)[0x81] = &verb_clearscreentextfields;   //added 06102002 // EMP how to use?
	PNO(op_func)[0x82] = &verb_redraw;
	PNO(op_func)[0x83] = &verb_nextscreenwithvariable;   //added 06102002
	PNO(op_func)[0x84] = &verb_cursor_id;
	PNO(op_func)[0x85] = &verb_redraw_id;
	PNO(op_func)[0x86] = &verb_dbputnew;
	PNO(op_func)[0x87] = &verb_dbgetnew;
	PNO(op_func)[0x88] = &verb_generalVerb;      //added08222002
	PNO(op_func)[0x89] = &verb_setGeneralProperty;        //added08222002
	PNO(op_func)[0x8a] = &verb_func_getGeneralPropertyNumeric;      //added08222002
	PNO(op_func)[0x8b] = &verb_func_getGeneralPropertyString;      //added08222002
	PNO(op_func)[0x90] = &verb_concat_two_strings;   
	

	PNO(op_func)[0xa1] = &verb_startfor;
	PNO(op_func)[0xa2] = &verb_continuefor;
	PNO(op_func)[0xa3] = &verb_next;
	PNO(op_func)[0xa7] = &verb_do;
	PNO(op_func)[0xa8] = &verb_dountil;
	PNO(op_func)[0xa9] = &verb_dowhile;
	PNO(op_func)[0xaa] = &verb_loop;
	PNO(op_func)[0xab] = &verb_exitdo;
	PNO(op_func)[0xac] = &verb_exitfor;

	PNO(op_func)[0xb2] = &verb_launchprogram;       // EMP more appropriate to do from 68K
	PNO(op_func)[0xb3] = &verb_transfertoprogram;

	PNO(op_func)[0xc0] = &verb_setnumvarsfromheap;   //added 06102002 EMP DIKEO delay until setupadataelem
	PNO(op_func)[0xc1] = &verb_alert;
	PNO(op_func)[0xc2] = &verb_start_function;      // funcs

	PNO(op_func)[0xd2] = &verb_cursor;
	PNO(op_func)[0xd3] = &verb_errmsg;
	
	PNO(op_func)[0xdc] = &verb_dbreset;
	PNO(op_func)[0xdd] = &verb_end_logic_cond;
	PNO(op_func)[0xde] = &verb_function;
	PNO(op_func)[0xf0] = &verb_start_new_parag;
	PNO(op_func)[0xf1] = &verb_start_new_stmt;
	PNO(op_func)[0xf2] = &verb_preceedSubFunc;
	PNO(op_func)[0xf8] = &verb_end_sub;
	PNO(op_func)[0xf9] = &verb_end_function;
	PNO(op_func)[0xfd] = &verb_start_debug;
	PNO(op_func)[0xfe] = &verb_end_debug;

	for( i = 0; i < 15; ++i )
		dummyCode[i] = 0x00; 
	clearArgs();
	debug_sw = 0;
           /**/

	sz = sizeof(struct codeBlock);
	newCodeHand = MemHandleNew(sz);
	
	if(newCodeHand==0)  OutOfMemory(6051);  //05282003
	newCodePtr = (struct codeBlock*)MemHandleLock(newCodeHand);
	newCodePtr->prevCodePtr = null_ptr;
	PNO(codeBlockPtr) = newCodePtr;

	PNO(codeBlockPtr)->id = 50000;
	PNO(codeBlockPtr)->p3 = null_ptr;
	PNO(codeBlockPtr)->h3 = 0;
	PNO(codeBlockPtr)->numberParas = 0;
	PNO(codeBlockPtr)->paragTbl = null_ptr;
	PNO(codeBlockPtr)->codePtr = &dummyCode[0];
	PNO(codePtr) = &dummyCode[0];

	PNO(codeBlockPtr)->instr_ctr = 0;
	PNO(codeBlockPtr)->oldOffset = 0;
	PNO(codeBlockPtr)->functionLinkNo=0;
	PNO(h3) = 0;
	PNO(p3) = (char*)null_ptr;
//StrPrintF(debug,"in init PNO(codeBlockPtr)=%lu codePtr=%lu",PNO(codeBlockPtr),PNO(codePtr));
//SysFatalAlert(debug);
}
#endif

/********************************************************************************************/
Int16 getx()
{
   Int16 x,y;
   InsPtGetLocation(&x,&y);
   return(x);
}

/********************************************************************************************/
Int16 gety()
{
  Int16 x,y;
  InsPtGetLocation(&x,&y);
  return(y);
}

#ifdef __MC68K__
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
#endif

/********************************************************************************************/
#ifdef __MC68K__
void verb_alert()
#else
void verb_alert(PNOBlock *pnoP)     // EMP
#endif
{
#ifdef __MC68K__
  //Note:  ldm 09132004 had to add a save of arg1 before calling sys function because
  //           it is destroying arg1 address.  Don't know why
  struct dataelem* arg1Save;   //ldm 09132004
#endif
  VoidPtr ptr;
  VoidHand hView;
  Int16 res;
  Int16 cnt;
  char rest[900];
  Int16 howMany;
  //AlertResourceType al;
  struct  //GHGlue
  {
		UInt16		alertType;
		UInt16		helpRscID;
		UInt16		numButtons;
		UInt16		defaultButton;
  } al;  //GHGlue
#ifdef __MC68K__
  find_arg_1_4();     //result button
                      //title
                      //message
                      //type
#else
  Arg arg1, arg2, arg3, arg4;
  double d;
  
  find_arg_PNO(pnoP, &arg1);
  find_arg_PNO(pnoP, &arg2);
  find_arg_PNO(pnoP, &arg3);
  find_arg_PNO(pnoP, &arg4);
#endif
  cnt=0;
  rest[0] = '\0';

#ifdef __MC68K__
  al.alertType=basc_integ_value(arg4,(double*)arg4_val);
#else
  al.alertType = (UInt16) ReadUnaligned64(arg4.val);
  al.alertType = ByteSwap16(al.alertType);
#endif
  al.numButtons=0;
  al.defaultButton=0;
  al.helpRscID=0;
  cnt=8;   //will fill in 1st 8 later
#ifdef __MC68K__
  MemMove(rest+cnt,arg2_val,StrLen(arg2_val)+1);    
  cnt+=StrLen(arg2_val)+1;
  
  howMany=StrLen(arg3_val);
  if(howMany>800) howMany=800;
  MemMove(rest+cnt,arg3_val,howMany+1);
  rest[cnt+howMany]=0x00;
  cnt +=howMany+1;
#else
  MemMove(rest+cnt,arg2.val,strlen(arg2.val) + 1); 
  cnt+=strlen(arg2.val)+1;
  
  howMany=strlen(arg3.val);
  if(howMany>800) howMany=800;
  MemMove(rest+cnt,arg3.val,howMany + 1);
  rest[cnt+howMany]='\0';
  cnt +=howMany+1;
#endif

  while(1)
  {    
#ifdef __MC68K__
     find_arg_2();
     if (arg2==null_ptr) break;

     MemMove(rest+cnt,arg2_val,StrLen(arg2_val)+1);
     cnt=cnt+StrLen(arg2_val)+1;
     al.numButtons+=1;
#else
     find_arg_PNO(pnoP, &arg2);
     if (arg2.dataElem == NULL) break;   // DIKEO should have overflow protection

     MemMove(rest+cnt,arg2.val,strlen(arg2.val)+1);
     cnt=cnt+strlen(arg2.val)+1;
     al.numButtons = ByteSwap16(al.numButtons);
     ++al.numButtons;
     al.numButtons = ByteSwap16(al.numButtons);
#endif
  }
  MemMove(rest,&al,8);

  res=DmFindResource(PNO(VbRscDB),(UInt32)'Talt',(UInt16)1,NULL);
  if(res != -1) DmRemoveResource(PNO(VbRscDB),res); //delete alert if there
 
  hView=DmNewResource(PNO(VbRscDB),(UInt32)'Talt',(UInt16)1,cnt);

  if(hView==0) OutOfMemory(-1);
  ptr=MemHandleLock(hView);
//StrPrintF(debug,"verb-alert= %s",rest);
//SysFatalAlert(debug);      
  DmWrite(ptr,0,rest,cnt);
  MemHandleUnlock(hView);

//StrPrintF(debug,"alert arg1=%lu",arg1);
//SysFatalAlert(debug);
#ifdef __MC68K__
  arg1Save = arg1;     //ldm 09132004
#endif
  PNO(msgboxOrAlertUp)=true;  //stops penup from triggering object under msgbox 
  res=FrmAlert(1);
  PNO(msgboxOrAlertUp)=false;
  PNO(ignoreNextPenup)=true;
 
 //StrPrintF(debug,"alert arg1=%lu",arg1);
 //SysFatalAlert(debug);
#ifdef __MC68K__
 arg1=arg1Save;   //ldm 09132004
#endif
#ifdef __MC68K__
  restore_int_val(res,arg1, (double*)arg1_val, arg1_occ1,arg1_occ2,arg1_occ3);
#else
   d = res;
   d = SwapDouble(res);
   misc_stodbl(pnoP, arg1.dataElem, arg1.occ1,arg1.occ2,arg1.occ3,&d);
#endif
}

#ifdef __MC68K__

/********************************************************************************************/
void verb_sound()
{
   SndCommandType s;
  int wait;
  Boolean waitsw;

   find_arg_1_3();  //freq,duration,amplitude
   wait=find_char();
   
   if(PNO(romVersion)<0x03000000)
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
	
//SysFatalAlert("at playsound");
	if (!FtrGet(sysFileCSoundMgr,sndFtrIDVersion,&version))
	{
	    find_arg_1();
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


  
  if(PNO(romVersion)>=(unsigned long)(0x03500000)) WinSetPatternType(customPattern);
  
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
#endif

/********************************************************************************************/
#ifdef __MC68K__
void verb_drawline()
#else
void verb_drawline(PNOBlock *pnoP)   // EMP
#endif
{
  unsigned char pen;
#ifdef __MC68K__
  find_arg_1_4();    //1=topleft  x  2=topleft y 3=endx  4=endy
  pen=find_char();      //pen
#else
  Arg arg_tlx, arg_tly, arg_endx, arg_endy;
  Int16 tlx, tly, endx, endy;
  find_arg_PNO(pnoP, &arg_tlx);
  find_arg_PNO(pnoP, &arg_tly);
  find_arg_PNO(pnoP, &arg_endx);
  find_arg_PNO(pnoP, &arg_endy);
  pen = find_char(pnoP);
  tlx = ReadUnaligned64(arg_tlx.val);
  tly = ReadUnaligned64(arg_tly.val);
  endx = ReadUnaligned64(arg_endx.val);
  endy = ReadUnaligned64(arg_endy.val);
#endif


#ifdef __MC68K__
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
#else
  if (pen==0x00) WinDrawLine(tlx, tly, endx, endy);
  else
  {
    if(pen==0x01) WinEraseLine(tlx, tly, endx, endy);
    else           WinDrawGrayLine(tlx, tly, endx, endy);

  }
#endif  
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_drawchars()
#else
void verb_drawchars(PNOBlock *pnoP)
#endif
{
  unsigned char pen;
#ifdef __MC68K__
  find_arg_1_3();   //1=chars , 2=x , 3=y
  pen=find_char();
  if (pen==0x00) WinDrawChars(arg1_val,StrLen(arg1_val),
                                 *((double*)arg2_val),*((double*)arg3_val));
  else           WinDrawInvertedChars(arg1_val,StrLen(arg1_val),
                                 *((double*)arg2_val),*((double*)arg3_val));

#else
  Arg charsArg, xArg, yArg;
  double x, y;
  find_arg_PNO(pnoP, &charsArg);
  find_arg_PNO(pnoP, &xArg);
  find_arg_PNO(pnoP, &yArg);
  pen=find_char(pnoP);
  x = ReadUnaligned64(xArg.val);
  y = ReadUnaligned64(yArg.val);
  if (pen==0x00) WinDrawChars(charsArg.val,strlen(charsArg.val), x, y);
  else           WinDrawInvertedChars(charsArg.val,strlen(charsArg.val), x, y);

#endif
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_erasewindow()
#else
void verb_erasewindow(PNOBlock *pnoP)
#endif
{
  WinSetDrawWindow(PNO(DrawWin)); 
  WinSetActiveWindow(PNO(DrawWin));
  WinEraseWindow();
}


/********************************************************************************************/
#ifdef __MC68K__
Handle findNewWindow()
#else
Handle findNewWindow(PNOBlock *pnoP)    // EMP
#endif
{
   VoidHand h;
   struct DrawWinStruct *p;
   VoidHand nameH;
   char *  nameP;
   
#ifdef __MC68K__
   find_arg_1();  //window name string
#else
   Arg winNameArg;
   VoidHand tempH;
   find_arg_PNO(pnoP, &winNameArg);
#endif
   h= PNO(winRoot);
   while(1)
   {
      if(h==0)
      {
           //create new window
           h=MemHandleNew(sizeof(struct DrawWinStruct));
           if(h==0) OutOfMemory(6052);  //05282003
           p=(struct DrawWinStruct*) MemHandleLock(h);
#ifdef __MC68K__
           p->next=PNO(winRoot);
           nameH=MemHandleNew(StrLen(arg1_val)+1);
#else
           tempH = PNO(winRoot);
           p -> next = (MemHandle) ByteSwap32(tempH);
           nameH=MemHandleNew(strlen(winNameArg.val)+1);
#endif
           if(nameH==0) OutOfMemory(6053);  //05282003
           nameP=(char*)MemHandleLock(nameH);
#ifdef __MC68K__
           StrCopy(nameP,arg1_val);
#else
           strcpy(nameP,winNameArg.val);
#endif
           MemHandleUnlock(nameH);
#ifdef __MC68K__
           p->nameHandle=(Handle)nameH;
#else
           tempH = nameH;
           p -> nameHandle = (MemHandle) ByteSwap32(tempH);
#endif
           PNO(winRoot)=(Handle)h;
           MemPtrUnlock(p);
           return((Handle)h);
       }
        p=(struct DrawWinStruct*)MemHandleLock(h);
#ifdef __MC68K__
        nameP=(char*)MemHandleLock(p->nameHandle);
#else
        tempH = p -> nameHandle;
        nameP = (char *)MemHandleLock((MemHandle) ByteSwap32(tempH));
#endif
#ifdef __MC68K__
        if( StrCaselessCompare(nameP,arg1_val)==0)
#else
        if( StrCaselessCompare(nameP,winNameArg.val)==0)
#endif
        {
            MemPtrUnlock(nameP);
            MemPtrUnlock(p);
            return((Handle)h);
        }
        
       MemPtrUnlock(nameP);
       h=p->next;
#ifndef __MC68K__
       h = (MemHandle) ByteSwap32(h);
#endif
       MemPtrUnlock(p);
   }
}

/********************************************************************************************/
#ifdef __MC68K__
Handle findOldWindow()
#else
Handle findOldWindow(PNOBlock *pnoP, Arg *arg1)
#endif
{
   char wk[128];
   Handle         h;
   char *nameP;
   struct DrawWinStruct *p;
#ifdef __MC68K__
   find_arg_1();  //window name string
#else
   MemHandle nh;
   find_arg_PNO(pnoP, arg1);
#endif

   h=PNO(winRoot);
   
   while(1)
   {
      if(h==0) 
      {
#ifdef __MC68K__
        StrCopy(wk,"Can't locate draw window=");
        StrCat(wk,arg1_val);
        SysFatalAlert(wk);
        ErrThrow(-1);                 //inserted 05212003
#else
        char *b;
        b = strcpy(wk, "Can't locate draw window=");
        strcpy(b,arg1 -> val);
        SysFatalAlert(wk);
        GlueErrThrow(pnoP, -1);                 //inserted 05212003
#endif
      }
      p=(struct DrawWinStruct*)MemHandleLock(h);
#ifdef __MC68K__
      nameP=(char*)MemHandleLock(p->nameHandle);
#else
      nh = p -> nameHandle;
      nh = (MemHandle) ByteSwap32(nh);
      nameP = (char *)MemHandleLock(nh);
#endif

#ifdef __MC68K__
      if(StrCaselessCompare(nameP,arg1_val)==0)
#else
      if(StrCaselessCompare(nameP,arg1 -> val)==0)
#endif
      {
#ifdef __MC68K__
          MemHandleUnlock(p->nameHandle);
#else
          MemHandleUnlock(nh);
#endif
          MemHandleUnlock(h);
          return(h);            
      }
#ifdef __MC68K__
      MemHandleUnlock(p->nameHandle);
#else
      MemHandleUnlock(nh);
#endif
      h=p->next;
#ifndef __MC68K__
      h = (Handle) ByteSwap32(h);
#endif
      MemPtrUnlock(p);
   }
   return h;
}


/********************************************************************************************/
#ifdef __MC68K__
void verb_setcurwindow()
#else
void verb_setcurwindow(PNOBlock *pnoP)     // EMP
#endif
{
  RectangleType r;
  char wk[128];
  Handle          tempH;
  struct DrawWinStruct * tempP;
#ifdef __MC68K__
  tempH=findOldWindow();
#else
  Arg arg1;
  WinHandle win;
  tempH = findOldWindow(pnoP, &arg1);
#endif
  if(tempH==0)
  {
#ifdef __MC68K__
      StrCopy(wk,"Accessed an unknown window=");
      StrCat(wk,arg1_val);
      SysFatalAlert(wk);
      ErrThrow(-1);                 //inserted 05212003 
#else
      char *b;
      b = strcpy(wk,"Accessed an unknown window=");
      strcpy(b, arg1.val);
      SysFatalAlert(wk);
      GlueErrThrow(pnoP, -1);                 //inserted 05212003 
#endif
  }
  
  tempP=(struct DrawWinStruct*)MemHandleLock(tempH);
#ifdef __MC68K__
  PNO(DrawWin)=tempP->win;
  WinSetActiveWindow(PNO(DrawWin));
  WinSetDrawWindow(PNO(DrawWin));                
#else
  win = tempP -> win;
  win = (WinHandle) ByteSwap32(win);
  PNO(DrawWin)=win;
  WinSetActiveWindow(win);
  WinSetDrawWindow(win);                
#endif
  
  WinGetWindowBounds(&r);
  r.topLeft.x=0;                            
  r.topLeft.y=0;                            
  WinSetClip(&r);        
  MemHandleUnlock(tempH);  
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_destroywindow()
#else
void verb_destroywindow(PNOBlock *pnoP)     // EMP
#endif
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

#ifdef __MC68K__
  tempH=findOldWindow();
#else
  Arg arg1;
  WinHandle prevWin, curWin;
  tempH = findOldWindow(pnoP, &arg1);
#endif

  if(tempH==0)
  {
#ifdef __MC68K__
      StrCopy(wk,"Accessed an unknown window=");
      StrCat(wk,arg1_val);
      SysFatalAlert(wk);
      ErrThrow(-1);                 //inserted 05212003 
#else
      char *b;
      b = strcpy(wk, "Accessed an unknown window=");
      strcpy(b, arg1.val);
      GlueErrThrow(pnoP, -1);
#endif
  }

  tempP=(struct DrawWinStruct*)MemHandleLock(tempH);
  saveWin=tempP->win;
#ifndef __MC68K__
  saveWin = (WinHandle) ByteSwap32(saveWin);
#endif

#ifdef __MC68K__
  WinSetDrawWindow(tempP->prevWin);
  WinSetActiveWindow(tempP->prevWin);
  WinDeleteWindow(tempP->win,true);
#else
  prevWin = tempP -> prevWin;
  prevWin = (WinHandle) ByteSwap32(prevWin);
  WinSetDrawWindow(prevWin);
  WinSetActiveWindow(prevWin);
  curWin = tempP -> win;
  curWin = (WinHandle) ByteSwap32(curWin);
  WinDeleteWindow(curWin,true);
#endif

  WinGetWindowBounds(&r);
  WinSetClip(&r);
  
  MemPtrUnlock(tempP);
 
  h=PNO(winRoot);
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
#ifdef __MC68K__
            PNO(winRoot)=p->next;
#else
            MemHandle rootH = p -> next;
            PNO(winRoot) = (MemHandle) ByteSwap32(rootH);
#endif             
         }
         else 
         {
             prevPtr=(struct DrawWinStruct *)MemHandleLock(prevH);
             prevPtr->next=p->next;
             MemPtrUnlock(prevPtr);
         }

#ifdef __MC68K__
         MemHandleFree(p->nameHandle);
#else
         {
            MemHandle name = p -> nameHandle;   // DIKEOBATS
            MemHandleFree((MemHandle) ByteSwap32(name));
         }
#endif
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
#ifndef __MC68K__
        p = (MemPtr) ByteSwap32(p);
#endif
        MemPtrUnlock(p);
     }
  }
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_createwindow()
#else
void verb_createwindow(PNOBlock *pnoP)
#endif
{
  RectangleType r;
  UInt16 err;
  struct DrawWinStruct*   tempP;
  Handle tempH; 
#ifdef __MC68K__
  tempH=findNewWindow();
  find_arg_1_4();   // 1=topleft x, 2=topleft y, 3=width, 4=height
#else
  Arg tlxArg, tlyArg, widthArg, heightArg;
  WinHandle win;
  tempH=findNewWindow(pnoP);
  find_arg_PNO(pnoP, &tlxArg);
  find_arg_PNO(pnoP, &tlyArg);
  find_arg_PNO(pnoP, &widthArg);
  find_arg_PNO(pnoP, &heightArg);
#endif

#ifdef __MC68K__
  r.topLeft.x=*((double*)arg1_val);
  r.topLeft.y=*((double*)arg2_val);
  r.extent.x=*((double*)arg3_val);
  r.extent.y=*((double*)arg4_val);
#else
  RctSetRectangle(&r, ReadUnaligned64(tlxArg.val),
                      ReadUnaligned64(tlyArg.val),
                      ReadUnaligned64(widthArg.val),
                      ReadUnaligned64(heightArg.val));
#endif

  tempP=(struct DrawWinStruct*)MemHandleLock(tempH);

#ifdef __MC68K__  
  tempP->prevWin=WinGetDrawWindow();
#else
  win = WinGetDrawWindow();
  tempP -> prevWin = (WinHandle) ByteSwap32(win);
#endif

  PNO(DrawWin)=WinCreateWindow(&r,1,false,false,&err);
  
  WinSetActiveWindow(PNO(DrawWin));
  
  WinSetDrawWindow(PNO(DrawWin));                //6.28
  r.topLeft.x=0;                            //6.28
  r.topLeft.y=0;                            //6.28
  WinSetClip(&r);                            //6.28
#ifdef __MC68K__
  tempP->win=PNO(DrawWin);
#else
  win = PNO(DrawWin);
  tempP -> win = (WinHandle) ByteSwap32(win);
#endif
  MemHandleUnlock(tempH); 
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_sub()
#else
void verb_sub(PNOBlock *pnoP)   // EMP
#endif
{
  UInt16 instr_ctr_save;
  char *saveCodePtr;
  UInt16 callerInstrCtrSave;
  Int16 kk,mm,nn;
  
  Int16 ix;
  Int16 id;
  
  Err err;
  VoidHand newHand;
  VoidPtr newPtr;
  ULong wkl;
  Int16 wk1;

#ifndef __MC68K__
  Arg arg1, arg2;
  Int16 newFuncLinkNo;
  UInt16 newOffset;
  UInt16 s;
#endif
//if(debug_sw){
//dbug("verb_sub");
//}



#ifdef __MC68K__
 //verbOrFunction ='s';   // EMP never seems to be used
#endif
  callerInstrCtrSave=PNO(codeBlockPtr)->instr_ctr;
//StrPrintF(debug,"callers codePtr=%lu  callers-instr-ctr=%u PNO(instr_ctr)=%d curCodePtr=%lu",(unsigned long)(PNO(codeBlockPtr)->codePtr),PNO(codeBlockPtr)->instr_ctr,PNO(instr_ctr),(unsigned long)PNO(codePtr));
//SysFatalAlert(debug); 


  PNO(codeBlockPtr)->argsOffset=PNO(instr_ctr); //save called args ptr
  instr_ctr_save=PNO(instr_ctr);
//StrPrintF(debug,"sub start saving called pgms args offset=%d",PNO(instr_ctr));
//SysFatalAlert(debug);

  while (1)
  {
//if(debug_sw){
//dbug("3");
//}
    instr_ctr_save=PNO(instr_ctr);
    saveCodePtr=PNO(codePtr);
    PNO(codePtr)=(char*)PNO(codeBlockPtr)->codePtr;
    PNO(instr_ctr)=PNO(codeBlockPtr)->instr_ctr;
//if(debug_sw){
//StrPrintF(debug,"ss  PNO(instr_ctr)=%d PNO(codeBlockPtr)=%lu codePtr=%lu",PNO(instr_ctr),PNO(codeBlockPtr),PNO(codePtr));
//SysFatalAlert(debug);
//}


#ifdef __MC68K__
    find_arg_1();
#else
    find_arg_PNO(pnoP, &arg1);
#endif
//if(debug_sw){
//dbug("past ss");
//}
    PNO(codeBlockPtr)->instr_ctr=PNO(instr_ctr);
    PNO(codePtr)=saveCodePtr;
    PNO(instr_ctr)=instr_ctr_save;

#ifdef __MC68K__
    find_arg_2();
#else
    find_arg_PNO(pnoP, &arg2);
#endif

#ifdef __MC68K__
    if (arg1 == NULL)
    {

      if (arg2 != NULL)
      {
#else
    if (arg1.dataElem == NULL)
    {

      if (arg2.dataElem != NULL)
      {
#endif
wrong_no:
#ifdef __MC68K__
         MiscFatalAlert("Wrong number of func args");
#else
         SysFatalAlert("Wrong number of func args");
#endif
      }
      else break;
    }


//dbug("caller not null");
#ifdef __MC68K__
    if (arg2 == NULL)
#else
    if (arg2.dataElem == NULL)
#endif
    {
//dbug("func is null");
        goto wrong_no;
    }
//StrPrintF(debug,"arg2#=%d s1=%d s2=%d s3=%d  offset=%d",arg2->tbl_no,arg2->max_no_values1,arg2->max_no_values2, arg2->max_no_values3,PNO(instr_ctr)); 
//SysFatalAlert(debug);
#ifdef __MC68K__
    subFuncXferArgument();
#else
    subFuncXferArgument(pnoP, &arg1, &arg2);
#endif
  }
  
no_args:

goahead:
//if(debug_sw){
//dbug("e");
//}
   PNO(codeBlockPtr)->instr_ctr=callerInstrCtrSave;  //reset caller so can reuse later

    //copy the current work var handles
//StrPrintF(debug,"init wk vars id=%d",PNO(lastSubOrFunctionId));  
//SysFatalAlert(debug); 
   PNO(userFunctionSequentialNo)+=1;  //bump the count of nested user functions
   PNO(codeBlockPtr)->functionLinkNo=PNO(lastSubOrFunctionId);
//StrPrintF(debug,"new sub increm seqno=%d   id=%d",userFunctionSequentialNo,PNO(lastSubOrFunctionId));
//SysFatalAlert(debug);     
   wkl=PNO(work_de_max)*4;   //need to copy all work variable handles
   id=PNO(codeBlockPtr)->functionLinkNo;
   
   while(1)
   {
      ix=DmFindResource(PNO(VbRscDB),(ULong)'fwrk',id,NIL); 
      if(ix!= -1)
      {
//dbug("got old sub rec");
#ifdef __MC68K__
        newHand=MiscDmGetResourceIndex(PNO(VbRscDB),ix,"rescwk"); 
        newPtr=MiscHandleLock(newHand);
        if( (*((Int16*)newPtr) != PNO(codeBlockPtr)->functionLinkNo) ||
            (*(UInt16*)((char*)newPtr+2) != PNO(codeBlockPtr)->offset))
#else
        newHand=DmGetResourceIndex(PNO(VbRscDB),ix); 
        newPtr=MemHandleLock(newHand);
        newFuncLinkNo = *((Int16*)newPtr);
        newFuncLinkNo = ByteSwap16(newFuncLinkNo);
        
        newOffset = *(UInt16*)((char*)newPtr+2);
        newOffset = ByteSwap16(newOffset);
        
        if (newFuncLinkNo != PNO(codeBlockPtr)->functionLinkNo ||
            newOffset != PNO(codeBlockPtr)->offset)
#endif
        {
#ifdef __MC68K__
           MiscHandleUnlock(newHand);
           MiscDmReleaseResource(newHand);
#else
           MemHandleUnlock(newHand);
           DmReleaseResource(newHand);
#endif
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
#ifdef __MC68K__
        newHand=MiscDmNewResource(PNO(VbRscDB),(ULong)'fwrk',id,wkl+4,"rescwk"); //setup a new resource for the new copy
        if(newHand==0) OutOfMemory(6101);    //inserted 05282003
        newPtr=MiscHandleLock(newHand);  
#else
        newHand = DmNewResource(PNO(VbRscDB),(ULong)'fwrk',id,wkl+4); //setup a new resource for the new copy
        if(newHand==0) OutOfMemory(6101);    //inserted 05282003
        newPtr=MemHandleLock(newHand);  
#endif
        break;
      }
   }   
//StrPrintF(debug,"find linkNo=%d rsc=%d ",id,ix);
//SysFatalAlert(debug);
                              //point to the new wk var record

//dbug("verb sub");
#ifdef __MC68K__
   DmWrite(newPtr,0,&PNO(codeBlockPtr)->functionLinkNo,2);
 
   DmWrite(newPtr,2,&PNO(codeBlockPtr)->offset,2);
 
   DmWrite(newPtr,4,(char*)PNO(deListPtr)+4,wkl);  //copy the record
#else
   s = PNO(codeBlockPtr) -> functionLinkNo;
   s = ByteSwap16(s);
   DmWrite(newPtr, 0, &s, 2);
   
   s = PNO(codeBlockPtr) -> offset;
   s = ByteSwap16(s);
   DmWrite(newPtr, 2, &s, 2);
   
   DmWrite(newPtr,4,(char*)PNO(deListPtr)+4,wkl);  //copy the record   
#endif

#ifdef __MC68K__
   MiscPtrUnlock(newPtr);

   err=MiscDmReleaseResource(newHand);                             //release the new record 
   if(err) MiscFatalAlert("Internal error-Can't release work record.");
#else
   MemPtrUnlock(newPtr);

   err=DmReleaseResource(newHand);                             //release the new record 
   if(err) SysFatalAlert("Internal error-Can't release work record.");
#endif 
   
   //old wk var handles saved, now zero them all for new func
   
    DmSet(PNO(deListPtr),4,wkl,0x00); 
//dbug("leaving sub init");    
    return;
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_start_function()
#else
void verb_start_function(PNOBlock *pnoP)
#endif
{
  UInt16 instr_ctr_save;
  Int16 kk,mm,nn;
  char *codePtrSave;
  UInt16 callerInstrCtrSave=PNO(codeBlockPtr)->instr_ctr;
  
  Int16 ix;
  Int16 id;
  Err err;
  VoidHand newHand;
  VoidPtr newPtr;
  ULong wkl;
  Int16 wk1;
#ifndef __MC68K__
  Arg arg1, arg2;
#endif
  
  PNO(codeBlockPtr)->argsOffset=PNO(instr_ctr);  //save called args ptr  
//dbug("copying args");
  while (1)   //copy args to internal vars
  {

    instr_ctr_save=PNO(instr_ctr);
    codePtrSave=PNO(codePtr);
    PNO(codePtr)=(char*)PNO(codeBlockPtr)->codePtr;
    PNO(instr_ctr)=PNO(codeBlockPtr)->instr_ctr;
//StrPrintF(debug,"moving one arg instr-ctr=%ui",PNO(instr_ctr));
//SysFatalAlert(debug);
#ifdef __MC68K__   
    find_arg_1();
#else
    find_arg_PNO(pnoP, &arg1);
#endif
    PNO(codeBlockPtr)->instr_ctr=PNO(instr_ctr);
    PNO(codePtr)=codePtrSave;
    PNO(instr_ctr)=instr_ctr_save;
#ifdef __MC68K__
    find_arg_2();
     if (arg1==NULL)
    {

      if (arg2 != NULL)
#else
    find_arg_PNO(pnoP, &arg2);
     if (arg1.dataElem==NULL)
    {

      if (arg2.dataElem != NULL)
#endif
      {
wrong_no:
         SysFatalAlert("Wrong number of func args");
      }
      else break;
    }
//dbug("caller not null");
#ifdef __MC68K__
    if (arg2==null_ptr)
#else
    if (arg2.dataElem == NULL)
#endif
    {
//dbug("func is null");
        goto wrong_no;
    }
//StrPrintF(debug,"arg2#=%d s1=%d s2=%d s3=%d  offset=%d",arg2->tbl_no,arg2->max_no_values1,arg2->max_no_values2, arg2->max_no_values3,PNO(instr_ctr)); 
//SysFatalAlert(debug);
#ifdef __MC68K__
    subFuncXferArgument();
#else
    subFuncXferArgument(pnoP, &arg1, &arg2);
#endif
  }
//dbug("args done");

#ifdef __MC68K__   
    find_arg_2();   //name of func dataname to put result in   ??used or not
#else
    find_arg_PNO(pnoP, &arg2);
#endif

    PNO(codeBlockPtr)->instr_ctr=callerInstrCtrSave;  //reset caller so can reuse later
    
   //copy the current work var handles
   
   PNO(userFunctionSequentialNo)+=1;  //bump the count of nested user functions
   PNO(codeBlockPtr)->functionLinkNo=PNO(lastSubOrFunctionId);
//StrPrintF(debug,"function increm seqno=%d   id=%d",userFunctionSequentialNo,lastSubOrFunctionId);
//SysFatalAlert(debug);   
   wkl=PNO(work_de_max)*4;   //need to copy all work variable handles
   id=PNO(codeBlockPtr)->functionLinkNo;
   
   while(1)
   {
      ix=DmFindResource(PNO(VbRscDB),(ULong)'fwrk',id,NIL); 
      if(ix!= -1)
      {
//dbug("got old func rec");
#ifdef __MC68K__
        newHand=MiscDmGetResourceIndex(PNO(VbRscDB),ix,"rescwk"); 
        newPtr=MiscHandleLock(newHand);
        if( (*((int*)newPtr) != PNO(codeBlockPtr)->functionLinkNo) || (*(unsigned int*)((char*)newPtr+2) != PNO(codeBlockPtr)->offset))
        {
           MiscHandleUnlock(newHand);
           MiscDmReleaseResource(newHand);
           id+=50;                        //increm recno by 50 to try again
        }
#else
        Int16 newFLN;
        UInt16 newOffset;
        newHand = DmGetResourceIndex(PNO(VbRscDB), ix);
        newPtr = MemHandleLock(newHand);
        newFLN = *((int*)newPtr);
        newFLN = ByteSwap16(newFLN);
        newOffset = *(UInt16*)((char*)newPtr+2);
        newOffset = ByteSwap16(newOffset);

        if( (newFLN != PNO(codeBlockPtr)->functionLinkNo) || 
            (newOffset != PNO(codeBlockPtr)->offset))
        
        {
           MemHandleUnlock(newHand);
           DmReleaseResource(newHand);
           id+=50;                        //increm recno by 50 to try again
        }
#endif
        else
        {
           break;
        }   
      }
      else
      {
//dbug("got new func rec");
#ifdef __MC68K__
        newHand=MiscDmNewResource(PNO(VbRscDB),(ULong)'fwrk',id,wkl+4,"rescwk"); //setup a new resource for the new copy
        if(newHand==0) OutOfMemory(6102);    //inserted 05282003
        newPtr=MiscHandleLock(newHand);
#else
        newHand=DmNewResource(PNO(VbRscDB),(ULong)'fwrk',id,wkl+4); //setup a new resource for the new copy
        if(newHand==0) OutOfMemory(6102);    //inserted 05282003
        newPtr=MemHandleLock(newHand);
#endif 
        break;
      }
   }   
//StrPrintF(debug,"find linkNo=%d rsc=%d ",id,ix);
//SysFatalAlert(debug);
                              //point to the new wk var record
//dbug("start function");
#ifdef __MC68K__
   DmWrite(newPtr,0,&PNO(codeBlockPtr)->functionLinkNo,2);
   DmWrite(newPtr,2,&PNO(codeBlockPtr)->offset,2);
#else
   {
       UInt16 s;
       s = PNO(codeBlockPtr) -> functionLinkNo;
       s = ByteSwap16(s);
       DmWrite(newPtr, 0, &s, 2);
       s = PNO(codeBlockPtr) -> offset;
       s = ByteSwap16(s);
       DmWrite(newPtr, 2, &s, 2);
   }
#endif
   DmWrite(newPtr,4,(char*)PNO(deListPtr)+4,wkl);  //copy the record


#ifdef __MC68K__
   MiscPtrUnlock(newPtr);
   err=MiscDmReleaseResource(newHand);                             //release the new record 
   if(err) MiscFatalAlert("Internal error-Can't release work record.");
#else
   MemPtrUnlock(newPtr);
   err=DmReleaseResource(newHand);                             //release the new record 
   if(err) SysFatalAlert("Internal error-Can't release work record.");
#endif
 
   //old wk var handles saved, now zero them all for new func
//dbug("zeroing wk var ptrs");
   
   DmSet(PNO(deListPtr),4,wkl,0x00); 

}


/********************************************************************************************/
#ifdef __MC68K__
void verb_dbgetnorecs()
#else
void verb_dbgetnorecs(PNOBlock *pnoP)
#endif
{
  struct dbType *db;
  double d;
  Int16 res;
  UInt i;
  DmOpenRef dbr;
#ifdef __MC68K__
   dbfind_arg(2); //1=result,2=db
    db=getDatabasePtr();
   dbr=db->dm;
   chkDbOpen(db);
#else
    Arg arg1;

    find_arg_PNO(pnoP, &arg1);
    PNO(dbNo) = find_integer(pnoP)-1;
    db=getDatabasePtr(pnoP);
    dbr=db->dm;
    dbr = (DmOpenRef) ByteSwap32(dbr);
    chkDbOpen(pnoP, db);
#endif
  
   i=DmNumRecords(dbr);
   d=i;

#ifdef __MC68K__
   misc_stodbl1(&d);
#else
   d = SwapDouble(d);
   misc_stodbl(pnoP, arg1.dataElem, arg1.occ1, arg1.occ2, arg1.occ3, &d);
#endif
  
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_dbposition()
#else
void verb_dbposition(PNOBlock *pnoP)
#endif
{
  struct dbType *db;
  VoidHand recHand;
  VoidPtr  recPtr;
  Int16 res;
  char nullbyte[2] = {0x00,0x00};
  
  UInt16 i;
  UInt16 index;
  DmOpenRef dbr;
  Int16 err;
#ifdef __MC68K__
  dbfind_arg(4); //1=errcode,2=db,3=where,4=offset
   
   db=getDatabasePtr( );
   dbr=db->dm;
   chkDbOpen(db);
#else
    Arg arg1, arg2, arg3, arg4;
    double d;
    
    find_arg_PNO(pnoP, &arg1);
    PNO(dbNo) = find_integer(pnoP)-1;
    find_arg_PNO(pnoP, &arg3);
    find_arg_PNO(pnoP, &arg4);
    
    db=getDatabasePtr(pnoP);
    dbr=db->dm;
    dbr = (DmOpenRef) ByteSwap32(dbr);
    chkDbOpen(pnoP, db);
#endif


#ifdef __MC68K__
   index=basc_integ_value(arg3,(double*)arg3_val)-1;
#else
    d = ReadUnaligned64(arg3.val);
    index = d;
    --index;
#endif

   i=DmNumRecords(dbr);
   while( DmNumRecords(dbr) < (index+1) )
   {
       i++;
       
       //create new record
#ifndef __MC68K__
// EMP PACE doesn't swap this
// EMP now it does 3/31/04        i = ByteSwap16(i);
#endif

       recHand=DmNewRecord(dbr,&i,1);
#ifndef __MC68K__
// EMP PACE doesn't swap this
// EMP now it does 3/31/04        i = ByteSwap16(i);
#endif
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

#ifdef __MC68K__
   db->LastDbRecordRead=index;
   db->offset=basc_integ_value(arg4,(double*)arg4_val);
   db->curHand=recHand;
#else
   db -> LastDbRecordRead=ByteSwap16(index);
   db -> offset=(UInt16) ReadUnaligned64(arg4.val);
   db -> curHand = (MemHandle) ByteSwap32(recHand);
#endif
   DmReleaseRecord(dbr,index,false);
   setDbOK();
}

Int16 commonDbcloseLogic(struct dbType *db);

/********************************************************************************************/
#ifdef __MC68K__
void verb_dbclose()
#else
void verb_dbclose(PNOBlock *pnoP)
#endif
{
  Int16 err;
  struct dbType *db;
  VoidHand recHand;
  VoidPtr  recPtr;
  Int16 res;
#ifdef __MC68K__
  dbfind_arg(2);
  db=getDatabasePtr();
  if (db->openSw!='o') 
  {
      setDbErr(dmErrInvalidParam);
      return;
  }
#else
    Arg arg1;
    double d;
    VoidPtr dbc;
    
    find_arg_PNO(pnoP, &arg1);
    PNO(dbNo) = find_integer(pnoP)-1;
    db=getDatabasePtr(pnoP);
#endif
  res=commonDbcloseLogic(db);   //added 09242003
  if (res==0) {setDbOK();}        //added 09242003
  else        {setDbErr(res);}    //added 09242003
}

Int16 commonDbcloseLogic(struct dbType *db)
{
  DmOpenRef dbr;
	Int16 err;

#ifdef __MC68K__
  dbr=db->dm;
#else
    dbr=db->dm;
    dbr = (DmOpenRef) ByteSwap32(dbr);
#endif

  if (db->openSw!='o') 
  {
      return (dmErrInvalidParam);
  }

  err=DmCloseDatabase(dbr);
//StrPrintF(debug,"close ok stat=%d",err);
//SysFatalAlert(debug);

   db->openSw='c';
   db->LastDbRecordRead=-1;   // OK for pno
   db->curHand=0;
   db->offset=0;
   
   return err;
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_dbopen()
#else
void verb_dbopen(PNOBlock *pnoP)   // EMP
#endif
{
  struct dbType *db;
  VoidHand recHand;
  VoidPtr  recPtr;
  int res;
  DmOpenRef dbr;
  int err;
  DmOpenRef dbref;
#ifdef __MC68K__
   dbfind_arg(4);
   db=getDatabasePtr();
   db->lid=DmFindDatabase( *((double*)arg4_val),arg3_val);
   if(db->lid==0)
   {
      setDbErr(DmGetLastErr());
      return;
   }
#else
    Arg arg1, arg3, arg4;
    LocalID lid;
    UInt16 cardNo;
    double d;
    find_arg_PNO(pnoP, &arg1);
    PNO(dbNo) = find_integer(pnoP)-1;
    find_arg_PNO(pnoP, &arg3);
    find_arg_PNO(pnoP, &arg4);
    db=getDatabasePtr(pnoP);
    d = ReadUnaligned64(arg4.val);
    lid = DmFindDatabase((UInt16) d, arg3.val);
    db -> lid = ByteSwap32(lid);
    if (lid == 0)
    {
      setDbErr(DmGetLastErr());
      return;
    }
#endif

#ifdef __MC68K__
   dbref=DmOpenDatabase(*((double*)arg4_val),db->lid,dmModeReadWrite);
   if(dbref==0)
   {
         dbref=DmOpenDatabase(*((double*)arg4_val),db->lid,dmModeReadOnly);//02.20.02 GH
#else
   dbref=DmOpenDatabase((UInt16) d, lid,dmModeReadWrite);
   if(dbref==0)
   {
         dbref=DmOpenDatabase((UInt16) d, lid,dmModeReadOnly);//02.20.02 GH
#endif
         if(dbref==0)
         {                                              //02.20.02 GH
          setDbErr(DmGetLastErr()); // not opened
          return;
      }
      else setDbRes(3); //opened in read only mode                            //02.20.02 GH
   }
   else setDbOK();        //opened in read write mode

#ifdef __MC68K__
   db->openSw='o';
   db->dm=dbref;
   db->LastDbRecordRead=-1;
   db->curHand=0;
   db->offset=0;
   db->cardno=*((double*)arg4_val);
#else

   db->openSw='o';
   db->dm= (void *) ByteSwap32(dbref);
   db->LastDbRecordRead=-1; // OK, already swapped
   db->curHand=0;
   db->offset=0;
   cardNo = d;
   db->cardno= ByteSwap16(cardNo);
#endif
   //setDbOK();            //02.20.02 GH
}



/********************************************************************************************/
#ifdef __MC68K__
void verb_dbcreate()
#else
void verb_dbcreate(PNOBlock *pnoP)    // EMP
#endif
{
  struct dbType *db;
  VoidHand recHand;
  VoidPtr  recPtr;
  Int16 res;
  DmOpenRef *dbr;
  UInt16 cardno;
  UInt32 creator;
  UInt32 types;
  Int16 err;
  LocalID lid;
  UInt16 attrib;
#ifdef __MC68K__
   dbfind_arg(4); //1=res,2=db,3=name,4=cardno,5=creator
   find_arg_5();
   cardno=*((double*)arg4_val);
#else
    Arg arg1, arg3, arg4, arg5;
    double d;
    
    find_arg_PNO(pnoP, &arg1);
    PNO(dbNo) = find_integer(pnoP)-1;
    find_arg_PNO(pnoP, &arg3);
    find_arg_PNO(pnoP, &arg4);
    find_arg_PNO(pnoP, &arg5);
    
    d = ReadUnaligned64(arg4.val);
    cardno = d;
    
    creator = ReadUnaligned32(arg5.val);
#endif

#ifdef __MC68K__
   err=DmCreateDatabase(cardno,arg3_val,*((ULong *)arg5_val),
          (ULong)'data',false);
#else
   err=DmCreateDatabase(cardno,arg3.val,creator,
          (UInt32)'data',false);
#endif

//StrPrintF(debug,"cardno=%d err=%d",cardno,err);
//SysFatalAlert(debug);
	if (err==0) {
#ifdef __MC68K__
   		lid=DmFindDatabase( cardno, arg3_val);
#else
   		lid=DmFindDatabase( cardno, arg3.val);
#endif
   		DmDatabaseInfo( cardno, lid, NULL,&attrib,NULL,NULL,NULL,NULL,
                                NULL,NULL,NULL,NULL,NULL);
   		attrib=attrib | dmHdrAttrBackup;    //set to hotsync 
   		DmSetDatabaseInfo( cardno, lid, NULL,&attrib,NULL,NULL,NULL,NULL,
                                NULL,NULL,NULL,NULL,NULL); 
   }   
                            
   setDbRes(err);
}


/********************************************************************************************/
#ifdef __MC68K__
void verb_dberase()
#else
void verb_dberase(PNOBlock *pnoP)   // EMP
#endif
{
  struct dbType *db;
  Int16 err;
#ifdef __MC68K__
  dbfind_arg(2);
  db=getDatabasePtr();

  err=DmDeleteDatabase( db->cardno,db->lid);
#else
    Arg arg1;
    double d;
    VoidPtr dbc;
    LocalID lid;
    UInt16 cardno;
    
    find_arg_PNO(pnoP, &arg1);
    PNO(dbNo) = find_integer(pnoP)-1;
    db=getDatabasePtr(pnoP);
    
    cardno = db -> cardno;
    cardno = ByteSwap16(cardno);
    
    lid = db -> lid;
    lid = ByteSwap32(lid);

    err=DmDeleteDatabase(cardno, lid);
#endif


  if(err!=0) {setDbErr(err);}
  else      {setDbOK();}
}


/********************************************************************************************/
#ifdef __MC68K__
void verb_dbreset() //reset back to the 1st rec on next read
#else
void verb_dbreset(PNOBlock *pnoP) //reset back to the 1st rec on next read
#endif
{
  struct dbType *db;
  VoidHand recHand;
  VoidPtr  recPtr;
  DmOpenRef dbr;
  Int16 err;
  Int16 res;

#ifdef __MC68K__
  dbfind_arg(2);   //result and dbref
  db=getDatabasePtr();
  dbr=db->dm;
  chkDbOpen(db);
  db->LastDbRecordRead=-1;
  setDbOK();
#else
    Arg arg1;
    
    find_arg_PNO(pnoP, &arg1);
    PNO(dbNo) = find_integer(pnoP)-1;
    db=getDatabasePtr(pnoP);
    dbr=db->dm;
    dbr = (DmOpenRef) ByteSwap32(dbr);
    chkDbOpen(pnoP, db);
  db->LastDbRecordRead=-1;  // OK because -1 swapped is -1
  setDbOK();
#endif
}



/********************************************************************************************/
#ifdef __MC68K__
void verb_dbreadnext()
#else
void verb_dbreadnext(PNOBlock *pnoP)
#endif
{
  struct dbType *db;
  VoidHand recHand;
  VoidPtr  recPtr;
  DmOpenRef dbr;
  Int16 err;
  Int16 res;
#ifdef __MC68K__
  dbfind_arg(3);
  db=getDatabasePtr();
  dbr=db->dm;
  chkDbOpen(db);
#else
    Arg arg1, arg3;
    double d;
    UInt16 lrr;
    
    find_arg_PNO(pnoP, &arg1);
    PNO(dbNo) = find_integer(pnoP)-1;
    find_arg_PNO(pnoP, &arg3);
    db=getDatabasePtr(pnoP);
    dbr=db->dm;
    dbr = (DmOpenRef) ByteSwap32(dbr);
    chkDbOpen(pnoP, db);
#endif

#ifdef __MC68K__
  res=db->LastDbRecordRead+1;
#else
  res = db -> LastDbRecordRead;
  res = ByteSwap16(res);
  ++res;
#endif

  if (res>=DmNumRecords(dbr))
  {
     while(1)
     {
#ifdef __MC68K__
       find_arg_5();
       if(arg5==null_ptr) break;
#else
        Arg arg5;
        find_arg_PNO(pnoP, &arg5);
        if (arg5 . dataElem == NULL) break;
#endif
     }
     res=1;
     goto getOut3;
  }

  recHand=DmGetRecord(dbr,res);
#ifdef __MC68K__
  readDbFields(db,recHand,&arg3,arg3_occ1,arg3_occ2,arg3_occ3);
#else
  readDbFields(pnoP, db,recHand,&(arg3.dataElem),arg3.occ1,arg3.occ2,arg3.occ3);
#endif
  
  DmReleaseRecord(dbr,res,false);
//dbug("record released");
  res=0;
#ifdef __MC68K__
  db->LastDbRecordRead+=1;   //this stmt need to be moved
#else
    lrr = db -> LastDbRecordRead;
    lrr = ByteSwap16(lrr);
    ++lrr;
    db -> LastDbRecordRead = ByteSwap16(lrr);
#endif
getOut3:
  setDbRes(res);
}

#ifndef __MC68K__
/********************************************************************************************/
/**
    skipArgs
    Skips remaining args */
void skipArgs(PNOBlock *pnoP)
{
    Arg arg;
    do
    {
        find_arg_PNO(pnoP, &arg);
    } while (arg.dataElem != NULL);
}
#endif

/********************************************************************************************/
#ifdef __MC68K__
void verb_dbreadprev()
#else
void verb_dbreadprev(PNOBlock *pnoP)
#endif
{
  struct dbType *db;
  VoidHand recHand;
  VoidPtr  recPtr;
  DmOpenRef dbr;
  Int16 err;
  Int16 res;
#ifdef __MC68K__
  dbfind_arg(3);
  db=getDatabasePtr();
  dbr=db->dm;
  chkDbOpen(db);
#else
    Arg arg1, arg3;
    double d;
    UInt16 lrr;
    
    find_arg_PNO(pnoP, &arg1);
    PNO(dbNo) = find_integer(pnoP)-1;
    find_arg_PNO(pnoP, &arg3);
    db=getDatabasePtr(pnoP);
    dbr=db->dm;
    dbr = (DmOpenRef) ByteSwap32(dbr);
    chkDbOpen(pnoP, db);
#endif
  
//StrPrintF(debug,"readnxt=%d dbcnt=%d lastrec=%u",res,DmNumRecords(dbr),db->LastDbRecordRead);
//SysFatalAlert(debug);
#ifdef __MC68K__
  if ((db->LastDbRecordRead==0)||(db->LastDbRecordRead==65535))  //65535 equiv to -1 in unsigned fld
#else
    lrr = db -> LastDbRecordRead;
    lrr = ByteSwap16(lrr);
    if ((lrr == 0) || (lrr == 65535))
#endif
  {
//dbug("skip params");
     //skip parameters
#ifdef __MC68K__
     while(1)
     {
       find_arg_5();
       if(arg5==null_ptr) break;
     }
#else
     skipArgs(pnoP);
#endif
     res=1;
     setDbRes(res);
     return;
  }
//dbug("found rec");
#ifdef __MC68K__  
  res=db->LastDbRecordRead-1;  //position to prev rec
#else
  lrr = db -> LastDbRecordRead;
  lrr = ByteSwap16(lrr);
  --lrr;
  res=lrr;
#endif
  recHand=DmGetRecord(dbr,res);
  
//dbug("reading rec flds");
#ifdef __MC68K__  
  readDbFields(db,recHand,&arg3,arg3_occ1,arg3_occ2,arg3_occ3);
#else
  readDbFields(pnoP, db, recHand, &(arg3.dataElem), arg3.occ1, arg3.occ2, arg3.occ3);
#endif

  //db->LastDbRecordRead=res;
  DmReleaseRecord(dbr,res,false);
//dbug("record released");
  res=0;
getOut3:
  setDbRes(res);

#ifdef __MC68K__
  db->LastDbRecordRead-=1;
#else
    db -> LastDbRecordRead = ByteSwap16(lrr);
#endif
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_dbinsert()
#else
void verb_dbinsert(PNOBlock *pnoP)    // EMP 
#endif
{
  struct dbType *db;
  SortRecordInfoType srtinfo;
  VoidHand recHand;
  VoidPtr  recPtr;
  UInt16 res;
  DmOpenRef dbr;
  Int16 err;
  Int16 kindInt;
  Int16 result;   //inserted 05282003
#ifdef __MC68K__
  dbfind_arg(3);  //1=result, 2=dbno,3=key
  db=getDatabasePtr();
  dbr=db->dm;
  chkDbOpen(db);
#else
    Arg arg1, arg3;
    double d;
    VoidPtr dbc;
    
    find_arg_PNO(pnoP, &arg1);
    PNO(dbNo) = find_integer(pnoP)-1;
    find_arg_PNO(pnoP, &arg3);
    db=getDatabasePtr(pnoP);
    dbr=db->dm;
    dbr = (DmOpenRef) ByteSwap32(dbr);
    chkDbOpen(pnoP, db);
#endif   
  kindInt=0;
#ifdef __MC68K__
  *((char*)(&kindInt))=arg3->kind;
  *((char*)(&kindInt)+1)=arg3->flags;
#else
    kindInt = ((arg3.dataElem -> kind) << 8) + arg3.dataElem -> flags;
#endif

#ifdef __MC68K__
  res=DmFindSortPosition(dbr, arg3_val, &srtinfo, database_compare, kindInt);
#else
  dbc = PNO(database_compare);
  dbc = (VoidPtr) ByteSwap32(dbc);
  res = DmFindSortPosition(dbr, arg3.val, &srtinfo, dbc, kindInt);
#endif

  res-=1;
  if (res>=DmNumRecords(dbr) )
  {
     goto OKtoAdd;
  }
  
  recHand=DmGetRecord(dbr,res);
  recPtr=MemHandleLock(recHand);

  
#ifdef __MC68K__
  if (keyCompare(arg3_val,recPtr,kindInt)==0)
#else
  if (keyCompare(arg3.val,recPtr,kindInt)==0)
#endif
  {
     MemHandleUnlock(recHand);
     DmReleaseRecord(dbr,res,false);
getOut7:                           //inserted 05282003
     setDbRes(1);  //rec already on file(or mem error)  //05282003
#ifdef __MC68K__
     while(1)     /*skip rest of args */
     {
        find_arg_5();
        if (arg5==null_ptr) break;
     }
#else
    skipArgs(pnoP);
#endif
     
     return;
  } 
  MemHandleUnlock(recHand);
  DmReleaseRecord(dbr,res,false);
OKtoAdd:
  res+=1;
  
#ifndef __MC68K__
  // EMP pace doesn't handle this
  // EMP now it does 3/31/04 res = ByteSwap16(res);
#endif
  recHand=DmNewRecord(dbr,&res,1); //1/9/2000 //just get 1 bytes & it will resize later
#ifndef __MC68K__
  // EMP pace doesn't handle this
  // EMP now it does 3/31/04 res = ByteSwap16(res);
#endif
  if(recHand==0)                   //inserted 05282003
  {                                //inserted 05282003
          goto getOut7;//out-of-mem//inserted 05282003
  }                                //inserted 05282003
//StrPrintF(debug,"in dbinsert size=%lu",MemHandleSize(recHand));
//SysFatalAlert(debug);

  
#ifdef __MC68K__
     result=writeDbFields(db,&recHand,arg3_val,(Int16)kindInt,'a',res);   //mod 05282003
#else
     result=writeDbFields(pnoP, db,&recHand,arg3.val,(Int16)kindInt,'a',res);   //mod 05282003
#endif
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
#ifdef __MC68K__
void verb_dbdelete()
#else
void verb_dbdelete(PNOBlock *pnoP)
#endif
{
  struct dbType *db;
  SortRecordInfoType srtinfo;
  VoidHand recHand;
  VoidPtr  recPtr;
  Int16 res;
  UInt rec;
  Int16 kindInt;
  DmOpenRef dbr;
  Int16 *err;
  
#ifdef __MC68K__
  dbfind_arg(3);  //1=result, 2=dbno,3=key
  db=getDatabasePtr();
  dbr=db->dm;
  chkDbOpen(db);
#else
    Arg arg1, arg3;
    double d;
    VoidPtr dbc;
    
    find_arg_PNO(pnoP, &arg1);
    PNO(dbNo) = find_integer(pnoP)-1;
    find_arg_PNO(pnoP, &arg3);
    db=getDatabasePtr(pnoP);
    dbr=db->dm;
    dbr = (DmOpenRef) ByteSwap32(dbr);
    chkDbOpen(pnoP, db);
#endif   
  
  if(DmNumRecords(dbr) ==0)
  {
     res=1;
     goto getOut5;
  }

  kindInt=0;
#ifdef __MC68K__
  *((char*)(&kindInt))=arg3->kind;
  *((char*)(&kindInt)+1)=arg3->flags;
#else
    kindInt = ((arg3.dataElem -> kind) << 8) + arg3.dataElem -> flags;
#endif

#ifdef __MC68K__
  rec=DmFindSortPosition(dbr, arg3_val, &srtinfo, database_compare, kindInt);
#else
  dbc = PNO(database_compare);
  dbc = (VoidPtr) ByteSwap32(dbc);
  rec=DmFindSortPosition(dbr, arg3.val, &srtinfo, dbc, kindInt);
#endif
  
  if (rec > DmNumRecords(dbr) )
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

#ifdef __MC68K__
  if (keyCompare(arg3_val,recPtr,kindInt)==0)
#else
  if (keyCompare(arg3.val,recPtr,kindInt)==0)
#endif
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
#ifdef __MC68K__
void verb_dbupdate()
#else
void verb_dbupdate(PNOBlock *pnoP)   // EMP
#endif
{
  struct dbType *db;
  SortRecordInfoType srtinfo;
  Int16 kindInt;
  VoidHand recHand;
  VoidPtr  recPtr;
  UInt16 res;
  DmOpenRef dbr;
  Int16 err;
  Int16 result;                    //05282003
#ifdef __MC68K__ 
  dbfind_arg(3);  //1=result, 2=dbno,3=key
  db=getDatabasePtr();
  dbr=db->dm;
  chkDbOpen(db);
#else 
    Arg arg1, arg3;
    VoidPtr dbc;
    
    find_arg_PNO(pnoP, &arg1);
    PNO(dbNo) = find_integer(pnoP)-1;
    find_arg_PNO(pnoP, &arg3);
    db=getDatabasePtr(pnoP);
    dbr=db->dm;
    dbr = (DmOpenRef) ByteSwap32(dbr);
    chkDbOpen(pnoP, db);
#endif


#ifdef __MC68K__
  kindInt=0;
  *((char*)(&kindInt))=arg3->kind;
  *((char*)(&kindInt)+1)=arg3->flags;
#else
    kindInt = ((arg3.dataElem -> kind) << 8) + arg3.dataElem -> flags;
#endif


#ifdef __MC68K__
  res=DmFindSortPosition(dbr,arg3_val,&srtinfo,database_compare,kindInt);
#else
  dbc = PNO(database_compare);
  dbc = (VoidPtr) ByteSwap32(dbc);
  res = DmFindSortPosition(dbr, arg3.val, &srtinfo, dbc, kindInt);
#endif

   if(res==0)                             //05192003 added (key lower than any record on file)
   {
    res=1;
#ifdef __MC68K__
    while(1)    //skip rest of args 
     {
        find_arg_5();
        if (arg5==null_ptr) break;
     }
#else
    skipArgs(pnoP);
#endif
    goto getOut2;
  }
  
 
  res-=1;
//StrPrintF(debug,"getting rec2=%d key=%s",res,arg3_val);
//SysFatalAlert(debug);
  recHand=DmGetRecord(dbr,res);
  recPtr=MemHandleLock(recHand);

#ifdef __MC68K__  
  if (keyCompare(arg3_val,recPtr,kindInt)==0)
#else
  if (keyCompare(arg3.val,recPtr,kindInt)==0)
#endif
  {
//dbug("matched");
     MemHandleUnlock(recHand);
//dbug("going to write");
#ifdef __MC68K__  
     result=writeDbFields(db,&recHand,arg3_val,kindInt,'u',res);  //mod 05282003
#else
     result=writeDbFields(pnoP, db,&recHand,arg3.val,kindInt,'u',res);  //mod 05282003
#endif
     if(result==1) goto getOut8;  //out of mem      05282003
     
//dbug("back from write");
#ifdef __MC68K__  
     db->LastDbRecordRead=res;
#else
     db -> LastDbRecordRead = ByteSwap16(res);
#endif
   
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
#ifdef __MC68K__
    while(1)     /*skip rest of args */
     {
        find_arg_5();
        if (arg5==null_ptr) break;
     }
#else
    skipArgs(pnoP);
#endif
  }
getOut2:
  setDbRes(res);
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_dbread()
#else
void verb_dbread(PNOBlock *pnoP)    // EMP
#endif
{
  struct dbType *db;
  SortRecordInfoType srtinfo;
  Int16 kindInt;
  VoidHand recHand;
  VoidPtr  recPtr;
  UInt16 tempRes;
  UInt16 res;
  DmOpenRef dbr;
  Int16 err;
#ifdef __MC68K__
  dbfind_arg(3);  //1=result, 2=dbno,3=key
  db=getDatabasePtr();
  dbr=db->dm;
  chkDbOpen(db);
#else
    Arg arg1, arg3;
    double d;
    VoidPtr dbc;
    
    find_arg_PNO(pnoP, &arg1);
    PNO(dbNo) = find_integer(pnoP)-1;
    find_arg_PNO(pnoP, &arg3);
    db=getDatabasePtr(pnoP);
    dbr=db->dm;
    dbr = (DmOpenRef) ByteSwap32(dbr);
    chkDbOpen(pnoP, db);
#endif  
   
  kindInt=0;
  
  
#ifdef __MC68K__
  *((char*)(&kindInt))=arg3->kind;
  *((char*)(&kindInt)+1)=arg3->flags;
#else
    kindInt = ((arg3.dataElem -> kind) << 8) + arg3.dataElem -> flags;
#endif

#ifdef __MC68K__
  res=DmFindSortPosition(dbr, arg3_val, &srtinfo, database_compare, kindInt);
#else
  dbc = PNO(database_compare);
  dbc = (VoidPtr) ByteSwap32(dbc);
  res=DmFindSortPosition(dbr, arg3.val, &srtinfo, dbc, kindInt);
#endif
  
//StrPrintF(debug,"res=%d",res);
//SysFatalAlert(debug);

  if (res > DmNumRecords(dbr))
  {
    //skip parameters
     res=1;
skipParams:
#ifdef __MC68K__

     while(1)
     {
       find_arg_5();
       if(arg5==null_ptr) break;
     }
#else
    skipArgs(pnoP);
#endif   
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

#ifdef __MC68K__
  if (keyCompare(arg3_val,recPtr,kindInt)==0)
#else
  if (keyCompare(arg3.val, recPtr, kindInt)==0)
#endif
  {
     MemHandleUnlock(recHand);
     
#ifdef __MC68K__
     readDbFields(db,recHand,&arg3,arg3_occ1,arg3_occ2,arg3_occ3);
     db->LastDbRecordRead=res;
#else
     readDbFields(pnoP, db, recHand, &(arg3.dataElem), arg3.occ1, arg3.occ2, arg3.occ3);
     db -> LastDbRecordRead = ByteSwap16(res); 
#endif
     res=0;
  }
  else
  {
      MemHandleUnlock(recHand);
      DmReleaseRecord(dbr, tempRes, false);
      res+=1;
readNextHigher:
      if(res==DmNumRecords(dbr)) 
      {
          res=1;
          goto skipParams;
      }
      
      tempRes=res;
      recHand=DmGetRecord(dbr,res);
      
#ifdef __MC68K__
      readDbFields(db,recHand,&arg3,arg3_occ1,arg3_occ2,arg3_occ3);
      db->LastDbRecordRead=res;
#else
     readDbFields(pnoP, db, recHand, &(arg3.dataElem), arg3.occ1, arg3.occ2, arg3.occ3);
     db -> LastDbRecordRead = ByteSwap16(res); 
#endif
      res=2;    //2 says returning next higher record
      
  }    

  DmReleaseRecord(dbr,tempRes,false);
getOut2:
  setDbRes(res);
  
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_dbfind()
#else
void verb_dbfind(PNOBlock *pnoP)
#endif
{
  struct dbType *db;
  SortRecordInfoType srtinfo;
  Int16 kindInt;
  VoidHand recHand;
  VoidPtr  recPtr;
  UInt16 rec;
  UInt res;
  DmOpenRef dbr;
  Int16 err;

#ifdef __MC68K__
  dbfind_arg(3);  //1=result, 2=dbno,3=key
  db=getDatabasePtr();
  dbr=db->dm;
  chkDbOpen(db);
#else
    Arg arg1, arg3;
    double d;
    VoidPtr dbc;
    
    find_arg_PNO(pnoP, &arg1);
    PNO(dbNo) = find_integer(pnoP)-1;
    find_arg_PNO(pnoP, &arg3);
    db=getDatabasePtr(pnoP);
    dbr=db->dm;
    dbr = (DmOpenRef) ByteSwap32(dbr);
    chkDbOpen(pnoP, db);
#endif  
  
#ifdef __MC68K__
  *((char*)(&kindInt))=arg3->kind;
  *((char*)(&kindInt)+1)=arg3->flags;
#else
    kindInt = ((arg3.dataElem -> kind) << 8) + arg3.dataElem -> flags;
#endif

#ifdef __MC68K__
  rec=DmFindSortPosition(dbr,arg3_val,&srtinfo,database_compare,kindInt);
#else
  dbc = PNO(database_compare);
  dbc = (VoidPtr) ByteSwap32(dbc);
  rec=DmFindSortPosition(dbr, arg3.val, &srtinfo, dbc, kindInt);
#endif
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
  
#ifdef __MC68K__
  if(keyCompare(arg3_val,recPtr,kindInt)==0) res=0;
#else
  if(keyCompare(arg3.val,recPtr,kindInt)==0) res=0;
#endif
  else  res=1;
  
  MemHandleUnlock(recHand);
  DmReleaseRecord(dbr,rec,false);
getOut:
  setDbRes(res);
   
}
/********************************************************************************************/

#ifdef __MC68K__

void dbfind_arg(int n)
{
    find_arg_1();
    PNO(dbNo)=find_integer()-1;
    if(n>2) find_arg_3();
    if(n>3) find_arg_4();
    if(n>4) find_arg_5();
    if(n>5) find_arg_6();
   
}

/********************************************************************************************/
void verb_dbcreatedatabasefromresource()	//03.24.02 GH
{
	Err res;
	Int16 resID;
	VoidHand imageHandle;
   
	resID= long_integ_value(arg2,(double*)arg2_val);
	imageHandle = DmGetResource(*(DmResType *) arg1_val, (DmResID) resID);
	if(imageHandle==0) {setSerErr(DmGetLastErr());return;}
   
	res = DmCreateDatabaseFromImage(MemHandleLock(imageHandle));
	MemHandleUnlock(imageHandle);
	DmReleaseResource(imageHandle);

  	setSerErr(res);
}
#endif

/**
    EMP
    A series of more space-efficient routines to read and write databases
    18 Oct 2003
*/
#ifndef __MC68K__
typedef void(IterateFunction)(PNOBlock *pnoP, Arg *theArg, void *userData);

void forArgument(PNOBlock *pnoP, Arg *theArg, IterateFunction *func, void *userData)
{
    UInt16 ii, jj, kk;
    UInt16 mv1, mv2, mv3;

    mv1 = theArg -> dataElem -> max_no_values1;
    mv2 = theArg -> dataElem -> max_no_values2;
    mv3 = theArg -> dataElem -> max_no_values3;

    mv1 = ByteSwap16(mv1);
    mv2 = ByteSwap16(mv2);
    mv3 = ByteSwap16(mv3);
    
    if( (mv3 > 1) && (theArg -> sde3==0)) 
    {
        if( (mv2 > 1) && (theArg -> sde2==0))
        {
            if( (mv1 > 1) && (theArg -> sde1==0))
            { 
                for(ii=0;ii<mv1;++ii)
                {
                    for(jj=0;jj<mv2;++jj)
                    {
                        for(kk=0;kk<mv3;++kk)
                        {
                            theArg -> occ1=ii;
                            theArg -> occ2=jj;
                            theArg -> occ3=kk;
                            (*func)(pnoP, theArg, userData);
                        }
                    }
                }

            }
            else
            {
                for(jj=0;jj<mv2;++jj)
                {
                    for(kk=0;kk<mv3;++kk)
                    {
                        theArg -> occ2=jj;
                        theArg -> occ3=kk;
                        (*func)(pnoP, theArg, userData);
                    }
                }
            }
        }
        else
        {
            for(kk=0;kk<mv1;++kk)
            {
                theArg -> occ3=kk;
                (*func)(pnoP, theArg, userData);
            }
        }
    }
    else
    {
        if( (mv2 > 1) && (theArg -> sde2==0))
        {
            if( (mv1 > 1) && (theArg -> sde1==0))
            { 
                for(ii=0;ii<mv1;++ii)
                {
                    for(jj=0;jj<mv2;++jj)
                    {
                        theArg -> occ1=ii;
                        theArg -> occ2=jj;
                        (*func)(pnoP, theArg, userData);
                    }
                }
            }
            else
            {
                for(jj=0;jj<mv2;++jj)
                {
                    theArg -> occ2=jj;
                    (*func)(pnoP, theArg, userData);
                }
            }
        } 
        else
        {
            if( (mv1 > 1) && (theArg -> sde1==0))
            { 
                for(ii=0;ii<mv1;++ii)
                {
                    theArg -> occ1=ii;
                    (*func)(pnoP, theArg, userData);
                }
            }
            else
            {
                //arg5_val OK because all levels of subscripting there
                (*func)(pnoP, theArg, userData);
            }
        }
    } 
}


#endif

/********************************************************************************************/
/**
    EMP common fill arg for space efficiency
  */
#ifndef __MC68K__

/* Get a numeric value at recPtr, stuff it into double, and return length */
UInt16 getNumericValueAt(char *recPtr, double *dbl, char flags)
{
    UInt16 theLen;
    Int16 theShort;
    Int32 theInteger;
    double theData;
    union {float f; UInt32 i;} x;
    
    if(flags&0x80)   //integer
    {
        theLen=4; 
        dbGetSome((char*)(recPtr),theLen,&theInteger);
        theInteger = ByteSwap32(theInteger);
        theData=theInteger;
    }
    else if(flags&0x40)  //float/double
    {
        theLen=8; 
        dbGetSome((char*)(recPtr),theLen,&theData);
        theData = SwapDouble(theData);
    } 
    else if(flags&0x20)   //single float
    {
        theLen = 4;
        dbGetSome((char*)(recPtr),theLen,&(x.i));
        x.i = ByteSwap32(x.i);
        theData = x.f;
    }
    else if(flags&0x10)   //2-byte integer
    {
        theLen=2;
        dbGetSome((char*)(recPtr),theLen,&theShort);
        theShort = ByteSwap16(theShort);
        theData = theShort;
    }
    *dbl = theData;
    return theLen;
}


/* Fill an arg based on its type from recPtr and return the number of bytes */
UInt16 fillArgFromDb(PNOBlock *pnoP, Arg *arg5, char *recPtr)
{
    UInt16 theLen;
    double theData;
    char b[2];
    
    if (arg5 -> dataElem -> kind== 's')
    {
        if(arg5-> dataElem -> flags&0x80)
        {
            b[0] =*((char*)recPtr);
            b[1] =0x00;
            misc_stostr(pnoP, &(arg5 -> dataElem), arg5 -> occ1, arg5 -> occ2, arg5 -> occ3, b);
            theLen = 1;
        }
        else
        {     
            misc_stostr(pnoP, &(arg5 -> dataElem), arg5 -> occ1, arg5 -> occ2, arg5 -> occ3, (char*)recPtr);
            theLen = strlen((char*)(recPtr))+1;
        }
    }
    else
    {
        theLen = getNumericValueAt(recPtr, &theData, arg5 -> dataElem -> flags);
        theData = SwapDouble(theData);
        misc_stodbl(pnoP, arg5 -> dataElem, arg5 -> occ1, arg5 -> occ2, arg5 -> occ3, &theData);
    }
    return theLen;
}
#endif

/********************************************************************************************/
#ifdef __MC68K__
// EMP remove internal MC68K at leisure, had to change all of this
#ifdef __MC68K__
void readOneDbField(struct dbType* db,VoidPtr recPtr,UInt *theOffset)
#else
void readOneDbField(PNOBlock *pnoP, Arg *arg5, struct dbType * db,VoidPtr recPtr,UInt *theOffset)
#endif
{
    UInt16 offset=*theOffset;
    char b[2];
    UInt16 theLen;
    Int16 theShort;
    Int32 theInteger;
    float theSingle;
    double theData =37;   
    char wk[50];
    
#ifdef __MC68K__  
    if (arg5->kind== 's')
#else
    if (arg5 -> dataElem -> kind== 's')
#endif
    {
#ifdef __MC68K__  
        if(arg5->flags&0x80)
#else
        if(arg5-> dataElem -> flags&0x80)
#endif
        {
            b[0] =*((char*)recPtr+offset);
            b[1] =0x00;
#ifdef __MC68K__
            misc_stostr5(b);
#else
            misc_stostr(pnoP, &(arg5 -> dataElem), arg5 -> occ1, arg5 -> occ2, arg5 -> occ3, b);
#endif
            offset+=1;
        }
        else
        {     
#ifdef __MC68K__
            misc_stostr5((char*)recPtr+offset);
            offset+=StrLen((char*)(recPtr)+offset)+1;
#else
            misc_stostr(pnoP, &(arg5 -> dataElem), arg5 -> occ1, arg5 -> occ2, arg5 -> occ3, (char*)recPtr+offset);
            offset+=strlen((char*)(recPtr)+offset)+1;
#endif
        }
    }
    else
    {
#ifdef __MC68K__
        if(arg5->flags&0x80)   //integer
#else
        if(arg5 -> dataElem -> flags&0x80)   //integer
#endif
        {
            theLen=4; 
            dbGetSome((char*)(recPtr)+offset,theLen,&theInteger);
#ifndef __MC68K__
            theInteger = ByteSwap32(theInteger);
#endif
            theData=theInteger;
            goto readIt;
        }
#ifdef __MC68K__
        if(arg5->flags&0x40)  //float/double
#else
        else if(arg5 -> dataElem -> flags&0x40)  //float/double
#endif
        {
            theLen=8; 
            dbGetSome((char*)(recPtr)+offset,theLen,&theData);
#ifndef __MC68K__
            theData = SwapDouble(theData);
#endif
            goto readIt;
        } 
#ifdef __MC68K__
        if(arg5->flags&0x20)   //single float
#else
        else if(arg5-> dataElem -> flags&0x20)   //single float
#endif
        {
#ifdef __MC68K__
            theLen=4; 
            dbGetSome((char*)(recPtr)+offset,theLen,&theSingle);
#else
            union {float f; UInt32 i;} x;
            theLen = 4;
            dbGetSome((char*)(recPtr)+offset,theLen,&(x.i));
            x.i = ByteSwap32(x.i);
            theSingle = x.f;
#endif
            theData=theSingle;
            goto readIt;

        }
#ifdef __MC68K__
        if(arg5->flags&0x10)   //2-byte integer
#else
        else if(arg5-> dataElem -> flags&0x10)   //2-byte integer
#endif
        {
            theLen=2;
            dbGetSome((char*)(recPtr)+offset,theLen,&theShort);
#ifndef __MC68K__
            theShort = ByteSwap16(theShort);
#endif
            theData=theShort;
            goto readIt;
        }
readIt:  
      
#ifdef __MC68K__
        misc_stodbl5(&theData);
#else
        theData = SwapDouble(theData);
        misc_stodbl(pnoP, arg5 -> dataElem, arg5 -> occ1, arg5 -> occ2, arg5 -> occ3, &theData);
#endif
        offset+=theLen;
    }
    *theOffset=offset;
      
}
#else
void readOneDbField(PNOBlock *pnoP, Arg *arg5, struct dbType * db,VoidPtr recPtr,UInt *theOffset)
{
    UInt16 offset=*theOffset;
    char b[2];
    UInt16 theLen;
    Int16 theShort;
    Int32 theInteger;
    float theSingle;
    double theData =37;   
    char wk[50];
    
    theLen = fillArgFromDb(pnoP, arg5, offset + (char *)recPtr);
    
    offset+=theLen;
    *theOffset=offset;   
}
#endif

#ifndef __MC68K__
/********************************************************************************************/
/* EMP modified to use commmon argument traversal code */

void readOneDbFieldGlue(PNOBlock *pnoP, Arg *arg5, void *data)
{
    struct
    {
        struct dbType *db;
        VoidPtr recPtr;
        UInt16 *theOffset;
    } *pass;
    
    pass = data;
        
    readOneDbField(pnoP, arg5, pass -> db ,pass -> recPtr, pass -> theOffset);
}

void readOneDbArgument(PNOBlock *pnoP, Arg *arg5, struct dbType * db,VoidPtr recPtr,UInt16 *theOffset)
{
    struct
    {
        struct dbType *db;
        VoidPtr recPtr;
        UInt16 *theOffset;
    } pass;
    
    pass.db = db;
    pass.recPtr = recPtr;
    pass.theOffset = theOffset;
    forArgument(pnoP, arg5, /*__ARMlet_Take_Func_Addr__*/(readOneDbFieldGlue), (void *) &pass);
}
#endif

#ifdef __MC68K__
/********************************************************************************************/
void readOneDbArgument(struct dbType * db,VoidPtr recPtr,UInt16 *theOffset)
{
   UInt16 ii,jj,kk;

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
#endif



/********************************************************************************************/
#ifdef __MC68K__
void readDbFields(struct dbType * db,VoidHand recHand,
                  struct dataelem* *keyarg,unsigned int keysub1,
                  unsigned int keysub2,unsigned int keysub3)
#else
void readDbFields(PNOBlock *pnoP, struct dbType * db,VoidHand recHand,
                  struct dataelem* *keyarg,UInt16 keysub1,
                  UInt16 keysub2,UInt16 keysub3)
#endif
{
  char b[2];
  UInt32 theLen;
  Int16 theShort;
  UInt32 theInteger;
  float theSingle;
  double theData;   
  UInt16 offset;
  VoidPtr recPtr;
  char wk[50];
#ifndef __MC68K__
  Arg key;
  key.dataElem = *keyarg;
  key.occ1 = keysub1;
  key.occ2 = keysub2;
  key.occ3 = keysub3;
  
#endif  

  recPtr=MemHandleLock(recHand);

#ifndef __MC68K__

    theLen = fillArgFromDb(pnoP, &key, (char *)recPtr);
    *keyarg = key.dataElem;

#else
// EMP PNO code no longer needed, remove at leisure

  if((*keyarg)->kind=='s')
  {
     if( (*keyarg)->flags&0x80) 
     {
          theLen=1;
          b[0] =*((char*)recPtr);
          b[1] =0x00;
#ifdef __MC68K__
          misc_stostr(keyarg,keysub1,keysub2,keysub3,b);
#else
          misc_stostr(pnoP, keyarg,keysub1,keysub2,keysub3,b);
#endif
     }
     else 
     {
#ifdef __MC68K__
       misc_stostr(keyarg,keysub1,keysub2,keysub3,(char*)recPtr);
       theLen=StrLen((char*)recPtr)+1;
#else
       misc_stostr(pnoP, keyarg,keysub1,keysub2,keysub3,(char*)recPtr);
       theLen=strlen((char*)recPtr)+1;
#endif
     } 
  }
  else
  {
     
         if( (*keyarg)->flags& 0x80) //long
         {  theLen=4; 
           dbGetSome((char*)(recPtr),theLen,&theInteger);
#ifdef __MC68K__
           theData=theInteger;
#else
           theData=ByteSwap32(theInteger);
#endif
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
#ifdef __MC68K__
           theLen=4; 
           dbGetSome((char*)(recPtr),theLen,&theSingle);
           theData=theSingle;
#else
            union {float f; Int32 i;} x;
            theLen = 4;
            dbGetSome((char*)(recPtr),theLen,&(x.i));
            x.i = ByteSwap32(x.i);
            theData = x.f;
#endif
           goto keySet;
         }
         if((*keyarg)->flags& 0x10)  //int      
         {
           theLen=2;
           dbGetSome((char*)(recPtr),theLen,&theShort);
#ifdef __MC68K__
           theData=theShort;
#else
            theData = ByteSwap16(theShort);
#endif
           goto keySet;
         }
keySet: 
     
storeKeyNum:
#ifdef __MC68K__
      misc_stodbl( *keyarg, keysub1,keysub2,keysub3,&theData);
#else
      theData = SwapDouble(theData);
      misc_stodbl(pnoP, *keyarg, keysub1,keysub2,keysub3,&theData);
#endif
   }
#endif

   offset=theLen;

   while(1)
   {
#ifdef __MC68K__
        find_arg_5();
        if (arg5==null_ptr) break;
        readOneDbArgument(db,recPtr,&offset);
#else
        Arg arg5;
        find_arg_PNO(pnoP, &arg5);
        if (arg5.dataElem == NULL) break;
        readOneDbArgument(pnoP, &arg5, db,recPtr,&offset);
#endif
   }
   MemHandleUnlock(recHand);
}

/********************************************************************************************/
#ifdef __MC68K__
Int16 write_one_dbField(struct dbType *db,
                    VoidHand * recHand,
                     UInt16 index ,ULong *theOffset)
#else
Int16 write_one_dbField(PNOBlock *pnoP, Arg *arg5, struct dbType *db,   // EMP
                    VoidHand * recHand,
                     UInt16 index ,ULong *theOffset)
#endif
{
  ULong offset=*theOffset;
  double temp;
  Int16 err;
  
  VoidPtr ptr;
  UInt16 theLen;
  Int16 theShort;
  Int32 theInteger;
  float theSingle;
  void *theData;
  Int16 klm;
  double z;
  double wkdbl;
  DmOpenRef dbr = db -> dm;
  
  char nullbyte=0x00;

#ifndef __MC68K__
  dbr = (DmOpenRef) ByteSwap32(dbr);
#endif

#ifdef __MC68K__
           if (arg5->kind == 's')
          {
            if(arg5->flags&0x80)
#else
           if (arg5->dataElem -> kind == 's')
           {
            if(arg5-> dataElem -> flags&0x80)
#endif
            {
               if(MemHandleSize(*recHand)<(offset+1))   //08142002
               {
                 *recHand=DmResizeRecord(dbr,index,
                       (ULong)(offset+1));
                 if(*recHand==0) return(1);     //inserted 05282003      
               }
               ptr=MemHandleLock(*recHand); 
               
#ifdef __MC68K__
               DmWrite(ptr,offset,((char*)(arg5_val)),1);
#else
               DmWrite(ptr,offset,((char*)(arg5 -> val)),1);
#endif              
               offset+=1;
            }
            else
            {
               //07312002*recHand=DmResizeRecord(db->dm,index,
               //07312002        (ULong)(MemHandleSize(*recHand)+StrLen(arg5_val)+1));
#ifdef __MC68K__
              if(MemHandleSize(*recHand)<(offset+StrLen(arg5_val)+1))   //08142002
#else
              if(MemHandleSize(*recHand)<(offset+strlen(arg5 -> val)+1))   //08142002
#endif
               {
#ifdef __MC68K__
                   *recHand=DmResizeRecord(dbr,index,
                       (ULong)(offset+StrLen(arg5_val)+1));
#else
                   *recHand=DmResizeRecord(dbr,index,
                       (ULong)(offset+strlen(arg5 -> val)+1));
#endif
                   if(*recHand==0) return(1);     //inserted 05282003    
               }
               ptr=MemHandleLock(*recHand);
//StrPrintF(debug,"new lenmgth=%d",MemPtrSize(ptr));
//SysFatalAlert(debug);
      
//StrPrintF(debug,"copying string reclen=%d len=%d  rec=%s len=%d x=%x %x",MemHandleSize(*recHand)-StrLen(arg5_val)-1,StrLen(arg5_val),ptr,StrLen(ptr),*((char*)ptr+1),*((char*)ptr+2));
//SysFatalAlert(debug);

#ifdef __MC68K__
               err=DmStrCopy(ptr,offset,arg5_val);
#else
               err=DmStrCopy(ptr,offset,arg5 -> val);
#endif
//StrPrintF(debug,"err after StrCopy=%d",err);
//SysFatalAlert(debug);
               
               //06102002offset+=StrLen(arg5_val)+1;
               //07312002offset+=StrLen(arg5_val);             //06102002  to elim double nulls following string
#ifdef __MC68K__
               offset+=StrLen(arg5_val)+1;         //07312002            
#else
               offset+=strlen(arg5 -> val)+1;         //07312002            
#endif
            }
          }
          else
          {
#ifdef __MC68K__
            char flags = arg5 -> flags;
#else
            char flags = arg5 -> dataElem -> flags;
#endif
            if(flags&0x80)   //integer
            { 

               theLen=4; 
#ifdef __MC68K__
               wkdbl=*((double*)arg5_val);  
#else
               wkdbl= ReadUnaligned64(arg5 -> val); 
#endif
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
#ifndef __MC68K__
                theInteger = ByteSwap32(theInteger);
#endif
               theData=&theInteger;
//StrPrintF(debug,"write integer =%lu",theInteger);
//SysFatalAlert(debug);
               goto writeIt;
            }
            if(flags&0x40)  //float/double
            {
               theLen=8; 
#ifdef __MC68K__
               theData=(double*)arg5_val;
#else
               theData=(double*)arg5 -> val;
#endif 
               goto writeIt;
            } 
            if(flags&0x20)   //single float
            {
#ifndef __MC68K__
               union {float f; UInt32 i;} x;
#endif
               theLen=4; 
       
#ifdef __MC68K__
               theSingle=*((double*)arg5_val);
#else
               wkdbl = ReadUnaligned64(arg5 -> val);
               x.f = wkdbl;
               x.i = ByteSwap32(x.i);
               theSingle = x.f;
#endif
               theData=&theSingle;
               goto writeIt;
            }
            if(flags&0x10)   //2-byte integer
            {
              theLen=2;
#ifdef __MC68K__
              wkdbl=*((double*)arg5_val);  
#else
               wkdbl = ReadUnaligned64(arg5 -> val);
#endif
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
#ifndef __MC68K__
              theShort = ByteSwap16(theShort);
#endif
               
              theData=&theShort;
              goto writeIt;
            }
writeIt:
            //07312002*recHand=DmResizeRecord(db->dm,index,
           //07312002                       (ULong)(MemHandleSize(*recHand)+theLen));
            if(MemHandleSize(*recHand)<(offset+theLen))   //08142002
            {
                *recHand=DmResizeRecord(dbr,index,
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
#ifdef __MC68K__
Int16 writeOutOneDbArgument(struct dbType *db,
                    VoidHand * recHand,
                     UInt16 index ,UInt32 *theOffset)
{
    Int16 ii,jj,kk;
    Int16 res;               //inserted 05282003
    
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
#else
Int16 writeOutOneDbArgument(PNOBlock *pnoP, Arg *arg5, struct dbType *db,   // EMP
                    VoidHand * recHand,
                     UInt16 index ,UInt32 *theOffset)
{
    Int16 ii,jj,kk;
    Int16 res;               //inserted 05282003
    UInt16 mv1, mv2, mv3;
    
    mv1 = arg5 -> dataElem -> max_no_values1;
    mv1 = ByteSwap16(mv1);
    mv2 = arg5 -> dataElem -> max_no_values2;
    mv2 = ByteSwap16(mv2);
    mv3 = arg5 -> dataElem -> max_no_values3;
    mv3 = ByteSwap16(mv3);
        
    //writes out one passed argument which might be an array name which means write out several values
    if( (mv3 > 1) && (arg5 -> sde3==0)) 
    {
       if( (mv2 > 1) && (arg5 -> sde2==0))
       {
         if( (mv1 > 1) && (arg5 -> sde1==0))
         { 
            for(ii=0;ii<mv1;++ii)
            {
               for(jj=0;jj<mv2;++jj)
               {
                 for(kk=0;kk<mv3;++kk)
                 {
                     arg5 -> val = devel_address(pnoP, arg5 -> dataElem, ii,jj,kk);
                     res=write_one_dbField(pnoP, arg5, db, recHand,  index ,theOffset) ;   //modified 05282003
                     if(res!=0) return(1);      //outOfMemory   inserted 05282003
                 }
               }
             }
             
         }
         else
         {
                for(jj=0;jj<mv2;++jj)
                {
                  for(kk=0;kk<mv3;++kk)
                  {
                     arg5 -> val = devel_address(pnoP, arg5 -> dataElem, arg5 -> occ1 ,jj,kk);
                     res=write_one_dbField(pnoP, arg5, db, recHand, index ,theOffset) ;   //modified 05282003
                     if(res!=0) return(1);      //outOfMemory   inserted 05282003
                  }
                }
         }
                                         
       }
       else
       {
               for(kk=0;kk<mv1;++kk)
                {
                  
                     arg5 -> val = devel_address(pnoP, arg5 -> dataElem, arg5 -> occ1 ,arg5 -> occ2,kk);
                     res=write_one_dbField(pnoP, arg5, db, recHand,  index ,theOffset) ;   //mod 05282003
                     if(res!=0) return(1);      //outOfMemory   inserted 05282003
                }
       }
    }
    else
    {
       
       if( (mv2 > 1) && (arg5 -> sde2==0))
       {
         if( (mv1 > 1) && (arg5 -> sde1==0))
         { 
            for(ii=0;ii<mv1;++ii)
            {
               for(jj=0;jj<mv2;++jj)
               {
                     arg5 -> val = devel_address(pnoP, arg5 -> dataElem, ii,jj,arg5 ->occ3);
                     res=write_one_dbField(pnoP, arg5, db, recHand,  index ,theOffset) ;  //mod 05282003
                     if(res!=0) return(1);      //outOfMemory   inserted 05282003
               }
             }
             
         }
         else
         {
                for(jj=0;jj<mv2;++jj)
                {
                    arg5 -> val = devel_address(pnoP, arg5 -> dataElem, arg5 -> occ1 ,jj,arg5 -> occ3);
                    res= write_one_dbField(pnoP, arg5, db, recHand,   index ,theOffset) ;  //mod 05282003
                    if(res!=0) return(1);      //outOfMemory   inserted 05282003
                 }
         }
                                         
       } 
       else
       {
          if( (mv1 > 1) && (arg5 -> sde1==0))
         { 
            for(ii=0;ii<mv1;++ii)
            {
                     arg5 -> val = devel_address(pnoP, arg5 -> dataElem, ii, arg5 -> occ2, arg5 -> occ3);
                     res=write_one_dbField(pnoP, arg5, db, recHand,  index ,theOffset) ;  //mod 05282003
                     if(res!=0) return(1);      //outOfMemory   inserted 05282003
            }
             
         }
         else
         {
                 //arg5_val OK because all levels of subscripting there
                  res=write_one_dbField(pnoP, arg5, db, recHand, index ,theOffset) ;  //mod 05282003
                  if(res!=0) return(1);      //outOfMemory   inserted 05282003
          }
        }
    }
    return 0;      
}
#endif

/********************************************************************************************/
#ifdef __MC68K__
int writeDbFields(struct dbType *db,                                   //mod 05282003
                    VoidHand * recHand,char*key,int other,char addUpdt,
                     UInt16 index )
#else
Int16 writeDbFields(PNOBlock *pnoP, struct dbType *db,                   // EMP
                    VoidHand * recHand,char*key,Int16 other,char addUpdt,
                     UInt16 index )
#endif
{
  double temp;
  ULong offset;
  VoidPtr ptr;
  UInt16 theLen;
  Int16 theShort;
  Int32 theInteger;
  float theSingle;
  void *theData;
  ULong keylen;
  struct 
  {
     char kind;
     char flags;
  } theKind;
  char wk[50]; 
  Int16 ii,jj,kk;
  double wkdbl;
  double z;
  char nullbyte=0x00;
  Int16 res;                   //05282003
  DmOpenRef dbr = db -> dm;
#ifndef __MC68K__
  
  dbr = (DmOpenRef)ByteSwap32(dbr);
#endif


#ifdef __MC68K__   
  *((Int16*)&theKind)=other;
#else
  *((Int16*)&theKind)= ByteSwap16(other);
#endif
//StrPrintF(debug,"in writewflds kind=%c flags=%d",theKind.kind,theKind.flags);
//SysFatalAlert(debug);
  if( theKind.kind=='s')
  {
#ifdef __MC68K__   
        if( theKind.flags&0x80) keylen=1;
        else keylen= StrLen((char*)key)+1;
#else
        if( theKind.flags&0x80) keylen=1;
        else keylen= strlen((char*)key)+1;
#endif
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
    
      *recHand=DmResizeRecord(dbr,index,keylen+1);    //leave 1 extra null byte  //1/9/2001
      if(*recHand==0)   return(1);      //outOfMem       //inserted 05282003

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
#ifdef __MC68K__
       wkdbl=*((double*)key);  
#else
       wkdbl = ReadUnaligned64(key);
#endif
       theInteger=wkdbl;
#ifndef __MC68K__
       theInteger = ByteSwap32(theInteger);
#endif
       
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
#ifndef __MC68K__
        union {float f; UInt32 i;} x;
#endif
       theLen=4; 
      
#ifdef __MC68K__
       theSingle=*((double*)key);
#else
        wkdbl = ReadUnaligned64(key);
        x.f = wkdbl;
        x.i = ByteSwap16(x.i);
        theSingle = x.f;
#endif
       theData=&theSingle;
       goto writeKey;
     }
     if(theKind.flags&0x10)   //2-byte integer
     {
       theLen=2;

#ifdef __MC68K__
       wkdbl=*((double*)key);  
#else
       wkdbl = ReadUnaligned64(key);
#endif
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
#ifndef __MC68K__
        theShort = ByteSwap16(theShort);
#endif
               
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
#ifdef __MC68K__
    find_arg_5();
    if (arg5==null_ptr) break;
#else
    Arg arg5;
    find_arg_PNO(pnoP, &arg5);
    if (arg5.dataElem == NULL) break;
#endif
//StrPrintF(debug,"ready to copy offset=%d kind=%c",offset,arg5->kind);
//SysFatalAlert(debug);

#ifdef __MC68K__
     res=writeOutOneDbArgument(db, recHand,  index ,&offset);   //mod 05282003
#else
     res=writeOutOneDbArgument(pnoP, &arg5, db, recHand, index ,&offset);   //mod 05282003
#endif
     if(res==1) return(1);    //outOfMem  05282003
  }
  return(0);                             //05282003
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_dbgetnew()   //this is the new dbget which gets multiple fields
#else
void verb_dbgetnew(PNOBlock *pnoP)   //this is the new dbget which gets multiple fields
#endif
{
  struct dbType *db;
  VoidHand recHand;
  VoidPtr  recPtr;
  Int16 res;
  DmOpenRef dbr;
  char b[2];
  UInt32 theLen;
  double theData;
  float theSingle;
  
  UInt16 theShort;       //added 5.20.2000  
  
  UInt32 theInteger;    //added 5.20.2000
  UInt16 err = 0;
    MemHandle curHand;
    UInt16 lrr;
    UInt16 offset;
#ifdef __MC68K__
  dbfind_arg(2);  //1=errcode,2=db,5=singlevar
  db=getDatabasePtr();
  dbr=db->dm;
  chkDbOpen(db);
#else
    Arg arg1;
    Arg arg5;
    double d;
    
    find_arg_PNO(pnoP, &arg1);
    PNO(dbNo) = find_integer(pnoP)-1;
    
    db=getDatabasePtr(pnoP);
    dbr=db->dm;
    dbr = (DmOpenRef) ByteSwap32(dbr);
    chkDbOpen(pnoP, db);
#endif
      
//dbug("aaa");
    curHand = db -> curHand;
#ifndef __MC68K__
    curHand = (MemHandle) ByteSwap32(curHand);
#endif
    if(curHand ==0 )
    {
        setDbErr(err);
#ifdef __MC68K__
        while(1)
        {
            find_arg_5();
            if (arg5==NULL) break;   //skip all remaining flds
        }
#else
        skipArgs(pnoP);
#endif
        goto getOut3;
    }
    
    lrr = db -> LastDbRecordRead;
#ifndef __MC68K__
    lrr = ByteSwap16(lrr);
#endif

    curHand = DmGetRecord(dbr,lrr);
    recPtr=MemHandleLock(curHand);

#ifdef __MC68K__
    db->curHand = curHand;
#else
    db -> curHand = (MemHandle) ByteSwap32(curHand);
#endif
  while(1)
  {
#ifdef __MC68K__
     find_arg_5();
     if(arg5==null_ptr) break;
#else
     find_arg_PNO(pnoP, &arg5);
     if (arg5.dataElem == NULL) break;
#endif
     
     offset = db -> offset;
#ifndef __MC68K__
     offset = ByteSwap16(offset);
#endif

     if(offset >= (MemPtrSize(recPtr)))
     {
        setDbErr(err);
        while(1)
        {
#ifdef __MC68K__
            find_arg_5();
            if (arg5==null_ptr) break;   //skip all remaining flds
#else
            find_arg_PNO(pnoP, &arg5);
            if (arg5.dataElem==NULL) break;   //skip all remaining flds
#endif
        }
		SysFatalAlert("offset too big");
        goto getOut2;
     }
   
#ifdef __MC68K__
        readOneDbArgument(db, recPtr, &offset);
        db -> offset = offset;
#else
        readOneDbArgument(pnoP, &arg5, db, recPtr, &offset);
        db -> offset = ByteSwap16(offset);
#endif
  }   
  setDbOK();
getOut2:
  MemHandleUnlock(curHand);
  DmReleaseRecord(dbr,lrr,false);

getOut3:
   ;
}

#ifdef __MC68K__
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
#endif

/********************************************************************************************/
#ifdef __MC68K__
void verb_dbputnew()    //this is the new dbput which puts out multiple fields 
#else
void verb_dbputnew(PNOBlock *pnoP)    // EMP 
#endif
{
   UInt16 index;
   struct dbType *db;
   VoidHand recHand;
  VoidPtr  recPtr;
  UInt32 theLen;
  Int16 theShort;
  
  UInt32 offset;
  Int32 theInteger;
  float theSingle;
  void *theData;   
  Int16 res;
  DmOpenRef dbr;
  
 
  int err = 1;
  
#ifdef __MC68K__
  dbfind_arg(2);   //1=errcode,2=db,5=singlevar
  db=getDatabasePtr();
  dbr=db->dm;
  chkDbOpen(db);
#else
    Arg arg1;
    double d;
    VoidPtr dbc;
    UInt16 lrr;
    
    find_arg_PNO(pnoP, &arg1);
    PNO(dbNo) = find_integer(pnoP)-1;
    db=getDatabasePtr(pnoP);
    dbr=db->dm;
    dbr = (DmOpenRef) ByteSwap32(dbr);
    chkDbOpen(pnoP, db);
#endif   
  
  //if(db->curHand==0)      //deleted 04242003
#ifdef __MC68K__
  if((db->curHand==0) || (db->LastDbRecordRead<0) || (db->LastDbRecordRead>=(DmNumRecords(dbr)))) //inserterd 04242003
#else
  lrr = db -> LastDbRecordRead;
  lrr = ByteSwap16(lrr);
  if((db->curHand==0) || 
     (lrr == 65535) || (lrr>=(DmNumRecords(dbr)))) //inserterd 04242003
#endif
  {
       setDbErr(err);
       while(1)
       {
#ifdef __MC68K__
          find_arg_5();
          if(arg5==null_ptr) break;  //skip flds
#else
          skipArgs(pnoP);
#endif
       }
       goto getOut3;
  }

#ifdef __MC68K__
  recHand=DmGetRecord(dbr,db->LastDbRecordRead); //03242002
#else
  recHand=DmGetRecord(dbr,lrr); //03242002
#endif
 
  offset=db->offset;
#ifndef __MC68K__
  offset = ByteSwap16(offset);
#endif

  while(1)
  {
#ifdef __MC68K__
      find_arg_5();
      if (arg5==null_ptr) break;
      writeOutOneDbArgument(db, &(db->curHand), db->LastDbRecordRead ,&offset);
#else
      Arg arg5;
      find_arg_PNO(pnoP, &arg5);
      if (arg5.dataElem == NULL) break;
      recHand = db -> curHand;
      recHand = (MemHandle) ByteSwap32(recHand);
      writeOutOneDbArgument(pnoP, &arg5, db, &recHand, lrr ,&offset);
      db -> curHand = (MemHandle) ByteSwap32(recHand);
#endif
  }
#ifdef __MC68K__
  db->offset=offset;
#else
  db -> offset = ByteSwap16(offset);
#endif 
  
  setDbOK();
  
getOut2:
  
#ifdef __MC68K__
  DmReleaseRecord(dbr,db->LastDbRecordRead,true);
#else
  DmReleaseRecord(dbr,lrr,true);
#endif
getOut3:
    ;
}

#ifdef __MC68K__
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
#endif

/********************************************************************************************/
#ifdef __MC68K__
void chkDbOpen(struct dbType *db)
#else
void chkDbOpen(PNOBlock *pnoP, struct dbType *db)    // EMP
#endif
{
#ifdef __MC68K__
  if (db->openSw!='o') 
  {                                        //inserted 05212003
      SysFatalAlert("accessing an unopened database");
      ErrThrow(-1);                 //inserted 05212003
  }                                        //inserted 05212003    
#else
  if (db->openSw!='o') 
  {                                        //inserted 05212003
      SysFatalAlert("accessing an unopened database");
      GlueErrThrow(pnoP, -1);                 //inserted 05212003
  }                                        //inserted 05212003    
#endif
}

#ifdef __MC68K__
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
#endif


#ifdef __MC68K__
// EMP this will only be used from within 68K
/********************************************************************************************/
Int database_compare(void* a, void *b,Int oth,SortRecordInfoPtr j,SortRecordInfoPtr k, VoidHand appInfoH)
{
   int res;
   res=keyCompare((char*)a , (VoidPtr)b, oth);
   return(res);
}
#endif

/********************************************************************************************/
Int16 keyCompare(char* a, VoidPtr b, Int16 oth)
{   
   Int16 res;
   Int16 ci;
   Int32 cl;
   double cd;
   float cf;
   char wks[50];
   struct 
   {
     char kind;
     char flags;
   } theKind;  
//dbug("at compare");
//DoubleToStr(*((double*)a),wks);
//StrPrintF(debug, "at db comp a=%s b=%d ",wks,(int*)b);
//SysFatalAlert(debug);

#ifdef __MC68K__
  *((int*)&theKind)=oth;
#else
  *((Int16*)&theKind)=ByteSwap16(oth);
#endif



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
#ifndef __MC68K__
       double aval, bval;
       aval = ReadUnaligned64(a);
       getNumericValueAt((char *)b, &bval, theKind.flags);
       res = (aval < bval) ? -1 : ((aval > bval) ? 1 : 0);
       goto compOver;
#else
// PNO code here needless, remove at leisure
       if( theKind.flags& 0x80)  //integers (long -- 4-byte)
       {
#ifdef __MC68K__
         cl=*((double*)a);
         if ( cl < *((long*)b) ) res=-1;
         else
         {
           if   ( cl > *((long*)b) ) res=1;
           else res=0;
         }
#else
         Int32 clt = ReadUnaligned32(b);
         cl= aval;
         if ( cl < clt) res=-1;
         else
         {
           if   ( cl > clt) res=1;
           else res=0;
         }
#endif
         goto compOver;
       }
       if( theKind.flags&  0x40)     //numeric compare of two double args
       {
#ifdef __MC68K__
        if ( *((double*)a) < *((double*)b) ) res=-1;
        else
        {
           if   ( *((double*)a) > *((double*)b) ) res=1;
           else res=0;
        }
#else
        double bval = ReadUnaligned64(b);
        
        if (aval < bval) res=-1;
        else
        {
           if   (aval > bval) res=1;
           else res=0;
        }
#endif
         goto compOver;  
       }
       
       if(theKind.flags&  0x20)  //single floatpt
       {
#ifdef __MC68K__
         cf=*((double*)a);
         if ( cf < *((float*)b) ) res=-1;
         else
         {
           
           if   ( cf > *((float*)b) ) res=1;
           else res=0;
         }
#else
         double cft;
         union {float d; UInt32 i;} x;
         x.i = ReadUnaligned32(b);
         cft = x.d;
         cf=aval;
         if (cf <cft) res=-1;
         else
         {
           
           if   (cf > cft) res=1;
           else res=0;
         }
#endif
         goto compOver;
      }
      if(theKind.flags&  0x10)  //2-byte integers
      {
#ifdef __MC68K__
        ci=*((double*)a);
        if ( ci < *((int*)b) ) res=-1;
        else
        {
           if   ( ci > *((int*)b) ) res=1;
           else res=0;
        }
#else
        Int16 cit = *((Int16*)b);
        cit = ByteSwap16(cit);
        ci=aval;
        if ( ci < cit) res=-1;
        else
        {
           if   ( ci > cit) res=1;
           else res=0;
        }
#endif
        goto compOver;
      }
      
        res=0;
#endif         
  }
compOver:  

//StrPrintF(debug,"leaving compare res=%d",res);
//SysFatalAlert(debug);

  return(res);
}

/********************************************************************************************/
#ifdef __MC68K__
struct dbType *getDatabasePtr( )
#else
struct dbType *getDatabasePtr(PNOBlock *pnoP)
#endif
{
  VoidPtr p;
  struct dbType db_example;
  VoidPtr q;
  
  Int16 s=sizeof(db_example);
  UInt offset=s*PNO(dbNo);
    
//StrPrintF(debug,"dbno=%d len=%d dboffset=%d",dbNo,s,offset);
//SysFatalAlert(debug);
  
  p= (char*)PNO(dbElemsPtr) + offset;
  return((struct dbType*)p);
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_menureset()
#else
void verb_menureset(PNOBlock *pnoP)
#endif
{
   if (PNO(menuPtr)!=NULL)
   {
     MenuEraseStatus(PNO(menuPtr));
   }
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_menudraw()
#else
void verb_menudraw(PNOBlock *pnoP)
#endif
{
   Int16 menuID;
   if(MenuGetActiveMenu()!=NULL)
   {
      MenuEraseStatus(NULL);
      MenuSetActiveMenu(NULL);
      FrmSetMenu(FrmGetActiveForm(),0);
      MenuDispose(PNO(menuPtr));
      PNO(menuPtr)=(MenuBarType*)NULL; 
   }
#ifdef __MC68K__
   menuID=find_integer();
#else
   menuID=find_integer(pnoP);
#endif
   PNO(menuPtr)=MenuInit(menuID);
   MenuSetActiveMenu(PNO(menuPtr));
   MenuDrawMenu(PNO(menuPtr));
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_menuerase()
#else
void verb_menuerase(PNOBlock *pnoP)     // EMP
#endif
{
  
  if( MenuGetActiveMenu() != NULL )
  {
     MenuDispose(PNO(menuPtr));
     PNO(menuPtr)=(MenuBarType*)NULL;
  }
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_initAVariableValue()
#else
void verb_initAVariableValue(PNOBlock *pnoP)
#endif
{
    //initializes all occurrences of a variable's value to null-values if a string var and 0 if any other kind
    Int16 wki;
    double d=0;
    Int16 ii,jj,kk;

#ifdef __MC68K__
    find_arg_1();
#else
    UInt16 mv1, mv2, mv3, tn;
    struct dataelem *dex = NULL;
    MemHandle hData;
    Arg arg1;
    find_arg_PNO(pnoP, &arg1);
    
#define DELEN ((ULong)&(dex -> flags3))-((ULong)dex)+1

    mv1 = arg1.dataElem -> max_no_values1;
    mv2 = arg1.dataElem -> max_no_values2;
    mv3 = arg1.dataElem -> max_no_values3;
    
    mv1 = ByteSwap16(mv1);
    mv2 = ByteSwap16(mv2);
    mv3 = ByteSwap16(mv3);
    
    d = SwapDouble(d);
    
#endif

#ifdef __MC68K__
    if(arg1->max_no_values1<2)
#else
    if (mv1 < 2)
#endif
    {
#ifdef __MC68K__
       if(arg1->kind=='s')  misc_stostr1("");
       else                 misc_stodbl1(&d);
#else
       if(arg1.dataElem -> kind=='s')
       {
         misc_stostr(pnoP, &arg1.dataElem, arg1.occ1, arg1.occ2, arg1.occ3, "");
       }
       else
       {
         misc_stodbl(pnoP, arg1.dataElem, arg1.occ1, arg1.occ2, arg1.occ3, &d);
       }
#endif
    }
    else
    {
#ifdef __MC68K__
      if(arg1->kind!='s')  DmSet(arg1,DELEN,8*arg1->max_no_values1*arg1->max_no_values2*arg1->max_no_values3,0x00);
#else
      if(arg1.dataElem -> kind != 's')
      {
        DmSet(arg1.dataElem, DELEN, 8*mv1*mv2*mv3,0x00);
      }

#endif
      else
      { 
#ifdef __MC68K__
           hData=MemPtrRecoverHandle(arg1);
           MemHandleUnlock(hData);
           hData=DmResizeResource(hData,DELEN+2*arg1->max_no_values1*arg1->max_no_values2*arg1->max_no_values3);
           if(hData==0) OutOfMemory(6004);     //inserted 05282003
           arg1=(struct dataelem*)MemHandleLock(hData);
#else
           hData=MemPtrRecoverHandle(arg1.dataElem);
           MemHandleUnlock(hData);
           hData=DmResizeResource(hData,DELEN+2*mv1*mv2*mv3);
           if(hData==0) OutOfMemory(6004);     //inserted 05282003
           arg1.dataElem = (struct dataelem*)MemHandleLock(hData);
           dex = (struct dataelem *)ByteSwap32(arg1.dataElem);
#endif

#ifdef __MC68K__           
           DmWrite(PNO(deListPtr),arg1->tbl_no*4,&arg1,4);  //store handle in de list

           wki=DELEN+2*arg1->max_no_values1*arg1->max_no_values2*arg1->max_no_values3;;
           updti(arg1,&arg1->firstData,&wki);
           DmSet(arg1,DELEN,2*arg1->max_no_values1*arg1->max_no_values2*arg1->max_no_values3,0x00);
#else
           tn = arg1.dataElem -> tbl_no;
           tn = ByteSwap16(tn);
           DmWrite(PNO(deListPtr),tn * 4,&dex,4);  //store handle in de list

           wki=DELEN+2*mv1*mv2*mv3;
           wki = ByteSwap16(wki);
           updti(arg1.dataElem, &(arg1.dataElem -> firstData), &wki);
           DmSet(arg1.dataElem,DELEN,2*mv1*mv2*mv3,0x00);
#endif

#ifdef __MC68K__
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
#endif
      }
    }
//dbug("leaving init");  

#ifndef __MC68K__
#undef DELEN
#endif
}


/********************************************************************************************/
#ifdef __MC68K__
void getModIDandOffset(UInt16 seqno,UInt16*id,UInt16*offset)
#else
void getModIDandOffset(PNOBlock *pnoP, UInt16 seqno, UInt16*id, UInt16*offset)   // EMP
#endif
{
 Int16 id2;
 Int16 err;
 VoidHand h2;
 VoidPtr p2;
//dbug("at getmodid");

    if (PNO(parag_cnt) > 0)
    {
        h2=DmGetResource(rscTag,(ULong)9910);
        if(h2==0)
        {
            SysFatalAlert("Can't find program's parag record");
#ifdef __MC68K__
            ErrThrow(-1);                 //inserted 05212003
#else
            GlueErrThrow(pnoP, -1);                 //inserted 05212003
#endif
         //05212003 return;

        }

        p2=MemHandleLock(h2);

      //these are really link records for ext sub/func calls
//StrPrintF(debug,"getting id & offset for seqno=%d",seqno);
//SysFatalAlert(debug);

        id2=basc_dbGetInt((char*)p2+(seqno-1)*4);
        *id=(unsigned short)id2;
        *offset=(unsigned short)basc_dbGetInt((char*)p2+(seqno-1)*4+2);

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
#ifdef __MC68K__
void verb_user_func()
#else
void verb_user_func(PNOBlock *pnoP)
#endif
{
  Err err;
  char resourceId[5]; //added 5.27.2000  4 + null (the null is ignored
  UInt32 rscLong;

  VoidHand newHand;  //added 5.27.2000
  VoidPtr newPtr;    //added 5.27.2000
  VoidPtr oldPtr;    //added 5.27.2000
  
  UInt16 idno;
  UInt16 shortOffset;
  UInt32 offset;
  VoidHand hand;
  VoidPtr ptr;
  Int16 i;
  Int16 iy;
  UInt32 wkl;
  Int16 wki;
  
//dbug("a");
#ifdef __MC68K__
  iy=find_integer();
  getModIDandOffset(iy,&idno,&shortOffset);
#else
  iy = find_integer(pnoP);
  getModIDandOffset(pnoP, iy,&idno,&shortOffset);
#endif
  offset=shortOffset;
  

notNow:
//StrPrintF(debug,"going to user func idno=%d offset=%lu",idno,offset);
//SysFatalAlert(debug);
  if (idno != 0)
#ifdef __MC68K__
    codeexec2(idno,offset);
#else
    codeexec2(pnoP, idno,offset);
#endif
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_call()
#else
void verb_call(PNOBlock *pnoP)
#endif
{
    UInt16 idno;
    UInt16 shortOffset;
    UInt16 offset;
    UInt16 i;
  
#ifdef __MC68K__
    i=find_integer();
#else
    i=find_integer(pnoP);
#endif
#ifdef __MC68K__
    getModIDandOffset(i,&idno,&shortOffset);
#else
    getModIDandOffset(pnoP, i,&idno,&shortOffset);
#endif
    offset=shortOffset;
//dbug("verb-call going to codeexec");
#ifdef __MC68K__
    codeexec(idno,offset);
#else
    codeexec2(pnoP, idno,offset);
#endif
  
}

#ifdef __MC68K__
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
#endif

static void HToA(Char *d, UInt32 i)
{
	char buf[10];
	char *b;
	char hex[16] = 
{
	'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'
};
	
	b = buf;
	if (i)
	{
		while (i)
		{
			Int16 dig = i % 16;
			i = i / 16;
			*b++ = hex[dig];
		}
		
		while (b > buf)
		{
			*d++ = *--b;
		}
		
		*d = '\0';
	}
	else
	{
		*d = '0';
		*(d + 1) = '\0';
	}
}

/********************************************************************************************/
#ifdef __MC68K__
void commonShowHide(Int16 what, FormPtr frmPtr, Int16 controlid)
#else
void commonShowHide(PNOBlock *pnoP, Int16 what, FormPtr frmPtr, Int16 controlid)
#endif
{
	struct ObjectData *objPtr;		//added 09242004
  UInt16 j;
  
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

#ifdef __MC68K__
 objPtr = locateObjectPtr(controlid);	//added 09242003
#else
 objPtr = locateObjectPtr(pnoP, controlid);	//added 09242003
#endif
//StrPrintF(debug,"found j=%d",j);
//SysFatalAlert(debug);
  if (what==0x00)
  {
     FrmHideObject((FormType*)frmPtr,j);
     objPtr->hidden=true;		// added 09242003
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
                   //have an attached scrollbar                                           //added 12172001
                   FrmHideObject((FormType*)frmPtr,j+1);  //09092002 hide scrollbar
                }                                                                         //added 12172001
            }
            if(FrmGetObjectType(frmPtr,j)==frmTableObj)  
#ifdef __MC68K__
            	redrawGrid(objPtr); //added 09242003
#else
            	redrawGrid(pnoP, objPtr); //added 09242003
#endif
      }
  }
  else 
  {
  	  FrmShowObject((FormType*)frmPtr,j);
      objPtr->hidden=false;                  //added 09242003
      
      if((FrmGetObjectType(frmPtr,j)==frmFieldObj)    //added 09242003
      || (FrmGetObjectType(frmPtr,j)==frmTableObj) )  //added 09242003
	  {			
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
      if(FrmGetObjectType(frmPtr,j)==frmTableObj)  
	  {
#ifdef __MC68K__
      	redrawGrid(objPtr); //added 09242003                  
#else
	    redrawGrid(pnoP, objPtr);
#endif
	  }
  }

}

/********************************************************************************************/
#ifdef __MC68K__
void verb_controlhideorshow()
#else
void verb_controlhideorshow(PNOBlock *pnoP)
#endif
{
  char res;
  Word j;
  VoidPtr frmPtr;

#ifdef __MC68K__
  find_ctlid(true);
  res=find_char();
#else
  find_ctlid(pnoP, true);
  res=find_char(pnoP);
#endif
  
  frmPtr=FrmGetActiveForm();   //pt to form
  if(frmPtr==NULL) return;   //???says frm not loaded
//StrPrintF(debug,"got form=%d #objs=%d",wkid,  FrmGetNumberOfObjects(frmPtr));
//SysFatalAlert(debug);
#ifdef __MC68K__
  commonShowHide(res,frmPtr,PNO(controlid));
#else
  commonShowHide(pnoP, res,frmPtr,PNO(controlid));
#endif
  return;
}

/********************************************************************************************/
void commonSetFieldTextRoutine(FieldPtr controlPtr,Word controlId, char*s) // EMP
{
  FormPtr frmPtr;        // added 5.20.2000
  Word idx;              //added 5.20.2000  
 
  VoidHand oldHand;
  VoidHand h;
  VoidPtr p;

#ifdef __MC68K__
  FieldAttrType attr;
#else
  UInt16 attr;
#endif
  
  Int16 res;
  Int16 i;
  
  oldHand=FldGetTextHandle((FieldPtr)controlPtr);  //get handle to the field's current content

#ifdef __MC68K__
  i=StrLen(s)+1;
  h=MiscHandleNew(i,"setTxt");  //get new memory for the fld text
  p=MiscHandleLock(h);          //and lock a pointer to it
  StrCopy((char*)p,s);   //and copy text into new area
  MiscPtrUnlock(p);           // and unlock the new text pointer
#else
  i=strlen(s)+1;
  h=MemHandleNew(i);  //get new memory for the fld text
  p=MemHandleLock(h);          //and lock a pointer to it
  strcpy((char*)p,s);   //and copy text into new area
  MemPtrUnlock(p);
#endif
//StrPrintF(debug,"comparing id=%d to %d",FrmGetObjectId(frmPtr,idx),controlId);
//dbug(debug);

  
//StrPrintF(debug,"Setting field text to %s",p);
//dbug(debug);  
  
  //now go change the field's text but don't redraw                          //added 5.31.2000
  //temp SetFieldText(controlid, p, FldGetMaxChars((FieldPtr)controlPtr)+1,false);  //added 5.31.2000
  //FldSetTextHandle((FieldPtr)controlPtr,(Handle)h);  //temp
  FldSetText((FieldPtr)controlPtr,(Handle)h,0,MemHandleSize(h)); 
  if(oldHand) MemHandleFree(oldHand);  //0803 m2000
  //FldDrawField ((FieldPtr)controlPtr);

  frmPtr= FrmGetActiveForm();
//StrPrintF(debug,"active form=%d controlId=%d",FrmGetActiveFormID(),controlId);
//dbug(debug);
  
  for(idx=0;idx<FrmGetNumberOfObjects(frmPtr);++idx)
  {
     if(FrmGetObjectId(frmPtr,idx)==controlId)  //see if fld on cur form
     {
//dbug("redrawing");
       //see if hidden and if so exit
#ifdef __MC68K__
       FldGetAttributes((FieldPtr)FrmGetObjectPtr(frmPtr,idx) ,&attr);
       if(attr.visible==0)  return;
#else
       FldGetAttributes((FieldPtr)FrmGetObjectPtr(frmPtr,idx) ,(FieldAttrPtr) &attr);
       if((attr & 0x4000) == 0)  return;
#endif
         //see if any attached scrollbars that need updated                          //added 5.20.2000
       FldDrawField ((FieldPtr)controlPtr);
       if(FrmGetObjectType(frmPtr, idx+1)==frmScrollBarObj)                      //added 5.20.2000
       {                                                                         //added 5.20.2000 
          //have an attached scrollbar                                           //added 5.20.2000
//SysFatalAlert("updating scrollbar");
          UpdateScrollbar((FieldPtr)controlPtr                      ,            //added 5.20.2000
                      (ScrollBarPtr )(FrmGetObjectPtr(frmPtr, idx+1)));       //added 5.20.2000
          return;            
       }
     }                                                                           //added 5.20.2000
   }
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_fieldsettext()
#else
void verb_fieldsettext(PNOBlock *pnoP)
#endif
{
#ifdef __MC68K__
  find_ctlid(true);
  find_arg_1(); //text
  commonSetFieldTextRoutine((FieldPtr)PNO(controlPtr),PNO(controlid),arg1_val);
#else
    Arg text;
    find_ctlid(pnoP, true);
    find_arg_PNO(pnoP, &text);
    commonSetFieldTextRoutine((FieldPtr)PNO(controlPtr),PNO(controlid),text.val);
#endif
}


/********************************************************************************************/
#ifdef __MC68K__
void verb_draw_bitmap()
#else
void verb_draw_bitmap(PNOBlock *pnoP)
#endif
{
    //from Palm Dev Support
    UInt16 theBitmapId;
    VoidHand		theResourceHandle;
	BitmapPtr	theBitmapPtr;
	Int16 x;
	Int16 y;
//SysFatalAlert("at draw bitmap");
#ifdef __MC68K__
    find_arg_1();
    find_arg_2();
    find_arg_3();
	theBitmapId=basc_integ_value(arg1,(double*)arg1_val);
	x=basc_integ_value(arg2,(double*)arg2_val);
	y=basc_integ_value(arg3,(double*)arg3_val);
#else
    Arg arg1, arg2, arg3;
    find_arg_PNO(pnoP, &arg1);
    find_arg_PNO(pnoP, &arg2);
    find_arg_PNO(pnoP, &arg3);
    
    theBitmapId = ReadUnaligned64(arg1.val);
    x = ReadUnaligned64(arg2.val);
    y = ReadUnaligned64(arg3.val);
    
#endif	
	// Grab the handle to our bitmap resource
	theResourceHandle = DmGetResource( bitmapRsc, theBitmapId );
	if (theResourceHandle==NULL)
	{                                //inserted 05212003   
	   SysFatalAlert("Can't find a bitmap to draw.");
#ifdef __MC68K__
	   ErrThrow(-1);                 //inserted 05212003
#else
       GlueErrThrow(pnoP, -1);
#endif
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

#ifdef __MC68K__
void verb_assign_bitmap()
#else
void verb_assign_bitmap(PNOBlock *pnoP) // EMP
#endif
{
   FormBitmapType * BitmapPtr;
#ifdef __MC68K__
   find_ctlid(true);
   find_arg_2();  //bitmap rscid
#else
    Arg arg2;
    find_ctlid(pnoP, true);
    find_arg_PNO(pnoP, &arg2);
    BitmapPtr = (FormBitmapType*)PNO(controlPtr);
#endif
   BitmapPtr=(FormBitmapType*)PNO(controlPtr);
   //BitmapPtr->rscID=basc_integ_value(arg2,(double*)arg2_val); //GHGlue: AFAIK, this is never called.
   
}


/********************************************************************************************/
#ifdef __MC68K__
Boolean find_ctlid(Boolean abortSw)
#else
Boolean find_ctlid(PNOBlock *pnoP, Boolean abortSw)
#endif
{
   char work[100];
   Int16 err;
   Word idx2;
   VoidHand h2;
   char* p2;
   char *savep2;
   Int16 wkint;
   Int16 wkcnt;
   Int16 wk0,wk1,wk2,wk3;
   Int16 i;
   UInt wkid;
   VoidPtr frmPtr;
   Int16 j;
   Boolean retVal;

#ifdef __MC68K__
   PNO(controlid) = find_integer();
#else
   PNO(controlid) = find_integer(pnoP);
#endif
   
    h2=DmGetResource(rscTag,(ULong)9907);
    if(h2==0)
    {
        SysFatalAlert("Can't find view record");
#ifdef __MC68K__
        ErrThrow(-1);                 //inserted 05212003
#else
        GlueErrThrow(pnoP, -1);
#endif
        //05212003 return;
    }

    p2=MemHandleLock(h2);
    savep2=p2;
    //StrPrintF(debug,"-4  view_cnt=%d",view_cnt);
    //SysFatalAlert(debug);
    wkint=0;
    wkcnt=0;
                           //06102002
    for(i=0;i< PNO(view_cnt);++i)
    {
        wkid=basc_dbGetInt( (char*)p2); //06102002(modified) /*get id of view*/
        p2=(VoidPtr)((char*)p2+2); 
        if (PNO(applVersionInteg) >= 300)    //06102002
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
            if( FrmGetObjectId((FormType*)frmPtr,j)==PNO(controlid))
            {
                PNO(controlPtr)=FrmGetObjectPtr((FormType*)frmPtr,j);
                retVal=true;
                goto foundId;
            }
        }
        //++p2;
    }
notFoundCtlId:   
    if (abortSw==true)
    {
#ifdef __MC68K__
        StrPrintF(work,"can't find control object #=%d cnt=%d TOT=%d ",
              PNO(controlid),wkcnt,wkint);
        SysFatalAlert(work);
        ErrThrow(-1);                 //inserted 05212003
#else
        char *s, *d;
        d = work;
        s = "can't find control object #=";
        while (*s) *d++ = *s++;
        StrIToA(d, PNO(controlid));
        while (*d) ++d;
        s = " cnt=";
        while (*s) *d++ = *s++;
        StrIToA(d, wkcnt);
        while (*d) ++d;
        s = " TOT =";
        while (*s) *d++ = *s++;
        StrIToA(d, wkint);
        SysFatalAlert(work);
        GlueErrThrow(pnoP, -1);
#endif
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
#ifdef __MC68K__
void verb_getPen()
#else
void verb_getPen(PNOBlock *pnoP)   // EMP
#endif
{
#ifdef __MC68K__
  find_arg_1();  //current x
  find_arg_2();  //current y
  find_arg_3();  //pen up/down
#else
    Arg arg1, arg2, arg3;
    double d;
    
    find_arg_PNO(pnoP, &arg1);
    find_arg_PNO(pnoP, &arg2);
    find_arg_PNO(pnoP, &arg3);
#endif

#ifdef __MC68K__
  restore_int_val(PNO(currentX),arg1, (double*)arg1_val, arg1_occ1,arg1_occ2,arg1_occ3);
  restore_int_val(PNO(currentY),arg2, (double*)arg2_val, arg2_occ1,arg2_occ2,arg2_occ3);
  if(PNO(penDown))  restore_int_val(2,arg3, (double*)arg3_val, arg3_occ1,arg3_occ2,arg3_occ3);
  else               restore_int_val(3,arg3, (double*)arg3_val, arg3_occ1,arg3_occ2,arg3_occ3);
#else
  /* All these intermediary functions are giving me a headache.  Obviate them. --EMP*/
  d = PNO(currentX);
  d = SwapDouble(d);
  misc_stodbl(pnoP, arg1.dataElem, arg1.occ1, arg1.occ2, arg1.occ3, &d);
  
  d = PNO(currentY);
  d = SwapDouble(d);
  misc_stodbl(pnoP, arg2.dataElem, arg2.occ1, arg2.occ2, arg2.occ3, &d);
  
  d = PNO(penDown) ? 2.0 : 3.0;
  d = SwapDouble(d);
  misc_stodbl(pnoP, arg3.dataElem, arg3.occ1, arg3.occ2, arg3.occ3, &d);
#endif
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_start_debug()
#else
void verb_start_debug(PNOBlock *pnoP)
#endif
{
  PNO(debug_on)=1;
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_end_debug()
#else
void verb_end_debug(PNOBlock *pnoP)
#endif
{
  PNO(debug_on)=0;
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_end_sub()
#else
void verb_end_sub(PNOBlock *pnoP)
#endif
{
   VoidHand newHand;
   VoidHand oldHand;
   VoidPtr oldPtr;
   VoidPtr newPtr;
   Int16 ix;
   Int16 id;
   Int16 i;
   Int16 kk;
   Int16 res;
   UInt finalInstrCtr=PNO(instr_ctr);
   struct dataelem* de;
#ifndef __MC68K__
    Int16 ox;
    UInt16 oy;
#endif

    //remove any work var recs created for this function
   for(kk=1;kk<=PNO(work_de_max);++kk)
   {
       de=*((VoidPtr*)((char*)PNO(deListPtr)+4*kk));
#ifndef __MC68K__
       de = (struct dataelem *) ByteSwap32((unsigned long) de);
#endif
       if( de!=0)
       {
          if((de->flags3 & 0x02)==0x02)  //08032002
          {
             MemPtrFree(de);
          }
          else
          {
           res=DmFindResource(PNO(VbRscDB),(ULong)'WkVr',PNO(work_de_max)*PNO(userFunctionSequentialNo)+kk,NULL);
           if(res!= -1)
           {
//StrPrintF(debug,"removing wkvar %d",work_de_max*userFunctionSequentialNo+kk);
//SysFatalAlert(debug);
               DmRemoveResource(PNO(VbRscDB),res); //delete  if there
           }
         }   
       }
   }
//dbug("re-estab wk vars");

   
   id=PNO(codeBlockPtr)->functionLinkNo;
   
   while(1)
   {
//StrPrintF(debug,"searching for rec=%d offset=&%d",PNO(codeBlockPtr)->functionLinkNo, PNO(codeBlockPtr)->offset);
//SysFatalAlert(debug);
     ix=DmFindResource(PNO(VbRscDB),(ULong)'fwrk',id,NIL); 
      if(ix!= -1)
      {
//dbug("got old func rec");
#ifdef __MC68K__
        oldHand=MiscDmGetResourceIndex(PNO(VbRscDB),ix,"rescwk"); 
        oldPtr=MiscHandleLock(oldHand);
#else
        oldHand=DmGetResourceIndex(PNO(VbRscDB),ix); 
        oldPtr=MemHandleLock(oldHand);
#endif
//StrPrintF(debug,"got id=%d offset=%d",*((int*)oldPtr),*((unsigned int*)((char*)oldPtr+2)));
//SysFatalAlert(debug);

#ifdef __MC68K__
        if( (*((Int16*)oldPtr) != PNO(codeBlockPtr)->functionLinkNo) || 
            (*((UInt16*)((char*)oldPtr+2)) != PNO(codeBlockPtr)->offset))
#else
        ox = *((Int16 *)oldPtr);
        ox = ByteSwap16(ox);
        oy = *((UInt16*)((char*)oldPtr+2));
        oy = ByteSwap16(oy);
        
        if (ox != PNO(codeBlockPtr) -> functionLinkNo ||
            oy != PNO(codeBlockPtr) -> offset)
#endif
        {
#ifdef __MC68K__
           MiscHandleUnlock(oldHand);
           MiscDmReleaseResource(oldHand);
#else
            MemHandleUnlock(oldHand);
            DmReleaseResource(oldHand);
#endif
           id+=50;                        //increm recno by 50 to try again
        }
        else
        {
          break;               //found the record we want
        } 
      }
      else
      {
#ifdef __MC68K__
          MiscFatalAlert("internal error exiting a function.");
#else
          SysFatalAlert("internal error exiting a function.");
#endif
      }
   }   
//StrPrintF(debug,"find linkNo=%d rsc=%d ",id,ix);
//SysFatalAlert(debug);
   MemMove((char*)PNO(deListPtr)+4,(char*)oldPtr+4,PNO(work_de_max)*4);        //and copy the handles
   MemHandleUnlock(oldHand);
#ifdef __MC68K__
   MiscDmReleaseResource(oldHand);
#else
   DmReleaseResource(oldHand);
#endif
   PNO(userFunctionSequentialNo)-=1;  //reduce count of nested user function calls
   
   
   PNO(instr_ctr)=PNO(codeBlockPtr)->argsOffset; //reset called args ptr
//dbug("in verb end rtn");
//StrPrintF(debug,"sub-end=%d resetting PNO(instr_ctr) to %d",PNO(codeBlockPtr)->id,PNO(instr_ctr));
//SysFatalAlert(debug);

#ifdef __MC68K__
   end_all_move_args();
#else
   end_all_move_args(pnoP);
#endif
   PNO(instr_ctr)=finalInstrCtr;
//dbug("leaving verb_end_sub");
}



//------------------------------------------------------------------------------
//     end of a user defined function
//------------------------------------------------------------------------------
#ifdef __MC68K__
void verb_end_function()
#else
void verb_end_function(PNOBlock *pnoP)      // EMP
#endif
{
     char resourceId[5];        //added 5.27.2000
     ULong rscLong;

     VoidHand newHand;          //added 5.27.2000
     VoidHand oldHand;          //added 5.27.2000
     VoidPtr  oldPtr;           //added 5.27.2000
     VoidPtr  newPtr;           //added 5.27.2000 
     Int16 ix;                    //added 5.27.2000 
     Int16 id;
     Int i;                     //added 5.27.2000    
     DmOpenRef dbr; 
     Int16 kk,mm,nn; 
     Int16 res;
     UInt16 instr_ctr_save;
     char *codePtrSave;
     UInt16 finalInstrCtr=PNO(instr_ctr);
//dbug("in end of user func");
     struct dataelem* de;
 
    //remove any work var recs created for this function
   for(kk=1;kk<=PNO(work_de_max);++kk)
   {
       de=*((VoidPtr*)((char*)PNO(deListPtr)+4*kk));
       if( de!=0)
       {
#ifndef __MC68K__
          de = (struct dataelem *) ByteSwap32(de);
#endif
          if((de->flags3 & 0x02)==0x02)  //08032002
          {
             MemPtrFree(de);
          }
          else
          {
           res=DmFindResource(PNO(VbRscDB),(ULong)'WkVr',PNO(work_de_max)*PNO(userFunctionSequentialNo)+kk,NULL);
           if(res!= -1)
           {
//dbug("removing wkvar");
               DmRemoveResource(PNO(VbRscDB),res); //delete  if there
           }
         }   
       }
   }
   id=PNO(codeBlockPtr)->functionLinkNo;
   
   while(1)
   {
      ix=DmFindResource(PNO(VbRscDB),(ULong)'fwrk',id,NIL); 
      if(ix!= -1)
      {
//dbug("got old func rec");
#ifdef __MC68K__
        oldHand=MiscDmGetResourceIndex(PNO(VbRscDB),ix,"rescwk"); 
        oldPtr=MiscHandleLock(oldHand);
        if( (*((Int16*)oldPtr) != PNO(codeBlockPtr)->functionLinkNo) || (*(UInt16*)((char*)oldPtr+2) != PNO(codeBlockPtr)->offset))
        {
           MiscHandleUnlock(oldHand);
           MiscDmReleaseResource(oldHand);
           id+=50;                        //increm recno by 50 to try again
        }
#else
        Int16 oldFLN, oldOffset;
        oldHand = DmGetResourceIndex(PNO(VbRscDB), ix);
        oldPtr = MemHandleLock(oldHand);
        oldFLN = *((Int16 *) oldPtr);
        oldFLN = ByteSwap16(oldFLN);
        oldOffset = *(UInt16*)((char*)oldPtr+2);
        oldOffset = ByteSwap16(oldOffset);
        
        if ((oldFLN != PNO(codeBlockPtr) -> functionLinkNo ||
            (oldOffset != PNO(codeBlockPtr)->offset)))
        {
            MemHandleUnlock(oldHand);
            DmReleaseResource(oldHand);
            id += 50;
        }

#endif
        else
        {
          break;               //found the record we want
        } 
      }
      else
      {
          SysFatalAlert("internal error exiting a function.");
      }
   }   
//StrPrintF(debug,"find linkNo=%d rsc=%d ",id,ix);
//SysFatalAlert(debug);
                              //point to the new wk var record
   
                          //point to the old copy of the wk var handles
   MemMove((char*)PNO(deListPtr)+4,(char*)oldPtr+4,PNO(work_de_max)*4);        //and copy the handles
   MemHandleUnlock(oldHand);
#ifdef __MC68K__
   MiscDmReleaseResource(oldHand);
#else
    DmReleaseResource(oldHand);
#endif

   PNO(userFunctionSequentialNo)-=1;  //reduce count of nested user function calls
       
    PNO(instr_ctr)=PNO(codeBlockPtr)->argsOffset; //reset called args ptr
#ifdef __MC68K__
    end_all_move_args();
#else
    end_all_move_args(pnoP);
#endif
 skip:
#ifdef __MC68K__
    find_arg_2();   //name of func dataname to put result in   ??used or not
#else
    {
        Arg arg2;
        find_arg_PNO(pnoP, &arg2);  // EMP hope this isn't used
    }
#endif

    instr_ctr_save=PNO(instr_ctr);
    codePtrSave=PNO(codePtr);
    PNO(codePtr)=(char*)PNO(codeBlockPtr)->codePtr;
    PNO(instr_ctr)=PNO(codeBlockPtr)->instr_ctr;
//StrPrintF(debug,"moving one arg instr-ctr=%ui",PNO(instr_ctr));
//SysFatalAlert(debug);    
#ifdef __MC68K__
    find_arg_1();  //called func name ref
#else
    {
        Arg arg1;
        find_arg_PNO(pnoP, &arg1);  // EMP hope this isn't used
    }
#endif
    PNO(codeBlockPtr)->instr_ctr=PNO(instr_ctr);
    PNO(codePtr)=codePtrSave;
    PNO(instr_ctr)=instr_ctr_save;  // EMP need this?
    
   PNO(instr_ctr)=finalInstrCtr;
   

  
}

/********************************************************************************************/

#ifdef __MC68K__
void end_all_move_args()
#else
void end_all_move_args(PNOBlock *pnoP)
#endif
{
    UInt16 instr_ctr_save;
    char *codePtrSave;
    Int16 kk,mm,nn;
    struct dataelem *de1, *de2;
    UInt16 mv1, mv2, mv3, occ1;
#ifndef __MC68K__
    Arg arg1, arg2;
#endif

  while (1)   //copy args to internal vars
  {

    instr_ctr_save=PNO(instr_ctr);
    codePtrSave=PNO(codePtr);
    PNO(codePtr)=(char*)PNO(codeBlockPtr)->codePtr;
    PNO(instr_ctr)=PNO(codeBlockPtr)->instr_ctr;
//StrPrintF(debug,"moving one arg codePtr=%lu instr-ctr=%u",(unsigned long)(codePtr),PNO(instr_ctr));
//SysFatalAlert(debug);
#ifdef __MC68K__    
    find_arg_1();
#else
    find_arg_PNO(pnoP, &arg1);
#endif
    PNO(codeBlockPtr)->instr_ctr=PNO(instr_ctr);
    PNO(codePtr)=codePtrSave;
    PNO(instr_ctr)=instr_ctr_save;
 //StrPrintF(debug,"2cnd arg codePtr=%lu PNO(instr_ctr)=%d",(unsigned long)(codePtr),PNO(instr_ctr));
 //SysFatalAlert(debug);
 #ifdef __MC68K__
    find_arg_2();
    if (arg1==NULL)
 #else
     find_arg_PNO(pnoP, &arg2);
     if (arg1.dataElem == NULL)
 #endif
   {
//dbug("caller is null");
#ifdef __MC68K__
      if (arg2 != NULL)
#else
      if (arg2.dataElem != NULL)
#endif
      {
wrong_no:
         SysFatalAlert("Wrong number of func args");
#ifdef __MC68K__
         ErrThrow(-1);                 //inserted 05212003
#else
         GlueErrThrow(pnoP, -1);
#endif
      }
      else break;
    }
//dbug("caller not null");
#ifdef __MC68K__
    if (arg2==NULL)
#else
    if (arg2.dataElem == NULL)
#endif
    {
//dbug("func is null");
        goto wrong_no;
    }
//dbug("********moving it*");
#ifdef __MC68K__
    de1 = arg1;
    de2 = arg2;
#else
    de1 = arg1.dataElem;
    de2 = arg2.dataElem;
#endif

    mv1 = de2 -> max_no_values1;
    mv2 = de2 -> max_no_values2;
    mv3 = de2 -> max_no_values3;
#ifdef __MC68K__
    occ1 = arg2_occ1;
#else
    occ1 = arg2.occ1;
#endif
#ifndef __MC68K__
    mv1 = ByteSwap16(mv1);
    mv2 = ByteSwap16(mv2);
    mv3 = ByteSwap16(mv3);
#endif
    if (mv1 > 1 && occ1 == 0)
    {
        //looks like an array name without a subscript
        
        //need to move all values of the array
        for( kk=0;kk<mv1;++kk)
        {
           for( mm=0;mm<mv2;++mm)
           {
              for( nn=0;nn<mv3;++nn)
              {
#ifdef __MC68K__
                 arg1_val = devel_address(arg1, kk,mm,nn);
                 arg2_val = devel_address(arg2, kk,mm,nn);
                 arg1_occ1=kk;
                 arg1_occ2=mm;
                 arg1_occ3=nn;
#else
                 unsigned long l;
                 arg1.val = devel_address(pnoP, arg1.dataElem, kk, mm, nn);
                 arg2.val = devel_address(pnoP, arg2.dataElem, kk, mm, nn);
                 
                 arg1.occ1 = kk;
                 arg1.occ2 = mm;
                 arg1.occ3 = nn;
#endif
                 if (de1->kind=='s')
                 {
#ifdef __MC68K__
                      misc_stostr1(arg2_val);
#else
                      misc_stostr(pnoP, &arg1.dataElem, arg1.occ1, arg1.occ2, arg1.occ3, arg2.val);
#endif
                 }
                 else
                 {
#ifdef __MC68K__
                      misc_stodbl1((double*)arg2_val);
#else
	                  misc_stodbl(pnoP, arg1.dataElem, arg1.occ1, arg1.occ2, arg1.occ3, (double *) arg2.val);
#endif
                 }
              }
           }
        }   
      }
      else
      {
        if (de1->kind=='s')
        {
#ifdef __MC68K__
          misc_stostr1(arg2_val);
#else
          misc_stostr(pnoP, &arg1.dataElem, arg1.occ1, arg1.occ2, arg1.occ3, arg2.val);
#endif
        }
        else
        {
#ifdef __MC68K__
          misc_stodbl1((double*)arg2_val);
#else
	      misc_stodbl(pnoP, arg1.dataElem, arg1.occ1, arg1.occ2, arg1.occ3, (double *) arg2.val);
#endif
        }
     }  
  }
//dbug("args done");

}


/********************************************************************************************/
#ifdef __MC68K__
void verb_beep()
{
    if(PNO(romVersion)<0x03000000)
    {
        if(PrefGetPreference(prefSysSoundLevelV20)==slOff) return;  //prior to v3.0 -- exit if sound off
    }
    else
    {
        if(PrefGetPreference(prefSysSoundVolume)==0) return;        //v3.0 and up -- exit if sound volume=0
    }
    SndPlaySystemSound(sndError);
}
#endif

/********************************************************************************************/
#ifdef __MC68K__
void verb_seteventhandled()
#else
void verb_seteventhandled(PNOBlock *pnoP)    // EMP
#endif
{
   PNO(eventHandled)=1;
   if ( PNO(eventType)==3)
   {
       //penUp, so clear the pen event queue
       EvtFlushPenQueue();
   }
}

/********************************************************************************************/
void dbGetSome(void* from, Int16 len,void*to)
{
  int i;
  char*f=(char*)from;
  char*t=(char*)to;
  for (i=0;i<len;++i)
  {
     *(t++)=*(f++);
  }
}


#ifdef __MC68K__
/********************************************************************************************/
void verb_serialOpen()
{
   Err err;
   ULong port;											//12.05.02 GH
   ULong baud;
   VoidHand h;
   SrmOpenConfigType config;
   
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
       if(port==0) port=0x8000; //hotSync port           //02.27.02 GH
   	   err=SrmOpen(port, baud, &PNO(serRef));				 //02.27.02 GH
  	   modemInfo.portID=PNO(serRef);							 //02.27.02 GH
   setSerErr(err);
   if(err==0)
   {
       h=MemHandleNew(serialBufferSize+1+32);  //05282003
       if(h==0) OutOfMemory(6054);             //05282003
       serialBufferPtr=MemHandleLock(h);       //05282003
       
       SrmSetReceiveBuffer(PNO(serRef),serialBufferPtr,serialBufferSize+1+32);
   }
   serialSetState(kSerialNoAsync);
}

/**************************************************************************************************/
void verb_serialClose()
{
  Err err;
  
  if(PNO(serRef)) 
  {
  	if (gOldSerialManager) err=SerClose(PNO(serRef));	//02.27.02 GH
  	else err=SrmClose(PNO(serRef));						//02.27.02 GH
  }
  else err=serErrNotOpen;
  PNO(serRef)=0;
//StrPrintF(debug,"at serclose err=%d",err);
//SysFatalAlert(debug);
  if (err == 0)
  {
   MemPtrFree(serialBufferPtr);
   serialSetState(kSerialNoAsync);
  }
  setSerErr(err);

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
            err=SrmControl(PNO(serRef), srmCtlSetBaudRate, &i32, &size_i32);
            modemInfo.initialBaud=i32;
            goto processed;
       }      
       if (StrCompare(in,"stopbits")==0) 
       {    
            i=basc_integ_value(arg2,(double*)arg2_val);
            err=SrmControl(PNO(serRef), srmCtlGetFlags, &ui32, &size_ui32);
            if(i==1) ui32 &= ~srmSettingsFlagStopBits1;
            else if(i==2) ui32 |= srmSettingsFlagStopBits2;
            goto setIt;
       }     
       if (StrCompare(in,"parity")==0)
       {
            i=basc_integ_value(arg2,(double*)arg2_val);
            err=SrmControl(PNO(serRef), srmCtlGetFlags, &ui32, &size_ui32);
                        
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
            err=SrmControl(PNO(serRef), srmCtlGetFlags, &ui32, &size_ui32);
            if (i==1) ui32 |= srmSettingsFlagXonXoffM; //on
            else if (i==2) ui32 &= ~srmSettingsFlagXonXoffM; //off
            goto setIt; 
       }      
       if (StrCompare(in,"rtsauto")==0)
       {
            i=basc_integ_value(arg2,(double*)arg2_val);
            err=SrmControl(PNO(serRef), srmCtlGetFlags, &ui32, &size_ui32);
            if (i==1) ui32 |= srmSettingsFlagRTSAutoM; //on
            else if (i==2) ui32 &= ~srmSettingsFlagRTSAutoM; //off
            goto setIt; 
       }     
       if (StrCompare(in,"ctsauto")==0)
       {
            i=basc_integ_value(arg2,(double*)arg2_val);
            err=SrmControl(PNO(serRef), srmCtlGetFlags, &ui32, &size_ui32);
            if (i==1) ui32 |= srmSettingsFlagCTSAutoM; //on
            else if (i==2) ui32 &= ~srmSettingsFlagCTSAutoM; //off
            goto setIt; 
       }     
       if (StrCompare(in,"bitsperchar")==0)
       {
            i=basc_integ_value(arg2,(double*)arg2_val);
            err=SrmControl(PNO(serRef), srmCtlGetFlags, &ui32, &size_ui32);
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
            err=SrmControl(PNO(serRef), srmCtlIrDADisable,0,0);
            err=SrmControl(PNO(serRef), srmCtlRxDisable,0,0);
            }
            else if (i==1) //receive IR
            {
            err=SrmControl(PNO(serRef), srmCtlIrDAEnable,0,0);
            err=SrmControl(PNO(serRef), srmCtlRxEnable,0,0);
            }
            else if (i==2) //transmit IR
            {
            err=SrmControl(PNO(serRef), srmCtlIrDAEnable,0,0);
            err=SrmControl(PNO(serRef), srmCtlRxDisable,0,0);
            }
            goto processed; 
		}
	   if (StrCompare(in,"break")==0)
	    {
	        if (i==0)
	        {
	        err=SrmControl(PNO(serRef), srmCtlStopBreak,0,0);
	        }
	        else
	        {
	        err=SrmControl(PNO(serRef), srmCtlStartBreak,0,0);
	        }
	        goto processed;
	    }
       if (StrCompare(in,"ctstimeout")==0)
       {
            i32=*((double*)arg2_val)*sysTicksPerSecond;
            err=SrmControl(PNO(serRef), srmCtlSetCtsTimeout, &i32, &size_i32);
            goto processed;
       }
       if (StrCompare(in,"dtrassert")==0)
       {
            i=basc_integ_value(arg2,(double*)arg2_val);
            b=(i==1);
            err=SrmControl(PNO(serRef), srmCtlSetDTRAsserted, &b, &size_b);
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
            SrmSetReceiveBuffer(PNO(serRef),serialBufferPtr,serialBufferSize+1+32);
       
            err=0;
            goto processed;
       }
       if (StrCompare(in,"portid")==0)
       {
            PNO(serRef)=integ_value(arg2,(double*)arg2_val);       
            err=0;
            goto processed;
       }
       if (StrCompare(in,"coordinatesystem")==0)  //GWH 2003.03.27
       {
            if (PNO(romVersion)>=0x05000000) WinSetCoordinateSystem(integ_value(arg2,(double*)arg2_val));
            err=0;    
            goto processed;
       }
       StrPrintF(debug,"Unrecognizable set parameter=%s",in);
       SysFatalAlert(debug);
       ErrThrow(-1);                 //inserted 05212003     
  	   //05212003 return;
setIt:
       err=SrmControl(PNO(serRef), srmCtlSetFlags, &ui32, &size_ui32);
processed:
    setSerErr(err);
}
/**************************************************************************************************/
void verb_serialSetOld()
{
/*   VoidHand h;  //05282003 
   Err err;
   char in[50];
   char z;
   double dbl;
   int x;
   int i;
   SerSettingsType s;
   err=SerGetSettings( PNO(serRef),&s);
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
            
            SerSetReceiveBuffer(PNO(serRef),serialBufferPtr,serialBufferSize+1+32);
       
            err=0;
            goto processed;
       }
       if( StrCompare( in, "ir" ) == 0 )							//11.29.00 gh
       {															//11.29.00 gh
            i=basc_integ_value(arg2,(double*)arg2_val);
            if (i==0)
            {
            err=SrmControl(PNO(serRef), srmCtlIrDADisable,(void *)NULL, (UInt16 *)NULL);
            err=SrmControl(PNO(serRef), srmCtlRxDisable,(void *)NULL, (UInt16 *)NULL);
            }
            else if (i==1) //receive IR
            {
            err=SrmControl(PNO(serRef), srmCtlIrDAEnable,(void *)NULL, (UInt16 *)NULL);
            err=SrmControl(PNO(serRef), srmCtlRxEnable,(void *)NULL, (UInt16 *)NULL);
            }
            else if (i==2) //transmit IR
            {
            err=SrmControl(PNO(serRef), srmCtlIrDAEnable,(void *)NULL, (UInt16 *)NULL);
            err=SrmControl(PNO(serRef), srmCtlRxDisable,(void *)NULL, (UInt16 *)NULL);
            }
            goto processed; 
       }															//11.29.00 gh
       if (StrCompare(in,"portid")==0)
       {
            PNO(serRef)=integ_value(arg2,(double*)arg2_val);       
            err=0;
            goto processed;
       }
       StrPrintF(debug,"Unrecognizable serial set parameter=%s",in);
       SysFatalAlert(debug);
       ErrThrow(-1);                 //inserted 05212003     
   
   return;
setIt:
    err=SerSetSettings( PNO(serRef),&s);       
processed:
    setSerErr(err);
    return;
*/
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
    if(gOldSerialManager) SerReceiveFlush(PNO(serRef),0);  //flush any response bytes	//02.27.02 GH
    else SrmReceiveFlush(PNO(serRef),0);														//02.27.02 GH
    
    if(arg1->kind=='s')
    {
        //send a string
        if(gOldSerialManager) actBytes=SerSend(PNO(serRef), arg1_val, bytes, &err);		//02.27.02 GH
        else actBytes=SrmSend(PNO(serRef), arg1_val, bytes, &err);							//02.27.02 GH
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
       if(gOldSerialManager) actBytes=SerSend(PNO(serRef),pRcvBuf, bytes, &err);			//02.27.02 GH
       else actBytes=SrmSend(PNO(serRef),pRcvBuf, bytes, &err);								//02.27.02 GH
       MemPtrFree(pRcvBuf);
    }
    
    if(gOldSerialManager) SerSendWait(PNO(serRef),bytes*SysTicksPerSecond()/300); //use lowest speed //02.27.02 GH
    else SrmSendWait(PNO(serRef));															//02.27.02 GH
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
    
    if(PNO(gSerialState)==kSerialNoAsync)  
    {  	//************************** Normal serialReceive without events
retryReceive:
    //wait for entire response to arrive
    for( i=0;i<10; i++)
    {
	      //wait for max # of bytes. If the response is shorter, then timeout.
      bytes=saveBytes;
	      if(gOldSerialManager) err=SerReceiveWait(PNO(serRef), bytes, timeout);				 //02.27.02 GH
	      else err=SrmReceiveWait(PNO(serRef), bytes, timeout);				 //02.27.02 GH
	      
	      if( (err==0) || (err==serErrTimeOut)) break;   //normal case--all chars are in the receive queue or timeout received
	      else
	      {
	         if(err==serErrLineErr) 
	         {
	         	if(gOldSerialManager) SerReceiveFlush(PNO(serRef),SysTicksPerSecond()/50);	//02.27.02 GH
	         	else SrmReceiveFlush(PNO(serRef),SysTicksPerSecond()/50);	//02.27.02 GH
	         }   
      }   
    }
    saveErr=err;
    
getIt:
	    if(gOldSerialManager) err=SerReceiveCheck(PNO(serRef), &actBytes);					//02.27.02 GH
	    else err=SrmReceiveCheck(PNO(serRef), &actBytes);									//02.27.02 GH
	    
    if(actBytes>bytes) actBytes=bytes;  //limit to our req # chars
	    
	    if(gOldSerialManager) SerReceive(PNO(serRef), pRcvBuf, actBytes, 0, &err);			//02.27.02 GH
	    else SrmReceive(PNO(serRef), pRcvBuf, actBytes, 0, &err);						//02.27.02 GH
	    
    if(err==0) err=saveErr;   //may return timeout error
    setSerErr(err);
    }  	//*************************** End Normal serialReceive without events
    
    
    else if(PNO(gSerialState)==kSerialDataWaiting)
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
  if(PNO(gSerialState)!=kSerialNoAsync)
  {
  	setSerErr(2);  //state error - call issued while receive in progress
  	return;
  }
  if (gOldSerialManager) 
  {
	err=SerSetWakeupHandler(PNO(serRef),  (WakeupHandlerProcPtr)serialWakeupHandler, (UInt32) &PNO(gSerialState));
  	err=SerPrimeWakeupHandler(PNO(serRef), 1);
  }
  else 
  {
	err=SrmSetWakeupHandler(PNO(serRef),  (WakeupHandlerProcPtr)serialWakeupHandler, (UInt32) &PNO(gSerialState));
  	err=SrmPrimeWakeupHandler(PNO(serRef), 1);
  }
  setSerErr(err);
}

/**************************************************************************************************/
void serialWakeupHandler(UInt32 refCon)	//03.06.02 GH
{
	Boolean *serialStatePtr = (UInt8 *) refCon;
	*serialStatePtr = kSerialWaitingForData;
	EvtWakeup();
}

/**************************************************************************************************/
ULong serialReceiveAfterEvent(Char *outBuf, UInt32 outSize)	//03.06.02 GH
{
	Err	err;
	UInt8	*bytePtr;
	UInt32	size;
	ULong	totalAmtRead = 0;
	
	serialSetState(kSerialReadingData);
	do {
		err = DoReceiveWindowOpen(PNO(serRef), &bytePtr, &size);
		if (err == 0) {
			UInt32 amtToMove = size;
			
			if (amtToMove > outSize)
				amtToMove = outSize;
			MemMove(outBuf, bytePtr, amtToMove);
			outBuf += amtToMove;
			outSize -= amtToMove;
			totalAmtRead += amtToMove;
			DoReceiveWindowClose(PNO(serRef), size);
		}
	} while (err == 0 && size > 0);
	return totalAmtRead;
}

/**************************************************************************************************/
void serialSetState(UInt8 state)	//03.06.02 GH
{
//StrPrintF(debug,"Setting serial state to %hu ",state);
//SysFatalAlert(debug);
	PNO(gSerialState)=state;
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

/**************************************************************************************************/
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
#endif

/**************************************************************************************************/
#ifdef __MC68K__
struct ObjectData * locateObjectPtr(Word id)
#else
struct ObjectData * locateObjectPtr(PNOBlock *pnoP, Word id)
#endif
{
   
   struct ViewData * viewPtr;
   VoidPtr objectsPtr;
   struct ObjectData * thisObjPtr;

   Int16 testID;
   Int16 j;
   Int16 i;
   Int16 vpc;
   unsigned long l;
  
   for(i=0;i< PNO(view_cnt);++i)
   {
       viewPtr=(struct ViewData*)((char*)PNO(viewElemsPtr)+i*sizeof(viewExample));  //point to this view's data 


        vpc = viewPtr -> cnt;
#ifndef __MC68K__
        vpc = ByteSwap16(vpc);
#endif
       if(vpc==0) goto skipView;    //added 5.24.2000
       
       objectsPtr=viewPtr->objectsPtr;
#ifndef __MC68K__
        objectsPtr = (VoidPtr) ByteSwap32((unsigned long) objectsPtr);
#endif

       for(j=0;j<vpc;++j)
       {
          thisObjPtr=(struct ObjectData*)((char*)objectsPtr+j*sizeof(objectExample));  //point to this object's data
          
#ifdef __MC68K__
          if(thisObjPtr->id==id)
#else
          testID = thisObjPtr -> id;
          testID = ByteSwap16(testID);
          if (testID == id)
#endif
          {
#if 0
#ifdef __MC68K__
            saveObjectHandle=viewPtr->objectsHand; //save handle to unlock later after thru with thisObjPtr
#else
             l = (unsigned long) viewPtr->objectsHand; //save handle to unlock later after thru with thisObjPtr
            saveObjectHandle = (struct ObjectData *) ByteSwap32(l);
#endif
#endif
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
void FreeListValues(VoidPtr pold,Int16 noItems )
{
      
    
      VoidPtr p;
      
      Int16 i;
//dbug("in freeListValues");
      if(pold==0) return;
      //if( MemHandleOwner( MemPtrRecoverHandle(pold))==0) return;  //system owns it
      for(i=0;i<noItems;++i)
      {
//StrPrintF(debug,"freeing a string #=%d  this=%d",noItems,i);
//SysFatalAlert(debug);
         p=*((VoidPtr*)( (char*)pold+4*i));
#ifndef __MC68K__
         p = (VoidPtr) ByteSwap32(p);
#endif

//StrPrintF(debug,"freeing list element=%s   of length=%d",p,StrLen(p));
//SysFatalAlert(debug);         
         if(  p!=0) 
         {
#ifdef __MC68K__
             if(StrLen(p)==0) return;  //avoid mem problems --just exit
             MiscPtrFree( p);  //free one string
#else
             if(strlen(p)==0) return;  //avoid mem problems --just exit
             MemPtrFree(p);  //free one string
#endif
         }     

      }
//dbug("freeing the list ptr");
#ifdef __MC68K__
       MiscPtrFree(pold);   //and free the pointer list
#else
        MemPtrFree(pold);
#endif

}

/**************************************************************************************************/
#ifdef __MC68K__
void verb_setnumvarsfromheap()   //added 06102002
{
   find_arg_1();
   maxVarsInDynamHeap=integ_value(arg1,(double*)arg1_val);

}
#endif


/**************************************************************************************************/
#ifdef __MC68K__
void verb_clearscreentextfields()   //added 06102002
#else
void verb_clearscreentextfields(PNOBlock *pnoP)   //added 06102002
#endif
{
    //sets all fields in the form to empty strings
    UInt16 ID;


    VoidPtr frmPtr;
    struct ViewData * viewPtr;
    VoidPtr objectsPtr;
    struct ObjectData * thisObjPtr;
    Int16 j;
    Int16 i;
    Int16 n;
    char empty[]="";

#ifdef __MC68K__
    ID=find_integer();
#else
    UInt16 testID;
    
    ID = find_integer(pnoP);
#endif

    frmPtr=FrmGetFormPtr(ID);

   for(i=0;i< PNO(view_cnt);++i)
   {
     viewPtr=(struct ViewData*)((char*)PNO(viewElemsPtr)+i*sizeof(viewExample));  //point to this view's data 
     if(viewPtr->cnt==0) goto noObjs;   // OK for byte swap
#ifdef __MC68K__
     if(viewPtr->id==ID)
#else
     testID = viewPtr -> id;
     testID = ByteSwap16(testID);
     if (testID == ID)
#endif
     {
#ifdef __MC68K__
       objectsPtr=viewPtr->objectsPtr;
       for(j=0;j<viewPtr->cnt;++j)
#else
       Int16 cnt;
       Int16 type;
       objectsPtr = (VoidPtr) ReadUnaligned32(&(viewPtr -> objectsPtr));
       cnt = viewPtr -> cnt;
       cnt = ByteSwap16(cnt);
       for(j=0;j<cnt;++j)
#endif
       {

#ifdef __MC68K__
          thisObjPtr=(struct ObjectData*)((char*)objectsPtr+j*sizeof(objectExample));  //point to this object's data
              switch(thisObjPtr->type)
#else
          thisObjPtr=(struct ObjectData*)((char*)objectsPtr+j*sizeof(objectExample));  //point to this object's data
              type = thisObjPtr -> type;
              type = ByteSwap16(type);

              switch (type)
#endif
              {
                  case frmFieldObj:

                    for(n=0;n<FrmGetNumberOfObjects((FormType*)frmPtr);++n)
      				{
#ifdef __MC68K__      				
        				if( FrmGetObjectId((FormType*)frmPtr,n)==thisObjPtr->id)
#else
                        Int16 ID = thisObjPtr -> id;
                        ID = ByteSwap16(ID);
        				if( FrmGetObjectId((FormType*)frmPtr,n) == ID)
#endif
        				{
          					PNO(controlPtr)=FrmGetObjectPtr((FormType*)frmPtr,n);
          					PNO(controlid)=FrmGetObjectId((FormType*)frmPtr,n);
          					goto foundId;
        				}
      				}
foundId:
     				commonSetFieldTextRoutine((FieldPtr)PNO(controlPtr),PNO(controlid),empty);
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

#ifdef __MC68K__
void commonSetScrollbar(char c,FormPtr frmPtr, struct dataelem*arg, double* arg_val)
#else
void commonSetScrollbar(PNOBlock *pnoP, char c, FormPtr frmPtr, struct dataelem*arg, double* arg_val)
#endif
{
  
  Int16 res;
  SWord val;
  SWord min;
  SWord max;
  SWord pag;

#ifdef __MC68K__
  res=basc_integ_value(arg,(double*)arg_val);
#else
  double d = ReadUnaligned64((char *)arg_val);
  res = (Int16) d;
#endif
  SclGetScrollBar((ScrollBarPtr)PNO(controlPtr),&val,&min,&max,&pag);
  if (c==0x01)      val=res;
  else if (c==0x02) min=res;
  else if (c==0x03) max=res;
  else if (c==0x04) pag=res;  
    
  SclSetScrollBar((ScrollBarPtr)PNO(controlPtr),val,min,max,pag);
  if(FrmGetActiveForm()==frmPtr)  SclDrawScrollBar( (ScrollBarPtr)PNO(controlPtr));  
}

/**************************************************************************************************/
#ifdef __MC68K__
void verb_setscrollbar()
#else
void verb_setscrollbar(PNOBlock *pnoP)
#endif
{
  Int16 res;
  char c;

#ifdef __MC68K__
  c=find_char();
  find_ctlid(true);
  find_arg_2(); //value
  commonSetScrollbar(c,FrmGetActiveForm(),arg2,(double*)arg2_val);
#else
  Arg arg2;
  double d;
  c=find_char(pnoP);
  find_ctlid(pnoP, true);
  find_arg_PNO(pnoP, &arg2); //value
  commonSetScrollbar(pnoP, c,FrmGetActiveForm(),arg2.dataElem,(double*)arg2.val);
#endif
}
/**************************************************************************************************/

#ifdef __MC68K__
void commonSetMaxChars( struct dataelem*arg, double* arg_val)
{
    FldSetMaxChars((FieldType*)PNO(controlPtr),basc_integ_value( arg,arg_val));
}
#else
void commonSetMaxChars(PNOBlock *pnoP, struct dataelem*arg, double* arg_val)
{
    double d;
    d = ReadUnaligned64((char *) arg_val);
    FldSetMaxChars((FieldType*)PNO(controlPtr), (UInt16) d);
}
#endif


/**************************************************************************************************/
#ifdef __MC68K__
void verb_fieldsetmaxchars()
#else
void verb_fieldsetmaxchars(PNOBlock *pnoP)
#endif
{
#ifdef __MC68K__
  find_ctlid(true);
  find_arg_2(); //#chars
  
  commonSetMaxChars(arg2,(double*)arg2_val);
#else
    Arg chars;
    find_ctlid(pnoP, true);
    find_arg_PNO(pnoP, &chars);
    
    commonSetMaxChars(pnoP, chars.dataElem, (double *)chars.val);
#endif
}
/**************************************************************************************************/

#ifdef __MC68K__
void commonSetSelected( FormPtr frm,ControlPtr controlPtr,Int16 controlType, Int16 where)
#else
void commonSetSelected(PNOBlock *pnoP, FormPtr frm,ControlPtr controlPtr,Int16 controlType, Int16 where)
#endif
{
  Int16 res;
  Int16 i;
  ControlPtr popupObjPtr;
  VoidHand h;
  VoidPtr p;
  struct ObjectData *objectPtr;
#ifdef __MC68K__
#else
  VoidPtr testDataPtr;
#endif
  //res=basc_integ_value(arg2,(double*)arg2_val)-1;
  
  res=where-1;if(res<(-1))res=-1;
  LstSetSelection((ListPtr)controlPtr,res);
  
  for(i=0;i<FrmGetNumberOfObjects(frm);++i)
  {
      if( FrmGetObjectType(frm, i)==frmControlObj)
      {
          popupObjPtr=FrmGetObjectPtr(frm,i);
#ifdef __MC68K__
          if (CtlGlueGetControlStyle(popupObjPtr)==3)
#else
          if (GlueCtlGlueGetControlStyle(pnoP, popupObjPtr)==3)
#endif
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
     h=MemHandleNew(1);
     p=MemHandleLock(h);
     *((char*)p)=0x00;
     CtlSetLabel((ControlPtr)popupObjPtr,p);
  }
  else
  {
#ifdef __MC68K__
     h=MemHandleNew(StrLen(LstGetSelectionText((ListPtr)controlPtr,res))+1);
#else
     h=MemHandleNew(strlen(LstGetSelectionText((ListPtr)controlPtr,res))+1);
#endif
     p=MemHandleLock(h);
#ifdef __MC68K__
     StrCopy((char*)p,LstGetSelectionText((ListPtr)controlPtr,res));
#else
     {
        char *s, *d;
        d = (char *)p;
        s = LstGetSelectionText((ListPtr)controlPtr,res);
        while (*s) *d++ = *s++;
        *d = '\0';
     }
#endif
     CtlSetLabel((ControlPtr)popupObjPtr,p);
  }
  
  //objectPtr=locateObjectPtr(popupObjPtr->id);
  //objectPtr=locateObjectPtr(FrmGetObjectId(frm,FrmGetObjectIndexFromPtr(frm,(ListPtr)popupObjPtr)));  //GHGlue
#ifdef __MC68K__
  objectPtr=locateObjectPtr(miscFrmGetObjectIdFromPtr(frm,(ListPtr)popupObjPtr));  //GHGlue
#else
  objectPtr=locateObjectPtr(pnoP, miscFrmGetObjectIdFromPtr(frm,(ListPtr)popupObjPtr));  //GHGlue
#endif
  
#ifdef __MC68K__
  if(objectPtr->dataPtr!=0)
  {
      MiscPtrFree(objectPtr->dataPtr);   
      
  }
#else
  testDataPtr = (VoidPtr) ReadUnaligned32(&(objectPtr -> dataPtr));
  if (testDataPtr != 0)
  {
      MemPtrFree(testDataPtr);
  }
#endif
#ifdef __MC68K__
  objectPtr->dataPtr=p;
#else
  WriteUnaligned32(&(objectPtr -> dataPtr), p);
#endif
  
  if(frm==FrmGetActiveForm()) CtlDrawControl((ControlPtr)popupObjPtr);  
  
}



/**************************************************************************************************/
#ifdef __MC68K__
void commonSetText(FormPtr frmPtr,int controlType, char*text)
#else
void commonSetText(PNOBlock *pnoP, FormPtr frmPtr,UInt16 controlType, char*text) //EMP
#endif
{
  struct ObjectData * objectPtr;
#ifdef __MC68K__
#else
  VoidPtr dataPtr;
#endif
  VoidHand h;
  VoidPtr p;
 
  RectangleType r; 
  FontID curFont;
  VoidPtr oldPtr;
  RectangleType r1;  //GHGlue
  
  Word idx;              //added 5.20.2000  
 
  VoidHand oldHand;
  Int16 res;
  Int16 i;
  

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

#ifdef __MC68K__   
   h=MiscHandleNew(StrLen(text)+1,"setLab");
  p=MiscHandleLock(h);
  StrCopy((char*)p,text);
#else
   h=MemHandleNew(strlen(text)+1);
  p=MemHandleLock(h);
  strcpy((char*)p,text);
#endif

//StrPrintF(debug,"setting label now to %s",text);
//SysFatalAlert(debug);
  
  oldPtr=(VoidPtr)CtlGetLabel((ControlType*)PNO(controlPtr));   //5.10.2000
  CtlSetLabel((ControlType*)PNO(controlPtr),(char*)p);
 
#ifdef __MC68K__
  objectPtr = locateObjectPtr(PNO(controlid));
#else
  objectPtr = locateObjectPtr(pnoP, PNO(controlid));
#endif

#ifdef __MC68K__
  if( objectPtr->dataPtr!=0)
#else
  dataPtr = (VoidPtr) ReadUnaligned32(&(objectPtr->dataPtr));
  if (dataPtr != NULL);
#endif
  {
#ifdef __MC68K__
     MiscPtrFree(objectPtr->dataPtr);
#else
     MemPtrFree(dataPtr);
#endif
  }
#ifdef __MC68K__
  objectPtr->dataPtr=p; 
#else
  WriteUnaligned32(&(objectPtr -> dataPtr), (unsigned long) p);
#endif
  
  
  CtlDrawControl ((ControlType*)PNO(controlPtr));
  return ;
itsALabel:
  //treat label ctls differently
  //the rule is that a label control cannot have its string length exceeded
  //also, you have to erase the labels bounded area to get rid of old label
  //curFont = FntSetFont(((FormLabelType*)controlPtr)->fontID); //GHGlue
  
#ifdef __MC68K__
  curFont = FntSetFont(FrmGlueGetLabelFont(FrmGetActiveForm(), PNO(controlid))); //GHGlue
#else
  curFont = GlueFrmGlueGetLabelFont(pnoP, FrmGetActiveForm(), PNO(controlid));
  curFont = FntSetFont(curFont); //GHGlue
#endif

  
  FrmGetObjectBounds(frmPtr, FrmGetObjectIndex(frmPtr,PNO(controlid)), &r1);

  RctSetRectangle(&r,r1.topLeft.x,
                     r1.topLeft.y,
                     FntCharsWidth(FrmGetLabel(frmPtr, PNO(controlid)),
#ifdef __MC68K__
                            StrLen(FrmGetLabel(frmPtr, PNO(controlid)))),
#else
                            strlen(FrmGetLabel(frmPtr, PNO(controlid)))),
#endif
                     FntCharHeight());
  WinEraseRectangle(&r,0);
  FntSetFont(curFont);

#ifdef __MC68K__
  h=MiscHandleNew(StrLen(FrmGetLabel(frmPtr, PNO(controlid)))+1,"setLab2");
  p=MiscHandleLock(h);
#else
  h=MemHandleNew(strlen(FrmGetLabel(frmPtr,PNO(controlid)))+1);
  p=MemHandleLock(h);
#endif

  {
  	Int16 k;
  	for (k = 0; k < MemPtrSize(p) - 1; ++k) ((char *)p)[k] = ' ';
  	((char *)p)[k] = '\0';
  }

#ifdef __MC68K__
  if( StrLen(text)<MemPtrSize(p))  MemMove(p,text,StrLen(text));
  else                                 MemMove(p,text,MemPtrSize(p)-1);
#else
  if( strlen(text)<MemPtrSize(p))  MemMove(p,text,strlen(text));
  else                                 MemMove(p,text,MemPtrSize(p)-1);
#endif

//StrPrintF(debug,"newstring=%s  len=%d",p,StrLen(p));
//SysFatalAlert(debug);

  FrmCopyLabel( frmPtr,PNO(controlid), (char*)p);

#ifdef __MC68K__
  objectPtr=locateObjectPtr(PNO(controlid));
#else
  objectPtr=locateObjectPtr(pnoP, PNO(controlid));
#endif

#ifdef __MC68K__
  if( objectPtr->dataPtr!=0)
#else
  dataPtr = (VoidPtr) ReadUnaligned32(objectPtr -> dataPtr);
  if (dataPtr)
#endif
  {
#ifdef __MC68K__
     MiscPtrFree(objectPtr->dataPtr);
#else
        MemPtrFree(dataPtr);
#endif
  }
#ifdef __MC68K__
  objectPtr->dataPtr=p;
#else
  WriteUnaligned32(&(objectPtr -> dataPtr), p);
#endif

  return;
itsAField:

   commonSetFieldTextRoutine(PNO(controlPtr), PNO(controlid), text);
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
#ifdef __MC68K__
void verb_controlsetlabel()  //also controlsettext
#else
void verb_controlsetlabel(PNOBlock *pnoP) // EMP
#endif
{
  struct ObjectData * objectPtr;
  VoidHand h;
  VoidPtr p;
  char ctlType;
  Int16 controlType;
  RectangleType r; 
  FontID curFont;
  VoidPtr oldPtr;
  RectangleType r1;  //GHGlue
  Int16 pos;
  FormPtr frmPtr;
  
#ifdef __MC68K__
  find_ctlid(true);
  find_arg_1();
  ctlType=find_char();
  frmPtr=FrmGetActiveForm();
  pos=FrmGetObjectIndex(frmPtr, PNO(controlid));
  controlType=FrmGetObjectType(frmPtr,pos);
  commonSetText(frmPtr,controlType,arg1_val);
#else
  Arg arg1;
  find_ctlid(pnoP, true);
  find_arg_PNO(pnoP, &arg1);
  ctlType=find_char(pnoP);
  frmPtr=FrmGetActiveForm();
  pos=FrmGetObjectIndex(frmPtr, PNO(controlid));
  controlType=FrmGetObjectType(frmPtr,pos);
  commonSetText(pnoP, frmPtr,controlType,arg1.val);
#endif
}

/**************************************************************************************************/
#ifdef __MC68K__
void commonSetStatus(FormPtr frmPtr,Int16 controlType, Int16 stat)
#else
void commonSetStatus(PNOBlock *pnoP, FormPtr frmPtr,Int16 controlType, Int16 stat)
#endif
{
    CtlSetValue((ControlType*)PNO(controlPtr),stat);
    if(frmPtr==FrmGetActiveForm()) CtlDrawControl ((ControlType*)PNO(controlPtr));
}
/**************************************************************************************************/
#ifdef __MC68K__
void verb_controlsetstatus()
#else
void verb_controlsetstatus(PNOBlock *pnoP)
#endif
{
  Int16 res;

#ifdef __MC68K__
  find_ctlid(true);
  res=find_integer();
  commonSetStatus(FrmGetActiveForm(), frmControlObj, res);
#else
  find_ctlid(pnoP, true);
  res=find_integer(pnoP);
  commonSetStatus(pnoP, FrmGetActiveForm(), frmControlObj, res);
#endif
}
/**************************************************************************************************/
#ifdef __MC68K__
void verb_controlsetstatusNew()
#else
void verb_controlsetstatusNew(PNOBlock *pnoP)
#endif
{
  //same as regular verb_controlsetstatus except a varname is used
  Int16 res;
  
#ifdef __MC68K__
  find_ctlid(true);
  find_arg_1();
  res=basc_integ_value( arg1,(double*)arg1_val);
  commonSetStatus(FrmGetActiveForm(),frmControlObj,res);
#else
    Arg arg1;
    double d;
    find_ctlid(pnoP, true);
    find_arg_PNO(pnoP, &arg1);
    d = ReadUnaligned64(arg1.val);
    res = (Int16)d;
    commonSetStatus(pnoP, FrmGetActiveForm(),frmControlObj,res);
#endif
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
#ifdef __MC68K__
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
#else
void commonErrorWrongType(PNOBlock *pnoP, char *typ)
{
    char msg[80];
    char *s, *d;
    d = msg;
    s = "Wrong type of variable used in call to set property for '";
    while (*s) *d++ = *s++;
    s = typ;
    while (*s) *d++ = *s++;
    *d++ = '\'';
    *d = '\0';
    SysFatalAlert(msg);
    GlueErrThrow(pnoP, -1);                 //inserted 05212003 
}
/**************************************************************************************************/
void commonErrorWrongTypeOnGet(PNOBlock *pnoP, char *typ)
{
    char msg[80];
    char *s, *d;
    d = msg;
    s = "Wrong type of variable used in call to get property for '";
    while (*s) *d++ = *s++;
    s = typ;
    while (*s) *d++ = *s++;
    *d++ = '\'';
    *d = '\0';
    SysFatalAlert(msg);
    GlueErrThrow(pnoP, -1);                 //inserted 05212003 
}
/**************************************************************************************************/
commonErrorWrongCtltype(PNOBlock *pnoP, char * propName,Int16 controlType)
{
    char msg[80];
    char *s, *d;
    d = msg;
    s = "Cannot set property (";
    while (*s) *d++ = *s++;
    s = propName;
    while (*s) *d++ = *s++;
    s = ") on control type ";
    while (*s) *d++ = *s++;
    StrIToA(d, controlType);
    SysFatalAlert(msg);
    GlueErrThrow(pnoP, -1);                 //inserted 05212003 
}
/**************************************************************************************************/
commonErrorWrongCtltypeOnGet(PNOBlock *pnoP, char * propName,Int16 controlType)
{
    char msg[80];
    char *s, *d;
    d = msg;
    s = "Cannot get property (";
    while (*s) *d++ = *s++;
    s = propName;
    while (*s) *d++ = *s++;
    s = ") on control type ";
    while (*s) *d++ = *s++;
    StrIToA(d, controlType);
    SysFatalAlert(msg);
    GlueErrThrow(pnoP, -1);                 //inserted 05212003 
}
#endif

/**************************************************************************************************/
#ifdef __MC68K__
FormPtr  findFormTheControlIsOn(Int16 ctlid)
#else
FormPtr  findFormTheControlIsOn(PNOBlock *pnoP, Int16 ctlid)
#endif
{
    Word j;
    Word i;
    UInt16 new_x,new_y;
    struct ViewData * viewPtr;  
    FormPtr frmPtr;
    Int16 id;

    for(j=0;j< PNO(view_cnt);++j)
    {
        viewPtr=(struct ViewData*)((char*)PNO(viewElemsPtr)+j*sizeof(viewExample));  //point to this view's data

        id = viewPtr -> id;
#ifndef __MC68K__
        id = ByteSwap16(id);
#endif


        frmPtr = FrmGetFormPtr(id);
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
#ifdef __MC68K__
Int16 findControlsPositionOnForm(FormPtr * frmPtr,char * controlname)
#else
Int16 findControlsPositionOnForm(PNOBlock *pnoP, FormPtr * frmPtr,char * controlname)  //EMP
#endif
{
    
    Int16 cnt;
    Int16 i;
    Int16 j;
    char*ad;
    char *p2;
    VoidHand h2;
    char name[256];
    UInt16 ID;
    //find_arg_1();   //name of control
//StrPrintF(debug,"ctlname to search for=%s",arg1_val);
//dbug(debug);
	//frmPtr=FrmGetActiveForm();
	
    Int16 new_x,new_y;
    struct ViewData * viewPtr;  
    
    
    for(j=0;j< PNO(view_cnt);++j)
    {
#ifdef __MC68K__
       viewPtr=(struct ViewData*)((char*)PNO(viewElemsPtr)+j*sizeof(viewExample));  //point to this view's data
       *frmPtr=FrmGetFormPtr(viewPtr->id);
	    h2=MiscDmGetResource('olst',viewPtr->id,"olst");  //read the forms object list of name
#else
        Int16 vid;
        viewPtr=(struct ViewData*)((char*)PNO(viewElemsPtr)+j*sizeof(viewExample));  //point to this view's data

        vid = viewPtr->id;
        vid = ByteSwap16(vid);
        *frmPtr = FrmGetFormPtr(vid);

	    h2 = DmGetResource('olst',vid);  //read the forms object list of name
#endif
	    if(h2==0)
	    {
	       goto cantFindCtl;
	    }
#ifdef __MC68K__
	    p2=MiscHandleLock(h2);
#else
        p2 = MemHandleLock(h2);
#endif

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
#ifdef __MC68K__
  StrPrintF(debug,"Illegal object name used = %s",controlname);
  SysFatalAlert(debug);
  ErrThrow(-1);                 //inserted 05212003
#else
  {
    char *d;
    char debug[60];
    d = strcpy(debug, "Illegal object name used = ");
    strcpy(d, controlname);
    SysFatalAlert(debug);
    GlueErrThrow(pnoP, -1);
  }
#endif	    
}

/**************************************************************************************************/

#ifdef __MC68K__
void verb_setGeneralProperty()
#else
void verb_setGeneralProperty(PNOBlock *pnoP)
#endif
{
  UInt16 minValue;  //added 04012005
  UInt16 maxValue;  //added 04012005
  UInt16 pageSize;  //added 04012005
  UInt16 curValue;  //added 04012005
  ControlStyleType type;  //added 04012005 
  struct ObjectData *obj;         //07052005
  RectangleType bounds;
  Int16 controlType;
  Int16 pos;
  char c;
  Int16 propId;
  Boolean found;
  double d;
#ifndef __MC68K__
  Arg arg2, arg3;
#endif

  
  FormPtr frmPtr;        //added 5.20.2000 
//dbug("in set text"); 

#ifdef __MC68K__
   c=find_char();   //type of control identifier
#else
    c = find_char(pnoP);
#endif

   switch(c)
   {
      case 'i':  //ctlid

#ifdef __MC68K__
        found=find_ctlid(true);
#else
        found=find_ctlid(pnoP, true);

#endif

        //if(found==false) return;  //probably a bitmap that can't use by id
#ifdef __MC68K__
        frmPtr=findFormTheControlIsOn(PNO(controlid));
#else
        frmPtr=findFormTheControlIsOn(pnoP, PNO(controlid));
#endif

        pos=FrmGetObjectIndex(frmPtr,PNO(controlid));

        break;
      case 'v':  //variable containing name
#ifdef __MC68K__
        find_arg_2();      //variable containing name
#else
        find_arg_PNO(pnoP, &arg2);
#endif


        frmPtr=FrmGetActiveForm();
#ifdef __MC68K__
        pos=findControlsPositionOnForm(&frmPtr,arg2_val);
#else
        pos=findControlsPositionOnForm(pnoP, &frmPtr, arg2.val);
#endif
//StrPrintF(debug,"name=%s posOnForm=%d",arg2_val,pos);
//dbug(debug);
        goto havePosition;
        break;
      case 'p':  //position of ctl on form
#ifdef __MC68K__
        find_arg_2();      //position of control on form
        pos = integ_value( arg2, (double *)arg2_val ); 
#else
        find_arg_PNO(pnoP, &arg2);
        pos = ReadUnaligned64(arg2.val);
#endif
        frmPtr=FrmGetActiveForm();
havePosition:
        
	    if(pos>FrmGetNumberOfObjects(frmPtr)-1)
	    {
	       SysFatalAlert("Control position too high.");
#ifdef __MC68K__
	       ErrThrow(-1);                 //inserted 05212003
#else
           GlueErrThrow(pnoP, -1);
#endif
	    }

#ifdef __MC68K__
   		obj= locateObjectPtr(PNO(controlid));   //07052005
#else
   		obj= locateObjectPtr(pnoP, PNO(controlid));   //07052005
#endif
	    PNO(controlPtr)=((ControlType*)FrmGetObjectPtr(frmPtr,pos));
	    PNO(controlid)=FrmGetObjectId(frmPtr,pos);
	    break;
   }

   controlType=FrmGetObjectType(frmPtr,pos);

#ifdef __MC68K__
   propId=find_integer();          //property type identifier #
   find_arg_3();          //new property value to assign
#else
   propId=find_integer(pnoP);
   find_arg_PNO(pnoP, &arg3);  // not working?
#endif

   switch(propId)
   {
       case 0:  //text
//StrPrintF(debug,"set text  type=%d  text=%s",controlType,arg3_val);
//dbug(debug);
          if( (controlType!=frmControlObj)&&(controlType!=frmFieldObj)   //added 09242003
          &&(controlType!=frmLabelObj)&&(controlType!=frmTableObj))      //added 09242003 
#ifdef __MC68K__
            commonErrorWrongCtltype("text",controlType);
#else
            commonErrorWrongCtltype(pnoP, "text",controlType);
#endif
          else
          {
#ifdef __MC68K__
            if(arg3->kind == 's')
            {
               if(controlType!=frmTableObj)                        //added 09242003
               commonSetText( frmPtr,controlType, arg3_val);
               else  gridSetSelectedText(   frmPtr,PNO(controlPtr), arg3_val); //added 09242003       
            }
            else commonErrorWrongType("text");
#else
            if(arg3.dataElem->kind == 's')
            {
               if(controlType!=frmTableObj)                        //added 09242003
               commonSetText(pnoP, frmPtr,controlType, arg3.val);
               else  gridSetSelectedText(pnoP,   frmPtr,PNO(controlPtr), arg3.val); //added 09242003       
            }
            else commonErrorWrongType(pnoP, "text");
#endif
          }
          break; 
       case 1:  //status
          if(controlType  != frmControlObj)
#ifdef __MC68K__
            commonErrorWrongCtltype("status",controlType);
#else
            commonErrorWrongCtltype(pnoP, "status",controlType);
#endif
          else
          {
#ifdef __MC68K__
            if(arg3->kind != 's')
                commonSetStatus( frmPtr,controlType, basc_integ_value( arg3,(double*)arg3_val));
            else commonErrorWrongType("status");
#else
            if(arg3.dataElem -> kind != 's')
            {
                d = ReadUnaligned64(arg3.val);
                commonSetStatus(pnoP, frmPtr,controlType, (Int16) d);
            }
            else commonErrorWrongType(pnoP, "status");
#endif
	      }
	      
	      break; 
       case 2:  //selected
          if( (controlType!=frmListObj)&&(controlType!=frmControlObj))
#ifdef __MC68K__
            commonErrorWrongCtltype("selectd",controlType);
#else
            commonErrorWrongCtltype(pnoP, "selectd",controlType);
#endif
          else
          {
#ifdef __MC68K__
            if(arg3->kind != 's')
#else
            if(arg3.dataElem -> kind != 's')
#endif
            {
                if (controlType==frmListObj)
#ifdef __MC68K__
                    commonSetSelected(frmPtr,PNO(controlPtr),controlType, basc_integ_value(arg3,(double*)arg3_val));       
#else
                {
                    d = ReadUnaligned64(arg3.val);
                    commonSetSelected(pnoP, frmPtr,PNO(controlPtr), controlType, (Int16) d);       
                }
#endif
                else
                {
                     //must point to list part of popup
                     PNO(controlPtr) = ((ControlType*)FrmGetObjectPtr(frmPtr,pos+1));
	                 PNO(controlid) = FrmGetObjectId(frmPtr,pos+1);
#ifdef __MC68K__
                    commonSetSelected( frmPtr,PNO(controlPtr),controlType, basc_integ_value(arg3,(double*)arg3_val));
#else
                    d = ReadUnaligned64((char *) arg3.val);
                    commonSetSelected(pnoP, frmPtr, PNO(controlPtr) ,controlType, (Int16) d);
#endif
                }     
            }    
            else
#ifdef __MC68K__
            commonErrorWrongType("selected");
#else
            commonErrorWrongType(pnoP, "selected");
#endif
          }
          break;
       case 3:  //maxChars
          if(controlType  != frmFieldObj)
#ifdef __MC68K__
            commonErrorWrongCtltype("maxChars",controlType);
#else
            commonErrorWrongCtltype(pnoP, "maxChars",controlType);
#endif
          else
          {
#ifdef __MC68K__
            if(arg3->kind != 's') commonSetMaxChars(arg3,(double*)arg3_val );
            else commonErrorWrongType("maxChars");
#else
            if (arg3.dataElem -> kind != 's')
            {
                commonSetMaxChars(pnoP, arg3.dataElem,(double*) arg3.val);
            }
            else commonErrorWrongType(pnoP, "maxChars");
#endif
          }
          break;
       case 4:  //current
       case 94:
          //modified 04012005
          

          {
          		if(controlType  != frmScrollBarObj)
#ifdef __MC68K__
          			commonErrorWrongCtltype("current",controlType);
#else
          			commonErrorWrongCtltype(pnoP, "current",controlType);
#endif
          		else
         		{
#ifdef __MC68K__
           			if(arg3->kind != 's')
            			commonSetScrollbar(0x01,frmPtr,arg3,(double*)arg3_val);
            		else
            			commonErrorWrongType("current");
#else
           			if(arg3.dataElem->kind != 's')
            			commonSetScrollbar(pnoP, 0x01,frmPtr,arg3.dataElem,(double*)arg3.val);
            		else
            			commonErrorWrongType(pnoP, "current");
#endif
          		}
          }
          break; 
       case 5:  //min
       case 95:
            //modified 04012005

#ifdef __MC68K__
           type = CtlGlueGetControlStyle((ControlType*)(PNO(controlPtr))); 
#else
           type = GlueCtlGlueGetControlStyle(pnoP, (ControlType*)(PNO(controlPtr))); 
#endif
           if  ((controlType==frmControlObj)&&((type==sliderCtl) || (type==feedbackSliderCtl) ))   //added 09242003
           {
               //it's a slider ctl
#ifdef __MC68K__
               if(arg3->kind != 's')
#else
			   if(arg3.dataElem->kind != 's')
#endif
               {
                  CtlGetSliderValues ((ControlType*)(PNO(controlPtr)),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue);
#ifdef __MC68K__ 
                  minValue =  *(double*)arg3_val;
#else
                  minValue =  *(double*)arg3.val;
                  minValue = ByteSwap13(minValue);
#endif
                  CtlSetSliderValues ((ControlType*)(PNO(controlPtr)),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue);
			   }
               else
#ifdef __MC68K__
               commonErrorWrongType("minValue");
#else
               commonErrorWrongType(pnoP, "minValue");
#endif            
          }
          else
          {
          	  if(controlType  != frmScrollBarObj )
#ifdef __MC68K__
          	  	commonErrorWrongCtltype("min",controlType);
#else
          	  	commonErrorWrongCtltype(pnoP, "min",controlType);
#endif
          	  else
              {
#ifdef __MC68K__
                 if(arg3->kind != 's') commonSetScrollbar(0x02,frmPtr,arg3,(double*)arg3_val);
                 else commonErrorWrongType("min");
#else
                 if(arg3.dataElem->kind != 's') commonSetScrollbar(pnoP, 0x02,frmPtr,arg3.dataElem,(double*)arg3.val);
                 else commonErrorWrongType(pnoP, "min");
#endif
              }
          }
          break; 
       case 6:  //max
       case 96:
            //modified 04012005
#ifdef __MC68K__
           type = CtlGlueGetControlStyle((ControlType*)(PNO(controlPtr)));
#else
           type = GlueCtlGlueGetControlStyle(pnoP, (ControlType*)(PNO(controlPtr))); 
#endif

           if  ((controlType==frmControlObj)&&((type==sliderCtl) || (type==feedbackSliderCtl) ))   //added 09242003
           {
               //it's a slider ctl
#ifdef __MC68K__
               if(arg3->kind != 's')
#else
			   if(arg3.dataElem->kind != 's')
#endif
               {
                  CtlGetSliderValues ((ControlType*)(PNO(controlPtr)),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue);
#ifdef __MC68K__ 
                  maxValue =  *(double*)arg3_val;
#else
                  maxValue =  *(double*)arg3.val;
                  maxValue = ByteSwap16(maxValue);
#endif
                  CtlSetSliderValues ((ControlType*)(PNO(controlPtr)),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue);
			   }
               else
#ifdef __MC68K__
               commonErrorWrongType("maxValue");
#else
               commonErrorWrongType(pnoP, "maxValue");
#endif            
          }
          else
          {
          	  if(controlType  != frmScrollBarObj )
#ifdef __MC68K__
          	  	commonErrorWrongCtltype("max",controlType);
#else
          	  	commonErrorWrongCtltype(pnoP, "max",controlType);
#endif
          	  else
              {
#ifdef __MC68K__
                 if(arg3->kind != 's') commonSetScrollbar(0x03,frmPtr,arg3,(double*)arg3_val);
                 else commonErrorWrongType("max");
#else
                if(arg3.dataElem->kind != 's') commonSetScrollbar(pnoP, 0x03,frmPtr,arg3.dataElem,(double*)arg3.val);
                 else commonErrorWrongType(pnoP, "max");
#endif
              }
          }
          break; 
       case 7:  //pageSize
       case 97:
            //modified 04012005
            
#ifdef __MC68K__
           type = CtlGlueGetControlStyle((ControlType*)(PNO(controlPtr))); 
#else
           type = GlueCtlGlueGetControlStyle(pnoP, (ControlType*)(PNO(controlPtr))); 
#endif
           if  ((controlType==frmControlObj)&&((type==sliderCtl) || (type==feedbackSliderCtl) ))   //added 09242003
           {
               //it's a slider ctl
#ifdef __MC68K__
               if(arg3->kind != 's')
#else
			   if(arg3.dataElem->kind != 's')
#endif
               {
                  CtlGetSliderValues ((ControlType*)(PNO(controlPtr)),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue);
#ifdef __MC68K__ 
                  pageSize =  *(double*)arg3_val;
#else
                  pageSize =  *(double*)arg3.val;
                  pageSize = ByteSwap16(pageSize);
#endif
                  CtlSetSliderValues ((ControlType*)(PNO(controlPtr)),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue);
			   }
               else
#ifdef __MC68K__
               commonErrorWrongType("pageSizeValue");
#else
               commonErrorWrongType(pnoP, "pageSizeValue");
#endif            
          }
          else
          {
          	  if(controlType  != frmScrollBarObj )
#ifdef __MC68K__
          	  	commonErrorWrongCtltype("pageSize",controlType);
#else
          	  	commonErrorWrongCtltype(pnoP, "pageSize",controlType);
#endif
          	  else
              {
#ifdef __MC68K__
                 if(arg3->kind != 's') commonSetScrollbar(0x04,frmPtr,arg3,(double*)arg3_val);
                 else commonErrorWrongType("pageSize");
#else
                 if(arg3.dataElem->kind != 's') commonSetScrollbar(pnoP, 0x04,frmPtr,arg3.dataElem,(double*)arg3.val);
                 else commonErrorWrongType(pnoP, "pageSize");
#endif
              }
          }
          break; 
        //start additions 09242003
         case 48:  //selectedCol
#ifdef __MC68K__
          if(controlType  != frmTableObj) commonErrorWrongCtltype("Col",controlType);
#else
          if(controlType  != frmTableObj) commonErrorWrongCtltype(pnoP, "Col",controlType);
#endif
          else
          {
#ifdef __MC68K__
            if(arg3->kind != 's') gridSetSelectedCol(frmPtr,PNO(controlPtr),(double*)arg3_val);
            else commonErrorWrongType("Col");
#else
			if (arg3.dataElem -> kind != 's') gridSetSelectedCol(pnoP, frmPtr, PNO(controlPtr), (double*)arg3.val);
			else commonErrorWrongType(pnoP, "Col");
#endif
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
#ifdef __MC68K__
          if(controlType  != frmTableObj) commonErrorWrongCtltype("ColWidth",controlType);
#else
          if(controlType  != frmTableObj) commonErrorWrongCtltype(pnoP, "ColWidth",controlType);
#endif
          else
          {
#ifdef __MC68K__
            if(arg3->kind != 's') gridSetColWidth(frmPtr,PNO(controlPtr),(double*)arg3_val);
            else commonErrorWrongType("ColWidth");
#else
			if (arg3.dataElem -> kind != 's') gridSetColWidth(pnoP, frmPtr,PNO(controlPtr),(double*)arg3.val);
			else commonErrorWrongType(pnoP, "ColWidth");
#endif
          }
          break;
        case 51:  //selectedRow
#ifdef __MC68K__
          if(controlType  != frmTableObj) commonErrorWrongCtltype("Row",controlType);
#else
          if(controlType  != frmTableObj) commonErrorWrongCtltype(pnoP, "Row",controlType);
#endif
          else
          {
#ifdef __MC68K__
            if(arg3->kind != 's') gridSetSelectedRow(frmPtr,PNO(controlPtr),(double*)arg3_val);
            else commonErrorWrongType("Row");
#else
			if (arg3.dataElem -> kind != 's') gridSetSelectedRow(pnoP, frmPtr,PNO(controlPtr),(double*)arg3.val);
			else commonErrorWrongType(pnoP, "Row");
#endif
          }
          break;
        case 52:  //Rows
#ifdef __MC68K__
          if(controlType  != frmTableObj) commonErrorWrongCtltype("Rows",controlType);
#else
          if(controlType  != frmTableObj) commonErrorWrongCtltype(pnoP, "Rows",controlType);
#endif
          else
          {
#ifdef __MC68K__
            if(arg3->kind != 's') gridSetRows(frmPtr,PNO(controlPtr),(double*)arg3_val);
            else commonErrorWrongType("Rows");
#else
			if (arg3.dataElem -> kind != 's') gridSetRows(pnoP, frmPtr,PNO(controlPtr),(double*)arg3.val);
			else commonErrorWrongType(pnoP, "Rows");
#endif
          }
          break;
        /*
        case 53:  //VisibleRows
          if(controlType  != frmTableObj) commonErrorWrongCtltype("VisibleRows",controlType);
          else
          {
            if(arg3->kind != 's') gridSetVisibleRows(frmPtr,PNO(controlPtr),arg3,(double*)arg3_val);
            else commonErrorWrongType("VisibleRows");
          }
          break;
        */
        case 54:  //cellMatrix
#ifdef __MC68K__
          if(controlType  != frmTableObj) commonErrorWrongCtltype("CellMatrix",controlType);
#else
          if(controlType  != frmTableObj) commonErrorWrongCtltype(pnoP, "CellMatrix",controlType);
#endif
          else
          {
            //note:arg3 is row#
//StrPrintF(debug,"setting cell text -- arg3=%s",arg3_val);
//SysFatalAlert(debug);
#ifdef __MC68K__
            if(arg3->kind != 's') gridSetCellMatrix(frmPtr,PNO(controlPtr), arg3_val);
            else commonErrorWrongType("cellMatrix");
#else
			if(arg3.dataElem -> kind != 's') gridSetCellMatrix(pnoP, frmPtr,PNO(controlPtr), (double *)arg3.val);
			else commonErrorWrongType(pnoP, "cellMatrix");
#endif
          }
          break;
        case 55: //valueMatrix
#ifdef __MC68K__
          if(controlType  != frmTableObj) commonErrorWrongCtltype("valueMatrix",controlType);
#else
          if(controlType  != frmTableObj) commonErrorWrongCtltype(pnoP, "valueMatrix",controlType);
#endif
          else
          {
#ifdef __MC68K__
            if(arg3->kind != 's') gridSetValueMatrix(frmPtr,PNO(controlPtr) ,(double*)arg3_val);
            else commonErrorWrongType("valueMatrix");
#else
			if(arg3.dataElem -> kind != 's') gridSetValueMatrix(frmPtr,PNO(controlPtr),(double*)arg3.val);
			else commonErrorWrongType(pnoP, "valueMatrix");
#endif
          }
          break;
        case 56:  //value
           //start additions 07122005
           if  (controlType==frmControlObj)
           {
#ifdef __MC68K__
           		type = CtlGlueGetControlStyle((ControlType*)(PNO(controlPtr))); 
#else
          		type = GlueCtlGlueGetControlStyle(pnoP, (ControlType*)(PNO(controlPtr))); 
#endif
               if ((type==sliderCtl) || (type==feedbackSliderCtl)  )    
               {
                   //it's a slider ctl
#ifdef __MC68K__
                   if(arg3->kind != 's')
#else
					if (arg3.dataElem->kind != 's')
#endif
                   {
                      CtlGetSliderValues ((ControlType*)(PNO(controlPtr)),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue);
#ifdef __MC68K__ 
                      curValue =  basc_integ_value(arg3,(double*)arg3_val);
#else
                      curValue =  *(double*)arg3.val;
                      curValue = ByteSwap16(curValue);
#endif
                      CtlSetSliderValues ((ControlType*)(PNO(controlPtr)),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue);
			       }
#ifdef __MC68K__
                   else commonErrorWrongType("Value");   
#else
                   else commonErrorWrongType(pnoP, "Value");   
#endif
               }   
            
          }
          else
          {
                if(controlType  == frmScrollBarObj)  
                {
#ifdef __MC68K__
                	if(arg3->kind != 's') commonSetScrollbar(0x01,frmPtr,arg3,(double*)arg3_val);
#else
                	if(arg3.dataElem->kind != 's') commonSetScrollbar(pnoP, 0x01,frmPtr,arg3.dataElem,(double*)arg3.val);

#endif
            		else
#ifdef __MC68K__
            		commonErrorWrongType("Value");
#else
					commonErrorWrongType(pnoP, "Value");
#endif
          		}
          		else
          		{
          		//end additions 07122005
#ifdef __MC68K__
          if(controlType  != frmTableObj) commonErrorWrongCtltype("Value",controlType);
#else
          if(controlType  != frmTableObj) commonErrorWrongCtltype(pnoP, "Value",controlType);
#endif
          else
          {
#ifdef __MC68K__
            if(arg3->kind != 's') gridSetSelectedValue(frmPtr,PNO(controlPtr), (double*)arg3_val);
            else commonErrorWrongType("Value");
#else
			if (arg3.dataElem -> kind != 's') gridSetSelectedValue(frmPtr,PNO(controlPtr),(double*)arg3.val);
			else commonErrorWrongType(pnoP, "Value");
#endif
          }
                }                                //07122005
          }                                      //07122005
          
          break;
        case 57:  //rowData
#ifdef __MC68K__
          if(controlType  != frmTableObj) commonErrorWrongCtltype("rowData",controlType);
#else
		  if(controlType != frmTableObj) commonErrorWrongCtltype(pnoP, "rowData", controlType);
#endif
          else
          {
#ifdef __MC68K__
            if(arg3->kind != 's') gridSetRowData(frmPtr,PNO(controlPtr), (double*)arg3_val);
            else commonErrorWrongType("RowData");
#else
			if(arg3.dataElem -> kind != 's') gridSetRowData(pnoP, frmPtr,PNO(controlPtr), (double*)arg3.val);
			else commonErrorWrongType(pnoP, "RowData");
#endif
          }
          break;
          //start additions 02062004
          case 58:  //toprow
#ifdef __MC68K__
          if(controlType  != frmTableObj) commonErrorWrongCtltype("topRow",controlType);
#else
		  if(controlType != frmTableObj) commonErrorWrongCtltype(pnoP, "topRow", controlType);
#endif
          else
          {
#ifdef __MC68K__
            if(arg3->kind != 's') gridSetTopRow(frmPtr,PNO(controlPtr), (double*)arg3_val);
            else commonErrorWrongType("TopRow");
#else
			if(arg3.dataElem -> kind != 's') gridSetTopRow(frmPtr,PNO(controlPtr), (double*)arg3.val);
			else commonErrorWrongType(pnoP, "TopRow");
#endif
          }
          break;
          //end additions 02062004
       //start additions 04012005
        
         case 59: //fontMatrix
          if(controlType  != frmTableObj)
#ifdef __MC68K__
          commonErrorWrongCtltype("fontMatrix",controlType);
#else
          commonErrorWrongCtltype(pnoP, "fontMatrix",controlType);
#endif
          else
          {
#ifdef __MC68K__
            if(arg3->kind != 's') gridSetFontMatrix(frmPtr,PNO(controlPtr) ,(double*)arg3_val);
            else
          commonErrorWrongCtltype("fontMatrix",controlType);
#else
            if(arg3.dataElem->kind != 's') gridSetFontMatrix(frmPtr,PNO(controlPtr) ,(double*)arg3.val);
            else
          commonErrorWrongCtltype(pnoP, "fontMatrix",controlType);
#endif
          }
          break;
        case 80:  //left
        
#ifdef __MC68K__
            if(arg3->kind != 's')
            {
                FrmGetObjectBounds (frmPtr,pos,&bounds);
                  if(FrmGetObjectType(frmPtr,pos)==frmTableObj)            //07052005
                  {                                                        //07052005
                      WinEraseRectangle (&bounds,0);                       //07052005
                  }                                                        //07052005 
                  commonShowHide(0x00,frmPtr,FrmGetObjectId(frmPtr,pos));  //07052005
                   if( obj->type == frmTableObj)                           //07052005
                   {                                                       //07052005
                         obj->origGridBounds.topLeft.x = bounds.topLeft.x; //07052005
                   }                                                       //07052005
                  
                bounds.topLeft.x=basc_integ_value(arg3,(double*)arg3_val);
                FrmSetObjectBounds (frmPtr,pos, &bounds);
            }
            else
            commonErrorWrongType("Left");
#else
            if(arg3.dataElem->kind != 's')
            {
                FrmGetObjectBounds (frmPtr,pos,&bounds);
                  if(FrmGetObjectType(frmPtr,pos)==frmTableObj)            //07052005
                  {                                                        //07052005
                      WinEraseRectangle (&bounds,0);                       //07052005
                  }                                                        //07052005 
                  commonShowHide(pnoP, 0x00,frmPtr,FrmGetObjectId(frmPtr,pos));  //07052005
                   if( obj->type == frmTableObj)                           //07052005
                   {                                                       //07052005
                         obj->origGridBounds.topLeft.x = bounds.topLeft.x; //07052005
                   }                                                       //07052005
                  
                bounds.topLeft.x=*(double*)arg3.val;
                bounds.topLeft.x = ByteSwap16(bounds.topLeft.x);
                FrmSetObjectBounds (frmPtr,pos, &bounds);
            }
            else
            commonErrorWrongType(pnoP, "Left");
#endif
            break; 
        case 81:  //top
        
#ifdef __MC68K__
            if(arg3->kind != 's')
            {
                FrmGetObjectBounds (frmPtr,pos,&bounds);
                  if(FrmGetObjectType(frmPtr,pos)==frmTableObj)            //07052005
                  {                                                        //07052005
                      WinEraseRectangle (&bounds,0);                       //07052005
                  }                                                        //07052005 
                  commonShowHide(0x00,frmPtr,FrmGetObjectId(frmPtr,pos));  //07052005
                   if( obj->type == frmTableObj)                           //07052005
                   {                                                       //07052005
                         obj->origGridBounds.topLeft.y = bounds.topLeft.y; //07052005
                   }                                                       //07052005
                  
                bounds.topLeft.y=basc_integ_value(arg3,(double*)arg3_val);
                FrmSetObjectBounds (frmPtr,pos, &bounds);
            }
            else
            commonErrorWrongType("Top");
#else
            if(arg3.dataElem->kind != 's')
            {
                FrmGetObjectBounds (frmPtr,pos,&bounds);
                  if(FrmGetObjectType(frmPtr,pos)==frmTableObj)            //07052005
                  {                                                        //07052005
                      WinEraseRectangle (&bounds,0);                       //07052005
                  }                                                        //07052005 
                  commonShowHide(pnoP, 0x00,frmPtr,FrmGetObjectId(frmPtr,pos));  //07052005
                   if( obj->type == frmTableObj)                           //07052005
                   {                                                       //07052005
                         obj->origGridBounds.topLeft.y = bounds.topLeft.y; //07052005
                   }                                                       //07052005
                  
                bounds.topLeft.y=*(double*)arg3.val;
                bounds.topLeft.y = ByteSwap16(bounds.topLeft.y);
                FrmSetObjectBounds (frmPtr,pos, &bounds);
            }
            else
            commonErrorWrongType(pnoP, "Top");
#endif
            break; 
        case 82:   //width
        
#ifdef __MC68K__
            if(arg3->kind != 's')
            {
                FrmGetObjectBounds (frmPtr,pos,&bounds);
                  if(FrmGetObjectType(frmPtr,pos)==frmTableObj)            //07052005
                  {                                                        //07052005
                      WinEraseRectangle (&bounds,0);                       //07052005
                  }                                                        //07052005 
                  commonShowHide(0x00,frmPtr,FrmGetObjectId(frmPtr,pos));  //07052005
                   if( obj->type == frmTableObj)                           //07052005
                   {                                                       //07052005
                         obj->origGridBounds.extent.x = bounds.extent.x; //07052005
                   }                                                       //07052005
                  
                bounds.extent.x=basc_integ_value(arg3,(double*)arg3_val);
                FrmSetObjectBounds (frmPtr,pos, &bounds);
            }
            else
            commonErrorWrongType("Width");
#else
            if(arg3.dataElem->kind != 's')
            {
                FrmGetObjectBounds (frmPtr,pos,&bounds);
                  if(FrmGetObjectType(frmPtr,pos)==frmTableObj)            //07052005
                  {                                                        //07052005
                      WinEraseRectangle (&bounds,0);                       //07052005
                  }                                                        //07052005 
                  commonShowHide(pnoP, 0x00,frmPtr,FrmGetObjectId(frmPtr,pos));  //07052005
                   if( obj->type == frmTableObj)                           //07052005
                   {                                                       //07052005
                         obj->origGridBounds.extent.x = bounds.extent.x; //07052005
                   }                                                       //07052005
                  
                bounds.extent.x=*(double*)arg3.val;
                bounds.extent.x = ByteSwap16(bounds.extent.x);
                FrmSetObjectBounds (frmPtr,pos, &bounds);
            }
            else
            commonErrorWrongType(pnoP, "Width");
#endif
            break; 
        case 83:  //height
        
#ifdef __MC68K__
            if(arg3->kind != 's')
            {
                FrmGetObjectBounds (frmPtr,pos,&bounds);
                  if(FrmGetObjectType(frmPtr,pos)==frmTableObj)            //07052005
                  {                                                        //07052005
                      WinEraseRectangle (&bounds,0);                       //07052005
                  }                                                        //07052005 
                  commonShowHide(0x00,frmPtr,FrmGetObjectId(frmPtr,pos));  //07052005
                   if( obj->type == frmTableObj)                           //07052005
                   {                                                       //07052005
                         obj->origGridBounds.extent.y = bounds.extent.y; //07052005
                   }                                                       //07052005
                  
                bounds.extent.y=basc_integ_value(arg3,(double*)arg3_val);
                FrmSetObjectBounds (frmPtr,pos, &bounds);
            }
            else
            commonErrorWrongType("Height");
#else
            if(arg3.dataElem->kind != 's')
            {
                FrmGetObjectBounds (frmPtr,pos,&bounds);
                  if(FrmGetObjectType(frmPtr,pos)==frmTableObj)            //07052005
                  {                                                        //07052005
                      WinEraseRectangle (&bounds,0);                       //07052005
                  }                                                        //07052005 
                  commonShowHide(pnoP, 0x00,frmPtr,FrmGetObjectId(frmPtr,pos));  //07052005
                   if( obj->type == frmTableObj)                           //07052005
                   {                                                       //07052005
                         obj->origGridBounds.extent.y = bounds.extent.y; //07052005
                   }                                                       //07052005
                  
                bounds.extent.y=*(double*)arg3.val;
                bounds.extent.y = ByteSwap16(bounds.extent.y);
                FrmSetObjectBounds (frmPtr,pos, &bounds);
            }
            else
            commonErrorWrongType(pnoP, "Height");
#endif
            break; 
          //end additions 04012005                 
      //end additions 09242003
                           
        //end additions 09242003
       }     
   //if(controlType != frmControlObj) return;
}

/********************************************************************************************/
#ifdef __MC68K__
void commonDeleteItem(FormPtr frmPtr,ControlPtr controlPtr, Int16 controlid, struct dataelem *argn, double* argn_val)
#else
void commonDeleteItem(PNOBlock *pnoP, FormPtr frmPtr,ControlPtr controlPtr, Int16 controlid, struct dataelem *argn, double* argn_val)
#endif
{
    struct ObjectData * objectPtr;
#ifdef __MC68K__
#else
    Int16 oTemp;
    VoidPtr oTempPtr;
#endif
  Int16 oldNoItems;
  Int16 where;
  VoidHand hnew;
  VoidPtr pnew;
  VoidPtr pold;
  VoidPtr oldptr;
  
#ifdef __MC68K__
  objectPtr=locateObjectPtr(controlid);                   //locate our own object info ptr
  pold=  objectPtr->dataPtr;                              //point to the old list of text ptrs
  oldNoItems=objectPtr->numItems;                         //set the # of items in the old list
  where=basc_integ_value(argn,(double*)argn_val);         //get the integer # of the item to delete
#else
  objectPtr = locateObjectPtr(pnoP, controlid);                   //locate our own object info ptr
  pold = (VoidPtr) ReadUnaligned32(&(objectPtr -> dataPtr));                              //point to the old list of text ptrs
  oldNoItems= objectPtr -> numItems;                         //set the # of items in the old list
  oldNoItems = ByteSwap16(oldNoItems);
  where = (Int16) ReadUnaligned64((char *) argn_val);         //get the integer # of the item to delete
#endif
  
  
  
//StrPrintF(debug,"in listdeleteItem   where=%d  old#=%d   ",where,objectPtr->numItems);
//dbug(debug);
  if ((where>oldNoItems) || (where<=0) )                  //if # specified to delete is too high or too low
  {
//dbug("out-of-bounds");               
         return;                                          //can't delete, so exit 
  }
 
  if (oldNoItems==1)
  {
     if(pold)
     {
#ifdef __MC68K__
         FreeListValues(objectPtr->dataPtr,oldNoItems);   //free up the old list and each text string
#else
         FreeListValues(pold, oldNoItems);   //free up the old list and each text string
#endif
     }
     pnew=0;
     LstSetListChoices( (ListPtr)controlPtr, 0,0 );       //set the screen list object empty
     goto redraw;
  }

  oldptr=*( (char**)((char*)(pold)+(where-1)*4));   //point to the old text string
#ifndef __MC68K__
  oldptr = (VoidPtr) ByteSwap32(oldptr);
#endif
  MemPtrFree(oldptr);	// DIKEOBATS                                   //and free it up

#ifdef __MC68K__   // DIKEOBATS
  hnew=MemHandleNew( ( objectPtr->numItems-1)*4);  //allocate a new list of text pointers one smaller than old list
#else
  hnew=MemHandleNew( ( oldNoItems-1)*4);  //allocate a new list of text pointers one smaller than old list
#endif
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
  LstSetListChoices( (ListPtr)controlPtr, (char**)pnew, oldNoItems-1 );  //set the screen object to have the new list of text items
  MemPtrFree(pold);														 //and free the pointer list 12162003 LDM
redraw:
#ifdef __MC68K__
  objectPtr->dataPtr=pnew;            //save the new ptr to the list in our own area
  objectPtr->numItems=oldNoItems-1;   //and save the new # of items
#else
    WriteUnaligned32(&(objectPtr -> dataPtr), pnew);
    --oldNoItems;
   objectPtr -> numItems = ByteSwap16(oldNoItems);
#endif
  

  
  if(frmPtr==FrmGetActiveForm()) LstDrawList((ListPtr) controlPtr);  //redraw the list on the screen
  
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_listdeleteitem()
#else
void verb_listdeleteitem(PNOBlock *pnoP)
#endif

{
  FormPtr frmPtr;
#ifdef __MC68K__
  find_ctlid(true);                                           //find the ptr to the List object
  find_arg_2();                                           //the position in the list to delete
  frmPtr=FrmGetActiveForm();
  commonDeleteItem(frmPtr,PNO(controlPtr),PNO(controlid),arg2,(double*)arg2_val);
#else
  Arg arg2;
  find_ctlid(pnoP, true);                                           //find the ptr to the List object
  find_arg_PNO(pnoP, &arg2);                                           //the position in the list to delete
  frmPtr=FrmGetActiveForm();
  commonDeleteItem(pnoP, frmPtr,PNO(controlPtr),PNO(controlid),arg2.dataElem,(double*)arg2.val);
#endif  
}
     
/********************************************************************************************/
#ifdef __MC68K__
void commonAddItem(FormPtr frmPtr,ControlPtr controlPtr, Int16 controlid,struct dataelem *argn, double*argn_val,struct dataelem* args, char*args_val, char redrawChar)
#else
void commonAddItem(PNOBlock *pnoP, FormPtr frmPtr,ControlPtr controlPtr, Int16 controlid,struct dataelem *argn, double*argn_val,struct dataelem* args, char*args_val, char redrawChar)  // EMP
#endif
{
  struct ObjectData *objectPtr;
#ifdef __MC68K__
#else
  Int16 oTemp;
  void *oTempPtr;
#endif
  UInt16 i;
  UInt16 j;
  Int16 oldNoItems;  
  Int16 where;
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
  if(argn==NULL) where = LstGetNumberOfItems((ListPtr)controlPtr)+1;  //if didn't specify optional position in list at which to add,
                                                               //then, add to end of list
#ifdef __MC68K__
  else where=basc_integ_value(argn,(double*)argn_val);         //otherwise, get integer # of position to add at
  objectPtr=locateObjectPtr(controlid);                      //point to our own internal object info
#else
  else where = (Int16) ReadUnaligned64((char *) argn_val);
  objectPtr=locateObjectPtr(pnoP, controlid);                      //point to our own internal object info
#endif
//StrPrintF(debug,"in listdeleteItaddtem   where=%d  old#=%d   ",where,objectPtr->numItems);
//dbug(debug);

    if(where<=0) where=1;    //GH added 10092002
    
#ifdef __MC68K__    
  if((where<=0)||(where>(objectPtr->numItems+1)))              //if specified a position too high or too low 
#else
  oTemp = objectPtr -> numItems;
  oTemp = ByteSwap16(oTemp);
  if((where<=0)||(where > oTemp + 1))              //if specified a position too high or too low 
#endif
  {
                                      //can't add , so exit                                
      //theChar=find_char();      //must bypass the char in code to avoid abort
#ifdef __MC68K__
      StrPrintF(debug,"index (%d) is invalid for list.add operation.",where);
      SysFatalAlert(debug);
      ErrThrow(-1);                 //inserted 05212003
#else
      char debug[60];
      char *b;
      b = strcpy(debug, "index (");
      StrIToA(b, where);
      while (*b) ++b;
      strcpy(b, ") is invalid for list.add operation.");
      SysFatalAlert(debug);
      GlueErrThrow(pnoP, -1);                 //inserted 05212003
#endif
      //05212003 return;
  }
  
//StrPrintF(debug,"addItem id=%d where=%d val=%s",controlid,where,args_val);
//dbug(debug);
#ifdef __MC68K__
  hnew=MiscHandleNew( ( objectPtr->numItems+1)*4,"addLst");  //allocate a new list of text pointers one larger than old list
  pnew=MiscHandleLock(hnew);                                 //and lock it down
#else
  oTemp = objectPtr -> numItems;
  oTemp = ByteSwap16(oTemp);
  hnew=MemHandleNew((oTemp + 1)*4);  //allocate a new list of text pointers one larger than old list
  pnew=MemHandleLock(hnew);                                 //and lock it down
#endif

#ifdef __MC68K__
  pold =  objectPtr->dataPtr;                   //point to old list of text ptrs
  oldNoItems=objectPtr->numItems;              //and how many were in the list 
#else
  pold = (void *)ReadUnaligned32(&(objectPtr -> dataPtr));                   //point to old list of text ptrs
  oldNoItems= objectPtr -> numItems;              //and how many were in the list 
  oldNoItems = ByteSwap16(oldNoItems);
#endif
  
  itemPtr=args_val;                           //the item to add  

#ifdef __MC68K__
  newptr=(char*)MiscHandleLock(MiscHandleNew(StrLen((char*) itemPtr)+1 ,"addLst3"));  //alloc new meme for the text string
#else
  newptr=(char*)MemHandleLock(MemHandleNew(strlen((char*) itemPtr)+1));  //alloc new meme for the text string
#endif

#ifdef __MC68K__
  MemMove(newptr,itemPtr,StrLen((char*) itemPtr)+1);                                  //and move the text to it to save it
#else
  MemMove(newptr,itemPtr,strlen((char*) itemPtr)+1);
#endif
  if(where==1)                //adding to the beginning of the list
  {
#ifdef __MC68K__
      *( (char**)((char*)pnew)) =(char*) newptr;   //set 1st ptr to the new item text
#else
       *( (char**)((char*)pnew)) =(char*) ByteSwap32((unsigned long) newptr); // EMP swapped
#endif
      MemMove((char*)pnew+4,pold, oldNoItems*4);  //move all the old pointers into the list of pointers
  }
  else
  {
     if( where>oldNoItems)   //adding to the end of the list
     {
          MemMove((char*)pnew,pold, oldNoItems*4);  //move all the old pointers into the list of pointers
#ifdef __MC68K__
          *( (char**)((char*)pnew+oldNoItems*4)) =(char*)newptr;   //set last ptr to the new item text
#else
          *( (char**)((char*)pnew+oldNoItems*4)) =(char*) ByteSwap32((unsigned long) newptr);   //set last ptr to the new item text
#endif
     }
     else                    //adding in the middle of the list
     {
          MemMove((char*)pnew,pold, (where-1)*4);                                        //move  the preceeding old pointers into the list of pointers
#ifdef __MC68K__
          *( (char**)((char*)pnew+(where-1)*4)) =(char*)newptr;                            //set middle ptr to the new item text
#else
          *( (char**)((char*)pnew+(where-1)*4)) =(char*) ByteSwap32((unsigned long) newptr);                          //set middle ptr to the new item text
#endif
          MemMove((char*)pnew+(where)*4,(char*)pold+(where-1)*4, (oldNoItems-where+1)*4);  //move  the succeeding old pointers into the list of pointers
     }
  }

  LstSetListChoices( (ListPtr)controlPtr,(char**) pnew, oldNoItems+1);  //set the new list in the screen object

#ifdef __MC68K__
  if( objectPtr->dataPtr!=0)
  {
      MiscPtrFree(objectPtr->dataPtr);                      //free up the old list of pointers
  }
#else
  oTempPtr = (void *) ReadUnaligned32(&(objectPtr -> dataPtr));
  if(oTempPtr)
  {
      MemPtrFree(oTempPtr);                      //free up the old list of pointers
  }
#endif

#ifdef __MC68K__
  objectPtr->dataPtr=pnew;                                      //and save the new list of ptrs in our own mem area
  objectPtr->numItems=oldNoItems+1;                             //and save how many in the list as well
#else
  WriteUnaligned32(&(objectPtr -> dataPtr), pnew);
  ++oldNoItems;
  objectPtr -> numItems = ByteSwap16(oldNoItems);
#endif

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
#ifdef __MC68K__
void verb_listadditem()
#else
void verb_listadditem(PNOBlock *pnoP)   // EMP
#endif
{
  char theChar;
  FormPtr frmPtr;
#ifndef __MC68K__
  Arg arg1, arg2;
#endif
  
  frmPtr=FrmGetActiveForm(); 
  
#ifdef __MC68K__
  find_ctlid(true);      //find ptr to the List screen object 

  find_arg_1();      //text string of item to be added
  find_arg_2();      //position in the list to add this new item at
  theChar=find_char();
  commonAddItem(frmPtr,PNO(controlPtr), PNO(controlid), arg2,(double*)arg2_val,arg1,arg1_val,theChar);
#else
  find_ctlid(pnoP, true);      //find ptr to the List screen object 

  find_arg_PNO(pnoP, &arg1);      //text string of item to be added
  find_arg_PNO(pnoP, &arg2);      //position in the list to add this new item at
  theChar=find_char(pnoP);
  commonAddItem(pnoP, frmPtr, PNO(controlPtr), PNO(controlid), arg2.dataElem,(double*)arg2.val,arg1.dataElem,arg1.val,theChar);
#endif
}


/********************************************************************************************/
#ifdef __MC68K__
void commonClear(ControlPtr controlPtr,Int16 objType,FormPtr frmPtr, Int16 controlid)
#else
void commonClear(PNOBlock *pnoP, ControlPtr controlPtr,Int16 objType,FormPtr frmPtr, Int16 controlid)
#endif
{
   
   VoidPtr pold;
   Int16 oldNoItems;
    struct ObjectData *objectPtr;
#ifdef __MC68K__
#else
    Int16 oTemp;
    VoidPtr oTempPtr;
#endif
    Int16 i;

    if(objType==frmListObj) goto listClear;   // EMP seems strange?
    if(objType==frmPopupObj) goto listClear;
    return;
popupClear:
  
//dbug("in popup clear");
   LstSetListChoices( (ListType*)controlPtr, 0,0);

#ifdef __MC68K__   
   objectPtr=locateObjectPtr(controlid);
#else
   objectPtr=locateObjectPtr(pnoP, controlid);
#endif

#ifdef __MC68K__
   if( objectPtr->dataPtr!=0)
   {
     FreeListValues(objectPtr->dataPtr,objectPtr->numItems);
   }
   objectPtr->dataPtr=0;
   objectPtr->numItems=0; 
#else
   oTempPtr = (VoidPtr) ReadUnaligned32(&(objectPtr -> dataPtr));
   oTemp = objectPtr -> numItems;
   oTemp = ByteSwap16(oTemp);
   if(oTempPtr)
   {
     FreeListValues(oTempPtr,oTemp);
   }
   WriteUnaligned32(&(objectPtr -> dataPtr), 0);
   objectPtr -> numItems = 0;	// No need to swap 
#endif   
  
   if(frmPtr==FrmGetActiveForm()) LstDrawList(  (ListPtr)controlPtr  );
   return; 
    
listClear: 
//dbug("in commonlist clear");
      LstSetListChoices( (ListPtr)controlPtr, 0, 0); //set list of item text ptrs to nothing

#ifdef __MC68K__      
      objectPtr=locateObjectPtr(controlid);          //now update our own internal pointers
#else
      objectPtr=locateObjectPtr(pnoP, controlid);          //now update our own internal pointers
#endif

#ifdef __MC68K__
       if( objectPtr->dataPtr!=0)
       {
         FreeListValues(objectPtr->dataPtr,objectPtr->numItems);
       }
       objectPtr->dataPtr=0;
       objectPtr->numItems=0; 
#else
       oTempPtr = (VoidPtr) ReadUnaligned32(&(objectPtr -> dataPtr));
       oTemp = objectPtr -> numItems;
       oTemp = ByteSwap16(oTemp);

       if(oTempPtr)
       {
         FreeListValues(oTempPtr,oTemp);
       }
       WriteUnaligned32(&(objectPtr -> dataPtr), 0);
       objectPtr -> numItems = 0; 
#endif   

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
#ifdef __MC68K__
void verb_popupclear()
#else
void verb_popupclear(PNOBlock *pnoP)   // EMP
#endif
{
   FormPtr frmPtr;   

#ifdef __MC68K__   
   find_ctlid(true);
   frmPtr=FrmGetActiveForm();
   commonClear(PNO(controlPtr),frmPopupObj,frmPtr, PNO(controlid));
#else
   find_ctlid(pnoP, true);
   frmPtr=FrmGetActiveForm();
   commonClear(pnoP, PNO(controlPtr),frmPopupObj,frmPtr, PNO(controlid));
#endif
}
/********************************************************************************************/

#ifdef __MC68K__
void verb_listclear()
#else
void verb_listclear(PNOBlock *pnoP)
#endif
{
    FormPtr frmPtr;


#ifdef __MC68K__
    find_ctlid(true);                                  //find ptr to the List object
#else
    find_ctlid(pnoP, true);
#endif
    frmPtr=FrmGetActiveForm();
    //dbug("verb_listclear");
#ifdef __MC68K__
    commonClear(PNO(controlPtr),frmListObj,frmPtr, PNO(controlid));
#else
    commonClear(pnoP, PNO(controlPtr),frmListObj,frmPtr, PNO(controlid));
#endif  
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_generalVerb()
#else
void verb_generalVerb(PNOBlock *pnoP)       // EMP
#endif
{
  
    Int16 controlType;
    Int16 pos;
    char c;
    Int16 verbId;
    Boolean found;
    char theChar;    //09302002
    FormPtr frmPtr;        //added 5.20.2000
#ifndef __MC68K__
    double d;
    Arg arg2, arg3;
#endif
    found=true;
#ifdef __MC68K__
    c=find_char();   //type of control identifier
#else
    c = find_char(pnoP);
#endif
    switch(c)
    {
      case 'i':  //ctlid
#ifdef __MC68K__
        found=find_ctlid(false);
        if(found==false) break;  //probably a bitmap that can't use by id
        frmPtr=findFormTheControlIsOn(PNO(controlid));
        pos=FrmGetObjectIndex(frmPtr,PNO(controlid));
        break;
#else
        found=find_ctlid(pnoP, false);
        if(found==false) break;  //probably a bitmap that can't use by id
        frmPtr=findFormTheControlIsOn(pnoP, PNO(controlid));
        pos=FrmGetObjectIndex(frmPtr,PNO(controlid));
        break;
#endif
      case 'v':  //variable containing name
#ifdef __MC68K__
        find_arg_2();      //variable containing name
        frmPtr=FrmGetActiveForm();
        pos=findControlsPositionOnForm(&frmPtr,arg2_val);
        goto havePosition;
        break;
#else
        find_arg_PNO(pnoP, &arg2);      //variable containing name
        frmPtr=FrmGetActiveForm();
        pos=findControlsPositionOnForm(pnoP, &frmPtr,arg2.val);
        goto havePosition;
        break;
#endif
      case 'p':  //position of ctl on form
#ifdef __MC68K__
        find_arg_2();      //position of control on form
        pos = integ_value( arg2, (double *)arg2_val ); 
#else
        find_arg_PNO(pnoP, &arg2);      //position of control on form
        pos = (Int16) ReadUnaligned64(arg2.val); 
#endif
        frmPtr=FrmGetActiveForm();
    havePosition:

        if(pos>FrmGetNumberOfObjects(frmPtr)-1)
        {
#ifdef __MC68K__
           SysFatalAlert("Control position too high.");
           ErrThrow(-1);                 //inserted 05212003
#else
           SysFatalAlert("Control position too high.");
           GlueErrThrow(pnoP, -1);                 //inserted 05212003
#endif
        }
       
        PNO(controlPtr) = ((ControlType*)FrmGetObjectPtr(frmPtr,pos));
        PNO(controlid) = FrmGetObjectId(frmPtr,pos);
        break;
    }
   if(found) controlType=FrmGetObjectType(frmPtr,pos);
#ifdef __MC68K__
   verbId=find_integer();          //property type identifier #
#else
   verbId=find_integer(pnoP);          //property type identifier #
#endif

   switch(verbId)
   {
       case 0:  //hide          
            if (found==false) return;
#ifdef __MC68K__
            commonShowHide(0x00,frmPtr,PNO(controlid));
#else
            commonShowHide(pnoP, 0x00,frmPtr,PNO(controlid));
#endif
            break; 
       case 1:  //show
             if (found==false) return;
#ifdef __MC68K__
            commonShowHide(0x01,frmPtr,PNO(controlid));
#else
            commonShowHide(pnoP, 0x01,frmPtr,PNO(controlid));
#endif
	        break; 
       case 2:  //additem
//StrPrintF(debug,"in additem id=%d ",controlid);
//dbug(debug);
          

          if( (controlType!=frmListObj)&&(controlType!=frmControlObj))
#ifdef __MC68K__
            commonErrorWrongCtltype("additem",controlType);
#else
            commonErrorWrongCtltype(pnoP, "additem",controlType);
#endif
          else
          {
#ifdef __MC68K__
            find_arg_3();  //text
            find_arg_2();  //position in list
            theChar=find_char();             //09302002
            
            if(arg3->kind == 's') 
#else
            find_arg_PNO(pnoP, &arg3);  //text
            find_arg_PNO(pnoP, &arg2);  //position in list
            theChar=find_char(pnoP);             //09302002
            
            if(arg3.dataElem -> kind == 's') 
#endif
            {
                if (controlType==frmListObj)
#ifdef __MC68K__
                    commonAddItem( frmPtr,PNO(controlPtr), PNO(controlid), arg2, (double*)arg2_val,arg3,arg3_val,theChar);       
#else
                    commonAddItem(pnoP, frmPtr,PNO(controlPtr), PNO(controlid), arg2.dataElem, (double*)arg2.val,arg3.dataElem,arg3.val,theChar);       
#endif
                else
                {
                    //must point to list part of popup
                    PNO(controlPtr) = ((ControlType*)FrmGetObjectPtr(frmPtr,pos+1));
                    PNO(controlid) = FrmGetObjectId(frmPtr,pos+1);
#ifdef __MC68K__
                    commonAddItem( frmPtr, PNO(controlPtr), PNO(controlid), arg2, (double*)arg2_val,arg3,arg3_val,theChar);
#else
                    commonAddItem(pnoP, frmPtr, PNO(controlPtr), PNO(controlid), arg2.dataElem, (double*)arg2.val,arg3.dataElem,arg3.val,theChar);
#endif
                }     
            }
#ifdef __MC68K__
            else commonErrorWrongType("additem");
#else
            else commonErrorWrongType(pnoP, "additem");
#endif
          }
          break;
       case 3:  //clear
          if( (controlType!=frmListObj)&&(controlType!=frmControlObj)&&(controlType!=frmTableObj))  //added 09242003
          {
#ifdef __MC68K__
              commonErrorWrongCtltype("clear",controlType);
#else
              commonErrorWrongCtltype(pnoP, "clear",controlType);
#endif
          }
          else
          {
                if (controlType==frmListObj)
                {
                
//StrPrintF(debug,"clearing list obj id=%d",controlid);
//dbug(debug); 
#ifdef __MC68K__
                  commonClear(PNO(controlPtr),frmListObj,frmPtr, PNO(controlid));       
#else
                  commonClear(pnoP, PNO(controlPtr),frmListObj,frmPtr, PNO(controlid));       
#endif
                }
                else
                {
                	if (controlType==frmTableObj)
                    {
#ifdef __MC68K__
                        gridClear(frmPtr,PNO(controlPtr));
#else
						gridClear(pnoP, frmPtr, PNO(controlPtr));
#endif
                	}
                	else
                	{

                     //must point to list part of popup
                     PNO(controlPtr) = ((ControlType*)FrmGetObjectPtr(frmPtr,pos+1));
	                 PNO(controlid) = FrmGetObjectId(frmPtr,pos+1);
#ifdef __MC68K__
                     commonClear(PNO(controlPtr),frmPopupObj,frmPtr, PNO(controlid));
#else
                     commonClear(pnoP, PNO(controlPtr),frmPopupObj,frmPtr, PNO(controlid));
#endif
					}
                }
          }
          break;
       case 4:  //deleteitem
          if( (controlType!=frmListObj)&&(controlType!=frmControlObj))
#ifdef __MC68K__
            commonErrorWrongCtltype("deleteitem",controlType);
#else
            commonErrorWrongCtltype(pnoP, "deleteitem",controlType);
#endif
          else
          {
#ifdef __MC68K__
            find_arg_3();    //index
            if(arg3->kind != 's')
#else
            find_arg_PNO(pnoP, &arg3);    //index
            if(arg3.dataElem -> kind != 's')
#endif
            {
                if (controlType==frmListObj)
#ifdef __MC68K__
                    commonDeleteItem(frmPtr, PNO(controlPtr), PNO(controlid),arg3, (double*)arg3_val);       
#else
                    commonDeleteItem(pnoP, frmPtr, PNO(controlPtr), PNO(controlid),arg3.dataElem, (double*)arg3.val);       
#endif
                else
                {
//dbug("recognized popup delete");
                     //must point to list part of popup
                     PNO(controlPtr) = ((ControlType*)FrmGetObjectPtr(frmPtr,pos+1));
	                 PNO(controlid) =FrmGetObjectId(frmPtr,pos+1);
#ifdef __MC68K__
                     commonDeleteItem( frmPtr,PNO(controlPtr), PNO(controlid), arg3, (double*)arg3_val);
#else
                     commonDeleteItem(pnoP, frmPtr,PNO(controlPtr), PNO(controlid), arg3.dataElem, (double*)arg3.val);
#endif
                }     
            }
#ifdef __MC68K__
            else commonErrorWrongType("deleteitem");
#else
            else commonErrorWrongType(pnoP, "deleteitem");
#endif
          }
          break; 
       case 5:  //startCapture
          if(controlType  != frmGadgetObj)
#ifdef __MC68K__
            commonErrorWrongCtltype("startCapture",controlType);
#else
            commonErrorWrongCtltype(pnoP, "startCapture",controlType);
#endif
          else
          {
#ifdef __MC68K__
            commonStartCapture(frmPtr,PNO(controlid));
#else
            Glue_commonStartCapture(pnoP, frmPtr,PNO(controlid));
#endif
          }
          break; 
       case 6:  //erase
          if(controlType  != frmGadgetObj)
#ifdef __MC68K__
            commonErrorWrongCtltype("erase",controlType);
#else
            commonErrorWrongCtltype(pnoP, "erase",controlType);
#endif
          else
          {
#ifdef __MC68K__
            commonErase(frmPtr, PNO(controlid));
#else
            Glue_commonErase(pnoP, frmPtr, PNO(controlid));
#endif
          }
          break;
       
        case 7:  //display signature
          if(controlType  != frmGadgetObj)
#ifdef __MC68K__
            commonErrorWrongCtltype("display",controlType);
#else
            commonErrorWrongCtltype(pnoP, "display",controlType);
#endif
          else
          {
#ifdef __MC68K__
            find_arg_3();  
            commonSignatureDisplay(frmPtr, arg3_val, PNO(controlid));
#else
            find_arg_PNO(pnoP, &arg3);
            Glue_commonSignatureDisplay(pnoP, frmPtr, arg3.val, PNO(controlid));
#endif
          }
          break; 
        case 8:  //redraw/refresh ctl
          //if(controlType  != frmGadgetObj) commonErrorWrongCtltype("refresh",controlType);
          //else
          //{
            if(found==false)  break;   //may be shift indic that can't redraw
            if(controlType==frmGraffitiStateObj)  break;  //shift indic can't redraw
#ifdef __MC68K__
            commonRedrawId(frmPtr, PNO(controlid));
#else
			commonRedrawId(pnoP, frmPtr, PNO(controlid));
#endif
          //}
          break; 
        case 9:  //setfocus
          if(controlType  != frmFieldObj)
#ifdef __MC68K__
            commonErrorWrongCtltype("setFocus",controlType);
#else
            commonErrorWrongCtltype(pnoP, "setFocus",controlType);
#endif
          else
          {
#ifdef __MC68K__
            commonSetFocus(frmPtr, PNO(controlid));
#else
            commonSetFocus(pnoP, frmPtr, PNO(controlid));
#endif
          }
          break;      
        //start of additions 09242003   
        case 70:  //addItem
#ifdef __MC68K__
          if(controlType  != frmTableObj) commonErrorWrongCtltype("Add",controlType);
#else
		  if(controlType != frmTableObj) commonErrorWrongCtltype(pnoP, "Add", controlType);
#endif
          else
          {
#ifdef __MC68K__            
            gridAdd(frmPtr,  PNO(controlPtr));
#else
		    gridAdd(pnoP, frmPtr, PNO(controlPtr));
#endif
          }
          break;
        case 71:  //delete
#ifdef __MC68K__
          if(controlType  != frmTableObj) commonErrorWrongCtltype("Delete",controlType);
#else
		  if(controlType != frmTableObj) commonErrorWrongCtltype(pnoP, "Delete", controlType);
#endif
          else
          {
            
            gridDelete(frmPtr,  PNO(controlPtr));
          }
          break;    
        case 72:  //colType
#ifdef __MC68K__
          if(controlType  != frmTableObj) commonErrorWrongCtltype("ColType",controlType);
#else
		  if(controlType != frmTableObj) commonErrorWrongCtltype(pnoP, "ColType", controlType);
#endif
          else
          {
//SysFatalAlert("basc--found colType"); 
#ifdef __MC68K__           
            gridColType(frmPtr,  PNO(controlPtr));
#else
			gridColType(pnoP, frmPtr, PNO(controlPtr));
#endif
          }
          break;
        case 73:  //bindToDatabase
#ifdef __MC68K__
          if(controlType != frmTableObj) commonErrorWrongCtltype("BindToDatabase",controlType);
#else
		  if(controlType != frmTableObj) commonErrorWrongCtltype(pnoP, "BindToDatabase", controlType);
#endif
          else
          {
#ifdef __MC68K__
            gridBindToDatabase(frmPtr,  PNO(controlPtr));
#else
			gridBindToDatabase(pnoP, frmPtr, PNO(controlPtr));
#endif
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
#ifdef __MC68K__
          if(controlType  != frmTableObj) commonErrorWrongCtltype("ColType",controlType);
#else
          if(controlType  != frmTableObj) commonErrorWrongCtltype(pnoP, "ColType",controlType);
#endif
          else
          {
//SysFatalAlert("basc--found colType");  
#ifdef __MC68K__
            gridHideGridLines(frmPtr,  PNO(controlPtr));
#else
			gridHideGridLines(pnoP, frmPtr, PNO(controlPtr));
#endif
          }
          break; 
        case 76:  //showGridLines
#ifdef __MC68K__
          if(controlType  != frmTableObj) commonErrorWrongCtltype("ColType",controlType);
#else
          if(controlType  != frmTableObj) commonErrorWrongCtltype(pnoP, "ColType",controlType);
#endif
          else
          {
//SysFatalAlert("basc--found colType");            
#ifdef __MC68K__          
            gridShowGridLines(frmPtr,  PNO(controlPtr));
#else
			gridShowGridLines(pnoP, frmPtr, PNO(controlPtr));
#endif
          }
          break;
        //end additions 08152004        
       }     
   //if(controlType != frmControlObj) return;

} 

//*****************************************************************************************

/* EMP moved these from code.c because code.c will be in another PNO */

#ifndef __MC68K__
//*****************************************************************************************
void func_popupgettext(PNOBlock *pnoP, Arg *arg4)
{
  //10102002 char *ptr;
   //10102002 ptr=(char*)CtlGetLabel((ControlType*)controlPtr);
  //10102002storestr4(ptr);
  
  FormPtr frm;
  Int16 i;
  char *ptr;
  Word idNo;
  ListType* listObjPtr;
   
//dbug(ptr);
  //the popup has an associated listctl with an id 1 greater than the popup id
  //access the listctl to get the currently selected text. 

  // If the listctl does not have an item in the list selected, then just get the text of the control.
  //(Note. change was necessary because in the tap code for the control, the control's contents
  //are not yet updated when TAP code is fired.)

//dbug("in popupGetText"); 

  frm=FrmGetActiveForm();
  for(i=0;i<FrmGetNumberOfObjects(frm);++i)
  {
      if( FrmGetObjectType(frm, i)==frmListObj)
      {
          listObjPtr=FrmGetObjectPtr(frm,i);
          //the assoc list will have an id = one greater than the control
          //if(listObjPtr->id==(((ControlPtr)controlPtr)->id+1))  goto gotTheAssocList;  //found the associated listctl for this popup ctl
          if(FrmGetObjectId(frm,i)==(PNO(controlid)+1))  goto gotTheAssocList;  //found the associated listctl for this popup ctl
          
      }
  }
  goto returnTheControlsValue;  //should not happen
gotTheAssocList:

  i=LstGetSelection(listObjPtr);
  if (LstGetNumberOfItems(listObjPtr)==0) i=-1;
  
//StrPrintF(debug,"got the list element id=%d  #elems=%d selected=%d", listObjPtr->id,LstGetNumberOfItems(listObjPtr),i);
//dbug(debug);
  
  if(i<0)
  {
      //Program accessing a list to get text when no item selected or list empty
returnTheControlsValue:

//StrPrintF(debug,"just returning the control's text=%s",(char*)CtlGetLabel((ControlType*)controlPtr));
//dbug(debug);
      ptr=(char*)CtlGetLabel((ControlType*)PNO(controlPtr));   //just get the control's current text value
      misc_stostr(pnoP, &(arg4 -> dataElem), arg4 -> occ1, arg4 ->occ2, arg4 ->occ3, ptr);
      return;
  }
//dbug("returning the selected list entry");
  //04022003ptr=*((char**)((char *)(listObjPtr->itemsText)+i*4) );
  ptr=LstGetSelectionText(listObjPtr,i)  ;    //added 04022003 (George's Glue code)
  //ptr=*((char**)((char *)(LstGlueGetItemsText(listObjPtr))+i*4) );  //(Larry's code - gets an error)
  misc_stostr(pnoP, &(arg4 -> dataElem), arg4 -> occ1, arg4 ->occ2, arg4 ->occ3, ptr);
}
#endif


//*****************************************************************************************
#ifdef __MC68K__
void verb_func_getGeneralPropertyString()
#else
void verb_func_getGeneralPropertyString(PNOBlock *pnoP)  // EMP
#endif
{
  //no auto arguments (really a verb)
  Int16 controlType;
  Int16 pos;
  //char c;
  //Int16 propId;
  FormPtr frmPtr;        //added 5.20.2000 
#ifndef __MC68K__
  Arg arg4, arg2, arg1;
#endif

//dbug("in set text");   
#ifdef __MC68K__
   find_arg_4();
   switch(find_char()) //type of control identifier
#else
   find_arg_PNO(pnoP, &arg4);
   switch(find_char(pnoP))   //type of control identifier
#endif

   {
      case 'i':  //ctlid
#ifdef __MC68K__
        find_ctlid(true);
        frmPtr=findFormTheControlIsOn(PNO(controlid));
#else
        find_ctlid(pnoP, true);
        frmPtr=findFormTheControlIsOn(pnoP, PNO(controlid));
#endif
        pos=FrmGetObjectIndex(frmPtr,PNO(controlid));
        break;
      case 'v':  //variable containing name
#ifdef __MC68K__
        find_arg_2();      //variable containing name
        pos=findControlsPositionOnForm(&frmPtr,arg2_val);
#else
        find_arg_PNO(pnoP, &arg2);
        pos = findControlsPositionOnForm(pnoP, &frmPtr, arg2.val); 
#endif
        goto havePosition;
        break;
      case 'p':  //position of ctl on form
#ifdef __MC68K__
        find_arg_2();      //position of control on form
        pos = integ_value( arg2, (double *)arg2_val ); 
#else
        find_arg_PNO(pnoP, &arg2);
        pos = (Int16) ReadUnaligned64(arg2.val);
#endif
        frmPtr=FrmGetActiveForm();
havePosition:
        
	    if(pos>FrmGetNumberOfObjects(frmPtr)-1)
	    {
	       SysFatalAlert("Control position too high.");
#ifdef __MC68K__
	       ErrThrow(-1);                 //inserted 05212003
#else
           GlueErrThrow(pnoP, -1);
#endif
	    }
	   
	    PNO(controlPtr) = ((ControlType*)FrmGetObjectPtr(frmPtr,pos));
	    PNO(controlid) = FrmGetObjectId(frmPtr,pos);
	    break;
   }
   controlType=FrmGetObjectType(frmPtr,pos);
#ifdef __MC68K__
	switch(find_integer())          //property type identifier #
#else
   switch(find_integer(pnoP))          //property type identifier #
#endif
   //find_arg_3();          //new property value to assign
//StrPrintF(debug,"getText  c=%c id=%d pos=%d propid=%d",c,controlid,pos,propId);
//dbug(debug);

   {
        
       case 0:  //text
          if(pos==0)  //return form title
          {
 			if(FrmGetTitle(frmPtr) != 0) //04272004 if there is a title on form
                {
#ifdef __MC68K__
              commonGetTitle(frmPtr);
#else
            char *ptr;

            ptr=(char*)FrmGetTitle(frmPtr);
            if (ptr)
            {
                misc_stostr(pnoP, &(arg4.dataElem), arg4.occ1, arg4.occ2, arg4.occ3, ptr);
            }
            else
            {
                misc_stostr(pnoP, &(arg4.dataElem), arg4.occ1, arg4.occ2, arg4.occ3, "");
            }
#endif
			}
              break;
          }
          switch(controlType)
          {
              case frmLabelObj:
//dbug("yes--got a label");
#ifdef __MC68K__
                commonGetLabel(frmPtr,PNO(controlid));
#else
              {
                char *ptr;

                ptr=(char*)FrmGetLabel(frmPtr,PNO(controlid));
                if (ptr)
                {
                    misc_stostr(pnoP, &(arg4.dataElem), arg4.occ1, arg4.occ2, arg4.occ3, ptr);
                }
                else
                {
                    misc_stostr(pnoP, &(arg4.dataElem), arg4.occ1, arg4.occ2, arg4.occ3, "");
                }
              }
#endif
                break;
              case frmControlObj:
//dbug("got controlgettext");
#ifdef __MC68K__
                if(CtlGlueGetControlStyle(PNO(controlPtr))==popupTriggerCtl)
#else
                if(GlueCtlGlueGetControlStyle(pnoP, PNO(controlPtr))==popupTriggerCtl)
#endif
                {
//dbug("going to popupgettext 2");
#ifdef __MC68K__
                    func_popupgettext();
#else
                    func_popupgettext(pnoP, &arg4);
#endif
                }
                else
                {
#ifdef __MC68K__
                    func_controlgettext();
#else
                    char *ptr;

                    ptr=(char*)CtlGetLabel((ControlType*)PNO(controlPtr));
                    if (ptr)
                    {
                        misc_stostr(pnoP, &(arg4.dataElem), arg4.occ1, arg4.occ2, arg4.occ3, ptr);
                    }
                    else
                    {
                        misc_stostr(pnoP, &(arg4.dataElem), arg4.occ1, arg4.occ2, arg4.occ3, "");
                    }
#endif
                }
                break;
              case frmFieldObj:
#ifdef __MC68K__
                func_fieldgettext();
#else
                {
                    char *ptr;

                    ptr=(char*)FldGetTextPtr((FieldType*)PNO(controlPtr));
                    if (ptr)
                    {
                        misc_stostr(pnoP, &(arg4.dataElem), arg4.occ1, arg4.occ2, arg4.occ3, ptr);
                    }
                    else
                    {
                        misc_stostr(pnoP, &(arg4.dataElem), arg4.occ1, arg4.occ2, arg4.occ3, "");
                    }
                }
#endif
                break;
              case frmPopupObj:
//dbug("going to popupgettext");
#ifdef __MC68K__
                func_popupgettext();
#else
                func_popupgettext(pnoP, &arg4);
#endif
                break;
              default:
#ifdef __MC68K__
                 commonErrorWrongCtltypeOnGet("text",controlType); 
#else
                 commonErrorWrongCtltypeOnGet(pnoP, "text",controlType); 
#endif
              case frmTableObj:           //added 09242003
#ifdef __MC68K__
                 gridGetSelectedText(frmPtr,PNO(controlPtr)); //added 09242003 
#else
                 gridGetSelectedText(pnoP, &arg4, frmPtr,PNO(controlPtr)); //added 09242003 
#endif
                 break;                   //added 09242003 
          }
          break; 
       case 11:  //itemtext
          if( (controlType!=frmListObj)&&(controlType!=frmControlObj))
#ifdef __MC68K__
            commonErrorWrongCtltypeOnGet("itemText",controlType);
#else
            commonErrorWrongCtltypeOnGet(pnoP, "itemText",controlType);
#endif
          else
          {
#ifdef __MC68K__
            find_arg_1();
                if (controlType==frmListObj) commonGetItemText(integ_value( arg1, (double *)arg1_val )-1);    
#else
            find_arg_PNO(pnoP, &arg1);
                if (controlType==frmListObj)
                {
                    double d;
                    char *ptr;
                    ListPtr l;
                    Int16 i;
                    
                    d = ReadUnaligned64(arg1.val);
                    i = (Int16) d;
                    i -= 1;

                    l=(ListType*)PNO(controlPtr);
                    if((i<0) || (i>=LstGetNumberOfItems(l)))
                    {
                      //SysFatalAlert("Program accessing a list to get text when no item selected");
                      misc_stostr(pnoP, &(arg4.dataElem), arg4.occ1, arg4.occ2, arg4.occ3, "***");
                      return;
                    }

                    ptr=LstGetSelectionText(l, i); //GHGlue
                    misc_stostr(pnoP, &(arg4.dataElem), arg4.occ1, arg4.occ2, arg4.occ3, ptr);
                }
#endif
                else
                {

                     //must point to list part of popup
                     PNO(controlPtr) = ((ControlType*)FrmGetObjectPtr(frmPtr,pos+1));
	                 PNO(controlid) = FrmGetObjectId(frmPtr,pos+1);
#ifdef __MC68K__
                     commonGetItemText(integ_value( arg1, (double *)arg1_val )-1);
#else
                    {
                        double d;
                        char *ptr;
                        ListPtr l;
                        Int16 i;
                    
                        d = ReadUnaligned64(arg1.val);
                        i = (Int16) d;
                        i -= 1;

                        l=(ListType*)PNO(controlPtr);
                        
                        if((i<0) || (i>=LstGetNumberOfItems(l)))
                        {
                          //SysFatalAlert("Program accessing a list to get text when no item selected");
                          misc_stostr(pnoP, &(arg4.dataElem), arg4.occ1, arg4.occ2, arg4.occ3, "***");
                          return;
                        }

                        ptr=LstGetSelectionText(l, i); //GHGlue
                        misc_stostr(pnoP, &(arg4.dataElem), arg4.occ1, arg4.occ2, arg4.occ3, ptr);
                    }
#endif
                }
          }
          break; 
       case 12:  //endcapture
          if (controlType!=frmGadgetObj)
#ifdef __MC68K__
            commonErrorWrongCtltypeOnGet("itemText",controlType);
#else
            commonErrorWrongCtltypeOnGet(pnoP, "itemText",controlType);
#endif
          else
          {
            //find_arg_4();
#ifdef __MC68K__
            commonEndCapture(frmPtr,  &arg4, arg4_occ1,arg4_occ2,arg4_occ3, PNO(controlid));
#else
			arg4.dataElem = (struct dataelem *)ByteSwap32((UInt32) arg4.dataElem);
            Glue_commonEndCapture(pnoP, frmPtr, &(arg4.dataElem), arg4.occ1, arg4.occ2, arg4.occ3, PNO(controlid));
			arg4.dataElem = (struct dataelem *)ByteSwap32((UInt32) arg4.dataElem);
#endif            
          }
          break;             
       case 54:  //cellMatrix
#ifdef __MC68K__
          if (controlType!=frmTableObj)commonErrorWrongCtltypeOnGet("cellMatrix", PNO(controlid));
#else
          if (controlType!=frmTableObj)commonErrorWrongCtltypeOnGet(pnoP, "cellMatrix",PNO(controlid));
#endif
          else
          {
            //find_arg_4();
#ifdef __MC68K__
            gridGetCellMatrix(frmPtr,  PNO(controlPtr));
#else
            gridGetCellMatrix(pnoP, &arg4, frmPtr, PNO(controlPtr));
#endif
            
          }
          break;             
       //end of additions 09242003                
    }         
}

