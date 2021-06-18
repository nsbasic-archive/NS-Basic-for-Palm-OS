## Process this file with automake to produce Makefile.in

VPATH = $(srcdir):$(srcdir)/..

if PILRCUI
PILRCUI_CFLAGS = $(GTK_CFLAGS)
endif
if WARNINGS
WARNING_CFLAGS = -Wall -W -Wno-unused-parameter -Wpointer-arith \
		 -Wcast-qual -Wcast-align -Wsign-compare
endif

AM_CFLAGS = $(PILRCUI_CFLAGS) $(WARNING_CFLAGS)

bin_PROGRAMS = pilrc @PILRCUI@
EXTRA_PROGRAMS = pilrcui

dist_pkgdata_DATA = ppmquant/palette-02.pbm ppmquant/palette-04.pgm \
		    ppmquant/palette-16.pgm ppmquant/palette-256.ppm

COMMON_SOURCES = pilrc.c lex.c util.c restype.c bitmap.c font.c plex.c
noinst_HEADERS = bitmap.h font.h lex.h pilrc.h plex.h restype.h std.h util.h

pilrc_SOURCES = $(COMMON_SOURCES) main.c

pilrcui_SOURCES = $(COMMON_SOURCES) xwin.c
pilrcui_LDADD = $(GTK_LIBS)

DOC_FILES = doc/archive.html doc/contrib.html doc/images/download.gif \
	doc/download.html doc/history.html doc/index.html doc/manual.html

EXAMPLE_FILES = example/images/icon1bpp.bmp example/images/icon2bpp.bmp \
	example/images/icon8bpp.bmp example/images/info1bpp.bmp \
	example/images/palm1bpp.bmp example/images/palm2bpp.bmp \
	example/images/palm8bpp.bmp example/images/smic1bpp.bmp \
	example/images/smic2bpp.bmp example/images/smic8bpp.bmp \
	example/5x11.txt example/Makefile example/README.txt example/palm.c \
	example/palm.h example/pilrctst.def example/pilrctst.prc \
	example/pilrctst.rcp example/resource.h

FONTS_FILES = contrib/pilfont.zip
ROOT_FILES = makefile.os2 pilrc.dsp pilrc.mak README.txt LICENSE.txt resource.rc

EXTRA_DIST = $(DOC_FILES) $(EXAMPLE_FILES) $(FONTS_FILES) $(ROOT_FILES)
