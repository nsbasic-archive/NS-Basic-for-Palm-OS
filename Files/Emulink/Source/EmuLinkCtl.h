#if !defined(AFX_EMULINKCTL_H__EFC9CC75_188E_11D5_9892_0000CB222337__INCLUDED_)
#define AFX_EMULINKCTL_H__EFC9CC75_188E_11D5_9892_0000CB222337__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// EmuLinkCtl.h : Declaration of the CEmuLinkCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CEmuLinkCtrl : See EmuLinkCtl.cpp for implementation.

class CEmuLinkCtrl : public COleControl
{
	DECLARE_DYNCREATE(CEmuLinkCtrl)

// Constructor
public:
	CEmuLinkCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmuLinkCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	protected:
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CEmuLinkCtrl();

	DECLARE_OLECREATE_EX(CEmuLinkCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CEmuLinkCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CEmuLinkCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CEmuLinkCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CEmuLinkCtrl)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CEmuLinkCtrl)
	afx_msg BOOL ImportFile(LPCTSTR FIleName);
	afx_msg BOOL ExportFile(LPCTSTR FileName, LPCTSTR DBName);
	afx_msg BOOL AppStop();
	afx_msg BOOL NormalUIAppSwitch(LPCTSTR DBName);
	afx_msg BOOL CheckCurApp(LPCTSTR NameDB);
	afx_msg BOOL SysSoftReset();
	afx_msg BOOL CheckPresence();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CEmuLinkCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CEmuLinkCtrl)
	dispidImportFile = 1L,
	dispidExportFile = 2L,
	dispidAppStop = 3L,
	dispidNormalUIAppSwitch = 4L,
	dispidCheckCurApp = 5L,
	dispidSysSoftReset = 6L,
	dispidCheckPresence = 7L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMULINKCTL_H__EFC9CC75_188E_11D5_9892_0000CB222337__INCLUDED)
