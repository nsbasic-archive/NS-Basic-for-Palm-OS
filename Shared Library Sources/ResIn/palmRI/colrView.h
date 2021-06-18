// colrView.h : interface of the CColrView class
//
/////////////////////////////////////////////////////////////////////////////
#include "palmbitmap.h"
#if !defined(AFX_COLRVIEW_H__7625702C_99E2_11D3_BD06_00A024AC6022__INCLUDED_)
#define AFX_COLRVIEW_H__7625702C_99E2_11D3_BD06_00A024AC6022__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define NUMBER_OF_PATTERNS (105)
//#define MAX_NUMBER_OF_PATTERNS (NUMBER_OF_PATTERNS+NUMBER_OF_PATTERNS*5)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef unsigned char 	Byte;
typedef unsigned short 	Word;			
typedef unsigned long	DWord;		
typedef DWord           LocalID;		// local (card relative) chunk ID

#pragma pack(2)

typedef struct {
	LocalID		localChunkID;				// local chunkID of a record
	Byte			attributes;			// record attributes;
	Byte			uniqueID[3];			// unique ID of record; should
								//	not be 0 for a legal record.
	} RecordEntryType;
typedef RecordEntryType*	RecordEntryPtr;

typedef struct {
	DWord			type;				// resource type
	Word			id;				// resource id
	LocalID		localChunkID;				// resource data chunk ID
	} RsrcEntryType;
typedef RsrcEntryType*	RsrcEntryPtr;

typedef struct {
	LocalID				nextRecordListID;	// local chunkID of next list
	Word					numRecords;	// number of records in this list
	Word					firstEntry;	// array of Record/Rsrc entries 
								// starts here
	} RecordListType;
typedef RecordListType*	RecordListPtr;



#define	dmDBNameLength				32		// 31 chars + 1 null terminator
#define	dmHdrAttrResDB					0x0001	// Resource database

typedef struct {
	Byte			name[dmDBNameLength];		// name of database
	Word			attributes;			// database attributes
	Word			version;			// version of database

	DWord			creationDate;			// creation date of database
	DWord			modificationDate;		// latest modification date
	DWord			lastBackupDate;			// latest backup date
	DWord			modificationNumber;		// modification number of database

	LocalID		appInfoID;				// application specific info
	LocalID		sortInfoID;				// app specific sorting info

	DWord			type;				// database type
	DWord			creator;			// database creator 
	
	DWord			uniqueIDSeed;			// used to generate unique IDs.
								//	Note that only the low order
								//	3 bytes of this is used (in
								//	RecordEntryType.uniqueID).
								//	We are keeping 4 bytes for 
								//	alignment purposes.

	RecordListType	recordList;				// first record list
	} DatabaseHdrType;		

typedef DatabaseHdrType*	DatabaseHdrPtr;
typedef DatabaseHdrPtr*		DatabaseHdrHand;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



class CColrView : public CView
{
protected: // create from serialization only
	CColrView();
	DECLARE_DYNCREATE(CColrView)

// Attributes
public:
	CColrDoc* GetDocument();
	void addResourceToPalm(int picCount,int totalSize[20],BitmapPtrV2 palmBitmap[20],LPCTSTR oFileName,int refID,LPCTSTR resType);
	void write68kDWord(DWord *to, DWord value);
	void write68kWord(Word *to, Word value);
	int read68kWord(Word *from);
	int read68kDWord(DWord *from);
	void addResourceToPalm();
	void createWebPalette();
	void createGrayPalette();
    void create4ShadePalette();
    void createBWPalette();
	void createWebPalmCT();
	void createGrayPalmCT();
	void create4ShadePalmCT();
	void createBWPalmCT();
	void createPCPalette(CDC* pDC,int dp);
	void createPalmCT(int dp);



// Operations
public:

	LOGPALETTE*		m_plp;
	CPalette		m_palette;

	int maxWidth,maxHeight;
	int picWidth[numLayer];
	int picHeight[numLayer];
	long pichmWidth[numLayer];
	long pichmHeight[numLayer];
	unsigned long table[256+256]; //second 256 are for add on to the basic 256 colors
	static unsigned char prcData[80];

	boolean First_Time_in_Draw;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColrView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:


	virtual ~CColrView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CColrView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in colrView.cpp
inline CColrDoc* CColrView::GetDocument()
   { return (CColrDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLRVIEW_H__7625702C_99E2_11D3_BD06_00A024AC6022__INCLUDED_)
