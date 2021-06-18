#if !defined(AFX_GUIDIALOG_H__C78C1BB1_EBEE_11D3_94DB_0090271BF6FA__INCLUDED_)
#define AFX_GUIDIALOG_H__C78C1BB1_EBEE_11D3_94DB_0090271BF6FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// guiDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// guiDialog dialog

class guiDialog : public CDialog
{
// Construction
public:
	guiDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(guiDialog)
	enum { IDD = IDD_DIALOG1 };
	CString	m_scanline;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(guiDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(guiDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIDIALOG_H__C78C1BB1_EBEE_11D3_94DB_0090271BF6FA__INCLUDED_)
