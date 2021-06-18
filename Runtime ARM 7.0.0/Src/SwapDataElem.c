// Automatically generated from sud.pl

#include "PACEInterfaceLib.h"
#include <PalmCompatibility.h>
#include "copy.h"
#include "NSBPNOShared.h"
#include "NSBPNOGlue.h"

void SwapDataElem (struct dataelem *pnoP)
{
    register UInt32 t32;
    register UInt16 t16;
    DoubleExchange d;

    if (!pnoP) return;

    t16 = (UInt16) (pnoP -> length);
    t16 = ByteSwap16(t16);
    pnoP -> length = (UInt16) t16;
    t16 = (UInt16) (pnoP -> dgt_bef);
    t16 = ByteSwap16(t16);
    pnoP -> dgt_bef = (Int16) t16;
    t16 = (UInt16) (pnoP -> dgt_aft);
    t16 = ByteSwap16(t16);
    pnoP -> dgt_aft = (Int16) t16;
    t16 = (UInt16) (pnoP -> cur_no_values);
    t16 = ByteSwap16(t16);
    pnoP -> cur_no_values = (UInt16) t16;
    t16 = (UInt16) (pnoP -> max_no_values1);
    t16 = ByteSwap16(t16);
    pnoP -> max_no_values1 = (UInt16) t16;
    t16 = (UInt16) (pnoP -> max_no_values2);
    t16 = ByteSwap16(t16);
    pnoP -> max_no_values2 = (UInt16) t16;
    t16 = (UInt16) (pnoP -> max_no_values3);
    t16 = ByteSwap16(t16);
    pnoP -> max_no_values3 = (UInt16) t16;
    t16 = (UInt16) (pnoP -> tbl_no);
    t16 = ByteSwap16(t16);
    pnoP -> tbl_no = (UInt16) t16;
    t16 = (UInt16) (pnoP -> firstData);
    t16 = ByteSwap16(t16);
    pnoP -> firstData = (UInt16) t16;

}
