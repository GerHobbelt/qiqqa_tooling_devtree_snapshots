/******************************************************************************
** This file is an amalgamation of many separate C source files from SQLite
** version 3.37.0.  By combining all the individual C code files into this
** single large file, the entire code can be compiled as a single translation
** unit.  This allows many compilers to do optimizations that would not be
** possible if the files were compiled separately.  Performance improvements
** of 5% or more are commonly seen when SQLite is compiled as a single
** translation unit.
**
** This file is all you need to compile SQLite.  To use SQLite in other
** programs, you need this file and the "sqlite3.h" header file that defines
** the programming interface to the SQLite library.  (If you do not have
** the "sqlite3.h" header file at hand, you will find a copy embedded within
** the text of this file.  Search for "Begin file sqlite3.h" to find the start
** of the embedded sqlite3.h header file.) Additional code files may be needed
** if you want a wrapper to interface SQLite with your choice of programming
** language. The code for the "sqlite3" command-line shell is also in a
** separate file. This file contains only code for the core SQLite library.
*/

/*
** Include the configuration header output by 'configure' if we're using the
** autoconf-based build
*/
#include "sqlite3_config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>

#undef SQLITE_CORE 
#define SQLITE_OMIT_LOAD_EXTENSION
#undef SQLITE_AMALGAMATION 
#ifndef SQLITE_PRIVATE
# define SQLITE_PRIVATE static
#endif

#undef SQLITE_ENABLE_BROKEN_FTS1
#undef SQLITE_ENABLE_BROKEN_FTS2
#define SQLITE_ENABLE_FTS3
#define SQLITE_ENABLE_FTS4
#define SQLITE_ENABLE_FTS5

#include "sqlite3.h"
#include "sqliteInt.h"

/*
** The following macros are used to suppress compiler warnings and to
** make it clear to human readers when a function parameter is deliberately
** left unused within the body of a function. This usually happens when
** a function is called via a function pointer. For example the
** implementation of an SQL aggregate step callback may not use the
** parameter indicating the number of arguments passed to the aggregate,
** if it knows that this is enforced elsewhere.
**
** When a function parameter is not used at all within the body of a function,
** it is generally named "NotUsed" or "NotUsed2" to make things even clearer.
** However, these macros may also be used to suppress warnings related to
** parameters that may or may not be used depending on compilation options.
** For example those parameters only used in assert() statements. In these
** cases the parameters are named as per the usual conventions.
*/
#define UNUSED_PARAMETER(x) (void)(x)

#if defined(SQLITE_COVERAGE_TEST) || defined(SQLITE_MUTATION_TEST)
# define SQLITE_OMIT_AUXILIARY_SAFETY_CHECKS 1
#endif
#if defined(SQLITE_OMIT_AUXILIARY_SAFETY_CHECKS)
# define ALWAYS(X)      (1)
# define NEVER(X)       (0)
#elif !defined(NDEBUG)
# define ALWAYS(X)      ((X)?1:(assert(0),0))
# define NEVER(X)       ((X)?(assert(0),1):0)
#else
# define ALWAYS(X)      (X)
# define NEVER(X)       (X)
#endif

/*
* Note:
*
* #include's marked with `//--` have been reviewed as already included in the amalgamated sqlite sourcecode.
*/

#include "../sqlite/ext/lsm1/lsm-test/lsmtest3.c"
#include "../sqlite/ext/lsm1/lsm-test/lsmtest_tdb3.c"
//#include "../sqlite/ext/lsm1/lsm-test/lsmtest_tdb4.c"
