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
	UInt32 *p;
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
	p = &(ld -> crctt_32[0]);
	*p++ = 0x00000000L;
	*p++ = 0x77073096L;
	*p++ = 0xee0e612cL;
	*p++ = 0x990951baL;
	*p++ = 0x076dc419L;
	*p++ = 0x706af48fL;
	*p++ = 0xe963a535L;
	*p++ = 0x9e6495a3L;
	*p++ = 0x0edb8832L;
	*p++ = 0x79dcb8a4L;
	*p++ = 0xe0d5e91eL;
	*p++ = 0x97d2d988L;
	*p++ = 0x09b64c2bL;
	*p++ = 0x7eb17cbdL;
	*p++ = 0xe7b82d07L;
	*p++ = 0x90bf1d91L;
	*p++ = 0x1db71064L;
	*p++ = 0x6ab020f2L;
	*p++ = 0xf3b97148L;
	*p++ = 0x84be41deL;
	*p++ = 0x1adad47dL;
	*p++ = 0x6ddde4ebL;
	*p++ = 0xf4d4b551L;
	*p++ = 0x83d385c7L;
	*p++ = 0x136c9856L;
	*p++ = 0x646ba8c0L;
	*p++ = 0xfd62f97aL;
	*p++ = 0x8a65c9ecL;
	*p++ = 0x14015c4fL;
	*p++ = 0x63066cd9L;
	*p++ = 0xfa0f3d63L;
	*p++ = 0x8d080df5L;
	*p++ = 0x3b6e20c8L;
	*p++ = 0x4c69105eL;
	*p++ = 0xd56041e4L;
	*p++ = 0xa2677172L;
	*p++ = 0x3c03e4d1L;
	*p++ = 0x4b04d447L;
	*p++ = 0xd20d85fdL;
	*p++ = 0xa50ab56bL;
	*p++ = 0x35b5a8faL;
	*p++ = 0x42b2986cL;
	*p++ = 0xdbbbc9d6L;
	*p++ = 0xacbcf940L;
	*p++ = 0x32d86ce3L;
	*p++ = 0x45df5c75L;
	*p++ = 0xdcd60dcfL;
	*p++ = 0xabd13d59L;
	*p++ = 0x26d930acL;
	*p++ = 0x51de003aL;
	*p++ = 0xc8d75180L;
	*p++ = 0xbfd06116L;
	*p++ = 0x21b4f4b5L;
	*p++ = 0x56b3c423L;
	*p++ = 0xcfba9599L;
	*p++ = 0xb8bda50fL;
	*p++ = 0x2802b89eL;
	*p++ = 0x5f058808L;
	*p++ = 0xc60cd9b2L;
	*p++ = 0xb10be924L;
	*p++ = 0x2f6f7c87L;
	*p++ = 0x58684c11L;
	*p++ = 0xc1611dabL;
	*p++ = 0xb6662d3dL;
	*p++ = 0x76dc4190L;
	*p++ = 0x01db7106L;
	*p++ = 0x98d220bcL;
	*p++ = 0xefd5102aL;
	*p++ = 0x71b18589L;
	*p++ = 0x06b6b51fL;
	*p++ = 0x9fbfe4a5L;
	*p++ = 0xe8b8d433L;
	*p++ = 0x7807c9a2L;
	*p++ = 0x0f00f934L;
	*p++ = 0x9609a88eL;
	*p++ = 0xe10e9818L;
	*p++ = 0x7f6a0dbbL;
	*p++ = 0x086d3d2dL;
	*p++ = 0x91646c97L;
	*p++ = 0xe6635c01L;
	*p++ = 0x6b6b51f4L;
	*p++ = 0x1c6c6162L;
	*p++ = 0x856530d8L;
	*p++ = 0xf262004eL;
	*p++ = 0x6c0695edL;
	*p++ = 0x1b01a57bL;
	*p++ = 0x8208f4c1L;
	*p++ = 0xf50fc457L;
	*p++ = 0x65b0d9c6L;
	*p++ = 0x12b7e950L;
	*p++ = 0x8bbeb8eaL;
	*p++ = 0xfcb9887cL;
	*p++ = 0x62dd1ddfL;
	*p++ = 0x15da2d49L;
	*p++ = 0x8cd37cf3L;
	*p++ = 0xfbd44c65L;
	*p++ = 0x4db26158L;
	*p++ = 0x3ab551ceL;
	*p++ = 0xa3bc0074L;
	*p++ = 0xd4bb30e2L;
	*p++ = 0x4adfa541L;
	*p++ = 0x3dd895d7L;
	*p++ = 0xa4d1c46dL;
	*p++ = 0xd3d6f4fbL;
	*p++ = 0x4369e96aL;
	*p++ = 0x346ed9fcL;
	*p++ = 0xad678846L;
	*p++ = 0xda60b8d0L;
	*p++ = 0x44042d73L;
	*p++ = 0x33031de5L;
	*p++ = 0xaa0a4c5fL;
	*p++ = 0xdd0d7cc9L;
	*p++ = 0x5005713cL;
	*p++ = 0x270241aaL;
	*p++ = 0xbe0b1010L;
	*p++ = 0xc90c2086L;
	*p++ = 0x5768b525L;
	*p++ = 0x206f85b3L;
	*p++ = 0xb966d409L;
	*p++ = 0xce61e49fL;
	*p++ = 0x5edef90eL;
	*p++ = 0x29d9c998L;
	*p++ = 0xb0d09822L;
	*p++ = 0xc7d7a8b4L;
	*p++ = 0x59b33d17L;
	*p++ = 0x2eb40d81L;
	*p++ = 0xb7bd5c3bL;
	*p++ = 0xc0ba6cadL;
	*p++ = 0xedb88320L;
	*p++ = 0x9abfb3b6L;
	*p++ = 0x03b6e20cL;
	*p++ = 0x74b1d29aL;
	*p++ = 0xead54739L;
	*p++ = 0x9dd277afL;
	*p++ = 0x04db2615L;
	*p++ = 0x73dc1683L;
	*p++ = 0xe3630b12L;
	*p++ = 0x94643b84L;
	*p++ = 0x0d6d6a3eL;
	*p++ = 0x7a6a5aa8L;
	*p++ = 0xe40ecf0bL;
	*p++ = 0x9309ff9dL;
	*p++ = 0x0a00ae27L;
	*p++ = 0x7d079eb1L;
	*p++ = 0xf00f9344L;
	*p++ = 0x8708a3d2L;
	*p++ = 0x1e01f268L;
	*p++ = 0x6906c2feL;
	*p++ = 0xf762575dL;
	*p++ = 0x806567cbL;
	*p++ = 0x196c3671L;
	*p++ = 0x6e6b06e7L;
	*p++ = 0xfed41b76L;
	*p++ = 0x89d32be0L;
	*p++ = 0x10da7a5aL;
	*p++ = 0x67dd4accL;
	*p++ = 0xf9b9df6fL;
	*p++ = 0x8ebeeff9L;
	*p++ = 0x17b7be43L;
	*p++ = 0x60b08ed5L;
	*p++ = 0xd6d6a3e8L;
	*p++ = 0xa1d1937eL;
	*p++ = 0x38d8c2c4L;
	*p++ = 0x4fdff252L;
	*p++ = 0xd1bb67f1L;
	*p++ = 0xa6bc5767L;
	*p++ = 0x3fb506ddL;
	*p++ = 0x48b2364bL;
	*p++ = 0xd80d2bdaL;
	*p++ = 0xaf0a1b4cL;
	*p++ = 0x36034af6L;
	*p++ = 0x41047a60L;
	*p++ = 0xdf60efc3L;
	*p++ = 0xa867df55L;
	*p++ = 0x316e8eefL;
	*p++ = 0x4669be79L;
	*p++ = 0xcb61b38cL;
	*p++ = 0xbc66831aL;
	*p++ = 0x256fd2a0L;
	*p++ = 0x5268e236L;
	*p++ = 0xcc0c7795L;
	*p++ = 0xbb0b4703L;
	*p++ = 0x220216b9L;
	*p++ = 0x5505262fL;
	*p++ = 0xc5ba3bbeL;
	*p++ = 0xb2bd0b28L;
	*p++ = 0x2bb45a92L;
	*p++ = 0x5cb36a04L;
	*p++ = 0xc2d7ffa7L;
	*p++ = 0xb5d0cf31L;
	*p++ = 0x2cd99e8bL;
	*p++ = 0x5bdeae1dL;
	*p++ = 0x9b64c2b0L;
	*p++ = 0xec63f226L;
	*p++ = 0x756aa39cL;
	*p++ = 0x026d930aL;
	*p++ = 0x9c0906a9L;
	*p++ = 0xeb0e363fL;
	*p++ = 0x72076785L;
	*p++ = 0x05005713L;
	*p++ = 0x95bf4a82L;
	*p++ = 0xe2b87a14L;
	*p++ = 0x7bb12baeL;
	*p++ = 0x0cb61b38L;
	*p++ = 0x92d28e9bL;
	*p++ = 0xe5d5be0dL;
	*p++ = 0x7cdcefb7L;
	*p++ = 0x0bdbdf21L;
	*p++ = 0x86d3d2d4L;
	*p++ = 0xf1d4e242L;
	*p++ = 0x68ddb3f8L;
	*p++ = 0x1fda836eL;
	*p++ = 0x81be16cdL;
	*p++ = 0xf6b9265bL;
	*p++ = 0x6fb077e1L;
	*p++ = 0x18b74777L;
	*p++ = 0x88085ae6L;
	*p++ = 0xff0f6a70L;
	*p++ = 0x66063bcaL;
	*p++ = 0x11010b5cL;
	*p++ = 0x8f659effL;
	*p++ = 0xf862ae69L;
	*p++ = 0x616bffd3L;
	*p++ = 0x166ccf45L;
	*p++ = 0xa00ae278L;
	*p++ = 0xd70dd2eeL;
	*p++ = 0x4e048354L;
	*p++ = 0x3903b3c2L;
	*p++ = 0xa7672661L;
	*p++ = 0xd06016f7L;
	*p++ = 0x4969474dL;
	*p++ = 0x3e6e77dbL;
	*p++ = 0xaed16a4aL;
	*p++ = 0xd9d65adcL;
	*p++ = 0x40df0b66L;
	*p++ = 0x37d83bf0L;
	*p++ = 0xa9bcae53L;
	*p++ = 0xdebb9ec5L;
	*p++ = 0x47b2cf7fL;
	*p++ = 0x30b5ffe9L;
	*p++ = 0xbdbdf21cL;
	*p++ = 0xcabac28aL;
	*p++ = 0x53b39330L;
	*p++ = 0x24b4a3a6L;
	*p++ = 0xbad03605L;
	*p++ = 0xcdd70693L;
	*p++ = 0x54de5729L;
	*p++ = 0x23d967bfL;
	*p++ = 0xb3667a2eL;
	*p++ = 0xc4614ab8L;
	*p++ = 0x5d681b02L;
	*p++ = 0x2a6f2b94L;
	*p++ = 0xb40bbe37L;
	*p++ = 0xc30c8ea1L;
	*p++ = 0x5a05df1bL;
	*p++ = 0x2d02ef8dL;
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
