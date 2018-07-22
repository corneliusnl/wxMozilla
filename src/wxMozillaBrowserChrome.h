#ifndef __WX_MOZILLA_CHROME_H__
#define __WX_MOZILLA_CHROME_H__
/*
 * wxMozillaBrowserChrome
 * Copyright 2001 (c) Jeremiah Cornelius McCarthy. All Rights Reserved.
 */

#include "wxMozilla.h"
#include "wxMozillaBrowser.h"
#include "nsIWebBrowserChromeFocus.h"
#include "nsICommandParams.h"
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


// forward declarations


/**
 * Mozilla chrome manager
 */
class wxMozillaBrowserChrome: 
	public nsIWebBrowserChrome,
	public nsIWebBrowserChromeFocus,
	public nsIWebProgressListener,
	public nsIEmbeddingSiteWindow,
	public nsIInterfaceRequestor,
	public nsSupportsWeakReference,
	public nsIContextMenuListener2,
	public nsIWindowCreator
{

public:
	NS_DECL_ISUPPORTS
	NS_DECL_NSIWEBBROWSERCHROME
	NS_DECL_NSIWEBBROWSERCHROMEFOCUS
	NS_DECL_NSIWEBPROGRESSLISTENER
	NS_DECL_NSIINTERFACEREQUESTOR
	NS_DECL_NSIEMBEDDINGSITEWINDOW
	NS_DECL_NSICONTEXTMENULISTENER2
	NS_DECL_NSIWINDOWCREATOR

	wxMozillaBrowserChrome(class wxMozillaBrowser *moz);
	virtual ~wxMozillaBrowserChrome();
	void CreateBrowser();
        
protected:
	class wxMozillaBrowser *mMoz;
	void * siteWindow;
	nsCOMPtr<nsIWebBrowser> mWebBrowser;
	nsCOMPtr<nsIBaseWindow> mBaseWindow;
    nsCOMPtr<nsIWebNavigation> mWebNav;
};

#endif
