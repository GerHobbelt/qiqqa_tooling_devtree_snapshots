/*
 * reftypes_internals.h
 *
 * Copyright (c) Chris Putnam 2003-2019
 *
 * Source code released under the GPL version 2
 *
 */
#ifndef REFTYPES_INTERNALS_H
#define REFTYPES_INTERNALS_H

#include "cross_platform_porting.h"

#define ORIG(a) 		( &(a[0]) )
#define SIZE(a) 		countof(a)
#define REFTYPE(a,b) 	{ a, ORIG(b), SIZE(b) }

#endif
