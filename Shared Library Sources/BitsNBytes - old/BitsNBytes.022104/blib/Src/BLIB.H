#ifndef __BLIB_H__

#define __BLIB_H__

// Library name for use with SysLibFind()
#define BLibName	"BitsNbyteslib"

// Values for use with SysLibLoad()
#define LibType		'libr'
#define BLibCreator	'NSPb'

// version of lib
#define BLibVersion 2

// Possible Err values from BLib functions
typedef enum BLibErrorCode {
	bErrNone = 0,
	bErrOldVersion,		// library is older than version passed to open()
	bErrNotOpen,		// close() without having called open() first
	bErrNoMemory		// can't allocate global data block
} BLibErrorCode;

// Library reference returned by SysLibFind() or SysLibLoad()
extern UInt BLibRef;

/*****************************
 * Library control functions *
 *****************************/
#ifdef __cplusplus
extern "C" {
#endif

Err BLibOpen(UInt refnum)		SYS_TRAP(sysLibTrapOpen);
Err BLibClose(UInt refnum)/*, UIntPtr usecountP)*/	SYS_TRAP(sysLibTrapClose);
Err BLibSleep(UInt refnum)			SYS_TRAP(sysLibTrapSleep);
Err BLibWake(UInt refnum)			SYS_TRAP(sysLibTrapWake);

/***************************
 * Bit functions
 ***************************/
Byte	orB(Byte a,Byte b);
Word	orW(Word a,Word b);
DWord	orD(DWord a,DWord b);

Byte	andB(Byte a,Byte b);
Word	andW(Word a,Word b);
DWord	andD(DWord a,DWord b);

Byte	xorB(Byte a,Byte b);
Word	xorW(Word a,Word b);
DWord	xorD(DWord a,DWord b);

Byte	notB(Byte a);
Word	notW(Word a);
DWord	notD(DWord a);

Word	swapW(Word a);
DWord	swapD(DWord a);
double	swapDB(double a);

Byte	shiftB(Byte a,Int16 s);
Word	shiftW(Word a,Int16 s);
DWord	shiftD(DWord a,Int16 s);

Byte	sshiftB(Byte a,Int16 s);
Word	sshiftW(Word a,Int16 s);
DWord	sshiftD(DWord a,Int16 s);

Byte	cshiftB(Byte a,Int16 s);
Word	cshiftW(Word a,Int16 s);
DWord	cshiftD(DWord a,Int16 s);

Word	getbitB(Byte a,Word s);
Word	getbitW(Word a,Word s);
Word	getbitD(DWord a,Word s);

Byte	setbitB(Byte a,Word s);
Word	setbitW(Word a,Word s);
DWord	setbitD(DWord a,Word s);

Byte	resetbitB(Byte a,Word s);
Word	resetbitW(Word a,Word s);
DWord	resetbitD(DWord a,Word s);

Byte	inversebitB(Byte a,Word s);
Word	inversebitW(Word a,Word s);
DWord	inversebitD(DWord a,Word s);

Byte	eqvB(Byte a,Byte b,Byte mask);
Word	eqvW(Word a,Word b,Word mask);
DWord	eqvD(DWord a,DWord b,DWord mask);

DWord setloword(DWord a, Word ins);
DWord sethiword(DWord a, Word ins);
Word sethibyte(Word a, Byte ins);
Word setlobyte(Word a, Byte ins);

Word getloword(DWord a);
Word gethiword(DWord a);
Byte gethibyte(Word a);
Byte getlobyte(Word a);

DWord dec2hex( DWord a);
DWord hex2dec( DWord a);
DWord bin2dec( DWord a);
DWord dec2bin( DWord a);

UInt32 crc32(void * bufP, UInt16 count, UInt32 crc);

UInt32 encdes(BytePtr srcP, BytePtr keyP, BytePtr dstP, UInt16 encrypt);
UInt32 encmd4(BytePtr strP, Word strLen, Byte digestP[16]);
UInt32 encmd5(BytePtr strP, Word strLen, Byte digestP[16]);

UInt version(void);

DWord puthexstr( char* str);
void gethexstr( DWord a,char* res );

DWord putbinstr( char* str);
void getbinstr( DWord a,char* res );

//**************************************************************
//*  New EncDES Encryption/Decryption routines for strings...
//**************************************************************

void encryptdesstring( char *decryptedStr, char *encryptedStr );
void decryptdesstring( char *encryptedStr, char *decryptedStr );
void setdeskey( char *keyStr );


/****************************************
 * Prototypes for the system traps that *
 * actually perform the library calls,  *
 * in the format mandated by the OS.    *
 ****************************************/

Err BLibOrB(UInt refnum, Byte a,  Byte b,  Byte  *result)	SYS_TRAP(sysLibTrapCustom);
Err BLibOrW(UInt refnum, Word a,  Word b,  Word  *result)	SYS_TRAP(sysLibTrapCustom+1);
Err BLibOrD(UInt refnum, DWord a, DWord b, DWord *result)	SYS_TRAP(sysLibTrapCustom+2);

Err BLibAndB(UInt refnum, Byte a,  Byte b,  Byte  *result)	SYS_TRAP(sysLibTrapCustom+3);
Err BLibAndW(UInt refnum, Word a,  Word b,  Word  *result)	SYS_TRAP(sysLibTrapCustom+4);
Err BLibAndD(UInt refnum, DWord a, DWord b, DWord *result)	SYS_TRAP(sysLibTrapCustom+5);

Err BLibXorB(UInt refnum, Byte a,  Byte b,  Byte  *result)	SYS_TRAP(sysLibTrapCustom+6);
Err BLibXorW(UInt refnum, Word a,  Word b,  Word  *result)	SYS_TRAP(sysLibTrapCustom+7);
Err BLibXorD(UInt refnum, DWord a, DWord b, DWord *result)	SYS_TRAP(sysLibTrapCustom+8);

Err BLibNotB(UInt refnum, Byte a,  Byte  *result)	SYS_TRAP(sysLibTrapCustom+9);
Err BLibNotW(UInt refnum, Word a,  Word  *result)	SYS_TRAP(sysLibTrapCustom+10);
Err BLibNotD(UInt refnum, DWord a, DWord *result)	SYS_TRAP(sysLibTrapCustom+11);

Err BLibSwapW(UInt refnum, Word a,  Word* result)	SYS_TRAP(sysLibTrapCustom+12);
Err BLibSwapD(UInt refnum, DWord a, DWord* result)	SYS_TRAP(sysLibTrapCustom+13);
Err BLibSwapDB(UInt refnum, double a, double* result)	SYS_TRAP(sysLibTrapCustom+14);

Err BLibShiftB(UInt refnum, Byte a,  Int16 s,  Byte  *result)	SYS_TRAP(sysLibTrapCustom+15);
Err BLibShiftW(UInt refnum, Word a,  Int16 s,  Word  *result)	SYS_TRAP(sysLibTrapCustom+16);
Err BLibShiftD(UInt refnum, DWord a, Int16 s,  DWord *result)	SYS_TRAP(sysLibTrapCustom+17);

Err BLibSShiftB(UInt refnum, Byte a,  Int16 s,  Byte  *result)	SYS_TRAP(sysLibTrapCustom+18);
Err BLibSShiftW(UInt refnum, Word a,  Int16 s,  Word  *result)	SYS_TRAP(sysLibTrapCustom+19);
Err BLibSShiftD(UInt refnum, DWord a, Int16 s,  DWord *result)	SYS_TRAP(sysLibTrapCustom+20);

Err BLibCShiftB(UInt refnum, Byte a,  Int16 s,  Byte  *result)	SYS_TRAP(sysLibTrapCustom+21);
Err BLibCShiftW(UInt refnum, Word a,  Int16 s,  Word  *result)	SYS_TRAP(sysLibTrapCustom+22);
Err BLibCShiftD(UInt refnum, DWord a, Int16 s,  DWord *result)	SYS_TRAP(sysLibTrapCustom+23);

Err BLibGetBitB(UInt refnum, Byte a,  Word s,  Word  *result)	SYS_TRAP(sysLibTrapCustom+24);
Err BLibGetBitW(UInt refnum, Word a,  Word s,  Word  *result)	SYS_TRAP(sysLibTrapCustom+25);
Err BLibGetBitD(UInt refnum, DWord a, Word s,  Word  *result)	SYS_TRAP(sysLibTrapCustom+26);

Err BLibSetBitB(UInt refnum, Byte a,  Word s,  Byte  *result)	SYS_TRAP(sysLibTrapCustom+27);
Err BLibSetBitW(UInt refnum, Word a,  Word s,  Word  *result)	SYS_TRAP(sysLibTrapCustom+28);
Err BLibSetBitD(UInt refnum, DWord a, Word s,  DWord *result)	SYS_TRAP(sysLibTrapCustom+29);

Err BLibResetBitB(UInt refnum, Byte a,  Word s,  Byte  *result)	SYS_TRAP(sysLibTrapCustom+30);
Err BLibResetBitW(UInt refnum, Word a,  Word s,  Word  *result)	SYS_TRAP(sysLibTrapCustom+31);
Err BLibResetBitD(UInt refnum, DWord a, Word s,  DWord *result)	SYS_TRAP(sysLibTrapCustom+32);

Err BLibInverseBitB(UInt refnum, Byte a,  Word s,  Byte  *result)	SYS_TRAP(sysLibTrapCustom+33);
Err BLibInverseBitW(UInt refnum, Word a,  Word s,  Word  *result)	SYS_TRAP(sysLibTrapCustom+34);
Err BLibInverseBitD(UInt refnum, DWord a, Word s,  DWord *result)	SYS_TRAP(sysLibTrapCustom+35);

Err BLibEqvB(UInt refnum, Byte a,  Byte b, Byte mask, Byte  *result)	SYS_TRAP(sysLibTrapCustom+36);
Err BLibEqvW(UInt refnum, Word a,  Word b, Word mask,  Word  *result)	SYS_TRAP(sysLibTrapCustom+37);
Err BLibEqvD(UInt refnum, DWord a, DWord b,DWord mask,  DWord *result)	SYS_TRAP(sysLibTrapCustom+38);

Err BLibSetLoWord(UInt refnum, DWord a, Word ins, DWord  *result) 	SYS_TRAP(sysLibTrapCustom+39);
Err BLibSetHiWord(UInt refnum, DWord a, Word ins, DWord  *result) 	SYS_TRAP(sysLibTrapCustom+40);
Err BLibSetLoByte(UInt refnum, Word a, Byte ins, Word  *result) 	SYS_TRAP(sysLibTrapCustom+41);
Err BLibSetHiByte(UInt refnum, Word a, Byte ins, Word  *result) 	SYS_TRAP(sysLibTrapCustom+42);

Err BLibGetLoWord(UInt refnum, DWord a, Word  *result) 	SYS_TRAP(sysLibTrapCustom+43);
Err BLibGetHiWord(UInt refnum, DWord a, Word  *result) 	SYS_TRAP(sysLibTrapCustom+44);
Err BLibGetLoByte(UInt refnum, Word a, Byte  *result) 	SYS_TRAP(sysLibTrapCustom+45);
Err BLibGetHiByte(UInt refnum, Word a, Byte  *result) 	SYS_TRAP(sysLibTrapCustom+46);

Err BLibDec2Hex(UInt refnum, DWord a, DWord  *result) 	SYS_TRAP(sysLibTrapCustom+47);
Err BLibHex2Dec(UInt refnum, DWord a, DWord  *result) 	SYS_TRAP(sysLibTrapCustom+48);
Err BLibBin2Dec(UInt refnum, DWord a, DWord  *result) 	SYS_TRAP(sysLibTrapCustom+49);
Err BLibDec2Bin(UInt refnum, DWord a, DWord  *result) 	SYS_TRAP(sysLibTrapCustom+50);

Err BLibCrc32(UInt refnum, void * bufP, UInt16 count, UInt32 crc, UInt32 *result) 	SYS_TRAP(sysLibTrapCustom+51);
Err BLibEncDES(UInt refnum, BytePtr srcP, BytePtr keyP, BytePtr dstP, UInt16 encrypt, UInt32 *result) 	SYS_TRAP(sysLibTrapCustom+52);
Err BLibEncMD4(UInt refnum, BytePtr strP, Word strLen, Byte digestP[16], UInt32 *result) 	SYS_TRAP(sysLibTrapCustom+53);
Err BLibEncMD5(UInt refnum, BytePtr strP, Word strLen, Byte digestP[16], UInt32 *result) 	SYS_TRAP(sysLibTrapCustom+54);

Err BLibVer(UInt refnum,  UInt *result) 	SYS_TRAP(sysLibTrapCustom+55);

Err  BLibPutHexStr(UInt refnum, char* str, DWord *result)	SYS_TRAP(sysLibTrapCustom+56);
Err  BLibGetHexStr(UInt refnum, DWord a,char *result)		SYS_TRAP(sysLibTrapCustom+57);

Err  BLibPutBinStr(UInt refnum, char* str, DWord *result)	SYS_TRAP(sysLibTrapCustom+58);
Err  BLibGetBinStr(UInt refnum, DWord a,char *result)		SYS_TRAP(sysLibTrapCustom+59);

//**************************************************************
//*  New EncDES Encryption/Decryption routines for strings...
//**************************************************************

Err BLibEncryptDesString(UInt refnum, char* decryptedStr, char *encryptedStr)  SYS_TRAP(sysLibTrapCustom+60);
Err BLibDecryptDesString(UInt refnum, char* encryptedStr, char *decryptedStr)  SYS_TRAP(sysLibTrapCustom+61);
Err BLibSetDesKey(UInt refnum, char* keyStr)  SYS_TRAP(sysLibTrapCustom+62);

#ifdef __cplusplus 
}
#endif

#endif // __BLIB_H__
