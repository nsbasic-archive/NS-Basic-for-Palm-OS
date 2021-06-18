/*
 * @(#)palm.c
 *
 * Copyright 2000, Aaron Ardiri (mailto:aaron@ardiri.com)
 * All rights reserved.
 *
 * This file was generated as part of the "pilrctst" program developed for 
 * the Palm Computing Platform designed by Palm: http://www.palm.com/ 
 *
 * The contents of this file are to be used for educational purposes
 * only in understanding the PilRC application.  Redistribution or 
 * modification without prior consent of the original author is prohibited. 
 */

#include "palm.h"

// variables
static Int32 evtTimeOut;

// interface
static Boolean mainFormEventHandler(EventType *);
static Boolean infoFormEventHandler(EventType *);
static Boolean tSTLFormEventHandler(EventType *);

/**
 * The Form:mainForm event handling routine.
 *
 * @param event the event to process.
 * @return true if the event was handled, false otherwise.
 */
static Boolean 
mainFormEventHandler(EventType *event)
{
  Boolean processed = false;

  switch (event->eType) 
  {
    case frmOpenEvent:
         FrmDrawForm(FrmGetActiveForm());
         processed = true;
         break;

    default:
         break;
  }

  return processed;
}

/**
 * The Form:infoForm event handling routine.
 *
 * @param event the event to process.
 * @return true if the event was handled, false otherwise.
 */
static Boolean 
infoFormEventHandler(EventType *event)
{
  Boolean processed = false;

  switch (event->eType) 
  {
    case frmOpenEvent:
         FrmDrawForm(FrmGetActiveForm());
         processed = true;
         break;
   
    case ctlSelectEvent:

         switch (event->data.ctlSelect.controlID)
         {
           case infoFormOkButton:

                // send a close event
	        {
             	  EventType event;

                  MemSet(&event, sizeof(EventType), 0);
                  event.eType = frmCloseEvent;
                  event.data.frmClose.formID = FrmGetActiveFormID();
                  EvtAddEventToQueue(&event);
                }

                processed = true;
                break;

           default:
                break;
         }
         break;

    default:
         break;
  }

  return processed;
}

/**
 * The Form:tSTLForm event handling routine.
 *
 * @param event the event to process.
 * @return true if the event was handled, false otherwise.
 */
static Boolean 
tSTLFormEventHandler(EventType *event)
{
  Boolean processed = false;

  switch (event->eType) 
  {
    case frmOpenEvent:
         FrmDrawForm(FrmGetActiveForm());
         {
	   FormType  *frm;
	   FieldType *fldType;
	   MemHandle memHandle;

	   frm = FrmGetActiveForm();

           fldType = 
	     (FieldType *)FrmGetObjectPtr(frm,
	         FrmGetObjectIndex(frm, tSTLFormTypeField));
           memHandle = MemHandleNew(32);
	   StrCopy(MemHandleLock(memHandle), ""); MemHandleUnlock(memHandle);
	   FldSetTextHandle(fldType, memHandle);
         }

         // simulate the tap of the "imperial button"
	 {
	   EventType event;

           MemSet(&event, sizeof(EventType), 0);
	   event.eType = ctlSelectEvent;
	   event.data.ctlSelect.controlID = tSTLFormMetricButton;
	   EvtAddEventToQueue(&event);
	 }
         processed = true;
         break;
   
    case ctlSelectEvent:

         switch (event->data.ctlSelect.controlID)
         {
           case tSTLFormMetricButton:
           case tSTLFormImperialButton:
                {
                  FormType  *frm;
		  ListType  *lstTable;
	          FieldType *fldType;
                  MemHandle memHandle, memTableHandle, memLists;
		  MemPtr    ptrStringTable;
		  UInt16    count, index, tblIndex;

		  frm = FrmGetActiveForm();

                  index    = 
		    event->data.ctlSelect.controlID - tSTLFormMetricButton;
                  tblIndex = stringTableMetric + index;

		  memTableHandle = DmGetResource('tSTL', tblIndex);
                  ptrStringTable = (MemPtr)MemHandleLock(memTableHandle);
		  count    =  
  (*((UInt8 *)(ptrStringTable + StrLen((Char *)ptrStringTable) + 1)) << 8) |
   *((UInt8 *)(ptrStringTable + StrLen((Char *)ptrStringTable) + 2));
		  memLists = SysFormPointerArrayToStrings(
                    ptrStringTable + StrLen((Char *)ptrStringTable) + 3, count);
		  MemHandleUnlock(memTableHandle);
		  DmReleaseResource(memTableHandle);

		  lstTable = 
		    (ListType *)FrmGetObjectPtr(frm,
		      FrmGetObjectIndex(frm, tSTLFormList));
                  LstSetListChoices(lstTable, MemHandleLock(memLists), count); 
                  LstDrawList(lstTable);

                  fldType = 
                    (FieldType *)FrmGetObjectPtr(frm,
                       FrmGetObjectIndex(frm, tSTLFormTypeField));
                  memHandle = FldGetTextHandle(fldType);
                  SysStringByIndex(stringTableType, index, 
                                   MemHandleLock(memHandle), 32);
                  FldSetTextHandle(fldType, memHandle);
		  MemHandleUnlock(memHandle);
		  FldDrawField(fldType);
		}

                processed = true;
                break;

           case tSTLFormOkButton:

                // send a close event
	        {
	          EventType event;

                  MemSet(&event, sizeof(EventType), 0);
                  event.eType = frmCloseEvent;
                  event.data.frmClose.formID = FrmGetActiveFormID();
	          EvtAddEventToQueue(&event);
	        }

                processed = true;
                break;

           default:
                break;
         }
         break;

    case frmCloseEvent:

         // clean up memory allocations
	 {
	   FormType  *frm;
	   FieldType *fldType;
           ListType  *lstTable;
	   MemHandle memHandle;

	   frm = FrmGetActiveForm();

           fldType = 
	     (FieldType *)FrmGetObjectPtr(frm,
	         FrmGetObjectIndex(frm, tSTLFormTypeField));
           memHandle = FldGetTextHandle(fldType);
	   FldSetTextHandle(fldType, NULL);
	   MemHandleFree(memHandle);

	   lstTable = 
             (ListType *)FrmGetObjectPtr(frm,
		FrmGetObjectIndex(frm, tSTLFormList));
           if (lstTable->itemsText) {
	     MemPtrUnlock(lstTable->itemsText);
	     MemPtrFree(lstTable->itemsText);
	   }
	 }

	 break;

    default:
         break;
  }

  return processed;
}

/**
 * The Palm Computing Platform initialization routine.
 */
void  
InitApplication()
{
  evtTimeOut = evtWaitForever;

  // load the FONT 128 into memory
  {
    MemHandle fntHandle = DmGetResource('NFNT', font128);
    FntDefineFont(128, (FontPtr)MemHandleLock(fntHandle));
    MemHandleUnlock(fntHandle);
  }
}

/**
 * The Palm Computing Platform entry routine (mainline).
 *
 * @param cmd         a word value specifying the launch code.
 * @param cmdPBP      pointer to a structure associated with the launch code.
 * @param launchFlags additional launch flags.
 * @return zero if launch successful, non zero otherwise.
 */
UInt32  
PilotMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
  UInt32 result = 0;

  // what type of launch was this?
  switch (cmd) 
  {
    case sysAppLaunchCmdNormalLaunch:
         {
           // this program needs at LEAST palmos 3.0
           if (DeviceSupportsVersion(romVersion3)) {

             // initialize the application
             InitApplication();

             // process the event loop
             FrmGotoForm(mainForm);
             EventLoop();

             // terminate the application
             EndApplication();
           }

           // no palm os 3.0? get out!
	   else {

             // display a incompatability dialog
             FormPtr form = FrmInitForm(deviForm);
             FrmDoDialog(form);
             FrmDeleteForm(form);

             // lets exit the application "gracefully" :>
             if (!DeviceSupportsVersion(romVersion2)) {
               AppLaunchWithCommand(sysFileCDefaultApp,
	                            sysAppLaunchCmdNormalLaunch,NULL);
             }
           }
         }
         break;

    default:
         break;
  }

  return result;
}

/**
 * The application event handling routine.
 *
 * @param event the event to process.
 * @return true if the event was handled, false otherwise.
 */
Boolean 
ApplicationHandleEvent(EventType *event)
{
  Boolean processed = false;

  switch (event->eType)
  {
    case frmLoadEvent:
         {
           UInt16   formID = event->data.frmLoad.formID;
           FormType *frm   = FrmInitForm(formID);

           FrmSetActiveForm(frm);
           switch (formID) 
           {
             case mainForm:
                  FrmSetEventHandler(frm, 
                    (FormEventHandlerPtr)mainFormEventHandler);

                  processed = true;
                  break;

             case infoForm:
                  FrmSetEventHandler(frm, 
                    (FormEventHandlerPtr)infoFormEventHandler);

                  processed = true;
                  break;

             case tSTLForm:
                  FrmSetEventHandler(frm, 
                    (FormEventHandlerPtr)tSTLFormEventHandler);

                  processed = true;
                  break;

             default:
                  break;
           }
         }
         break;
         
    case menuEvent:

         switch (event->data.menu.itemID) 
         {
           case menuItemtSTL:
                ApplicationDisplayDialog(tSTLForm);
                processed = true;
                break;

           case menuItemAbout:
                ApplicationDisplayDialog(infoForm);
                processed = true;
                break;

           default:
                break;
         }
         break;

    case ctlSelectEvent:
  
         switch (event->data.ctlSelect.controlID)
         {
           case globalFormAboutButton:

                // regenerate menu event
	        {
	          EventType event;

                  MemSet(&event, sizeof(EventType), 0);
                  event.eType = menuEvent;
                  event.data.menu.itemID = menuItemAbout;
	          EvtAddEventToQueue(&event);
	        }

                processed = true;
                break;

           default:
                break;
         }
         break;
         
    default:
         break;
  }

  return processed;
}

/**
 * Display a MODAL dialog to the user (this is a modified FrmDoDialog)
 *
 * @param formID the ID of the form to display.
 */
void
ApplicationDisplayDialog(UInt16 formID)
{
  FormActiveStateType frmCurrState;
  FormType            *frmActive      = NULL;
  WinHandle           winDrawWindow   = NULL;
  WinHandle           winActiveWindow = NULL;

  // save the active form/window
  if (DeviceSupportsVersion(romVersion3)) {
    FrmSaveActiveState(&frmCurrState);
  }
  else {
    frmActive       = FrmGetActiveForm();
    winDrawWindow   = WinGetDrawWindow();
    winActiveWindow = WinGetActiveWindow();  // < palmos3.0, manual work
  }

  {
    EventType event;
    UInt16    err;
    Boolean   keepFormOpen;

    MemSet(&event, sizeof(EventType), 0);

    // send a load form event
    event.eType = frmLoadEvent;
    event.data.frmLoad.formID = formID;
    EvtAddEventToQueue(&event);

    // send a open form event
    event.eType = frmOpenEvent;
    event.data.frmLoad.formID = formID;
    EvtAddEventToQueue(&event);

    // handle all events here (trap them before the OS does) :)
    keepFormOpen = true;
    while (keepFormOpen) {

      EvtGetEvent(&event, evtTimeOut);

      // this is our exit condition! :)
      keepFormOpen = (event.eType != frmCloseEvent);

      if (!SysHandleEvent(&event))
        if (!MenuHandleEvent(0, &event, &err))
          if (!ApplicationHandleEvent(&event))
            FrmDispatchEvent(&event);

      if (event.eType == appStopEvent) {
        keepFormOpen = false;
        EvtAddEventToQueue(&event);  // tap "applications", need to exit
      }
    }
  }

  // restore the active form/window
  if (DeviceSupportsVersion(romVersion3)) {
    FrmRestoreActiveState(&frmCurrState);
  }
  else {
    FrmSetActiveForm(frmActive);
    WinSetDrawWindow(winDrawWindow);
    WinSetActiveWindow(winActiveWindow);     // < palmos3.0, manual work
  }
}

/**
 * The Palm Computing Platform event processing loop.
 */
void  
EventLoop()
{
  EventType event;
  UInt16    err;

  do {
    EvtGetEvent(&event, evtTimeOut);

    if (!SysHandleEvent(&event)) 
      if (!MenuHandleEvent(0, &event, &err)) 
        if (!ApplicationHandleEvent(&event)) 
          FrmDispatchEvent(&event);

  } while (event.eType != appStopEvent);
}

/**
 * The Palm Computing Platform termination routine.
 */
void  
EndApplication()
{
  // ensure all forms are closed
  FrmCloseAllForms();
}
