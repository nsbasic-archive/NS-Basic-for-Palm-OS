#include <PalmOS.h>			// Includes all Palm OS headers

#define BUILDING_VFS_LIB

#include "VFSLib.h"
#include "VFSLibPrv.h"

#include "StringMgr.h"

/********************************************************************
 * Internally used routines
 ********************************************************************/
static PSGlobal PrvMakeGlobals(UInt16 refNum);
static void PrvFreeGlobals(UInt16 refNum);
static PSGlobal PrvLockGlobals(UInt16 refNum);
static void PrvUnlockGlobals(PSGlobal gP);
static Boolean PrvIsLibOpen(UInt16 refNum);
static void SetLastError(UInt16 refNum, Err error);
static UInt16 GetVolume(UInt16 refNum);
static UInt32 GetMediaType(UInt32 index);
static UInt32 GetIndexMediaType(UInt32 mediaType);

/********************************************************************
 * Internally used macros
 ********************************************************************/

#define prvVFSLibVersion	3
#define OBJECT_STORE_SLOT_REF	0xff00	//For Symbian and WM StyleTap


/********************************************************************
 * VFS Library API Routines
 ********************************************************************/
 
Err VFSLibOpen(UInt16 refNum)
{
	PSGlobal		gP;
	Err			err = 0;
	Int16			originalOpenCount = 0;

	// Get library globals
	gP = PrvLockGlobals(refNum);
	
	if (!gP)  // Check if already open
		{
		// Allocate and initialize our library globals.
		gP = PrvMakeGlobals(refNum);
		if ( !gP )	err = vfsErrMemory;
		}
	
	// If we have globals, increment open count, and unlock our globals
	if ( gP )
		{
		originalOpenCount = gP->openCount;
		if ( !err ) gP->openCount++;												
		PrvUnlockGlobals(gP);
													
		if ( err && (originalOpenCount == 0) ) PrvFreeGlobals(refNum);
		}

	return( err );
}

Err VFSLibClose(UInt16 refNum)
{
	PSGlobal	gP;
	Int16		openCount;
	Err		err = 0;


	gP = PrvLockGlobals(refNum);	
	
	// If not open, return
	if (!gP) { return 0; }

	gP->openCount--;
	
	// Error check for open count underflow
	ErrFatalDisplayIf(gP->openCount < 0, "VFSLib open count underflow");
	
	openCount = gP->openCount;
	PrvUnlockGlobals(gP);	
	
	if ( openCount <= 0 )		{ PrvFreeGlobals(refNum);}
	else					err = vfsErrStillOpen;

	return err;
}

Err VFSLibSleep(UInt16 refNum)
{
	return( 0 );
}

Err VFSLibWake(UInt16 refNum)
{
	return( 0 );
}

// VFS API functions
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Common
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Err VFSLibGetLibAPIVersion(UInt16 refNum, UInt32 * dwVerP)
{
#pragma unused(refNum)
	// Error-check our parameters
	ErrFatalDisplayIf(dwVerP == NULL, "null pointer argument");
		
	*dwVerP = prvVFSLibVersion;
	
	return( 0 );
}

Err VFSLibGetLastError(UInt16 refNum, UInt32* errorP)
{
 	PSGlobal	 gP = NULL;
 
 	gP = PrvLockGlobals(refNum);
 
 	if (gP)
 	{
  		*errorP = gP->lastError;
  		PrvUnlockGlobals(gP);
 	}
 	
 	return ( 0 );
}

Err VFSLibInit(UInt16 refNum, UInt32* result)
{
	UInt32	vfsMgrVersion;
	UInt32	expMgrVersion;
	VFSSlotMountParamType mountParam;
	Err		err;
	
	err = FtrGet(sysFileCExpansionMgr,expFtrIDVersion, &expMgrVersion);
	if (err == errNone)
	{
		err = FtrGet(sysFileCVFSMgr, vfsFtrIDVersion, &vfsMgrVersion);
	}
	SetLastError(refNum, err);
	*result  = err;
	
	//Mount the home directory as a VFS volume. Symbian and WM under StyleTap
    MemSet (&mountParam, sizeof(mountParam), 0);
    mountParam.vfsMountParam.mountClass = vfsMountClass_SlotDriver;
    mountParam.slotRefNum = OBJECT_STORE_SLOT_REF;
    
    err = VFSVolumeMount (0, 0, (VFSAnyMountParamType *) &mountParam); // todo: flags etc
    
	return errNone;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Volume
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Err VFSLib_BeginVolumeEnumerate(UInt16 refNum)
{
	PSGlobal	 gP = NULL;
 
 	gP = PrvLockGlobals(refNum);
 
 	if (gP)
 	{
  		gP->volumeIterator = vfsIteratorStart;
  		PrvUnlockGlobals(gP);
 	}
 	
 	SetLastError(refNum, errNone);
 	return errNone;
} 

Err VFSLib_GetNextVolume(UInt16 refNum, UInt32* volumeP)
{
	PSGlobal	 gP = NULL;
	Err err;
	UInt16 vol;
 	gP = PrvLockGlobals(refNum);
 
 	if (gP)
 	{
		gP->lastError  = VFSVolumeEnumerate(&vol, &(gP->volumeIterator) );
		*volumeP = vol;
		err = gP->lastError;
		if (err == errNone)
		{
		 gP->currentVolume = *volumeP;
		}
  		PrvUnlockGlobals(gP);
 	}
 	
	return errNone;
}

Err VFSLib_SetVolume(UInt16 refNum, UInt32 volume)
{
	PSGlobal	 gP = NULL;
	Err err = errNone;
 	gP = PrvLockGlobals(refNum);
 
 	if (gP)
 	{
		gP->currentVolume = volume;
  		PrvUnlockGlobals(gP);
 	}
 	
 	SetLastError(refNum,err);
	return errNone;
}

Err VFSLib_GetVolumeLabel(UInt16 refNum, char* result)
{
	Err err;
	*result =0;
 	err = VFSVolumeGetLabel(GetVolume(refNum), result, 255);
 	SetLastError(refNum,err);
	return errNone;
}

Err VFSLib_SetVolumeLabel(UInt16 refNum, char* label)
{
	Err err = VFSVolumeSetLabel(GetVolume(refNum),label);
 	SetLastError(refNum,err);
	return errNone;
}

Err VFSLib_IsVolumeReadOnly(UInt16 refNum, UInt32* resultP)
{
	VolumeInfoType vi;
	Err err = VFSVolumeInfo(GetVolume(refNum), &vi);
	SetLastError(refNum,err);
	*resultP =  (vi.attributes & vfsVolumeAttrReadOnly) ? 1 : 0;
	return errNone;
}

Err VFSLib_IsVolumeHidden(UInt16 refNum, UInt32* resultP)
{
	VolumeInfoType vi;
	Err err = VFSVolumeInfo(GetVolume(refNum), &vi);
	SetLastError(refNum,err);
	*resultP =  (vi.attributes & vfsVolumeAttrHidden) ? 1 : 0;
	return errNone;
}

Err VFSLib_GetVolumeMediaType(UInt16 refNum, UInt32 *mediaTypeP)
{
	VolumeInfoType vi;
	Err err = VFSVolumeInfo(GetVolume(refNum), &vi);
	SetLastError(refNum,err);
	*mediaTypeP = GetIndexMediaType(vi.mediaType);
	return errNone;
}

Err VFSLib_VolumeUsedSize(UInt16 refNum, UInt32* sizeP)
{
	UInt32 totalSize;
	Err err = VFSVolumeSize(GetVolume(refNum),sizeP, &totalSize);
	SetLastError(refNum,err);
	return errNone;
}

Err VFSLib_VolumeTotalSize(UInt16 refNum, UInt32* sizeP)
{
	 UInt32 usedSize;
	Err err = VFSVolumeSize(GetVolume(refNum),&usedSize, sizeP);
	SetLastError(refNum,err);
	return errNone;
}

Err VFSLib_GetDeviceUniqueIDStr(UInt16 refNum, char* result)
{
	VolumeInfoType vi;
	ExpCardInfoType cardInfo;
	Err err;

	err = VFSVolumeInfo(GetVolume(refNum), &vi);
	if (err == errNone)
	{
	
		err = ExpCardInfo(vi.slotRefNum, &cardInfo);
		if (err == errNone) 
		{
			StrCopy(result,cardInfo.deviceUniqueIDStr); 
		}
	}
	SetLastError(refNum,err);
	return errNone;
}

Err VFSLib_VolumeFormat(UInt16 refNum)
{
	VolumeInfoType vi;
	VFSSlotMountParamType slotParam;
	Err err;

	err = VFSVolumeInfo(GetVolume(refNum), &vi);
	if (err == errNone)
	{
		slotParam.slotRefNum = vi.slotRefNum;
		slotParam.slotLibRefNum = vi.slotLibRefNum;
		slotParam.vfsMountParam.mountClass = vfsMountClass_SlotDriver;

		err = VFSVolumeFormat(NULL, NULL, (VFSAnyMountParamPtr) & slotParam);
	}
	SetLastError(refNum,err);
	return errNone;

/*	
	VFSSlotMountParamType slotParam;
	Err err;

	UInt32 slotIterator = expIteratorStart;

	slotParam.vfsMountParam.mountClass = vfsMountClass_SlotDriver;
	
	err = ExpSlotEnumerate(&slotParam.slotRefNum,&slotIterator);
	if (err != errNone) goto EXIT;
		
	err = ExpSlotLibFind(slotParam.slotRefNum,&slotParam.slotLibRefNum);
	if  (err != errNone) goto EXIT;
	
	err = VFSVolumeFormat(NULL, NULL, (VFSAnyMountParamPtr) & slotParam);
	if (err != errNone) goto EXIT;
	
EXIT:

	SetLastError(refNum,err);
	return err;
*/
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Directory 
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Err VFSLib_DirCreate(UInt16 refNum, char* dirName)
{
	Err err = VFSDirCreate(GetVolume(refNum),dirName);
	SetLastError(refNum,err);
	return errNone;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File 
// FileRef - UInt32
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Err VFSLib_IsEOF(UInt16 refNum, FileRef fileRef, UInt32*  result)
{

	Err err  = VFSFileEOF (fileRef);
	
	SetLastError(refNum, errNone);
	
	if (err == vfsErrFileEOF) 
		*result  = 1; else
		 if ( err == errNone) 
		 *result = 0; 
		 else	 {
	  			*result =1;
	  			SetLastError(refNum, err);
	 		}
	return errNone;
}

Err VFSLib_FileCreate(UInt16 refNum, char* path)
{
	Err err  = VFSFileCreate(GetVolume(refNum),path);
 	SetLastError(refNum, err);
	return errNone;
}

Err VFSLib_Read16(UInt16 refNum, FileRef fileRef, UInt16* res)
{
	Err err = VFSFileRead (fileRef, sizeof(UInt16), res, NULL);
	SetLastError(refNum,err);
	return errNone;
}

Err VFSLib_Read32(UInt16 refNum, FileRef fileRef, UInt32* res)
{
	Err err = VFSFileRead (fileRef, sizeof(UInt32), res, NULL);
	SetLastError(refNum,err);
	return errNone;
}

Err VFSLib_Read64(UInt16 refNum, FileRef fileRef, double* res)
{
	Err err = VFSFileRead (fileRef, sizeof(double), res, NULL);
	SetLastError(refNum,err);
	return errNone;
}

Err VFSLib_ReadString(UInt16 refNum, FileRef fileRef, char* res)
{
	Err err=errNone;
	char * max;
	Int16 maxLen;
	
	maxLen = StrLen(res);
	if (maxLen<255) maxLen = 255;
	max = res + maxLen;
	
	do
	{	
	 err = VFSFileRead (fileRef, sizeof(UInt8),res++, NULL);
	}while (!err && max!=res && *(res-1)!=0 );
	
	if (err || max==res) *res=0;
	
	SetLastError(refNum,err);
	return errNone;
}

Err VFSLib_ReadHuge(UInt16 refNum, FileRef fileRef, char* data, UInt32 size,UInt32 *res)
{
	Err err = VFSFileRead (fileRef, size , data , res);
	SetLastError(refNum,err);
	return errNone;
}

Err VFSLib_Write16(UInt16 refNum, FileRef fileRef, UInt16 data)
{
	Err err = VFSFileWrite ( fileRef,sizeof(UInt16), &data, NULL);
	SetLastError(refNum,err);
	return errNone;
}

Err VFSLib_Write32(UInt16 refNum, FileRef fileRef, UInt32 data)
{
	Err err = VFSFileWrite ( fileRef,sizeof(UInt32), &data, NULL);
	SetLastError(refNum,err);
	return errNone;
}

Err VFSLib_Write64(UInt16 refNum, FileRef fileRef, double data)
{
	Err err = VFSFileWrite ( fileRef,sizeof(double), &data, NULL);
	SetLastError(refNum,err);
	return errNone;
}

Err VFSLib_WriteString(UInt16 refNum,FileRef fileRef, char* str)
{
	Err err = VFSFileWrite (fileRef, StrLen(str)+1, str, NULL);
	SetLastError(refNum,err);
	return errNone;
}

Err VFSLib_WriteHuge(UInt16 refNum, FileRef fileRef, char* data, UInt32 size, UInt32* res)
{
	Err err = VFSFileWrite ( fileRef, size, data,res);
	SetLastError(refNum,err);
	return errNone;
}

Err VFSLib_FileTell(UInt16 refNum,FileRef fileRef, UInt32* pos)
{
	Err err =  VFSFileTell (fileRef,pos);
	SetLastError(refNum, err);
	return errNone;
}

Err VFSLib_FileSize(UInt16 refNum, FileRef fileRef, UInt32 *sizeP)
{
	Err err = VFSFileSize (fileRef, sizeP);
	SetLastError(refNum, err);
	return errNone;
}

Err VFSLib_FileResize(UInt16 refNum,FileRef fileRef, UInt32 newSize)
{
	Err err = VFSFileResize (fileRef,newSize);
	SetLastError(refNum, err);
	return errNone;
}

Err VFSLib_FileSeekBegin(UInt16 refNum, FileRef fileRef, Int32 offset)
{
	Err err = VFSFileSeek (fileRef, vfsOriginBeginning,offset);
	SetLastError(refNum, err);
	return errNone;
}
Err VFSLib_FileSeekCurrent(UInt16 refNum, FileRef fileRef, Int32 offset)
{
	Err err = VFSFileSeek (fileRef, vfsOriginCurrent,offset);
	SetLastError(refNum, err);
	return errNone;
}

Err VFSLib_FileSeekEnd(UInt16 refNum, FileRef fileRef, Int32 offset)
{
	Err err = VFSFileSeek (fileRef, vfsOriginEnd,-offset);
	SetLastError(refNum, err);
	return errNone;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// File & Directory 
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Err VFSLib_Open(UInt16 refNum, char* pathName,UInt32 openMode, FileRef *fileRef)
{
	UInt16 om16 = openMode;

	Err err = VFSFileOpen (GetVolume(refNum), pathName, om16,fileRef);

 	SetLastError(refNum, err);
	return errNone;
}

Err VFSLib_SetAttributes(UInt16 refNum,FileRef fileRef,UInt32 attributes)
{
	Err err;
	UInt32 prevAttr;
	
	err =VFSFileGetAttributes (fileRef,&prevAttr);
	if (err == errNone)
	{
		prevAttr = prevAttr& (~vfsFileAttrDirectory); 
		prevAttr = prevAttr& (~ vfsFileAttrVolumeLabel); 
		attributes = attributes|prevAttr;
		err = VFSFileSetAttributes (fileRef,attributes);
	}
	SetLastError(refNum, err);
	return errNone;
}

Err VFSLib_ResetAttributes(UInt16 refNum,FileRef fileRef,UInt32 attributes)
{
	Err err;
	UInt32 prevAttr;
	
	err =VFSFileGetAttributes (fileRef,&prevAttr);
	if (err == errNone)
	{
		prevAttr = prevAttr& (~vfsFileAttrDirectory); 
		prevAttr = prevAttr& (~ vfsFileAttrVolumeLabel); 
		attributes = prevAttr&(~attributes);
		err = VFSFileSetAttributes (fileRef,attributes);
	}
	SetLastError(refNum, err);
	return errNone;
}


Err VFSLib_GetAttributes(UInt16 refNum,FileRef fileRef,UInt32 checkAttributes,UInt32* res)
{
	UInt32 attributes;
	Err err =VFSFileGetAttributes (fileRef,&attributes);
	*res = (checkAttributes&attributes)? 1 : 0;

 	SetLastError(refNum, err);
	return errNone;
}
//// Enumerationg the files in directory /////
Err VFSLib_BeginDirEntryEnumerate(UInt16 refNum,char *dir)
{
	PSGlobal	 gP = NULL;
	Err		 err =dmErrMemError;
 
 	gP = PrvLockGlobals(refNum);
 
 	if (gP)
 	{
  		gP->fileIterator = vfsIteratorStart;
  		err  = VFSFileOpen(gP->currentVolume, dir, vfsModeRead, &(gP->dirEnumRef) );
  		PrvUnlockGlobals(gP);
 	}
 	
 	SetLastError(refNum, err);
	return errNone;
}

Err VFSLib_EndDirEntryEnumerate(UInt16 refNum)
{
	PSGlobal	 gP = NULL;
	Err		 err =dmErrMemError;
 
 	gP = PrvLockGlobals(refNum);
 
 	if (gP)
 	{
 		err = VFSFileClose(gP->dirEnumRef);
  		PrvUnlockGlobals(gP);
 	}
 	
 	SetLastError(refNum, err);
	return errNone;
}

Err VFSLib_DirEntryEnumerate(UInt16 refNum, char* fileName)
{
 	PSGlobal		gP = NULL;
	Err		 	err =dmErrMemError;
	FileInfoType 	info;
 
 	*fileName=0;
 	gP = PrvLockGlobals(refNum);
 	//*res = 0;
 	if (gP)
 	{
 		info.nameP = fileName;
		info.nameBufLen = 255; 		
 		err = VFSDirEntryEnumerate (gP->dirEnumRef, &(gP->fileIterator), &info);
  		PrvUnlockGlobals(gP);
 		//if (gP->fileIterator != vfsIteratorStop && err == errNone) *res = 1;
 	}
 	
 	SetLastError(refNum, err);
	return errNone;
}
///////////////////////////////////

Err VFSLib_Delete(UInt16 refNum, char* path)
{
 	Err err = VFSFileDelete(GetVolume(refNum), path);
 	SetLastError(refNum, err);
	return errNone;
}

Err VFSLib_Close (UInt16 refNum, FileRef fileRef)
{
	Err err = VFSFileClose (fileRef);
	SetLastError(refNum, err);
	return errNone;
}
Err VFSLib_Rename(UInt16 refNum, char* pathNameP, char* newNameP)
{
	Err err = VFSFileRename (GetVolume(refNum), pathNameP, newNameP);
	SetLastError(refNum, err);
	return errNone;
}

// Set Date
Err VFSLib_SetDateCreated(UInt16 refNum,FileRef fileRef,UInt32 date)
{
	Err err = VFSFileSetDate (fileRef, vfsFileDateCreated, date);
	SetLastError(refNum, err);
	return errNone;
}

Err VFSLib_SetDateModified(UInt16 refNum,FileRef fileRef,UInt32 date)
{
	Err err = VFSFileSetDate (fileRef, vfsFileDateModified, date);
	SetLastError(refNum, err);
	return errNone;
}

Err VFSLib_SetDateAccessed(UInt16 refNum,FileRef fileRef,UInt32 date)
{
	Err err = VFSFileSetDate (fileRef, vfsFileDateAccessed, date);
	SetLastError(refNum, err);
	return errNone;
}
// Get Date

Err VFSLib_GetDateCreated(UInt16 refNum, FileRef fileRef, UInt32* date)
{
	Err err = VFSFileGetDate (fileRef, vfsFileDateCreated, date);
	SetLastError(refNum, err);
	return errNone;
}

Err VFSLib_GetDateModified(UInt16 refNum, FileRef fileRef, UInt32* date)
{
	Err err = VFSFileGetDate (fileRef, vfsFileDateModified, date);
	SetLastError(refNum, err);
	return errNone;
}

Err VFSLib_GetDateAccessed(UInt16 refNum, FileRef fileRef, UInt32* date)
{
	Err err = VFSFileGetDate (fileRef, vfsFileDateAccessed, date);
	SetLastError(refNum, err);
	return errNone;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Export/Import 
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CARD_NO	(0)

Err VFSLib_Import(UInt16 refNum, char* pathName, char* dbName)
{
	Err err;
	UInt16 cardNo;
	LocalID dbID;
	*dbName =0;
	err = VFSImportDatabaseFromFile (GetVolume(refNum),  pathName,  &cardNo,  &dbID);
	if (err==errNone)
	{
	 	err =DmDatabaseInfo (CARD_NO, dbID, dbName, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	}
	SetLastError(refNum,err);
	return errNone;
}

Err VFSLib_Export(UInt16 refNum, char* dbName, char* pathName )
{
	Err err;
	LocalID dbID;
	
	dbID  = DmFindDatabase (CARD_NO, dbName);
	
	if (dbID)
	{
		err = VFSExportDatabaseToFile (GetVolume(refNum), pathName, CARD_NO, dbID);
	}else
	{
		err = DmGetLastErr();
	}
	
	SetLastError(refNum,err);
	return errNone;
}

////// Custom Import/export //////
static Boolean ProgressTextCB(PrgCallbackDataPtr cbP);
static Err CopyProgressCB(UInt32 size, UInt32 offset, void *userDataP);
static Err ImportFile(UInt16 volRefNum, Char *fullPathP, UInt16 *cardNoP, LocalID *dbIDP,char* dialogTitle, char* actionStr);
static Err ExportFile(UInt16 volRefNum, Char *fullPathP, UInt16 cardNo, LocalID dbID,char* dialogTitle, char* actionStr);

typedef struct
 {
	ProgressType *progressP;
	const Char *nameP;
	const Char *actionP;
	const Char *dialogTitleP;
} CBDataType, *CBDataPtr;

static Boolean ProgressTextCB(PrgCallbackDataPtr cbP)
 {
	const Char *nameP = ((CBDataPtr) cbP->userDataP)->nameP;
	Char *actionP = (char*)((CBDataPtr) cbP->userDataP)->actionP;
	// Set up the progress text to be displayed
	StrPrintF(cbP->textP, "%s ",actionP);// Importing// Exporting
	cbP->textChanged = true;
	return true; // So what we specify here is used to update the dialog
}

static Err CopyProgressCB(UInt32 size, UInt32 offset, void *userDataP)
 {
	CBDataPtr CBDataP = (CBDataPtr) userDataP;
	
	//if (offset == 0)
	if (CBDataP->progressP==NULL)
	 { 
	 	// If we're just starting, we need to set up the dialog
	 	
		CBDataP->progressP = PrgStartDialog(CBDataP->dialogTitleP, ProgressTextCB,CBDataP);
		if (!CBDataP->progressP)	return memErrNotEnoughSpace;
	} else
	{
		EventType event;
		Boolean handled;
		do
		 {
			EvtGetEvent(&event, 0); // Check for events
			handled = PrgHandleEvent(CBDataP->progressP, &event);
			if (!handled)
			 {
			 	 // Did the user tap the "Cancel" button?
				if( PrgUserCancel(CBDataP->progressP) ) return exgErrUserCancel;
			}
		} while(event.eType != sysEventNilEvent);
	}
	return errNone;
}

static Err ImportFile(UInt16 volRefNum, Char *fullPathP, UInt16 *cardNoP, LocalID *dbIDP,char* dialogTitle, char* actionStr)
{
	CBDataType userData;
	Err err;
	
	userData.progressP = NULL;
	userData.actionP = actionStr;
	userData.dialogTitleP = dialogTitle;
	userData.nameP = fullPathP + StrLen(fullPathP)-1;
	while (fullPathP != userData.nameP &&  *(userData.nameP-1)!= '/' ) userData.nameP--;
	
	err = VFSImportDatabaseFromFileCustom(volRefNum, fullPathP, cardNoP, dbIDP, CopyProgressCB, &userData);
	
	if (userData.progressP) // If the progress dialog was displayed, remove it.
		PrgStopDialog(userData.progressP, (err == exgErrUserCancel) );
	return err;
}

Err VFSLib_ImportDialog(UInt16 refNum, char* pathName, char* dialogTitle, char* actionStr, char* dbName)
{
	Err err;
	UInt16 cardNo;
	LocalID dbID;
	*dbName =0;
	err = ImportFile (GetVolume(refNum),  pathName, &cardNo,  &dbID,dialogTitle, actionStr );
	if (err==errNone)
	{
	 	err =DmDatabaseInfo (CARD_NO, dbID, dbName, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	}
	SetLastError(refNum,err);
	return errNone;
}

static Err ExportFile(UInt16 volRefNum, Char *fullPathP, UInt16 cardNo, LocalID dbID,char* dialogTitle, char* actionStr)
{
	CBDataType userData;
	Err err;
	
	userData.progressP = NULL;
	userData.actionP = actionStr;
	userData.dialogTitleP = dialogTitle;
	userData.nameP = fullPathP;
//	userData.nameP = fullPathP + StrLen(fullPathP)-1;
//	while (fullPathP != userData.nameP &&  *(userData.nameP-1)!= '/' ) userData.nameP--;
	
	err = VFSExportDatabaseToFileCustom( volRefNum, fullPathP, cardNo,  dbID, CopyProgressCB, &userData);

	if (userData.progressP) // If the progress dialog was displayed, remove it.
		PrgStopDialog(userData.progressP, (err == exgErrUserCancel) );
	return err;
}

Err VFSLib_ExportDialog(UInt16 refNum, char* dbName, char* pathName ,char* dialogTitle, char* actionStr)
{
	Err err;
	LocalID dbID;
	
	dbID  = DmFindDatabase (CARD_NO, dbName);
	
	if (dbID)
	{
		err = ExportFile (GetVolume(refNum), pathName, CARD_NO, dbID,dialogTitle, actionStr);
	}else
	{
		err = DmGetLastErr();
	}
	
	SetLastError(refNum,err);
	return errNone;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Default Directory 
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static UInt32 GetMediaType(UInt32 index)
{
/*
0 expMediaType_Any 			'wild' 	//Matches all media types when looking up a default directory
1 expMediaType_MemoryStick		'mstk' 	//Memory stick
2 expMediaType_CompactFlash 	'cfsh' 	//Compact Flash
3 expMediaType_SecureDigital 	'sdig' 	//Secure Digital
4 expMediaType_MultiMediaCard 	'mmcd' 	//MultiMedia Card
5 expMediaType_SmartMedia 		'smed' 	//SmartMedia
6 expMediaType_RAMDisk 		'ramd' 	//A RAM disk based media
7 expMediaType_PoserHost 		'pose' 	//Host file system emulated by the Palm OS® Emulator
8 expMediaType_MacSim 		'PSim' 	//Host file syste memulated by the Mac Simulator
*/

	UInt32 mt[10] = 
	{
		'wild',	//0
		'mstk',	//1
		'cfsh',	//2
		'sdig',	//3
		'mmcd',	//4
		'smed',	//5
		'ramd',	//6
		'pose',	//7
		'PSim',	//8
		'XxXx'	//9 - error
	};
	if (index>9) index = 9;
	return mt[index];
}

static UInt32 GetIndexMediaType(UInt32 mediaType)
{
	UInt32 index;
	UInt32 mt[10] = 
	{
		'wild',	//0
		'mstk',	//1
		'cfsh',	//2
		'sdig',	//3
		'mmcd',	//4
		'smed',	//5
		'ramd',	//6
		'pose',	//7
		'PSim',	//8
		'XxXx'	//9 - error
	};
	
	for (index =0; index< sizeof(mt)/sizeof(UInt32); index ++) if (mt[index]==mediaType) break;
	return index;
}

Err VFSLib_RegisterDefaultDirectory(UInt16 refNum, char* fileType, UInt32 indexMediaType, char* path)
{
	Err err = VFSRegisterDefaultDirectory(fileType, GetMediaType(indexMediaType) , path);
	
	SetLastError(refNum, err);
	return errNone;
}

Err VFSLib_UnregisterDefaultDirectory(UInt16 refNum, char* fileType, UInt32 indexMediaType)
{
	Err err = VFSUnregisterDefaultDirectory(fileType, GetMediaType(indexMediaType) );

	SetLastError(refNum, err);
	return errNone;
}

Err VFSLib_GetDefaultDirectory(UInt16 refNum,char* fileType, char*path)
{
	Err err;
	UInt16 len;

	*path =0;
	len = StrLen(path);
	if (len<255) len = 255;
	
	err = VFSGetDefaultDirectory (GetVolume(refNum), fileType, path,&len);
	
	SetLastError(refNum, err);
	return errNone;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Resourses && records 
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Err VFSLib_GetResource(UInt16 refNum, FileRef fileRef, UInt32 id, char* resType, MemHandle* resHP)
{
	DmResID resID = id;
	DmResType type = *((UInt32*)resType);

	Err err = VFSFileDBGetResource (fileRef,  type,  resID, resHP);

	SetLastError(refNum, err);
	return errNone;
}

//////////////////////////////////////////
// Private functions
static PSGlobal PrvMakeGlobals(UInt16 refNum)
{
	PSGlobal			gP = NULL;							// our globals pointer
	MemHandle		gH;									// our globals handle
	SysLibTblEntryPtr	libEntryP;								// pointer to our library table entry

	libEntryP = SysLibTblEntry(refNum);							// get our system library table entry
	ErrFatalDisplayIf(libEntryP == NULL, "invalid VFSLib refNum");
	
	// Error check to make sure the globals don't already exist
	ErrFatalDisplayIf(libEntryP->globalsP, "VFSLib globals already exist");
	
	gH = MemHandleNew(sizeof(SGlobal));
	if ( !gH )	return( NULL );
	
	libEntryP->globalsP = (void*)gH;

	gP = PrvLockGlobals(refNum);
	ErrFatalDisplayIf(gP == NULL, "failed to lock VFSLib globals");
	
	MemPtrSetOwner(gP, 0); //owner of our globals is system
	
	// Initialize our library globals
	MemSet(gP, sizeof(SGlobal), 0);
	gP->thisLibRefNum = refNum;		
	gP->openCount = 0;
	gP->lastError = 0; // initial - all OK				
	
	return( gP );							
}

static void PrvFreeGlobals(UInt16 refNum)
{
	MemHandle		gH;								// our globals handle
	SysLibTblEntryPtr	libEntryP;							// pointer to our library table entry

	libEntryP = SysLibTblEntry(refNum);						// get our system library table entry
	ErrFatalDisplayIf(libEntryP == NULL, "invalid VFSLib refNum");
	
	gH = (MemHandle)(libEntryP->globalsP);					// get our globals handle from the entry
	
	if ( gH )
		{
		libEntryP->globalsP = NULL;							
		MemHandleFree(gH);
		}
}

static UInt16 GetVolume(UInt16 refNum)
{
 	PSGlobal	 gP = NULL;
 	UInt16 vol;
 	gP = PrvLockGlobals(refNum);
 
 	if (gP)
 	{
  		vol = gP->currentVolume;
  		PrvUnlockGlobals(gP);
 	}
 	
	return vol;
}
static void SetLastError(UInt16 refNum, Err error)
{
 	PSGlobal	 gP = NULL;
 
 	gP = PrvLockGlobals(refNum);
 
 	if (gP)
 	{
  		gP->lastError = error;
  		PrvUnlockGlobals(gP);
 	}
}

static PSGlobal PrvLockGlobals(UInt16 refNum)
{
	PSGlobal			gP = NULL;
	MemHandle		gH;
	SysLibTblEntryPtr	libEntryP;

	libEntryP = SysLibTblEntry(refNum);						// get our system library table entry
	if ( libEntryP )	gH = (MemHandle)(libEntryP->globalsP);		// get our globals handle from the entry
	if ( gH )		gP = (PSGlobal)MemHandleLock(gH);		// lock our globals
	return( gP );
}

static Boolean PrvIsLibOpen(UInt16 refNum)
{
	PSGlobal	gP;
	Boolean	isOpen = false;
	
	gP = PrvLockGlobals(refNum);
	
	if ( gP )
		{
		isOpen = true;
		PrvUnlockGlobals(gP);
		}
	
	return( isOpen );
}

static void PrvUnlockGlobals(PSGlobal gP)
{
  if (gP) MemPtrUnlock(gP);
}
