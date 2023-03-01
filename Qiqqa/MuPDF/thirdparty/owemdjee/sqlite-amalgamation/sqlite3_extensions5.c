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

#include "sqlite3_extensions.h"

/*
* Note:
*
* #include's marked with `//--` have been reviewed as already included in the amalgamated sqlite sourcecode.
*/

#include "../sqlite/ext/async/sqlite3async.c"

#ifdef SQLITE_ENABLE_ICU
#include "../sqlite/ext/icu/icu.c"
#endif

#include "../sqlite/ext/misc/amatch.c"
#include "../sqlite/ext/misc/anycollseq.c"
//--#include "../sqlite/ext/misc/appendvfs.c"
#include "../sqlite/ext/misc/bgckpt.c"
#include "../sqlite/ext/misc/blobio.c"
#include "../sqlite/ext/misc/btreeinfo.c"
#include "../sqlite/ext/misc/carray.c"
//#include "../sqlite/ext/misc/cksumvfs.c"
#include "../sqlite/ext/misc/closure.c"
//--#include "../sqlite/ext/misc/completion.c"
#include "../sqlite/ext/misc/compress.c"
#include "../sqlite/ext/misc/csv.c"
//#include "../sqlite/ext/misc/dbdata.c"
#include "../sqlite/ext/misc/dbdump.c"
//--#include "../sqlite/ext/misc/decimal.c"
#include "../sqlite/ext/misc/eval.c"
#include "../sqlite/ext/misc/explain.c"
//--#include "../sqlite/ext/misc/fileio.c"
#include "../sqlite/ext/misc/fossildelta.c"
//--#include "../sqlite/ext/misc/ieee754.c"
#include "../sqlite/ext/misc/memstat.c"
//--#include "../sqlite/ext/misc/memtrace.c"
#include "../sqlite/ext/misc/memvfs.c"
#include "../sqlite/ext/misc/mmapwarm.c"
#include "../sqlite/ext/misc/nextchar.c"
#include "../sqlite/ext/misc/noop.c"
#include "../sqlite/ext/misc/normalize.c"
#include "../sqlite/ext/misc/percentile.c"
#include "../sqlite/ext/misc/prefixes.c"
#include "../sqlite/ext/misc/qpvtab.c"
//--#include "../sqlite/ext/misc/regexp.c"
#include "../sqlite/ext/misc/remember.c"
#include "../sqlite/ext/misc/rot13.c"
#include "../sqlite/ext/misc/scrub.c"
//--#include "../sqlite/ext/misc/series.c"
//#include "../sqlite/ext/misc/sha1.c"
//#include "../sqlite/ext/misc/shathree.c"
#include "../sqlite/ext/misc/showauth.c"
#include "../sqlite/ext/misc/spellfix.c"
//--#include "../sqlite/ext/misc/sqlar.c"
#include "../sqlite/ext/misc/stmt.c"
#include "../sqlite/ext/misc/templatevtab.c"
#include "../sqlite/ext/misc/totype.c"
//--#include "../sqlite/ext/misc/uint.c"
#include "../sqlite/ext/misc/unionvtab.c"
#include "../sqlite/ext/misc/urifuncs.c"
#include "../sqlite/ext/misc/uuid.c"
#include "../sqlite/ext/misc/vfslog.c"
#include "../sqlite/ext/misc/vfsstat.c"
#include "../sqlite/ext/misc/vtablog.c"
#include "../sqlite/ext/misc/vtshim.c"
#include "../sqlite/ext/misc/wholenumber.c"
//--#include "../sqlite/ext/misc/zipfile.c"
#include "../sqlite/ext/misc/zorder.c"

//#include "../sqlite/ext/rbu/rbu.c"
//--#include "../sqlite/ext/rbu/sqlite3rbu.c"
#include "../sqlite/ext/rbu/test_rbu.c"

#include "../sqlite/ext/repair/checkfreelist.c"
#include "../sqlite/ext/repair/checkindex.c"

//#include "../sqlite/ext/rtree/geopoly.c"
//#include "../sqlite/ext/rtree/rtree.c"
//#include "../sqlite/ext/rtree/test_rtreedoc.c"
// 
//#include "../sqlite/ext/session/changeset.c"
//#include "../sqlite/ext/session/changesetfuzz.c"
//#include "../sqlite/ext/session/session_speed_test.c"
#include "../sqlite/ext/session/sqlite3changebatch.c"
//--#include "../sqlite/ext/session/sqlite3session.c"
#include "../sqlite/ext/session/test_session.c"

#include "../sqlite/ext/userauth/userauth.c"
