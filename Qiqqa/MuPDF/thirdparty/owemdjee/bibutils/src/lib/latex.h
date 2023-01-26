/*
 * latex.h
 *
 * Copyright (c) Chris Putnam 2004-2021
 *
 * Source code released under the GPL version 2
 *
 */
#ifndef LATEX_H
#define LATEX_H

#include "cross_platform_porting.h"

unsigned int latex2char( const char *s, unsigned int *pos, int *unicode );
void         uni2latex ( unsigned int ch, char buf[], int buf_size );

#endif

