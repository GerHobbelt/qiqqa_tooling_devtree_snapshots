
#pragma once

#if defined(BUILD_MONOLITHIC)

#ifdef __cplusplus
extern "C" {
#endif

	extern int dirent_cat_main(int argc, const char** argv);
	extern int dirent_dir_main(int argc, const char** argv);
	extern int dirent_du_main(int argc, const char** argv);
	extern int dirent_example_lookup_main(int argc, const char** argv);
	extern int dirent_find_main(int argc, const char** argv);
	extern int dirent_ls_main(int argc, const char** argv);
	extern int dirent_scandir_main(int argc, const char** argv);
	extern int dirent_updatedb_main(int argc, const char** argv);

	extern int dirent_compile_test_main(void);
	extern int dirent_cpp_test_main(void);
	extern int dirent_dirent_test_main(void);
	extern int dirent_scandir_test_main(void);
	extern int dirent_strverscmp_test_main(void);
	extern int dirent_telldir_test_main(void);
	extern int dirent_unicode_test_main(void);
	extern int dirent_utf8_test_main(void);

#ifdef __cplusplus
}
#endif

#endif
