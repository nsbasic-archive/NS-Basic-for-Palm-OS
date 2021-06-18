/**
    NSBPNOGlue.c
    Glue for 68K functions
    Eric Pepke
    23 Sep 2003
  */
  
  
#include "PACEInterfaceLib.h"
#include "PALMCompatibility.h"
#include "NSBPNOShared.h"
#include "copy.h"
#include "NSBPNOGlue.h"


double SwapDouble(double in)
{
    DoubleExchange d;
    unsigned long temp;
    
    d.d = in;
    temp = d.i.high;
    d.i.high = ByteSwap32(d.i.low);
    d.i.low = ByteSwap32(temp);
    
    return d.d;
}

double ReadUnaligned64(char *addr)
{
    DoubleExchange d;
    
    d.i.low = ReadUnaligned32(addr);
    addr += 4;
    d.i.high = ReadUnaligned32(addr);
    return d.d;
}

void WriteUnaligned64(char *addr, double val)
{
    DoubleExchange d;
    
    d.d = val;
    WriteUnaligned32(addr, d.i.low);
    addr += 4;
    WriteUnaligned32(addr, d.i.high);
}

void Glue_chkMathLibOpen(PNOBlock *pnoP)
{
    char buf[sizeof(UInt16)];
    char *b;
    void *p;
    unsigned short s;
    unsigned long l;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
    
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);

    p = PNO(chkMathLibOpen);
    p = (void *)ByteSwap32((long)p);
    
    
    SwapUserData(pnoP);
    l = ((call68KFuncP)(emulStateP, 
        (unsigned long) p, 
        buf,
        0));
    SwapUserData(pnoP);
}

void Glue_FlpFToA(PNOBlock *pnoP, double d, char *ch)
{
    char buf[sizeof(double) + sizeof(char *)];
    char *b;
    void *p;
    unsigned short s;
    unsigned long l;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
    
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);

    p = PNO(flpftoa);
    p = (void *)ByteSwap32((long)p);
    
    b = buf;

    WriteUnaligned64(b, d);
    b += sizeof(double);

    l = ByteSwap32(ch);
    *(unsigned long *) b = l;

    l = ((call68KFuncP)(emulStateP, 
        (unsigned long) p, 
        buf,
        sizeof(buf)));
}

Int32 Glue_SerialReceiveCheck(PNOBlock *pnoP, UInt16 serRef)
{
    char buf[sizeof(UInt16)];
    char *b;
    void *p;
    unsigned short s;
    long l;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
    
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);

    p = PNO(serialreceivecheck);
    p = (void *)ByteSwap32((long)p);
    
    b = buf;
    * (UInt16 *)buf = ByteSwap16(serRef);

    l = ((call68KFuncP)(emulStateP, 
        (unsigned long) p, 
        buf,
        sizeof(buf)));
        
    return l;
}

Int16 Glue_WinGetCoordinateSystem(PNOBlock *pnoP)
{
    char buf[sizeof(UInt16)];
    char *b;
    void *p;
    unsigned short s;
    unsigned long l;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
    
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);

    p = PNO(wingetcoordinatesystem);
    p = (void *)ByteSwap32((long)p);
    
    l = ((call68KFuncP)(emulStateP, 
        (unsigned long) p, 
        buf,
        0));

    return l;
}

UInt32 Glue_DateToDays(PNOBlock *pnoP, UInt16 year, UInt16 month, UInt16 day)
{
    char buf[3 * sizeof(UInt16)];
    char *b;
    void *p;
    unsigned short s;
    unsigned long l;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
    
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);

    p = PNO(datetodays);
    p = (void *)ByteSwap32((long)p);

    b = buf;
    s = year;
    * (unsigned short *)b = ByteSwap16(s);
    b += sizeof(UInt16);

    s = month;
    * (unsigned short *)b = ByteSwap16(s);
    b += sizeof(UInt16);

    s = day;
    * (unsigned short *)b = ByteSwap16(s);
    b += sizeof(UInt16);

    l = ((call68KFuncP)(emulStateP, 
        (unsigned long) p, 
        buf,
        sizeof(buf)));
    return l;
}


double Glue_FlpAToF(PNOBlock *pnoP, char *ch)
{
    char buf[sizeof(double *) + sizeof(char *)];
    char *b;
    void *p;
    double d;
    unsigned short s;
    unsigned long l;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
    
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);

    p = PNO(flpatof);
    p = (void *)ByteSwap32((long)p);
    
    b = buf;

    l = ByteSwap32(ch);
    *(unsigned long *) b = l;
    
    b += sizeof(char *);
    
    l = ByteSwap32(&d);
    *(unsigned long *) b = l;
    
    l = ((call68KFuncP)(emulStateP, 
        (unsigned long) p, 
        buf,
        sizeof(buf)));
        
    return SwapDouble(d);
}

void Glue_CallFunction(PNOBlock *pnoP)
{
    char buf[2];
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
    void *p;
    
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);

    p = PNO(function_doit_from_PNO);
    p = (void *)ByteSwap32((long)p);
    
    SwapUserData(pnoP);
    ((call68KFuncP)(emulStateP, 
        (unsigned long) p, 
        buf,
        0));
    SwapUserData(pnoP);
}

void Glue_commonStartCapture(PNOBlock *pnoP, FormPtr frmPtr, Int16 controlid)
{
    char buf[sizeof(FormPtr) + sizeof(Int16)];
    char *b;
    void *p;
    unsigned short s;
    unsigned long l;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
    
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);

    p = PNO(commonStartCapture);
    p = (void *)ByteSwap32((long)p);
    
    b = buf;

    l = (unsigned long) frmPtr;
    *(unsigned long *)b = ByteSwap32(l);
    b += sizeof(unsigned long);

    s = controlid;
    *(unsigned short *)b = ByteSwap16(s);

    SwapUserData(pnoP);
    l = ((call68KFuncP)(emulStateP, 
        (unsigned long) p, 
        buf,
        sizeof(buf)));
    SwapUserData(pnoP);
}

void Glue_commonErase(PNOBlock *pnoP, FormPtr frmPtr, Int16 controlid)
{
    char buf[sizeof(FormPtr) + sizeof(Int16)];
    char *b;
    void *p;
    unsigned short s;
    unsigned long l;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
    
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);

    p = PNO(commonErase);
    p = (void *)ByteSwap32((long)p);
    
    b = buf;

    l = (unsigned long) frmPtr;
    *(unsigned long *)b = ByteSwap32(l);
    b += sizeof(unsigned long);

    s = controlid;
    *(unsigned short *)b = ByteSwap16(s);

    SwapUserData(pnoP);
    l = ((call68KFuncP)(emulStateP, 
        (unsigned long) p, 
        buf,
        sizeof(buf)));
    SwapUserData(pnoP);

}

void Glue_commonSignatureDisplay(PNOBlock *pnoP, FormPtr frmPtr, char *data, Int16 controlid)
{
    char buf[sizeof(FormPtr) + sizeof(char *) + sizeof(Int16)];
    char *b;
    void *p;
    unsigned short s;
    unsigned long l;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
    
    
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);

    p = PNO(commonSignatureDisplay);
    p = (void *)ByteSwap32((long)p);
    
    b = buf;

    l = (unsigned long) frmPtr;
    *(unsigned long *)b = ByteSwap32(l);
    b += sizeof(unsigned long);

    l = (unsigned long) data;
    *(unsigned long *)b = ByteSwap32(l);
    b += sizeof(unsigned long);

    s = controlid;
    *(unsigned short *)b = ByteSwap16(s);

    SwapUserData(pnoP);

    l = ((call68KFuncP)(emulStateP, 
        (unsigned long) p, 
        buf,
        sizeof(buf)));

    SwapUserData(pnoP);

}

void Glue_commonEndCapture(PNOBlock *pnoP, FormPtr frmPtr,
	struct dataelem **de, Int16 occ1, Int16 occ2, Int16 occ3, Int16 controlid)
{
    char buf[sizeof(FormPtr) + sizeof(Int16) + sizeof(void *) + 3 * sizeof(Int16)];
    char *b;
    void *p;
    unsigned short s;
    unsigned long l;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
    
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);

    p = PNO(commonEndCapture);
    p = (void *)ByteSwap32((long)p);
    
    b = buf;

    l = (unsigned long) frmPtr;
    *(unsigned long *)b = ByteSwap32(l);
    b += sizeof(unsigned long);
    
    l = (unsigned long) de;
    *(unsigned long *)b = ByteSwap32(l);
    b += sizeof(unsigned long);
    
    s = occ1;
    *(unsigned short *)b = ByteSwap16(s);
    b += sizeof(Int16);

    s = occ2;
    *(unsigned short *)b = ByteSwap16(s);
    b += sizeof(Int16);

    s = occ3;
    *(unsigned short *)b = ByteSwap16(s);
    b += sizeof(Int16);

    s = controlid;
    *(unsigned short *)b = ByteSwap16(s);

    SwapUserData(pnoP);
    l = ((call68KFuncP)(emulStateP, 
        (unsigned long) p, 
        buf,
        sizeof(buf)));
    SwapUserData(pnoP);
}

void Glue_setupADataelem(PNOBlock *pnoP, UInt16 de_no)
{
    char buf[sizeof(UInt16)];
    char *b;
    void *p;
    unsigned short s;
    unsigned long l;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
    
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);

    p = PNO(setupADataelem);
    p = (void *)ByteSwap32((long)p);
    
    b = buf;

    s = de_no;
    *(unsigned short *)b = ByteSwap16(s);

    SwapUserData(pnoP);
    l = ((call68KFuncP)(emulStateP, 
        (unsigned long) p, 
        buf,
        sizeof(buf)));
    SwapUserData(pnoP);

}

void GlueErrThrow(PNOBlock *pnoP, UInt16 i)
{
    char buffer[sizeof(MemHandle)];
    char *b;
    unsigned short s;
    unsigned long l;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
    
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);
    
    s = (unsigned short) i;
    b = buffer;
    *(unsigned short *)b = ByteSwap16(s);
    
    ((call68KFuncP)(emulStateP, 
        PceNativeTrapNo(sysTrapErrThrow),
        buffer,
        sizeof(buffer)));
}

OutOfMemory(int i)
{
    char ch[40];
    StrIToA(strcpy(ch, "Out of memory "), i);
    SysFatalAlert(ch);
}

#include "PNOVerbGlue.c"

ControlStyleType GlueCtlGlueGetControlStyle(PNOBlock *pnoP, ControlType *ctlP)
{
    char buf[sizeof(ControlType *)];
    char *b;
    void *p;
    unsigned long l;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
    
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);

    p = PNO(CtlGlueGetControlStyle);
    p = (void *)ByteSwap32((long)p);

    b = buf;
    l = (unsigned long) ctlP;
    l = ByteSwap32(l);
    * (unsigned long *)b = l;

    l = ((call68KFuncP)(emulStateP, 
        (unsigned long) p, 
        buf,
        sizeof(buf)));
	return l;
}

FontID GlueFrmGlueGetLabelFont(PNOBlock *pnoP, const FormType *formP, UInt16 labelID)
{
    char buf[sizeof(FormType *) + sizeof(UInt16)];
    char *b;
    void *p;
    unsigned long l;
    unsigned short s;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
    
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);

    p = PNO(FrmGlueGetLabelFont);
    p = (void *)ByteSwap32((long)p);
 
    b = buf;
    l = (unsigned long) formP;
    l = ByteSwap32(l);
    *(unsigned long *)b = l;
    b += sizeof(unsigned long);
    
    s = labelID;
    s = ByteSwap16(s);
    *(UInt16 *)b = s;
  
    l = ((call68KFuncP)(emulStateP, 
        (unsigned long) p, 
        buf,
        sizeof(buf)));

	return l;
}

Int16 Glue_codeexec2(PNOBlock *pnoP)
{
    char buf[sizeof(unsigned short) + sizeof(unsigned long)];
    char *b;
    void *p;
    unsigned short s;
    unsigned long l;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
    
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);

    p = PNO(codeexec);
    p = (void *)ByteSwap32((long)p);

    b = buf;
    s = PNO(objId);
    //s = ByteSwap16(s);
    *(unsigned short *)b = s;
    b += sizeof(unsigned short);
    l = PNO(offset);
    l = ByteSwap32(l);
    WriteUnaligned32(b, l);
    b += sizeof(unsigned long);

    l = ((call68KFuncP)(emulStateP, 
        (unsigned long) p, 
        buf,
        sizeof(buf)));
	return l;
}

/** MathLib glue functions */

/* 2 args and return value */

double GluePow(PNOBlock *pnoP, double arg1, double arg2)
{
    char buffer[sizeof(UInt16) + sizeof(double) * 2 + sizeof(double *)];
    char *b;
    unsigned short s;
    double d;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
        
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);
    
    b = buffer;
    *(unsigned short *)b = PNO(mathLibRefNum);
    b += sizeof(unsigned short);
    
    WriteUnaligned64(b, arg1);
    b += sizeof(double);
    
    WriteUnaligned64(b, arg2);
    b += sizeof(double);
    
    WriteUnaligned32(b, (unsigned long) &d);
    
    s = ((call68KFuncP)(emulStateP, 
        PceNativeTrapNo(sysLibTrapCustom+24),
        buffer,
        sizeof(buffer)));
    return SwapDouble(d);
}

double GlueATan2(PNOBlock *pnoP, double arg1, double arg2)
{
    char buffer[sizeof(UInt16) + sizeof(double) * 2 + sizeof(double *)];
    char *b;
    unsigned short s;
    double d;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
        
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);
    
    b = buffer;
    *(unsigned short *)b = PNO(mathLibRefNum);
    b += sizeof(unsigned short);
    
    WriteUnaligned64(b, arg1);
    b += sizeof(double);
    
    WriteUnaligned64(b, arg2);
    b += sizeof(double);
    
    WriteUnaligned32(b, (unsigned long) &d);
    
    s = ((call68KFuncP)(emulStateP, 
        PceNativeTrapNo(sysLibTrapCustom+3),
        buffer,
        sizeof(buffer)));
    return SwapDouble(d);
}

/* 1 arg and return value */

double GlueACos(PNOBlock *pnoP, double arg1)
{
    char buffer[sizeof(UInt16) + sizeof(double) + sizeof(double *)];
    char *b;
    unsigned short s;
    double d;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
        
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);
    
    b = buffer;
    *(unsigned short *)b = PNO(mathLibRefNum);
    b += sizeof(unsigned short);
    
    WriteUnaligned64(b, arg1);
    b += sizeof(double);
    
    WriteUnaligned32(b, (unsigned long) &d);
    
    s = ((call68KFuncP)(emulStateP, 
        PceNativeTrapNo(sysLibTrapCustom+0),
        buffer,
        sizeof(buffer)));
    return SwapDouble(d);
}

double GlueASin(PNOBlock *pnoP, double arg1)
{
    char buffer[sizeof(UInt16) + sizeof(double) + sizeof(double *)];
    char *b;
    unsigned short s;
    double d;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
        
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);
    
    b = buffer;
    *(unsigned short *)b = PNO(mathLibRefNum);
    b += sizeof(unsigned short);
    
    WriteUnaligned64(b, arg1);
    b += sizeof(double);
    
    WriteUnaligned32(b, (unsigned long) &d);
    
    s = ((call68KFuncP)(emulStateP, 
        PceNativeTrapNo(sysLibTrapCustom+1),
        buffer,
        sizeof(buffer)));
    return SwapDouble(d);
}

double GlueATan(PNOBlock *pnoP, double arg1)
{
    char buffer[sizeof(UInt16) + sizeof(double) + sizeof(double *)];
    char *b;
    unsigned short s;
    double d;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
        
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);
    
    b = buffer;
    *(unsigned short *)b = PNO(mathLibRefNum);
    b += sizeof(unsigned short);
    
    WriteUnaligned64(b, arg1);
    b += sizeof(double);
    
    WriteUnaligned32(b, (unsigned long) &d);
    
    s = ((call68KFuncP)(emulStateP, 
        PceNativeTrapNo(sysLibTrapCustom+2),
        buffer,
        sizeof(buffer)));
    return SwapDouble(d);
}

double GlueCos(PNOBlock *pnoP, double arg1)
{
    char buffer[sizeof(UInt16) + sizeof(double) + sizeof(double *)];
    char *b;
    unsigned short s;
    double d;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
        
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);
    
    b = buffer;
    *(unsigned short *)b = PNO(mathLibRefNum);
    b += sizeof(unsigned short);
    
    WriteUnaligned64(b, arg1);
    b += sizeof(double);
    
    WriteUnaligned32(b, (unsigned long) &d);
    
    s = ((call68KFuncP)(emulStateP, 
        PceNativeTrapNo(sysLibTrapCustom+4),
        buffer,
        sizeof(buffer)));
    return SwapDouble(d);
}

double GlueSin(PNOBlock *pnoP, double arg1)
{
    char buffer[sizeof(UInt16) + sizeof(double) + sizeof(double *)];
    char *b;
    unsigned short s;
    double d;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
        
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);
    
    b = buffer;
    *(unsigned short *)b = PNO(mathLibRefNum);
    b += sizeof(unsigned short);
    
    WriteUnaligned64(b, arg1);
    b += sizeof(double);
    
    WriteUnaligned32(b, (unsigned long) &d);
    
    s = ((call68KFuncP)(emulStateP, 
        PceNativeTrapNo(sysLibTrapCustom+5),
        buffer,
        sizeof(buffer)));
    return SwapDouble(d);
}

double GlueTan(PNOBlock *pnoP, double arg1)
{
    char buffer[sizeof(UInt16) + sizeof(double) + sizeof(double *)];
    char *b;
    unsigned short s;
    double d;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
        
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);
    
    b = buffer;
    *(unsigned short *)b = PNO(mathLibRefNum);
    b += sizeof(unsigned short);
    
    WriteUnaligned64(b, arg1);
    b += sizeof(double);
    
    WriteUnaligned32(b, (unsigned long) &d);
    
    s = ((call68KFuncP)(emulStateP, 
        PceNativeTrapNo(sysLibTrapCustom+6),
        buffer,
        sizeof(buffer)));
    return SwapDouble(d);
}

double GlueCosH(PNOBlock *pnoP, double arg1)
{
    char buffer[sizeof(UInt16) + sizeof(double) + sizeof(double *)];
    char *b;
    unsigned short s;
    double d;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
        
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);
    
    b = buffer;
    *(unsigned short *)b = PNO(mathLibRefNum);
    b += sizeof(unsigned short);
    
    WriteUnaligned64(b, arg1);
    b += sizeof(double);
    
    WriteUnaligned32(b, (unsigned long) &d);
    
    s = ((call68KFuncP)(emulStateP, 
        PceNativeTrapNo(sysLibTrapCustom+8),
        buffer,
        sizeof(buffer)));
    return SwapDouble(d);
}

double GlueSinH(PNOBlock *pnoP, double arg1)
{
    char buffer[sizeof(UInt16) + sizeof(double) + sizeof(double *)];
    char *b;
    unsigned short s;
    double d;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
        
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);
    
    b = buffer;
    *(unsigned short *)b = PNO(mathLibRefNum);
    b += sizeof(unsigned short);
    
    WriteUnaligned64(b, arg1);
    b += sizeof(double);
    
    WriteUnaligned32(b, (unsigned long) &d);
    
    s = ((call68KFuncP)(emulStateP, 
        PceNativeTrapNo(sysLibTrapCustom+9),
        buffer,
        sizeof(buffer)));
    return SwapDouble(d);
}

double GlueTanH(PNOBlock *pnoP, double arg1)
{
    char buffer[sizeof(UInt16) + sizeof(double) + sizeof(double *)];
    char *b;
    unsigned short s;
    double d;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
        
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);
    
    b = buffer;
    *(unsigned short *)b = PNO(mathLibRefNum);
    b += sizeof(unsigned short);
    
    WriteUnaligned64(b, arg1);
    b += sizeof(double);
    
    WriteUnaligned32(b, (unsigned long) &d);
    
    s = ((call68KFuncP)(emulStateP, 
        PceNativeTrapNo(sysLibTrapCustom+10),
        buffer,
        sizeof(buffer)));
    return SwapDouble(d);
}

double GlueACosH(PNOBlock *pnoP, double arg1)
{
    char buffer[sizeof(UInt16) + sizeof(double) + sizeof(double *)];
    char *b;
    unsigned short s;
    double d;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
        
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);
    
    b = buffer;
    *(unsigned short *)b = PNO(mathLibRefNum);
    b += sizeof(unsigned short);
    
    WriteUnaligned64(b, arg1);
    b += sizeof(double);
    
    WriteUnaligned32(b, (unsigned long) &d);
    
    s = ((call68KFuncP)(emulStateP, 
        PceNativeTrapNo(sysLibTrapCustom+11),
        buffer,
        sizeof(buffer)));
    return SwapDouble(d);
}

double GlueASinH(PNOBlock *pnoP, double arg1)
{
    char buffer[sizeof(UInt16) + sizeof(double) + sizeof(double *)];
    char *b;
    unsigned short s;
    double d;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
        
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);
    
    b = buffer;
    *(unsigned short *)b = PNO(mathLibRefNum);
    b += sizeof(unsigned short);
    
    WriteUnaligned64(b, arg1);
    b += sizeof(double);
    
    WriteUnaligned32(b, (unsigned long) &d);
    
    s = ((call68KFuncP)(emulStateP, 
        PceNativeTrapNo(sysLibTrapCustom+12),
        buffer,
        sizeof(buffer)));
    return SwapDouble(d);
}

double GlueATanH(PNOBlock *pnoP, double arg1)
{
    char buffer[sizeof(UInt16) + sizeof(double) + sizeof(double *)];
    char *b;
    unsigned short s;
    double d;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
        
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);
    
    b = buffer;
    *(unsigned short *)b = PNO(mathLibRefNum);
    b += sizeof(unsigned short);
    
    WriteUnaligned64(b, arg1);
    b += sizeof(double);
    
    WriteUnaligned32(b, (unsigned long) &d);
    
    s = ((call68KFuncP)(emulStateP, 
        PceNativeTrapNo(sysLibTrapCustom+13),
        buffer,
        sizeof(buffer)));
    return SwapDouble(d);
}

double GlueExp(PNOBlock *pnoP, double arg1)
{
    char buffer[sizeof(UInt16) + sizeof(double) + sizeof(double *)];
    char *b;
    unsigned short s;
    double d;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
        
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);
    
    b = buffer;
    *(unsigned short *)b = PNO(mathLibRefNum);
    b += sizeof(unsigned short);
    
    WriteUnaligned64(b, arg1);
    b += sizeof(double);
    
    WriteUnaligned32(b, (unsigned long) &d);
    
    s = ((call68KFuncP)(emulStateP, 
        PceNativeTrapNo(sysLibTrapCustom+14),
        buffer,
        sizeof(buffer)));
    return SwapDouble(d);
}

double GlueLog(PNOBlock *pnoP, double arg1)
{
    char buffer[sizeof(UInt16) + sizeof(double) + sizeof(double *)];
    char *b;
    unsigned short s;
    double d;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
        
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);
    
    b = buffer;
    *(unsigned short *)b = PNO(mathLibRefNum);
    b += sizeof(unsigned short);
    
    WriteUnaligned64(b, arg1);
    b += sizeof(double);
    
    WriteUnaligned32(b, (unsigned long) &d);
    
    s = ((call68KFuncP)(emulStateP, 
        PceNativeTrapNo(sysLibTrapCustom+17),
        buffer,
        sizeof(buffer)));
    return SwapDouble(d);
}

double GlueLog10(PNOBlock *pnoP, double arg1)
{
    char buffer[sizeof(UInt16) + sizeof(double) + sizeof(double *)];
    char *b;
    unsigned short s;
    double d;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
        
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);
    
    b = buffer;
    *(unsigned short *)b = PNO(mathLibRefNum);
    b += sizeof(unsigned short);
    
    WriteUnaligned64(b, arg1);
    b += sizeof(double);
    
    WriteUnaligned32(b, (unsigned long) &d);
    
    s = ((call68KFuncP)(emulStateP, 
        PceNativeTrapNo(sysLibTrapCustom+18),
        buffer,
        sizeof(buffer)));
    return SwapDouble(d);
}

double GlueSqrt(PNOBlock *pnoP, double arg1)
{
    char buffer[sizeof(UInt16) + sizeof(double) + sizeof(double *)];
    char *b;
    unsigned short s;
    double d;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
        
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);
    
    b = buffer;
    *(unsigned short *)b = PNO(mathLibRefNum);
    b += sizeof(unsigned short);
    
    WriteUnaligned64(b, arg1);
    b += sizeof(double);
    
    WriteUnaligned32(b, (unsigned long) &d);
    
    s = ((call68KFuncP)(emulStateP, 
        PceNativeTrapNo(sysLibTrapCustom+25),
        buffer,
        sizeof(buffer)));
    return SwapDouble(d);
}

double GlueCbrt(PNOBlock *pnoP, double arg1)
{
    char buffer[sizeof(UInt16) + sizeof(double) + sizeof(double *)];
    char *b;
    unsigned short s;
    double d;
    Call68KFuncType *call68KFuncP;
    const void *emulStateP;
        
    call68KFuncP = (Call68KFuncType *) PNO(call68KFuncP);
    emulStateP = PNO(emulStateP);
    
    b = buffer;
    *(unsigned short *)b = PNO(mathLibRefNum);
    b += sizeof(unsigned short);
    
    WriteUnaligned64(b, arg1);
    b += sizeof(double);
    
    WriteUnaligned32(b, (unsigned long) &d);
    
    s = ((call68KFuncP)(emulStateP, 
        PceNativeTrapNo(sysLibTrapCustom+27),
        buffer,
        sizeof(buffer)));
    return SwapDouble(d);
}