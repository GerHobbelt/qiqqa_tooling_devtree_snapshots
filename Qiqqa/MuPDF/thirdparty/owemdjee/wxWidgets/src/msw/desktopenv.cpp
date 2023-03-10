///////////////////////////////////////////////////////////////////////////////
// Name:        src/msw/desktopenv.cpp
// Purpose:     implementation of wxDesktopEnvBase
// Author:      Igor Korot
// Created:     2021-09-05
// Copyright:   (c) 2021 wxWidgets development team
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#include "shlobj.h"
#include "wx/log.h"
#include "wx/desktopenv.h"
#include "wx/msw/private.h"

#if wxUSE_GUI

// ============================================================================
// implementation
// ============================================================================

/* static */
bool wxDesktopEnv::MoveToRecycleBin(const wxString &path)
{
    bool res = wxDesktopEnvBase::MoveToRecycleBin( path );
    if( res )
    {
        SHFILEOPSTRUCT fileOp;
        wxZeroMemory( fileOp );
        fileOp.hwnd = nullptr;
        fileOp.wFunc = FO_DELETE;
        wxString temp = path + '\0';
        fileOp.pFrom = temp.t_str();
        fileOp.pTo = nullptr;
        fileOp.fFlags = FOF_ALLOWUNDO | FOF_NOERRORUI | FOF_NOCONFIRMATION | FOF_SILENT;
        res = SHFileOperation( &fileOp );
        if( res != 0 )
            wxLogError( _( "Failed to move '%s' to Recycle Bin" ), path );
        else
            res = true;
    }
    return res;
}

/*static*/
bool wxDesktopEnv::GetFilesInRecycleBin(std::vector<wxString> &paths)
{
    bool res = false;
    LPITEMIDLIST pidl = nullptr;
    LPITEMIDLIST pidlRecycleBin	= nullptr;
    IShellFolder2 *m_pFolder2;
    LPSHELLFOLDER pDesktop = nullptr;
    STRRET strRet;
    TCHAR szPath[MAX_PATH], szTemp[MAX_PATH];
    wxString lpszName;
    LPENUMIDLIST penumFiles;
    SHELLDETAILS sd;
    SHFILEINFO fi;

    if( ( SUCCEEDED( SHGetDesktopFolder( &pDesktop ) ) ) &&
//        ( SUCCEEDED( SHGetFolderLocation( nullptr, CSIDL_BITBUCKET, nullptr, nullptr, &pidlRecycleBin ) ) ) )
        ( SHGetKnownFolderIDList( FOLDERID_RecycleBinFolder, KF_FLAG_DONT_VERIFY, nullptr, &pidlRecycleBin ) ) )
    {
        if( SUCCEEDED( pDesktop->BindToObject( pidlRecycleBin, nullptr, IID_IShellFolder2, (LPVOID *)&m_pFolder2 ) ) )
        {
            if( S_OK == pDesktop->GetDisplayNameOf( pidlRecycleBin, SHGDN_NORMAL, &strRet ) )
            {
                ZeroMemory( szPath, sizeof( szPath ) );
                switch( strRet.uType )
                {
                case STRRET_CSTR:
                    _tcscpy( szPath, strRet.pOleStr );
                    break;
                case STRRET_OFFSET:
                    break;
                case STRRET_WSTR:
                    memcpy( szPath, strRet.pOleStr, MAX_PATH );
                    CoTaskMemFree( strRet.pOleStr );
                    break;
                }
            }
            if( SUCCEEDED( m_pFolder2->EnumObjects( nullptr, SHCONTF_FOLDERS | SHCONTF_NONFOLDERS| SHCONTF_INCLUDEHIDDEN, &penumFiles ) ) )
            {
                int iSubItem = 0;
                while( penumFiles->Next( 1, &pidl, nullptr ) != S_FALSE )
                {
                    ::ZeroMemory( &fi, sizeof( fi ) );
                    if( SUCCEEDED( SHGetFileInfo( (LPCWSTR) pidl, 0, &fi, sizeof( fi ), SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_PIDL ) ) )
                    {
                        if( SUCCEEDED( m_pFolder2->GetDetailsOf( pidl, iSubItem, &sd ) ) )
                        {
                            switch( sd.str.uType )
                            {
                            case STRRET_CSTR:
                                _tcscpy( szTemp, sd.str.pOleStr );
                                break;
                            case STRRET_OFFSET:
                                break;
                            case STRRET_WSTR:
                                memcpy( szPath, sd.str.pOleStr, MAX_PATH );
                                CoTaskMemFree( sd.str.pOleStr );
                                break;
                            }
                            wxString tmp( szPath );
                            paths.push_back( tmp );
                            res = true;
                        }
                    }
                }
            }
        }
    }
    if( pidlRecycleBin )
        CoTaskMemFree( pidlRecycleBin );
    return res;
}

/* static */
bool wxDesktopEnv::RestoreFromRecycleBin(const wxString &path)
{
    bool res = false;
    LPITEMIDLIST pidl = nullptr;
    LPITEMIDLIST pidlRecycleBin	= nullptr;
    IShellFolder2 *m_pFolder2;
    LPSHELLFOLDER pDesktop = nullptr;
    STRRET strRet;
    TCHAR szPath[MAX_PATH], szTemp[MAX_PATH];
    wxString lpszName;
    LPENUMIDLIST penumFiles;
    SHELLDETAILS sd;
    SHFILEINFO fi;
    LPCONTEXTMENU pCtxMenu = nullptr;

    if( ( SUCCEEDED( SHGetDesktopFolder( &pDesktop ) ) ) &&
        ( SUCCEEDED( SHGetKnownFolderIDList( FOLDERID_RecycleBinFolder, KF_FLAG_DEFAULT, nullptr, &pidlRecycleBin ) ) ) )
    {
        if( SUCCEEDED( pDesktop->BindToObject( pidlRecycleBin, nullptr, IID_IShellFolder2, (LPVOID *)&m_pFolder2 ) ) )
        {
            if( S_OK == pDesktop->GetDisplayNameOf( pidlRecycleBin, SHGDN_NORMAL, &strRet ) )
            {
                ZeroMemory( szPath, sizeof( szPath ) );
                switch( strRet.uType )
                {
                case STRRET_CSTR:
                    _tcscpy( szPath, strRet.pOleStr );
                    break;
                case STRRET_OFFSET:
                    break;
                case STRRET_WSTR:
                    memcpy( szPath, strRet.pOleStr, MAX_PATH );
                    CoTaskMemFree( strRet.pOleStr );
                    break;
                }
            }
            if( SUCCEEDED( m_pFolder2->EnumObjects( nullptr, SHCONTF_FOLDERS | SHCONTF_NONFOLDERS| SHCONTF_INCLUDEHIDDEN, &penumFiles ) ) )
            {
                int iSubItem = 0;
                while( penumFiles->Next( 1, &pidl, nullptr ) != S_FALSE )
                {
                    ::ZeroMemory( &fi, sizeof( fi ) );
                    if( SUCCEEDED( SHGetFileInfo( (LPCWSTR) pidl, 0, &fi, sizeof( fi ), SHGFI_SYSICONINDEX | SHGFI_SMALLICON | SHGFI_PIDL ) ) )
                    {
                        if( SUCCEEDED( m_pFolder2->GetDetailsOf( pidl, iSubItem, &sd ) ) )
                        {
                            switch( sd.str.uType )
                            {
                            case STRRET_CSTR:
                                _tcscpy( szTemp, sd.str.pOleStr );
                                break;
                            case STRRET_OFFSET:
                                break;
                            case STRRET_WSTR:
                                memcpy( szPath, sd.str.pOleStr, MAX_PATH );
                                CoTaskMemFree( sd.str.pOleStr );
                                break;
                            }
                            wxString tmp( szPath );
                            if( path == tmp )
                            {
                                if( SUCCEEDED( m_pFolder2->GetUIObjectOf( nullptr, 1, (LPCITEMIDLIST *) &pidl, IID_IContextMenu, nullptr, (LPVOID *) &pCtxMenu ) ) )
                                {
                                    UINT uiID = INVALID_MENU_ID;
                                    UINT uiCommand = 0;
                                    UINT uiMenuFirst = 1;
                                    UINT uiMenuLast = 0x00007FFF;
                                    HMENU hmenuCtx;
                                    int iMenuPos = 0;
                                    int iMenuMax = 0;
                                    TCHAR szMenuItem[128];
                                    char verb[MAX_PATH];

                                    hmenuCtx = CreatePopupMenu();
                                    if( SUCCEEDED( pCtxMenu->QueryContextMenu( hmenuCtx, 0, uiMenuFirst, uiMenuLast, CMF_NORMAL ) ) )
                                    {
                                        iMenuMax = GetMenuItemCount( hmenuCtx );
                                        bool found = false;
                                        for( iMenuPos = 0 ; iMenuPos < iMenuMax && !found; iMenuPos++ )
                                        {
                                            GetMenuString( hmenuCtx, iMenuPos, szMenuItem, sizeof( szMenuItem ), MF_BYPOSITION );
                                            uiID = GetMenuItemID( hmenuCtx, iMenuPos );
                                            if( ( uiID == INVALID_MENU_ID ) || ( uiID == 0 ) )
                                            {
                                                wxLogError( _( "Error getting appropriate menu ID" ) );
                                            }
                                            else
                                            {
                                                HRESULT hr = pCtxMenu->GetCommandString( uiID - 1, GCS_VERBA, nullptr, verb, sizeof( verb ) );
                                                if( FAILED( hr ) )
                                                {
                                                    verb[0] = TCHAR( '\0' );
                                                }
                                                else
                                                {
                                                    wxString command( verb );
                                                    if( command == "undelete" )
                                                    {
                                                        found = true;
                                                        uiCommand = uiID - 1;
                                                        CMINVOKECOMMANDINFO cmi;
                                                        ::ZeroMemory( &cmi, sizeof( CMINVOKECOMMANDINFO ) );
                                                        cmi.cbSize			= sizeof( CMINVOKECOMMANDINFO );
                                                        cmi.fMask			= CMIC_MASK_FLAG_NO_UI;
                                                        cmi.hwnd			= nullptr;
                                                        cmi.lpParameters	= nullptr;
                                                        cmi.lpDirectory		= nullptr;
                                                        cmi.lpVerb			= (LPSTR) MAKEINTRESOURCE( uiCommand );
                                                        cmi.nShow			= SW_SHOWNORMAL;
                                                        cmi.dwHotKey		= 0;
                                                        cmi.hIcon			= nullptr;
                                                        hr = pCtxMenu->InvokeCommand( &cmi );
                                                        if( SUCCEEDED( hr ) )
                                                        {
                                                            res = TRUE;
                                                        }
                                                        else
                                                            wxLogSysError( _( "Failed to call undelete" ) );
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    else
                                        wxLogSysError( _( "Failed to obtain context menu" ) );
                                }
                            }
                        }
                    }
                }
            }
            else
                wxLogSysError( _( "Failed to enumerate objects in Recycle Bin" ) );
        }
    }
    else
        wxLogSysError( _( "Failed to obtain reference to Recycle Bin" ) );
    if( pidlRecycleBin )
    {
        CoTaskMemFree( pidlRecycleBin );
    }
    if( pDesktop )
    {
        pDesktop->Release();
    }
    return res;
}

#endif
