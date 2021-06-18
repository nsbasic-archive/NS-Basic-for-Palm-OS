//
//    NSBSystemLibPrototypes.h
//

#ifndef __NSBSystemLibPrototypes_H__
#define __NSBSystemLibPrototypes_H__

typedef enum {
    THIS_TrapVersion = sysLibTrapCustom,
    THIS_TrapCompileInfo,
    THIS_TrapSystemVersion,
    THIS_TrapGlobalVersionMajor,
    THIS_TrapGlobalVersionMinor,
    THIS_TrapGlobalX,
    THIS_TrapGlobalY,
    THIS_TrapGlobalStartX,
    THIS_TrapGlobalStartY,
    THIS_TrapGlobalEndX,
    THIS_TrapGlobalEndY,
    THIS_TrapGlobalStartPos,
    THIS_TrapGlobalEndPos,
    THIS_TrapGlobalWidth,
    THIS_TrapGlobalHeight,
    THIS_TrapGlobalHour,
    THIS_TrapGlobalMinute,
    THIS_TrapSetAlarmReset,
    THIS_TrapSetAlarm,
    THIS_TrapCancelAlarm,
    THIS_TrapGetAlarm,
    THIS_TrapGetAlarmTime,
    THIS_TrapGetAlarmResetTime,
    THIS_TrapGetAlarmResetLimit,
    THIS_TrapGetAlarmCommand,
    THIS_TrapGetAlarmMessage,
    THIS_TrapAlarmLog,
    THIS_TrapAlarmLogAlarmTime,
    THIS_TrapAlarmLogResetTime,
    THIS_TrapAlarmLogResetLimit,
    THIS_TrapAlarmLogResetCount,
    THIS_TrapAlarmLogCommand,
    THIS_TrapAlarmLogMessage,
    THIS_TrapClearAlarmLog,
    THIS_TrapFindDatabase,
    THIS_TrapDatabaseInfo,
    THIS_TrapDatabaseName,
    THIS_TrapDatabaseAttributes,
    THIS_TrapDatabaseVersion,
    THIS_TrapDatabaseCreationDate,
    THIS_TrapDatabaseModificationDate,
    THIS_TrapDatabaseBackupDate,
    THIS_TrapDatabaseModificationNumber,
    THIS_TrapDatabaseAppInfoID,
    THIS_TrapDatabaseSortInfoID,
    THIS_TrapDatabaseType,
    THIS_TrapDatabaseCreatorID,
    THIS_TrapDatabaseTotalSize,
    THIS_TrapDatabaseNumRecords,
    THIS_TrapDatabaseDataSize,
    THIS_TrapDeleteDatabase,
    THIS_TrapGetNextDatabaseByTypeCreator,
    THIS_TrapDatabaseCardNo,
    THIS_TrapNumDatabases,
    THIS_TrapNumCards,
    THIS_TrapGetDatabase,
    THIS_TrapSetDatabaseName,
    THIS_TrapSetDatabaseAttributes,
    THIS_TrapSetDatabaseVersion,
    THIS_TrapSetDatabaseCreationDate,
    THIS_TrapSetDatabaseModificationDate,
    THIS_TrapSetDatabaseBackupDate,
    THIS_TrapSetDatabaseModificationNumber,
    THIS_TrapSetDatabaseAppInfoID,
    THIS_TrapSetDatabaseSortInfoID,
    THIS_TrapSetDatabaseType,
    THIS_TrapSetDatabaseCreatorID,
    THIS_TrapGetEvent,
    THIS_TrapSysHandleEvent,
    THIS_TrapFlushEvents,
    THIS_TrapKeyEventChr,
    THIS_TrapKeyEventKeyCode,
    THIS_TrapKeyEventModifiers,
    THIS_TrapControlHitControl,
    THIS_TrapFieldCopy,
    THIS_TrapFieldCut,
    THIS_TrapFieldInsert,
    THIS_TrapFieldPaste,
    THIS_TrapFieldUndo,
    THIS_TrapFieldGetInsPtPosition,
    THIS_TrapFieldGetSelection,
    THIS_TrapFieldAnyDirty,
    THIS_TrapFieldDirty,
    THIS_TrapFieldSetDirty,
    THIS_TrapFieldSetAllDirty,
    THIS_TrapFieldSetSelection,
    THIS_TrapFieldSetInsertionPoint,
    THIS_TrapFieldSetInsPtPosition,
    THIS_TrapFieldGetAttributes,
    THIS_TrapFieldSetAttributes,
    THIS_TrapFieldGetFont,
    THIS_TrapFieldSetFont,
    THIS_TrapFieldGetScrollPosition,
    THIS_TrapFieldSetScrollPosition,
    THIS_TrapFieldGetScrollValues,
    THIS_TrapFieldGetVisibleLines,
    THIS_TrapFieldGetNumberOfBlankLines,
    THIS_TrapFieldScrollable,
    THIS_TrapFieldScrollField,
    THIS_TrapFieldSetBounds,
    THIS_TrapFormGetNumberOfObjects,
    THIS_TrapFormGetObjectBounds,
    THIS_TrapFormGetObjectPosition,
    THIS_TrapFormGetObjectType,
    THIS_TrapFormSetObjectPosition,
    THIS_TrapFormSetObjectBounds,
    THIS_TrapFormGetTitle,
    THIS_TrapFormReplaceTitle,
    THIS_TrapListGetTopItem,
    THIS_TrapListSetTopItem,
    THIS_TrapListGetVisibleItems,
    THIS_TrapListScrollList,
    THIS_TrapFontGetFont,
    THIS_TrapFontSetFont,
    THIS_TrapFontSelect,
    THIS_TrapFontCharWidth,
    THIS_TrapFontCharsWidth,
    THIS_TrapFontWidthToOffset,
    THIS_TrapFontCharsInWidth,
    THIS_TrapFontWordWrap,
    THIS_TrapSyncUserName,
    THIS_TrapSuccessfulSync,
    THIS_TrapLastSync,
    THIS_TrapLocalizeNumber,
    THIS_TrapDelocalizeNumber,
    THIS_TrapLocalizeDate,
    THIS_TrapGetAppPreferences,
    THIS_TrapSetAppPreferences,
    THIS_TrapGetSysPreference,
    THIS_TrapSetSysPreference,
    THIS_TrapProgressStartDialog,
    THIS_TrapProgressStopDialog,
    THIS_TrapProgressUpdateDialog,
    THIS_TrapProgressUserCancel,
    THIS_TrapProgressPercent,
    THIS_TrapProgressPercentString,
    THIS_TrapString4ToInt,
    THIS_TrapIntToString4,
    THIS_TrapDelimitedItem,
    THIS_TrapFixedWidthString,
    THIS_TrapNormalSpacedString,
    THIS_TrapSelectOneTime,
    THIS_TrapIncrementSystemTime,
    THIS_TrapSystemTime,
    THIS_TrapStringDateTime,
    THIS_TrapStringDate,
    THIS_TrapStringTime,
    THIS_TrapPostEvent,
    THIS_TrapFormGetFocus,
    THIS_TrapFieldGetTextLength,
    THIS_TrapRandomNumber,
    THIS_TrapResetAutoOffTimer,
    THIS_TrapSetAutoOffTime,
    THIS_TrapProgramVersionString,
    THIS_TrapDynamicHeapSize,
    THIS_TrapDynamicHeapFree,
    THIS_TrapDynamicHeapMaxChunk,
    THIS_TrapSortInit,
    THIS_TrapSortAddString,
    THIS_TrapSortAddInteger,
    THIS_TrapSortAddDouble,
    THIS_TrapSortGetString,
    THIS_TrapSortGetInteger,
    THIS_TrapSortGetDouble,
    THIS_TrapSortQSort,
    THIS_TrapSortInsertionSort,
    THIS_TrapListQSort,
    THIS_TrapListInsertionSort,
    THIS_TrapFormGetAllObjectTypes,
    THIS_TrapFieldClearAll,
    THIS_TrapObjectWithPoint,
    THIS_TrapANDInt,
    THIS_TrapORInt,
    THIS_TrapXORInt,
    THIS_TrapOnesComplement,
    THIS_TrapBitValue,
    THIS_TrapBitsValue,
    THIS_TrapSetBitValue,
    THIS_TrapSetBitsValue,
    THIS_TrapIntToHex,
    THIS_TrapHexToInt,
    THIS_TrapIntToBin,
    THIS_TrapBinToInt,
    THIS_TrapGetSupportedDepths,
    THIS_TrapDepthSupported,
    THIS_TrapColorSupported,
    THIS_TrapSetDepth,
    THIS_TrapSetColor,
    THIS_TrapSaveScreenMode,
    THIS_TrapRestoreScreenMode,
    THIS_TrapCurrentDepth,
    THIS_TrapCurrentColor,
    THIS_TrapSetToDefaults,
    THIS_TrapDefaultDepth,
    THIS_TrapDefaultColor,
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
    THIS_TrapWinSaveBits,
    THIS_TrapWinRestoreBits,
    THIS_TrapSetSleepEvent,
    THIS_TrapSetWakeEvent,
    THIS_TrapGetSleepEvent,
    THIS_TrapGetWakeEvent,
    THIS_TrapGetSleepEventTime,
    THIS_TrapGetWakeEventTime,
    THIS_TrapEncryptDESString,
    THIS_TrapDecryptDESString,
    THIS_TrapSetDESKey,

    THIS_TrapEnumLast
} THIS_TrapEnum;

#ifdef __cplusplus
extern "C" {
#endif

extern Err THIS_Version(UInt16 refNum, double *version)
                THIS_LIB_TRAP(THIS_TrapVersion);

extern Err THIS_CompileInfo(UInt16 refNum, char *compileDateTime)
                THIS_LIB_TRAP(THIS_TrapCompileInfo);

extern Err THIS_SystemVersion(UInt16 refNum, double *version)
                THIS_LIB_TRAP(THIS_TrapSystemVersion);

extern Err THIS_GlobalVersionMajor(UInt16 refNum, Int32 *gblMajor)
                THIS_LIB_TRAP(THIS_TrapGlobalVersionMajor);

extern Err THIS_GlobalVersionMinor(UInt16 refNum, Int32 *gblMinor)
                THIS_LIB_TRAP(THIS_TrapGlobalVersionMinor);

extern Err THIS_GlobalX(UInt16 refNum, Int32 *x)
                THIS_LIB_TRAP(THIS_TrapGlobalX);

extern Err THIS_GlobalY(UInt16 refNum, Int32 *y)
                THIS_LIB_TRAP(THIS_TrapGlobalY);

extern Err THIS_GlobalStartX(UInt16 refNum, Int32 *startX)
                THIS_LIB_TRAP(THIS_TrapGlobalStartX);

extern Err THIS_GlobalStartY(UInt16 refNum, Int32 *startY)
                THIS_LIB_TRAP(THIS_TrapGlobalStartY);

extern Err THIS_GlobalEndX(UInt16 refNum, Int32 *endX)
                THIS_LIB_TRAP(THIS_TrapGlobalEndX);

extern Err THIS_GlobalEndY(UInt16 refNum, Int32 *endY)
                THIS_LIB_TRAP(THIS_TrapGlobalEndY);

extern Err THIS_GlobalStartPos(UInt16 refNum, Int32 *startPos)
                THIS_LIB_TRAP(THIS_TrapGlobalStartPos);

extern Err THIS_GlobalEndPos(UInt16 refNum, Int32 *endPos)
                THIS_LIB_TRAP(THIS_TrapGlobalEndPos);

extern Err THIS_GlobalWidth(UInt16 refNum, Int32 *width)
                THIS_LIB_TRAP(THIS_TrapGlobalWidth);

extern Err THIS_GlobalHeight(UInt16 refNum, Int32 *height)
                THIS_LIB_TRAP(THIS_TrapGlobalHeight);

extern Err THIS_GlobalHour(UInt16 refNum, Int32 *gblHour)
                THIS_LIB_TRAP(THIS_TrapGlobalHour);

extern Err THIS_GlobalMinute(UInt16 refNum, Int32 *gblMinute)
                THIS_LIB_TRAP(THIS_TrapGlobalMinute);

extern Err THIS_SetAlarmReset(UInt16 refNum, UInt32 resetTime, Int32 resetLimit)
                THIS_LIB_TRAP(THIS_TrapSetAlarmReset);

extern Err THIS_SetAlarm(UInt16 refNum, char *alarmPgm,
                  UInt32 alarmTime, Int32 alarmCmd,
                  char *alarmMsg, Int32 *status)
                THIS_LIB_TRAP(THIS_TrapSetAlarm);

extern Err THIS_CancelAlarm(UInt16 refNum, char *alarmPgm, Int32 *status)
                THIS_LIB_TRAP(THIS_TrapCancelAlarm);

extern Err THIS_GetAlarm(UInt16 refNum, char *alarmPgm,
                  char *alarmCmd, char *alarmMsg,
                  UInt32 *alarmTime)
                THIS_LIB_TRAP(THIS_TrapGetAlarm);

extern Err THIS_GetAlarmTime(UInt16 refNum, char *alarmPgm,
                      UInt32 *alarmTime)
                THIS_LIB_TRAP(THIS_TrapGetAlarmTime);

extern Err THIS_GetAlarmResetTime(UInt16 refNum, char *alarmPgm,
                           UInt32 *resetTime)
                THIS_LIB_TRAP(THIS_TrapGetAlarmResetTime);

extern Err THIS_GetAlarmResetLimit(UInt16 refNum, char *alarmPgm,
                            Int32 *resetLimit)
                THIS_LIB_TRAP(THIS_TrapGetAlarmResetLimit);

extern Err THIS_GetAlarmCommand(UInt16 refNum, char *alarmPgm,
                         Int32 *alarmCmd)
                THIS_LIB_TRAP(THIS_TrapGetAlarmCommand);

extern Err THIS_GetAlarmMessage(UInt16 refNum, char *alarmPgm,
                         char *alarmMsg)
                THIS_LIB_TRAP(THIS_TrapGetAlarmMessage);

extern Err THIS_AlarmLog(UInt16 refNum, char *alarmPgm,
                  char *alarmCmd, char *alarmMsg,
                  UInt32 *alarmTime)
                THIS_LIB_TRAP(THIS_TrapAlarmLog);

extern Err THIS_AlarmLogAlarmTime(UInt16 refNum, char *alarmPgm,
                           UInt32 *alarmTime)
                THIS_LIB_TRAP(THIS_TrapAlarmLogAlarmTime);

extern Err THIS_AlarmLogResetTime(UInt16 refNum, char *alarmPgm,
                           UInt32 *resetTime)
                THIS_LIB_TRAP(THIS_TrapAlarmLogResetTime);

extern Err THIS_AlarmLogResetLimit(UInt16 refNum, char *alarmPgm,
                            Int32 *resetLimit)
                THIS_LIB_TRAP(THIS_TrapAlarmLogResetLimit);

extern Err THIS_AlarmLogResetCount(UInt16 refNum, char *alarmPgm,
                            Int32 *resetCount)
                THIS_LIB_TRAP(THIS_TrapAlarmLogResetCount);

extern Err THIS_AlarmLogCommand(UInt16 refNum, char *alarmPgm,
                         Int32 *alarmCmd)
                THIS_LIB_TRAP(THIS_TrapAlarmLogCommand);

extern Err THIS_AlarmLogMessage(UInt16 refNum, char *alarmPgm,
                         char *alarmMsg)
                THIS_LIB_TRAP(THIS_TrapAlarmLogMessage);

extern Err THIS_ClearAlarmLog(UInt16 refNum, char *alarmPgm)
                THIS_LIB_TRAP(THIS_TrapClearAlarmLog);

extern Err THIS_FindDatabase(UInt16 refNum, Int32 cardNo, char *dbName, Int32 *dbID)
                THIS_LIB_TRAP(THIS_TrapFindDatabase);

extern Err THIS_DatabaseInfo(UInt16 refNum, Int32 cardNo, Int32 dbID, char *dbName)
                THIS_LIB_TRAP(THIS_TrapDatabaseInfo);

extern Err THIS_DatabaseName(UInt16 refNum, char *dbName)
                THIS_LIB_TRAP(THIS_TrapDatabaseName);

extern Err THIS_DatabaseAttributes(UInt16 refNum, Int32 *dbAttributes)
                THIS_LIB_TRAP(THIS_TrapDatabaseAttributes);

extern Err THIS_DatabaseVersion(UInt16 refNum, Int32 *dbVersion)
                THIS_LIB_TRAP(THIS_TrapDatabaseVersion);

extern Err THIS_DatabaseCreationDate(UInt16 refNum, Int32 *dbCreationDate)
                THIS_LIB_TRAP(THIS_TrapDatabaseCreationDate);

extern Err THIS_DatabaseModificationDate(UInt16 refNum, Int32 *dbModificationDate)
                THIS_LIB_TRAP(THIS_TrapDatabaseModificationDate);

extern Err THIS_DatabaseBackupDate(UInt16 refNum, Int32 *dbBackupDate)
                THIS_LIB_TRAP(THIS_TrapDatabaseBackupDate);

extern Err THIS_DatabaseModificationNumber(UInt16 refNum, Int32 *dbModificationNumber)
                THIS_LIB_TRAP(THIS_TrapDatabaseModificationNumber);

extern Err THIS_DatabaseAppInfoID(UInt16 refNum, Int32 *dbAppInfoID)
                THIS_LIB_TRAP(THIS_TrapDatabaseAppInfoID);

extern Err THIS_DatabaseSortInfoID(UInt16 refNum, Int32 *dbSortInfoID)
                THIS_LIB_TRAP(THIS_TrapDatabaseSortInfoID);

extern Err THIS_DatabaseType(UInt16 refNum, Int32 *dbType)
                THIS_LIB_TRAP(THIS_TrapDatabaseType);

extern Err THIS_DatabaseCreatorID(UInt16 refNum, Int32 *dbCreatorID)
                THIS_LIB_TRAP(THIS_TrapDatabaseCreatorID);

extern Err THIS_DatabaseTotalSize(UInt16 refNum, Int32 cardNo, Int32 dbID, Int32 *dbTotalSize)
                THIS_LIB_TRAP(THIS_TrapDatabaseTotalSize);

extern Err THIS_DatabaseNumRecords(UInt16 refNum, Int32 *dbNumRecords)
                THIS_LIB_TRAP(THIS_TrapDatabaseNumRecords);

extern Err THIS_DatabaseDataSize(UInt16 refNum, Int32 *dbDataSize)
                THIS_LIB_TRAP(THIS_TrapDatabaseDataSize);

extern Err THIS_DeleteDatabase(UInt16 refNum, Int32 cardNo, Int32 dbID, Int32 *status)
                THIS_LIB_TRAP(THIS_TrapDeleteDatabase);

extern Err THIS_GetNextDatabaseByTypeCreator(UInt16 refNum, Int32 newSearch,
                        Int32 dbType, Int32 dbCreatorID, 
                        Int32 onlyLatestVersion, Int32 *dbID)
                THIS_LIB_TRAP(THIS_TrapGetNextDatabaseByTypeCreator);

extern Err THIS_DatabaseCardNo(UInt16 refNum, Int32 *dbCardNo)
                THIS_LIB_TRAP(THIS_TrapDatabaseCardNo);

extern Err THIS_NumDatabases(UInt16 refNum, Int32 cardNo, Int32 *nbr)
                THIS_LIB_TRAP(THIS_TrapNumDatabases);

extern Err THIS_NumCards(UInt16 refNum, Int32 *nbr)
                THIS_LIB_TRAP(THIS_TrapNumCards);

extern Err THIS_GetDatabase(UInt16 refNum, Int32 cardNo, Int32 index, Int32 *dbID)
                THIS_LIB_TRAP(THIS_TrapGetDatabase);

extern Err THIS_SetDatabaseName(UInt16 refNum, Int32 cardNo, Int32 dbID, char *dbName, Int32 *status)
                THIS_LIB_TRAP(THIS_TrapSetDatabaseName);

extern Err THIS_SetDatabaseAttributes(UInt16 refNum, Int32 cardNo, Int32 dbID, Int32 dbAttributes, Int32 *status)
                THIS_LIB_TRAP(THIS_TrapSetDatabaseAttributes);

extern Err THIS_SetDatabaseVersion(UInt16 refNum, Int32 cardNo, Int32 dbID, Int32 dbVersion, Int32 *status)
                THIS_LIB_TRAP(THIS_TrapSetDatabaseVersion);

extern Err THIS_SetDatabaseCreationDate(UInt16 refNum, Int32 cardNo, Int32 dbID, 
                                 Int32 dbCreationDate, Int32 *status)
                THIS_LIB_TRAP(THIS_TrapSetDatabaseCreationDate);

extern Err THIS_SetDatabaseModificationDate(UInt16 refNum, Int32 cardNo, Int32 dbID, 
                                 Int32 dbModificationDate, Int32 *status)
                THIS_LIB_TRAP(THIS_TrapSetDatabaseModificationDate);

extern Err THIS_SetDatabaseBackupDate(UInt16 refNum, Int32 cardNo, Int32 dbID, 
                                 Int32 dbBackupDate, Int32 *status)
                THIS_LIB_TRAP(THIS_TrapSetDatabaseBackupDate);

extern Err THIS_SetDatabaseModificationNumber(UInt16 refNum, Int32 cardNo, Int32 dbID, 
                                 Int32 dbModificationNumber, Int32 *status)
                THIS_LIB_TRAP(THIS_TrapSetDatabaseModificationNumber);

extern Err THIS_SetDatabaseAppInfoID(UInt16 refNum, Int32 cardNo, Int32 dbID, 
                              Int32 dbAppInfoID, Int32 *status)
                THIS_LIB_TRAP(THIS_TrapSetDatabaseAppInfoID);

extern Err THIS_SetDatabaseSortInfoID(UInt16 refNum, Int32 cardNo, Int32 dbID, 
                              Int32 dbSortInfoID, Int32 *status)
                THIS_LIB_TRAP(THIS_TrapSetDatabaseSortInfoID);

extern Err THIS_SetDatabaseType(UInt16 refNum, Int32 cardNo, Int32 dbID, 
                              Int32 dbType, Int32 *status)
                THIS_LIB_TRAP(THIS_TrapSetDatabaseType);

extern Err THIS_SetDatabaseCreatorID(UInt16 refNum, Int32 cardNo, Int32 dbID, 
                              Int32 dbCreatorID, Int32 *status)
                THIS_LIB_TRAP(THIS_TrapSetDatabaseCreatorID);

extern Err THIS_GetEvent(UInt16 refNum, Int32 timeoutTicks, 
                  Int32 consumePenEvents, Int32 returnVirtualEvents,
                  Int32 *eventType)
                THIS_LIB_TRAP(THIS_TrapGetEvent);

extern Err THIS_SysHandleEvent(UInt16 refNum)
                THIS_LIB_TRAP(THIS_TrapSysHandleEvent);

extern Err THIS_FlushEvents(UInt16 refNum)
                THIS_LIB_TRAP(THIS_TrapFlushEvents);

extern Err THIS_KeyEventChr(UInt16 refNum, Int32 *keyChr)
                THIS_LIB_TRAP(THIS_TrapKeyEventChr);

extern Err THIS_KeyEventKeyCode(UInt16 refNum, Int32 *keyCode)
                THIS_LIB_TRAP(THIS_TrapKeyEventKeyCode);

extern Err THIS_KeyEventModifiers(UInt16 refNum, Int32 *modifiers)
                THIS_LIB_TRAP(THIS_TrapKeyEventModifiers);

extern Err THIS_ControlHitControl(UInt16 refNum, Int32 objID)
                THIS_LIB_TRAP(THIS_TrapControlHitControl);

extern Err THIS_FieldCopy(UInt16 refNum, Int32 objID)
                THIS_LIB_TRAP(THIS_TrapFieldCopy);

extern Err THIS_FieldCut(UInt16 refNum, Int32 objID)
                THIS_LIB_TRAP(THIS_TrapFieldCut);

extern Err THIS_FieldInsert(UInt16 refNum, Int32 objID, char* insString)
                THIS_LIB_TRAP(THIS_TrapFieldInsert);

extern Err THIS_FieldPaste(UInt16 refNum, Int32 objID)
                THIS_LIB_TRAP(THIS_TrapFieldPaste);

extern Err THIS_FieldUndo(UInt16 refNum, Int32 objID)
                THIS_LIB_TRAP(THIS_TrapFieldUndo);

extern Err THIS_FieldGetInsPtPosition(UInt16 refNum, Int32 objID, Int32 *pos)
                THIS_LIB_TRAP(THIS_TrapFieldGetInsPtPosition);

extern Err THIS_FieldGetSelection(UInt16 refNum, Int32 objID, Int32 *startPos)
                THIS_LIB_TRAP(THIS_TrapFieldGetSelection);

extern Err THIS_FieldAnyDirty(UInt16 refNum, Int32 *dirty)
                THIS_LIB_TRAP(THIS_TrapFieldAnyDirty);

extern Err THIS_FieldDirty(UInt16 refNum, Int32 objID, Int32 *dirty)
                THIS_LIB_TRAP(THIS_TrapFieldDirty);

extern Err THIS_FieldSetDirty(UInt16 refNum, Int32 objID, Int32 dirty)
                THIS_LIB_TRAP(THIS_TrapFieldSetDirty);

extern Err THIS_FieldSetAllDirty(UInt16 refNum, Int32 dirty)
                THIS_LIB_TRAP(THIS_TrapFieldSetAllDirty);

extern Err THIS_FieldSetSelection(UInt16 refNum, Int32 objID, Int32 startPos, Int32 endPos)
                THIS_LIB_TRAP(THIS_TrapFieldSetSelection);

extern Err THIS_FieldSetInsertionPoint(UInt16 refNum, Int32 objID, Int32 pos)
                THIS_LIB_TRAP(THIS_TrapFieldSetInsertionPoint);

extern Err THIS_FieldSetInsPtPosition(UInt16 refNum, Int32 objID, Int32 pos)
                THIS_LIB_TRAP(THIS_TrapFieldSetInsPtPosition);

extern Err THIS_FieldGetAttributes(UInt16 refNum, Int32 objID, Int32 *attributes)
                THIS_LIB_TRAP(THIS_TrapFieldGetAttributes);

extern Err THIS_FieldSetAttributes(UInt16 refNum, Int32 objID, Int32 attributes)
                THIS_LIB_TRAP(THIS_TrapFieldSetAttributes);

extern Err THIS_FieldGetFont(UInt16 refNum, Int32 objID, Int32 *fontId)
                THIS_LIB_TRAP(THIS_TrapFieldGetFont);

extern Err THIS_FieldSetFont(UInt16 refNum, Int32 objID, Int32 fontId)
                THIS_LIB_TRAP(THIS_TrapFieldSetFont);

extern Err THIS_FieldGetScrollPosition(UInt16 refNum, Int32 objID, Int32 *position)
                THIS_LIB_TRAP(THIS_TrapFieldGetScrollPosition);

extern Err THIS_FieldSetScrollPosition(UInt16 refNum, Int32 objID, Int32 position)
                THIS_LIB_TRAP(THIS_TrapFieldSetScrollPosition);

extern Err THIS_FieldGetScrollValues(UInt16 refNum, Int32 objID, Int32 *totalLines)
                THIS_LIB_TRAP(THIS_TrapFieldGetScrollValues);

extern Err THIS_FieldGetVisibleLines(UInt16 refNum, Int32 objID, Int32 *lines)
                THIS_LIB_TRAP(THIS_TrapFieldGetVisibleLines);

extern Err THIS_FieldGetNumberOfBlankLines(UInt16 refNum, Int32 objID, Int32 *lines)
                THIS_LIB_TRAP(THIS_TrapFieldGetNumberOfBlankLines);

extern Err THIS_FieldScrollable(UInt16 refNum, Int32 objID, Int32 direction, Int32 *yesNo)
                THIS_LIB_TRAP(THIS_TrapFieldScrollable);

extern Err THIS_FieldScrollField(UInt16 refNum, Int32 objID, Int32 nbrLines, Int32 direction)
                THIS_LIB_TRAP(THIS_TrapFieldScrollField);

extern Err THIS_FieldSetBounds(UInt16 refNum, Int32 objID, 
                        Int32 topLeftX, Int32 topLeftY, 
                        Int32 width, Int32 height)
                THIS_LIB_TRAP(THIS_TrapFieldSetBounds);

extern Err THIS_FormGetNumberOfObjects(UInt16 refNum, Int32 *nbr)
                THIS_LIB_TRAP(THIS_TrapFormGetNumberOfObjects);

extern Err THIS_FormGetObjectBounds(UInt16 refNum, Int32 objID, Int32 *x)
                THIS_LIB_TRAP(THIS_TrapFormGetObjectBounds);

extern Err THIS_FormGetObjectPosition(UInt16 refNum, Int32 objID, Int32 *x)
                THIS_LIB_TRAP(THIS_TrapFormGetObjectPosition);

extern Err THIS_FormGetObjectType(UInt16 refNum, Int32 objID, Int32 *type)
                THIS_LIB_TRAP(THIS_TrapFormGetObjectType);

extern Err THIS_FormSetObjectPosition(UInt16 refNum, Int32 objID, Int32 x, Int32 y)
                THIS_LIB_TRAP(THIS_TrapFormSetObjectPosition);

extern Err THIS_FormSetObjectBounds(UInt16 refNum, Int32 objID, 
                             Int32 topLeftX, Int32 topLeftY, 
                             Int32 width, Int32 height)
                THIS_LIB_TRAP(THIS_TrapFormSetObjectBounds);

extern Err THIS_FormGetTitle(UInt16 refNum, char *title)
                THIS_LIB_TRAP(THIS_TrapFormGetTitle);

extern Err THIS_FormReplaceTitle(UInt16 refNum, char* title, Int32 forceLength)
                THIS_LIB_TRAP(THIS_TrapFormReplaceTitle);

extern Err THIS_ListGetTopItem(UInt16 refNum, Int32 objID, Int32 *topItem)
                THIS_LIB_TRAP(THIS_TrapListGetTopItem);

extern Err THIS_ListSetTopItem(UInt16 refNum, Int32 objID, Int32 topItem)
                THIS_LIB_TRAP(THIS_TrapListSetTopItem);

extern Err THIS_ListGetVisibleItems(UInt16 refNum, Int32 objID, Int32 *visibleItems)
                THIS_LIB_TRAP(THIS_TrapListGetVisibleItems);

extern Err THIS_ListScrollList(UInt16 refNum, Int32 objID, Int32 direction, 
                     Int32 nbrItems, Int32 *result)
                THIS_LIB_TRAP(THIS_TrapListScrollList);

extern Err THIS_FontGetFont(UInt16 refNum, Int32 *fontId)
                THIS_LIB_TRAP(THIS_TrapFontGetFont);

extern Err THIS_FontSetFont(UInt16 refNum, Int32 fontId, Int32 *oldFontId)
                THIS_LIB_TRAP(THIS_TrapFontSetFont);

extern Err THIS_FontSelect(UInt16 refNum, Int32 *fontId)
                THIS_LIB_TRAP(THIS_TrapFontSelect);

extern Err THIS_FontCharWidth(UInt16 refNum, char *charString, Int32 *width)
                THIS_LIB_TRAP(THIS_TrapFontCharWidth);

extern Err THIS_FontCharsWidth(UInt16 refNum, char *charString, Int32 optionalLen, Int32 *width)
                THIS_LIB_TRAP(THIS_TrapFontCharsWidth);

extern Err THIS_FontWidthToOffset(UInt16 refNum, char *charString, Int32 optionalLen, 
                           Int32 width, Int32 *offset)
                THIS_LIB_TRAP(THIS_TrapFontWidthToOffset);

extern Err THIS_FontCharsInWidth(UInt16 refNum, char *charString, Int32 optionalLen, 
                          Int32 width, Int32 *length)
                THIS_LIB_TRAP(THIS_TrapFontCharsInWidth);

extern Err THIS_FontWordWrap(UInt16 refNum, char *charString, Int32 width, Int32 *length)
                THIS_LIB_TRAP(THIS_TrapFontWordWrap);

extern Err THIS_SyncUserName(UInt16 refNum, char *userName)
                THIS_LIB_TRAP(THIS_TrapSyncUserName);

extern Err THIS_SuccessfulSync(UInt16 refNum, Int32 *syncDate)
                THIS_LIB_TRAP(THIS_TrapSuccessfulSync);

extern Err THIS_LastSync(UInt16 refNum, Int32 *syncDate)
                THIS_LIB_TRAP(THIS_TrapLastSync);

extern Err THIS_LocalizeNumber(UInt16 refNum, char *stdNbrStr, char *localNbrStr)
                THIS_LIB_TRAP(THIS_TrapLocalizeNumber);

extern Err THIS_DelocalizeNumber(UInt16 refNum, char *localNbrStr, char *stdNbrStr)
                THIS_LIB_TRAP(THIS_TrapDelocalizeNumber);

extern Err THIS_LocalizeDate(UInt16 refNum, char *stdDateStr, Int32 ToDateFormat,
                          Int32 longDateFormat, char *localDateStr)
                THIS_LIB_TRAP(THIS_TrapLocalizeDate);

extern Err THIS_GetAppPreferences(UInt16 refNum, char *pgmName, 
                           Int32 prefId, Int32 saved, char *data)
                THIS_LIB_TRAP(THIS_TrapGetAppPreferences);

extern Err THIS_SetAppPreferences(UInt16 refNum, char *pgmName, 
                           Int32 prefId, char *data, Int32 saved, Int32 *status)
                THIS_LIB_TRAP(THIS_TrapSetAppPreferences);

extern Err THIS_GetSysPreference(UInt16 refNum, Int32 prefID, Int32 *data)
                THIS_LIB_TRAP(THIS_TrapGetSysPreference);

extern Err THIS_SetSysPreference(UInt16 refNum, Int32 prefID, Int32 data)
                THIS_LIB_TRAP(THIS_TrapSetSysPreference);

extern Err THIS_ProgressStartDialog(UInt16 refNum, char* title)
                THIS_LIB_TRAP(THIS_TrapProgressStartDialog);

extern Err THIS_ProgressStopDialog(UInt16 refNum, Int32 force)
                THIS_LIB_TRAP(THIS_TrapProgressStopDialog);

extern Err THIS_ProgressUpdateDialog(UInt16 refNum, Int32 error, char* message)
                THIS_LIB_TRAP(THIS_TrapProgressUpdateDialog);

extern Err THIS_ProgressUserCancel(UInt16 refNum, Int32 *canceled)
                THIS_LIB_TRAP(THIS_TrapProgressUserCancel);

extern Err THIS_ProgressPercent(UInt16 refNum, Int32 current, Int32 count, Int32 *percent)
                THIS_LIB_TRAP(THIS_TrapProgressPercent);

extern Err THIS_ProgressPercentString(UInt16 refNum, Int32 percent, Int32 resolution, 
                               char *completeChar, char *incompleteChar, char *strValue)
                THIS_LIB_TRAP(THIS_TrapProgressPercentString);

extern Err THIS_String4ToInt(UInt16 refNum, char *fourByteString, UInt32 *intValue)
                THIS_LIB_TRAP(THIS_TrapString4ToInt);

extern Err THIS_IntToString4(UInt16 refNum, UInt32 intValue, char *fourByteString)
                THIS_LIB_TRAP(THIS_TrapIntToString4);

extern Err THIS_DelimitedItem(UInt16 refNum, 
                       char *inputStr, char *delimiter, Int32 nbr,
                       char *item)
                THIS_LIB_TRAP(THIS_TrapDelimitedItem);

extern Err THIS_FixedWidthString(UInt16 refNum, char *origStr, Int32 width, 
                          Int32 options, char *fixedStr)
                THIS_LIB_TRAP(THIS_TrapFixedWidthString);

extern Err THIS_NormalSpacedString(UInt16 refNum, char *origStr, char *normalStr)
                THIS_LIB_TRAP(THIS_TrapNormalSpacedString);

extern Err THIS_SelectOneTime(UInt16 refNum, Int32 defHour, Int32 defMinute,
                       char *title, Int32 *newTimeSelected)
                THIS_LIB_TRAP(THIS_TrapSelectOneTime);

extern Err THIS_IncrementSystemTime(UInt16 refNum, UInt32 oldSysTime,
                            Int32 hours, Int32 minutes, Int32 seconds,
                            UInt32 *newSysTime)
                THIS_LIB_TRAP(THIS_TrapIncrementSystemTime);

extern Err THIS_SystemTime(UInt16 refNum, 
                   char *strDate, char *strTime, Int32 seconds, 
                   Int32 ToDateFormat,
                   UInt32 *sysTime)
                THIS_LIB_TRAP(THIS_TrapSystemTime);

extern Err THIS_StringDateTime(UInt16 refNum, 
                        UInt32 sysTime,
                        Int32 ToDateFormat,
                        Int32 ToTimeFormat,
                        Int32 AMPMFormat,
                        char *strDateTime)
                THIS_LIB_TRAP(THIS_TrapStringDateTime);

extern Err THIS_StringDate(UInt16 refNum, 
                    UInt32 sysTime,
                    Int32 ToDateFormat,
                    char *strDate)
                THIS_LIB_TRAP(THIS_TrapStringDate);

extern Err THIS_StringTime(UInt16 refNum, 
                    UInt32 sysTime,
                    Int32 ToTimeFormat,
                    Int32 AMPMFormat,
                    char *strTime)
                THIS_LIB_TRAP(THIS_TrapStringTime);

extern Err THIS_PostEvent(UInt16 refNum, Int32 eventNbr)
                THIS_LIB_TRAP(THIS_TrapPostEvent);

extern Err THIS_FormGetFocus(UInt16 refNum, Int32 *objID)
                THIS_LIB_TRAP(THIS_TrapFormGetFocus);

extern Err THIS_FieldGetTextLength(UInt16 refNum, Int32 objID, Int32 *txtLen)
                THIS_LIB_TRAP(THIS_TrapFieldGetTextLength);

extern Err THIS_RandomNumber(UInt16 refNum, Int32 seed, Int32 minNbr, Int32 maxNbr, Int32 *nbr)
                THIS_LIB_TRAP(THIS_TrapRandomNumber);

extern Err THIS_ResetAutoOffTimer(UInt16 refNum)
                THIS_LIB_TRAP(THIS_TrapResetAutoOffTimer);

extern Err THIS_SetAutoOffTime(UInt16 refNum, Int32 newSeconds, Int32 *oldSeconds)
                THIS_LIB_TRAP(THIS_TrapSetAutoOffTime);

extern Err THIS_ProgramVersionString(UInt16 refNum, Int32 cardNbr, char *pgmName, char *verStr)
                THIS_LIB_TRAP(THIS_TrapProgramVersionString);

extern Err THIS_DynamicHeapSize(UInt16 refNum, Int32 *heapSize)
                THIS_LIB_TRAP(THIS_TrapDynamicHeapSize);

extern Err THIS_DynamicHeapFree(UInt16 refNum, Int32 *freeSize)
                THIS_LIB_TRAP(THIS_TrapDynamicHeapFree);

extern Err THIS_DynamicHeapMaxChunk(UInt16 refNum, Int32 *maxChunkSize)
                THIS_LIB_TRAP(THIS_TrapDynamicHeapMaxChunk);

extern Err THIS_SortInit(UInt16 refNum, Int32 maxItems, char *itemType, Int32 *error)
                THIS_LIB_TRAP(THIS_TrapSortInit);

extern Err THIS_SortAddString(UInt16 refNum, char *strItem, Int32 *error)
                THIS_LIB_TRAP(THIS_TrapSortAddString);

extern Err THIS_SortAddInteger(UInt16 refNum, Int32 intItem, Int32 *error)
                THIS_LIB_TRAP(THIS_TrapSortAddInteger);

extern Err THIS_SortAddDouble(UInt16 refNum, double dblItem, Int32 *error)
                THIS_LIB_TRAP(THIS_TrapSortAddDouble);

extern Err THIS_SortGetString(UInt16 refNum, Int32 index, char *strItem)
                THIS_LIB_TRAP(THIS_TrapSortGetString);

extern Err THIS_SortGetInteger(UInt16 refNum, Int32 index, Int32 *intItem)
                THIS_LIB_TRAP(THIS_TrapSortGetInteger);

extern Err THIS_SortGetDouble(UInt16 refNum, Int32 index, double *dblItem)
                THIS_LIB_TRAP(THIS_TrapSortGetDouble);

extern Err THIS_SortQSort(UInt16 refNum, Int32 reverseSort, Int32 caselessSort, Int32 *numItems)
                THIS_LIB_TRAP(THIS_TrapSortQSort);

extern Err THIS_SortInsertionSort(UInt16 refNum, Int32 reverseSort, Int32 caselessSort, Int32 *numItems)
                THIS_LIB_TRAP(THIS_TrapSortInsertionSort);

extern Err THIS_ListQSort(UInt16 refNum, Int32 objID, Int32 reverseSort, Int32 caselessSort, Int32 *numItems)
                THIS_LIB_TRAP(THIS_TrapListQSort);

extern Err THIS_ListInsertionSort(UInt16 refNum, Int32 objID, Int32 reverseSort, Int32 caselessSort, Int32 *numItems)
                THIS_LIB_TRAP(THIS_TrapListInsertionSort);

extern Err THIS_FormGetAllObjectTypes(UInt16 refNum, Int32 objID, Int32 *type)
                THIS_LIB_TRAP(THIS_TrapFormGetAllObjectTypes);

extern Err THIS_FieldClearAll(UInt16 refNum)
                THIS_LIB_TRAP(THIS_TrapFieldClearAll);

extern Err THIS_ObjectWithPoint(UInt16 refNum, Int32 x, Int32 y, 
                         Int32 returnType, Int32 searchOption, Int32 *obj)
                THIS_LIB_TRAP(THIS_TrapObjectWithPoint);

extern Err THIS_ANDInt(UInt16 refNum, Int32 int1, Int32 int2, Int32 *result)
                THIS_LIB_TRAP(THIS_TrapANDInt);

extern Err THIS_ORInt(UInt16 refNum, Int32 int1, Int32 int2, Int32 *result)
                THIS_LIB_TRAP(THIS_TrapORInt);

extern Err THIS_XORInt(UInt16 refNum, Int32 int1, Int32 int2, Int32 *result)
                THIS_LIB_TRAP(THIS_TrapXORInt);

extern Err THIS_OnesComplement(UInt16 refNum, Int32 intValue, Int32 *result)
                THIS_LIB_TRAP(THIS_TrapOnesComplement);

extern Err THIS_BitValue(UInt16 refNum, Int32 intValue, Int32 bitNumber, Int32 *result)
                THIS_LIB_TRAP(THIS_TrapBitValue);

extern Err THIS_BitsValue(UInt16 refNum, Int32 intValue, Int32 startBit, Int32 endBit, Int32 *result)
                THIS_LIB_TRAP(THIS_TrapBitsValue);

extern Err THIS_SetBitValue(UInt16 refNum, Int32 intValue, Int32 bitNumber, 
                  Int32 bitValue, Int32 *result)
                THIS_LIB_TRAP(THIS_TrapSetBitValue);

extern Err THIS_SetBitsValue(UInt16 refNum, Int32 intValue, Int32 bitsValue, 
                      Int32 startBit, Int32 endBit, Int32 *result)
                THIS_LIB_TRAP(THIS_TrapSetBitsValue);

extern Err THIS_IntToHex(UInt16 refNum, Int32 intValue, Int32 trimLeading, char *hexValue)
                THIS_LIB_TRAP(THIS_TrapIntToHex);

extern Err THIS_HexToInt(UInt16 refNum, char *hexValue, Int32 *intValue)
                THIS_LIB_TRAP(THIS_TrapHexToInt);

extern Err THIS_IntToBin(UInt16 refNum, Int32 intValue, Int32 trimLeading, char *binValue)
                THIS_LIB_TRAP(THIS_TrapIntToBin);

extern Err THIS_BinToInt(UInt16 refNum, char *binValue, Int32 *intValue)
                THIS_LIB_TRAP(THIS_TrapBinToInt);

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

extern Err THIS_SaveScreenMode(UInt16 refNum)
                THIS_LIB_TRAP(THIS_TrapSaveScreenMode);

extern Err THIS_RestoreScreenMode(UInt16 refNum)
                THIS_LIB_TRAP(THIS_TrapRestoreScreenMode);

extern Err THIS_CurrentDepth(UInt16 refNum, Int32 *depth)
                THIS_LIB_TRAP(THIS_TrapCurrentDepth);

extern Err THIS_CurrentColor(UInt16 refNum, Int32 *boolean)
                THIS_LIB_TRAP(THIS_TrapCurrentColor);

extern Err THIS_SetToDefaults(UInt16 refNum)
                THIS_LIB_TRAP(THIS_TrapSetToDefaults);

extern Err THIS_DefaultDepth(UInt16 refNum, Int32 *depth)
                THIS_LIB_TRAP(THIS_TrapDefaultDepth);

extern Err THIS_DefaultColor(UInt16 refNum, Int32 *boolean)
                THIS_LIB_TRAP(THIS_TrapDefaultColor);

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

extern Err THIS_WinSaveBits(UInt16 refNum, Int32 index, Int32 x, Int32 y,
                                    Int32 width, Int32 height)
                THIS_LIB_TRAP(THIS_TrapWinSaveBits);

extern Err THIS_WinRestoreBits(UInt16 refNum, Int32 index, Int32 x, Int32 y)
                THIS_LIB_TRAP(THIS_TrapWinRestoreBits);

extern Err THIS_SetSleepEvent(UInt16 refNum, Int32 eventNbr)
                THIS_LIB_TRAP(THIS_TrapSetSleepEvent);

extern Err THIS_SetWakeEvent(UInt16 refNum, Int32 eventNbr)
                THIS_LIB_TRAP(THIS_TrapSetWakeEvent);

extern Err THIS_GetSleepEvent(UInt16 refNum, Int32 *eventNbr)
                THIS_LIB_TRAP(THIS_TrapGetSleepEvent);

extern Err THIS_GetWakeEvent(UInt16 refNum, Int32 *eventNbr)
                THIS_LIB_TRAP(THIS_TrapGetWakeEvent);

extern Err THIS_GetSleepEventTime(UInt16 refNum, Int32 *eventTime)
                THIS_LIB_TRAP(THIS_TrapGetSleepEventTime);

extern Err THIS_GetWakeEventTime(UInt16 refNum, Int32 *eventTime)
                THIS_LIB_TRAP(THIS_TrapGetWakeEventTime);

extern Err THIS_EncryptDESString(UInt16 refNum, char* decryptedStr, char *encryptedStr)
                THIS_LIB_TRAP(THIS_TrapEncryptDESString);

extern Err THIS_DecryptDESString(UInt16 refNum, char* encryptedStr, char *decryptedStr)
                THIS_LIB_TRAP(THIS_TrapDecryptDESString);

extern Err THIS_SetDESKey(UInt16 refNum, char* keyStr)
                THIS_LIB_TRAP(THIS_TrapSetDESKey);

#ifdef __cplusplus
}
#endif

#endif	// __NSBSystemLibPrototypes_H__

