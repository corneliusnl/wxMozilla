/*
 * wxWindows Mozilla Browser Events Component
 * 
 * Developers:
 *  Jeremiah Cornelius McCarthy <jeremiah@whoop-ass.ca>
 *  Kevin Ollivier <kevino@tulane.edu>
 *  Dave Fancella <david.fancella@attbi.com>
 */

#include "wx/wxprec.h"

#include "wxMozilla.h"

IMPLEMENT_DYNAMIC_CLASS( wxMozillaLinkChangedEvent, wxCommandEvent )
IMPLEMENT_DYNAMIC_CLASS( wxMozillaStatusChangedEvent, wxCommandEvent )
IMPLEMENT_DYNAMIC_CLASS( wxMozillaRightClickEvent, wxMouseEvent )


DEFINE_EVENT_TYPE( myEVT_MOZILLA_URL_CHANGED )
DEFINE_EVENT_TYPE( myEVT_MOZILLA_STATUS_CHANGED )
DEFINE_EVENT_TYPE( myEVT_MOZILLA_RIGHT_CLICK )

wxMozillaLinkChangedEvent::wxMozillaLinkChangedEvent( wxWindow* win )
{
    SetEventType( myEVT_MOZILLA_URL_CHANGED);
    SetEventObject( win );
}

wxMozillaStatusChangedEvent::wxMozillaStatusChangedEvent( wxWindow* win )
{
    SetEventType( myEVT_MOZILLA_STATUS_CHANGED);
    SetEventObject( win );
}

wxMozillaRightClickEvent::wxMozillaRightClickEvent( wxWindow* win )
{
    SetEventType( myEVT_MOZILLA_RIGHT_CLICK);
    SetEventObject( win );
}
