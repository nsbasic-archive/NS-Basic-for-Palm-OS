/******************************************************************************
 *
 * Copyright (c) 2006 InfosystemsPro LLC All rights reserved.
 * Contact: Carmine Castiglia - ccastiglia@infosystemspro.com
 * File: SharedLib.c
 *
 * Description:
 *		This is the main source module for a Palm OS shared library.
 *		Based on fine examples from PRC-tools.
 *
 *****************************************************************************/

#include <palmone_68k.h> 
#include <68K\Hs.h>
#include <SystemMgr.h>
#include <string.h>


#define SHARED_LIB_TRAP(trapNum)	/* Needs to be prior to SharedLib.h inclusion */

#include "SharedLib.h"

typedef struct {
	UInt16 refNumCount;
} SharedLib_globals;


/***********************************************************************
 *
 * FUNCTION:    start
 *
 * DESCRIPTION: A function all shared libraries must have to patch the
 * 				jump table to enable this shared library. 
 *
 ***********************************************************************/

UInt32 start(UInt16 refNum, SysLibTblEntryPtr entryP) {
	extern void *jmptable ();
	
	entryP->dispatchTblP = (void *)jmptable;
	entryP->globalsP = NULL;
	
	return errNone;
}

/***********************************************************************
 *
 * FUNCTION:    SharedLib_Open
 *
 * DESCRIPTION: A function that updates the reference count on how
 * 				many applications have the library open. 
 *
 ***********************************************************************/

Err SharedLib_Open(UInt16 refNum) {
	Err	err = 0;
	return err;

}

/***********************************************************************
 *
 * FUNCTION:    SharedLib_Close
 *
 * DESCRIPTION: A function that decrements the reference count on how
 * 				many applications have the library open. 
 *
 ***********************************************************************/

Err SharedLib_Close(UInt16 refNum) {
	Err		err = 0;

	return err;
  
}

/***********************************************************************
 *
 * FUNCTION:    SharedLib_Sleep
 *
 * DESCRIPTION: A function needed for handling sleep. 
 *
 ***********************************************************************/

Err SharedLib_Sleep(UInt16 refNum)
{
	return errNone;
}
	
/***********************************************************************
 *
 * FUNCTION:    SharedLib_Wake
 *
 * DESCRIPTION: A function needed for handling wake. 
 *
 ***********************************************************************/

Err SharedLib_Wake(UInt16 refNum)
{
	return errNone;
}

/***********************************************************************
 *
 * FUNCTION:    SharedLib_Version
 *
 * DESCRIPTION: Returns the version number of the library.
 * provided. 
 *
 ***********************************************************************/

Int32 SharedLib_Version(UInt16 refNum, double *version) {	
	*version = 1.0;
	return 0;
	
}

/***********************************************************************
 *
 * FUNCTION:    SharedLib_CompileInfo
 *
 * DESCRIPTION: Returns the date and time of library compilation.
 *
 ***********************************************************************/

Int32 SharedLib_CompileInfo(UInt16 refNum, char *compileDate, char *compileTime) {	
	StrCopy(compileDate, __DATE__);
	StrCopy(compileTime, __TIME__);
	return 0;
	
}

/***********************************************************************
 *
 * FUNCTION:    SharedLib_GetPhoneType
 *
 * DESCRIPTION: Returns the phone type:
 * 
 * 	result 1:	Phone is CDMA
 *  	result 2:	Phone is GSM
 * 
 * Compatability: GSM, CDMA
 *
 ***********************************************************************/
 
Int32 SharedLib_GetPhoneType (UInt16 refNum, UInt32 *result)
{
	UInt32 phnType = hsAttrPhoneTypeGSM; 
	HsAttrGet (hsAttrPhoneType, 0, &phnType);
	*result = phnType;
	return 0;
	
}
/***********************************************************************
 *
 * FUNCTION:    SharedLib_GetRadioPowerStatus
 *
 * DESCRIPTION: Returns the power state of the radio module
 * 
 * 	result 0:	Radio module is off
 * 	result 1:	Radio module is on
 *
 * Compatability:  GSM, CDMA
 * 
 ***********************************************************************/
 
Int32 SharedLib_GetRadioPowerStatus(UInt16 refNum, Int16 *result) {
	UInt16 hsRef;
	HsGetPhoneLibrary(&hsRef);
	if (!PhnLibModulePowered(hsRef)) 
		*result = 0;
	else 
		*result = 1;
	return 0;
}

/***********************************************************************
 *
 * FUNCTION:    SharedLib_GetPhnLibRefNum
 *
 * DESCRIPTION: Returns the library reference number of PhnLib
 *
 * Compatability:  GSM, CDMA
 * 
 ***********************************************************************/

Int32 SharedLib_GetPhnLibRefNum(UInt16 refNum, UInt16 *result) {
	UInt16 phoneLibRef=0; 
	if (!HsGetPhoneLibrary(&phoneLibRef))
		*result = phoneLibRef;
	else
		*result = -1;
	return errNone;

}

/***********************************************************************
 *
 * FUNCTION:    SharedLib_GetPhnRoamMode
 *
 * DESCRIPTION: Returns the current roaming mode
 * 
 * 	Treo 700p:	0 Home Only (ie roaming is disabled)
 *			1 Any (ie roaming is enabled)
 *			2 Roam Only (ie roaming is required)
 * 
 *	Treo 650	0 Home Only (ie roaming is disabled)
 *			1 Any (ie roaming is enabled)
 * 
 * Compatability:  CDMA only
 * 
 ***********************************************************************/

Int32 SharedLib_GetPhnRoamMode(UInt16 refNum, Int16 *result ) {
	UInt16 hsRef;
	PhnRoamPrefSelectionType hsMode;

	//check phonetype (GSM / CDMA) first
	UInt32 phnType = hsAttrPhoneTypeGSM; 
	HsAttrGet (hsAttrPhoneType, 0, &phnType);
	if (phnType == hsAttrPhoneTypeGSM) {
		*result = -4;
		return 0;
	}
	
	// Get reference number to Handspring phone library
	// and return -3 if error occurs finding library
	if ( HsGetPhoneLibrary( &hsRef ) ) {
		*result = -3;
		return 0;
	}

	// Check to ensure radio is on before proceeding
	// and return -2 if radio is off
	if ( !PhnLibModulePowered( hsRef ) )	{
		*result = -2;
		return 0;
	}
	
	// Get current roaming preference mode from phone
	// and return -1 if error occurs else roaming mode
	if ( PhnLibGetRoamPrefMode( hsRef, &hsMode ) )
		*result = -1;
	else
		*result = hsMode;

	return 0;
}


/***********************************************************************
 *
 * FUNCTION:    SharedLib_SetPhnRoamMode
 *
 * 	Treo 700p:	0 Home Only (ie roaming is disabled)
 *			1 Any (ie roaming is enabled)
 *			2 Roam Only (ie roaming is required)
 * 
 *	Treo 650	0 Home Only (ie roaming is disabled)
 *			1 Any (ie roaming is enabled)
 * 
 * Compatability:  CDMA only
 *
 ***********************************************************************/

Int32 SharedLib_SetPhnRoamMode(UInt16 refNum, Int16 mode, Int16 *result) {
	UInt16 hsRef;
	PhnRoamPrefSelectionType hsMode=mode;

	//check phonetype (GSM / CDMA) first
	UInt32 phnType = hsAttrPhoneTypeGSM; 
	HsAttrGet (hsAttrPhoneType, 0, &phnType);
	if (phnType == hsAttrPhoneTypeGSM) {
		*result = -5;
		return 0;
	}
	
	
	// Get reference number to Handspring phone library
	// and return -4 if error occurs finding library
	if ( HsGetPhoneLibrary( &hsRef ) ) {
		*result = -4;
		return 0;
	}

	// Check to ensure radio is on before proceeding
	// and return -3 if radio is off
	if ( !PhnLibModulePowered( hsRef ) )	{
		*result = -3;
		return 0;
	}

	// Check for valid prefMode request
	// and return -2 if outside range
	if (hsMode > 2) {
		*result = -2;
		return 0;
	}
			
	// Set roaming preference mode 
	// Return -1 if error occurs else roaming mode
	if ( PhnLibSetRoamPrefMode( hsRef, hsMode ) ) {
		*result = -1;
	}
	else {
		*result = hsMode;
	}

	return 0;

}

/***********************************************************************
 *
 * FUNCTION:    SharedLib_TurnRadioOn
 *
 * DESCRIPTION: Prompts the user to turn the radio on
 * 
 * Compatability:  GSM, CDMA
 *
 ***********************************************************************/

Int32 SharedLib_TurnRadioOn(UInt16 refNum, Int16 *result) {
	if ( HsTurnRadioOn() ) 
		*result = -1;
	else 
		*result = 0;
	return 0;

}

/***********************************************************************
 *
 * FUNCTION:    SharedLib_GetDeviceID
 *
 * DESCRIPTION: Returns the device's companyID and deviceID
 * 
 * 	Treo 700p	companyID = 	"Palm" (phone), "hspr" (simulator)
 * 			deviceID =	"D052"
 *
 * 	Treo 650	companyID =	"hspr" phone/simulator
 * 			deviceID =	"H102"
 *
 * Note: A fairly complete listing of companyID and deviceID's can be
 *       found at http://www.mobilegeographics.com/dev/devices.php
 *
 ***********************************************************************/

Int32 SharedLib_GetDeviceID(UInt16 refNum, char *company, char *device) {
	UInt32 companyID;
	UInt32 deviceID;
	FtrGet(sysFtrCreator,sysFtrNumOEMCompanyID,&companyID);
	FtrGet(sysFtrCreator,sysFtrNumOEMDeviceID,&deviceID);
	StrCopy(company,((char *) &companyID));
	StrCopy(device,((char *) &deviceID));
	return errNone;

}

/***********************************************************************
 *
 * FUNCTION:    SharedLib_GetRoamWarnings
 *
 * DESCRIPTION: Returns the roam-specific application preferences
 *
 * 	Treo 700p:
 * 		result   0: Warn before call & Warn before data unchecked
 * 		result   1: Warn before data checked
 *  		result 256: Warn before call checked
 * 		result 257: Warn before call & Warn before data checked
 * 
 * Compatability:  CDMA only (?)
 * 
 ***********************************************************************/

Int32 SharedLib_GetRoamWarnings(UInt16 refNum, Int16 *result) {
	UInt32 HsPhCreatorID='HsPh';
	UInt16 HsPhPrefID=0x0D;
   	Int16 prefs;
	UInt16 prefsSize;
    prefsSize = sizeof(prefs);
	if (PrefGetAppPreferences(HsPhCreatorID, HsPhPrefID, &prefs, &prefsSize,
                              true) != noPreferenceFound) {
								*result = prefs;
                              }
                              else {
                              	*result = -1;
                              }
		return 0;
}  
                     
/***********************************************************************
 *
 * FUNCTION:    SharedLib_SetRoamWarnings
 *
 * DESCRIPTION: Sets the roam-specific application preferences
 *
 * 	Treo 700p:
 * 		warnings   0: Warn before call & Warn before data unchecked
 * 		warnings   1: Warn before data checked
 *  		warnings 256: Warn before call checked
 * 		warnings 257: Warn before call & Warn before data checked
 * 
 * Compatability:  CDMA only (?)
 * 
 ***********************************************************************/

Int32 SharedLib_SetRoamWarnings(UInt16 refNum, UInt16 warnings, Int16 *result) {
	UInt32 HsPhCreatorID='HsPh';
	UInt16 HsPhPrefID=0x0D;
   	UInt16 prefs=0;
   	Int16 prefsVersion;
	UInt16 prefsSize=0;
	// Check size of preferences.  If not 16 bytes, something
	// has changed since the time this lib was designed
	if (PrefGetAppPreferences(HsPhCreatorID, HsPhPrefID, NULL, &prefsSize, 
								true)!= noPreferenceFound) 
									if (prefsSize != sizeof(prefs)) {
									// unexpected prefSize, better not continue
										*result = -3;
										return 0;
									}
									
	// This time, pick up the version number
	prefsVersion = PrefGetAppPreferences(HsPhCreatorID, HsPhPrefID, &prefs, &prefsSize, true);
	if (prefsVersion != noPreferenceFound) {
		*result=prefsVersion;
	}
	else {
		*result = -2;
		return 0;
	}
	prefs=warnings;
	PrefSetAppPreferences(HsPhCreatorID, HsPhPrefID, prefsVersion, &prefs, prefsSize, true);
	if (prefsSize != sizeof(prefs)) {
		// Seems that the preferences didn't update?
		*result = -1;
	}
	else {
		*result = 0;
	}
	return errNone;
}                       

/***********************************************************************
 *
 * FUNCTION:    SharedLib_SetModulePower
 *
 * DESCRIPTION: Turns radio module power on or off directly without
 * 				the user prompt used by HsPowerOn
 * 
 * Compatability:  GSM, CDMA
 * 
 * ***********************************************************************/

Int32 SharedLib_SetModulePower(UInt16 refNum, char *offOn, Int16 *result) {
	Boolean doWhat;
	UInt16 hsRef;
	if (!strcmp(offOn,"off")) 
		doWhat = false;
	else {
		if (!strcmp(offOn,"on")) 
			doWhat = true;
		else {
			*result = -3;
			return 0;
		}
	}
	
	// Get reference number to Handspring phone library
	// and return -2 if error occurs finding library
	if ( HsGetPhoneLibrary( &hsRef ) ) {
		*result = -2;
		return 0;
	}
		
	if (PhnLibSetModulePower (hsRef, doWhat))
		*result = -1;
	else
		*result = 0;
	return 0;
}       


/***********************************************************************
 *
 * FUNCTION:    SharedLib_GetRingProfile
 *
 * DESCRIPTION: Returns the ring/vibrate profile
 * 
 * Treo 700p:
 *  profile:	Ring tones,		0
 * 		Phone alerts,	6
 * 		Calendar,		2
 * 		Messaging,		5
 * 	vol:	Ringer volume, 	0 through 7 (0 = Off)
 * 	vib:	Vibrate mode, 	0 = Never
 * 				1 = When sound off
 * 				256 = Vibrate then ring
 * 				257 = Always
 * 
 * Compatability:  GSM, CDMA
 *
 ***********************************************************************/

Int32 SharedLib_GetRingProfile(UInt16 refNum, UInt16 profile, Int16 *vol, Int16 *vib, Int16 *result ) {
	UInt32 HsPhCreatorID='HsTo';
	UInt16 HsPhPrefID=profile;
	struct {
		UInt16 fill_1;
		UInt16 fill_2;
		UInt16 fill_3;
		UInt16 fill_4;
		UInt16 fill_5;
		UInt16 fill_6;
		UInt16 fill_7;
		UInt16 fill_8;
		UInt16 fill_9;
		UInt16 fill_10;
		UInt16 fill_11;
		UInt16 fill_12;
		UInt16 fill_13;
		UInt16 volume;
		UInt16 vibrate;
	}  prefs;
	
	UInt16 prefsSize=0;
	// Check size of preferences.  If not 30 bytes, something
	// has changed since the time this lib was designed
	if (PrefGetAppPreferences(HsPhCreatorID, HsPhPrefID, NULL, &prefsSize, 
								true)!= noPreferenceFound) 
									if (prefsSize != sizeof(prefs)) {
									// unexpected prefSize, better not continue
										*result = -2;
										return 0;
									}

	if (PrefGetAppPreferences(HsPhCreatorID, HsPhPrefID, &prefs, &prefsSize,
                              true) != noPreferenceFound) {
								*vol = prefs.volume;
								*vib = prefs.vibrate;
								*result = 0;
                              }
                              else {
                              	*result = -1;
                              }
		return 0;
}  
                     
/***********************************************************************
 *
 * FUNCTION:    SharedLib_SetRingProfile
 *
 * DESCRIPTION: Sets the ring/vibrate profile
 * 
 * Treo 700p:
 *  profile:	Ring tones,		0
 * 		Phone alerts,	6
 * 		Calendar,		2
 * 		Messaging,		5
 * 	vol:	Ringer volume, 	0 through 7 (0 = Off)
 * 	vib:	Vibrate mode, 	0 = Never
 * 				1 = When sound off
 * 				256 = Vibrate then ring
 * 				257 = Always
 * 
 * Compatability:  GSM, CDMA
 *
 * DESCRIPTION: Second sample library function that does the same as A.
 *
 ***********************************************************************/

Int32 SharedLib_SetRingProfile(UInt16 refNum, UInt16 profile, Int16 vol, Int16 vib, Int16 *result ) {
	UInt32 HsPhCreatorID='HsTo';
	UInt16 HsPhPrefID=profile;
   	Int16 prefsVersion;
	struct {
		UInt16 fill_1;
		UInt16 fill_2;
		UInt16 fill_3;
		UInt16 fill_4;
		UInt16 fill_5;
		UInt16 fill_6;
		UInt16 fill_7;
		UInt16 fill_8;
		UInt16 fill_9;
		UInt16 fill_10;
		UInt16 fill_11;
		UInt16 fill_12;
		UInt16 fill_13;
		UInt16 volume;
		UInt16 vibrate;
	}  prefs;
	
	UInt16 prefsSize=0;
	// Check size of preferences.  If not 30 bytes, something
	// has changed since the time this lib was designed
	if (PrefGetAppPreferences(HsPhCreatorID, HsPhPrefID, NULL, &prefsSize, 
								true)!= noPreferenceFound) 
									if (prefsSize != sizeof(prefs)) {
									// unexpected prefSize, better not continue
										*result = -3;
										return 0;
									}

	// This time, pick up the version number
	prefsVersion = PrefGetAppPreferences(HsPhCreatorID, HsPhPrefID, &prefs, &prefsSize, true);
	if (prefsVersion != noPreferenceFound) {
		*result=prefsVersion;
	}
	else {
		*result = -2;
		return 0;
	}

	prefs.volume=vol;
	prefs.vibrate=vib;

	PrefSetAppPreferences(HsPhCreatorID, HsPhPrefID, prefsVersion, &prefs, prefsSize, true);
	if (prefsSize != sizeof(prefs)) {
		// Seems that the preferences didn't update?
		*result = -1;
	}
	else {
		*result = 0;
	}
	return errNone;

}  
                     
Int32 SharedLib_GetLifeTimer(UInt16 refNum, char *s) {
	char st[32];
	HsGetVersionString(hsVerStrLifeTime, st, NULL);
		StrCopy(s,st);
		return 0;
}