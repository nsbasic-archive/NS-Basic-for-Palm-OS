#ifdef mainpgm
#define XXXX
#else
#define XXXX extern
#endif
#define DO_NOT_ALLOW_ACCESS_TO_INTERNALS_OF_STRUCTS

//inserted next few  statements 04012005
//To turn DEBUGGER off, comment out the next statement
//#define _DEBUGGER yes
//end additions 04012005


//#define    ORG_SWB        comment out if not StylusWareBasic
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
XXXX unsigned long romVersion;
XXXX int userFunctionSequentialNo;      //added 5.27.2000  seq no assigned to each nested user function call
XXXX ULong  rscTag;              //resource identifier used for code and other resource records
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

//XXXX void *op_func[256];
void * misc_get_mem(int size, char* who);

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

void * misc_get_mem(int size, char* who);

XXXX int work_de_max;
XXXX VoidPtr controlPtr;
XXXX UInt    controlid;
XXXX VoidHand  hData;
XXXX VoidHand  hView;
XXXX DmOpenRef VbRscDB;
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
//additions 09242003
XXXX char typeOfScript;  //type of code in process
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

XXXX VoidHand   perfHand;
XXXX WinHandle  DrawWin;
XXXX MenuBarPtr menuPtr;
XXXX UInt       menuId;
XXXX VoidHand   dbElems;
XXXX VoidPtr    dbElemsPtr;

// Structure definition moved from main.c
struct basc_pref     // 12/18/2000 MMD
{                    // 12/18/2000 MMD
   char name[32];    // 12/18/2000 MMD
   UInt cardNo;      // 12/18/2000 MMD
};                   // 12/18/2000 MMD


//added 09242003
//**************************************************************************
//     each field of a database record
//**************************************************************************
struct dbField
{
    
     int        tblNo;          //data element #
     int        colNo;    //# of column
     int        type;  //type data
#define dbFldTypeString    00
#define dbFldTypeLongInt   01                           
#define dbFldTypeDouble    02                           
#define dbFldTypeDate      03                            
#define dbFldTypeTime      04
#define dbFldTypeShortInt  05 
#define dbFldTypeSingle    06                           
#define dbFldTypeByte      07                           //  04=time
                            
     VoidHand   hName;    //name handle
     Boolean    keyFlag;  //true = fld is a db key field
   
};
XXXX struct dbField dbFldExample; 
  
//**************************************************************************
//     each   database  
//**************************************************************************
//end of additions 09242003

struct dbType
{
  char      openSw;
  UInt      LastDbRecordRead;
  DmOpenRef dm;
  UInt      cardno;
  LocalID   lid;
  VoidHand  curHand;
  UInt      offset;
  int       noFields;                //added 09242003
  struct dbField*  ptrFields;        //added 09242003
  VoidHand     hName;                   //added 09242003
  VoidHand     hCreator;  //string      //added 09242003 
  
  int          keyFldNo;      //added 02042004 
};
XXXX struct dbType db_example;
struct codeBlock
{
  UInt         id;
  struct codeBlock*      prevCodePtr;   //modified 04012005
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
  unsigned int cur_stmt_no;           //added 04012005 stmt# of calling program that called a sub/func
  unsigned int subFuncEntry_stmt_no;  //the sub stmt or func stmt no that was called
};
XXXX struct codeBlock sampleCodeBlock;
XXXX struct codeBlock *codeBlockPtr;

struct base_rec
{
  int def_screen_no;
  int de_cnt;
  int parag_cnt;
  int codemod_cnt;
  int view_cnt;
  int first_string_work;  /*neg #*/
  int string_wk_max;
  int first_arith_work; /*neg #*/
  int arith_wk_max;
  int dbCnt;
  int versionInteg;
  int versionFrac;
  int LitePro;
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
XXXX int de_cnt;
XXXX int parag_cnt;
XXXX int codemod_cnt;
XXXX int view_cnt;
XXXX int dbCnt;
XXXX unsigned int theCodeOffset;
XXXX UInt32 timerExpirationTime;      //in system ticks     08022005

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
XXXX struct dataelem *arg1;
XXXX char*            arg1_val;
XXXX unsigned int     arg1_occ1;
XXXX unsigned int     arg1_occ2;
XXXX unsigned int     arg1_occ3;
XXXX struct dataelem*     arg1_sde1;
XXXX struct dataelem*     arg1_sde2;
XXXX struct dataelem*     arg1_sde3;
 
XXXX struct dataelem *arg2;
XXXX char*            arg2_val;
XXXX unsigned int     arg2_occ1;
XXXX unsigned int     arg2_occ2;
XXXX unsigned int     arg2_occ3;
XXXX struct dataelem*     arg2_sde1;
XXXX struct dataelem*     arg2_sde2;
XXXX struct dataelem*     arg2_sde3;


XXXX struct dataelem *arg3;
XXXX char*            arg3_val;
XXXX unsigned int     arg3_occ1;
XXXX unsigned int     arg3_occ2;
XXXX unsigned int     arg3_occ3;
XXXX struct dataelem*     arg3_sde1;
XXXX struct dataelem*     arg3_sde2;
XXXX struct dataelem*     arg3_sde3;

XXXX struct dataelem *arg4;
XXXX char *           arg4_val;
XXXX unsigned int     arg4_occ1;
XXXX unsigned int     arg4_occ2;
XXXX unsigned int     arg4_occ3;
XXXX struct dataelem*     arg4_sde1;
XXXX struct dataelem*     arg4_sde2;
XXXX struct dataelem*     arg4_sde3;


XXXX struct dataelem *arg5;
XXXX char*            arg5_val;
XXXX unsigned int     arg5_occ1;
XXXX unsigned int     arg5_occ2;
XXXX unsigned int     arg5_occ3;
XXXX struct dataelem*     arg5_sde1;
XXXX struct dataelem*     arg5_sde2;
XXXX struct dataelem*     arg5_sde3;

XXXX struct dataelem *arg6;
XXXX char*            arg6_val;
XXXX unsigned int     arg6_occ1;
XXXX unsigned int     arg6_occ2;
XXXX unsigned int     arg6_occ3;
XXXX struct dataelem*     arg6_sde1;
XXXX struct dataelem*     arg6_sde2;
XXXX struct dataelem*     arg6_sde3;

XXXX int  arith_work_de_max ;
XXXX int  first_arith_work;
XXXX char master_quit_sw;
XXXX int  init_first_time;
XXXX int  logic_value;
XXXX char stop_op_code ;
XXXX int  debug_sw;
XXXX int  logic_var[128];    //??how many needed
XXXX unsigned int instr_ctr;
XXXX double reg_a;
XXXX double reg_b;
XXXX double reg_c;
XXXX int size_error_switch;
XXXX unsigned int cur_stmt_no;
XXXX unsigned int cur_module_id;      //added 04012005
XXXX int msgCount;                    //added 04012005
XXXX int string_work_de_max ;  
XXXX int first_string_work;

XXXX void load_reg(double* r1,struct dataelem* de,double* elem_ad) ;
XXXX void store_reg(double *r1,struct dataelem* de, double*elem_ad,
     unsigned int elem_occ1,unsigned int  elem_occ2,unsigned int  elem_occ3)   ;     /*-------store reg to data elem---*/
XXXX void round_reg(double *reg,struct dataelem* de)   ;

XXXX int   con0;
XXXX int   con1;

XXXX char* paraListPtr;
XXXX char* vwListPtr;
XXXX char *deListPtr;

XXXX VoidHand paraListHand;
XXXX VoidHand vwListHand;

XXXX VoidHand deListHand;


XXXX VoidHand hPara;
XXXX int      funcNoParams;
XXXX int      numberParas;
XXXX char*    paragTbl;
XXXX  UInt    frmNo;
XXXX SWord    currentX;
XXXX SWord    currentY;
XXXX Boolean  penDown;
XXXX Boolean  msgboxOrAlertUp;
XXXX Boolean  ignoreNextPenup;

XXXX char *   codePtr;               //09242003

struct DrawWinStruct 
{
   Handle next;
   Handle nameHandle;
   WinHandle win;
   WinHandle prevWin;
} ;
XXXX Handle winRoot;
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


XXXX char verbOrFunction;
XXXX int  underway;
XXXX char lastKeyString[2];
XXXX UInt16  lastKeyDownKeyCode;
XXXX WChar	 lastKeyDownChr;
XXXX UInt16  lastKeyDownModifiers;
XXXX int  eventHandled;
XXXX int  eventType;
XXXX Boolean pendingFormUpdateEventSw;                       //09192004
XXXX int sigCaptureCtlId;   //id of gadget control to capture signature on
XXXX int sigCaptureFormId;  //id of form that ctl is on
XXXX Boolean sigCaptureSw;  // true=capture pen movements

XXXX VoidHand viewElems;   //handle to table of ViewData structures for all views
XXXX VoidPtr  viewElemsPtr; 
//**************************************************************
//  structure for data maintained about each view(form) in an applic
//**************************************************************
struct ViewData
{
    VoidHand objectsHand;      //memory for an object table of all objects on this form
    VoidPtr  objectsPtr;
    int      id;               //id of this form 
    int      cnt;              //cnt of objects on this form
} ;
XXXX struct ViewData viewExample;
//******************************************************************
//  structure for data maintained about each object on a view(form)
//******************************************************************
struct ObjectData
{
    int id;                //resource id of object
    int       type;        //the type of object
    int       numItems;    //(only for a lisbox/grid) the number of items in the list
    VoidPtr   dataPtr;     //ptr to display data ( fld value, label, list of values, etc) 
    //added 09242003
    Word frmId;            //form parent of object
    int index;             //index of obj on form
    Boolean   refreshFromDatabase;      //grid needs to be refreshed from database records
    Boolean   bindToDbHasWhereClause;   //grid bound to db & where clause selects records
    ULong*    itemData;                 //user data field for each row of grid
    VoidPtr   colInfo;                  //parameters for each column of grid
    char**    gridContent;              //content of each cell of grid
                            //Note: may be a stng pointer for non-numeric columns
                            //or    a double ptr for a numeric column
     
    
    int      cols;                      //# of columns in the grid
    int      howManyColsInBind;         //# of columns that bind clause specified
    int      currentCol;               //column currently selected by user
    int      currentRow;               //row currently selected by user

    
    int      visibleRows;               //# of visible rows in the grid
    int      firstRow;                  //# of row displayed as 1st row in grid
    
    int       scrollMin;			//grid's scrollbar min value
    int       scrollMax;            //grid's scrollbar max value
    int       scrollPagesize;       //grid's scrollbar pagesize value
    
    int       dbNo;                   //db that supplies data to grid
    Boolean   hidden;                //true if obj has been hidden
    //08152004 char filler;
    char  wantGridLines;                //08152004 'y'=yes, 'n'=no don't drawGrid
    Int16 filler2;		
    //end of additions 09242003
    RectangleType origGridBounds;   //added 04232004 ldm to prevent colWidths from expanding grid width
    
} ;
XXXX struct ObjectData objectExample;
//added 09242003
//*************************************************************************
//        Grid's Column Info
//*************************************************************************
struct gridColInfo
{
     char*        format;                   //chkbox prompt or numeric format string
                                       //or the text label to follow checkboxes if a checkbox column
     int         width;                    //width of this column  (pixels)    
     int          colNo;                     //column's number 0-based
     int          dbColNo;                  //column # of field in db that supplies values 
   
     char         type;            
                     //'c'  chkbox  
                     //'n'  numeric
                     //'s'  text string
                     //'d'  date
                     //'t'  time 
    Boolean      dbSupplied;                //if col bound to db, data will be supplied by db reads
 
} ;
XXXX struct gridColInfo gridColInfoExample;
//end of additions 09242003
struct forStruct 
{
    long moduleCntr;
    double ToValue;
    double StepValue;
    int   number;
    //06102002VoidHand prevHandle;
    VoidPtr prevForPtr; 
} ;
XXXX struct forStruct *forptr;
XXXX struct forStruct *firstFor;