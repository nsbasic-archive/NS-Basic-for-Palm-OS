/* MathLib: Pilot shared library of IEEE-754 double math functions
 *
 * Convenience functions for the calling application.  These functions
 * provide a programmer-friendly wrapper around the raw system trap
 * invocations which actually call the library routines.  The idea
 * is to allow the programmer to say:
 *    y = sqrt(x);
 * instead of requiring:
 *	   MathLibSqrt(MathLibRef, x, &y);
 * like the system trap interface requires.  The system trap form is
 * not only harder to read, but can't directly replace the traditional
 * function call in ported code, and can't be nested inside an expression.
 * Just add this source file to your project or makefile, and include
 * "MathLib.h" in any source file that needs to call these.
 *
 * The downside to these routines is that they'll take up some space
 * in your program, though CodeWarrior at least is smart enough to
 * only link in the ones which you actually use, so it doesn't really
 * cost you that much.  In fact, if you call these enough they'll pay
 * for themselves, since "x=sqrt(x)" generates much less code than
 * calling MathLibSqrt() directly.
 *
 * Copyright (C) 1997 Rick Huebner
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
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
#include <PalmOS.h>

#include "MathLib_Shlib.h"


double Racos(UInt16 MathLibRef, double x) {
	double result;
	MathLibACos(MathLibRef, x, &result);
	return result;
}

double Rasin(UInt16 MathLibRef, double x) {
	double result;
	MathLibASin(MathLibRef, x, &result);
	return result;
}

double Ratan(UInt16 MathLibRef, double x) {
	double result;
	MathLibATan(MathLibRef, x, &result);
	return result;
}

double Ratan2(UInt16 MathLibRef, double y, double x) {
	double result;
	MathLibATan2(MathLibRef, y, x, &result);
	return result;
}

double Rcos(UInt16 MathLibRef, double x) {
	double result;
	MathLibCos(MathLibRef, x, &result);
	return result;
}

double Rsin(UInt16 MathLibRef, double x) {
	double result;
	MathLibSin(MathLibRef, x, &result);
	return result;
}

double Rtan(UInt16 MathLibRef, double x) {
	double result;
	MathLibTan(MathLibRef, x, &result);
	return result;
}

void Rsincos(UInt16 MathLibRef, double x, double *sinx, double *cosx) {
	MathLibSinCos(MathLibRef, x, sinx, cosx);
}

double Rcosh(UInt16 MathLibRef, double x) {
	double result;
	MathLibCosH(MathLibRef, x, &result);
	return result;
}

double Rsinh(UInt16 MathLibRef, double x) {
	double result;
	MathLibSinH(MathLibRef, x, &result);
	return result;
}

double Rtanh(UInt16 MathLibRef, double x) {
	double result;
	MathLibTanH(MathLibRef, x, &result);
	return result;
}

double Racosh(UInt16 MathLibRef, double x) {
	double result;
	MathLibACosH(MathLibRef, x, &result);
	return result;
}

double Rasinh(UInt16 MathLibRef, double x) {
	double result;
	MathLibASinH(MathLibRef, x, &result);
	return result;
}

double Ratanh(UInt16 MathLibRef, double x) {
	double result;
	MathLibATanH(MathLibRef, x, &result);
	return result;
}

double Rexp(UInt16 MathLibRef, double x) {
	double result;
	MathLibExp(MathLibRef, x, &result);
	return result;
}

double Rfrexp(UInt16 MathLibRef, double x, Int16 *exponent) {
	double fraction;
	MathLibFrExp(MathLibRef, x, &fraction, exponent);
	return fraction;
}

double Rldexp(UInt16 MathLibRef, double x, Int16 exponent) {
	double result;
	MathLibLdExp(MathLibRef, x, exponent, &result);
	return result;
}

double Rlog(UInt16 MathLibRef, double x) {
	double result;
	MathLibLog(MathLibRef, x, &result);
	return result;
}

double Rlog10(UInt16 MathLibRef, double x) {
	double result;
	MathLibLog10(MathLibRef, x, &result);
	return result;
}

double Rmodf(UInt16 MathLibRef, double x, double *intpart) {
	double fraction;
	MathLibModF(MathLibRef, x, intpart, &fraction);
	return fraction;
}

double Rexpm1(UInt16 MathLibRef, double x) {
	double result;
	MathLibExpM1(MathLibRef, x, &result);
	return result;
}

double Rlog1p(UInt16 MathLibRef, double x) {
	double result;
	MathLibLog1P(MathLibRef, x, &result);
	return result;
}

double Rlogb(UInt16 MathLibRef, double x) {
	double result;
	MathLibLogB(MathLibRef, x, &result);
	return result;
}

double Rlog2(UInt16 MathLibRef, double x) {
	double result;
	MathLibLog2(MathLibRef, x, &result);
	return result;
}

double Rpow(UInt16 MathLibRef, double x, double y) {
	double result;
	MathLibPow(MathLibRef, x, y, &result);
	return result;
}

double Rpower10(UInt16 MathLibRef, double x, double y) {
	double result;
	MathLibPow(MathLibRef, (double) 10.0, y, &result);
	result = result * x;
	return result;
}

double Rsqrt(UInt16 MathLibRef, double x) {
	double result;
	MathLibSqrt(MathLibRef, x, &result);
	return result;
}

double Rhypot(UInt16 MathLibRef, double x, double y) {
	double result;
	MathLibHypot(MathLibRef, x, y, &result);
	return result;
}

double Rcbrt(UInt16 MathLibRef, double x) {
	double result;
	MathLibCbrt(MathLibRef, x, &result);
	return result;
}

double Rceil(UInt16 MathLibRef, double x) {
	double result;
	MathLibCeil(MathLibRef, x, &result);
	return result;
}

double Rfabs(UInt16 MathLibRef, double x) {
	double result;
	MathLibFAbs(MathLibRef, x, &result);
	return result;
}

double Rfloor(UInt16 MathLibRef, double x) {
	double result;
	MathLibFloor(MathLibRef, x, &result);
	return result;
}

double Rfmod(UInt16 MathLibRef, double x, double y) {
	double result;
	MathLibFMod(MathLibRef, x, y, &result);
	return result;
}

Int16 Risinf(UInt16 MathLibRef, double x) {
	Int16 result;
	MathLibIsInf(MathLibRef, x, &result);
	return result;
}

Int16 Rfinite(UInt16 MathLibRef, double x) {
	Int16 result;
	MathLibFinite(MathLibRef, x, &result);
	return result;
}

double Rscalbn(UInt16 MathLibRef, double x, Int16 exponent) {
	double result;
	MathLibScalBN(MathLibRef, x, exponent, &result);
	return result;
}

double Rdrem(UInt16 MathLibRef, double x, double y) {
	double result;
	MathLibDRem(MathLibRef, x, y, &result);
	return result;
}

double Rsignificand(UInt16 MathLibRef, double x) {
	double result;
	MathLibSignificand(MathLibRef, x, &result);
	return result;
}

double Rcopysign(UInt16 MathLibRef, double x, double y) {
	double result;
	MathLibCopySign(MathLibRef, x, y, &result);
	return result;
}

Int16 Risnan(UInt16 MathLibRef, double x) {
	Int16 result;
	MathLibIsNaN(MathLibRef, x, &result);
	return result;
}

Int16 Rilogb(UInt16 MathLibRef, double x) {
	Int16 result;
	MathLibILogB(MathLibRef, x, &result);
	return result;
}

double Rrint(UInt16 MathLibRef, double x) {
	double result;
	MathLibRInt(MathLibRef, x, &result);
	return result;
}

double Rnextafter(UInt16 MathLibRef, double x, double y) {
	double result;
	MathLibNextAfter(MathLibRef, x, y, &result);
	return result;
}

double Rremainder(UInt16 MathLibRef, double x, double y) {
	double result;
	MathLibRemainder(MathLibRef, x, y, &result);
	return result;
}

double Rscalb(UInt16 MathLibRef, double x, double exponent) {
	double result;
	MathLibScalB(MathLibRef, x, exponent, &result);
	return result;
}

double Rround(UInt16 MathLibRef, double x) {
	double result;
	MathLibRound(MathLibRef, x, &result);
	return result;
}

double Rtrunc(UInt16 MathLibRef, double x) {
	double result;
	MathLibTrunc(MathLibRef, x, &result);
	return result;
}

UInt32 Rsignbit(UInt16 MathLibRef, double x) {
	UInt32 result;
	MathLibSignBit(MathLibRef, x, &result);
	return result;
}
