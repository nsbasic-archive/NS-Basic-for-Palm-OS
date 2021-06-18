// colrDoc.h : interface of the CColrDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLRDOC_H__7625702A_99E2_11D3_BD06_00A024AC6022__INCLUDED_)
#define AFX_COLRDOC_H__7625702A_99E2_11D3_BD06_00A024AC6022__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"

class CColrDoc : public CDocument
{
protected: // create from serialization only
	CColrDoc();
	DECLARE_DYNCREATE(CColrDoc)

// Attributes
public:

	char * filename[numLayer];// (only use 1,2,4 and 8)
	LPPICTURE gpPicture[numLayer]; // only use 1,2,4 and 8)
	int  picCount;		// index into picture file names
	char deep[numLayer];		// bit depth of the picture (only use 1,2,4,8 and 16)
	char * ofilename;	// output filename
	char * resType;		// type of resource
	int  resID;			// resource ID
	TCHAR scanLine[255];

	//HWND ghWnd;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColrDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	int scanCommandLine(char ** errptr);
	virtual ~CColrDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CColrDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLRDOC_H__7625702A_99E2_11D3_BD06_00A024AC6022__INCLUDED_)
