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

// Library reference returned by SysLibFind() or SysLibLoad()
UInt BLibRef;

Byte orB( Byte a, Byte b)
{
 Byte result;
 BLibOrB(BLibRef, a, b,&result);
 return result;
}

Word orW( Word a, Word b)
{
 Word result;
 BLibOrW(BLibRef, a, b,&result);
 return result;
}

DWord orD( DWord a, DWord b)
{
 DWord result;
 BLibOrD(BLibRef, a, b,&result);
 return result;
}
//-----------------------------------------
Byte andB( Byte a, Byte b)
{
 Byte result;
 BLibAndB(BLibRef, a, b,&result);
 return result;
}

Word andW( Word a, Word b)
{
 Word result;
 BLibAndW(BLibRef, a, b,&result);
 return result;
}

DWord andD( DWord a, DWord b)
{
 DWord result;
 BLibAndD(BLibRef, a, b,&result);
 return result;
}
//-----------------------------------------
Byte xorB( Byte a, Byte b)
{
 Byte result;
 BLibXorB(BLibRef, a, b,&result);
 return result;
}

Word xorW( Word a, Word b)
{
 Word result;
 BLibXorW(BLibRef, a, b,&result);
 return result;
}

DWord xorD( DWord a, DWord b)
{
 DWord result;
 BLibXorD(BLibRef, a, b,&result);
 return result;
}
//-----------------------------------------
Byte notB( Byte a)
{
 Byte result;
 BLibNotB(BLibRef, a, &result);
 return result;
}

Word notW( Word a)
{
 Word result;
 BLibNotW(BLibRef, a, &result);
 return result;
}

DWord notD( DWord a)
{
 DWord result;
 BLibNotD(BLibRef, a, &result);
 return result;
}
//-----------------------------------------
Word swapW( Word a)
{
 Word result;
 BLibSwapW(BLibRef, a, &result);
 return result;
}

DWord swapD( DWord a)
{
 DWord result;
 BLibSwapD(BLibRef, a, &result);
 return result;
}
double swapDB( double a)
{
 double result;
 BLibSwapDB(BLibRef, a, &result);
 return result;
}
//-----------------------------------------
Byte shiftB( Byte a, Int16 s)
{
 Byte result;
 BLibShiftB(BLibRef, a, s,&result);
 return result;
}

Word shiftW( Word a, Int16 s)
{
 Word result;
 BLibShiftW(BLibRef, a, s,&result);
 return result;
}

DWord shiftD( DWord a, Int16 s)
{
 DWord result;
 BLibShiftD(BLibRef, a, s,&result);
 return result;
}
//-----------------------------------------
Byte sshiftB( Byte a, Int16 s)
{
 Byte result;
 BLibSShiftB(BLibRef, a, s,&result);
 return result;
}

Word sshiftW( Word a, Int16 s)
{
 Word result;
 BLibSShiftW(BLibRef, a, s,&result);
 return result;
}

DWord sshiftD( DWord a, Int16 s)
{
 DWord result;
 BLibSShiftD(BLibRef, a, s,&result);
 return result;
}
//-----------------------------------------
Byte cshiftB( Byte a, Int16 s)
{
 Byte result;
 BLibCShiftB(BLibRef, a, s,&result);
 return result;
}

Word cshiftW( Word a, Int16 s)
{
 Word result;
 BLibCShiftW(BLibRef, a, s,&result);
 return result;
}

DWord cshiftD( DWord a, Int16 s)
{
 DWord result;
 BLibCShiftD(BLibRef, a, s,&result);
 return result;
}
//-----------------------------------------
Word getbitB( Byte a, Word s)
{
 Word result;
 BLibGetBitB(BLibRef, a, s,&result);
 return result;
}

Word getbitW( Word a, Word s)
{
 Word result;
 BLibGetBitW(BLibRef, a, s,&result);
 return result;
}

Word getbitD( DWord a, Word s)
{
 Word result;
 BLibGetBitD(BLibRef, a, s,&result);
 return result;
}
//-----------------------------------------
Byte setbitB( Byte a, Word s)
{
 Byte result;
 BLibSetBitB(BLibRef, a, s,&result);
 return result;
}

Word setbitW( Word a, Word s)
{
 Word result;
 BLibSetBitW(BLibRef, a, s,&result);
 return result;
}

DWord setbitD( DWord a, Word s)
{
 DWord result;
 BLibSetBitD(BLibRef, a, s,&result);
 return result;
}
//-----------------------------------------
Byte resetbitB( Byte a, Word s)
{
 Byte result;
 BLibResetBitB(BLibRef, a, s,&result);
 return result;
}

Word resetbitW( Word a, Word s)
{
 Word result;
 BLibResetBitW(BLibRef, a, s,&result);
 return result;
}

DWord resetbitD( DWord a, Word s)
{
 DWord result;
 BLibResetBitD(BLibRef, a, s,&result);
 return result;
}
//-----------------------------------------
Byte inversebitB( Byte a, Word s)
{
 Byte result;
 BLibInverseBitB(BLibRef, a, s,&result);
 return result;
}

Word inversebitW( Word a, Word s)
{
 Word result;
 BLibInverseBitW(BLibRef, a, s,&result);
 return result;
}

DWord inversebitD( DWord a, Word s)
{
 DWord result;
 BLibInverseBitD(BLibRef, a, s,&result);
 return result;
}
//-----------------------------------------
Byte eqvB( Byte a, Byte b, Byte mask)
{
 Byte result;
 BLibEqvB(BLibRef, a, b, mask, &result);
 return result;
}

Word eqvW( Word a, Word b, Word mask)
{
 Word result;
 BLibEqvW(BLibRef, a, b, mask, &result);
 return result;
}

DWord eqvD( DWord a, DWord b, DWord mask)
{
 DWord result;
 BLibEqvD(BLibRef, a, b, mask, &result);
 return result;
}
//-----------------------------------------
DWord setloword(DWord a, Word ins)
{
 DWord result;
 BLibSetLoWord(BLibRef, a, ins, &result);
 return result;
}

DWord sethiword(DWord a, Word ins)
{
 DWord result;
 BLibSetHiWord(BLibRef, a, ins, &result);
 return result;
}

Word setlobyte(Word a, Byte ins)
{
 Word result;
 BLibSetLoByte(BLibRef, a, ins, &result);
 return result;
}

Word sethibyte(Word a, Byte ins)
{
 Word result;
 BLibSetHiByte(BLibRef, a, ins, &result);
 return result;
}


Word getloword(DWord a)
{
 Word result;
 BLibGetLoWord(BLibRef, a, &result);
 return result;
}

Word gethiword(DWord a)
{
 Word result;
 BLibGetHiWord(BLibRef, a, &result);
 return result;
}

Byte getlobyte(Word a)
{
 Byte result;
 BLibGetLoByte(BLibRef, a, &result);
 return result;
}

Byte gethibyte(Word a)
{
 Byte result;
 BLibGetHiByte(BLibRef, a, &result);
 return result;
}


DWord dec2hex( DWord a)
{
 DWord result;
 BLibDec2Hex(BLibRef, a, &result);
 return result;
}
DWord hex2dec( DWord a)
{
 DWord result;
 BLibHex2Dec(BLibRef, a, &result);
 return result;
}
DWord bin2dec( DWord a)
{
 DWord result;
 BLibBin2Dec(BLibRef, a, &result);
 return result;
}
DWord dec2bin( DWord a)
{
 DWord result;
 BLibDec2Bin(BLibRef, a, &result);
 return result;
}



UInt32 crc32(void * bufP, UInt16 count, UInt32 crc)
{
UInt32 result;
 BLibCrc32(BLibRef,bufP, count, crc, &result);
 return result;
}

UInt32 encdes(BytePtr srcP, BytePtr keyP, BytePtr dstP, UInt16 encrypt)
{
UInt32 result;
BLibEncDES(BLibRef,srcP, keyP, dstP, encrypt, &result);
 return result;
}

UInt32 encmd4(BytePtr strP, Word strLen, Byte digestP[16])
{
UInt32 result;
BLibEncMD4(BLibRef,strP, strLen, digestP, &result);
 return result;
}

UInt32 encmd5(BytePtr strP, Word strLen, Byte digestP[16])
{
UInt32 result;
BLibEncMD5(BLibRef,strP, strLen, digestP, &result);
 return result;
}


UInt version(void) 
{
 UInt result;
 BLibVer(BLibRef, &result);
 return result;
}

void gethexstr(DWord a,char* result) 
{
 BLibGetHexStr(BLibRef, a, result);
 return;
}

DWord puthexstr(char* str) 
{
 DWord  result;
 BLibPutHexStr(BLibRef, str, &result);
 return result;
}


void getbinstr(DWord a,char* result) 
{
 BLibGetBinStr(BLibRef, a, result);
 return;
}

DWord putbinstr(char* str) 
{
 DWord  result;
 BLibPutBinStr(BLibRef, str, &result);
 return result;
}

//**************************************************************
//*  New EncDES Encryption/Decryption routines for strings...
//**************************************************************

void encryptdesstring(char *decryptedStr, char *encryptedStr)
{
 BLibEncryptDesString(BLibRef, decryptedStr, encryptedStr);
}

void decryptdesstring(char *encryptedStr, char *decryptedStr)
{
 BLibDecryptDesString(BLibRef, encryptedStr, decryptedStr);
}

void setdeskey(char *keyStr)
{
 BLibSetDesKey(BLibRef, keyStr);
}
