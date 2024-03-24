//
// part of Demo 
//

#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

int re2_benchmark_main(int argc, const char** argv);
int re2_basic_test_main(void);
int re2_test_main(void);

#ifdef __cplusplus
}
#endif

#endif
