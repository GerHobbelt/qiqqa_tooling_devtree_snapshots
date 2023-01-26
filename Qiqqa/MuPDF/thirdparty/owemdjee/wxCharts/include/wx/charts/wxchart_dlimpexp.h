/*
    Copyright (c) 2022 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

/// @file

#ifndef _WX_CHARTS_DLIMPEXP_H_
#define _WX_CHARTS_DLIMPEXP_H_

#include <wx/platform.h>

#if defined(WXCHARTS_STATICLIB)
#    define WXCHARTS_EXPORT
#    define WXCHARTS_IMPORT
#elif defined(HAVE_VISIBILITY)
#    define WXCHARTS_EXPORT __attribute__ ((visibility("default")))
#    define WXCHARTS_IMPORT __attribute__ ((visibility("default")))
#elif defined(__WINDOWS__)
    /*
       __declspec works in as VC++.
     */
#    if defined(__VISUALC__)
#        define WXCHARTS_EXPORT __declspec(dllexport)
#        define WXCHARTS_IMPORT __declspec(dllimport)
    /*
        While gcc also supports __declspec(dllexport), it created unusably huge
        DLL files in gcc 4.[56] (while taking horribly long amounts of time),
        see http://gcc.gnu.org/bugzilla/show_bug.cgi?id=43601. Because of this
        we rely on binutils auto export/import support which seems to work
        quite well for 4.5+. However the problem was fixed in 4.7 and later and
        not exporting everything creates smaller DLLs (~8% size difference), so
        do use the explicit attributes again for the newer versions.
     */
#    elif defined(__GNUC__) && \
        (!wxCHECK_GCC_VERSION(4, 5) || wxCHECK_GCC_VERSION(4, 7))
        /*
            __declspec could be used here too but let's use the native
            __attribute__ instead for clarity.
        */
#       define WXCHARTS_EXPORT __attribute__((dllexport))
#       define WXCHARTS_IMPORT __attribute__((dllimport))
#    endif
#elif defined(__CYGWIN__)
#    define WXCHARTS_EXPORT __declspec(dllexport)
#    define WXCHARTS_IMPORT __declspec(dllimport)
#endif

/* for other platforms/compilers we don't anything */
#ifndef WXCHARTS_EXPORT
#    define WXCHARTS_EXPORT
#    define WXCHARTS_IMPORT
#endif

/*
   WXCHARTS_DLLIMPEXP maps to export declaration when building the DLL, to import
   declaration if using it or to nothing at all if we don't use wxCharts as DLL
 */
#ifdef WXCHARTS_MAKINGDLL
#    define WXCHARTS_DLLIMPEXP WXCHARTS_EXPORT
#    define WXCHARTS_DLLIMPEXP_DATA(type) WXCHARTS_EXPORT type
#    if defined(HAVE_VISIBILITY)
#        define WXCHARTS_DLLIMPEXP_INLINE WXCHARTS_EXPORT
#    else
#        define WXCHARTS_DLLIMPEXP_INLINE
#    endif
#elif defined(WXCHARTS_USINGDLL)
#    define WXCHARTS_DLLIMPEXP WXCHARTS_IMPORT
#    define WXCHARTS_DLLIMPEXP_DATA(type) WXCHARTS_IMPORT type
#    if defined(HAVE_VISIBILITY)
#        define WXCHARTS_DLLIMPEXP_INLINE WXCHARTS_IMPORT
#    else
#        define WXCHARTS_DLLIMPEXP_INLINE
#    endif
#else /* not making nor using DLL */
#    define WXCHARTS_DLLIMPEXP
#    define WXCHARTS_DLLIMPEXP_DATA(type) type
#    define WXCHARTS_DLLIMPEXP_INLINE
#endif

/*
   GCC warns about using __attribute__ (and also __declspec in mingw32 case) on
   forward declarations while MSVC complains about forward declarations without
   __declspec for the classes later declared with it, so we need a separate set
   of macros for forward declarations to hide this difference:
 */
#if defined(HAVE_VISIBILITY) || (defined(__WINDOWS__) && defined(__GNUC__))
    #define WXCHARTS_DLLIMPEXP_FWD
#else
    #define WXCHARTS_DLLIMPEXP_FWD      WXCHARTS_DLLIMPEXP
#endif

#endif /* _WX_DLIMPEXP_H_ */
