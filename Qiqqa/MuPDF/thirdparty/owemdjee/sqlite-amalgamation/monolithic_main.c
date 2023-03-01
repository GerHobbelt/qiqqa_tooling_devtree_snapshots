
#define BUILD_MONOLITHIC 1
#include "monolithic_examples.h"

#define USAGE_NAME   "sqlite_tools"

#include "monolithic_main_internal_defs.h"

MONOLITHIC_CMD_TABLE_START()

{ "dbhash", { .fa = sqlite_dbhash_main } },
{ "dbtotxt", { .fa = sqlite_dbtotxt_main } },
{ "diff", { .fa = sqlite_diff_main } },
{ "enlargedb", { .fa = sqlite_enlargedb_main } },
{ "expert", {.fa = sqlite_ext_expert_main } },
{ "fts3view", {.fa = sqlite_fts3view_main } },
{ "lsmtest", {.fa = sqlite_lsmtest_main } },
{ "rbu", {.fa = sqlite_rbu_main } },
{ "session_changeset", {.fa = sqlite_ext_session_changeset_main } },
{ "session_speed_test", {.fa = sqlite_ext_session_speed_test_main } },
{ "fast_vacuum", { .fa = sqlite_fast_vacuum_main } },
{ "getlock", { .fa = sqlite_getlock_main } },
{ "index_usage", { .fa = sqlite_index_usage_main } },
{ "kvtest", { .fa = sqlite_kvtest_main } },
{ "lemon", {.fa = sqlite_lemon_main } },
{ "libvers", { .fa = sqlite_libvers_main } },
{ "logest", { .fa = sqlite_logest_main } },
{ "sqlite", { .fa = sqlite_main } },
{ "max_limits", { .fa = sqlite_max_limits_main } },
{ "offsets", { .fa = sqlite_offsets_main } },
{ "pagesig", { .fa = sqlite_pagesig_main } },
{ "showdb", { .fa = sqlite_showdb_main } },
{ "showjournal", { .fa = sqlite_showjournal_main } },
{ "showlocks", { .fa = sqlite_showlocks_main } },
{ "showshm", { .fa = sqlite_showshm_main } },
{ "showstat4", { .fa = sqlite_showstat4_main } },
{ "showwal", { .fa = sqlite_showwal_main } },
{ "speedtest1", { .fa = sqlite_speedtest1_main } },
{ "speedtest8", { .fa = sqlite_speedtest8_main } },
{ "test_startup", { .fa = sqlite_test_startup_main } },
{ "threadtest1", { .fa = sqlite_threadtest1_main } },
{ "threadtest2", { .fa = sqlite_threadtest2_main } },
{ "threadtest3", { .fa = sqlite_threadtest3_main } },
{ "threadtest4", { .fa = sqlite_threadtest4_main } },
{ "threadtest5", { .fa = sqlite_threadtest5_main } },
{ "varint", { .fa = sqlite_varint_main } },
{ "wordcount", { .fa = sqlite_wordcount_main } },

MONOLITHIC_CMD_TABLE_END();

#include "monolithic_main_tpl.h"
