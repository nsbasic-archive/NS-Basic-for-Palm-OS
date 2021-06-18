#include "blibprv.h"

// Prototypes for primary functions, copied verbatim from GCC source
Byte __orb(Byte a,Byte b);
Word __orw(Word a,Word b);
DWord __ord(DWord a,DWord b);

Byte __andb(Byte a,Byte b);
Word __andw(Word a,Word b);
DWord __andd(DWord a,DWord b);

Byte __xorb(Byte a,Byte b);
Word __xorw(Word a,Word b);
DWord __xord(DWord a,DWord b);

Byte __notb(Byte a);
Word __notw(Word a);
DWord __notd(DWord a);

Word __swapw(Word a);
DWord __swapd(DWord a);
double __swapdb(double a);

Byte __shiftb(Byte a,Int16 s);
Word __shiftw(Word a,Int16 s);
DWord __shiftd(DWord a,Int16 s);

Byte __sshiftb(Byte a,Int16 s);
Word __sshiftw(Word a,Int16 s);
DWord __sshiftd(DWord a,Int16 s);

Byte __cshiftb(Byte a,Int16 s);
Word __cshiftw(Word a,Int16 s);
DWord __cshiftd(DWord a,Int16 s);

Word __getbitb(Byte a,Word s);
Word __getbitw(Word a,Word s);
Word __getbitd(DWord a,Word s);

Byte __setbitb(Byte a,Word s);
Word __setbitw(Word a,Word s);
DWord __setbitd(DWord a,Word s);

Byte __resetbitb(Byte a,Word s);
Word __resetbitw(Word a,Word s);
DWord __resetbitd(DWord a,Word s);

Byte __inversebitb(Byte a,Word s);
Word __inversebitw(Word a,Word s);
DWord __inversebitd(DWord a,Word s);

Byte __eqvb(Byte a,Byte b,Byte mask);
Word __eqvw(Word a,Word b,Word mask);
DWord __eqvd(DWord a,DWord b,DWord mask);


DWord __setloword( DWord a, Word ins);
DWord __sethiword( DWord a, Word ins);

Word __setlobyte( Word a, Byte ins);
Word __sethibyte( Word a, Byte ins);

Word __getloword( DWord a);
Word __gethiword( DWord a);

Byte __getlobyte( Word a);
Byte __gethibyte( Word a);


DWord __dec2hex( DWord a);
DWord __hex2dec( DWord a);
DWord __bin2dec( DWord a);
DWord __dec2bin( DWord a);

UInt32 __crc32(void * bufP, UInt16 count, UInt32 crc);

UInt32 __encdes(BytePtr srcP, BytePtr keyP, BytePtr dstP, UInt16 encrypt);
UInt32 __encmd4(BytePtr strP, Word strLen, Byte digestP[16]);
UInt32 __encmd5(BytePtr strP, Word strLen, Byte digestP[16]);

UInt __version(void);

DWord __puthexstr( char* str);
void  __gethexstr( DWord a, char *res);

DWord __putbinstr( char* str);
void  __getbinstr( DWord a, char *res);

//**************************************************************
//*  New EncDES Encryption/Decryption routines for strings...
//**************************************************************
SWord __decryptData(unsigned char *key, unsigned char *src, unsigned char *dst, 
                    SWord len, char replaceNulls);
SWord __encryptData(unsigned char *key, unsigned char *src, unsigned char *dst, 
                  SWord len, char replaceNulls);
void __encryptDesString(UInt refNum,		// Lib ref num
                        char *decryptedStr,
                        char *encryptedStr);
BLibData * __prvLockGlobals(UInt refNum);
void __decryptDesString(UInt refNum,		// Lib ref num
                        char *encryptedStr,
                        char *decryptedStr);
void __setDesKey(DWord UInt,		// Lib ref num
                 char *keyStr);
