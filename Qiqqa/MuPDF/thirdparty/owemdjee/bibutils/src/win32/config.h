#ifndef __WIN32_BIBUTILS_CONFIG_H__
#define __WIN32_BIBUTILS_CONFIG_H__

#undef HAVE_UNISTD_H
#define HAVE_PROCESS_H		1
#undef HAVE_DIRENT_H
#define HAVE_IO_H			1
#define HAVE_DIRECT_H		1



#undef HAVE_DESIGNATED_INITIALIZER_GNU_EXTENSION

#define SET_ARRAY_DEFAULT_VALUE(array, default_value)			\
	{															\
		for (int ii = 0; ii < countof(array); ii++) {			\
			if ((array)[ii] == 0) {								\
				(array)[ii] = (default_value);					\
			}													\
		}														\
	}



#if 0
#define _CRT_SECURE_NO_WARNINGS		1
#pragma warning(disable:4996)
#endif

// disable superfluous warnings:

#if defined(_MSC_VER)

// warning C4090: '=': different 'const' qualifiers
// warning C4090: 'function': different 'const' qualifiers
// warning C4090: 'initializing': different 'const' qualifiers
//#pragma warning(disable:4090)

// warning C4464: relative include path contains '..'
#pragma warning(disable:4464)

// warning C4710: 'int fprintf(FILE *const ,const char *const ,...)': function not inlined
// warning C4710: 'int printf(const char *const ,...)': function not inlined
// warning C4710: 'int sprintf_s(char *const ,const size_t,const char *const ,...)': function not inlined
#pragma warning(disable:4710)

// warning C4820: '<unnamed-tag>': '3' bytes padding added after data member 'type'
// warning C4820: '_wdirent': '2' bytes padding added after data member 'd_name'
// warning C4820: '_wdirent': '2' bytes padding added after data member 'd_reclen'
// warning C4820: 'dirent': '2' bytes padding added after data member 'd_reclen'
// warning C4820: 'dirent': '3' bytes padding added after data member 'd_name'
// warning C4820: 'param': '1' bytes padding added after data member 'singlerefperfile'
// warning C4820: 'param': '3' bytes padding added after data member 'nosplittitle'
// warning C4820: 'param': '3' bytes padding added after data member 'xmlout'
#pragma warning(disable:4820)

// warning C5045: Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
#pragma warning(disable:5045)

// warning C4514 : 'mktime' : unreferenced inline function has been removed
#pragma warning(disable:4514)

// warning C4505: 'strncasecmp': unreferenced local function has been removed
#pragma warning(disable:4505)

// warning C4711: function 'bibl_free' selected for automatic inline expansion
#pragma warning(disable:4711)

#endif




#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif

static inline int strcasecmp(const char* s1, const char* s2) {
	return _stricmp(s1, s2);
}
static int strncasecmp(const char* s1, const char* s2, size_t len) {
	return _strnicmp(s1, s2, len);
}

#ifdef __cplusplus
}
#endif

#endif
