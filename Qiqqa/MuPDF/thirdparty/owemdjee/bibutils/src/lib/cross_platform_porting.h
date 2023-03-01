/*
 * cross_platform_porting.h
 *
 * Copyright (c) Chris Putnam 2003-2019
 *
 * Source code released under the GPL version 2
 *
 */
#ifndef CROSS_PLATFORM_PORTING_H
#define CROSS_PLATFORM_PORTING_H

#if defined(WIN32) || defined(WIN64)
#if defined(_MSC_VER)
// warning C4464: relative include path contains '..'
#pragma warning(disable:4464)
#ifndef _CRT_NONSTDC_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#endif
#endif
#include "../win32/config.h"
#endif

#define CURR_VERSION	"7.20"
#define CURR_DATE		"2021-11-12"

#define countof(array)					( sizeof(array) / sizeof(array[0]) )


#endif
