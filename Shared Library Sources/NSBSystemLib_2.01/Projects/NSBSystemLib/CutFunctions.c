/********************************************************************
 *                T H I S _ A N D I n t
 ********************************************************************/
Err THIS_ANDInt(UInt16 refNum, Int32 int1, Int32 int2, Int32 *result)
// DESC Returns a bitwise AND on the int1 and int2 parameters.
{
    *result = int1 & int2;
    
    return 0;
}

/********************************************************************
 *                T H I S _ O R I n t
 ********************************************************************/
Err THIS_ORInt(UInt16 refNum, Int32 int1, Int32 int2, Int32 *result)
// DESC Returns a bitwise OR on the int1 and int2 parameters.
{
    *result = int1 | int2;
    
    return 0;
}

/********************************************************************
 *                T H I S _ X O R I n t
 ********************************************************************/
Err THIS_XORInt(UInt16 refNum, Int32 int1, Int32 int2, Int32 *result)
// DESC Returns a bitwise XOR on the int1 and int2 parameters.
{
    *result = int1 ^ int2;
    
    return 0;
}

/********************************************************************
 *             T H I S _ O n e s C o m p l e m e n t
 ********************************************************************/
Err THIS_OnesComplement(UInt16 refNum, Int32 intValue, Int32 *result)
// DESC Returns the "one's complement" of the intValue parameter.
// DESC This essentially turns all 1 bits to 0 and all 0 bits to 1.
{
    *result = ~intValue;
    
    return 0;
}

/********************************************************************
 *                T H I S _ B i t V a l u e
 ********************************************************************/
Err THIS_BitValue(UInt16 refNum, Int32 intValue, Int32 bitNumber, Int32 *result)
// DESC Returns 1 if the specified bit number is 1, otherwise it
// DESC returns 0.
// PARAM2 Bits are numbered from right to left from 0 to 31.
{
    if (bitNumber < 0)
        bitNumber = 0;
    if (bitNumber > 31)
        bitNumber = 31;
    if (intValue & bitMask(bitNumber))
        *result = 1;
    else
        *result = 0;
    
    return 0;
}

/********************************************************************
 *                T H I S _ B i t s V a l u e
 ********************************************************************/
Err THIS_BitsValue(UInt16 refNum, Int32 intValue, Int32 bitNumber, Int32 numberOfBits, Int32 *result)
// DESC Returns the integer value of the specified bits.  The bits
// DESC retrieved are the bits to the right of the specified bit
// DESC number.  Therefore, BitsValue(intValue, 7, 3) returns the
// DESC value of bits 7, 6, and 5.
// PARAM2 Bits are numbered from right to left from 0 to 31.
{
    if (bitNumber < 0)
        bitNumber = 0;
    if (bitNumber > 31)
        bitNumber = 31;
    if ((bitNumber - numberOfBits) < 0)
        numberOfBits = bitNumber + 1;
    if (numberOfBits <= 0) {
        *result = 0;
    }
    *result = (intValue >> (bitNumber + 1 - numberOfBits)) & ~(~0 << numberOfBits);
    
    return 0;
}

/********************************************************************
 *                T H I S _ S e t B i t V a l u e
 ********************************************************************/
Err THIS_SetBitValue(UInt16 refNum, Int32 intValue, Int32 bitNumber, 
                  Int32 bitValue, Int32 *result)
// DESC Sets the bit specified by bitNumber to the specified
// DESC bit value.
// PARAM2 Bits are numbered from right to left from 0 to 31.
{
    if (bitNumber < 0)
        bitNumber = 0;
    if (bitNumber > 31)
        bitNumber = 31;
    if (bitValue)
        *result = (intValue | bitMask(bitNumber));
    else
        *result = (intValue & ~(bitMask(bitNumber)));
    
    return 0;
}

/********************************************************************
 *                T H I S _ S e t B i t s V a l u e
 ********************************************************************/
Err THIS_SetBitsValue(UInt16 refNum, Int32 intValue, Int32 bitsValue, 
                      Int32 bitNumber, Int32 numberOfBits, Int32 *result)
// DESC Sets the specified bits to the integer value of the 
// DESC specified bits.  The bits set are the bits to the right of the 
// DESC specified bit number.  Therefore, 
// DESC SetBitsValue(intValue, 7, 3) sets the value of bits 7, 6, 
// DESC and 5.
// PARAM2 Bits are numbered from right to left from 0 to 31.
{
    Int8 i;
    Int8 n;
    
    if (bitNumber < 0)
        bitNumber = 0;
    if (bitNumber > 31)
        bitNumber = 31;
    if ((bitNumber - numberOfBits) < 0)
        numberOfBits = bitNumber + 1;
    if (numberOfBits <= 0) {
        *result = intValue;
        return 0;
    }
    *result = intValue;
    n = numberOfBits - 1;
    for (i = bitNumber; i > (bitNumber - numberOfBits); i--)
        if (bitsValue & bitMask(n--))
            *result = (*result | bitMask(i));
        else
            *result = (*result & ~(bitMask(i)));
                
    return 0;
}

/********************************************************************
 *                T H I S _ I n t T o H e x
 ********************************************************************/
Err THIS_IntToHex(UInt16 refNum, Int32 intValue, Int32 trimLeading, char *hexValue)
// DESC Convert the specified integer value to a hexadecimal string.
// PARAM2 0 = do not trim leading zeros from result string
// PARAM2 1 = trim leading zeros from result string.
{
    char hexV[9];
    char *s;
    
    StrIToH(hexV, (UInt32) intValue);
    if (trimLeading) {
        s = hexV;
        while (*s == '0')
            s++;
        if (StrLen(s) == 0)
            StrCopy(hexValue, "0");
        else
            StrCopy(hexValue, s);
    }
    else
        StrCopy(hexValue, hexV);    
    return 0;
}

/********************************************************************
 *                T H I S _ H e x T o I n t
 ********************************************************************/
Err THIS_HexToInt(UInt16 refNum, char *hexValue, Int32 *intValue)
// DESC Convert the specified hexadecimal string to an integer value.
{
    char   hexV[10];
    Int8   i;
    UInt32 multiplier = 1;
    char   *s;
    UInt16 len;
    
    len = StrLen(hexValue);
    if ((s = StrChr(hexValue, ' ')) != NULL)
        len = (UInt16) (s - hexValue);
    hexV[0] = 0;
    for (i = 0; i < 8 - len; i++)
        hexV[i] = '0';
    hexV[i] = 0;
    StrNCat(hexV, hexValue, 9);
    hexV[8] = 0;
    
    for (i = 0; i < 8; i++)
        if (hexV[i] >= '0' && hexV[i] <= '9')
            hexV[i] = hexV[i] - '0';
        else
            if (hexV[i] >= 'a' && hexV[i] <= 'f')
                hexV[i] = (hexV[i] - 'a') + 10;
            else
                if (hexV[i] >= 'A' && hexV[i] <= 'F')
                    hexV[i] = (hexV[i] - 'A') + 10;
                else {
                    *intValue = 0;
                    return 0;
                }
                
    *intValue = 0;
    for (i = 7; i >= 0; i--) {
        *intValue = *intValue + (hexV[i] * multiplier);
        multiplier = multiplier * 16;
    }
    
    return 0;
}

/********************************************************************
 *                T H I S _ I n t T o B i n
 ********************************************************************/
Err THIS_IntToBin(UInt16 refNum, Int32 intValue, Int32 trimLeading, char *binValue)
// DESC Convert the specified integer value to a binary string.
// PARAM2 0 = do not trim leading zeros from result string
// PARAM2 1 = trim leading zeros from result string.
{
    Int8 i;
    Int8 n = 0;
    char binV[33];
    
    for (i = 31; i >= 0; i--)
        if ((UInt32) intValue & bitMask(i)) {
            binV[n++] = '1';
            trimLeading = 0;
        }
        else
            if (trimLeading == 0)
                binV[n++] = '0';
    binV[n] = 0;
    StrCopy(binValue, binV);
    
    return 0;
}

/********************************************************************
 *                T H I S _ B i n T o I n t
 ********************************************************************/
Err THIS_BinToInt(UInt16 refNum, char *binValue, Int32 *intValue)
// DESC Convert the specified binary string to an integer value.
{
    char   binV[34];
    Int8   i;
    UInt32 multiplier = 1;
    char   *s;
    UInt32 intV;
    UInt16 len;
    
    len = StrLen(binValue);
    if ((s = StrChr(binValue, ' ')) != NULL)
        len = (UInt16) (s - binValue);
    binV[0] = 0;
    for (i = 0; i < 32 - len; i++)
        binV[i] = '0';
    binV[i] = 0;
    StrNCat(binV, binValue, 33);
    binV[32] = 0;

    intV = 0;   
    for (i = 31; i >= 0; i--)
        if (binV[(0 - i) + 31] != '0')
            intV = (intV | bitMask(i));

    *intValue = (Int32) intV;
    return 0;
}

// SECTION Screen and Color Functions:

/********************************************************************
 *          T H I S _ G e t S u p p o r t e d D e p t h s
 ********************************************************************/
Err THIS_GetSupportedDepths(UInt16 refNum, Int32 *depths)
// DESC	Returns a bitmapped integer with each bit indicating a
// DESC	bitmap depth supported by the PalmOS device.
// NOTE	The bit manipulation functions in this library or the 
// NOTE NS Basic Shared Library "BitsNBytes" probably provide
// NOTE	the best suited functions for evaluating the returned value
// NOTE	from this function.
{
    Err err;
    UInt32 supportedDepthMap;
    
    err = WinScreenMode(winScreenModeGetSupportedDepths, 
                        NULL, NULL, &supportedDepthMap, NULL);
    *depths = (Int32) supportedDepthMap;
    
	return 0 ;
}

/********************************************************************
 *             T H I S _ D e p t h S u p p o r t e d
 ********************************************************************/
Err THIS_DepthSupported(UInt16 refNum, Int32 depth, Int32 *boolean)
// DESC	Returns 1 if the specified depth is supported by the
// DESC	PalmOS device.  Otherwise, it returns 0.
// BEFORE
// BEFORE depth = 4
{
    Err err;
    UInt32 supportedDepthMap;
    
    err = WinScreenMode(winScreenModeGetSupportedDepths, 
                        NULL, NULL, &supportedDepthMap, NULL);
    if (supportedDepthMap & bitDepthMask(depth))
        *boolean = 1;
    else
    	*boolean = 0;
    	
	return 0;
}

/********************************************************************
 *               T H I S _ C o l o r S u p p o r t e d
 ********************************************************************/
Err THIS_ColorSupported(UInt16 refNum, Int32 *boolean) 
// DESC	Returns 1 if the PalmOS device has color capabilities.
// DESC	Otherwise, it returns 0.
{
    Err err;
    Boolean supportsColor;
    
    err = WinScreenMode(winScreenModeGetSupportsColor, 
                        NULL, NULL, NULL, &supportsColor);
    *boolean = (Int32) supportsColor;
	return 0;
}

/********************************************************************
 *                   T H I S _ S e t D e p t h
 ********************************************************************/
Err THIS_SetDepth(UInt16 refNum, Int32 depth) 
// DESC	Sets the screen mode to support the specified bitmap 
// DESC	bit depth.
// BEFORE
// BEFORE depth = 4
{
    Err    err;
    UInt32 requestedDepth;
    
    requestedDepth = (UInt32) depth;
    err = WinScreenMode(winScreenModeSet, 
                        NULL, NULL, &requestedDepth, NULL);
	return 0;
}

/********************************************************************
 *                   T H I S _ S e t C o l o r
 ********************************************************************/
Err THIS_SetColor(UInt16 refNum, Int32 boolean) 
// DESC	Sets the screen mode to support color bitmaps.
// PARAM1 1 = support color
// PARAM1 0 = do not support color
// BEFORE
// BEFORE boolean = 1
{
    Err     err;
    Boolean setColor;
    
    setColor = (Boolean) boolean;
    err = WinScreenMode(winScreenModeSet, 
                        NULL, NULL, NULL, &setColor);
    return 0;
}

/********************************************************************
 *               T H I S _ S a v e S c r e e n M o d e
 ********************************************************************/
Err THIS_SaveScreenMode(UInt16 refNum) 
// DESC	Saves the current screen mode parameters.  These parameters
// DESC	can later be restored by calling "RestoreScreenMode".  It is
// DESC	suggested that the current screen mode parameters be saved before
// DESC	any changes are requested and that these saved parameters
// DESC	are restored when the program exits.
{
    Err err;
    THIS_ATTACH_GLOBALS
        
    err = WinScreenMode(winScreenModeGet, 
                        NULL, NULL, &gP->depth, &gP->color);
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *           T H I S _ R e s t o r e S c r e e n M o d e
 ********************************************************************/
Err THIS_RestoreScreenMode(UInt16 refNum) 
// DESC	Restores saved screen mode parameters.  These parameters
// DESC	must have been saved by calling "SaveScreenMode".  It is
// DESC	suggested that the current screen mode parameters be saved before
// DESC	any changes are requested and that these saved parameters
// DESC	are restored when the program exits.
{
    Err err;
    THIS_ATTACH_GLOBALS
        
    err = WinScreenMode(winScreenModeSet, 
                        NULL, NULL, &gP->depth, &gP->color);
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *                 T H I S _ C u r r e n t D e p t h
 ********************************************************************/
Err THIS_CurrentDepth(UInt16 refNum, Int32 *depth) 
// DESC	Returns the current bitmap depth.
{
    Err err;
        
    err = WinScreenMode(winScreenModeGet, 
                        NULL, NULL, (UInt32 *) depth, NULL);
    return 0;
}

/********************************************************************
 *                 T H I S _ C u r r e n t C o l o r
 ********************************************************************/
Err THIS_CurrentColor(UInt16 refNum, Int32 *boolean) 
// DESC	Returns 1 if the PalmOS Device's screen mode is currently
// DESC	set to support color.   Otherwise, it returns 0.
{
    Err err;
    Boolean color;
        
    err = WinScreenMode(winScreenModeGet, 
                        NULL, NULL, NULL, &color);
    *boolean = (Int32) color;
    return 0;
}

/********************************************************************
 *                 T H I S _ S e t T o D e f a u l t s
 ********************************************************************/
Err THIS_SetToDefaults(UInt16 refNum) 
// DESC	Sets all screen mode parameters to their default values.
{
    Err err;
        
    err = WinScreenMode(winScreenModeSetToDefaults, 
                        NULL, NULL, NULL, NULL);
    return 0;
}

/********************************************************************
 *                 T H I S _ D e f a u l t D e p t h
 ********************************************************************/
Err THIS_DefaultDepth(UInt16 refNum, Int32 *depth) 
// DESC	Returns the default bitmap depth.
{
    Err err;
        
    err = WinScreenMode(winScreenModeGetDefaults, 
                        NULL, NULL, (UInt32 *) depth, NULL);
    return 0;
}

/********************************************************************
 *                 T H I S _ D e f a u l t C o l o r
 ********************************************************************/
Err THIS_DefaultColor(UInt16 refNum, Int32 *boolean) 
// DESC	Returns 1 if the PalmOS Device's screen mode default is
// DESC	set to support color.   Otherwise, it returns 0.
{
    Err err;
    Boolean color;
        
    err = WinScreenMode(winScreenModeGetDefaults, 
                        NULL, NULL, NULL, &color);
    *boolean = (Int32) color;
    return 0;
}

/********************************************************************
 *         T H I S _ G e t T a b l e E n t r y I n d e x
 ********************************************************************/
Err THIS_GetTableEntryIndex(UInt16 refNum, Int32 which, Int32 *index) 
// DESC	This function calls the PalmOS UIColorGetTableEntryIndex
// DESC	function.  It returns the index value for a UI color for the 
// DESC	current system palette.
// PARAM1 UIObjectFrame = 0,
// PARAM1 UIObjectFill = 1
// PARAM1 UIObjectForeground = 2
// PARAM1 UIObjectSelectedFill = 3
// PARAM1 UIObjectSelectedForeground = 4
// PARAM1
// PARAM1 UIMenuFrame = 5
// PARAM1 UIMenuFill = 6
// PARAM1 UIMenuForeground = 7
// PARAM1 UIMenuSelectedFill = 8
// PARAM1 UIMenuSelectedForeground = 9
// PARAM1
// PARAM1 UIFieldBackground = 10
// PARAM1 UIFieldText = 11
// PARAM1 UIFieldTextLines = 12
// PARAM1 UIFieldCaret = 13
// PARAM1 UIFieldTextHighlightBackground = 14
// PARAM1 UIFieldTextHighlightForeground = 15
// PARAM1 UIFieldFepRawText = 16
// PARAM1 UIFieldFepRawBackground = 17
// PARAM1 UIFieldFepConvertedText = 18
// PARAM1 UIFieldFepConvertedBackground = 19
// PARAM1 UIFieldFepUnderline = 20
// PARAM1
// PARAM1 UIFormFrame = 21
// PARAM1 UIFormFill = 22
// PARAM1
// PARAM1 UIDialogFrame = 23
// PARAM1 UIDialogFill = 24
// PARAM1
// PARAM1 UIAlertFrame = 25
// PARAM1 UIAlertFill = 26
// PARAM1
// PARAM1 UIOK = 27
// PARAM1 UICaution = 28
// PARAM1 UIWarning = 29
// RETURNS -1 = PalmOS version is less than 3.5
// BEFORE
// BEFORE which = 11   'UIFieldText
// NOTES This function requires PalmOS version 3.5 or greater.
{
        
    if (SysVersion(NULL, 3, 5)) 
        *index = (Int32) UIColorGetTableEntryIndex((UIColorTableEntries) which);
    else
        *index = -1;
        
    return 0;
}

/********************************************************************
 *            T H I S _ G e t T a b l e E n t r y R G B
 ********************************************************************/
Err THIS_GetTableEntryRGB(UInt16 refNum, Int32 which, Int32 *index) 
// DESC	This function calls the PalmOS UIColorGetTableEntryRGB function.
// DESC	It retrieves the RGB values for the UI Color.  RGB Values are
// DESC	returned in a structure called "RGBColorType".  It contains the 
// DESC	following fields:
// DESC		index, red, green, blue.
// DESC	This function retrieves all these values, but only returns
// DESC	the index.  To get the red, green, and blue values, call this
// DESC	function first and then call GetRGBRed, GetRGBGreen, and 
// DESC	GetRGBBlue.  See the example for more information.
// PARAM1 (see the GetTableEntryIndex function for
// PARAM1  a list of valid "Which" values")
// RETURNS -1 = PalmOS version is less than 3.5
// BEFORE Dim red as Integer
// BEFORE Dim green as Integer
// BEFORE Dim blue as Integer
// BEFORE
// BEFORE which = 11   'UIFieldText
// AFTER red = SL.GetRGBRed()
// AFTER green = SL.GetRGBGreen()
// AFTER blue = SL.GetRGBBlue()
// NOTES This function requires PalmOS version 3.5 or greater.
{
    THIS_ATTACH_GLOBALS

    if (SysVersion(gP, 3, 5)) {       
        UIColorGetTableEntryRGB((UIColorTableEntries) which, &gP->RGB);
        *index = (Int32) WinRGBToIndex(&gP->RGB);
        gP->RGB.index = (UInt8) *index;
    }
    else
        *index = -1;
        
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *                 T H I S _ G e t R G B I n d e x
 ********************************************************************/
Err THIS_GetRGBIndex(UInt16 refNum, Int32 *index) 
// DESC	RGB Values are returned in a structure called "RGBColorType".  
// DESC	It contains the following fields:
// DESC		index, red, green, blue.
// DESC
// DESC	This function returns the index value that was previously
// DESC	retrieved by either the GetTableEntryRGB or IndexToRGB functions.
{
    THIS_ATTACH_GLOBALS
        
    *index = (Int32) gP->RGB.index;
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *                     T H I S _ G e t R G B R e d
 ********************************************************************/
Err THIS_GetRGBRed(UInt16 refNum, Int32 *red) 
// DESC	RGB Values are returned in a structure called "RGBColorType".  
// DESC	It contains the following fields:
// DESC		index, red, green, blue.
// DESC
// DESC	This function returns the red value that was previously
// DESC	retrieved by either the GetTableEntryRGB or IndexToRGB functions.
// EXAMPLE See the example provided with either the GetTableEntryRGB or 
// EXAMPLE IndexToRGB functions.
{
    THIS_ATTACH_GLOBALS
        
    *red = (Int32) gP->RGB.r;
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *                   T H I S _ G e t R G B G r e e n
 ********************************************************************/
Err THIS_GetRGBGreen(UInt16 refNum, Int32 *green) 
// DESC	RGB Values are returned in a structure called "RGBColorType".  
// DESC	It contains the following fields:
// DESC		index, red, green, blue.
// DESC
// DESC	This function returns the green value that was previously
// DESC	retrieved by either the GetTableEntryRGB or IndexToRGB functions.
// EXAMPLE See the example provided with either the GetTableEntryRGB or 
// EXAMPLE IndexToRGB functions.
{
    THIS_ATTACH_GLOBALS
        
    *green = (Int32) gP->RGB.g;
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *                   T H I S _ G e t R G B B l u e
 ********************************************************************/
Err THIS_GetRGBBlue(UInt16 refNum, Int32 *blue) 
// DESC	RGB Values are returned in a structure called "RGBColorType".  
// DESC	It contains the following fields:
// DESC		index, red, green, blue.
// DESC
// DESC	This function returns the blue value that was previously
// DESC	retrieved by either the GetTableEntryRGB or IndexToRGB functions.
// EXAMPLE See the example provided with either the GetTableEntryRGB or 
// EXAMPLE IndexToRGB functions.
{
    THIS_ATTACH_GLOBALS
        
    *blue = (Int32) gP->RGB.b;
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *           T H I S _ S e t T a b l e E n t r y I n d e x
 ********************************************************************/
Err THIS_SetTableEntryIndex(UInt16 refNum, Int32 which, Int32 index) 
// DESC	This subroutine calls the PalmOS IndexToRGB function and then 
// DESC it calls UIColorSetTableEntry.	It changes a value in the UI 
// DESC Color list.
// NOTE	Some changes aren't reflected until the object or form is
// NOTE	redrawn with the "Redraw" statement.  Even then, some changes
// NOTE	like the form background (UIFormFill - 22) aren't reflected
// NOTE	until until you change forms with a "NextScreen" statement.
// NOTE	You might want to set some table entries in either the
// NOTE	programs "Startup" code or just before you use the "NextScreen"
// NOTE	statement.
// NOTE
// NOTE This function requires PalmOS version 3.5 or greater.
// PARAM1 (see the GetTableEntryIndex function for
// PARAM1  a list of valid "Which" values")
{ 
    Err err;
    RGBColorType RGB;

    if (SysVersion(NULL, 3, 5)) {
        WinIndexToRGB((IndexedColorType) index, &RGB);    
        err = UIColorSetTableEntry((UIColorTableEntries) which, &RGB);
    }

    return 0;
}

/********************************************************************
 *             T H I S _ S e t T a b l e E n t r y R G B
 ********************************************************************/
Err THIS_SetTableEntryRGB(UInt16 refNum, Int32 which, 
                       Int32 red, Int32 green, Int32 blue) 
// DESC	This subroutine calls the PalmOS UIColorSetTableEntry function.
// DESC	It changes a value in the UI Color list.
// NOTE	Some changes aren't reflected until the object or form is
// NOTE	redrawn with the "Redraw" statement.  Even then, some changes
// NOTE	like the form background (UIFormFill - 22) aren't reflected
// NOTE	until until you change forms with a "NextScreen" statement.
// NOTE	You might want to set some table entries in either the
// NOTE	programs "Startup" code or just before you use the "NextScreen"
// NOTE	statement.
// NOTE
// NOTE This function requires PalmOS version 3.5 or greater.
// PARAM1 (see the GetTableEntryIndex function for
// PARAM1  a list of valid "Which" values")
// PARAM4 Red, Green, Blue valid values are 0 to 255
{
    Err err;
    RGBColorType RGB;
        
    RGB.r = (UInt8) red;
    RGB.g = (UInt8) green;
    RGB.b = (UInt8) blue;

    if (SysVersion(NULL, 3, 5)) {    
        err = UIColorSetTableEntry((UIColorTableEntries) which, &RGB);
    }
    return 0;
}

/********************************************************************
 *           T H I S _ B r i g h t n e s s A d j u s t
 ********************************************************************/
Err THIS_BrightnessAdjust(UInt16 refNum) 
// DESC	This subroutine calls the PalmOS UIBrightnessAdjust function.  
// DESC	It displays the "Brightness Adjust" dialog.
// NOTES This function requires PalmOS version 3.5 or greater.
{ 
    if (SysVersion(NULL, 3, 5))
        UIBrightnessAdjust();
    return 0;
}

/********************************************************************
 *               T H I S _ C o n t r a s t A d j u s t
 ********************************************************************/
Err THIS_ContrastAdjust(UInt16 refNum) 
// DESC	This subroutine calls the PalmOS UIContrastAdjust function.  
// DESC	It displays the "Contrast Adjust" dialog.
// NOTE	The PalmOS documentation states that this function only works
// NOTE	on the "Palm V Connected Organizer".
// NOTE
// NOTE This function requires PalmOS version 3.5 or greater.
{
    if (SysVersion(NULL, 3, 5))
        UIContrastAdjust();
    return 0;
}

/********************************************************************
 *              T H I S _ P i c k C o l o r I n d e x
 ********************************************************************/
Err THIS_PickColorIndex(UInt16 refNum, Int32 index, Char *title, Int32 *changed) 
// DESC	This function calls the PalmOS UIPickColor function.  It
// DESC	displays a Palette dialog to allow a user to select a
// DESC	color.  The selected index and RGB values can be retrieved
// DESC	by calling the GetRGBIndex, GetRGBRed, GetRGBGreen and 
// DESC	GetRGBBlue functions.
// PARAM1 Suggested index
// PARAM2 Title to display on dialog
// RETURNS -1 = PalmOS version is less than v3.5
// RETURNS  0 = User cancelled or chose suggested index
// RETURNS  1 = User chose a new index
// NOTES This function requires PalmOS version of 3.5 or greater.
{
    IndexedColorType idx;
    THIS_ATTACH_GLOBALS

    if (SysVersion(gP, 3, 5)) {
        idx = (IndexedColorType) index;
        *changed = (Int32) UIPickColor(&idx, &gP->RGB, UIPickColorStartPalette, title, "");
        gP->RGB.index = idx;
    }
    else
        *changed = -1;
        
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *              T H I S _ P i c k C o l o r R G B
 ********************************************************************/
Err THIS_PickColorRGB(UInt16 refNum, Int32 red, Int32 green, Int32 blue, Char *title, Int32 *changed) 
// DESC	This function calls the PalmOS UIPickColor function.  It
// DESC	displays an RGB dialog to allow a user to select a
// DESC	color.  The selected index and RGB values can be retrieved
// DESC	by calling the GetRGBIndex, GetRGBRed, GetRGBGreen and 
// DESC	GetRGBBlue functions.
// PARAM3 Suggested Red, Green, Blue values (0 to 255)
// PARAM4 Title to display on dialog
// RETURNS -1 = PalmOS version is less than 3.5
// RETURNS  0 = User cancelled or chose suggested colors
// RETURNS  1 = User chose a new index
// NOTES This function requires PalmOS version 3.5 or greater.
{
    IndexedColorType idx;
    THIS_ATTACH_GLOBALS
        
    if (SysVersion(gP, 3, 5)) {
        gP->RGB.r = (UInt8) red;
        gP->RGB.g = (UInt8) green;
        gP->RGB.b = (UInt8) blue;
        *changed = (Int32) UIPickColor(&idx, &gP->RGB, UIPickColorStartRGB, title, "");
        gP->RGB.index = idx;
    }
    else
        *changed = -1;
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *                   T H I S _ I n d e x T o R G B
 ********************************************************************/
Err THIS_IndexToRGB(UInt16 refNum, Int32 index) 
// DESC	This subroutine calls the PalmOS WinIndexToRGB function.  It
// DESC	converts an index in the currently active color table to an
// DESC	RGB value.  RGB Values are returned in a structure called 
// DESC	"RGBColorType".  It contains the following fields:
// DESC		index, red, green, blue.
// DESC	To get the actual index, red, green, and blue values, call this
// DESC	function first and then call GetRGBIndex, GetRGBRed, GetRGBGreen,
// DESC	and GetRGBBlue.  See the example for more information.
// NOTES This function requires PalmOS version 3.5 or greater.
{
    THIS_ATTACH_GLOBALS

    if (SysVersion(gP, 3, 5))
        WinIndexToRGB((IndexedColorType) index, &gP->RGB);
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *               T H I S _ R G B T o I n d e x
 ********************************************************************/
Err THIS_RGBToIndex(UInt16 refNum, Int32 red, Int32 green, Int32 blue,
                    Int32 *index) 
// DESC	This function calls the PalmOS WinRGBToIndex function.  It 
// DESC	converts RGB values to the index of the closest color in the
// DESC	currently active color lookup table (CLUT).
// PARAM3 Red, Green, Blue valid values are 0 to 255
// RETURNS -1 = PalmOS version is less than 3.5
// NOTES This function requires PalmOS version 3.5 or greater.
{
    RGBColorType RGB;
        
    RGB.r = (UInt8) red;
    RGB.g = (UInt8) green;
    RGB.b = (UInt8) blue;
    
    if (SysVersion(NULL, 3, 5))
        *index = (Int32) WinRGBToIndex(&RGB);
    else
        *index = -1;
    return 0;
}

/********************************************************************
 *                   T H I S _ S e t F o r e C o l o r
 ********************************************************************/
Err THIS_SetForeColor(UInt16 refNum, Int32 newIndex, Int32 *oldIndex) 
// DESC	This function calls the PalmOS WinSetForeColor function.  It
// DESC	sets the foreground color to use in subsequent draw operations.
// NOTE	Colors set with this function appear to be reset to default
// NOTE	values when switching between forms or when a form is redrawn.
// NOTE	It is probably best to call this function in the form's
// NOTE	"After" code section.
// NOTE
// NOTE This function requires PalmOS version 3.5 or greater.
// RETURNS Previous foreground index
// RETURNS -1 = PalmOS version is less than 3.5
{
        
    if (SysVersion(NULL, 3, 5)) 
        *oldIndex = (Int32) WinSetForeColor((IndexedColorType) newIndex);
    else
        *oldIndex = -1;
        
    return 0;
}

/********************************************************************
 *                   T H I S _ S e t B a c k C o l o r
 ********************************************************************/
Err THIS_SetBackColor(UInt16 refNum, Int32 newIndex, Int32 *oldIndex) 
// DESC	This function calls the PalmOS WinSetBackColor function.  It
// DESC	sets the background color to use in subsequent draw operations.
// NOTE	Colors set with this function appear to be reset to default
// NOTE	values when switching between forms or when a form is redrawn.
// NOTE	It is probably best to call this function in the form's
// NOTE	"After" code section.
// NOTE
// NOTE This function requires PalmOS version 3.5 or greater.
// RETURNS Previous background index
// RETURNS -1 = PalmOS version is less than 3.5
{

    if (SysVersion(NULL, 3, 5))
        *oldIndex = (Int32) WinSetBackColor((IndexedColorType) newIndex);
    else
        *oldIndex = -1;
    return 0;
}

/********************************************************************
 *                   T H I S _ S e t T e x t C o l o r
 ********************************************************************/
Err THIS_SetTextColor(UInt16 refNum, Int32 newIndex, Int32 *oldIndex) 
// DESC	This function calls the PalmOS WinSetTextColor function.  It
// DESC	sets the color to use for drawing characters in subsequent draw 
// DESC	operations.
// NOTE	Colors set with this function appear to be reset to default
// NOTE	values when switching between forms or when a form is redrawn.
// NOTE	It is probably best to call this function in the form's
// NOTE	"After" code section.
// NOTE
// NOTE This function requires PalmOS version 3.5 or greater.
// RETURNS Previous text color index
// RETURNS -1 = PalmOS version is less than 3.5
{
        
    if (SysVersion(NULL, 3, 5))        
        *oldIndex = (Int32) WinSetTextColor((IndexedColorType) newIndex);
    else
        *oldIndex = -1;
        
    return 0;
}

/********************************************************************
 *                  T H I S _ D r a w L i n e
 ********************************************************************/
Err THIS_DrawLine(UInt16 refNum, Int32 x1, Int32 y1, Int32 x2, Int32 y2) 
// DESC	This soubroutine calls the PalmOS WinDrawLine function.  It 
// DESC	draws a line in the draw window using the current foreground 
// DESC	color.
// NOTE	This function was provided for completeness only.  The
// NOTE	built-in DrawLine NSBasic statement produces the same result.
{
        
    WinDrawLine((Coord) x1, (Coord) y1, (Coord) x2, (Coord) y2);
    return 0;
}

/********************************************************************
 *                  T H I S _ D r a w G r a y L i n e
 ********************************************************************/
Err THIS_DrawGrayLine(UInt16 refNum, Int32 x1, Int32 y1, Int32 x2, Int32 y2) 
// DESC	This subroutine calls the PalmOS WinDrawGrayLine function.  It
// DESC	does not draw in a gray color, but rather draws with
// DESC	alternating foreground and background colors.
{
        
    WinDrawGrayLine((Coord) x1, (Coord) y1, (Coord) x2, (Coord) y2);
    return 0;
}

/********************************************************************
 *                  T H I S _ E r a s e L i n e
 ********************************************************************/
Err THIS_EraseLine(UInt16 refNum, Int32 x1, Int32 y1, Int32 x2, Int32 y2) 
// DESC	This subroutine calls the PalmOS WinEraseLine function.  It
// DESC	draws a line in the draw window using the current background
// DESC	color.
{
        
    WinEraseLine((Coord) x1, (Coord) y1, (Coord) x2, (Coord) y2);
    return 0;
}

/********************************************************************
 *                  T H I S _ I n v e r t L i n e
 ********************************************************************/
Err THIS_InvertLine(UInt16 refNum, Int32 x1, Int32 y1, Int32 x2, Int32 y2) 
// DESC	This subroutine calls the PalmOS WinInvertLine function.  It
// DESC	draws an inverted line in the draw window.
{
        
    WinInvertLine((Coord) x1, (Coord) y1, (Coord) x2, (Coord) y2);
    return 0;
}

/********************************************************************
 *                  T H I S _ D r a w P i x e l
 ********************************************************************/
Err THIS_DrawPixel(UInt16 refNum, Int32 x, Int32 y) 
// DESC	This subroutine calls the PalmOS WinDrawPixel function.  It
// DESC	draws a pixel in the draw window using the current foreground
// DESC	color.
{
        
    WinDrawPixel((Coord) x, (Coord) y);
    return 0;
}

/********************************************************************
 *                  T H I S _ E r a s e P i x e l
 ********************************************************************/
Err THIS_ErasePixel(UInt16 refNum, Int32 x, Int32 y) 
// DESC	This subroutine calls the PalmOS WinErasePixel function.  It
// DESC	draws a pixel in the draw window using the current background
// DESC	color.
{
        
    WinErasePixel((Coord) x, (Coord) y);
    return 0;
}

/********************************************************************
 *                  T H I S _ I n v e r t P i x e l
 ********************************************************************/
Err THIS_InvertPixel(UInt16 refNum, Int32 x, Int32 y) 
// DESC	This subroutine calls the PalmOS WinInvertPixel function.  It
// DESC	draws an inverted pixel in the draw window.
{
        
    WinInvertPixel((Coord) x, (Coord) y);
    return 0;
}

/********************************************************************
 *                  T H I S _ G e t P i x e l
 ********************************************************************/
Err THIS_GetPixel(UInt16 refNum, Int32 x, Int32 y, Int32 *index) 
// DESC	This function calls the PalmOS WinGetPixel function.  It
// DESC	returns the color of the specified a pixel in the draw window.
{
        
    *index = (Int32) WinGetPixel((Coord) x, (Coord) y);
    return 0;
}

/********************************************************************
 *                  T H I S _ S c r e e n L o c k
 ********************************************************************/
Err THIS_ScreenLock(UInt16 refNum, Int32 mode, Int32 *success) 
// DESC	This function calls the PalmOS WinScreenLock function.  It 
// DESC	"locks" the current screen by switching the UI concept of the 
// DESC	screen base address to an area that is not reflected on the
// DESC	display.  This routine can be used to "freeze" the display 
// DESC	while doing lengthy drawing operations to avoid a flickering
// DESC	effect.  Call ScreenUnlock to unlock the display and cause
// DESC	it to be updated with any changes.  The screen must be unlocked
// DESC	as many times as it is locked to actually update the display.
// PARAM1 winLockCopy = 0 - copy old screen to new
// PARAM1 winLockErase = 1 - erase new screen to white
// PARAM1 winLockDontCare = 2 - don't do anything
// RETURNS -1 = PalmOS version is less than 3.5
// RETURNS  1 = success
// RETURNS  0 = failure
// NOTES This function requires PalmOS version 3.5 or greater.
{
    UInt8 *baseAddress;
    
    if (SysVersion(NULL, 3, 5)) {
        baseAddress = WinScreenLock((WinLockInitType) mode);
        if (baseAddress == NULL)
            *success = 0;
        else
            *success = 1;
    }
    else
        *success = -1;
        
    return 0;
}

/********************************************************************
 *                  T H I S _ S c r e e n U n l o c k
 ********************************************************************/
Err THIS_ScreenUnlock(UInt16 refNum) 
// DESC	This subroutine calls the PalmOS WinScreenUnlock function.  Call 
// DESC	ScreenUnlock to unlock the display and cause it to be updated 
// DESC	with any changes.  The screen, which was locked by calling
// DESC	ScreenLock, must be unlocked as many times as it is locked to 
// DESC	actually update the display.
// NOTES This function requires PalmOS version 3.5 or greater.
{
    
    if (SysVersion(NULL, 3, 5))
        WinScreenUnlock();
    
    return 0;
}

/********************************************************************
 *                T H I S _ W i n S a v e B i t s
 ********************************************************************/
Err THIS_WinSaveBits(UInt16 refNum, Int32 index, Int32 x, Int32 y,
                                    Int32 width, Int32 height) 
{
    RectangleType rect;
    UInt16 err;
    THIS_ATTACH_GLOBALS
    
    if (index < 0  || index >= SAVEBITSMAX) {
        THIS_DETACH_GLOBALS
        return 0;
    }
    
    if (gP->saveBits[index])
        WinDeleteWindow(gP->saveBits[index], false);

    rect.topLeft.x = (Coord) x;
    rect.topLeft.y = (Coord) y;
    rect.extent.x = (Coord) width;
    rect.extent.y = (Coord) height;
    gP->saveBits[index] = WinSaveBits(&rect, &err);
    
    THIS_DETACH_GLOBALS
    return 0;
}

/********************************************************************
 *            T H I S _ W i n R e s t o r e B i t s
 ********************************************************************/
Err THIS_WinRestoreBits(UInt16 refNum, Int32 index, Int32 x, Int32 y)
{
    THIS_ATTACH_GLOBALS
    
    if (index < 0  || index >= SAVEBITSMAX) {
        THIS_DETACH_GLOBALS
        return 0;
    }
    
    if (gP->saveBits[index])
        WinRestoreBits(gP->saveBits[index], (Coord) x, (Coord) y);

    gP->saveBits[index] = NULL;
    
    THIS_DETACH_GLOBALS
    return 0;
}
