//
//    NSBiQueGPSPrototypes.h
//

#ifndef __NSBiQueGPSPrototypes_H__
#define __NSBiQueGPSPrototypes_H__

typedef enum {
    THIS_TrapVersion = sysLibTrapCustom,
    THIS_TrapCompileInfo,
    THIS_TrapGPSLibLoaded,
    THIS_TrapGPSGetLibAPIVersion,
    THIS_TrapGPSClose,
    THIS_TrapGPSOpen,
    THIS_TrapGPSGetMaxSatellites,
    THIS_TrapGPSGetPosition,
    THIS_TrapGPSGetPVT,
    THIS_TrapGPSGetStatus,
    THIS_TrapGPSGetTime,
    THIS_TrapGPSGetVelocity,
    THIS_TrapGPSGetSatellites,
    THIS_TrapGetLatLonSemicircles,
    THIS_TrapGetLatLonDegMin,
    THIS_TrapGetLatLonDegMinSec,
    THIS_TrapGetErrString,
    THIS_TrapGetModeString,
    THIS_TrapGetFixString,
    THIS_TrapGetSatStatusValues,
    THIS_TrapConvertDouble,
    THIS_TrapLatLonToUTM,
    THIS_TrapUTMToLatLon,
    THIS_TrapUTMDistance,
    THIS_TrapPwrSetLowPowerMode,
    THIS_TrapRegisterNotifyEvents,
    THIS_TrapWinGetDisplayExtent,
    THIS_TrapWinSetDisplayExtent,
    THIS_TrapFrmGetDIAPolicy,
    THIS_TrapFrmSetDIAPolicy,
    THIS_TrapPINGetDIAState,
    THIS_TrapPINSetDIAState,
    THIS_TrapPINGetInputTriggerState,
    THIS_TrapPINSetInputTriggerState,

    THIS_TrapEnumLast
} THIS_TrapEnum;

#ifdef __cplusplus
extern "C" {
#endif

extern Int32 THIS_Version(UInt16 refNum, double *version)
                THIS_LIB_TRAP(THIS_TrapVersion);

extern Int32 THIS_CompileInfo(UInt16 refNum, char *compileDateTime)
                THIS_LIB_TRAP(THIS_TrapCompileInfo);

extern Int32 THIS_GPSLibLoaded(UInt16 refNum, Int32 *loaded)
                THIS_LIB_TRAP(THIS_TrapGPSLibLoaded);

extern Int32 THIS_GPSGetLibAPIVersion(UInt16 refNum, Int32 *version)
                THIS_LIB_TRAP(THIS_TrapGPSGetLibAPIVersion);

extern Int32 THIS_GPSClose(UInt16 refNum)
                THIS_LIB_TRAP(THIS_TrapGPSClose);

extern Int32 THIS_GPSOpen(UInt16 refNum, Int32 *status)
                THIS_LIB_TRAP(THIS_TrapGPSOpen);

extern Int32 THIS_GPSGetMaxSatellites(UInt16 refNum, Int32 *maxSatellites)
                THIS_LIB_TRAP(THIS_TrapGPSGetMaxSatellites);

extern Int32 THIS_GPSGetPosition(UInt16 refNum, double *lat, double *lon,
                                         double *altMSL, double *altWGS84,
                                         Int32 *status)
                THIS_LIB_TRAP(THIS_TrapGPSGetPosition);

extern Int32 THIS_GPSGetPVT(UInt16 refNum, Int32 *mode, Int32 *fix,
                                    double *epe, double *eph, double *epv,
                                    double *lat, double *lon,
                                    double *altMSL, double *altWGS84,
                                    double *east, double *north, double *up,
                                    double *track, double *speed,
                                    Int32 *seconds, Int32 *fracSeconds,
                                    Int32 *status)
                THIS_LIB_TRAP(THIS_TrapGPSGetPVT);

extern Int32 THIS_GPSGetStatus(UInt16 refNum, Int32 *mode, Int32 *fix,
                                       double *epe, double *eph, double *epv, Int32 *status)
                THIS_LIB_TRAP(THIS_TrapGPSGetStatus);

extern Int32 THIS_GPSGetTime(UInt16 refNum, Int32 *seconds, Int32 *fracSeconds,
                                     Int32 *status)
                THIS_LIB_TRAP(THIS_TrapGPSGetTime);

extern Int32 THIS_GPSGetVelocity(UInt16 refNum, double *east, double *north, double *up,
                                         double *track, double *speed,
                                         Int32 *status)
                THIS_LIB_TRAP(THIS_TrapGPSGetVelocity);

extern Int32 THIS_GPSGetSatellites(UInt16 refNum, Int32 satellite, 
                                           Int32 *svid, Int32 *statusBits,
                                           Int32 *snr, double *azimuth, 
                                           double *elevation,
                                           Int32 *status)
                THIS_LIB_TRAP(THIS_TrapGPSGetSatellites);

extern Int32 THIS_GetLatLonSemicircles(UInt16 refNum, Int32 *lat, Int32 *  lon)
                THIS_LIB_TRAP(THIS_TrapGetLatLonSemicircles);

extern Int32 THIS_GetLatLonDegMin(UInt16 refNum, char *lat, char  *  lon)
                THIS_LIB_TRAP(THIS_TrapGetLatLonDegMin);

extern Int32 THIS_GetLatLonDegMinSec(UInt16 refNum, char *lat, char  *  lon)
                THIS_LIB_TRAP(THIS_TrapGetLatLonDegMinSec);

extern Int32 THIS_GetErrString(UInt16 refNum, Int32 status, char *errString)
                THIS_LIB_TRAP(THIS_TrapGetErrString);

extern Int32 THIS_GetModeString(UInt16 refNum, Int32 mode, char *modeString)
                THIS_LIB_TRAP(THIS_TrapGetModeString);

extern Int32 THIS_GetFixString(UInt16 refNum, Int32 fix, char *fixString)
                THIS_LIB_TRAP(THIS_TrapGetFixString);

extern Int32 THIS_GetSatStatusValues(UInt16 refNum, Int32 statusBits, 
                   Int32 *ephemeris, Int32 *differential, 
                   Int32 *used, Int32 *  rising)
                THIS_LIB_TRAP(THIS_TrapGetSatStatusValues);

extern Int32 THIS_ConvertDouble(UInt16 refNum, double originalValue,
                                        Int32 conversionType,
                                        double *convertedValue)
                THIS_LIB_TRAP(THIS_TrapConvertDouble);

extern Int32 THIS_LatLonToUTM(UInt16 refNum, Int32 datumID,
                                      double lat,
                                      double lon,
                                      double *easting,
                                      double *northing,
                                      char *zone)
                THIS_LIB_TRAP(THIS_TrapLatLonToUTM);

extern Int32 THIS_UTMToLatLon(UInt16 refNum, Int32 datumID,
                                      char *   zone,
                                      double easting,
                                      double northing,
                                      double *lat,
                                      double *  lon)
                THIS_LIB_TRAP(THIS_TrapUTMToLatLon);

extern Int32 THIS_UTMDistance(UInt16 refNum, 
                       char *   zone1, double easting1, double northing1,
                       char *   zone2, double easting2, double northing2,
                       char *ewDir, double *ewDist,
                       char *nsDir, double *nsDist, 
                       double *distance)
                THIS_LIB_TRAP(THIS_TrapUTMDistance);

extern Int32 THIS_PwrSetLowPowerMode(UInt16 refNum, char *   creatorID,
                                             Int32 enabled,
                                             Int32 *status)
                THIS_LIB_TRAP(THIS_TrapPwrSetLowPowerMode);

extern Int32 THIS_RegisterNotifyEvents(UInt16 refNum, Int32 locationChange,
                                               Int32 statusChange,
                                               Int32 lostFix,
                                               Int32 satDataChange,
                                               Int32 modeChange,
                                               Int32 displayResized)
                THIS_LIB_TRAP(THIS_TrapRegisterNotifyEvents);

extern Int32 THIS_WinGetDisplayExtent(UInt16 refNum, Int32 *  x, Int32 *  y)
                THIS_LIB_TRAP(THIS_TrapWinGetDisplayExtent);

extern Int32 THIS_WinSetDisplayExtent(UInt16 refNum, Int32 size)
                THIS_LIB_TRAP(THIS_TrapWinSetDisplayExtent);

extern Int32 THIS_FrmGetDIAPolicy(UInt16 refNum, Int32 *value)
                THIS_LIB_TRAP(THIS_TrapFrmGetDIAPolicy);

extern Int32 THIS_FrmSetDIAPolicy(UInt16 refNum, Int32 value)
                THIS_LIB_TRAP(THIS_TrapFrmSetDIAPolicy);

extern Int32 THIS_PINGetDIAState(UInt16 refNum, Int32 *value)
                THIS_LIB_TRAP(THIS_TrapPINGetDIAState);

extern Int32 THIS_PINSetDIAState(UInt16 refNum, Int32 value)
                THIS_LIB_TRAP(THIS_TrapPINSetDIAState);

extern Int32 THIS_PINGetInputTriggerState(UInt16 refNum, Int32 *value)
                THIS_LIB_TRAP(THIS_TrapPINGetInputTriggerState);

extern Int32 THIS_PINSetInputTriggerState(UInt16 refNum, Int32 value)
                THIS_LIB_TRAP(THIS_TrapPINSetInputTriggerState);

#ifdef __cplusplus
}
#endif

#endif	// __NSBiQueGPSPrototypes_H__

