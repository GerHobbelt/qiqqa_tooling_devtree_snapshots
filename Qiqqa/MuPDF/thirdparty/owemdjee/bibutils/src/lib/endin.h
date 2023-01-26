/*
 * endin.h
 *
 * Copyright (c) Chris Putnam 2003-2019
 *
 * Source code released under the GPL version 2
 *
 */
#ifndef ENDIN_H
#define ENDIN_H

#include "cross_platform_porting.h"
#include "reftypes.h"

extern int endin_typef(fields* endin, const char* filename, int nrefs, param* p);
extern int endin_convertf(fields* endin, fields* info, int reftype, param* p);
extern int endin_cleanf(bibl* bin, param* p);

#endif
