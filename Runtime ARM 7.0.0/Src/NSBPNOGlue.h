/**
    NSBPNOGlue.h
    Glue for 68K functions fron PNO, plus some internal prototypes
    Eric Pepke
    23 Sep 2003
  */

#ifdef __MC68K__
#else
#include "PACEInterfaceLib.h"
#include <endianutils.h>
#endif

#include "PALMCompatibility.h"

typedef void (*VerbType)(PNOBlock *);

CDECL double SwapDouble(double in);
CDECL double ReadUnaligned64(char *addr);
CDECL void WriteUnaligned64(char *addr, double val);
CDECL void SwapUserData(PNOBlock *pnoP);

CDECL Int16 Glue_codeexec2(PNOBlock *pnoP);
CDECL void GlueErrThrow(PNOBlock *pnoP, UInt16 i);

CDECL ControlStyleType GlueCtlGlueGetControlStyle(PNOBlock *pnoP, ControlType *ctlP);
CDECL FontID GlueFrmGlueGetLabelFont(PNOBlock *pnoP, const FormType *formP, UInt16 labelID);
CDECL void Glue_commonSignatureDisplay(PNOBlock *pnoP, FormPtr frmPtr, char *data, Int16 controlid);
CDECL void Glue_commonErase(PNOBlock *pnoP, FormPtr frmPtr, Int16 controlid);
CDECL void Glue_FlpFToA(PNOBlock *pnoP, double d, char *ch);
CDECL double Glue_FlpAToF(PNOBlock *pnoP, char *ch);
CDECL double GluePow(PNOBlock *pnoP, double a, double b);
CDECL void Glue_chkMathLibOpen(PNOBlock *pnoP);
CDECL Int32 Glue_SerialReceiveCheck(PNOBlock *pnoP, UInt16 serRef);

CDECL double GlueACos(PNOBlock *pnoP, double a);
CDECL double GlueASin(PNOBlock *pnoP, double a);
CDECL double GlueATan(PNOBlock *pnoP, double a);
CDECL double GlueCos(PNOBlock *pnoP, double a);
CDECL double GlueSin(PNOBlock *pnoP, double a);
CDECL double GlueTan(PNOBlock *pnoP, double a);
CDECL double GlueCosH(PNOBlock *pnoP, double a);
CDECL double GlueSinH(PNOBlock *pnoP, double a);
CDECL double GlueTanH(PNOBlock *pnoP, double a);
CDECL double GlueACosH(PNOBlock *pnoP, double a);
CDECL double GlueASinH(PNOBlock *pnoP, double a);
CDECL double GlueATanH(PNOBlock *pnoP, double a);
CDECL double GlueExp(PNOBlock *pnoP, double a);
CDECL double GlueLog(PNOBlock *pnoP, double a);
CDECL double GlueLog10(PNOBlock *pnoP, double a);
CDECL double GlueSqrt(PNOBlock *pnoP, double a);
CDECL double GlueCbrt(PNOBlock *pnoP, double a);
CDECL double GluePow(PNOBlock *pnoP, double a, double b);
CDECL double GlueATan2(PNOBlock *pnoP, double a, double b);
CDECL UInt32 Glue_DateToDays(PNOBlock *pnoP, UInt16 year, UInt16 month, UInt16 day);

CDECL void Glue_commonStartCapture(PNOBlock *pnoP, FormPtr frmPtr, Int16 controlid);
CDECL void Glue_commonErase(PNOBlock *pnoP, FormPtr frmPtr, Int16 controlid);
CDECL void Glue_commonSignatureDisplay(PNOBlock *pnoP, FormPtr frmPtr, char *data, Int16 controlid);
CDECL void Glue_commonEndCapture(PNOBlock *pnoP, FormPtr frmPtr,
	struct dataelem **de, Int16 occ1, Int16 occ2, Int16 occ3, Int16 controlid);

#define BASIS   ((long) (&SwapDouble))
 

