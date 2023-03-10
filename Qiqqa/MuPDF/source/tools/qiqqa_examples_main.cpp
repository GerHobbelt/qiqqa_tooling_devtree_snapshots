
#define BUILD_MONOLITHIC 1
#include "qiqqa_monolithic_examples.h"

#define USAGE_NAME   "qiqqa_tools"

#include "monolithic_main_internal_defs.h"

MONOLITHIC_CMD_TABLE_START()

	{ "db_import", {.fa = qiqqa_db_importer_main} },
	{ "db_export", { .fa = qiqqa_db_exporter_main } },
	{ "meta_import", { .fa = qiqqa_meta_importer_main } },
	{ "content_proc", { .fa = qiqqa_content_processor_main } },
	{ "content_import", { .fa = qiqqa_content_importer_main } },
	{ "safe_file_copier", { .fa = qiqqa_safe_file_copier_main } },
    { "cvt_annot_blob", { .fa = qiqqa_convert_legacy_annot_blobs_main } },
    { "cvt_autotags", { .fa = qiqqa_convert_legacy_autotags_main } },
    { "cvt_configfile", { .fa = qiqqa_convert_legacy_configuration_main } },
    { "cvt_expedition", { .fa = qiqqa_convert_legacy_expedition_main } },

MONOLITHIC_CMD_TABLE_END();

#include "monolithic_main_tpl.h"
