#ifndef VERSION       // clashes with config.h from libgd when we build that library and use the GNU file / libmagic portability layer code there...
#define VERSION "100"
#endif
#define BUILTIN_ELF
/* #undef BZLIBSUPPORT */
#define ELFCORE
/* #undef HAVE_ASCTIME_R */
/* #undef HAVE_ASPRINTF */
/* #undef HAVE_BYTESWAP_H */
/* #undef HAVE_BZLIB_H */
/* #undef HAVE_CTIME_R */
/* #undef HAVE_DECL_OPTRESET */
/* #undef HAVE_DPRINTF */
/* #undef HAVE_ERR_H */
/* #undef HAVE_FMTCHECK */
/* #undef HAVE_FORK */
/* #undef HAVE_FREELOCALE */
/* #undef HAVE_GETLINE */
/* #undef HAVE_GETOPT_H */
/* #undef HAVE_GMTIME_R */
#define HAVE_INTTYPES_H         1
/* #undef HAVE_LIBSECCOMP */
/* #undef HAVE_LOCALTIME_R */
/* #undef HAVE_LZMA_H */
#define HAVE_MBRTOWC   1
/* #undef HAVE_MEMMEM */
/* #undef HAVE_MKSTEMP */
/* #undef HAVE_MMAP */
/* #undef HAVE_NBTOOL_CONFIG_H */
/* #undef HAVE_NEWLOCALE */
/* #undef HAVE_PIPE2 */
/* #undef HAVE_POSIX_SPAWNP */
/* #undef HAVE_PREAD */
/* #undef HAVE_SYS_BSWAP_H */
/* #undef HAVE_SIG_T */
/* #undef HAVE_SPAWN_H */
#define HAVE_REGEX_H    1   /* by way of TRE */
/* #undef HAVE_STRCASESTR */
/* #undef HAVE_STRLCAT */
/* #undef HAVE_STRLCPY */
/* #undef HAVE_STRNDUP */
#define HAVE_STRTOF
/* #undef HAVE_STRUCT_OPTION */
#define HAVE_STRUCT_STAT_ST_RDEV
/* #undef HAVE_STRUCT_TM_TM_GMTOFF */
/* #undef HAVE_STRUCT_TM_TM_ZONE */
/* #undef HAVE_SYS_BSWAP_H */
/* #undef HAVE_SYS_IOCTL_H */
/* #undef HAVE_SYS_MMAN_H */
/* #undef HAVE_SYS_SYSMACROS_H */
/* #undef HAVE_SYS_TIME_H */
#define HAVE_SYS_TYPES_H          1
#define HAVE_SYS_UTIME_H
/* #undef HAVE_SYS_WAIT_H */
/* #undef HAVE_UNISTD_H */
/* #undef HAVE_USELOCALE */
/* #undef HAVE_UTIME */
/* #undef HAVE_UTIMES */
/* #undef HAVE_UTIME_H */
/* #undef HAVE_VASPRINTF */
#define HAVE_WCHAR_H    1
#define HAVE_WCTYPE_H    1
/* #undef HAVE_WCWIDTH */
/* #undef HAVE_XLOCALE_H */
/* #undef HAVE_ZLIB_H */
/* #undef XZLIBSUPPORT */
/* #undef ZLIBSUPPORT */

#define HAVE_SYS_STAT_H 1
#undef HAVE_DLFCN_H
