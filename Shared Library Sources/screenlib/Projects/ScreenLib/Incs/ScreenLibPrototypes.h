typedef enum {
    THIS_TrapVersion = sysLibTrapCustom,
    THIS_TrapCompileInfo,
    THIS_TrapGetSupportedDepths,
    THIS_TrapDepthSupported,
    THIS_TrapColorSupported,
    THIS_TrapSetDepth,
    THIS_TrapSetColor,
    THIS_TrapSetWidth,
    THIS_TrapSetHeight,
    THIS_TrapSaveScreenMode,
    THIS_TrapRestoreScreenMode,
    THIS_TrapCurrentDepth,
    THIS_TrapCurrentColor,
    THIS_TrapCurrentWidth,
    THIS_TrapCurrentHeight,
    THIS_TrapSetToDefaults,
    THIS_TrapDefaultDepth,
    THIS_TrapDefaultColor,
    THIS_TrapDefaultWidth,
    THIS_TrapDefaultHeight,
    THIS_TrapGetTableEntryIndex,
    THIS_TrapGetTableEntryRGB,
    THIS_TrapGetRGBIndex,
    THIS_TrapGetRGBRed,
    THIS_TrapGetRGBGreen,
    THIS_TrapGetRGBBlue,
    THIS_TrapSetTableEntryIndex,
    THIS_TrapSetTableEntryRGB,
    THIS_TrapBrightnessAdjust,
    THIS_TrapContrastAdjust,
    THIS_TrapPickColorIndex,
    THIS_TrapPickColorRGB,
    THIS_TrapIndexToRGB,
    THIS_TrapRGBToIndex,
    THIS_TrapSetForeColor,
    THIS_TrapSetBackColor,
    THIS_TrapSetTextColor,
    THIS_TrapDrawLine,
    THIS_TrapDrawGrayLine,
    THIS_TrapEraseLine,
    THIS_TrapInvertLine,
    THIS_TrapDrawPixel,
    THIS_TrapErasePixel,
    THIS_TrapInvertPixel,
    THIS_TrapGetPixel,
    THIS_TrapScreenLock,
    THIS_TrapScreenUnlock,

    THIS_TrapLast
} THIS_TrapEnum;

#ifdef __cplusplus
extern "C" {
#endif

extern Err THIS_Version(UInt16 refNum, double *version)
                THIS_LIB_TRAP(THIS_TrapVersion);

extern Err THIS_CompileInfo(UInt16 refNum, char *compileDate, char *compileTime)
                THIS_LIB_TRAP(THIS_TrapCompileInfo);

extern Err THIS_GetSupportedDepths(UInt16 refNum, Int32 *depths)
                THIS_LIB_TRAP(THIS_TrapGetSupportedDepths);

extern Err THIS_DepthSupported(UInt16 refNum, Int32 depth, Int32 *boolean)
                THIS_LIB_TRAP(THIS_TrapDepthSupported);

extern Err THIS_ColorSupported(UInt16 refNum, Int32 *boolean)
                THIS_LIB_TRAP(THIS_TrapColorSupported);

extern Err THIS_SetDepth(UInt16 refNum, Int32 depth)
                THIS_LIB_TRAP(THIS_TrapSetDepth);

extern Err THIS_SetColor(UInt16 refNum, Int32 boolean)
                THIS_LIB_TRAP(THIS_TrapSetColor);

extern Err THIS_SetWidth(UInt16 refNum, Int32 width)
                THIS_LIB_TRAP(THIS_TrapSetWidth);

extern Err THIS_SetHeight(UInt16 refNum, Int32 height)
                THIS_LIB_TRAP(THIS_TrapSetHeight);

extern Err THIS_SaveScreenMode(UInt16 refNum)
                THIS_LIB_TRAP(THIS_TrapSaveScreenMode);

extern Err THIS_RestoreScreenMode(UInt16 refNum)
                THIS_LIB_TRAP(THIS_TrapRestoreScreenMode);

extern Err THIS_CurrentDepth(UInt16 refNum, Int32 *depth)
                THIS_LIB_TRAP(THIS_TrapCurrentDepth);

extern Err THIS_CurrentColor(UInt16 refNum, Int32 *boolean)
                THIS_LIB_TRAP(THIS_TrapCurrentColor);

extern Err THIS_CurrentWidth(UInt16 refNum, Int32 *width)
                THIS_LIB_TRAP(THIS_TrapCurrentWidth);

extern Err THIS_CurrentHeight(UInt16 refNum, Int32 *height)
                THIS_LIB_TRAP(THIS_TrapCurrentHeight);

extern Err THIS_SetToDefaults(UInt16 refNum)
                THIS_LIB_TRAP(THIS_TrapSetToDefaults);

extern Err THIS_DefaultDepth(UInt16 refNum, Int32 *depth)
                THIS_LIB_TRAP(THIS_TrapDefaultDepth);

extern Err THIS_DefaultColor(UInt16 refNum, Int32 *boolean)
                THIS_LIB_TRAP(THIS_TrapDefaultColor);

extern Err THIS_DefaultWidth(UInt16 refNum, Int32 *width)
                THIS_LIB_TRAP(THIS_TrapDefaultWidth);

extern Err THIS_DefaultHeight(UInt16 refNum, Int32 *height)
                THIS_LIB_TRAP(THIS_TrapDefaultHeight);

extern Err THIS_GetTableEntryIndex(UInt16 refNum, Int32 which, Int32 *index)
                THIS_LIB_TRAP(THIS_TrapGetTableEntryIndex);

extern Err THIS_GetTableEntryRGB(UInt16 refNum, Int32 which, Int32 *index)
                THIS_LIB_TRAP(THIS_TrapGetTableEntryRGB);

extern Err THIS_GetRGBIndex(UInt16 refNum, Int32 *index)
                THIS_LIB_TRAP(THIS_TrapGetRGBIndex);

extern Err THIS_GetRGBRed(UInt16 refNum, Int32 *red)
                THIS_LIB_TRAP(THIS_TrapGetRGBRed);

extern Err THIS_GetRGBGreen(UInt16 refNum, Int32 *green)
                THIS_LIB_TRAP(THIS_TrapGetRGBGreen);

extern Err THIS_GetRGBBlue(UInt16 refNum, Int32 *blue)
                THIS_LIB_TRAP(THIS_TrapGetRGBBlue);

extern Err THIS_SetTableEntryIndex(UInt16 refNum, Int32 which, Int32 index)
                THIS_LIB_TRAP(THIS_TrapSetTableEntryIndex);

extern Err THIS_SetTableEntryRGB(UInt16 refNum, Int32 which, 
                       Int32 red, Int32 green, Int32 blue)
                THIS_LIB_TRAP(THIS_TrapSetTableEntryRGB);

extern Err THIS_BrightnessAdjust(UInt16 refNum)
                THIS_LIB_TRAP(THIS_TrapBrightnessAdjust);

extern Err THIS_ContrastAdjust(UInt16 refNum)
                THIS_LIB_TRAP(THIS_TrapContrastAdjust);

extern Err THIS_PickColorIndex(UInt16 refNum, Int32 index, Char *title, Int32 *changed)
                THIS_LIB_TRAP(THIS_TrapPickColorIndex);

extern Err THIS_PickColorRGB(UInt16 refNum, Int32 red, Int32 green, Int32 blue, Char *title, Int32 *changed)
                THIS_LIB_TRAP(THIS_TrapPickColorRGB);

extern Err THIS_IndexToRGB(UInt16 refNum, Int32 index)
                THIS_LIB_TRAP(THIS_TrapIndexToRGB);

extern Err THIS_RGBToIndex(UInt16 refNum, Int32 red, Int32 green, Int32 blue,
                    Int32 *index)
                THIS_LIB_TRAP(THIS_TrapRGBToIndex);

extern Err THIS_SetForeColor(UInt16 refNum, Int32 newIndex, Int32 *oldIndex)
                THIS_LIB_TRAP(THIS_TrapSetForeColor);

extern Err THIS_SetBackColor(UInt16 refNum, Int32 newIndex, Int32 *oldIndex)
                THIS_LIB_TRAP(THIS_TrapSetBackColor);

extern Err THIS_SetTextColor(UInt16 refNum, Int32 newIndex, Int32 *oldIndex)
                THIS_LIB_TRAP(THIS_TrapSetTextColor);

extern Err THIS_DrawLine(UInt16 refNum, Int32 x1, Int32 y1, Int32 x2, Int32 y2)
                THIS_LIB_TRAP(THIS_TrapDrawLine);

extern Err THIS_DrawGrayLine(UInt16 refNum, Int32 x1, Int32 y1, Int32 x2, Int32 y2)
                THIS_LIB_TRAP(THIS_TrapDrawGrayLine);

extern Err THIS_EraseLine(UInt16 refNum, Int32 x1, Int32 y1, Int32 x2, Int32 y2)
                THIS_LIB_TRAP(THIS_TrapEraseLine);

extern Err THIS_InvertLine(UInt16 refNum, Int32 x1, Int32 y1, Int32 x2, Int32 y2)
                THIS_LIB_TRAP(THIS_TrapInvertLine);

extern Err THIS_DrawPixel(UInt16 refNum, Int32 x, Int32 y)
                THIS_LIB_TRAP(THIS_TrapDrawPixel);

extern Err THIS_ErasePixel(UInt16 refNum, Int32 x, Int32 y)
                THIS_LIB_TRAP(THIS_TrapErasePixel);

extern Err THIS_InvertPixel(UInt16 refNum, Int32 x, Int32 y)
                THIS_LIB_TRAP(THIS_TrapInvertPixel);

extern Err THIS_GetPixel(UInt16 refNum, Int32 x, Int32 y, Int32 *index)
                THIS_LIB_TRAP(THIS_TrapGetPixel);

extern Err THIS_ScreenLock(UInt16 refNum, Int32 mode, Int32 *success)
                THIS_LIB_TRAP(THIS_TrapScreenLock);

extern Err THIS_ScreenUnlock(UInt16 refNum)
                THIS_LIB_TRAP(THIS_TrapScreenUnlock);

