/**
    NSBPNOShared.h
    
    Global information to be shared
    between the 68K portion of NSBasic and the PNO.
    
    Should be included by both the 68K code and the PNO
    code.
    
    Eric Pepke Sep 20, 2003
  */

#ifndef PNOSHARED

#define PNOSHARED

#define ARM

#ifdef __cplusplus
#define CDECL extern "C"
#else
#define CDECL
#endif

#ifdef __MC68K__
#define ESTATE
#else
#define ESTATE ,emulStateP
#endif


/** EMP 092803
The args are going into an array of structs because
all these variables are just too unwieldy to pass 
around.  PNO will reference them.  Also, there are
defines for existing global variable code.  There
should be no performance hits for using them this 
way.*/

typedef struct
{
    struct dataelem *dataElem;
    char *val;
    struct dataelem *sde1, *sde2, *sde3;
    UInt16 occ1, occ2, occ3;
    UInt16 dume;
} Arg;

/* Needed for exchanging doubles */
typedef union
{
    double d;
    struct
    {
        unsigned long high;
        unsigned long low;
    } i;
} DoubleExchange;


/* Structure holding callbacks, parameters, global
   variables to be shares with PNO  Note that the Intel
   compiler will 4-byte align, so be careful.. */


struct pnoblock;
typedef void opCodeFunc();
typedef void opCodeFuncPNO(struct pnoblock *pnoP);
typedef unsigned long(*PNOMC)(const void *, 
    struct pnoblock *, void *);

typedef struct pnoblock
{
    Int16 initByPNO;
    char initByPNOVerbs;
    char initByPNODB;
    Int16 initByPNOFuncs;
    Int16 mathLibRefNum;

    /* PNO info */
    const void *emulStateP; 
	void *call68KFuncP;
	PNOMC mainPNOP;
	unsigned long mainPNOr10;
	
	/* The other PNOs */
	PNOMC verbPNO;
	unsigned long verbPNOr10;
	PNOMC funcPNO;
	unsigned long funcPNOr10;
	PNOMC dbPNO;
	unsigned long dbPNOr10;

    /* Needed 68K functions */
    void *database_compare;
    
    /* Callbacks */
    void *codeexec;
	void *setupADataelem;
	void *CtlGlueGetControlStyle;
	void *FrmGlueGetLabelFont;
	void *chkMathLibOpen;
	void *commonEndCapture;
	void *commonErase;
	void *commonStartCapture;
	void *commonSignatureDisplay;
	void *flpftoa;
	void *flpatof;
    void *function_doit_from_PNO;
    void *serialreceivecheck;
    void *wingetcoordinatesystem;
    void *datetodays;
    void *gridDrawCallback;

    /* Input arguments.  Keep 68K unless needed.*/
    unsigned long offset;
    unsigned short objId;
    char verb;   
    char debugTest;

    /* PNO-only global variables, keep ARM aligned */
    UInt16 nArgs;
    UInt16 it;
    Arg *args;
    
    /* Shared lobal variables. Convert on entry and exit */
    /* begin swap SwapUserData (comment for sud.pl) */
    struct codeBlock *codeBlockPtr;
    MemHandle h3;
    char *p3;
    long moduleCntr;
    char *paragTbl;
    char *codePtr;
    void * forPtrSave;
    struct forStruct *forptr;
    char *deListPtr;
    DmOpenRef VbRscDB;
    VoidPtr controlPtr;
    VoidHand viewElems;
    VoidPtr  viewElemsPtr;
    VoidPtr dbElemsPtr;
    UInt16 *logic_var;
    MenuBarPtr menuPtr;
    WinHandle  DrawWin;
    MemHandle winRoot;
    UInt32 romVersion;
    UInt16 work_de_max;
    Int16 userFunctionSequentialNo;
    Int16 applVersionInteg;
    Int16 controlID;
    UInt16 lastSubOrFunctionId;
    Int16 numberParas;
    UInt16 theCodeOffset;
    UInt16 instr_ctr;
    Int16 logic_value;
    UInt16 controlid;
    Int16 view_cnt;
    Int16 msgboxOrAlertUp;
    Int16 parag_cnt;
    Int16 currentX;
    Int16 currentY;
    Int16 penDown;
    Int16 fldToUpdate;
    Int16 eventHandled;
    Int16 eventType;
    Int16 ignoreNextPenup;
    UInt16 frmNo;
    Int16 debug_on;
    UInt16 lastKeyDownKeyCode;
    WChar lastKeyDownChr;
    UInt16 lastKeyDownModifiers;
    Int16 runtimeVersionInteg;
    UInt16 serRef;
    Int16 dbNo;
    Int16 cur_stmt_no;
    Int16 cur_module_id;
    /* end swap (comment for sud.pl) */
    char lastKeyString[2];
    char typeOfScript;	
    unsigned char gSerialState;
    UInt16 exCodeLevel;
    UInt16 dummy6;
     
    /* PNO-endian shared variables */
    VoidHand perfHand;

    /* PNO-only variables */
    opCodeFunc * op_func[256];
    Int32 op_func_PNO[256];
    Int32 op_func_PNOVerbs[256];
    Int32 op_func_PNODB[256];
    Int32 func_table_PNO[528];
    unsigned char op_code;
    unsigned char dumm3, dummy4, dummy5;
} PNOBlock;

#ifdef ARM
#define PNO(x) (pnoP -> x)
#else
#define PNO(x) x
#endif

#ifdef __MC68K__
#include <PCENativeCall.h>
#include <PNOLoader.h>


extern MemHandle mainPNOH;
extern PnoDescriptor mainPNOD;
#if 0
extern MemHandle blockForPNO;
#endif

#else
//CDECL void * __ARMlet_Take_Func_Addr__(void *f);
CDECL void SwapCodeBlock(struct codeBlock *pnoP);

CDECL Int32 strlen(const char *s);
CDECL char *strcpy(char *d, const char *s);
CDECL char *strncpy(char *d, const char *s, Int16 ct);
CDECL char *strcat(char *d, const char *s);
CDECL char *strncat(char *d, const char *s, Int16 ct);
CDECL char *strchr(const char *s, Int16 c);


#endif

extern PNOBlock *pnoP;

#endif