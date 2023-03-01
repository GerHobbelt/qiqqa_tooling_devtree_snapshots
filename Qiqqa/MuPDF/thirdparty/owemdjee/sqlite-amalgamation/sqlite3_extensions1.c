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


//--#include "../sqlite/ext/fts3/fts3.c"
//--#include "../sqlite/ext/fts3/fts3_aux.c"
//--#include "../sqlite/ext/fts3/fts3_expr.c"
//--#include "../sqlite/ext/fts3/fts3_hash.c"
#include "../sqlite/ext/fts3/fts3_icu.c"
//--#include "../sqlite/ext/fts3/fts3_porter.c"
//--#include "../sqlite/ext/fts3/fts3_snippet.c"
#include "../sqlite/ext/fts3/fts3_term.c"
//#include "../sqlite/ext/fts3/fts3_test.c"
//--#include "../sqlite/ext/fts3/fts3_tokenizer.c"
//--#include "../sqlite/ext/fts3/fts3_tokenizer1.c"
//--#include "../sqlite/ext/fts3/fts3_tokenize_vtab.c"
//--#include "../sqlite/ext/fts3/fts3_unicode.c"
//--#include "../sqlite/ext/fts3/fts3_unicode2.c"
//--#include "../sqlite/ext/fts3/fts3_write.c"
#include "../sqlite/ext/fts3/tool/fts3view.c"
