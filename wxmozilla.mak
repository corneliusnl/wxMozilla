# Microsoft Developer Studio Generated NMAKE File, Based on wxmozilla.dsp
!IF "$(CFG)" == ""
CFG=wxmozilla - Win32 Debug
!MESSAGE No configuration specified. Defaulting to wxmozilla - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "wxmozilla - Win32 Release" && "$(CFG)" != "wxmozilla - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "wxmozilla.mak" CFG="wxmozilla - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "wxmozilla - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "wxmozilla - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wxmozilla - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\lib\wxmozilla.lib"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\wxMozillaBrowser.obj"
	-@erase "$(INTDIR)\wxMozillaBrowserChrome.obj"
	-@erase "$(INTDIR)\wxMozillaChrome.obj"
	-@erase "$(INTDIR)\wxMozillaEvents.obj"
	-@erase "$(INTDIR)\wxMozillaWindow.obj"
	-@erase ".\lib\wxmozilla.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "include" /I "mozfiles" /I "mozfiles/dist/include" /I "mozfiles/dist/include/xpcom/" /I "mozfiles/dist/include/webbrwsr" /I "mozfiles/dist/include/uriloader" /I "mozfiles/dist/include/docshell" /I "mozfiles/dist/include/nspr" /I "mozfiles/dist/include/string" /I "mozfiles/dist/include/pref" /I "mozfiles/dist/include/widget" /I "mozfiles/dist/include/embed_base" /I "mozfiles/dist/include/webbrowserpersist" /I "mozfiles/dist/include/windowwatcher" /I "mozfiles/dist/include/commandhandler" /I "mozfiles/dist/include/composer" /I "mozfiles/dist/include/dom" /I "mozfiles/dist/include/gfx" /I "mozfiles/dist/include/content" /I "mozfiles/dist/include/necko" /I "mozfiles/dist/include/webshell" /I "mozfiles/dist/include/find" /I "$(WXWIN)/lib/mswd" /I "$(WXWIN)/include" /I "$(WXWIN)/contrib/include" /D "_NDEBUG" /D "WIN32" /D "_WINDOWS" /D WINVER=0x400 /D "_MT" /D wxUSE_GUI=1 /D "XP_WIN" /D "XP_WIN32" /Fp"$(INTDIR)\wxmozilla.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wxmozilla.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"lib\wxmozilla.lib" 
LIB32_OBJS= \
	"$(INTDIR)\wxMozillaBrowser.obj" \
	"$(INTDIR)\wxMozillaBrowserChrome.obj" \
	"$(INTDIR)\wxMozillaChrome.obj" \
	"$(INTDIR)\wxMozillaEvents.obj" \
	"$(INTDIR)\wxMozillaWindow.obj"

".\lib\wxmozilla.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "wxmozilla - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\lib\wxmozillad.lib"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\wxMozillaBrowser.obj"
	-@erase "$(INTDIR)\wxMozillaBrowserChrome.obj"
	-@erase "$(INTDIR)\wxMozillaChrome.obj"
	-@erase "$(INTDIR)\wxMozillaEvents.obj"
	-@erase "$(INTDIR)\wxMozillaWindow.obj"
	-@erase ".\lib\wxmozillad.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /ZI /Od /I "include" /I "mozfiles" /I "mozfiles/dist/include" /I "mozfiles/dist/include/xpcom/" /I "mozfiles/dist/include/webbrwsr" /I "mozfiles/dist/include/uriloader" /I "mozfiles/dist/include/docshell" /I "mozfiles/dist/include/nspr" /I "mozfiles/dist/include/string" /I "mozfiles/dist/include/pref" /I "mozfiles/dist/include/widget" /I "mozfiles/dist/include/embed_base" /I "mozfiles/dist/include/webbrowserpersist" /I "mozfiles/dist/include/windowwatcher" /I "mozfiles/dist/include/commandhandler" /I "mozfiles/dist/include/composer" /I "mozfiles/dist/include/dom" /I "mozfiles/dist/include/gfx" /I "mozfiles/dist/include/content" /I "mozfiles/dist/include/necko" /I "mozfiles/dist/include/webshell" /I "mozfiles/dist/include/find" /I "$(WXWIN)/lib/mswd" /I "$(WXWIN)/include" /I "$(WXWIN)/contrib/include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D WINVER=0x400 /D "_MT" /D wxUSE_GUI=1 /D "__WXDEBUG__" /D WXDEBUG=1 /D "XP_WIN" /D "XP_WIN32" /Fp"$(INTDIR)\wxmozilla.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\wxmozilla.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"lib\wxmozillad.lib" 
LIB32_OBJS= \
	"$(INTDIR)\wxMozillaBrowser.obj" \
	"$(INTDIR)\wxMozillaBrowserChrome.obj" \
	"$(INTDIR)\wxMozillaChrome.obj" \
	"$(INTDIR)\wxMozillaEvents.obj" \
	"$(INTDIR)\wxMozillaWindow.obj"

".\lib\wxmozillad.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
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
!IF EXISTS("wxmozilla.dep")
!INCLUDE "wxmozilla.dep"
!ELSE 
!MESSAGE Warning: cannot find "wxmozilla.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "wxmozilla - Win32 Release" || "$(CFG)" == "wxmozilla - Win32 Debug"
SOURCE=.\src\wxMozillaBrowser.cpp

"$(INTDIR)\wxMozillaBrowser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\wxMozillaBrowserChrome.cpp

"$(INTDIR)\wxMozillaBrowserChrome.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\wxMozillaChrome.cpp

"$(INTDIR)\wxMozillaChrome.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\wxMozillaEvents.cpp

"$(INTDIR)\wxMozillaEvents.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\src\wxMozillaWindow.cpp

"$(INTDIR)\wxMozillaWindow.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

