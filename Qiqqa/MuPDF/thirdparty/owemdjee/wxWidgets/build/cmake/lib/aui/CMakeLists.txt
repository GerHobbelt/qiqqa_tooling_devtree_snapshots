#############################################################################
# Name:        build/cmake/lib/aui/CMakeLists.txt
# Purpose:     CMake file for aui library
# Author:      Tobias Taschner
# Created:     2016-10-04
# Copyright:   (c) 2016 wxWidgets development team
# Licence:     wxWindows licence
#############################################################################

wx_append_sources(AUI_FILES AUI_CMN)

if(WXMSW)
    wx_append_sources(AUI_FILES AUI_MSW)
elseif(WXUWP)
    wx_append_sources(AUI_FILES AUI_UWP)
elseif(WXGTK2)
    wx_append_sources(AUI_FILES AUI_GTK)
endif()
wx_add_library(wxaui ${AUI_FILES})
