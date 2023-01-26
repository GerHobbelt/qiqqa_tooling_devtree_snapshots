/* misc.c - misc routines for jpeginfo
 * $Id$
 *
 * Copyright (c) Timo Kokkonen, 1997.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(HAVE_UNISTD_H)
#include <unistd.h>
#endif
#include "jpeginfo.h"


int is_dir(FILE *fp)
{
 struct stat buf;
 
 if (!fp) return 0;
 if (fstat(_fileno(fp),&buf)) return 0;
 if (S_ISDIR(buf.st_mode)) return 1;
 return 0;
}


long filesize(FILE *fp) 
{
  struct stat buf;

  if (!fp) return -1;
  if (fstat(_fileno(fp),&buf)) return -1;
  return buf.st_size;
}


void delete_file(const char *name, int verbose_mode, int quiet_mode)
{
  if (!name) return;
  if (verbose_mode && !quiet_mode) fprintf(stderr,"deleting: %s\n",name);
  if (_unlink(name) && !quiet_mode) 
    fprintf(stderr,"Error unlinking file: %s\n",name);
}


char *fgetstr(char *s,int n,FILE *stream) 
{
  char *p;
  
  if (!stream || !s || n < 1) return NULL;
  if (!fgets(s,n,stream)) return NULL;
  p=&s[strlen(s)-1];
  while ((p>=s)&&((*p==10)||(*p==13))) *p--=0;
  return s;
}



char *md2str(unsigned char *digest, char *s)
{
  int i;
  char buf[16],*r;

  if (!digest) return NULL;
  if (!s) {
    s=(char*)malloc(33);
    if (!s) return NULL;
  }

  r=s;
  for (i = 0; i < 16; i++) {
    sprintf (buf,"%02x", digest[i]);
    *(s++)=buf[0];
    *(s++)=buf[1];
  }
  *s=0;

  return r;
}

/* eof :-) */






