/////////////////////////////////////////////////////////////////////////////
// Name:        wx/qt/nonownedwnd.h
// Author:      Sean D'Epagnier
// Copyright:   (c) 2016 wxWidgets dev team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_QT_NONOWNEDWND_H_
#define _WX_QT_NONOWNEDWND_H_

#include "wx/platform.h"

#if wxUSE_GUI

// ----------------------------------------------------------------------------
// wxNonOwnedWindow contains code common to wx{Popup,TopLevel}Window in wxQT.
// ----------------------------------------------------------------------------

class WXDLLIMPEXP_CORE wxNonOwnedWindow : public wxNonOwnedWindowBase
{
public:
    wxNonOwnedWindow();

protected:
    virtual bool DoClearShape() override;
    virtual bool DoSetRegionShape(const wxRegion& region) override;
#if wxUSE_GRAPHICS_CONTEXT
    virtual bool DoSetPathShape(const wxGraphicsPath& path) override;
#endif // wxUSE_GRAPHICS_CONTEXT

    wxDECLARE_NO_COPY_CLASS(wxNonOwnedWindow);
};

#endif

#endif // _WX_QT_NONOWNEDWND_H_
