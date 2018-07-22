/*
 * wxMozillaWindow Sample Application
 * Copyright 2001 (c) Jeremiah Cornelius McCarthy. All Rights Reserved.
 */
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "wxMozillaWindow.h"
#include "wxMozillaBrowser.h"

class wxMozillaDemo: public wxApp
{
public:

	virtual bool OnInit();
};

bool wxMozillaDemo::OnInit()
{
	wxMozillaWindow *MainWnd;
	MainWnd = new wxMozillaWindow();
	MainWnd->Mozilla->LoadURL("http://www.wxwindows.org");
	MainWnd->Show(TRUE);
	//wxMainWnd *MainWnd;

	//MainWnd = new wxMainWnd();
	//MainWnd->Show(TRUE);

	return TRUE;
};

IMPLEMENT_APP(wxMozillaDemo)