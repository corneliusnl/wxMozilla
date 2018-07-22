/*
 * wxMozillaWindow Modal Window Browser
 *
 * 
 * Developers:
 *  Jeremiah Cornelius McCarthy <jeremiah@whoop-ass.ca>
 *  Kevin Ollivier <kevino@tulane.edu>
 *  Dave Fancella <david.fancella@attbi.com>
 */
#include "wx/wxprec.h"
#include "wxMozillaWindow.h"

enum {
    ID_MOZCTL = wxID_HIGHEST + 1,
		ID_GO = wxID_HIGHEST + 2,
		ID_ADDRESS = wxID_HIGHEST + 3,
		ID_BACK = wxID_HIGHEST + 4,
		ID_NEXT = wxID_HIGHEST + 5,
		ID_SAVE = wxID_HIGHEST + 6,
		ID_STOP = wxID_HIGHEST + 7,
		ID_REFRESH = wxID_HIGHEST + 8,
		ID_BOLD = wxID_HIGHEST + 9,
		ID_EDITABLE = wxID_HIGHEST + 10,
		ID_COPY = wxID_HIGHEST + 11,
		ID_SELECT_ALL = wxID_HIGHEST + 12,
		ID_SELECT_NONE = wxID_HIGHEST + 13,
		ID_FIND = wxID_HIGHEST + 14,
		ID_NEW_WINDOW = wxID_HIGHEST + 15,
		ID_OPEN = wxID_HIGHEST + 16,
		ID_QUIT = wxID_HIGHEST + 17,
		ID_OPEN_NEW_WINDOW = wxID_HIGHEST + 18,
		ID_SAVE_LINK = wxID_HIGHEST + 19,
		ID_SAVE_IMAGE = wxID_HIGHEST + 20,
		ID_VIEW_SOURCE = wxID_HIGHEST + 21
};

IMPLEMENT_DYNAMIC_CLASS(wxMozillaWindow, wxFrame)

BEGIN_EVENT_TABLE(wxMozillaWindow, wxFrame)
	EVT_BUTTON(ID_GO, wxMozillaWindow::GoClicked)
	EVT_TOOL(ID_BACK, wxMozillaWindow::BackClicked)
	EVT_TOOL(ID_NEXT, wxMozillaWindow::NextClicked)
	EVT_TOOL(ID_STOP, wxMozillaWindow::StopLoading)
	EVT_TOOL(ID_REFRESH, wxMozillaWindow::RefreshPage)
	EVT_MENU(ID_NEW_WINDOW, wxMozillaWindow::NewWindow)
	EVT_MENU(ID_OPEN_NEW_WINDOW, wxMozillaWindow::OpenNewWindow)
	EVT_MENU(ID_QUIT, wxMozillaWindow::Quit)
	EVT_MENU(ID_VIEW_SOURCE, wxMozillaWindow::ViewSource)
	EVT_MENU(ID_STOP, wxMozillaWindow::StopLoading)
	EVT_MENU(ID_REFRESH, wxMozillaWindow::RefreshPage)
	EVT_MENU(wxID_SAVE, wxMozillaWindow::SaveClicked)
	EVT_MENU(ID_SELECT_ALL, wxMozillaWindow::SelectAll)
	EVT_MENU(ID_SELECT_NONE, wxMozillaWindow::SelectNone)
	EVT_MENU(ID_FIND, wxMozillaWindow::ShowFindDlg)
//	EVT_FIND(-1, wxMozillaWindow::DoFind)
//	EVT_FIND_NEXT(-1, wxMozillaWindow::DoFind)
//	EVT_FIND_CLOSE(-1, wxMozillaWindow::DoFind)
	EVT_MENU(ID_EDITABLE, wxMozillaWindow::MakeEditable)
	//EVT_MENU(ID_BOLD, wxMozillaWindow::BoldClicked)
	EVT_MENU(ID_COPY, wxMozillaWindow::DoCopy)
	EVT_MOZILLA_URL_CHANGED(wxMozillaWindow::UpdateURL)
	EVT_MOZILLA_STATUS_CHANGED(wxMozillaWindow::UpdateStatus)
	EVT_MOZILLA_RIGHT_CLICK(wxMozillaWindow::OnMozillaRightClick)
END_EVENT_TABLE()

wxMozillaWindow::wxMozillaWindow(bool showMenu, bool showToolbar, bool showStatusbar)
{
	wxFrame::Create((wxFrame *)NULL, -1, "wxMozilla", wxPoint(0, 0), wxSize(800,600));
        //int posx, posy;
	if (showStatusbar){
		hasStatusbar = TRUE;
		statusBar = this->CreateStatusBar();
	}
	else
		hasStatusbar = FALSE;

	//findDlg = NULL;
	if (showMenu){
	hasMenu = TRUE;
	appMenuBar = new wxMenuBar();
	fileMenu = new wxMenu();
	fileMenu->Append(ID_NEW_WINDOW, "New Window");
	fileMenu->Append(ID_OPEN, "Open");
	fileMenu->Append(wxID_SAVE, "Save Page");
	fileMenu->AppendSeparator();
	fileMenu->Append(ID_QUIT, "Exit");

	appMenuBar->Append(fileMenu, "File");

	editMenu = new wxMenu();
	editMenu->Append(ID_EDITABLE, "Make Editable");
	editMenu->Append(ID_BOLD, "Bold");
	editMenu->AppendSeparator();
	editMenu->Append(ID_COPY, "Copy");
	editMenu->AppendSeparator();
	editMenu->Append(ID_SELECT_ALL, "Select All");
	editMenu->Append(ID_SELECT_NONE, "Select None");
	editMenu->Append(ID_FIND, "Find");
	appMenuBar->Append(editMenu, "Edit");

	viewMenu = new wxMenu();
	viewMenu->Append(ID_STOP, "Stop");
	viewMenu->Append(ID_REFRESH, "Refresh");
	viewMenu->AppendSeparator();
	viewMenu->Append(ID_VIEW_SOURCE, "View Source");
	appMenuBar->Append(viewMenu, "View");

	this->SetMenuBar(appMenuBar);
	}
	else
		hasMenu = FALSE;
	//myClipboard = new wxClipboard();

        //Create a fake toolbar - it's not pretty but works for now
	if (showToolbar){
		hasToolbar = TRUE;
	wxInitAllImageHandlers();

	wxBitmap BackOn = wxBitmap(".\\icons\\back24.gif", wxBITMAP_TYPE_GIF);
	wxBitmap BackOff = wxBitmap(".\\icons\\back24_d.gif", wxBITMAP_TYPE_GIF);
	
	wxBitmap NextOn = wxBitmap(".\\icons\\forward24.gif", wxBITMAP_TYPE_GIF);
	wxBitmap NextOff = wxBitmap(".\\icons\\forward24_d.gif", wxBITMAP_TYPE_GIF);
	
	wxBitmap RefreshOn = wxBitmap(".\\icons\\refresh24_h.gif", wxBITMAP_TYPE_GIF);
	wxBitmap RefreshOff = wxBitmap(".\\icons\\refresh24_d.gif", wxBITMAP_TYPE_GIF);

	wxBitmap StopOn = wxBitmap(".\\icons\\stop24.gif", wxBITMAP_TYPE_GIF);
	wxBitmap StopOff = wxBitmap(".\\icons\\stop24_d.gif", wxBITMAP_TYPE_GIF);

	toolbar = this->CreateToolBar();
	toolbar->AddTool(ID_BACK, "Back", BackOn, BackOff);
	toolbar->AddTool(ID_NEXT, "Next", NextOn, NextOff);
	toolbar->AddTool(ID_STOP, "Stop", StopOn, StopOff);
	toolbar->AddTool(ID_REFRESH, "Refresh", RefreshOn, RefreshOff);
	toolbar->SetToolBitmapSize(wxSize(24,24));
	lblAddress = new wxStaticText(toolbar, -1, "Address:", wxPoint(350,7));
    txtURL = new wxTextCtrl(toolbar, ID_ADDRESS, "http://www.mozilla.org", wxPoint(400,0), wxSize(180,25));	
	GoButton = new wxButton(toolbar, ID_GO, "Go!", wxPoint(590,0)); 
	toolbar->AddControl(lblAddress);
	toolbar->AddControl(txtURL);
	toolbar->AddControl(GoButton);
	toolbar->Realize();
	}
	else
		hasToolbar = FALSE;
/*
	BackButton = new wxButton(this, ID_BACK, "Back", wxPoint(30,0));
	BackButton->Enable(FALSE);
	NextButton = new wxButton(this, ID_NEXT, "Next", wxPoint(90,0));
	NextButton->Enable(FALSE);
	StopButton = new wxButton(this, ID_STOP, "Stop", wxPoint(190,0));
	StopButton->Enable(FALSE);
	RefreshButton = new wxButton(this, ID_REFRESH, "Refresh", wxPoint(270,0));
*/
        
	Mozilla = new wxMozillaBrowser(this, ID_MOZCTL, wxDefaultPosition, wxSize(700, 500));
	Mozilla->Show(TRUE);
        
        wxBoxSizer *mysizer = new wxBoxSizer(wxVERTICAL);
 /*
		wxBoxSizer *buttonsizer = new wxBoxSizer(wxHORIZONTAL);
        buttonsizer->Add(BackButton, 0, wxALL, 4);
        buttonsizer->Add(NextButton, 0, wxALL, 4);
        buttonsizer->Add(StopButton, 0, wxALL, 4);
        buttonsizer->Add(RefreshButton, 0, wxALL, 4);
        buttonsizer->Add(lblAddress, 0, wxALL, 4);
        buttonsizer->Add(txtURL, 0, wxALL, 4);
        buttonsizer->Add(GoButton, 0, wxALL, 4);
        mysizer->Add(buttonsizer, 0, wxALL, 4);
*/
        mysizer->Add(Mozilla, 1, wxALL|wxEXPAND ,4);

        SetAutoLayout(TRUE);
        SetSizerAndFit(mysizer);
        Layout();
}

void wxMozillaWindow::NewWindow(wxMenuEvent &myEvent)
{
	wxMozillaWindow *newWin = new wxMozillaWindow();
	newWin->Show(TRUE);
}

void wxMozillaWindow::Quit(wxMenuEvent &myEvent)
{
	Destroy();
}

void wxMozillaWindow::ViewSource(wxMenuEvent &myEvent)
{
	wxMozillaWindow *newWin = new wxMozillaWindow(FALSE, FALSE, FALSE);
	newWin->Mozilla->LoadURL(wxString("view-source:") + txtURL->GetValue());
	newWin->Show(TRUE);
}

void wxMozillaWindow::StopLoading(wxEvent &myEvent)
{
	Mozilla->Stop();
}

void wxMozillaWindow::RefreshPage(wxEvent &myEvent)
{
	Mozilla->Reload();
}

void wxMozillaWindow::GoClicked(wxEvent &myEvent)
{
	Mozilla->LoadURL(txtURL->GetValue());
	//CheckStates();
};

void wxMozillaWindow::BackClicked(wxEvent &myEvent)
{
	if (Mozilla->CanGoBack())
		Mozilla->GoBack();
		//CheckStates();
};

void wxMozillaWindow::NextClicked(wxEvent &myEvent)
{
	if (Mozilla->CanGoForward())
		Mozilla->GoForward();
		//CheckStates();
};

void wxMozillaWindow::SaveClicked(wxEvent &myEvent)
{
	wxFileDialog mydialog(this, _T("Save file as..."), _T(""),Mozilla->GetTitle(),_T("HTML Files (htm,html)|*.htm,*.html"), wxSAVE|wxOVERWRITE_PROMPT);
	if (mydialog.ShowModal() == wxID_OK)
	{
		Mozilla->SavePage(mydialog.GetPath());
	}
	mydialog.Destroy();
}

void wxMozillaWindow::OpenNewWindow(wxMenuEvent &myEvent)
{
	if(eventURL){
		wxMozillaWindow *myWin = new wxMozillaWindow();
		myWin->Mozilla->LoadURL(eventURL);
		myWin->Show(TRUE);
	}

}
void wxMozillaWindow::OnMozillaRightClick(wxMozillaRightClickEvent &myEvent)
{
	/*
	//lastEvent = myEvent;
	wxMenu *myMenu = new wxMenu();
	if (myEvent.link){
		myMenu->Append(ID_OPEN_NEW_WINDOW, "Open in New Window");
		eventURL = myEvent.link;
	}
	if (myEvent.imageSrc){
		eventImage = myEvent.imageSrc;
	}
	wxPoint myPoint = myEvent.GetPosition();
	PopupMenu(myMenu, myPoint);
	
	myEvent.Skip();
	*/
}

void wxMozillaWindow::MakeEditable(wxEvent &myEvent)
{
	Mozilla->MakeEditable(TRUE);
}

void wxMozillaWindow::BoldClicked(wxEvent &myEvent)
{
	Mozilla->EditCommand("cmd_bold");
}

void wxMozillaWindow::ShowFindDlg(wxEvent &myEvent)
{
/*
	if (findDlg)
	{
		delete findDlg;
		findDlg = NULL;
	}
	//settings = new wxFindReplaceData(wxFR_DOWN|wxFR_WHOLEWORD);
	findDlg = new wxFindReplaceDialog(this, settings, "Find Text");
	findDlg->Show(TRUE);
        */
}

/*
void wxMozillaWindow::DoFind(wxFindDialogEvent &myEvent)
{
    wxEventType type = myEvent.GetEventType();
	bool result; 

	bool matchCase = FALSE;
	bool matchWholeWord = FALSE;
	bool searchBackwards = FALSE;

    if ( type == wxEVT_COMMAND_FIND)
	{
		int flags = myEvent.GetFlags();
		if (flags & wxFR_MATCHCASE)
			matchCase = TRUE;

		if (flags & wxFR_WHOLEWORD)
			matchWholeWord = TRUE;
		
		if (flags & wxFR_DOWN)
			searchBackwards = FALSE;
		else
			searchBackwards = TRUE;
			
		result = Mozilla->Find(myEvent.GetFindString(), matchCase, matchWholeWord, TRUE, searchBackwards);
	}
	else if (type == wxEVT_COMMAND_FIND_NEXT)
	{
		int flags = myEvent.GetFlags();
		if (flags & wxFR_MATCHCASE)
			matchCase = TRUE;

		if (flags & wxFR_WHOLEWORD)
			matchWholeWord = TRUE;
		
		if (flags & wxFR_DOWN)
			searchBackwards = FALSE;
		else
			searchBackwards = TRUE;

		result = Mozilla->Find(myEvent.GetFindString(), matchCase, matchWholeWord, TRUE, searchBackwards);
	}
	else if (type == wxEVT_COMMAND_FIND_CLOSE)
	{
		findDlg->Destroy();
		findDlg = NULL;
		settings = NULL;
	}

	if (!result)
		wxMessageDialog(this, "The text could not be found.", "Text Not Found").ShowModal();
}
*/

void wxMozillaWindow::DoCopy(wxEvent &myEvent)
{
	Mozilla->Copy();
  //if (myClipboard->Open())
  //{
    //right now we automatically assume the selection is part of the mozilla contorl
	  //for testing purposes
   // myClipboard->SetData( new wxTextDataObject(Mozilla->GetSelection()) );
   // myClipboard->Close();
  //}
}

void wxMozillaWindow::SelectAll(wxEvent &myEvent)
{
	Mozilla->SelectAll();
}

void wxMozillaWindow::SelectNone(wxEvent &myEvent)
{
	Mozilla->SelectNone();
}
void wxMozillaWindow::UpdateURL(wxMozillaLinkChangedEvent &myEvent)
{
	if (hasToolbar){
	toolbar->EnableTool(ID_BACK, myEvent.canGoBack);
	toolbar->EnableTool(ID_NEXT, myEvent.canGoForward);
	txtURL->SetValue(myEvent.newURL);
	}
}

void wxMozillaWindow::UpdateStatus(wxMozillaStatusChangedEvent &myEvent)
{
	if (hasToolbar)
		toolbar->EnableTool(ID_STOP, myEvent.isBusy);
	if (hasStatusbar)
		statusBar->SetStatusText(myEvent.statusText);
	SetTitle(wxString("wxMozilla - ") + Mozilla->GetTitle());

}
