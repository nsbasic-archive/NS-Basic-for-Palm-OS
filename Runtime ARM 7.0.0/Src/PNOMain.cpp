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

// Original stationery application but using library interface
// rather than class-derived interface.

extern "C" int codeexec2(PNOBlock *pnoP, Word objId,unsigned long offset);


static unsigned long Run()
{
	// draw randomly-colored pixels on the screen
	for (Coord y = 16; y < 160; ++y)
	{
		for (Coord x = 0; x < 160; ++x)
		{
			RGBColorType RGB, prevRGB;
			RGB.index = 0;
			RGB.r = SysRandom(0) % 256;
			RGB.g = SysRandom(0) % 256;
			RGB.b = SysRandom(0) % 256;

			WinSetForeColorRGB(&RGB, &prevRGB);
			WinDrawPixel(x, y);
		}
	}

	return 0;
}
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

Int32 toad;

void bork()

{
	toad = 37;
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

long foo(unsigned long x)
{
	long y = 37;
	
	return x * y;
}

extern "C" Int16 executeSomeCode(PNOBlock *pnoP);

// ------------------------

extern "C"
unsigned long PNO_Main(
	const void *emulStateP, 
	PNOBlock *userData68KP, 
	Call68KFuncType *call68KFuncP);

unsigned long PNO_Main(
	const void *emulStateP, 
	PNOBlock *userData68KP, 
	Call68KFuncType *call68KFuncP)
{
    char cb[20];
    char *b;
    register unsigned short s;
    register unsigned long l;
    unsigned long retVal;
    
    userData68KP -> emulStateP = emulStateP;
    userData68KP -> call68KFuncP = (void *) call68KFuncP;

    if (!userData68KP -> initByPNO)
    {
        /* Initialize */
        int k;
        
        for (k = 0; k < 256; ++k)
        {
            userData68KP -> op_func_PNO[k] = 0;
        }

        userData68KP -> op_func_PNO[0x04] = ((unsigned long) &verb_add) - BASIS;
        userData68KP -> op_func_PNO[0x10] = ((unsigned long) &verb_gosub) - BASIS;
        userData68KP -> op_func_PNO[0x18] = ((unsigned long) &verb_stop) - BASIS;
        userData68KP -> op_func_PNO[0x07] = ((unsigned long) &verb_seteventhandled) - BASIS;
        userData68KP -> op_func_PNO[0x0a] = ((unsigned long) &verb_divide) - BASIS;
        userData68KP -> op_func_PNO[0x0c] = ((unsigned long) &verb_if) - BASIS;
        userData68KP -> op_func_PNO[0x0e] = ((unsigned long) &verb_multiply) - BASIS;
        userData68KP -> op_func_PNO[0x11] = ((unsigned long) &verb_call) - BASIS;
        userData68KP -> op_func_PNO[0x12] = ((unsigned long) &verb_sub) - BASIS;
        userData68KP -> op_func_PNO[0x13] = ((unsigned long) &verb_user_func) - BASIS;
        userData68KP -> op_func_PNO[0x1d] = ((unsigned long) &verb_return) - BASIS;
        userData68KP -> op_func_PNO[0x1e] = ((unsigned long) &verb_goto) - BASIS;
        userData68KP -> op_func_PNO[0x19] = ((unsigned long) &verb_initAVariableValue) - BASIS;
        userData68KP -> op_func_PNO[0x1a] = ((unsigned long) &verb_subtract) - BASIS;
        userData68KP -> op_func_PNO[0x1b] = ((unsigned long) &verb_negate) - BASIS;
        userData68KP -> op_func_PNO[0x20] = ((unsigned long) &verb_menuerase) - BASIS;
        userData68KP -> op_func_PNO[0x22] = ((unsigned long) &verb_menureset) - BASIS;
        userData68KP -> op_func_PNO[0x21] = ((unsigned long) &verb_menudraw) - BASIS;
        userData68KP -> op_func_PNO[0x3d] = ((unsigned long) &verb_assign_bitmap) - BASIS;
        userData68KP -> op_func_PNO[0x40] = ((unsigned long) &verb_createwindow) - BASIS;
        userData68KP -> op_func_PNO[0x41] = ((unsigned long) &verb_destroywindow) - BASIS;
        userData68KP -> op_func_PNO[0x42] = ((unsigned long) &verb_erasewindow) - BASIS;
        userData68KP -> op_func_PNO[0x43] = ((unsigned long) &verb_drawchars) - BASIS;
        userData68KP -> op_func_PNO[0x44] = ((unsigned long) &verb_drawline) - BASIS;
        userData68KP -> op_func_PNO[0x47] = ((unsigned long) &verb_setcurwindow) - BASIS;
        userData68KP -> op_func_PNO[0x48] = ((unsigned long) &verb_draw_bitmap) - BASIS;
        userData68KP -> op_func_PNO[0x4a] = ((unsigned long) &verb_delay) - BASIS;
        userData68KP -> op_func_PNO[0x4c] = ((unsigned long) &verb_getPen) - BASIS;
        userData68KP -> op_func_PNO[0x50] = ((unsigned long) &verb_exponentiation) - BASIS;
        userData68KP -> op_func_PNO[0x51] = ((unsigned long) &verb_not_logic_oper) - BASIS;
        userData68KP -> op_func_PNO[0x52] = ((unsigned long) &verb_relat_logic_oper) - BASIS;
        userData68KP -> op_func_PNO[0x53] = ((unsigned long) &verb_logic_class_tests) - BASIS;
        userData68KP -> op_func_PNO[0x54] = ((unsigned long) &verb_and) - BASIS;
        userData68KP -> op_func_PNO[0x55] = ((unsigned long) &verb_or) - BASIS;
        userData68KP -> op_func_PNO[0x57] = ((unsigned long) &verb_special_arith_store) - BASIS;
        userData68KP -> op_func_PNO[0x59] = ((unsigned long) &verb_compute) - BASIS;
        userData68KP -> op_func_PNO[0x5b] = ((unsigned long) &verb_clear_frac_dgts) - BASIS;
        userData68KP -> op_func_PNO[0x80] = ((unsigned long) &verb_nextscreen) - BASIS;
        userData68KP -> op_func_PNO[0x83] = ((unsigned long) &verb_nextscreenwithvariable) - BASIS;
        userData68KP -> op_func_PNO[0x84] = ((unsigned long) &verb_cursor_id) - BASIS;
        userData68KP -> op_func_PNO[0x85] = ((unsigned long) &verb_redraw_id) - BASIS;
        userData68KP -> op_func_PNO[0x90] = ((unsigned long) &verb_concat_two_strings) - BASIS;
        userData68KP -> op_func_PNO[0xa1] = ((unsigned long) &verb_startfor) - BASIS;
        userData68KP -> op_func_PNO[0xa2] = ((unsigned long) &verb_continuefor) - BASIS;
        userData68KP -> op_func_PNO[0xa3] = ((unsigned long) &verb_next) - BASIS;
        userData68KP -> op_func_PNO[0xa7] = ((unsigned long) &verb_do) - BASIS;
        userData68KP -> op_func_PNO[0xa8] = ((unsigned long) &verb_dountil) - BASIS;
        userData68KP -> op_func_PNO[0xa9] = ((unsigned long) &verb_dowhile) - BASIS;
        userData68KP -> op_func_PNO[0xaa] = ((unsigned long) &verb_loop) - BASIS;
        userData68KP -> op_func_PNO[0xab] = ((unsigned long) &verb_exitdo) - BASIS;
        userData68KP -> op_func_PNO[0xac] = ((unsigned long) &verb_exitfor) - BASIS;
        userData68KP -> op_func_PNO[0xc1] = ((unsigned long) &verb_alert) - BASIS;
        userData68KP -> op_func_PNO[0xc2] = ((unsigned long) &verb_start_function) - BASIS;
        userData68KP -> op_func_PNO[0xd2] = ((unsigned long) &verb_cursor) - BASIS;
        userData68KP -> op_func_PNO[0xd3] = ((unsigned long) &verb_errmsg) - BASIS;
        userData68KP -> op_func_PNO[0xdd] = ((unsigned long) &verb_end_logic_cond) - BASIS;
        userData68KP -> op_func_PNO[0xde] = ((unsigned long) &verb_function) - BASIS;
        userData68KP -> op_func_PNO[0xf0] = ((unsigned long) &verb_start_new_parag) - BASIS;
        userData68KP -> op_func_PNO[0xf1] = ((unsigned long) &verb_start_new_stmt) - BASIS;
        userData68KP -> op_func_PNO[0xf2] = ((unsigned long) &verb_preceedSubFunc) - BASIS;
        userData68KP -> op_func_PNO[0xf8] = ((unsigned long) &verb_end_sub) - BASIS;
        userData68KP -> op_func_PNO[0xf9] = ((unsigned long) &verb_end_function) - BASIS;
        userData68KP -> op_func_PNO[0xfd] = ((unsigned long) &verb_start_debug) - BASIS;
        userData68KP -> op_func_PNO[0xfe] = ((unsigned long) &verb_end_debug) - BASIS;

        userData68KP -> initByPNO = -1;
        
     	userData68KP -> mainPNOP = (PNOMC) /*__ARMlet_Take_Func_Addr__*/(PNO_Main);

        userData68KP -> mainPNOr10 = getr10();

        return 0;
    }

#if 0
    l = Glue_codeexec2(userData68KP);
#else
	if (userData68KP -> exCodeLevel)
	{
		UInt32 oldr10 = getr10();
		setr10(userData68KP -> mainPNOr10);
		// needed before making any OS calls using the 
		// PACEInterface library
		InitPACEInterface(emulStateP, call68KFuncP);
		l = executeSomeCode(userData68KP);
		setr10(oldr10);
	}
	else
	{
		// needed before making any OS calls using the 
		// PACEInterface library
		InitPACEInterface(emulStateP, call68KFuncP);
	    SwapUserData(userData68KP);
	    SwapCodeBlock(userData68KP -> codeBlockPtr);
	    {
	        Word objId;
	        unsigned long offset;
	        
	        objId = userData68KP -> objId;
	        objId = ByteSwap16(objId);
	        offset = userData68KP -> offset;
	        offset = ByteSwap32(offset);
	        l = codeexec2(userData68KP, objId, offset);
	    }
	    SwapCodeBlock(userData68KP -> codeBlockPtr);
	    SwapUserData(userData68KP);
	}
#endif

	return ByteSwap32(l);
}

