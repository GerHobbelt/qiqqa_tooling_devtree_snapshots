
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

extern int sqlite_dbhash_main(int argc, const char** argv);
extern int sqlite_dbtotxt_main(int argc, const char** argv);
extern int sqlite_diff_main(int argc, const char** argv);
extern int sqlite_enlargedb_main(int argc, const char** argv);
extern int sqlite_fast_vacuum_main(int argc, const char** argv);
extern int sqlite_getlock_main(int argc, const char** argv);
extern int sqlite_index_usage_main(int argc, const char** argv);
extern int sqlite_kvtest_main(int argc, const char** argv);
extern int sqlite_lemon_main(int argc, const char** argv);
extern int sqlite_libvers_main(int argc, const char** argv);
extern int sqlite_logest_main(int argc, const char** argv);
extern int sqlite_main(int argc, const char** argv);
extern int sqlite_max_limits_main(int argc, const char** argv);
extern int sqlite_offsets_main(int argc, const char** argv);
extern int sqlite_pagesig_main(int argc, const char** argv);
extern int sqlite_showdb_main(int argc, const char** argv);
extern int sqlite_showjournal_main(int argc, const char** argv);
extern int sqlite_showlocks_main(int argc, const char** argv);
extern int sqlite_showshm_main(int argc, const char** argv);
extern int sqlite_showstat4_main(int argc, const char** argv);
extern int sqlite_showwal_main(int argc, const char** argv);
extern int sqlite_speedtest1_main(int argc, const char** argv);
extern int sqlite_speedtest8_main(int argc, const char** argv);
extern int sqlite_test_startup_main(int argc, const char** argv);
extern int sqlite_threadtest1_main(int argc, const char** argv);
extern int sqlite_threadtest2_main(int argc, const char** argv);
extern int sqlite_threadtest3_main(int argc, const char** argv);
extern int sqlite_threadtest4_main(int argc, const char** argv);
extern int sqlite_threadtest5_main(int argc, const char** argv);
extern int sqlite_varint_main(int argc, const char** argv);
extern int sqlite_wordcount_main(int argc, const char** argv);

extern int sqlite_ext_expert_main(int argc, const char** argv);
extern int sqlite_fts3view_main(int argc, const char** argv);
extern int sqlite_lsmtest_main(int argc, const char** argv);
extern int sqlite_rbu_main(int argc, const char** argv);
extern int sqlite_ext_session_changeset_main(int argc, const char** argv);
extern int sqlite_ext_session_speed_test_main(int argc, const char** argv);

#ifdef __cplusplus
}
#endif

#endif
