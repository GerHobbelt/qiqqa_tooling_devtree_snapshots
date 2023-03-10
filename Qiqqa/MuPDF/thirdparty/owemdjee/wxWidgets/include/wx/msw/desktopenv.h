//////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/desktopenv.h
// Purpose:     wxDesktopEnv class interface
// Author:      Igor Korot
// Created:     2021-09-05
// Copyright:   (c) 2021 wxWidgets development team
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef _WX_MSW_DESKTOPENV_H_
#define _WX_MSW_DESKTOPENV_H_

#include "wx/platform.h"
#include <vector>

#if wxUSE_GUI

// ----------------------------------------------------------------------------
// Desktop Environment
// ----------------------------------------------------------------------------

#define INVALID_MENU_ID (UINT)-1

class WXDLLIMPEXP_CORE wxDesktopEnv : public wxDesktopEnvBase
{
public:
    static bool MoveToRecycleBin(const wxString &path);
    static bool GetFilesInRecycleBin(std::vector<wxString> &files);
    static bool RestoreFromRecycleBin(const wxString &path);
};

#endif

#endif
