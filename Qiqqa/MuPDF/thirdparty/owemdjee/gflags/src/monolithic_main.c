
#define BUILD_MONOLITHIC 1
#include "monolithic_examples.h"

#define USAGE_NAME   "gflags"

#include "monolithic_main_internal_defs.h"

MONOLITHIC_CMD_TABLE_START()

	{ "bazel_expand_template", {.fa = gflags_bazel_expand_template_main } },
	{ "test_config", { .fa = gflags_test_config_main } },
	{ "test_declare", { .fa = gflags_test_declare_main } },
	{ "test_strip_flags", { .fa = gflags_test_strip_flags_main } },
	{ "unittests", { .fa = gflags_test_unittests_main } },
	{ "test_nc", { .fa = gflags_test_nc_main } },

MONOLITHIC_CMD_TABLE_END();

#include "monolithic_main_tpl.h"
