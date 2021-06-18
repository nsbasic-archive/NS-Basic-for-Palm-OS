#include "PACEInterfaceLib.h"
#include <size_t.h>
#include <cstddef>
#include <BigEndianTypes.h>
#include "PALMCompatibility.h"

#include "NSBPNOShared.h"
#include "copy.h"
#include "NSBPNOGlue.h"

#include "NSBPNOVerbs.h"

// Linker still looks for ARMlet_Main as entry point, but the
// "ARMlet" name is now officially discouraged.  Compare an
// contrast to "PilotMain" for 68K applications.
#define PNO_Main ARMlet_Main

// ------------------------
extern "C" Int32 strlen(const char *s)
{
    int retVal = 0;
    while (*s) {++retVal; ++s;};
    return retVal;
}

extern "C" char *strcpy(char *d, const char *s)
{
    while (*s) *d++ = *s++;
    *d = '\0';
    return d;
}

extern "C" char *strncpy(char *d, const char *s, Int16 ct)
{
    while (*s){
        if (ct <= 0) break;
        --ct;
        *d++ = *s++;
    }
    *d = '\0';
    return d;
}

extern "C" char *strcat(char *d, const char *s)
{
    char *d2 = d;
    while (*d2) ++d2;
    
    return strcpy(d2, s);
}

extern "C" char *strncat(char *d, const char *s, Int16 ct)
{
    char *d2 = d;
    while (*d2) ++d2;
    
    return strncpy(d2, s, ct);
}

extern "C" char *strchr(const char *s, Int16 c)
{
    char *s2 = (char *) s;
    while (*s2 != c)
    {
        if (!*s2) return NULL;
        ++s2;
    }
    return s2;
}

unsigned long asm getr10(void)
{
    mov         r0,r10
    bx          lr
}

unsigned long asm setr10(unsigned long x)
{
    stmfd       sp!,{r0-r3}
    ldr         r10,[sp,#0]
    mov         r0,r10
    add         sp,sp,#16
    bx          lr
}

extern "C"
unsigned long PNO_Main(
	const void *emulStateP, 
	PNOBlock *userData68KP, 
	Call68KFuncType *call68KFuncP);

extern "C" void RecurCall(PNOMC addr, const void *emulStateP, 
	PNOBlock *userData68KP, 
	Call68KFuncType *call68KFuncP)
{
    PNOMC addr2;
    addr2 = (PNOMC) /*__ARMlet_Take_Func_Addr__*/(addr);
    (*addr2)(emulStateP, userData68KP, call68KFuncP);
}

unsigned long PNO_Main(
	const void *emulStateP, 
	PNOBlock *pnoP, 
	Call68KFuncType *call68KFuncP)
{
    char cb[20];
    char *b;
    register unsigned short s;
    register unsigned long l;
    unsigned long retVal;
    
    if (!pnoP -> initByPNODB)
    {
        /* Initialize */
        int k;
        
        for (k = 0; k < 256; ++k)
        {
            pnoP -> op_func_PNODB[k] = 0;
        }

        pnoP -> op_func_PNODB[0x1c] = ((unsigned long) &verb_dbread) - BASIS;
        pnoP -> op_func_PNODB[0x1f] = ((unsigned long) &verb_dbgetnorecs) - BASIS;
        pnoP -> op_func_PNODB[0x23] = ((unsigned long) &verb_dbfind) - BASIS;
        pnoP -> op_func_PNODB[0x24] = ((unsigned long) &verb_dbread) - BASIS;
        pnoP -> op_func_PNODB[0x2c] = ((unsigned long) &verb_dbclose) - BASIS;
        pnoP -> op_func_PNODB[0x25] = ((unsigned long) &verb_dbupdate) - BASIS;
        pnoP -> op_func_PNODB[0x26] = ((unsigned long) &verb_dbdelete) - BASIS;
        pnoP -> op_func_PNODB[0x27] = ((unsigned long) &verb_dbinsert) - BASIS;
        pnoP -> op_func_PNODB[0x28] = ((unsigned long) &verb_dbreadnext) - BASIS;
        pnoP -> op_func_PNODB[0x29] = ((unsigned long) &verb_dberase) - BASIS;
        pnoP -> op_func_PNODB[0x2a] = ((unsigned long) &verb_dbcreate) - BASIS;
        pnoP -> op_func_PNODB[0x2b] = ((unsigned long) &verb_dbopen) - BASIS;
        pnoP -> op_func_PNODB[0x2f] = ((unsigned long) &verb_dbposition) - BASIS;
        pnoP -> op_func_PNODB[0x49] = ((unsigned long) &verb_dbreadprev) - BASIS;
        pnoP -> op_func_PNODB[0x86] = ((unsigned long) &verb_dbputnew) - BASIS;
        pnoP -> op_func_PNODB[0x87] = ((unsigned long) &verb_dbgetnew) - BASIS;
        pnoP -> op_func_PNODB[0xdc] = ((unsigned long) &verb_dbreset) - BASIS;

        pnoP -> dbPNO = (PNOMC) /*__ARMlet_Take_Func_Addr__*/(PNO_Main);

        pnoP -> initByPNODB = -1;
        
        pnoP -> dbPNOr10 = getr10();
        
        return 0;
    }
    else
    {
        /* It's a request for a verb */
        Int32 offset;
        Int32 retVal;
        UInt32 oldr10;
        
        oldr10 = getr10();
        
        setr10(pnoP -> dbPNOr10);

		// needed before making any OS calls using the 
		// PACEInterface library
		InitPACEInterface(emulStateP, call68KFuncP);
	
        offset = pnoP -> op_func_PNODB[PNO(op_code)];

        if (offset)
        {
            VerbType verb;
            verb = (VerbType)/*__ARMlet_Take_Func_Addr__*/((void *) (offset + BASIS));
            (*verb)(pnoP);
            retVal = 1;
        }
        else
        {
            retVal = 0;
        }
        
        setr10(oldr10);
        
        return retVal;
    }
}

