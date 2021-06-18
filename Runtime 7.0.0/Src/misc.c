 
#include <PalmOS.h>
#include <PalmTypes.h>
#include <PalmCompatibility.h>
#include <FatalAlert.h>
#include <FloatMgr.h>
#include <SoundMgr.h>
#include "copy.h"

#include <mathlib.h>
#include <PalmOSGlue.h>  //GHGlue
#include <field.h>       //GHGlue
#include <FeatureMgr.h>
#include <SystemMgr.h>
#include <ErrorBase.h>                   //05212003

void dbugx(double* val, char*identifier);
void updti( struct dataelem* ptr, unsigned int* dest, int* src );
extern void misc_errmsg( char * the_msg);
void dbug(char*msg);
void misc_format_number(struct dataelem* v, double* n , char * s);

struct dataelem *elem_tbl_ptr(unsigned int);
extern void misc_stostr(struct dataelem * *d,
      unsigned int sub1,unsigned int sub2,unsigned int sub3, char *result);
extern void misc_format_date(struct dataelem* v, double* n , char * s);
extern void misc_format_time(struct dataelem* v, double* n , char * s);

extern int codeexec(Word objId,unsigned long offset);
extern void cvt_date_to_ymd(double d,int *yr, int *mo, int* da);
extern void cvt_time_to_hms(double t,int *h, int *m, int* s); 
extern void misc_text_abort( char * msg );

extern void * misc_find_virtual_addr(struct dataelem *d,unsigned int sub1,unsigned int sub2,unsigned int sub3, char type);
extern int char_typed_ahead;
extern double mypow10(int i);    //modified 12182002
extern double cvt_date_to_dbl(int yr,int mo,int da);
extern double cvt_time_to_dbl(int hr, int min, int sec);
extern long unsigned timestamp;
    
extern void misc_getint(struct dataelem *d,  unsigned int sub1,unsigned int sub2,unsigned int sub3,  unsigned int  *result);
extern void store_reg(double* r1, struct dataelem* de,double* elem_ad,
      unsigned int elem_occ1,unsigned int elem_occ2,unsigned int elem_occ3) ;
extern void round_reg(double* reg, struct dataelem* de);      

extern void move_it(char *to_ad, unsigned to_len,char* from_ad,unsigned from_len); /*--gen move rtn---*/
extern void misc_stostr1(char *s);
extern void misc_stostr2(char *s);
extern void misc_stostr3(char *s);
extern void misc_stostr4(char *s);
extern void misc_stostr5(char *s);
void misc_fix(int i, char *res, int num);
void MiscReleaseMemPtr(struct memBlock *p);

void misc_fmtno(char *fmt,char *wk,int bef,int aft,int decpt,char*res);
void misc_stodbl1(double* x);
void misc_stodbl2(double* x);
void misc_stodbl3(double* x);
void misc_stodbl5(double* x);
void DoubleToStr (double val, CharPtr str);

extern int debug_on;
extern int integ_value( struct dataelem *  arg, double *    arg_ad);        /*---calc integ value of data elem__*/
extern void misc_stodbl(struct dataelem *d,  unsigned int sub1,unsigned int sub2,unsigned int sub3, double  *result);

extern UInt16 miscFrmGetObjectIdFromPtr(const FormType *formP, void *objP);  //GH  01.10.2002

extern struct timearray {
   unsigned char min;
   unsigned char hour;
   unsigned char hund;
   unsigned char sec;
} sample_time;

int    mem_debug_sw = 0;
//*****************************************************************************************
void OutOfMemory(int i)
{
    StrPrintF(debug,"Cannot continue--Out of memory(loc=%d)",i);
    SysFatalAlert(debug);
//SysFatalAlert( "before throw");
   ErrThrow(-1);              //inserted 05212003
//SysFatalAlert("should not get to this msg");    
}

//*****************************************************************************************
void updti( struct dataelem* ptr, unsigned int* dest, int* src )
{
   ULong offset=(ULong)dest-(ULong)ptr;
   DmWrite(ptr,offset,src,2);
}
//*****************************************************************************************
void updtc( struct dataelem* ptr, char* dest, char*  src )
{
   ULong offset=(ULong)dest-(ULong)ptr;
   DmWrite(ptr,offset,src,1);
}
                                                                     
//*****************************************************************************************
extern void updtd( struct dataelem* ptr, double* dest, double*src )
{
   ULong offset=(ULong)dest-(ULong)ptr;
   DmWrite(ptr,offset,src,8);
}

//*****************************************************************************************
void MiscFatalAlert(char *msg)
{
   SysFatalAlert( msg );
   ErrThrow(-1);
}
//*****************************************************************************************
void misc_stringfix(int i, char *res, int num) //used for %2.2x format
{
   char orig[80];
   char wk[80];
   char wk2[80];
   StrPrintF(wk,"%d",i);
   if (StrLen(wk) > num)
   {
     StrCopy(wk,"");
     while (StrLen(wk)<num) StrCat(wk,"*");
   }
  else
  {
     while (StrLen(wk) < num)
     {
        StrCopy(wk2,wk);
        StrCopy(wk,"0");
        StrCat(wk,wk2);
     }
   }
   StrCopy(res,wk);
}
//*****************************************************************************************
double misc_int(double x)
{
    long i;
    double r;
    
    i=x;     //03092002
    r=i;
    return(r);
}
//*****************************************************************************************
double misc_floor(double x)
{
    long i;
    double r;
    int test;
    char wk[20];
    i=x;
    
    if(x>=0) ;
    else
    {
       if(i!=x) i=i-1;
    }   
    r=i;
    return(r);
}
//*****************************************************************************************
double misc_ceil(double x)
{
    long i;
    int test;
    double r;
    char wk[20];
    i=x;
    
    if (x<0) ;          //10.10.2000
    else  
    {
        if (i != x)  i=i+1;
    }
    r=i;


    return(r);
}
//*****************************************************************************************
double misc_fabs(double x)
{
   double res;
//SysFatalAlert("at misc_fabs");
    if (x<0.00)  res=0.00-x;
    else         res=x;       

    return(res);
}
//*****************************************************************************************
double StrToDouble(char *theString)
{
       unsigned long romversion;
       int err;
       char right [50];
       char left  [50];
       char s[100];
       int cnt;
       Boolean sign;
       Boolean decptYet;
       Boolean signifDigitYet;    //added 05192003
       int sub;
       double rightValue;
       double leftValue;
       int leftExpon=0;
       int i;
       
       union 
       {
            FlpDouble q;
            double d;
       } x;
     
       //12182002  added several stmts to  elim expon e-xx or exx on end
       char v[10]; 
       int expon=0;
//StrPrintF(debug,"inStrToDouble  s=%s",theString);
//dbug(debug);        
        StrCopy(left,theString);
            
        if(StrLen(left)>4)
		{
		  if (( *(left+StrLen(left)-4)=='e' ) || ( *(left+StrLen(left)-4)=='E' ))
		  {

		    StrCopy(v,left+StrLen(left)-3);
		    expon=StrAToI(v);
		    
		    
		    //StrCat(sr,zeroes+31-(i-1));
		    //*(sr+2+i-1)=*s;  //get dgt preceeding dec pt
		    *(left+StrLen(left)-4)=0x00;
		    
		  }    
		//StrPrintF(debug,"elim expon  %s to %s by %d zeroes",s,sr,i);
		//SysFatalAlert(debug);
		   
		}
		if(StrLen(left)>3)
		{

		  if (( *(left+StrLen(left)-3)=='e' ) || ( *(left+StrLen(left)-3)=='E' ))
		  {
		    StrCopy(v,left+StrLen(left)-2);
		    expon=StrAToI(v);
		    
		    
		    //StrCat(sr,zeroes+31-(i-1));
		    //*(sr+2+i-1)=*s;  //get dgt preceeding dec pt
		    *(left+StrLen(left)-3)=0x00;
		    
		  }   
		}
       
       //12182002 end of adds
//StrPrintF(debug,"***expon=%d  left=%s",expon,left);
//dbug(debug);       
       err=FtrGet(sysFtrCreator,sysFtrNumROMVersion,&romversion);
       //10272002if( romversion < 0x04000000 )
       //10272002{
           //on roms  before vers 4.0 must do own stringToDouble conversion
           //comment out 12182002  StrCopy(left,theString);
           if( (left[0]=='-' )||(left[0]=='+')) sub = 1;
           else               sub = 0;
           
           while( left[sub] ==' ') StrCopy(&left[sub],&left[sub+1]);
           if(left[0]=='+') StrCopy(&left[0],&left[1]);            //09092002
           StrCopy(right,left );
           cnt=0;                 
           sign=false;
           decptYet=false;
           signifDigitYet=false;         //added 05192003
           sub=0;
           while(1)
           {
              switch( left[sub] )
              {
                case 0x00:
                  goto allDone;
                
                case '.':
                  if (decptYet==true) 
                  {
                     //StrPrintF(debug,"Numeric string has two decimal point characters");
                     //SysFatalAlert(debug);
                     break;
                  }
                  decptYet=true;
                  break;
                case '-':
                  if(sub!=0)
                  {
signNotFirst:
                      //StrPrintF(debug,"Numeric string's sign character is not the first character.");
                      //SysFatalAlert(debug);
                      break;
                  }
                  if (sign==true) 
                  {
dupSign:       
                     //StrPrintF(debug,"Numeric string has two sign characters");
                     //SysFatalAlert(debug);
                     break;
                  }
                  sign=true;
                  break;
                case '+':
                  if(sub!=0) goto signNotFirst;
                  if (sign==true) goto dupSign;
                  sign=true;
                  break;  
                default:
                  if( (left[sub]<'0') || (left[sub]>'9'))
                  {
                     //StrPrintF(debug,"Numeric string has invalid characters");
                     //SysFatalAlert(debug);
                     break;
                  }
                  
                  if(left[sub]!='0') signifDigitYet=true;     //added 05192003
                  if(signifDigitYet==true) cnt+=1;            //modified 05192003
                  if(cnt<=8)
                  {
                      if(decptYet==false) right[sub] =' ';  //using left so blank out right
                      else                right[sub] ='0';  
                  }
                  else
                  {
                      //04242003 if(decptYet==false) left[sub] ='0';  //using right so blank out left
                      if(decptYet==false)
                      {
                         left[sub]=' ';  //added 04242003
                         leftExpon+=1;   //added 04242003
                      }
                      else                left[sub] =' ';  
                  } 
                  
              }
              ++sub;
                  
                          
                     
           }
allDone:
        
      goto rightOK;  
      /*     //remove trailing zeroes from left
           cnt=0;
           sub=StrLen(left);
           while(sub >1)
           {
               --sub;
               if( left[sub] != '0' ) break;
               
               ++cnt;
               left[sub]=0x00;
                 
           }
           if( cnt != 0 )
           {
               StrCat(left,"e+");
               StrPrintF(debug,"%d",cnt);
               StrCat(left,debug);
StrPrintF(debug,"revised left=%s",left);
SysFatalAlert(debug);               
           }
           
           //remove leading zeroes from right
           cnt=0;
           sub=0;
           while(right[sub]==' ') ++sub;
           
           
           
           if(right[sub]=='.') ++sub;
           
           
           while(1)
           {
              
               if( right[sub] != '0' ) break;
               
               if( right[sub+1]==0x00 ) break;
               ++cnt;
               right[sub]='.';
               right[sub-1]=' ';
               
               ++sub; 
           }
StrPrintF(debug,"new right=%s'  cnt=%d",right,cnt);
SysFatalAlert(debug);
           if( cnt != 0 )
           {
               StrCat(right,"e-");
               StrPrintF(debug,"%d",cnt);
               StrCat(right,debug);
       
           }
    */       
rightOK:           
           x.q=FlpAToF(left);
           //04242003 leftValue=x.d;    
           leftValue=x.d * mypow10(leftExpon);      //added 04242003 


//DoubleToStr(x.d, s);
//StrPrintF(debug,"s=%s  left=%s  leftValue=%s",theString,left,s);
//SysFatalAlert(debug);                     
           
           if ((right[0]=='-' ) || (right[0]=='+')) sub = 1;    //09092002
           else                sub = 0;
            
           while( right[sub] ==' ') StrCopy(&right[sub],&right[sub+1]);
           if(right[0]=='+') StrCopy(&right[0],&right[1]);     //09092002
//StrPrintF(debug,"revised right=%s",right);
//SysFatalAlert(debug);                   
           //statements added beginning here 04242003
           cnt=0;
           signifDigitYet=false;          //added 05192003
           for(i=0;i<StrLen(right);++i)
           {
               switch(right[i])
               {
                   case '-':
                   case '.':
                     break;
                   default:
                     if(right[i] != '0') signifDigitYet=true;  //added 05192003
                     if(signifDigitYet==true)                  //added 05192003
                     {                                         //added 05192003
                         ++cnt;
                         if(cnt>8)
                         {
                            right[i]=' ';  //dont allow over 8 digits
                         }
                     }                     //added 05192003  
               }
           }
           //end of additions 04242003
           x.q=FlpAToF(right);
           rightValue=x.d;
 
//DoubleToStr(x.d, s);
//StrPrintF(debug,"s=%s  right=%s  rightValue=%s",theString,right,s);
//dbug(debug);           
      
           x.d+=leftValue;

       /* 10272002
       }
       else
       {
          //use the system rtn which handles double precision
           StrCopy(left,theString);
           if( (left[0]=='-' )||(left[0]=='+')) sub = 1;
           else               sub = 0;
           
           while( left[sub] ==' ') StrCopy(&left[sub],&left[sub+1]);
           x.q=FlpAToF(left);   //03092002
      }
      */    //10272002
//DoubleToStr (x.d, s);
//StrPrintF(debug,"s=%s  full=%s",theString,s);
//SysFatalAlert(debug);       
                  
       //12182002 return x.d;

       leftValue=x.d;                     //added 12182002
           
     
//StrPrintF(debug,"bb   expon=%d ",expon);
//dbug(debug);
       leftValue*= mypow10(expon);       //added 12182002
       return (leftValue );               //added 12182002

//FlpFToA(x.q, s);
//StrPrintF(debug,"s=%s  result=%s",theString,s);
//SysFatalAlert(debug);

//dbugx(&(x.d),"in StrToDouble");
        
}



//*****************************************************************************************
void DoubleToStr(double val, CharPtr ans)
{
   double originalD;   //09012005
   char temp[5];       //09012005
   char *adr;
   char v[3];
   char *p;
   char *pos;
   double d;
   int i;
   char sign;
   long left;
   double right;
   //char save[50];
   char sl[50];
   char sr[50];
   char s[100];
   int cnt;
   char zeroes[32]="0000000000000000000000000000000";
   union 
      {
           FlpDouble q;
           double d;
      } x;
       
       
    FlpCompDouble flp;

//x.d=val;
//FlpFToA(x.q, s);
//StrPrintF(debug,"ssssss=%s",s);
//SysFatalAlert(debug);

   if (val<0) { sign='-'; d=0.0-val; }
   else       { sign='+'; d=val;     }
   originalD = d;          //09012005
   
   cnt=0;
   if (d==0) goto itsZero;
   if(d>.97e+09 )
   {
       while( d>.97e+09)
       {
           ++cnt;  d/=10.0 ; originalD /=10;
       } 
   }
   else
   {
       while( d<.97e+08 )
       {
           --cnt;  d*=10.0; originalD *=10;
       }
       
   }

  left=d+.000002;
  
  StrIToA(sl, left);
//StrPrintF(debug,"@@@cnt=%d   left=%lu",cnt,left);
//SysFatalAlert(debug);
  
  //09012005 right=(d-left);
  right=(originalD-left);    //09012005
  
  if(right<0) right=1.0e-22;  //added 4.25.2000
  else
  {
    if(StrLen(sl)==9) right+=0.00000005;
    else                right+=0.000000005;
  
    if(StrLen(sl)==9)                     //2012001
    {
        if(right<1.0e-06)  right=1.0e-22;
    }
    else
    {
        if(right<1.0e-07) right=1.0e-22;
    }
  } 
  
  
  
  
  flp.d=right;
  FlpFToA( flp.fd, sr);
//StrPrintF(debug,"sl=%s sr=%s cnt=%d",sl,sr,cnt);
//SysFatalAlert(debug);


//now eliminate e-xx exponent on end

//StrPrintF(debug,"left=%s right=%s  lenl=%d lenr=%d",sl,sr,StrLen(sl),StrLen(sr));
//SysFatalAlert(debug);

//StrCopy(save,sr);
if(StrLen(sr)>4)
{
  if (( *(sr+StrLen(sr)-4)=='e' )  || ( *(sr+StrLen(sr)-4)=='E' ))  //modified 12182002
 {
    //12182002 v[0]=*(sr+StrLen(sr)-2);
    //12182002 v[1]=*(sr+StrLen(sr)-1);
    //12182002 v[2]=0x00;
    StrCopy(v,sr+StrLen(sr)-3);   //12182002 added
    i=StrAToI(v);
    *(sr+StrLen(sr)-4)=0x00;        //12182002 //elim e-xx

    goto elimExponent;
    
 }    

}
if(StrLen(sr)>3)
{
  if( (*(sr+StrLen(sr)-3)=='e') || (*(sr+StrLen(sr)-3)=='E') )  //modified 12182002  //e00 no expon power
  {
    StrCopy(v,sr+StrLen(sr)-2);   //12182002 added
    i=StrAToI(v);                 //12182002 added
    *(sr+StrLen(sr)-2)=0x00;      //12182002 added
    
elimExponent:

//StrPrintF(debug,"at elim expon  =%d sr=%s",i,sr);
//dbug(debug);
    if( (i<31) && (i>0))    //12182002 added
    {                       //12182002 added 
           
           if(i>(StrLen(sr)-2))       //12182002 added 
                 StrCat(sr,zeroes+31-(i-(StrLen(sr)-2)));    //12182002 added 
           StrCopy(s,sr);   //12182002 added 
	       *(sr)=*s;        //12182002 added   //get dgt preceeding dec pt	
	       *(sr+1)=0x00;    //12182002 added
	       StrCat(sr,s+2);  //12182002
	       
	         
    }                       //12182002 added
    else                    //12182002 added
    {                       //12182002 added
	   if( (i>(-31)) && (i<0))    //12182002 added
       {                       //12182002 added 
           StrCopy(s,sr);
	       StrCopy(sr,"0.");
	   
	       StrCat(sr,zeroes+31+i);   //12182002 modified
	       *(sr+2-i-1)=*s;              //12182002 modified  //get dgt preceeding dec pt
	       *(sr+2-i)=0x00;              //12182002 modified
	       
	       StrCat(sr,s+2);
	   }                   //12182002 added       
   }                       //12182002 added 
   
  }
}

//StrPrintF(debug,"elim expon  %s to %s by expon =%d zeroes   left=%s",save,sr,i,sl);
//SysFatalAlert(debug);
   



//StrPrintF(debug,"left=%s (len)=%d right=%s (len)=%d  cnt=%d",
//sl,StrLen(sl),sr,StrLen(sr),cnt);
//SysFatalAlert(debug);

if (cnt>0)
{
    if( sign=='-') { *s='-';*(s+1)=0x00; }
    else *s=0x00;
   
     
    //changes in this area 09012005
    if(cnt < 8)
    {
    StrCat(s,sl);
         s[StrLen(s)+cnt]=0x00;
         MemMove(s+StrLen(s),sr+2,cnt);
         
         if(cnt<(StrLen(sr)-2))
         {
             StrCat(s,".");     
             StrCat(s,sr+2+cnt);
         }
         cnt=0;
    }
    else
    {
        s[0]=sl[0];
        s[1]='.';
        s[2]=0x00;
        StrCat(s,&sl[1]);
    StrCat(s,sr+2);
        cnt += StrLen(sl)-1;
        

    }
   
    
    //09012005
    //if(sign=='-')
    //{
    //    if( (StrLen(sl)+cnt+1)<StrLen(s)) *(s+StrLen(sl)+cnt+1)=0x00;   
    //}
    //else 
    //{
    //     if( (StrLen(sl)+cnt)<StrLen(s)+1)     *(s+StrLen(sl)+cnt+1)=0x00;    //4.14.2000 add
   
    //}
    //end changes 09012005
    
     //09012005 StrCat(s,".");
    //09012005 StrCat(s,sr+cnt+2);
//03232006 StrPrintF(debug,"cnt=%d   s=%s",cnt,s);
//03232006 SysFatalAlert(debug);    
   
   
    
    
}
else
{
    cnt=0-cnt;
    if( sign=='-') { *s='-';*(s+1)=0x00; }
    else *s=0x00;
    i=StrLen(s);
    
    if(cnt<StrLen(sl))                            //4.14.2000 added  
    {                                             //4.14.2000 added  
        StrNCat(s,sl,StrLen(sl)-cnt+1+i);         //4.14.2000 added   
        *(s+StrLen(sl)-cnt+i)=0x00;               //4.14.2000 added
    }                                             //4.14.2000 added
    
     
    StrCat(s,".");
    
                         
    while( cnt>StrLen(sl))                       //4.14.2000 added
    {                                            //4.14.2000 added
       StrCat(s,"0");                            //4.14.2000 added
       --cnt;                                    //4.14.2000 added
    }                                            //4.14.2000 added
    
    StrCat(s,sl+(StrLen(sl)-cnt));
    
    
    StrCat(s,sr+2);
       
//StrPrintF(debug,"cnt=%d   s=%s",cnt,s);
//SysFatalAlert(debug);       
    cnt=0;    
    
}
pos=StrChr(s,'.');

//StrPrintF(debug,"before=%d s=%s",(int)(pos-s),s);
//SysFatalAlert(debug);


if((pos>=s)&&((pos-s)<=StrLen(s)))
{
  if (sign=='-')
  {
     if( *(pos+17-(pos-s)) >='5')
     {
         //round last digit
         adr=pos+16-(pos-s);
         
            while(1)
            {
            
              if ( ((*adr)>='0') && ( (*adr)<='9'))
              {
                         
                //round the prev pos
                if( *adr=='9')
                {
                   *adr='0';
                }
                else
                {
                   *adr=*adr+1;
                   break;    //and quit
                }
              }  
              if (adr==s) break;
              --adr;            
            
            }
     }
     *(pos+17-(pos-s))=0x00;  //limit 15 dgts accuracy
  }
  else
  {
     if( *(pos+16-(pos-s)) >='5')
     {
         //round last digit
         adr=pos+15-(pos-s);
         
            while(1)
            {
            
              if ( ((*adr)>='0') && ( (*adr)<='9'))
              {
                         
                //round the prev pos
                if( *adr=='9')
                {
                   *adr='0';
                }
                else
                {
                   *adr=*adr+1;
                   break;    //and quit
                }
              }  
              if (adr==s) break;
              --adr;            
            
            }
     }
     *(pos+16-(pos-s))=0x00;
  }           
}


for(i=StrLen(pos)-1;i>=0;--i)  //remove trailing zeroes after decimal pt 
{
   if (pos[i]!='0') break;
   pos[i]=0x00;
}
if(cnt>0)
{
	StrCat(s,"E");
    StrPrintF(temp,"%d",cnt);
    if(StrLen(temp)==1) StrCat(s,"0");
    StrCat(s,temp);
}

//StrPrintF(debug,"ans=%s",s);
//SysFatalAlert(debug);

   StrCopy(ans,s);
return;

itsZero:
   StrCopy(ans,"0");
    
}



//*****************************************************************************************
void restore_integ_value(int i,struct dataelem * arg,double * arg_ad,
     unsigned int arg_occ1,unsigned int arg_occ2,unsigned int arg_occ3)        /*---restore integ value--*/
{
   double reg;
   reg=i;
   store_reg(&reg, arg, arg_ad, arg_occ1,arg_occ2,arg_occ3);
    return;
}

//*****************************************************************************************
//11/04
//extern void restore_long_integ_value(i,arg, arg_ad, arg_occ1,arg_occ2,arg_occ3)        /*---restore integ value--*/
//       unsigned long i;
//    struct dataelem *arg;
//     double * arg_ad;
//     unsigned int arg_occ1;
//      unsigned int arg_occ2;
//      unsigned int arg_occ3;
//{
//   double reg;
//   reg=i;
//   store_reg(&reg, arg, arg_ad, arg_occ1,arg_occ2,arg_occ3);
//    return;
//}




//*****************************************************************************************
void free(void *p)
{
  MemPtrUnlock(p);
}
//*****************************************************************************************
//void abort()  01/21/03 GH: In CW 9m, this is in PalmOS_AboutExit.cpp
//{

//  SysReset();  /*aborts*/
//}

//*****************************************************************************************
extern void misc_text_abort( char * msg )
{
  char temp[256];
  char errmsg[256];
     
     StrCopy(errmsg,"ABORT MESSAGE=");
     StrCat(errmsg,msg);
     SysFatalAlert(errmsg);
     //05212003 abort();
     ErrThrow(-1);                 //inserted 05212003
}

    

/*-------------------------------------------------*/
extern int misc_chk_for_key()    /*just sees if a key ready*/
{
     //??used
     return 0;
}

//*****************************************************************************************
extern void misc_beep()
{
    SndPlaySystemSound(sndError);  //error sound
    return;
}

//*****************************************************************************************
extern void misc_format_number(struct dataelem* v, double* n , char * s)
{
char debug[160];
    struct dataelem *elem_tbl_ptr( unsigned int);
    struct dataelem *tempde;
    char wk[45];
    char wk2[3];
    char wk3[45];
    int sign;
    int i, j, k,l;
    int jsave;
    int yr,mo,da,hr,min,sec;
    int decpt;
   
    char fmt[128];
    
    int bef;
    int aft;
    int fmtdecpt;
    int fmtaft;
    int fmtbef;
    
    if(v->kind=='d')
    {
        misc_format_date( v, n , s);
        return;
    }
    if(v->kind=='t')
    {
        misc_format_time( v, n , s);
        return;

    }
//dbug("before doubleToString");
//printDouble(*n,wk3);
    DoubleToStr(*n,wk);
//dbug("after doubletostring");
//StrPrintF(debug,"wkold=%s   wknew=%s",wk,wk3);
//dbug(debug);
//dbugx(n,"miscFormatNo");
//StrPrintF(debug,"inMisc_format_number  wk=%s",wk);
//SysFatalAlert(debug);

    if ( *n<0)
    {
        sign=-1;
     }
    else       sign=0;
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
    fmtbef=bef;
    fmtaft=aft; 
    if (v->dgt_bef!=0) fmtbef=v->dgt_bef;
    if (v->dgt_aft!=0) fmtaft=v->dgt_aft;
    StrCopy(fmt,"-");
    
    for(i=0;i<fmtbef;++i)  
    {
       StrCat(fmt,"n");
    }
    if (fmtaft!=0) StrCat(fmt,".");
    for(i=0;i<fmtaft;++i)  
    {
       StrCat(fmt,"0");
    }
//dbug("before fmtno");

//StrPrintF(debug,"fmt  fmt=%s wk=%s bef=%d aft=%d decpt=%d",fmt,wk,bef,aft,decpt);
//dbug(debug);
    misc_fmtno(fmt,wk,bef,aft,decpt,s);
//dbug("after fmtno");    
//StrPrintF(debug,"endofMisc_format_number  wk=%s",s);
//SysFatalAlert(debug);

    return;
}
//*****************************************************************************************
void misc_fmtno(char *fmt,char *wk,int bef,int aft,int decpt, char *result)
{
    char txt[128];
    int i;
    int fmtdecpt;
    int fmtbef;
    int fmtaft;
    int f;
    int w;
    int t;
    char sign;
    int suppress=0;
    
    
//StrPrintF(debug,"fmt=%s wk=%s bef=%d aft=%d decpt=%d",fmt,wk,bef,aft,decpt);
//SysFatalAlert(debug);
    fmtdecpt=-1;
    fmtbef=0;
    fmtaft=0;
    for(i=0;i<StrLen(fmt);++i)
    {
      if ((fmt[i]=='-')||(fmt[i]=='+')||(fmt[i]==',')||(fmt[i]=='+')) ;
      else
      {
           if ((fmt[i]=='#')||(fmt[i]=='n')) suppress=1;
           if (fmt[i]=='.') {fmtdecpt=i;continue;}
           if ((fmt[i]=='0') ||(fmt[i]=='n')||(fmt[i]=='#'))
           {  
             if(fmtdecpt==-1) fmtbef+=1;
             else          fmtaft+=1;
           }   
      }
    }
//StrPrintF(debug,"fmt decpt=%d bef=%d aft=%d",fmtdecpt,fmtbef,fmtaft);
//SysFatalAlert(debug);
    StrCopy(txt,"");
    if(fmtbef<bef) goto tooBig;
//SysFatalAlert("1");   
    //put in dgts left of dec
    f=0;
    w=0;
    t=0;
    sign=' ';
    if ( wk[0]=='+')
    {
       sign='+';
       w+=1;
    }   
    else
    {
       if (wk[0]=='-') 
       {
         sign='-';
         w+=1;
       }
    }
    
    //leading dgts 0, so put 0 or blank
    while(fmtbef>bef)
    {
      
      switch(fmt[f])
      {
        case '-':
          if(sign=='-') txt[t++]=sign;
          break;
        case '+':
          txt[t++]=sign;
          break;
        case ',':
          
          break;
        case '0':
          --fmtbef;
          txt[t++]='0';
          suppress=0;
          break;
        case 'n':
          --fmtbef;
          txt[t++]=' ';
          break;  
        case '#':
          --fmtbef;
          break;
        case 0x00:
          goto tooBig;  //more likely an error
       
        case '.' :
          break; //should not occur
        default:
          txt[t++]=fmt[f];
          break;
      }
      ++f;                     
    }
//SysFatalAlert("2");
    if((fmt[f]==',')&&(suppress==1))  //ignore a leading comma
    {
        if( (f>0)&&(fmt[f-1]=='n')) txt[t++]=' ';
        ++f;
    }
  
    //put in dgts to left of decpt
    while(1)
    {
      if ((fmt[f]=='.')||(fmt[f]==0x00)) break;
      switch(fmt[f])
      {
        case '-':
          if(sign=='-') txt[t++]=sign;
          break;
        case '+':
          txt[t++]=sign;
          break;
        case ',':
          txt[t++]=',';
          break;
        case '0':
          txt[t++]=wk[w++];
          break;
        case 'n':
          txt[t++]=wk[w++];
          break;  
        case '#':
          txt[t++]=wk[w++];
          break;
        default:
          txt[t++]=fmt[f];
          break;
      }
      ++f;                     
    }    
//txt[t]=0x00;
//StrPrintF(debug,"3  txt=*%s* len=%d",txt,StrLen(txt));
//SysFatalAlert(debug);  
     //put in dgts to right of dec
     while(1)
    {
      if (fmt[f]==0x00) break;
      switch(fmt[f])
      {
        case '.':
          txt[t++]='.';
          if(wk[w]=='.') ++w;
          break;       
        case 'n':       //09172004 made 'n' work like '0' after dec pt
        case '0':
          if(wk[w]==0x00) txt[t++]='0';
          else            txt[t++]=wk[w++];
          break;
        //09172004 case 'n':
        //09172004  if(wk[w]==0x00) txt[t++]=' ';
        //09172004  else            txt[t++]=wk[w++];
        //09172004  break;  
        case '#':
          if(wk[w]==0x00) break;  //stop inserts
          txt[t++]=wk[w++];
          break;
        default:
          txt[t++]=fmt[f];
          break;
      }
      ++f;                     
    }
    txt[t]=0x00;
 
//StrPrintF(debug,"4   txt=*%s* len=%d",txt,StrLen(txt));
//SysFatalAlert(debug);  
    StrCopy(result,txt);    
    return;
tooBig:
  f=0;
  w=0;
  while(fmt[w]!=0x00)
  {
    wk[w++]='*';
    
  }    
  wk[w]=0x00;
  StrCopy(result,txt);
  return;
}

//*****************************************************************************************
extern void misc_format_date(struct dataelem* v, double* n , char * s)
{
    char wk2[5];
    int yr,mo,da;

                cvt_date_to_ymd(*n,&yr,&mo,&da);
//StrPrintF(debug,"yr=%d mo=%d da=%d",yr,mo,da);
//SysFatalAlert(debug);
                //if(yr>=2000)yr=yr-2000;
                //else yr = yr-1900;
//SysFatalAlert("fmt date w 2.2 terms");
                
                StrCopy(s,"");
                misc_stringfix(yr,wk2,4);
                StrCat(s,wk2);
                misc_stringfix(mo,wk2,2);
                StrCat(s,"/");
                StrCat(s,wk2);
                misc_stringfix(da,wk2,2);
                StrCat(s,"/");
                StrCat(s,wk2);
//SysFatalAlert(s);

   return;   
}
//*****************************************************************************************
extern void misc_format_time(struct dataelem* v, double* n , char * s)
{
char debug[160];
    char wk2[3];
    int hr,min,sec;
                cvt_time_to_hms(*n,&hr,&min,&sec);
                /**/
// StrPrintF(debug,"in misc_format_time hr=%d min=%d sec=%d",hr,min,sec);
// SysFatalAlert(debug);
                //if(hr==0) hr=12;
                StrCopy(s,"");
                misc_stringfix(hr,wk2,2);
                StrCat(s,wk2);
                misc_stringfix(min,wk2,2);
                StrCat(s,":");
                StrCat(s,wk2);
                misc_stringfix(sec,wk2,2);
                StrCat(s,":");
                StrCat(s,wk2);
       return;
}


//*****************************************************************************************
extern void * misc_find_virtual_addr(struct dataelem *d,unsigned int sub1,unsigned int sub2,unsigned  int sub3, char type)
{
   //06012002 unsigned int wk;
   unsigned int s1=sub1;
   unsigned int s2=sub2;
   unsigned int s3=sub3;

   switch(d->kind)
   {
      case 's':
//StrPrintF(debug,"string virtual for de#=%u s1=%d s2=%d s3=%d ",d->tbl_no,s1,s2,s3);
//SysFatalAlert(debug);
         //06012002 wk= ( (s3)*(d->max_no_values2)*(d->max_no_values1)
         //06012002      +   (s2)*(d->max_no_values1) + (s1))*2; 

         //06012002return((char*)d+*((unsigned int*)((char*)d+DELEN +wk)) );
         return((char*)d+*((unsigned int*)((char*)d+DELEN +( (s3)*(d->max_no_values2)*(d->max_no_values1)
               +   (s2)*(d->max_no_values1) + (s1))*2)) );
      default:
//StrPrintF(debug,"numeric virtual for de#=%u s1=%d s2=%d s3=%d ",d->tbl_no,s1,s2,s3);
//SysFatalAlert(debug);
        //06012002wk=  ( (s3)*(d->max_no_values2)*(d->max_no_values1)
        //06012002     + (s2)*(d->max_no_values1) + (s1))*8; 


        //06012002 return(  (char*)d  +DELEN +wk);
        return(  (char*)d  +DELEN + ( (s3)*(d->max_no_values2)*(d->max_no_values1)
             + (s2)*(d->max_no_values1) + (s1))*8);
   }

}


//*****************************************************************************************
extern void store_reg(double *r1,struct dataelem* de, double* elem_ad,
                      unsigned int elem_occ1,unsigned int elem_occ2,unsigned int elem_occ3) 
                             /*-------store reg to data elem---*/
{

    misc_stodbl(de,elem_occ1,elem_occ2,elem_occ3,r1);
    return;

}

//*****************************************************************************************
extern unsigned long long_integ_value(struct dataelem* arg,double * arg_ad)        /*---calc integ value of data elem__*/
{
    unsigned long the_integ;
    double reg;

    the_integ=*arg_ad;
    return(the_integ);
}
  
//*****************************************************************************************
extern void move_it(char *to_ad, unsigned to_len, char *from_ad, unsigned from_len) /*--gen move rtn---*/
{
    ULong i;
     ULong len;
    char *ad1=(char*)null_ptr;
    if( to_len >= from_len ) len=from_len;
    else                     len=  to_len;
    
    for(i=0;i<len;++i) *(to_ad++)=*(from_ad++);
    if( len < to_len ) {
	ad1 = to_ad + len;
	while (len < to_len ) {
	    *ad1++ = ' ';
	    ++len;
	}
    }
    *(to_ad+to_len)=0x00;
    return;
}

//*****************************************************************************************
extern void misc_errmsg( char * the_msg)
{
   VoidPtr ptr;
   VoidHand hView;
   int res;
   int cnt;
   char rest[810];
   char errmsg[80];		//GHGlue
   //AlertTemplateType al;	//GHGlue
   struct  //GHGlue
   {
		UInt16		alertType;
		UInt16		helpRscID;
		UInt16		numButtons;
		UInt16		defaultButton;
	} al;  //GHGlue
//SysFatalAlert(the_msg);
  res=DmFindResource(VbRscDB,(ULong)'Talt',1,0);
  if(res!= -1) DmRemoveResource(VbRscDB,res); //delete alert if there

  StrCopy(rest,"");
  al.alertType=0;
  al.numButtons=1;
  al.defaultButton=0;
  al.helpRscID=0;
  cnt=8;   //will fill in 1st 8 later
  MemMove(rest+cnt,"Program Message",StrLen("Program Message")+1);    
  cnt+=StrLen("Program Message")+1;

  if( (StrLen(the_msg)+cnt)<800)
  {
      MemMove(rest+cnt,the_msg,StrLen(the_msg)+1);
      cnt += StrLen(the_msg)+1;
  }
  else
  {
      MemMove(rest+cnt,the_msg,800-cnt);
      rest[800]=0x00;
      cnt=801;
  }
  MemMove(rest+cnt,"OK",StrLen("OK")+1);
  cnt=cnt+StrLen("OK")+1;
  MemMove(rest,&al,8); 

  hView=DmNewResource(VbRscDB,(ULong)'Talt',1,cnt);

  if(hView==0)
  {                                           //inserted 05212003
       SysFatalAlert("Out of Memory-alert");
       ErrThrow(-1);                          //inserted 05212003
  }                                           //inserted 05212003
  ptr=MemHandleLock(hView);
//StrPrintF(debug,"msgbox s=%s ",the_msg);
//SysFatalAlert(debug);		              

  DmWrite(ptr,0,rest,cnt);
  MemHandleUnlock(hView);
      
  //commented out 2005.02.08 ignoreNextPenup=true;   //01212004
  
  msgboxOrAlertUp=true;  //stops penup from triggering object under msgbox
  res=FrmAlert(1);
//SysFatalAlert("Deleting alert resource");
  res=DmFindResource(VbRscDB,(ULong)'Talt',1,0);
  if(res != -1) DmRemoveResource(VbRscDB,res); //delete alert if there
  EvtFlushPenQueue();   //12172001
//SysFatalAlert("beyond alert");

  msgboxOrAlertUp=false;
  return;
}
//*****************************************************************************************
extern int integ_value(struct dataelem *arg, double *arg_ad)        /*---calc integ value of data elem__*/
{    
    int the_integ = *arg_ad;
    return(the_integ);
}

//*****************************************************************************************
extern void misc_getint(struct dataelem *d,  unsigned int sub1,unsigned int sub2,unsigned int sub3,  unsigned int *result)
{
  double *ptr=(double*)null_ptr;
  unsigned int the_no;

  char errmsg[80];

  if(d==null_ptr)
     misc_text_abort("getint--null addr");
  if(d->kind == 's')
  {
    
    StrPrintF(errmsg,"Using string variable where numeric expected(%d).",d->tbl_no);
    misc_text_abort(errmsg);
  }
  ptr=(double*)misc_find_virtual_addr(d,sub1,sub2,sub3,'g');
  the_no = *ptr;
  *result = the_no;
  return;
}

//*****************************************************************************************
extern void misc_getdbl(struct dataelem *d,  unsigned int sub1,unsigned int sub2,unsigned int sub3, double *result)
{
  double *ptr=0x00;
  char errmsg[80];


  if(d==null_ptr)
     misc_text_abort("getdbl--null addr");

  if(d->kind == 's')
  {
    
    StrPrintF(errmsg,"Using string variable where numeric expected(%d kind=%c).",d->tbl_no,d->kind);
    misc_text_abort(errmsg);
  }
  ptr=(double*)misc_find_virtual_addr(d,sub1,sub2,sub3,'g');
  *result = *ptr;
  return;
}
//*****************************************************************************************
extern void misc_getstr(struct dataelem *d,  unsigned int sub1,unsigned int sub2,unsigned int sub3, char *result)
{
  char *ptr=0x00;
  char errmsg[80];
  unsigned long curoffset;

  if(d==null_ptr)
     misc_text_abort("getstring--null addr");
  if(d->kind != 's')
  {
   
    StrPrintF(errmsg,"Using non-string variable where string expected(%d).",d->tbl_no);
    misc_text_abort(errmsg);
  }
  curoffset= *((int*) ((char *)(d)+DELEN
                +( (sub3)*(d->max_no_values2)*(d->max_no_values1)
                +  (sub2)*(d->max_no_values1)
                +  (sub1) )*2));
  if(curoffset==0)
  {
       StrCopy(result,"");
       return;
  }

  ptr=(char*)misc_find_virtual_addr(d,sub1,sub2,sub3,'g');
  
  StrCopy(result , ptr);
  return;
}



//*****************************************************************************************
extern void misc_stoint(struct dataelem *d,  unsigned int sub1,unsigned int sub2,unsigned int sub3,  unsigned int *result)
{
  double *ptr=(double*)null_ptr;
  double dbl;
  ULong offset;
  char errmsg[80];
  double z;
  if(d==null_ptr)
     misc_text_abort("stoint--null addr");
  if(d->kind == 's')
  {
    /**/
    StrPrintF(errmsg,"Using string variable where numeric expected(%d).",d->tbl_no);
    misc_text_abort(errmsg);
  }
  ptr=(double*)misc_find_virtual_addr(d,sub1,sub2,sub3,'s');
  dbl=*result;
  if(ptr!=null_ptr)
  {
    offset=(ULong)ptr-(ULong)d;
//StrPrintF(debug,"stoint = %d",d->tbl_no);
//SysFatalAlert(debug);		              

    DmWrite(d,offset,&dbl,8);   
  }
  return;
}

//*****************************************************************************************
void misc_stostr1(char*s)
{
	misc_stostr(&arg1,arg1_occ1,arg1_occ2,arg1_occ3,s);
}

//*****************************************************************************************
void misc_stostr2(char*s)
{
	misc_stostr(&arg2,arg2_occ1,arg2_occ2,arg2_occ3,s);
}

//*****************************************************************************************
void misc_stostr3(char*s)
{
	misc_stostr(&arg3,arg3_occ1,arg3_occ2,arg3_occ3,s);
}

//*****************************************************************************************
void misc_stostr4(char*s)
{
	misc_stostr(&arg4,arg4_occ1,arg4_occ2,arg4_occ3,s);
}

//*****************************************************************************************
void misc_stostr5(char*s)
{
	misc_stostr(&arg5,arg5_occ1,arg5_occ2,arg5_occ3,s);
}

//*****************************************************************************************
void misc_stostr6(char*s)
{
	misc_stostr(&arg6,arg6_occ1,arg6_occ2,arg6_occ3,s);
}

//*****************************************************************************************
extern void  misc_stostr      (struct dataelem * *d,
        unsigned int sub1,unsigned int sub2,unsigned int sub3, char *result)
{
  char *ptr=(char*)null_ptr;
  char errmsg[80];
  unsigned int l;
  unsigned int actLen;
  int k,kk,kkk;
  unsigned int curoffset;
  unsigned int tempoffset;
  VoidHand h;
  VoidHand saveH;
  unsigned int len;
  unsigned int len2;
  VoidHand tempHand;
  VoidPtr  tempPtr;
  
  if(*d==null_ptr)
     misc_text_abort("stostr--null addr");

  if((*d)->kind != 's')
  {
    StrPrintF(errmsg,"Using numeric var. where string expected var#%d kind=%c%c.",(*d)->tbl_no,&((*d)->kind)-1,(*d)->kind);
    misc_text_abort(errmsg);
  }
  //06012002if((*d)->isConstant==0x01)
  if((*d)->flags3 & 0x01)    //is it a constant    //06012002
  {
      //misc_text_abort("Trying to overwrite a system or application constant.");
      return;
  }
  ptr=(char*)misc_find_virtual_addr((*d),sub1,sub2,sub3,'s');
 
  
     l=0;
     curoffset= *((int*) ((char *)(*d)+DELEN
                +( (sub3)*((*d)->max_no_values2)*((*d)->max_no_values1)
                +  (sub2)*((*d)->max_no_values1)
                +  (sub1) )*2));
//StrPrintF(debug,"stostr offset=%d",curoffset);
//SysFatalAlert(debug);
    
   if (curoffset!=0) l=StrLen(ptr)+1;    
   else l=0;
   len2=MemPtrSize(*d);
   
      if(StrLen(result)<=(*d)->length) actLen=StrLen(result)+1;
      else actLen=(*d)->length+1;
   
   len=len2+actLen-l;
   if (curoffset!=0)   //means there is already a string value present
   {
//StrPrintF(debug,"l=%d actLen=%d",l,actLen);
//SysFatalAlert(debug);
     if(l==(actLen))
     {
        //same length, so just replace
//StrPrintF(debug,"stostr1= %s",result);
//SysFatalAlert(debug);		              
       
           DmWrite(*d, curoffset,result,actLen-1);
           DmSet(*d, curoffset+actLen-1,1,0x00);
           goto itsDone;
     }
     if (actLen<l)
     {
        
//StrPrintF(debug,"stostr2= %s",result);
//SysFatalAlert(debug);
           DmWrite(*d, curoffset,result,actLen-1);
           DmSet(*d, curoffset+actLen-1,1,0x00);
         //move up remaining
         if((curoffset+l)<MemPtrSize(*d))
         {
//StrPrintF(debug,"stostr3= %s",result);
//SysFatalAlert(debug);
             DmWrite(*d,curoffset+actLen,
                    ((char*)(*d)+curoffset+l),MemPtrSize(*d)-curoffset-l);
         }
         //now resize de 
             saveH=MemPtrRecoverHandle(*d);
             MemPtrUnlock(*d);
//StrPrintF(debug,"resizing string to %u (old de =%u)(old len was=%u)(new str='%s' len=%u) "
//,len,l,len2,result,StrLen(result));
//SysFatalAlert(debug);
             h=DmResizeResource(saveH,len);
             if(h==0)  OutOfMemory(6011);          //05282003
             *d=(struct dataelem*)MemHandleLock(h);
//StrPrintF(debug,"stostr4 delistptr= %s",result);
//SysFatalAlert(debug);
             DmWrite(deListPtr,(*d)->tbl_no*4,d,4); 
             ptr=(char*)misc_find_virtual_addr((*d),sub1,sub2,sub3,'s');
     }
     else
     {   
         //now resize de first to be larger
         saveH=MemPtrRecoverHandle(*d);
         MemPtrUnlock(*d);
//StrPrintF(debug,"resizing string to %u (old de =%u)(old len was=%u)(new str='%s' len=%u) "
//,len,l,len2,result,StrLen(result));
//SysFatalAlert(debug);
         h=DmResizeResource(saveH,len);
         if(h==0) OutOfMemory(6012);               //05282003
         *d=(struct dataelem*)MemHandleLock(h);
//StrPrintF(debug,"stostr1 delistptr2= %s",result);
//SysFatalAlert(debug);
         DmWrite(deListPtr,(*d)->tbl_no*4,d,4); 
         ptr=(char*)misc_find_virtual_addr((*d),sub1,sub2,sub3,'s');
//StrPrintF(debug,"ptr after resize=%s len=%d  l=%d",ptr,StrLen(ptr),l);
//SysFatalAlert(debug);
         //now move any remaining down
         if((curoffset+l)<(MemPtrSize(*d)-(actLen-l)))
         {

             tempHand=MemHandleNew(MemPtrSize(*d)-(curoffset+l)-(actLen-l));
             if(tempHand==0) OutOfMemory(6031);    //05282003 
             tempPtr=MemHandleLock(tempHand);

             MemMove(tempPtr,ptr+l,
                     MemPtrSize(*d)-(curoffset+l)-(actLen-l));
//StrPrintF(debug,"tempPtr=%s",tempPtr);
//SysFatalAlert(debug);
//StrPrintF(debug,"stostr1  tempptr= %s",tempPtr);
//SysFatalAlert(debug);
             DmWrite(*d,curoffset+actLen,
                    tempPtr,
                    MemPtrSize(*d)-(curoffset+l)-(actLen-l));

             MemPtrUnlock(tempPtr);
             MemHandleFree(tempHand);

         }
         
//StrPrintF(debug,"stostr8= %s",result);
//SysFatalAlert(debug);
         DmWrite(*d, curoffset,result,actLen-1);
         DmSet(*d, curoffset+actLen-1,1,0x00);
     }
     
     
     for (k=0;k<(*d)->max_no_values3;++k)
     {
      for(kk=0;kk<(*d)->max_no_values2;++kk)
      {
      for(kkk=0;kkk<(*d)->max_no_values1;++kkk)
       {
          tempoffset= *((unsigned int*) ((char*)(*d)+DELEN
                      +((k)*(*d)->max_no_values2*(*d)->max_no_values1
                      +(kk)*(*d)->max_no_values1+(kkk))*2)); 
          if( (tempoffset!=0) && (tempoffset > curoffset)    )
          {
             
             
//StrPrintF(debug, "setting offset=%d l=%d actlen=%d",tempoffset,l,actLen);
//SysFatalAlert(debug);
             tempoffset=tempoffset-l+actLen; //reduce by cur string len
             updti((struct dataelem*)(*d),(unsigned int *)((char*)(*d)+DELEN
                      +((k)*((*d)->max_no_values2)*((*d)->max_no_values1)
                      +(kk)*((*d)->max_no_values1)+(kkk))*2),
                          (int*)(&tempoffset));
             
          }
      }
     }
    }
   }
   else   //there isn't already a string value 
   {
             //store string at end

         //now resize de first to be larger
         saveH=MemPtrRecoverHandle(*d);
         MemPtrUnlock(*d);
//StrPrintF(debug,"resizing string to %u (old de =%u)(old len was=%u)(new str='%s' len=%u) "
//,len,l,len2,result,StrLen(result));
//SysFatalAlert(debug);
         h=DmResizeResource(saveH,len);
         if(h==0) OutOfMemory(6014);                 //05282003
         *d=(struct dataelem*)MemHandleLock(h);
         ptr=(char*)misc_find_virtual_addr((*d),sub1,sub2,sub3,'s');
        
           //resizes to new len
//StrPrintF(debug,"stostr9= %s",result);
//SysFatalAlert(debug);
           DmWrite(*d, MemPtrSize(*d)-actLen,result,actLen-1); //??if fixed
           DmSet(*d, MemPtrSize(*d)-1,1,0x00);
         
//StrPrintF(debug,"past the copy sub3=%d sub2=%d sub1=%d",sub3,sub2,sub1);
//SysFatalAlert(debug);
         k=MemPtrSize(*d)-actLen;
         updti((struct dataelem*)(*d),(unsigned int*)((char*)(*d)+DELEN
                      +((sub3)*((*d)->max_no_values2)*((*d)->max_no_values1)
                      +(sub2)*((*d)->max_no_values1)+(sub1))*2)
                      ,(int*)(&k));  //ptr to entry 's string
         
//StrPrintF(debug,"updating tblno=%d",(*d)->tbl_no);
//SysFatalAlert(debug);
//StrPrintF(debug,"stostr1 delistptr9= %s",result);
//SysFatalAlert(debug);
         DmWrite(deListPtr,(*d)->tbl_no*4,d,4);  //store handle in de list
         
   }      
//SysFatalAlert("leaving stostr");
itsDone:
  return;
}

//*****************************************************************************************
extern void misc_stodbl(struct dataelem *d,
      unsigned int sub1,unsigned int sub2,unsigned int sub3, double  *result)
{
  double *ptr;
  double z;
  char errmsg[80];
  ULong offset;

//char debug2[256];
//union 
//       {
//            FlpDouble q;
//            double d;
//       } x;


//StrPrintF(debug,"store dbl id=%d",d->tbl_no);
//SysFatalAlert(debug);
  
  if(d==null_ptr)
     misc_text_abort("stodbl--null addr");

  if(d->kind == 's')
  {

    StrPrintF(errmsg,"Using string var. where numeric expected(%d).",d->tbl_no);
    misc_text_abort(errmsg);
  }
  //06022002if(d->isConstant==0x01)
  if(d->flags3 & 0x01)    //is it a constant     //06012002
  {
      
      return;
  } 
//dbug("finding virtual addr");
  ptr=(double*)misc_find_virtual_addr(d,sub1,sub2,sub3,'n');
//DoubleToStr(*((double*)ptr),errmsg);
//StrPrintF(debug,"storing var=%d  value=%s",d->tbl_no,errmsg);
//dbug(debug);
  if(ptr!=null_ptr)
  {

    //06012002offset=(ULong)ptr-(ULong)d;
    z=*result;
    
   if(d->kind=='i')  z=misc_int(*result);  //03092002
   
//x.d=*result;
//FlpFToA(x.q,debug2);
//StrPrintF(debug,"storing dbl tblno=%d  val=%s",d->tbl_no,debug2);
//dbug(debug);
   //if (d->tbl_no<=(arith_work_de_max+string_work_de_max))   //03012002??
   
   if(d->flags3 & 0x02)    //is mem on heap    //06012002
   {                                            //06012002  
//StrPrintF(debug,"stodbl-write to heap i=%d",d->tbl_no);
//dbug(debug);
      MemMove(ptr,&z,8);    		//06012002
   }                                   			//06012002
   else                              	        //06012002
   {
//dbug("stodbl-modify non-heap");
//StrPrintF(debug,"stodbl-modify non-heap  %lu %lu  diff=%d size=%lu",(unsigned long)ptr,(unsigned long)d,(int)((char*)ptr-(char*)d),MemPtrSize(d));
//dbug(debug);
      //06012002 DmWrite(d,offset,&z,8);
     
      DmWrite(d,(ULong)ptr-(ULong)d,&z,8l);   //06012002
//dbug("after store in storedbl");
   }
//StrPrintF(debug,"stodbl= %d",d->tbl_no);
//SysFatalAlert(debug);

  }
  return;
}

//*****************************************************************************************
void dbug(char*msg)
{

      misc_errmsg(msg);

}

//*****************************************************************************************
int misc_codeexec(Word objId,unsigned long offset)
{               
	int result;                                    //09192004
	//ErrTry           //inserted 05212003
	//{                //inserted 05212003
	   pendingFormUpdateEventSw = false;          //09192004
	   //09192004 return( codeexec(objId,offset));
	   result = codeexec(objId,offset);            //09192004
	   if( pendingFormUpdateEventSw == true )      //09192004
	   {                                          //09192004
	   	   spawnFormUpdateEventCode();            //09192004
	   }                                          //09192004
	   return( result );                          //09192004
	//}                //inserted 05212003
	//ErrCatch(inErr)  //inserted 05212003
	//{                //inserted 05212003
//SysFatalAlert("caught codeexec");
//	   ErrThrow(-2);       //modified 05282003
//SysFatalAlert("after throw--codeexec");	       
//	}  ErrEndCatch   //inserted 05212003    
//SysFatalAlert("should not see--codeexec");	    
}

//*****************************************************************************************
void misc_stodbl1(double* x)
{
	misc_stodbl(arg1,arg1_occ1,arg1_occ2,arg1_occ3,x);
}

//*****************************************************************************************
void misc_stodbl2(double* x)
{
	misc_stodbl(arg2,arg2_occ1,arg2_occ2,arg2_occ3,x);
}

//*****************************************************************************************
void misc_stodbl3(double* x)
{
	misc_stodbl(arg3,arg3_occ1,arg3_occ2,arg3_occ3,x);
}

//*****************************************************************************************
void misc_stodbl5(double* x)
{
	misc_stodbl(arg5,arg5_occ1,arg5_occ2,arg5_occ3,x);
}

//*****************************************************************************************
void misc_stodbl6(double* x)
{
	misc_stodbl(arg6,arg6_occ1,arg6_occ2,arg6_occ3,x);
}

//*****************************************************************************************
void dbugKinds(char*s)
{
  struct dataelem *p;
  char c1,c2,c3,c4,c5;
  p=elem_tbl_ptr(1);
  c1=p->kind;
  p=elem_tbl_ptr(2);
  c2=p->kind;
  p=elem_tbl_ptr(3);
  c3=p->kind;
  p=elem_tbl_ptr(4);
  c4=p->kind;
  p=elem_tbl_ptr(5);
  c5=p->kind;
  StrPrintF(debug,"kinds at %s=%c%c%c%c%c",s,c1,c2,c3,c4,c5);
  SysFatalAlert(debug);
}

//*****************************************************************************************
VoidHand MiscHandleNew(ULong size, char *who)
{
    //this routine allocates new memory handles
    //if memory debugging is off, this acts just like MemHandleNew
    //if memory debugging is on, a block of memory is allocated for debugging and tracjking
    //  as well as allocating a new handle for the calling routine to use
    
   
    struct memBlock * p;
    VoidHand h;
    Err err;
     if(memDebugSw==0) //memory debug not active
    {
        h=MemHandleNew(size);
        if(h==0) OutOfMemory(1);
        return(h);
    }
    else
    {
//StrPrintF(debug,"handle new-%s",who);
//SysFatalAlert(debug);
        p=MemPtrNew(sizeof(sampleMemBlock));
        if(p==0) OutOfMemory(2);
        p->handle=MemHandleNew(size);
        if(p->handle==0) OutOfMemory(3);
        p->ptr=0;
        p->lockCnt=0;
        p->who=MemPtrNew(StrLen(who)+1);
        if(p->who==0) OutOfMemory(4);
        StrCopy(p->who,who);
        if ( memDebugFirst==0)   //link into memory chain
        {
             memDebugFirst=p;
             p->prev=0;
             p->next=0;
        }
        else
        {
             
             p->next=memDebugFirst;
             p->next->prev=p;
             p->prev=0;
             memDebugFirst=p;
        }      
        return(p->handle);    
    }
    
}
//*****************************************************************************************
VoidPtr MiscPtrNew(ULong size, char *who)
{
    //this routine allocates new memory pointers
    //if memory debugging is off, this acts just like MemPtrNew
    //if memory debugging is on, a block of memory is allocated for debugging and tracjking
    //  as well as allocating a new pointer for the calling routine to use
    
   
    struct memBlock * p;
    VoidPtr ptr;
    Err err;
     if(memDebugSw==0) //memory debug not active
    {
        ptr=MemPtrNew(size);
        if(ptr==0)
        {
           //05212003 StrPrintF(debug,"getting %ld bytes",size);
           //05212003 SysFatalAlert(debug);
           OutOfMemory(5);
        }
        return(ptr);      
    }
    else
    {
//StrPrintF(debug,"ptr new-%s",who);
//SysFatalAlert(debug);
        p=MemPtrNew(sizeof(sampleMemBlock));
        if(p==0) OutOfMemory(6);
        p->handle=MemHandleNew(size);
        if(p->handle==0) OutOfMemory(7);
        p->ptr=MemHandleLock(p->handle);
        p->lockCnt=0;
        p->who=MemPtrNew(StrLen(who)+1);
        if(p->who==0) OutOfMemory(8);
        StrCopy(p->who,who);
        if ( memDebugFirst==0)   //link into memory chain
        {
             memDebugFirst=p;
             p->prev=0;
             p->next=0;
        }
        else
        {
             
             p->next=memDebugFirst;
             p->next->prev=p;
             p->prev=0;
             memDebugFirst=p;
        }      
        return(p->ptr);    
    }
    
}

//*****************************************************************************************
Err MiscHandleFree( VoidHand h )
{
    struct memBlock* p;
    Err err;
    if(memDebugSw==0)  //no mem debug in process
    {
        return(MemHandleFree(h));
    }
    else
    {

        p=memDebugFirst;
        while(p)
        {
          if(p->handle==h) break; 
          p=p->next;
        }
        
        if(p==0) return(memErrInvalidParam);
        //ok to free
//StrPrintF(debug,"handle free-%s",p->who);
//SysFatalAlert(debug);
        
        
        err=MemHandleFree( p->handle);
        //unlink and free the memBlock
        MiscReleaseMemPtr(p);
        return(err);
    }
}
//*****************************************************************************************
Err MiscPtrFree( VoidPtr ptr )
{
    struct memBlock* p;
    Err err;
//SysFatalAlert("ptr free");
    if(memDebugSw==0)  //no mem debug in process
    {
        return(MemPtrFree(ptr));
    }
    else
    {

        p=memDebugFirst;
        while(p)
        {
          if(p->ptr==ptr) break; 
          p=p->next;
        }
        if(p==0)
        {
            MemPtrFree(ptr);
            return(memErrInvalidParam);
        }
        //ok to free

        
        err=MemPtrFree( p->ptr);
        //unlink and free the memBlock
        MiscReleaseMemPtr(p);
        
        return(err);
    }
}
//*****************************************************************************************
VoidPtr MiscHandleLock( VoidHand h)
{
    struct memBlock* p;
    Err err;
    if(memDebugSw==0)  //no mem debug in process
    {
        return(MemHandleLock(h));
    }
    else
    {

        p=memDebugFirst;
        while(p)
        {
          if(p->handle==h) break; 
          p=p->next;
        }
        if(p==0) 
        {
//SysFatalAlert("could not find handle to lock!!!!");
            return(0);
        }    
//StrPrintF(debug,"handle lock-%s",p->who);
//SysFatalAlert(debug);
        p->ptr = MemHandleLock(h);
        p->lockCnt += 1;
        
        if(p->lockCnt>25)
        {
           StrPrintF(debug,"Too many locks %s  cnt=%lu",p->who,p->lockCnt);
           SysFatalAlert(debug);
           ErrThrow(-1);                //inserted 05212003
        }
        
        
        return(p->ptr);
   }     
}
//*****************************************************************************************
Err MiscHandleUnlock( VoidHand h)
{
    struct memBlock* p;
    Err err;
    if(memDebugSw==0)  //no mem debug in process
    {
        return(MemHandleUnlock(h));
    }
    else
    {

        p=memDebugFirst;
        while(p)
        {
          if(p->handle==h) break; 
          p=p->next;
        }
        if(p==0) 
        {
            SysFatalAlert("can't find a matching handle to unlock");
            //05212003 return(memErrInvalidParam);
            ErrThrow(-1);                 //inserted 05212003
        }
//StrPrintF(debug,"successful handle unlock-%s",p->who);
//SysFatalAlert(debug);
        MemHandleUnlock(h);
        p->ptr=0;
        if(p->lockCnt<=0)
        {
           StrPrintF(debug,"Too few locks %s  cnt=%lu",p->who,p->lockCnt);
           SysFatalAlert(debug);
           ErrThrow(-1);                 //inserted 05212003
        }
        p->lockCnt -= 1;
        
         
        return(0);
   }     
}
//*****************************************************************************************
Err MiscPtrUnlock( VoidPtr ptr)
{
    struct memBlock* p;
    Err err;
    if(memDebugSw==0)  //no mem debug in process
    {
        return(MemPtrUnlock(ptr));
    }
    else
    {

        if(ptr==0) return(0);
        p=memDebugFirst;
        while(p)
        {
          if(p->ptr==ptr) break; 
          p=p->next;
        }
        if(p==0)
        {
             SysFatalAlert("Can't find a matching ptr to unlock");
             //05212003 return(memErrInvalidParam);
             ErrThrow(-1);                 //inserted 05212003
        }
//StrPrintF(debug,"ptr unlock-%s",p->who);
//SysFatalAlert(debug);
        if(p->lockCnt<=0)
        {
           StrPrintF(debug,"Too few locks %s cnt=%lu",p->who,p->lockCnt);
           SysFatalAlert(debug);
           ErrThrow(-1);                 //inserted 05212003
        }
        MemPtrUnlock(ptr);
        p->lockCnt -= 1;
        //if (StrCompare(p->who,"dbElems")==0)
        //{
        //      StrPrintF(debug,"unlocking dbElems via ptr unlock cnt=%lu",p->lockCnt);
        //      SysFatalAlert(debug);
        //}
        return(0);
   }     
}
//*****************************************************************************************
VoidHand MiscPtrRecoverHandle( VoidPtr ptr )
{
    struct memBlock* p;
    Err err;
    if(memDebugSw==0)  //no mem debug in process
    {
        return(MemPtrRecoverHandle(ptr));
    }
    else
    {
        p=memDebugFirst;
        while(p)
        {
          if(p->ptr==ptr) break; 
          p=p->next;
        }
        if(p==0)
        {
//SysFatalAlert("could not find ptr to recover handle");
             return(0);
        }
        
//StrPrintF(debug,"ptr recover handle-%s",p->who);
//SysFatalAlert(debug);
        if(p->handle==0) p->handle=MemPtrRecoverHandle(p->ptr);

        return(p->handle);
   }     
}
//*****************************************************************************************
VoidHand MiscDmNewHandle(DmOpenRef dbr, ULong size, char *who)
{
    //this routine allocates new memory handles
    //if memory debugging is off, this acts just like MemHandleNew
    //if memory debugging is on, a block of memory is allocated for debugging and tracjking
    //  as well as allocating a new handle for the calling routine to use
    
   
    struct memBlock * p;
    VoidHand h;
    Err err;
     if(memDebugSw==0) //memory debug not active
    {
        h=DmNewHandle(dbr,size);
        if(h==0) OutOfMemory(9);
        return(h);
    }
    else
    {
//StrPrintF(debug,"misc dm new handle-%s",who);
//SysFatalAlert(debug);
        p=MemPtrNew(sizeof(sampleMemBlock));
        if(p==0) OutOfMemory(10);
        p->handle=DmNewHandle(dbr,size);
        if(p->handle==0) OutOfMemory(11);
        p->ptr=0;
        p->lockCnt=0;
        p->who=MemPtrNew(StrLen(who)+1);
        if(p->who==0) OutOfMemory(12);
        StrCopy(p->who,who);
        if ( memDebugFirst==0)   //link into memory chain
        {
             memDebugFirst=p;
             p->prev=0;
             p->next=0;
        }
        else
        {
             p->next=memDebugFirst;
             p->next->prev=p;
             p->prev=0;
             memDebugFirst=p;
        }      
        return(p->handle);    
    }
    
}
//*****************************************************************************************
VoidHand MiscDmNewResource(DmOpenRef dbr, ULong type,Int rscId,ULong size,char *who)
{
    //this routine allocates new memory handles
    //if memory debugging is off, this acts just like MemHandleNew
    //if memory debugging is on, a block of memory is allocated for debugging and tracjking
    //  as well as allocating a new handle for the calling routine to use
    
   
    struct memBlock * p;
    VoidHand h;
    Err err;
     if(memDebugSw==0) //memory debug not active
    {
        h=DmNewResource(dbr,type,rscId,size);
        if(h==0) OutOfMemory(13);
        return(h);
    }
    else
    {
        p=MemPtrNew(sizeof(sampleMemBlock));
        if(p==0) OutOfMemory(14);
        p->handle=DmNewResource(dbr,type,rscId,size);
        if(p->handle==0) OutOfMemory(15);
        p->ptr=0;
        p->lockCnt=0;
        p->who=MemPtrNew(StrLen(who)+1);
        if(p->who==0) OutOfMemory(16);

        StrCopy(p->who,who);
//StrPrintF(debug,"dm new resource-%s",p->who);
//SysFatalAlert(debug);
        if ( memDebugFirst==0)   //link into memory chain
        {
             memDebugFirst=p;
             p->prev=0;
             p->next=0;
        }
        else
        {
             p->next=memDebugFirst;
             p->next->prev=p;
             p->prev=0;
             memDebugFirst=p;
        }      
        return(p->handle);    
    }
    
}
//*****************************************************************************************
VoidHand MiscDmGetResource( ULong type, Int ID, char *who)
{
     
    struct memBlock * p;
    Err err;
     if(memDebugSw==0) //memory debug not active
    {
        return(DmGetResource(type, ID));
    }
    else
    {

        p=MemPtrNew(sizeof(sampleMemBlock));
        if(p==0) OutOfMemory(17);
        p->handle=DmGetResource(type, ID);
        if(p->handle==0) 
        {
            MemPtrFree(p);
            return((VoidHand)0);
        }
        p->ptr=0;
        p->lockCnt=0;
        p->who=MemPtrNew(StrLen(who)+1);
        if(p->who==0) OutOfMemory(18);
        StrCopy(p->who,who);
//StrPrintF(debug,"dm get resource-%s",p->who);
//SysFatalAlert(debug);
        if ( memDebugFirst==0)   //link into memory chain
        {
             memDebugFirst=p;
             p->prev=0;
             p->next=0;
        }
        else
        {
             p->next=memDebugFirst;
             p->next->prev=p;
             p->prev=0;
             memDebugFirst=p;
        }      
        return(p->handle);    
    }
    
}
//*****************************************************************************************
VoidHand MiscDmGetResourceIndex( DmOpenRef dbr, Int index, char *who)
{
     
    struct memBlock * p;
    Err err;
     if(memDebugSw==0) //memory debug not active
    {
        return(DmGetResourceIndex(dbr,index));
    }
    else
    {

        p=MemPtrNew(sizeof(sampleMemBlock));
        if(p==0) OutOfMemory(19);
        p->handle=DmGetResourceIndex(dbr,index);
        if(p->handle==0) 
        {
            MemPtrFree(p);
            return((VoidHand)0);
        }
        p->ptr=0;
        p->lockCnt=0;
        p->who=MemPtrNew(StrLen(who)+1);
        if(p->who==0) OutOfMemory(20);
        StrCopy(p->who,who);
//StrPrintF(debug,"dm get resource-%s",p->who);
//SysFatalAlert(debug);
        if ( memDebugFirst==0)   //link into memory chain
        {
             memDebugFirst=p;
             p->prev=0;
             p->next=0;
        }
        else
        {
             p->next=memDebugFirst;
             p->next->prev=p;
             p->prev=0;
             memDebugFirst=p;
        }      
        return(p->handle);    
    }
    
}
//*****************************************************************************************
Err MiscDmReleaseResource( VoidHand h )
{
    struct memBlock* p;
    Err err;
    if(memDebugSw==0)  //no mem debug in process
    {
        return(DmReleaseResource(h));
    }
    else
    {

        p=memDebugFirst;
        while(p)
        {
          if(p->handle==h) break; 
          p=p->next;
        }
        if(p==0) return(memErrInvalidParam);
        //ok to free
        err=DmReleaseResource(h);
        MiscReleaseMemPtr(p);
        return(err);
    }
}
//*****************************************************************************************
VoidHand MiscDmGetRecord( DmOpenRef dbr, UInt index)
{
     
    struct memBlock * p;
    Err err;
     if(memDebugSw==0) //memory debug not active
    {
        return(DmGetRecord(dbr,index));
    }
    else
    {

        p=MemPtrNew(sizeof(sampleMemBlock));
        if(p==0) OutOfMemory(21);
        p->handle=DmGetRecord(dbr,index);
        p->ptr=0;
        p->lockCnt=0;
        p->who=MemPtrNew(StrLen("dmGetRec")+1);
        if(p->who==0) OutOfMemory(22);
        StrCopy(p->who,"dmGetRec");
//StrPrintF(debug,"dm get resource-%s",p->who);
//SysFatalAlert(debug);
        if ( memDebugFirst==0)   //link into memory chain
        {
             memDebugFirst=p;
             p->prev=0;
             p->next=0;
        }
        else
        {
             p->next=memDebugFirst;
             p->next->prev=p;
             p->prev=0;
             memDebugFirst=p;
        }      
        return(p->handle);    
    }
    
}
//*****************************************************************************************
Err MiscDmReleaseRecord( VoidHand h, DmOpenRef dbr, UInt index, Boolean dirty)
{
    struct memBlock * p;
    Err err;
    if(memDebugSw==0) //memory debug not active
    {
        return(DmReleaseRecord(dbr,index,dirty));
    }
    else
    {
        err=DmReleaseRecord( dbr,index,dirty);
        p=memDebugFirst;
        while(p)
        {
          if(p->handle==h) break; 
          p=p->next;
        }
        if(p==0) return(memErrInvalidParam);
        //ok to free

        //unlink and free the memBlock
        MiscReleaseMemPtr(p);
        return(err);
    }    
} 

//*****************************************************************************************
VoidHand MiscDmNewRecord( DmOpenRef dbr, UIntPtr atP, ULong size,char *who) 
{
     
    struct memBlock * p;
    Err err;
    VoidHand h;                                 //05282003
     if(memDebugSw==0) //memory debug not active
    {
        h=DmNewRecord(  dbr, atP,  size) ;   //mod 05282003
        if(h==0) OutOfMemory(6010);           //inserted 05282003
        return(h);                            //mod 05282003
    }
    else
    {

        p=MemPtrNew(sizeof(sampleMemBlock));
        if(p==0) OutOfMemory(23);
        p->handle=DmNewRecord(  dbr,  atP,  size) ;
        if(p->handle==0) OutOfMemory(23);    //05282003
        p->ptr=0;
        p->lockCnt=0;
        p->who=MemPtrNew(StrLen(who)+1);
        if(p->who==0) OutOfMemory(24);
        
        StrCopy(p->who,who);
//StrPrintF(debug,"dm get resource-%s",p->who);
//SysFatalAlert(debug);
        if ( memDebugFirst==0)   //link into memory chain
        {
             memDebugFirst=p;
             p->prev=0;
             p->next=0;
        }
        else
        {
             p->next=memDebugFirst;
             p->next->prev=p;
             p->prev=0;
             memDebugFirst=p;
        }      
        return(p->handle);    
    }
    
}
//*****************************************************************************************
VoidHand MiscDmResizeResource(VoidHand h, ULong size)
{
    //this routine resizes an existing handle
    //if memory debugging is off, this acts just like DmResizeResource
    //if memory debugging is on, the extra memory block is used
    
   
    struct memBlock * p;
    VoidHand newH;                   //05282003
    
    Err err;
     if(memDebugSw==0) //memory debug not active
    {
        newH=DmResizeResource(h,size);    //mod 05282003
        if(newH==0)  OutOfMemory(6018);   //05282003
        return(newH);                     //05282003
    }
    else
    {
//StrPrintF(debug,"handle new-%s",who);
//SysFatalAlert(debug);
        
        p=memDebugFirst;
        while(p)
        {
          if(p->handle==h) break; 
          p=p->next;
        }
        if(p==0)
        {
           SysFatalAlert("Can't resize resource");
           //05212003 return((VoidHand)0);
           ErrThrow(-1);                 //inserted 05212003
        }
        p->handle=DmResizeResource(p->handle,size);
        if(p->handle==0) OutOfMemory(6018);   //05282003
        p->ptr=0;
        p->lockCnt=0;
        
        
        
        
        return(p->handle);    
    }
    
}
//*****************************************************************************************
VoidHand MiscDmResizeRecord(VoidHand h, DmOpenRef dbr, UInt index, ULong size)
{
    struct memBlock * p;
    VoidHand newH;   //05282003
    if(memDebugSw==0) //memory debug not active
    {
        newH=DmResizeRecord(  dbr, index,  size) ;  //mod 05282003
        if(newH==0)   OutOfMemory(6019);      //05282003      
        return(newH);               //05282003
    }
    else
    {
        p=memDebugFirst;
        while(p)
        {
          if(p->handle==h) break; 
          p=p->next;
        }
        if(p==0)
        {
           SysFatalAlert("Can't resize resource");
           //05212003 return((VoidHand)0);
           ErrThrow(-1);                 //inserted 05212003
        }
        p->handle=DmResizeRecord(dbr, index,  size);
        if(p->handle==0) OutOfMemory(6019);  //05282003
        p->ptr=0;
        p->lockCnt=0;
        
        return(p->handle);    
    }  
}
//*****************************************************************************************
Err MiscDmDetachRecord( DmOpenRef dbr, UInt index, Handle * oldH)
{
    struct memBlock * p;
    
    Err err;
    if(memDebugSw==0) //memory debug not active
    {
        return(DmDetachRecord(  dbr, index,  oldH) );
    }
    else
    {
        p=MemPtrNew(sizeof(sampleMemBlock));
        if(p==0) OutOfMemory(25);
        ;
        err=DmDetachRecord(dbr, index, oldH);
        if(err!=0)
        {
           StrPrintF(debug,"Detach record error=%d",err);
           SysFatalAlert(debug);
           ErrThrow(-1);                 //inserted 05212003
        }
        p->handle = *oldH; 
        p->ptr=0;
        p->lockCnt=0;
        p->who=MemPtrNew(StrLen("detach")+1);
        if(p->who==0) OutOfMemory(26);
        StrCopy(p->who,"detach");
//StrPrintF(debug,"dm get resource-%s",p->who);
//SysFatalAlert(debug);
        if ( memDebugFirst==0)   //link into memory chain
        {
             memDebugFirst=p;
             p->prev=0;
             p->next=0;
        }
        else
        {
             p->next=memDebugFirst;
             p->next->prev=p;
             p->prev=0;
             memDebugFirst=p;
        }      
        return(err);           
    }
	    
}
//*****************************************************************************************
void MiscChkLockCnt( char * what, char *  who)
{
   struct memBlock * p;
    if(memDebugSw==0) //memory debug not active
    {
        return;
    }
    else
    {   
        p=memDebugFirst;
        while(p)
        {
          if(StrCaselessCompare(p->who,what)==0) break; 
          p=p->next;
        }
        if(p==0)
        {
           return;
        }
        StrPrintF(debug,"the lock count for %s at %s is %lu",what,who,p->lockCnt);
        SysFatalAlert(debug);
        ErrThrow(-1);                 //inserted 05212003
    }
    return;
}
//*****************************************************************************************
void MiscMemDump()
{
    struct memBlock * p;
    char wk[50];
    
    if(memDebugSw==0) //memory debug not active
    {
        return;
    }
    else
    {   
        p=memDebugFirst;
        while(p)
        {
          if(p->who) StrCopy(wk,p->who);
          else       wk[0]=0x00;
          StrPrintF(debug,"mem=%s   size=%lu lockCnt=%lu",wk,MemHandleSize(p->handle),p->lockCnt); 
          SysFatalAlert(debug);
          p=p->next;
        }
    }
}    

//*****************************************************************************************
void MiscReleaseMemPtr(struct memBlock *p)
{
        if(p->who) MemPtrFree(p->who);
        if(p->next) p->next->prev=p->prev;
        if( p==memDebugFirst)
        {
            memDebugFirst=p->next;
        }
        else
        {
           p->prev->next=p->next;
        }
        MemPtrFree(p);
}

//*****************************************************************************************
UInt16 miscFrmGetObjectIdFromPtr(const FormType *formP, void *objP)  //GH  01.10.2002
// like FrmGetObjectIndexFromPtr, but works with OS<4.0
{
  int i;
  for(i=0;i<FrmGetNumberOfObjects(formP);++i)
    {
      if (FrmGetObjectPtr(formP,i)==objP)
         {
           break; 
         }    
      } 
  FrmGetObjectId(formP, i);  
 } 
//*****************************************************************************************
void dbugx(double *val, char*identifier)
{

   char s[256];
   union 
       {
            FlpDouble q;
            double d;
       } x;
       
       
    FlpCompDouble flp;

x.d=*val;
FlpFToA(x.q, s);
StrPrintF(debug,"dbugx@%s x=%s    addr=%lu",identifier,s,val);
SysFatalAlert(debug);

}