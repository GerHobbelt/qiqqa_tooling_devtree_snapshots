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

#include "../sqlite/ext/lsm1/lsm-test/lsmtest1.c"
#include "../sqlite/ext/lsm1/lsm-test/lsmtest2.c"
//#include "../sqlite/ext/lsm1/lsm-test/lsmtest3.c"
#include "../sqlite/ext/lsm1/lsm-test/lsmtest4.c"
#include "../sqlite/ext/lsm1/lsm-test/lsmtest5.c"
#include "../sqlite/ext/lsm1/lsm-test/lsmtest6.c"
#include "../sqlite/ext/lsm1/lsm-test/lsmtest7.c"
#include "../sqlite/ext/lsm1/lsm-test/lsmtest8.c"
#include "../sqlite/ext/lsm1/lsm-test/lsmtest9.c"
//#include "../sqlite/ext/lsm1/lsm-test/lsmtest_bt.c"
#include "../sqlite/ext/lsm1/lsm-test/lsmtest_datasource.c"
#include "../sqlite/ext/lsm1/lsm-test/lsmtest_func.c"
#include "../sqlite/ext/lsm1/lsm-test/lsmtest_io.c"
#include "../sqlite/ext/lsm1/lsm-test/lsmtest_main.c"
#include "../sqlite/ext/lsm1/lsm-test/lsmtest_mem.c"
#include "../sqlite/ext/lsm1/lsm-test/lsmtest_tdb.c"
//#include "../sqlite/ext/lsm1/lsm-test/lsmtest_tdb3.c"
//#include "../sqlite/ext/lsm1/lsm-test/lsmtest_tdb4.c"
#include "../sqlite/ext/lsm1/lsm-test/lsmtest_util.c"
#include "../sqlite/ext/lsm1/lsm-test/lsmtest_win32.c"

#include "../sqlite/ext/lsm1/lsm_ckpt.c"
#include "../sqlite/ext/lsm1/lsm_file.c"
#include "../sqlite/ext/lsm1/lsm_log.c"
#include "../sqlite/ext/lsm1/lsm_main.c"
#include "../sqlite/ext/lsm1/lsm_mem.c"
#include "../sqlite/ext/lsm1/lsm_mutex.c"
#include "../sqlite/ext/lsm1/lsm_shared.c"
#include "../sqlite/ext/lsm1/lsm_sorted.c"
#include "../sqlite/ext/lsm1/lsm_str.c"
#include "../sqlite/ext/lsm1/lsm_tree.c"
#include "../sqlite/ext/lsm1/lsm_unix.c"
#include "../sqlite/ext/lsm1/lsm_varint.c"
#include "../sqlite/ext/lsm1/lsm_vtab.c"
#include "../sqlite/ext/lsm1/lsm_win32.c"
