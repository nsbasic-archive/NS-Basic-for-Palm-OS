#
# @(#)configure.ac
#
# Copyright 1997-1999, Wes Cherry   (mailto:wesc@technosis.com)
#           2000-2003, Aaron Ardiri (mailto:aaron@ardiri.com)
# All rights reserved.
# 
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation;  either version 2, or (at your option)
# any version.
#
# This program is distributed in the hope that it will be useful,  but
# WITHOUT  ANY  WARRANTY;   without  even   the  implied  warranty  of 
# MERCHANTABILITY  or FITNESS FOR A  PARTICULAR  PURPOSE.  See the GNU
# General Public License for more details.
#
# You  should have  received a  copy of the GNU General Public License
# along with this program;  if not,  please write to the Free Software 
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#
# Revisions:
# ==========
#
# pre 18-Jun-2000 <numerous developers>
#                 creation
#     18-Jun-2000 Aaron Ardiri
#                 GNU GPL documentation additions

AC_INIT(PilRC, RPM_SPEC_VERSION(pilrc.spec))
AM_INIT_AUTOMAKE([foreign no-define])
AC_CONFIG_SRCDIR(../pilrc.c)
AC_PREREQ(2.50)

AC_PROG_CC

AC_ARG_ENABLE(pilrcui,
  AC_HELP_STRING([--enable-pilrcui],
		 [build PilRCUI (requires GTK headers and libraries)]),
  [], [enable_pilrcui=no])

PILRCUI=
if test $enable_pilrcui = yes; then
  AM_PATH_GTK(1.2.0, [PILRCUI=pilrcui])
fi

AC_SUBST(PILRCUI)
AM_CONDITIONAL(PILRCUI, [test -n "$PILRCUI"])

AC_ARG_ENABLE(build-warnings,
  AC_HELP_STRING([--enable-build-warnings],
		 [build with various GCC warnings activated]),
  [], [enable_build_warnings=no])

AM_CONDITIONAL(WARNINGS, [test $enable_build_warnings = yes])

AC_CHECK_SIZEOF(int)
AC_CHECK_SIZEOF(long)
AC_CHECK_SIZEOF(char *)

AC_OUTPUT(Makefile)
