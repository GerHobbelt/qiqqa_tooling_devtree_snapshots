/*
 * end2xml.c
 *
 * Copyright (c) Chris Putnam 2003-2021
 *
 * Program and source code released under the GPL version 2
 *
 */
#include "cross_platform_porting.h"
#include <stdio.h>
#include <stdlib.h>
#include "bibutils.h"
#include "bibformats.h"
#include "tomods.h"
#include "bibprog.h"

#include "monolithic_examples.h"

static const char help1[] = "Converts an Endnote reference file (refer format) "
		"into MODS XML\n\n";
static const char help2[] = "endnote_file";

static const char progname[] = "end2xml";

#if defined(BUILD_MONOLITHIC)
#define main     bibutils_end2xml_main
#endif

int main(int argc, const char** argv)
{
	param p;
	endin_initparams( &p, progname );
	modsout_initparams( &p, progname );
	int rc = tomods_processargs(&argc, argv, &p, help1, help2);
	if (rc == BIBL_OK)
		rc = bibprog(argc, argv, &p);
	bibl_freeparams(&p);
	return (rc == BIBL_OK ? EXIT_SUCCESS : EXIT_FAILURE);
}
 
