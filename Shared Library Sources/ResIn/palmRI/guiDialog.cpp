// guiDialog.cpp : implementation file
//

#include "stdafx.h"
#include "colr.h"
#include "guiDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// guiDialog dialog


guiDialog::guiDialog(CWnd* pParent /*=NULL*/)
	: CDialog(guiDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(guiDialog)
	m_scanline = _T("");
	//}}AFX_DATA_INIT
}


void guiDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(guiDialog)
	DDX_Text(pDX, IDC_EDIT1, m_scanline);
	DDV_MaxChars(pDX, m_scanline, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(guiDialog, CDialog)
	//{{AFX_MSG_MAP(guiDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// guiDialog message handlers
