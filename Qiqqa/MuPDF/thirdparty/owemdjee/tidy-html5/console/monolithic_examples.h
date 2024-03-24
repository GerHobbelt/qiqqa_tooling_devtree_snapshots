
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

int tidy_tab2space_main(int argc, const char** argv);
int tidy_test71_main(void);
int tidy_cli_main(int argc, const char** argv);

#ifdef __cplusplus
}
#endif

#endif
