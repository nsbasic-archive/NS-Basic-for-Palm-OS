#define PALMOS_35_OR_HIGHER
#ifdef PALMOS_35_OR_HIGHER
#define PILOT_PRECOMPILED_HEADERS_OFF
#include <PalmOS.h>
#include <PalmCompatibility.h>
#else
#include <Pilot.h>
#include <SysAll.h>
#endif

#include "BLib.h"
#include "BLibPrv.h"

// Convenient macros for defining the dispatch table (below)
#define NFUNCS			67				// Number of entry points in library
#define SIZEOF_OFFSET		sizeof(Word)
#define SIZEOF_OFFSET_TABLE	((1+NFUNCS) * SIZEOF_OFFSET)	// for name, plus one per function
#define SIZEOF_JMP		4				// Memory model/platform dependent

#define LIBENTRY_OFFSET(x)	(SIZEOF_OFFSET_TABLE + x * SIZEOF_JMP)
#define LIBNAME_OFFSET		(SIZEOF_OFFSET_TABLE + NFUNCS * SIZEOF_JMP)



/* Main entry point of the library, automatically invoked by the
 * OS when the library is loaded.  Fills in the SysLibTblEntry
 * structure passed by the OS to publish the address of
 * our dispatch table.  This MUST be the first routine in
 * the code segment.  By naming it __Startup__, we sneakily
 * replace the normal startup code that Codewarrior would
 * usually insert for a regular application.  The only bad
 * part about this trick is that we have to put up with the
 * linker complaining about it; just ignore the error.
 */
Err __Startup__(UInt refnum, SysLibTblEntryPtr entryP) {
#pragma unused(refnum)
	// Install pointer to our dispatch table
	entryP->dispatchTblP = DispatchTable();
	
	// Initialize globals handle to zero until mathlib_open called
	entryP->globalsP = 0;
	
	return bErrNone;
}



/* Library dispatch table.  Offset of library name, followed
 * by offset of each function's jmp instruction, followed by
 * a jmp for each function, followed by the library name used
 * for SysLibFind() calls.
 */
asm Ptr *DispatchTable(void) 
{
	lea		table, a0
	rts

 table:
	dc.w	LIBNAME_OFFSET
	dc.w	LIBENTRY_OFFSET(0)	// Must start from 0
	dc.w	LIBENTRY_OFFSET(1)
	dc.w	LIBENTRY_OFFSET(2)
	dc.w	LIBENTRY_OFFSET(3)
	dc.w	LIBENTRY_OFFSET(4)
	dc.w	LIBENTRY_OFFSET(5)
	dc.w	LIBENTRY_OFFSET(6)
	dc.w	LIBENTRY_OFFSET(7)
	dc.w	LIBENTRY_OFFSET(8)
	dc.w	LIBENTRY_OFFSET(9)
	dc.w	LIBENTRY_OFFSET(10)
	dc.w	LIBENTRY_OFFSET(11)
	dc.w	LIBENTRY_OFFSET(12)
	dc.w	LIBENTRY_OFFSET(13)
	dc.w	LIBENTRY_OFFSET(14)
	dc.w	LIBENTRY_OFFSET(15)
	dc.w	LIBENTRY_OFFSET(16)
	dc.w	LIBENTRY_OFFSET(17)
	dc.w	LIBENTRY_OFFSET(18)
	dc.w	LIBENTRY_OFFSET(19)
	dc.w	LIBENTRY_OFFSET(20)
	dc.w	LIBENTRY_OFFSET(21)
	dc.w	LIBENTRY_OFFSET(22)
	dc.w	LIBENTRY_OFFSET(23)
	dc.w	LIBENTRY_OFFSET(24)
	dc.w	LIBENTRY_OFFSET(25)
	dc.w	LIBENTRY_OFFSET(26)
	dc.w	LIBENTRY_OFFSET(27)
	dc.w	LIBENTRY_OFFSET(28)
	dc.w	LIBENTRY_OFFSET(29)
	dc.w	LIBENTRY_OFFSET(30)
	dc.w	LIBENTRY_OFFSET(31)
	dc.w	LIBENTRY_OFFSET(32)
	dc.w	LIBENTRY_OFFSET(33)
	dc.w	LIBENTRY_OFFSET(34)
	dc.w	LIBENTRY_OFFSET(35)
	dc.w	LIBENTRY_OFFSET(36)
	dc.w	LIBENTRY_OFFSET(37)
	dc.w	LIBENTRY_OFFSET(38)
	dc.w	LIBENTRY_OFFSET(39)
	dc.w	LIBENTRY_OFFSET(40)
	dc.w	LIBENTRY_OFFSET(41)
	dc.w	LIBENTRY_OFFSET(42)
	dc.w	LIBENTRY_OFFSET(43)
	dc.w	LIBENTRY_OFFSET(44)
	dc.w	LIBENTRY_OFFSET(45)
	dc.w	LIBENTRY_OFFSET(46)
	dc.w	LIBENTRY_OFFSET(47)
	dc.w	LIBENTRY_OFFSET(48)
	dc.w	LIBENTRY_OFFSET(49)
	dc.w	LIBENTRY_OFFSET(50)
	dc.w	LIBENTRY_OFFSET(51)
	dc.w	LIBENTRY_OFFSET(52)
	dc.w	LIBENTRY_OFFSET(53)
	dc.w	LIBENTRY_OFFSET(54)
	dc.w	LIBENTRY_OFFSET(55)
	dc.w	LIBENTRY_OFFSET(56)
	dc.w	LIBENTRY_OFFSET(57)
	dc.w	LIBENTRY_OFFSET(58)
	dc.w	LIBENTRY_OFFSET(59)
	dc.w	LIBENTRY_OFFSET(60)
	dc.w	LIBENTRY_OFFSET(61)
	dc.w	LIBENTRY_OFFSET(62)
	dc.w	LIBENTRY_OFFSET(63)
	dc.w	LIBENTRY_OFFSET(64)
	dc.w	LIBENTRY_OFFSET(65)
	dc.w	LIBENTRY_OFFSET(66)	// NFUNCS must equal this index + 1
	jmp		blib_open	// These must match the sequence in BLib.h
	jmp		blib_close
	jmp		blib_sleep
	jmp		blib_wake
	jmp		blib_orb
	jmp		blib_orw
	jmp		blib_ord
	jmp		blib_andb
	jmp		blib_andw
	jmp		blib_andd
	jmp		blib_xorb
	jmp		blib_xorw
	jmp		blib_xord
	jmp		blib_notb
	jmp		blib_notw
	jmp		blib_notd
	jmp		blib_swapw
	jmp		blib_swapd
	jmp		blib_swapdb
	jmp		blib_shiftb
	jmp		blib_shiftw
	jmp		blib_shiftd
	jmp		blib_sshiftb
	jmp		blib_sshiftw
	jmp		blib_sshiftd
	jmp		blib_cshiftb
	jmp		blib_cshiftw
	jmp		blib_cshiftd
	jmp		blib_getbitb
	jmp		blib_getbitw
	jmp		blib_getbitd
	jmp		blib_setbitb
	jmp		blib_setbitw
	jmp		blib_setbitd
	jmp		blib_resetbitb
	jmp		blib_resetbitw
	jmp		blib_resetbitd
	jmp		blib_inversebitb
	jmp		blib_inversebitw
	jmp		blib_inversebitd
	jmp		blib_eqvb
	jmp		blib_eqvw
	jmp		blib_eqvd
	jmp		blib_setloword
	jmp		blib_sethiword
	jmp		blib_setlobyte
	jmp		blib_sethibyte
	jmp		blib_getloword
	jmp		blib_gethiword
	jmp		blib_getlobyte
	jmp		blib_gethibyte
	jmp		blib_dec2hex
	jmp		blib_hex2dec
	jmp		blib_bin2dec
	jmp		blib_dec2bin
	jmp		blib_crc32
	jmp		blib_encdes
	jmp		blib_encmd4
	jmp		blib_encmd5
	jmp		blib_version
	jmp		blib_gethexstr
	jmp		blib_puthexstr
	jmp		blib_getbinstr
	jmp		blib_putbinstr
	jmp		blib_encryptDesString
	jmp		blib_decryptDesString
	jmp		blib_setDesKey
	dc.b	BLibName
}


/* Called by the application to validate the library's version number
 * and prepare it for use.
 */
Err blib_open(UInt refnum)
{
 SysLibTblEntryPtr entryP;
 VoidHand lh;
 BLibData *ld = NULL;

 //if (version > BLibVersion) return bErrOldVersion;

 // Get our global data handle from the OS			
 entryP = SysLibTblEntry(refnum);
 lh = (VoidHand)entryP->globalsP;
	
 // If we've already set up our globals, just increment the use count
 if (lh) 
 {
  ld = MemHandleLock(lh);
  ++ld->usecount;
 // Otherwise, allocate space for the globals and initialize them
 } else 
 {
  lh = MemHandleNew(sizeof(BLibData));
  if (!lh) return bErrNoMemory;
  entryP->globalsP = (void *)lh;
  ld = MemHandleLock(lh);
  MemPtrSetOwner(ld, 0);
  ld->usecount = 1;
  ld->src[0] = 0;
  ld->dst[0] = 0;
  ld->keys[0] = 0;
  ld->key[0] = NULL;
  ld->key[1] = NULL;
  ld->key[2] = NULL;
 }
 MemHandleUnlock(lh);
	
 return bErrNone;
}



/* Called by the application to release any resources used, and to
 * get the current use count to determine if SysLibRemove() should
 * be called.
 */

Err blib_close(UInt refnum)//, UIntPtr usecountP) 
{
 SysLibTblEntryPtr entryP;
 VoidHand lh;
 BLibData *ld;
 UInt usecount;
 	
 // Get our global data pointer from the OS			
 entryP = SysLibTblEntry(refnum);
 lh = (VoidHand)entryP->globalsP;
	
 // If globals aren't set up, we've haven't been opened yet
 if (!lh) return bErrNotOpen;

 // Decrement use count; if this makes it zero, free our globals		
 ld = MemHandleLock( lh);
 usecount = --ld->usecount;
 MemHandleUnlock(lh);
	
 if (!usecount) { MemHandleFree( lh);	entryP->globalsP = 0; }

 return bErrNone;
}

/* Called by OS when Pilot sleeps.  We don't care.*/
Err blib_sleep(UInt refnum)
{
#pragma unused(refnum)
 return bErrNone;
}

/* Called by OS when Pilot wakes.  We don't care.*/
Err blib_wake(UInt refnum) 
{
#pragma unused(refnum)
 return bErrNone;
}
