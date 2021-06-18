//
//    NSBiQueGPS.h
//

#ifndef __NSBiQueGPS_H__
#define __NSBiQueGPS_H__

// Palm OS common definitions
#include <PalmTypes.h>
#include <SystemResources.h>

/********************************************************************
 * Creator ID, Type, and Name of THIS Shared Library
 ********************************************************************/
#define    THIS_LibCreatorID    'Ngps'
#define    THIS_LibTypeID       'libr'
#define    THIS_LibName          "NSBiQueGPS"

#define    MAX_INT_DATA_ITEMS   6
#define    MAX_FLOAT_DATA_ITEMS 10
#define    MAX_SAT_DATA_ITEMS   16
/************************************************************
 * Library result codes:
 * (appErrorClass is reserved for 3rd party apps/libraries.
 * It is defined in SystemMgr.h)
 *************************************************************/

#define THIS_ErrParam        (appErrorClass | 1)    // invalid parameter
#define THIS_ErrNotOpen      (appErrorClass | 2)    // library is not open
#define THIS_ErrStillOpen    (appErrorClass | 3)    // returned from THIS_LibClose() if
                                                    // the library is still open by others
#define THIS_ErrMemory       (appErrorClass | 4)    // memory error occurred

#ifdef BUILDING_THIS_LIB
    #define THIS_LIB_TRAP(trapNum)
#else
    #define THIS_LIB_TRAP(trapNum) SYS_TRAP(trapNum)
#endif

void LatLonToString(char *neswStr, Boolean showSeconds, Int32 value, Char *outStr);
char UTMLetterDesignator(double Lat);
void GetDatumParams(Int32 datumID, UInt32 *equatorialRadius, double *eccentricitySquared);
void LLtoUTM(UInt16 refNum, const UInt32 equatorialRadius, const double eccentricitySquared, 
             const double Lat, const double Long, 
			 double *UTMNorthing, double *UTMEasting, char *UTMZone);
void UTMtoLL(UInt16 refNum, UInt32 equatorialRadius, double eccentricitySquared,
             const char *UTMZone, const double UTMEasting, const double UTMNorthing,
			 double *Lat,  double *Long);
Err openMathLib(UInt16 refNum);
Err closeMathLib(UInt16 refNum);
Err GPSNotificationCallback(SysNotifyParamType *notifyParamsP);

#include "NSBiQueGPSPrototypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/*###################################################################
 #      S t a n d a r d ,  R E Q U I R E D    P r o t o t y p e s
 #*/

extern Err THIS_LibOpen(UInt16 refNum)
               THIS_LIB_TRAP(sysLibTrapOpen);
				
extern Err THIS_LibClose(UInt16 refNum)
               THIS_LIB_TRAP(sysLibTrapClose);

extern Err THIS_LibSleep(UInt16 refNum)
               THIS_LIB_TRAP(sysLibTrapSleep);

extern Err THIS_LibWake(UInt16 refNum)
               THIS_LIB_TRAP(sysLibTrapWake);

/*###################################################################*/

#ifdef __cplusplus 
}
#endif

#endif	// __NSBiQueGPS_H__

