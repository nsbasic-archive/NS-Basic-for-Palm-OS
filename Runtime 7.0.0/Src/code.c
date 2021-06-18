
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
#include "copy.h"
#include <ScrollBar.h>
#include <MathLib.h>
#include <TimeMgr.h>
#include <SerialMgr.h>
#include <SerialMgrOld.h>
#include <ErrorBase.h>                   //05212003

#ifdef ORG_NSB
#include "nsbasic.h"
#endif

#define PI 3.14159265358979
extern void dbugx(double* v, char* identifier);
extern Boolean find_ctlid(Boolean abort);
extern void  store_reg(double *r1,struct dataelem* de,
                      double* elem_ad,
                      unsigned int  elem_occ1,
                      unsigned int  elem_occ2,
                      unsigned int  elem_occ3 )   ;     /*-------store reg to data elem---*/
                   
void DoubleToStr (double val, CharPtr str);
void misc_format_number(struct dataelem* v, double* n , char * s);
extern  misc_fmtno(char* a,char *wk,int bef,int aft,int decpt,char *s);
extern int integ_value( struct dataelem *  arg, double *    arg_ad);        /*---calc integ value of data elem__*/

void verb_func_signatureEndCapture();
void commonEndCapture(FormPtr frmPtr, int controlid);

extern void gridGetSelectedText(FormType* frmPtr,VoidPtr controlPtr);      //added 09242003
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
void DoubleToStr (double val, CharPtr str);
UInt16 miscFrmGetObjectIdFromPtr(const FormType *formP, void *objP);  //GH  01.10.2002
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
int getx();
int gety();
extern misc_stodbl(struct dataelem *d,  unsigned int sub1,unsigned int sub2,unsigned int sub3, double  *result);
extern void verb_function_doit (unsigned int it);
int more_processing();
extern void misc_errmsg( char * the_msg);
void misc_format_time(struct dataelem* v, double* n , char * s);
void roundRtn(  double* reg, int noDecPos);
unsigned int ue(struct dataelem *arg, double *arg_ad);        /*---calc integ value of data elem__*/
double misc_fabs(double x);
void restore4(int i);
void test_debug(char *msg);
void store4( double *d);
void storestr4( char *s);
extern double misc_ceil(double x);
extern double misc_floor(double x);
extern double misc_int(double x);
extern void round_reg(double *reg,struct dataelem* de)   ;
void cvt_time_to_hms(double t,int *h, int *m, int* s);

void verb_func_setlocale();
void verb_func_format();
void verb_func_formatNL();


void restore_integ_value(int i,struct dataelem * arg,double * arg_ad,
unsigned int arg_occ1,unsigned int arg_occ2,unsigned int arg_occ3) ;
extern misc_format_date(struct dataelem*v,double*x,char*s);
extern misc_format_date(struct dataelem*v,double*x,char*s);
int dbug(char*s);

typedef long DATE; /*Julian dates*/

DATE julian_date(int day, int month , int year );
void calendar_date(DATE jdate, int *day, int *month, int *year);
int valid_date(int day, int month, int year);
int day_of_week(DATE jdate );
extern misc_stostr(struct dataelem * *d, unsigned int  sub1,unsigned int  sub2,unsigned int  sub3, char *result);
extern double StrToDouble(char *s);
extern void misc_free(void*,char *);
double cvt_date_to_dbl(int yr,int mo,int da);

void cvt_date_to_ymd(double d,int *yr, int *mo, int* da);

   int funcNextEntry =0;
   int funcs1To99      =0;
   int funcs100To199   =0;
   int funcs200To299   =0;
   int funcs300To399   =0;
   int funcs400To499   =0;
   int funcs500To599   =0;
   int funcs600To699   =0;
   int funcs700To799   =0;
   VoidPtr funcTable[250];
   
   
   
   
extern void find_arg_1();
extern void find_arg_2();
extern void find_arg_3();
extern void find_arg_4();
extern void find_arg_5();
extern void *misc_allocate(unsigned int , char*);
extern void misc_getstr(struct dataelem* arg,int occ,char*name);
ULong TimGetSeconds() ;
extern unsigned int misc_getint(struct dataelem  *,unsigned int ,unsigned int * );

#define MAX_ARITH_PLUS_1          arith_work_de_max+1
#define MAX_ARITH_STRING_PLUS_1   arith_work_de_max+string_work_de_max+1

extern int runtimeVersionInteg;
extern    int init_first_time ;
extern    unsigned int load_index_occ;
extern void move_it(char* a,unsigned int i,char* b,unsigned int j);
extern char master_quit_sw;
void verb_function_doit2( unsigned int it);
extern UInt     serRef;
void func_controlgetstatus();
void verb_func_getGeneralPropertyNumeric();
void verb_func_getGeneralPropertyString();
 
extern FormPtr findFormTheControlIsOn(int controlid);
extern int findControlsPositionOnForm(FormPtr* frmPtr, char* name); 
struct olddate
{
   unsigned char da_day;
   unsigned char da_mon;
   unsigned int da_year;
   unsigned char da_dayofweek;
} ;

struct tm
{
      int tm_sec;
      int tm_min;
      int tm_hour;
      int tm_mday;
      int tm_mon;
      int tm_year;
      int tm_wday;
      int tm_yday;
      int tm_isdst;
};

struct timedef
{
       unsigned char ti_min;
       unsigned char ti_hour;
       unsigned char ti_hund;
       unsigned char ti_sec;
};


//*****************************************************************************************
int asc(char c)
{
   return((int)c);
}
//*****************************************************************************************
void strupr(Char * s)
{
   int i;
   for(i=0;i<StrLen(s);++i)
   {
      if ((*(s+i)<'a')||(*(s+i)>'z')) continue;
      *(s+i)=*(s+i)+'A'-'a';
   }
}
//*****************************************************************************************
int isalpha( char  s)
{
  if (s<'a') return(0);
  if (s<='z')return(1);
  if (s<'A') return(0);
  if (s<='Z') return(1);
  return(0);
}
//*****************************************************************************************
void getdate ( struct olddate * olddt)
{
  DateTimeType newdt;

  TimSecondsToDateTime(TimGetSeconds(),&newdt);

  olddt->da_day=newdt.day;
  olddt->da_mon=newdt.month;
  olddt->da_year=newdt.year;
  olddt->da_dayofweek=newdt.weekDay;
}
//*****************************************************************************************
void gettime( struct timedef * t)
{
  DateTimeType newdt;
  TimSecondsToDateTime(TimGetSeconds(),&newdt);

  t->ti_min=newdt.minute;
  t->ti_sec=newdt.second;
  t->ti_hour=newdt.hour;
  t->ti_hund=0;
}

//*****************************************************************************************
double  mypow10(int i)   //modified 12182002
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
	      res=res/10;
	   }
    
    }
    return(res);
}

//*****************************************************************************************
void verb_func_instr()
{
   //arg1=starting pos
   //arg2=string to search
   //arg3=string to find
   //arg5=case sens(0=yes,1=no)
    
    char wk[28];
    int i;
    int len;
    VoidHand h;
    char *p;
    VoidHand h3;
    char *p3;
    int start;
    char *strPtr;   //added 07212003
    
    h=MemHandleNew(StrLen(arg2_val)+1);
    if(h==0) OutOfMemory(6070);  //05282003
    p=(char*)MemHandleLock(h);
    StrCopy(p,(char*)arg2_val);
    
    h3=MemHandleNew(StrLen(arg3_val)+1);
    if(h3==0) OutOfMemory(6071);  //05282003
    p3=(char*)MemHandleLock(h3);
    StrCopy(p3,(char*)arg3_val);
//StrPrintF(debug,"instr--  in=%s  srch=%s",p,p3);
//dbug(debug);    
    if( *((double*)arg5_val)==1.0)  //caseless
    {
      StrToLower(p,p);
      StrToLower(p3,p3);
    }
    len=StrLen(p3);
    start=integ_value(arg1,(double*)arg1_val)-1;
//StrPrintF(debug,"start=%d lenp=%d lenp3=%d",start,StrLen(p),len);
//dbug(debug);
    //01262003 if((start<0)||(start>StrLen(p)))
    if((start<0)||((start+len)>StrLen(p)))     //01262003
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
    restore4(i);
}
//*****************************************************************************************
extern int cvt_string_to_ymd( char *ad, int *y,int *m,int *d)
{
    int i;
    int res = 0;
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
extern int cvt_mmddyystring_to_ymd( char *ad, int *y,int *m,int *d)
{
    int i;
    int res = 0;
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

//*****************************************************************************************
double cvt_date_to_dbl(int yr,int mo,int da)
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
double cvt_time_to_dbl(int hr,int min,int sec)
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
void verb_func_chr()
{
   char s[2];
   s[1]=0x00;
   s[0]=integ_value(arg1,(double*)arg1_val);
   storestr4(&s[0]);
}
//*****************************************************************************************
void verb_func_abs()
{
 
   reg_a=*((double*)arg1_val);
   reg_a=misc_fabs(reg_a);
   store4( &reg_a );

   return;
}
//*****************************************************************************************
void verb_func_ascii()
{
    unsigned char c;
    c=*((char*)arg1_val);
    reg_a=c;
    store4(&reg_a);

    return;

}
//*****************************************************************************************
void verb_func_int()
{
   double d;
   double zero=0.0;

   reg_a=*((double*)arg1_val);

    d=misc_floor(misc_fabs(reg_a));
    if(reg_a<zero) d=zero - d;
    store4(&d);
   return;
}

//*****************************************************************************************
void verb_func_mod()
{
   
    double t;
   
   reg_a=*((double*)arg1_val);
   reg_b=*((double*)arg2_val);
   roundRtn(&reg_a,0); //round up to integer
   roundRtn(&reg_b,0); //same
   
   
   t=misc_int(reg_a/reg_b);      //10.10.2000
   reg_a=reg_a-t*reg_b;
   store4(&reg_a);
   
   return;
}
//*****************************************************************************************
void verb_func_nooccurs()
{
    int which;
    double d;
    which=integ_value(arg2,(double*)arg2_val);
    
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
    store4(&d);
   
    return;
}


//*****************************************************************************************
void verb_func_power10()
{
   double d;
   int j;
   int i;
   int absj;
   reg_a=*((double*)arg1_val);

   j=integ_value(arg2,(double*)arg2_val);
   if(j<0) absj=-j;
   else absj=j;
   d=1.0;
   for(i=1;i<=absj;++i) d*=10.0; 
   if (j>=0) reg_b=d;
   else reg_b=1.0/d;
   reg_a=reg_a*reg_b;
   store4(&reg_a);
   return;
}

//*****************************************************************************************
void verb_func_rand()
{
   double wk;
   ULong i;
  
   i=0;
   i=  SysRandom ( i );
   wk=i;
   reg_a= wk /((double)sysRandomMax+1); //01/19/03 GH: prevent value of 1.0000
   store4(&reg_a);
   return;
}
//*****************************************************************************************
void verb_func_round()
{


    double w;
    char wk[25];
    int k;
    int i;
    int j;
    
    
    k=integ_value(arg2,(double*)arg2_val);          //#decimal places to round after
    misc_format_number(arg1,(double*)arg1_val,wk);  //first get number into ascii string
    //may have to grow the string (e.g. 9.5 rounded becomes 10.0), so expand one char
    for(i=StrLen(wk);i>=0;--i)  wk[i+1]=wk[i];
    if(wk[0]=='-') wk[1]='0';
    else           wk[0]='0';
    for(i=0;i<StrLen(wk);++i)
    {
      if (wk[i]=='.') goto foundDecPoint;
    }
    //number is an integer, so no rounding required
    w=*((double*)arg1_val);
    goto itsSet;
foundDecPoint:
    if( StrLen(wk) < i+k+2)
    {
       w=*((double*)arg1_val);   //it doesn't have enuf dgts to round
       goto itsSet;
    }
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
       w=StrToDouble(wk);   //and convert back to double
    
itsSet:

   store4(&w);
   return;
}
//*****************************************************************************************
void roundRtn(  double* reg, int noDecPos)
{
    char wk1 [25];
    char wk2 [25];
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
void verb_func_left()
{

    int i;
    VoidHand h;
    char *p;
    i=integ_value(arg2,(double*)arg2_val);
    if(i>StrLen(arg1_val)) i=StrLen((char*)arg1_val);
    h=MemHandleNew(i+1);
    if(h==0) OutOfMemory(6072);  //05282003
    p=(char*)MemHandleLock(h);
    MemMove(p,arg1_val,i);
    MemSet(p+i,1,0x00);
    storestr4(p);
    MemPtrUnlock(p);
    MemHandleFree(h);
    return;
}
//*****************************************************************************************
void verb_func_right()
{
    VoidHand h;
    char *p;

    int j;
    int i;

    i=integ_value(arg2,(double*)arg2_val);

    if(i>StrLen(arg1_val)) i=StrLen(arg1_val);
    if(i<0)                i=0;

    h=MemHandleNew(i+1);
    if(h==0) OutOfMemory(6075);  //05282003 
    p=(char*)MemHandleLock(h);
    j=StrLen(arg1_val)-i;

    MemMove(p,(char*)arg1_val+j,i);

    MemSet(p+i,1,0x00);

    storestr4(p);

    MemPtrUnlock(p);
    MemHandleFree(h);
    return;
}
//*****************************************************************************************
void verb_func_length()
{
    restore4(StrLen(arg1_val));
    return;
}
//*****************************************************************************************
void verb_func_geteventtype()
{
     restore4(eventType);
}

//*****************************************************************************************
void verb_func_syseventavailable()
{
    //returns 1 if an event pending else 0
    int type;
        type=0;
        //12172001 if(EvtSysEventAvail(true)) type=1;
        //if(EvtSysEventAvail(false)) type=1;
        if(EvtSysEventAvail(true)) type=1;
        else
        {
             if(EvtKeyQueueEmpty()) ;
             else type=1;
        }
        restore4(type);
    return;
}
//*****************************************************************************************
void verb_func_maxlength()
{
    restore4(arg1->length);
    return;
}
//*****************************************************************************************
void verb_func_lower()
{
    VoidHand h;
    char *p;
    h=MemHandleNew(StrLen(arg1_val)+1);
    if(h==0) OutOfMemory(6076);  //05282003
    p=(char*)MemHandleLock(h);

    StrCopy(p,(char*)arg1_val);
    StrToLower(p,p);
     storestr4(p);
    MemPtrUnlock(p);
    MemHandleFree(h);
    return;
}
//*****************************************************************************************
void verb_func_mid()
{
    int i,j;
    VoidHand h;
    char *p;
    h=MemHandleNew(StrLen(arg1_val)+1);
    if(h==0) OutOfMemory(6078);  //05282003
    p=(char*)MemHandleLock(h);

    i=integ_value(arg2,(double*)arg2_val);
    j=integ_value(arg3,(double*)arg3_val);
    
    
    if((j<=0) ||  (i>StrLen(arg1_val)) )  //modified 02/012001 to check j<=0
    {
        //return a null string
        *p=0x00;
    }
    else
    {
      --i;
      if((StrLen((char*)arg1_val)-i)<j) j=StrLen((char*)arg1_val)-i;
    
      MemMove(p,(char*)arg1_val+i,j);
      MemSet(p+j,1,0x00);
    }
    storestr4(p);
    MemPtrUnlock(p);
    MemHandleFree(h);
    return;
}
//*****************************************************************************************
void verb_func_tonumber()  //VAL(strx)    func_val
{
    double f;
    double f2;
//char wk1[45];
//char wk2[45];    
// union 
//       {
//            FlpDouble q;
//            double d;
//       } x;
         
       
       f=StrToDouble(arg1_val) ;
       
       
//StrPrintF(debug,"in val tblno=%d functionstr=%s",arg1->tbl_no,(char*)arg1_val);
//dbug(debug);
//dbugx(&f,"in VAL function");
    
//x.q=FlpAToF((char*)arg1_val);
 
//f2=x.d;
//printDouble(f,wk1);
//printDouble(f2,wk2);
//StrPrintF(debug,"string=%s  f1=%s  f2=%s",arg1_val,wk1,wk2);
//dbug(debug); 
    store4( &f);

//dbugx(&f,"leaving val function");

    return;

}


//*****************************************************************************************
void verb_func_tostring()
{
    char work[80];
//dbugx(((double*)arg1_val),"atstartof func_tostring");
//StrPrintF(debug,"tostring is for tblno=%d",arg1->tbl_no);
//dbug(debug);
    misc_format_number(arg1,(double*)arg1_val,work);

    storestr4(work);

    return;
}
//*****************************************************************************************
void verb_func_proper()
{
    VoidHand h;
    char *p;
    
    char* ad;

    h=MemHandleNew(StrLen(arg1_val)+1);
    if(h==0) OutOfMemory(6079);  //05282003
    p=(char*)MemHandleLock(h);

    
    StrCopy(p,(char*)arg1_val);
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
    storestr4(p);
    MemPtrUnlock(p);
    MemHandleFree(h);
    return;
}
//*****************************************************************************************
void verb_func_upper()
{
    VoidHand h;
    char *p;
    h=MemHandleNew(StrLen(arg1_val)+1);
    if(h==0) OutOfMemory(6080);  //05282003
    p=(char*)MemHandleLock(h);

    
    StrCopy(p,(char*)arg1_val);
    strupr(p);
    storestr4(p);
    MemPtrUnlock(p);
    MemHandleFree(h);
    return;
}
//*****************************************************************************************
void verb_func_popupdate()
{
  //ldm 09122004 don't know why, but call to SelectDay is destroying arg1 and arg4
  //ldm 09122004 so put in a save/restore for these two variables
  Boolean z;
  int yr;
  int mo;
  int da;
  double d;
  char s[25];
  struct dataelem* saveArg1 = arg1;  //09122004
  struct dataelem* saveArg4 = arg4;  //09122004
  
  msgboxOrAlertUp = true;   //10122004
   
  cvt_date_to_ymd(*((double*)arg1_val),&yr,&mo,&da);
//StrPrintF(debug,"d addr = %lu arg1=%lu addr1=%lu null=%lu",&d, arg1,arg1_val,null_ptr);
//SysFatalAlert(debug);


  z=SelectDay(selectDayByDay,(SWord*)(&mo),(SWord*)(&da),(SWord*)(&yr),arg2_val);  //arg2 is title
  
//SysFatalAlert("Back from SelectDay call");
 
  if(z==true)
  {
//StrPrintF(debug,"d addr = %lu arg1=%lu addr1=%lu null=%lu",&d, arg1,arg1_val,null_ptr);
//SysFatalAlert(debug);
//SysFatalAlert("store 1");
    d=cvt_date_to_dbl(yr,mo,da);

//StrPrintF(debug,"d addr = %lu arg1=%lu addr1=%lu null=%lu saveArg1=%lu",&d, arg1,arg1_val,null_ptr,saveArg1);
//SysFatalAlert(debug);
    arg1 = saveArg1;          //09122004
    misc_stodbl1(&d);
//SysFatalAlert("store 2");
    arg4 = saveArg4;           //09122004
    d=1.0;
    store4(&d);   //1=chg'd
  }
  else
  {
    d=0.0;
     arg4 = saveArg4;           //09122004
    store4(&d);
  }
  
  msgboxOrAlertUp = false;   //10122004
}
//*****************************************************************************************
void verb_func_popuptime()
{
  struct dataelem *saveArg4;   //ldm 09132004
  struct dataelem *saveArg1;   //ldm09132004
  struct dataelem *saveArg2;   //ldm09132004
   
  Boolean z;
  int hr;
  int min;
  int sec;
  TimeType start;
  TimeType end;
  double d;
  //SWord startOfDay;									//11.03.06 GWH
  
  cvt_time_to_hms(*(double*)arg1_val,&hr,&min,&sec);
  start.hours=hr;
  start.minutes=min;
  //if(start.hours==0) start.hours=8;					//03.12.03 GWH
  if(start.hours+start.minutes==0) start.hours=8;		//11.03.06 GWH

  cvt_time_to_hms(*(double*)arg2_val,&hr,&min,&sec);
  end.hours=hr;
  end.minutes=min;
  //if(end.hours==0) end.hours=17;						//03.12.03 GWH
  if(end.hours+end.minutes==0) end.hours=17;			//11.03.06 GWH
  //startOfDay=8;										//11.03.06 GWH
  
  saveArg1=arg1;
  saveArg2=arg2;
  saveArg4=arg4;
  
  msgboxOrAlertUp = true;   //10122004
  
  if(romVersion>=(unsigned long)(0x03500000))
  {
     //z=SelectTime(&start,&end,false,arg3_val,8,5,8);  //03.12.03 GWH
     z=SelectTime(&start,&end,false,arg3_val,start.hours,end.hours,start.hours);  //arg2 is title
  }
  else
  {
    //z=SelectTimeV33(&start,&end,false,arg3_val,8);  //arg2 is title //03.12.03 GWH
    z=SelectTimeV33(&start,&end,false,arg3_val,start.hours);  //arg2 is title
  }
  
  
  arg1=saveArg1;  //ldm09132004
  arg2=saveArg2;  //ldm09132004
  arg4=saveArg4;  //ldm09132004
  
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
    misc_stodbl1(&d);

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
    misc_stodbl2(&d);
    d=1.0;
    store4(&d);   //1=chg'd
  }
  else
  {
    d=0.0;
    store4(&d);

  }
  
  msgboxOrAlertUp = false;    //10122004
}

//*****************************************************************************************
void verb_func_todate()
{
    char *ad;
    
    int res;
    int y,m,d;
    char errmsg[80];
    double w;
    
    ad=(char*)arg1_val;

    res=cvt_string_to_ymd( ad,&y,&m,&d);

    if(res==0)
    {
       res=valid_date(d,m,y);
       if(res==0) res=1;
       else       res=0;
    }
    if(res)
    {
       
       StrPrintF(errmsg,"String '%s' is not a valid date.",ad);
       misc_errmsg(errmsg);
    }

    w=cvt_date_to_dbl(y,m,d);
    store4(&w);
    return;
}
//*****************************************************************************************
void verb_func_yearmonth()
{
    char work[80];
    misc_format_date(arg1,(double*)arg1_val,work);
    work[7]=0x00;
    
    storestr4(work);
    return;
}
//*****************************************************************************************
void verb_func_datemmddyy()
{
    char dat[50];
    char work[80];

    misc_format_date(arg1,(double*)arg1_val,dat);

    StrCopy(work,&dat[5]);
    dat[4]=0x00;
    StrCat(work,"/");
    StrCat(work,dat);
    
    storestr4(work);
    return;
}
//*****************************************************************************************
void verb_func_monthday()
{
    int i;
    char work[80];
    misc_format_date(arg1,(double*)arg1_val,work);
    for(i=0;i<6;++i) work[i]=work[i+5];
    
    storestr4(work);
    return;
}
//*****************************************************************************************
void verb_func_hourmin()
{
    char work[80];
    misc_format_time(arg1,(double *)arg1_val,work);
    work[5]=0x00;
    
    storestr4(work);
    return;
}
//*****************************************************************************************
void verb_func_hourminampm()
{
    char work[80];
    int hh;
    int mm;
    int ss;
    double tim;
    char ampm[4];
    
    tim=*((double*)arg1_val);
//misc_format_time(arg1,&tim,work);
//StrPrintF(debug,"*5*time is %s",work);
//dbug(debug);
    cvt_time_to_hms(tim,&hh,&mm,&ss);
//StrPrintF(debug,"*10*in hourminampm hr=%d min=%d sec=%d",hh,mm,ss);
//test_debug(debug);
    /*" pm"*/
    if(hh>11){ StrCopy(ampm," pm"); if(hh>12) hh=hh-12; }
    /*" am"*/
    else      StrCopy(ampm," am");
    if(hh==0) hh=12;
    tim=cvt_time_to_dbl(hh,mm,ss);
    misc_format_time (arg1,&tim,work);
    work[5]=0x00;
    StrCat(work,ampm);
    
    storestr4(work);
    return;
}

//*****************************************************************************************
void verb_func_totime()
{
    char *ad;
    int i;
    int h,m,s;
    int res=0;
    double w;
    char errmsg[80];
    char wk[20];
    ad=(char*)arg1_val;
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
       StrPrintF(errmsg,"String '%s' is not a valid time.",(char*)arg1_val);
       misc_errmsg(errmsg);
    }
    w=cvt_time_to_dbl(h,m,s);
    
    store4(&w);
    return;
}
//*****************************************************************************************
void verb_func_date()
{
    double w;
    int y,m,d;
    char errmsg[80];
    y=*(double*)arg1_val;
    m=*(double*)arg2_val;
    d=*(double*)arg3_val;
    if(valid_date(d,m,y)==0)
    {
       StrPrintF(errmsg,"Year=%i Month=%i Day=%i is not a valid date.",y,m,d);
       misc_errmsg(errmsg);
    }
    w=cvt_date_to_dbl(y,m,d);
    
    store4(&w);
    return;
}

//*****************************************************************************************
void verb_func_time()
{
    int h,m,s;
    double w;
    char errmsg[80];
    h=*(double*)arg1_val;
    m=*(double*)arg2_val;
    s=*(double*)arg3_val;
    if( (h<0) || (h>23) || (m<0) || (m>59) || (s<0) || (s>59))
    {
       /**/
       StrPrintF(errmsg,"Hour=%i Minute=%i Second=%i is not a valid time.",
               h,m,s);
       misc_errmsg(errmsg);
    }
    w=cvt_time_to_dbl(h,m,s);
    store4(&w);
    return;
}
//*****************************************************************************************
void verb_func_day()
{
    double w;
    int y,m,d;

    w=*(double*)arg1_val;
    cvt_date_to_ymd(w,&y,&m,&d);
    w=d;
 
    store4(&w);
    return;
}
//*****************************************************************************************
void verb_func_hour()
{
    double w;
    int h,m,s;

    w=*(double*)arg1_val;
    cvt_time_to_hms(w,&h,&m,&s);
    w=h;
    
    store4(&w);
    return;
}
//*****************************************************************************************
void verb_func_minute()
{
    double w;
    int h,m,s;

    w=*(double*)arg1_val;
    cvt_time_to_hms(w,&h,&m,&s);
    w=m;
    
    store4(&w);
    return;
}
//*****************************************************************************************
void verb_func_second()
{
    double w;
    int h,m,s;

    w=*(double*)arg1_val;
    cvt_time_to_hms(w,&h,&m,&s);
    w=s;
    store4(&w);
    return;
}
//*****************************************************************************************
void verb_func_month()
{
    double w;
    int y,m,d;

    w=*(double*)arg1_val;
    cvt_date_to_ymd(w,&y,&m,&d);
    w=m;
    
    store4(&w);
    return;
}
//*****************************************************************************************
void verb_func_year()
{
    double w;
    int y,m,d;

    w=*(double*)arg1_val;
    cvt_date_to_ymd(w,&y,&m,&d);
    w=y;
    
    store4(&w);
    return;
}
//*****************************************************************************************
//06102002 new funcs timediff and datediff ****
void verb_func_dayofweek()
{
    double w;
    int y,m,d;
    
    w=*(double*)arg1_val;
    cvt_date_to_ymd(w,&y,&m,&d);
    w=DayOfWeek(m,d,y)+1;
    
    store4(&w);
    return;
}
//*****************************************************************************************
void verb_func_datediff()
{
    double w;
    double daysdiff;
    DATE date1;
    DATE date2;
    int y,m,d;
    
    w=*(double*)arg1_val;
    cvt_date_to_ymd(w,&y,&m,&d);
    date1=julian_date(d,m,y);
    
    w=*(double*)arg2_val;
    cvt_date_to_ymd(w,&y,&m,&d);
    date2=julian_date(d,m,y);
    
    daysdiff=date2-date1;
    store4(&daysdiff);
    return;
}
//*****************************************************************************************
//06102002 **** end *****
void verb_func_timediff()
{
    double w;
    double timediff;
    long secs1;
    long secs2;
    int hr,min,sec;
    long temp1;
    long temp2;
    long temp3;
    
    
    cvt_time_to_hms(*(double*)arg1_val,&hr,&min,&sec);
    temp1=hr;
    temp1*=3600;
    temp2=min;
    temp2*=60;
    
    secs1=temp1+temp2+sec;
    
    cvt_time_to_hms(*(double*)arg2_val,&hr,&min,&sec);
    temp1=hr;
    temp1*=3600;
    temp2=min;
    temp2*=60;
    secs2=temp1+temp2+sec;
    
    timediff=secs2-secs1;
    store4(&timediff);
    return;
}

//*****************************************************************************************
void verb_func_dayofyear()
{
    double w;
    int y,m,d;
    unsigned long nowdays;
    

    DateType dt;
    w=*(double*)arg1_val;
    cvt_date_to_ymd(w,&y,&m,&d);
    dt.year=y;
    dt.month=m;
    dt.day=d;
    nowdays=DateToDays(dt);
    dt.month=1;
    dt.day=1;
    w=nowdays-DateToDays(dt)+1;
    
    store4(&w);
    return;
}


//*****************************************************************************************
void verb_func_ceiling()
{
   
   reg_a=*((double*)arg1_val);

   reg_a=misc_ceil(reg_a);
  
   store4(&reg_a);
   return;
}
//*****************************************************************************************
void verb_func_floor()
{
  
   reg_a=*((double*)arg1_val);

   reg_a=misc_floor(reg_a);
   
   store4(&reg_a);
    return;
}

//*****************************************************************************************
void verb_func_sign()
{
   
   reg_a=*((double*)arg1_val);

   if(reg_a<0) reg_b=-1;
   else reg_b=1;
   store4(&reg_b);

    return;
}
//*****************************************************************************************
void verb_func_trunc()
{
    
    double w;
    char wk[25];
    int k;
    int i;
    
    
    k=integ_value(arg2,(double*)arg2_val);          //#decimal places to truncate after
    misc_format_number(arg1,(double*)arg1_val,wk);  //first get number into ascii string
    for(i=0;i<StrLen(wk);++i)
    {
      if (wk[i]=='.') goto foundDecPoint;
    }
    //number is an integer, so no truncation required
    w=*((double*)arg1_val);
    goto itsSet;
foundDecPoint:
    if( StrLen(wk) < i+k+2)
    {
       w=*((double*)arg1_val);   //its already truncated
    }
    else
    {
       //has more dec places than wanted, so truncate
       wk[i+k+1]=0x00;      //truncate after k dec places
       w=StrToDouble(wk);   //and convert back to double
    }
itsSet:

//StrPrintF(debug,"string=%s #=%d",wk,w);
//dbug(debug);
    store4(&w);

    return;
}
//*****************************************************************************************
void verb_func_leftpad()
{
    VoidHand h;
    char * wk;
    int i,j,k;
    h=MemHandleNew(*(double*)arg2_val+StrLen(arg1_val)+1);
    if(h==0) OutOfMemory(6081);  //05282003
    wk=(char*)MemHandleLock(h);

    j=0;
    i=*(double*)arg2_val;
    k=StrLen(arg1_val);

    while (k < i)
    {
        wk[j++]=' ';
        ++k;
    }
    wk[j]=0x00;
    StrCat(wk,(char*)arg1_val);
    misc_stostr4(wk);
    MemPtrUnlock(wk);
    MemHandleFree(h);
    return;
}
//*****************************************************************************************
void verb_func_rightpad()
{
    VoidHand h;
    char * wk;

    int i,j;

    h=MemHandleNew(*((double*)arg2_val)+StrLen(arg1_val)+1);
    if(h==0) OutOfMemory(6082);  //05282003
    wk=(char*)MemHandleLock(h);

    StrCopy(wk,(char*)arg1_val);
    j=StrLen(wk);
    i=*((double*)arg2_val);

    while (j < i)
    {
       wk[j++]=' ';
       
    }
    wk[j]=0x00;
    misc_stostr4(wk);
    MemPtrUnlock(wk);
    MemHandleFree(h);
    return;
}
//*****************************************************************************************
void verb_func_adddays()
{
    int y,m,d,a;
    DATE jdate;
    double w,s;
    a=*(double*)arg2_val;
    s=*(double*)arg1_val;
    cvt_date_to_ymd(s,&y,&m,&d);
    jdate=julian_date(d,m,y);

    jdate += a;
    calendar_date(jdate,&d,&m,&y);
    w=cvt_date_to_dbl(y,m,d);
    
    store4(&w);

    return;
}
//*****************************************************************************************
void verb_func_subtractdays()
{
    int y,m,d,a;
    DATE jdate;
    double w,s;
    a=*(double*)arg2_val;
    s=*(double*)arg1_val;
    cvt_date_to_ymd(s,&y,&m,&d);
    jdate=julian_date(d,m,y);

    jdate -= a;
    calendar_date(jdate,&d,&m,&y);
    w=cvt_date_to_dbl(y,m,d);
    
    store4(&w);

    return;
}
//*****************************************************************************************
void verb_func_addmonths()
{
    int y,m,d,a;
    double w,s;
    a=*(double*)arg2_val;
    s=*(double*)arg1_val;
    cvt_date_to_ymd(s,&y,&m,&d);
    m += a;
    while (m > 12)
    {
        m -= 12;
        y += 1;
    }
    w=cvt_date_to_dbl(y,m,d);
    
    store4(&w);

    return;
}
//*****************************************************************************************
void verb_func_subtractmonths()
{
    int y,m,d,a;
    double w,s;
    a=*(double*)arg2_val;
    s=*(double*)arg1_val;
    cvt_date_to_ymd(s,&y,&m,&d);
    m -= a;
    while (m < 1)
    {
        m += 12;
        y -= 1;
    }
    w=cvt_date_to_dbl(y,m,d);
    
    store4(&w);

    return;
}
//*****************************************************************************************
void verb_func_addyears()
{
    int y,m,d,a;
    double w,s;
    a=*(double*)arg2_val;
    s=*(double*)arg1_val;
    cvt_date_to_ymd(s,&y,&m,&d);
    y=y+a;
    w=cvt_date_to_dbl(y,m,d);

    
    store4(&w);

    return;
}
//*****************************************************************************************
void verb_func_subtractyears()
{
    int y,m,d,a;
    double w,s;
    a=*(double*)arg2_val;
    s=*(double*)arg1_val;
    cvt_date_to_ymd(s,&y,&m,&d);
    y=y-a;
    w=cvt_date_to_dbl(y,m,d);

    
    store4(&w);

    return;
}
//*****************************************************************************************
void verb_func_firstofmonth()
{
    double w;
    int y,m,d;

    w=*(double*)arg1_val;
    cvt_date_to_ymd(w,&y,&m,&d);
    d=1;
    w=cvt_date_to_dbl(y,m,d);

    
    store4(&w);

    return;
}
//*****************************************************************************************
void verb_func_lastofmonth()
{
    double w;
    int y,m,d;

    w=*(double*)arg1_val;
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
    
    store4(&w);

    return;
}
//*****************************************************************************************
void verb_func_getkey()
{
//StrPrintF(debug,"in function keydown event val=%d",lastKeyString[0]);
//SysFatalAlert(debug);
    storestr4(lastKeyString);
}

//*****************************************************************************************
void verb_func_sysdate()
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
   
    store4(&w);
    return;
}
//*****************************************************************************************
void verb_func_systime()
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
   
    store4(&t);

    return;
}
//*****************************************************************************************
void verb_func_sysinfo()
{
    double ticks;
    Word ticksPerSec;
    int which;
    UInt32 numBytes;
    UInt32 freeBytes;
    UInt32 maxChunk;
    Err err;
    
    which=integ_value(arg1,(double*)arg1_val);
    
    switch (which)
    {
        case 0:
          reg_a=runtimeVersionInteg ; //runtime version
          store4(&reg_a);
          break;
        case 1: //tick count
          ticks=TimGetTicks();
          store4(&ticks);
          break;
        case 2:  //ticks per second         
          ticksPerSec=SysTicksPerSecond();
          restore4(ticksPerSec);
          break;
        case 3:  //Serial Port ID         
          restore4(serRef);
          break;
        case 4:  //Current Form ID       
          restore4(FrmGetActiveFormID());
          break;
        case 5:	 //bytes waiting in serial queue
          if(gOldSerialManager) err=SerReceiveCheck(serRef, &numBytes);
          else err=SrmReceiveCheck(serRef, &numBytes);
          if(err>0) numBytes=0;
          restore4(numBytes);
		  break;
        case 6: //ROM major version  			  //GWH 2003.03.27
		  restore4(sysGetROMVerMajor(romVersion)*10+sysGetROMVerMinor(romVersion));
          break;
        case 7:	//Get Coordinate System   		  //GWH 2003.03.27
          if (romVersion>=0x05000000) restore4(WinGetCoordinateSystem());
          else restore4(0);
          break;
        case 8: //Get free storage heap          //GWH 2003.06.09
          //does not give correct result if more than 32,767k free
          MemHeapFreeBytes((UInt16) 1, &freeBytes, &maxChunk);
          restore4(freeBytes/1024);
          break;
        case 9: //Get last data.keyDown.chr  //GWH 2003.11.03
          restore4(lastKeyDownChr);
          break;
        case 10: //Get last data.keyDown.KeyCode  //GWH 2003.11.03
          restore4(lastKeyDownKeyCode);
          break;
        case 11: //Get last data.keyDown.modifiers  //GWH 2003.11.03
          restore4(lastKeyDownModifiers);
          break;
    }
    return;
}

//*****************************************************************************************
DATE julian_date(int day, int month , int year )
{
     /* calc Julian date(if yr is B.c> will be negative*/
     int a,b;
     float year_corr;
     year_corr=(year > 0 ? 0.0 : 0.75 );
     if (month <= 2 )
     {
        year--;
        month += 12;
     }
     b = 0;
     if( year * 10000.0 + month * 100.0 + day >= 15821015.0)
     {
       a=year/100;
       b=2-a + a/4;
     }
     return(DATE) (long) (365.25 * year - year_corr) +
       (long) (30.6001 * (month+1)) + day + 1720994L + b;
}
//*****************************************************************************************
void calendar_date(DATE jdate, int *day, int *month, int *year)
{
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
   *day=(int)b-d-(long)(30.6001 * e);
   *month=(int)(e < 13.5) ? e-1: e-13;
   *year=(int)(*month > 2.5) ? (c-4716) : c - 4715;
}
//*****************************************************************************************
int valid_date(int day, int month, int year)
{
   /*also includes chk if year is leap yr*/
   int cal_day,cal_month,cal_year;
   /*cvt date to Julian date and back*/
   calendar_date(julian_date(day,month,year),
                &cal_day,&cal_month,&cal_year);
   /*date is valid if day,month,and year did not chg*/
   return((day==cal_day)&&(month==cal_month)&&(year==cal_year));
}
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

//*****************************************************************************************
void func_fieldgettext()
{
  char *ptr;
  VoidHand h;
  char *c;

  ptr=FldGetTextPtr((FieldType*)controlPtr);
  if(ptr==0)
  {
     h=MemHandleNew(1);
     if(h==0) OutOfMemory(6084);  //05282003
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
//*****************************************************************************************
void func_controlgetlabel()
{
  FormPtr frmPtr;
  
  frmPtr=FrmGetActiveForm();
  commonGetLabel(frmPtr,controlid);
  
 
}
//*****************************************************************************************
void func_controlgettext()
{
  char *ptr;
  VoidHand h;
  char *c;
 
  ptr=(char*)CtlGetLabel((ControlType*)controlPtr);
  if(ptr==0)
  {
     h=MemHandleNew(1);
     if(h==0) OutOfMemory(6087);  //05282003
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
void func_listgetnoitems()
{
  int res;
  res=LstGetNumberOfItems((ListType*)controlPtr);
  restore4(res);   //added 4.17.2000
}
//*****************************************************************************************
void func_listgetselecteditemno()
{
  int res;
  res=LstGetSelection((ListType*)controlPtr);
  if (LstGetNumberOfItems((ListType*)controlPtr)==0) res=-1;
  
  restore4(res+1);
}
//*****************************************************************************************
void commonGetID(FormPtr frmPtr,ControlType* controlPtr)  //09302002  added entire routien
{
  int Id;
  Id=miscFrmGetObjectIdFromPtr(frmPtr, controlPtr);  
  restore4(Id);
}
//*****************************************************************************************
void func_controlgetID()  //09302002 modified
{
  
  FormPtr frmPtr;
  frmPtr=FrmGetActiveForm();
  commonGetID(frmPtr,controlPtr);   //09302002
  
 
}

//*****************************************************************************************
void commonGetItemText(int i)
{
  char *ptr;
  
  ListPtr l;

  
 
  l=(ListType*)controlPtr;
  if((i<0) || (i>=LstGetNumberOfItems(l)))
  {
      //SysFatalAlert("Program accessing a list to get text when no item selected");
      storestr4("***");  //??????
      return;
  }

  
  
  ptr=LstGetSelectionText(l, i); //GHGlue
  storestr4(ptr);
}
//*****************************************************************************************
void func_listgetitemtext()
{
  
  int i;
 

  
  i=integ_value(arg1,(double*)arg1_val)-1;

  commonGetItemText(i);
}
//*****************************************************************************************
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
          if(FrmGetObjectId(frm,i)==(controlid+1))  goto gotTheAssocList;  //found the associated listctl for this popup ctl
          
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
      ptr=(char*)CtlGetLabel((ControlType*)controlPtr);   //just get the control's current text value
      storestr4(ptr);
      return;
  }
//dbug("returning the selected list entry");
  
  //04022003ptr=*((char**)((char *)(listObjPtr->itemsText)+i*4) );
  ptr=LstGetSelectionText(listObjPtr,i)  ;    //added 04022003 (George's Glue code)
  //ptr=*((char**)((char *)(LstGlueGetItemsText(listObjPtr))+i*4) );  //(Larry's code - gets an error)
  storestr4(ptr);

}

//*****************************************************************************************
void func_scrollbargetcurrent()
{
 int res;
 SWord val;
 SWord min;
 SWord max;
 SWord pag;
  
 SclGetScrollBar((ScrollBarPtr)controlPtr,&val,&min,&max,&pag);
  res=val;
  restore4(val);
}

//*****************************************************************************************
void func_acos()
{
  double w;
  w=acos(*(double*)arg1_val);
  store4(&w);
}
//*****************************************************************************************
void func_asin()
{
  double w;
  w=asin(*(double*)arg1_val);
  store4(&w);
}
//*****************************************************************************************
void func_atan()
{
  double w;
  w=atan(*(double*)arg1_val);
  store4(&w);
}
//*****************************************************************************************
void func_atan2()
{
  double w;
  w=atan2(*(double*)arg1_val,*(double*)arg2_val);
  store4(&w);
}
//*****************************************************************************************
void func_cos()
{
  double w;
  w=cos(*(double*)arg1_val);
  store4(&w);
}
//*****************************************************************************************
void func_sin()
{
  double w;
  w=sin(*(double*)arg1_val);
  store4(&w);
}
//*****************************************************************************************
void func_tan()
{
  double w;
  w=tan(*(double*)arg1_val);
  store4(&w);
}
//*****************************************************************************************
void func_cosh()
{
  double w;
  w=cosh(*(double*)arg1_val);
  store4(&w);
}
//*****************************************************************************************
void func_sinh()
{
  double w;
  w=sinh(*(double*)arg1_val);
  store4(&w);
}
//*****************************************************************************************
void func_tanh()
{
  double w;
  w=tanh(*(double*)arg1_val);
  store4(&w);
}
//*****************************************************************************************
void func_acosh()
{
  double w;
  w=acosh(*(double*)arg1_val);
  store4(&w);
}
//*****************************************************************************************
void func_asinh()
{
  double w;
  w=asinh(*(double*)arg1_val);
  store4(&w);
}
//*****************************************************************************************
void func_atanh()
{
  double w;
  w=atanh(*(double*)arg1_val);
  store4(&w);
}
//*****************************************************************************************
void func_exp()
{
  double w;
  w=exp(*(double*)arg1_val);
  store4(&w);
}
//*****************************************************************************************
void func_log()
{
  double w;
  w=log(*(double*)arg1_val);
  store4(&w);
}
//*****************************************************************************************
void func_log10()
{
  double w;
  w=log10(*(double*)arg1_val);
  store4(&w);
}
//*****************************************************************************************
void func_cbrt()
{
  double w;
  w=cbrt(*(double*)arg1_val);
  store4(&w);
}
//*****************************************************************************************
void func_rem()
{
  
   double t;
   long k;
   
   

   reg_a=*((double*)arg1_val);
   reg_b=*((double*)arg2_val);

   
       
   t=reg_a/reg_b;
   k=t;
   reg_a=reg_a-k*reg_b;
   store4(&reg_a);
}

//*****************************************************************************************
void func_pow()
{
  double w;
  w=pow(*(double*)arg1_val,*(double*)arg2_val);
  store4(&w);
}
//*****************************************************************************************
void func_sqrt()
{
  double w;
  w=sqrt(*(double*)arg1_val);
  store4(&w);
}
//*****************************************************************************************
void verb_func_degtoradians()
{
    double d;
    d=(*(double*)arg1_val)*2*PI/360.0;
    store4(&d);
}
//*****************************************************************************************
void verb_func_radtodegrees()
{
    double d;
    d=(*(double*)arg1_val)*360.0/(2*PI);
    store4(&d);
}

//*****************************************************************************************
void verb_func_rtrim()
{
    VoidHand h;
    char *p;
    char *a;
    h=MemHandleNew(StrLen(arg1_val)+1);
    if(h==0) OutOfMemory(6088);  //05282003
    p=(char*)MemHandleLock(h);

    StrCopy(p,(char*)arg1_val);
    a=p+StrLen(p);
    while (1)
    {
       --a;
       if(a<p) break;
       if(*a==' ') *a=0x00;
       else break;
    }
    storestr4(p);
    MemPtrUnlock(p);
    MemHandleFree(h);
    return;
}
//*****************************************************************************************
void verb_func_getversion()   // EMP 09032003
{
    VoidHand h;
    char *p;
    char *a;
    LocalID dbID;
    
    dbID = DmFindDatabase(0, (char *)arg1_val);
    
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
                storestr4(p);
                MemHandleUnlock(rsrc);
                DmReleaseResource(rsrc);
            }
            else
            {
                storestr4("ERR: Could not find resource");
            }
            DmCloseDatabase(openDB);
        }
        else
        {
            storestr4("ERR: Could not open");
        }
    }
    else
    {
        storestr4("ERR: Database not found");
    }

    return;
}
//*****************************************************************************************
void verb_func_ltrim()
{
    VoidHand h;
    char *p;
    char *a;
    char *d;
   
    h=MemHandleNew(StrLen(arg1_val)+1);
    if(h==0) OutOfMemory(6089);  //05282003
    p=(char*)MemHandleLock(h);

   
    a=(char*)arg1_val;
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
    
    storestr4(p);
    MemPtrUnlock(p);
    MemHandleFree(h);
    return;
}
//*****************************************************************************************
void verb_func_trim()
{
 VoidHand h;
    char *p;
    char *a;
    char *d;
   
    h=MemHandleNew(StrLen(arg1_val)+1);
    if(h==0) OutOfMemory(6090);  //05282003
    p=(char*)MemHandleLock(h);

 
    a=(char*)arg1_val;
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
    storestr4(p);
    MemPtrUnlock(p);
    MemHandleFree(h);
    return;
}
//*****************************************************************************************
void verb_func_mmddyytodate()
{
char *ad;
    
    int res;
    int y,m,d;
    char errmsg[80];
    double w;
    
    ad=(char*)arg1_val;

    res=cvt_mmddyystring_to_ymd( ad,&y,&m,&d);
    if(res==0)
    {
       res=valid_date(d,m,y);
       if(res==0) res=1;
       else       res=0;
    }
    if(res)
    {
       StrPrintF(errmsg,"String '%s' is not a valid date in mm/dd/yy format.",ad);
       misc_errmsg(errmsg);
    }

    w=cvt_date_to_dbl(y,m,d);

    store4(&w);
    return;
}
//*****************************************************************************************
void verb_func_testnum()
{
   //arg1=string to test for numeric
   //arg2=signs allowed  " "=none,"+" or  "-"=  +or-
   //arg3=max no decs before dec pt
   //arg5=max no decs after dec pt
 int err;
 int b=0;
 int a=0;
 char s=' ';
 char *p=(char*)arg1_val;
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
         if(p!=arg1_val)
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
 if (a>integ_value(arg3,(double*)arg3_val)) {res=1; goto err;}
 if (b>integ_value(arg5,(double*)arg5_val)) {res=2; goto err;}
 if (decYet>1)          {res=3; goto err;}
 if ( (*((char*)arg2_val)==' ') && (s!=' ') ) {res=6; goto err;}
 res=0;
    
err:
    restore4(res);
}
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
//*****************************************************************************************
void verb_func_controlscount()
{
    FormPtr frmPtr;
    int i;
    int j;
    char*ad;
    char *p2;
    VoidHand h2;
    char name[256];
    unsigned int ID;
    
    ID=find_integer();
    
    
    //find_arg_1();
	//h2=MiscDmGetResource(rscTag,(ULong)9907,"vtoc");  //read the view tbl-of-contents record
    ///if(h2==0)
    //{
     //  SysFatalAlert("Can't find view TOC record");
    //}
    //p2=MiscHandleLock(h2);

    //for(i=0;i<view_cnt;++i)  //for each view
    //{
     // ID=basc_dbGetInt( (char*)p2);  //get id of view from the vtoc record
     // p2+=2;   //06102002
      //ad=&name[0];
     // 							//06102002
	//		//read form name	//06102002
	//		while(1)				//06102002
   	//		{						//06102002
    //				*ad=*p2;			//06102002
   	//			++ad;				//06102002
   	//			++p2;				//06102002
   	//			if((*p2)==0x00) break; //06102002
  	//		}						//06102002
  	//  								//06102002
  	//  							//06102002
    //  
    //  if(StrCompare(name,arg1_val)==0)
    //  {
    //      goto matchedName;
    // } 
      
//dbug("loading form   in vtoc processing:");
          
   //}
   //StrPrintF(debug,"Illegal form name used = %s",name);
   //SysFatalAlert(debug);
//matchedName:
    //MemHandleUnlock(h2);      
    //DmReleaseResource(h2); 
    
    frmPtr=FrmGetFormPtr(ID);   //pt to form
    if(frmPtr==NULL) return;   //???says frm not loaded
//StrPrintF(debug,"got form=%d #objs=%d",wkid,  FrmGetNumberOfObjects(frmPtr));
//SysFatalAlert(debug);
    j=FrmGetNumberOfObjects((FormType*)frmPtr);
    restore4(j);   
}   
//*****************************************************************************************
void AddToFuncTable(int funcNo, VoidPtr f)
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
        AddToFuncTable (  6,   &verb_func_setlocale);
        AddToFuncTable (  7,   &verb_func_power10);
        AddToFuncTable (  8,   &verb_func_chr);
        AddToFuncTable (  9,   &verb_func_format);
        AddToFuncTable (  10,  &verb_func_formatNL);
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

//*****************************************************************************************
extern void verb_function_doit (unsigned int it)
{
        verb_function_doit2(it);
}

//*****************************************************************************************
void cvt_date_to_ymd(double d,int *yr, int *mo, int* da)
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
void cvt_time_to_hms(double t,int *h, int *m, int* s)
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
//??
}
//*****************************************************************************************
void verb_func_format()
{
  int i;
  char wk[128];
  int decpt;
  int bef;
  int aft;
  char s[128];
        
    DoubleToStr(*((double*)arg1_val),wk);

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
    misc_fmtno((char*)arg2_val,wk,bef,aft,decpt,s);
    misc_stostr4(s);
}
/*******************************************************************************************/
void verb_func_formatNL()
{
//??
}
/*******************************************************************************************/
void func_controlgetstatus()
{
  int res;
  res=CtlGetValue((ControlType*)controlPtr);
  restore4(res);
}
/*******************************************************************************************/
void verb_func_getGeneralPropertyNumeric()
{
  UInt16 minValue;  //added 04012005
  UInt16 maxValue;  //added 04012005
  UInt16 pageSize;  //added 04012005
  UInt16 curValue;  //added 04012005
  ControlStyleType type;  //added 04012005 
  
  //no auto arguments (this is really treated as a verb
  int res;
  int controlType;
  int pos=0;
  char c;
  Boolean found;
  int propId;
  FormPtr frmPtr;        //added 5.20.2000 
  RectangleType bounds;  //added 04012005
  
  found=true;
   find_arg_4();    //get result var 
   c=find_char();   //type of control identifier
//StrPrintF(debug,"getGeneralProp c=%c",c);
//dbug(debug);
   switch(c)
   {
      case 'i':  //ctlid
        found=find_ctlid(false);
        if(found==true)
        {
//dbug("true");
          frmPtr=findFormTheControlIsOn(controlid);
          pos=FrmGetObjectIndex(frmPtr,controlid);
        }  
        else
        {
            pos=-1;  //could not find
        }
//StrPrintF(debug,"aaa pos=%d controlid=%d",pos,controlid);
//dbug(debug);
        break;
      case 'v':  //variable containing name

        find_arg_2();      //variable containing name

        frmPtr=FrmGetActiveForm();    //09302002
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
	    if(pos== (-1)) 
	    {
	        found=false;
	        break;   //grafitti
	   }
	    controlPtr=((ControlType*)FrmGetObjectPtr(frmPtr,pos));
	    controlid=FrmGetObjectId(frmPtr,pos);
	    if(controlid== (-1)) 
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
   propId=find_integer();          //property type identifier #
//StrPrintF(debug,"in get general prop  --  c=%c propid=%d",c,propId);   
//dbug(debug);
   //find_arg_3();          //new property value to assign
   switch(propId)
   {
        
       case 1:  //status
           if(found==false) goto abortNotFound;
           if(controlType  != frmControlObj) commonErrorWrongCtltypeOnGet("status",controlType);
          else
          {
            if(arg4->kind != 's') 
            {
                func_controlgetstatus();
                return;
            }
            else commonErrorWrongTypeOnGet("status");
	      }
	      break; 
       case 2:  //selected
          if(found==false) goto abortNotFound;
          if( (controlType!=frmListObj)&&(controlType!=frmControlObj))commonErrorWrongCtltypeOnGet("selectd",controlType);
          else
          {
            if(arg4->kind != 's') 
            {
                if (controlType==frmListObj) func_listgetselecteditemno();     
                else
                {
                     //must point to list part of popup
                     controlPtr=((ControlType*)FrmGetObjectPtr(frmPtr,pos+1));
	                 controlid=FrmGetObjectId(frmPtr,pos+1);
                     func_listgetselecteditemno();
                }
                return;
            }
            else commonErrorWrongTypeOnGet("selected");
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
       //07062005 NOTE: !!!!do not use case values 4-9 to avoid incompatabilty with old compiler gernerated code
       //07062005 moved cases 4-9 to 94-99 (see below)
       
        case 13:  //type      
          if(pos==(-1))
          {
             restore4(11);  //graffiti
             break;
          }
          if(found==false) goto abortNotFound;
          common_controlsgettype(frmPtr, controlid);
          break;
         case 14:  //index (position)
           if(found==false) 
           {
              restore4(-1);
              break;          //indicate not found
           }
           common_controlsgetposition(frmPtr,controlid);
           break;
         case 15:  //id   //09302002 added this section
           if(found==false) 
           {
              restore4(-1);
              break;          //indicate not found
           }
           commonGetID(frmPtr,controlPtr);   //09302002
           break; 
         //additions start 09242003
         case 48:  //col  
           if(found==false) 
           {
              restore4(-1);
              break;          //indicate not found
           }
           gridGetSelectedCol(frmPtr,controlPtr);    
           break;
         case 49:  //cols  
           if(found==false) 
           {
              restore4(-1);
              break;          //indicate not found
           }
           gridGetCols(frmPtr,controlPtr);    
           break;
         case 50:  //colwidth  
           if(found==false) 
           {
              restore4(-1);
              break;          //indicate not found
           }
           gridGetColWidth(frmPtr,controlPtr);    
           break;
         case 51:  //row  
           if(found==false) 
           {
              restore4(-1);
              break;          //indicate not found
           }
           gridGetSelectedRow(frmPtr,controlPtr);    
           break;
        case 52:  //rows 
           if(found==false) 
           {
              restore4(-1);
              break;          //indicate not found
           }
           gridGetRows(frmPtr,controlPtr);    
           break;    
        case 53:  //col  
           if(found==false) 
           {
              restore4(-1);
              break;          //indicate not found
           }
           gridGetVisibleRows(frmPtr,controlPtr);    
           break;
         case 55:  //cell value  
           if(found==false) 
           {
              restore4(-1);
              break;          //indicate not found
           }
           gridGetValueMatrix(frmPtr,controlPtr);    
           break;
         case 56:  //value              //modified comment 07122005 
           if(found==false) 
           {
              restore4(-1);
              break;          //indicate not found
           }
           //start additions 07122005 
           if  (controlType==frmControlObj)                              
           {                                                             
             type = CtlGlueGetControlStyle((ControlType*)(controlPtr));  
             if((type==sliderCtl) || (type==feedbackSliderCtl) )        
             {
               //it's a slider ctl
               
                  CtlGetSliderValues ((ControlType*)(controlPtr),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue); 
                  
                    if(arg4->kind != 's') 
		            {
		                restore4(curValue);           
		                return;
					}
			        else commonErrorWrongTypeOnGet("Value");    
			  }                                                        
			   
           }
           else
           {
                  if(controlType  == frmScrollBarObj) 
		          {
		            if(arg4->kind != 's') 
		            {
		                func_scrollbargetcurrent();
		                return;
					}
					else commonErrorWrongTypeOnGet("Value");
				  }
				  else
				  {
				  //end additions 07122005
           
           gridGetSelectedValue(frmPtr,controlPtr);    
                  }                                          //added 07122005                
           }                                                 //added 07122005
           break;
         case 57:  //get row data  
           if(found==false) 
           {
              restore4(-1);
              break;          //indicate not found
           }
           gridGetRowData(frmPtr,controlPtr);    
           break;                      
         //start additions 02062004
          case 58:  //toprow  
           if(found==false) 
           {
              restore4(-1);
              break;          //indicate not found
           }
           gridGetTopRow(frmPtr,controlPtr);    
           break;
         //end additins 02062004
         //start additions 04012005
         
         case 59:  //fontMatrix
           if(found==false) 
           {
              restore4(-1);
              break;          //indicate not found
           }
           gridGetFontMatrix(frmPtr,controlPtr);    
           break;
         case 80:  //left
//StrPrintF(debug, "at left pos=%d",pos);
//dbug(debug);
              FrmGetObjectBounds (frmPtr,pos,&bounds);
//dbug("got bounds");
              restore4(bounds.topLeft.x);
              break;
            
        case 81:  //top
             FrmGetObjectBounds (frmPtr,pos,&bounds);
             restore4(bounds.topLeft.y);
             break; 
        	 
        case 82:   //width
             FrmGetObjectBounds (frmPtr,pos,&bounds);
             restore4(bounds.extent.x);
             break;
        case 83:  //height
             FrmGetObjectBounds (frmPtr,pos,&bounds);
             restore4(bounds.extent.y);
             break;
         //end of additions 04012005                        
         //additions end 09242003
         
         //07062005 code relocated from above and renumbered the case values (94-99)
         case 94:  //current   //modified 04012005
          if(found==false) goto abortNotFound;
 //SysFatalAlert("at get current");    
           //modified 04012005
     
           //07122005 type = CtlGlueGetControlStyle((ControlType*)(controlPtr)); 
           //07122005 if  ((controlType==frmControlObj)&&((type==sliderCtl) || (type==feedbackSliderCtl) ))   //added 09242003
           //07122005 {
           //07122005     //it's a slider ctl
           //07122005     
           //07122005        CtlGetSliderValues ((ControlType*)(controlPtr),
           //07122005                                 &minValue, &maxValue,
           //07122005                                 &pageSize, &curValue); 
           //07122005        
           //07122005          if(arg4->kind != 's') 
		   //07122005          {
		   //07122005              restore4(curValue);           
		   //07122005              return;
           //07122005 					}
		   //07122005 	        else commonErrorWrongTypeOnGet("curValue");     
		   //07122005 	   
           //07122005 }
           //07122005 else
           //07122005 {
          	 
          		  if(controlType  != frmScrollBarObj) commonErrorWrongCtltypeOnGet("current",controlType);
		          else
		          {
		            if(arg4->kind != 's') 
		            {
		                func_scrollbargetcurrent();
		                return;
					}
					else commonErrorWrongTypeOnGet("current");
		          }
          //07122005 }
          break; 
        case 95:  //min   //modified 04012005
          //modified 04012005
          if(found==false) goto abortNotFound;
           type = CtlGlueGetControlStyle((ControlType*)(controlPtr)); 
           if  ((controlType==frmControlObj)&&((type==sliderCtl) || (type==feedbackSliderCtl) ))   //added 09242003
           {
               //it's a slider ctl
               
                  CtlGetSliderValues ((ControlType*)(controlPtr),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue); 
                  
                    if(arg4->kind != 's') 
		            {
		                restore4(minValue);
		                return;
					}
			        else commonErrorWrongTypeOnGet("minValue");
			   
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
           type = CtlGlueGetControlStyle((ControlType*)(controlPtr)); 
           if  ((controlType==frmControlObj)&&((type==sliderCtl) || (type==feedbackSliderCtl) ))   //added 09242003
           {
               //it's a slider ctl
               
                  CtlGetSliderValues ((ControlType*)(controlPtr),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue); 
                  
                    if(arg4->kind != 's') 
		            {
		                restore4(maxValue);
		                return;
					}
			        else commonErrorWrongTypeOnGet("maxValue");
			   
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
           type = CtlGlueGetControlStyle((ControlType*)(controlPtr)); 
           if  ((controlType==frmControlObj)&&((type==sliderCtl) || (type==feedbackSliderCtl) ))   //added 09242003
           {
               //it's a slider ctl
               
                  CtlGetSliderValues ((ControlType*)(controlPtr),
                                           &minValue, &maxValue,
                                           &pageSize, &curValue); 
                  
                    if(arg4->kind != 's') 
		            {
		                restore4(pageSize);
		                return;
					}
			        else commonErrorWrongTypeOnGet("pageSize");
			   
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
       
       case 9:     //added 07062005   !!!!must allow 9 or 99 for compatability with old programs
       case 99:  //noItems   
          if(found==false) goto abortNotFound;
          if( (controlType!=frmListObj)&&(controlType!=frmControlObj)) commonErrorWrongCtltypeOnGet("noItems",controlType);
          else
          {
            if(arg4->kind != 's') 
			{
			    if (controlType==frmListObj) func_listgetnoitems();    
                else
                {
                     //must point to list part of popup
                     controlPtr=((ControlType*)FrmGetObjectPtr(frmPtr,pos+1));
	                 controlid=FrmGetObjectId(frmPtr,pos+1);
                     func_listgetnoitems();
                }
                return;
                
			    
			}        
            else commonErrorWrongTypeOnGet("noItems");
          }
             break;
            
       }
       return;
abortNotFound:
   SysFatalAlert("Cannot find the control referenced.  May be caused by using bitmap.index which does not work.");            
   ErrThrow(-1);                 //inserted 05212003	   
    //restore4(res);
}
//*****************************************************************************************
void verb_func_getGeneralPropertyString()
{
  //no auto arguments (really a verb)
  int i;
  int controlType;
  int pos;
  char c;
  int propId;
  FormPtr frmPtr;        //added 5.20.2000 
//dbug("in set text");   
   find_arg_4();
   c=find_char();   //type of control identifier
   switch(c)
   {
      case 'i':  //ctlid
        find_ctlid(true);
        frmPtr=findFormTheControlIsOn(controlid);
        pos=FrmGetObjectIndex(frmPtr,controlid);
        break;
      case 'v':  //variable containing name
        find_arg_2();      //variable containing name
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
   controlType=FrmGetObjectType(frmPtr,pos);
   propId=find_integer();          //property type identifier #
   //find_arg_3();          //new property value to assign
//StrPrintF(debug,"getText  c=%c id=%d pos=%d propid=%d",c,controlid,pos,propId);
//dbug(debug);
   switch(propId)
   {
        
       case 0:  //text
          if(pos==0)  //return form title
          {
                if(FrmGetTitle(frmPtr) != 0) //04272004 if there is a title on form
                {
              commonGetTitle(frmPtr);
              break;
                }
          }
          switch(controlType)
          {
              case frmLabelObj:
//dbug("yes--got a label");
                commonGetLabel(frmPtr,controlid);
                break;
              case frmControlObj:
//dbug("got controlgettext");
                if(CtlGlueGetControlStyle(controlPtr)==popupTriggerCtl)
                {
//dbug("going to popupgettext 2");
                    func_popupgettext();
                }
                else func_controlgettext();
                break;
              case frmFieldObj:
                func_fieldgettext();
                break;
              case frmPopupObj:
//dbug("going to popupgettext");
                func_popupgettext();
                break;
              case frmTableObj:           //added 09242003  
                 gridGetSelectedText(frmPtr,controlPtr); //added 09242003 
                 break;                   //added 09242003 
              default:
                 commonErrorWrongCtltypeOnGet("text",controlType); 
          }
          break; 
       case 11:  //itemtext
          if( (controlType!=frmListObj)&&(controlType!=frmControlObj))commonErrorWrongCtltypeOnGet("itemText",controlType);
          else
          {
            find_arg_1();
                if (controlType==frmListObj) commonGetItemText(integ_value( arg1, (double *)arg1_val )-1);    
                else
                {

                     //must point to list part of popup
                     controlPtr=((ControlType*)FrmGetObjectPtr(frmPtr,pos+1));
	                 controlid=FrmGetObjectId(frmPtr,pos+1);
                     commonGetItemText(integ_value( arg1, (double *)arg1_val )-1);
                }
          }
          break; 
       case 12:  //endcapture
          if (controlType!=frmGadgetObj)commonErrorWrongCtltypeOnGet("itemText",controlType);
          else
          {
            //find_arg_4();
            commonEndCapture(frmPtr,  controlid);
            
          }
          break;
       //additions 09242003
       case 54:  //cellMatrix
          if (controlType!=frmTableObj)commonErrorWrongCtltypeOnGet("cellMatrix",controlPtr);
          else
          {
            //find_arg_4();
            gridGetCellMatrix(frmPtr,  controlPtr);
            
          }
          break;             
       //end of additions 09242003                
    }     
	   
    
}
