// EmuLinkPpg.cpp : Implementation of the CEmuLinkPropPage property page class.

#include "stdafx.h"
#include "EmuLink.h"
#include "EmuLinkPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CEmuLinkPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CEmuLinkPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CEmuLinkPropPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CEmuLinkPropPage, "EMULINK.EmuLinkPropPage.1",
	0xefc9cc6a, 0x188e, 0x11d5, 0x98, 0x92, 0, 0, 0xcb, 0x22, 0x23, 0x37)


/////////////////////////////////////////////////////////////////////////////
// CEmuLinkPropPage::CEmuLinkPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CEmuLinkPropPage

BOOL CEmuLinkPropPage::CEmuLinkPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_EMULINK_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CEmuLinkPropPage::CEmuLinkPropPage - Constructor

CEmuLinkPropPage::CEmuLinkPropPage() :
	COlePropertyPage(IDD, IDS_EMULINK_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CEmuLinkPropPage)
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CEmuLinkPropPage::DoDataExchange - Moves data between page and properties

void CEmuLinkPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CEmuLinkPropPage)
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CEmuLinkPropPage message handlers
