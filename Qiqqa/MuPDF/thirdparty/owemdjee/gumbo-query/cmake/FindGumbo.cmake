# - Try to find Gumbo
# Once done, this will define
#
#  Gumbo_FOUND - system has Gumbo-Parser
#  Gumbo_INCLUDE_DIRS - the Gumbo-Parser include directories
#  Gumbo_LIBRARY - shared library
#  Gumbo_static_LIBRARY - static library
#  Gumbo_LIBRARIES - libraries

include(LibFindMacros)

# Dependencies
# libfind_package()

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(Gumbo_PKGCONF gumbo)

# Include dir
find_path(Gumbo_INCLUDE_DIR
  NAMES gumbo.h
  PATHS ${Gumbo_PKGCONF_INCLUDE_DIRS}
)

# Finally the library itself
find_library(Gumbo_LIBRARY
  NAMES libgumbo.dylib libgumbo.dll gumbo.dylib gumbo.dll libgumbo.so
  PATHS ${Gumbo_PKGCONF_LIBRARY_DIRS}
)

find_library(Gumbo_static_LIBRARY
  NAMES libgumbo.a libgumbo_static.a gumbo.a gumbo_static.a libgumbo.lib libgumbo_static.lib gumbo.lib gumbo_static.lib
  PATHS ${Gumbo_PKGCONF_LIBRARY_DIRS}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(Gumbo_INCLUDE_OPTS Gumbo_INCLUDE_DIR)

if(NOT "${Gumbo_LIBRARY}" STREQUAL "Gumbo_LIBRARY-NOTFOUND")
    list(APPEND Gumbo_LIBRARY_OPTS Gumbo_LIBRARY)
endif()

if(NOT "${Gumbo_static_LIBRARY}" STREQUAL "Gumbo_static_LIBRARY-NOTFOUND")
    list(APPEND Gumbo_LIBRARY_OPTS Gumbo_static_LIBRARY)
endif()

libfind_process(Gumbo)
