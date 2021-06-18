#ifndef _TCPIPLIB_H_
#define _TCPIPLIB_H_

#include <LibTraps.h>

#define TcpIpLibVersion_trapno	sysLibTrapCustom
#define InetOpen_trapno		sysLibTrapCustom+1
#define InetClose_trapno	sysLibTrapCustom+2
#define InetRead_trapno		sysLibTrapCustom+3
#define InetWrite_trapno	sysLibTrapCustom+4
#define InetFlush_trapno	sysLibTrapCustom+5

#ifdef COMPILING_SHLIB
#define TCPIPLIB_TRAP(trapno)
#else
#define TCPIPLIB_TRAP(trapno)	SYS_TRAP(trapno)
#endif

Int32 TcpIpLibVersion(UInt16 refNum, double *version)
	TCPIPLIB_TRAP(TcpIpLibVersion_trapno);
Int32 InetOpen(UInt16 refNum, char *host, Int32 port, UInt32 timeout, Int32 *s)
	TCPIPLIB_TRAP(InetOpen_trapno);
Int32 InetClose(UInt16 refNum, Int32 s)
	TCPIPLIB_TRAP(InetClose_trapno);
Int32 InetRead(UInt16 refNum, Int32 s, Int32 len, char *set, UInt32 timeout, char *data)
	TCPIPLIB_TRAP(InetRead_trapno);
Int32 InetWrite(UInt16 refNum, Int32 s, char *data, Int32 *len)
	TCPIPLIB_TRAP(InetWrite_trapno);
Int32 InetFlush(UInt16 refNum, Int32 s)
	TCPIPLIB_TRAP(InetFlush_trapno);

#endif /* _TCPIPLIB_H_ */
