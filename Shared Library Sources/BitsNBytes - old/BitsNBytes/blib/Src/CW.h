#define PALMOS_35_OR_HIGHER
#ifdef PALMOS_35_OR_HIGHER
#define PILOT_PRECOMPILED_HEADERS_OFF
#include <PalmOS.h>
#include <PalmCompatibility.h>
#else
#include <Pilot.h>
#include <SysAll.h>
#endif

#define	NON_PORTABLE
//#include <SystemPrv.h>



asm long __lmul__(long left:__D0,long right:__D1):__D0;
asm long __ldivu__(unsigned long left:__D0,unsigned long right:__D1):__D0;
asm long __ldiv__(long left:__D0,long right:__D1):__D0;
asm long __lmodu__(unsigned long left:__D0,unsigned long right:__D1):__D0;
asm long __lmod__(long left:__D0,long right:__D1):__D0;
asm void __wswtch__(void);
asm void __lswtch__(void);
