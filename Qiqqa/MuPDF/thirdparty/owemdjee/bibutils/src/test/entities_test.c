/*
 * entities_test.c
 *
 * Copyright (c) 2012-2021
 *
 * Source code released under the GPL version 2
 */
#include "cross_platform_porting.h"
#include <stdio.h>
#include <stdlib.h>
#include "entities.h"
#ifdef BUNDLE_BIBUTILS_TESTS
#include "bibutils_tests.h"
#endif

#include "monolithic_examples.h"


static const char progname[] = "entities_test";

#if defined(BUILD_MONOLITHIC)
#define main     bibutils_entities_test_main
#endif

static const char version[] = "0.1";

static int
test_decimal_entities1( void )
{
	unsigned int i, answer, pos_in;
	int failed = 0, err, unicode = 0;
	char buf[512];
	for ( i=0; i<10000; ++i ) {
		pos_in = 0;
		err = 0;
		sprintf_s( buf, countof(buf), "&#%u;*", i );
		answer = decode_entity( buf, &pos_in, &unicode, &err );
		if ( err ) {
			failed = 1;
			printf("%s: Error test_decimal_entities received "
				"error, sent '%s' returned %u\n", 
				progname, buf, answer );
		}
		if ( answer!=i ) {
			failed = 1;
			printf("%s: Error test_decimal_entities mismatch, "
				"sent '%s' returned %u\n", 
				progname, buf, answer );
		}
		if ( buf[pos_in]!='*' ) {
			failed = 1;
			printf("%s: Error test_decimal_entities bad ending pos,"
				"sent '%s' returned pointer to '%s'\n",
				progname, buf, &(buf[pos_in]) );
		}
	}
	return failed;
}

static int
test_decimal_entities2( void )
{
	unsigned int i, answer, pos_in;
	int failed = 0, err, unicode = 0;
	char buf[512];
	for ( i=0; i<10000; ++i ) {
		pos_in = 1;
		err = 0;
		sprintf_s( buf, countof(buf), "&#%u;*", i );
		answer = decode_entity( buf, &pos_in, &unicode, &err );
		if ( !err ) {
			failed = 1;
			printf("%s: Error test_decimal_entities should have "
				"received error, sent '%s' returned %u\n", 
				progname, &(buf[1]), answer );
		}
	}
	for ( i=0; i<1000; ++i ) {
		pos_in = 0;
		err = 0;
		sprintf_s( buf, countof(buf), "&#%u ;", i );
		answer = decode_entity( buf, &pos_in, &unicode, &err );
		if ( !err ) {
			failed = 1;
			printf("%s: Error test_decimal_entities should have "
				"received error, sent '%s' returned %u\n", 
				progname, buf, answer );
		}
	}
	return failed;
}

static int
test_hex_entities( void )
{
	unsigned int i, answer, pos_in;
	int failed = 0, err, unicode = 0;
	char buf[512];
	for ( i=0; i<10000; ++i ) {
		pos_in = 0;
		err = 0;
		sprintf_s( buf, countof(buf), "&#x%x;*", i );
		answer = decode_entity( buf, &pos_in, &unicode, &err );
		if ( err ) {
			failed = 1;
			printf("%s: Error test_hex_entities received error, "
				"sent '%s' = %u returned %u\n", 
				progname, buf, i, answer );
		}
		if ( answer!=i ) {
			failed = 1;
			printf("%s: Error test_hex_entities mismatch, "
				"sent '%s' = %u returned %u\n", 
				progname, buf, i, answer );
		}
		if ( buf[pos_in]!='*' ) {
			failed = 1;
			printf("%s: Error test_decimal_entities bad ending pos,"
				"sent '%s' returned pointer to '%s'\n",
				progname, buf, &(buf[pos_in]) );
		}
	}
	return failed;
}

#ifdef BUNDLE_BIBUTILS_TESTS
int
entities_test(void)
#else
int
main(void)
#endif
{
	int failed = 0;
	failed += test_decimal_entities1();
	failed += test_decimal_entities2();
	failed += test_hex_entities();
	if ( !failed ) {
		printf( "%s: PASSED\n", progname );
		return EXIT_SUCCESS;
	} else {
		printf( "%s: FAILED\n", progname );
		return EXIT_FAILURE;
	}
}

#if defined(BUNDLE_BIBUTILS_TESTS) && defined(BUILD_MONOLITHIC)
int
main(void)
{
	return entities_test();
}
#endif


