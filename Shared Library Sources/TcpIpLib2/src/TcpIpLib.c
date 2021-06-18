/*  TcpIpLib.c:  Simple TCP/IP library for NSBasic for the Palm
 *  Also an example for making NSBasic shared libs using gcc
 *
 *  ********************* IMPORTANT NOTE **********************
 *  IF YOU'RE USING THIS AS A BASE TO CREATE YOUR OWN LIBRARY,
 *  CHANGE THE CREATOR IN THE .DEF FILE FOR YOUR OWN PROJECT!!!
 *  ********************* IMPORTANT NOTE **********************
 *
 *  Copyright Matthijs van Duin, 2002  --  beep@nubz.org
 *
 *  Version 2.1  Changed timout in Read so it works on POSE
 *  Version 2.0  Public release, copied from LCedLib 1.0
 *  (successor to TcpIpLib 1.0, however shares no code at all)
 */

#include <PalmOS.h>
#include <string.h>
#include "TcpIpLib.h"

/* this macro behaves like a global variable */
/* yes, I know, I'm going to go to Programmer's Hell for this */
#define gLibref \
	(((UInt16 *) &(SysLibTblEntry(refNum)->globalsP))[0])

/* initialize shared library */
Err start(UInt16 refNum, SysLibTblEntryPtr entryP) {
	extern void *jmptable ();
	entryP->dispatchTblP = (void *) jmptable;
	entryP->globalsP = 0;
	return 0;
}

/* placeholder for unused traps */
Err nothing(UInt16 refNum) {
	return 0;
}

/* return version */
Int32 TcpIpLibVersion(UInt16 refNum, double *version) {
	*version = 2.1;
	return 0;
}

/* refresh networking */
Err InetRefresh(UInt16 refNum) {
	Err err;
	UInt8 allup;
	UInt16 iferr;
	
	err = NetLibConnectionRefresh(gLibref, true, &allup, &iferr);
	
	return err ? err : iferr;
}

/* initialize networking */
Err InetInit(UInt16 refNum) {
	Err	err;
	UInt16	iferr;
	UInt16	libref;
	
	err = SysLibFind("Net.lib", &libref);
	if (err)
		return err;
	
	err = NetLibOpen(libref, &iferr);
	if (err && err != netErrAlreadyOpen)
		return err;
	
	if (iferr) {
		NetLibClose(libref, true);
		return iferr;
	}
	
	gLibref = libref;
	
	return 0;
}

/* terminate networking */
Err InetTerm(UInt16 refNum) {
	NetLibClose(gLibref, false);
	return 0;
}

/* convert a hostname or ip address to a NetIPAddr */
Err HostToAddr(UInt16 libref, char *host, NetIPAddr *addr, Int32 timeout) {
	NetHostInfoBufType buf;
	NetHostInfoType *hinfo;
	Err err;
	
	*addr = NetLibAddrAToIN(libref, host);
	if (*addr != -1)
		return 0;
	
	hinfo = NetLibGetHostByName(libref, host, &buf, timeout, &err);
	if (!hinfo)
		return err;
	
	*addr = *((NetIPAddr *) hinfo->addrListP[0]);
	return 0;
}

/* open a new socket */
Int32 InetOpen(UInt16 refNum, char *host, Int32 port, UInt32 timeout, Int32 *s) {
	NetSocketAddrINType addr;
	Err err;
	UInt16 libref;
	char yea = 1;
	
	timeout = (SysTicksPerSecond() * timeout + 500) / 1000;
	
	err = InetInit(refNum);
	if (!err)
		err = InetRefresh(refNum);
	if (err) {
		*s = -((Int32) err);
		return 0;
	}
	
	libref = gLibref;
	
	err = HostToAddr(libref, host, &addr.addr, timeout);
	if (err) {
		InetTerm(refNum);
		*s = -((Int32) err);
		return 0;
	}
	
	addr.family = netSocketAddrINET;
	addr.port = port;
	
	*s = NetLibSocketOpen(libref, netSocketAddrINET, netSocketTypeStream, 0,
				-1, &err);
	if (*s < 0) {
		InetTerm(refNum);
		*s = -((Int32) err);
		return 0;
	}
	
	if (NetLibSocketConnect(libref, *s, (NetSocketAddrType *) &addr,
			sizeof(NetSocketAddrINType), timeout, &err) < 0 ||
			NetLibSocketOptionSet(libref, *s, netSocketOptLevelTCP,
			netSocketOptTCPNoDelay, &yea, sizeof(yea), 10, &err) < 0) {
		InetClose(refNum, *s);
		*s = -((Int32) err);
		return 0;
	}
	
	return 0;
}

/* close a socket */
Int32 InetClose(UInt16 refNum, Int32 s) {
	Err err;
	
	NetLibSocketClose(gLibref, s, -1, &err);
	InetTerm(refNum);
	
	return 0;
}

/* read from a socket */
Int32 InetRead(UInt16 refNum, Int32 s, Int32 len, char *set, UInt32 timeout, char *data) {
	Err err;
	UInt16 libref = gLibref;
	Int32 l;
	
	/* total timeout is in miliseconds */
	timeout = timeout / 10; 
	
	if (!*set)
		set = 0;
	
	do {
		l = NetLibReceive(libref, s, data, len, 0, 0, 0, 0, &err);
		if (l > 0) {
			if (set) {
				data[l] = 0;
				if (strpbrk(data, set))
					return 0;
			}
			data += l;
			len -= l;
			err = netErrTimeout;
		} 
		SysTaskDelay(1);
	} while (len > 0 && err == netErrTimeout && timeout--);
	
	*data = 0;
	return 0;
}

/* write to a socket */
Int32 InetWrite(UInt16 refNum, Int32 s, char *data, Int32 *len) {
	Err err;
	
	err = InetRefresh(refNum);
	if (!err)
		*len = NetLibSend(gLibref, s, data, strlen(data), 0, 0, 0, 0, &err);
	if (err)
		*len = -((Int32) err);
	
	return 0;
}

/* flush data from a socket */
Int32 InetFlush(UInt16 refNum, Int32 s) {
	char buf[128];
	Err err;
	UInt16 libref = gLibref;
	
	while (NetLibReceive(libref, s, buf, 128, 0, 0, 0, 1, &err) > 0);
	
	return 0;
}
