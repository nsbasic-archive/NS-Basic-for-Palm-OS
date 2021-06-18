/* -----------------------------------------------------------------------
   SampleViewer.h
   (c)2002 Regis Nicolas - All rights reserved.
   ----------------------------------------------------------------------- */

#ifndef SAMPLEVIEWER_H
#define SAMPLEVIEWER_H

#if _MSC_VER > 1000
	#pragma once
#endif

/* ----------------------------------------------------------------------- */
#include <windows.h>

#define VIEWERHELPER_API __declspec(dllimport)

/* ----------------------------------------------------------------------- */
#ifdef __cplusplus
	extern "C" {
#endif

/* ----------------------------------------------------------------------- */
typedef struct _TPRCItem		TPRCItem;
typedef struct _TResource		TResource;
typedef struct _TCtlSizeInfo	TCtlSizeInfo;
typedef struct _TSizeInfo		TSizeInfo;
typedef struct _TPRCViewer		TPRCViewer;

/* ----------------------------------------------------------------------- */
struct _TPRCItem
{
	int			type;
	void*		userInfo;
#ifndef PALMPRC_NO_VIEWERS
	TPRCViewer*	viewer;
#endif
	void*		db; // Reserved (TPRC*)
};

/* A single resource */
struct _TResource
{
	TPRCItem		item;
	TResource*		next;
	WORD			id;
	BYTE*			ptr;
	/* If this is not 0, this is called when freeing this struct to release ptr */
	void			(*releaseFunc)(void*);
	void*			resType; // Reserved (TResourceType*)
	DWORD			size;
};

/* ----------------------------------------------------------------------- */
#define SizeMove_Start	0
#define SizeMove_Size	1 /* Not implemented yet: do it in MainFrm.cpp */
#define SizeMove_Move	2 /* Not implemented yet: do it in MainFrm.cpp */
#define SizeMove_End	3

struct _TCtlSizeInfo
{
	HWND	hwnd;
	int		xi, yi, cxi, cyi;
	int		tx, ty, cx, cy;
};

struct _TSizeInfo
{
	HINSTANCE		hInst;
	int				cxi, cyi, cxm, cym;
	int				sizeInfoCount, sizeInfoSize;
	TCtlSizeInfo**	sizeInfo;
};

#define SourceType_Begin	-2
#define SourceType_End		-1

#define SourceType_RCP		0

struct _TPRCViewer
{
	char*		description;
	char*		developer;
	void*		staticData;
	void*		instanceData;
	HWND		hwnd;
	TSizeInfo*	sizeInfo;

	/* void* item is a TPRC* for PRC viewers, TResourceType* for ResourceType viewers or TResource* for Resource viewers */
	/* parentView is always a CFormView */
	int			(*createView)(void* item, HWND parentView);
	void		(*destroyView)(void* item);
	/* returned SIZE is valid when type is SizeMove_End */
	SIZE		(*sizeMoveView)(void* item, int type);
	/* 
	saveSource must return 0 if this feature is not supported. In that case the resource will be dumped in binary format.
	Otherwise it must return a text block allocated with malloc and which will be release with free. 
	  This text will be appended to the source file.
	path points to the folder in which to create additional attachments like bitmaps. 
	  path is set to 0 when for example "view source" is command is executed (which should not actually create the attachment).
	type describes which type of source should be generated (RCP, XRD, ...). Return 0 if not supported...
	*/
	char*		(*saveSource)(void* item, int sourceType, char* path);
	void		(*selectOffset)(void* item, size_t offset, size_t size);
};

/* 
hInst is the hInstance of the DLL containing the resources and dlgID is the id of the 
RT_SIZABLE resource containing cxm=100,cym=100. This should be the dlg id. Use 0 to set min size to init size. */
VIEWERHELPER_API	void	TPRCViewer_InitSizeInfo(TPRCViewer* viewer, HINSTANCE hInst, int dlgID);
VIEWERHELPER_API	SIZE	TPRCViewer_ManageSize(TPRCViewer* viewer);
VIEWERHELPER_API	void	TPRCViewer_DeleteSizeInfo(TPRCViewer* viewer);

/* ----------------------------------------------------------------------- */
VIEWERHELPER_API	char*	Viewer_DumpData(BYTE* ptr, DWORD size, DWORD nChars, DWORD* bytesLine);
VIEWERHELPER_API	void	Viewer_ReleaseDumpData(char* data);

/*
	This function is designed to be called in sequence. The first time, *text must be 0, *len and *size must be 0.
	*text will be grown appropriately and freed if it cannot be grown.
	*len points to the 'strlen' of *text
	*size is the currently allocated size for *text.

	When called, addText is the text to add and addLen the number of bytes. 
	If addLen is 0, strlen(addText) is used.

	Returns 0 if a problem occurs (*text is freed then ) or non-0 if OK.

	When there is not enough memory allocated for *text, the buffer is grown by VIEWER_SAVESOURCE_BUFFERINCR
*/
#define VIEWER_SAVESOURCE_BUFFERINCR	1024

/* EOLType is linked to path parameter of saveSource function */
#define EOLType_File		0
#define EOLType_Edit		1

VIEWERHELPER_API	int		Viewer_SaveSource_AddText(char** text, size_t* len, size_t* size, char* addText, size_t addLen);
VIEWERHELPER_API	int		Viewer_SaveSource_AddEOL(char** text, size_t* len, size_t* size, int eolType);
VIEWERHELPER_API	int		Viewer_SaveSource_DumpData(char** text, size_t* len, size_t* size, BYTE* data, DWORD dataSize, int fBinaryOnly, int eolType);
VIEWERHELPER_API	int		Viewer_SaveSource_DumpString(char** text, size_t* len, size_t* size, char* str, DWORD strLen, int eolType);
VIEWERHELPER_API	void	Viewer_SaveSource_ReleaseDumpData(char* data);

/* ----------------------------------------------------------------------- */
#define VIEWERS_VERSION	0x0200

/* Version is the version number contained in this file with which the Viewer has been built */
VIEWERHELPER_API TPRCViewer* (*TDLLViewerNew)(WORD* version);

/* ----------------------------------------------------------------------- */
#ifdef __cplusplus
	}
#endif

/* ----------------------------------------------------------------------- */
#endif // SAMPLEVIEWER_H