#include "PACEInterfaceLib.h"
#include <size_t.h>
#include <cstddef>
#include <BigEndianTypes.h>
#include "PALMCompatibility.h"

#include "NSBPNOShared.h"
#include "copy.h"
#include "NSBPNOGlue.h"

#include "NSBPNOFuncs.h"

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

    if (!(pnoP -> initByPNOFuncs))
    {
        /* Initialize */
        Int16 k;
        
        pnoP -> funcPNO = (PNOMC) /*__ARMlet_Take_Func_Addr__*/(PNO_Main);
        pnoP -> funcPNOr10 = getr10();

        for (k = 0; k < sizeof(PNO(func_table_PNO)) / sizeof(Int32); ++k)
        {
            PNO(func_table_PNO[k] = 0);
        }

        pnoP -> func_table_PNO[1] = ((unsigned long) &verb_func_abs) - BASIS;
        pnoP -> func_table_PNO[2] = ((unsigned long) &verb_func_int) - BASIS;
        pnoP -> func_table_PNO[3] = ((unsigned long) &verb_func_mod) - BASIS;
        pnoP -> func_table_PNO[4] = ((unsigned long) &verb_func_rand) - BASIS;
        pnoP -> func_table_PNO[5] = ((unsigned long) &verb_func_round) - BASIS;
        pnoP -> func_table_PNO[7] = ((unsigned long) &verb_func_power10) - BASIS;
        pnoP -> func_table_PNO[8] = ((unsigned long) &verb_func_chr) - BASIS;
        pnoP -> func_table_PNO[9] = ((unsigned long) &verb_func_format) - BASIS;
        pnoP -> func_table_PNO[11] = ((unsigned long) &verb_func_instr) - BASIS;
        pnoP -> func_table_PNO[12] = ((unsigned long) &verb_func_nooccurs) - BASIS;
        pnoP -> func_table_PNO[14] = ((unsigned long) &verb_func_ascii) - BASIS;
        pnoP -> func_table_PNO[15] = ((unsigned long) &verb_func_left) - BASIS;
        pnoP -> func_table_PNO[16] = ((unsigned long) &verb_func_right) - BASIS;
        pnoP -> func_table_PNO[17] = ((unsigned long) &verb_func_length) - BASIS;
        pnoP -> func_table_PNO[18] = ((unsigned long) &verb_func_lower) - BASIS;
        pnoP -> func_table_PNO[19] = ((unsigned long) &verb_func_mid) - BASIS;
        pnoP -> func_table_PNO[20] = ((unsigned long) &verb_func_testnum) - BASIS;
        pnoP -> func_table_PNO[21] = ((unsigned long) &verb_func_tostring) - BASIS;
        pnoP -> func_table_PNO[22] = ((unsigned long) &verb_func_proper) - BASIS;
        pnoP -> func_table_PNO[23] = ((unsigned long) &verb_func_upper) - BASIS;  
        pnoP -> func_table_PNO[24] = ((unsigned long) &verb_func_tonumber) - BASIS;
        pnoP -> func_table_PNO[25] = ((unsigned long) &verb_func_todate) - BASIS;
        pnoP -> func_table_PNO[26] = ((unsigned long) &verb_func_totime) - BASIS;
        pnoP -> func_table_PNO[27] = ((unsigned long) &verb_func_date) - BASIS;
        pnoP -> func_table_PNO[28] = ((unsigned long) &verb_func_mmddyytodate) - BASIS;
        pnoP -> func_table_PNO[29] = ((unsigned long) &verb_func_time) - BASIS;
        pnoP -> func_table_PNO[31] = ((unsigned long) &verb_func_day) - BASIS;
        pnoP -> func_table_PNO[32] = ((unsigned long) &verb_func_hour) - BASIS;
        pnoP -> func_table_PNO[33] = ((unsigned long) &verb_func_minute) - BASIS;
        pnoP -> func_table_PNO[34] = ((unsigned long) &verb_func_second) - BASIS;
        pnoP -> func_table_PNO[35] = ((unsigned long) &verb_func_month) - BASIS;
        pnoP -> func_table_PNO[36] = ((unsigned long) &verb_func_year) - BASIS;
        pnoP -> func_table_PNO[37] = ((unsigned long) &verb_func_dayofweek) - BASIS;
        pnoP -> func_table_PNO[38] = ((unsigned long) &verb_func_dayofyear) - BASIS;
        pnoP -> func_table_PNO[44] = ((unsigned long) &verb_func_ceiling) - BASIS;
        pnoP -> func_table_PNO[45] = ((unsigned long) &verb_func_floor) - BASIS;
        pnoP -> func_table_PNO[47] = ((unsigned long) &verb_func_sign) - BASIS;
        pnoP -> func_table_PNO[48] = ((unsigned long) &verb_func_trunc) - BASIS;
        pnoP -> func_table_PNO[49] = ((unsigned long) &verb_func_leftpad) - BASIS;
        pnoP -> func_table_PNO[50] = ((unsigned long) &verb_func_rightpad) - BASIS;
        pnoP -> func_table_PNO[51] = ((unsigned long) &verb_func_adddays) - BASIS;
        pnoP -> func_table_PNO[52] = ((unsigned long) &verb_func_addmonths) - BASIS;
        pnoP -> func_table_PNO[53] = ((unsigned long) &verb_func_addyears) - BASIS;
        pnoP -> func_table_PNO[54] = ((unsigned long) &verb_func_firstofmonth) - BASIS;
        pnoP -> func_table_PNO[55] = ((unsigned long) &verb_func_lastofmonth) - BASIS;
        pnoP -> func_table_PNO[56] = ((unsigned long) &verb_func_sysdate) - BASIS;
        pnoP -> func_table_PNO[57] = ((unsigned long) &verb_func_systime) - BASIS;
        pnoP -> func_table_PNO[58] = ((unsigned long) &verb_func_datediff) - BASIS;
        pnoP -> func_table_PNO[59] = ((unsigned long) &verb_func_timediff) - BASIS;
        pnoP -> func_table_PNO[60] = ((unsigned long) &verb_func_yearmonth) - BASIS;
        pnoP -> func_table_PNO[61] = ((unsigned long) &verb_func_monthday) - BASIS;
        pnoP -> func_table_PNO[62] = ((unsigned long) &verb_func_hourmin) - BASIS;
        pnoP -> func_table_PNO[63] = ((unsigned long) &verb_func_hourminampm) - BASIS;
        pnoP -> func_table_PNO[64] = ((unsigned long) &verb_func_datemmddyy) - BASIS;
        pnoP -> func_table_PNO[65] = ((unsigned long) &verb_func_subtractdays) - BASIS;
        pnoP -> func_table_PNO[66] = ((unsigned long) &verb_func_subtractmonths) - BASIS;
        pnoP -> func_table_PNO[67] = ((unsigned long) &verb_func_subtractyears) - BASIS;
        // pnoP -> func_table_PNO[68] = ((unsigned long) &verb_func_popupdate) - BASIS;
        // pnoP -> func_table_PNO[69] = ((unsigned long) &verb_func_popuptime) - BASIS;
        pnoP -> func_table_PNO[70] = ((unsigned long) &verb_func_degtoradians) - BASIS;
        pnoP -> func_table_PNO[71] = ((unsigned long) &verb_func_radtodegrees) - BASIS;
        pnoP -> func_table_PNO[75] = ((unsigned long) &verb_func_controlscount) - BASIS;
        pnoP -> func_table_PNO[80] = ((unsigned long) &verb_func_rtrim) - BASIS;
        pnoP -> func_table_PNO[81] = ((unsigned long) &verb_func_ltrim) - BASIS;
        pnoP -> func_table_PNO[82] = ((unsigned long) &verb_func_trim) - BASIS;
        // pnoP -> func_table_PNO[83] = ((unsigned long) &verb_func_syseventavailable) - BASIS;
        pnoP -> func_table_PNO[84] = ((unsigned long) &verb_func_getkey) - BASIS;
        pnoP -> func_table_PNO[86] = ((unsigned long) &verb_func_geteventtype) - BASIS;
        // pnoP -> func_table_PNO[87] = ((unsigned long) &verb_func_sysinfo) - BASIS;
        pnoP -> func_table_PNO[89] = ((unsigned long) &verb_func_getversion) - BASIS;
        pnoP -> func_table_PNO[400] = ((unsigned long) &func_controlgetstatus) - BASIS;
        pnoP -> func_table_PNO[401] = ((unsigned long) &func_fieldgettext) - BASIS;
        pnoP -> func_table_PNO[402] = ((unsigned long) &func_listgetnoitems) - BASIS;
        pnoP -> func_table_PNO[403] = ((unsigned long) &func_listgetselecteditemno) - BASIS;
        pnoP -> func_table_PNO[404] = ((unsigned long) &func_listgetitemtext) - BASIS;
        pnoP -> func_table_PNO[409] = ((unsigned long) &func_controlgetID) - BASIS;
        pnoP -> func_table_PNO[412] = ((unsigned long) &func_listgetnoitems) - BASIS;
        pnoP -> func_table_PNO[413] = ((unsigned long) &func_listgetselecteditemno) - BASIS;
        pnoP -> func_table_PNO[414] = ((unsigned long) &func_listgetitemtext) - BASIS;
        pnoP -> func_table_PNO[415] = ((unsigned long) &func_scrollbargetcurrent) - BASIS;
        pnoP -> func_table_PNO[416] = ((unsigned long) &func_listgetitemtext) - BASIS;
        pnoP -> func_table_PNO[417] = ((unsigned long) &func_controlgettext) - BASIS;
        pnoP -> func_table_PNO[500] = ((unsigned long) &func_acos) - BASIS;
        pnoP -> func_table_PNO[501] = ((unsigned long) &func_asin) - BASIS;
        pnoP -> func_table_PNO[502] = ((unsigned long) &func_atan) - BASIS;
        pnoP -> func_table_PNO[503] = ((unsigned long) &func_atan2) - BASIS;
        pnoP -> func_table_PNO[504] = ((unsigned long) &func_cos) - BASIS;
        pnoP -> func_table_PNO[505] = ((unsigned long) &func_sin) - BASIS;
        pnoP -> func_table_PNO[506] = ((unsigned long) &func_tan) - BASIS;
        pnoP -> func_table_PNO[508] = ((unsigned long) &func_cosh) - BASIS;
        pnoP -> func_table_PNO[509] = ((unsigned long) &func_sinh) - BASIS;
        pnoP -> func_table_PNO[510] = ((unsigned long) &func_tanh) - BASIS;
        pnoP -> func_table_PNO[511] = ((unsigned long) &func_acosh) - BASIS;
        pnoP -> func_table_PNO[512] = ((unsigned long) &func_asinh) - BASIS;
        pnoP -> func_table_PNO[513] = ((unsigned long) &func_atanh) - BASIS;
        pnoP -> func_table_PNO[514] = ((unsigned long) &func_exp) - BASIS;
        pnoP -> func_table_PNO[515] = ((unsigned long) &func_log) - BASIS;
        pnoP -> func_table_PNO[516] = ((unsigned long) &func_log10) - BASIS;
        pnoP -> func_table_PNO[517] = ((unsigned long) &func_cbrt) - BASIS;
        pnoP -> func_table_PNO[518] = ((unsigned long) &func_rem) - BASIS;
        pnoP -> func_table_PNO[519] = ((unsigned long) &func_pow) - BASIS;
        pnoP -> func_table_PNO[520] = ((unsigned long) &func_sqrt) - BASIS;

        pnoP -> initByPNOFuncs = -1;
        return 0;
    }
    else
    {
        /* It's a request for a func */
        Int32 offset;
        Int32 retVal;
        UInt32 oldr10;
       	
        oldr10 = getr10();
        
        setr10(pnoP -> funcPNOr10);
		
		// needed before making any OS calls using the 
		// PACEInterface library
		InitPACEInterface(emulStateP, call68KFuncP);

		if (PNO(it) <= 520)
		{
	        offset = pnoP -> func_table_PNO[PNO(it)];

	        if (offset)
	        {
	            VerbType verb;
	            verb = (VerbType)/*__ARMlet_Take_Func_Addr__*/((void *) (offset + BASIS));

	            (*verb)(pnoP);

	            retVal = -1;
	        }
	        else
	        {
	            retVal = 0;
	        }
		}
		else
		{
			retVal = 0;
		}
        setr10(oldr10);
        return retVal;
    }
}

