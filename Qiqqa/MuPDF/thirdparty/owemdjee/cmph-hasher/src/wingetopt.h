#ifdef __cplusplus
extern "C" {
#endif

#ifndef _WIN32
	#include <getopt.h>
#else
	#ifndef _GETOPT_
	#define _GETOPT_

	#include <stdio.h>                  /* for EOF */ 
	#include <string.h>                 /* for strchr() */ 

#if defined(INSTANTIATE_WINGETOPT_GLOBALS) || !defined(BUILD_MONOLITHIC)
	const char *optarg = NULL;    /* pointer to the start of the option argument  */ 
	int   optind = 1;			  /* number of the next argv[] to be evaluated    */ 
	int   opterr = 1;			  /* non-zero if a question mark should be returned */
#else
	extern const char *optarg;    /* pointer to the start of the option argument  */
	extern int   optind;          /* number of the next argv[] to be evaluated    */
	extern int   opterr;          /* non-zero if a question mark should be returned */
#endif

	int getopt(int argc, const char **argv, const char *opstring); 
	#endif //_GETOPT_
#endif //_WIN32

#ifdef __cplusplus
}
#endif

