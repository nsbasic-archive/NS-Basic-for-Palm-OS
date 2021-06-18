// EmuLink.cpp : Implementation of CEmuLinkApp and DLL registration.

#include "stdafx.h"
#include "EmuLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CEmuLinkApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xefc9cc66, 0x188e, 0x11d5, { 0x98, 0x92, 0, 0, 0xcb, 0x22, 0x23, 0x37 } };
const WORD _wVerMajor = 2;
const WORD _wVerMinor = 0;


////////////////////////////////////////////////////////////////////////////
// CEmuLinkApp::InitInstance - DLL initialization

BOOL CEmuLinkApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CEmuLinkApp::ExitInstance - DLL termination

int CEmuLinkApp::ExitInstance()
{
	return COleControlModule::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
