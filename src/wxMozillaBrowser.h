#ifndef __WX_MOZILLA_BROWSER_H__
#define __WX_MOZILLA_BROWSER_H__
/*
 * wxWindows Mozilla Component
 * Copyright 2001 (c) Jeremiah Cornelius McCarthy. All Rights Reserved.
 * 
 * Developers:
 *  Jeremiah Cornelius McCarthy <jeremiah@whoop-ass.ca>
 *  Kevin Ollivier <kevino@tulane.edu>
 *  Dave Fancella <david.fancella@attbi.com>    
 */

/* wxwindow includes */

// forward declarations

class nsIBaseWindow;
class nsIWebBrowser;
class nsIWebNavigation;
class nsICommandManager;

class wxMozillaBrowserChrome;

#ifdef __WXMAC__
class nsIEventSink;
#endif


// wxWindows headers

#include "wx/defs.h"
#include "wx/window.h"

#include "wxMozilla.h"
#include "nsCOMPtr.h"
//#include "wxMozillaBrowserChrome.h"

//for editing mode
/*
#include "nsICommandParams.h"
#include "nsIEditingSession.h"
#include "nsICommandManager.h"
#include "nsIScriptGlobalObject.h"
#include "nsISimpleEnumerator.h"
#include "nsIDOMWindow.h"
#include "nsIDOMDocument.h"
*/
//wxMac needs this to dispatch events to Mozilla
#ifdef __WXMAC__
	#include "nsIEventSink.h"
#endif

extern const char *wxMozillaBrowserNameStr;

/**
 * wxWindows Mozilla browser component
 */
class wxMozillaBrowser: public wxWindow
{
	friend class wxMozillaBrowserChrome;
	//private class int instances;

private:
	DECLARE_DYNAMIC_CLASS(wxMozillaBrowser)
		
protected:
	class wxMozillaBrowserChrome *Chrome;

	nsCOMPtr<nsIBaseWindow> mBaseWindow;
	nsCOMPtr<nsIWebBrowser> mWebBrowser;
	nsCOMPtr<nsIWebNavigation> mWebNav;
	nsCOMPtr<nsICommandManager> mCommandManager; //for editing, NYI
#ifdef __WXMAC__
    nsCOMPtr<nsIEventSink> mEventSink;
#endif

	static int gNumInstances;

	//Mozilla events
	void OnLocationChange();
	void OnStatusChange();
	void OnProgressChange();
	void OnRightClick();

    WXWidget m_macControl;
    bool m_needParent;
    bool m_acceptsFocus;
	wxString m_status;
	bool m_isEditable;
	bool m_isBusy;

public:

	wxMozillaBrowser();
	wxMozillaBrowser(wxWindow *parent, wxWindowID id,
		const wxPoint &pos = wxDefaultPosition,
		const wxSize &size = wxDefaultSize,
		long style = 0,
        	const wxString &name = wxMozillaBrowserNameStr);
	//{
	//	Create(parent, id, pos, size, style, name);
	//}
	virtual ~wxMozillaBrowser();

	bool Create(wxWindow *parent, wxWindowID id,
		const wxPoint &pos = wxDefaultPosition,
		const wxSize &size = wxDefaultSize,
		long style = 0,
	       	const wxString &name = wxMozillaBrowserNameStr);

	virtual bool LoadURL(const wxString &location);
	wxString GetURL();

	bool SavePage(const wxString &filename);
	bool IsBusy();
	void SetProfilePath(const wxString &path);
	bool GoBack();
	bool CanGoBack();
	bool GoForward();
	bool CanGoForward();
	bool Stop();
	bool Reload();
	bool Find(const wxString &searchString, bool matchCase = FALSE, bool matchWholeWord = FALSE, bool wrapAround = TRUE, bool searchBackwards = FALSE);
	bool FindNext();
	wxString GetStatus();
	wxString GetSelection();
	void Copy();
	void SelectAll();
	void SelectNone();
	
	/* Not Yet Implemented - or at least not working! */
	void MakeEditable(bool enable=TRUE);
	bool IsEditable();
	void EditCommand(const wxString &cmdId, int params = 0);
	bool OpenStream(const wxString &location, const wxString &type);
	bool AppendToStream(const wxString &data);
	bool CloseStream();
	void OnSize(wxSizeEvent &event);
    #ifdef __WXMAC__
        void OnPaint(wxPaintEvent &event);
        void OnActivate(wxActivateEvent &event);
        void OnMove(wxMoveEvent &event);
        void OnLeftDown(wxMouseEvent &event);
    #endif
	wxString GetLinkMessage();
	wxString GetJSStatus();


	DECLARE_EVENT_TABLE()
//protected:
//	int m_numInstances;
};

#endif
