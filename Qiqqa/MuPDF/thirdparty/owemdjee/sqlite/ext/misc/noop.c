/*
** 2020-01-08
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
******************************************************************************
**
** This SQLite extension implements a noop() function used for testing.
**
** Variants:
**
**    noop(X)           The default.  Deterministic.
**    noop_i(X)         Deterministic and innocuous.
**    noop_do(X)        Deterministic and direct-only.
**    noop_nd(X)        Non-deterministic.
*/

#include "sqlite3_config.h"

#include "sqlite3ext.h"

#if !defined(BUILD_MONOLITHIC)
SQLITE_EXTENSION_INIT1
#else
SQLITE_EXTENSION_INIT3
#endif

#include <assert.h>
#include <string.h>

/*
** Implementation of the noop() function.
**
** The function returns its argument, unchanged.
*/
static void noopfunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  assert( argc==1 );
  sqlite3_result_value(context, argv[0]);
}

SQLITE_EXTENSION_EXPORT int sqlite3_noop_init(
  sqlite3 *db, 
  char **pzErrMsg, 
  const sqlite3_api_routines *pApi
){
  int rc = SQLITE_OK;
  SQLITE_EXTENSION_INIT2(pApi);
  (void)pzErrMsg;  /* Unused parameter */
  rc = sqlite3_create_function(db, "noop", 1,
                     SQLITE_UTF8 | SQLITE_DETERMINISTIC,
                     0, noopfunc, 0, 0);
  if( rc ) return rc;
  rc = sqlite3_create_function(db, "noop_i", 1,
                     SQLITE_UTF8 | SQLITE_DETERMINISTIC | SQLITE_INNOCUOUS,
                     0, noopfunc, 0, 0);
  if( rc ) return rc;
  rc = sqlite3_create_function(db, "noop_do", 1,
                     SQLITE_UTF8 | SQLITE_DETERMINISTIC | SQLITE_DIRECTONLY,
                     0, noopfunc, 0, 0);
  if( rc ) return rc;
  rc = sqlite3_create_function(db, "noop_nd", 1,
                     SQLITE_UTF8,
                     0, noopfunc, 0, 0);
  return rc;
}
