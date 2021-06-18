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
    	
    if (!pnoP -> initByPNOVerbs)
    {
        /* Initialize */
        int k;
        
        for (k = 0; k < 256; ++k)
        {
            pnoP -> op_func_PNOVerbs[k] = 0;
        }

        pnoP -> op_func_PNOVerbs[0x06] = ((unsigned long) &verb_popupclear) - BASIS;
        pnoP -> op_func_PNOVerbs[0x30] = ((unsigned long) &verb_controlsetstatus) - BASIS;
        pnoP -> op_func_PNOVerbs[0x31] = ((unsigned long) &verb_controlhideorshow) - BASIS;
        pnoP -> op_func_PNOVerbs[0x32] = ((unsigned long) &verb_fieldsettext) - BASIS;
        pnoP -> op_func_PNOVerbs[0x33] = ((unsigned long) &verb_fieldsetmaxchars) - BASIS;
        pnoP -> op_func_PNOVerbs[0x35] = ((unsigned long) &verb_listdeleteitem) - BASIS;
        pnoP -> op_func_PNOVerbs[0x36] = ((unsigned long) &verb_listsetselected) - BASIS;
        pnoP -> op_func_PNOVerbs[0x3b] = ((unsigned long) &verb_controlsetstatusNew) - BASIS;
        pnoP -> op_func_PNOVerbs[0x3e] = ((unsigned long) &verb_controlsetlabel) - BASIS;
        pnoP -> op_func_PNOVerbs[0x3f] = ((unsigned long) &verb_setscrollbar) - BASIS;
        pnoP -> op_func_PNOVerbs[0x34] = ((unsigned long) &verb_listadditem) - BASIS;
        pnoP -> op_func_PNOVerbs[0x4d] = ((unsigned long) &verb_listclear) - BASIS;
        pnoP -> op_func_PNOVerbs[0x81] = ((unsigned long) &verb_clearscreentextfields) - BASIS;
        //pnoP -> op_func_PNOVerbs[0x88] = ((unsigned long) &verb_generalVerb) - BASIS;
        //pnoP -> op_func_PNOVerbs[0x89] = ((unsigned long) &verb_setGeneralProperty) - BASIS;
        pnoP -> op_func_PNOVerbs[0x8a] = ((unsigned long) &verb_func_getGeneralPropertyNumeric) - BASIS;
        pnoP -> op_func_PNOVerbs[0x8b] = ((unsigned long) &verb_func_getGeneralPropertyString) - BASIS;

        pnoP -> verbPNO = (PNOMC) /*__ARMlet_Take_Func_Addr__*/(PNO_Main);

        pnoP -> initByPNOVerbs = -1;
        
        pnoP -> verbPNOr10 = getr10();
        
        return 0;
    }
    else
    {
        /* It's a request for a verb */
        Int32 offset;
        Int32 retVal;
        UInt32 oldr10;
        
        oldr10 = getr10();
        
        setr10(pnoP -> verbPNOr10);

		// needed before making any OS calls using the 
		// PACEInterface library
		InitPACEInterface(emulStateP, call68KFuncP);

        offset = pnoP -> op_func_PNOVerbs[PNO(op_code)];

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

