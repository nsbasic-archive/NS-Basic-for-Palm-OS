/* MathLib: Pilot shared library of IEEE-754 double math functions
 *
 * Library function prototypes for the calling application.  This is
 * the file that the calling application should include in order to
 * get access to the routines in the library; it serves the same
 * function as the file "math.h" normally used on systems with
 * standard math libraries.  Each function in the library has two
 * prototypes listed; the first is for the programmer-friendly
 * wrapper function in MathLib.c, the second is for the raw SYS_TRAP()
 * invocation that actually calls the library routine.
 *
 * Copyright (C) 1997 Rick Huebner
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this program; see file COPYING.LIB.  If not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA
 *
 * Version 1.01, 23 August 1997, Rick Huebner
 */
#ifndef __MATHLIB_H__
#define __MATHLIB_H__

// Library name for use with SysLibFind()
#define MathLibName		"MathLib"
// Values for use with SysLibLoad()
#define LibType			'libr'
#define MathLibCreator	'MthL'

// This is the major version number of the library.  If new functions
// are added to this library, this version number must be incremented
// to protect programs which are compiled with this header from trying
// to invoke the new functions in an old version of MathLib.prc,
// which would be fatal.  Do NOT delete any functions from this list,
// or any older programs which try to use them will die.  Any changes
// other than adding new functions should be reflected in the minor
// part of the version number, e.g. 1.1 if a bug fix, 2.0 if new
// functions added.
#define MathLibVersion 1

// Possible Err values from MathLib functions
typedef enum MathLibErrorCode {
	mlErrNone = 0,
	mlErrOldVersion,	// library is older than version passed to open()
	mlErrNotOpen,		// close() without having called open() first
	mlErrNoMemory		// can't allocate global data block
} MathLibErrorCode;

// Library reference returned by SysLibFind() or SysLibLoad()
extern UInt16 MathLibRef;

/*****************************
 * Library control functions *
 *****************************/
Err MathLibOpen(UInt16 refnum, UInt16 version)		// Initialize library for use
	SYS_TRAP(sysLibTrapOpen);
Err MathLibClose(UInt16 refnum, UInt16* usecountP)// Free library resources when finished
	SYS_TRAP(sysLibTrapClose);
Err MathLibSleep(UInt16 refnum)					// Called by OS when Pilot sleeps
	SYS_TRAP(sysLibTrapSleep);
Err MathLibWake(UInt16 refnum)					// Called by OS when Pilot wakes
	SYS_TRAP(sysLibTrapWake);

/***************************
 * Trigonometric functions *
 ***************************/
#define acos(x)               Racos(gP->MathLibRef, x) 
#define asin(x)               Rasin(gP->MathLibRef, x)	
#define atan(x)               Ratan(gP->MathLibRef, x)	
#define atan2(y, x)           Ratan2(gP->MathLibRef, y, x)	
#define cos(x)                Rcos(gP->MathLibRef, x)	
#define sin(x)                Rsin(gP->MathLibRef, x)	
#define tan(x)                Rtan(gP->MathLibRef, x)	
#define sincos(x, sinx, cosx) Rsincos(gP->MathLibRef, x, sinx, cosx)	

/************************	
 * Hyperbolic functions	*
 ************************/ 
#define cosh(x)  Rcosh(gP->MathLibRef, x) 
#define sinh(x)  Rsinh(gP->MathLibRef, x)
#define tanh(x)  Rtanh(gP->MathLibRef, x)
#define acosh(x) Racosh(gP->MathLibRef, x)
#define asinh(x) Rasinh(gP->MathLibRef, x)
#define atanh(x) Ratanh(gP->MathLibRef, x)

/*****************************************
 * Exponential and logarithmic functions *
 *****************************************/
#define exp(x)             Rexp(gP->MathLibRef, x)
#define frexp(x, exponent) Rfrexp(gP->MathLibRef, x, exponent)
#define ldexp(x, exponent) Rldexp(gP->MathLibRef, x, exponent)
#define log(x)             Rlog(gP->MathLibRef, x)
#define log10(x)           Rlog10(gP->MathLibRef, x)
#define modf(x, intpart)   Rmodf(gP->MathLibRef, x, intpart)
#define expm1(x)           Rexpm1(gP->MathLibRef, x)
#define log1p(x)           Rlog1p(gP->MathLibRef, x)
#define logb(x)            Rlogb(gP->MathLibRef, x)
#define log2(x)            Rlog2(gP->MathLibRef, x)

/*******************
 * Power functions *
 *******************/	
#define pow(x, y)     Rpow(gP->MathLibRef, x, y)
#define power10(x, y) Rpower10(gP->MathLibRef, x, y)
#define sqrt(x)       Rsqrt(gP->MathLibRef, x)
#define hypot(x, y)   Rhypot(gP->MathLibRef, x, y)
#define cbrt(x)      Rcbrt(gP->MathLibRef, x)

/************************************************************
 * Nearest integer, absolute value, and remainder functions *
 ************************************************************/
#define ceil(x)     Rceil(gP->MathLibRef, x)
#define fabs(x)     Rfabs(gP->MathLibRef, x)
#define floor(x)    Rfloor(gP->MathLibRef, x)
#define fmod(x, y)  Rfmod(gP->MathLibRef, x, y)

/***************************
 * Miscellaneous functions *
 ***************************/
#define isinf(x)            Risinf(gP->MathLibRef, x)
#define finite(x)           Rfinite(gP->MathLibRef, x)
#define scalbn(x, exponent) Rscalbn(gP->MathLibRef, x, exponent)
#define drem(x, y)          Rdrem(gP->MathLibRef, x, y)
#define significand(x)      Rsignificand(gP->MathLibRef, x)
#define copysign(x, y)      Rcopysign(gP->MathLibRef, x, y)
#define isnan(x, y)         Risnan(gP->MathLibRef, x)
#define ilogb(x)            Rilogb(gP->MathLibRef, x)
#define rint(x)             Rrint(gP->MathLibRef, x)
#define nextafter(x)        Rnextafter(gP->MathLibRef, x, y)
#define remainder(x)        Rremainder(gP->MathLibRef, x, y)
#define scalb(x)            Rscalb(gP->MathLibRef, x, exponent)
#define round(x)            Rround(gP->MathLibRef, x)
#define trunc(x)            Rtrunc(gP->MathLibRef, x)
#define signbit(x)          Rsignbit(UInt16 MathLibRef, x)

/***************************
 * Trigonometric functions *
 ***************************/
double Racos(UInt16 MathLibRef, double x);				// Arc cosine of x 
double Rasin(UInt16 MathLibRef, double x);				// Arc sine of x	
double Ratan(UInt16 MathLibRef, double x);				// Arc tangent of x	
double Ratan2(UInt16 MathLibRef, double y, double x);	// Arc tangent of y/x	
double Rcos(UInt16 MathLibRef, double x);				// Cosine of x	
double Rsin(UInt16 MathLibRef, double x);				// Sine of x	
double Rtan(UInt16 MathLibRef, double x);				// Tangent of x	
void   Rsincos(UInt16 MathLibRef, double x, double *sinx, double *cosx); 	// Sine and cosine of x	

/************************	
 * Hyperbolic functions	*
 ************************/ 
double Rcosh(UInt16 MathLibRef, double x);				// Hyperbolic cosine of x 
double Rsinh(UInt16 MathLibRef, double x);				// Hyperbolic sine of x
double Rtanh(UInt16 MathLibRef, double x);				// Hyperbolic tangent of x
double Racosh(UInt16 MathLibRef, double x);				// Hyperbolic arc cosine of x
double Rasinh(UInt16 MathLibRef, double x);				// Hyperbolic arc sine of x
double Ratanh(UInt16 MathLibRef, double x);				// Hyperbolic arc tangent of x

/*****************************************
 * Exponential and logarithmic functions *
 *****************************************/
double Rexp(UInt16 MathLibRef, double x);					// Exponential function of x [pow(e,x)]
double Rfrexp(UInt16 MathLibRef, double x, Int16 *exponent);	// Break x into normalized fraction and an integral power of 2
double Rldexp(UInt16 MathLibRef, double x, Int16 exponent);	// x * pow(2,exponent)
double Rlog(UInt16 MathLibRef, double x);					// Natural logarithm of x
double Rlog10(UInt16 MathLibRef, double x);					// Base 10 logarithm of x
double Rmodf(UInt16 MathLibRef, double x, double *intpart);	// Break x into integral and fractional parts
double Rexpm1(UInt16 MathLibRef, double x);					// exp(x) - 1
double Rlog1p(UInt16 MathLibRef, double x);					// log(1+x)
double Rlogb(UInt16 MathLibRef, double x);					// Base 2 signed integral exponent of x
double Rlog2(UInt16 MathLibRef, double x);					// Base 2 logarithm of x

/*******************
 * Power functions *
 *******************/	
double Rpow(UInt16 MathLibRef, double x, double y);		// x to the y power [x**y]
double Rpower10(UInt16 MathLibRef, double x, double y);		// x to the y power [x**y]
double Rsqrt(UInt16 MathLibRef, double x);				// Square root of x [x**0.5]
double Rhypot(UInt16 MathLibRef, double x, double y);	// sqrt(x*x + y*y)	[hypotenuse of right triangle]
double Rcbrt(UInt16 MathLibRef, double x);				// Cube root of x	[x**(1/3)]

/************************************************************
 * Nearest integer, absolute value, and remainder functions *
 ************************************************************/
double Rceil(UInt16 MathLibRef, double x);				// Smallest integral value not less than x
double Rfabs(UInt16 MathLibRef, double x);				// Absolute value of x
double Rfloor(UInt16 MathLibRef, double x);				// Largest integral value not greater than x
double Rfmod(UInt16 MathLibRef, double x, double y);	// Modulo remainder of x/y

/***************************
 * Miscellaneous functions *
 ***************************/
Int16    Risinf(UInt16 MathLibRef, double x);					// Return 0 if x is finite or NaN, +1 if +Infinity, or -1 if -Infinity
Int16    Rfinite(UInt16 MathLibRef, double x);				// Return nonzero if x is finite and not NaN
double Rscalbn(UInt16 MathLibRef, double x, Int16 exponent);	// x * pow(2,exponent)
double Rdrem(UInt16 MathLibRef, double x, double y);		// Remainder of x/y
double Rsignificand(UInt16 MathLibRef, double x);			// Fractional part of x after dividing out ilogb(x)
double Rcopysign(UInt16 MathLibRef, double x, double y);	// Return x with its sign changed to match y's
Int16    Risnan(UInt16 MathLibRef, double x);					// Return nonzero if x is NaN (Not a Number)
Int16    Rilogb(UInt16 MathLibRef, double x);					// Binary exponent of non-zero x
double Rrint(UInt16 MathLibRef, double x);					// Integral value nearest x in direction of prevailing rounding mode
double Rnextafter(UInt16 MathLibRef, double x, double y);	// Next machine double value after x in the direction towards y
double Rremainder(UInt16 MathLibRef, double x, double y);	// Remainder of integer division x/y with infinite precision
double Rscalb(UInt16 MathLibRef, double x, double exponent);// x * pow(2,exponent)
double Rround(UInt16 MathLibRef, double x);					// Round x to nearest integral value away from zero
double Rtrunc(UInt16 MathLibRef, double x);					// Round x to nearest integral value not larger than x
UInt32  Rsignbit(UInt16 MathLibRef, double x);				// Return signbit of x's machine representation

/****************************************
 * Prototypes for the system traps that *
 * actually perform the library calls,  *
 * in the format mandated by the OS.    *
 ****************************************/
Err MathLibACos(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom);
Err MathLibASin(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+1);
Err MathLibATan(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+2);
Err MathLibATan2(UInt16 refnum, double y, double x, double *result)	SYS_TRAP(sysLibTrapCustom+3);
Err MathLibCos(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+4);
Err MathLibSin(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+5);
Err MathLibTan(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+6);
Err MathLibSinCos(UInt16 refnum, double x, double *sinx, double *cosx)	SYS_TRAP(sysLibTrapCustom+7);
Err MathLibCosH(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+8);
Err MathLibSinH(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+9);
Err MathLibTanH(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+10);
Err MathLibACosH(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+11);
Err MathLibASinH(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+12);
Err MathLibATanH(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+13);
Err MathLibExp(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+14);
Err MathLibFrExp(UInt16 refnum, double x, double *fraction, Int16 *exponent)	SYS_TRAP(sysLibTrapCustom+15);
Err MathLibLdExp(UInt16 refnum, double x, Int16 exponent, double *result)	SYS_TRAP(sysLibTrapCustom+16);
Err MathLibLog(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+17);
Err MathLibLog10(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+18);
Err MathLibModF(UInt16 refnum, double x, double *intpart, double *fracpart)	SYS_TRAP(sysLibTrapCustom+19);
Err MathLibExpM1(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+20);
Err MathLibLog1P(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+21);
Err MathLibLogB(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+22);
Err MathLibLog2(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+23);
Err MathLibPow(UInt16 refnum, double x, double y, double *result)	SYS_TRAP(sysLibTrapCustom+24);
Err MathLibSqrt(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+25);
Err MathLibHypot(UInt16 refnum, double x, double y, double *result)	SYS_TRAP(sysLibTrapCustom+26);
Err MathLibCbrt(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+27);
Err MathLibCeil(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+28);
Err MathLibFAbs(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+29);
Err MathLibFloor(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+30);
Err MathLibFMod(UInt16 refnum, double x, double y, double *result)	SYS_TRAP(sysLibTrapCustom+31);
Err MathLibIsInf(UInt16 refnum, double x, Int16 *result)	SYS_TRAP(sysLibTrapCustom+32);
Err MathLibFinite(UInt16 refnum, double x, Int16 *result)	SYS_TRAP(sysLibTrapCustom+33);
Err MathLibScalBN(UInt16 refnum, double x, Int16 exponent, double *result)	SYS_TRAP(sysLibTrapCustom+34);
Err MathLibDRem(UInt16 refnum, double x, double y, double *result)	SYS_TRAP(sysLibTrapCustom+35);
Err MathLibSignificand(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+36);
Err MathLibCopySign(UInt16 refnum, double x, double y, double *result)	SYS_TRAP(sysLibTrapCustom+37);
Err MathLibIsNaN(UInt16 refnum, double x, Int16 *result)	SYS_TRAP(sysLibTrapCustom+38);
Err MathLibILogB(UInt16 refnum, double x, Int16 *result)	SYS_TRAP(sysLibTrapCustom+39);
Err MathLibRInt(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+40);
Err MathLibNextAfter(UInt16 refnum, double x, double y, double *result)	SYS_TRAP(sysLibTrapCustom+41);
Err MathLibRemainder(UInt16 refnum, double x, double y, double *result)	SYS_TRAP(sysLibTrapCustom+42);
Err MathLibScalB(UInt16 refnum, double x, double exponent, double *result)	SYS_TRAP(sysLibTrapCustom+43);
Err MathLibRound(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+44);
Err MathLibTrunc(UInt16 refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+45);
Err MathLibSignBit(UInt16 refnum, double x, UInt32 *result)	SYS_TRAP(sysLibTrapCustom+46);
 
#endif // __MATHLIB_H__
