#ifndef _NSBASIC_C_
#define _NSBASIC_C_

#include "nsbasic.h"

extern struct basc_pref bp;

typedef struct
{
   UInt16 trap15;
   UInt16 libCall;
   UInt16 ret[7];
} CodeBlockType;
CodeBlockType code_block;

#ifdef __MC68K__
extern char *devel_address(struct dataelem *arg, unsigned short s1,unsigned short s2,unsigned short s3);
#else
extern char *devel_address(PNOBlock *pnoP, struct dataelem *arg, UInt16 s1,UInt16 s2,UInt16 s3);
#endif

LibInfoType arrLibInfo[kMaxLibs /* 32 */];

/* New open and close library calls to accomodate CW 9 */
Err CW9LibOpen(UInt refnum, UInt32 *context)		// Initialize library for use
	SYS_TRAP(sysLibTrapOpen);
Err CW9LibClose(UInt refnum, UInt32 context)// Free library resources when finished
	SYS_TRAP(sysLibTrapClose);


// Called by main application, to allow any necessary setup
// Call is made during StartApplication before any project
// startup code is executed
void NSBInit()
{
   // Initalize code block for executing traps
   code_block.trap15 = 0x4E4F; // trap #15
   code_block.libCall = 0x0000;               // the library call
   code_block.ret[0] = 0x2E44; // move.l d4,a7     // Restore stack pointer
   code_block.ret[1] = 0x261F; // move.l (a7)+,d3  // Restore d3 from the stack
   code_block.ret[2] = 0x281F; // move.l (a7)+,d4  // Restore d4 from the stack
   code_block.ret[3] = 0x245F; // move.l (a7)+,a2  // Restore a2 from the stack
   code_block.ret[4] = 0x225F; // move.l (a7)+,a1  // Restore a1 from the stack
   code_block.ret[5] = 0x4E5E; // unlk a6          // Put the link back
   code_block.ret[6] = 0x4E75; // rts              // Return from the subroutine

   // Zero out library info storage
   MemSet( arrLibInfo, kMaxLibs * sizeof( LibInfoType ), 0 );

	// Register PNO(op_code) functions
	PNO(op_func)[0x70] = &verb_external;    // external proc        // 12/08/2000 MMD
	PNO(op_func)[0x71] = &verb_external;    // external func        // 12/08/2000 MMD
	PNO(op_func)[0x72] = &verb_loadLibrary;                         // 12/08/2000 MMD
	PNO(op_func)[0x73] = &verb_sysTrap;      // System Trap proc    // 12/08/2000 MMD
	PNO(op_func)[0x74] = &verb_sysTrap;      // System Trap func    // 12/08/2000 MMD
	
	PNO(op_func)[0x78] = &verb_newExternal;  // new external proc   // 6/24/2003 EMP
	PNO(op_func)[0x79] = &verb_newExternal;	// new external func   // 6/24/2003 EMP
	PNO(op_func)[0x7A] = &verb_loadLibrary;  // new external library // 8/07/2003 EMP
	PNO(op_func)[0x7B] = &verb_newExternal;  // new external proc   // 6/24/2003 EMP
	PNO(op_func)[0x7C] = &verb_newExternal;	// new external func   // 6/24/2003 EMP
	AddToFuncTable( 650, &verb_appLaunch );
} // NSBInit

// Called by main application, to allow any necessary cleanup
// Call is made during ExitHousekeeping
void NSBTerm()
{
   Err error;
   int i;
   SysLibTblEntryPtr entryP;

   // Loop through Library Info, closing and unloading when necessary
   for( i = 0; i < kMaxLibs; i++ )
   {
      UInt16 foo;
      // Empty info block means the end of libraries
      if( arrLibInfo[i].nSysLibIndex == 0 )
         break;


      // Doug's suggestion
      entryP = SysLibTblEntry(arrLibInfo[i].nSysLibIndex);
      if (entryP -> dispatchTblP)
      {
          // Close library
          // This call causes problems with MathLib, because it has its own
          // specialized MathLibClose which takes an additional parameter
          // that isn't passed here.
          // EMP 11 April 2001 So pass it then.  It doesn't hurt anything.

          if (arrLibInfo[i].isMathLib)
          
             error = MathLibClose( arrLibInfo[i].nSysLibIndex, &foo );
          else
          	 // EMP was CW9LibOpen
             error = CW9LibClose(arrLibInfo[i].nSysLibIndex, (arrLibInfo[i].clientContext));

          if( error )
             misc_errmsg( "Error closing library" );

          // If we loaded it, unload it
          if( arrLibInfo[i].bLoaded )
          {
             error = SysLibRemove( arrLibInfo[i].nSysLibIndex );
             if( error )
                misc_errmsg( "Error removing library" );
          }
      }
   }
} // NSBTerm

BOOL NSBFunc( UInt16 it )
{
	switch( it )
	{
	case 201: verb_appLaunch(); break;
	default:
		return FALSE;
	}
	return TRUE;
} // NSBFunc



/**
    CallExternalLibProcHelper
    Helper routine for CallExternalLibProc
    Eric Pepke
    29 September, 2000
    
    See CallExternalLibProc for details
*/
UInt32 CallExternalLibProcHelper(void *routine, UInt16 nRefNum, UInt16 nArgCount, void **pArgs, UInt8 *pSize);
asm UInt32 CallExternalLibProcHelper(void *routine, UInt16 nRefNum, UInt16 nArgCount, void **pArgs, UInt8 *pSize)
{
#define routine		8
#define nRefNum		12
#define nArgCount		14
#define pArgs			16
#define pSize			20
	link		a6,#0					// Don't need any locals at a6, keep link just in case
	move.l	a1,-(a7)				// Push a1 on the stack; we'll need it
	move.l	a2,-(a7)				// Push a2 on the stack; we'll need it.
	move.l	d4,-(a7)				// Save d4; we'll need it.
	move.l	d3,-(a7)				// Save d3; we'll need it

	// Push all the arguments onto the stack.
	clr.l   d3                  // d3 high word = 0
	move.w	nArgCount(a6),d3	// d3 = nArgCount
	move.l	pSize(a6),d0		// d0 -> beginning of pSize
	add.l		d3,d0					// d0 -> end of pSize + 1
	move.l	d0,a2					// a2 -> end of pSize + 1
	move.l	pArgs(a6),d0		// d0 -> beginning of pArgs
	add.l		d3,d0
	add.l		d3,d0
	add.l		d3,d0
	add.l		d3,d0					// d0 -> end of pArgs + 1
	move.l	d0,a1					// a1 -> end of pArgs + 1

	move.l	a7,d4					// d4 is stack pointer, to be restored
	cmpi.l	#0,d3					// See if d3 is zero or less
	ble.s		AvoidPush			// If so, avoid pushing any arguments
PushAgain:                    // Push one (more) argument onto the stack 
	move.l	-(a1),a0				// a0 -> this argument
	clr.l		d0
	move.b	-(a2),d0				// d0 -> the size of argument
	cmpi.w	#8,d0					// See if it's an eight-byte argument
	blt.s		NotEightByte		// Avoid the next pushes if not
	move.l	4(a0),-(a7)			// Push the further four bytes of the argument
NotEightByte:						// It's either not eight-byte, or the first seg has been pushed
	cmpi.w	#4,d0					// See if it's a four- or eight-byte argument
	blt.s		NotFourByte			// Avoid pushing these two bytes if not
	move.w	2(a0),-(a7)			// Push the further-by-two two bytes of the argument
NotFourByte:						// There have to be two bytes; push them
	move.w	(a0),-(a7)			// Push the last two bytes
	addi.l	#-1,d3				// See if there are any more arguments
	bgt.s		PushAgain			// If so, go do some more
AvoidPush:							// Otherwise, fall through to the part where business is done
	move.w	nRefNum(a6),-(a7)	// push nRefNum

	// Now do it!
	move.l	routine(a6),a0		// a0 -> routine
	jmp		(a0)					// Go do it

	// The following is for information purposes only,
	// as the actual return is in the tail routine.
	move.l	d4,a7					// Restore stack pointer
	move.l	(a7)+,d3				// Restore d3 from the stack
	move.l	(a7)+,d4				// Restore d4 from the stack
	move.l	(a7)+,a2				// Restore a2 from the stack
	move.l	(a7)+,a1				// Restore a1 from the stack
	unlk		a6						// Put the link back
	rts								// Return from the subroutine
#undef routine
#undef nArgCount
#undef pArgs
#undef pSize
#undef nRefNum
} // CallExternalLibProcHelper

/**
    CallExternalLibProc
    Function to call a procedure in a Palm shared library
    Eric Pepke
    29 September, 2000
    
    Input parameters:
    UInt32 nProcVector  The procedure call, for example, 0xA813 for procedure 14
    UInt16 nRefNum      Reference number of library from SysLibLoad
    UInt16 nArgCount    The number of arguments (see Output)
    void **pArgs        An array of pointers to arguments
    UInt8 *pSize        An array containing the size of each argument (2, 4, or 8)
    
    The input arguments do not include the nProcVector.  For example, the call
    MathLibExp(UInt16 nProcVector, double x, double &result)
    would be represented with two arguments:
        1) A double value x
        2) A pointer to a double result
    
    Output parameters:
    The return value of CallExternalLibProc is the return value of the called procedure
    if it returns up to 4 bytes (the size of a pointer or Int32).  If the called
    procedure returns void, ignore the return value.
    If the called procedure returns more than 4 bytes, for example a double, make the 
    first parameter a pointer to memory to hold the returned value and ignore the
    returned value.
    
    How it works:
    CallExternalLibProc creates, on the stack, the tail end of a function call containing
    the trap for the appropriate library procedure.  It then passes the address of this 
    tail to CallExternalLibProcHelper.  This helper function sets up the stack and then
    does a jump to the tail.  The tail contains the library call, code to restore the
    stack, and the all-important unlk and rts to return from the function.
    
    The tail need not be allocated on the stack, as in this function.  It can as easily
    be allocated on the heap or stored in a global variable, provided that care is taken
    to ensure that it is aligned on a word boundary (preferably a double-word boundary).
    As only a single word of this ever changes, it is possible to achieve greater speed 
    by keeping the tail around and only changing the libCall word.  If you allocate this
    as a handle, be sure to lock the handle down before using it.  The code does not care
    where it is in memory, as it contains no absolute hard-coded addresses (in fact, no 
    hard-coded addresses at all).
    
    This exactly mimics the assembly code of an inline call to the library routine and
    thus makes no assumptions whatsoever about the internals of trap15.  It should 
    therefore work with any well behaved shared library, even if the implementation
    of shared libraries changes dramatically.
    
    The assembly code assumes that d0 and a0 are freely usable, as per standard Palm 
    conventions, and it saves all other registers before use.
    
    Calling this function with improper arguments will nearly always result in a fatal
    exception, so be careful.
    
    See MyExp for an example of using CallExternalLibProc.
*/

UInt32 CallExternalLibProc( UInt16 nProcVector, UInt16 nRefNum, UInt16 nArgCount, void **pArgs, UInt8 *pSize )
{
   // This has to be declared here for some reason
   // Using a global variable causes errors
   CodeBlockType cb;
   UInt32 retVal;

   // We initialized a copy of this structure
   // Let's move memory in a chunk instead of multiple assigns
   MemMove( (void *)&cb, (void *)&code_block, sizeof( CodeBlockType ) );
   cb.libCall = nProcVector;

   retVal = CallExternalLibProcHelper( &cb, nRefNum, nArgCount, pArgs, pSize );
   return retVal;
} // CallExternalLibProc


/** Note: The following two routines are like the previous four but for system calls, 
not external library calls.
*/

/**
CallSystemProcHelper
Helper routine for CallSystemProc
Eric Pepke
4 October, 2000

See CallSystemProc for details
*/
UInt32 CallSystemProcHelper(void *routine, UInt16 nArgCount, void **pArgs, UInt8 *pSize);
asm UInt32 CallSystemProcHelper(void *routine, UInt16 nArgCount, void **pArgs, UInt8 *pSize)
{
#define routine		8
#define nArgCount		12
#define pArgs			14
#define pSize			18
	link		a6,#0					// Don't need any locals at a6, keep link just in case
	move.l	a1,-(a7)				// Push a1 on the stack; we'll need it
	move.l	a2,-(a7)				// Push a2 on the stack; we'll need it.
	move.l	d4,-(a7)				// Save d4; we'll need it.
	move.l	d3,-(a7)				// Save d3; we'll need it

	// Push all the arguments onto the stack.
	clr.l   d3                  // d3 high word = 0
	move.w	nArgCount(a6),d3	// d3 = nArgCount
	move.l	pSize(a6),d0		// d0 -> beginning of pSize
	add.l		d3,d0					// d0 -> end of pSize + 1
	move.l	d0,a2					// a2 -> end of pSize + 1
	move.l	pArgs(a6),d0		// d0 -> beginning of pArgs
	add.l		d3,d0
	add.l		d3,d0
	add.l		d3,d0
	add.l		d3,d0					// d0 -> end of pArgs + 1
	move.l	d0,a1					// a1 -> end of pArgs + 1

	move.l	a7,d4					// d4 is stack pointer, to be restored
	cmpi.l	#0,d3					// See if d3 is zero or less
	ble.s		AvoidPush			// If so, avoid pushing any arguments
PushAgain:							// Push one (more) argument onto the stack 
	move.l	-(a1),a0				// a0 -> this argument
	clr.l		d0
	move.b	-(a2),d0				// d0 -> the size of argument
	cmpi.w	#8,d0					// See if it's an eight-byte argument
	blt.s		NotEightByte		// Avoid the next pushes if not
	move.l	4(a0),-(a7)			// Push the further four bytes of the argument
NotEightByte:						// It's either not eight-byte, or the first seg has been pushed
	cmpi.w	#4,d0					// See if it's a four- or eight-byte argument
	blt.s		NotFourByte			// Avoid pushing these two bytes if not
	move.w	2(a0),-(a7)			// Push the further-by-two two bytes of the argument
NotFourByte:						// There have to be two bytes; push them
	move.w	(a0),-(a7)			// Push the last two bytes
	addi.l	#-1,d3				// See if there are any more arguments
	bgt.s		PushAgain			// If so, go do some more
AvoidPush:							// Otherwise, fall through to the part where business is done

	// Now do it!
	move.l	routine(a6),a0		// a0 -> routine
	jmp		(a0)					// Go do it

	// The following is for information purposes only
	// as the actual return is in the tail routine.
	move.l	d4,a7					// Restore stack pointer
	move.l	(a7)+,d3				// Restore d3 from the stack
	move.l	(a7)+,d4				// Restore d4 from the stack
	move.l	(a7)+,a2				// Restore a2 from the stack
	move.l	(a7)+,a1				// Restore a1 from the stack
	unlk		a6						// Put the link back
	rts								// Return from the subroutine
#undef routine
#undef nArgCount
#undef pArgs
#undef pSize
} // CallSystemProcHelper

/**
CallSystemProc
Function to call a Palm system procedure
Eric Pepke
4 October, 2000

Input parameters:
UInt32 nProcVector The procedure call, for example, 0xA803
UInt16 nArgCount The number of arguments (see Output)
void **pArgs An array of pointers to arguments
UInt8 *pSize An array containing the size of each argument (2, 4, or 8)

The input arguments do not include the nProcVector. For example, the call
MathLibExp(UInt16 nProcVector, double x, double &result)
would be represented with two arguments:
1) A double value x
2) A pointer to a double result

Output parameters:
The return value of CallSystemProc is the return value of the called procedure
if it returns up to 4 bytes (the size of a pointer or Int32). If the called
procedure returns void, ignore the return value.
If the called procedure returns more than 4 bytes, for example a double, make the 
first parameter a pointer to memory to hold the returned value and ignore the
returned value.

How it works:
CallSystemProc creates, on the stack, the tail end of a function call containing
the trap for the appropriate library procedure. It then passes the address of this 
tail to CallSystemProcHelper. This helper function sets up the stack and then
does a jump to the tail. The tail contains the library call, code to restore the
stack, and the all-important unlk and rts to return from the function.

The tail need not be allocated on the stack, as in this function. It can as easily
be allocated on the heap or stored in a global variable, provided that care is taken
to ensure that it is aligned on a word boundary (preferably a double-word boundary).
As only a single word of this every changes, it is possible to achieve greater speed 
by keeping the tail around and only changing the libCall word. If you allocate this
as a handle, be sure to lock the handle down before using it. The code does not care
where it is in memory, as it contains no absolute hard-coded addresses (in fact, no 
hard-coded addresses at all).

This exactly mimics the assembly code of an inline call to the library routine and
thus makes no assumptions whatsoever about the internals of trap15. It should 
therefore work with any well behaved shared library, even if the implementation
of shared libraries changes dramatically.

The assembly code assumes that d0 and a0 are freely usable, as per standard Palm 
conventions, and it saves all other registers before use.

Calling this function with improper arguments will nearly always result in a fatal
exception, so be careful.

See MyStrCpy for an example of using CallSystemProc.
*/

UInt32 CallSystemProc( UInt16 nProcVector, UInt16 nArgCount, void **pArgs, UInt8 *pSize )
{
   // This has to be declared here for some reason
   // Using a global variable causes errors
   CodeBlockType cb;

   // We initialized a copy of this structure
   // Let's move memory in a chunk instead of multiple assigns
   MemMove( (void *)&cb, (void *)&code_block, sizeof( CodeBlockType ) );
   cb.libCall = nProcVector;

   return CallSystemProcHelper( &cb, nArgCount, pArgs, pSize );
} // CallSystemProc


/* Note: The following two routines are identical to CallSystemProc and
CallSystemProcHelper except that they return pointers rather than
integers, don't accept the refnum, and don't push the refnum.*/

/**
PCallSystemProcHelper
Helper routine for PCallSystemProc
Eric Pepke
4 OCTOBER, 2000

See PCallSystemProc for details
*/
void *PCallSystemProcHelper(void *routine, UInt16 nArgCount, void **pArgs, UInt8 *pSize);
asm void *PCallSystemProcHelper(void *routine, UInt16 nArgCount, void **pArgs, UInt8 *pSize)
{
#define routine		8
#define nArgCount		12
#define pArgs			14
#define pSize			18
	link		a6,#0					// Don't need any locals at a6, keep link just in case
	move.l	a1,-(a7)				// Push a1 on the stack; we'll need it
	move.l	a2,-(a7)				// Push a2 on the stack; we'll need it.
	move.l	d4,-(a7)				// Save d4; we'll need it.
	move.l	d3,-(a7)				// Save d3; we'll need it

	// Push all the arguments onto the stack.
	clr.l   d3                  // d3 high word = 0
	move.w	nArgCount(a6),d3	// d3 = nArgCount
	move.l	pSize(a6),d0		// d0 -> beginning of pSize
	add.l		d3,d0					// d0 -> end of pSize + 1
	move.l	d0,a2					// a2 -> end of pSize + 1
	move.l	pArgs(a6),d0		// d0 -> beginning of pArgs
	add.l		d3,d0
	add.l		d3,d0
	add.l		d3,d0
	add.l		d3,d0					// d0 -> end of pArgs + 1
	move.l	d0,a1					// a1 -> end of pArgs + 1

	move.l	a7,d4					// d4 is stack pointer, to be restored
	cmpi.l	#0,d3					// See if d3 is zero or less
	ble.s		AvoidPush			// If so, avoid pushing any arguments
PushAgain:							// Push one (more) argument onto the stack 
	move.l	-(a1),a0				// a0 -> this argument
	clr.l		d0
	move.b	-(a2),d0				// d0 -> the size of argument
	cmpi.w	#8,d0					// See if it's an eight-byte argument
	blt.s		NotEightByte		// Avoid the next pushes if not
	move.l	4(a0),-(a7)			// Push the further four bytes of the argument
NotEightByte:						// It's either not eight-byte, or the first seg has been pushed
	cmpi.w	#4,d0					// See if it's a four- or eight-byte argument
	blt.s		NotFourByte			// Avoid pushing these two bytes if not
	move.w	2(a0),-(a7)			// Push the further-by-two two bytes of the argument
NotFourByte:						// There have to be two bytes; push them
	move.w	(a0),-(a7)			// Push the last two bytes
	addi.l	#-1,d3				// See if there are any more arguments
	bgt.s		PushAgain			// If so, go do some more
AvoidPush:							// Otherwise, fall through to the part where business is done

	// Now do it!
	move.l	routine(a6),a0		// a0 -> routine
	jmp		(a0)					// Go do it

	// The following is for information purposes only,
	// as the actual return is in the tail routine.
	move.l	d4,a7					// Restore stack pointer
	move.l	(a7)+,d3				// Restore d3 from the stack
	move.l	(a7)+,d4				// Restore d4 from the stack
	move.l	(a7)+,a2				// Restore a2 from the stack
	move.l	(a7)+,a1				// Restore a1 from the stack
	unlk		a6						// Put the link back
	rts								// Return from the subroutine
#undef routine
#undef nArgCount
#undef pArgs
#undef pSize
} // PCallSystemProcHelper

/**
PCallSystemProc
Function to call a system procedure
Eric Pepke
4 October, 2000

Input parameters:
UInt32 nProcVector The procedure call, for example, 0xA813 for procedure 14
UInt16 nArgCount The number of arguments (see Output)
void **pArgs An array of pointers to arguments
UInt8 *pSize An array containing the size of each argument (2, 4, or 8)

The input arguments do not include the nProcVector. For example, the call
MathLibExp(UInt16 nProcVector, double x, double &result)
would be represented with two arguments:
1) A double value x
2) A pointer to a double result

Output parameters:
The return value of CallSystemProc is the return value of the called procedure
if it returns up to 4 bytes (the size of a pointer or Int32). If the called
procedure returns void, ignore the return value.
If the called procedure returns more than 4 bytes, for example a double, make the 
first parameter a pointer to memory to hold the returned value and ignore the
returned value.

How it works:
CallSystemProc creates, on the stack, the tail end of a function call containing
the trap for the appropriate library procedure. It then passes the address of this 
tail to CallSystemProcHelper. This helper function sets up the stack and then
does a jump to the tail. The tail contains the library call, code to restore the
stack, and the all-important unlk and rts to return from the function.

The tail need not be allocated on the stack, as in this function. It can as easily
be allocated on the heap or stored in a global variable, provided that care is taken
to ensure that it is aligned on a word boundary (preferably a double-word boundary).
As only a single word of this every changes, it is possible to achieve greater speed 
by keeping the tail around and only changing the libCall word. If you allocate this
as a handle, be sure to lock the handle down before using it. The code does not care
where it is in memory, as it contains no absolute hard-coded addresses (in fact, no 
hard-coded addresses at all).

This exactly mimics the assembly code of an inline call to the library routine and
thus makes no assumptions whatsoever about the internals of trap15. It should 
therefore work with any well behaved shared library, even if the implementation
of shared libraries changes dramatically.

The assembly code assumes that d0 and a0 are freely usable, as per standard Palm 
conventions, and it saves all other registers before use.

Calling this function with improper arguments will nearly always result in a fatal
exception, so be careful.

See MyMemHandleLock for an example of using CallSystemProc.
*/

void *PCallSystemProc(UInt16 nProcVector, UInt16 nArgCount, void **pArgs, UInt8 *pSize)
{
   // This has to be declared here for some reason
   // Using a global variable causes errors
   CodeBlockType cb;

   // We initialized a copy of this structure
   // Let's move memory in a chunk instead of multiple assigns
   MemMove( (void *)&cb, (void *)&code_block, sizeof( CodeBlockType ) );
   cb.libCall = nProcVector;

   return PCallSystemProcHelper( &cb, nArgCount, pArgs, pSize );
} // PCallSystemProc

typedef struct
{
	struct dataelem *arg;
	unsigned int occ1, occ2, occ3;
    struct dataelem *sde1, *sde2, *sde3;
} ArgInstance;

void NSBPackPtrs(ArgInstance *argI, VoidHand *pHnd, void **pArg, UInt8 *pSize,
  Int16 type)
{
   char *charP, **charPP;
   void **voidPP;
   UInt16 nSize;
   UInt16 elSize;
   void **argVal;
   UInt32 nElements = 1;
   
   /* Determine the number of elements.  If 1, reduces to a scalar */
   if (!argI -> sde1) nElements *= argI -> arg -> max_no_values1;
   if (!argI -> sde2) nElements *= argI -> arg -> max_no_values2;
   if (!argI -> sde3) nElements *= argI -> arg -> max_no_values3;

   // Figure out how much memory needed for the argument,
   // then get a handle and lock down its pointer

   if (type)
   {
       /* New function call, use this type and size */
       switch(type)
       {
           case 'i':
           case 'n':
           case 'v':
           	   elSize = *pSize;
           	   nSize = nElements * *pSize;
               break;
           case 'I':
           case 'N':
           	   elSize = *pSize;
               nSize = nElements * *pSize + sizeof(void *);   
               *pSize = sizeof(void *); // for self-referencing pointer;
               break;
           case 's':
           case 'S':
		      *pSize = sizeof( char * );
		      // Add an extra byte to allocated memory for null termination of string
		      // Add extra bytes to include a self-referencing pointer
		      if(argI -> arg -> kind != 's' ||  (UInt8)argI -> arg->flags == 0x80 ) // 031004 a single-byte non-terminated string
		      {
		         nSize = 1 + nElements;
		      }
		      else // arg->flags == 0x00 Null terminated C-string, only scalar
		      {
				 argVal = (void **) devel_address(argI -> arg, argI -> occ1, argI -> occ2, argI -> occ3);
		         nSize = StrLen((char *) argVal ) + 1;
		         if (nSize < 300) nSize = 300;
		      }
		      nSize += sizeof( char * );
		      break;
           default:
               ErrFatalDisplay("Unrecognized type in external library call");
               break;
       }
   }
   else
   {
	   switch( argI -> arg ->kind )
	   {
		   case 'i':
		      if( (UInt8)argI -> arg->flags == 0x80 )
		         *pSize = sizeof( Int32 );
		      else // arg->flags == 0x10
		         *pSize = sizeof( Int16 );
		      if (nElements > 1)
		      {
		      	elSize = *pSize;
		      	nSize = nElements * *pSize + sizeof(void *);
		      	*pSize = sizeof(void *); // for self-referencing pointer
		      }
		      else
		      {
		      	elSize = *pSize;
		      	nSize = *pSize;
		      }
		      break;
		   case 'n':
		      if( (UInt8)argI -> arg->flags == 0x40 )
		         *pSize = sizeof( double );
		      else // arg->flags == 0x20
		         *pSize = sizeof( float );
		      if (nElements > 1)
		      {
		      	elSize = *pSize;
		      	nSize = nElements * *pSize + sizeof(void *);
		      	*pSize = sizeof(void *); // for self-referencing pointer
		      }
		      else
		      {
		      	elSize = *pSize;
		      	nSize = *pSize;
		      }
		   case 's':
		      *pSize = sizeof( char * );
		      // Add an extra byte to allocated memory for null termination of string
		      // Add extra bytes to include a self-referencing pointer
		      if( (UInt8)argI -> arg->flags == 0x80 ) //  a single-byte non-terminated string
		      {
		         nSize = 1 + nElements;
		      }
		      else // arg->flags == 0x00 Null terminated C-string
		      {
		      	 argVal = (void **) devel_address(argI -> arg, argI -> occ1, argI -> occ2, argI -> occ3);
		         nSize = StrLen((char *) argVal ) + 1;
		         if (nSize < 300) nSize = 300;
		      }
		      nSize += sizeof( char * );
		      break;
		   case 'v':
		      *pSize = sizeof( void * );
		      nSize = *pSize;
		   default: ;
	   }
   }
      
   *pHnd = MemHandleNew( nSize );
   *pArg = MemHandleLock( *pHnd );

   // Now, stuff the appropriate data
   if (type)
   {
       /* New type, use the types */
       Int16 i, j, k;
       
	   charP = *pArg;

	   switch (type)
	   {
		   case 'I':
		   case 'N':
		   case 's':
           case 'S':
				// Turn first four bytes of block into a pointer to the fifth byte
		      charPP = (char **)charP;
		      charP += sizeof( char * );
		      *charPP = charP;
	   }

       for (i = argI -> occ1; i < (argI -> sde1 ? argI -> occ1 + 1 : argI -> arg -> max_no_values1); ++i)
       for (j = argI -> occ2; j < (argI -> sde2 ? argI -> occ2 + 1 : argI -> arg -> max_no_values2); ++j)
       for (k = argI -> occ3; k < (argI -> sde3 ? argI -> occ3 + 1 : argI -> arg -> max_no_values3); ++k)
       {
	   		argVal = (void **)devel_address(argI -> arg, i, j, k);

	       switch (type)
	       {
			   case 'i':
			      // EMP Byte conversion
			      if (argI -> arg->kind == 's' && (UInt8)argI -> arg->flags == 0x80)
			      {
			          /* It's a byte, convert it to an integer */
	    		      if(elSize == 4)
	    		         *( (Int32 *)charP ) = (Int32)( *( (char *)argVal ) );
	    		      else // elSize = 2
	    		         *( (Int16 *)charP ) = (Int16)( *( (char *)argVal ) );
			      }
			      else
			      {
	    		      if(elSize == 4)
	    		         *( (Int32 *)charP ) = (Int32)( *( (double *)argVal ) );
	    		      else // elSize = 2
	    		         *( (Int16 *)charP ) = (Int16)( *( (double *)argVal ) );
			      }
			      
			      break;
			   case 'n':
			      // EMP Byte Conversion 
			      if (argI -> arg->kind == 's' && (UInt8)argI -> arg->flags == 0x80)
			      {
	    		      if(elSize == 8)
	    		         *( (double *)charP ) = (double)( *( (char *)argVal ) );
	    		      else // elSize = 4
	    		         *( (float *)charP ) = (float)( *( (char *)argVal ) );
			      }
			      else
			      {
	    		      if(elSize == 8)
	    		         *( (double *)charP ) = *( (double *)argVal );
	    		      else // elSize = 4
	    		         *( (float *)charP ) = (float)( *( (double *)argVal ) );
	              }
	              
			      break;
			   case 'I':		   
			      // EMP Byte Conversion 
			      if (argI -> arg->kind == 's' && (UInt8)argI -> arg->flags == 0x80)
			      {
	    		      if(elSize == 4)
	    		         *( (Int32 *)charP ) = (Int32)( *( (char *)argVal ) );
	    		      else // elSize = 2
	    		         *( (Int16 *)charP ) = (Int16)( *( (char *)argVal ) );
			      }
			      else
			      {
	    		      if(elSize == 4)
	    		         *( (Int32 *)charP ) = (Int32)( *( (double *)argVal ) );
	    		      else // elSize = 2
	    		         *( (Int16 *)charP ) = (Int16)( *( (double *)argVal ) );
			      }
			      
			      break;
			   case 'N':		   
			      // EMP Byte Conversion 
			      if (argI -> arg->kind == 's' && (UInt8)argI -> arg->flags == 0x80)
	              {
	    		      if(elSize == 8 + sizeof(void *))
	    		         *( (double *)charP ) = (double)( *( (char *)argVal));
	    		      else // elSize = 4
	    		         *( (float *)charP ) = (float)( *( (char *)argVal ) );
	    		  }
	    		  else
	    		  {
	    		      if(elSize == 8 + sizeof(void *))
	    		         *( (double *)charP ) = *( (double *)argVal );
	    		      else // elSize = 4
	    		         *( (float *)charP ) = (float)( *( (double *)argVal ) );
	    		  }
	    		  
			      break;
			   case 's':
	           case 'S':
			      if( (UInt8)argI -> arg->flags == 0x00 )
			      {
			         elSize = StrLen((char *) argVal );
			      }
			      else
			      {
			      	 elSize = 1;
			      }
			      
			      MemMove( (void *)charP, argVal, elSize );
			      // Add terminator for C-string
			      if( (UInt8)argI -> arg->flags == 0x00 )
			      {
			         MemSet( charP + elSize, 1, 0x00 );
			      }
			      
			      break;
			   case 'v':
					*( (UInt32 *)*pArg ) = (UInt32)( *( (double *)argVal ) );
	       }
       		charP += elSize;
       }
   }
   else
   {
   		/* Old obselete type */
   		Int16 i, j, k;
   		
	   charP = *pArg;

	   if (nElements > 1 || argI -> arg -> kind == 's')
	   {
		   switch (argI -> arg->kind)
		   {
			   case 'i':
			   case 'n':
			   case 's':
					// Turn first four bytes of block into a pointer to the fifth byte
			      charPP = (char **)charP;
			      charP += sizeof( char * );
			      *charPP = charP;
		   }
	   }

       for (i = argI -> occ1; i < (argI -> sde1 ? argI -> occ1 + 1 : argI -> arg -> max_no_values1); ++i)
       for (j = argI -> occ2; j < (argI -> sde2 ? argI -> occ2 + 1 : argI -> arg -> max_no_values2); ++j)
       for (k = argI -> occ3; k < (argI -> sde3 ? argI -> occ3 + 1 : argI -> arg -> max_no_values3); ++k)
       {
	   		argVal = (void **) devel_address(argI -> arg, i, j, k);

		   switch(argI -> arg->kind )
		   {
		   case 'i':
		      if( (UInt8)argI -> arg->flags == 0x80 )
		      {
		         *( (Int32 *)charP ) = (Int32)( *( (double *)argVal ) );
		      }
		      else // arg->flags == 0x10
		      {
		         *( (Int16 *)charP ) = (Int16)( *( (double *)argVal ) );
		      }
		      break;
		   case 'n':
		      if( (UInt8)argI -> arg->flags == 0x40 )
		         *( (double *)charP ) = *( (double *)argVal );
		      else // arg->flags == 0x20
		         *( (float *)charP ) = (float)( *( (double *)argVal ) );
		      break;
		   case 's':
		      // Subtract 1 from nSize to get C-string size
		      // extra byte was added for null termination of string
		      // no need to subtract for single-byte string
			      if( (UInt8)argI -> arg->flags == 0x00 )
			      {
			         elSize = StrLen((char *) argVal );
			      }
			      else
			      {
			      	 elSize = 1;
			      }
		      MemMove( (void *)charP, argVal, elSize );
		      // Add terminator for C-string
		      if( (UInt8)argI -> arg->flags == 0x00 )
		         MemSet( charP + elSize, 1, 0x00 );
		      break;
		   case 'v':
				*( (UInt32 *)*pArg ) = (UInt32)( *( (double *)argVal ) );
		#if 0
		   	switch( (UInt8)arg->flags2 )
		   	{
		   	case 0x00: // int
		   		break;
		   	case 0x01: // string
		   		break;
		   	case 0x02: // float/double
		   		break;
		   	case 0x04: // date
		   		break;
		   	case 0x08: // time
		   		break;
		   	case 0x10: // database
		   		break;
		   	case 0x20: // user type
		   		break;
		   	case 0x40: // object/pointer
					*( (Int32 *)*pArg ) = (Int32)( *( (double *)argVal ) );
		//	      	arg->flags = 0x01;  // Object/Non-NULL
		   		break;
		   	default: ;
		   	}
		#endif
		      break;
		   default: ;
		   }
		   charP += elSize;
		}
    }
} // NSBPackPtrs

#if 1

#define STOREDBL(a, i, d) misc_stodbl(a, i.occ1, i.occ2, i.occ3, d) 
#define STORESTR(a, i, s) misc_stostr(&(a), i.occ1, i.occ2, i.occ3, s) 
#define ISRETURN ((PNO(op_code) == 0x71 || PNO(op_code) == 0x79 || PNO(op_code) == 0x7C) ? 1 : 0)
#define WANTSCONTEXT ((PNO(op_code) == 0x7B || PNO(op_code) == 0x7C) ? 1 : 0)


void NSBExecuteTrap( BOOL bLibTrap, UInt16 nSysLibIndex, UInt16 libID, UInt16 nProc, UInt16 nArgs, 
	UInt16 retType, UInt16 retSize, signed char *argTypes, signed char *argSizes)
{
   UInt32 err;
   Int32 int32Result;
   Int16 int16Result;
   double dblResult;
   float fplResult;
   int i;
   void *pResult = NULL;
   char **charPP;
   char work[60];
   Int16 argType;
   MemHandle argsPtrArrayHandle = NULL;
   void **argsPtrArray;
   MemHandle argsHndArrayHandle = NULL;
   VoidHand *argsHndArray;
   MemHandle argsPtrSizeHandle = NULL;
   UInt8 *argsPtrSize;
   MemHandle argsInstanceHandle = NULL;
   ArgInstance *argsInstance;
   UInt32 context;
   
   if (nArgs > 0)
   {
	   argsInstanceHandle = MemHandleNew((nArgs + ISRETURN) * sizeof(ArgInstance));

	   if (!argsInstanceHandle) ErrFatalDisplay("unable to make handle");
	   argsInstance = (ArgInstance *) MemHandleLock(argsInstanceHandle);
   }

   if (nArgs + ISRETURN + WANTSCONTEXT > 0)
   {
	   argsPtrSizeHandle = MemHandleNew((nArgs + ISRETURN + WANTSCONTEXT) * sizeof(UInt8));
	   if (!argsPtrSizeHandle) ErrFatalDisplay("unable to make handle");
	   argsPtrSize = (UInt8 *) MemHandleLock(argsPtrSizeHandle);
	   
	   argsPtrArrayHandle = MemHandleNew((nArgs + ISRETURN + WANTSCONTEXT) * sizeof(void *));
	   if (!argsPtrArrayHandle) ErrFatalDisplay("unable to make handle");
	   argsPtrArray = (void **) MemHandleLock(argsPtrArrayHandle);
    }
    
    if (nArgs + ISRETURN > 0)
    {  
	   argsHndArrayHandle = MemHandleNew((nArgs + ISRETURN) * sizeof(VoidHand));
	   if (!argsHndArrayHandle) ErrFatalDisplay("unable to make handle");
	   argsHndArray = (VoidHand *) MemHandleLock(argsHndArrayHandle);   
    }

    for( i = 0; i < nArgs + ISRETURN; i++ )
      argsHndArray[i] = NULL;
    
    /* Load the context */
    if (WANTSCONTEXT)
    {
        context = arrLibInfo[libID].clientContext;
        argsPtrSize[0] = 4;
        argsPtrArray[0] = &context;
    }
    
    /* Load the args */
    for (i = 0; i < nArgs; ++i)
    {
        argsInstance[i].arg =
      		 find_arg(&argsInstance[i].occ1, &argsInstance[i].occ2, &argsInstance[i].occ3,
      		   &argsInstance[i].sde1, &argsInstance[i].sde2, &argsInstance[i].sde3);
  		   
		argsPtrSize[i + WANTSCONTEXT] = argSizes ? argSizes[i] : 0;
		argType = argTypes ? argTypes[i] : 0;
		NSBPackPtrs(&(argsInstance[i]),
			&argsHndArray[i], &argsPtrArray[i + WANTSCONTEXT], &argsPtrSize[i + WANTSCONTEXT], argType);
    }

// Four cases:
//    External    No Return   0x70 - 112 or 0x78 - 120, or 0x7B new format
//       Stuff arguments, CallExternalLibProc
//    External    Return      0x71 - 113 or 0x79 - 121, or 0x7C new format
//       Stuff arguments, stuff side-effect (return) value, CallExternalLibProc
//    SysTrap     No Return   0x73 - 115
//       Stuff arguments, CallSystemProc
//    SysTrap     Return      0x74 - 116
//       Stuff arguments, PCallSystemProc
   switch( PNO(op_code) )
   {
	case 0x70:			// External No Return
	case 0x78:
	case 0x7B:
		err = CallExternalLibProc( nProc, nSysLibIndex, nArgs + WANTSCONTEXT, argsPtrArray, argsPtrSize );
		break;

   case 0x71:			// External Return
   	{
      ArgInstance retInstance;

      retInstance.arg =
      		 find_arg(&retInstance.occ1, &retInstance.occ2, &retInstance.occ3,
      		   &retInstance.sde1, &retInstance.sde2, &retInstance.sde3);	      
	      	      
      switch( retInstance.arg->kind )
      {
      case 'i':
         if( (UInt8)retInstance.arg->flags == 0x80 )
           pResult = &int32Result;
         else // arg->flags == 0x10
             pResult = &int16Result;
         break;
      case 'n':
         if( (UInt8)retInstance.arg->flags == 0x40 )
            pResult = &dblResult;
         else // arg->flags == 0x20
            pResult = &fplResult;
         break;
      case 'v':		// Suspect
      	 argsHndArray[nArgs] = MemHandleNew( sizeof( void * ) );
         pResult = MemHandleLock( argsHndArray[nArgs] );
         break;
      case 's':		// No longer suspect
      	// argsHndArray[nArgs] = MemHandleNew( StrLen( arg4_val ) + sizeof( char ) );
      	 // EMP 8 April 2001 -- Must allocate enough room for a reasonable return value
      	 {
      	     UInt16 size;
      	     size = StrLen((char *) devel_address(retInstance.arg,
      	     	retInstance.occ1, retInstance.occ2, retInstance.occ3)) + sizeof(char);
      	     if (size < 300) size = 300;
      	     argsHndArray[nArgs] = MemHandleNew(size);
      	 }
         pResult = MemHandleLock( argsHndArray[nArgs] );
         break;
      default: ;
		}
		argsPtrArray[nArgs] = &pResult;
      argsPtrSize[nArgs] = sizeof( void * );
      nArgs++;
      err = CallExternalLibProc( nProc, nSysLibIndex, nArgs, argsPtrArray, argsPtrSize );
      nArgs--;
      if( err == 0 )
      {
         switch( retInstance.arg->kind )
         {
			case 'i':
			if( (UInt8)retInstance.arg->flags == 0x80 )
			   dblResult = int32Result;
			else // arg->flags == 0x10
			   dblResult = int16Result;
		    STOREDBL(retInstance.arg, retInstance, &dblResult);
			break;
			 case 'n':
			    if( (UInt8)retInstance.arg->flags == 0x20 )
			       dblResult = fplResult;
		    STOREDBL(retInstance.arg, retInstance, &dblResult);
			    break;
			case 'v':		// Suspect
				dblResult = (UInt32)pResult;
		      	STOREDBL(retInstance.arg, retInstance, &dblResult);
				break;
			case 's':		// No longer suspect
				/* Unlock and relock in case it changed */
				MemHandleUnlock(argsHndArray[nArgs]);
         		pResult = MemHandleLock( argsHndArray[nArgs] );
		      	STORESTR(retInstance.arg, retInstance, pResult);
				break;
			default: ;
		   }
		}
		break;
	}
   case 0x79:		// New external return
   case 0x7C:
	   {
	      ArgInstance retInstance;
	      
	      retInstance.arg = find_arg(&retInstance.occ1, &retInstance.occ2, &retInstance.occ3,
	      		   &retInstance.sde1, &retInstance.sde2, &retInstance.sde3);	      
	      	      
	      switch(retType)
	      {
	      	case 'i':
	      	case 'I':
	      		if (2 == retSize)
	      		{
	      			pResult = &int16Result;
	      		}
	      		else if (4 == retSize)
	      		{
	      			pResult = &int32Result;
	      		}
	      		else ErrFatalDisplay("Undefined integer size");
	      		break;
	      	case 'n':
	      	case 'N':
	      		if (4 == retSize)
	      		{
	      		    pResult = &fplResult;
	      		}
	      		else if (8 == retSize)
	      		{
	      			pResult = &dblResult;
	      		}
		      	else ErrFatalDisplay("Undefined float size");
	      		break;
	      	case 's':
	      	case 'S':
	      	case 'c':
	      	case 'C':
	      		{
		      	     UInt16 size;
		      	     size = StrLen((char *) devel_address(retInstance.arg,
		      	     	retInstance.occ1, retInstance.occ2, retInstance.occ3)) + sizeof(char);
		      	     if (size < 300) size = 300;
	      			 argsHndArray[nArgs] = MemHandleNew(size + sizeof(char *));
	      			 pResult = MemHandleLock(argsHndArray[nArgs]);
	      			 *((char **) pResult) = ((char *) pResult) + 4;
	      			 pResult = (void *) (((char *) pResult) + 4);
	      		}
	      		break;
	      	case 'v':	// Do what here?
	      	case 'V':
	      		break;
	      	default:
	      		ErrFatalDisplay("Unsupported return type");
	      }
	      
	      argsPtrArray[nArgs + WANTSCONTEXT] = &pResult;
	      argsPtrSize[nArgs + WANTSCONTEXT] = sizeof( void * );
	      nArgs++;
	      err = CallExternalLibProc( nProc, nSysLibIndex, nArgs + WANTSCONTEXT, argsPtrArray, argsPtrSize );
	      nArgs--;
	      
	      if( err == 0 )
	      {
		      switch(retType)
		      {
		      	case 'i':
		      	case 'I':
		      		if (2 == retSize)
		      		{
		      			dblResult = int16Result;
		      		}
		      		else if (4 == retSize)
		      		{
		      			dblResult = int32Result;
		      		}
		      		else ErrFatalDisplay("Undefined integer size");
		      		
		      		if (retInstance.arg -> kind == 'i' || retInstance.arg -> kind == 'n')
		      		{
		      			STOREDBL(retInstance.arg, retInstance, &dblResult);
		      		}
		      		else ErrFatalDisplay("Type mismatch on return from external library");
		      		break;
		      	case 'n':
		      	case 'N': 
		      		if (4 == retSize)
		      		{
		      		    dblResult = fplResult;
		      		}
		      		
		      		if (retInstance.arg -> kind == 'i' || retInstance.arg -> kind == 'n')
		      		{
		      			STOREDBL(retInstance.arg, retInstance, &dblResult);
		      		}
		      		else ErrFatalDisplay("Type mismatch on return from external library");
		      		break;
		      	case 's':
		      	case 'S':
		      	case 'c':
		      	case 'C':
		      		if (retInstance.arg -> kind == 's')
		      		{
						MemHandleUnlock(argsHndArray[nArgs]);
		         		pResult = MemHandleLock( argsHndArray[nArgs] );
		         		pResult = * ((char **) pResult);
	      			 	//pResult = (void *) (((char *) pResult) + 4);
		      			STORESTR(retInstance.arg, retInstance, pResult);
		      		}
		      		else ErrFatalDisplay("Type mismatch on return from external library");
		      		break;
		      	case 'v':	// Do what here?
		      	case 'V':
		      		break;
		      	default:
		      		// DIKEO put in the other types later
		      		ErrFatalDisplay("Unsupported return type");
		      }
			}
			break;
	    }
	case 0x73:			// SysTrap  No Return
		err = CallSystemProc( nProc, nArgs, argsPtrArray, argsPtrSize );
		break;

   case 0x74:			// SysTrap  Return
	  {
	      ArgInstance retInstance;

	      retInstance.arg = find_arg(&retInstance.occ1, &retInstance.occ2, &retInstance.occ3,
	      		   &retInstance.sde1, &retInstance.sde2, &retInstance.sde3);	      
	      switch( retInstance.arg->kind )
	      {
	      case 'i':
	      	if( (UInt8)retInstance.arg->flags == 0x80 )	// Int
	      	{
				int32Result = CallSystemProc( nProc, nArgs, argsPtrArray, argsPtrSize );
				dblResult = int32Result;
			}
			else								// Short
			{
	         	int16Result = CallSystemProc( nProc, nArgs, argsPtrArray, argsPtrSize );
		        dblResult = int16Result;
			}
	      	STOREDBL(retInstance.arg, retInstance, &dblResult);
			break;
	      case 'n':
	         if( (UInt8)retInstance.arg->flags == 0x40 )	// Double
	         {
	            pResult = PCallSystemProc( nProc, nArgs, argsPtrArray, argsPtrSize );
	            dblResult = *(double *)pResult;
	         }
	         else								// Float
	         {
	            err = CallSystemProc( nProc, nArgs, argsPtrArray, argsPtrSize );
	            dblResult = (float)err;
	         }
	         STOREDBL(retInstance.arg, retInstance, &dblResult);
	         break;
	      case 'v':
	      	pResult = PCallSystemProc( nProc, nArgs, argsPtrArray, argsPtrSize );
	      	dblResult = (UInt32)pResult;
	      	STOREDBL(retInstance.arg, retInstance, &dblResult);

	        break;
	      case 's':
	         pResult = PCallSystemProc( nProc, nArgs, argsPtrArray, argsPtrSize );
	         STORESTR(retInstance.arg, retInstance, pResult);

	         break;
	      default: ;
	      }
       }
   default: ;
   }

	// This is where we restore pointer types to ensure that side effect return
	// values are actually returned
	
    for (i = 0; i < nArgs; ++i)
    {
		ArgInstance *argI = &(argsInstance[i]);
		Int16 argSize;
    	if (argTypes)
    	{
    		/* New style call */
    		argType = argTypes[i];
    		argSize = argSizes[i];
    	}
    	else
    	{
    		/* Old style call */
		   UInt32 nElements = 1;
		   
		   /* Determine the number of elements.  If 1, reduces to a scalar */
		   if (!argI -> sde1) nElements *= argI -> arg -> max_no_values1;
		   if (!argI -> sde2) nElements *= argI -> arg -> max_no_values2;
		   if (!argI -> sde3) nElements *= argI -> arg -> max_no_values3;
		   
		   argType = 0;
		   if (nElements > 1)
		   {
		   		if (argI -> arg->kind == 'i')
		   		{
					argType = 'I';
			         if( (UInt8)argI -> arg->flags == 0x80 )
			           argSize = 4;
			         else // arg->flags == 0x10
			           argSize = 2;
		   		}
		   		else if (argI -> arg->kind == 'n')
		   		{
		   			argType = 'N';
			         if( (UInt8)argI -> arg->flags == 0x40 )
			            argSize = 8;
			         else // arg->flags == 0x20
			            argSize = 4;;
		   		}
		   }
    	}
    	
    	if (argType == 'I')
    	{
			Int16 ii, jj, kk;
			
			MemHandleUnlock(argsHndArray[i]);
			pResult = MemHandleLock(argsHndArray[i + WANTSCONTEXT]);
			pResult = * ((char **) pResult);
			for (ii = argI -> occ1; ii < (argI -> sde1 ? argI -> occ1 + 1 : argI -> arg -> max_no_values1); ++ii)
			for (jj = argI -> occ2; jj < (argI -> sde2 ? argI -> occ2 + 1 : argI -> arg -> max_no_values2); ++jj)
			for (kk = argI -> occ3; kk < (argI -> sde3 ? argI -> occ3 + 1 : argI -> arg -> max_no_values3); ++kk)
			{
			    if (argSize == 4)
			    {
			        dblResult = *(Int32 *) pResult;
			        pResult = (void *) (sizeof(Int32) + (char *) pResult);
			    }
			    else
			    {
			        dblResult = *(Int16 *) pResult;
			        pResult = (void *) (sizeof(Int16) + (char *) pResult);
			    }
			    misc_stodbl(argI -> arg, ii, jj, kk, &dblResult);
			}
		}
		else if (argType == 'N')
		{
			Int16 ii, jj, kk;
			
			MemHandleUnlock(argsHndArray[i]);
			pResult = MemHandleLock(argsHndArray[i + WANTSCONTEXT]);
			pResult = * ((char **) pResult);

			for (ii = argI -> occ1; ii < (argI -> sde1 ? argI -> occ1 + 1 : argI -> arg -> max_no_values1); ++ii)
			for (jj = argI -> occ2; jj < (argI -> sde2 ? argI -> occ2 + 1 : argI -> arg -> max_no_values2); ++jj)
			for (kk = argI -> occ3; kk < (argI -> sde3 ? argI -> occ3 + 1 : argI -> arg -> max_no_values3); ++kk)
			{
			    if (argSize == 4)
			    {
			        dblResult = *(float*) pResult;
			        pResult = (void *) (sizeof(float) + (char *) pResult);
			    }
			    else
			    {
			        dblResult = *(double*) pResult;
			        pResult = (void *) (sizeof(double) + (char *) pResult);
			    }
			     misc_stodbl(argI -> arg, ii, jj, kk, &dblResult);
			}
		}
		else if(argsInstance[i].arg->kind == 's' ||
				argsInstance[i].arg->kind == 'S')
		{
			Int16 ii, jj, kk;
			
			MemHandleUnlock(argsHndArray[i]);
     		pResult = MemHandleLock( argsHndArray[i + WANTSCONTEXT] );
     		// pResult = (void *) (((char *) pResult) + 4);
     		pResult = * ((char **) pResult);
     		
			for (ii = argI -> occ1; ii < (argI -> sde1 ? argI -> occ1 + 1 : argI -> arg -> max_no_values1); ++ii)
			for (jj = argI -> occ2; jj < (argI -> sde2 ? argI -> occ2 + 1 : argI -> arg -> max_no_values2); ++jj)
			for (kk = argI -> occ3; kk < (argI -> sde3 ? argI -> occ3 + 1 : argI -> arg -> max_no_values3); ++kk)
			{
				// DIKEO array will only work for bytes
				 misc_stostr(&(argI -> arg), ii, jj, kk, pResult);
				 pResult = (void *) (1 + (char *) pResult);
		    }
		}
		else if(argsInstance[i].arg->kind == 'v' ||
				argsInstance[i].arg->kind == 'V')
		{
			dblResult = ( *(UInt32 *)argsPtrArray[i + WANTSCONTEXT] );
		    STOREDBL(argsInstance[i].arg, argsInstance[i], &dblResult);
		}
    }
    
	// Unlock and Free memory handles
	for( i = 0; i < nArgs + ISRETURN; i++ )
	{
		if( argsHndArray[i] == NULL )
			break;
		MemHandleUnlock( argsHndArray[i] );
		MemHandleFree( argsHndArray[i] );
	}
	
	
	if (nArgs + ISRETURN + WANTSCONTEXT > 0)
	{
	    MemHandleUnlock(argsPtrSizeHandle);
	    MemHandleFree(argsPtrSizeHandle);
	    MemHandleUnlock(argsPtrArrayHandle);
	    MemHandleFree(argsPtrArrayHandle);
	}
	
	if (nArgs + ISRETURN > 0)
	{
	    MemHandleUnlock(argsHndArrayHandle);
	    MemHandleFree(argsHndArrayHandle);
	}

	if (nArgs > 0)
	{
		MemHandleUnlock(argsInstanceHandle);
		MemHandleFree(argsInstanceHandle);
	}
#undef kMaxArgs
} // NSBExecuteTrap
#endif



void verb_external()
{
   UInt16 nLibID = find_integer();
   UInt16 nProc = 0xA804 + find_integer();
   UInt16 nArgs = find_integer();
   NSBExecuteTrap( true, arrLibInfo[nLibID].nSysLibIndex,nLibID, nProc, nArgs, 0, 0, 0, 0 );
} // verb_external

void verb_newExternal()
{
   UInt16 nLibID = find_integer();
   UInt16 nProc = 0xA804 + find_integer();
   UInt16 nArgs = find_integer();
   UInt16 retType = 0, retSize = 0;
   signed char *argTypes = 0, *argSizes = 0;
      
   if (0x79 == PNO(op_code) || 0x7C == PNO(op_code))
   {
     retType = find_char();
     retSize = find_char();
   }
   if (0x79 == PNO(op_code) || 0x78 == PNO(op_code) ||
       0x7B == PNO(op_code) || 0x7C == PNO(op_code))
   {
      if (nArgs > 0)
      {
          UInt16 k;
	      argTypes = (signed char *) MemPtrNew(nArgs);
	      argSizes = (signed char *) MemPtrNew(nArgs);
	      for (k = 0; k < nArgs; ++k)
	      {
	          argTypes[k] = find_char();
	          argSizes[k] = find_char();
	      }
      }
   }
   NSBExecuteTrap( true, arrLibInfo[nLibID].nSysLibIndex, nLibID, nProc, nArgs, retType, retSize, argTypes, argSizes);

   if (argTypes) MemPtrFree(argTypes);
   if (argSizes) MemPtrFree(argSizes);

} // verb_external

void verb_sysTrap()
{
	UInt16 nProc = 0xA000 + find_integer();
	UInt16 nArgs = find_integer();
	
	NSBExecuteTrap( false, (UInt16)0, 0, nProc, nArgs, 0, 0, 0, 0);
} // verb_sysTrap

void verb_loadLibrary()
{
    // EMP modified to do libraries as resources
   char strPrcName[32];
   char strMsg[60];
   Err error;
   LocalID lID;
   ULong crtr;
   ULong typeP; //Nicoliev
   unsigned nLibID = find_integer();
   UInt16 resID;
   
   find_arg_1();
   StrCopy( strPrcName, arg1_val);
      
   if (0x7A == PNO(op_code))
   {
       resID = find_integer();
   }

   // It's already open, so let's just leave
   if( arrLibInfo[nLibID].nSysLibIndex != 0 )
      return;


   if (0x7A == PNO(op_code))
   {
         /* Get the lib as a resource */
         MemHandle codeRscH = DmGetResource('libr', resID);
         if (codeRscH)
         {
            SysLibEntryProcPtr codeRscP;
                           
            codeRscP = MemHandleLock(codeRscH);
            *((UInt16 *)&arrLibInfo[nLibID]) = sysInvalidRefNum;
            error = SysLibInstall(codeRscP, (UInt16 *)&arrLibInfo[nLibID]);
            MemHandleUnlock(codeRscH);
            DmReleaseResource(codeRscH);
            arrLibInfo[nLibID].bLoaded = true;
         }
         else
         {
            StrPrintF(strMsg, "Unable to find lib rsrc %d\n", resID);
            misc_text_abort( strMsg );
         }
   }
   else
   {

       error = SysLibFind( strPrcName, (UInt16 *)&arrLibInfo[nLibID] );
       if( error )
       {
          // Lib isn't already loaded, so let's find it
          // First we have to get 4-char creator code
          // and 4 char type code  //Nicoliev
          lID = DmFindDatabase( bp.cardNo, strPrcName );
          if( lID )
              error = DmDatabaseInfo( bp.cardNo, lID, 0, 0, 0, 0, 0, 0, 0, 0, 0, &typeP, &crtr );

          // Now try to load it
          if( !error )
             //error = SysLibLoad( 'libr', crtr, (UIntPtr)&arrLibInfo[nLibID] );   //Nicoliev
             error = SysLibLoad( typeP, crtr, (UIntPtr)&arrLibInfo[nLibID] );     //Nicoliev

          // All is not well, if error.  Abort
          if( error )
          {
             //char cr[5];
             //cr[4] = 0;
             //MemMove(cr, &crtr, 4);
             // StrPrintF( strMsg, "Unable to find lib %s.prc", cr );
                StrPrintF( strMsg, "Unable to find lib %s.prc", strPrcName );
                misc_text_abort( strMsg );
          }
          arrLibInfo[nLibID].bLoaded = true;
       }
       else
          arrLibInfo[nLibID].bLoaded = false;
   }
   // Trying to open the library, some error here though...
   // SysLibOpen is a reserved system call.
   // Now we get tricky, to make the MathLibbers happy

	if( StrCaselessCompare( "mathlib", strPrcName ) == 0 )
	{
		error = MathLibOpen( arrLibInfo[nLibID].nSysLibIndex, MathLibVersion );
		arrLibInfo[nLibID].isMathLib = 1;
	}
	else
	{
	// EMP changed for CW 9	error = SysLibOpen( arrLibInfo[nLibID].nSysLibIndex, );
	    error = CW9LibOpen(arrLibInfo[nLibID].nSysLibIndex, 
	        &(arrLibInfo[nLibID].clientContext));
		arrLibInfo[nLibID].isMathLib = 0;
	}

   if( error )
   {
      StrPrintF( strMsg, "Unable to open %s.prc", strPrcName );
      misc_text_abort( strMsg );
   }
} // verb_loadLibrary

void verb_appLaunch()
{
	Int16 cardNo, err;
	UInt16 launchCmd;
	UInt32 ret;
	double dblRet;
	LocalID pgm;
	char work[100];

	cardNo = (Int16)( *(double *)arg1_val);
	pgm = DmFindDatabase( cardNo, arg2_val );
	launchCmd = (UInt16)( *(double *)arg3_val );

	if( pgm == 0 )
	{
		StrPrintF( work, "Can't find program '%s'", arg2_val );
		misc_errmsg( work );
		return;
	}

	err = SysAppLaunch( cardNo, pgm, 0, launchCmd, arg5_val, &ret );
 	if( err != 0 )
 	{
 		StrPrintF( work, "Unable to launch program '%s' with command '%d'", arg2_val, launchCmd );
 		misc_errmsg( work );
 		return;
 	}
 	if ( ret > 0x7FFFFFFF )
 	{        // value too large for NSB to handle?
    	ret = (ret - 0xFFFF0000);     // Yes, then thin it down.
 	}

	dblRet = ret;
	store4( &dblRet );
} // verb_appLaunch

#endif _NSBASIC_C_
