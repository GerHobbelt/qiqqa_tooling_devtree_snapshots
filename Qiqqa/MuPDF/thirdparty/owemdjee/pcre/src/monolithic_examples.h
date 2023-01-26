
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

	extern int pcre2_jit_test_main(int argc, const char** argv);
	extern int pcre2_ucptest_main(int argc, const char** argv);
	extern int pcre2_utf8_main(int argc, const char** argv);
	extern int pcre2demo_main(int argc, const char** argv);
	extern int pcre2grep_main(int argc, const char** argv);
	extern int pcre2test_main(int argc, const char** argv);

#ifdef __cplusplus
}
#endif

#endif
