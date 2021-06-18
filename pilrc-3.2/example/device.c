/*
 * @(#)device.c
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

/**
 * Check if the device is compatable with a particular ROM version.
 *
 * @param version the ROM version to compare against.
 * @return true if it is compatable, false otherwise.
 */
Boolean 
DeviceSupportsVersion(UInt32 version)
{
  UInt32 romVersion;

  // get the rom version and ram size for this device
  FtrGet(sysFtrCreator, sysFtrNumROMVersion, &romVersion);

  return (romVersion >= version);
}
