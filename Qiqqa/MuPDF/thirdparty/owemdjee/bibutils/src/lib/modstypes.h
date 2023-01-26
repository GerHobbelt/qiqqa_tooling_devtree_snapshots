/*
 * modstypes.h
 *
 * Copyright (c) Chris Putnam 2008-2021
 *
 * Source code released under the GPL version 2
 *
 */
#ifndef MODSTYPES_H
#define MODSTYPES_H

#include "cross_platform_porting.h"
#include "fields.h"

typedef struct convert {
	const char *mods;     /* old */
	const char *internal; /* new */
} convert;

typedef struct convert2 {
	char *mods;     /* old */
	char *internal; /* new */
	int pos;
	int code;
} convert2;


const char *mods_get_id_from_internal( const char *internal_name, convert *data, int ndata );
const char *mods_get_id_from_mods( const char *mods_name, convert *data, int ndata );

int convert2_findallfields( fields *f, convert2 *parts, int nparts, int level );


#endif
