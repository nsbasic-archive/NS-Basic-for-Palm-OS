/*
 * @(#)device.h
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

#ifndef _DEVICE_H
#define _DEVICE_H

#include "palm.h"

#define romVersion1   sysMakeROMVersion(1,0,0,sysROMStageRelease,0)
#define romVersion2   sysMakeROMVersion(2,0,0,sysROMStageRelease,0)
#define romVersion3   sysMakeROMVersion(3,0,0,sysROMStageRelease,0)
#define romVersion3_1 sysMakeROMVersion(3,1,0,sysROMStageRelease,0)
#define romVersion3_2 sysMakeROMVersion(3,2,0,sysROMStageRelease,0)
#define romVersion3_5 sysMakeROMVersion(3,5,0,sysROMStageRelease,0)

extern Boolean DeviceSupportsVersion(UInt32);

#endif
