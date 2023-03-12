/* jpeginfo.h
 *
 * Copyright (c) Timo Kokkonen, 1997.
 */

#include <stdio.h>

#define MIN(a,b) (a < b ? a : b)


/* misc.c */

int  is_dir(FILE *fp);
long long filesize(FILE *fp);
void delete_file(const char *name, int verbose_mode, int quiet_mode);
char *fgetstr(char *s,int n,FILE *stream);
char *digest2str(unsigned char *digest, char *s, unsigned int len);


/* eof :-) */
