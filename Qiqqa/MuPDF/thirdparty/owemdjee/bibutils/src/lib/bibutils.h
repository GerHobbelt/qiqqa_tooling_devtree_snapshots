/*
 * bibutils.h
 *
 * Copyright (c) Chris Putnam 2005-2021
 *
 * Source code released under GPL version 2
 *
 */
#ifndef BIBUTILS_H
#define BIBUTILS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "cross_platform_porting.h"
#include <stdio.h>
#include "bibdefs.h"
#include "reftypes.h"
#include "bibl.h"
#include "slist.h"
#include "charsets.h"
#include "str_conv.h"

#define BIBL_FIRSTIN      (100)
#define BIBL_MODSIN       (BIBL_FIRSTIN)
#define BIBL_BIBTEXIN     (BIBL_FIRSTIN+1)
#define BIBL_RISIN        (BIBL_FIRSTIN+2)
#define BIBL_ENDNOTEIN    (BIBL_FIRSTIN+3)
#define BIBL_COPACIN      (BIBL_FIRSTIN+4)
#define BIBL_ISIIN        (BIBL_FIRSTIN+5)
#define BIBL_MEDLINEIN    (BIBL_FIRSTIN+6)
#define BIBL_ENDNOTEXMLIN (BIBL_FIRSTIN+7)
#define BIBL_BIBLATEXIN   (BIBL_FIRSTIN+8)
#define BIBL_EBIIN        (BIBL_FIRSTIN+9)
#define BIBL_WORDIN       (BIBL_FIRSTIN+10)
#define BIBL_NBIBIN       (BIBL_FIRSTIN+11)
#define BIBL_LASTIN       (BIBL_FIRSTIN+11)

#define BIBL_FIRSTOUT     (200)
#define BIBL_MODSOUT      (BIBL_FIRSTOUT)
#define BIBL_BIBTEXOUT    (BIBL_FIRSTOUT+1)
#define BIBL_RISOUT       (BIBL_FIRSTOUT+2)
#define BIBL_ENDNOTEOUT   (BIBL_FIRSTOUT+3)
#define BIBL_ISIOUT       (BIBL_FIRSTOUT+4)
#define BIBL_WORD2007OUT  (BIBL_FIRSTOUT+5)
#define BIBL_ADSABSOUT    (BIBL_FIRSTOUT+6)
#define BIBL_NBIBOUT      (BIBL_FIRSTOUT+7)
#define BIBL_BIBLATEXOUT  (BIBL_FIRSTOUT+8)
#define BIBL_LASTOUT      (BIBL_FIRSTOUT+8)

#define BIBL_FORMAT_VERBOSE             (1)
#define BIBL_FORMAT_BIBOUT_FINALCOMMA   (2)
#define BIBL_FORMAT_BIBOUT_SINGLEDASH   (4)
#define BIBL_FORMAT_BIBOUT_WHITESPACE   (8)
#define BIBL_FORMAT_BIBOUT_BRACKETS    (16)
#define BIBL_FORMAT_BIBOUT_UPPERCASE   (32)
#define BIBL_FORMAT_BIBOUT_STRICTKEY   (64)
#define BIBL_FORMAT_BIBOUT_SHORTTITLE (128)
#define BIBL_FORMAT_BIBOUT_DROPKEY    (256)
#define BIBL_FORMAT_MODSOUT_DROPKEY   (512)

#define BIBL_RAW_WITHCHARCONVERT (4)
#define BIBL_RAW_WITHMAKEREFID   (8)

#define BIBL_CHARSET_UNKNOWN      CHARSET_UNKNOWN
#define BIBL_CHARSET_UNICODE      CHARSET_UNICODE
#define BIBL_CHARSET_GB18030      CHARSET_GB18030
#define BIBL_CHARSET_DEFAULT      CHARSET_DEFAULT
#define BIBL_CHARSET_UTF8_DEFAULT CHARSET_UTF8_DEFAULT
#define BIBL_CHARSET_BOM_DEFAULT  CHARSET_BOM_DEFAULT

#define BIBL_SRC_DEFAULT (0)  /* value from program default */
#define BIBL_SRC_FILE    (1)  /* value from file, priority over default */
#define BIBL_SRC_USER    (2)  /* value from user, priority over file, default */

#define BIBL_XMLOUT_FALSE    STR_CONV_XMLOUT_FALSE
#define BIBL_XMLOUT_TRUE     STR_CONV_XMLOUT_TRUE
#define BIBL_XMLOUT_ENTITIES STR_CONV_XMLOUT_ENTITIES

typedef unsigned char uchar;

typedef struct param {
	int readformat;
	int writeformat;

	int charsetin;
	uchar charsetin_src; /*BIBL_SRC_DEFAULT, BIBL_SRC_FILE, BIBL_SRC_USER*/
	uchar latexin;
	uchar utf8in;
	uchar xmlin;
	uchar nosplittitle;

	int charsetout;
	uchar charsetout_src; /* BIBL_SRC_PROG, BIBL_SRC_USER */
	uchar latexout;       /* If true, write Latex codes */
	uchar utf8out;        /* If true, write characters encoded by utf8 */
	uchar utf8bom;        /* If true, write utf8 byte-order-mark */
	uchar xmlout;         /* If true, write characters in XML entities */

	int format_opts; /* options for specific formats */
	int addcount;  /* add reference count to reference id */
	uchar output_raw;
	uchar verbose;
	uchar singlerefperfile;

	slist asis;  /* Names that shouldn't be mangled */
	slist corps; /* Names that shouldn't be mangled-MODS corporation type */

	const char *progname;

	int  (*readf)(FILE* fp, char* buf, int bufsize, int* bufpos, str* line, str* reference, int* fcharset);
	int  (*processf)(fields* bibin, const char* data, const char* filename, long nref, struct param* pm);
	int  (*cleanf)(bibl* bin, struct param* pm);
	int  (*typef)(fields* bibin, const char* filename, int nrefs, struct param* pm);
	int  (*convertf)(fields* bibin, fields* info, int reftype, struct param* pm);
	void (*headerf)(FILE* outptr, struct param* pm);
	void (*footerf)(FILE* outptr);
	int  (*assemblef)(fields* in, fields* out, struct param* pm, unsigned long refnum);
	int  (*writef)(fields* out, FILE* fp, struct param* pm, unsigned long refnum);
	const variants *all;
	int  nall;
} param;

int  bibl_initparams( param *p, int readmode, int writemode, const char *progname );
void bibl_freeparams( param *p );
int  bibl_readasis( param *p, const char *filename );
int  bibl_addtoasis( param *p, const char *entry );
int  bibl_readcorps( param *p, const char *filename );
int  bibl_addtocorps( param *p, const char *entry );
int  bibl_read( bibl *b, FILE *fp, const char *filename, param *p );
int  bibl_write( bibl *b, FILE *fp, param *p );
void bibl_reporterr( int err );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

