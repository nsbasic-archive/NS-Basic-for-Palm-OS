#ifdef mainpgm
#define XXXX
#else
#define XXXX extern
#endif
#define DO_NOT_ALLOW_ACCESS_TO_INTERNALS_OF_STRUCTS

//#define   ORG_SWB        comment out if not StylusWareBasic
#define   ORG_NSB        comment out if not NSB Basic

#ifdef ORG_SWB
      #ifdef ORG_NSB
           error--can't have both ORG's set
      #endif 
          
#else
  #ifdef ORG_NSB
      #ifdef ORG_SWB
          error--can't have both ORG's set
      #endif
  #else
          error--must define one or the other
  #endif
  
#endif


XXXX Boolean resetToDesignState;      //true if need to revert form to design state

#ifndef ARM
/* EMP variables normally in PNO block */
XXXX Int16 cur_stmt_no;
XXXX Int16 mathLibRefNum;
XXXX VoidHand perfHand;
XXXX unsigned char gSerialState;
XXXX char *paragTbl;
XXXX void * forPtrSave;
XXXX struct forStruct *forptr;
XXXX char *deListPtr;
XXXX DmOpenRef VbRscDB;
XXXX VoidPtr controlPtr;
XXXX VoidHand viewElems;
XXXX VoidPtr  viewElemsPtr;
XXXX VoidPtr dbElemsPtr;
XXXX MenuBarPtr menuPtr;
XXXX WinHandle  DrawWin;
XXXX MemHandle winRoot;
XXXX UInt32 romVersion;
XXXX UInt16 work_de_max;
XXXX Int16 userFunctionSequentialNo;
XXXX Int16 applVersionInteg;
XXXX Int16 numberParas;
XXXX UInt16 theCodeOffset;
XXXX UInt16 instr_ctr;
XXXX Int16 logic_value;
XXXX UInt16 controlid;
XXXX Int16 view_cnt;
XXXX Int16 msgboxOrAlertUp;
XXXX Int16 parag_cnt;
XXXX Int16 currentX;
XXXX Int16 currentY;
XXXX Int16 penDown;
XXXX Int16 fldToUpdate;
XXXX Int16 eventHandled;
XXXX Int16 eventType;
XXXX Int16 ignoreNextPenup;
XXXX UInt16 frmNo;
XXXX Int16 debug_on;
XXXX UInt16 lastKeyDownKeyCode;
XXXX WChar lastKeyDownChr;
XXXX UInt16 lastKeyDownModifiers;
XXXX Int16 runtimeVersionInteg;
XXXX UInt16 serRef;
XXXX char lastKeyString[2];
#endif
XXXX UInt32 timerExpirationTime;

XXXX Boolean pendingFormUpdateEventSw;                       //09192004


#if 0
// EMP moved to shared
XXXX unsigned long PNO(romVersion);

XXXX Int16 userFunctionSequentialNo;      //added 5.27.2000  seq no assigned to each nested user function call
#endif
/* EMP replaced with a define to make StrongArm easier */
#ifdef ORG_SWB
#define rscTag 'Swba'  /*resource identifier used for code and other resource records*/
#endif
#ifdef ORG_NSB
#define rscTag 'nsba'   /*resource identifier used for code and other resource records*/
#endif 

#if 0
XXXX ULong  rscTag;              //resource identifier used for code and other resource records
#endif

XXXX char testSw;
#define TRUE -1
#define FALSE 0
#define NIL 0x00
#define RESOURCE_CODE_TYPE 'Pcod'
#define SCREEN_MAX_X 160

//gSerialState machine constants	//03.06.02 GH
#define  kSerialNoAsync 		0	//set in open and close.
#define  kSerialWaitingForData	1	//set by serialReceiveWithEvent
#define  kSerialDataWaiting		2	//set when woken up, fires nilevent
#define  kSerialReadingData		3	//set by nilevent in event loop. Receive resets to kSerialWaitingForData

#ifdef __MC68K__

void * misc_get_mem(Int16 size, char* who);

VoidHand MiscHandleNew(ULong size, char *who);
VoidPtr MiscPtrNew(ULong size, char *who);
Err MiscHandleFree( VoidHand h );
Err MiscPtrFree( VoidPtr ptr );

Err     MiscHandleUnlock( VoidHand h);
VoidPtr MiscHandleLock( VoidHand h);
Err     MiscPtrUnlock( VoidPtr ptr);
VoidHand MiscPtrRecoverHandle( VoidPtr ptr );
VoidHand MiscDmNewHandle(DmOpenRef dbr, ULong size, char *who);
VoidHand MiscDmGetResource( ULong type, Int ID, char*who);
VoidHand MiscDmNewResource(DmOpenRef dbr, ULong type,Int rscId,ULong size,char *who);
VoidHand MiscDmNewRecord(DmOpenRef dbr, UIntPtr atP, ULong size , char *who);
Err MiscDmReleaseResource( VoidHand h );
VoidHand MiscDmGetRecord(DmOpenRef dbr,UInt index);
VoidHand MiscDmResizeResource( VoidHand h, ULong newSize);
VoidHand MiscDmResizeRecord(VoidHand h, DmOpenRef dbr, UInt index, ULong size);
Err MiscDmDetachRecord(DmOpenRef dbr, UInt index, Handle* oldH);
Err MiscDmReleaseRecord( VoidHand h, DmOpenRef dbr, UInt index, Boolean dirty);
VoidHand MiscDmGetResourceIndex( DmOpenRef dbr, Int index,char *who);

void * misc_get_mem(Int16 size, char* who);

#endif

#if 0
// EMP moved to pno
XXXX int work_de_max;
XXXX VoidPtr controlPtr;
XXXX UInt16    controlid;
#endif
XXXX VoidHand  hData;
XXXX VoidHand  hView;
#if 0
// EMP moved to pno
XXXX DmOpenRef VbRscDB;
#endif
XXXX LocalID   VbRscLocalID;
XXXX  UInt     ApplPdbCardNo;
XXXX LocalID   ApplPrcLocalID;
XXXX DmOpenRef ApplPrcDB;
XXXX LocalID   ApplPdbLocalID;
XXXX DmOpenRef ApplPdbDB;
XXXX EventPtr  theEvent;

XXXX char aNullStringConstant;
XXXX char *   dummy;
XXXX char debug[255];

#if 0
// EMP moved to PNO
XXXX VoidHand   perfHand;
XXXX WinHandle  DrawWin;
XXXX MenuBarPtr menuPtr;
XXXX UInt       menuId;
XXXX VoidPtr    dbElemsPtr;
#endif
XXXX VoidHand   dbElems;

// Structure definition moved from main.c
struct basc_pref     // 12/18/2000 MMD
{                    // 12/18/2000 MMD
   char name[32];    // 12/18/2000 MMD
   UInt cardNo;      // 12/18/2000 MMD
};                   // 12/18/2000 MMD

// EMP rearranged for PNO
//added 09242003
//**************************************************************************
//     each field of a database record
//**************************************************************************
struct dbField
{
     VoidHand   hName;    //name handle
     Int16        tblNo;          //data element #
     Int16        colNo;    //# of column
     Int16        type;  //type data
#define dbFldTypeString    00
#define dbFldTypeLongInt   01                           
#define dbFldTypeDouble    02                           
#define dbFldTypeDate      03                            
#define dbFldTypeTime      04
#define dbFldTypeShortInt  05 
#define dbFldTypeSingle    06                           
#define dbFldTypeByte      07                           //  04=time
                            
     Int16    keyFlag;  //true = fld is a db key field
};
XXXX struct dbField dbFldExample; 

// EMP arranged for PNO
#if 1
struct dbType
{
  VoidHand  curHand;
  struct dbField*  ptrFields;        //added 09242003
  VoidHand     hName;                   //added 09242003
  VoidHand     hCreator;  //string      //added 09242003 
  Int16       noFields;                //added 09242003
  Int16          keyFldNo;      //added 02042004 
  DmOpenRef dm;
  LocalID   lid;
  UInt16    LastDbRecordRead;
  UInt16    cardno;
  UInt16    offset;
  char      openSw;
  char      filler;
};
#else
struct dbType
{
  char      openSw;
  UInt      LastDbRecordRead;
  DmOpenRef dm;
  UInt      cardno;
  LocalID   lid;
  VoidHand  curHand;
  UInt      offset;
};
#endif

#ifndef ARM
extern char *   codePtr;               //09242003
#endif

#ifdef __MC68K__
XXXX struct dbType db_example;
#endif

// EMP rearranged for PNO
#if 1
struct codeBlock
{
  // begin swap SwapCodeBlock
  VoidPtr      prevCodePtr;
  VoidPtr      p3;
  VoidHand     h3;
  VoidPtr      paragTbl;
  VoidPtr      codePtr;
  VoidPtr      newp3;
  VoidHand     newh3;
  UInt16       instr_ctr;
  UInt16       id;
  Int16        numberParas;
  UInt16       oldOffset;
  UInt16       argsOffset;
  Int16        functionLinkNo;
  UInt16       offset;
  UInt16	   cur_stmt_no;
  UInt16	   subFuncEntry_stmt_no;
  // end swap
};
#else

struct codeBlock
{
  UInt         id;
  VoidPtr      prevCodePtr;
  VoidPtr      p3;
  VoidHand     h3;
  int          numberParas;
  VoidPtr      paragTbl;
  VoidPtr      codePtr;
  unsigned int instr_ctr;
  VoidPtr      newp3;
  VoidHand     newh3;
  unsigned int oldOffset;
  unsigned int argsOffset;
  int          functionLinkNo;
  unsigned int offset;
};
#endif
XXXX struct codeBlock sampleCodeBlock;
#ifndef ARM
XXXX struct codeBlock *codeBlockPtr;
#endif

struct base_rec
{
  Int16 def_screen_no;
  Int16 de_cnt;
  Int16 parag_cnt;
  Int16 codemod_cnt;
  Int16 view_cnt;
  Int16 first_string_work;  /*neg #*/
  Int16 string_wk_max;
  Int16 first_arith_work; /*neg #*/
  Int16 arith_wk_max;
  Int16 dbCnt;
  Int16 versionInteg;
  Int16 versionFrac;
  Int16 LitePro;
  unsigned char secByte1;
  unsigned char secByte2;
  unsigned char secByte3;
  unsigned char secByte4;
  unsigned char secByte5;
  unsigned char secByte6;
  unsigned char secByte7;
  unsigned char secByte8;
  unsigned long createDate;
  char fill[38];
} ;

#ifdef __MC68K__
XXXX int de_cnt;
#if 0
    // EMP moved to PNO
XXXX Int16 parag_cnt;
#endif
XXXX int codemod_cnt;

#if 0
// EMP moved to PNO
XXXX int view_cnt;
#endif

XXXX int dbCnt;
#endif

// EMP 092503 Added
#ifndef ARM
typedef void opCodeFunc();
extern opCodeFunc *  PNO(op_func)[256];
#else
#endif


// EMP 092403 Changed for PACE
#if 1
XXXX struct dataelem
{
    // begin swap SwapDataElem
    UInt16 length;
    Int16 dgt_bef;
    Int16 dgt_aft;
    UInt16 cur_no_values;
    UInt16 max_no_values1;
    UInt16 max_no_values2;
    UInt16 max_no_values3;
    UInt16 tbl_no;
    UInt16 firstData;
    // end swap
    char kind;
	 /* yes d=date yyyymmdd                         */
	 /* yes t=time hhmmss                           */
	 /* yes i=integer                               */
	 /* yes n=number with decimals                  */
	 /* not implemented  $=dollars with $ and ,'s                */
	 /* not implemented  c=dollars and cents with $ and ,'s      */
	 /* yes s=string of char's(text)                */

    char flags;      //80 = char (1-byte string)
                     // This is actually byteFlags from IDE
                     // i:
                     //    0x80 Int32
                     //    0x10 Int16
                     // n:
                     //    0x40 float/double
                     //    0x20 single
                     // s:
                     //    0x00 C-string
                     //    0x80 single-byte string (char?)
    //char unused;  //to word align
    char flags2;    // 02/20/2001 MMD
    //06012002char isConstant;  //01 = a literal or constant
    char flags3;                                      //06012002
    				// 0x01 = isConstant              //06012002
    				// 0x80 = memory allocated on heap          //06012002 
} de_example;
#else
XXXX struct dataelem
{
    unsigned int length;
    int dgt_bef;
    int dgt_aft;

    unsigned int cur_no_values;
    unsigned int max_no_values1;
    unsigned int max_no_values2;
    unsigned int max_no_values3;
    unsigned int tbl_no;        /* sep assigned seq # */
    unsigned int firstData;
    char kind;
	 /* yes d=date yyyymmdd                         */
	 /* yes t=time hhmmss                           */
	 /* yes i=integer                               */
	 /* yes n=number with decimals                  */
	 /* not implemented  $=dollars with $ and ,'s                */
	 /* not implemented  c=dollars and cents with $ and ,'s      */
	 /* yes s=string of char's(text)                */

    char flags;      //80 = char (1-byte string)
                     // This is actually byteFlags from IDE
                     // i:
                     //    0x80 Int32
                     //    0x10 Int16
                     // n:
                     //    0x40 float/double
                     //    0x20 single
                     // s:
                     //    0x00 C-string
                     //    0x80 single-byte string (char?)
    //char unused;  //to word align
    char flags2;    // 02/20/2001 MMD
    //06012002char isConstant;  //01 = a literal or constant
    char flags3;                                      //06012002
    				// 0x01 = isConstant              //06012002
    				// 0x80 = memory allocated on heap          //06012002 
} de_example;
//06012002#define DELEN ((ULong)&de_example.isConstant)-((ULong)&de_example)+1
#endif
#ifdef __MC68K__
#define DELEN ((ULong)&de_example.flags3)-((ULong)&de_example)+1
XXXX struct dataelem *data;
XXXX struct dataelem *data2;
XXXX struct dataelem *data3;

struct para_perf_tbl {
     unsigned int           return_offset;
     struct para_perf_tbl * next;
     char   type;               /*switch */
				/* 0=perf a thru b  */
				/* 2=perf until     */
				/* 3=perf varying   */
     struct dataelem *vary_var[3]; /*variable to vary  */
     struct dataelem *from_var[3]; /*vary from value   */
     struct dataelem *by_var[3];   /*vary by   value   */
     char *   vary_var_ad[3];
     char *   from_var_ad[3];
     char *   by_var_ad[3];
     char *   logic_ptr[3];        /* ptr to until code */
     unsigned int    logic_var_no[3];     /* ptr to logic var set by until cd*/
     int    times_max;          /* max times to perform */
     int    times_cnt;          /* # times performed */
     int    vsub_save;           /*save of subscript to perf lvl*/
};
XXXX struct para_perf_tbl *perf;

struct object_record
{
    struct object_record * prev;
    struct object_record * next;
    unsigned int pgm_script;
    char *       obj_code;
    unsigned     obj_code_len;
    void*        obj_code_offset;
    char         obj_id;  /*type of object in object chain*/
    int          orig_x;
    int          orig_y;
    int          no_x;
    int          no_y;
    int          ident;
    unsigned int seq;
    int          bkgrnd_color;
    int          color;
} ;

XXXX struct object_record * obj;
XXXX struct object_record * obj2;
XXXX struct object_record * obj3;
XXXX struct object_record * o;

typedef struct view_record
{
    struct view_record * prev;
    struct view_record * next;
    char         title[31];
    unsigned int seq;
    int          pane_bkgrnd_color; /*default for panes */
    int          pane_content_color; /*default for panes */
    struct view_record * from_view; /*view that triggerred this pane*/
    int   orig_x;  /*start location*/
    int   orig_y;  /*start location*/
    int   no_x; /*# of horiz pixels*/
    int   no_y; /*# of vert  pixels*/
    char  type; /* ?used?*/
	      
    struct object_record *first_object;
    unsigned int          pgm_script;    /*script to exec at beginning of view*/
    char *                obj_code;  /* and its compiled code*/
    unsigned              obj_code_len;
    void*                 obj_code_offset;
    //int                   cache_alloc_handle;  /*cache buffer # to start storage of obj's at*/
    //unsigned char         cache_modified_sw; /*0x00=yes,0x01=no*/
    void* null1;  /*unused*/
    void* null2;  /*unused*/
 } vw_example;
XXXX struct view_record * vw;
XXXX struct view_record * view;
XXXX struct view_record * view2;
XXXX struct view_record * view3;
XXXX struct view_record * old_view;

struct model_record
{
    struct model_record * prev;
    struct model_record * * next;

    char         name[31];
    unsigned int seq;
    char         filename[9];
    struct dataelem *    first_data;
    struct view_record * first_view;
    char         owner[31];
    
};

XXXX struct model_record *model;
XXXX struct model_record *model2;
XXXX struct model_record *model3;

XXXX void *           null_ptr;
#endif


#pragma options align=mac68k

XXXX struct
{
#pragma options align=mac68k4byte
#pragma align_array_members on
    Arg allArgs[6];
}aac;
#pragma align_array_members off
#pragma options align=mac68k


XXXX UInt16 crap;


#ifdef __MC68K__
#define arg1        (aac.allArgs[0].dataElem)
#define arg1_val    (aac.allArgs[0].val)
#define arg1_occ1   (aac.allArgs[0].occ1)
#define arg1_occ2   (aac.allArgs[0].occ2)
#define arg1_occ3   (aac.allArgs[0].occ3)
#define arg1_sde1   (aac.allArgs[0].sde1)
#define arg1_sde2   (aac.allArgs[0].sde2)
#define arg1_sde3   (aac.allArgs[0].sde3)
#endif

#ifdef __MC68K__
#define arg2        (aac.allArgs[1].dataElem)
#define arg2_val    (aac.allArgs[1].val)
#define arg2_occ1   (aac.allArgs[1].occ1)
#define arg2_occ2   (aac.allArgs[1].occ2)
#define arg2_occ3   (aac.allArgs[1].occ3)
#define arg2_sde1   (aac.allArgs[1].sde1)
#define arg2_sde2   (aac.allArgs[1].sde2)
#define arg2_sde3   (aac.allArgs[1].sde3)
#endif

#ifdef __MC68K__
#define arg3        (aac.allArgs[2].dataElem)
#define arg3_val    (aac.allArgs[2].val)
#define arg3_occ1   (aac.allArgs[2].occ1)
#define arg3_occ2   (aac.allArgs[2].occ2)
#define arg3_occ3   (aac.allArgs[2].occ3)
#define arg3_sde1   (aac.allArgs[2].sde1)
#define arg3_sde2   (aac.allArgs[2].sde2)
#define arg3_sde3   (aac.allArgs[2].sde3)
#endif

#ifdef __MC68K__
#define arg4        (aac.allArgs[3].dataElem)
#define arg4_val    (aac.allArgs[3].val)
#define arg4_occ1   (aac.allArgs[3].occ1)
#define arg4_occ2   (aac.allArgs[3].occ2)
#define arg4_occ3   (aac.allArgs[3].occ3)
#define arg4_sde1   (aac.allArgs[3].sde1)
#define arg4_sde2   (aac.allArgs[3].sde2)
#define arg4_sde3   (aac.allArgs[3].sde3)
#endif

#ifdef __MC68K__
#define arg5        (aac.allArgs[4].dataElem)
#define arg5_val    (aac.allArgs[4].val)
#define arg5_occ1   (aac.allArgs[4].occ1)
#define arg5_occ2   (aac.allArgs[4].occ2)
#define arg5_occ3   (aac.allArgs[4].occ3)
#define arg5_sde1   (aac.allArgs[4].sde1)
#define arg5_sde2   (aac.allArgs[4].sde2)
#define arg5_sde3   (aac.allArgs[4].sde3)
#endif

#ifdef __MC68K__
#define arg6        (aac.allArgs[5].dataElem)
#define arg6_val    (aac.allArgs[5].val)
#define arg6_occ1   (aac.allArgs[5].occ1)
#define arg6_occ2   (aac.allArgs[5].occ2)
#define arg6_occ3   (aac.allArgs[5].occ3)
#define arg6_sde1   (aac.allArgs[5].sde1)
#define arg6_sde2   (aac.allArgs[5].sde2)
#define arg6_sde3   (aac.allArgs[5].sde3)
#endif

#ifdef __MC68K__
XXXX int  arith_work_de_max ;
XXXX int  first_arith_work;
XXXX char master_quit_sw;
XXXX int  init_first_time;
#ifndef ARM
XXXX Int16  logic_value;  // EMP moved to PNO 092603
#endif
XXXX char stop_op_code ;
XXXX int  debug_sw;
XXXX UInt16 logic_var[128];    //EMP pointed to from PNO
XXXX double reg_a;      // EMP moved to PMO 092703
XXXX double reg_b;
XXXX double reg_c;
XXXX int size_error_switch;
XXXX unsigned int cur_module_id;      //added 04012005
XXXX int msgCount;                    //added 04012005
XXXX int string_work_de_max ;  
XXXX int first_string_work;

XXXX void load_reg(double* r1,struct dataelem* de,double* elem_ad) ;
XXXX void store_reg(double *r1,struct dataelem* de, double*elem_ad,
     unsigned int elem_occ1,unsigned int  elem_occ2,unsigned int  elem_occ3)   ;     /*-------store reg to data elem---*/
XXXX void round_reg(double *reg,struct dataelem* de)   ;

XXXX int   con0;
XXXX Int16   con1;  // EMP no more ints

XXXX char* paraListPtr;
XXXX char* vwListPtr;

// EMP moved to shared PNO struct
#if 0
XXXX char *deListPtr;
#endif

XXXX VoidHand paraListHand;
XXXX VoidHand vwListHand;

XXXX VoidHand deListHand;


XXXX VoidHand hPara;
#if 0
// EMP unused
XXXX int      funcNoParams;
#endif
#ifndef ARM
XXXX char*    paragTbl;
#endif
#if 0
// EMP moved to PNO
XXXX  UInt16    frmNo;
XXXX Int16    currentX;
XXXX Int16    currentY;
XXXX UInt16  penDown;
#endif
#if 0
// EMP moved to PNO
XXXX Boolean  msgboxOrAlertUp;
XXXX Boolean  ignoreNextPenup;
#endif

#endif

struct DrawWinStruct 
{
   Handle next;
   Handle nameHandle;
   WinHandle win;
   WinHandle prevWin;
} ;

#if 0
// EMP moved to pno
XXXX Handle winRoot;
#endif

#ifdef __MC68K__
//the memBlock structure is used in debugging memory leak problems
//a memBlock structure is allocated each time memory is allocated and destroyed when memory freed
 struct memBlock
 {
        struct memBlock* prev;     //prev memblock in debug chain
        struct memBlock * next;    //next memblock in debug chain
        VoidHand   handle;  //handle of mem allocated 
        VoidPtr    ptr;       //ptr to mem 
        ULong      lockCnt; //count of how many times locked 
        char *     who;     //string to identify who allocated this mem block
    } ;
XXXX struct memBlock sampleMemBlock;
XXXX struct memBlock  * memDebugFirst;  //ptr to first memblock in the memory debug chain
XXXX int memDebugSw;  
#define _MEM_DEBUG_SW 0


XXXX int  underway;
#if 0
// EMP moved to PNO
XXXX char lastKeyString[2];
XXXX UInt16  PNO(lastKeyDownKeyCode);
XXXX WChar	 PNO(lastKeyDownChr);
XXXX UInt16  PNO(lastKeyDownModifiers);
#endif
#if 0
// EMP moved to PNO
XXXX Int16  eventHandled;
XXXX Int16  eventType;
#endif

XXXX Boolean pendingFormUpdateEventSw;                       //09192004
XXXX int sigCaptureCtlId;   //id of gadget control to capture signature on
XXXX int sigCaptureFormId;  //id of form that ctl is on
XXXX Boolean sigCaptureSw;  // true=capture pen movements

#if 0
// EMP moved to shared PNO
XXXX VoidHand viewElems;   //handle to table of ViewData structures for all views
XXXX VoidPtr  viewElemsPtr;
#endif

#endif
//**************************************************************
//  structure for data maintained about each view(form) in an applic
//**************************************************************
struct ViewData
{
    VoidHand objectsHand;      //memory for an object table of all objects on this form
    VoidPtr  objectsPtr;
    Int16      id;               //id of this form 
    Int16      cnt;              //cnt of objects on this form
} ;

XXXX struct ViewData viewExample;

// EMP rearranged for PNO
//******************************************************************
//  structure for data maintained about each object on a view(form)
//******************************************************************
struct ObjectData
{
    VoidPtr     dataPtr;     //ptr to display data ( fld value, label, list of values, etc) 
	RectangleType origGridBounds;
    Int16       id;          //resource id of object
    Int16       type;        //the type of object
    Int16       numItems;    //(only for a lisbox) the number of items in the list
    //added 09242003
    Word frmId;            //form parent of object
    Int16 index;             //index of obj on form
    signed char   refreshFromDatabase;      //grid needs to be refreshed from database records
    signed char   bindToDbHasWhereClause;   //grid bound to db & where clause selects records
    ULong*    itemData;                 //user data field for each row of grid
    VoidPtr   colInfo;                  //parameters for each column of grid
    char**    gridContent;              //content of each cell of grid
                            //Note: may be a stng pointer for non-numeric columns
                            //or    a double ptr for a numeric column
     
    
    Int16      cols;                      //# of columns in the grid
    Int16      howManyColsInBind;         //# of columns that bind clause specified
    Int16      currentCol;               //column currently selected by user
    Int16      currentRow;               //row currently selected by user

    
    Int16      visibleRows;               //# of visible rows in the grid
    Int16      firstRow;                  //# of row displayed as 1st row in grid
    
    Int16       scrollMin;			//grid's scrollbar min value
    Int16       scrollMax;            //grid's scrollbar max value
    Int16       scrollPagesize;       //grid's scrollbar pagesize value
    
    Int16       dbNo;                   //db that supplies data to grid
    char   hidden;                //true if obj has been hidden
    //08152004 char filler;
    char  wantGridLines;                //08152004 'y'=yes, 'n'=no don't drawGrid
    Int16 filler2;		

};
XXXX struct ObjectData objectExample;
//added 09242003
// EMP rearranged for PNO
//*************************************************************************
//        Grid's Column Info
//*************************************************************************
struct gridColInfo
{
     char*        format;                   //chkbox prompt or numeric format string
                                       //or the text label to follow checkboxes if a checkbox column
     Int16         width;                    //width of this column  (pixels)    
     Int16          colNo;                     //column's number 0-based
     Int16          dbColNo;                  //column # of field in db that supplies values 
   
     char         type;            
                     //'c'  chkbox  
                     //'n'  numeric
                     //'s'  text string
                     //'d'  date
                     //'t'  time 
    char      dbSupplied;                //if col bound to db, data will be supplied by db reads
 
} ;
XXXX struct gridColInfo gridColInfoExample;
//end of additions 09242003


//additions 09242003
#ifndef ARM
XXXX char typeOfScript;  //type of code in process
#endif
                           //  a=after draw   , ,      
                           //  b=before draw                         ,  
                           //  c=form close
                           //  e=edit fld entered
                           //  f=edit fld text changed
                           //  i=initialization
                           //  m=menu  
                           //  t=tap
                           //  v=special event
                           //  o=on timer expiration  
                           //  s=scanner completion,
                           //  v=validation  
                           //  z=termination
//end of additions 09242003


// EMP rearranged for PNO
struct forStruct 
{
    double ToValue;
    double StepValue;
    long moduleCntr;
    //06102002VoidHand prevHandle;
    VoidPtr prevForPtr; 
    Int16   number;
} ;
#if 0
XXXX struct forStruct *forptr;  // EMP moved to PNO
#endif
XXXX struct forStruct *firstFor;