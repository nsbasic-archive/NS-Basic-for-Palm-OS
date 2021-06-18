//
//    NSBiQueGPS.c
//

#define SHLIB_FORMAT_2

#define VERSION 1.1
// MANUFACTURER GlowkaWare
// INFHELP ""
// INFHELP "NSBiQueGPS Shared Library"
// INFHELP ""
// INFHELP "This library provides an NSBasic wrapper library for the
// INFHELP "Garmin iQue 3600 GPS shared library.
// INFHELP ""
// INFHELP "Written by Ron Glowka, June 2004"
// INFHELP ""

#include <PalmOS.h>			// Includes all Palm OS headers
#include <SysGlue.h>
#include <FloatMgr.h>


/****************************************************************/
/* Purpose..: MUL.L d1,d0 ( unsigned or signed )				*/
/* Input....: operands in d0,d1									*/
/* Returns..: result in d0										*/
/****************************************************************/
asm long __lmul__(long left:__D0,long right:__D1):__D0;
asm long __lmul__(long left:__D0,long right:__D1):__D0
{	/* d0: operand a ; d1: operand b */
	machine	68020

	movem.l	d2-d3,-(sp)
	moveq	#2,d2		// special check for 68020+
	jmp		(pc,d2.w*2)
s20:	bra	s21
	mulu.l	d1,d0
	movem.l	(sp)+,d2-d3
	rts
s21:
	move.l	d0,d2
	swap	d2
	mulu.w	d1,d2		/* HiWord(a)*LoWord(b)->d2 */
	move.l	d1,d3
	swap	d3
	mulu.w	d0,d3		/* LoWord(a)*HiWord(b)->d3 */
	add.w	d3,d2		/* add the two results */
	swap	d2		/* and put LoWord of result in HiWord(d2) */
	clr.w	d2		/* clr LoWord(d2) */
	mulu	d1,d0		/* LoWord(a)*LoWord(b)->d0 */
	add.l	d2,d0		/* result:=d0+d2 */
	movem.l	(sp)+,d2-d3
	rts
}


#define BUILDING_THIS_LIB	// Defined in this file only...
#include "NSBiQueGPS.h"		// Library public definitions

#if defined(__GNUC__)
    #include "NSBiQueGPSDispatch.c"
#endif

#define THIS_REQUIRES_GLOBALS
#ifdef THIS_REQUIRES_GLOBALS
    #include "NSBiQueGPSGlobals.h"
#else
    #define THIS_ALLOCATE_GLOBALS
    #define THIS_FREE_GLOBALS
    #define THIS_ATTACH_GLOBALS
    #define THIS_DETACH_GLOBALS
#endif

#include <Garmin.h>
//#include <GarminChars.h>
#include <GPSLib.h>
#include <GPSLib68k.h>
#include <GPSLibSysTrapNums.h>
#ifndef pinMaxConstraintSize
	#define SetBits(b,len ) (((1U << ((len) - 1)) - 1U + (1U << ((len) - 1))) << (b))
    #define MaxSintVal(t) (SetBits(0, (sizeof(t) * 8) - 1))
    #define pinMaxConstraintSize    MaxSintVal(Coord)
#endif
#ifndef PinInputTriggerStateT16
    #define PinInputTriggerStateT16 UInt16
#endif

//#include <PenInputMgr.h>
//#include <PenInputMgrCommon.h>
//#include <PenInputMgrSelectorNums.h>
#include <PwrMgrLib68K.h>
#include "MathLib_Shlib.h"
#include "MathLib_Shlib.c"
#include "NSBiQueGPS_Contributed.c"

/********************************************************************
 *                     T H I S _ V e r s i o n
 ********************************************************************/
Int32 THIS_Version(UInt16 refNum, double *version) 
// DESC Returns the version number of the NSBiQueGPS Shared Library.
// BEFORE
{	
	
    *version = (double) VERSION;
    return 0;
}

/********************************************************************
 *                 T H I S _ C o m p i l e I n f o
 ********************************************************************/
Int32 THIS_CompileInfo(UInt16 refNum, char *compileDateTime) 
// DESC Returns the date and time that the NSBiQueGPS was compiled.
// BEFORE
{	
    char dateTime[21];
	
    StrCopy(dateTime, __DATE__);
    StrCat(dateTime, " ");
    StrCat(dateTime, __TIME__);
    StrCopy(compileDateTime, dateTime);

    return 0;
}

/********************************************************************
 *                 T H I S _ G P S L i b L o a d e d
 ********************************************************************/
Int32 THIS_GPSLibLoaded(UInt16 refNum, Int32 *loaded) 
// DESC Check to see if the Garmin iQue GPS shared library is loaded
// DESC and open.
// RETURNS 1 - the library is loaded and open and is ready to use.
// RETURNS 0 - the library is not loaded and no GPS functions should
// RETURNS     be called except for the GPSOpen() function.
// NOTES This function should always be called and the value returned
// NOTES should always be 1 before any other functions, except Version ()
// NOTES or CompileInfo(), in this library are called.
// BEFORE
{	
	THIS_ATTACH_GLOBALS

    *loaded = (Int32) gP->libLoaded;

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *           T H I S _ G P S G e t L i b A P I V e r s i o n
 ********************************************************************/
Int32 THIS_GPSGetLibAPIVersion(UInt16 refNum, Int32 *version) 
// DESC Returns the Garmin iQue Shared Library API Version number.
// DESC If the Garmin iQue Shared Library is not loaded, the
// DESC return value will be -1.
// BEFORE
{	
	THIS_ATTACH_GLOBALS

	if (gP->libLoaded)
	    *version = (Int32) GPSGetLibAPIVersion(gP->GPSLibRef);
	else
		*version = -1;

    THIS_DETACH_GLOBALS
    return 0;
}


/********************************************************************
 *                 T H I S _ G P S C l o s e
 ********************************************************************/
Int32 THIS_GPSClose(UInt16 refNum) 
// DESC Explicity close the GPS library. (See Notes)
// NOTES Normally, the GPS library is automatically closed when
// NOTES the NSBasic program gets terminated.  The GPSOpen()
// NOTES function must be called before any other GPS library
// NOTES functions are called after the GPS library has been closed.
// BEFORE
{	
	Err err;
	THIS_ATTACH_GLOBALS
	
	if (gP->libLoaded) {
	    err = GPSClose(gP->GPSLibRef);
	    if (err == gpsErrNone)
	        SysLibRemove(gP->GPSLibRef);
	    gP->libLoaded = false;
	}

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *                 T H I S _ G P S O p e n
 ********************************************************************/
Int32 THIS_GPSOpen(UInt16 refNum, Int32 *status) 
// DESC Explicity open the GPS library. (See Notes)
// RETURNS 1 if the library was opened succussfully.
// RETURNS 0 if the library could not be loaded or opened.
// NOTES Normally, the GPS library is automatically opened when
// NOTES the NSBasic program loads this library.  This function
// NOTES function must be called before any other GPS library
// NOTES functions are called after the GPS library has been closed.
// BEFORE
{	
	Err err;
	THIS_ATTACH_GLOBALS
	
	if (!gP->libLoaded) {
		gP->libLoaded = false;
		
		err = SysLibFind(gpsLibName, &gP->GPSLibRef);
		if (err != errNone) {
			err = SysLibLoad(gpsLibType, gpsLibCreator, &gP->GPSLibRef);
			if (err == errNone) {
			    err = GPSOpen(gP->GPSLibRef);
			    if (err != gpsErrNone) {
			        SysLibRemove(gP->GPSLibRef);
				    gP->libLoaded = false;
			    }
			    else
				    gP->libLoaded = true;
			}
		}
		else {
		    err = GPSOpen(gP->GPSLibRef);
		    if (err != gpsErrNone)
				gP->libLoaded = false;
			else		
				gP->libLoaded = true;
		}
	}
	
	*status = (Int32) gP->libLoaded;

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *           T H I S _ G P S G e t M a x S a t e l l i t e s
 ********************************************************************/
Int32 THIS_GPSGetMaxSatellites(UInt16 refNum, Int32 *maxSatellites) 
// DESC Get the maximum number of satellites that are currently
// DESC supported.
// RETURNS -1 if the Garmin iQue shared libary is not loaded and open.
// RETURNS nbr, the maximum number of satellites currently supported.
// BEFORE
{
	THIS_ATTACH_GLOBALS

	if (gP->libLoaded)
	    *maxSatellites = (Int32) GPSGetMaxSatellites(gP->GPSLibRef);
	else
		*maxSatellites = -1;

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *           T H I S _ G P S G e t P o s i t i o n
 ********************************************************************/
Int32 THIS_GPSGetPosition(UInt16 refNum, double *lat, double *lon,
                                         double *altMSL, double *altWGS84,
                                         Int32 *status) 
// DESC Get current position data.
// PARAM1  lat - latitude in degrees
// PARAM2  lon - longitude in degrees
// PARAM3  altMSL - altitude above mean sea level (meters)
// PARAM4  altWGS84 - altitude above WGS84 ellipsoid (meters)
// RETURNS 0 = gpsErrNone
// RETURNS     If the return status is not gpsErrNone (0), the data
// RETURNS     should be considered invalid.
// RETURNS 32769 = gpsErrNotOpen
// RETURNS 32770 = gpsErrStillOpen
// RETURNS 32771 = gpsErrMemory
// RETURNS 32772 = gpsErrNoData
// BEFORE Dim errString as String
// BEFORE
// AFTER If status <> 0 Then
// AFTER     errString = NQG.GetErrString(status)
// AFTER     MsgBox "GPSGetPosition error = " + errString
// AFTER End If
{	
    GPSPositionDataType position;
	THIS_ATTACH_GLOBALS

	if (gP->libLoaded) {
	    *status = (Int32) GPSGetPosition(gP->GPSLibRef, &position);
	    if (*status == (Int32) gpsErrNone) {
	        gP->lat = (Int32) position.lat;
	        gP->lon = (Int32) position.lon;
        	*lat = (double) position.lat * (double) ((double) 180.0 / (double) (2147483648.0));
        	*lon = (double) position.lon * (double) ((double) 180.0 / (double) (2147483648.0));
	        *altMSL = (double) position.altMSL;
	        *altWGS84 = (double) position.altWGS84;
	    }
	}
	else
		*status = gpsErrNotOpen;

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *           T H I S _ G P S G e t P V T
 ********************************************************************/
Int32 THIS_GPSGetPVT(UInt16 refNum, Int32 *mode, Int32 *fix,
                                    double *epe, double *eph, double *epv,
                                    double *lat, double *lon,
                                    double *altMSL, double *altWGS84,
                                    double *east, double *north, double *up,
                                    double *track, double *speed,
                                    Int32 *seconds, Int32 *fracSeconds,
                                    Int32 *status) 
// DESC Get current position, velocity, and time data.
// PARAM1 mode - mode type.  Values returned are:
// PARAM1     0 = gpsModeOff - GPS is off
// PARAM1     1 = gpsModeNormal - continuous satellite tracking
// PARAM1     2 = gpsModeBatSaver - periodic satellite tracking
// PARAM1     3 = gpsModeSim - simulated GPS information
// PARAM1     4 = gpsModeExternal - external source of GPS information
// PARAM2 fix - fix type.  Values returned are:
// PARAM2     0 = gpsFixUnusable - failed integrity check
// PARAM2     1 = gpsFixInvalid - invalid or unavailable
// PARAM2     2 = gpsFix2D - 2 dimension
// PARAM2     3 = gpsFix3D - 3 dimension
// PARAM2     4 = gpsFix2DDiff - 2 dimension differential
// PARAM2     5 = gpsFix3DDiff - 3 dimension differential
// PARAM3 epe - estimated position error, 1-sigma (meters)
// PARAM4 eph - epe, horizontal only (meters)
// PARAM5 epv - epe, vertical only (meters)
// PARAM6 lat - latitude in degrees 
// PARAM7 lon - longitude in degrees
// PARAM8 altMSL - altitude above mean sea level (meters)
// PARAM9 altWGS84 - altitude above WGS84 ellipsoid (meters)
// PARAM10 east - east (m/s)
// PARAM11 north - north (m/s)
// PARAM12 up - upwards (m/s)
// PARAM13 track - track (radians)
// PARAM14 speed - speed, horizontal only (m/s)
// PARAM15 seconds - seconds since midnight (UTC)
// PARAM16 fracSeconds - 0..1 second *2^32
// RETURNS 0 = gpsErrNone
// RETURNS     If the return status is not gpsErrNone (0), the data
// RETURNS     should be considered invalid.
// RETURNS 32769 = gpsErrNotOpen
// RETURNS 32770 = gpsErrStillOpen
// RETURNS 32771 = gpsErrMemory
// RETURNS 32772 = gpsErrNoData
// BEFORE Dim errString as String
// BEFORE
// AFTER If status <> 0 Then
// AFTER     errString = NQG.GetErrString(status)
// AFTER     MsgBox "GPSGetPVT error = " + errString
// AFTER End If
{	
    GPSPVTDataType pvt;
	THIS_ATTACH_GLOBALS

	if (gP->libLoaded) {
	    *status = (Int32) GPSGetPVT(gP->GPSLibRef, &pvt);
	    if (*status == (Int32) gpsErrNone) {
	        *mode = (Int32) pvt.status.mode;
	        *fix = (Int32) pvt.status.fix;
	        *epe = (double) pvt.status.epe;
	        *eph = (double) pvt.status.eph;
	        *epv = (double) pvt.status.epv;
	        gP->lat = (Int32) pvt.position.lat;
	        gP->lon = (Int32) pvt.position.lon;
        	*lat = (double) pvt.position.lat * (double) ((double) 180.0 / (double) (2147483648.0));
        	*lon = (double) pvt.position.lon * (double) ((double) 180.0 / (double) (2147483648.0));
	        *altMSL = (double) pvt.position.altMSL;
	        *altWGS84 = (double) pvt.position.altWGS84;
	        *east = (double) pvt.velocity.east;
	        *north = (double) pvt.velocity.north;
	        *up = (double) pvt.velocity.up;
	        *track = (double) pvt.velocity.track;
	        *speed = (double) pvt.velocity.speed;
	        *seconds = (Int32) pvt.time.seconds;
	        *fracSeconds = (Int32) pvt.time.fracSeconds;
	    }
	}
	else
		*status = gpsErrNotOpen;

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *           T H I S _ G P S G e t S t a t u s
 ********************************************************************/
Int32 THIS_GPSGetStatus(UInt16 refNum, Int32 *mode, Int32 *fix,
                                       double *epe, double *eph, double *epv, Int32 *status) 
// DESC Get current status data.
// PARAM1 mode - mode type.  Values returned are:
// PARAM1     0 = gpsModeOff - GPS is off
// PARAM1     1 = gpsModeNormal - continuous satellite tracking
// PARAM1     2 = gpsModeBatSaver - periodic satellite tracking
// PARAM1     3 = gpsModeSim - simulated GPS information
// PARAM1     4 = gpsModeExternal - external source of GPS information
// PARAM2 fix - fix type.  Values returned are:
// PARAM2     0 = gpsFixUnusable - failed integrity check
// PARAM2     1 = gpsFixInvalid - invalid or unavailable
// PARAM2     2 = gpsFix2D - 2 dimension
// PARAM2     3 = gpsFix3D - 3 dimension
// PARAM2     4 = gpsFix2DDiff - 2 dimension differential
// PARAM2     5 = gpsFix3DDiff - 3 dimension differential
// PARAM3 epe - estimated position error, 1-sigma (meters)
// PARAM4 eph - epe, horizontal only (meters)
// PARAM5 epv - epe, vertical only (meters)
// RETURNS 0 = gpsErrNone
// RETURNS     If the return status is not gpsErrNone (0), the data
// RETURNS     should be considered invalid.  
// RETURNS 32769 = gpsErrNotOpen
// RETURNS 32770 = gpsErrStillOpen
// RETURNS 32771 = gpsErrMemory
// RETURNS 32772 = gpsErrNoData
// BEFORE Dim errString as String
// BEFORE
// AFTER If status <> 0 Then
// AFTER     errString = NQG.GetErrString(status)
// AFTER     MsgBox "GPSGetStatus error = " + errString
// AFTER End If
{
    GPSStatusDataType gpsStatus;
	THIS_ATTACH_GLOBALS

	if (gP->libLoaded) {
	    *status = (Int32) GPSGetStatus(gP->GPSLibRef, &gpsStatus);
	    if (*status == (Int32) gpsErrNone) {
	        *mode = (Int32) gpsStatus.mode;
	        *fix = (Int32) gpsStatus.fix;
	        *epe = (double) gpsStatus.epe;
	        *eph = (double) gpsStatus.eph;
	        *epv = (double) gpsStatus.epv;
	    }
	}
	else
		*status = gpsErrNotOpen;

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *           T H I S _ G P S G e t T i m e
 ********************************************************************/
Int32 THIS_GPSGetTime(UInt16 refNum, Int32 *seconds, Int32 *fracSeconds,
                                     Int32 *status) 
// DESC Get current time data.
// PARAM1 seconds - seconds since midnight (UTC)
// PARAM2 fracSeconds - 0..1 second *2^32
// RETURNS 0 = gpsErrNone
// RETURNS     If the return status is not gpsErrNone (0), the data
// RETURNS     should be considered invalid.  
// RETURNS 32769 = gpsErrNotOpen
// RETURNS 32770 = gpsErrStillOpen
// RETURNS 32771 = gpsErrMemory
// RETURNS 32772 = gpsErrNoData
// BEFORE Dim errString as String
// BEFORE
// AFTER If status <> 0 Then
// AFTER     errString = NQG.GetErrString(status)
// AFTER     MsgBox "GPSGetTime error = " + errString
// AFTER End If
{	
    GPSTimeDataType gpsTime;
	THIS_ATTACH_GLOBALS

	if (gP->libLoaded) {
	    *status = (Int32) GPSGetTime(gP->GPSLibRef, &gpsTime);
	    if (*status == (Int32) gpsErrNone) {
	        *seconds = (Int32) gpsTime.seconds;
	        *fracSeconds = (Int32) gpsTime.fracSeconds;
	    }
	}
	else
		*status = gpsErrNotOpen;

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *           T H I S _ G P S G e t V e l o c i t y
 ********************************************************************/
Int32 THIS_GPSGetVelocity(UInt16 refNum, double *east, double *north, double *up,
                                         double *track, double *speed,
                                         Int32 *status) 
// DESC Get current velocity data.
// PARAM1 east - east (m/s)
// PARAM2 north - north (m/s)
// PARAM3 up - upwards (m/s)
// PARAM4 track - track (radians)
// PARAM5 speed - speed, horizontal only (m/s)
// RETURNS 0 = gpsErrNone
// RETURNS     If the return status is not gpsErrNone (0), the data
// RETURNS     should be considered invalid.  
// RETURNS 32769 = gpsErrNotOpen
// RETURNS 32770 = gpsErrStillOpen
// RETURNS 32771 = gpsErrMemory
// RETURNS 32772 = gpsErrNoData
// BEFORE Dim errString as String
// BEFORE
// AFTER If status <> 0 Then
// AFTER     errString = NQG.GetErrString(status)
// AFTER     MsgBox "GPSGetVelocity error = " + errString
// AFTER End If
{	
    GPSVelocityDataType velocity;
	THIS_ATTACH_GLOBALS

	if (gP->libLoaded) {
	    *status = (Int32) GPSGetVelocity(gP->GPSLibRef, &velocity);
	    if (*status == (Int32) gpsErrNone) {
	        *east = (double) velocity.east;
	        *north = (double) velocity.north;
	        *up = (double) velocity.up;
	        *track = (double) velocity.track;
	        *speed = (double) velocity.speed;
	    }
	}
	else
		*status = gpsErrNotOpen;

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *           T H I S _ G P S G e t S a t e l l i t e s
 ********************************************************************/
Int32 THIS_GPSGetSatellites(UInt16 refNum, Int32 satellite, 
                                           Int32 *svid, Int32 *statusBits,
                                           Int32 *snr, double *azimuth, 
                                           double *elevation,
                                           Int32 *status) 
// DESC Get current satellite data for the indicated satellite.
// PARAM1 satellite - (1..maxSatellites)
// PARAM2 svid - space vehicle identifier
// PARAM3 status bitfield
// PARAM3     bit 0 (bitmask 1) = gpsSatEphMask (ephemeris mask)
// PARAM3     bit 1 (bitmask 2) = gpsSatDifMask (differential mask)
// PARAM3     bit 2 (bitmask 4) = gpsSatUsedMask (used in solution mask)
// PARAM3     bit 3 (bitmask 8) = gpsSatRisingMask (rising mask)
// PARAM3     Note:  The GetSatStatusValues() in this library can be
// PARAM3            used to retrieve these individual bit values.
// PARAM4 snr - signal to noise ratio *100 (dB Hz)
// PARAM5 azimuth - azimuth (radians)
// PARAM6 elevation - elevation (radians)
// RETURNS 0 = gpsErrNone
// RETURNS     If the return status is not gpsErrNone (0), the data
// RETURNS     should be considered invalid. 
// RETURNS 32769 = gpsErrNotOpen
// RETURNS 32770 = gpsErrStillOpen
// RETURNS 32771 = gpsErrMemory
// RETURNS 32772 = gpsErrNoData
// RETURNS -1 = GPSGetMaxSatellites() returned <= 0
// BEFORE Dim errString as String
// BEFORE
// AFTER If status <> 0 Then
// AFTER     errString = NQG.GetErrString(status)
// AFTER     MsgBox "GPSGetSatellites error = " + errString
// AFTER End If
{	
    UInt8           maxSatellites;
	GPSSatDataType  sat[MAX_SAT_DATA_ITEMS];
	THIS_ATTACH_GLOBALS

	if (gP->libLoaded) {
	    maxSatellites = GPSGetMaxSatellites(gP->GPSLibRef);
	    if (satellite > 0 && satellite <= maxSatellites) {
		    if (maxSatellites > 0) {
				*status = (Int32) GPSGetSatellites(gP->GPSLibRef, sat);
	            if (*status == gpsErrNone) {
                    *svid = (Int32) sat[satellite - 1].svid;
                    if (*svid < (Int32) gpsInvalidSVID) {
                         *statusBits = (Int32) sat[satellite - 1].status;
                         *snr = (Int32) sat[satellite - 1].snr;
                         *azimuth = (double) sat[satellite - 1].azimuth;
                         *elevation = (double) sat[satellite - 1].elevation;
                    }
	            }
	    	}
	    	else
	    		*status = -2;
        }
        else
            *status = -1;
            
	}
	else
		*status = (Int32) gpsErrNotOpen;
	

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *           T H I S _ G e t L a t L o n S e m i c i r c l e s
 ********************************************************************/
Int32 THIS_GetLatLonSemicircles(UInt16 refNum, Int32 *lat, Int32 *  lon)
// DESC Return the latitude and longitude as expressed in semicircles 
// DESC (not degrees).  The return values from the Garmin library's 
// DESC GPSGetPosition() and GPSGetPVT() functions actually
// DESC return latitude and longitude as expressed in semicircles - not
// DESC degrees.  Except for this function, the other functions in this
// DESC library convert latitude and longitude to degrees.  This function 
// DESC retrieves the raw values returned from the Garmin Library's 
// DESC GPSGetPosition() and GPSGetPVT() functions.
// DESC 
// DESC The Garmin iQue 3600 Shared Library .h files documents the following:
// DESC
// DESC GPS Position Data Type
// DESC
// DESC The GPSPositionDataType uses integers to indicate latitude
// DESC and longitude in semicircles, where 2^31 semicircles equals
// DESC 180 degrees. North latitudes and East longitudes are
// DESC indicated with positive numbers; South latitudes and West
// DESC longitudes are indicated with negative numbers. The
// DESC following formulas show how to convert between degrees and
// DESC semicircles:
// DESC 
// DESC     degrees = semicircles * ( 180 / 2^31 ) 
// DESC
// DESC This is the equation used by this library for converting from
// DESC semicircles to degrees.
// PARAM1 lat - latitude in semicircles
// PARAM2 lon - longitude in semicircles
{	
	THIS_ATTACH_GLOBALS

	*lat = gP->lat;
	*lon = gP->lon;

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *           T H I S _ G e t L a t L o n D e g M i n
 ********************************************************************/
Int32 THIS_GetLatLonDegMin(UInt16 refNum, char *lat, char  *  lon)
// DESC Return the last retrieved latitude and longitude as expressed
// DESC in degrees and minutes (not decimal degrees). 
// DESC 
// DESC Example:  W097&deg08.957880'
// DESC
// PARAM1 lat - latitude in degrees and minutes
// PARAM2 lon - longitude in degrees and minutes
{	
    char tmpLat[24];
    char tmpLon[24];
	THIS_ATTACH_GLOBALS

	LatLonToString("NS", false, gP->lat, tmpLat);
	LatLonToString("EW", false, gP->lon, tmpLon);
	StrCopy(lat, tmpLat);
	StrCopy(lon, tmpLon);

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *           T H I S _ G e t L a t L o n D e g M i n S e c
 ********************************************************************/
Int32 THIS_GetLatLonDegMinSec(UInt16 refNum, char *lat, char  *  lon)
// DESC Return the last retrieved latitude and longitude as expressed
// DESC in degrees, minutes, and seconds (not decimal degrees).
// DESC  
// DESC Example: W097&deg08'57.472844"
// DESC
// PARAM1 lat - latitude in degrees, minutes, and seconds
// PARAM2 lon - longitude in degrees, minutes, and seconds
{	
    char tmpLat[24];
    char tmpLon[24];
	THIS_ATTACH_GLOBALS

	LatLonToString("NS", true, gP->lat, tmpLat);
	LatLonToString("EW", true, gP->lon, tmpLon);
	StrCopy(lat, tmpLat);
	StrCopy(lon, tmpLon);

    THIS_DETACH_GLOBALS
    return 0;
}
/********************************************************************
 *           T H I S _ G e t E r r S t r i n g
 ********************************************************************/
Int32 THIS_GetErrString(UInt16 refNum, Int32 status, char *errString) 
// DESC Returns a string interpretation of the passed status value.
// PARAM1 result status returned from a library call
// RETURNS "badCreatorID" if status is -2
// RETURNS "failure" if status is -1
// RETURNS "success" if status is gpsErrNone (0)
// RETURNS "gpsErrNotOpen" if status is gpsErrNotOpen (32769)
// RETURNS "gpsErrStillOpen" if staus is gpsErrStillOpen (32770)
// RETURNS "gpsErrMemory" if status is gpsErrMemory (32771)
// RETURNS "gspErrNoData" if status is gpsErrNoData (32772)
{	
    if (status == -1)
        StrCopy(errString, "failure");
    else if (status == -2)
        StrCopy(errString, "badCreatorID");
    else if (status == gpsErrNone)
        StrCopy(errString, "success");
    else if (status == gpsErrNotOpen)
        StrCopy(errString, "gpsErrNotOpen");
    else if (status == gpsErrStillOpen)
        StrCopy(errString, "gpsErrStillOpen");
    else if (status == gpsErrMemory)
        StrCopy(errString, "gpsErrMemory");
    else if (status == gpsErrNoData)
        StrCopy(errString, "gpsErrNoData");
    else
        StrIToA(errString, status);
    return 0;
}


/********************************************************************
 *           T H I S _ G e t M o d e S t r i n g
 ********************************************************************/
Int32 THIS_GetModeString(UInt16 refNum, Int32 mode, char *modeString) 
// DESC Returns a string interpretation of the passed status mode value.
// PARAM1 mode value returned from GPSGetStatus() or GPSGetPVT()
// RETURNS "Off" when mode is gpsModeOff (0)
// RETURNS "Continuous" when mode is gpsModeNormal (1)
// RETURNS "Periodic" when mode is gpsModeBatSaver (2)
// RETURNS "Simulated" when mode is gpsModeSim (3)
// RETURNS "External" when mode is gpsModeExternal (4)
{	
    if (mode == gpsModeOff)
        StrCopy(modeString, "Off");
    else if (mode == gpsModeNormal)
        StrCopy(modeString, "Continuous");
    else if (mode == gpsModeBatSaver)
        StrCopy(modeString, "Periodic");
    else if (mode == gpsModeSim)
        StrCopy(modeString, "Simulated");
    else if (mode == gpsModeExternal)
        StrCopy(modeString, "External");
    else
        StrIToA(modeString, mode);
    return 0;
}

/********************************************************************
 *           T H I S _ G e t F i x S t r i n g
 ********************************************************************/
Int32 THIS_GetFixString(UInt16 refNum, Int32 fix, char *fixString) 
// DESC Returns a string interpretation of the passed status fix value.
// PARAM1 fix value returned from GPSGetStatus() or GPSGetPVT()
// RETURNS "Unusable" when fix is gpsFixUnusable (0)
// RETURNS "Invalid" when fix is gpsFixInvalid (1)
// RETURNS "2D" when fix is gpsFix2D (2)
// RETURNS "3D" when fix is gpsFix3D (3)
// RETURNS "2DDiff" when fix is gspFix2DDiff (4)
// RETURNS "3DDiff" when fix is gspFix3DDiff (5)
{	
    if (fix == gpsFixUnusable)
        StrCopy(fixString, "Unusable");
    else if (fix == gpsFixInvalid)
        StrCopy(fixString, "Invalid");
    else if (fix == gpsFix2D)
        StrCopy(fixString, "2D");
    else if (fix == gpsFix3D)
        StrCopy(fixString, "3D");
    else if (fix == gpsFix2DDiff)
        StrCopy(fixString, "2DDiff");
    else if (fix == gpsFix3DDiff)
        StrCopy(fixString, "3DDiff");
    else
        StrIToA(fixString, fix);
    return 0;
}

/********************************************************************
 *           T H I S _ G e t S a t S t a t u s V a l u e s
 ********************************************************************/
Int32 THIS_GetSatStatusValues(UInt16 refNum, Int32 statusBits, 
                   Int32 *ephemeris, Int32 *differential, 
                   Int32 *used, Int32 *  rising) 
// DESC Returns the value of each of the status bitfield bits
// DESC returned by the GPSGetSatellites() function.
// PARAM2 returns 1 if the "ephemeris" bit is set, otherwise 0
// PARAM3 returns 1 if the "differential" bit is set, otherwise 0
// PARAM4 returns 1 if the "used in solution bit" is set,
// PARAM4     otherwise 0
// PARAM5 returns 1 if the "rising" bit is set, otherwise 0
{	
    *ephemeris = (Int32) (statusBits & (Int32) gpsSatEphMask);
    *differential = (Int32) (statusBits & (Int32) gpsSatDifMask);
    *used = (Int32) (statusBits & (Int32) gpsSatUsedMask);
    *rising = (Int32) (statusBits & (Int32) gpsSatRisingMask);
    if (*ephemeris)
        *ephemeris = 1;
    if (*differential)
        *differential = 1;
    if (*used)
        *used = 1;
    if (*rising)
        *rising = 1;
    return 0;
}

/********************************************************************
 *           T H I S _ C o n v e r t D o u b l e
 ********************************************************************/
Int32 THIS_ConvertDouble(UInt16 refNum, double originalValue,
                                        Int32 conversionType,
                                        double *convertedValue)
// DESC Returns a converted value based on the passed conversionType.
// PARAM1 original value
// PARAM2  1 = meters to inches
// PARAM2  2 = meters to feet
// PARAM2  3 = meters to miles
// PARAM2  4 = kilometers to miles
// PARAM2  5 = meters per second to miles per hour
// PARAM2  6 = meters per second to kilometers per hour
// PARAM2  7 = inches to meters
// PARAM2  8 = feet to meters
// PARAM2  9 = miles to meters
// PARAM2 10 = miles to kilometers
// PARAM2 11 = miles per hour to meters per second
// PARAM2 12 = kilometers per hour to meters per second
// RETURNS converted value
{	
    if (conversionType == 1)
        *convertedValue = (double) (originalValue * (double) 39.370078740157);
    else if (conversionType == 2)
        *convertedValue = (double) (originalValue * (double) 3.2808398950131);
    else if (conversionType == 3)
        *convertedValue = (double) (originalValue * (double) 0.00062137119223733);
    else if (conversionType == 4)
        *convertedValue = (double) (originalValue * (double) 0.62137119223733);
    else if (conversionType == 5)
        *convertedValue = (double) (originalValue * (double) 2.2369362920544);
    else if (conversionType == 6)
        *convertedValue = (double) (originalValue * (double) 3.6);
    else if (conversionType == 7)
        *convertedValue = (double) (originalValue * (double) 0.0254);
    else if (conversionType == 8)
        *convertedValue = (double) (originalValue * (double) 0.3048);
    else if (conversionType == 9)
        *convertedValue = (double) (originalValue * (double) 1609.344);
    else if (conversionType == 10)
        *convertedValue = (double) (originalValue * (double) 1.609344);
    else if (conversionType == 11)
        *convertedValue = (double) (originalValue * (double) 0.44704);
    else if (conversionType == 12)
        *convertedValue = (double) (originalValue * (double) 0.2777778);
    return 0;
}

/********************************************************************
 *           T H I S _ L a t L o n T o U T M
 ********************************************************************/
Int32 THIS_LatLonToUTM(UInt16 refNum, Int32 datumID,
                                      double lat,
                                      double lon,
                                      double *easting,
                                      double *northing,
                                      char *zone)
// DESC Converts latitude and longitude to UTM (Universal Transverse 
// DESC Mercator) coordinates.  The accuracy of the conversion, when
// DESC compared to another source such as a map, depends on the
// DESC "datum" (set of parameters) used by the other source.  The
// DESC following table shows the ID and parameters that can be used
// DESC for converting lat/lon to UTM coordinates.  ID 0 is probably
// DESC the best datum to use if you don't have a reference to 
// DESC another specific datum.
// DESC
// DESC <<table border=1 width="80%">><<FONT FACE="Helvetica" SIZE=1>>
// DESC   <<tr>><<td width="5%">><<b>>ID<</b>><</td>><<td width="25%">><<b>>Datum<</b>><</td>>
// DESC     <<td width="25%">><<b>>Equatorial Radius, meters<</b>><</td>><<td width="25%">><<b>>Eccentricity Squared<</b>><</td>><</tr>>
// DESC   <<tr>><<td width="5%">>0<</td>><<td width="45%">>WGS-84, GRS 1980, NAD83<</td>>
// DESC     <<td width="25%">>6378137<</td>><<td width="25%">>0.00669438<</td>><</tr>>
// DESC   <<tr>><<td width="5%">>1<</td>><<td width="45%">>Everest<</td>>
// DESC     <<td width="25%">>6377276<</td>><<td width="25%">>0.006637847<</td>><</tr>>
// DESC   <<tr>><<td width="5%">>2<</td>><<td width="45%">>Modified Everest<</td>>
// DESC     <<td width="25%">>6377304<</td>><<td width="25%">>0.006637847<</td>><</tr>>
// DESC   <<tr>><<td width="5%">>3<</td>><<td width="45%">>Modified Airy<</td>>
// DESC     <<td width="25%">>6377340<</td>><<td width="25%">>0.00667054<</td>><</tr>>
// DESC   <<tr>><<td width="5%">>4<</td>><<td width="45%">>Bessel 1841<</td>>
// DESC     <<td width="25%">>6377397<</td>><<td width="25%">>0.006674372<</td>><</tr>>
// DESC   <<tr>><<td width="5%">>5<</td>><<td width="45%">>Bessel 1841 (Nambia)<</td>>
// DESC     <<td width="25%">>6377484<</td>><<td width="25%">>0.006674372<</td>><</tr>>
// DESC   <<tr>><<td width="5%">>6<</td>><<td width="45%">>Airy<</td>>
// DESC     <<td width="25%">>6377563<</td>><<td width="25%">>0.00667054<</td>><</tr>>
// DESC   <<tr>><<td width="5%">>7<</td>><<td width="45%">>WGS-72<</td>>
// DESC     <<td width="25%">>6378135<</td>><<td width="25%">>0.006694318<</td>><</tr>>
// DESC   <<tr>><<td width="5%">>8<</td>><<td width="45%">>WGS-84, GRS 1980, NAD83<</td>>
// DESC     <<td width="25%">>6378137<</td>><<td width="25%">>0.00669438<</td>><</tr>>
// DESC   <<tr>><<td width="5%">>9<</td>><<td width="45%">>WGS 66<</td>>
// DESC     <<td width="25%">>6378145<</td>><<td width="25%">>0.006694542<</td>><</tr>>
// DESC   <<tr>><<td width="5%">>10<</td>><<td width="45%">>Fischer 1968<</td>>
// DESC     <<td width="25%">>6378150<</td>><<td width="25%">>0.006693422<</td>><</tr>>
// DESC   <<tr>><<td width="5%">>11<</td>><<td width="45%">>Modified Fischer 1960<</td>>
// DESC     <<td width="25%">>6378155<</td>><<td width="25%">>0.006693422<</td>><</tr>>
// DESC   <<tr>><<td width="5%">>12<</td>><<td width="45%">>Australian National, South American 1969, GRS 1967<</td>>
// DESC     <<td width="25%">>6378160<</td>><<td width="25%">>0.006694542<</td>><</tr>>
// DESC   <<tr>><<td width="5%">>13<</td>><<td width="45%">>WGS 60<</td>>
// DESC     <<td width="25%">>6378165<</td>><<td width="25%">>0.006693422<</td>><</tr>>
// DESC   <<tr>><<td width="5%">>14<</td>><<td width="45%">>Fischer 1960 (Mercury)<</td>>
// DESC     <<td width="25%">>6378166<</td>><<td width="25%">>0.006693422<</td>><</tr>>
// DESC   <<tr>><<td width="5%">>15<</td>><<td width="45%">>Helmert 1906<</td>>
// DESC     <<td width="25%">>6378200<</td>><<td width="25%">>0.006693422<</td>><</tr>>
// DESC   <<tr>><<td width="5%">>16<</td>><<td width="45%">>Clarke 1866<</td>>
// DESC     <<td width="25%">>6378206<</td>><<td width="25%">>0.006768658<</td>><</tr>>
// DESC   <<tr>><<td width="5%">>17<</td>><<td width="45%">>Krassovsky<</td>>
// DESC     <<td width="25%">>6378245<</td>><<td width="25%">>0.006693422<</td>><</tr>>
// DESC   <<tr>><<td width="5%">>18<</td>><<td width="45%">>Clarke 1880<</td>>
// DESC     <<td width="25%">>6378249<</td>><<td width="25%">>0.006803511<</td>><</tr>>
// DESC   <<tr>><<td width="5%">>19<</td>><<td width="45%">>Hough<</td>>
// DESC     <<td width="25%">>6378270<</td>><<td width="25%">>0.00672267<</td>><</tr>>
// DESC   <<tr>><<td width="5%">>20<</td>><<td width="45%">>International<</td>>
// DESC     <<td width="25%">>6378388<</td>><<td width="25%">>0.00672267<</td>><</tr>>
// DESC <</FONT>><</table>>

// PARAM1 see the description and datum table above
// PARAM2 latitude in decimal degrees
// PARAM3 longitude in decimal degrees
// PARAM4 UTM "easting" coordinate
// PARAM4     -1 is returned if MathLib is not available.
// PARAM5 UTM "northing" coordinate
// PARAM5     -1 is returned if MathLib is not available.
// RETURNS UTM "zone" identifier
// RETURNS     An empty string ("") if the datumID is invalid.
// RETURNS 
// RETURNS     The last character of the zone id is an indicator of the
// RETURNS     coordinate's hemisphere.  With the exception of "Z", if 
// RETURNS     it is "N" or greater, the coordinate is in the northern
// RETURNS     hemisphere.  Less than "N", the coordinate is in 
// RETURNS     the southern hemisphere.  If the last character is "Z",
// RETURNS     the coordinate is outside the UTM limits of latitude
// RETURNS     84&degN and 80&degS
{	
    UInt32 equatorialRadius;
    double eccentricitySquared;
    char   UTMZone[20];
    
    GetDatumParams(datumID, &equatorialRadius, &eccentricitySquared);       
    if (equatorialRadius != 0) {
        LLtoUTM(refNum, equatorialRadius, eccentricitySquared,
                        lat, lon,
                        easting, northing, UTMZone);
        StrCopy(zone, UTMZone);
    }
    else
    	StrCopy(zone, "");

    return 0;
}

/********************************************************************
 *           T H I S _ U T M T o L a t L o n
 ********************************************************************/
Int32 THIS_UTMToLatLon(UInt16 refNum, Int32 datumID,
                                      char *   zone,
                                      double easting,
                                      double northing,
                                      double *lat,
                                      double *  lon)
// DESC Converts UTM (Universal Transverse Mercator) coordinates
// DESC to latitude and longitude.  The accuracy of the 
// DESC conversion, when compared to another source such as a map, 
// DESC depends on the "datum" (set of parameters) used by the other 
// DESC source.  Please see the LatLonToUTM() function for a list
// DESC and description of the datums supported.  ID 0 is probably
// DESC the best datum to use if you don't have a reference to 
// DESC another specific datum.
// DESC
// PARAM1 see the description and datum table described for the 
// PARAM1     LatLonToUTM() function
// PARAM2 UTM "zone" identifier
// PARAM3 UTM "easting" coordinate
// PARAM4 UTM "northing" coordinate 
// PARAM5 latitude in decimal degrees
// PARAM5     -1 is returned if MathLib is not available or the
// PARAM5     datumID is invalid.
// PARAM6 longitude in decimal degrees
// PARAM6     -1 is returned if MathLib is not available or the
// PARAM6     datumID is invalid.
{	
    UInt32 equatorialRadius;
    double eccentricitySquared;
    
    GetDatumParams(datumID, &equatorialRadius, &eccentricitySquared);       
    if (equatorialRadius != 0) {
        UTMtoLL(refNum, equatorialRadius, eccentricitySquared,
                        zone, easting, northing,
                        lat, lon);
    }
    else {
        *lat = -1.0;
        *lon = -1.0;
    }

    return 0;
}

/********************************************************************
 *           T H I S _ U T M D i s t a n c e
 ********************************************************************/
Int32 THIS_UTMDistance(UInt16 refNum, 
                       char *   zone1, double easting1, double northing1,
                       char *   zone2, double easting2, double northing2,
                       char *ewDir, double *ewDist,
                       char *nsDir, double *nsDist, 
                       double *distance)
// DESC Returns the distances between two UTM coordinates.
// NOTES This function can only calculate distances between
// NOTES UTM coordinates if they are in the same zone. 
// PARAM1 UTM 1's zone
// PARAM2 UTM 1's easting coordinate
// PARAM3 UTM 1's northing coordinate
// PARAM4 UTM 2's zone
// PARAM5 UTM 2's easting coordinate
// PARAM6 UTM 2's northing coordinate
// PARAM7 returns "E" if UTM 2 is east of UTM 1, otherwise the
// PARAM7     return value is "W"
// PARAM8 east/west distance in meters
// PARAM9 returns "N" if UTM 2 is north of UTM 1, otherwise the
// PARAM9     return value is "S"
// PARAM10 north/south distance in meters
// RETURNS straight line distance between UTM 1 and UTM 2 in meters
// RETURNS    returns -1.0 if zone1 and zone2 are not equal.
{	
    THIS_ATTACH_GLOBALS
    
    if (StrCompare(zone1, zone2) == 0) {
        if (easting1 > easting2) {
            StrCopy(ewDir, "W");
            *ewDist = easting1 - easting2;
        }
        else {
            StrCopy(ewDir, "E");
            *ewDist = easting2 - easting1;
        }
        if (northing1 > northing2) {
            StrCopy(nsDir, "S");
            *nsDist = northing1 - northing2;
        }
        else {
            StrCopy(nsDir, "N");
            *nsDist = northing2 - northing1;
        }
        *distance = sqrt((*nsDist * *nsDist) + (*ewDist * *ewDist));
    }
    else
        *distance = -1.0;
        
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *           T H I S _ P w r S e t L o w P o w e r M o d e
 ********************************************************************/
Int32 THIS_PwrSetLowPowerMode(UInt16 refNum, char *   creatorID,
                                             Int32 enabled,
                                             Int32 *status)
// DESC Set or unset the LowPowerMode of the Garmin iQue 3600 device.
// DESC The Garmin SDK has this to say about "LowPowerMode":
// DESC
// DESC <<blockquote>> "<<b>><<u>><<I>>Low Power Mode:<</u>><</b>>
// DESC
// DESC When the iQue 3600 enters low power mode, the display and
// DESC backlight are turned off, while the processor, GPS, and audio
// DESC continue to operate normally.  Low power mode can be used to
// DESC extend the battery life while continuing to allow the unit 
// DESC to execute applications, such as an audio player.  If any 
// DESC application has enabled low power mode, while the auto-off time
// DESC has expired the iQue 3600 will enter low power mode instead of
// DESC powering off.  Low power mode is indicated by the LED blinking
// DESC briefly approximately every 10 seconds.  Note that low power
// DESC mode uses substantially more battery power than allowing the
// DESC unit to power off.
// DESC
// DESC If an application desires to have the iQue 3600 enter
// DESC low power mode when the auto-off time has expired, the
// DESC application should enable low power mode.  Low power 
// DESC mode will stay enabled until your application disables
// DESC it; therefore it is <<b>>extremely<</b>> important that
// DESC your application disables low power mode when it no longer
// DESC needs to be enabled.  Note that if your application
// DESC <<b>>disables<</b>> low power mode it does not 
// DESC guarantee that the unit will power off, as another 
// DESC application could also have low power mode enabled;
// DESC however if your application enables low power mode, it 
// DESC <<b>>does<</b>> guarantee that the unit will enter 
// DESC low power mode and will <<b>>not<</b>> power off."<</I>><</blockquote>>
// DESC
// DESC <<b>><<u>>NOTE:<</u>><</b>>  Unless the enable parameter 
// DESC is 2, this library will automatically disable the Low 
// DESC Power Mode setting for the <<u>>last<</u>> creator ID 
// DESC specified when this library is closed (ie. when the 
// DESC NSBasic program exits).  It is still important however, that
// DESC the correct actual creator Id of the NSBasic program is 
// DESC used for this function.
// DESC
// DESC This function only works on Palm OS software v.5.2.1r3 or higher.
// DESC To update your Garmin device, visit 
// DESC <<A HREF="https://www.garmin.com/support/download.jsp">>https://www.garmin.com/support/download.jsp<</A>> 
// DESC and choose the software updates for the iQue 3600.
// PARAM1 4 character creator ID of the NSBasic program
// PARAM2 0 = disable
// PARAM2 1 = enable
// PARAM2 2 = enable, but don't disable when this library closes
// RETURNS -2 if the creator ID is less than 4 characters
// RETURNS -1 if the Power Manager library couldn't be loaded
// RETURNS 0 if unsuccessful for some other reason
// RETURNS 1 if successful
// BEFORE
// BEFORE creatorID = "Nigt"    'NSBiQueGPS_Test creator ID
// BEFORE enabled = 1
{	
    Err err = 0;
    UInt32 nCreatorID;
    THIS_ATTACH_GLOBALS


    if (StrLen(creatorID) == 4) {
        nCreatorID = ((creatorID[0] * 16777216)
                    + (creatorID[1] * 65536)
                    + (creatorID[2] * 256)
                    +  creatorID[3]);
        gP->nCreatorID = nCreatorID;
    	err = SysLibFind(kPwrMgrLibName, &gP->PWRLibRef);
		if (err != errNone) {
			err = SysLibLoad(kPwrMgrLibType, kPwrMgrLibCreator, &gP->PWRLibRef);
			if (err ==  errNone) {
			    if (enabled)
			        *status = (Int32) PwrSetLowPowerMode(gP->PWRLibRef, nCreatorID, true);
			    else
			        *status = (Int32) PwrSetLowPowerMode(gP->PWRLibRef, nCreatorID, false);
			    gP->IloadedPWR = true;
			    gP->enabled = enabled;
			}
			else {
			    gP->nCreatorID = 0xFFFFFFFF;
			    *status = -1;
			}
		}
		else {
		    if (enabled)
		        *status = (Int32) PwrSetLowPowerMode(gP->PWRLibRef, nCreatorID, true);
		    else
		        *status = (Int32) PwrSetLowPowerMode(gP->PWRLibRef, nCreatorID, false);
		    gP->enabled = enabled;
		}
	}
	else {
	    gP->nCreatorID = 0xFFFFFFFF;
	    *status = -2;
    }
	
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *           G P S N o t i f i c a t i o n C a l l b a c k
 ********************************************************************/
Err GPSNotificationCallback(SysNotifyParamType *notifyParamsP)
{
    UInt16 refNum;
    UInt32 notifyEvent;
    EventType event;
    
    THIS_LibGlobalsPtr  gP;
    
    refNum = (UInt16) notifyParamsP->userDataP;
    gP = PrvLockGlobals(refNum);
   
    event.eType = 0;
    if (notifyParamsP->notifyType == sysNotifyDisplayResizedEvent) {
        event.eType = gP->displayResized;
    }
    else 
        if (notifyParamsP->notifyType == sysNotifyGPSDataEvent) {
            notifyEvent = (UInt32) notifyParamsP->notifyDetailsP;
            if (notifyEvent == gpsLocationChange)
                event.eType = gP->locationChange;
            if (notifyEvent == gpsStatusChange)
                event.eType = gP->statusChange;
            if (notifyEvent == gpsLostFix)
                event.eType = gP->lostFix;
            if (notifyEvent == gpsSatDataChange)
                event.eType = gP->satDataChange;
            if (notifyEvent == gpsModeChange)
                event.eType = gP->modeChange;
        }
    if (event.eType != 0)
        EvtAddEventToQueue(&event);
        
    MemPtrUnlock(gP); 
    return 0;
}

/********************************************************************
 *           T H I S _ R e g i s t e r N o t i f y E v e n t s
 ********************************************************************/
Int32 THIS_RegisterNotifyEvents(UInt16 refNum, Int32 locationChange,
                                               Int32 statusChange,
                                               Int32 lostFix,
                                               Int32 satDataChange,
                                               Int32 modeChange,
                                               Int32 displayResized)
// DESC Register with the Notification Manager to be notified when
// DESC the sysNotifyGPSDataEvent or sysNotifyDisplayResizedEvent
// DESC events occur.  When they do occur, an event for the specific
// DESC type of notification will be generated.  The parameters for 
// DESC this function specify the event number to generate.  A value 
// DESC of 0 disables event notification for that specific notification
// DESC type.  Parameter values should typically be in the custom
// DESC event number range (24576 to 32767).  These events can be 
// DESC "caught" with the NSBasic GetEventType() function.
// PARAM1 event number for gpsLocationChange - The GPS position has changed.
// PARAM2 event number for gpsStatusChange - The GPS status has changed.
// PARAM3 event number for gpsLostFix  - The quality of the GPS position
// PARAM3                                computation has become less than
// PARAM3                                two dimensional.
// PARAM4 event number for gpsSatDataChange - The GPS satellite data has
// PARAM4                                     changed.
// PARAM5 event number for gpsModeChange - The GPS mode has changed.
// PARAM6 event number for sysNotifyDisplayResizedEvent - The display has
// PARAM6                                                 been resized.
// EXAMPLE Sub Form1223_After()
// EXAMPLE
// EXAMPLE     'Register to have the following events generated:
// EXAMPLE     '   event number 30001 - location change
// EXAMPLE     '   event number 30002 - status change
// EXAMPLE     '   event number 30003 - lost fix
// EXAMPLE     '   event number 30004 - satellite data change
// EXAMPLE     '   event number 30005 - mode change
// EXAMPLE     '   event number 30006 - display was resized
// EXAMPLE
// EXAMPLE     NQG.RegisterNotifyEvents 30001, 30002, 30003, 30004, 30005, 30006
// EXAMPLE End Sub
// EXAMPLE
// EXAMPLE
// EXAMPLE Sub Form1239_Event()
// EXAMPLE     Dim event as Integer
// EXAMPLE     
// EXAMPLE     event = GetEventType()
// EXAMPLE     Select Case event
// EXAMPLE         Case 30001
// EXAMPLE             fldLocationChange.text = str(val(fldLocationChange.text) + 1)
// EXAMPLE         Case 30002
// EXAMPLE             fldStatusChange.text = str(val(fldStatusChange.text) + 1)
// EXAMPLE         Case 30003
// EXAMPLE             fldLostFix.text = str(val(fldLostFix.text) + 1)
// EXAMPLE         Case 30004
// EXAMPLE             fldSatDataChange.text = str(val(fldSatDataChange.text) + 1)
// EXAMPLE         Case 30005
// EXAMPLE             fldModeChange.text = str(val(fldModeChange.text) + 1)
// EXAMPLE         Case 30006
// EXAMPLE             fldDisplayResized.text = str(val(fldDisplayResized.text) + 1)
// EXAMPLE     End Select
// EXAMPLE End Sub
{
    THIS_ATTACH_GLOBALS
    
    if (gP->locationChange == 0 &&
        gP->statusChange == 0 &&
        gP->lostFix == 0 &&
        gP->satDataChange == 0 &&
        gP->modeChange == 0) {
        if (locationChange != 0 ||
            statusChange != 0 ||
            lostFix != 0 ||
            satDataChange != 0 ||
            modeChange != 0)
            SysNotifyRegister(gP->thisLibCard, gP->thisLibID,
                              sysNotifyGPSDataEvent,
                              GPSNotificationCallback,
                              sysNotifyNormalPriority,
                              (void *) refNum);
    }
	else
        if (locationChange == 0 &&
            statusChange == 0 &&
            lostFix == 0 &&
            satDataChange == 0 &&
            modeChange == 0)
	        SysNotifyUnregister(gP->thisLibCard, gP->thisLibID,
	                            sysNotifyGPSDataEvent,
	                            sysNotifyNormalPriority);
    if (gP->displayResized == 0) {
        if (displayResized != 0)
            SysNotifyRegister(gP->thisLibCard, gP->thisLibID,
                              sysNotifyDisplayResizedEvent,
                              GPSNotificationCallback,
                              sysNotifyNormalPriority,
                              (void *) refNum);
    }
	else
	    if (displayResized == 0)
	        SysNotifyUnregister(gP->thisLibCard, gP->thisLibID,
	                            sysNotifyDisplayResizedEvent,
	                            sysNotifyNormalPriority);

    gP->locationChange = locationChange;
    gP->statusChange = statusChange;
    gP->lostFix = lostFix;
    gP->satDataChange = satDataChange;
    gP->modeChange = modeChange;
    gP->displayResized = displayResized;
                                
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *           T H I S _ W i n G e t D i s p l a y E x t e n t
 ********************************************************************/
Int32 THIS_WinGetDisplayExtent(UInt16 refNum, Int32 *  x, Int32 *  y)
// DESC Return the current width and height of the display.
// RETURNS -1 - error.  The Pen Input Manager is not present on device.
{
    Coord extentX;
    Coord extentY;
    THIS_ATTACH_GLOBALS
    
    if (gP->penMgrAvailable) {
	    WinGetDisplayExtent(&extentX, &extentY);
	    *x = (Int32) extentX;
	    *y = (Int32) extentY;
    }
    else {
    	*x = -1;
    	*y = -1;
    }
    
    THIS_DETACH_GLOBALS
    return 0;
}
/********************************************************************
 *           T H I S _ W i n S e t D i s p l a y E x t e n t
 ********************************************************************/
Int32 THIS_WinSetDisplayExtent(UInt16 refNum, Int32 size)
// DESC Sets the display width and height to either <<i>>normal<</i>> or
// DESC <<i>>large<</i>>.  If the size is <<i>>large<</i>>, the form's 
// DESC Dynamic Input Area (DIA) Policy, Input Trigger, and Dynamic
// DESC Input Area values will be set to <<i>>custom<</i>>, 
// DESC <<i>>enabled<</i>>, and <<i>>closed<</i>> respectively.
// PARAM1 0 = normal - 160 pixels wide x 160 pixels high
// PARAM1 1 = large - 160 pixels wide x 225 pixels high
{
    THIS_ATTACH_GLOBALS
    
    if (gP->penMgrAvailable) {
	    if (size) {
			WinSetConstraintsSize(WinGetDisplayWindow(),
								  160, 160, 
								  pinMaxConstraintSize, 160, 
								  160, 160);
			FrmSetDIAPolicyAttr(FrmGetActiveForm(),
								frmDIAPolicyCustom);
			PINSetInputAreaState(pinInputAreaClosed);
			PINSetInputTriggerState(pinInputTriggerEnabled);
		}
		else {
			PINSetInputAreaState(pinInputAreaOpen);
			PINSetInputTriggerState(pinInputTriggerDisabled);
			FrmSetDIAPolicyAttr(FrmGetActiveForm(),
								frmDIAPolicyStayOpen);
			WinSetConstraintsSize(WinGetDisplayWindow(),
								  160, 160, 
								  160, 160, 
								  160, 160);
		}
	}

    THIS_DETACH_GLOBALS
	return 0;
}

/********************************************************************
 *           T H I S _ F r m G e t D I A P o l i c y
 ********************************************************************/
Int32 THIS_FrmGetDIAPolicy(UInt16 refNum, Int32 *value)
// DESC Returns the form's current Dynamic Input Area (DIA) Policy.
// DESC The DIA Policy controls whether the graffiti input area
// DESC may be collapsed or not.
// RETURNS 0 - frmDIAPolicyStayOpen.  The graffiti input area
// RETURNS                            is always open.  It cannot
// RETURNS                            be collapsed.
// RETURNS 1 - frmDIAPolicyCustom.  The graffiti input area is
// RETURNS                          collapsable.
// RETURNS -1 - error.  The Pen Input Manager is not present on device.
{
    THIS_ATTACH_GLOBALS
    
    if (gP->penMgrAvailable)
		*value = FrmGetDIAPolicyAttr(FrmGetActiveForm());
	else
		*value = -1;

    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *           T H I S _ F r m S e t D I A P o l i c y
 ********************************************************************/
Int32 THIS_FrmSetDIAPolicy(UInt16 refNum, Int32 value)
// DESC Sets the form's Dynamic Input Area (DIA) Policy. 
// DESC The DIA Policy controls whether the graffiti input area
// DESC may be collapsed or not.
// PARAM1 0 - frmDIAPolicyStayOpen.  The graffiti input area
// PARAM1                            is always open.  It cannot
// PARAM1                            be collapsed.
// PARAM1 1 - frmDIAPolicyCustom.  The graffiti input area is
// PARAM1                          collapsable.
{
    THIS_ATTACH_GLOBALS
    
    if (gP->penMgrAvailable) {
	    if (value)
			FrmSetDIAPolicyAttr(FrmGetActiveForm(),
								frmDIAPolicyCustom);
		else
			FrmSetDIAPolicyAttr(FrmGetActiveForm(),
								frmDIAPolicyStayOpen);
	}

    THIS_DETACH_GLOBALS
	return 0;
}

/********************************************************************
 *           T H I S _ P I N G e t D I A S t a t e
 ********************************************************************/
Int32 THIS_PINGetDIAState(UInt16 refNum, Int32 *value)
// DESC Returns the current Dynamic Input Area (DIA) state. 
// RETURNS 0 - pinInputAreaOpen.  The Dynamic Input Area is displayed.
// RETURNS 1 - pinInputAreaClosed.  The Dynamic Input Area is not
// RETURNS                          being displayed.
// RETURNS 2 - pinInputAreaNone.  There is no Dynamic Input Area.
// RETURNS -1 - error.  The Pen Input Manager is not present on device.
{
    THIS_ATTACH_GLOBALS
    
    if (gP->penMgrAvailable)
		*value = (Int32) PINGetInputAreaState();
	else
		*value = -1;

    THIS_DETACH_GLOBALS
	return 0;
}

/********************************************************************
 *           T H I S _ P I N S e t D I A S t a t e
 ********************************************************************/
Int32 THIS_PINSetDIAState(UInt16 refNum, Int32 value)
// DESC Sets the current Dynamic Input Area (DIA) state. 
// PARAM1 0 - pinInputAreaOpen.  The Dynamic Input Area will be displayed.
// PARAM1 1 - pinInputAreaClosed.  The Dynamic Input Area will not
// PARAM1                          be displayed.
// PARAM1 2 - pinInputAreaNone.  There is no Dynamic Input Area.
{
    THIS_ATTACH_GLOBALS
    
    if (gP->penMgrAvailable)
		PINSetInputAreaState((PinInputTriggerStateT16) value);

    THIS_DETACH_GLOBALS
	return 0;
}

/********************************************************************
 *     T H I S _ P I N G e t I n p u t T r i g g e r S t a t e
 ********************************************************************/
Int32 THIS_PINGetInputTriggerState(UInt16 refNum, Int32 *value)
// DESC Returns the current Input Trigger state. 
// RETURNS 0 - pinInputTriggerEnabled.   The status bar icon is enabled,
// RETURNS                               meaning that the user is allowed
// RETURNS                               to open and close the Dynamic
// RETURNS                               Input Area.
// RETURNS 1 - pinInputTriggerDisabled.  The status bar icon is disabled,
// RETURNS                               meaning that the user is not
// RETURNS                               allowed to open and close the
// RETURNS                               Dynamic Input Area.
// RETURNS 2 - pinInputTriggerNone.   There is no Dynamic Input Area.
// RETURNS -1 - error.  The Pen Input Manager is not present on device.
{
    THIS_ATTACH_GLOBALS
    
    if (gP->penMgrAvailable)
		*value = (Int32) PINGetInputTriggerState();
	else
		*value = -1;

    THIS_DETACH_GLOBALS
	return 0;
}

/********************************************************************
 *     T H I S _ P I N S e t I n p u t T r i g g e r S t a t e
 ********************************************************************/
Int32 THIS_PINSetInputTriggerState(UInt16 refNum, Int32 value)
// DESC Sets the current Input Trigger state. 
// PARAM1 0 - pinInputTriggerEnabled.   Enable the status bar icon,
// PARAM1                               meaning that the user is allowed
// PARAM1                               to open and close the Dynamic
// PARAM1                               Input Area.
// PARAM1 1 - pinInputTriggerDisabled.  Disable the status bar icon,
// PARAM1                               meaning that the user is not
// PARAM1                               allowed to open and close the
// PARAM1                               Dynamic Input Area.
// PARAM1 2 - pinInputTriggerNone.   There is no Dynamic Input Area.
{
    THIS_ATTACH_GLOBALS
    
    if (gP->penMgrAvailable)
		PINSetInputTriggerState((PinInputTriggerStateT16) value);

    THIS_DETACH_GLOBALS
	return 0;
}

/*###################################################################
 #       S t a n d a r d ,  R E Q U I R E D    F u n c t i o n s
 #*/

Err THIS_LibOpen(UInt16 refNum) {
    Err err = 0;
    UInt16  i;
    THIS_ALLOCATE_GLOBALS	// Define local variables before this
	
	gP->libLoaded = false;
	gP->penMgrAvailable = true;

    for (i = 0; i < MemNumCards(); i++)
        if ((gP->thisLibID = DmFindDatabase(i, THIS_LibName)) != 0) {
            gP->thisLibCard = i;
            break;
        }
            
	err = FtrGet(pinCreator, pinFtrAPIVersion, &gP->penMgrAPIVersion);
    if (err == ftrErrNoSuchFeature)
        gP->penMgrAvailable = false;
        
	err = SysLibFind(gpsLibName, &gP->GPSLibRef);
	if (err != errNone) {
		err = SysLibLoad(gpsLibType, gpsLibCreator, &gP->GPSLibRef);
		if (err == errNone) {
		    err = GPSOpen(gP->GPSLibRef);
		    if (err != gpsErrNone) {
		        SysLibRemove(gP->GPSLibRef);
			    gP->libLoaded = false;
		    }
		    else
			    gP->libLoaded = true;
		}
	}
	else {
	    err = GPSOpen(gP->GPSLibRef);
	    if (err != gpsErrNone)
			gP->libLoaded = false;
		else		
			gP->libLoaded = true;

	}
    err = SysLibFind(MathLibName, &gP->MathLibRef);
    if (err != errNone) {
        err = SysLibLoad(LibType, MathLibCreator, &gP->MathLibRef);
		if (err == errNone) {
		    err = MathLibOpen(gP->MathLibRef, MathLibVersion);
		    if (err != errNone) {
		        SysLibRemove(gP->MathLibRef);
			    gP->mathLibLoaded = false;
		    }
		    else
			    gP->mathLibLoaded = true;
		}
	}
	else {
	    err = MathLibOpen(gP->MathLibRef, MathLibVersion);
	    if (err != errNone)
			gP->mathLibLoaded = false;
		else		
			gP->mathLibLoaded = true;
	}
	
    return err;
}

Err THIS_LibClose(UInt16 refNum) {
    THIS_FREE_GLOBALS	// Define local variables before this

    return err;
}

Err THIS_LibSleep(UInt16 refNum) {
    return 0;
}

Err THIS_LibWake(UInt16 refNum) {
    return 0;
}

/*###################################################################*/
