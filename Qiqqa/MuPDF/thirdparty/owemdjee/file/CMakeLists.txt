cmake_minimum_required (VERSION 3.15)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MACOSX_RPATH 1)

project(file VERSION 1.0.0 DESCRIPTION "open source implementation of the file(1) command that ships with most free operating systems")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(ConfigureChecks)

REPLACE_FUNCTIONS(LIB_SOURCES getopt_long asprintf vasprintf strlcpy strlcat getline ctime_r asctime_r localtime_r gmtime_r pread strcasestr fmtcheck dprintf)

add_library(magic STATIC
  src/buffer.c src/magic.c src/magic.h src/apprentice.c src/softmagic.c src/ascmagic.c
  src/encoding.c src/compress.c src/is_csv.c src/is_json.c src/is_tar.c src/readelf.c src/print.c
  src/fsmagic.c src/funcs.c src/file.h src/readelf.h src/tar.h src/apptype.c src/der.c src/der.h
  src/file_opts.h src/elfclass.h src/mygetopt.h src/cdf.c src/cdf_time.c src/readcdf.c src/cdf.h
  ${LIB_SOURCES}
)
target_compile_definitions(magic PUBLIC HAVE_CONFIG_H=1)
target_include_directories(magic PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

add_executable(file src/file.c src/magic.c)

target_compile_definitions(file PUBLIC HAVE_CONFIG_H=1)
target_include_directories(file PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(file magic)

set(MAGIC_FRAGMENT_BASE Magdir)
set(MAGIC_DIR ${PROJECT_SOURCE_DIR}/magic)
set(MAGIC_FRAGMENT_DIR ${MAGIC_DIR}/${MAGIC_FRAGMENT_BASE})
set(pkgdata_DATA magic.mgc)

file(GLOB MAGIC_FRAGMENTS
          CONFIGURE_DEPENDS
          "${MAGIC_DIR}/Header"
          "${MAGIC_DIR}/Localstuff"
          "${MAGIC_FRAGMENT_DIR}/*"
)

file(GLOB EXTRA_DIST
          "${MAGIC_DIR}/scripts/create_filemagic_flac"
          "${MAGIC_FRAGMENTS}"
)

if (WIN32)
	# Automake calls this EXEEXT, and CMake doesn't have a standard name
	# for it; follow Automake's naming convention so we can share .in files
	set (EXEEXT ".exe")
endif(WIN32)

file(COPY ${MAGIC_FRAGMENTS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/magic)

add_custom_command(
  TARGET file
  POST_BUILD
  COMMAND file -C -m magic
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Compile magic files to magic.mgc in ${CMAKE_CURRENT_BINARY_DIR}"
)

include(GNUInstallDirs)

install(TARGETS magic LIBRARY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/magic.mgc DESTINATION ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})
