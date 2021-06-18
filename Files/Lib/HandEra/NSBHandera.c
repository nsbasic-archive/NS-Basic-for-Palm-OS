#include <PalmOS.h>			// Includes all Palm OS headers
#include <Vga.h>
#include <Silk.h>
#include <Audio.h>

#define BUILDING_THIS_LIB	// Defined in this file only...
#include "NSBHandera.h"		// Library public definitions

/********************************************************************
 * SHARED LIBRARY GLOBALS:
 *
 * IMPORTANT:
 * ==========
 * Shared Libraries are *not* allowed to have global or static 
 * variables.  Instead, they allocate a memory chunk to hold their 
 * persistent data, and save a handle to it in the library's system
 * library table entry.
 *
 * The "THIS_LibGlobals.h" file contains the routines necessary for
 * allocating, accessing, and freeing the library's "globals" structure.
 *
 * If "THIS" Library requires "globals", then ensure that the 
 * "THIS_REQUIRES_GLOBALS" definition is defined.  This will cause
 * the "THIS_LibGlobals.h" file to be included, thus including the 
 * "globals" allocation, access, and freeing routines.
 *
 * If "THIS_REQUIRES_GLOBALS" is not defined, then the "globals" 
 * routines are defined as "nothing" and they are simply ignored.
 *
 ********************************************************************/

#define THIS_REQUIRES_GLOBALS
#ifdef THIS_REQUIRES_GLOBALS
	#include "NSBHanderaGlobals.h"
#else
	#define THIS_ALLOCATE_GLOBALS
	#define THIS_FREE_GLOBALS
	#define THIS_ATTACH_GLOBALS
	#define THIS_DETACH_GLOBALS
#endif



/********************************************************************
 *                     T H I S _ V e r s i o n
 ********************************************************************/

Err THIS_Version(UInt16 refNum, double *version) {	
	
	*version = 1.0;
	return 0;
}

/********************************************************************
 *                 T H I S _ C o m p i l e I n f o
 ********************************************************************/

Err THIS_CompileInfo(UInt16 refNum, char *compileDate, char *compileTime) {	
	
	StrCopy(compileDate, __DATE__);
	StrCopy(compileTime, __TIME__);
	return 0;
}

/********************************************************************
 *    T H I S _ A u d i o A d j V o l u m e S u p p o r t e d
 ********************************************************************/
Err THIS_AudioAdjVolumeSupported(UInt16 refNum, Int32 *boolean) {
    UInt32 version;
    UInt32 features;
    
    if (FtrGet(TRGSysFtrID, TRGAudioFtrNum, &version) == 0) {
        AudioGetSupportedFeatures(&features);
        if (features & audioFtrAdjVolume)
	        *boolean = 1;
	    else
	        *boolean = 0;
    }
    else
        *boolean = -1;

	return 0;
}

/********************************************************************
 *       T H I S _ A u d i o D T M F S u p p o r t e d
 ********************************************************************/
Err THIS_AudioDTMFSupported(UInt16 refNum, Int32 *boolean) {
    UInt32 version;
    UInt32 features;
    
    if (FtrGet(TRGSysFtrID, TRGAudioFtrNum, &version) == 0) {
        AudioGetSupportedFeatures(&features);
        if (features & audioFtrDTMF)
	        *boolean = 1;
	    else
	        *boolean = 0;
    }
    else
        *boolean = -1;

	return 0;
}

/********************************************************************
 *       T H I S _ A u d i o G e t M a s t e r V o l u m e
 ********************************************************************/
Err THIS_AudioGetMasterVolume(UInt16 refNum, Int32 *volume) {
    UInt32 version;
    UInt8 vol;
    
    if (FtrGet(TRGSysFtrID, TRGAudioFtrNum, &version) == 0) {
        AudioGetMasterVolume(&vol);
        *volume = vol;
    }
    else
        *volume = -1;

	return 0;
}

/********************************************************************
 *            T H I S _ A u d i o G e t M u t e
 ********************************************************************/
Err THIS_AudioGetMute(UInt16 refNum, Int32 *boolean) {
    UInt32 version;
    Boolean yesNo;
    
    if (FtrGet(TRGSysFtrID, TRGAudioFtrNum, &version) == 0) {
        AudioGetMute(&yesNo);
        *boolean = yesNo;
    }
    else
        *boolean = -1;

	return 0;
}

/********************************************************************
 *         T H I S _ A u d i o P l a y D T M F C h a r
 ********************************************************************/
Err THIS_AudioPlayDTMFChar(UInt16 refNum, char *dtmfStr, Int32 toneLength) {
    UInt32 version;
    
    if (FtrGet(TRGSysFtrID, TRGAudioFtrNum, &version) == 0)
        AudioPlayDTMFChar(*dtmfStr, (Int16) toneLength);
    
	return 0;
}

/********************************************************************
 *          T H I S _ A u d i o P l a y D T M F S t r
 ********************************************************************/
Err THIS_AudioPlayDTMFStr(UInt16 refNum, char *dtmfStr, 
                          Int32 toneLength, Int32 toneGap) {
    UInt32 version;
    
    if (FtrGet(TRGSysFtrID, TRGAudioFtrNum, &version) == 0)
        AudioPlayDTMFStr(dtmfStr, (Int16) toneLength, (Int16) toneGap);
    
	return 0;
}

/********************************************************************
 *       T H I S _ A u d i o P l a y W a v e S u p p o r t e d
 ********************************************************************/
Err THIS_AudioPlayWaveSupported(UInt16 refNum, Int32 *boolean) {
    UInt32 version;
    UInt32 features;
    
    if (FtrGet(TRGSysFtrID, TRGAudioFtrNum, &version) == 0) {
        AudioGetSupportedFeatures(&features);
        if (features & audioFtrPlayWave)
	        *boolean = 1;
	    else
	        *boolean = 0;
    }
    else
        *boolean = -1;

	return 0;
}

/********************************************************************
 *   T H I S _ A u d i o R e c o r d W a v e S u p p o r t e d
 ********************************************************************/
Err THIS_AudioRecordWaveSupported(UInt16 refNum, Int32 *boolean) {
    UInt32 version;
    UInt32 features;
    
    if (FtrGet(TRGSysFtrID, TRGAudioFtrNum, &version) == 0) {
        AudioGetSupportedFeatures(&features);
        if (features & audioFtrRecordWave)
	        *boolean = 1;
	    else
	        *boolean = 0;
    }
    else
        *boolean = -1;

	return 0;
}

/********************************************************************
 *       T H I S _ A u d i o S e t M a s t e r V o l u m e
 ********************************************************************/
Err THIS_AudioSetMasterVolume(UInt16 refNum, Int32 volume) {
    UInt32 version;
    
    if (FtrGet(TRGSysFtrID, TRGAudioFtrNum, &version) == 0) {
        if (volume < audioVolumeMin)
            volume = audioVolumeMin;
        if (volume > audioVolumeMax)
            volume = audioVolumeMax;
        AudioSetMasterVolume((UInt8) volume);
    }
    
	return 0;
}

/********************************************************************
 *            T H I S _ A u d i o S e t M u t e
 ********************************************************************/
Err THIS_AudioSetMute(UInt16 refNum, Int32 boolean) {
    UInt32 version;
    
    if (FtrGet(TRGSysFtrID, TRGAudioFtrNum, &version) == 0)
        AudioSetMute((Boolean) boolean);
    
	return 0;
}

/********************************************************************
 *          T H I S _ A u d i o V o l u m e D l g
 ********************************************************************/
Err THIS_AudioVolumeDlg(UInt16 refNum, char *title) {
    UInt32 version;
    
    if (FtrGet(TRGSysFtrID, TRGAudioFtrNum, &version) == 0)
        AudioVolumeDlg(title);
    
	return 0;
}

/********************************************************************
 *  T H I S _ S i l k G e t G r a f f i t i P e r s i s t e n c e
 ********************************************************************/
Err THIS_SilkGetGraffitiPersistence(UInt16 refNum, Int32 *ticks) {
    UInt32 version;
    
    if (FtrGet(TRGSysFtrID, TRGSilkFtrNum, &version) == 0)
        *ticks = SilkGetGraffitiPersistence();
    else
        *ticks = -1;

	return 0;
}

/********************************************************************
 *           T H I S _ S i l k M a x i m i z e W i n d o w
 ********************************************************************/
Err THIS_SilkMaximizeWindow(UInt16 refNum) {
    UInt32 version;
    
    if (FtrGet(TRGSysFtrID, TRGSilkFtrNum, &version) == 0)
        SilkMaximizeWindow();

	return 0;
}

/********************************************************************
 *           T H I S _ S i l k M i n i m i z e W i n d o w
 ********************************************************************/
Err THIS_SilkMinimizeWindow(UInt16 refNum) {
    UInt32 version;
    
    if (FtrGet(TRGSysFtrID, TRGSilkFtrNum, &version) == 0)
        SilkMinimizeWindow();

	return 0;
}

/********************************************************************
 *  T H I S _ S i l k S e t G r a f f i t i P e r s i s t e n c e
 ********************************************************************/
Err THIS_SilkSetGraffitiPersistence(UInt16 refNum, Int32 ticks) {
    UInt32 version;
    
    if (FtrGet(TRGSysFtrID, TRGSilkFtrNum, &version) == 0)
        SilkSetGraffitiPersistence(ticks);

	return 0;
}

/********************************************************************
 *         T H I S _ S i l k W i n d o w M i n i m i z e d
 ********************************************************************/
Err THIS_SilkWindowMinimized(UInt16 refNum, Int32 *boolean) {
    UInt32 version;
    
    if (FtrGet(TRGSysFtrID, TRGSilkFtrNum, &version) == 0) {
        if (SilkWindowMaximized())
            *boolean = 0;
        else
            *boolean = 1;
    }
    else
        *boolean = -1;

	return 0;
}

/********************************************************************
 *                T H I S _ S i z e F o r m
 ********************************************************************/
Err THIS_SizeForm(UInt16 refNum) {
    FormType *activeForm;
    RectangleType rect;
        
    activeForm = FrmGetActiveForm();
    rect.topLeft.x = 0;
    rect.topLeft.y = 0;
    WinGetDisplayExtent(&rect.extent.x, &rect.extent.y);
    WinSetWindowBounds(FrmGetWindowHandle(activeForm), &rect);
    FrmEraseForm(activeForm);
    
	return 0;
}

/********************************************************************
 *          T H I S _ V g a B a s e T o V g a F o n t
 ********************************************************************/
Err THIS_VgaBaseToVgaFont(UInt16 refNum, Int32 fontId, Int32 *vgaFontId) {
    UInt32 version;
    
    if (FtrGet(TRGSysFtrID, TRGVgaFtrNum, &version) == 0)
        *vgaFontId = VgaBaseToVgaFont(fontId);
    else
        *vgaFontId = -1;

	return 0;
}

/********************************************************************
 *             T H I S _ V g a F o n t S e l e c t
 ********************************************************************/
Err THIS_VgaFontSelect(UInt16 refNum, 
                       Int32 fontFormType, Int32 defaultFontId,
                       Int32 *fontId) {
    UInt32 version;
    
    if (FtrGet(TRGSysFtrID, TRGVgaFtrNum, &version) == 0)
        *fontId = VgaFontSelect(fontFormType, defaultFontId);
    else
        *fontId = -1;

	return 0;
}

/********************************************************************
 *               T H I S _ V g a F r m M o d i f y
 ********************************************************************/
Err THIS_VgaFrmModify(UInt16 refNum, Int32 *error) {
    UInt32 version;
    VgaScreenModeType mode;
    VgaRotateModeType  rotation;
    FormType *activeForm;
    
    if (FtrGet(TRGSysFtrID, TRGVgaFtrNum, &version) == 0) {
        VgaGetScreenMode(&mode, &rotation);
        activeForm = FrmGetActiveForm();
        if (activeForm != NULL)
            FrmEraseForm(activeForm);
        if (mode != screenMode1To1)
            VgaSetScreenMode(screenMode1To1, rotation);
        if (activeForm != NULL) {
            *error = VgaFormModify(activeForm, vgaFormModify160To240);
        }
        else
            *error = -2;
    }
    else
        *error = -1;

	return 0;
}

/********************************************************************
 *      T H I S _ V g a F r m G e t T i t l e H e i g h t
 ********************************************************************/
Err THIS_VgaFrmGetTitleHeight(UInt16 refNum, Int32 *height) {
    UInt32 version;
    
    if (FtrGet(TRGSysFtrID, TRGVgaFtrNum, &version) == 0)
        *height = VgaGetFrmTitleHeight();
    else
        *height = -1;

	return 0;
}

/********************************************************************
 *        T H I S _ V g a G e t S c r e e n M o d e
 ********************************************************************/
Err THIS_VgaGetScreenMode(UInt16 refNum, Int32 *mode) {
    UInt32 version;
	THIS_ATTACH_GLOBALS		// Define local variables before this
    
    if (FtrGet(TRGSysFtrID, TRGVgaFtrNum, &version) == 0) {
        VgaGetScreenMode(&gP->mode, &gP->rotation);
        *mode = gP->mode;
    }
    else
        *mode = -1;

	THIS_DETACH_GLOBALS	
	return 0;
}

/********************************************************************
 *      T H I S _ V g a G e t S c r e e n O f f s e t
 ********************************************************************/
Err THIS_VgaGetScreenOffset(UInt16 refNum, Int32 *offset) {
	THIS_ATTACH_GLOBALS		// Define local variables before this
    
    *offset = gP->state.offset;
    
	THIS_DETACH_GLOBALS	
	return 0;
}

/********************************************************************
 *      T H I S _ V g a G e t S c r e e n R o t a t i o n
 ********************************************************************/
Err THIS_VgaGetScreenRotation(UInt16 refNum, Int32 *rotation) {
	THIS_ATTACH_GLOBALS		// Define local variables before this
    
    *rotation = gP->rotation;
    
	THIS_DETACH_GLOBALS	
	return 0;
}

/********************************************************************
 *        T H I S _ V g a G e t S c r e e n S t a t e
 ********************************************************************/
Err THIS_VgaGetScreenState(UInt16 refNum, Int32 *mode) {
    UInt32 version;
	THIS_ATTACH_GLOBALS		// Define local variables before this
    
    if (FtrGet(TRGSysFtrID, TRGVgaFtrNum, &version) == 0) {
        VgaSaveScreenState(&gP->state);
        gP->mode = gP->state.mode;
        gP->rotation = gP->state.rotate;
        *mode = gP->mode;
    }
    else
        *mode = -1;

	THIS_DETACH_GLOBALS	
	return 0;
}

/********************************************************************
 *              T H I S _ V g a I s V g a F o n t
 ********************************************************************/
Err THIS_VgaIsVgaFont(UInt16 refNum, Int32 fontId, Int32 *boolean) {
    UInt32 version;
    
    if (FtrGet(TRGSysFtrID, TRGVgaFtrNum, &version) == 0)
        *boolean = VgaIsVgaFont(fontId);
    else
        *boolean = -1;

	return 0;
}

/********************************************************************
 *        T H I S _ V g a R e s t o r e S c r e e n S t a t e
 ********************************************************************/
Err THIS_VgaRestoreScreenState(UInt16 refNum, Int32 *error) {
    UInt32 version;
    FormType *activeForm;
	THIS_ATTACH_GLOBALS		// Define local variables before this

    if (FtrGet(TRGSysFtrID, TRGVgaFtrNum, &version) == 0) {
        activeForm = FrmGetActiveForm();
        if (activeForm != NULL)
            FrmEraseForm(activeForm);
        *error = VgaRestoreScreenState(&gP->state);
    }
    else
        *error = -1;

	THIS_DETACH_GLOBALS	
	return 0;
}

/********************************************************************
 *               T H I S _ V g a R o t a t e S e l e c t
 ********************************************************************/
Err THIS_VgaRotateSelect(UInt16 refNum, 
                         Int32 defaultRotation, Int32 *selectedRotation) {	
    UInt32 version;
    
    if (FtrGet(TRGSysFtrID, TRGVgaFtrNum, &version) == 0) {
        if (defaultRotation < rotateModeNone || defaultRotation > rotateMode270)
            defaultRotation = rotateModeNone;
        *selectedRotation = VgaRotateSelect(defaultRotation);
    }
    else
        *selectedRotation = -1;

	return 0 ;
}


/********************************************************************
 *        T H I S _ V g a S a v e S c r e e n S t a t e
 ********************************************************************/
Err THIS_VgaSaveScreenState(UInt16 refNum) {
    UInt32 version;
	THIS_ATTACH_GLOBALS		// Define local variables before this
    
    if (FtrGet(TRGSysFtrID, TRGVgaFtrNum, &version) == 0) 
        VgaSaveScreenState(&gP->state);

	THIS_DETACH_GLOBALS	
	return 0;
}

/********************************************************************
 *            T H I S _ V g a S e t S c r e e n M o d e
 ********************************************************************/
Err THIS_VgaSetScreenMode(UInt16 refNum, 
                          Int32 mode, Int32 rotation, Int32 *error) {
    UInt32 version;
    FormType *activeForm;
    
    if (FtrGet(TRGSysFtrID, TRGVgaFtrNum, &version) == 0) {
        activeForm = FrmGetActiveForm();
        if (activeForm != NULL)
            FrmEraseForm(activeForm);
        *error = VgaSetScreenMode(mode, rotation);
    }
    else
        *error = -1;

	return 0;
}

/********************************************************************
 *          T H I S _ V g a S e t S c r e e n S t a t e
 ********************************************************************/
Err THIS_VgaSetScreenState(UInt16 refNum, 
                    Int32 mode, Int32 rotation, Int32 offset, Int32 *error) {
    UInt32 version;
    FormType *activeForm;
	VgaScreenStateType state;

    if (FtrGet(TRGSysFtrID, TRGVgaFtrNum, &version) == 0) {
        activeForm = FrmGetActiveForm();
        if (activeForm != NULL)
            FrmEraseForm(activeForm);
        state.mode = mode;
        state.rotate = rotation;
        state.offset = offset;
        *error = VgaRestoreScreenState(&state);
    }
    else
        *error = -1;

	return 0;
}

/********************************************************************
 *          T H I S _ V g a V g a T o B a s e F o n t
 ********************************************************************/
Err THIS_VgaVgaToBaseFont(UInt16 refNum, Int32 vgaFontId, Int32 *fontId) {
    UInt32 version;
    
    if (FtrGet(TRGSysFtrID, TRGVgaFtrNum, &version) == 0)
        *fontId = VgaVgaToBaseFont(vgaFontId);
    else
        *fontId = -1;

	return 0;
}

/********************************************************************
 *    T H I S _ V g a W i n D r a w B i t m a p E x p a n d e d
 ********************************************************************/
Err THIS_VgaWinDrawBitmapExpanded(UInt16 refNum, Int32 objectId, Int32 x, Int32 y) {
    UInt32 version;
    MemHandle resH;
    BitmapPtr bmPtr;

    if (FtrGet(TRGSysFtrID, TRGVgaFtrNum, &version) == 0) {
        resH = DmGetResource (bitmapRsc, objectId);
        bmPtr = MemHandleLock (resH);
        VgaWinDrawBitmapExpanded(bmPtr, x, y);
    }
	return 0;
}

/*###################################################################
 #       S t a n d a r d ,  R E Q U I R E D    F u n c t i o n s
 #
 #   You should not need to modify these functions.  Put your
 #   library's custom functions before these to separate your custom
 #   code from the standard, required code.  This way, the code you 
 #   need to modify is easily found at the top of the file and you 
 #   can "ignore" the standard, required, code at the end of the file.
 ####################################################################
 #
 #   T H I S _ L i b O p e n , C l o s e , S l e e p , & W a k e
 #
 #   The following four functions, THIS_LibOpen, THIS_LibClose,
 #   THIS_LibSleep, and THIS_LibWake are standard, REQUIRED
 #   functions for a Shared Library.  If you are using "globals" 
 #   and you want to initialize them to something other than 0, 
 #   then modify the function PrvMakeGlobals in the 
 #   "THIS_LibGlobals.h" header file.
 #*/

Err THIS_LibOpen(UInt16 refNum) {
	Err	err = 0;
	THIS_ALLOCATE_GLOBALS	// Define local variables before this
	
	return err;
}

Err THIS_LibClose(UInt16 refNum) {
	Err	err = 0;
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
