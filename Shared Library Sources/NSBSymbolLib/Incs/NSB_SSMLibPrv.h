/****************************************************************************** * * Copyright (c) 1994-1999 Palm Computing, Inc. or its subsidiaries. * All rights reserved. * * File: NSB_SSMLibPrv.h * * Description: *		Sample library private definitions. * * History: *   	5/20/97	vmk * *****************************************************************************/#ifndef __SAMPLE_LIB_PRV_H__#define __SAMPLE_LIB_PRV_H__// Palm OS common definitions#include <PalmTypes.h>#include <NSB_SSMLib.h>#include <PalmCompatibility.h>// Symbol device definitions are no longer used./******************************************************************** * Private Structures ********************************************************************/ // Library globalstypedef struct NSB_SSMLibGlobalsType {	UInt16					thisLibRefNum;			// our library reference number (for convenience and debugging)	Int16						openCount;				// library open count		// Add other library global fields here	Int16						contextCount;			// number of context in existence (for debugging)	UInt16                  ssmLibRefNum;       // Refnum of open library	} NSB_SSMLibGlobalsType;typedef NSB_SSMLibGlobalsType*		NSB_SSMLibGlobalsPtr;// Client context structure for storing each client-specific datatypedef struct NSB_SSMLibClientContextType {	UInt16					wSignature;				// signature for validating the context		UInt16 sysLibRefNum;	// Ref num of the SST library	UInt32 context;         // The context of the sub library	} NSB_SSMLibClientContextType;typedef NSB_SSMLibClientContextType*		NSB_SSMLibClientContextPtr;// The wSignature field of each NSB_SSMLibClientContextType will be set to// this value for debugging#define sampleLibContextSignature		(0xFEED)/******************************************************************** * Private Macros ********************************************************************/#define sampleDefaultCornerDiameter		(0)#endif	// __SAMPLE_LIB_PRV_H__