# Microsoft Developer Studio Generated NMAKE File, Based on demo.dsp
!IF "$(CFG)" == ""
CFG=demo - Win32 Debug
!MESSAGE No configuration specified. Defaulting to demo - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "demo - Win32 Release" && "$(CFG)" != "demo - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "demo.mak" CFG="demo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "demo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "demo - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "demo - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\dist\demo.exe"


CLEAN :
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "..\dist\demo.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "$(WXWIN)/lib/mswd" /I "$(WXWIN)/include" /I "$(WXWIN)/contrib/include" /I "../src" /I "../mozfiles/dist/include/xpcom" /I "../mozfiles/dist/include/nspr" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\demo.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\demo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib rpcrt4.lib wsock32.lib winmm.lib wxmsw.lib png.lib zlib.lib jpeg.lib tiff.lib wxmozilla.lib editorbase_s.lib embed_base_s.lib gkgfx.lib nspr4.lib nspr4_s.lib plc4.lib plc4_s.lib plds4.lib plds4_s.lib xpcom.lib xpcomglue_s.lib /nologo /version:0.1 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\demo.pdb" /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libci.lib" /nodefaultlib:"msvcrtd.lib" /out:"../dist/demo.exe" /libpath:"$(WXWIN)/lib" /libpath:"$(WXWIN)/contrib/lib" /libpath:"../lib" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj"

"..\dist\demo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "demo - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\dist\demo.exe"


CLEAN :
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\demo.pdb"
	-@erase "..\dist\demo.exe"
	-@erase "..\dist\demo.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "$(WXWIN)/lib/mswd" /I "$(WXWIN)/include" /I "$(WXWIN)/contrib/include" /I "../src" /I "../mozfiles/dist/include/xpcom" /I "../mozfiles/dist/include/nspr" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\demo.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\demo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib rpcrt4.lib wsock32.lib winmm.lib wxmswd.lib pngd.lib zlibd.lib jpegd.lib tiffd.lib wxmozillad.lib editorbase_s.lib embed_base_s.lib gkgfx.lib nspr4.lib nspr4_s.lib plc4.lib plc4_s.lib plds4.lib plds4_s.lib xpcom.lib xpcomglue_s.lib /nologo /version:0.1 /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\demo.pdb" /debug /machine:I386 /nodefaultlib:"libcd.lib" /nodefaultlib:"libcid.lib" /nodefaultlib:"msvcrt.lib" /nodefaultlib:"libcmtd.lib" /out:"../dist/demo.exe" /pdbtype:sept /libpath:"$(WXWIN)/lib" /libpath:"$(WXWIN)/contrib/lib" /libpath:"../lib" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj"

"..\dist\demo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("demo.dep")
!INCLUDE "demo.dep"
!ELSE 
!MESSAGE Warning: cannot find "demo.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "demo - Win32 Release" || "$(CFG)" == "demo - Win32 Debug"
SOURCE=.\main.cpp

"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

