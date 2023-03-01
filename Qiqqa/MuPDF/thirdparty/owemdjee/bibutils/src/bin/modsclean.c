/*
 * modsclean.c
 *
 * Copyright (c) Chris Putnam 2004-2021
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

static const char progname[] = "modsclean";

#if defined(BUILD_MONOLITHIC)
#define main     bibutils_modsclean_main
#endif

int main(int argc, const char** argv)
{
	param p;
	modsin_initparams( &p, progname );
	modsout_initparams( &p, progname );
	int rc = tomods_processargs(&argc, argv, &p, "", "");
	if (rc == BIBL_OK)
		rc = bibprog(argc, argv, &p);
	bibl_freeparams(&p);
	return (rc == BIBL_OK ? EXIT_SUCCESS : EXIT_FAILURE);
}
