/*
 * @(#)palm.h
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

#ifndef _PALM_H
#define _PALM_H

// system includes
#include <PalmOS.h>

// local includes
#include "resource.h"
#include "device.h"

// functions
extern UInt32  PilotMain(UInt16, MemPtr, UInt16);
extern void    InitApplication(void);
extern Boolean ApplicationHandleEvent(EventType *);
extern void    ApplicationDisplayDialog(UInt16);
extern void    EventLoop(void);
extern void    EndApplication(void);

#endif 
