#define PALMOS_35_OR_HIGHER
#ifdef PALMOS_35_OR_HIGHER
#define PILOT_PRECOMPILED_HEADERS_OFF
#include <PalmOS.h>
#include <PalmCompatibility.h>
#else
#include <Pilot.h>
#include <SysAll.h>
#endif
#include <Encrypt.h>

#include "blib.h"
#include "bits.h"
#include "CW.h"

// _OR_ bit operation for byte
#ifdef __STDC__
	Byte __orb( Byte a, Byte b)
#else
	Byte __orb(a,b)
	Byte a,b;
#endif
{
 return a|b;
}

// _OR_ bit operation for word
#ifdef __STDC__
	Word __orw( Word a, Word b)
#else
	Word __orw(a,b)
	Word a,b;
#endif
{
 return a|b;
}

// _OR_ bit operation for dword
#ifdef __STDC__
	DWord __ord( DWord a, DWord b)
#else
	DWord __ord(a,b)
	DWord a,b;
#endif
{
 return a|b;
}
//------------------------------------------------------------
// _AND_ bit operation for byte
#ifdef __STDC__
	Byte __andb( Byte a, Byte b)
#else
	Byte __andb(a,b)
	Byte a,b;
#endif
{
 return a&b;
}

// _AND_ bit operation for word
#ifdef __STDC__
	Word __andw( Word a, Word b)
#else
	Word __andw(a,b)
	Word a,b;
#endif
{
 return a&b;
}

// _AND_ bit operation for dword
#ifdef __STDC__
	DWord __andd( DWord a, DWord b)
#else
	DWord __andd(a,b)
	DWord a,b;
#endif
{
 return a&b;
}
//------------------------------------------------------------
// _XOR_ bit operation for byte
#ifdef __STDC__
	Byte __xorb( Byte a, Byte b)
#else
	Byte __xorb(a,b)
	Byte a,b;
#endif
{
 return a^b;
}

// _XOR_ bit operation for word
#ifdef __STDC__
	Word __xorw( Word a, Word b)
#else
	Word __xorw(a,b)
	Word a,b;
#endif
{
 return a^b;
}

// _XOR_ bit operation for dword
#ifdef __STDC__
	DWord __xord( DWord a, DWord b)
#else
	DWord __xord(a,b)
	DWord a,b;
#endif
{
 return a^b;
}
//------------------------------------------------------------
// _NOT_ bit operation for byte
#ifdef __STDC__
	Byte __notb( Byte a)
#else
	Byte __notb(a)
	Byte a;
#endif
{
 return ~a;
}

// _NOT_ bit operation for word
#ifdef __STDC__
	Word __notw( Word a)
#else
	Word __notw(a)
	Word a;
#endif
{
 return ~a;
}

// _NOT_ bit operation for dword
#ifdef __STDC__
	DWord __notd( DWord a)
#else
	DWord __notd(a)
	DWord a;
#endif
{
 return ~a;
}
//------------------------------------------------------------
// _SWAP_ litle endian
#ifdef __STDC__
	Word __swapw( Word a)
#else
	Word __swapw(a)
	Word a;
#endif
{
 volatile Word result,aa;
 result = 0;
 aa=a;
 *((Byte *)(&result)) = *(((Byte *)(&aa))+1);
 *(((Byte *)(&result))+1) = *((Byte *)(&aa));
 
 return result;
}

// _SWAP_ big endian
#ifdef __STDC__
	DWord __swapd(DWord a)
#else
	DWord __swapd(a)
	DWord a;
#endif
{
 volatile DWord result, aa;
 result = 0;
 aa=a;
 
 *(((Byte *)(&result))+0) = *(((Byte *)(&aa))+2);
 *(((Byte *)(&result))+1) = *(((Byte *)(&aa))+3);
 *(((Byte *)(&result))+2) = *(((Byte *)(&aa))+0);
 *(((Byte *)(&result))+3) = *(((Byte *)(&aa))+1);
 
 return result;
}

#ifdef __STDC__
	double __swapdb( double a)
#else
	double __swapdb(a)
	double a;
#endif
{
 volatile double result, aa;
 result = 0;
 aa=a;
 
 *(((Byte *)(&result))+0) = *(((Byte *)(&aa))+4);
 *(((Byte *)(&result))+1) = *(((Byte *)(&aa))+5);
 *(((Byte *)(&result))+2) = *(((Byte *)(&aa))+6);
 *(((Byte *)(&result))+3) = *(((Byte *)(&aa))+7);
 *(((Byte *)(&result))+4) = *(((Byte *)(&aa))+0);
 *(((Byte *)(&result))+5) = *(((Byte *)(&aa))+1);
 *(((Byte *)(&result))+6) = *(((Byte *)(&aa))+2);
 *(((Byte *)(&result))+7) = *(((Byte *)(&aa))+3);
 
 return result;
}

//------------------------------------------------------------
// _Shift_ bit operation for byte
#ifdef __STDC__
	Byte __shiftb( Byte a, Int16 s)
#else
	Byte __shiftb(a,s)
	Byte a;
	Int16 s;
#endif
{
 if (s < 0) return a>>(-s); else if ( s > 0 ) return a<<s; 
 return a;
}

// _Shift_ bit operation for word
#ifdef __STDC__
	Word __shiftw( Word a, Int16 s)
#else
	Word __shiftw(a,s)
	Word a;
	Int16 s;
#endif
{
 if (s < 0) return a>>(-s); else if ( s > 0 ) return a<<s; 
 return a;
}

// _Shift_ bit operation for dword
#ifdef __STDC__
	DWord __shiftd( DWord a, Int16 s)
#else
	DWord __shiftd(a,s)
	DWord a;
	Int16 s;
#endif
{
 if (s < 0) return a>>(-s); else if ( s > 0 ) return a<<s; 
 return a;
}
//------------------------------------------------------------
// _Sign Shift_ bit operation for byte
#ifdef __STDC__
	Byte __sshiftb( Byte a, Int16 s)
#else
	Byte __sshiftb(a,s)
	Byte a;
	Int16 s;
#endif
{
 Byte sign;
 sign = ((Byte)1)<<7;
 sign &= a;
 a ^= sign;
 if (s < 0)  a>>=(-s); else if ( s > 0 ) a<<=s; 
 a &= 0x7f;
 a |= sign;
 return a;
}

// _Sign Shift_ bit operation for word
#ifdef __STDC__
	Word __sshiftw( Word a, Int16 s)
#else
	Word __sshiftw(a,s)
	Word a;
	Int16 s;
#endif
{
 Word sign;
 sign = ((Word)1)<<15;
 sign &= a;
 a ^= sign;
 if (s < 0)  a>>=(-s); else if ( s > 0 ) a<<=s; 
 a &= 0x7fff;
 a |= sign;

 return a;
}

// _Sign Shift_ bit operation for dword
#ifdef __STDC__
	DWord __sshiftd( DWord a, Int16 s)
#else
	DWord __sshiftd(a,s)
	DWord a;
	Int16 s;
#endif
{
 DWord sign;
 sign = ((DWord)1)<<31;
 sign &= a;
 a ^= sign;
 if (s < 0)  a>>=(-s); else if ( s > 0 ) a<<=s; 
a &= 0x7fffffffL;
a |= sign;
 return a;
}
//------------------------------------------------------------
// _Cyclic Shift_ bit operation for byte
#ifdef __STDC__
	Byte __cshiftb( Byte a, Int16 s)
#else
	Byte __cshiftb(a,s)
	Byte a;
	Int16 s;
#endif
{
 Byte left,right;
 s %= 8; 
 if (s < 0)  
 {
  right = a >> (-s);
  left = a << (8 + s);
  a>>=s; 
 }else {if ( s > 0 )
 {
  left = a << s;
  right = a >> (8 - s);
 }  else return a;}

 return left|right;
}

// _Cyclic Shift_ bit operation for word
#ifdef __STDC__
	Word __cshiftw( Word a, Int16 s)
#else
	Word __cshiftw(a,s)
	Word a;
	Int16 s;
#endif
{
 Word left,right;
 s %= 16; 
 if (s < 0)  
 {
  right = a >> (-s);
  left = a << (16 + s);
  a>>=s; 
 }else {if ( s > 0 )
 {
  left = a << s;
  right = a >> (16 - s);
 }  else return a;}

 return left|right;
}

// _Cyclic Shift_ bit operation for dword
#ifdef __STDC__
	DWord __cshiftd( DWord a, Int16 s)
#else
	DWord __cshiftd(a,s)
	DWord a;
	Int16 s;
#endif
{
 DWord left,right;
 s %= 32; 
 if (s < 0)  
 {
  right = a >> (-s);
  left = a << (32 + s);
  a>>=s; 
 }else {if ( s > 0 )
 {
  left = a << s;
  right = a >> (32 - s);
 }  else return a;}

 return left|right;
}
//------------------------------------------------------------
// _GET_ bit operation for byte
#ifdef __STDC__
	Word __getbitb( Byte a, Word s)
#else
	Word __getbitb(a,s)
	Byte a;
	Word s;
#endif
{
 if (a &  ( ((Byte)(1)) <<s) ) return 1; else return 0;
}

// _GET_ bit operation for word
#ifdef __STDC__
	Word __getbitw( Word a, Word s)
#else
	Word __getbitw(a,s)
	Word a;
	Word s;
#endif
{
 if (a & (((Word)(1))<<s)) return 1; else return 0;
}

// _GET_ bit operation for dword
#ifdef __STDC__
	Word __getbitd( DWord a, Word s)
#else
	Word __getbitd(a,s)
	DWord a;
	Word s;
#endif
{
 if (a & (((DWord)(1))<<s)) return 1; else return 0;
}
//------------------------------------------------------------
// _SET_ bit operation for byte
#ifdef __STDC__
	Byte __setbitb( Byte a, Word s)
#else
	Byte __setbitb(a,s)
	Byte a;
	Word s;
#endif
{
 return (a |  ( ((Byte)(1)) <<s) ) ;
}

// _SET_ bit operation for word
#ifdef __STDC__
	Word __setbitw( Word a, Word s)
#else
	Word __setbitw(a,s)
	Word a;
	Word s;
#endif
{
 return (a | (((Word)(1))<<s)) ;
}

// _SET_ bit operation for dword
#ifdef __STDC__
	DWord __setbitd( DWord a, Word s)
#else
	DWord __setbitd(a,s)
	DWord a;
	Word s;
#endif
{
 return (a | (((DWord)(1))<<s)) ;
}
//------------------------------------------------------------
// _RESET_ bit operation for byte
#ifdef __STDC__
	Byte __resetbitb( Byte a, Word s)
#else
	Byte __resetbitb(a,s)
	Byte a;
	Word s;
#endif
{
 return (a &  ~(((Byte)(1)) <<s) ) ;
}

// _RESET_ bit operation for word
#ifdef __STDC__
	Word __resetbitw( Word a, Word s)
#else
	Word __resetbitw(a,s)
	Word a;
	Word s;
#endif
{
 return (a & ~(((Word)(1))<<s)) ;
}

// _RESET_ bit operation for dword
#ifdef __STDC__
	DWord __resetbitd( DWord a, Word s)
#else
	DWord __resetbitd(a,s)
	DWord a;
	Word s;
#endif
{
 return (a & ~(((DWord)(1))<<s)) ;
}
//------------------------------------------------------------
// _INVERSE_ bit operation for byte
#ifdef __STDC__
	Byte __inversebitb( Byte a, Word s)
#else
	Byte __inversebitb(a,s)
	Byte a;
	Word s;
#endif
{
 return (a ^ (((Byte)(1)) <<s) ) ;
}

// _INVERSE_ bit operation for word
#ifdef __STDC__
	Word __inversebitw( Word a, Word s)
#else
	Word __inversebitw(a,s)
	Word a;
	Word s;
#endif
{
 return (a ^ (((Word)(1))<<s)) ;
}

// _INVERSE_ bit operation for dword
#ifdef __STDC__
	DWord __inversebitd( DWord a, Word s)
#else
	DWord __inversebitd(a,s)
	DWord a;
	Word s;
#endif
{
 return (a ^ (((DWord)(1))<<s)) ;
}
//------------------------------------------------------------
// _EQV_ bit operation for byte
#ifdef __STDC__
	Byte __eqvb( Byte a, Byte b, Byte mask)
#else
	Byte __eqvb(a,b,mask)
	Byte a,b,mask;
#endif
{
 return (a ^ b) & mask ;
}

// _EQV_ bit operation for word
#ifdef __STDC__
	Word __eqvw( Word a, Word b, Word mask)
#else
	Word __eqvw(a,b,mask)
	Word a,b,mask;
#endif
{
 return (a ^ b) & mask ;
}

// _EQV_ bit operation for dword
#ifdef __STDC__
	DWord __eqvd( DWord a, DWord b, DWord mask)
#else
	DWord __eqvd(a,b,mask)
	DWord a,b,mask;
#endif
{
 return (a ^ b) & mask ;
}

//------------------------------------------------------------
// _SetLoWord_ word operation for dword
#ifdef __STDC__
	DWord __setloword( DWord a, Word ins)
#else
	DWord __setloword(a,ins)
	DWord a;
	Word ins;
#endif
{
 return ((a & 0xffff0000L) | ((DWord)(ins)));
}

// _SetHiWord_ word operation for dword
#ifdef __STDC__
	DWord __sethiword( DWord a, Word ins)
#else
	DWord __sethiword(a,ins)
	DWord a;
	Word ins;
#endif
{
 return  ((a%65536) | (((DWord)(ins))<<16));
}

// _SetLoByte_ byte operation for word
#ifdef __STDC__
	Word __setlobyte( Word a, Byte ins)
#else
	Word __setlobyte(a, ins)
	Word a;
	Byte ins;
#endif
{
 return  ((a & 0xff00) | ((Word)(ins))); 
}

// _SetHiByte_ byte operation for word
#ifdef __STDC__
	Word __sethibyte( Word a, Byte ins)
#else
	Word __sethibyte(a,ins)
	Word a;
	Byte ins;
#endif
{
 Word tmp;
 tmp = ins;
 tmp <<= 8;
 a %= 256;
 return  a|tmp;
}

//------------------------------------------------------------

// _GetLoWord_ word operation for dword
#ifdef __STDC__
	Word __getloword( DWord a)
#else
	Word __getloword(a)
	DWord a;
#endif
{
 return ((Word)(a%65536));
}
// _GetHiWord_ word operation for dword
#ifdef __STDC__
	Word __gethiword( DWord a)
#else
	Word __gethiword(a)
	DWord a;
#endif
{
 return ((Word)(a>>16));
}

// _GetLoByte_ byte operation for word
#ifdef __STDC__
	Byte __getlobyte( Word a)
#else
	Byte __getlobyte(a)
	Word a;
#endif
{
 a %= 256; // OK
 return (Byte)(a);
}

// _GetHiByte_ byte operation for word
#ifdef __STDC__
	Byte __gethibyte( Word a)
#else
	Byte __gethibyte(a)
	Word a;
#endif
{
 return ((Byte)(a>>8));
}


//------------------------------------------------------------
// _dec2hex_ operation for dword

#ifdef __STDC__
	DWord __dec2hex( DWord a)
#else
	DWord __dec2hex(a)
	DWord a;
#endif
{
 DWord div,res;
  div = 268435456L;// or 0x1000 0000
 res=0;
 while (div) 
 {
  res *=  10;
  res += a/div;
  a %= div;
  div >>=4;
 }
 return res;
}

// _hex2dec_ operation for dword
#ifdef __STDC__
	DWord __hex2dec( DWord a)
#else
	DWord __hex2dec(a)
	DWord a;
#endif
{
 DWord div,res;
 // max dec in hex -> 2576980377 or 0x9999 9999
 // start div       = 1000000000
 if (a>0x99999999L) return 0;
 div = 1000000000;
 res=0;
 while (div) 
 {
  res *=16;
  res += a/div;
  a %= div;
  div /=10;
 }
 return res;
}
// _bin2dec_ operation dword
#ifdef __STDC__
	DWord __bin2dec( DWord a)
#else
	DWord __bin2dec(a)
	DWord a;
#endif
{
// max dec        -> 42 9496 7295
// max bin in dec -> 11 1111 1111
// start div       = 10 0000 0000
 DWord div,res;
 div = 1000000000;
 res=0;
 while (div) 
 {
  res *=2;
  res += a/div;
  a %= div;
  div /=10;
 }
 return res;
}
// _dec2bin_ operation dword
#ifdef __STDC__
	DWord __dec2bin( DWord a)
#else
	DWord __dec2bin(a)
	DWord a;
#endif
{
// max dec        ->          42 9496 7295
// max dec in bin -> 1023 or  11 1111 1111b
// start div       = 512
 DWord div,res;
 if (a>1023) return 0;
 div = 512;
 res=0;
 while (div) 
 {
  res *=10;
  res += a/div;
  a %= div;
  div /=2;
 }
 return res;
}

//------------------------------------------------------------
// __CRC__32___
#if 0
	// Just exactly what part of "no globals in a shared library" do we not understand?  -EMP

const UInt32 crctt_32[ 256 ] =
{
0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL, 0x076dc419L, 0x706af48fL, 0xe963a535L, 0x9e6495a3L,
0x0edb8832L, 0x79dcb8a4L, 0xe0d5e91eL, 0x97d2d988L, 0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L, 0x90bf1d91L,
0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL, 0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L,
0x136c9856L, 0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL, 0x14015c4fL, 0x63066cd9L, 0xfa0f3d63L, 0x8d080df5L,
0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L, 0xa2677172L, 0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,
0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L, 0x32d86ce3L, 0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L,
0x26d930acL, 0x51de003aL, 0xc8d75180L, 0xbfd06116L, 0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L, 0xb8bda50fL,
0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L, 0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL,
0x76dc4190L, 0x01db7106L, 0x98d220bcL, 0xefd5102aL, 0x71b18589L, 0x06b6b51fL, 0x9fbfe4a5L, 0xe8b8d433L,
0x7807c9a2L, 0x0f00f934L, 0x9609a88eL, 0xe10e9818L, 0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,
0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL, 0x6c0695edL, 0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L,
0x65b0d9c6L, 0x12b7e950L, 0x8bbeb8eaL, 0xfcb9887cL, 0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L, 0xfbd44c65L,
0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L, 0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL,
0x4369e96aL, 0x346ed9fcL, 0xad678846L, 0xda60b8d0L, 0x44042d73L, 0x33031de5L, 0xaa0a4c5fL, 0xdd0d7cc9L,
0x5005713cL, 0x270241aaL, 0xbe0b1010L, 0xc90c2086L, 0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,
0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L, 0x59b33d17L, 0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL,
0xedb88320L, 0x9abfb3b6L, 0x03b6e20cL, 0x74b1d29aL, 0xead54739L, 0x9dd277afL, 0x04db2615L, 0x73dc1683L,
0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L, 0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L,
0xf00f9344L, 0x8708a3d2L, 0x1e01f268L, 0x6906c2feL, 0xf762575dL, 0x806567cbL, 0x196c3671L, 0x6e6b06e7L,
0xfed41b76L, 0x89d32be0L, 0x10da7a5aL, 0x67dd4accL, 0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,
0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L, 0xd1bb67f1L, 0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL,
0xd80d2bdaL, 0xaf0a1b4cL, 0x36034af6L, 0x41047a60L, 0xdf60efc3L, 0xa867df55L, 0x316e8eefL, 0x4669be79L,
0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L, 0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL,
0xc5ba3bbeL, 0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L, 0xc2d7ffa7L, 0xb5d0cf31L, 0x2cd99e8bL, 0x5bdeae1dL,
0x9b64c2b0L, 0xec63f226L, 0x756aa39cL, 0x026d930aL, 0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,
0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L, 0x92d28e9bL, 0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L,
0x86d3d2d4L, 0xf1d4e242L, 0x68ddb3f8L, 0x1fda836eL, 0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L, 0x18b74777L,
0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL, 0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L,
0xa00ae278L, 0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L, 0xa7672661L, 0xd06016f7L, 0x4969474dL, 0x3e6e77dbL,
0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L, 0x37d83bf0L, 0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,
0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L, 0xbad03605L, 0xcdd70693L, 0x54de5729L, 0x23d967bfL,
0xb3667a2eL, 0xc4614ab8L, 0x5d681b02L, 0x2a6f2b94L, 0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL, 0x2d02ef8dL
};

#endif
/************************************************************
 *
 * DESCRIPTION: Calculate the 32-bit CRC of a data block using the table
 *					lookup method.
 *
 * PARAMETERS:
 *		bufP				-- pointer to the data buffer;
 *		count				-- the number of bytes in the buffer;
 *		crc					-- the seed crc value;
 *
 * RETURNS:
 *		A 32-bit CRC for the data buffer.
 *
 *************************************************************/
#ifdef __STDC__
	UInt32 __crc32(UInt16 refNum, void * bufP, UInt16 count, UInt32 crc)
#else
	UInt32 __crc32(refNum, bufP,count,crc)
	UInt16 refNum;
	void * bufP;
	UInt16 count;
	UInt32 crc;
#endif
{
	Byte *	byteP = (Byte *)bufP;
	UInt32					temp1;
	UInt32					temp2;
	UInt32 *				crctt;
	BLibData *gP;
	char buf[20];

	gP = __prvLockGlobals(refNum);
	crctt= (UInt32 *)gP -> crctt_32;				// CRC translation table
	//
	// Calculate the 32 bit CRC using the table lookup method.
	//

	if ( count )
		{
		do	{
			temp1 = ( crc >> 8 ) & 0x00FFFFFFL;
			temp2 = crctt[ ((Int16)crc ^ *byteP++) & 0xff ];
			crc = temp1 ^ temp2;
			} while ( --count );
		}
		
    MemPtrUnlock(gP);

	return( crc );
}

/************************************************************
 * Encrypt Function Prototypes
 *************************************************************/
/*
// Perform reversible encryption or decryption of 8 byte string in
//  srcP using 8 byte key keyP. Place 8 byte result in dstP.
Err	EncDES(BytePtr srcP, BytePtr keyP, BytePtr dstP, Boolean encrypt)
			SYS_TRAP(sysTrapEncDES);


// Digest a string of bytes and produce a 128 bit result using
//   the MD4 algorithm.
Err	EncDigestMD4(BytePtr strP, Word strLen, Byte digestP[16])
			SYS_TRAP(sysTrapEncDigestMD4);


// Digest a string of bytes and produce a 128 bit result using
//   the MD5 algorithm.
Err	EncDigestMD5(BytePtr strP, Word strLen, Byte digestP[16])
			SYS_TRAP(sysTrapEncDigestMD5);
*/

#ifdef __STDC__
	UInt32 __encdes(BytePtr srcP, BytePtr keyP, BytePtr dstP, UInt16 encrypt)
#else
	UInt32 __encdes(srcP, keyP, dstP, encrypt)
	BytePtr srcP;
	BytePtr keyP;
	BytePtr dstP;
	UInt16  encrypt;
#endif
{
 EncDES(srcP,keyP,dstP, (unsigned char)(encrypt));
}

#ifdef __STDC__
	UInt32 __encmd4(BytePtr strP, Word strLen, Byte digestP[16])
#else
	UInt32 __encmd4(strP, strLen, digestP)
	BytePtr strP;
	Word strLen;
	Byte digestP[16];
#endif
{
  EncDigestMD4(strP, strLen, digestP);
}

#ifdef __STDC__
	UInt32 __encmd5(BytePtr strP, Word strLen, Byte digestP[16])
#else
	UInt32 __encmd5(strP, strLen, digestP)
	BytePtr strP;
	Word strLen;
	Byte digestP[16];
#endif
{
  EncDigestMD5(strP, strLen, digestP);
}
//------------------------------------------------
// __ VERSION __

UInt __version(void)
{	
	return BLibVersion;
}
//------------------------------------------------
// __puthexstr operation for dword

#ifdef __STDC__
	DWord __puthexstr( char* str)
#else
	DWord __puthexstr(str)
	char* str;
#endif
{
int len,i,d;
DWord res;

 
 len = StrLen(str);
 if (len>8) return (0xffffffff);
 for (i = 0; i<len; i++) 
 { if (str[i]>0x60) str[i]-=0x20;
   if (!( (str[i]>=0x30) && (str[i]<=0x39)
       || (str[i]>=0x41) && (str[i]<=0x46)))
    return (0xffffffff);
    }
 for (i = 0 , res=0; i<len; i++)
 {
  if ( (str[i]>=0x30) && (str[i]<=0x39) ) d=str[i]-0x30; else d=str[i]-0x41+10; 
  res*=16;
  res+=d;
 }
 return res;
}

// __gethexstr operation for dword
#ifdef __STDC__
	void __gethexstr( DWord a,char *res)
#else
	void __gethexstr(a)
	DWord a;
#endif
{
// number->string
DWord d;
int i;
char num;
 d = 0x10000000;
 if (a==0) {res[0]=0x30;res[1]=0; return;}
 while (a/d==0) d>>=4;
 i=0;
 do
 {
  if (a/d<10) num=a/d+0x30; else num= a/d+0x41-0xa;
  res[i++]=num;
  a%=d;
  d/=16;
 }while (d!=0);
 res[i]=0;
 //StrIToH(res,a);
 return;
}
//-------------------------------------------------------------------------------------
// __putbinstr operation for dword

#ifdef __STDC__
	DWord __putbinstr( char* str)
#else
	DWord __putbinstr(str)
	char* str;
#endif
{
int len,i,d;
DWord res;
 
 len = StrLen(str);
 if (len>32) return (0xffffffff);
 for (i = 0; i<len; i++) if (!( (str[i]==0x30) || (str[i]==0x31) )) return (0xffffffff);

 for (i = 0 , res=0; i<len; i++)
 {
  res*=2;
  res+=str[i]-0x30;
 }
 return res;
}

// __getbinstr operation for dword
#ifdef __STDC__
	void __getbinstr( DWord a,char *res)
#else
	void __getbinstr(a)
	DWord a;
#endif
{
// number->string
DWord d;
int i;
char num;
 d = 0x80000000;
 if (a==0) {res[0]=0x30;res[1]=0; return;}
 while (a/d==0) d>>=1;
 i=0;
 do
 {
  res[i++]=a/d+0x30;
  a%=d;
  d>>=1;
 }while (d!=0);
 res[i]=0;
 //StrIToH(res,a);
 return;
}

//**************************************************************
//*  New EncDES Encryption/Decryption routines for strings...
//**************************************************************
  
SWord __decryptData(unsigned char *key, unsigned char *src, unsigned char *dst, 
                    SWord len, char replaceNulls) {
    SWord           dstLen = 0;
    unsigned char   lastReplaced = 0;
    unsigned char   nextReplaced = 0;
    
    if (replaceNulls) {
	    while (1) {
    	    if (lastReplaced == 255 || lastReplaced >= len)
        	    break;
	        nextReplaced = src[lastReplaced];
    	    src[lastReplaced] = 0;
        	lastReplaced = nextReplaced;
	    }
	    len--;
        src++;
	}
	
    dst[0] = 0;
    while (dstLen < len) {
        EncDES(src, key, dst, 0);
        src += 8;
        dst += 8;
        dstLen += 8;
    } 
    
    if (replaceNulls)
        *dst = 0;
    return dstLen;
}

SWord __encryptData(unsigned char *key, unsigned char *src, unsigned char *dst, 
                  SWord len, char replaceNulls) {
    SWord           dstLen = 0;
    unsigned char   i;
    unsigned char   n;
    unsigned char   lastReplaced = 0;

    if (replaceNulls) {
        dst[0] = 255;
        dstLen++;
        len++;
    }
    while (dstLen < len) {
        EncDES(src, key, dst + dstLen, 1);
        if (replaceNulls)
            for (n = 0; n < 8; n++) {
                i = dstLen + n;
                if (dst[i] == 0) {
                    dst[lastReplaced] = i;
                    lastReplaced = i;
                    dst[i] = 255;
                }
            }
        dstLen += 8;
        src +=8;
    }
    if (replaceNulls)
        dst[dstLen] = 0;
    return dstLen;
}

static BLibData * __prvLockGlobals(UInt refNum) {
	BLibData            *gP = NULL;
	MemHandle			gH;
	SysLibTblEntryPtr	libEntryP;


	libEntryP = SysLibTblEntry(refNum);
	if (libEntryP)
		gH = (MemHandle)(libEntryP->globalsP);
	if (gH)
		gP = (BLibData *) MemHandleLock(gH);

	return(gP);
}

void __encryptDesString(UInt refNum,		// Lib ref num
                        char *decryptedStr,
                        char *encryptedStr) {
    SWord n;
    SWord len = 0;
    char  padAmt = 0;
	BLibData *gP;

	gP = __prvLockGlobals(refNum);

    StrNCopy((char *) gP->src, decryptedStr, 255);
    gP->src[255] = 0;
    if ((len = StrLen((char *) gP->src)) == 0) {
        StrCopy(encryptedStr, "");
        MemPtrUnlock(gP);
        return;
    }
    padAmt = len % 8;
    if (padAmt > 0) {
        padAmt = 8 - padAmt;
        n = len + padAmt;
        for (; len < n; len++)
            gP->src[len] = ' ';
    }
    if (gP->key[1] != NULL) {
        len = __encryptData(gP->key[0], gP->src, gP->dst, len, 0);
        len = __decryptData(gP->key[1], gP->dst, gP->src, len, 0);
        len = __encryptData(gP->key[2], gP->src, gP->dst, len, 1);
    }
    else
        len = __encryptData(gP->key[0], gP->src, gP->dst, len, 1);
    gP->dst[len++] = padAmt + 1;
    gP->dst[len] = 0;
    
    StrCopy(encryptedStr, (char *) gP->dst);
    MemPtrUnlock(gP);
}

void __decryptDesString(UInt refNum,		// Lib ref num
                        char *encryptedStr,
                        char *decryptedStr) {
    SWord len = 0;
    char  padAmt = 0;
	BLibData *gP;

	gP = __prvLockGlobals(refNum);
    StrNCopy((char *) gP->src, encryptedStr, 255);
    gP->src[255] = 0;
    if ((len = StrLen((char *) gP->src)) == 0) {
        StrCopy(decryptedStr, "");
        MemPtrUnlock(gP);
        return;
    }

    padAmt = len % 8;
    if (padAmt == 1)
        padAmt = 0;
    else
        padAmt = gP->src[--len] - 1;
    gP->src[len] = 0;
    if (gP->key[1] != NULL) {
        len = __decryptData(gP->key[2], gP->src, gP->dst, len, 1);
        len = __encryptData(gP->key[1], gP->dst, gP->src, len, 0);
        len = __decryptData(gP->key[0], gP->src, gP->dst, len, 0);
    }
    else
        len = __decryptData(gP->key[0], gP->src, gP->dst, len, 1);
    len -= padAmt;
    gP->dst[len] = 0;
    
    StrCopy(decryptedStr, (char *) gP->dst);
    
    MemPtrUnlock(gP);
}

void __setDesKey(DWord refNum,		// Lib ref num
                 char *keyStr) {
    SWord i;
    SWord n;
	BLibData *gP;

	gP = __prvLockGlobals(refNum);

    StrNCopy((char *) gP->keys, keyStr, 24);
    gP->keys[24] = 0;
    for (n = 1; n < 3; n++)
        gP->key[n] = NULL;
    gP->key[0] = gP->keys;
    if (StrLen((char *) gP->keys) > 8) {
        gP->key[1] = gP->keys + 8;
        if (StrLen((char *) gP->keys) > 16)
            gP->key[2] = gP->keys + 16;
    }
    if (gP->key[2] == NULL && gP->key[1] != NULL)
        gP->key[2] = gP->key[0];
 	for (n = 0; n < 3; n++)
        if (gP->key[n] != NULL)
            for (i = StrLen((char *) gP->key[n]); i < 8; i++)
                gP->key[n][i] = (unsigned char) i; 

    MemPtrUnlock(gP);
}
