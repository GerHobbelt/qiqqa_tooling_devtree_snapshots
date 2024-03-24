//
// part of libxslt
//

#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

int xslt_icu_sort_sample_main(void);
int xslt_runtest_main(int argc, const char** argv);
int xslt_test_threads_main(void);
int xsltproc_main(int argc, const char** argv);

#ifdef __cplusplus
}
#endif

#endif
