/*
 * bibprog.c
 *
 * Copyright (c) Chris Putnam 2004-2021
 *
 * Source code released under the GPL version 2
 *
 */
#include <stdio.h>
#include "bibutils.h"
#include "bibprog.h"

int
bibprog( int argc, const char *argv[], param *p )
{
	FILE *fp;
	bibl b;
	errno_t err;
	int i;
	int rv = BIBL_OK;

	bibl_init( &b );
	if ( argc<2 ) {
		err = bibl_read( &b, stdin, "stdin", p );
		if (err) {
			bibl_reporterr(err);
			rv = BIBL_ERR_EXIT_FAILURE;
		}
	} else {
		for ( i=1; i<argc; ++i ) {
			err = fopen_s( &fp, argv[i], "r" );
			if ( fp ) {
				err = bibl_read( &b, fp, argv[i], p );
				if (err) {
					bibl_reporterr(err);
					rv = BIBL_ERR_EXIT_FAILURE;
				}
				fclose( fp );
			}
			else {
				bibl_reporterr(err);
				rv = BIBL_ERR_EXIT_FAILURE;
			}
		} 
	}
	err = bibl_write( &b, stdout, p );
	if (err) {
		bibl_reporterr(err);
		rv = BIBL_ERR_EXIT_FAILURE;
	}
	fflush( stdout );
	if( p->progname ) fprintf( stderr, "%s: ", p->progname );
	fprintf( stderr, "Processed %ld references.\n", b.n );
	bibl_free( &b );
	return rv;
}
