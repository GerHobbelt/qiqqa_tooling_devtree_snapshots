
#define BUILD_MONOLITHIC 1
#include "monolithic_examples.h"

#define USAGE_NAME   "re2"

#include "monolithic_main_internal_defs.h"

MONOLITHIC_CMD_TABLE_START()

	{ "benchmark", {.fa = re2_benchmark_main } },
	{ "basic_test", { .f = re2_basic_test_main } },
	{ "test", { .f = re2_test_main } },

MONOLITHIC_CMD_TABLE_END();

#include "monolithic_main_tpl.h"
