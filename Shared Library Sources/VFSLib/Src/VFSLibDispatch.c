#ifndef	PILOT_PRECOMPILED_HEADERS_OFF
#define	PILOT_PRECOMPILED_HEADERS_OFF
#endif

#if __PALMOS_TRAPS__
		#define EMULATION_LEVEL		EMULATION_NONE		// building Pilot executable
#endif

#undef __PALMOS_TRAPS__
#define __PALMOS_TRAPS__ 	0
#define	USE_TRAPS 	0


#include <PalmOS.h>

#include "VFSLib.h"
#include "VFSLibPrv.h"

// Private routines

#if EMULATION_LEVEL == EMULATION_NONE
	#define VFSLibInstall		__Startup__
#endif

// Local prototypes

Err VFSLibInstall(UInt16 refNum, SysLibTblEntryPtr entryP);
static MemPtr	asm VFSLibDispatchTable(void);

// Statndard functions

Err VFSLibInstall(UInt16 refNum, SysLibTblEntryPtr entryP)
{
	// Install pointer to our dispatch table
	entryP->dispatchTblP = (MemPtr*)VFSLibDispatchTable();
	
	// Initialize globals pointer to zero (we will set up our library  globals in the library "open" call).
	entryP->globalsP = 0;

	return 0;
}

#if EMULATION_LEVEL == EMULATION_NONE
	#define prvJmpSize		4					// Palm OS presently uses short jumps
#elif EMULATION_LEVEL == EMULATION_MAC
	#define prvJmpSize		6					// Our Mac builds use long jumps
#else
	#error unsupported emulation mode
#endif	// EMULATION_LEVEL...

#define libDispatchEntry(index)		(kOffset+((index)*prvJmpSize))

#define libDispEntryEnum(e)			(kOffset+((e - sysLibTrapCustom+4)*prvJmpSize))
//#define	kOffset		(2*7)			// 2 * (Number of function+1)
#define kOffset			(2*(vfsLibLibTrapLast - sysLibTrapCustom+5))

static MemPtr	asm VFSLibDispatchTable(void)
{
	LEA		@Table, A0								// table ptr
	RTS												// exit with it

@Table:
	// Offset to library name
	DC.W		@Name
	
	// Standard traps
	DC.W		libDispatchEntry(0)					// Open
	DC.W		libDispatchEntry(1)					// Close
	DC.W		libDispatchEntry(2)					// Sleep
	DC.W		libDispatchEntry(3)					// Wake
	
// Start of the Custom traps
	DC.W		libDispEntryEnum(vfsLibTrapGetLibAPIVersion)			// GetLibAPIVersion
	DC.W		libDispEntryEnum(vfsLibTrapGetLastError)				// GetLastError
	DC.W		libDispEntryEnum(vfsLibTrapInit)						
// volume
	DC.W		libDispEntryEnum(vfsLibTrap_BeginVolumeEnumerate)
	DC.W		libDispEntryEnum(vfsLibTrap_GetNextVolume)
	DC.W		libDispEntryEnum(vfsLibTrap_SetVolume)
	DC.W		libDispEntryEnum(vfsLibTrap_GetVolumeLabel)
	DC.W		libDispEntryEnum(vfsLibTrap_SetVolumeLabel)
	DC.W		libDispEntryEnum(vfsLibTrap_IsVolumeReadOnly)
	DC.W		libDispEntryEnum(vfsLibTrap_IsVolumeHidden)
	DC.W		libDispEntryEnum(vfsLibTrap_VolumeUsedSize)
	DC.W		libDispEntryEnum(vfsLibTrap_VolumeTotalSize)
	DC.W		libDispEntryEnum(vfsLibTrap_VolumeFormat)
	DC.W		libDispEntryEnum(vfsLibTrap_GetVolumeMediaType)
// dir
	DC.W		libDispEntryEnum(vfsLibTrap_DirCreate)
// file
	DC.W		libDispEntryEnum(vfsLibTrap_IsEOF)
	DC.W		libDispEntryEnum(vfsLibTrap_FileCreate)
	DC.W		libDispEntryEnum(vfsLibTrap_Read16)
	DC.W		libDispEntryEnum(vfsLibTrap_Read32)
	DC.W		libDispEntryEnum(vfsLibTrap_Read64)
	DC.W		libDispEntryEnum(vfsLibTrap_ReadString)
	DC.W		libDispEntryEnum(vfsLibTrap_Write16)
	DC.W		libDispEntryEnum(vfsLibTrap_Write32)
	DC.W		libDispEntryEnum(vfsLibTrap_Write64)
	DC.W		libDispEntryEnum(vfsLibTrap_WriteString)
	DC.W		libDispEntryEnum(vfsLibTrap_FileTell)
	DC.W		libDispEntryEnum(vfsLibTrap_FileSize)
	DC.W		libDispEntryEnum(vfsLibTrap_FileResize)
	DC.W		libDispEntryEnum(vfsLibTrap_FileSeekBegin)
	DC.W		libDispEntryEnum(vfsLibTrap_FileSeekCurrent)
	DC.W		libDispEntryEnum(vfsLibTrap_FileSeekEnd)
// File & dir
	DC.W		libDispEntryEnum(vfsLibTrap_Delete)
	DC.W		libDispEntryEnum(vfsLibTrap_Close)
	DC.W		libDispEntryEnum(vfsLibTrap_Rename)
	DC.W		libDispEntryEnum(vfsLibTrap_SetDateCreated)
	DC.W		libDispEntryEnum(vfsLibTrap_SetDateModified)
	DC.W		libDispEntryEnum(vfsLibTrap_SetDateAccessed)
	DC.W		libDispEntryEnum(vfsLibTrap_GetDateCreated)
	DC.W		libDispEntryEnum(vfsLibTrap_GetDateModified)
	DC.W		libDispEntryEnum(vfsLibTrap_GetDateAccessed)
	DC.W		libDispEntryEnum(vfsLibTrap_BeginDirEntryEnumerate)
	DC.W		libDispEntryEnum(vfsLibTrap_EndDirEntryEnumerate)
	DC.W		libDispEntryEnum(vfsLibTrap_DirEntryEnumerate)
	DC.W		libDispEntryEnum(vfsLibTrap_SetAttributes)
	DC.W		libDispEntryEnum(vfsLibTrap_ResetAttributes)
	DC.W		libDispEntryEnum(vfsLibTrap_GetAttributes)
	DC.W		libDispEntryEnum(vfsLibTrap_Open)
// Import/export
	DC.W		libDispEntryEnum(vfsLibTrap_Import)
	DC.W		libDispEntryEnum(vfsLibTrap_Export)
	DC.W		libDispEntryEnum(vfsLibTrap_ImportDialog)
	DC.W		libDispEntryEnum(vfsLibTrap_ExportDialog)
// Default dir
	DC.W		libDispEntryEnum(vfsLibTrap_RegisterDefaultDirectory)
	DC.W		libDispEntryEnum(vfsLibTrap_UnregisterDefaultDirectory)
	DC.W		libDispEntryEnum(vfsLibTrap_GetDefaultDirectory)	
// get resourse	
	DC.W		libDispEntryEnum(vfsLibTrap_GetResource)		
	DC.W		libDispEntryEnum(vfsLibTrap_ReadHuge)
	DC.W		libDispEntryEnum(vfsLibTrap_WriteHuge)			
// version 2		
	DC.W		libDispEntryEnum(vfsLibTrap_GetDeviceUniqueIDStr)
	
// Standard library function handlers
@GotoOpen:	JMP 		VFSLibOpen
@GotoClose:	JMP 		VFSLibClose
@GotoSleep:	JMP 		VFSLibSleep
@GotoWake:	JMP 		VFSLibWake
	
// Customer library function handlers
	 
	JMP 		VFSLibGetLibAPIVersion
	JMP		 VFSLibGetLastError
	JMP		 VFSLibInit
// Volume
	JMP		 VFSLib_BeginVolumeEnumerate
	JMP		 VFSLib_GetNextVolume
	JMP		 VFSLib_SetVolume
	JMP		 VFSLib_GetVolumeLabel
	JMP		 VFSLib_SetVolumeLabel
	JMP		 VFSLib_IsVolumeReadOnly
	JMP		 VFSLib_IsVolumeHidden
	JMP		 VFSLib_VolumeUsedSize
	JMP		 VFSLib_VolumeTotalSize
	JMP		 VFSLib_VolumeFormat
	JMP		 VFSLib_GetVolumeMediaType
// Dir
	JMP		 VFSLib_DirCreate
// File
	JMP		 VFSLib_IsEOF
	JMP		 VFSLib_FileCreate
	JMP		 VFSLib_Read16
	JMP		 VFSLib_Read32
	JMP		 VFSLib_Read64
	JMP		 VFSLib_ReadString
	JMP		 VFSLib_Write16
	JMP		 VFSLib_Write32
	JMP		 VFSLib_Write64
	JMP		 VFSLib_WriteString
	JMP		 VFSLib_FileTell
	JMP		 VFSLib_FileSize
	JMP		 VFSLib_FileResize
	JMP		 VFSLib_FileSeekBegin
	JMP		 VFSLib_FileSeekCurrent
	JMP		 VFSLib_FileSeekEnd
// File & dir
	JMP		 VFSLib_Delete
	JMP		 VFSLib_Close
	JMP		 VFSLib_Rename
	JMP		 VFSLib_SetDateCreated
	JMP		 VFSLib_SetDateModified
	JMP		 VFSLib_SetDateAccessed
	JMP		 VFSLib_GetDateCreated
	JMP		 VFSLib_GetDateModified
	JMP		 VFSLib_GetDateAccessed
	JMP		 VFSLib_BeginDirEntryEnumerate
	JMP		 VFSLib_EndDirEntryEnumerate
	JMP		 VFSLib_DirEntryEnumerate
	JMP		 VFSLib_SetAttributes
	JMP		 VFSLib_ResetAttributes
	JMP		 VFSLib_GetAttributes
	JMP		 VFSLib_Open
// Import/export
	JMP		 VFSLib_Import
	JMP		 VFSLib_Export
	JMP		 VFSLib_ImportDialog
	JMP		 VFSLib_ExportDialog
// Default dir
	JMP		 VFSLib_RegisterDefaultDirectory
	JMP		 VFSLib_UnregisterDefaultDirectory
	JMP		 VFSLib_GetDefaultDirectory
//Get resourse
	JMP		 VFSLib_GetResource
	JMP		 VFSLib_ReadHuge
	JMP		 VFSLib_WriteHuge				
// version 2
	JMP		 VFSLib_GetDeviceUniqueIDStr
@Name:	DC.B		VFSLibName
}
