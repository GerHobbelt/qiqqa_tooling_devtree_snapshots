
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

int arch_bsdcat_main(int argc, const char **argv);
int arch_test_main(int argc, const char **argv);
int arch_shar_main(int argc, const char **argv);
int arch_untar_contrib_main(int argc, const char **argv);
int arch_cpio_main(int argc, const char **argv);
int arch_untar_main(int argc, const char **argv);
int arch_minitar_main(int argc, const char **argv);
int arch_tarfilter_main(int argc, const char **argv);
int arch_bsdtar_main(int argc, const char **argv);
int arch_test_util_main(int argc, const char **argv);

#ifdef __cplusplus
}
#endif

#endif
