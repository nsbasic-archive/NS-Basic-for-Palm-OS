// Automatically generated from sud.pl

#include "PACEInterfaceLib.h"
#include <PalmCompatibility.h>
#include "NSBPNOShared.h"
#include "copy.h"
#include "NSBPNOGlue.h"

void SwapCodeBlock (struct codeBlock *pnoP)
{
    register UInt32 t32;
    register UInt16 t16;
    DoubleExchange d;

    if (!pnoP) return;

    t32 = (UInt32) (pnoP -> prevCodePtr);
    t32 = ByteSwap32(t32);
    pnoP -> prevCodePtr = (VoidPtr) t32;
    t32 = (UInt32) (pnoP -> p3);
    t32 = ByteSwap32(t32);
    pnoP -> p3 = (VoidPtr) t32;
    t32 = (UInt32) (pnoP -> h3);
    t32 = ByteSwap32(t32);
    pnoP -> h3 = (VoidHand) t32;
    t32 = (UInt32) (pnoP -> paragTbl);
    t32 = ByteSwap32(t32);
    pnoP -> paragTbl = (VoidPtr) t32;
    t32 = (UInt32) (pnoP -> codePtr);
    t32 = ByteSwap32(t32);
    pnoP -> codePtr = (VoidPtr) t32;
    t32 = (UInt32) (pnoP -> newp3);
    t32 = ByteSwap32(t32);
    pnoP -> newp3 = (VoidPtr) t32;
    t32 = (UInt32) (pnoP -> newh3);
    t32 = ByteSwap32(t32);
    pnoP -> newh3 = (VoidHand) t32;
    t16 = (UInt16) (pnoP -> instr_ctr);
    t16 = ByteSwap16(t16);
    pnoP -> instr_ctr = (UInt16) t16;
    t16 = (UInt16) (pnoP -> id);
    t16 = ByteSwap16(t16);
    pnoP -> id = (UInt16) t16;
    t16 = (UInt16) (pnoP -> numberParas);
    t16 = ByteSwap16(t16);
    pnoP -> numberParas = (Int16) t16;
    t16 = (UInt16) (pnoP -> oldOffset);
    t16 = ByteSwap16(t16);
    pnoP -> oldOffset = (UInt16) t16;
    t16 = (UInt16) (pnoP -> argsOffset);
    t16 = ByteSwap16(t16);
    pnoP -> argsOffset = (UInt16) t16;
    t16 = (UInt16) (pnoP -> functionLinkNo);
    t16 = ByteSwap16(t16);
    pnoP -> functionLinkNo = (Int16) t16;
    t16 = (UInt16) (pnoP -> offset);
    t16 = ByteSwap16(t16);
    pnoP -> offset = (UInt16) t16;
    t16 = (UInt16) (pnoP -> cur_stmt_no);
    t16 = ByteSwap16(t16);
    pnoP -> cur_stmt_no = (UInt16) t16;
    t16 = (UInt16) (pnoP -> subFuncEntry_stmt_no);
    t16 = ByteSwap16(t16);
    pnoP -> subFuncEntry_stmt_no = (UInt16) t16;

}
