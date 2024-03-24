
#define PCRE2_CODE_UNIT_WIDTH 32
#define PCRE2_AMALGAMETE 1


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif


#define SUPPORT_PCRE2_32 1
#undef SUPPORT_PCRE2_8
#undef SUPPORT_PCRE2_16
//#undef SUPPORT_PCRE2_32
#include "../src/pcre2test.c"
