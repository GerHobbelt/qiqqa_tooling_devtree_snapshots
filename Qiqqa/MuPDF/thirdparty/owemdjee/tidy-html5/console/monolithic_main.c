
#define BUILD_MONOLITHIC 1
#include "monolithic_examples.h"

#define USAGE_NAME   "gflags"

#include "monolithic_main_internal_defs.h"

MONOLITHIC_CMD_TABLE_START()

	{ "tab2space", { .fa = tidy_tab2space_main } },
	{ "test71", { .f = tidy_test71_main } },
	{ "cli", { .fa = tidy_cli_main } },

MONOLITHIC_CMD_TABLE_END();

#include "monolithic_main_tpl.h"
