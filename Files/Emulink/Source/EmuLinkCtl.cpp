// EmuLinkCtl.cpp : Implementation of the CEmuLinkCtrl ActiveX Control class.

#include "stdafx.h"
#include "EmuLink.h"
#include "EmuLinkCtl.h"
#include "EmuLinkPpg.h"

#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "BuildDefines.h"
#include "BuildDefaults.h"
#include "PalmTypes.h"
#include "PalmCompatibility.h" 
#include "CoreTraps.h"
#include "HostControl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	vchrLaunch					0x0108		// Ctl-E
#define commandKeyMask     0x0008

IMPLEMENT_DYNCREATE(CEmuLinkCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CEmuLinkCtrl, COleControl)
	//{{AFX_MSG_MAP(CEmuLinkCtrl)
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CEmuLinkCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CEmuLinkCtrl)
	DISP_FUNCTION(CEmuLinkCtrl, "ImportFile", ImportFile, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CEmuLinkCtrl, "ExportFile", ExportFile, VT_BOOL, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CEmuLinkCtrl, "AppStop", AppStop, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CEmuLinkCtrl, "NormalUIAppSwitch", NormalUIAppSwitch, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CEmuLinkCtrl, "CheckCurApp", CheckCurApp, VT_BOOL, VTS_BSTR)
	DISP_FUNCTION(CEmuLinkCtrl, "SysSoftReset", SysSoftReset, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CEmuLinkCtrl, "CheckPresence", CheckPresence, VT_BOOL, VTS_NONE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CEmuLinkCtrl, COleControl)
	//{{AFX_EVENT_MAP(CEmuLinkCtrl)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

BEGIN_PROPPAGEIDS(CEmuLinkCtrl, 1)
	PROPPAGEID(CEmuLinkPropPage::guid)
END_PROPPAGEIDS(CEmuLinkCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CEmuLinkCtrl, "EMULINK.EmuLinkCtrl.1",
	0xefc9cc69, 0x188e, 0x11d5, 0x98, 0x92, 0, 0, 0xcb, 0x22, 0x23, 0x37)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CEmuLinkCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DEmuLink =
		{ 0xefc9cc67, 0x188e, 0x11d5, { 0x98, 0x92, 0, 0, 0xcb, 0x22, 0x23, 0x37 } };
const IID BASED_CODE IID_DEmuLinkEvents =
		{ 0xefc9cc68, 0x188e, 0x11d5, { 0x98, 0x92, 0, 0, 0xcb, 0x22, 0x23, 0x37 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwEmuLinkOleMisc =
	OLEMISC_INVISIBLEATRUNTIME |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CEmuLinkCtrl, IDS_EMULINK, _dwEmuLinkOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CEmuLinkCtrl::CEmuLinkCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CEmuLinkCtrl

BOOL CEmuLinkCtrl::CEmuLinkCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_EMULINK,
			IDB_EMULINK,
			afxRegApartmentThreading,
			_dwEmuLinkOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CEmuLinkCtrl::CEmuLinkCtrl - Constructor

CEmuLinkCtrl::CEmuLinkCtrl()
{
	InitializeIIDs(&IID_DEmuLink, &IID_DEmuLinkEvents);
}


/////////////////////////////////////////////////////////////////////////////
// CEmuLinkCtrl::~CEmuLinkCtrl - Destructor

CEmuLinkCtrl::~CEmuLinkCtrl()
{
}


/////////////////////////////////////////////////////////////////////////////
// CEmuLinkCtrl::OnDraw - Drawing function

void CEmuLinkCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	int prevMode = pdc->SetMapMode(MM_TEXT);
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	pdc->DrawIcon(rcBounds.left,rcBounds.top , m_hIcon);
	pdc->SetMapMode(prevMode);
}


/////////////////////////////////////////////////////////////////////////////
// CEmuLinkCtrl::DoPropExchange - Persistence support

void CEmuLinkCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

}


/////////////////////////////////////////////////////////////////////////////
// CEmuLinkCtrl::OnResetState - Reset control to default state

void CEmuLinkCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
}


/////////////////////////////////////////////////////////////////////////////
// CEmuLinkCtrl message handlers

BOOL Connect(SOCKET  &conn_socket)
{ 
	char *server_name= "localhost";
	unsigned short port = 6415; //DEFAULT_PORT;
	int socket_type = SOCK_STREAM;//DEFAULT_PROTO;
	struct sockaddr_in server;
	struct hostent *hp;
	WSADATA wsaData;
	// SOCKET  conn_socket;

	if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR) 
	{
		WSACleanup();
		return false;
	}

	hp = gethostbyname(server_name);

	if (hp == NULL ) 
	{
		WSACleanup();
		return false;// exit(1);
	}

	memset(&server,0,sizeof(server));
	memcpy(&(server.sin_addr),hp->h_addr,hp->h_length);
	server.sin_family = hp->h_addrtype;
	server.sin_port = htons(port);

	conn_socket = socket(AF_INET,socket_type,0); /* Open a socket */
	if (conn_socket<0 ) 
	{
		WSACleanup();
		return false;
	}

	// printf("Client connecting to: %s\n",hp->h_name);
	if (connect(conn_socket,(struct sockaddr*)&server,sizeof(server)) == SOCKET_ERROR) 
	{
		WSACleanup();
		return false;
	}
	return true;
}

void Close(SOCKET  &conn_socket)
{
 closesocket(conn_socket);
 WSACleanup();
}



////////////////////////////////////////////////////////
// RPC types
#define sysPktRPCCmd    0x0A
#define sysPktRPCRsp    0x8A
//System packets
#define slkPktTypeSystem		0	

#define slkSocketPoserRPC		14




typedef struct SysPktRPCParamInfo0
{
    Byte   byRef;    // true if param is by reference
    Byte   size;     // # of Bytes of paramData (must be even)
    Word   data;     // variable length array of paramData
} SysPktRPCParamType0;

typedef struct SysPktRPCParamInfoB
{
    Byte   byRef;    // true if param is by reference
    Byte   size;     // # of Bytes of paramData (must be even)
    Byte   data;     // variable length array of paramData
} SysPktRPCParamTypeB;


typedef struct SysPktRPCParamInfo
{
    Byte   byRef;    // true if param is by reference
    Byte   size;     // # of Bytes of paramData (must be even)
    //Word   data[2];  // variable length array of paramData
	Byte   data1;
	Byte   data2;
	Byte   data3;
	Byte   data4;
} SysPktRPCParamType;

typedef struct SysPktRPCParamInfo10
{
    Byte   byRef;    // true if param is by reference
    Byte   size;     // # of Bytes of paramData (must be even)
//    char   data[256];  // variable length array of paramData
} SysPktRPCParamType10;
 
typedef struct SysPktRPCType
{
	UInt8	command;
	UInt8	_filler;
	Word	trapWord;     // which trap to execute
	DWord	resultD0;     // result from D0 placed here
	DWord	resultA0;     // result from A0 placed here
	Word	numParams;    // how many parameters follow
	// Following is a variable length array of SysPktRPCParamType's
} SysPktRPCType;

typedef	UInt8	SlkPktHeaderChecksum;
struct SlkPktHeaderType
{
	Word	signature1;		// X  first 2 bytes of signature
	Byte	signature2;		// X  3 and final byte of signature
	Byte	dest;			// -> destination socket Id
	Byte	src;			// -> src socket Id
	Byte	type;			// -> packet type
	Byte	bodySize1;		// X  size of body
	Byte	bodySize2;		// X  size of body
	Byte	transID;		// -> transaction Id
							//    if 0 specified, it will be replaced 
	SlkPktHeaderChecksum	checksum;	// X  check sum of header
};

struct SlkPktFooterType
{
	Word	crc16;			// header and body crc
};

	

////////////////////////////////////////////////////////
void SwapWord(Word* data)
{
	char swap; 

	swap=*((char*)(data));
	*(char*)(data)=*(((char*)(data))+1);
	*(((char*)(data))+1)=swap;
}

SlkPktHeaderChecksum CalcHdrChecksum (SlkPktHeaderChecksum start,UInt8* bufP, Int32 count)
{
	do {
		start += *bufP++;
	} while (--count);

	return start;
}

Word CalcFtrChecksum( UInt8 *bufP, Int32 count )
{
	Word a, b, crc;
	Int32 n;
	Word crctt[] = {	0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
							0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
							0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
							0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
							0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
							0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
							0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
							0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
							0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
							0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
							0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
							0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
							0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
							0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
							0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
							0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
							0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
							0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
							0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
							0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
							0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
							0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
							0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
							0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
							0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
							0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
							0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
							0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
							0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
							0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
							0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
							0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0};

	crc = 0;
	for( n = 0; n < count; n++ )
	{
		a = ( crc << 8 );
		b = crctt[( crc >> 8 ) ^ *(bufP + n)];
		crc = a ^ b;
	}
	SwapWord( &crc );
	return crc;
}

/*
int copyBYTE(Byte param,char * buffer)
{
	SysPktRPCParamType0    paramPKT;
	paramPKT.byRef=0;
	paramPKT.size=1;
	paramPKT.data = param;
	memmove(buffer,(char*)(&paramPKT),3);
	return 3;
}
*/
int copyZERO(char * buffer)
{
	SysPktRPCParamType0 paramPKT;

	paramPKT.byRef=0;
	paramPKT.size=0;
	memmove(buffer,(char*)(&paramPKT),2);
	return 2;
}

int copyWORD(Word param,char * buffer)
{
	SysPktRPCParamType0 paramPKT;

	paramPKT.byRef=0;
	paramPKT.size=2;
	paramPKT.data = param;
	SwapWord(&paramPKT.data);
	memmove(buffer,(char*)(&paramPKT),4);
	return 4;
}

int copyRWORD(Word param,char * buffer)
{
	SysPktRPCParamType0    paramPKT;

	paramPKT.byRef=1;
	paramPKT.size=2;
	paramPKT.data = param;
	SwapWord(&paramPKT.data);
	memmove(buffer,(char*)(&paramPKT),4);
	return 4;
}

int copyRDWORD(DWord param,char * buffer)
{
	SysPktRPCParamType    paramPKT;

	paramPKT.byRef=1;
	paramPKT.size=4;
	paramPKT.data1=*(((Byte*)(&param))+3);
	paramPKT.data2=*(((Byte*)(&param))+2);
	paramPKT.data3=*(((Byte*)(&param))+1);
	paramPKT.data4=*(((Byte*)(&param))+0);
	memmove(buffer,(char*)(&paramPKT),6);
	return 6;
}

int copyDWORD( DWord param,char * buffer)
{
	SysPktRPCParamType    paramPKT;

	paramPKT.byRef=0;
	paramPKT.size=4;
	paramPKT.data1=*(((Byte*)(&param))+3);
	paramPKT.data2=*(((Byte*)(&param))+2);
	paramPKT.data3=*(((Byte*)(&param))+1);
	paramPKT.data4=*(((Byte*)(&param))+0);
	memmove(buffer,(char*)(&paramPKT),6);
	return 6;
}

int copySTRING(const char* param,char*buffer)
{
	SysPktRPCParamType10    paramPKT;
	char zero[]="";

	paramPKT.byRef=1;
	paramPKT.size=strlen(param)+1;
	if (paramPKT.size%2==0)
	{
		memmove(buffer,(char*)(&paramPKT),2);
		memmove(buffer+2,param,paramPKT.size);
	}
	else
	{
		paramPKT.size++;
		memmove(buffer,(char*)(&paramPKT),2);
		memmove(buffer+2,param,paramPKT.size-1);
		memmove(buffer+paramPKT.size+1,zero,1);
	}

	return 2+paramPKT.size;
}

int copyBIN(void* param,int size, char*buffer)
{
	SysPktRPCParamType10    paramPKT;
	char zero[]="";

	paramPKT.byRef=1;
	if (size%2==1) paramPKT.size=size+1; else paramPKT.size=size; 

	memmove(buffer,(char*)(&paramPKT),2);
	memmove(buffer+2,param,size);
	if (size%2==1)
		memmove(buffer+size+2,zero,1);

	return 2+paramPKT.size;
}

int createBody(Word trapW,Word numParam,char* buffer)
{
	SysPktRPCType		RPCType;

	RPCType.command = sysPktRPCCmd;  // 0x0A
	RPCType._filler = 0;
	RPCType.trapWord=trapW;//sysTrapHostControl;//hostSelectorImportFile;
	RPCType.resultA0=0;
	RPCType.resultD0=0;
	RPCType.numParams=numParam;

	SwapWord(&RPCType.trapWord);
	SwapWord(&RPCType.numParams);
	memmove(buffer,(char*)&RPCType,sizeof(RPCType)-2);

	return sizeof(RPCType)-2;
}

int createHeader(Byte bodySize,char* buffer)
{
	SlkPktHeaderType  HeaderType;

	HeaderType.signature1=0xEFBE;
	HeaderType.signature2=0xED;
//	HeaderType.dest=slkSocketPoserRPC;																// Emulink
	HeaderType.dest=1;																					// Simulink
//	HeaderType.src=slkSocketPoserRPC;																// Emulink
	HeaderType.src=1;																						// Simulink
	HeaderType.type=slkPktTypeSystem;
	HeaderType.bodySize1=0;
	HeaderType.bodySize2=bodySize;
	HeaderType.transID=1;
	HeaderType.checksum=CalcHdrChecksum (0, (UInt8*)(&HeaderType), sizeof(HeaderType)-sizeof(HeaderType.checksum));
	memmove(buffer,(char*)&HeaderType,sizeof(HeaderType));

	return sizeof(HeaderType);
}

int createPacket(char* header,char *body,char *packet)
{
	SlkPktFooterType  FooterType;

	memmove(packet,header,10);
	memmove(packet+10,body,*(header+7));
//	FooterType.crc16=0;																					// Emulink
	FooterType.crc16 = CalcFtrChecksum( (UInt8*)packet, 10 + *(header + 7) );			// Simulink
	memmove(packet+10+*(header+7),(char*)&FooterType,2);

	return 10+*(header+7)+2;
}

////////////////////////////////////////////////////////

BOOL CEmuLinkCtrl::ImportFile(LPCTSTR FileName) 
{
	SOCKET  conn_socket;

	if (Connect(conn_socket)==false) return false;
	//
	// Import
	//HostErrType			HostImportFile(const char* fileName, long cardNum)

	char newBody[280],newHeader[12],newPacket[512];
	int LenB =createBody(sysTrapHostControl,3,newBody);
	int LenP3=copyDWORD(0,newBody+LenB);
	int LenP2=copySTRING(FileName,newBody+LenB+LenP3);
	int LenP1=copyWORD(hostSelectorImportFile,newBody+LenB+LenP3+LenP2);
	createHeader(LenB+LenP3+LenP2+LenP1,newHeader);
	int LenPack=createPacket(newHeader,newBody,newPacket);
	int retval = send(conn_socket,newPacket,LenPack,0);
	if (retval == SOCKET_ERROR) {WSACleanup();return false;}
	char header[10],body[512],foot[2];

	retval = recv(conn_socket,header,10,0 );
	retval = recv(conn_socket,body,header[7],0 );
	retval = recv(conn_socket,foot,2,0 );
	if (retval == SOCKET_ERROR) {closesocket(conn_socket);WSACleanup();return false;}

	Close(conn_socket);
	if ((body[4]|body[5]|body[6]|body[7])==0) return true; else return false;
	
	return TRUE;
}
////////////////////////////////////////////////////////

BOOL CEmuLinkCtrl::ExportFile(LPCTSTR FileName, LPCTSTR DBName) 
{
	SOCKET  conn_socket;
	if (Connect(conn_socket)==false) return false;

	// Export
	//HostErrType	HostExportFile(const char* fileName, long cardNum, const char* dbName)
	//#define hostSelectorExportFile				0x0501

	char newBody[280],newHeader[12],newPacket[512];
	int LenB =createBody(sysTrapHostControl,4,newBody);
	int LenP4=copySTRING(DBName,newBody+LenB);
	int LenP3=copyDWORD(0,newBody+LenB+LenP4);
	int LenP2=copySTRING(FileName,newBody+LenB+LenP3+LenP4);
	int LenP1=copyWORD(hostSelectorExportFile,newBody+LenB+LenP2+LenP3+LenP4);
	createHeader(LenB+LenP4+LenP3+LenP2+LenP1,newHeader);
	int LenPack=createPacket(newHeader,newBody,newPacket);
	int retval = send(conn_socket,newPacket,LenPack,0);
	if (retval == SOCKET_ERROR) {WSACleanup();return false;}
	char header[10],body[512],foot[2];

	retval = recv(conn_socket,header,10,0 );
	retval = recv(conn_socket,body,header[7],0 );
	retval = recv(conn_socket,foot,2,0 );
	if (retval == SOCKET_ERROR) {closesocket(conn_socket);WSACleanup();return false;}

	Close(conn_socket);
	if ((body[4]|body[5]|body[6]|body[7])==0) return true; else return false;

	return TRUE;
}
////////////////////////////////////////////////////////

BOOL CEmuLinkCtrl::CheckCurApp(LPCTSTR NameDB) 
{
	SOCKET  conn_socket;
	if (Connect(conn_socket)==false) return false;

	char newBody[280],newHeader[12],newPacket[512];
	//LocalID DmFindDatabase (UInt16 cardNo,const Char* nameP)
	UInt32 *p32=NULL;

	int LenB =createBody(sysTrapDmFindDatabase,2,newBody);
	int LenP2=copySTRING(NameDB,newBody+LenB);
	int LenP1=copyWORD(0,newBody+LenB+LenP2);
	createHeader(LenB+LenP1+LenP2,newHeader);
	int LenPack=createPacket(newHeader,newBody,newPacket);
	int retval = send(conn_socket,newPacket,LenPack,0);
	if (retval == SOCKET_ERROR) {WSACleanup();	return false;}
	char header[10],body[512],foot[2];

	retval = recv(conn_socket,header,10,0 );
	retval = recv(conn_socket,body,header[7],0 );
	retval = recv(conn_socket,foot,2,0 );

	DWord LID,LIDCheck;
	*(((Byte*)(&LID))+3)=body[4];
	*(((Byte*)(&LID))+2)=body[5];
	*(((Byte*)(&LID))+1)=body[6];
	*(((Byte*)(&LID))+0)=body[7];
	if (LID==0) {Close(conn_socket);return false;}

	//Err SysCurAppDatabase (UInt16* cardNoP,LocalID* dbIDP)
	LenB = createBody(sysTrapSysCurAppDatabase,2,newBody);
	LenP2=copyRDWORD(0,newBody+LenB);
	LenP1=copyRWORD(0,newBody+LenB+LenP2);

	createHeader(LenB+LenP1+LenP2,newHeader);
	LenPack=createPacket(newHeader,newBody,newPacket);
	retval = send(conn_socket,newPacket,LenPack,0);
	if (retval == SOCKET_ERROR) {WSACleanup();return false;}

	retval = recv(conn_socket,header,10,0 );
	retval = recv(conn_socket,body,header[7],0 );
	retval = recv(conn_socket,foot,2,0 );
	if (retval == SOCKET_ERROR) {closesocket(conn_socket);WSACleanup();	return false;}
	*(((Byte*)(&LIDCheck))+3)=body[16];
	*(((Byte*)(&LIDCheck))+2)=body[17];
	*(((Byte*)(&LIDCheck))+1)=body[18];
	*(((Byte*)(&LIDCheck))+0)=body[19];

	Close(conn_socket);

	return  (LID==LIDCheck); 
}

BOOL CEmuLinkCtrl::AppStop() 
{
	SOCKET  conn_socket;
	if (Connect(conn_socket)==false) return false;

	char newBody[280],newHeader[12],newPacket[512];
 
	// AppStop
	// Err EvtEnqueueKey (WChar ascii, UInt16 keycode, UInt16 modifiers)
	int LenB =createBody(sysTrapEvtEnqueueKey,3,newBody);
	int LenP3=copyWORD(commandKeyMask,newBody+LenB);
	int LenP2=copyWORD(0,newBody+LenB+LenP3);
	int LenP1=copyWORD(vchrLaunch,newBody+LenB+LenP2+LenP3);
	createHeader(LenB+LenP1+LenP2+LenP3,newHeader);
	int LenPack=createPacket(newHeader,newBody,newPacket);
	int retval = send(conn_socket,newPacket,LenPack,0);
	if (retval == SOCKET_ERROR) {WSACleanup();return false;}
	char header[10],body[512],foot[2];

	retval = recv(conn_socket,header,10,0 );
	retval = recv(conn_socket,body,header[7],0 );
	retval = recv(conn_socket,foot,2,0 );
	if (retval == SOCKET_ERROR) {closesocket(conn_socket);WSACleanup();	return false;}

	Close(conn_socket);
	if ((body[4]|body[5]|body[6]|body[7])==0) return true; else return false;

	return TRUE;
}
////////////////////////////////////////////////////////

BOOL CEmuLinkCtrl::NormalUIAppSwitch(LPCTSTR DBName) 
{
	SOCKET  conn_socket;
	if (Connect(conn_socket)==false) return false;

	//LocalID DmFindDatabase (UInt16 cardNo,const Char* nameP)
	UInt32 *p32=NULL;
	char newBody[280],newHeader[12],newPacket[512];

	int LenB =createBody(sysTrapDmFindDatabase,2,newBody);
	int LenP2=copySTRING(DBName,newBody+LenB);
	int LenP1=copyWORD(0,newBody+LenB+LenP2);
	createHeader(LenB+LenP1+LenP2,newHeader);
	int LenPack=createPacket(newHeader,newBody,newPacket);
	int retval = send(conn_socket,newPacket,LenPack,0);
	if (retval == SOCKET_ERROR) {WSACleanup();	return false;}
	char header[10],body[512],foot[2];

	retval = recv(conn_socket,header,10,0 );
	retval = recv(conn_socket,body,header[7],0 );
	retval = recv(conn_socket,foot,2,0 );

	DWord LID;
	*(((Byte*)(&LID))+3)=body[4];
	*(((Byte*)(&LID))+2)=body[5];
	*(((Byte*)(&LID))+1)=body[6];
	*(((Byte*)(&LID))+0)=body[7];
	if (LID==0) {Close(conn_socket);return false;}

	// Err SysUIAppSwitch(UInt16 cardNo, LocalID dbID, UInt16 cmd, MemPtr cmdPBP)

	LenB =createBody(sysTrapSysUIAppSwitch, 4,newBody);
	int LenP4=copyDWORD(0,newBody+LenB);
	int LenP3=copyWORD(0,newBody+LenB+LenP4);//sysAppLaunchCmdNormalLaunch
	LenP2=copyDWORD(LID,newBody+LenB+LenP4+LenP3);
	LenP1=copyWORD(0,newBody+LenB+LenP4+LenP3+LenP2);
	createHeader(LenB+LenP1+LenP2+LenP3+LenP4,newHeader);
	LenPack=createPacket(newHeader,newBody,newPacket);
	retval = send(conn_socket,newPacket,LenPack,0);
	if (retval == SOCKET_ERROR) {WSACleanup();return false;}
	retval = recv(conn_socket,header,10,0 );
	retval = recv(conn_socket,body,header[7],0 );
	retval = recv(conn_socket,foot,2,0 );

	Close(conn_socket);
	if ((body[4]|body[5]|body[6]|body[7])==0) return TRUE; else return false;

	return TRUE;
}


BOOL CEmuLinkCtrl::SysSoftReset() 
{
	SOCKET  conn_socket;
	if (Connect(conn_socket)==false) return false;
	char newBody[280],newHeader[12],newPacket[512];
	int LenB =createBody(sysTrapSysReset,0,newBody);
	createHeader(LenB,newHeader);
	int LenPack=createPacket(newHeader,newBody,newPacket);
	int retval = send(conn_socket,newPacket,LenPack,0);
	if (retval == SOCKET_ERROR) {WSACleanup();	return false;}
	Close(conn_socket);

	return TRUE;
}

BOOL CEmuLinkCtrl::CheckPresence() 
{
	SOCKET  conn_socket;
	if (Connect(conn_socket)==false) return false;

	Close(conn_socket);

	return TRUE;
}
