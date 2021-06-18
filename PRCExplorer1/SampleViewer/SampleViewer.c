/* -----------------------------------------------------------------------
   SampleViewer.c
   (c)2002 Regis Nicolas - All rights reserved.
   ----------------------------------------------------------------------- */

#include "SampleViewer.h"
#include "SampleViewerRes.h"

#include <stdio.h>

/* ----------------------------------------------------------------------- */
#pragma comment (lib, "ViewerHelper.lib")
#define MODULE_HANDLE	GetModuleHandle("SampleViewer.dll")

/* ----------------------------------------------------------------------- */
static INT_PTR CALLBACK tintDlgProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	return FALSE;
}

/* ----------------------------------------------------------------------- */
int Viewer_tint_createView(void* item, HWND parentView)
{
	TResource*		res = (TResource*)item;
	char			str[40], *text;
	int				i;
	HWND			hDlg;
	DWORD			value;

	hDlg = CreateDialog(MODULE_HANDLE, MAKEINTRESOURCE(IDD_VIEWER_TINT), parentView, tintDlgProc);

	value = (res->ptr[0] << 24) + (res->ptr[1] << 16) + (res->ptr[2] << 8) + res->ptr[3];
	
	sprintf(str, "%lu", value);
	SetDlgItemText(hDlg, IDC_VIEWER_TINT_DEC, str);
	sprintf(str, "%02X %02X %02X %02X", res->ptr[0], res->ptr[1], res->ptr[2], res->ptr[3]);
	SetDlgItemText(hDlg, IDC_VIEWER_TINT_HEXA, str);

	text = str;
	for (i = 0; i < 32; i++)
	{
		if (value & 0x80000000)
			*text++ = '1';
		else
			*text++ = '0';
		value <<= 1;

		if (((i + 1) & 0x07) == 0)
			*text++ = ' ';
	}
	*text = 0;
	SetDlgItemText(hDlg, IDC_VIEWER_TINT_BIN, str);
#define CHAR(x) (x<32?'.':x)
	sprintf(str, "'%c%c%c%c'", CHAR(res->ptr[0]), CHAR(res->ptr[1]), CHAR(res->ptr[2]), CHAR(res->ptr[3]));
	SetDlgItemText(hDlg, IDC_VIEWER_TINT_ASCII, str);

	text = Viewer_DumpData(res->ptr, res->size, 80, 0);
	SetDlgItemText(hDlg, IDC_VIEWER_TINT_DUMP, text);
	Viewer_ReleaseDumpData(text);

	res->item.viewer->hwnd = hDlg;

	TPRCViewer_InitSizeInfo(res->item.viewer, MODULE_HANDLE, 0/*IDD_VIEWER_TINT*/);
	TPRCViewer_ManageSize(res->item.viewer);

	return 1;
}

/* ----------------------------------------------------------------------- */
void Viewer_tint_destroyView(void* item)
{
	TResource*	res = (TResource*)item;

	DestroyWindow((HWND)res->item.viewer->hwnd);
	TPRCViewer_DeleteSizeInfo(res->item.viewer);
}

/* ----------------------------------------------------------------------- */
SIZE Viewer_tint_sizeMoveView(void* item, int type)
{
	SIZE size = { 0, 0 };

	if (type == SizeMove_End)
		size = TPRCViewer_ManageSize(((TResource*)item)->item.viewer);

	return size;
}

/* ----------------------------------------------------------------------- */
#define EOLTYPE	(path!=0?EOLType_File:EOLType_Edit)
char* Viewer_tint_saveSource(void* item, int sourceType, char* path)
{
	TResource*	res = (TResource*)item;
	char*		text = 0;
	size_t		size = 0, len = 0;
	char		str[64];
	DWORD		value;

	if (sourceType != SourceType_RCP)
		return 0;

	value = (res->ptr[0] << 24) + (res->ptr[1] << 16) + (res->ptr[2] << 8) + res->ptr[3];
	sprintf(str, "INTEGER ID %d VALUE %lu", res->id, value);
	if (!Viewer_SaveSource_AddText(&text, &len, &size, str, 0))
		return 0;

	if (!Viewer_SaveSource_AddEOL(&text, &len, &size, EOLTYPE))
		return 0;
	if (!Viewer_SaveSource_AddEOL(&text, &len, &size, EOLTYPE))
		return 0;

	return text;
}

/* ----------------------------------------------------------------------- */
TPRCViewer	Viewer_tint = { "32 bits value", "Regis Nicolas <Regis.Nicolas@PalmSource.com>", 0, 0, 0, 0, Viewer_tint_createView, Viewer_tint_destroyView, Viewer_tint_sizeMoveView, Viewer_tint_saveSource, 0 };

/* ----------------------------------------------------------------------- */
__declspec(dllexport) TPRCViewer* Viewer_tint_New(WORD* version)
{
	*version = VIEWERS_VERSION;

	return &Viewer_tint;
}
