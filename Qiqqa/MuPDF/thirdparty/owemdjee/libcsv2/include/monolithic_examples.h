
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

int csv2_bench_main(int argc, const char** argv);
int csv2_csv_count_main(int argc, const char** argv);
int csv2_fieldcount_main(int argc, const char** argv);

#ifdef __cplusplus
}
#endif

#endif
