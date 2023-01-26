/*
** Compile this program against an SQLite library of unknown version
** and then run this program, and it will print out the SQLite version
** information.
*/
#include <stdio.h>

#include "sqlite3.h"
#include "monolithic_examples.h"

#if 0
extern const char *sqlite3_libversion(void);
extern const char *sqlite3_sourceid(void);
#endif


#if defined(BUILD_MONOLITHIC)
#define main(cnt, arr)      sqlite_libvers_main(cnt, arr)
#endif

int main(int argc, const char** argv){
  printf("SQLite version %s\n", sqlite3_libversion());
  printf("SQLite source  %s\n", sqlite3_sourceid());
  return 0;
}
