set(headers dlfcn.h)
set(sources dlfcn.c)


add_library(dl ${sources})

# Correctly export the location of installed includes in the target
target_include_directories(dl
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>)

# dot not add -D<target>_EXPORTS
set_target_properties(dl PROPERTIES DEFINE_SYMBOL "")

# set shared mode for compiling library and propagate mode to cmake clients
if (BUILD_SHARED_LIBS)
    target_compile_definitions(dl PUBLIC DLFCN_WIN32_SHARED)
endif (BUILD_SHARED_LIBS)

install (TARGETS dl EXPORT dlfcn-win32-targets
                    RUNTIME DESTINATION bin
                    LIBRARY DESTINATION lib${LIB_SUFFIX}
                    ARCHIVE DESTINATION lib${LIB_SUFFIX})

install (FILES ${headers} DESTINATION include)

# Export the targets  (build tree)
export(EXPORT dlfcn-win32-targets
       FILE "${CMAKE_BINARY_DIR}/dlfcn-win32-targets.cmake"
       NAMESPACE dlfcn-win32::
)

# Write the CMake config file
set(CMAKE_CONF_INSTALL_DIR share/dlfcn-win32)
set(INCLUDE_INSTALL_DIR include)
include(CMakePackageConfigHelpers)
configure_package_config_file(../dlfcn-win32-config.cmake.in ${CMAKE_BINARY_DIR}/dlfcn-win32-config.cmake
                              INSTALL_DESTINATION ${CMAKE_CONF_INSTALL_DIR}
                              PATH_VARS INCLUDE_INSTALL_DIR
                              NO_CHECK_REQUIRED_COMPONENTS_MACRO)

# Install the targets (install)
install(EXPORT dlfcn-win32-targets
        FILE dlfcn-win32-targets.cmake
        NAMESPACE dlfcn-win32::
        DESTINATION ${CMAKE_CONF_INSTALL_DIR})

# Install the CMake config file
install(FILES ${CMAKE_BINARY_DIR}/dlfcn-win32-config.cmake
        DESTINATION ${CMAKE_CONF_INSTALL_DIR})
