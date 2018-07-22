/*
 * wxWindows Mozilla Browser Component
 * 
 * Developers:
 *  Jeremiah Cornelius McCarthy <jeremiah@whoop-ass.ca>
 *  Kevin Ollivier <kevino@tulane.edu>
 *  Dave Fancella <david.fancella@attbi.com>
 */

#include "wx/dynlib.h"
#include "wx/wxprec.h"
#include "wx/control.h"
#include "wx/dialog.h"
#include "wxMozillaBrowser.h"
#include "wxMozillaBrowserChrome.h"
#include "nsIWidget.h"
#include "nsIWebNavigation.h"
#include "nsWidgetsCID.h"
#include "nsRect.h"
#include "mozilla-config.h"
#include "nsIWebNavigation.h"
//#include "nsISHistoryListener.h"
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
#include "wx/event.h"
#include "nsISelection.h"
#include "nsIURI.h"
#include "nsIClipboardCommands.h"
#include "nsIWebBrowserFind.h"
#include "nsIDOMWindow.h"
#include "nsIEditingSession.h"
#include "nsICommandManager.h"

#ifdef __WXMAC__
#include "Carbon/Carbon.h"
//#include "nsWidget.h"
#endif
//#include "wx/app.h" //wxPostEvent
#include "nsIWeakReference.h" //for nsIProgressListener
//#include "winEmbedFileLocProvider.h"

static NS_DEFINE_IID(kWindowCID, NS_WINDOW_CID);

static NS_DEFINE_CID(kEventQueueServiceCID, NS_EVENTQUEUESERVICE_CID);

#ifdef __WXGTK__
    static gint io_id = 0;
    static void handle_event_queue(gpointer data,  gint source, GdkInputCondition cond)
    {
        nsIEventQueue *eventQueue = (nsIEventQueue *)data;
	eventQueue->ProcessPendingEvents();
    }
#endif

IMPLEMENT_DYNAMIC_CLASS(wxMozillaBrowser, wxWindow)

BEGIN_EVENT_TABLE(wxMozillaBrowser, wxWindow)
	EVT_SIZE(wxMozillaBrowser::OnSize)
    #ifdef __WXMAC__ //need to override wxMac event handlers for Mozilla
        EVT_PAINT(wxMozillaBrowser::OnPaint)
        EVT_ACTIVATE(wxMozillaBrowser::OnActivate)
        EVT_MOVE(wxMozillaBrowser::OnMove)
        EVT_MOUSE_EVENTS(wxMozillaBrowser::OnLeftDown)
        //EVT_UPDATE_UI(wxMozillaBrowser::OnPaint)
        EVT_SET_FOCUS(wxMozillaBrowser::OnPaint)
        EVT_KILL_FOCUS(wxMozillaBrowser::OnPaint)
    #endif
END_EVENT_TABLE()

const wxChar *wxMozillaBrowserNameStr = wxT("Mozilla");

int wxMozillaBrowser::gNumInstances = 0;

/**
 * Creates a new instances of a Mozilla browser component class
 *
 * @param None.
 *
 * @return Class instance.
 */

wxMozillaBrowser::wxMozillaBrowser()
{

}

wxMozillaBrowser::wxMozillaBrowser(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
{

    Create(parent, id, pos, size, style, name);
}
/**
 * Destroys the instance
 * 
 * @param none
 * @return Nothing
 */
wxMozillaBrowser::~wxMozillaBrowser()
{
	if (mWebNav)
		mWebNav = nsnull;
	if (mBaseWindow)
	{
		mBaseWindow->Destroy();
		mBaseWindow = nsnull;
	}
	if (mWebBrowser)
		mWebBrowser = nsnull;

	if (Chrome)
	{
		Chrome->Release();
		Chrome = nsnull;
	}
#ifdef __WXMAC__
    if (mEventSink)
        mEventSink = nsnull;
#endif
	
	wxMozillaBrowser::gNumInstances--;
	if (wxMozillaBrowser::gNumInstances == 0){
		NS_TermEmbedding();
        #ifdef __WXGTK__
             gdk_input_remove(io_id);
		#endif
	}
}

/**
 * Create an embedded mozilla component
 *
 * @param parent
 * 	Parent window
 * @param id
 * 	Id of window
 * @param pos
 * 	Position of window
 * @param size
 * 	Size of window
 * @param style
 * 	Style of window
 * @param name
 * 	Name of window
 * @return
 * 	True on sucess, False on failure
 */
bool wxMozillaBrowser::Create(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
{
	nsresult rv;
	
	m_needParent = TRUE;
	m_acceptsFocus = TRUE;
	m_isEditable = FALSE;
	m_isBusy = FALSE;

        //initialize the base wxWindow...
    #ifdef __WXGTK__
        //for some reason, I get initialization errors if I call wxWindow::Create
        //even if I call gtk_widget_realize afterwards
        PreCreation(parent, pos, size);
	CreateBase(parent, id, pos, size, style, wxDefaultValidator, name);
	m_widget = gtk_event_box_new();
	m_parent->DoAddChild(this);
	PostCreation();

	gtk_widget_realize(GTK_WIDGET(m_parent->m_widget));
	gtk_widget_realize(GTK_WIDGET(m_widget));
	gtk_widget_show(GTK_WIDGET(m_widget));
	GTK_WIDGET_SET_FLAGS(m_widget, GTK_CAN_FOCUS);
    #else //this works on Windows and Mac
	wxWindow::Create(parent, id, pos, size, style, name);
    #endif
	/*
	 * MOZILLA
	 */
#ifdef __WXMSW__
     //Get location of GRE
	 char szKey[256];
     HKEY hRegKey = NULL;
     DWORD dwLength = _MAX_PATH * sizeof(char);
     long rc;
     char keyValue[_MAX_PATH + 1];
     char *pGreLocation = NULL;

     strcpy(szKey, "Software\\mozilla.org\\GRE\\1.3b");
 
     if (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, szKey, 0, KEY_QUERY_VALUE, &hRegKey) == ERROR_SUCCESS) 
     {
         if ((rc = ::RegQueryValueEx(hRegKey, "GreHome", NULL, NULL, (BYTE *)keyValue, &dwLength))==ERROR_SUCCESS)
         {
             pGreLocation = ::strdup(keyValue);
             ::RegCloseKey(hRegKey);
         }
     }
#endif
	nsCOMPtr<nsILocalFile> greDir;
    rv = NS_NewNativeLocalFile(nsDependentCString(pGreLocation), TRUE, getter_AddRefs(greDir));
	if (NS_FAILED(rv))
	{
		printf("did not create local file!");
		return FALSE;
	}

	NS_InitEmbedding(nsnull, nsnull);

//GTK needs this but this code was causing problems (and was unnecessary) under Windows. 
#if __WXGTK__
	nsCOMPtr <nsIEventQueueService> eventQService = do_GetService(kEventQueueServiceCID);
	if(!eventQService)
	{
		printf("Failed to create EventQueueService!\n");
		return NS_ERROR_FAILURE;
	}
	
	nsCOMPtr <nsIEventQueue> eventQueue;
	eventQService->GetThreadEventQueue(NS_CURRENT_THREAD, getter_AddRefs(eventQueue));
	if(!eventQueue)
	{
		printf("Failed to create EventQueue!\n");
                		return NS_ERROR_FAILURE;
	}
	io_id = gdk_input_add(eventQueue->GetEventQueueSelectFD(), GDK_INPUT_READ, handle_event_queue, eventQueue);
#endif	

        //contains implementations of Mozilla interfaces
	Chrome = new wxMozillaBrowserChrome(this);
	if(!Chrome)
	{
		printf("Failed to create chrome!\n");
		return NS_ERROR_FAILURE;
	}
	Chrome->AddRef();

	//create the web browser
	mWebBrowser = do_CreateInstance(NS_WEBBROWSER_CONTRACTID, &rv);
	if(NS_FAILED(rv))
	{
		printf("Failed to create web browser. Exiting...\n");
		return rv;
	}
	//tell it where to send events
    mWebBrowser->SetContainerWindow(NS_STATIC_CAST(nsIWebBrowserChrome *, Chrome));
 
	//set the type (contentWrapper vs chromeWrapper)
	nsCOMPtr<nsIDocShellTreeItem> dsti = do_QueryInterface(mWebBrowser);
	dsti->SetItemType(nsIDocShellTreeItem::typeContentWrapper);

        //this is what we will use to bind Mozilla to the wxWindow control
	mBaseWindow = do_QueryInterface(mWebBrowser);
	int posx, posy;
	this->GetPosition(&posx, &posy);

	int sizex, sizey;
	this->GetSize(&sizex, &sizey);

//pass a handle to the native window to Mozilla
#ifdef __WXMSW__
	rv = mBaseWindow->InitWindow(nsNativeWidget(this->GetHWND()), nsnull, 0, 0, sizex, sizey);
#elif defined(__WXGTK__) 
        rv = mBaseWindow->InitWindow(nsNativeWidget(m_widget), nsnull, 0, 0, sizex, sizey);
#elif defined(__WXMAC__) 
        rv = mBaseWindow->InitWindow(nsNativeWidget(this->MacGetRootWindow()), nsnull, posx, posy, sizex, sizey);
        //needed to start event handling on Mac
        mEventSink = do_GetInterface(mWebBrowser);
#endif 

	if(NS_FAILED(rv)){
		printf("Couldn't initialize base window. Exiting...\n");
		return FALSE;
     }
                
	rv = mBaseWindow->Create();
    if(NS_FAILED(rv)){
		printf("Couldn't create base window. Exiting...\n");
		return FALSE;
     }           

    //mBaseWindow->SetPositionAndSize(50, 50, sizex, sizey, PR_TRUE);
    rv = mBaseWindow->SetVisibility(PR_TRUE);

    //To get/update status
    nsWeakPtr weakling(dont_AddRef(NS_GetWeakReference(NS_STATIC_CAST(nsIWebProgressListener*, 
			Chrome))));
    (void)mWebBrowser->AddWebBrowserListener(weakling, NS_GET_IID(nsIWebProgressListener)); 

	nsCOMPtr<nsIWindowCreator> windowCreator(NS_STATIC_CAST(nsIWindowCreator *, Chrome));
   if (windowCreator) {
     nsCOMPtr<nsIWindowWatcher> wwatch(do_GetService(NS_WINDOWWATCHER_CONTRACTID));
     if (wwatch) 
		 wwatch->SetWindowCreator(windowCreator);
	}

    //we need this for loading/navigating pages
    mWebNav = do_QueryInterface(mWebBrowser);
    wxMozillaBrowser::gNumInstances++;
    wxPoint clientArea;
    return TRUE;
}

wxString wxMozillaBrowser::GetStatus()
{
	return m_status;
}

/**
 * Handles sizing of the component
 *
 * @param pEvent
 * 	Pointer to the size event class
 *
 * @return
 * 	Nothing
 */
void wxMozillaBrowser::OnSize(wxSizeEvent &pEvent)
{
	wxSize size = pEvent.GetSize();
	if (mBaseWindow)
		mBaseWindow->SetSize(size.x, size.y, PR_TRUE);
        Refresh();
	pEvent.Skip();
}

#ifdef __WXMAC__
void wxMozillaBrowser::OnPaint(wxPaintEvent &pEvent)
{
    EventRecord osEvent;
    osEvent.what = updateEvt;
    PRBool handled = PR_FALSE;
    if (mEventSink)
        mEventSink->DispatchEvent(&osEvent, &handled);
    Refresh();
    //GetParent()->Refresh();
    pEvent.Skip();
}

void wxMozillaBrowser::OnActivate(wxActivateEvent &pEvent){

    EventRecord osEvent;
    osEvent.what = activateEvt;
    if (pEvent.GetActive())
        osEvent.modifiers = activeFlag;
    else
        osEvent.modifiers = 0;
    PRBool handled = PR_FALSE;
    if (mEventSink)
        mEventSink->DispatchEvent(&osEvent, &handled);
    Refresh();
    GetParent()->Refresh();
    pEvent.Skip();
    
}

void wxMozillaBrowser::OnMove(wxMoveEvent &pEvent){

    wxPoint point = pEvent.GetPosition();
    if (mBaseWindow)
        mBaseWindow->SetPositionAndSize(point.x, point.y, nsnull, nsnull, PR_TRUE);
    Refresh();
    GetParent()->Refresh();
    pEvent.Skip();

}

void wxMozillaBrowser::OnLeftDown(wxMouseEvent &pEvent){
    EventRecord osEvent;
    osEvent.what = mouseDown;
    PRBool handled = PR_FALSE;
    if (mEventSink)
        mEventSink->DispatchEvent(&osEvent, &handled);
    Refresh();
    GetParent()->Refresh();
    pEvent.Skip();
}

#endif

void wxMozillaBrowser::OnRightClick()
{
	wxMozillaRightClickEvent thisEvent = wxMozillaRightClickEvent(this);
	

	ProcessEvent(thisEvent);

}

void wxMozillaBrowser::OnProgressChange()
{
	wxMozillaStatusChangedEvent thisEvent = wxMozillaStatusChangedEvent(this);
	thisEvent.isBusy = this->IsBusy();
	thisEvent.statusText = this->m_status;
	ProcessEvent(thisEvent);
        #ifdef __WXMAC__
            Refresh();
            GetParent()->Refresh();
        #endif
}


void wxMozillaBrowser::OnStatusChange()
{
	wxMozillaStatusChangedEvent thisEvent = wxMozillaStatusChangedEvent(this);
	PRBool myresult = PR_FALSE;
	thisEvent.isBusy = this->IsBusy();
	thisEvent.statusText = this->m_status;
	ProcessEvent(thisEvent);
        #ifdef __WXMAC__
            Refresh();
            GetParent()->Refresh();
        #endif
}

void wxMozillaBrowser::OnLocationChange()
{
	wxMozillaLinkChangedEvent thisEvent = wxMozillaLinkChangedEvent(this);
	thisEvent.canGoBack = this->CanGoBack();
	thisEvent.canGoForward = this->CanGoForward();
	thisEvent.newURL = this->GetURL();
	ProcessEvent(thisEvent);
        #ifdef __WXMAC__
            Refresh();
            GetParent()->Refresh();
        #endif
}

bool wxMozillaBrowser::IsBusy()
{
	return m_isBusy;
}
/**
 * Opens a URL address
 *
 * @param location
 * 	The URL to open
 *
 * @return
 * 	True if sucessful, otherwise false
 */
bool wxMozillaBrowser::LoadURL(const wxString &location)
{	
	nsresult rv;
	
	nsString mCurrentURI;
	mCurrentURI.AssignWithConversion((const char*)location);
	if (mWebNav){
		rv = mWebNav->LoadURI(mCurrentURI.get(), nsIWebNavigation::LOAD_FLAGS_NONE, NULL, NULL, NULL);
		if(NS_FAILED(rv)){
                        printf(wxT("Couldn't load URL!"));
			return FALSE;
                }
	}
	return TRUE;
}

/**
 * Returns the current URL address
 *
 * @return
 * 	Nothing
 */
wxString wxMozillaBrowser::GetURL()
{
	nsCAutoString aString;
	nsCOMPtr<nsIURI> currentURI;

	if (mWebNav){
		mWebNav->GetCurrentURI(getter_AddRefs(currentURI));
		currentURI->GetSpec(aString);
		return aString.get();
	}
	return _T("");
}

bool wxMozillaBrowser::Find(const wxString &searchString, bool matchCase, bool matchWholeWord, bool wrapAround, bool searchBackwards)
{
	nsCOMPtr<nsIWebBrowserFind> finder(do_GetInterface(mWebBrowser));
	if (!finder)
		return FALSE;

    nsString txtSearch;
    txtSearch.AssignWithConversion(searchString);
    finder->SetSearchString(txtSearch.get());

	if (matchCase)
		finder->SetMatchCase(PR_TRUE);
	else
		finder->SetMatchCase(PR_FALSE);

	if (matchWholeWord)
		finder->SetEntireWord(PR_TRUE);
	else
		finder->SetEntireWord(PR_FALSE);

	if (wrapAround)
		finder->SetWrapFind(PR_TRUE);
	else
		finder->SetWrapFind(PR_FALSE);

	if (searchBackwards)
		finder->SetFindBackwards(PR_TRUE);
	else
		finder->SetFindBackwards(PR_FALSE);

	PRBool result;
	finder->FindNext(&result);

	if (result)
		return TRUE;
	else
		return FALSE;

}

bool wxMozillaBrowser::FindNext()
{
	nsCOMPtr<nsIWebBrowserFind> finder(do_GetInterface(mWebBrowser));
	if (!finder)
		return FALSE;

	//find next means all settings are the same
	PRBool result;
	finder->FindNext(&result);

	if (result)
		return TRUE;
	else
		return FALSE;
}

wxString wxMozillaBrowser::GetSelection()
{
    nsresult rv ;
	nsCOMPtr<nsISelection> theSelection ;
	nsCOMPtr<nsIDOMWindow> theDomWindow;

	// Get the nsIDOMWindow interface in order to get nsISelection 
	rv = mWebBrowser->GetContentDOMWindow(getter_AddRefs(theDomWindow));

	// Now get the nsISelection interface
	rv = theDomWindow->GetSelection(getter_AddRefs(theSelection));
	PRUnichar* thetext;
	theSelection->ToString(&thetext);
	nsCString aString;
	if (thetext)
		aString.AssignWithConversion(thetext);
	return aString.get();

}

void wxMozillaBrowser::Copy()
{
	nsCOMPtr<nsIClipboardCommands> clipCmds = do_GetInterface(mWebBrowser);
 
    if(clipCmds)
      clipCmds->CopySelection();

}
void wxMozillaBrowser::SelectAll()
{
 nsCOMPtr<nsIClipboardCommands> clipCmds = do_GetInterface(mWebBrowser);
 
     if(clipCmds)
         clipCmds->SelectAll();

}

void wxMozillaBrowser::SelectNone()
{
 nsCOMPtr<nsIClipboardCommands> clipCmds = do_GetInterface(mWebBrowser);
 
     if(clipCmds)
         clipCmds->SelectNone();

}

void wxMozillaBrowser::MakeEditable(bool enable)
{

    nsCOMPtr<nsIDOMWindow> domWindow;
	nsresult rv;
    mWebBrowser->GetContentDOMWindow(getter_AddRefs(domWindow));
    if (!domWindow)
		return;

    nsCOMPtr<nsIEditingSession> editingSession = do_GetInterface(mWebBrowser, &rv);
    if (!editingSession){
		wxMessageDialog(this, "Cannot start editing session!").ShowModal();
		//Always fails here. mfcembed sample seems to have problems with embedding as well?
  	  return;
	}
  
	if (enable){
		mCommandManager = do_GetInterface(mWebBrowser, &rv);
		//NOTE: For Moz 1.1 and below, the middle parameter was not used
		editingSession->MakeWindowEditable(domWindow, "html", PR_TRUE);
		m_isEditable = TRUE;
	}else
		{
		mCommandManager = nsnull;
		editingSession->MakeWindowEditable(domWindow, "html", PR_FALSE);
		m_isEditable = FALSE;
		}
}

bool wxMozillaBrowser::IsEditable()
{
	return m_isEditable;
}

void wxMozillaBrowser::EditCommand(const wxString &cmdId, int params)
{
	nsresult rv;
	nsCOMPtr<nsICommandParams> myParams = do_CreateInstance(NS_COMMAND_PARAMS_CONTRACTID,&rv);
    
	nsCOMPtr<nsIDOMWindow> domWindow;
    mWebBrowser->GetContentDOMWindow(getter_AddRefs(domWindow));

	if (mCommandManager)
		mCommandManager->DoCommand(cmdId,myParams);
}
/**
 * Sets the profile path for the browser
 *
 * @param path
 * 	Path in which to store profile information
 *
 * @return
 * 	Nothing
 */
void wxMozillaBrowser::SetProfilePath(const wxString &path)
{
}

/**
 * Goes to URL previously visited
 *
 * @return
 * 	True
 */
bool wxMozillaBrowser::GoBack()
{
	if(mWebNav)
		mWebNav->GoBack();

	return TRUE;
}

/**
 * Checks to determine if previous URL available
 *
 * @return
 * 	True if available, otherwise false
 */
bool wxMozillaBrowser::CanGoBack()
{
	PRBool myresult = PR_FALSE;
	if(mWebNav)
		mWebNav->GetCanGoBack(&myresult);
	return myresult;
}
/**
 * Go forward in history
 *
 * @return
 * 	True if successful, otherwise false
 */
bool wxMozillaBrowser::GoForward()
{
	if(mWebNav)
		mWebNav->GoForward();

	return TRUE;
}

/**
 * Checks to determine if forward address available
 *
 * @return
 * 	True if succesful, otherwise false
 */
bool wxMozillaBrowser::CanGoForward()
{
	PRBool myresult = PR_TRUE;
	if(mWebNav)
		mWebNav->GetCanGoForward(&myresult);
	return myresult;
}

/**
 * Stop the loading of address
 *
 * @return
 * 	True if successful, otherwise false
 */
bool wxMozillaBrowser::Stop()
{
	if(mWebNav)
		mWebNav->Stop(nsIWebNavigation::STOP_ALL);

	return TRUE;
}

/**
 * Reload current address
 *
 * @return
 * 	True if successful, otherwise false
 */
bool wxMozillaBrowser::Reload()
{
	if(mWebNav)
		mWebNav->Reload(nsIWebNavigation::LOAD_FLAGS_NONE);
		
	return TRUE;
}

bool wxMozillaBrowser::SavePage(const wxString &filename)
{
	//Works, but has troubles with frames pages
	int extensionStart;
	char ext = '.';
	extensionStart = filename.Find(ext, TRUE);
	wxString fileFolder = filename.Mid(0, extensionStart);
	fileFolder = fileFolder + "_files";
        // Save the file
        nsCOMPtr<nsIWebBrowserPersist> persist(do_QueryInterface(mWebBrowser));
        if(persist)
        {
            nsCOMPtr<nsILocalFile> file;
            NS_NewNativeLocalFile(nsDependentCString(filename.c_str()), PR_TRUE, getter_AddRefs(file));

            nsCOMPtr<nsILocalFile> dataPath;
            NS_NewNativeLocalFile(nsDependentCString(fileFolder.c_str()), PR_TRUE, getter_AddRefs(dataPath));
     
            persist->SaveDocument(nsnull, file, dataPath, nsnull, 0, 0);
        }

	return TRUE;
}

/**
 * Opens a stream of data
 *
 * @param location
 * 	URL to open
 *
 * @param type
 * 	Type of stream
 *
 * @return
 * 	True if successsful, otherwise false
 */
bool wxMozillaBrowser::OpenStream(const wxString &location, const wxString &type)
{
//	Stream->Open(location, type);

	return TRUE;
}

bool wxMozillaBrowser::CloseStream()
{
	return TRUE;
}

/**
 * Appends data to opened stream
 *
 * @param data
 * 	String data to be appended
 *
 * @return
 * 	True on success, False on failure
 */
bool wxMozillaBrowser::AppendToStream(const wxString &data)
{
//	Stream->Append(data, data.length);
	return TRUE;
}

/**
 * Get hyperlink link message
 *
 * @return
 * 	String containing message
 */
wxString wxMozillaBrowser::GetLinkMessage()
{
	return wxString("");
}

/**
 * Get Javascript status
 *
 * @return
 * 	String containing message
 */
wxString wxMozillaBrowser::GetJSStatus()
{
	return wxString("");
}

