#ifndef __WX_MOZILLA_H__
#define __WX_MOZILLA_H__
/*
 * wxWindows Mozilla Component
 *
 * Developers:
 *  Jeremiah Cornelius McCarthy <jeremiah@whoop-ass.ca>
 *  Kevin Ollivier <kevino@tulane.edu>
 *  Dave Fancella <david.fancella@attbi.com>
 */

/* mozilla includes */
/*
#include "mozilla-config.h"
#include "nsIWebNavigation.h"
#include "nsISHistoryListener.h"
#include "nsString.h"
#include "nsCOMPtr.h"
#include "nsIEventQueueService.h"
#include "nsIPref.h"
#include "nsISupports.h"
#include "nsIBaseWindow.h"
#include "nsIWebBrowser.h"
#include "nsIWebBrowserPersist.h"
#include "nsIWebBrowserChrome.h"
#include "nsIEmbeddingSiteWindow.h"
#include "nsEmbedAPI.h"
#include "nsIWindowCreator.h"
#include "nsIWindowWatcher.h"
#include "nsCWebBrowser.h"
#include "nsIWebProgressListener.h"
#include "nsIContextMenuListener2.h"
#include "nsIInterfaceRequestor.h"
#include "nsIWebBrowserSetup.h"
#include "nsIDocShellTreeItem.h"
#include "nsIWebBrowserChromeFocus.h"
#include "nsIInterfaceRequestor.h"
#include "nsIInterfaceRequestorUtils.h"
#include "nsReadableUtils.h"
#include "nsIWeakReference.h"
#include "nsIWeakReferenceUtils.h"
#include "nsWeakReference.h"
*/

/* wxwindow includes */
#include "wx/defs.h"
#include "wx/window.h"

/*event class definitions*/
class wxMozillaLinkChangedEvent : public wxCommandEvent
{
    DECLARE_DYNAMIC_CLASS( wxMozillaLinkChangedEvent )

    public:
	wxString newURL;
	bool canGoBack;
	bool canGoForward;

    wxMozillaLinkChangedEvent( wxWindow* win = (wxWindow*) NULL );
	wxEvent *Clone(void) const { return new wxMozillaLinkChangedEvent(*this); }

    //void CopyObject( wxObject& obj ) const;
};

class wxMozillaStatusChangedEvent : public wxCommandEvent
{
    DECLARE_DYNAMIC_CLASS( wxMozillaStatusChangedEvent )

    public:
	wxString statusText;
	bool isBusy;

    wxMozillaStatusChangedEvent( wxWindow* win = (wxWindow*) NULL );
	wxEvent *Clone(void) const { return new wxMozillaStatusChangedEvent(*this); }
    //void CopyObject( wxObject& obj ) const;
};

class wxMozillaRightClickEvent : public wxMouseEvent
{
    DECLARE_DYNAMIC_CLASS( wxMozillaRightClickEvent )

    public:
	//wxString statusText;
	bool isBusy;
	wxString backgroundImage;
	wxString text;
	wxString imageSrc;
	wxString link;
	wxString context;

    wxMozillaRightClickEvent( wxWindow* win = (wxWindow*) NULL );
	wxEvent *Clone(void) const { return new wxMozillaRightClickEvent(*this); }
    //void CopyObject( wxObject& obj ) const;
};


typedef void (wxEvtHandler::*wxMozillaLinkChangedEventFunction)(wxMozillaLinkChangedEvent&);
typedef void (wxEvtHandler::*wxMozillaStatusChangedEventFunction)(wxMozillaStatusChangedEvent&);
typedef void (wxEvtHandler::*wxMozillaRightClickEventFunction)(wxMozillaRightClickEvent&);

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_EVENT_TYPE(myEVT_MOZILLA_URL_CHANGED, 1)
	DECLARE_EVENT_TYPE(myEVT_MOZILLA_STATUS_CHANGED, 1)
	DECLARE_EVENT_TYPE(myEVT_MOZILLA_RIGHT_CLICK, 1)
END_DECLARE_EVENT_TYPES()

#define EVT_MOZILLA_URL_CHANGED(func) \
            DECLARE_EVENT_TABLE_ENTRY( myEVT_MOZILLA_URL_CHANGED, \
                            -1,                       \
                            -1,                       \
                            (wxObjectEventFunction)   \
                            (wxMozillaLinkChangedEventFunction) & func, \
                            (wxObject *) NULL ),

#define EVT_MOZILLA_STATUS_CHANGED(func) \
            DECLARE_EVENT_TABLE_ENTRY( myEVT_MOZILLA_STATUS_CHANGED, \
                            -1,                       \
                            -1,                       \
                            (wxObjectEventFunction)   \
                            (wxMozillaStatusChangedEventFunction) & func, \
                            (wxObject *) NULL ),

#define EVT_MOZILLA_RIGHT_CLICK(func) \
            DECLARE_EVENT_TABLE_ENTRY( myEVT_MOZILLA_RIGHT_CLICK, \
                            -1,                       \
                            -1,                       \
                            (wxObjectEventFunction)   \
                            (wxMozillaRightClickEventFunction) & func, \
                            (wxObject *) NULL ),

#endif
