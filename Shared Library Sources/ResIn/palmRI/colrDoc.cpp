// colrDoc.cpp : implementation of the CColrDoc class
//

#include "stdafx.h"
#include "colr.h"
#include <afxctl.h>

#include "colrDoc.h"
#include "guiDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// error indicators for scan of cmd line
#define NOT_AN_ERROR 0
#define DUP_OUTPUTFILE 1
#define MULTIPLE_RESIDS 2
#define RESID_TOO_LARGE 3
#define DUP_RESTYPES 4
#define INVALID_BIT_DEPTH 5
#define INVALID_ENTRY 6
#define NO_INPUTFILE 7
#define NO_OUTPUTFILE 8
#define NO_RESTYPE 9
#define NO_RESID 10
#define DUP_BIT_DEPTH 11
#define NO_PARAMETERS 12
#define UNMATCHED_QUOTES 13

/////////////////////////////////////////////////////////////////////////////
// CColrDoc

IMPLEMENT_DYNCREATE(CColrDoc, CDocument)

BEGIN_MESSAGE_MAP(CColrDoc, CDocument)
	//{{AFX_MSG_MAP(CColrDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColrDoc construction/destruction


CColrDoc::CColrDoc()
{
	for(int i=0;i<numLayer;i++) gpPicture[i]=NULL;
}

CColrDoc::~CColrDoc()
{
	for(int i=0;i<numLayer;i++) if (gpPicture[i]) 	gpPicture[i]->Release();
}

BOOL CColrDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CColrDoc serialization

void CColrDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CColrDoc diagnostics

#ifdef _DEBUG
void CColrDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CColrDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CColrDoc commands
// NOTE: file types supported "Supported Files Types(*.bmp;*.gif;*.jpg;*.ico;*.emf;*.wmf)\0*.bmp;*.gif;*.jpg;*.ico;*.emf;*.wmf\0Bitmaps (*.bmp)\0*.bmp\0GIF Files (*.gif)\0*.gif\0JPEG Files (*.jpg)\0*.jpg\0Icons (*.ico)\0*.ico\0Enhanced Metafiles (*.emf)\0*.emf\0Windows Metafiles (*.wmf)\0*.wmf\0\0"

BOOL CColrDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	picCount=0;
	ofilename=NULL;
	resType=NULL;
	resID=-1;
	char * errptr=NULL;

	for(int i=0;i<numLayer;i++) deep[i]=false;

	int error=scanCommandLine(&errptr);

	if(error)
		{
		// here we give a message that the string was in error
		CString errmsg="ERROR- ";
		switch (error)
		{
		case DUP_OUTPUTFILE:	errmsg+="more than one output file specified: ";break;
		case MULTIPLE_RESIDS:	errmsg+="more than one resource ID specified: ";break;
		case RESID_TOO_LARGE:	errmsg+="resource ID value too large: ";		break;
		case DUP_RESTYPES:		errmsg+="Multiple resource types specified: ";	break;
		case INVALID_BIT_DEPTH:	errmsg+="Invalid bit depth: ";					break;
		case INVALID_ENTRY:		errmsg+="Unidentifiable parameter: ";			break;
		case NO_INPUTFILE:		errmsg+="No input file specified ";				break;
		case NO_OUTPUTFILE:		errmsg+="No output file specified ";			break;
		case NO_RESTYPE:		errmsg+="No resource type specified ";			break;
		case NO_RESID:			errmsg+="No resource ID specified ";			break;
		case DUP_BIT_DEPTH:		errmsg+="Two Bitmaps of same depth specified";	break;
		case NO_PARAMETERS:		errmsg+="No (or undecipherable) parameters";	break;
		case UNMATCHED_QUOTES:	errmsg+="Unmatched quotes";						break;
		}
		AfxMessageBox(errmsg + errptr);

		return false;//exit(0);
		}

	int dpIdx=1;
	for(i=0;i<picCount;i++)
		{
		while(!deep[dpIdx]) dpIdx++;
		int dp=dpIdx;dpIdx++;
		// open file
		HANDLE hFile = CreateFile(filename[dp], GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL); //filename[1,2,4 or 8]
		//_ASSERTE(INVALID_HANDLE_VALUE != hFile);
		if(INVALID_HANDLE_VALUE == hFile)
			{
			AfxMessageBox("ERROR- cannot find file name specified ");
			return false;//exit(0);
			};



		// get file size
		DWORD dwFileSize = GetFileSize(hFile, NULL);
		_ASSERTE(-1 != dwFileSize);

		LPVOID pvData = NULL;
		// alloc memory based on file size
		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwFileSize);
		_ASSERTE(NULL != hGlobal);

		pvData = GlobalLock(hGlobal);
		_ASSERTE(NULL != pvData);

		DWORD dwBytesRead = 0;
		// read file and store in global memory
		BOOL bRead = ReadFile(hFile, pvData, dwFileSize, &dwBytesRead, NULL);
		_ASSERTE(FALSE != bRead);
		GlobalUnlock(hGlobal);
		CloseHandle(hFile);

		LPSTREAM pstm = NULL;
		// create IStream* from global memory
		HRESULT hr = CreateStreamOnHGlobal(hGlobal, TRUE, &pstm);
		_ASSERTE(SUCCEEDED(hr) && pstm);

		// Create IPicture from image file
		if (gpPicture[dp])
			gpPicture[dp]->Release();
		hr = ::OleLoadPicture(pstm, dwFileSize, FALSE, IID_IPicture, (LPVOID *)&gpPicture[dp]);
		_ASSERTE(SUCCEEDED(hr) && gpPicture[dp]);	
		pstm->Release();
		}


	UpdateAllViews(NULL);
return TRUE;
}

//test16bit.bmp:16 bitmap.prc Tbmp 1000 
//test16bit.bmp:16 1000 Tbmp bitmap.prc 

int CColrDoc::scanCommandLine(char ** errptr)
{
	// here, we will go through all args.  Each .bmp found will cause a picture to be generated
	// and it's depth set based on finding :1 :2 :4 :8 at the end of it's string.
	// if it ends with .pdb or .prc we save that off as the output file (can have only one)
	// we will also store of any number found as the id (<=32767), and any 4 letter item will
	// be the type created. (must have 1 of each)

	CColrApp * app = (CColrApp *) AfxGetApp( );
	LPCTSTR targv=app->CMD_targv;
	int argc=app->CMD_argc;


	char * token;
	if(argc==1) // no command line args
		{
		// handle a dialog prompt here.
		
		guiDialog dlg;
		if (dlg.DoModal() == IDOK)
			{
			 lstrcpy(scanLine, dlg.m_scanline);
			 token=scanLine;argc++;
			  // now, make scanLine look like the args passed on a command line:
			 while(*token)
				 {
				  if('\"'==*token)
				  {
					*token='\0'; argc++;
					do token++; while ((*token!='\"') && (*token!='\0'));
					if(*token=='\0') {return UNMATCHED_QUOTES;}
					*token='\0'; argc++;
					token++;
					continue;
				  }
				  if('\''==*token)
				  {
					*token='\0'; argc++;
					do token++; while ((*token!='\'') && (*token!='\0'));
					if(*token=='\0') {return UNMATCHED_QUOTES;}
					*token='\0'; argc++;
					token++;
					continue;
				  }
					


				 if(' '==*token) {*token='\0';argc++;}
				 token++;
				 
				}
			 token=scanLine;
			}
		else
			exit(0);

		}
	else
		token=(char *)targv;


	char * test,* test2, * test3;
	int error=NOT_AN_ERROR;


	for(int i=1;i<argc;i++)
		{
		test=token +(strlen(token)-2);

		test2=token +(strlen(token)-3);//NEW===add check for depth 16
		if(*test!=':')
			{
			if(*test2==':')
				test=token +(strlen(token)-3);
			else
			{
				test3 = token +(strlen(token)-4);//VU
				if(*test3==':')	test=token +(strlen(token)-4);
			}

			}

		if(*test==':')
			{
			bool doubleDensity = false;
			int d=(*(test+1))-'0';
			if( (d==1) || (d==2) || (d==4) || (d==8) )
				{

				int d2=(*(test+2))-'0';//NEW===add check for depth 16
				if(d2==6)
				{
					d=16;
					int d3=(*(test+3));
					if (d3 == 'd') doubleDensity = true; //double density
				}
				// VU
				if (d2 == 'd'-'0') doubleDensity = true; //double density

				int nd = d; if (doubleDensity) nd+=halfNumLayer;
				if(deep[nd])
					{
					error=DUP_BIT_DEPTH;
					break;
					}
				deep[nd]=true; // set true if we get a valid depth
				*test='\0';
				filename[nd]=token;
				token=token+(strlen(token))+3; // ready for next token
				if(d==16) token++;
				if(doubleDensity) token++;
				picCount++;
				while(*token=='\0') {token++;argc--;}
				continue;
				}
			else
				{
				error=INVALID_BIT_DEPTH;
				break;
				}
			}
		test=token +(strlen(token)-4);
		if((strcmp(test,".prc")==0) || (strcmp(test,".pdb")==0))
			{
			if (ofilename==NULL)
				ofilename=token;
			else 
				{
				error=DUP_OUTPUTFILE;
				break;
				}
			token=token+(strlen(token))+1; // ready for next token
			while(*token=='\0') {token++;argc--;}
			continue;
			}
		// check for a number (all chars digits & final no. <32767)
		int i=0;
		while ( (*(token+i))!=0)
			{
			if ( ((*(token+i))<'0') || ((*(token+i))>'9') ) break;
			i++;
			}
		if( (*(token+i))==0 )
			{
			// here, make token a number & test against 32767
			int tempNum;
			sscanf(token,"%d",&tempNum);

			if((tempNum<32767) && (tempNum>0))
				{
				if(resID!=-1)
					{
					error=MULTIPLE_RESIDS;
					break;
					}
				resID=tempNum;
				token=token+(strlen(token))+1; // ready for next token
				while(*token=='\0') {token++;argc--;}
				continue;
				}
			else
			{
				error=RESID_TOO_LARGE;
				break;
				}
			}
	// check it's 4 chars and use it as type (? should we test for taib or tbmp) - also - allow only one)
		if(strlen(token)==4)
			{
			//set the type of item to tbnmp or taib
			if(resType==NULL)
				{
				resType=token;
				token=token+(strlen(token))+1; // ready for next token
				while(*token=='\0') {token++;argc--;}
				continue;
				}
			else
				{
				error=DUP_RESTYPES;
				break;
				}
			}
	//if we fell through to here, we got something in the arg list that is unrecognizable
	error=INVALID_ENTRY;
	break;
	}

// still other errors possible:  missing ID, type, input, or output filename
	if(!error)
		{
		if(picCount==0) error=NO_INPUTFILE;
		else if (ofilename==NULL) error=NO_OUTPUTFILE;
		else if (resType==NULL) error=NO_RESTYPE;
		else if (resID==-1) error=NO_RESID;
		*errptr=NULL;
		return error;
		}



*errptr=token;
return error;
}
