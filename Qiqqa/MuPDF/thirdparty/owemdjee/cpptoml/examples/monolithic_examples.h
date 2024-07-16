
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

int cpptoml_build_toml_example_main(int argc, const char** argv);
int cpptoml_parse_example_main(int argc, const char** argv);

int cpptoml_conversions_example_main(void);
int cpptoml_parse_stdin_example_main(void);

#ifdef __cplusplus
}
#endif

#endif
