// colr.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#include "MainFrm.h"
#include "colrDoc.h"
#include "colrView.h"

#include "colr.h"
#include "string.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColrApp

BEGIN_MESSAGE_MAP(CColrApp, CWinApp)
	//{{AFX_MSG_MAP(CColrApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
//	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen) //OVERIDE - SO I CAN PASS IN MY OWN FILE DIALOG/FILTER
	ON_COMMAND(ID_FILE_OPEN, OnMyFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColrApp construction

CColrApp::CColrApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CColrApp object

CColrApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CColrApp initialization

BOOL CColrApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CColrDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CColrView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open



	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// Dispatch commands specified on the command line
//	if (!ProcessShellCommand(cmdInfo))	// this processes the file "open"
//		return FALSE;


	CMD_argc=__argc;
	CMD_targv=__targv[1];

	OpenDocumentFile("DUMMY")	;


//	m_pMainWnd->MoveWindow(0,0,?,?);

	return TRUE;  // for command line - I'm done here.


	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	int scanCommandLine();
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CColrApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CColrApp message handlers

void CColrApp::OnMyFileOpen(){

	TCHAR szFile[MAX_PATH];
	ZeroMemory(szFile, MAX_PATH);
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize	= sizeof(OPENFILENAME);
	ofn.Flags		= OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	ofn.hwndOwner	= m_pMainWnd->m_hWnd  ; //hWnd;
	ofn.lpstrFilter	= _T("Supported Files Types(*.bmp;*.gif;*.jpg;*.ico;*.emf;*.wmf)\0*.bmp;*.gif;*.jpg;*.ico;*.emf;*.wmf\0Bitmaps (*.bmp)\0*.bmp\0GIF Files (*.gif)\0*.gif\0JPEG Files (*.jpg)\0*.jpg\0Icons (*.ico)\0*.ico\0Enhanced Metafiles (*.emf)\0*.emf\0Windows Metafiles (*.wmf)\0*.wmf\0\0");
	ofn.lpstrTitle	= _T("Open Picture File");
	ofn.lpstrFile	= szFile;
	ofn.nMaxFile	= MAX_PATH;
	if (IDOK == GetOpenFileName(&ofn))
		OpenDocumentFile(szFile);

	
}

