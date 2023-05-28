cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# ---- Project ----

# Note: update this to your new project's name and version
project(
  NAS_lockfile
  VERSION 1.0
  LANGUAGES C
)

# ---- Options ----
option(NASLF_USE_GHC_FILESYSTEM "Use ghc::filesystem instead of std::filesystem" OFF)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

# ---- Add dependencies via CPM ----
# see https://github.com/TheLartians/CPM.cmake for more info

include(cmake/CPM.cmake)

# PackageProject.cmake will be used to make our target installable
CPMAddPackage(
  NAME PackageProject.cmake
  GITHUB_REPOSITORY TheLartians/PackageProject.cmake
  VERSION 1.3
)

# ---- Add source files ----

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.c")

# ---- Create library ----

# Note: for header-only libraries change all PUBLIC flags to INTERFACE and create an interface
# target: add_library(NAS_lockfile INTERFACE) set_target_properties(NAS_lockfile PROPERTIES
# INTERFACE_COMPILE_FEATURES cxx_std_17)

add_library(NAS_lockfile ${headers} ${sources})
SET_TARGET_PROPERTIES(NAS_lockfile PROPERTIES OUTPUT_NAME nas_lockfile)
set_target_properties(NAS_lockfile PROPERTIES CXX_STANDARD 17)

if ( NASLF_USE_GHC_FILESYSTEM )
  # Switch to ghc::filesystem.
  target_link_libraries(NAS_lockfile PRIVATE ghcFilesystem::ghc_filesystem)
  target_compile_definitions(NAS_lockfile PUBLIC NASLF_USE_GHC_FILESYSTEM)
endif()

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(NAS_lockfile PUBLIC "$<$<BOOL:${MSVC}>:/permissive->")

# Link dependencies (if required) target_link_libraries(NAS_lockfile PUBLIC cxxopts)

target_include_directories(
  NAS_lockfile PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                 $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

# ---- Create an installable target ----
# this allows users to install and find the library via `find_package()`.

# the location where the project's version header will be placed should match the project's regular
# header paths
string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)

packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
  INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
  VERSION_HEADER "${VERSION_HEADER_LOCATION}"
  DEPENDENCIES ""
)
