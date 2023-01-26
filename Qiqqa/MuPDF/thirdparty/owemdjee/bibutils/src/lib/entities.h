/*
 * entities.h
 *
 * Copyright (c) Chris Putnam 2003-2021
 *
 * Source code released under the GPL version 2
 *
 */
#ifndef ENTITIES_H
#define ENTITIES_H

#include "cross_platform_porting.h"

unsigned int decode_entity( const char *s, unsigned int *pi, int *unicode, int *err );

#endif

