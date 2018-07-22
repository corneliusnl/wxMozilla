/////////////////////////////////////////////////////////////////////////////
// Name:        mozillawin.h
// Purpose:     wxMozillaWindow class for parsing & displaying HTML use Mozilla
// Author:      Myers Carpenter
// RCS-ID:      $Id: mozillawin.h,v 1.1.1.1 2002/04/16 02:03:37 myers_carpenter Exp $
// Copyright:   (c) 2002 Myers Carpenter
// Licence:     wxWindows Licence
/////////////////////////////////////////////////////////////////////////////


#ifndef _WX_MOZILLAWIN_H_
#define _WX_MOZILLAWIN_H_

#ifdef __GNUG__
#pragma interface "mozillawin.h"
#endif

//#include "wx/defs.h"
#if wxUSE_MOZILLA

#include "wx/window.h"

class wxMozillaWindowImpl;

//--------------------------------------------------------------------------------
// wxMozillaWindow
//                  (This is probably the only class you will directly use.)
//                  Purpose of this class is to display HTML page (either local
//                  file or downloaded via HTTP protocol) in a window.  It's meant 
//                  to be a drop in replacement for wxHtmlWindow.
//                  Once the window is created you can set it's content by calling
//                  SetPage(text) or LoadPage(filename).
//--------------------------------------------------------------------------------

class WXDLLEXPORT wxMozillaWindow : public wxWindow
{
    DECLARE_DYNAMIC_CLASS(wxMozillaWindow)
    wxMozillaWindowImpl* _impl;

public:
    wxMozillaWindow();
    wxMozillaWindow(wxWindow *parent, wxWindowID id = -1,
                 const wxPoint& pos = wxDefaultPosition,
                 const wxSize& size = wxDefaultSize,
                 long style = wxHW_SCROLLBAR_AUTO,
                 const wxString& name = wxT("htmlWindow"));
                 
    ~wxMozillaWindow();

    bool Create(wxWindow *parent, wxWindowID id = -1,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = wxHW_SCROLLBAR_AUTO,
                const wxString& name = wxT("htmlWindow"));

    // Set HTML page and display it. !! source is HTML document itself,
    // it is NOT address/filename of HTML document. If you want to
    // specify document location, use LoadPage() istead
    // Return value : FALSE if an error occured, TRUE otherwise
    bool SetPage(const wxString& source);
    
    // Append to current page
    bool AppendToPage(const wxString& source);

    // Load HTML page from given location. Location can be either
    // a) /usr/wxGTK2/docs/html/wx.htm
    // b) http://www.somewhere.uk/document.htm
    // c) ftp://ftp.somesite.cz/pub/something.htm
    // In case there is no prefix (http:,ftp:), the method
    // will try to find it itself (1. local file, then http or ftp)
    // After the page is loaded, the method calls SetPage() to display it.
    // Note : you can also use path relative to previously loaded page
    // Return value : same as SetPage
    virtual bool LoadPage(const wxString& location);

    // Returns full location of opened page
    wxString GetOpenedPage() const {return m_OpenedPage;}
    // Returns anchor within opened page
    wxString GetOpenedAnchor() const {return m_OpenedAnchor;}
    // Returns <TITLE> of opened page or empty string otherwise
    wxString GetOpenedPageTitle() const {return m_OpenedPageTitle;}

    // Sets frame in which page title will  be displayed. Format is format of
    // frame title, e.g. "HtmlHelp : %s". It must contain exactly one %s
    void SetRelatedFrame(wxFrame* frame, const wxString& format);
    wxFrame* GetRelatedFrame() const {return m_RelatedFrame;}

    // After(!) calling SetRelatedFrame, this sets statusbar slot where messages
    // will be displayed. Default is -1 = no messages.
    void SetRelatedStatusBar(int bar);

    // Sets fonts to be used when displaying HTML page.
    void SetFonts(wxString normal_face, wxString fixed_face, const int *sizes);

    // Sets the title of the window
    // (depending on the information passed to SetRelatedFrame() method)
    virtual void OnSetTitle(const wxString& title);

    // Goes to previous/next page (in browsing history)
    // Returns TRUE if successful, FALSE otherwise
    bool HistoryBack();
    bool HistoryForward();
    bool HistoryCanBack();
    bool HistoryCanForward();
    // Resets history
    void HistoryClear();

    // Called when user clicked on hypertext link. Default behavior is to
    // call LoadPage(loc)
    virtual void OnLinkClicked(const wxHtmlLinkInfo& link);

    // Returns a pointer to the parser.
    wxHtmlWinParser *GetParser() const { return m_Parser; }

    // Adds HTML processor to this instance of wxMozillaWindow:
    void AddProcessor(wxHtmlProcessor *processor);
    // Adds HTML processor to wxMozillaWindow class as whole:
    static void AddGlobalProcessor(wxHtmlProcessor *processor);

    // what would we do with it?
    virtual bool AcceptsFocusFromKeyboard() const { return FALSE; }
};


#endif // wxUSE_MOZILLA

#endif // _WX_MOZILLAWIN_H_

