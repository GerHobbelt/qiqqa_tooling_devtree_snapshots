///////////////////////////////////////////////////////////////////////////////
// Name:        wx/generic/dvrenderer.h
// Purpose:     wxDataViewRenderer for generic wxDataViewCtrl implementation
// Author:      Robert Roebling, Vadim Zeitlin
// Created:     2009-11-07 (extracted from wx/generic/dataview.h)
// Copyright:   (c) 2006 Robert Roebling
//              (c) 2009 Vadim Zeitlin <vadim@wxwidgets.org>
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef _WX_GENERIC_DVRENDERER_H_
#define _WX_GENERIC_DVRENDERER_H_

#include "wx/platform.h"

#if wxUSE_GUI

// ----------------------------------------------------------------------------
// wxDataViewRenderer
// ----------------------------------------------------------------------------

class WXDLLIMPEXP_ADV wxDataViewRenderer: public wxDataViewCustomRendererBase
{
public:
    wxDataViewRenderer( const wxString &varianttype,
                        wxDataViewCellMode mode = wxDATAVIEW_CELL_INERT,
                        int align = wxDVR_DEFAULT_ALIGNMENT );
    virtual ~wxDataViewRenderer();

    virtual wxDC *GetDC() override;

    virtual void SetAlignment( int align ) override;
    virtual int GetAlignment() const override;

    virtual void EnableEllipsize(wxEllipsizeMode mode = wxELLIPSIZE_MIDDLE) override
        { m_ellipsizeMode = mode; }
    virtual wxEllipsizeMode GetEllipsizeMode() const override
        { return m_ellipsizeMode; }

    virtual void SetMode( wxDataViewCellMode mode ) override
        { m_mode = mode; }
    virtual wxDataViewCellMode GetMode() const override
        { return m_mode; }

    // implementation

    // This callback is used by generic implementation of wxDVC itself.  It's
    // different from the corresponding ActivateCell() method which should only
    // be overridable for the custom renderers while the generic implementation
    // uses this one for all of them, including the standard ones.

    virtual bool WXActivateCell(const wxRect& WXUNUSED(cell),
                                wxDataViewModel *WXUNUSED(model),
                                const wxDataViewItem & WXUNUSED(item),
                                unsigned int WXUNUSED(col),
                                const wxMouseEvent* WXUNUSED(mouseEvent))
        { return false; }

    void SetState(int state) { m_state = state; }

protected:
    virtual bool IsHighlighted() const override
        { return m_state & wxDATAVIEW_CELL_SELECTED; }

private:
    int                          m_align;
    wxDataViewCellMode           m_mode;

    wxEllipsizeMode m_ellipsizeMode;

    wxDC *m_dc;

    int m_state;

    wxDECLARE_DYNAMIC_CLASS_NO_COPY(wxDataViewRenderer);
};

#endif

#endif // _WX_GENERIC_DVRENDERER_H_

