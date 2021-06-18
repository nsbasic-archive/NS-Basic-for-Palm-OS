#if !defined(AFX_EMULINKPPG_H__EFC9CC77_188E_11D5_9892_0000CB222337__INCLUDED_)
#define AFX_EMULINKPPG_H__EFC9CC77_188E_11D5_9892_0000CB222337__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// EmuLinkPpg.h : Declaration of the CEmuLinkPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CEmuLinkPropPage : See EmuLinkPpg.cpp.cpp for implementation.

class CEmuLinkPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CEmuLinkPropPage)
	DECLARE_OLECREATE_EX(CEmuLinkPropPage)

// Constructor
public:
	CEmuLinkPropPage();

// Dialog Data
	//{{AFX_DATA(CEmuLinkPropPage)
	enum { IDD = IDD_PROPPAGE_EMULINK };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CEmuLinkPropPage)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMULINKPPG_H__EFC9CC77_188E_11D5_9892_0000CB222337__INCLUDED)
