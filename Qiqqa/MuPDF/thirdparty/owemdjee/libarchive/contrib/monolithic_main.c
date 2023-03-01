
#define BUILD_MONOLITHIC 1
#include "monolithic_examples.h"

#define USAGE_NAME   "libarchive"

#include "monolithic_main_internal_defs.h"

MONOLITHIC_CMD_TABLE_START()

	{ "bsdcat", { .fa = arch_bsdcat_main } },
	{ "test", { .fa = arch_test_main } },
#if 0   // TODO: properly port the shar example (when we feel the need) to Win32/64 and then remove this condition right here...
	{ "shar", { .fa = arch_shar_main } },
#endif
	{ "untar_contrib", { .fa = arch_untar_contrib_main } },
	{ "cpio", { .fa = arch_cpio_main } },
	{ "untar", { .fa = arch_untar_main } },
	{ "minitar", { .fa = arch_minitar_main } },
	{ "tarfilter", { .fa = arch_tarfilter_main } },
	{ "bsdtar", { .fa = arch_bsdtar_main } },
//	{ "test_util", { .fa = arch_test_util_main } },

MONOLITHIC_CMD_TABLE_END();

// load the monolithic core dispatcher
#include "monolithic_main_tpl.h"
