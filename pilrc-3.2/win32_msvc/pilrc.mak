# Microsoft Developer Studio Generated NMAKE File, Based on pilrc.dsp
!IF "$(CFG)" == ""
CFG=pilrc - Win32 Release
!MESSAGE No configuration specified. Defaulting to pilrc - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "pilrc - Win32 Release" && "$(CFG)" != "pilrc - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pilrc.mak" CFG="pilrc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pilrc - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "pilrc - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "pilrc - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\pilrc.exe"


CLEAN :
	-@erase "$(INTDIR)\bitmap.obj"
	-@erase "$(INTDIR)\font.obj"
	-@erase "$(INTDIR)\lex.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\pilrc.obj"
	-@erase "$(INTDIR)\pilrc.res"
	-@erase "$(INTDIR)\plex.obj"
	-@erase "$(INTDIR)\restype.obj"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\pilrc.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\pilrc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\pilrc.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\pilrc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\pilrc.pdb" /machine:I386 /out:"$(OUTDIR)\pilrc.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bitmap.obj" \
	"$(INTDIR)\font.obj" \
	"$(INTDIR)\lex.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\pilrc.obj" \
	"$(INTDIR)\plex.obj" \
	"$(INTDIR)\restype.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\pilrc.res"

"$(OUTDIR)\pilrc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "pilrc - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\pilrc.exe"


CLEAN :
	-@erase "$(INTDIR)\bitmap.obj"
	-@erase "$(INTDIR)\font.obj"
	-@erase "$(INTDIR)\lex.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\pilrc.obj"
	-@erase "$(INTDIR)\pilrc.res"
	-@erase "$(INTDIR)\plex.obj"
	-@erase "$(INTDIR)\restype.obj"
	-@erase "$(INTDIR)\util.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\pilrc.exe"
	-@erase "$(OUTDIR)\pilrc.ilk"
	-@erase "$(OUTDIR)\pilrc.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\pilrc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\pilrc.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\pilrc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\pilrc.pdb" /debug /machine:I386 /out:"$(OUTDIR)\pilrc.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\bitmap.obj" \
	"$(INTDIR)\font.obj" \
	"$(INTDIR)\lex.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\pilrc.obj" \
	"$(INTDIR)\plex.obj" \
	"$(INTDIR)\restype.obj" \
	"$(INTDIR)\util.obj" \
	"$(INTDIR)\pilrc.res"

"$(OUTDIR)\pilrc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("pilrc.dep")
!INCLUDE "pilrc.dep"
!ELSE 
!MESSAGE Warning: cannot find "pilrc.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "pilrc - Win32 Release" || "$(CFG)" == "pilrc - Win32 Debug"
SOURCE=..\bitmap.c

"$(INTDIR)\bitmap.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\font.c

"$(INTDIR)\font.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\lex.c

"$(INTDIR)\lex.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\main.c

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\pilrc.c

"$(INTDIR)\pilrc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\pilrc.rc

!IF  "$(CFG)" == "pilrc - Win32 Release"


"$(INTDIR)\pilrc.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\pilrc.res" /i "\building_zone\pilrc" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "pilrc - Win32 Debug"


"$(INTDIR)\pilrc.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\pilrc.res" /i "\building_zone\pilrc" /d "_DEBUG" $(SOURCE)


!ENDIF 

SOURCE=..\plex.c

"$(INTDIR)\plex.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\restype.c

"$(INTDIR)\restype.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\util.c

"$(INTDIR)\util.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

