/*
 * doi_test.c
 *
 * Copyright (c) 2016-2021
 *
 * Source code released under the GPL version 2
 *
 */
#include "cross_platform_porting.h"
#include <stdio.h>
#include <stdlib.h>
#include "url.h"
#ifdef BUNDLE_BIBUTILS_TESTS
#include "bibutils_tests.h"
#endif

#include "monolithic_examples.h"


static const char progname[] = "doi_test";

#if defined(BUILD_MONOLITHIC)
#define main     bibutils_doi_test_main
#endif

typedef struct test_t {
	const char *s;
	int expected;
} test_t;

static int
test_is_doi( void )
{
	const test_t tests[] = {
		{ "10.1021/",            0 },
		{ "00.0000/",            0 },
		{ "00,0000/",            -1 },
		{ "doi:99.9999/",        4 },
		{ "doi: 99.9999/",       5 },
		{ "doi: DOI: 99.9999/",  10 },
		{ "http://www.test.com", -1 },
	};
	int ntests = sizeof( tests ) / sizeof( tests[0] );
	int failed = 0;
	int found;
	int i;

	for ( i=0; i<ntests; ++i ) {
		found = is_doi( tests[i].s );
		if ( found != tests[i].expected ) {
			printf( "%s: Error is_doi( '%s' ) returned %d, expected %d\n", progname, tests[i].s, found, tests[i].expected );
			failed++;
		}
	}
	return failed;
}

static int
test_is_uri_remote_scheme( void )
{
	const test_t tests[] = {
		{ "This is a note",           -1 },
		{ "doi:99.9999/",             -1 },
		{ "git://www.git.com",        4 },
		{ "ftp://www.ftp.com",        4 },
		{ "gopher://www.gopher.com",  7 },
		{ "arXiv:10121",              -1 },
		{ "pubmed:121211",            -1 },
		{ "http://www.test.com",      5 },
		{ "https://www.test.com",     6 },
	};
	int ntests = sizeof( tests ) / sizeof( tests[0] );
	int failed = 0;
	int found;
	int i;

	for ( i=0; i<ntests; ++i ) {
		found = is_uri_remote_scheme( tests[i].s );
		if ( found != tests[i].expected ) {
			printf( "%s: Error is_uri_remote_scheme( '%s' ) returned %d, expected %d\n", progname, tests[i].s, found, tests[i].expected );
			failed++;
		}
	}
	return failed;
}

static int
test_is_embedded_link( void )
{
	const test_t tests[] = {
		{ "This is a note",           0 },
		{ "doi:99.9999/",             1 },
		{ "git://www.git.com",        1 },
		{ "ftp://www.ftp.com",        1 },
		{ "gopher://www.gopher.com",  1 },
		{ "arXiv:10121",              1 },
		{ "pubmed:121211",            1 },
		{ "http://www.test.com",      1 },
		{ "https://www.test.com",     1 },
	};
	int ntests = sizeof( tests ) / sizeof( tests[0] );
	int failed = 0;
	int found;
	int i;

	for ( i=0; i<ntests; ++i ) {
		found = is_embedded_link( tests[i].s );
		if ( found != tests[i].expected ) {
			printf( "%s: Error is_embedded_link( '%s' ) returned %d, expected %d\n", progname, tests[i].s, found, tests[i].expected );
			failed++;
		}
	}
	return failed;
}


#ifdef BUNDLE_BIBUTILS_TESTS
int 
doi_test(void)
#else
int
main(void)
#endif
{
	int failed = 0;
	failed += test_is_doi();
	failed += test_is_uri_remote_scheme();
	failed += test_is_embedded_link();
	if ( !failed ) {
		printf( "%s: PASSED\n", progname );
		return EXIT_SUCCESS;
	} else {
		printf( "%s: FAILED\n", progname );
		return EXIT_FAILURE;
	}
}
