#ifndef PILOT_PRECOMPILED_HEADERS_OFF
#define	PILOT_PRECOMPILED_HEADERS_OFF
#endif


#if __PALMOS_TRAPS__
	#define EMULATION_LEVEL	EMULATION_NONE
#endif

#undef __PALMOS_TRAPS__
#define __PALMOS_TRAPS__ 	0
#define	USE_TRAPS 	0


// Include Pilot headers
#include <PalmOS.h>


// Our library public definitions (library API)
#include "ScreenLib.h"


#if EMULATION_LEVEL == EMULATION_NONE
	#define THIS_LibInstall		__Startup__
#endif


// Local prototypes

Err THIS_LibInstall(UInt16 refNum, SysLibTblEntryPtr entryP);
static MemPtr	asm THIS_LibDispatchTable(void);



/************************************************************
 *               T H I S _ L i b I n s t a l l
 ***********************************************************/
Err THIS_LibInstall(UInt16 refNum, SysLibTblEntryPtr entryP) {
	entryP->dispatchTblP = (MemPtr*)THIS_LibDispatchTable();
	entryP->globalsP = 0;
	return 0;
}


/************************************************************
 *          T H I S _ L i b D i s p a t c h T a b l e
 *
 *  WARNING!!! 	This table must match the ordering of the
 *      		library's trap numbers!
 ***********************************************************/

// First, define the size of the jump instruction
#if EMULATION_LEVEL == EMULATION_NONE
	#define prvJmpSize		4	// Palm OS uses short jumps
#elif EMULATION_LEVEL == EMULATION_MAC
	#define prvJmpSize		6	// Our Mac builds use long jumps
#else
	#error unsupported emulation mode
#endif	// EMULATION_LEVEL...

// Now, define a macro for offset list entries
#define	kOffset		(2 * ((THIS_TrapLast - sysLibTrapCustom) + 5))
#define libDispatchEntry(index)		(kOffset+((index)*prvJmpSize))


static MemPtr	asm THIS_LibDispatchTable(void) {
	LEA     @Table, A0       // table ptr
	RTS                      // exit with it

@Table:
	// Offset to library name
	DC.W		@Name

	//
	// Library function dispatch entries:
	//
	// ***IMPORTANT***
	// The index parameters passed to the macro libDispatchEntry
	// must be numbered consecutively, beginning with zero.
	//

	// Standard traps
	DC.W		libDispatchEntry(0) // LibOpen
	DC.W		libDispatchEntry(1) // LibClose
	DC.W		libDispatchEntry(2) // LibSleep
	DC.W		libDispatchEntry(3) // LibWake

	// Start of the Custom traps

	DC.W		libDispatchEntry(4) // Version
	DC.W		libDispatchEntry(5) // CompileInfo
	DC.W		libDispatchEntry(6) // GetSupportedDepths
	DC.W		libDispatchEntry(7) // DepthSupported
	DC.W		libDispatchEntry(8) // ColorSupported
	DC.W		libDispatchEntry(9) // SetDepth
	DC.W		libDispatchEntry(10) // SetColor
	DC.W		libDispatchEntry(11) // SetWidth
	DC.W		libDispatchEntry(12) // SetHeight
	DC.W		libDispatchEntry(13) // SaveScreenMode
	DC.W		libDispatchEntry(14) // RestoreScreenMode
	DC.W		libDispatchEntry(15) // CurrentDepth
	DC.W		libDispatchEntry(16) // CurrentColor
	DC.W		libDispatchEntry(17) // CurrentWidth
	DC.W		libDispatchEntry(18) // CurrentHeight
	DC.W		libDispatchEntry(19) // SetToDefaults
	DC.W		libDispatchEntry(20) // DefaultDepth
	DC.W		libDispatchEntry(21) // DefaultColor
	DC.W		libDispatchEntry(22) // DefaultWidth
	DC.W		libDispatchEntry(23) // DefaultHeight
	DC.W		libDispatchEntry(24) // GetTableEntryIndex
	DC.W		libDispatchEntry(25) // GetTableEntryRGB
	DC.W		libDispatchEntry(26) // GetRGBIndex
	DC.W		libDispatchEntry(27) // GetRGBRed
	DC.W		libDispatchEntry(28) // GetRGBGreen
	DC.W		libDispatchEntry(29) // GetRGBBlue
	DC.W		libDispatchEntry(30) // SetTableEntryIndex
	DC.W		libDispatchEntry(31) // SetTableEntryRGB
	DC.W		libDispatchEntry(32) // BrightnessAdjust
	DC.W		libDispatchEntry(33) // ContrastAdjust
	DC.W		libDispatchEntry(34) // PickColorIndex
	DC.W		libDispatchEntry(35) // PickColorRGB
	DC.W		libDispatchEntry(36) // IndexToRGB
	DC.W		libDispatchEntry(37) // RGBToIndex
	DC.W		libDispatchEntry(38) // SetForeColor
	DC.W		libDispatchEntry(39) // SetBackColor
	DC.W		libDispatchEntry(40) // SetTextColor
	DC.W		libDispatchEntry(41) // DrawLine
	DC.W		libDispatchEntry(42) // DrawGrayLine
	DC.W		libDispatchEntry(43) // EraseLine
	DC.W		libDispatchEntry(44) // InvertLine
	DC.W		libDispatchEntry(45) // DrawPixel
	DC.W		libDispatchEntry(46) // ErasePixel
	DC.W		libDispatchEntry(47) // InvertPixel
	DC.W		libDispatchEntry(48) // GetPixel
	DC.W		libDispatchEntry(49) // ScreenLock
	DC.W		libDispatchEntry(50) // ScreenUnlock

// Standard library function handlers
@Goto0:		JMP 		THIS_LibOpen
@Goto1:		JMP 		THIS_LibClose
@Goto2:		JMP 		THIS_LibSleep
@Goto3:		JMP 		THIS_LibWake

// Custom library function handlers
@Goto4:		JMP 		THIS_Version
@Goto5:		JMP 		THIS_CompileInfo
@Goto6:		JMP 		THIS_GetSupportedDepths
@Goto7:		JMP 		THIS_DepthSupported
@Goto8:		JMP 		THIS_ColorSupported
@Goto9:		JMP 		THIS_SetDepth
@Goto10:	JMP 		THIS_SetColor
@Goto11:	JMP 		THIS_SetWidth
@Goto12:	JMP 		THIS_SetHeight
@Goto13:	JMP 		THIS_SaveScreenMode
@Goto14:	JMP 		THIS_RestoreScreenMode
@Goto15:	JMP 		THIS_CurrentDepth
@Goto16:	JMP 		THIS_CurrentColor
@Goto17:	JMP 		THIS_CurrentWidth
@Goto18:	JMP 		THIS_CurrentHeight
@Goto19:	JMP 		THIS_SetToDefaults
@Goto20:	JMP 		THIS_DefaultDepth
@Goto21:	JMP 		THIS_DefaultColor
@Goto22:	JMP 		THIS_DefaultWidth
@Goto23:	JMP 		THIS_DefaultHeight
@Goto24:	JMP 		THIS_GetTableEntryIndex
@Goto25:	JMP 		THIS_GetTableEntryRGB
@Goto26:	JMP 		THIS_GetRGBIndex
@Goto27:	JMP 		THIS_GetRGBRed
@Goto28:	JMP 		THIS_GetRGBGreen
@Goto29:	JMP 		THIS_GetRGBBlue
@Goto30:	JMP 		THIS_SetTableEntryIndex
@Goto31:	JMP 		THIS_SetTableEntryRGB
@Goto32:	JMP 		THIS_BrightnessAdjust
@Goto33:	JMP 		THIS_ContrastAdjust
@Goto34:	JMP 		THIS_PickColorIndex
@Goto35:	JMP 		THIS_PickColorRGB
@Goto36:	JMP 		THIS_IndexToRGB
@Goto37:	JMP 		THIS_RGBToIndex
@Goto38:	JMP 		THIS_SetForeColor
@Goto39:	JMP 		THIS_SetBackColor
@Goto40:	JMP 		THIS_SetTextColor
@Goto41:	JMP 		THIS_DrawLine
@Goto42:	JMP 		THIS_DrawGrayLine
@Goto43:	JMP 		THIS_EraseLine
@Goto44:	JMP 		THIS_InvertLine
@Goto45:	JMP 		THIS_DrawPixel
@Goto46:	JMP 		THIS_ErasePixel
@Goto47:	JMP 		THIS_InvertPixel
@Goto48:	JMP 		THIS_GetPixel
@Goto49:	JMP 		THIS_ScreenLock
@Goto50:	JMP 		THIS_ScreenUnlock


// This name identifies the library.  Apps can pass it to 
// SysLibFind() to check if the library is already installed.
@Name:		DC.B		THIS_LibName

}

