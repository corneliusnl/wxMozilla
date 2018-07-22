# File:		makefile.vc
# Author:	Julian Smart
# Created:	2001
# Updated:
# Copyright:	(c) 2001, Julian Smart
#
# "%W% %G%"
#
# Makefile : Builds Plot class library (MS VC++).
# Use FINAL=1 argument to nmake to build final version with no debugging
# info


# Set WXDIR for your system
WXDIR = $(WXWIN)
FINAL=Release
WXUSINGDLL=1

OBJECTS = $(D)\wxMozillaBrowser.obj $(D)\wxMozillaBrowserChrome.obj $(D)\wxMozillaEvents.obj $(D)\wxMozillaWindow.obj 
STLIBS=..\mozfiles\dist\lib\embed_base_s.lib ..\mozfiles\dist\lib\editorbase_s.lib ..\mozfiles\dist\lib\xpcom.lib $(WXDIR)\lib\wxmsw240h.lib
LIBTARGET=$(WXDIR)\lib\wxMozilla$(LIBEXT).lib

!include .\makelib.vc
CPPFLAGS = $(CPPFLAGS) /I "./" /I "..\mozfiles\dist\include" /D_DLL /D_WINDLL /I "..\mozfiles\dist\sdk\XPCOM\include" /I "..\mozfiles\dist\include\docshell" /I "..\mozfiles\dist\include\nspr" /I "..\mozfiles\dist\include\xpcom" /I "..\mozfiles\dist\include\string" /I "..\mozfiles\dist\include\pref" /I "..\mozfiles\dist\include\widget" /I "..\mozfiles\dist\include\webbrwsr" /I "..\mozfiles\dist\include\embed_base" /I "..\mozfiles\dist\include\uriloader" /I "..\mozfiles\dist\include\gfx" /I "..\mozfiles\dist\include\shistory" /I "..\mozfiles\dist\include\commandhandler" /I "..\mozfiles\dist\include\necko" /I "..\mozfiles\dist\include\webbrowserpersist" /I "..\mozfiles\dist\include\composer" /I "..\mozfiles\dist\include\dom" /I "..\mozfiles\dist\include\content" /I "..\mozfiles\dist\include\webshell" /I "..\mozfiles\dist\include\find" /I "..\mozfiles\dist\include\windowwatcher"