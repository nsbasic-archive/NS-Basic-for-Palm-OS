#ifndef __VFS_LIB_PRV_H__
#define __VFS_LIB_PRV_H__

// Palm OS common definitions
#include <PalmTypes.h>
#include <VFSLib.h>


/********************************************************************
 * Private Structures
 ********************************************************************/
 
// Library globals
typedef struct SGlobal {
	UInt16			thisLibRefNum;			// our library reference number (for convenience and debugging)
	Int16				openCount;				// library open count

	UInt32			lastError;
	UInt32			currentVolume;
	UInt32			volumeIterator;
	
	UInt32			dirEnumRef;
	UInt32			fileIterator;
	} SGlobal;

typedef SGlobal*		PSGlobal;


#endif	// __VFS_LIB_PRV_H__
