#ifndef _NSBASIC_H_
#define _NSBASIC_H_

extern UInt32 CallExternalLibProc(UInt16 nProcVector, UInt16 nRefNum, UInt16 nArgCount, void **pArgs, UInt8 *pSize);
//extern void *PCallExternalLibProc(UInt32 nProcVector, UInt16 nRefNum, UInt16 nArgCount, void **pArgs, UInt8 *pSize);
extern UInt32 CallSystemProc(UInt16 nProcVector, UInt16 nArgCount, void **pArgs, UInt8 *pSize);
extern void *PCallSystemProc(UInt16 nProcVector, UInt16 nArgCount, void **pArgs, UInt8 *pSize);
extern void verb_external();
extern void verb_newExternal();
extern void verb_sysTrap();
extern void verb_loadLibrary();
extern void verb_appLaunch();
extern BOOL NSBFunc( UInt16 it );

typedef struct
{
   UInt16 nSysLibIndex;
   UInt32 clientContext;
   BOOL bLoaded;
   BOOL isMathLib;
} LibInfoType;
typedef LibInfoType *LibInfoTypePtr;

#define kMaxLibs 32

#endif // _NSBASIC_H_
