/*
 * args.h
 *
 * Copyright (c) Chris Putnam 2012-2021
 *
 * Program and source code released under the GPL version 2
 *
 */
#ifndef ARGS_H
#define ARGS_H

void  args_tellversion( const char *progname );
int   args_match( const char *check, const char *shortarg, const char *longarg );
const char *args_next( int argc, const char *argv[], int n, const char *progname, const char *shortarg, const char *longarg );
void  process_charsets( int *argc, const char *argv[], param *p );

#endif
