#ifdef __MC68K__
//this module is primarily all of the logic for built-in functions

#include <PalmOS.h>
#include <FloatMgr.h>
#include <PalmTypes.h>
#include <PalmCompatibility.h>
#include <day.h>
#include <selday.h>
#include <SysUtils.h>
#include <FatalAlert.h>
#include <SysEvtMgr.h>
#include <seltime.h>
#include <ScrollBar.h>
#include <MathLib.h>
#include <TimeMgr.h>
#include <SerialMgr.h>
#include <SerialMgrOld.h>
#include <ErrorBase.h>                   //05212003
#else // __MC68K__

// EMP StrongArm includes
#include "PACEInterfaceLib.h"
#include <size_t.h>
#include <cstddef>
#include <PalmCompatibility.h>
#include <endianutils.h>
#endif // __MC68K__

#include "NSBPNOShared.h"               //EMP
#include "NSBPNOGlue.h"
#include "copy.h"
#ifdef ORG_NSB
#include "nsbasic.h"
#endif

extern EventPtr evptr;

#define PI 3.14159265358979
extern void dbugx(double* v, char* identifier);
#ifdef __MC68K__
Boolean find_ctlid(Boolean abortSw);
#else
Boolean find_ctlid(PNOBlock *pnoP, Boolean abortSw);
void find_arg_PNO(PNOBlock *pnoP, Arg *argRet);
#endif
extern void  store_reg(double *r1,struct dataelem* de,
                      double* elem_ad,
                      unsigned int  elem_occ1,
                      unsigned int  elem_occ2,
                      unsigned int  elem_occ3 )   ;     /*-------store reg to data elem---*/
                   
#ifdef __MC68K__
void DoubleToStr (double val, CharPtr str);
void misc_format_number(struct dataelem* v, double* n , char * s);
#else
void DoubleToStr (PNOBlock *pnoP, double val, CharPtr str);
void misc_format_number(PNOBlock *pnoP, struct dataelem* v, double* n , char * s);
#endif
extern void misc_fmtno(char* a,char *wk,Int16 bef,Int16 aft,Int16 decpt,char *s);
extern Int16 integ_value( struct dataelem *  arg, double *    arg_ad);        /*---calc integ value of data elem__*/

#ifdef __MC68K__
void verb_func_signatureEndCapture();
void commonEndCapture(FormPtr frmPtr, struct dataelem **de, Int16 occ1, Int16 occ2, Int16 occ3, Int16 controlid);

extern misc_stostr1(char *s);
extern misc_stostr2(char *s);
extern misc_stostr3(char *s);
extern misc_stostr4(char *s);
extern misc_stostr5(char *s);
void misc_fix(int i, char *res, int num);

void misc_stodbl1(double* x);
void misc_stodbl2(double* x);
void misc_stodbl3(double* x);
void misc_stodbl5(double* x);
void restore4(int i);
void test_debug(char *msg);
void store4( double *d);
void storestr4( char *s);
void verb_serialSend();
void verb_serialReceive();
void verb_serialSet();
void verb_serialSetOld();			//03.04.02 GH
void verb_serialOpen();
void verb_serialClose();
void verb_serialDial();
void verb_serialHangUp();
void verb_serialReceiveWithEvent();	//02.26.02 GH
extern Boolean gOldSerialManager;	//03.04.02 GH
void verb_dbcreatedatabasefromresource();	//03.24.02 GH
Int16 getx();
Int16 gety();
extern misc_stodbl(struct dataelem *d,  UInt16 sub1,UInt16 sub2,UInt16 sub3, double  *result);
#else
extern misc_stodbl(PNOBlock *pnoP, struct dataelem *d,  UInt16 sub1,UInt16 sub2,UInt16 sub3, double  *result);
#endif

UInt16 miscFrmGetObjectIdFromPtr(const FormType *formP, void *objP);  //GH  01.10.2002


#ifdef __MC68K__
extern void verb_function_doit (UInt16 it);
#else
extern void verb_function_doit (PNOBlock *pnoP, UInt16 it);
#endif

void roundRtn(double* reg, Int16 noDecPos);
double misc_fabs(double x);
extern double misc_floor(double x);
extern double misc_ceil(double x);
extern double misc_int(double x);

#ifdef __MC68K__
int more_processing();
extern void misc_errmsg( char * the_msg);
void misc_format_time(struct dataelem* v, double* n , char * s);
unsigned int ue(struct dataelem *arg, double *arg_ad);        /*---calc integ value of data elem__*/
void restore4(int i);
void test_debug(char *msg);
void store4( double *d);
void storestr4( char *s);
extern void round_reg(double *reg,struct dataelem* de)   ;

void verb_func_setlocale();
void verb_func_format();
#else
void verb_func_setlocale(PNOBlock *pnoP);
void verb_func_format(PNOBlock *pnoP);
void misc_format_time(struct dataelem* v, double* n , char * s);
#endif

void cvt_time_to_hms(double t,Int16 *h, Int16 *m, Int16* s);


#ifdef __MC68K__
void verb_func_formatNL();


void restore_integ_value(int i,struct dataelem * arg,double * arg_ad,
unsigned int arg_occ1,unsigned int arg_occ2,unsigned int arg_occ3) ;
int dbug(char*s);
#endif

extern misc_format_date(struct dataelem*v,double*x,char*s);

typedef long DATE; /*Julian dates*/

DATE julian_date(Int16 day, Int16 month , Int16 year );
void calendar_date(DATE jdate, Int16 *day, Int16 *month, Int16 *year);

Int16 valid_date(Int16 day, Int16 month, Int16 year);

#ifdef __MC68K__
int day_of_week(DATE jdate );
extern misc_stostr(struct dataelem * *d, unsigned int  sub1,unsigned int  sub2,unsigned int  sub3, char *result);
#endif

#ifdef __MC68K__
extern double StrToDouble(char *s);
#else
extern double StrToDouble(PNOBlock *pnoP, char *s);
#endif

double cvt_date_to_dbl(Int16 yr,Int16 mo,Int16 da);

void cvt_date_to_ymd(double d,Int16 *yr, Int16 *mo, Int16* da);

#ifdef __MC68K__
extern void misc_free(void*,char *);

   Int16 funcNextEntry =0;
   Int16 funcs1To99      =0;
   Int16 funcs100To199   =0;
   Int16 funcs200To299   =0;
   Int16 funcs300To399   =0;
   Int16 funcs400To499   =0;
   Int16 funcs500To599   =0;
   Int16 funcs600To699   =0;
   Int16 funcs700To799   =0;
   VoidPtr funcTable[250];
#endif
   
   
#ifdef __MC68K__
extern void find_arg_1();
extern void find_arg_2();
extern void find_arg_3();
extern void find_arg_4();
extern void find_arg_5();
#else
extern void find_arg_1(PNOBlock *pnoP);
extern void find_arg_2(PNOBlock *pnoP);
extern void find_arg_3(PNOBlock *pnoP);
extern void find_arg_4(PNOBlock *pnoP);
extern void find_arg_5(PNOBlock *pnoP);
#endif

extern void *misc_allocate(unsigned int , char*);
extern void misc_getstr(struct dataelem* arg,int occ,char*name);
ULong TimGetSeconds() ;
extern unsigned int misc_getint(struct dataelem  *,unsigned int ,unsigned int * );

#define MAX_ARITH_PLUS_1          arith_work_de_max+1
#define MAX_ARITH_STRING_PLUS_1   arith_work_de_max+string_work_de_max+1

extern    int init_first_time ;
extern    unsigned int load_index_occ;
extern void move_it(char* a,unsigned int i,char* b,unsigned int j);
extern char master_quit_sw;
void verb_function_doit2( unsigned int it);
void verb_func_getGeneralPropertyNumeric();
#ifdef __MC68K__
void func_controlgetstatus();
void verb_func_getGeneralPropertyString();
#else
void func_controlgetstatus(PNOBlock *pnoP);
void verb_func_getGeneralPropertyString(PNOBlock *pnoP);
#endif
 
#ifdef __MC68K__
Int16 findControlsPositionOnForm(FormPtr * frmPtr,char * controlname);
#else
Int16 findControlsPositionOnForm(PNOBlock *pnoP, FormPtr * frmPtr,char * controlname);  //EMP
#endif
struct olddate
{
   unsigned char da_day;
   unsigned char da_mon;
   UInt16 da_year;
   unsigned char da_dayofweek;
} ;

struct tm
{
      Int16 tm_sec;
      Int16 tm_min;
      Int16 tm_hour;
      Int16 tm_mday;
      Int16 tm_mon;
      Int16 tm_year;
      Int16 tm_wday;
      Int16 tm_yday;
      Int16 tm_isdst;
};

struct timedef
{
       unsigned char ti_min;
       unsigned char ti_hour;
       unsigned char ti_hund;
       unsigned char ti_sec;
};


//*****************************************************************************************
Int16 asc(char c)
{
   return((Int16)c);
}
//*****************************************************************************************

void strlwr(Char * s)
{
   int i;
#ifdef __MC68K__
   for(i=0;i<StrLen(s);++i)
#else
   for(i=0;i<strlen(s);++i)
#endif
   {
      if ((*(s+i)<'A')||(*(s+i)>'Z')) continue;
      *(s+i)=*(s+i) + 'a'-'A';
   }
}


void strupr(Char * s)
{
   int i;
#ifdef __MC68K__
   for(i=0;i<StrLen(s);++i)
#else
   for(i=0;i<strlen(s);++i)
#endif
   {
      if ((*(s+i)<'a')||(*(s+i)>'z')) continue;
      *(s+i)=*(s+i)+'A'-'a';
   }
}

//*****************************************************************************************
Int16 isalpha(char  s)
{
  if (s<'a') return(0);
  if (s<='z') return(1);
  if (s<'A') return(0);
  if (s<='Z') return(1);
  return(0);
}

//*****************************************************************************************
void getdate(struct olddate * olddt)
{
  DateTimeType newdt;

  TimSecondsToDateTime(TimGetSeconds(),&newdt);

#ifndef __MC68K__
    {
        unsigned short s;
        s = newdt.second; newdt.second = ByteSwap16(s);
        s = newdt.minute; newdt.minute = ByteSwap16(s);
        s = newdt.hour; newdt.hour = ByteSwap16(s);
        s = newdt.day; newdt.day = ByteSwap16(s);
        s = newdt.month; newdt.month = ByteSwap16(s);
        s = newdt.year; newdt.year = ByteSwap16(s);
        s = newdt.weekDay; newdt.weekDay = ByteSwap16(s);
    }
#endif

  olddt->da_day=newdt.day;
  olddt->da_mon=newdt.month;
  olddt->da_year=newdt.year;
  olddt->da_dayofweek=newdt.weekDay;
}
//*****************************************************************************************
void gettime(struct timedef * t)
{
  DateTimeType newdt;
  TimSecondsToDateTime(TimGetSeconds(),&newdt);

#ifndef __MC68K__
    {
        unsigned short s;
        s = newdt.second; newdt.second = ByteSwap16(s);
        s = newdt.minute; newdt.minute = ByteSwap16(s);
        s = newdt.hour; newdt.hour = ByteSwap16(s);
        s = newdt.day; newdt.day = ByteSwap16(s);
        s = newdt.month; newdt.month = ByteSwap16(s);
        s = newdt.year; newdt.year = ByteSwap16(s);
        s = newdt.weekDay; newdt.weekDay = ByteSwap16(s);
    }
#endif

  t->ti_min=newdt.minute;
  t->ti_sec=newdt.second;
  t->ti_hour=newdt.hour;
  t->ti_hund=0;
}

//*****************************************************************************************
double  mypow10(Int16 i)   //modified 12182002
{
   double res=1;
   int k=0;
   
	if(i>=0)
	{
	   while (k < i)
	   {
	      k=k+1;
	      res=res*10;
	   }
    }
    else
    {
       while (k < (-i))
	   {
	      k=k+1;
	      res=res*10;
	   }
	   res = 1.0 / res;     // EMP increases accuracy
    
    }
    return(res);
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_instr()
#else
void verb_func_instr(PNOBlock *pnoP)
#endif
{
   //arg1=starting pos
   //arg2=string to search
   //arg3=string to find
   //arg5=case sens(0=yes,1=no)
    
    char wk[28];
    Int16 i;
    Int16 len;
    VoidHand h;
    char *p;
    VoidHand h3;
    char *p3;
    Int16 start;
    char *strPtr;   //added 07212003
    double d;

#ifdef __MC68K__
    h=MemHandleNew(StrLen(arg2_val)+1);
    if(h==0) OutOfMemory(6070);  //05282003
    p=(char*)MemHandleLock(h);
    StrCopy(p,(char*)arg2_val);
#else
    h=MemHandleNew(strlen(PNO(args)[1].val)+1);
    if(h==0) OutOfMemory(6070);  //05282003
    p=(char*)MemHandleLock(h);
    strcpy(p,(char*)PNO(args)[1].val);
#endif
    
#ifdef __MC68K__
    h3=MemHandleNew(StrLen(arg3_val)+1);
    if(h3==0) OutOfMemory(6071);  //05282003
    p3=(char*)MemHandleLock(h3);
    StrCopy(p3,(char*)arg3_val);
#else
    h3=MemHandleNew(strlen(PNO(args)[2].val)+1);
    if(h3==0) OutOfMemory(6071);  //05282003
    p3=(char*)MemHandleLock(h3);
    strcpy(p3,(char*)PNO(args)[2].val);
#endif
    
//StrPrintF(debug,"instr--  in=%s  srch=%s",p,p3);
//dbug(debug);
#ifdef __MC68K__   
    if( *((double*)arg5_val) != 0.0)  //caseless
#else
    d = ReadUnaligned64(PNO(args)[4].val);
    if (d != 0.0)
#endif
    {
      StrToLower(p,p);
      StrToLower(p3,p3);
    }
#ifdef __MC68K__
    len=StrLen(p3);
    start=integ_value(arg1,(double*)arg1_val)-1;
#else
    len=strlen(p3);
    d = ReadUnaligned64(PNO(args)[0].val);
    start = d - 1;
#endif
//StrPrintF(debug,"start=%d lenp=%d lenp3=%d",start,StrLen(p),len);
//dbug(debug);
    //01262003 if((start<0)||(start>StrLen(p)))
#ifdef __MC68K__
    if((start<0)||((start+len)>StrLen(p)))     //01262003
#else
    if((start<0)||((start+len)>strlen(p)))     //01262003
#endif
    {
       i=0;
       goto getOut;
    }
//07212003    for (i=start;i<=(StrLen(p)-StrLen(p3));++i)
//07212003    {
//07212003
//07212003      if (MemCmp((char*)p+i,(char*)p3,len)==0)
//07212003      {
//07212003         i=i+1;
//07212003         goto getOut;
//07212003      }
//07212003    }
    strPtr=StrStr(p+start,p3);      //added 07212003
    if(strPtr!=0)				//added 07212003
    {							//added 07212003
       i=strPtr-p+1;			//added 07212003
       goto getOut; 			//added 07212003  
    }							//added 07212003
    
    i=0;
getOut:
    MemPtrUnlock(p);
    MemHandleFree(h);
    MemPtrUnlock(p3);
    MemHandleFree(h3);
#ifdef __MC68K__
    restore4(i);
#else
   d = i;
   d = SwapDouble(d);
   misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &d);
#endif
}

//*****************************************************************************************
extern Int16 cvt_string_to_ymd( char *ad, Int16 *y,Int16 *m,Int16 *d)
{
    Int16 i;
    Int16 res = 0;
    char *save_ad= ad;

    char wk[20];
    if(*(ad+2)=='/')
    {
      wk[0]='1';
      wk[1]='9';
    }
    else
    {
      wk[0]=*(ad++);
      wk[1]=*(ad++);
    }
    i=2;
    wk[i++]=*(ad++);
    wk[i++]=*(ad++);
    wk[i]=0x00;
    
    *y=StrAToI(wk);
    if(*ad!='/') res=1;
    ad += 1;
    i=0;
    if(*(ad+2)=='/') {wk[i++]=*(ad++);}
    else wk[i++]='0';
    wk[i++]=*ad++;
    wk[i]=0x00;
    *m=StrAToI(wk);
    
    if(*ad!='/') res=1;
    ad += 1;
    i=0;
    if(*(ad+2)==0x00) wk[i++]=*ad++;
    else wk[i++]='0';
    wk[i++]=*ad;
    wk[i]=0x00;
    
    *d=StrAToI(wk);
/*----
StrPrintF(debug,"cvt-string '%s' yr=%i mo=%i da=%i",save_ad,*y,*m,*d);
test_debug(debug);
----*/
    return(res);  /*1=invalid 0=valid*/
}

//*****************************************************************************************
extern Int16 cvt_mmddyystring_to_ymd( char *ad, Int16 *y,Int16 *m,Int16 *d)
{
    Int16 i;
    Int16 res = 0;
    char *save_ad= ad;

    char wk[20];
    
    
    //month
    i=0;
    if(*(ad+2)=='/') {wk[i++]=*(ad++);}
    else wk[i++]='0';
    wk[i++]=*ad++;
    wk[i]=0x00;
    *m=StrAToI(wk);
    
    //day
    if(*ad!='/') res=1;
    ad += 1;
    i=0;
    if(*(ad+2)=='/') wk[i++]=*ad++;
    else wk[i++]='0';
    wk[i++]=*ad++;
    wk[i]=0x00;
    *d=StrAToI(wk);

    //year
    if(*ad!='/') res=1;
    ad += 1;
    if(*(ad+2)==0x00)
    {
      wk[0]='1';
      wk[1]='9';
    }
    else
    {
      wk[0]=*(ad++);
      wk[1]=*(ad++);
    }
    i=2;
    wk[i++]=*(ad++);
    wk[i++]=*(ad++);
    wk[i]=0x00;
    *y=StrAToI(wk);
    
/*----
StrPrintF(debug,"cvt-string '%s' yr=%i mo=%i da=%i",save_ad,*y,*m,*d);
test_debug(debug);
----*/
    return(res);  /*1=invalid 0=valid*/
}

#ifdef __MC68K__
//*****************************************************************************************
extern int cvt_string_to_hms( char *ad, int *h,int *m,int *s)
{
    int i;
    int res = 0;
    char *save_ad= ad;

    char wk[20];
    if(*(ad+2)==':')
    {
       i=0;
    }
    else    if(*(ad+1)==':')
    {
      wk[0]='0';
      i=1;
    }
    else return(1);
    wk[i++]=*(ad++);
    if(*ad != ':') wk[i++]=*(ad++);
    wk[i]=0x00;
    
    *h=StrAToI(wk);
    if(*ad!=':') res=1;
    ad += 1;
    i=0;
    if(*(ad+2)==':') {wk[i++]=*(ad++);}
    else wk[i++]='0';
    wk[i++]=*ad++;
    wk[i]=0x00;
    
    *m=StrAToI(wk);
    if(*ad!=':') res=1;
    ad += 1;
    i=0;
    if(*(ad+2)==0x00) wk[i++]=*ad++;
    else wk[i++]='0';
    wk[i++]=*ad;
    wk[i]=0x00;
    
    *s=StrAToI(wk);
/*----
StrPrintF(debug,"cvt-string '%s' yr=%i mo=%i da=%i",save_ad,*y,*m,*d);
test_debug(debug);
----*/
    return(res);  /*1=invalid 0=valid*/
}
#endif

//*****************************************************************************************
double cvt_date_to_dbl(Int16 yr,Int16 mo,Int16 da)
{
    double a;
    double b;
    double c;
    double e;

    if( yr>99) a=(yr-1900);
    else       a=yr;
    a=a*10000;
    b=mo*100;
    c=da;
    e=a+b+c;

    return(e);
}
//*****************************************************************************************
double cvt_time_to_dbl(Int16 hr,Int16 min,Int16 sec)
{
    double a;
    double b;
    double c;
    double e;
  

    a=hr;
    a=a*10000;
    b=min*100;
    c=sec;
    e=a+b+c;


//StrPrintF(debug,"at cvt time hr=%i min=%i sec=%i  ",hr,min,sec);
//dbug(debug);
    return(e);
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_chr()
#else
void verb_func_chr(PNOBlock *pnoP)
#endif
{
#ifdef __MC68K__
   char s[2];
   s[1]=0x00;
   s[0]=integ_value(arg1,(double*)arg1_val);
   storestr4(&s[0]);
#else
   char s[2];
   double d;
   d = ReadUnaligned64(PNO(args)[0].val);
   s[1]='\0';
   s[0]=d;
   misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, s);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_abs()
#else
void verb_func_abs(PNOBlock *pnoP)
#endif
{
#ifdef __MC68K__
   reg_a=*((double*)arg1_val);
   reg_a=misc_fabs(reg_a);
   store4( &reg_a );
#else
   double d;
   d = ReadUnaligned64(PNO(args)[0].val);
   if (d < 0.0) d = -d;
   d = SwapDouble(d);
   misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &d);
   
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_ascii()
#else
void verb_func_ascii(PNOBlock *pnoP)
#endif
{
    unsigned char c;
#ifdef __MC68K__
    c=*((char*)arg1_val);
    reg_a=c;
    store4(&reg_a);
#else
    double reg_a;
    c=*((char*)PNO(args)[0].val);
    reg_a=c;
    reg_a = SwapDouble(reg_a);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &reg_a);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_int()
#else
void verb_func_int(PNOBlock *pnoP)
#endif
{
   double d;

#ifdef __MC68K__
   reg_a=*((double*)arg1_val);
#else
   double reg_a;
   reg_a = ReadUnaligned64(PNO(args)[0].val);
#endif
    d=misc_floor(misc_fabs(reg_a));

    if(reg_a < 0.0) d = - d;
    
#ifdef __MC68K__
    store4(&d);
#else
    d = SwapDouble(d);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &d);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_mod()
#else
void verb_func_mod(PNOBlock *pnoP)
#endif
{
   
    double t;

#ifdef __MC68K__
   reg_a=*((double*)arg1_val);
   reg_b=*((double*)arg2_val);
#else
    double reg_a, reg_b;
    reg_a = ReadUnaligned64(PNO(args)[0].val);
    reg_b = ReadUnaligned64(PNO(args)[1].val);
#endif
   roundRtn(&reg_a,0); //round up to integer
   roundRtn(&reg_b,0); //same
   
   t=misc_int(reg_a/reg_b);      //10.10.2000
   reg_a-=t*reg_b;         // EMP more efficient

#ifdef __MC68K__
   store4(&reg_a);
#else
    reg_a = SwapDouble(reg_a);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &reg_a);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_nooccurs()
#else
void verb_func_nooccurs(PNOBlock *pnoP)
#endif
{
    Int16 which;
    double d;
#ifdef __MC68K__
    which=integ_value(arg2,(double*)arg2_val);
#else
    Int16 n;
    d = ReadUnaligned64(PNO(args)[1].val);
    which = d;
#endif
    
#ifdef __MC68K__
    if (which==1) d=arg1->max_no_values1;
    else
    {
      if (which==2) d=arg1->max_no_values2;
      else
      {
        if (which==3) d=arg1->max_no_values3;
        else d=0;
      }
    }
#else
    if (which==1) n=PNO(args)[0].dataElem->max_no_values1;
    else
    {
      if (which==2) n=PNO(args)[0].dataElem->max_no_values2;
      else
      {
        if (which==3) n=PNO(args)[0].dataElem->max_no_values3;
        else n=0;
      }
    }
#endif

#ifdef __MC68K__
    store4(&d);
#else
    n = ByteSwap16(n);
    d = n;
    d = SwapDouble(d);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &d);
#endif
   
    return;
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_power10()
#else
void verb_func_power10(PNOBlock *pnoP)
#endif
{
   double d;
   Int16 j;
   Int16 i;
   Int16 absj;
#ifdef __MC68K__
   reg_a=*((double*)arg1_val);
   j=integ_value(arg2,(double*)arg2_val);
#else
    double reg_a, reg_b;
    reg_a = ReadUnaligned64(PNO(args)[0].val);
    d = ReadUnaligned64(PNO(args)[1].val);
    j = d;
#endif

   if(j<0) absj=-j;
   else absj=j;
   d=1.0;
   for(i=1;i<=absj;++i) d*=10.0; 
   if (j>=0) reg_b=d;
   else reg_b=1.0/d;
   reg_a*=reg_b;
#ifdef __MC68K__
   store4(&reg_a);
#else
    reg_a = SwapDouble(reg_a);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &reg_a);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_rand()
#else
void verb_func_rand(PNOBlock *pnoP)
#endif
{
   double wk;
   ULong i;
#ifndef __MC68K__
    double reg_a;
#endif
  
   i=0;
   i=  SysRandom ( i );
   wk=i;
   reg_a= wk /((double)sysRandomMax+1); //01/19/03 GH: prevent value of 1.0000
#ifdef __MC68K__
   store4(&reg_a);
#else
    reg_a = SwapDouble(reg_a);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &reg_a);

#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_round()
#else
void verb_func_round(PNOBlock *pnoP)
#endif
{
    double w;
    char wk[25];
    Int16 k;
    Int16 i;
    Int16 j;
    
#ifdef __MC68K__
    k=integ_value(arg2,(double*)arg2_val);          //#decimal places to round after
    misc_format_number(arg1,(double*)arg1_val,wk);  //first get number into ascii string
#else
    double d;
    k = ReadUnaligned64(PNO(args)[1].val);
	d = ReadUnaligned64(PNO(args)[0].val);
	d = SwapDouble(d);
	misc_format_number(pnoP, PNO(args)[0].dataElem, &d, wk);
	d = SwapDouble(d);
#endif


    //may have to grow the string (e.g. 9.5 rounded becomes 10.0), so expand one char
#ifdef __MC68K__
    for(i=StrLen(wk);i>=0;--i)  wk[i+1]=wk[i];
#else
    for(i=strlen(wk);i>=0;--i)  wk[i+1]=wk[i];
#endif
    if(wk[0]=='-') wk[1]='0';
    else           wk[0]='0';
#ifdef __MC68K__
    for(i=0;i<StrLen(wk);++i)
#else
    for(i=0;i<strlen(wk);++i)
#endif
    {
      if (wk[i]=='.') goto foundDecPoint;
    }
    //number is an integer, so no rounding required
#ifdef __MC68K__
    w=*((double*)arg1_val);
#else
	w = d;
#endif
    goto itsSet;
foundDecPoint:
#ifdef __MC68K__
    if( StrLen(wk) < i+k+2)
    {
       w=*((double*)arg1_val);   //it doesn't have enuf dgts to round
       goto itsSet;
    }
#else
	if (strlen(wk) < i + k + 2)
	{
		w = d;
		goto itsSet;
	}
#endif
       //has more dec places than wanted, so we can round
       if( wk[i+k+1] >='5')
       {
           
 //StrPrintF(debug,"wk=%s i=%d",wk,i);
 //dbug(debug);
                  //round prior digit and if it was '9' keep adding one as work to the left
                  j=i+k;
                  while (j >= 0)
                  {
                    if( (wk[j]==' ') || (wk[j]=='-')) break;  //should not happen
                    
                    if(wk[j]!='.' )
                    {
                       if (wk[j] < '9' )
                       {
                          wk[j]=wk[j]+1;
                          break;          //can quit--no dgts to the left need adjustment
                       }
                       else
                       {
                          wk[j]='0';   //set this dgt to 0 and continue to the left to add 1
                       }
                    }
                    --j;
                  }
          
       }
       else
       {
          
       }
       wk[i+k+1]=0x00;      //truncate after k dec places
#ifdef __MC68K__
       w=StrToDouble(wk);   //and convert back to double
#else
	   w = StrToDouble(pnoP, wk);
#endif   
itsSet:
#ifdef __MC68K__
   store4(&w);
#else
	w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);

#endif
}


//*****************************************************************************************
void roundRtn(  double* reg, Int16 noDecPos)
{
    double d1;
    double d2;
    double d3;
    double d4;

    d1=mypow10(noDecPos);       //modified 12182002
    d2=*reg * d1;                /*xxyyy.zzz*/
    d3=misc_floor (misc_fabs(d2));       /*xxyyy*/
    if(d2<0) d3= -d3;

    d4= d2-d3 ;               /*zzz*/
    d4=misc_fabs (d4);

    if((d4>=.5)||(d4<=-.5))
    {
       if(*reg>0.0)d3=d3+1;
       else      d3=d3-1;
    }
    *reg=d3/d1;
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_left()
#else
void verb_func_left(PNOBlock *pnoP)
#endif
{

    Int16 i;
    VoidHand h;
    char *p;
#ifdef __MC68K__
    i=integ_value(arg2,(double*)arg2_val);
    if(i>StrLen(arg1_val)) i=StrLen((char*)arg1_val);
#else
    double d;
    d = ReadUnaligned64(PNO(args)[1].val);
    i = d;
    if(i>strlen(PNO(args)[0].val)) i=strlen((char*)PNO(args)[0].val);
#endif
	if (i < 0) i = 0;
    h=MemHandleNew(i+1);
    if(h==0) OutOfMemory(6072);  //05282003
    p=(char*)MemHandleLock(h);
#ifdef __MC68K__
    MemMove(p,arg1_val,i);
#else
    MemMove(p,PNO(args)[0].val,i);
#endif
	*(p + i) = 0x00;
#ifdef __MC68K__
    storestr4(p);
#else
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, p);
#endif
    MemPtrUnlock(p);
    MemHandleFree(h);
    return;
}
//*****************************************************************************************
#ifdef __MC68K__
void verb_func_right()
#else
void verb_func_right(PNOBlock *pnoP)
#endif
{
    VoidHand h;
    char *p;

    Int16 j;
    Int16 i;
#ifdef __MC68K__
    i=integ_value(arg2,(double*)arg2_val);
    if(i>StrLen(arg1_val)) i=StrLen((char*)arg1_val);
#else
    double d;
    d = ReadUnaligned64(PNO(args)[1].val);
    i = d;
    if(i>strlen(PNO(args)[0].val)) i=strlen((char*)PNO(args)[0].val);
#endif
    if(i<0)                i=0;

    h=MemHandleNew(i+1);
    if(h==0) OutOfMemory(6075);  //05282003 
    p=(char*)MemHandleLock(h);
#ifdef __MC68K__
    j=StrLen(arg1_val)-i;
    MemMove(p,(char*)arg1_val+j,i);
#else
    j=strlen(PNO(args)[0].val)-i;
    MemMove(p,(char*)PNO(args)[0].val+j,i);
#endif

	*(p + i) = 0x00;

#ifdef __MC68K__
    storestr4(p);
#else
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, p);
#endif

    MemPtrUnlock(p);
    MemHandleFree(h);
}
//*****************************************************************************************
#ifdef __MC68K__
void verb_func_length()
#else
void verb_func_length(PNOBlock *pnoP)
#endif
{
#ifdef __MC68K__
    restore4(StrLen(arg1_val));
#else
    double d;
    d = strlen(PNO(args)[0].val);
    d = SwapDouble(d);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &d);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_geteventtype()
#else
void verb_func_geteventtype(PNOBlock *pnoP)
#endif
{
#ifdef __MC68K__
     restore4(PNO(eventType));
#else
    double d;
    d = PNO(eventType);
    d = SwapDouble(d);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &d);
#endif
}


//*****************************************************************************************
#ifdef __MC68K__
void verb_func_syseventavailable()
#else
void verb_func_syseventavailable(PNOBlock *pnoP)
#endif
{
    //returns 1 if an event pending else 0
    Int16 type;
    type=0;
    //12172001 if(EvtSysEventAvail(true)) type=1;
    //if(EvtSysEventAvail(false)) type=1;
    if(EvtSysEventAvail(true)) type=1;
    else
    {
         if(EvtKeyQueueEmpty()) {}
         else type=1;
    }
#ifdef __MC68K__
    restore4(type);
#else
    {
        double d;
        d = type;
        d = SwapDouble(d);
        misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &d);
    }
#endif
}

#ifdef __MC68K__
//*****************************************************************************************
void verb_func_maxlength()
{
    restore4(arg1->length);
    return;
}
#endif

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_lower()
#else
void verb_func_lower(PNOBlock *pnoP)
#endif
{
    VoidHand h;
    char *p;
#ifdef __MC68K__
    h=MemHandleNew(StrLen(arg1_val)+1);
#else
    h=MemHandleNew(strlen(PNO(args)[0].val)+1);
#endif
    if(h==0) OutOfMemory(6076);  //05282003
    p=(char*)MemHandleLock(h);

#ifdef __MC68K__
    StrCopy(p,(char*)arg1_val);
#else
    strcpy(p,(char*)PNO(args)[0].val);
#endif
    strlwr(p);
#ifdef __MC68K__
    storestr4(p);
#else
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, p);
#endif
    MemPtrUnlock(p);
    MemHandleFree(h);
    return;
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_mid()
#else
void verb_func_mid(PNOBlock *pnoP)
#endif
{
    Int16 i,j;
    VoidHand h;
    char *p;
#ifdef __MC68K__
    h=MemHandleNew(StrLen(arg1_val)+1);
#else
    double d;
    h=MemHandleNew(strlen(PNO(args)[0].val)+1);
#endif
    if(h==0) OutOfMemory(6078);  //05282003
    p=(char*)MemHandleLock(h);

#ifdef __MC68K__
    i=integ_value(arg2,(double*)arg2_val);
    j=integ_value(arg3,(double*)arg3_val);
    if((j<=0) ||  (i>StrLen(arg1_val)) )  //modified 02/012001 to check j<=0
#else
    d = ReadUnaligned64(PNO(args)[1].val);
    i = d;
    d = ReadUnaligned64(PNO(args)[2].val);
    j = d;
    if((j<=0) ||  (i>strlen(PNO(args)[0].val)) )
#endif    
    {
        //return a null string
        *p=0x00;
    }
    else
    {
      --i;
#ifdef __MC68K__
      if((StrLen((char*)arg1_val)-i)<j) j=StrLen((char*)arg1_val)-i;
      MemMove(p,(char*)arg1_val+i,j);
#else
      if((strlen((char*)PNO(args)[0].val)-i)<j) j=strlen((char*)PNO(args)[0].val)-i;
      MemMove(p,(char*)PNO(args)[0].val+i,j);
#endif
	  *(p + j) = 0x00;
    
      MemSet(p+j,1,0x00);
    }
#ifdef __MC68K__
    storestr4(p);
#else
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, p);
#endif
    MemPtrUnlock(p);
    MemHandleFree(h);
    return;
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_tonumber()  //VAL(strx)    func_val
#else
void verb_func_tonumber(PNOBlock *pnoP)  
#endif
{
    double f;
//char wk1[45];
//char wk2[45];    
// union 
//       {
//            FlpDouble q;
//            double d;
//       } x;
         

#ifdef __MC68K__       
       f=StrToDouble(arg1_val) ;
#else
    f = StrToDouble(pnoP, PNO(args)[0].val);
#endif
       
       
//StrPrintF(debug,"in val tblno=%d functionstr=%s",arg1->tbl_no,(char*)arg1_val);
//dbug(debug);
//dbugx(&f,"in VAL function");
    
//x.q=FlpAToF((char*)arg1_val);
 
//f2=x.d;
//printDouble(f,wk1);
//printDouble(f2,wk2);
//StrPrintF(debug,"string=%s  f1=%s  f2=%s",arg1_val,wk1,wk2);
//dbug(debug); 
#ifdef __MC68K__
    store4( &f);
#else
    f = SwapDouble(f);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &f);
#endif
//dbugx(&f,"leaving val function");

}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_tostring()
#else
void verb_func_tostring(PNOBlock *pnoP)
#endif
{
    char work[40];
//dbugx(((double*)arg1_val),"atstartof func_tostring");
//StrPrintF(debug,"tostring is for tblno=%d",arg1->tbl_no);
//dbug(debug);
#ifdef __MC68K__
    misc_format_number(arg1,(double*)arg1_val,work);
    storestr4(work);
#else
    misc_format_number(pnoP, PNO(args)[0].dataElem, (double *) PNO(args)[0].val, work);
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, work);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_proper()
#else
void verb_func_proper(PNOBlock *pnoP)
#endif
{
    VoidHand h;
    char *p;
    
    char* ad;

#ifdef __MC68K__
    h=MemHandleNew(StrLen(arg1_val)+1);
#else
    h=MemHandleNew(strlen(PNO(args)[0].val)+1);
#endif
    if(h==0) OutOfMemory(6079);  //05282003
    p=(char*)MemHandleLock(h);

    
#ifdef __MC68K__
    StrCopy(p,(char*)arg1_val);
#else
    strcpy(p,(char*)PNO(args)[0].val);
#endif
    ad=p;
    while(*ad != 0x00)
    {
      if(*ad==' ') {++ad;continue;}
      if( ((*ad>='a'&&*ad<='z')) || ((*ad>='A'&&*ad<='Z')) )
      {
         if ((*ad>='a')&&(*ad<='z')) *ad=*ad+asc('A')-asc('a');
         ++ad;
         while( (*ad!=0x00)&&(*ad!=' '))
         {
            if ((*ad>='A')&& (*ad<='Z')) *ad=*ad+asc('a')-asc('A');
            ++ad;
         }
      }
      else
      {
         ++ad;
         while ( (*ad!=0x00)&&(*ad!=' ')) ++ad;
      }
    }
#ifdef __MC68K__
    storestr4(p);
#else
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, p);
#endif
    MemPtrUnlock(p);
    MemHandleFree(h);
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_upper()
#else
void verb_func_upper(PNOBlock *pnoP)
#endif
{
    VoidHand h;
    char *p;
#ifdef __MC68K__
    h=MemHandleNew(StrLen(arg1_val)+1);
#else
    h=MemHandleNew(strlen(PNO(args)[0].val)+1);
#endif
    if(h==0) OutOfMemory(6076);  //05282003
    p=(char*)MemHandleLock(h);

#ifdef __MC68K__
    StrCopy(p,(char*)arg1_val);
#else
    strcpy(p,(char*)PNO(args)[0].val);
#endif
    strupr(p);
#ifdef __MC68K__
    storestr4(p);
#else
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, p);
#endif
    MemPtrUnlock(p);
    MemHandleFree(h);
    return;
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_popupdate()
#else
void verb_func_popupdate(PNOBlock *pnoP)
#endif
{
  //ldm 09122004 don't know why, but call to SelectDay is destroying arg1 and arg4
  //ldm 09122004 so put in a save/restore for these two variables
  Boolean z;
  Int16 yr;
  Int16 mo;
  Int16 da;
  double d;
  char s[25];

#ifdef __MC68K__
  struct dataelem* saveArg1 = arg1;  //09122004
  struct dataelem* saveArg4 = arg4;  //09122004
#endif
  PNO(msgboxOrAlertUp) = true;

#ifdef __MC68K__
  cvt_date_to_ymd(*((double*)arg1_val),&yr,&mo,&da);
#else
  d = ReadUnaligned64(PNO(args)[0].val);
  cvt_date_to_ymd(d,&yr,&mo,&da);
#endif

#ifdef __MC68K__
  z=SelectDay(selectDayByDay,(SWord*)(&mo),(SWord*)(&da),(SWord*)(&yr),arg2_val);  //arg2 is title
#else
  z=SelectDay(selectDayByDay,(SWord*)(&mo),(SWord*)(&da),(SWord*)(&yr),PNO(args)[1].val);  //arg2 is title
#endif
  if(z==true)
  {
    d=cvt_date_to_dbl(yr,mo,da);
#ifdef __MC68K__
    arg1 = saveArg1;          //09122004
    misc_stodbl1(&d);
#else
    d = SwapDouble(d);
    misc_stodbl(pnoP, PNO(args)[0].dataElem, PNO(args)[0].occ1, PNO(args)[0].occ2, PNO(args)[0].occ3, &d);
#endif
    d=1.0;
#ifdef __MC68K__
    arg4 = saveArg4;           //09122004
    store4(&d);   //1=chg'd
#else
    d = SwapDouble(d);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &d);
#endif
  }
  else
  {
    d=0.0;
#ifdef __MC68K__
    arg4 = saveArg4;           //09122004
    store4(&d);   //1=chg'd
#else
    d = SwapDouble(d);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &d);
#endif
  }
  PNO(msgboxOrAlertUp) = false;
}
//*****************************************************************************************
#ifdef __MC68K__
void verb_func_popuptime()
#else
void verb_func_popuptime(PNOBlock *pnoP)
#endif
{
  Boolean z;
  Int16 hr;
  Int16 min;
  Int16 sec;
  TimeType start;
  TimeType end;
  double d;
  //SWord startOfDay;
  //ldm 09122004 don't know why, but call to SelectDay is destroying arg1 and arg4
  //ldm 09122004 so put in a save/restore for these two variables

#ifdef __MC68K__
  //ldm 09122004 don't know why, but call to SelectDay is destroying arg1 and arg4
  //ldm 09122004 so put in a save/restore for these two variables
  struct dataelem *saveArg4;   //ldm 09132004
  struct dataelem *saveArg1;   //ldm09132004
  struct dataelem *saveArg2;   //ldm09132004
  cvt_time_to_hms(*(double*)arg1_val,&hr,&min,&sec);
#else
  d = ReadUnaligned64(PNO(args)[0].val);
  cvt_time_to_hms(d,&hr,&min,&sec);
#endif
  start.hours=hr;
  start.minutes=min;
  //if(start.hours==0) start.hours=8;					//03.12.03 GWH
  if(start.hours+start.minutes==0) start.hours=8;		//11.03.06 GWH

#ifdef __MC68K__
  cvt_time_to_hms(*(double*)arg2_val,&hr,&min,&sec);
#else
  d = ReadUnaligned64(PNO(args)[1].val);
  cvt_time_to_hms(d,&hr,&min,&sec);
#endif

  end.hours=hr;
  end.minutes=min;
  //if(end.hours==0) end.hours=17;						//03.12.03 GWH
  if(end.hours+end.minutes==0) end.hours=17;			//11.03.06 GWH
  //startOfDay=8;										//11.03.06 GWH

#ifdef __MC68K__
  saveArg1=arg1;
  saveArg2=arg2;
  saveArg4=arg4;
#endif
  PNO(msgboxOrAlertUp) = true;

  if(PNO(romVersion)>=(unsigned long)(0x03500000))
  {
     //z=SelectTime(&start,&end,false,arg3_val,8,5,8);  //03.12.03 GWH
#ifdef __MC68K__
     z=SelectTime(&start,&end,false,arg3_val,start.hours,end.hours,start.hours);  //arg2 is title
#else
     z=SelectTime(&start,&end,false,PNO(args)[2].val,start.hours,end.hours,start.hours);  //arg2 is title
#endif
  }
  else
  {
    //z=SelectTimeV33(&start,&end,false,arg3_val,8);  //arg2 is title //03.12.03 GWH
#ifdef __MC68K__
    z=SelectTimeV33(&start,&end,false,arg3_val,start.hours);  //arg2 is title
#else
    SysFatalAlert("Version < 5 with PNO?");
#endif
  }

#ifdef __MC68K__
  arg1=saveArg1;  //ldm09132004
  arg2=saveArg2;  //ldm09132004
  arg4=saveArg4;  //ldm09132004
#endif

  if(z==true)
  {
    hr=start.hours;
    min=start.minutes;
//StrPrintF(debug,"after popup starttime hr=%d min=%d",hr,min);
//dbug(debug);
    sec=0;
    if(hr==255)   //no time
    {
       hr=0;
       min=0;
    }
    d=cvt_time_to_dbl(hr,min,sec);
#ifdef __MC68K__
    misc_stodbl1(&d);
#else
    d = SwapDouble(d);
    misc_stodbl(pnoP, PNO(args)[0].dataElem, PNO(args)[0].occ1, PNO(args)[0].occ2, PNO(args)[0].occ3, &d);
#endif

    hr=end.hours;
    min=end.minutes;
//StrPrintF(debug,"after endtime popup hr=%d min=%d",hr,min);
//dbug(debug);

    sec=0;
    if(hr==255)  //no time
    {
       hr=0;
       min=0;
    }   
    d=cvt_time_to_dbl(hr,min,sec);
#ifdef __MC68K__
    misc_stodbl2(&d);
#else
    d = SwapDouble(d);
    misc_stodbl(pnoP, PNO(args)[1].dataElem, PNO(args)[1].occ1, PNO(args)[1].occ2, PNO(args)[1].occ3, &d);
#endif
    d=1.0;
#ifdef __MC68K__
    store4(&d);   //1=chg'd
#else
    d = SwapDouble(d);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &d);
#endif
  }
  else
  {
    d=0.0;
#ifdef __MC68K__
    store4(&d);   //1=chg'd
#else
    d = SwapDouble(d);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &d);
#endif

  }
  PNO(msgboxOrAlertUp) = false;
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_todate()
#else
void verb_func_todate(PNOBlock *pnoP)
#endif
{
    char *ad;

    Int16 res;
    Int16 y,m,d;
    char errmsg[80];
    double w;

#ifdef __MC68K__
    ad=(char*)arg1_val;
#else
    ad=(char*)PNO(args)[0].val;
#endif

    res=cvt_string_to_ymd( ad,&y,&m,&d);

    if(res==0)
    {
       res=valid_date(d,m,y);
       if(res==0) res=1;
       else       res=0;
    }
    
    if(res)
    {
#ifdef __MC68K__
       StrPrintF(errmsg,"String '%s' is not a valid date.",ad);
       misc_errmsg(errmsg);
#else
       char *b;
       b = errmsg;
       b = strcpy(b, "String '");
       b = strcpy(b, ad);
       strcpy(b, "' is not a valid date.");
       misc_errmsg(pnoP, errmsg);
#endif
    }

    w=cvt_date_to_dbl(y,m,d);
#ifdef __MC68K__
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
#endif
    return;
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_yearmonth()
#else
void verb_func_yearmonth(PNOBlock *pnoP)
#endif
{
    char work[20];
#ifdef __MC68K__    
    misc_format_date(arg1,(double*)arg1_val,work);
#else
    double d;
    d = ReadUnaligned64(PNO(args)[0].val);
    d = SwapDouble(d);
    misc_format_date(PNO(args)[0].dataElem, &d, work);
#endif    
	work[7]=0x00;
    
#ifdef __MC68K__
    storestr4(work);
#else
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, work);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_datemmddyy()
#else
void verb_func_datemmddyy(PNOBlock *pnoP)
#endif
{
    char dat[20];
    char work[20];

#ifdef __MC68K__
    misc_format_date(arg1,(double*)arg1_val,dat);
#else
    double d;
    d = ReadUnaligned64(PNO(args)[0].val);
    d = SwapDouble(d);
    misc_format_date(PNO(args)[0].dataElem,&d,dat);
#endif

#ifdef __MC68K__
    StrCopy(work,&dat[5]);
    dat[4]=0x00;
    StrCat(work,"/");
    StrCat(work,dat);
#else
    strcpy(work,&dat[5]);
    dat[4]=0x00;
    strcat(work,"/");
    strcat(work,dat);
#endif

#ifdef __MC68K__
    storestr4(work);
#else
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, work);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_monthday()
#else
void verb_func_monthday(PNOBlock *pnoP)
#endif
{
    Int16 i;
    char work[20];

#ifdef __MC68K__    
    misc_format_date(arg1,(double*)arg1_val,work);
#else
    double d;
    d = ReadUnaligned64(PNO(args)[0].val);
    d = SwapDouble(d);
    misc_format_date(PNO(args)[0].dataElem, &d, work);
#endif
    for(i=0;i<6;++i) work[i]=work[i+5];

#ifdef __MC68K__
    storestr4(work);
#else
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, work);
#endif
}
//*****************************************************************************************
#ifdef __MC68K__
void verb_func_hourmin()
#else
void verb_func_hourmin(PNOBlock *pnoP)
#endif
{
    char work[20];
#ifdef __MC68K__    
    misc_format_time(arg1,(double*)arg1_val,work);
#else
    double d;
    d = ReadUnaligned64(PNO(args)[0].val);
    d = SwapDouble(d);
    misc_format_time(PNO(args)[0].dataElem, &d, work);
#endif
    work[5]=0x00;
    
#ifdef __MC68K__
    storestr4(work);
#else
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, work);
#endif
}
//*****************************************************************************************
#ifdef __MC68K__
void verb_func_hourminampm()
#else
void verb_func_hourminampm(PNOBlock *pnoP)
#endif
{
    char work[20];
    Int16 hh;
    Int16 mm;
    Int16 ss;
    double tim;
    char ampm[4];

#ifdef __MC68K__
    tim=*((double*)arg1_val);
#else
    tim = ReadUnaligned64(PNO(args)[0].val);
#endif


//misc_format_time(arg1,&tim,work);
//StrPrintF(debug,"*5*time is %s",work);
//dbug(debug);
    cvt_time_to_hms(tim,&hh,&mm,&ss);
//StrPrintF(debug,"*10*in hourminampm hr=%d min=%d sec=%d",hh,mm,ss);
//test_debug(debug);
    /*" pm"*/

#ifdef __MC68K__
    if(hh>11){ StrCopy(ampm," pm"); if(hh>12) hh=hh-12; }
    /*" am"*/
    else      StrCopy(ampm," am");
#else
    if(hh>11){ strcpy(ampm," pm"); if(hh>12) hh=hh-12; }
    /*" am"*/
    else      strcpy(ampm," am");
#endif
    if(hh==0) hh=12;
    tim=cvt_time_to_dbl(hh,mm,ss);
#ifdef __MC68K__
    misc_format_time (arg1,&tim,work);
#else
	tim = SwapDouble(tim);
    misc_format_time (PNO(args)[0].dataElem,&tim,work);
    tim = SwapDouble(tim);
#endif
    work[5]=0x00;
#ifdef __MC68K__
    StrCat(work,ampm);
#else
    strcat(work, ampm);
#endif
   
#ifdef __MC68K__
    storestr4(work);
#else
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, work);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_totime()
#else
void verb_func_totime(PNOBlock *pnoP)
#endif
{
    char *ad;
    Int16 i;
    Int16 h,m,s;
    Int16 res=0;
    double w;
    char errmsg[80];
    char wk[20];
#ifdef __MC68K__
    ad=(char*)arg1_val;
#else
    ad = PNO(args)[0].val;
#endif
    i=0;
    if(*(ad+2)==':') wk[i++]=*ad++;
    else wk[i++]='0';
    wk[i++]=*ad++;
    wk[i]=0x00;
    /**/
   
    h=StrAToI(wk);
    if(*ad!=':') res=1;
    ++ad ;
    i=0;
    if(*(ad+2)==':') {wk[i++]=*(ad++);}
    else wk[i++]='0';
    wk[i++]=*ad++;
    wk[i]=0x00;
    /**/
    
    m=StrAToI(wk);
    if(*ad!=':') res=1;
    ++ad ;
    i=0;
    if(*(ad+2)==0x00) wk[i++]=*ad++;
    else wk[i++]='0';
    wk[i++]=*ad;
    wk[i]=0x00;
    
    s=StrAToI(wk);
    if(res==0)
    {
       if( (h<0) || (h>23) || (m<0) || (m>59) || (s<0) || (s>59) ) res=1;
    }
    if(res)
    {
#ifdef __MC68K__
       StrPrintF(errmsg,"String '%s' is not a valid time.",ad);
       misc_errmsg(errmsg);
#else
       char *b;
       b = errmsg;
       b = strcpy(b, "String '");
       b = strcpy(b, ad);
       strcpy(b, "' is not a valid time.");
       misc_errmsg(pnoP, errmsg);
#endif
    }
    w=cvt_time_to_dbl(h,m,s);

#ifdef __MC68K__    
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_date()
#else
void verb_func_date(PNOBlock *pnoP)
#endif
{
    double w;
    Int16 y,m,d;
    char errmsg[80];
#ifdef __MC68K__
    y=*(double*)arg1_val;
    m=*(double*)arg2_val;
    d=*(double*)arg3_val;
#else
    y=ReadUnaligned64(PNO(args)[0].val);
    m=ReadUnaligned64(PNO(args)[1].val);
    d=ReadUnaligned64(PNO(args)[2].val);
#endif
    if(valid_date(d,m,y)==0)
    {
#ifdef __MC68K__
       StrPrintF(errmsg,"Year=%i Month=%i Day=%i is not a valid date.",y,m,d);
       misc_errmsg(errmsg);
#else
        char *b;
        b = errmsg;
        b = strcpy(b, "Year= ");
        StrIToA(b, (long) y); while (*b) ++b;
        b = strcpy(b, " Month= ");
        StrIToA(b, (long) m); while (*b) ++b;
        b = strcpy(b, "Day= ");
        StrIToA(b, (long) d); while (*b) ++b;
        strcpy(b, " is not a valid date.");
        misc_errmsg(pnoP, errmsg);
#endif
    }
    w=cvt_date_to_dbl(y,m,d);
    
#ifdef __MC68K__    
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__    
void verb_func_time()
#else
void verb_func_time(PNOBlock *pnoP)
#endif
{
    Int16 h,m,s;
    double w;
    char errmsg[80];
#ifdef __MC68K__
    h=*(double*)arg1_val;
    m=*(double*)arg2_val;
    s=*(double*)arg3_val;
#else
    h=ReadUnaligned64(PNO(args)[0].val);
    m=ReadUnaligned64(PNO(args)[1].val);
    s=ReadUnaligned64(PNO(args)[2].val);
#endif
    if( (h<0) || (h>23) || (m<0) || (m>59) || (s<0) || (s>59))
    {
#ifdef __MC68K__
       StrPrintF(errmsg,"Hour=%i Minute=%i Second=%i is not a valid time.",
               h,m,s);
       misc_errmsg(errmsg);
#else
        char *b;
        b = errmsg;
        b = strcpy(b, "Hour=");
        StrIToA(b, (long) h); while (*b) ++b;
        b = strcpy(b, " Minute=");
        StrIToA(b, (long) m); while (*b) ++b;
        b = strcpy(b, "Second=");
        StrIToA(b, (long) s); while (*b) ++b;
        strcpy(b, " is not a valid time.");
        misc_errmsg(pnoP, errmsg);
#endif
    }
    w=cvt_time_to_dbl(h,m,s);
    
#ifdef __MC68K__    
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__    
void verb_func_day()
#else
void verb_func_day(PNOBlock *pnoP)
#endif
{
    double w;
    Int16 y,m,d;

#ifdef __MC68K__
    w=*(double*)arg1_val;
#else
    w = ReadUnaligned64(PNO(args)[0].val);
#endif
    cvt_date_to_ymd(w,&y,&m,&d);
    w=d;
 
#ifdef __MC68K__    
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
#endif
}
//*****************************************************************************************
#ifdef __MC68K__    
void verb_func_hour()
#else
void verb_func_hour(PNOBlock *pnoP)
#endif
{
    double w;
    Int16 h,m,s;

#ifdef __MC68K__
    w=*(double*)arg1_val;
#else
    w = ReadUnaligned64(PNO(args)[0].val);
#endif
    cvt_time_to_hms(w,&h,&m,&s);
    w=h;
    
#ifdef __MC68K__    
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
#endif
}
//*****************************************************************************************
#ifdef __MC68K__    
void verb_func_minute()
#else
void verb_func_minute(PNOBlock *pnoP)
#endif
{
    double w;
    Int16 h,m,s;

#ifdef __MC68K__
    w=*(double*)arg1_val;
#else
    w = ReadUnaligned64(PNO(args)[0].val);
#endif
    cvt_time_to_hms(w,&h,&m,&s);
    w=m;
    
#ifdef __MC68K__    
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
#endif
}
//*****************************************************************************************
#ifdef __MC68K__    
void verb_func_second()
#else
void verb_func_second(PNOBlock *pnoP)
#endif
{
    double w;
    Int16 h,m,s;

#ifdef __MC68K__
    w=*(double*)arg1_val;
#else
    w = ReadUnaligned64(PNO(args)[0].val);
#endif
    cvt_time_to_hms(w,&h,&m,&s);
    w=s;
#ifdef __MC68K__    
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
#endif
}
//*****************************************************************************************
#ifdef __MC68K__    
void verb_func_month()
#else
void verb_func_month(PNOBlock *pnoP)
#endif
{
    double w;
    Int16 y,m,d;

#ifdef __MC68K__
    w=*(double*)arg1_val;
#else
    w = ReadUnaligned64(PNO(args)[0].val);
#endif
    cvt_date_to_ymd(w,&y,&m,&d);
    w=m;
    
#ifdef __MC68K__    
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
#endif
}
//*****************************************************************************************
#ifdef __MC68K__    
void verb_func_year()
#else
void verb_func_year(PNOBlock *pnoP)
#endif
{
    double w;
    Int16 y,m,d;

#ifdef __MC68K__
    w=*(double*)arg1_val;
#else
    w = ReadUnaligned64(PNO(args)[0].val);
#endif
    cvt_date_to_ymd(w,&y,&m,&d);
    w=y;
    
#ifdef __MC68K__    
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
#endif
}
//*****************************************************************************************
//06102002 new funcs timediff and datediff ****
#ifdef __MC68K__    
void verb_func_dayofweek()
#else
void verb_func_dayofweek(PNOBlock *pnoP)
#endif
{
    double w;
    Int16 y,m,d;
    
#ifdef __MC68K__
    w=*(double*)arg1_val;
#else
    w = ReadUnaligned64(PNO(args)[0].val);
#endif
    cvt_date_to_ymd(w,&y,&m,&d);
    w=DayOfWeek(m,d,y)+1;
    
#ifdef __MC68K__    
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__    
void verb_func_datediff()
#else
void verb_func_datediff(PNOBlock *pnoP)
#endif
{
    double w;
    double daysdiff;
    DATE date1;
    DATE date2;
    Int16 y,m,d;

#ifdef __MC68K__
    w=*(double*)arg1_val;
#else
    w = ReadUnaligned64(PNO(args)[0].val);
#endif
    cvt_date_to_ymd(w,&y,&m,&d);
    date1=julian_date(d,m,y);
    
#ifdef __MC68K__
    w=*(double*)arg2_val;
#else
    w = ReadUnaligned64(PNO(args)[1].val);
#endif
    cvt_date_to_ymd(w,&y,&m,&d);
    date2=julian_date(d,m,y);
    
    daysdiff=date2-date1;
#ifdef __MC68K__
    store4(&daysdiff);
#else
    daysdiff = SwapDouble(daysdiff);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &daysdiff);
#endif
}
//*****************************************************************************************
//06102002 **** end *****
#ifdef __MC68K__
void verb_func_timediff()
#else
void verb_func_timediff(PNOBlock *pnoP)
#endif
{
    double w;
    double timediff;
    long secs1;
    long secs2;
    Int16 hr,min,sec;
    long temp1;
    long temp2;
    long temp3;
    
#ifdef __MC68K__
    w=*(double*)arg1_val;
#else
    w = ReadUnaligned64(PNO(args)[0].val);
#endif
    cvt_time_to_hms(w,&hr,&min,&sec);
    temp1=hr;
    temp1*=3600;
    temp2=min;
    temp2*=60;
    
    secs1=temp1+temp2+sec;
    
#ifdef __MC68K__
    w=*(double*)arg2_val;
#else
    w = ReadUnaligned64(PNO(args)[1].val);
#endif
    cvt_time_to_hms(w,&hr,&min,&sec);
    temp1=hr;
    temp1*=3600;
    temp2=min;
    temp2*=60;
    secs2=temp1+temp2+sec;
    
    timediff=secs2-secs1;
#ifdef __MC68K__
    store4(&timediff);
#else
    timediff = SwapDouble(timediff);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &timediff);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_dayofyear()
#else
void verb_func_dayofyear(PNOBlock *pnoP)
#endif
{
    double w;
    Int16 y,m,d;
    unsigned long nowdays;
    
#ifdef __MC68K__
    DateType dt;

    w=*(double*)arg1_val;
#else
    w = ReadUnaligned64(PNO(args)[0].val);
#endif

    cvt_date_to_ymd(w,&y,&m,&d);
#ifdef __MC68K__
    dt.year=y;
    dt.month=m;
    dt.day=d;
#endif

#ifdef __MC68K__
    nowdays=DateToDays(dt);
#else
    nowdays=Glue_DateToDays(pnoP, y, m, d);
#endif

#ifdef __MC68K__
    dt.month=1;
    dt.day=1;
#endif

#ifdef __MC68K__
    w=nowdays-DateToDays(dt)+1;
#else
    w=nowdays-Glue_DateToDays(pnoP, y, 1, 1)+1;
#endif

#ifdef __MC68K__
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_ceiling()
#else
void verb_func_ceiling(PNOBlock *pnoP)
#endif
{
#ifdef __MC68K__
   reg_a=*((double*)arg1_val);

   reg_a=misc_ceil(reg_a);
  
   store4(&reg_a);
#else
    double reg_a;
    reg_a = ReadUnaligned64(PNO(args)[0].val);
    reg_a = misc_ceil(reg_a);
    reg_a = SwapDouble(reg_a);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &reg_a);
#endif
}
//*****************************************************************************************
#ifdef __MC68K__
void verb_func_floor()
#else
void verb_func_floor(PNOBlock *pnoP)
#endif
{
#ifdef __MC68K__
   reg_a=*((double*)arg1_val);

   reg_a=misc_floor(reg_a);
   
   store4(&reg_a);
#else
    double reg_a;
    reg_a = ReadUnaligned64(PNO(args)[0].val);
    reg_a = misc_floor(reg_a);
    reg_a = SwapDouble(reg_a);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &reg_a);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_sign()
#else
void verb_func_sign(PNOBlock *pnoP)
#endif
{
#ifdef __MC68K__
   reg_a=*((double*)arg1_val);

   if(reg_a<0) reg_b=-1;
   else reg_b=1;
   store4(&reg_b);
#else
    double reg_a, reg_b;
    reg_a = ReadUnaligned64(PNO(args)[0].val);
    if(reg_a<0) reg_b=-1;
    else reg_b=1;
    reg_b = SwapDouble(reg_b);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &reg_b);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_trunc()
#else
void verb_func_trunc(PNOBlock *pnoP)
#endif
{
    
    double w;
    char wk[25];
    int k;
    int i;
    
#ifdef __MC68K__
    k=integ_value(arg2,(double*)arg2_val);          //#decimal places to truncate after
    misc_format_number(arg1,(double*)arg1_val,wk);  //first get number into ascii string
    for(i=0;i<StrLen(wk);++i)
#else
    double d;
    d = ReadUnaligned64(PNO(args)[1].val);
    k = d;
    misc_format_number(pnoP, PNO(args)[0].dataElem,(double *)PNO(args)[0].val,wk);  //first get number into ascii string
    for(i=0;i<strlen(wk);++i)

#endif
    {
      if (wk[i]=='.') goto foundDecPoint;
    }
    //number is an integer, so no truncation required
#ifdef __MC68K__
    w=*((double*)arg1_val);
#else
    w = ReadUnaligned64(PNO(args)[0].val);
#endif

    goto itsSet;
foundDecPoint:
#ifdef __MC68K__
    if( StrLen(wk) < i+k+2)
#else
    if( strlen(wk) < i+k+2)
#endif
    {
#ifdef __MC68K__
        w=*((double*)arg1_val);
#else
        w = ReadUnaligned64(PNO(args)[0].val);
#endif
    }
    else
    {
       //has more dec places than wanted, so truncate
       wk[i+k+1]=0x00;      //truncate after k dec places
#ifdef __MC68K__ 
       w=StrToDouble(wk);   //and convert back to double
#else
       w=StrToDouble(pnoP, wk);   //and convert back to double
#endif
    }
itsSet:

//StrPrintF(debug,"string=%s #=%d",wk,w);
//dbug(debug);
#ifdef __MC68K__
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
#endif
}
//*****************************************************************************************
#ifdef __MC68K__
void verb_func_leftpad()
#else
void verb_func_leftpad(PNOBlock *pnoP)
#endif
{
    VoidHand h;
    char * wk;
    Int16 i,j,k;
#ifdef __MC68K__
    h=MemHandleNew(*(double*)arg2_val+StrLen(arg1_val)+1);
#else
    double d;
    d = ReadUnaligned64(PNO(args)[1].val);
    i = d;
    h=MemHandleNew(i + strlen(PNO(args)[0].val)+1);
#endif
    if(h==0) OutOfMemory(6081);  //05282003
    wk=(char*)MemHandleLock(h);

    j=0;
#ifdef __MC68K__
    i=*(double*)arg2_val;
    k=StrLen(arg1_val);
#else
    k = strlen(PNO(args)[0].val);
#endif

    while (k < i)
    {
        wk[j++]=' ';
        ++k;
    }
    wk[j]=0x00;
#ifdef __MC68K__
    StrCat(wk,(char*)arg1_val);
    misc_stostr4(wk);
#else
    strcat(wk, PNO(args)[0].val);
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, wk);
#endif
    MemPtrUnlock(wk);
    MemHandleFree(h);
}
//*****************************************************************************************
#ifdef __MC68K__
void verb_func_rightpad()
#else
void verb_func_rightpad(PNOBlock *pnoP)
#endif
{
    VoidHand h;
    char * wk;

    Int16 i,j;

#ifdef __MC68K__
    h=MemHandleNew(*(double*)arg2_val+StrLen(arg1_val)+1);
#else
    double d;
    d = ReadUnaligned64(PNO(args)[1].val);
    i = d;
    h=MemHandleNew(i + strlen(PNO(args)[0].val)+1);
#endif
    if(h==0) OutOfMemory(6082);  //05282003
    wk=(char*)MemHandleLock(h);

#ifdef __MC68K__
    StrCopy(wk,(char*)arg1_val);
    j=StrLen(wk);
    i=*((double*)arg2_val);
#else
    strcpy(wk,(char*)PNO(args)[0].val);
    j=strlen(wk);
#endif

    while (j < i)
    {
       wk[j++]=' ';
    }
    wk[j]=0x00;
#ifdef __MC68K__
    misc_stostr4(wk);
#else
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, wk);
#endif
    MemPtrUnlock(wk);
    MemHandleFree(h);
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_adddays()
#else
void verb_func_adddays(PNOBlock *pnoP)
#endif
{
    Int16 y,m,d,a;
    DATE jdate;
    double w,s;
#ifdef __MC68K__
    a=*(double*)arg2_val;
    s=*(double*)arg1_val;
#else
    a = ReadUnaligned64(PNO(args)[1].val);
    s = ReadUnaligned64(PNO(args)[0].val);
#endif
    cvt_date_to_ymd(s,&y,&m,&d);
    jdate=julian_date(d,m,y);

    jdate += a;
    calendar_date(jdate,&d,&m,&y);
    w=cvt_date_to_dbl(y,m,d);
    
#ifdef __MC68K__
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
#endif
}
//*****************************************************************************************
#ifdef __MC68K__
void verb_func_subtractdays()
#else
void verb_func_subtractdays(PNOBlock *pnoP)
#endif
{
    Int16 y,m,d,a;
    DATE jdate;
    double w,s;
#ifdef __MC68K__
    a=*(double*)arg2_val;
    s=*(double*)arg1_val;
#else
    a = ReadUnaligned64(PNO(args)[1].val);
    s = ReadUnaligned64(PNO(args)[0].val);
#endif
    cvt_date_to_ymd(s,&y,&m,&d);
    jdate=julian_date(d,m,y);

    jdate -= a;
    calendar_date(jdate,&d,&m,&y);
    w=cvt_date_to_dbl(y,m,d);
    
#ifdef __MC68K__
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
#endif
}
//*****************************************************************************************
#ifdef __MC68K__
void verb_func_addmonths()
#else
void verb_func_addmonths(PNOBlock *pnoP)
#endif
{
    Int16 y,m,d,a;
    double w,s;
#ifdef __MC68K__
    a=*(double*)arg2_val;
    s=*(double*)arg1_val;
#else
    a = ReadUnaligned64(PNO(args)[1].val);
    s = ReadUnaligned64(PNO(args)[0].val);
#endif
    cvt_date_to_ymd(s,&y,&m,&d);
    m += a;
    while (m > 12)
    {
        m -= 12;
        y += 1;
    }
    w=cvt_date_to_dbl(y,m,d);
    
#ifdef __MC68K__
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
#endif
}
//*****************************************************************************************
#ifdef __MC68K__
void verb_func_subtractmonths()
#else
void verb_func_subtractmonths(PNOBlock *pnoP)
#endif
{
    Int16 y,m,d,a;
    double w,s;
#ifdef __MC68K__
    a=*(double*)arg2_val;
    s=*(double*)arg1_val;
#else
    a = ReadUnaligned64(PNO(args)[1].val);
    s = ReadUnaligned64(PNO(args)[0].val);
#endif
    cvt_date_to_ymd(s,&y,&m,&d);
    m -= a;
    while (m < 1)
    {
        m += 12;
        y -= 1;
    }
    w=cvt_date_to_dbl(y,m,d);
    
#ifdef __MC68K__
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
#endif
}
//*****************************************************************************************
#ifdef __MC68K__
void verb_func_addyears()
#else
void verb_func_addyears(PNOBlock *pnoP)
#endif
{
    Int16 y,m,d,a;
    double w,s;
#ifdef __MC68K__
    a=*(double*)arg2_val;
    s=*(double*)arg1_val;
#else
    a = ReadUnaligned64(PNO(args)[1].val);
    s = ReadUnaligned64(PNO(args)[0].val);
#endif
    cvt_date_to_ymd(s,&y,&m,&d);
    y=y+a;
    w=cvt_date_to_dbl(y,m,d);

#ifdef __MC68K__
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
#endif
}
//*****************************************************************************************
#ifdef __MC68K__
void verb_func_subtractyears()
#else
void verb_func_subtractyears(PNOBlock *pnoP)
#endif
{
    Int16 y,m,d,a;
    double w,s;
#ifdef __MC68K__
    a=*(double*)arg2_val;
    s=*(double*)arg1_val;
#else
    a = ReadUnaligned64(PNO(args)[1].val);
    s = ReadUnaligned64(PNO(args)[0].val);
#endif
    cvt_date_to_ymd(s,&y,&m,&d);
    y=y-a;
    w=cvt_date_to_dbl(y,m,d);

#ifdef __MC68K__
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_firstofmonth()
#else
void verb_func_firstofmonth(PNOBlock *pnoP)
#endif
{
    double w;
    Int16 y,m,d;

#ifdef __MC68K__
    w=*(double*)arg1_val;
#else
    w = ReadUnaligned64(PNO(args)[0].val);
#endif
    cvt_date_to_ymd(w,&y,&m,&d);
    d=1;
    w=cvt_date_to_dbl(y,m,d);

    
#ifdef __MC68K__
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
#endif
}
//*****************************************************************************************
#ifdef __MC68K__
void verb_func_lastofmonth()
#else
void verb_func_lastofmonth(PNOBlock *pnoP)
#endif
{
    double w;
    Int16 y,m,d;

#ifdef __MC68K__
    w=*(double*)arg1_val;
#else
    w = ReadUnaligned64(PNO(args)[0].val);
#endif
    cvt_date_to_ymd(w,&y,&m,&d);
    if( (m==1)||(m==3)||(m==5)||(m==7)||(m==8)||(m==10)||(m==12)) d=31;
    else if(    (m==4)||(m==6)||(m==9)||(m==11) )                 d=30;
    else
    {
      /*FEB and leap yr*/
      d=29;
      if(valid_date(d,m,y)) ; else d=28;
    }

    w=cvt_date_to_dbl(y,m,d);
    
#ifdef __MC68K__
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_getkey()
#else
void verb_func_getkey(PNOBlock *pnoP)
#endif
{
//StrPrintF(debug,"in function keydown event val=%d",lastKeyString[0]);
//SysFatalAlert(debug);
#ifdef __MC68K__
    storestr4(PNO(lastKeyString));
#else
   misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, PNO(lastKeyString));
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_sysdate()
#else
void verb_func_sysdate(PNOBlock *pnoP)
#endif
{

    struct  olddate sdate;
    double w;
    int y,m,d;

    getdate(&sdate);
    y=sdate.da_year;
    m=sdate.da_mon;
    d=sdate.da_day;

    w=cvt_date_to_dbl(y,m,d);
/*----
StrPrintF(work,"sysdate--yr=%i day =%i mo=%i date=%lf"
,sdate.yr,sdate.day,sdate.mo,w);
test_debug(work);
----*/

#ifdef __MC68K__
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);

#endif
    return;
}
//*****************************************************************************************
#ifdef __MC68K__
void verb_func_systime()
#else
void verb_func_systime(PNOBlock *pnoP)
#endif
{

    struct timedef stime;
    int h,m,s;
    double t;
    gettime(&stime);
    h=stime.ti_hour;m=stime.ti_min;s=stime.ti_sec;
    t=cvt_time_to_dbl(h,m,s);


/*---------
StrPrintF(work,"systime--min=%i hr=%i hund=%i sec=%i t=%lf",
stime.min,stime.hr,stime.hund,stime.sec,t);
test_debug(work);
----------*/
   
#ifdef __MC68K__
    store4(&t);
#else
    t = SwapDouble(t);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &t);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_sysinfo()
#else
void verb_func_sysinfo(PNOBlock *pnoP)  // EMP
#endif
{
    // EMP rewritten to make it easier to translate
    Int16 which;
    Err err;
    UInt32 numBytes, freeBytes, maxChunk;
    double result = 0.0;

#ifdef __MC68K__
    which=integ_value(arg1,(double*)arg1_val);
#else
    which = ReadUnaligned64(PNO(args)[0].val);
#endif

    switch (which)
    {
        case 0:
          result=PNO(runtimeVersionInteg); //runtime version
          break;
        case 1: //tick count
          result=TimGetTicks();
          break;
        case 2:  //ticks per second         
          result=SysTicksPerSecond();
          break;
        case 3:  //Serial Port ID         
          result = PNO(serRef);
          break;
        case 4:  //Current Form ID       
          result = FrmGetActiveFormID();
          break;
        case 5:	 //bytes waiting in serial queue
#ifdef __MC68K__
          if(gOldSerialManager) err=SerReceiveCheck(PNO(serRef), &numBytes);
          else err=SrmReceiveCheck(PNO(serRef), &numBytes);
          if(err>0) numBytes=0;
          result = numBytes;
#else
          result = Glue_SerialReceiveCheck(pnoP, PNO(serRef));
#endif
		  break;
        case 6: //ROM major version  			  //GWH 2003.03.27
		  result=sysGetROMVerMajor(PNO(romVersion))*10+sysGetROMVerMinor(PNO(romVersion));
          break;
        case 7:	//Get Coordinate System   		  //GWH 2003.03.27
#ifdef __MC68K__
          if (PNO(romVersion)>=0x05000000) result = WinGetCoordinateSystem();
#else
          if (PNO(romVersion)>=0x05000000) result = Glue_WinGetCoordinateSystem(pnoP);
#endif
          else result = 0;
          break;
        case 8: //Get free storage heap          //GWH 2003.06.09
          //does not give correct result if more than 32,767k free
          MemHeapFreeBytes((UInt16) 1, &freeBytes, &maxChunk);
          result = (freeBytes/1024);
          break;
        case 9: //Get last data.keyDown.chr  //GWH 2003.11.03
          result = PNO(lastKeyDownChr);
          break;
        case 10: //Get last data.keyDown.KeyCode  //GWH 2003.11.03
          result = PNO(lastKeyDownKeyCode);
          break;
        case 11: //Get last data.keyDown.modifiers  //GWH 2003.11.03
          result = PNO(lastKeyDownModifiers);
          break;
        case 14:
#ifdef __MC68K__
		  result = 0;
#else
		  result = 1;
		  {
		  	
		  }
#endif
    }
#ifdef __MC68K__
    store4(&result);
#else
    result = SwapDouble(result);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &result);
#endif
}

//*****************************************************************************************
DATE julian_date(Int16 day, Int16 month , Int16 year )
{
#ifdef __MC68K__
     /* calc Julian date(if yr is B.c> will be negative*/
     long a,b;
     double year_corr;
     DATE retVal;
     year_corr=(year > 0 ? 0.0 : 0.75 );
     if (month <= 2 )
     {
        year--;
        month += 12;
     }
     b = 0;
     if( year * 10000.0 + month * 100.0 + day >= 15821015.0L)
     {
       a=year/100;
       b=2-a + a/4;
     }
     retVal = (DATE) (long) (365.25L * year - year_corr) +
       ((long) (30.6001L * (double)(month+1))) + ((long) day) + 1720994L + b;
     return retVal;
#else
    /* EMP Use Fliegel/van Flandern algorithm to avoid FP precision errors */
    Int32 I, J, K;
    DATE retVal;

    I = year;
    J = month;
    K = day;
    
    retVal = K-32075L+1461L*(I+4800L+(J-14L)/12L)/4L+367L*(J-2-(J-14L)/12L*12L)/12L-3L*((I+4900L+(J-14L)/12L)/100L)/4;

    return retVal;
#endif
}

//*****************************************************************************************
void calendar_date(DATE jdate, Int16 *day, Int16 *month, Int16 *year)
{
#ifdef __MC68K__
   long a,b,c,d,e,z,alpha;
   z=jdate+1;
   if (z < 2299161L )
      a=z;
   else
   {
      alpha=(long)((z-1867216.25) / 36524.25);
      a=z+1+alpha - alpha/4;
   }
   b=a+1524;
   c=(long)((b-122.1) / 365.25);
   d=(long)(365.25 * c);
   e=(long)((b-d) / 30.6001);
   *day=(Int16)b-d-(long)(30.6001 * e);
   *month=(Int16)(e < 13.5) ? e-1: e-13;
   *year=(Int16)(*month > 2.5) ? (c-4716) : c - 4715;
#else
    /* EMP Use Fliegel/van Flandern algorithm to avoid FP precision errors */
    Int32 I, J, K, L, N;
        
      L= jdate+68569;
      N= 4*L/146097;
      L= L-(146097*N+3)/4;
      I= 4000*(L+1)/1461001;
      L= L-1461*I/4+31;
      J= 80*L/2447;
      K= L-2447*J/80;
      L= J/11;
      J= J+2-12*L;
      I= 100*(N-49)+I+L;

    *year = I;
    *month = J;
    *day = K;
#endif
}

//*****************************************************************************************
Int16 valid_date(Int16 day, Int16 month, Int16 year)
{
#ifdef __MC68K__
   /*also includes chk if year is leap yr*/
   Int16 cal_day,cal_month,cal_year;
   /*cvt date to Julian date and back*/
   calendar_date(julian_date(day,month,year),
                &cal_day,&cal_month,&cal_year);
   /*date is valid if day,month,and year did not chg*/
   return((day==cal_day)&&(month==cal_month)&&(year==cal_year));
#else
    /* EMP relying on Julian date conversion seems a bit fragile, besides,
       the Julian algorithm has changed. */
    Int16 dpm[12] = 
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (year < 200) year += 1900;
    
    if ((year % 4) == 0)
    {
        /* Leap year, maybe */
        if ((year % 100) == 0)
        {
            /* Except for centuries */
            if ((year % 400) == 0)
            {
                /* But put it back every 400 years */
                ++(dpm[1]);
            }
        }
        else
        {
            ++(dpm[1]);
        }
    }
    
    return (month >= 1 && month <= 12 && day >= 1 && day <= dpm[month - 1]); 
#endif
}

#ifdef __MC68K__
//*****************************************************************************************
int day_of_week(DATE date )
{
   /*1=sunday 2=mon etc*/
   return(int) ((date+2) % 7 + 1);
}
//*****************************************************************************************
void verb_func_truncate()
{
    VoidHand h;
    char *p;
    
    char *ad;

    h=MemHandleNew(StrLen(arg1_val)+1);
    if(h==0) OutOfMemory(6083);  //05282003
    p=(char*)MemHandleLock(h);

    
    StrCopy(p,arg1_val);
    ad=p;
    while(*ad != 0x00)    /*position to end of string*/
    {
        ++ad;
    }

    while (ad != p)
    {
      --ad;

      if(*ad != ' ') break;
      *ad=0x00;          /*replace blanks with null to end string*/
    }
    storestr4(p);

    MemPtrUnlock(p);
    MemHandleFree(h);
   return;
}
#endif

//*****************************************************************************************
#ifdef __MC68K__
void func_fieldgettext()
#else
void func_fieldgettext(PNOBlock *pnoP)
#endif
{
  char *ptr;
  VoidHand h;

  ptr=FldGetTextPtr((FieldType*)PNO(controlPtr));
  if(ptr==0)
  {
#ifdef __MC68K__
     storestr4("");
#else
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, "");
#endif
  }
  else
  {
#ifdef __MC68K__
     storestr4(ptr);
#else
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, ptr);
#endif
  }
}

#ifdef __MC68K__
//*****************************************************************************************
void commonGetLabel(FormPtr frmPtr, int controlid)
{

  char *ptr;
  VoidHand h;
  char *c;
 
  ptr=(char*)FrmGetLabel(frmPtr,controlid);
//StrPrintF(debug,"found label text=%s",ptr);
//dbug(debug);
  if(ptr==0)
  {
     h=MemHandleNew(1);
     if(h==0) OutOfMemory(6085);  //05282003
     c=(char*)MemHandleLock(h);
     StrCopy(c,"");
     storestr4(c);
     MemPtrUnlock(c);
     MemPtrFree(c);
  }
  else
  {
  
     storestr4(ptr);
  }
}

//*****************************************************************************************
void commonGetTitle(FormPtr frmPtr)
{

  char *ptr;
  VoidHand h;
  char *c;
 
  ptr=(char*)FrmGetTitle(frmPtr);
//StrPrintF(debug,"found label text=%s",ptr);
//dbug(debug);
  if(ptr==0)
  {
     h=MemHandleNew(1);
     if(h==0) OutOfMemory(6086);  //05282003
     c=(char*)MemHandleLock(h);
     StrCopy(c,"");
     storestr4(c);
     MemPtrUnlock(c);
     MemPtrFree(c);
  }
  else
  {
  
     storestr4(ptr);
  }
}
#endif
//*****************************************************************************************
void func_controlgetlabel()
{
  FormPtr frmPtr;
  
  frmPtr=FrmGetActiveForm();
  commonGetLabel(frmPtr, PNO(controlid));
  
 
}
//*****************************************************************************************
#ifdef __MC68K__
void func_controlgettext()
#else
void func_controlgettext(PNOBlock *pnoP)
#endif
{
  char *ptr;
  VoidHand h;
  char *c;
 
  ptr=(char*)CtlGetLabel((ControlType*)PNO(controlPtr));
  if(ptr==0)
  {
#ifdef __MC68K__
     h=MemHandleNew(1);
     if(h==0) OutOfMemory(6087);  //05282003
     c=(char*)MemHandleLock(h);
     StrCopy(c,"");
     storestr4(c);
     MemPtrUnlock(c);
     MemPtrFree(c);
#else
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, "");
#endif
  }
  else
  {
#ifdef __MC68K__
     storestr4(ptr);
#else
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, ptr);

#endif
  }
}

//*****************************************************************************************
#ifdef __MC68K__
void func_listgetnoitems()
#else
void func_listgetnoitems(PNOBlock *pnoP)  // DIKEO shouldn't these use a variable?
#endif
{
  int res;
  res=LstGetNumberOfItems((ListType*)PNO(controlPtr));
#ifdef __MC68K__
  restore4(res);   //added 4.17.2000
#else
  {
    double result;
    result = res;
    result = SwapDouble(result);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &result);
  }
#endif
}
//*****************************************************************************************
#ifdef __MC68K__
void func_listgetselecteditemno()
#else
void func_listgetselecteditemno(PNOBlock *pnoP)  // DIKEO shouldn't this use a variable?
#endif
{
  int res;
  res=LstGetSelection((ListType*)PNO(controlPtr));
  if (LstGetNumberOfItems((ListType*)PNO(controlPtr))==0) res=-1;

#ifdef __MC68K__
  restore4(res+1);
#else
  {
    double result;
    result = res + 1;
    result = SwapDouble(result);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &result);
  }
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void commonGetID(FormPtr frmPtr,ControlType* controlPtr)  //09302002  added entire routien
#else
void commonGetID(PNOBlock *pnoP, FormPtr frmPtr,ControlType* controlPtr)  //09302002  added entire routien
#endif
{
  Int16 Id;
  Id=miscFrmGetObjectIdFromPtr(frmPtr, controlPtr);
#ifdef __MC68K__
  restore4(Id);
#else
  {
    double result;
    result = Id;
    result = SwapDouble(result);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &result);
  }
#endif
}
//*****************************************************************************************
#ifdef __MC68K__
void func_controlgetID()  //09302002 modified
#else
void func_controlgetID(PNOBlock *pnoP)  // EMP
#endif
{
  
  FormPtr frmPtr;
  frmPtr=FrmGetActiveForm();
#ifdef __MC68K__
  commonGetID(frmPtr, PNO(controlPtr));   //09302002
#else
  commonGetID(pnoP, frmPtr, PNO(controlPtr));   //09302002
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void commonGetItemText(Int16 i)
#else
void commonGetItemText(PNOBlock *pnoP, Int16 i)
#endif
{
  char *ptr;
  
  ListPtr l;
 
  l=(ListType*)PNO(controlPtr);
  if((i<0) || (i>=LstGetNumberOfItems(l)))
  {
      //SysFatalAlert("Program accessing a list to get text when no item selected");
#ifdef __MC68K__
      storestr4("***");  //??????
#else
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, "***");
#endif
      return;
  }
  
  ptr=LstGetSelectionText(l, i); //GHGlue
#ifdef __MC68K__
  storestr4(ptr);
#else
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, ptr);
#endif
}
//*****************************************************************************************
#ifdef __MC68K__
void func_listgetitemtext()
#else
void func_listgetitemtext(PNOBlock *pnoP)
#endif
{
  
  Int16 i;

#ifdef __MC68K__
  i=integ_value(arg1,(double*)arg1_val)-1;

  commonGetItemText(i);
#else
  double d;
  d = ReadUnaligned64(PNO(args)[0].val);
  i = d;
  commonGetItemText(pnoP, i);
#endif
}
//*****************************************************************************************

#ifdef __MC68K__
void func_popupgettext()
{
  //10102002 char *ptr;
   //10102002 ptr=(char*)CtlGetLabel((ControlType*)controlPtr);
  //10102002storestr4(ptr);
  
  FormPtr frm;
  int i;
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
      storestr4(ptr);
      return;
  }
//dbug("returning the selected list entry");
  
  //04022003ptr=*((char**)((char *)(listObjPtr->itemsText)+i*4) );
  ptr=LstGetSelectionText(listObjPtr,i)  ;    //added 04022003 (George's Glue code)
  //ptr=*((char**)((char *)(LstGlueGetItemsText(listObjPtr))+i*4) );  //(Larry's code - gets an error)
  storestr4(ptr);

}
#endif


//*****************************************************************************************
#ifdef __MC68K__
void func_scrollbargetcurrent()
#else
//PNO call not called - work is done elsewhere
void func_scrollbargetcurrent(PNOBlock *pnoP)
#endif
{
 SWord val;
 SWord min;
 SWord max;
 SWord pag;
  
 SclGetScrollBar((ScrollBarPtr)PNO(controlPtr),&val,&min,&max,&pag);
#ifdef __MC68K__
  restore4(val);
#else
  {
    double result = val;
    result = SwapDouble(result);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &result);
  }
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void func_acos()
{
  double w;
  w=acos(*(double*)arg1_val);
  store4(&w);
}
#else
void func_acos(PNOBlock *pnoP)
{
  double w;
  double d;
  d = ReadUnaligned64(PNO(args)[0].val);
  w = GlueACos(pnoP, d);
  w = SwapDouble(w);
  misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
}
#endif
//*****************************************************************************************
#ifdef __MC68K__
void func_asin()
{
  double w;
  w=asin(*(double*)arg1_val);
  store4(&w);
}
#else
void func_asin(PNOBlock *pnoP)
{
  double w;
  double d;
  d = ReadUnaligned64(PNO(args)[0].val);
  w = GlueASin(pnoP, d);
  w = SwapDouble(w);
  misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
}
#endif
//*****************************************************************************************
#ifdef __MC68K__
void func_atan()
{
  double w;
  w=atan(*(double*)arg1_val);
  store4(&w);
}
#else
void func_atan(PNOBlock *pnoP)
{
  double w;
  double d;
  d = ReadUnaligned64(PNO(args)[0].val);
  w = GlueATan(pnoP, d);
  w = SwapDouble(w);
  misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
}
#endif
//*****************************************************************************************
#ifdef __MC68K__
void func_atan2()
{
  double w;
  w=atan2(*(double*)arg1_val,*(double*)arg2_val);
  store4(&w);
}
#else
void func_atan2(PNOBlock *pnoP)
{
  double w;
#if 1
  double d1, d2;
  d1 = ReadUnaligned64(PNO(args)[0].val);
  d2 = ReadUnaligned64(PNO(args)[1].val);
  w=GlueATan2(pnoP, d1, d2);
#else
    double lastTime;
    double timediff;
    long n = 0;

    verb_func_systime(pnoP);
    lastTime = ReadUnaligned64(PNO(args)[3].val);
    
    w = SwapDouble(lastTime);
    misc_stodbl(pnoP, PNO(args)[0].dataElem, PNO(args)[0].occ1, PNO(args)[0].occ2, PNO(args)[0].occ3, &w);
    
    do
    {
        double curTime;
        ++n;
        
        verb_func_systime(pnoP);
        curTime = ReadUnaligned64((char *)PNO(args)[3].val);
        w = SwapDouble(curTime);
        misc_stodbl(pnoP, PNO(args)[1].dataElem, PNO(args)[1].occ1, PNO(args)[1].occ2, PNO(args)[1].occ3, &w);
        
        verb_func_timediff(pnoP);
        timediff = ReadUnaligned64((char *) PNO(args)[3].val);

    } while (timediff < 10.0);
    w = n;
#endif
  w = SwapDouble(w);
  misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
}
#endif
//*****************************************************************************************
#ifdef __MC68K__
void func_cos()
{
  double w;
  w=cos(*(double*)arg1_val);
  store4(&w);
}
#else
void func_cos(PNOBlock *pnoP)
{
  double w;
  double d;
  d = ReadUnaligned64(PNO(args)[0].val);
  w = GlueCos(pnoP, d);
  w = SwapDouble(w);
  misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
}
#endif

//*****************************************************************************************
#ifdef __MC68K__
void func_sin()
{
  double w;
  w=sin(*(double*)arg1_val);
  store4(&w);
}
#else
void func_sin(PNOBlock *pnoP)
{
  double w;
  double d;
  d = ReadUnaligned64(PNO(args)[0].val);
  w = GlueSin(pnoP, d);
  w = SwapDouble(w);
  misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
}
#endif


//*****************************************************************************************
#ifdef __MC68K__
void func_tan()
{
  double w;
  w=tan(*(double*)arg1_val);
  store4(&w);
}
#else
void func_tan(PNOBlock *pnoP)
{
  double w;
  double d;
  d = ReadUnaligned64(PNO(args)[0].val);
  w = GlueTan(pnoP, d);
  w = SwapDouble(w);
  misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
}
#endif
//*****************************************************************************************
#ifdef __MC68K__
void func_cosh()
{
  double w;
  w=cosh(*(double*)arg1_val);
  store4(&w);
}
#else
void func_cosh(PNOBlock *pnoP)
{
  double w;
  double d;
  d = ReadUnaligned64(PNO(args)[0].val);
  w = GlueCosH(pnoP, d);
  w = SwapDouble(w);
  misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
}
#endif
//*****************************************************************************************
#ifdef __MC68K__
void func_sinh()
{
  double w;
  w=sinh(*(double*)arg1_val);
  store4(&w);
}
#else
void func_sinh(PNOBlock *pnoP)
{
  double w;
  double d;
  d = ReadUnaligned64(PNO(args)[0].val);
  w = GlueSinH(pnoP, d);
  w = SwapDouble(w);
  misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
}
#endif
//*****************************************************************************************
#ifdef __MC68K__
void func_tanh()
{
  double w;
  w=tanh(*(double*)arg1_val);
  store4(&w);
}
#else
void func_tanh(PNOBlock *pnoP)
{
  double w;
  double d;
  d = ReadUnaligned64(PNO(args)[0].val);
  w = GlueTanH(pnoP, d);
  w = SwapDouble(w);
  misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
}
#endif
//*****************************************************************************************
#ifdef __MC68K__
void func_acosh()
{
  double w;
  w=acosh(*(double*)arg1_val);
  store4(&w);
}
#else
void func_acosh(PNOBlock *pnoP)
{
  double w;
  double d;
  d = ReadUnaligned64(PNO(args)[0].val);
  w = GlueACosH(pnoP, d);
  w = SwapDouble(w);
  misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
}
#endif
//*****************************************************************************************
#ifdef __MC68K__
void func_asinh()
{
  double w;
  w=asinh(*(double*)arg1_val);
  store4(&w);
}
#else
void func_asinh(PNOBlock *pnoP)
{
  double w;
  double d;
  d = ReadUnaligned64(PNO(args)[0].val);
  w = GlueASinH(pnoP, d);
  w = SwapDouble(w);
  misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
}
#endif
//*****************************************************************************************
#ifdef __MC68K__
void func_atanh()
{
  double w;
  w=atanh(*(double*)arg1_val);
  store4(&w);
}
#else
void func_atanh(PNOBlock *pnoP)
{
  double w;
  double d;
  d = ReadUnaligned64(PNO(args)[0].val);
  w = GlueATanH(pnoP, d);
  w = SwapDouble(w);
  misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
}
#endif
//*****************************************************************************************
#ifdef __MC68K__
void func_exp()
{
  double w;
  w=exp(*(double*)arg1_val);
  store4(&w);
}
#else
void func_exp(PNOBlock *pnoP)
{
  double w;
  double d;
  d = ReadUnaligned64(PNO(args)[0].val);
  w = GlueExp(pnoP, d);
  w = SwapDouble(w);
  misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
}
#endif
//*****************************************************************************************
#ifdef __MC68K__
void func_log()
{
  double w;
  w=log(*(double*)arg1_val);
  store4(&w);
}
#else
void func_log(PNOBlock *pnoP)
{
  double w;
  double d;
  d = ReadUnaligned64(PNO(args)[0].val);
  w = GlueLog(pnoP, d);
  w = SwapDouble(w);
  misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
}
#endif
//*****************************************************************************************
#ifdef __MC68K__
void func_log10()
{
  double w;
  w=log10(*(double*)arg1_val);
  store4(&w);
}
#else
void func_log10(PNOBlock *pnoP)
{
  double w;
  double d;
  d = ReadUnaligned64(PNO(args)[0].val);
  w = GlueLog10(pnoP, d);
  w = SwapDouble(w);
  misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
}
#endif
//*****************************************************************************************
#ifdef __MC68K__
void func_cbrt()
{
  double w;
  w=cbrt(*(double*)arg1_val);
  store4(&w);
}
#else
void func_cbrt(PNOBlock *pnoP)
{
  double w;
  double d;
  d = ReadUnaligned64(PNO(args)[0].val);
  w = GlueCbrt(pnoP, d);
  w = SwapDouble(w);
  misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
}
#endif
//*****************************************************************************************
#ifdef __MC68K__
void func_rem()
{
   double t;
   long k;

   reg_a=*((double*)arg1_val);
   reg_b=*((double*)arg2_val);
    
   t=reg_a/reg_b;
   k=t;
   reg_a-= k*reg_b;    // EMP more efficient
   store4(&reg_a);
}
#else
void func_rem(PNOBlock *pnoP)
{
   double t;
   double reg_a, reg_b;
   long k;

   reg_a = ReadUnaligned64(PNO(args)[0].val);
   reg_b = ReadUnaligned64(PNO(args)[1].val);
    
   t=reg_a/reg_b;
   k=t;
   reg_a-= k*reg_b;    // EMP more efficient
   
   reg_a = SwapDouble(reg_a);
  misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &reg_a);
}
#endif

//*****************************************************************************************
#ifdef __MC68K__
void func_pow()
{
  double w;
  w=pow(*(double*)arg1_val,*(double*)arg2_val);
  store4(&w);
}
#else
void func_pow(PNOBlock *pnoP)
{
  double w;
  double d1, d2;
  d1 = ReadUnaligned64(PNO(args)[0].val);
  d2 = ReadUnaligned64(PNO(args)[1].val);
  w=GluePow(pnoP, d1, d2);
  w = SwapDouble(w);
  misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
}
#endif
//*****************************************************************************************
#ifdef __MC68K__
void func_sqrt()
{
  double w;
  w=sqrt(*(double*)arg1_val);
  store4(&w);
}
#else
void func_sqrt(PNOBlock *pnoP)
{
  double w;
  double d;
  d = ReadUnaligned64(PNO(args)[0].val);
  w = GlueSqrt(pnoP, d);
  w = SwapDouble(w);
  misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
}
#endif

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_degtoradians()
#else
void verb_func_degtoradians(PNOBlock *pnoP)
#endif
{
    double d;
#ifdef __MC68K__
    d=(*(double*)arg1_val)*2*PI/360.0;
    store4(&d);
#else
    d=ReadUnaligned64(PNO(args)[0].val)*PI/180.0;
    d = SwapDouble(d);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &d);
#endif
}
//*****************************************************************************************
#ifdef __MC68K__
void verb_func_radtodegrees()
#else
void verb_func_radtodegrees(PNOBlock *pnoP)
#endif
{
    double d;
#ifdef __MC68K__
    d=(*(double*)arg1_val)*360.0/(2*PI);
    store4(&d);
#else
    d=ReadUnaligned64(PNO(args)[0].val)*180.0/(PI);
    d = SwapDouble(d);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &d);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_getversion()   // EMP 09032003
#else
void verb_func_getversion(PNOBlock *pnoP)
#endif
{
    VoidHand h;
    char *p;
    char *a;
    LocalID dbID;
    
#ifdef __MC68K__
    dbID = DmFindDatabase(0, (char *)arg1_val);
#else
    dbID = DmFindDatabase(0, (char *)PNO(args)[0].val);
#endif
    
    if (dbID)
    {
        DmOpenRef openDB;
        
        openDB = DmOpenDatabase(0, dbID, dmModeReadOnly);
        if (openDB)
        {
            
            MemHandle rsrc;
            int index;
            
            index = DmFindResourceType(openDB, 'tver', 0);
            
            if (index >= 0)
            {
                char *p;
                rsrc = DmGetResourceIndex(openDB, index);
                p = MemHandleLock(rsrc);
#ifdef __MC68K__
                storestr4(p);
#else
                misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, p);
#endif
                MemHandleUnlock(rsrc);
                DmReleaseResource(rsrc);
            }
            else
            {
#ifdef __MC68K__
                storestr4("ERR: Could not find resource");
#else
                misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, "ERR: Could not find resource");
#endif
            }
            DmCloseDatabase(openDB);
        }
        else
        {
#ifdef __MC68K__
            storestr4("ERR: Could not open");
#else
            misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, "ERR: Could not open");
#endif
        }
    }
    else
    {
#ifdef __MC68K__
        storestr4("ERR: Database not found");
#else
        misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, "ERR: Database not found");
#endif
    }

    return;
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_ltrim()
#else
void verb_func_ltrim(PNOBlock *pnoP)
#endif
{
    VoidHand h;
    char *p;
    char *a;
    char *d;

#ifdef __MC68K__   
    h=MemHandleNew(StrLen(arg1_val)+1);
#else
    h=MemHandleNew(strlen(PNO(args)[0].val)+1);
#endif
    if(h==0) OutOfMemory(6089);  //05282003
    p=(char*)MemHandleLock(h);

#ifdef __MC68K__      
    a=(char*)arg1_val;
#else
    a = (char *)PNO(args)[0].val;
#endif
    d=p;
    while (1)
    {
       if(*a!=' ') break;
       ++a;
    }
    while (1)
    {
       *d++=*a;
       if(*a==0x00) break;
       ++a;
    }

#ifdef __MC68K__
    storestr4(p);
#else
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, p);
#endif
    MemPtrUnlock(p);
    MemHandleFree(h);
    return;
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_rtrim()
#else
void verb_func_rtrim(PNOBlock *pnoP)
#endif
{
    VoidHand h;
    char *p;
    char *a;
#ifdef __MC68K__   
    h=MemHandleNew(StrLen(arg1_val)+1);
#else
    h=MemHandleNew(strlen(PNO(args)[0].val)+1);
#endif
    if(h==0) OutOfMemory(6088);  //05282003
    p=(char*)MemHandleLock(h);

#ifdef __MC68K__
    StrCopy(p,(char*)arg1_val);
    a=p+StrLen(p);
#else
    strcpy(p,(char*)PNO(args)[0].val);
    a=p+strlen(p);
#endif
    while (1)
    {
       --a;
       if(a<p) break;
       if(*a==' ') *a=0x00;
       else break;
    }
#ifdef __MC68K__
    storestr4(p);
#else
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, p);
#endif
    MemPtrUnlock(p);
    MemHandleFree(h);
    return;
}
//*****************************************************************************************
#ifdef __MC68K__
void verb_func_trim()
#else
void verb_func_trim(PNOBlock *pnoP)
#endif
{
 VoidHand h;
    char *p;
    char *a;
    char *d;
   
#ifdef __MC68K__   
    h=MemHandleNew(StrLen(arg1_val)+1);
#else
    h=MemHandleNew(strlen(PNO(args)[0].val)+1);
#endif
    if(h==0) OutOfMemory(6090);  //05282003
    p=(char*)MemHandleLock(h);

 
#ifdef __MC68K__      
    a=(char*)arg1_val;
#else
    a = (char *)PNO(args)[0].val;
#endif
    d=p;
    while (1)
    {
       if(*a!=' ') break;
       ++a;
    }
    while (1)
    {
       *d++=*a;
       if(*a==0x00) break;
       ++a;
    }
    --d;
    while (1)
    {
       --d;
       if(d<p) break;
       if(*d!=' ') break;
       *d=0x00;
    }
#ifdef __MC68K__
    storestr4(p);
#else
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, p);
#endif
    MemPtrUnlock(p);
    MemHandleFree(h);
    return;
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_mmddyytodate()
#else
void verb_func_mmddyytodate(PNOBlock *pnoP)
#endif
{
char *ad;
    
    Int16 res;
    Int16 y,m,d;
    char errmsg[80];
    double w;
 
#ifdef __MC68K__
    ad=(char*)arg1_val;
#else
    ad = PNO(args)[0].val;
#endif

    res=cvt_mmddyystring_to_ymd( ad,&y,&m,&d);
    if(res==0)
    {
       res=valid_date(d,m,y);
       if(res==0) res=1;
       else       res=0;
    }
    if(res)
    {
#ifdef __MC68K__
       StrPrintF(errmsg,"String '%s' is not a valid date in mm/dd/yy format.",ad);
       misc_errmsg(errmsg);
#else
        char *b;
        b = strcpy(errmsg, "String '");
        b = strcpy(b, ad);
        b = strcpy(b, "' is not a valid date in mm/dd/yy format.");
        misc_errmsg(pnoP, errmsg);

#endif
    }

    w=cvt_date_to_dbl(y,m,d);

#ifdef __MC68K__    
    store4(&w);
#else
    w = SwapDouble(w);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &w);
#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_testnum()
#else
void verb_func_testnum(PNOBlock *pnoP)
#endif
{
   //arg1=string to test for numeric
   //arg2=signs allowed  " "=none,"+" or  "-"=  +or-
   //arg3=max no decs before dec pt
   //arg5=max no decs after dec pt
 int err;
 int b=0;
 int a=0;
 char s=' ';
#ifdef __MC68K__
 char *p=(char*)arg1_val;
#else
 double d;
 char *p = PNO(args)[0].val;
#endif
 int decYet=0;
 int res;
 
 while (1)
 {
    if((*p)==0x00) break;
    switch(*p)
    {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
         if (decYet==0)
         {
            ++a;
            
         }
         else
         {
            ++b;
         }
         break;
      case '.':
         ++decYet;
         break;
      case '+':
      case '-':
#ifdef __MC68K__
         if(p!=arg1_val)
#else
         if (p != PNO(args)[0].val)
#endif
         {
             res=4;
             goto err;    //sign not first char
         }
         if (s==' ') s=*p;
         else
         {
                res=4;  //two signs found
                goto err;
         }
         break;
default:
         res=5;;
         goto err;
       
    }
    ++p;
 }
#ifdef __MC68K__
 if (a>integ_value(arg3,(double*)arg3_val)) {res=1; goto err;}
 if (b>integ_value(arg5,(double*)arg5_val)) {res=2; goto err;}
#else
 if (a>(Int16) ReadUnaligned64(PNO(args)[2].val)) {res=1; goto err;}
 if (b>(Int16) ReadUnaligned64(PNO(args)[4].val)) {res=2; goto err;}
#endif
 if (decYet>1)          {res=3; goto err;}
#ifdef __MC68K__
 if ( (*((char*)arg2_val)==' ') && (s!=' ') ) {res=6; goto err;}
#else
 if ( (*((char*)PNO(args)[1].val)==' ') && (s!=' ') ) {res=6; goto err;}
#endif
 res=0;
    
err:
#ifdef __MC68K__
    restore4(res);
#else
    d = res;
    d = SwapDouble(d);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &d);
#endif
}

#ifdef __MC68K__
//*****************************************************************************************
/*void verb_func_controlsgettext()
{
   int id;
   ControlType* controlPtr;
   int controlType;
   char *ptr;
   VoidHand h;
   char *c;
   FormPtr frmPtr;
//dbug("in ctlsgettext");   
   //find_arg_1();
   frmPtr=FrmGetActiveForm();

   id=integ_value(arg1,(double*)arg1_val);
//StrPrintF(debug,"looking for index=%d",id);
//dbug(debug);
   controlPtr=(ControlType*)FrmGetObjectPtr(frmPtr,id);
   controlType=FrmGetObjectType(frmPtr,id);

   if(controlType==frmControlObj)
   {
      goto itsAControl;
   }
   //if(controlType==frmLabelObj)
   //{
   //   goto itsALabel;
   //}
   if(controlType==frmFieldObj)
   {
      goto itsAField;
   }
   goto noValue;
itsAControl:
  ptr=(char*)CtlGetLabel((ControlType*)controlPtr);
  if(ptr==0)
  {
     h=MemHandleNew(1);
     c=(char*)MemHandleLock(h);
     StrCopy(c,"");
     storestr4(c);
     MemPtrUnlock(c);
     MemPtrFree(c);
  }
  else
  {
  
     storestr4(ptr);
  }
  return; 
itsAField:
  ptr=FldGetTextPtr((FieldType*)controlPtr);
  if(ptr==0)
  {
noValue:
     h=MemHandleNew(1);
     c=(char*)MemHandleLock(h);
     StrCopy(c,"");
     storestr4(c);
     MemPtrUnlock(c);
     MemPtrFree(c);
  }
  else
  {
     storestr4(ptr);
  }
  return;
     
} 
*/  
//*****************************************************************************************
void common_controlsgettype(FormPtr frmPtr, int id)
{
   
    
   ControlType* controlPtr;
   int controlType;
   char *ptr;
   VoidHand h;
   int index;  //09302002
   char *c;
   //find_arg_1();
   //id=integ_value(arg1,(double*)arg1_val);
   //frmPtr=FrmGetActiveForm();
   index=FrmGetObjectIndex(frmPtr,id);     //09302002
   controlPtr=(ControlType*)FrmGetObjectPtr(frmPtr,index);   //09302002

   
   controlType=FrmGetObjectType(frmPtr,index);  //09302002
//StrPrintF(debug,"in get type  id=%d  index=%d  type=%d",id,index,controlType);   
//dbug(debug);

   
   	  if(controlType==1)
   	  {
   	  	   	controlType=20+CtlGlueGetControlStyle(controlPtr);  //gives 20-25
   	  }
   	  
//dbug("leaving get type");
   restore4(controlType);
}   

//*****************************************************************************************
/*void verb_func_controlsgetposition()
{
   FormPtr frmPtr;
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
	frmPtr=FrmGetActiveForm();
	h2=MiscDmGetResource('olst',FrmGetActiveFormID(),"olst");  //read the forms object list of names
    if(h2==0)
    {
       SysFatalAlert("Can't find object list for current form");
       
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
     
      if(StrCaselessCompare(name,arg1_val)==0)
      {
          goto matchedName;
      } 
      
//dbug("loading form   in vtoc processing:");
         ++p2;  //skip over null 
   }
   StrPrintF(debug,"Illegal object name used = %s",arg1_val);
   SysFatalAlert(debug);
matchedName:

//dbug("name matched");
    MemHandleUnlock(h2);      
    DmReleaseResource(h2);
//dbug("setting result");
    if (FrmGetTitle(FrmGetActiveForm()) != 0) restore4(i+1); //must return 1 higher if form has a title
    else                  restore4(i);  //return the control's position
     
}   
*/
//*****************************************************************************************
void common_controlsgetposition(FormPtr frmPtr,int controlid)
{
   int index;

   index=FrmGetObjectIndex(frmPtr, controlid);
//StrPrintF(debug,"controlid=%d  index=%d",controlid,index);
//dbug(debug);
   restore4(index);

}
#endif

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_controlscount()
#else
void verb_func_controlscount(PNOBlock *pnoP)
#endif
{
    FormPtr frmPtr;
    int i;
    int j;
    char*ad;
    char *p2;
    VoidHand h2;
    char name[256];
    unsigned int ID;
#ifdef __MC68K__
    ID=find_integer();
#else
    double d;
    ID=find_integer(pnoP);
#endif  
        
    frmPtr=FrmGetFormPtr(ID);   //pt to form
    if(frmPtr==NULL) return;   //???says frm not loaded
//StrPrintF(debug,"got form=%d #objs=%d",wkid,  FrmGetNumberOfObjects(frmPtr));
//SysFatalAlert(debug);
    j=FrmGetNumberOfObjects((FormType*)frmPtr);
#ifdef __MC68K__
    restore4(j);   
#else
    d = j;
    d = SwapDouble(d);
    misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &d);

#endif
}

//*****************************************************************************************
#ifdef __MC68K__
void AddToFuncTable(Int16 funcNo, VoidPtr f)
{
   if (funcNo<100)
   {
       funcTable[ funcNo ] =  f;
       ++funcs1To99;
       return;
   }
   if (funcNo<200)
   {
     funcTable[ funcNo-99+funcs1To99 ] =  f;
     ++funcs100To199;
     return;
   }
   if (funcNo<300)
   {
     funcTable[ funcNo-199+funcs1To99+funcs100To199 ] =  f;
     ++funcs200To299;
     return;
   }
   if (funcNo<400)
   {
     funcTable[ funcNo-299+funcs1To99+funcs100To199+funcs200To299 ] =  f;
     ++funcs300To399;
     return;
   }
   if (funcNo<500)
   {
     funcTable[ funcNo-399+funcs1To99+funcs100To199+funcs200To299+funcs300To399 ] =  f;
     ++funcs400To499;
     return;
   }
   if (funcNo<600)
   {
     funcTable[ funcNo-499+funcs1To99+funcs100To199+funcs200To299+funcs300To399+funcs400To499 ] =  f;
     ++funcs500To599;
     return;
   }
   if (funcNo<700)
   {
     funcTable[ funcNo-599+funcs1To99+funcs100To199+funcs200To299+funcs300To399+funcs400To499+funcs500To599 ] =  f;
     ++funcs600To699;
     return;
   }
}
#endif

#ifdef __MC68K__
//*****************************************************************************************
void checkItOut()
{
   dbug("in checkItOut");
}
//*****************************************************************************************
void setupFuncTable()
{
        AddToFuncTable (  1,   &verb_func_abs);
        AddToFuncTable (  2,   &verb_func_int);
        AddToFuncTable (  3,   &verb_func_mod);
        AddToFuncTable (  4,   &verb_func_rand);
        AddToFuncTable (  5,   &verb_func_round);
        AddToFuncTable (  6,   &verb_func_setlocale);   // EMP does nothing
        AddToFuncTable (  7,   &verb_func_power10);
        AddToFuncTable (  8,   &verb_func_chr);
        AddToFuncTable (  9,   &verb_func_format);
        AddToFuncTable (  10,  &verb_func_formatNL);    // IMP does nothing
        AddToFuncTable (  11,  &verb_func_instr);
        AddToFuncTable (  12,  &verb_func_nooccurs);
        AddToFuncTable (  13,  0);
        AddToFuncTable (  14,  &verb_func_ascii);
        AddToFuncTable (  15,  &verb_func_left);
        AddToFuncTable (  16,  &verb_func_right);
        AddToFuncTable (  17,  &verb_func_length);
        AddToFuncTable (  18,  &verb_func_lower);
        AddToFuncTable (  19,  &verb_func_mid);
        AddToFuncTable (  20,  &verb_func_testnum);
        AddToFuncTable (  21,  &verb_func_tostring);
        AddToFuncTable (  22,  &verb_func_proper);
        AddToFuncTable (  23,  &verb_func_upper);
        AddToFuncTable (  24,  &verb_func_tonumber);
        AddToFuncTable (  25,  &verb_func_todate);
        AddToFuncTable (  26,  &verb_func_totime);
        AddToFuncTable (  27,  &verb_func_date);
        AddToFuncTable (  28,  &verb_func_mmddyytodate);
        AddToFuncTable (  29,  &verb_func_time);
        AddToFuncTable (  30,  0);
        AddToFuncTable (  31,  &verb_func_day);
        AddToFuncTable (  32,  &verb_func_hour);
        AddToFuncTable (  33,  &verb_func_minute);
        AddToFuncTable (  34,  &verb_func_second);
        AddToFuncTable (  35,  &verb_func_month);
        AddToFuncTable (  36,  &verb_func_year);
        AddToFuncTable (  37,  &verb_func_dayofweek);
        AddToFuncTable (  38,  &verb_func_dayofyear);
        AddToFuncTable (  39,  0);
        AddToFuncTable (  40,  0);
        AddToFuncTable (  41,  0);
        AddToFuncTable (  42,  0);
        AddToFuncTable (  43,  0);
        AddToFuncTable (  44,  &verb_func_ceiling);
        AddToFuncTable (  45,  &verb_func_floor);
        AddToFuncTable (  46,  0);
        AddToFuncTable (  47,  &verb_func_sign);
        AddToFuncTable (  48,  &verb_func_trunc);
        AddToFuncTable (  49,  &verb_func_leftpad);
        AddToFuncTable (  50,  &verb_func_rightpad);
        AddToFuncTable (  51,  &verb_func_adddays);
        AddToFuncTable (  52,  &verb_func_addmonths);
        AddToFuncTable (  53,  &verb_func_addyears);
        AddToFuncTable (  54,  &verb_func_firstofmonth);
        AddToFuncTable (  55,  &verb_func_lastofmonth);
        AddToFuncTable (  56,  &verb_func_sysdate);
        AddToFuncTable (  57,  &verb_func_systime);
        AddToFuncTable (  58,  &verb_func_datediff);
        AddToFuncTable (  59,  &verb_func_timediff);
        AddToFuncTable (  60,  &verb_func_yearmonth);
        AddToFuncTable (  61,  &verb_func_monthday);
        AddToFuncTable (  62,  &verb_func_hourmin);
        AddToFuncTable (  63,  &verb_func_hourminampm);
        AddToFuncTable (  64,  &verb_func_datemmddyy);
        AddToFuncTable (  65,  &verb_func_subtractdays);
        AddToFuncTable (  66,  &verb_func_subtractmonths);
        AddToFuncTable (  67,  &verb_func_subtractyears);
        AddToFuncTable (  68,  &verb_func_popupdate);
        AddToFuncTable (  69,  &verb_func_popuptime);
        AddToFuncTable (  70,  &verb_func_degtoradians);
        AddToFuncTable (  71,  &verb_func_radtodegrees);
        //AddToFuncTable (  72,  &verb_func_controlsgettext);
        AddToFuncTable (  72,  0);
        //08222002AddToFuncTable (  73,  &verb_func_controlsgettype);
        AddToFuncTable (  73,  0);
        //AddToFuncTable (  74,  &verb_func_controlsgetposition);
        AddToFuncTable (  74, 0);
        AddToFuncTable (  75,  &verb_func_controlscount);
        AddToFuncTable (  76,  0);
        AddToFuncTable (  77,  0);
        AddToFuncTable (  78,  0);
        AddToFuncTable (  79,  0);
        AddToFuncTable (  80,  &verb_func_rtrim);
        AddToFuncTable (  81,  &verb_func_ltrim);
        AddToFuncTable (  82,  &verb_func_trim);
        AddToFuncTable (  83,  &verb_func_syseventavailable);
        AddToFuncTable (  84,  &verb_func_getkey);
        AddToFuncTable (  85,  0);
        AddToFuncTable (  86,  &verb_func_geteventtype);
        AddToFuncTable (  87,  &verb_func_sysinfo);
        //AddToFuncTable (  88,  &verb_func_signatureendcapture);
        AddToFuncTable (  88,  &verb_dbcreatedatabasefromresource);
        AddToFuncTable (  89,  &verb_func_getversion);
        
        AddToFuncTable (  100, &verb_serialOpen);
        AddToFuncTable (  101, &verb_serialClose);
        AddToFuncTable (  102, &verb_serialReceive);
        AddToFuncTable (  103, &verb_serialSend);
        AddToFuncTable (  104, &verb_serialSet);
        AddToFuncTable (  105, &verb_serialDial);
        AddToFuncTable (  106, &verb_serialHangUp);
        AddToFuncTable (  107, &verb_serialReceiveWithEvent);		//02.26.02 GH
        
        
        //for serial#s in 100's see above
        AddToFuncTable (  400, &func_controlgetstatus);
        AddToFuncTable (  401, &func_fieldgettext);
        AddToFuncTable (  402, &func_listgetnoitems);
        AddToFuncTable (  403, &func_listgetselecteditemno);
        AddToFuncTable (  404, &func_listgetitemtext);
        AddToFuncTable (  405,0);
        AddToFuncTable (  406,0);
        AddToFuncTable (  407,0);
        AddToFuncTable (  408,0);
        
        AddToFuncTable (  409, &func_controlgetID);
        AddToFuncTable (  410, 0);
        AddToFuncTable (  411, 0);
        AddToFuncTable (  412, &func_listgetnoitems);  //412-414 are popup changes to popup's list object
        AddToFuncTable (  413, &func_listgetselecteditemno);
        AddToFuncTable (  414, &func_listgetitemtext);
        AddToFuncTable (  415, &func_scrollbargetcurrent);
        AddToFuncTable (  416, &func_popupgettext);
        AddToFuncTable (  417, &func_controlgettext);
        AddToFuncTable (  418, &verb_func_signatureEndCapture);
        
        AddToFuncTable (  500, &func_acos);
        AddToFuncTable (  501, &func_asin);
        AddToFuncTable (  502, &func_atan);
        AddToFuncTable (  503, &func_atan2);
        AddToFuncTable (  504, &func_cos);
        AddToFuncTable (  505, &func_sin);
        AddToFuncTable (  506, &func_tan);
        AddToFuncTable (  507, 0);
        AddToFuncTable (  508, &func_cosh);
        AddToFuncTable (  509, &func_sinh);
        AddToFuncTable (  510, &func_tanh);
        AddToFuncTable (  511, &func_acosh);
        AddToFuncTable (  512, &func_asinh);
        AddToFuncTable (  513, &func_atanh);
        AddToFuncTable (  514, &func_exp);
        AddToFuncTable (  515, &func_log);
        AddToFuncTable (  516, &func_log10);
        AddToFuncTable (  517, &func_cbrt);
        AddToFuncTable (  518, &func_rem);
        AddToFuncTable (  519, &func_pow);
        AddToFuncTable (  520, &func_sqrt);
        
}

//*****************************************************************************************
void verb_function_doit2 (unsigned int it)
{
        BOOL bHandled = TRUE;
        char buf[30];
        
        typedef void miscCodeFunc();
        miscCodeFunc *  f;

        
        f=0;
        if (it<100){ f=funcTable[it]; goto testNull; }
        if (it<200){ f=funcTable[it-99+funcs1To99]; goto testNull; }
        if (it<300){ f=funcTable[it-199+funcs1To99+funcs100To199]; goto testNull; }
        if (it<400){ f=funcTable[it-299+funcs1To99+funcs100To199+funcs200To299]; goto testNull; }
        if (it<500){ f=funcTable[it-399+funcs1To99+funcs100To199+funcs200To299+funcs300To399]; goto testNull; }
        if (it<600){ f=funcTable[it-499+funcs1To99+funcs100To199+funcs200To299+funcs300To399+funcs400To499]; goto testNull; }
        if (it<700){ f=funcTable[it-599+funcs1To99+funcs100To199+funcs200To299+funcs300To399+funcs400To499+funcs500To599]; goto testNull; }
        
        
        
#ifdef ORG_NSB

        bHandled = NSBFunc( it );
        

        if( !bHandled )
        {
                StrPrintF( buf, "Invalid function code=%d", it );
                misc_errmsg( buf );
        }
        else return;
#endif
testNull:
       if (f==0)
       {
             StrPrintF( buf, "Invalid function code=%d", it );
             misc_errmsg( buf );
             return;
       }
//StrPrintF(debug,"it=%d addr=%lu",it,f);
//dbug(debug);    
       (*f )() ; /*this calls the function */
       
} // verb_function_doit2
#endif

#ifdef __MC68K__
//*****************************************************************************************
#ifdef ARM

/* EMP argument copy */
void CopyArg(UInt16 k);
void CopyArg(UInt16 k)
{
    aac.allArgs[k].dataElem = PNO(args)[k].dataElem;    
    aac.allArgs[k].val = PNO(args)[k].val;    
    aac.allArgs[k].occ1 = PNO(args)[k].occ1;    
    aac.allArgs[k].occ2 = PNO(args)[k].occ2;    
    aac.allArgs[k].occ3 = PNO(args)[k].occ3;    
    aac.allArgs[k].sde1 = PNO(args)[k].sde1;    
    aac.allArgs[k].sde2 = PNO(args)[k].sde2;    
    aac.allArgs[k].sde3 = PNO(args)[k].sde3;    
}

void RestoreArg(UInt16 k);
void RestoreArg(UInt16 k)
{
    PNO(args)[k].dataElem = aac.allArgs[k].dataElem;
    PNO(args)[k].val = aac.allArgs[k].val;
    PNO(args)[k].occ1 = aac.allArgs[k].occ1;
    PNO(args)[k].occ2 = aac.allArgs[k].occ2;
    PNO(args)[k].occ3 = aac.allArgs[k].occ3;
    PNO(args)[k].sde1 = aac.allArgs[k].sde1;
    PNO(args)[k].sde2 = aac.allArgs[k].sde2;
    PNO(args)[k].sde3 = aac.allArgs[k].sde3;
}

/* EMP callback function for function calls not implemented in PNO yet */
void function_doit_from_PNO(void);
void function_doit_from_PNO(void)
{
    UInt16 k;

     /* Copy args to their places */
    for (k = 0; k < PNO(nArgs); ++k)
    {
        if (k < 3)
            CopyArg(k);
        else
            CopyArg(k + 1);
    }
    CopyArg(3);

    verb_function_doit2(PNO(it));

    RestoreArg(3);
}
#endif
#endif

//*****************************************************************************************
#ifndef __MC68K__
/* EMP argument swapping helper function */
void SwapArg(PNOBlock *pnoP, UInt16 k);
void SwapArg(PNOBlock *pnoP, UInt16 k)
{
    unsigned long l;
    unsigned short s;
    
    l = (unsigned long) PNO(args)[k].dataElem;
    PNO(args)[k].dataElem = (struct dataelem *) ByteSwap32(l);
    
    l = (unsigned long) PNO(args)[k].val;
    PNO(args)[k].val = (void *) ByteSwap32(l);
    
    l = (unsigned long) PNO(args)[k].sde1;
    PNO(args)[k].sde1 = (struct dataelem *) ByteSwap32(l);
    
    l = (unsigned long) PNO(args)[k].sde2;
    PNO(args)[k].sde2 = (struct dataelem *) ByteSwap32(l);
    
    l = (unsigned long) PNO(args)[k].sde3;
    PNO(args)[k].sde3 = (struct dataelem *) ByteSwap32(l);
    
    s = PNO(args)[k].occ1;
    PNO(args)[k].occ1 = ByteSwap16(s);
    
    s = PNO(args)[k].occ2;
    PNO(args)[k].occ2 = ByteSwap16(s);
    
    s = PNO(args)[k].occ3;
    PNO(args)[k].occ3 = ByteSwap16(s);
}
#endif

//*****************************************************************************************
#ifdef __MC68K__
extern void verb_function_doit (UInt16 it)
#else
extern void verb_function_doit (PNOBlock *pnoP, UInt16 it)
#endif
{
#ifdef __MC68K__
        verb_function_doit2(it);
#else
    unsigned long ret;
    UInt16 k;
    unsigned long l;
    unsigned short s;

    PNO(it) = it;
    //SysFatalAlert("before func call");
    ret = ((*PNO(funcPNO))(PNO(emulStateP), pnoP, PNO(call68KFuncP)));
    //SysFatalAlert("after func call");
    if (ret) return;
    
    /* Must not have been there; do a callback */
    if (0)
    {
        char ch[20];
        StrIToA(ch, it);
        WinDrawChars(ch, strlen(ch), 110, 1);
    }
    /* Swap all the arguments */
    for (k = 0; k < PNO(nArgs); ++k)
    {
        if (k < 3)
            SwapArg(pnoP, k);
        else
            SwapArg(pnoP, k + 1);
    }
    SwapArg(pnoP, 3);   // Return value

    s = PNO(nArgs);
    PNO(nArgs) = ByteSwap16(s);
    PNO(it) = ByteSwap16(it);
    l = (unsigned long) PNO(args);
    PNO(args) = (void *) ByteSwap32(l);

    Glue_CallFunction(pnoP);

    l = (unsigned long) PNO(args);
    PNO(args) = (void *) ByteSwap32(l);

    s = PNO(nArgs);
    PNO(nArgs) = ByteSwap16(s);
    PNO(it) = it;
    /* Swap the return argument back */
    SwapArg(pnoP, 3);
#endif
}

//*****************************************************************************************
void cvt_date_to_ymd(double d,Int16 *yr, Int16 *mo, Int16* da)
{
//char work[80];
    unsigned long a,b,c;
    double aa;

    a=d/10000;
    aa=a;
    aa=aa*10000;
    b= (d-aa)/100;
    c=d-aa-b*100;
    a+= 1900;
    
    *yr=a;
    *mo=b;
    *da=c;
/*----
StrPrintF(work,"cvt date back date=%lf yr=%ul mo=%ul da=%ul",d,a,b,c);
test_debug(work);
-----*/
    return;
}
//*****************************************************************************************
void cvt_time_to_hms(double t,Int16 *h, Int16 *m, Int16* s)
{
    long q;
    unsigned long a,b,c;
    double aa;

    q=t;
//StrPrintF(debug,"*30*cvt time to hms q=%ld",q);
//dbug(debug);
    a=t/10000;
    aa=a;
    aa=aa*10000;

    b= (t-aa)/100;
    c=t-aa-b*100;
    *h=a;
    *m=b;
    *s=c;

//StrPrintF(debug,"*20*cvt time to hms q=%li h=%li m=%li s=%li",q,a,b,c);
//dbug(debug);

    return;
}

#ifdef __MC68K__
//*****************************************************************************************
void restore4(int i)
{
  restore_integ_value(i,arg4,(double*)arg4_val,arg4_occ1,arg4_occ2,arg4_occ3);
}
//*****************************************************************************************
void store4( double *d)
{

  store_reg(d,arg4,(double*)arg4_val,arg4_occ1,arg4_occ2,arg4_occ3);


}
//*****************************************************************************************
void storestr4(Char * s)
{
    misc_stostr4(s);
}
//*****************************************************************************************
void test_debug(Char * msg)
{
   SysFatalAlert(msg);
}

//*****************************************************************************************
void verb_func_setlocale()
{
}
#endif

//*****************************************************************************************
#ifdef __MC68K__
void verb_func_format()
#else
void verb_func_format(PNOBlock *pnoP)
#endif
{
  Int16 i;
  MemHandle wkH;
  MemHandle sH;
  char *wk;
  Int16 decpt;
  Int16 bef;
  Int16 aft;
  char *s;
#ifndef __MC68K__
  double d;
#endif

  sH = MemHandleNew(128);
  if (!sH)
  {
    OutOfMemory(-1);
    return;
  }
  wkH = MemHandleNew(128);
  if (!wkH)
  {
    MemHandleFree(sH);
    OutOfMemory(-1);
    return;
  }
  s = (char *)MemHandleLock(sH);
  wk = (char *)MemHandleLock(wkH);

#ifdef __MC68K__
    DoubleToStr(*(double *)arg1_val,wk);
#else
    d = ReadUnaligned64(PNO(args)[0].val);
    DoubleToStr(pnoP, d, wk);
#endif

    decpt=-1;
    bef=0;
    aft=0;
#ifdef __MC68K__
    for(i=0;i<StrLen(wk);++i)
#else
    for(i=0; i<strlen(wk); ++i)
#endif
    {
      if (wk[i]=='-') ;
      else
      {
         if (wk[i]=='.') {decpt=i;continue;}
         if(decpt==-1)bef+=1;
         else         aft+=1;
      }
    }
#ifdef __MC68K__
    misc_fmtno((char*)arg2_val,wk,bef,aft,decpt,s);
    misc_stostr4(s);
#else
    misc_fmtno((char*)PNO(args)[1].val,wk,bef,aft,decpt,s);
    misc_stostr(pnoP, &(PNO(args)[3].dataElem), PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, s);
#endif

	MemHandleUnlock(sH);
	MemHandleFree(sH);
	MemHandleUnlock(wkH);
	MemHandleFree(wkH);
}

#ifdef __MC68K__
/*******************************************************************************************/
void verb_func_formatNL()
{
//??
}
#endif

/*******************************************************************************************/
#ifdef __MC68K__
void func_controlgetstatus()
#else
void func_controlgetstatus(PNOBlock *pnoP)
#endif
{
  Int16 res;
  res=CtlGetValue((ControlType*)PNO(controlPtr));
#ifdef __MC68K__
  restore4(res);
#else
  {
   double d;
   d = res;
   d = SwapDouble(d);
   misc_stodbl(pnoP, PNO(args)[3].dataElem, PNO(args)[3].occ1, PNO(args)[3].occ2, PNO(args)[3].occ3, &d);
  }
#endif
}

/**********
	EMP moved from basc.c to make room
 */

#ifdef __MC68K__
Boolean  mathLibOpenSw=false;


/********************************************************************************************/
void chkMathLibOpen(void)
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
  PNO(mathLibRefNum) = MathLibRef;
  mathLibOpenSw=true;
  
}
#endif

#ifdef __MC68K__
/* EMP Glue because I don't think that the flp functions work from PACE */
Int16 flpftoa(double a, Char *s);
Int16 flpftoa(double a, Char *s)
{
    FlpCompDouble x;
    
    x.d = a;
    
    FlpFToA(x.fd, s);
    return 0;
}

Int16 flpatof(Char *s, double *a);
Int16 flpatof(Char *s, double *a)
{
    FlpCompDouble x;
    x.fd = FlpAToF(s);
    *a = x.d;
    return 0;
}

Int32 serialreceivecheck(UInt16 serRef)
{
    Int32 numBytes = 0;
    Err err;
    if(gOldSerialManager) err=SerReceiveCheck(serRef, &numBytes);
    else err=SrmReceiveCheck(serRef, &numBytes);
    if(err>0)
    {
    	numBytes=0;
    }
    return numBytes;
}

UInt16 wingetcoordinatesystem(void)
{
	UInt16 retVal;
    retVal = WinGetCoordinateSystem();
    return retVal;
}

UInt32 datetodays(UInt16 year, UInt16 month, UInt16 day)
{
	UInt32 retVal;
	DateType dt;
	dt.year = year;
	dt.month = month;
	dt.day = day;

    retVal = DateToDays(dt);
}

#endif



/**************************************************************************************************/
#ifdef __MC68K__
void verb_listsetselected()
#else
void verb_listsetselected(PNOBlock *pnoP)
#endif
{
  Int16 res;
  FormPtr frm;

#ifdef __MC68K__
  find_ctlid(true);
  find_arg_2(); //where
  frm=FrmGetActiveForm();
  commonSetSelected(frm, PNO(controlPtr), frmListObj,basc_integ_value(arg2,(double*)arg2_val));
#else
  Arg arg2;
  double d;
  find_ctlid(pnoP, true);
  find_arg_PNO(pnoP, &arg2); //where
  frm=FrmGetActiveForm();
  d = ReadUnaligned64(arg2.val);
  commonSetSelected(pnoP, frm, PNO(controlPtr), frmListObj, (Int16) d);
#endif
}


#ifdef __MC68K__
/********************************************************************************************/
void illegal_op_code()   /* if PNO(op_code) no good, this func is performed */
{

    char msg[80];
   

//SysFatalAlert("at illeg op code");
#ifdef ARM
   StrPrintF(msg,"Illegal op code=%d at offset%d ",PNO(op_code),PNO(instr_ctr));
    misc_text_abort(msg);
#endif
    return;
}
#endif


#ifdef __MC68K__
FormPtr  findFormTheControlIsOn(Int16 ctlid);
#else
FormPtr  findFormTheControlIsOn(PNOBlock *pnoP, Int16 ctlid);
#endif

/*******************************************************************************************/
#ifdef __MC68K__
void verb_func_getGeneralPropertyNumeric()
#else
void verb_func_getGeneralPropertyNumeric(PNOBlock *pnoP)
#endif
{
  //no auto arguments (this is really treated as a verb
  UInt16 minValue;  //added 04012005
  UInt16 maxValue;  //added 04012005
  UInt16 pageSize;  //added 04012005
  UInt16 curValue;  //added 04012005
  ControlStyleType type;  //added 04012005 
  Int16 res;
  Int16 controlType;
  Int16 pos = 0;
  char c;
  Boolean found = true;
  Int16 propId;
  FormPtr frmPtr;        //added 5.20.2000 
#ifdef __MC68K__  
   find_arg_4();    //get result var 
   c=find_char();   //type of control identifier
#else
    Arg arg4;
    find_arg_PNO(pnoP, &arg4);
    c = find_char(pnoP);
#endif
   switch(c)
   {
      case 'i':  //ctlid
#ifdef __MC68K__
        found=find_ctlid(false);
#else
        found = find_ctlid(pnoP, false);
#endif
        if(found==true)
        {
#ifdef __MC68K__
          frmPtr=findFormTheControlIsOn(PNO(controlid));
#else
          frmPtr=findFormTheControlIsOn(pnoP, PNO(controlid));
#endif
          pos=FrmGetObjectIndex(frmPtr,PNO(controlid));
        }  
        else
        {
            pos=-1;  //could not find
        }
//StrPrintF(debug,"aaa pos=%d controlid=%d",pos,controlid);
//dbug(debug);
        break;
      case 'v':  //variable containing name
#ifdef __MC68K__
        find_arg_2();      //variable containing name
        frmPtr=FrmGetActiveForm();    //09302002
        pos=findControlsPositionOnForm(&frmPtr,arg2_val);
#else
        {
            Arg arg2;
            find_arg_PNO(pnoP, &arg2);
            frmPtr=FrmGetActiveForm();    //09302002
            pos=findControlsPositionOnForm(pnoP, &frmPtr,arg2.val);
        }
#endif        
        goto havePosition;
        break;
      case 'p':  //position of ctl on form
#ifdef __MC68K__
        find_arg_2();      //position of control on form
        pos = integ_value( arg2, (double *)arg2_val ); 
#else
        {
            Arg arg2;
            double d;
            find_arg_PNO(pnoP, &arg2);
            d = ReadUnaligned64(arg2.val);
            pos = (Int16) d;
        }
#endif
        frmPtr=FrmGetActiveForm();
havePosition:
        
	    if(pos > FrmGetNumberOfObjects(frmPtr)-1)
	    {
	       SysFatalAlert("Control position too high.");
#ifdef __MC68K__
	       ErrThrow(-1);                 //inserted 05212003
#else
            GlueErrThrow(pnoP, -1);
#endif
	    }
	    if(pos== (-1)) 
	    {
	        found=false;
	        break;   //grafitti
	   }
	    PNO(controlPtr) = ((ControlType*)FrmGetObjectPtr(frmPtr,pos));
	    PNO(controlid) = FrmGetObjectId(frmPtr,pos);
	    if(PNO(controlid) == (-1)) 
	    {
	        pos=-1;
	        found=false;
	        break;   //grafitti
	   }
//StrPrintF(debug,"bbb pos=%d controlid=%d",pos,controlid);
//dbug(debug);
	    break;
   }
   if(found==true)controlType=FrmGetObjectType(frmPtr,pos);
#ifdef __MC68K__
   propId=find_integer();          //property type identifier #
#else
    propId = find_integer(pnoP);
#endif

   switch(propId)
   {
       case 1:  //status
          if(found==false) goto abortNotFound;
           if(controlType  != frmControlObj)
#ifdef __MC68K__
            commonErrorWrongCtltypeOnGet("status",controlType);
#else
            commonErrorWrongCtltypeOnGet(pnoP, "status",controlType);
#endif
          else
          {
#ifdef __MC68K__
            if(arg4->kind != 's') 
#else
            if (arg4.dataElem -> kind != 's') 
#endif
            {
#ifdef __MC68K__
                func_controlgetstatus();
#else
                Int16 res;
                double d;
                res = CtlGetValue((ControlType*)PNO(controlPtr));
                d = res;
                d = SwapDouble(d);
                misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
#endif
                return;
            }
#ifdef __MC68K__
            else commonErrorWrongTypeOnGet("status");
#else
            else commonErrorWrongTypeOnGet(pnoP, "status");
#endif
	      }
	      break; 
       case 2:  //selected
          if(found==false) goto abortNotFound;
          if( (controlType!=frmListObj)&&(controlType!=frmControlObj))
#ifdef __MC68K__
            commonErrorWrongCtltypeOnGet("selectd",controlType);
#else
            commonErrorWrongCtltypeOnGet(pnoP, "selectd",controlType);
#endif
          else
          {
#ifdef __MC68K__
            if(arg4->kind != 's')
#else
            if (arg4.dataElem -> kind != 's')
#endif
            {
                if (controlType != frmListObj)
                {
                     //must point to list part of popup
                     PNO(controlPtr) = ((ControlType*)FrmGetObjectPtr(frmPtr,pos+1));
	                 PNO(controlid) = FrmGetObjectId(frmPtr,pos+1);
                }
                {
#ifdef __MC68K__
                     func_listgetselecteditemno();
#else
                    Int16 res;
                    double d;
                    res=LstGetSelection((ListType*)PNO(controlPtr));
                    if (LstGetNumberOfItems((ListType*)PNO(controlPtr))==0) res=-1;
                    d = res + 1;
                    d = SwapDouble(d);
                    misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
#endif
                }
                return;
            }
            else
#ifdef __MC68K__
                commonErrorWrongTypeOnGet("selected");
#else
                commonErrorWrongTypeOnGet(pnoP, "selected");
#endif
          }
          break;
       /*case 4:  //maxChars
          if(controlType  != frmFieldObj) commonErrorWrongCtltypeOnGet("maxChars",controlType);
          else
          {
            if(arg4->kind != 's') res=commonGetMaxChars( );
            else commonErrorWrongType("maxChars");
          }
          break;
       */
        case 13:  //type      
          if(pos==(-1))
          {
#ifdef __MC68K__
             restore4(11);  //graffiti
#else
             double d = 11;
                d = SwapDouble(d);
             misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
#endif
             break;
          }
          if(found==false) goto abortNotFound;
#ifdef __MC68K__
          common_controlsgettype(frmPtr, PNO(controlid));
#else
            {
                Int16 index;  //09302002
                ControlType* controlPtr;
                Int16 controlType;
                double d;
                
                index=FrmGetObjectIndex(frmPtr,PNO(controlid));     //09302002
                controlPtr=(ControlType*)FrmGetObjectPtr(frmPtr,index);   //09302002

                controlType=FrmGetObjectType(frmPtr,index);  //09302002

                  if(controlType==1)
                  {
#ifdef __MC68K__
                  	   	controlType=20+CtlGlueGetControlStyle(controlPtr);  //gives 20-25
#else
                  	   	controlType=20+GlueCtlGlueGetControlStyle(pnoP, controlPtr);  //gives 20-25
#endif
                  }
                d = controlType;
                d = SwapDouble(d);
                misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
            }
#endif
          break;
         case 14:  //index (position)
           if(found==false) 
           {
#ifdef __MC68K__
              restore4(-1);
#else
                double d = -1;
                d = SwapDouble(d);
                misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
#endif
              break;          //indicate not found
           }
#ifdef __MC68K__
           common_controlsgetposition(frmPtr, PNO(controlid));
#else
            {
                Int16 index;
                double d;

                index=FrmGetObjectIndex(frmPtr, PNO(controlid));
                d = index;
                d = SwapDouble(d);
                misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
            }
#endif
           break;
         case 15:  //id   //09302002 added this section
           if(found==false) 
           {
#ifdef __MC68K__
              restore4(-1);
#else
                double d = -1;
                d = SwapDouble(d);
                misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
#endif
              break;          //indicate not found
           }
#ifdef __MC68K__
           commonGetID(frmPtr,PNO(controlPtr));   //09302002
#else
            {
                Int16 Id=miscFrmGetObjectIdFromPtr(frmPtr, PNO(controlPtr));
                double d = Id; 
                d = SwapDouble(d);
                misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
            }
#endif
           break;    
         //additions start 09242003
         case 48:  //col  
           if(found==false) 
           {
#ifdef __MC68K__
              restore4(-1);
#else
                double d = -1;
                d = SwapDouble(d);
                misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
#endif
              break;          //indicate not found
           }
#ifdef __MC68K__
           gridGetSelectedCol(frmPtr,PNO(controlPtr));    
#else
           gridGetSelectedCol(pnoP, &arg4, frmPtr,PNO(controlPtr));
#endif
           break;
         case 49:  //cols  
           if(found==false) 
           {
#ifdef __MC68K__
              restore4(-1);
#else
                double d = -1;
                d = SwapDouble(d);
                misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
#endif
              break;          //indicate not found
           }
#ifdef __MC68K__
           gridGetCols(frmPtr,PNO(controlPtr));
#else
           gridGetCols(pnoP, &arg4, frmPtr,PNO(controlPtr));    
#endif
           break;
         case 50:  //colwidth  
           if(found==false) 
           {
#ifdef __MC68K__
              restore4(-1);
#else
                double d = -1;
                d = SwapDouble(d);
                misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
#endif
              break;          //indicate not found
           }
#ifdef __MC68K__
           gridGetColWidth(frmPtr,PNO(controlPtr));    
#else
           gridGetColWidth(pnoP, frmPtr,PNO(controlPtr));    
#endif
           break;
         case 51:  //row  
           if(found==false) 
           {
#ifdef __MC68K__
              restore4(-1);
#else
                double d = -1;
                d = SwapDouble(d);
                misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
#endif
              break;          //indicate not found
           }
#ifdef __MC68K__
           gridGetSelectedRow(frmPtr,PNO(controlPtr));    
#else
           gridGetSelectedRow(pnoP, &arg4, frmPtr,PNO(controlPtr));    
#endif
           break;
        case 52:  //rows 
           if(found==false) 
           {
#ifdef __MC68K__
              restore4(-1);
#else
                double d = -1;
                d = SwapDouble(d);
                misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
#endif
              break;          //indicate not found
           }
#ifdef __MC68K__
           gridGetRows(frmPtr,PNO(controlPtr));    
#else
           gridGetRows(pnoP, &arg4, frmPtr,PNO(controlPtr));    
#endif
           break;    
        case 53:  //col  
           if(found==false) 
           {
#ifdef __MC68K__
              restore4(-1);
#else
                double d = -1;
                d = SwapDouble(d);
                misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
#endif
              break;          //indicate not found
           }
           gridGetVisibleRows(frmPtr,PNO(controlPtr));    
           break;
         case 55:  //cell value  
           if(found==false) 
           {
#ifdef __MC68K__
              restore4(-1);
#else
                double d = -1;
                d = SwapDouble(d);
                misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
#endif
             break;          //indicate not found
           }
#ifdef __MC68K__
           gridGetValueMatrix(frmPtr,PNO(controlPtr));    
#else
           gridGetValueMatrix(pnoP, &arg4, frmPtr,PNO(controlPtr));    
#endif
           break;
         case 56:  //value              //modified comment 07122005 
           if(found==false) 
           {
#ifdef __MC68K__
              restore4(-1);
#else
                double d = -1;
                d = SwapDouble(d);
                misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
#endif
              break;          //indicate not found
           }
           //start additions 07122005 
           if  (controlType==frmControlObj)                              
           {
#ifdef __MC68K__                                                         
             type = CtlGlueGetControlStyle((ControlType*)(PNO(controlPtr)));  
#else
             type = GlueCtlGlueGetControlStyle(pnoP, (ControlType*)(PNO(controlPtr)));  
#endif
             if((type==sliderCtl) || (type==feedbackSliderCtl) )        
             {
               //it's a slider ctl
               
                  CtlGetSliderValues ((ControlType*)(PNO(controlPtr)),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue); 

#ifdef __MC68K__                 
                    if(arg4->kind != 's') 
		            {
		                restore4(curValue);           
		                return;
					}
			        else
#else
                   if(arg4.dataElem->kind != 's') 
		            {
		            	double d = curValue;
		            	d = SwapDouble(d);
                		misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
		                return;
					}
			        else
#endif
#ifdef __MC68K__
			        commonErrorWrongTypeOnGet("Value");    
#else
			        commonErrorWrongTypeOnGet(pnoP, "Value");    
#endif
			  }                                                        
			   
           }
           else
           {
                  if(controlType  == frmScrollBarObj) 
		          {
#ifdef __MC68K__
		            if(arg4->kind != 's') 
		            {
		                func_scrollbargetcurrent();
#else
                   if(arg4.dataElem->kind != 's') 
		            {
						SWord val;
						SWord min;
						SWord max;
						SWord pag;
						double d;
 						SclGetScrollBar((ScrollBarPtr)PNO(controlPtr),&val,&min,&max,&pag);
		            	d = val;
		            	d = SwapDouble(d);
                		misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
#endif
		                return;
					}
#ifdef __MC68K__
			        commonErrorWrongTypeOnGet("Value");    
#else
			        commonErrorWrongTypeOnGet(pnoP, "Value");    
#endif
				  }
				  else
				  {
				  //end additions 07122005
           
#ifdef __MC68K__
           gridGetSelectedValue(frmPtr,PNO(controlPtr));    
#else
			gridGetSelectedValue(pnoP, &arg4, frmPtr, PNO(controlPtr));
#endif
                  }                                          //added 07122005                
           }                                                 //added 07122005
           break;
         case 57:  //get row data  
           if(found==false) 
           {
#ifdef __MC68K__
              restore4(-1);
#else
                double d = -1;
                d = SwapDouble(d);
                misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
#endif
              break;          //indicate not found
           }
#ifdef __MC68K__
           gridGetRowData(frmPtr,PNO(controlPtr));    
#else
		   gridGetRowData(pnoP, &arg4, frmPtr, PNO(controlPtr));
#endif
           break;                      
         //start additions 02062004
          case 58:  //toprow  
           if(found==false) 
           {
#ifdef __MC68K__
              restore4(-1);
#else
                double d = -1;
                d = SwapDouble(d);
                misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
#endif
              break;          //indicate not found
           }
#ifdef __MC68K__
           gridGetTopRow(frmPtr,PNO(controlPtr));
#else
           gridGetTopRow(pnoP, &arg4, frmPtr, PNO(controlPtr));
#endif   
           break;
         //end additins 02062004
           
                                 
         //additions end 09242003   
       case 94:  //current  DIKEO indides changed
          if(found==false) goto abortNotFound;
 //SysFatalAlert("at get current");    
           //modified 04012005

#ifdef __MC68K__
           type = CtlGlueGetControlStyle((ControlType*)(PNO(controlPtr))); 
#else
           type = GlueCtlGlueGetControlStyle(pnoP, (ControlType*)(PNO(controlPtr))); 
#endif

#if 0
           if  ((controlType==frmControlObj)&&((type==sliderCtl) || (type==feedbackSliderCtl) ))   //added 09242003
           {
               //it's a slider ctl
               
                  CtlGetSliderValues ((ControlType*)(PNO(controlPtr)),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue); 
                  
#ifdef __MC68K__
                    if(arg4->kind != 's') 
		            {
		                restore4(curValue);
		                return;
					}
			        else commonErrorWrongTypeOnGet("curValue");
#else
                    if(arg4.dataElem->kind != 's') 
		            {
		            	double d = curValue;
		            	d = SwapDouble(d);
                		misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
		                return;
					}
			        else commonErrorWrongTypeOnGet(pnoP, "curValue");
#endif			   
          }
          else
#endif
          {
          	 
          		  if(controlType  != frmScrollBarObj)
#ifdef __MC68K__
          		  	commonErrorWrongCtltypeOnGet("current",controlType);
#else
				    commonErrorWrongCtltypeOnGet(pnoP, "current", controlType);
#endif
		          else
		          {
#ifdef __MC68K__
		            if(arg4->kind != 's') 
		            {
		                func_scrollbargetcurrent();
		                return;
					}
#else
				    if(arg4.dataElem->kind != 's')
		            {
		                func_scrollbargetcurrent(pnoP);
		                return;
					}
#endif
					else
#ifdef __MC68K__
						commonErrorWrongTypeOnGet("current");
#else
						commonErrorWrongTypeOnGet(pnoP, "current");
#endif
		          }
          }
          break; 
        case 95:  //min   //modified 04012005
          //modified 04012005
          if(found==false) goto abortNotFound;
#ifdef __MC68K__
           type = CtlGlueGetControlStyle((ControlType*)(PNO(controlPtr))); 
#else
           type = GlueCtlGlueGetControlStyle(pnoP, (ControlType*)(PNO(controlPtr))); 
#endif
           if  ((controlType==frmControlObj)&&((type==sliderCtl) || (type==feedbackSliderCtl) ))   //added 09242003
           {
               //it's a slider ctl
               
                  CtlGetSliderValues ((ControlType*)(PNO(controlPtr)),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue); 
                  
  
#ifdef __MC68K__
                    if(arg4->kind != 's') 
		            {
		                restore4(minValue);
		                return;
					}
			        else commonErrorWrongTypeOnGet("minValue");
#else
                    if(arg4.dataElem->kind != 's') 
		            {
		            	double d = minValue;
		            	d = SwapDouble(d);
                		misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
		                return;
					}
			        else commonErrorWrongTypeOnGet(pnoP, "minValue");
#endif			   
			   
          }
          else
          {
          	/*
          	if(controlType  != frmScrollBarObj) commonErrorWrongCtltypeOnGet("min",controlType);
          	else
          	{
            	if(arg4->kind != 's') res=commonGetScrollbar(0x02,frmPtr);
            	else commonErrorWrongType("min");
          	}
          	*/
          }
          break; 
       case 96:  //max   //modified 04012005
          //modified 04012005
           if(found==false) goto abortNotFound;
#ifdef __MC68K__
           type = CtlGlueGetControlStyle((ControlType*)(PNO(controlPtr))); 
#else
           type = GlueCtlGlueGetControlStyle(pnoP, (ControlType*)(PNO(controlPtr))); 
#endif
           if  ((controlType==frmControlObj)&&((type==sliderCtl) || (type==feedbackSliderCtl) ))   //added 09242003
           {
               //it's a slider ctl
               
                  CtlGetSliderValues ((ControlType*)(PNO(controlPtr)),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue); 
                  
#ifdef __MC68K__
                    if(arg4->kind != 's') 
		            {
		                restore4(maxValue);
		                return;
					}
			        else commonErrorWrongTypeOnGet("maxValue");
#else
                    if(arg4.dataElem->kind != 's') 
		            {
		            	double d = maxValue;
		            	d = SwapDouble(d);
                		misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
		                return;
					}
			        else commonErrorWrongTypeOnGet(pnoP, "maxValue");
#endif			   
			   
          }
          else
          {
          		/*
          		  if(controlType  != frmScrollBarObj) commonErrorWrongCtltypeOnGet("max",controlType);
		          else
		          {
		            if(arg4->kind != 's') res=commonGetScrollbar(0x03,frmPtr);
		            else commonErrorWrongType("max");
		          }
		        */
          }
          break; 
       case 97:  //pageSize   //modified 04012005
          //modified 04012005
           if(found==false) goto abortNotFound;
#ifdef __MC68K__
           type = CtlGlueGetControlStyle((ControlType*)(PNO(controlPtr))); 
#else
           type = GlueCtlGlueGetControlStyle(pnoP, (ControlType*)(PNO(controlPtr))); 
#endif
           if  ((controlType==frmControlObj)&&((type==sliderCtl) || (type==feedbackSliderCtl) ))   //added 09242003
           {
               //it's a slider ctl
               
                  CtlGetSliderValues ((ControlType*)(PNO(controlPtr)),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue); 
                  
 #ifdef __MC68K__
                    if(arg4->kind != 's') 
		            {
		                restore4(pageSize);
		                return;
					}
			        else commonErrorWrongTypeOnGet("pageSize");
#else
                    if(arg4.dataElem->kind != 's') 
		            {
		            	double d = pageSize;
		            	d = SwapDouble(d);
                		misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
		                return;
					}
			        else commonErrorWrongTypeOnGet(pnoP, "pageSize");
#endif			   
			   
          }
          else
          {
          	/*
          		  if(controlType  != frmScrollBarObj) commonErrorWrongCtltypeOnGet("pageSize",controlType);
		          else
		          {
		            if(arg4->kind != 's') res=commonGetScrollbar(0x04,frmPtr);
		            else commonErrorWrongType("pageSize");
		          }		
            */
          }
          break;
       case 9:
       case 99:  //noItems
          if(found==false) goto abortNotFound;
          if( (controlType!=frmListObj)&&(controlType!=frmControlObj))
#ifdef __MC68K__
            commonErrorWrongCtltypeOnGet("noItems",controlType);
#else
            commonErrorWrongCtltypeOnGet(pnoP, "noItems",controlType);
#endif
          else
          {
#ifdef __MC68K__
            if(arg4->kind != 's') 
#else
            if(arg4.dataElem -> kind != 's') 
#endif
			{
			    if (controlType!=frmListObj)
			    {
                     //must point to list part of popup
                     PNO(controlPtr) = ((ControlType*)FrmGetObjectPtr(frmPtr,pos+1));
	                 PNO(controlid) = FrmGetObjectId(frmPtr,pos+1);
			    }
#ifdef __MC68K__
			    func_listgetnoitems();    
#else
                {
                  Int16 res;
                  double d;
                  res=LstGetNumberOfItems((ListType*)PNO(controlPtr));
                  d = res;
                d = SwapDouble(d);
                  misc_stodbl(pnoP, arg4.dataElem, arg4.occ1, arg4.occ2, arg4.occ3, &d);
                }
#endif
                return;
 			}        
            else
#ifdef __MC68K__
                commonErrorWrongTypeOnGet("noItems");
#else
                commonErrorWrongTypeOnGet(pnoP, "noItems");
#endif
          }
          break;
       }
       return;
abortNotFound:
   SysFatalAlert("Cannot find the control referenced.  May be caused by using bitmap.index which does not work.");            
#ifdef __MC68K__
   ErrThrow(-1);                 //inserted 05212003	   
#else
    GlueErrThrow(pnoP, -1);
#endif
    //restore4(res);
}

/********************************************************************************************/
#ifdef __MC68K__
void verb_nextscreen()   //nextform   //08142002 (old before RESET option)
#else
void verb_nextscreen(PNOBlock *pnoP)    // EMP
#endif
{
    UInt16 ID;
    VoidHand h;  //05282003

#ifdef __MC68K__
    ID=find_integer();
#else
    EventPtr evptr;
    ID = find_integer(pnoP);
#endif

    if(MenuGetActiveMenu()!=NULL) 
    {
      MenuEraseStatus(NULL);
      MenuSetActiveMenu(NULL);
      FrmSetMenu(FrmGetActiveForm(),0);
      MenuDispose(PNO(menuPtr));
      PNO(menuPtr)=(MenuBarType*)NULL; 
    }
    
    PNO(frmNo)=ID;

    h=MemHandleNew(sizeof(EventType));    //05282003
    if(h==0) OutOfMemory(6049);           //05282003
    evptr=(EventType*)MemHandleLock(h);   //05282003

#ifdef __MC68K__
    evptr->eType=firstUserEvent;
    evptr->data.generic.datum[0] =PNO(frmNo);
    evptr->data.generic.datum[1] =1;
#else
    evptr -> eType = ByteSwap16(firstUserEvent);
    evptr -> data.generic.datum[0] = ByteSwap16(ID);
    evptr -> data.generic.datum[1] = ByteSwap16(1);
#endif
    if(PNO(applVersionInteg) >= 300)   //chk for new reset option         //08142002
    {															  //08142002
#ifdef __MC68K__	
        evptr->data.generic.datum[2] =find_integer();             //08142002 get option to reset to design state from code
#else
        Int16 d2 = find_integer(pnoP);
        evptr->data.generic.datum[2] = ByteSwap16(d2);             //08142002 get option to reset to design state from code
#endif
        if (PNO(frmNo) == FrmGetActiveFormID())
	    {
	        //going to same form to clear it
	        FrmEraseForm(FrmGetActiveForm());   //erase form to avoid os err msg
	    } 
    }															  //08142002
    else evptr->data.generic.datum[2] =0;                         //08142002 dont reset to design state
    
    EvtAddEventToQueue(evptr);

    MemPtrFree(evptr);  //08032002
}

