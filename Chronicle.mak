# Microsoft Developer Studio Generated NMAKE File, Based on Chronicle.dsp
!IF "$(CFG)" == ""
CFG=Chronicle - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Chronicle - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Chronicle - Win32 Release" && "$(CFG)" != "Chronicle - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Chronicle.mak" CFG="Chronicle - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Chronicle - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Chronicle - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Chronicle - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Chronicle.exe" "$(OUTDIR)\Chronicle.bsc"


CLEAN :
	-@erase "$(INTDIR)\Chronicle.obj"
	-@erase "$(INTDIR)\Chronicle.res"
	-@erase "$(INTDIR)\Chronicle.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Chronicle.bsc"
	-@erase "$(OUTDIR)\Chronicle.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Chronicle.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Chronicle.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Chronicle.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Chronicle.sbr"

"$(OUTDIR)\Chronicle.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Chronicle.pdb" /machine:I386 /out:"$(OUTDIR)\Chronicle.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Chronicle.obj" \
	"$(INTDIR)\Chronicle.res"

"$(OUTDIR)\Chronicle.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Chronicle - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Chronicle.exe" "$(OUTDIR)\Chronicle.bsc"


CLEAN :
	-@erase "$(INTDIR)\Chronicle.obj"
	-@erase "$(INTDIR)\Chronicle.res"
	-@erase "$(INTDIR)\Chronicle.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Chronicle.bsc"
	-@erase "$(OUTDIR)\Chronicle.exe"
	-@erase "$(OUTDIR)\Chronicle.ilk"
	-@erase "$(OUTDIR)\Chronicle.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Chronicle.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Chronicle.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Chronicle.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Chronicle.sbr"

"$(OUTDIR)\Chronicle.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Chronicle.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Chronicle.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Chronicle.obj" \
	"$(INTDIR)\Chronicle.res"

"$(OUTDIR)\Chronicle.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Chronicle.dep")
!INCLUDE "Chronicle.dep"
!ELSE 
!MESSAGE Warning: cannot find "Chronicle.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Chronicle - Win32 Release" || "$(CFG)" == "Chronicle - Win32 Debug"
SOURCE=.\Chronicle.cpp

"$(INTDIR)\Chronicle.obj"	"$(INTDIR)\Chronicle.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Chronicle.rc

"$(INTDIR)\Chronicle.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

