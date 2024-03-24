
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

	extern int pcre2_jit_test_main(void);
	extern int pcre2_ucp_test_main(int argc, const char** argv);
	extern int pcre2_utf8_main(int argc, const char** argv);
	extern int pcre2_demo_main(int argc, const char** argv);
	extern int pcre2_grep_main(int argc, const char** argv);
	extern int pcre2posix_test_main(int argc, const char** argv);
	extern int pcre2_test8_main(int argc, const char** argv);
	extern int pcre2_test16_main(int argc, const char** argv);
	extern int pcre2_test32_main(int argc, const char** argv);
	extern int pcre2_dftables_main(int argc, const char** argv);

#ifdef __cplusplus
}
#endif

#endif
