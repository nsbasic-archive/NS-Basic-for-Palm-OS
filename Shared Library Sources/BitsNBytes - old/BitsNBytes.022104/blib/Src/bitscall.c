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
#include "bits.h"



// Jump target/GCC encapsulation stub routines
Err blib_orb(UInt refnum, Byte a, Byte b, Byte  *result) {
#pragma unused(refnum)
	*result = __orb(a,b);
	return bErrNone;
}

Err blib_orw(UInt refnum, Word a, Word b, Word  *result) {
#pragma unused(refnum)
	*result = __orw(a,b);
	return bErrNone;
}

Err blib_ord(UInt refnum, DWord a, DWord b, DWord  *result) {
#pragma unused(refnum)
	*result = __ord(a,b);
	return bErrNone;
}
//------------------------------------------------------------
Err blib_andb(UInt refnum, Byte a, Byte b, Byte  *result) {
#pragma unused(refnum)
	*result = __andb(a,b);
	return bErrNone;
}

Err blib_andw(UInt refnum, Word a, Word b, Word  *result) {
#pragma unused(refnum)
	*result = __andw(a,b);
	return bErrNone;
}

Err blib_andd(UInt refnum, DWord a, DWord b, DWord  *result) {
#pragma unused(refnum)
	*result = __andd(a,b);
	return bErrNone;
}
//------------------------------------------------------------
Err blib_xorb(UInt refnum, Byte a, Byte b, Byte  *result) {
#pragma unused(refnum)
	*result = __xorb(a,b);
	return bErrNone;
}

Err blib_xorw(UInt refnum, Word a, Word b, Word  *result) {
#pragma unused(refnum)
	*result = __xorw(a,b);
	return bErrNone;
}

Err blib_xord(UInt refnum, DWord a, DWord b, DWord  *result) {
#pragma unused(refnum)
	*result = __xord(a,b);
	return bErrNone;
}
//------------------------------------------------------------
Err blib_notb(UInt refnum, Byte a, Byte  *result) {
#pragma unused(refnum)
	*result = __notb(a);
	return bErrNone;
}

Err blib_notw(UInt refnum, Word a, Word  *result) {
#pragma unused(refnum)
	*result = __notw(a);
	return bErrNone;
}

Err blib_notd(UInt refnum, DWord a, DWord  *result) {
#pragma unused(refnum)
	*result = __notd(a);
	return bErrNone;
}
//------------------------------------------------------------
Err blib_swapw(UInt refnum, Word a, Word* result) {
#pragma unused(refnum)
	*result = __swapw(a);
	return bErrNone;
}
Err blib_swapd(UInt refnum, DWord a, DWord* result) {
#pragma unused(refnum)
	*result = __swapd(a);
	return bErrNone;
}
Err blib_swapdb(UInt refnum, double a, double* result) {
#pragma unused(refnum)
	*result = __swapdb(a);
	return bErrNone;
}
//------------------------------------------------------------
Err blib_shiftb(UInt refnum, Byte a, Int16 s, Byte  *result) {
#pragma unused(refnum)
	*result = __shiftb(a,s);
	return bErrNone;
}

Err blib_shiftw(UInt refnum, Word a, Int16 s, Word  *result) {
#pragma unused(refnum)
	*result = __shiftw(a,s);
	return bErrNone;
}

Err blib_shiftd(UInt refnum, DWord a, Int16 s, DWord  *result) {
#pragma unused(refnum)
	*result = __shiftd(a,s);
	return bErrNone;
}
//------------------------------------------------------------
Err blib_sshiftb(UInt refnum, Byte a, Int16 s, Byte  *result) {
#pragma unused(refnum)
	*result = __sshiftb(a,s);
	return bErrNone;
}

Err blib_sshiftw(UInt refnum, Word a, Int16 s, Word  *result) {
#pragma unused(refnum)
	*result = __sshiftw(a,s);
	return bErrNone;
}

Err blib_sshiftd(UInt refnum, DWord a, Int16 s, DWord  *result) {
#pragma unused(refnum)
	*result = __sshiftd(a,s);
	return bErrNone;
}
//------------------------------------------------------------
Err blib_cshiftb(UInt refnum, Byte a, Int16 s, Byte  *result) {
#pragma unused(refnum)
	*result = __cshiftb(a,s);
	return bErrNone;
}

Err blib_cshiftw(UInt refnum, Word a, Int16 s, Word  *result) {
#pragma unused(refnum)
	*result = __cshiftw(a,s);
	return bErrNone;
}

Err blib_cshiftd(UInt refnum, DWord a, Int16 s, DWord  *result) {
#pragma unused(refnum)
	*result = __cshiftd(a,s);
	return bErrNone;
}
//------------------------------------------------------------
Err blib_getbitb(UInt refnum, Byte a, Word s, Word  *result) {
#pragma unused(refnum)
	*result = __getbitb(a,s);
	return bErrNone;
}

Err blib_getbitw(UInt refnum, Word a, Word s, Word  *result) {
#pragma unused(refnum)
	*result = __getbitw(a,s);
	return bErrNone;
}

Err blib_getbitd(UInt refnum, DWord a, Word s, Word  *result) {
#pragma unused(refnum)
	*result = __getbitd(a,s);
	return bErrNone;
}
//------------------------------------------------------------
Err blib_setbitb(UInt refnum, Byte a, Word s, Byte  *result) {
#pragma unused(refnum)
	*result = __setbitb(a,s);
	return bErrNone;
}

Err blib_setbitw(UInt refnum, Word a, Word s, Word  *result) {
#pragma unused(refnum)
	*result = __setbitw(a,s);
	return bErrNone;
}

Err blib_setbitd(UInt refnum, DWord a, Word s, DWord  *result) {
#pragma unused(refnum)
	*result = __setbitd(a,s);
	return bErrNone;
}
//------------------------------------------------------------
Err blib_resetbitb(UInt refnum, Byte a, Word s, Byte  *result) {
#pragma unused(refnum)
	*result = __resetbitb(a,s);
	return bErrNone;
}

Err blib_resetbitw(UInt refnum, Word a, Word s, Word  *result) {
#pragma unused(refnum)
	*result = __resetbitw(a,s);
	return bErrNone;
}

Err blib_resetbitd(UInt refnum, DWord a, Word s, DWord  *result) {
#pragma unused(refnum)
	*result = __resetbitd(a,s);
	return bErrNone;
}
//------------------------------------------------------------
Err blib_inversebitb(UInt refnum, Byte a, Word s, Byte  *result) {
#pragma unused(refnum)
	*result = __inversebitb(a,s);
	return bErrNone;
}

Err blib_inversebitw(UInt refnum, Word a, Word s, Word  *result) {
#pragma unused(refnum)
	*result = __inversebitw(a,s);
	return bErrNone;
}

Err blib_inversebitd(UInt refnum, DWord a, Word s, DWord  *result) {
#pragma unused(refnum)
	*result = __inversebitd(a,s);
	return bErrNone;
}
//------------------------------------------------------------
Err blib_eqvb(UInt refnum, Byte a, Byte b, Byte mask, Byte  *result) {
#pragma unused(refnum)
	*result = __eqvb(a,b,mask);
	return bErrNone;
}

Err blib_eqvw(UInt refnum, Word a, Word b, Word mask, Word  *result) {
#pragma unused(refnum)
	*result = __eqvw(a,b,mask);
	return bErrNone;
}

Err blib_eqvd(UInt refnum, DWord a, DWord b, DWord mask, DWord  *result) {
#pragma unused(refnum)
	*result = __eqvd(a,b,mask);
	return bErrNone;
}
//------------------------------------------------------------
Err blib_setloword(UInt refnum, DWord a, Word ins, DWord  *result) {
#pragma unused(refnum)
	*result = __setloword( a, ins);
	return bErrNone;
}

Err blib_sethiword(UInt refnum, DWord a, Word ins, DWord  *result) {
#pragma unused(refnum)
	*result = __sethiword( a, ins);
	return bErrNone;
}

Err blib_setlobyte(UInt refnum, Word a, Byte ins, Word  *result) {
#pragma unused(refnum)
	*result = __setlobyte( a, ins);
	return bErrNone;
}

Err blib_sethibyte(UInt refnum, Word a, Byte ins, Word  *result) {
#pragma unused(refnum)
	*result = __sethibyte( a, ins);
	return bErrNone;
}

Err blib_getloword(UInt refnum, DWord a, Word  *result) {
#pragma unused(refnum)
	*result = __getloword( a);
	return bErrNone;
}

Err blib_gethiword(UInt refnum, DWord a, Word  *result) {
#pragma unused(refnum)
	*result = __gethiword( a);
	return bErrNone;
}

Err blib_getlobyte(UInt refnum, Word a, Byte  *result) {
#pragma unused(refnum)
	*result = __getlobyte( a);
	return bErrNone;
}

Err blib_gethibyte(UInt refnum, Word a, Byte  *result) {
#pragma unused(refnum)
	*result = __gethibyte( a);
	return bErrNone;
}
//------------------------------------------------------------
Err blib_dec2hex(UInt refnum, DWord a, DWord  *result) {
#pragma unused(refnum)
	*result = __dec2hex( a);
	return bErrNone;
}
Err blib_hex2dec(UInt refnum, DWord a, DWord  *result) {
#pragma unused(refnum)
	*result = __hex2dec( a);
	return bErrNone;
}
Err blib_bin2dec(UInt refnum, DWord a, DWord  *result) {
#pragma unused(refnum)
	*result = __bin2dec( a);
	return bErrNone;
}
Err blib_dec2bin(UInt refnum, DWord a, DWord  *result) {
#pragma unused(refnum)
	*result = __dec2bin( a);
	return bErrNone;
}
//------------------------------------------------------------
Err blib_crc32(UInt refnum, void * bufP, UInt16 count, UInt32 crc, UInt32 *result) {
#pragma unused(refnum)
	*result = __crc32(bufP, count, crc);
	return bErrNone;
}

Err blib_encdes(UInt refnum, BytePtr srcP, BytePtr keyP, BytePtr dstP, UInt16 encrypt, UInt32 *result) {
#pragma unused(refnum)
	*result = __encdes(srcP, keyP, dstP, encrypt);
	return bErrNone;
}

Err blib_encmd4(UInt refnum, BytePtr strP, Word strLen, Byte digestP[16], UInt32 *result) {
#pragma unused(refnum)
	*result = __encmd4(strP, strLen, digestP);
	return bErrNone;
}

Err blib_encmd5(UInt refnum, BytePtr strP, Word strLen, Byte digestP[16], UInt32 *result) {
#pragma unused(refnum)
	*result = __encmd5(strP, strLen, digestP);
	return bErrNone;
}
//------------------------------------------------------------
Err blib_version(UInt refnum,  UInt *result) {
#pragma unused(refnum)
	*result = __version();
	return bErrNone;
}
Err blib_puthexstr(UInt refnum, char* str,  DWord *result) {
#pragma unused(refnum)
	*result = __puthexstr( str );
	return bErrNone;
}

Err blib_gethexstr(UInt refnum, DWord a,char *result) {
#pragma unused(refnum)
	__gethexstr( a, result );
	return bErrNone;
}

Err blib_putbinstr(UInt refnum, char* str,  DWord *result) {
#pragma unused(refnum)
	*result = __putbinstr( str );
	return bErrNone;
}

Err blib_getbinstr(UInt refnum, DWord a,char *result) {
#pragma unused(refnum)
	__getbinstr( a, result );
	return bErrNone;
}


//**************************************************************
//*  New EncDES Encryption/Decryption routines for strings...
//**************************************************************

Err blib_encryptDesString(UInt refnum, char *decryptedStr, char *encryptedStr) {
	__encryptDesString(refnum, decryptedStr, encryptedStr );
	return bErrNone;
}

Err blib_decryptDesString(UInt refnum, char *encryptedStr, char *decryptedStr) {
	__decryptDesString(refnum, encryptedStr, decryptedStr );
	return bErrNone;
}

Err blib_setDesKey(UInt refnum, char *keyStr) {
	__setDesKey(refnum, keyStr );
	return bErrNone;
}

