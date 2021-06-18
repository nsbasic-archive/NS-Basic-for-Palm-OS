#
# @(#)Makefile
#
# Copyright 2000, Aaron Ardiri (mailto:aaron@ardiri.com)
# All rights reserved.
#
# This file was generated as part of the "pilrctst" program developed for 
# the Palm Computing Platform designed by Palm: http://www.palm.com/ 
#
# The contents of this file are to be used for educational purposes
# only in understanding the PilRC application.  Redistribution or 
# modification without prior consent of the original author is prohibited. 
#

# compiler commands 
PREFIX   = 
CC       = $(PREFIX)m68k-palmos-gcc
#PILRC    = $(PREFIX)pilrc
PILRC    = ../pilrc
BUILDPRC = $(PREFIX)build-prc
PRC2BIN  = $(PREFIX)prc2bin

# source / outputs
OBJS     = palm.o device.o
EXEC     = pilrctst

# compiler flags 
CCFLAGS = -O2 -Wall -palmos3.5 

# compile requirements
$(EXEC).prc: $(EXEC) $(EXEC).def bin.stamp
	$(BUILDPRC) $(EXEC).def $(EXEC) *.bin
	make clean

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(CCFLAGS) -o $(EXEC)

bin.stamp: $(EXEC).rcp
	$(PILRC) -q $(EXEC).rcp

# compile rules
.SUFFIXES: .c .o

.c.o:
	$(CC) -c $(CCFLAGS) $<

# clean-up funtions
clean:
	rm -f *.[oa] *.bin *.grc *~ $(EXEC)

distclean:
	rm -f *.[oa] *.bin *.[pg]rc *~ $(EXEC)
