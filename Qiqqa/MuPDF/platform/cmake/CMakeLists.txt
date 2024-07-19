cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    qiqqa_backend
    VERSION 0.1.0
    DESCRIPTION "Qiqqa(R) back-end: server and tools to manage and process PDF,HTML,EPUB,DJVU,... files (articles/publications/books/presentations)"
    HOMEPAGE_URL "https://qiqqa.org/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    qiqqa_backend_lib OBJECT
    source/lib.cpp
)

target_include_directories(
    qiqqa_backend_lib ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(qiqqa_backend_lib PUBLIC cxx_std_20)

# ---- Declare executable ----

add_executable(qiqqa_backend_exe source/main.cpp)
add_executable(qiqqa_backend::exe ALIAS qiqqa_backend_exe)

set_property(TARGET qiqqa_backend_exe PROPERTY OUTPUT_NAME qiqqa_backend)

target_compile_features(qiqqa_backend_exe PRIVATE cxx_std_20)

target_link_libraries(qiqqa_backend_exe PRIVATE qiqqa_backend_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT qiqqa_backend_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of qiqqa_backend"
  )
endif()

include(cmake/dev-mode.cmake)
