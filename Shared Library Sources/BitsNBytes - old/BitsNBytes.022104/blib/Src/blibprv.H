#ifndef __BLIBPRV_H__
#define __BLIBPRV_H__

// Our global data structure
typedef struct BLibData {
	UInt usecount;
	
    unsigned char   src[256];
    unsigned char   dst[256];
    unsigned char   keys[25];
    unsigned char   *key[3];

} BLibData;

// Control function prototypes
Err __Startup__(UInt refnum, SysLibTblEntryPtr entryP);
Ptr *DispatchTable(void);

Err blib_open(UInt refnum);
Err blib_close(UInt refnum);//, UIntPtr numappsP);
Err blib_sleep(UInt refnum);
Err blib_wake(UInt refnum);

// Dispatch table jmp target/GCC encapsulation prototypes

Err blib_orb(UInt refnum, Byte a, Byte b, Byte *result);
Err blib_orw(UInt refnum, Word a, Word b, Word *result);
Err blib_ord(UInt refnum, DWord a, DWord b, DWord *result);

Err blib_andb(UInt refnum, Byte a, Byte b, Byte *result);
Err blib_andw(UInt refnum, Word a, Word b, Word *result);
Err blib_andd(UInt refnum, DWord a, DWord b, DWord *result);

Err blib_xorb(UInt refnum, Byte a, Byte b, Byte *result);
Err blib_xorw(UInt refnum, Word a, Word b, Word *result);
Err blib_xord(UInt refnum, DWord a, DWord b, DWord *result);

Err blib_notb(UInt refnum, Byte a, Byte *result);
Err blib_notw(UInt refnum, Word a, Word *result);
Err blib_notd(UInt refnum, DWord a,DWord *result);

Err blib_swapw(UInt refnum, Word a, Word* result);
Err blib_swapd(UInt refnum, DWord a, DWord* result);
Err blib_swapdb(UInt refnum, double a, double* result);

Err blib_shiftb(UInt refnum, Byte a, Int16 s, Byte *result);
Err blib_shiftw(UInt refnum, Word a, Int16 s, Word *result);
Err blib_shiftd(UInt refnum, DWord a, Int16 s, DWord *result);

Err blib_sshiftb(UInt refnum, Byte a, Int16 s, Byte *result);
Err blib_sshiftw(UInt refnum, Word a, Int16 s, Word *result);
Err blib_sshiftd(UInt refnum, DWord a, Int16 s, DWord *result);

Err blib_cshiftb(UInt refnum, Byte a, Int16 s, Byte *result);
Err blib_cshiftw(UInt refnum, Word a, Int16 s, Word *result);
Err blib_cshiftd(UInt refnum, DWord a, Int16 s, DWord *result);

Err blib_getbitb(UInt refnum, Byte a, Word s, Word *result);
Err blib_getbitw(UInt refnum, Word a, Word s, Word *result);
Err blib_getbitd(UInt refnum, DWord a, Word s, Word *result);

Err blib_setbitb(UInt refnum, Byte a, Word s, Byte *result);
Err blib_setbitw(UInt refnum, Word a, Word s, Word *result);
Err blib_setbitd(UInt refnum, DWord a, Word s, DWord *result);

Err blib_resetbitb(UInt refnum, Byte a, Word s, Byte *result);
Err blib_resetbitw(UInt refnum, Word a, Word s, Word *result);
Err blib_resetbitd(UInt refnum, DWord a, Word s, DWord *result);

Err blib_inversebitb(UInt refnum, Byte a, Word s, Byte *result);
Err blib_inversebitw(UInt refnum, Word a, Word s, Word *result);
Err blib_inversebitd(UInt refnum, DWord a, Word s, DWord *result);

Err blib_eqvb(UInt refnum, Byte a, Byte b, Byte mask,Byte *result);
Err blib_eqvw(UInt refnum, Word a, Word b, Word mask, Word *result);
Err blib_eqvd(UInt refnum, DWord a,DWord b, DWord mask, DWord *result);

Err blib_setloword(UInt refnum, DWord a, Word ins, DWord  *result);
Err blib_sethiword(UInt refnum, DWord a, Word ins, DWord  *result);
Err blib_setlobyte(UInt refnum, Word a, Byte ins, Word  *result);
Err blib_sethibyte(UInt refnum, Word a, Byte ins, Word  *result);

Err blib_getloword(UInt refnum, DWord a, Word  *result);
Err blib_gethiword(UInt refnum, DWord a, Word  *result);
Err blib_getlobyte(UInt refnum, Word a, Byte  *result);
Err blib_gethibyte(UInt refnum, Word a, Byte  *result);

Err blib_dec2hex(UInt refnum, DWord a, DWord  *result);
Err blib_hex2dec(UInt refnum, DWord a, DWord  *result);
Err blib_bin2dec(UInt refnum, DWord a, DWord  *result);
Err blib_dec2bin(UInt refnum, DWord a, DWord  *result);

Err blib_crc32(UInt refnum, void * bufP, UInt16 count, UInt32 crc, UInt32 *result);

Err blib_encdes(UInt refnum, BytePtr srcP, BytePtr keyP, BytePtr dstP, UInt16 encrypt, UInt32 *result);
Err blib_encmd4(UInt refnum, BytePtr strP, Word strLen, Byte digestP[16], UInt32 *result);
Err blib_encmd5(UInt refnum, BytePtr strP, Word strLen, Byte digestP[16], UInt32 *result);

Err blib_version(UInt refnum,  UInt *result);

Err  blib_puthexstr(UInt refnum, char* str, DWord *result);
Err  blib_gethexstr(UInt refnum, DWord a,char *result);

Err  blib_putbinstr(UInt refnum, char* str, DWord *result);
Err  blib_getbinstr(UInt refnum, DWord a,char *result);

//**************************************************************
//*  New EncDES Encryption/Decryption routines for strings...
//**************************************************************

Err blib_encryptDesString(UInt refnum, char *decryptedStr, char *encryptedStr);
Err blib_decryptDesString(UInt refnum, char *encryptedStr, char *decryptedStr);
Err blib_setDesKey(UInt refnum, char *keyStr);


#endif // __BLIBPRV_H__
