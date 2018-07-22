/*
 * wxMozillaBrowserChrome
 *
 * Developers:
 *  Jeremiah Cornelius McCarthy <jeremiah@whoop-ass.ca>
 *  Kevin Ollivier <kevino@tulane.edu>
 *  Dave Fancella <david.fancella@attbi.com>

 */

#include "wx/wxprec.h"

#include "wxMozilla.h"
#include "wxMozillaBrowserChrome.h"
#include "wxMozillaWindow.h"
#include "nsIWidget.h"
#include "nsWidgetsCID.h"
#include "nsRect.h"
#include "nsIURI.h"
#include "nsIDOMWindow.h"
//#include <Carbon/Carbon.h>

NS_IMPL_ADDREF(wxMozillaBrowserChrome)
NS_IMPL_RELEASE(wxMozillaBrowserChrome)

static NS_DEFINE_IID(kWindowCID, NS_WINDOW_CID);

//NS_IMPL_ISUPPORTS1(wxMozillaBrowserChrome, nsIWebBrowserChrome)

NS_INTERFACE_MAP_BEGIN(wxMozillaBrowserChrome)
	NS_INTERFACE_MAP_ENTRY_AMBIGUOUS(nsISupports, nsIWebBrowserChrome)
	NS_INTERFACE_MAP_ENTRY(nsIInterfaceRequestor)
	NS_INTERFACE_MAP_ENTRY(nsIWebBrowserChromeFocus)
	NS_INTERFACE_MAP_ENTRY(nsIWebBrowserChrome)
	NS_INTERFACE_MAP_ENTRY(nsIEmbeddingSiteWindow)
	NS_INTERFACE_MAP_ENTRY(nsIWebProgressListener)
	NS_INTERFACE_MAP_ENTRY(nsISupportsWeakReference)
	NS_INTERFACE_MAP_ENTRY(nsIContextMenuListener2)
	NS_INTERFACE_MAP_ENTRY(nsIWindowCreator)
NS_INTERFACE_MAP_END

/**
 * Creates a new instance of the mozilla browser chrome
 *
 * @param Moz
 * 	Pointer to the parent MozillaBrowser class
 *
 * @return
 * 	New class instance
 */
wxMozillaBrowserChrome::wxMozillaBrowserChrome(wxMozillaBrowser *Moz)
{
	//NS_INIT_REFCNT(); Now NS_INIT_ISUPPORTS?
	mMoz = Moz;
        //mNativeWindow
}

/**
 * Class destructor
 *
 */
wxMozillaBrowserChrome::~wxMozillaBrowserChrome()
{
	mMoz = NULL;
}

/**
 * Get interface
 * 
 * @param aIID
 * 	Mozilla identifier
 * @param aInstancePtr
 * 	Instance pointer
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::GetInterface(const nsIID &aIID, void **aInstancePtr)
{
	if(aIID.Equals(NS_GET_IID(nsIDOMWindow)))
	{
		if (mMoz->mWebBrowser)
             return mMoz->mWebBrowser->GetContentDOMWindow((nsIDOMWindow **) aInstancePtr);
		return NS_ERROR_NOT_INITIALIZED;
	}
 
     return QueryInterface(aIID, aInstancePtr);
}


NS_IMETHODIMP wxMozillaBrowserChrome::CreateChromeWindow(nsIWebBrowserChrome *parent, PRUint32 chromeFlags, nsIWebBrowserChrome **_retval) {
	printf("In create chrome window!");
	bool showMenu;
	bool showToolbar;
	bool showStatusbar;
	
	if (chromeFlags & nsIWebBrowserChrome::CHROME_MENUBAR)
		showMenu = TRUE;
	else
		showMenu = FALSE;

	if (chromeFlags & nsIWebBrowserChrome::CHROME_TOOLBAR)
		showToolbar = TRUE;
	else
		showToolbar = FALSE;

	if (chromeFlags & nsIWebBrowserChrome::CHROME_STATUSBAR)
		showStatusbar = TRUE;
	else
		showStatusbar = FALSE;

	wxMozillaWindow *mywin = new wxMozillaWindow(showMenu, showToolbar, showStatusbar);
	mywin->Show(TRUE);
	*_retval = NS_STATIC_CAST(nsIWebBrowserChrome *, mywin->Mozilla->Chrome);
	NS_ADDREF(*_retval);
	
	return NS_OK;
}

/**
 * Change focus to next element
 *
 * @return
 * 	Netscape status
 */

NS_IMETHODIMP wxMozillaBrowserChrome::FocusNextElement()
{
	printf("FocusNextElement()");
	return NS_ERROR_NOT_IMPLEMENTED;
}

/**
 * Change focus to previous element
 *
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::FocusPrevElement()
{
	printf("FocusPrevElement()");
	return NS_ERROR_NOT_IMPLEMENTED;
}

/*
 * Callback for progress change
 *
 * @param progress
 * 	Pointer to <code>nsIWebProgress</code> class
 * @param request
 * 	Pointer to <code>nsIRequest</code> class
 * @param curSelfProgress
 * 	Current self progress
 * @param maxSelfProgress
 * 	Maximum self progress	
 * @param curTotalProgress
 * 	Current total progress
 * @param maxTotalProgress
 * 	Maximum total progress
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::OnProgressChange(nsIWebProgress *progress, nsIRequest *request, PRInt32 curSelfProgress, PRInt32 maxSelfProgress, PRInt32 curTotalProgress, PRInt32 maxTotalProgress)
{
	mMoz->OnProgressChange();
	return NS_OK;
}

/**
 * On state chanage
 *
 * @param webProgress
 * 	Pointer <code>nsIWebProgress</code> class
 * @param aRequest
 * 	Pointer to <code>nsIRequest</code> class
 * @param progressStateFlags
 * 	Progress state flags
 * @param status
 * 	Status
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::OnStateChange(nsIWebProgress *webProgress, nsIRequest *aRequest, PRUint32 progressStateFlags, PRUint32 status)
{

	if ((progressStateFlags & STATE_START) && (progressStateFlags & STATE_IS_DOCUMENT))
	{
		mMoz->m_isBusy = TRUE;
	}

	if ((progressStateFlags & STATE_STOP) && (progressStateFlags & STATE_IS_DOCUMENT))
	{
		mMoz->m_isBusy = FALSE;
		//mMoz->m_status = ""; 
	}
	//mMoz->OnStatusChange();

	return NS_OK;
}

/**
 * On the location change
 *
 * @param webProgress
 * 	Pointer to <code>nsIWebProgress</code> class.
 * @param aRequest
 * 	Pointer to <code>nsIRequest</code> class.
 * @param location
 * 	Pointer to <code>nsIURI</code> class.
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::OnLocationChange(nsIWebProgress *webPRogress, nsIRequest *aRequest, nsIURI *location)
{
	mMoz->OnLocationChange();
	return NS_OK;
}

/**
 * On status changed
 *
 * @param webProgress
 * 	Pointer to <code>nsIWebProgress</code> class
 * @param aRequest
 * 	Pointer to <code>nsIRequest</code> class
 * @param aStatus
 * 	Status
 * @param aMessage
 * 	String of status
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::OnStatusChange(nsIWebProgress *webProgress, nsIRequest *aRequest, nsresult aStatus, const PRUnichar *aMessage)
{
	//const nsAFlatString& flat = PromiseFlatString(*aMessage);
	//const wxString myString = flat.get();
	nsCString aString;
	if (aMessage)
		aString.AssignWithConversion(aMessage);
	mMoz->m_status = aString.get();
	mMoz->OnStatusChange(); //pass the event to the UI
	//printf("OnStatusChange()");
	return NS_OK;
}

/**
 * On security settings changed
 *
 * @param aWebProgress
 * 	Pointer to <code>nsIWebProgress</code> class
 * @param aRequest
 * 	Pointer to <code>nsIRequest</code> class
 * @param state
 * 	State
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::OnSecurityChange(nsIWebProgress *aWebProgress, nsIRequest *aRequest, PRUint32 status)
{
	printf("OnSecurityChange()");
	return NS_ERROR_NOT_IMPLEMENTED;
}

/**
 * Set status message
 *
 * @param statusType
 * 	Type of status
 * @param status
 * 	String containing status message
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::SetStatus(PRUint32 statusType, const PRUnichar *status)
{
	nsCString aString;
	if (status)
		aString.AssignWithConversion(status);
	mMoz->m_status = aString.get();
	mMoz->OnStatusChange();
	return NS_OK;
}

/**
 * Get the web browser class
 *
 * @param aWebBrowser
 * 	Object to assign class to
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::GetWebBrowser(nsIWebBrowser **aWebBrowser)
{
	NS_ENSURE_ARG_POINTER(aWebBrowser);
	NS_ENSURE_TRUE(mMoz->mWebBrowser, NS_ERROR_NOT_INITIALIZED);
	*aWebBrowser = mMoz->mWebBrowser;
	NS_IF_ADDREF(*aWebBrowser);
	return NS_OK;
}

/**
 * Set web browser
 *
 * @param aWebBrowser
 * 	Browser to assign to chrome
 * @return
 *	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::SetWebBrowser(nsIWebBrowser * aWebBrowser)
{
	printf("NI: SetWebBrowser\n");
	NS_ENSURE_ARG(aWebBrowser);
	NS_ENSURE_TRUE(mMoz->mWebBrowser, NS_ERROR_NOT_INITIALIZED);
	mMoz->mWebBrowser = aWebBrowser;
	return NS_OK;
}

/**
 * Get chrome flags
 * 
 * @param aChromeFlags
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::GetChromeFlags(PRUint32 *aChromeFlags)
{
	return NS_ERROR_FAILURE;
}

/**
 * Set chrome flags
 *
 * @param aChromeFlags
 * 	Chrome flags to assign
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::SetChromeFlags(PRUint32 aChromeFlags)
{
	
	return NS_ERROR_FAILURE;
}

/**
 * Destroy the browser window
 *
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::DestroyBrowserWindow()
{
	mMoz->GetParent()->Destroy();
	return NS_OK;
}

/**
 * Size browser to specified width and height
 *
 * @param aCX
 * 	Width
 * @param aXY
 * 	Height
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::SizeBrowserTo(PRInt32 aCX, PRInt32 aCY)
{
	mMoz->SetSize(aCX, aCY);
	
	return NS_OK;
}

/**
 * Show as modal window
 *
 * @return
 *	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::ShowAsModal()
{
	    return NS_ERROR_NOT_IMPLEMENTED;
}

/**
 * Checks to determine if window is modal
 *
 * @param _retval
 * 	Boolean return value indicating modality
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::IsWindowModal(PRBool *_retval)
{
	*_retval = PR_FALSE;
	return NS_OK;
}

/**
 * Exits a modal event loop
 *
 * @param aStatus
 * 	Status of action
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::ExitModalEventLoop(nsresult aStatus)
{
	return NS_ERROR_NOT_IMPLEMENTED;
}

/**
 * Set window dimensions
 *
 * @param flags
 * 	Window flags
 * @param x
 * 	Top left x coordinate of window
 * @param y
 * 	Top left y coordinate of window
 * @param cx
 * 	Width of window
 * @param cy
 * 	Height of window
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::SetDimensions(PRUint32 flags, PRInt32 x, PRInt32 y, PRInt32 cx, PRInt32 cy)
{
	if (mBaseWindow){
	if((flags & nsIEmbeddingSiteWindow::DIM_FLAGS_POSITION) &&
		(flags & (nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_INNER |
			   nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_OUTER)))
	{
                printf("Set dimensions called!");
		mMoz->Move(x,y);
		mMoz->SetSize(cx, cy);
		//mMoz->SetPositionAndSize(x, y, cx, cy, PR_TRUE);
		return NS_OK;
	}
	else if(flags & nsIEmbeddingSiteWindow::DIM_FLAGS_POSITION)
	{
		mMoz->Move(x, y);
		return NS_OK;
	}
	else if(flags & (nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_INNER |
			nsIEmbeddingSiteWindow::DIM_FLAGS_SIZE_OUTER))
	{
		mMoz->SetSize(x, y);
		return NS_OK;
	}
	
	return NS_ERROR_INVALID_ARG;
	}
	else
	{
		return NS_ERROR_INVALID_ARG;
	}
}

/**
 * Get window dimensions
 *
 * @param flags
 * 	Browser flags
 * @param x
 * 	Top left x coordinate of window
 * @param y
 * 	Top left y coordinate of window
 * @param cx
 * 	Width of window
 * @param cy
 * 	Height of window
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::GetDimensions(PRUint32 flags, PRInt32 *x, PRInt32 *y, PRInt32 *cx, PRInt32 *cy)
{
	wxSize mysize;
	wxPoint mypoint;
	mysize = mMoz->GetSize();
	mypoint = mMoz->GetPosition();
	//caller will pass nsnull if they do not want the value
	if (x != nsnull)
		*x = mypoint.x;
	if (y != nsnull)
		*y = mypoint.y;
	if (cx != nsnull)
		*cx = mysize.x;
	if (cy != nsnull)
		*cy = mysize.y;


	return NS_OK;
}

/**
 * Set focus to window
 *
 * @return
 *	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::SetFocus()
{
	mMoz->SetFocus();
	return NS_OK;
}

/**
 * Check for visibility of window
 *
 * @param Vis
 * 	Pointer to boolean
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::GetVisibility(PRBool *Vis)
{
	if (mMoz->IsShown())
		*Vis = PR_TRUE;
	else
		*Vis = PR_FALSE;
	return NS_OK;
}

/**
 * Set visibility of window
 *
 * @param Vis
 * 	Show window if true, otherwise hide
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::SetVisibility(PRBool Vis)
{
        if(Vis)
            mMoz->Show(TRUE);
        else
            mMoz->Show(FALSE);
       return NS_OK;
}

/**
 * Get title of browser window
 *
 * @param title
 * 	Pointer to string to contain title
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::GetTitle(PRUnichar **title)
{
	NS_ENSURE_ARG_POINTER(title);
	nsString tmp;

	tmp.AssignWithConversion((const char *)mMoz->GetTitle());
	*title = ToNewUnicode(tmp);
	
	return NS_OK;
}

/**
 * Set title of browser window
 *
 * @param title
 * 	String to set window title to
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::SetTitle(const PRUnichar *title)
{
	NS_ENSURE_ARG_POINTER(title);
	nsCString aString;
	if (title)
		aString.AssignWithConversion(title);
	mMoz->SetTitle(aString.get());
	return NS_OK;
}

/**
 * Get pointer to site window
 *
 * @param aSiteWindow
 * @return
 * 	Netscape status
 */
NS_IMETHODIMP wxMozillaBrowserChrome::GetSiteWindow(void **aSiteWindow)
{
	NS_ENSURE_ARG_POINTER(aSiteWindow);
#ifdef __WXMSW__
	*aSiteWindow = nsNativeWidget(mMoz->GetHWND());
#elif defined(__WXMAC__)
        *aSiteWindow = nsNativeWidget(mMoz->GetHandle());
#endif
	return NS_OK;
}


/*
NS_IMETHODIMP wxMozillaBrowserChrome::OnShowContextMenu(PRUint32 aContextFlags, nsIDOMEvent *aEvent, nsIDOMNode *aNode)
*/
NS_IMETHODIMP wxMozillaBrowserChrome::OnShowContextMenu(PRUint32 aContextFlags, nsIContextMenuInfo *aInfo) 
{
	wxMozillaRightClickEvent thisEvent = wxMozillaRightClickEvent(this->mMoz);
	
	if(aContextFlags & nsIContextMenuListener2::CONTEXT_DOCUMENT)
	{
		//just check for background image and pass to the handler
		thisEvent.context = "document";
		if (aContextFlags & nsIContextMenuListener2::CONTEXT_BACKGROUND_IMAGE)
		{
			nsCOMPtr<nsIURI> imgURI;
            aInfo->GetBackgroundImageSrc(getter_AddRefs(imgURI));
			nsCString aString;
			imgURI->GetSpec(aString);
			thisEvent.backgroundImage = aString.get();
		}
	}
	else if(aContextFlags & nsIContextMenuListener2::CONTEXT_TEXT)
	{
		//set the context and leave - embedder can use "GetSelection" to get text
		thisEvent.context = "text";
	}
	else if(aContextFlags & nsIContextMenuListener2::CONTEXT_LINK)
	{
		thisEvent.context = "link";
		nsAutoString urlString;
        nsresult rv = aInfo->GetAssociatedLink(urlString);
		if(NS_FAILED(rv))
            return NS_OK;
		thisEvent.link = urlString.get();

		nsCOMPtr<nsIURI> imgURI;
        aInfo->GetImageSrc(getter_AddRefs(imgURI));
		if (imgURI){
			nsCString aString;
			imgURI->GetSpec(aString);
			thisEvent.imageSrc = aString.get();
		}
	}
	else if(aContextFlags & nsIContextMenuListener2::CONTEXT_IMAGE)
	{
		thisEvent.context = "image";
		nsCOMPtr<nsIURI> imgURI;
        aInfo->GetImageSrc(getter_AddRefs(imgURI));
		if (imgURI){
			nsCString aString;
			imgURI->GetSpec(aString);
			thisEvent.imageSrc = aString.get();
		}
	}
	
	mMoz->ProcessEvent(thisEvent);
	return NS_OK;
}
