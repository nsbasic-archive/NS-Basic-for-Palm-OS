#ifndef __STRING_LIB_PRV_H__
#define __STRING_LIB_PRV_H__

// Palm OS common definitions
#include <PalmTypes.h>
#include "StringLib.h"

/********************************************************************
 * Private Structures
 ********************************************************************/
 
// Library globals
typedef struct StringLibGlobalsType {
	UInt16					thisLibRefNum;			// our library reference number (for convenience and debugging)
	Int16					openCount;			// library open count
	} StringLibGlobalsType;

typedef StringLibGlobalsType*		StringLibGlobalsPtr;
#endif	// __STRING_LIB_PRV_H__

