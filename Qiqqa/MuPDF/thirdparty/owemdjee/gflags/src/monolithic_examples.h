
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

int gflags_bazel_expand_template_main(int argc, const char** argv);
int gflags_test_config_main(int argc, const char** argv);
int gflags_test_declare_main(int argc, const char** argv);
int gflags_test_strip_flags_main(int argc, const char** argv);
int gflags_test_unittests_main(int argc, const char** argv);
int gflags_test_nc_main(int argc, const char** argv);

#ifdef __cplusplus
}
#endif

#endif
