#if !defined(AFX_EMULINK_H__EFC9CC6E_188E_11D5_9892_0000CB222337__INCLUDED_)
#define AFX_EMULINK_H__EFC9CC6E_188E_11D5_9892_0000CB222337__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// EmuLink.h : main header file for EMULINK.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEmuLinkApp : See EmuLink.cpp for implementation.

class CEmuLinkApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMULINK_H__EFC9CC6E_188E_11D5_9892_0000CB222337__INCLUDED)
