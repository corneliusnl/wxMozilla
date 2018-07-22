# Microsoft Developer Studio Project File - Name="wxmozilla" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=wxmozilla - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "wxmozilla.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "wxmozilla - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "include" /I "mozfiles" /I "mozfiles/dist/include" /I "mozfiles/dist/include/xpcom/" /I "mozfiles/dist/include/webbrwsr" /I "mozfiles/dist/include/uriloader" /I "mozfiles/dist/include/docshell" /I "mozfiles/dist/include/nspr" /I "mozfiles/dist/include/string" /I "mozfiles/dist/include/pref" /I "mozfiles/dist/include/widget" /I "mozfiles/dist/include/embed_base" /I "mozfiles/dist/include/webbrowserpersist" /I "mozfiles/dist/include/windowwatcher" /I "mozfiles/dist/include/commandhandler" /I "mozfiles/dist/include/composer" /I "mozfiles/dist/include/dom" /I "mozfiles/dist/include/gfx" /I "mozfiles/dist/include/content" /I "mozfiles/dist/include/necko" /I "mozfiles/dist/include/webshell" /I "mozfiles/dist/include/find" /I "$(WXWIN)/lib/mswd" /I "$(WXWIN)/include" /I "$(WXWIN)/contrib/include" /D "_NDEBUG" /D "WIN32" /D "_WINDOWS" /D WINVER=0x400 /D "_MT" /D wxUSE_GUI=1 /D "XP_WIN" /D "XP_WIN32" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\wxmozilla.lib"

!ELSEIF  "$(CFG)" == "wxmozilla - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /ZI /Od /I "include" /I "mozfiles" /I "mozfiles/dist/include" /I "mozfiles/dist/include/xpcom/" /I "mozfiles/dist/include/webbrwsr" /I "mozfiles/dist/include/uriloader" /I "mozfiles/dist/include/docshell" /I "mozfiles/dist/include/nspr" /I "mozfiles/dist/include/string" /I "mozfiles/dist/include/pref" /I "mozfiles/dist/include/widget" /I "mozfiles/dist/include/embed_base" /I "mozfiles/dist/include/webbrowserpersist" /I "mozfiles/dist/include/windowwatcher" /I "mozfiles/dist/include/commandhandler" /I "mozfiles/dist/include/composer" /I "mozfiles/dist/include/dom" /I "mozfiles/dist/include/gfx" /I "mozfiles/dist/include/content" /I "mozfiles/dist/include/necko" /I "mozfiles/dist/include/webshell" /I "mozfiles/dist/include/find" /I "$(WXWIN)/lib/mswd" /I "$(WXWIN)/include" /I "$(WXWIN)/contrib/include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D WINVER=0x400 /D "_MT" /D wxUSE_GUI=1 /D "__WXDEBUG__" /D WXDEBUG=1 /D "XP_WIN" /D "XP_WIN32" /YX /FD /GZ /c
# SUBTRACT CPP /X
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"lib\wxmozillad.lib"

!ENDIF 

# Begin Target

# Name "wxmozilla - Win32 Release"
# Name "wxmozilla - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\wxMozillaBrowser.cpp
# End Source File
# Begin Source File

SOURCE=.\src\wxMozillaBrowserChrome.cpp
# End Source File
# Begin Source File

SOURCE=.\src\wxMozillaChrome.cpp
# End Source File
# Begin Source File

SOURCE=.\src\wxMozillaEvents.cpp
# End Source File
# Begin Source File

SOURCE=.\src\wxMozillaWindow.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=".\mozfiles\mozilla-config.h"
# End Source File
# Begin Source File

SOURCE=.\include\mozillawin.h
# End Source File
# Begin Source File

SOURCE=.\src\mozillawin_impl.h
# End Source File
# Begin Source File

SOURCE=.\src\wxMozilla.h
# End Source File
# Begin Source File

SOURCE=.\src\wxMozillaBrowser.h
# End Source File
# Begin Source File

SOURCE=.\src\wxMozillaBrowserChrome.h
# End Source File
# Begin Source File

SOURCE=.\src\wxMozillaStream.h
# End Source File
# Begin Source File

SOURCE=.\src\wxMozillaWindow.h
# End Source File
# End Group
# End Target
# End Project
