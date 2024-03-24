
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

int libbf_bench_main(int argc, const char** argv);
int libbf_test_main(int argc, const char** argv);
int libbf_tinypi_main(int argc, const char** argv);

#ifdef __cplusplus
}
#endif

#endif
