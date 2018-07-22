#ifndef __WX_MOZILLA_WINDOW_H__
#define __WX_MOZILLA_WINDOW_H__
/*
 * wxMozilla
 *
 * Developers:
 *  Jeremiah Cornelius McCarthy <jeremiah@whoop-ass.ca>
 *  Kevin Ollivier <kevino@tulane.edu>
 *  Dave Fancella <david.fancella@attbi.com>
 */

#include "wx/wx.h"
#include "wx/frame.h"
#include "wx/filedlg.h"
#include "wx/image.h"
//#include "wx/fdrepdlg.h"
#include "wx/clipbrd.h"
#include "wxMozillaBrowser.h"

class wxMozillaWindow: public wxFrame
{
private:
	DECLARE_DYNAMIC_CLASS(wxMozillaWindow)
	//wxBoxSizer *VBox;
	//wxBoxSizer *HBox;
	bool hasMenu;
	bool hasToolbar;
	bool hasStatusbar;
	wxMozillaBrowser *MozWnd2;
	wxStaticText *lblAddress;
	wxButton *GoButton;
	wxButton *BackButton;
	wxButton *NextButton;
	wxButton *StopButton;
	wxButton *RefreshButton;
	//wxClipboard *myClipboard;
//	wxFindReplaceDialog *findDlg;
//	wxFindReplaceData *settings;

	wxTextCtrl *txtURL;
	//store the event so that you can use its data 
	//when someone clicks on the popup menu.
	wxString eventURL;
	wxString eventImage;
	wxString eventBgImage;
	wxToolBar *toolbar;
	wxStatusBar *statusBar;
	wxMenuBar* appMenuBar;
	wxMenu* fileMenu;
	wxMenu* editMenu;
	wxMenu* viewMenu;
	//wxMenuItem* stopItem;
	//wxMenuItem* saveItem;
	//wxMenuItem* refreshItem;

	//wxArtProvider *imageList;
	void NewWindow(wxMenuEvent &myEvent);
	void OpenNewWindow(wxMenuEvent &myEvent);
	void Quit(wxMenuEvent &myEvent);
	void ViewSource(wxMenuEvent &myEvent);
	void GoClicked(wxEvent &myEvent);
	void BackClicked(wxEvent &myEvent);
	void NextClicked(wxEvent &myEvent);
	void StopLoading(wxEvent &myEvent);
	void RefreshPage(wxEvent &myEvent);
	void SaveClicked(wxEvent &myEvent);
	void MakeEditable(wxEvent &myEvent);
	void BoldClicked(wxEvent &myEvent);
	void DoCopy(wxEvent &myEvent);
	void SelectAll(wxEvent &myEvent);
	void SelectNone(wxEvent &myEvent);
	void ShowFindDlg(wxEvent &myEvent);
//	void DoFind(wxFindDialogEvent &myEvent);
	void OnMozillaRightClick(wxMozillaRightClickEvent &event);
	void UpdateURL(wxMozillaLinkChangedEvent &myEvent);
	void UpdateStatus(wxMozillaStatusChangedEvent &myEvent); //determine the state of back and next buttons
	DECLARE_EVENT_TABLE()

public:

	wxMozillaWindow(bool showMenu = TRUE, bool showToolbar = TRUE, bool showStatusbar = TRUE);
	wxMozillaBrowser *Mozilla;
};
#endif
