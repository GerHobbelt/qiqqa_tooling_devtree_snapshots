
#if defined(PCRE2_CODE_UNIT_WIDTH)

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define PCRE2_AMALGAMETE 1

/* PCRE2 headers */
#include "pcre2.h"
#include "pcre2posix.h"
#include "../src/pcre2_internal.h"

#include "../src/pcre2_auto_possess.c"
#include "../src/pcre2_chartables.c"
//#include "../src/pcre2_chkdint.c"
#include "../src/pcre2_compile.c"
#include "../src/pcre2_config.c"
#include "../src/pcre2_context.c"
#include "../src/pcre2_convert.c"
#include "../src/pcre2_dfa_match.c"
#include "../src/pcre2_error.c"
#include "../src/pcre2_extuni.c"
#include "../src/pcre2_find_bracket.c"
#include "../src/pcre2_match.c"
#include "../src/pcre2_match_data.c"
#include "../src/pcre2_newline.c"
#include "../src/pcre2_ord2utf.c"
#include "../src/pcre2_pattern_info.c"
#include "../src/pcre2_printint.c"
#include "../src/pcre2_script_run.c"
#include "../src/pcre2_serialize.c"
#include "../src/pcre2_string_utils.c"
#include "../src/pcre2_study.c"
#include "../src/pcre2_substitute.c"
#include "../src/pcre2_substring.c"
#include "../src/pcre2_ucd.c"
#include "../src/pcre2_valid_utf.c"
#include "../src/pcre2_xclass.c"

//#include "../src/pcre2_ucptables.c"
#include "../src/pcre2_tables.c"

#include "../src/pcre2_maketables.c"

#else

#include "../src/pcre2_chkdint.c"

//#include "../src/pcre2posix.c"

#include "../src/pcre2_jit_compile.c"
//#include "../src/pcre2_jit_match.c"
//#include "../src/pcre2_jit_misc.c"

#if defined(BUILD_MONOLITHIC)

//#include "../src/pcre2_dftables.c"
//#include "../src/pcre2_fuzzsupport.c"
#include "../src/pcre2_jit_test.c"

#endif

#endif
