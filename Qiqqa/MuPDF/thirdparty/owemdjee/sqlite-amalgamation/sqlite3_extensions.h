#ifndef SQLITE3_EXTENSIONS_H
#define SQLITE3_EXTENSIONS_H

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

#endif
