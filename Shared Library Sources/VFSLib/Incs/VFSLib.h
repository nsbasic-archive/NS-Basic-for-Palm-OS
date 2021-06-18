#ifndef __VFS_LIB_H__
#define __VFS_LIB_H__

#ifdef BUILDING_VFS_LIB
	#define VFS_LIB_TRAP(trapNum)
#else
	#define VFS_LIB_TRAP(trapNum) SYS_TRAP(trapNum)
#endif


// Palm OS common definitions
#include <PalmTypes.h>
#include <SystemResources.h>

#include <VFSMgr.h>

/********************************************************************
 * Type and creator of VFS  Library database
 ********************************************************************/
#define		VFSLibCreatorID		'NSVf'			//  Library database creator
#define		VFSLibTypeID			'libr'				// Standard library database type

/********************************************************************
 * Internal library name which can be passed to SysLibFind()
 ********************************************************************/
#define		VFSLibName			"NSBVFSLib"		


/************************************************************
 * VFS Library result codes
 * (appErrorClass is reserved for 3rd party apps/libraries.
 * It is defined in SystemMgr.h)
 *************************************************************/

#define vfsErrParam			(appErrorClass | 1)		// invalid parameter
#define vfsErrNotOpen			(appErrorClass | 2)		// library is not open
#define vfsErrStillOpen			(appErrorClass | 3)		// returned from VFSLibClose() if  the library is still open by others
#define vfsErrMemory			(appErrorClass | 4)		// memory error occurred

typedef enum {
	vfsLibTrapGetLibAPIVersion = sysLibTrapCustom,
	vfsLibTrapGetLastError,
	vfsLibTrapInit,

// volume
	vfsLibTrap_BeginVolumeEnumerate,
	vfsLibTrap_GetNextVolume,
	vfsLibTrap_SetVolume,
	vfsLibTrap_GetVolumeLabel,
	vfsLibTrap_SetVolumeLabel,
	vfsLibTrap_IsVolumeReadOnly,
	vfsLibTrap_IsVolumeHidden,
	vfsLibTrap_VolumeUsedSize,
	vfsLibTrap_VolumeTotalSize,
	vfsLibTrap_VolumeFormat,
	vfsLibTrap_GetVolumeMediaType,
// dir
	vfsLibTrap_DirCreate,
// file
	vfsLibTrap_IsEOF,
	vfsLibTrap_FileCreate,
	vfsLibTrap_Read16,
	vfsLibTrap_Read32,
	vfsLibTrap_Read64,
	vfsLibTrap_ReadString,
	vfsLibTrap_Write16,
	vfsLibTrap_Write32,
	vfsLibTrap_Write64,
	vfsLibTrap_WriteString,
	vfsLibTrap_FileTell,
	vfsLibTrap_FileSize,
	vfsLibTrap_FileResize,
	vfsLibTrap_FileSeekBegin,
	vfsLibTrap_FileSeekCurrent,
	vfsLibTrap_FileSeekEnd,
// File & dir
	vfsLibTrap_Delete,
	vfsLibTrap_Close,
	vfsLibTrap_Rename,
	vfsLibTrap_SetDateCreated,
	vfsLibTrap_SetDateModified,
	vfsLibTrap_SetDateAccessed,
	vfsLibTrap_GetDateCreated,
	vfsLibTrap_GetDateModified,
	vfsLibTrap_GetDateAccessed,
	vfsLibTrap_BeginDirEntryEnumerate,
	vfsLibTrap_EndDirEntryEnumerate,
	vfsLibTrap_DirEntryEnumerate,
	vfsLibTrap_SetAttributes,
	vfsLibTrap_ResetAttributes,
	vfsLibTrap_GetAttributes,
	vfsLibTrap_Open,
// Import/export
	vfsLibTrap_Import,
	vfsLibTrap_Export,
	vfsLibTrap_ImportDialog,
	vfsLibTrap_ExportDialog,
// Default dir
	vfsLibTrap_RegisterDefaultDirectory,
	vfsLibTrap_UnregisterDefaultDirectory,
	vfsLibTrap_GetDefaultDirectory,
	
	vfsLibTrap_GetResource,
	
	vfsLibTrap_ReadHuge,
	vfsLibTrap_WriteHuge,				

// Update to version 2
	vfsLibTrap_GetDeviceUniqueIDStr,
	
	vfsLibLibTrapLast
	
	} VFSLibTrapNumberEnum;


/********************************************************************
 * API Prototypes
 ********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif


//--------------------------------------------------
// Standard library open, close, sleep and wake functions
//--------------------------------------------------

extern Err VFSLibOpen(UInt16 refNum)				VFS_LIB_TRAP(sysLibTrapOpen);
extern Err VFSLibClose(UInt16 refNum)				VFS_LIB_TRAP(sysLibTrapClose);
extern Err VFSLibSleep(UInt16 refNum)				VFS_LIB_TRAP(sysLibTrapSleep);
extern Err VFSLibWake(UInt16 refNum)				VFS_LIB_TRAP(sysLibTrapWake);

//--------------------------------------------------
// Custom library API functions
//--------------------------------------------------
	
extern Err VFSLibGetLibAPIVersion(UInt16 refNum, UInt32 * dwVerP)										VFS_LIB_TRAP(vfsLibTrapGetLibAPIVersion);
extern Err VFSLibGetLastError(UInt16 refNum, UInt32* errorP)											VFS_LIB_TRAP(vfsLibTrapGetLastError);
//
extern Err VFSLibInit(UInt16 refNum, UInt32* result)														VFS_LIB_TRAP(vfsLibTrapInit);
// Volume
extern Err VFSLib_BeginVolumeEnumerate(UInt16 refNum)												VFS_LIB_TRAP(vfsLibTrap_BeginVolumeEnumerate);
extern Err VFSLib_GetNextVolume(UInt16 refNum, UInt32* volumeP)										VFS_LIB_TRAP(vfsLibTrap_GetNextVolume);
extern Err VFSLib_SetVolume(UInt16 refNum, UInt32 volume)												VFS_LIB_TRAP(vfsLibTrap_SetVolume);
extern Err VFSLib_GetVolumeLabel(UInt16 refNum, char* result)											VFS_LIB_TRAP(vfsLibTrap_GetVolumeLabel);
extern Err VFSLib_SetVolumeLabel(UInt16 refNum, char* label)											VFS_LIB_TRAP(vfsLibTrap_SetVolumeLabel);
extern Err VFSLib_IsVolumeReadOnly(UInt16 refNum, UInt32* resultP)										VFS_LIB_TRAP(vfsLibTrap_IsVolumeReadOnly);
extern Err VFSLib_IsVolumeHidden(UInt16 refNum, UInt32* resultP)										VFS_LIB_TRAP(vfsLibTrap_IsVolumeHidden);
extern Err VFSLib_VolumeUsedSize(UInt16 refNum, UInt32* sizeP)										VFS_LIB_TRAP(vfsLibTrap_VolumeUsedSize);
extern Err VFSLib_VolumeTotalSize(UInt16 refNum, UInt32* sizeP)											VFS_LIB_TRAP(vfsLibTrap_VolumeTotalSize);
extern Err VFSLib_VolumeFormat(UInt16 refNum)														VFS_LIB_TRAP(vfsLibTrap_VolumeFormat);
extern Err VFSLib_GetVolumeMediaType(UInt16 refNum, UInt32 *mediaTypeP)								VFS_LIB_TRAP(vfsLibTrap_GetVolumeMediaType);
// Dir
extern Err VFSLib_DirCreate(UInt16 refNum, char* dirName)												VFS_LIB_TRAP(vfsLibTrap_DirCreate);
// File
extern Err VFSLib_IsEOF(UInt16 refNum, FileRef fileRef, UInt32*  result)										VFS_LIB_TRAP(vfsLibTrap_IsEOF); // 1- eof (or err), 0 - not
extern Err VFSLib_FileCreate(UInt16 refNum, char* path)												VFS_LIB_TRAP(vfsLibTrap_FileCreate);
extern Err VFSLib_Read16(UInt16 refNum, FileRef fileRef, UInt16* res)										VFS_LIB_TRAP(vfsLibTrap_Read16);
extern Err VFSLib_Read32(UInt16 refNum, FileRef fileRef, UInt32* res)										VFS_LIB_TRAP(vfsLibTrap_Read32);
extern Err VFSLib_Read64(UInt16 refNum, FileRef fileRef, double* res)										VFS_LIB_TRAP(vfsLibTrap_Read64);
extern Err VFSLib_ReadString(UInt16 refNum, FileRef fileRef, char* res)										VFS_LIB_TRAP(vfsLibTrap_ReadString);
extern Err VFSLib_Write16(UInt16 refNum, FileRef fileRef, UInt16 data)										VFS_LIB_TRAP(vfsLibTrap_Write16);
extern Err VFSLib_Write32(UInt16 refNum, FileRef fileRef, UInt32 data)										VFS_LIB_TRAP(vfsLibTrap_Write32);
extern Err VFSLib_Write64(UInt16 refNum, FileRef fileRef, double data)										VFS_LIB_TRAP(vfsLibTrap_Write64);
extern Err VFSLib_WriteString(UInt16 refNum, FileRef fileRef, char* str)										VFS_LIB_TRAP(vfsLibTrap_WriteString);
extern Err VFSLib_FileTell(UInt16 refNum,FileRef fileRef, UInt32* pos)										VFS_LIB_TRAP(vfsLibTrap_FileTell);
extern Err VFSLib_FileSize(UInt16 refNum, FileRef fileRef, UInt32 *sizeP)									VFS_LIB_TRAP(vfsLibTrap_FileSize);
extern Err VFSLib_FileResize(UInt16 refNum,FileRef fileRef, UInt32 newSize)									VFS_LIB_TRAP(vfsLibTrap_FileResize);
extern Err VFSLib_FileSeekBegin(UInt16 refNum, FileRef fileRef, Int32 offset)									VFS_LIB_TRAP(vfsLibTrap_FileSeekBegin);
extern Err VFSLib_FileSeekCurrent(UInt16 refNum, FileRef fileRef, Int32 offset)								VFS_LIB_TRAP(vfsLibTrap_FileSeekCurrent);
extern Err VFSLib_FileSeekEnd(UInt16 refNum, FileRef fileRef, Int32 offset)									VFS_LIB_TRAP(vfsLibTrap_FileSeekEnd);
// File & dir
extern Err VFSLib_Delete(UInt16 refNum, char* path)													VFS_LIB_TRAP(vfsLibTrap_Delete);
extern Err VFSLib_Close (UInt16 refNum, FileRef fileRef)												VFS_LIB_TRAP(vfsLibTrap_Close);
extern Err VFSLib_Rename(UInt16 refNum, char* pathNameP, char* newNameP)								VFS_LIB_TRAP(vfsLibTrap_Rename);
extern Err VFSLib_SetDateCreated(UInt16 refNum,FileRef fileRef,UInt32 date)								VFS_LIB_TRAP(vfsLibTrap_SetDateCreated);
extern Err VFSLib_SetDateModified(UInt16 refNum,FileRef fileRef,UInt32 date)								VFS_LIB_TRAP(vfsLibTrap_SetDateModified);
extern Err VFSLib_SetDateAccessed(UInt16 refNum,FileRef fileRef,UInt32 date)								VFS_LIB_TRAP(vfsLibTrap_SetDateAccessed);
extern Err VFSLib_GetDateCreated(UInt16 refNum, FileRef fileRef, UInt32* date)								VFS_LIB_TRAP(vfsLibTrap_GetDateCreated);
extern Err VFSLib_GetDateModified(UInt16 refNum, FileRef fileRef, UInt32* date)								VFS_LIB_TRAP(vfsLibTrap_GetDateModified);
extern Err VFSLib_GetDateAccessed(UInt16 refNum, FileRef fileRef, UInt32* date)								VFS_LIB_TRAP(vfsLibTrap_GetDateAccessed);
extern Err VFSLib_BeginDirEntryEnumerate(UInt16 refNum,char *dir)										VFS_LIB_TRAP(vfsLibTrap_BeginDirEntryEnumerate);
extern Err VFSLib_EndDirEntryEnumerate(UInt16 refNum)												VFS_LIB_TRAP(vfsLibTrap_EndDirEntryEnumerate);
extern Err VFSLib_DirEntryEnumerate(UInt16 refNum, char* fileName)										VFS_LIB_TRAP(vfsLibTrap_DirEntryEnumerate);
extern Err VFSLib_SetAttributes(UInt16 refNum,FileRef fileRef,UInt32 attributes)								VFS_LIB_TRAP(vfsLibTrap_SetAttributes);
extern Err VFSLib_ResetAttributes(UInt16 refNum,FileRef fileRef,UInt32 attributes)								VFS_LIB_TRAP(vfsLibTrap_ResetAttributes);

extern Err VFSLib_GetAttributes(UInt16 refNum,FileRef fileRef,UInt32 checkAttributes,UInt32* res)					VFS_LIB_TRAP(vfsLibTrap_GetAttributes);
extern Err VFSLib_Open(UInt16 refNum, char* pathName,UInt32 openMode, FileRef *fileRef)						VFS_LIB_TRAP(vfsLibTrap_Open);
// Import/export
extern Err VFSLib_Import(UInt16 refNum, char* pathName, char* dbName)									VFS_LIB_TRAP(vfsLibTrap_Import);
extern Err VFSLib_Export(UInt16 refNum, char* dbName, char* pathName )									VFS_LIB_TRAP(vfsLibTrap_Export);
extern Err VFSLib_ImportDialog(UInt16 refNum, char* pathName, char* dialogTitle, char* actionStr, char* dbName)	VFS_LIB_TRAP(vfsLibTrap_ImportDialog);
extern Err VFSLib_ExportDialog(UInt16 refNum, char* dbName, char* pathName ,char* dialogTitle, char* actionStr)	VFS_LIB_TRAP(vfsLibTrap_ExportDialog);
// Default dir
extern Err VFSLib_RegisterDefaultDirectory(UInt16 refNum, char* fileType, UInt32 indexMediaType, char* path)		VFS_LIB_TRAP(vfsLibTrap_RegisterDefaultDirectory);
extern Err VFSLib_UnregisterDefaultDirectory(UInt16 refNum, char* fileType, UInt32 indexMediaType)				VFS_LIB_TRAP(vfsLibTrap_UnregisterDefaultDirectory);
extern Err VFSLib_GetDefaultDirectory(UInt16 refNum, char* fileType, char*path)								VFS_LIB_TRAP(vfsLibTrap_GetDefaultDirectory);				

extern Err VFSLib_GetResource(UInt16 refNum, FileRef fileRef, UInt32 id, char* resType, MemHandle* resHP)		VFS_LIB_TRAP(vfsLibTrap_GetResource);

extern Err VFSLib_ReadHuge(UInt16 refNum, FileRef fileRef, char* data,UInt32 size, UInt32 *res)					VFS_LIB_TRAP(vfsLibTrap_ReadHuge);
extern Err VFSLib_WriteHuge(UInt16 refNum, FileRef fileRef, char* data, UInt32 size, UInt32* res)					VFS_LIB_TRAP(vfsLibTrap_WriteHuge);
				
extern Err VFSLib_GetDeviceUniqueIDStr(UInt16 refNum, char* result)											VFS_LIB_TRAP(vfsLibTrap_GetDeviceUniqueIDStr);
// For loading the library in Palm OS Mac emulation mode
extern Err VFSLibInstall(UInt16 refNum, SysLibTblEntryPtr entryP);

#ifdef __cplusplus 
}
#endif

#endif	// __VFS_LIB_H__
