# 3rd party libs

if(NOT BUILD_THIRDPARTY)
  include(FindPkgConfig)
endif(NOT BUILD_THIRDPARTY)

#------------
# Try to find lib Z
if(BUILD_THIRDPARTY)
  # Try to build it
  message(STATUS "We will build Z lib from thirdparty")
  add_subdirectory(libz)
  set(Z_LIBNAME z PARENT_SCOPE)
  set(Z_INCLUDE_DIRNAME ${OPENJPEG_SOURCE_DIR}/thirdparty/include PARENT_SCOPE)
  set(ZLIB_FOUND 1)
else(BUILD_THIRDPARTY)
  # Try to find lib Z
  find_package(ZLIB)
  if(ZLIB_FOUND)
    set(Z_LIBNAME ${ZLIB_LIBRARIES} PARENT_SCOPE)
    set(Z_INCLUDE_DIRNAME ${ZLIB_INCLUDE_DIRS} PARENT_SCOPE)
    message(STATUS "Your system seems to have a Z lib available, we will use it to generate PNG lib")
    # message(STATUS "DEBUG: ${ZLIB_INCLUDE_DIRS} vs ${ZLIB_INCLUDE_DIR}")
  else(ZLIB_FOUND) # not found
    message(STATUS "Z lib not found, activate BUILD_THIRDPARTY if you want build it (necessary to build libPNG)")
  endif(ZLIB_FOUND)
endif(BUILD_THIRDPARTY)


#------------
# Try to find lib PNG (which depends on zlib)
if(BUILD_THIRDPARTY)
  # Try to build it
  message(STATUS "We will build PNG lib from thirdparty")
  add_subdirectory(libpng)
  set(OPJ_HAVE_PNG_H 1 PARENT_SCOPE)
  set(OPJ_HAVE_LIBPNG 1 PARENT_SCOPE)
  set(PNG_LIBNAME png PARENT_SCOPE)
  set(PNG_INCLUDE_DIRNAME ${OPENJPEG_SOURCE_DIR}/thirdparty/libpng PARENT_SCOPE)
else(BUILD_THIRDPARTY)
  if(ZLIB_FOUND)
    find_package(PNG)
    # Static only build:
    #   it is not necessary to invoke pkg_check_module on libpng, because libpng
    #   only depends on zlib, which is already checked.
    if(PNG_FOUND)
      message(STATUS "Your system seems to have a PNG lib available, we will use it")
      set(OPJ_HAVE_PNG_H 1 PARENT_SCOPE)
      set(OPJ_HAVE_LIBPNG 1 PARENT_SCOPE)
      set(PNG_LIBNAME ${PNG_LIBRARIES} PARENT_SCOPE)
      set(PNG_INCLUDE_DIRNAME ${PNG_PNG_INCLUDE_DIR} PARENT_SCOPE)
    else(PNG_FOUND) # not found
      set(OPJ_HAVE_PNG_H 0 PARENT_SCOPE)
      set(OPJ_HAVE_LIBPNG 0 PARENT_SCOPE)
      message(STATUS "PNG lib not found, activate BUILD_THIRDPARTY if you want build it")
    endif(PNG_FOUND)
  endif(ZLIB_FOUND)
endif(BUILD_THIRDPARTY)

#------------
# Try to find lib TIFF

if(BUILD_THIRDPARTY)
  # Try to build it
  message(STATUS "We will build TIFF lib from thirdparty")
  add_subdirectory(libtiff)
  set(TIFF_LIBNAME tiff PARENT_SCOPE)
  set(TIFF_INCLUDE_DIRNAME
    ${OPENJPEG_SOURCE_DIR}/thirdparty/libtiff
    ${OPENJPEG_BINARY_DIR}/thirdparty/libtiff
    PARENT_SCOPE)
  set(OPJ_HAVE_TIFF_H 1 PARENT_SCOPE)
  set(OPJ_HAVE_LIBTIFF 1 PARENT_SCOPE)
else(BUILD_THIRDPARTY)
  find_package(TIFF)
  # Static only build:
  #   it is necessary to invoke pkg_check_module on libtiff since it may have
  #   several other dependencies not declared by its cmake module, but they are
  #   in the its pkgconfig module.
  if(PKG_CONFIG_FOUND)
    foreach(pc_tiff_module tiff tiff3 tiff4 tiff-3 tiff-4 libtiff libtiff3 libtiff4 libtiff-3 libtiff-4)
      pkg_check_modules(PC_TIFF QUIET ${pc_tiff_module})
      if(PC_TIFF_FOUND)
        break()
      endif(PC_TIFF_FOUND)
    endforeach()
  endif(PKG_CONFIG_FOUND)
  if(TIFF_FOUND)
    message(STATUS "Your system seems to have a TIFF lib available, we will use it")
    set(OPJ_HAVE_TIFF_H 1 PARENT_SCOPE)
    set(OPJ_HAVE_LIBTIFF 1 PARENT_SCOPE)
    if(BUILD_STATIC_LIBS AND NOT BUILD_SHARED_LIBS)
      # Probably incorrect as PC_TIFF_STATIC_LIBRARIES will lack the path to the libraries
      # and will only work if they are in system directories
      set(TIFF_LIBNAME ${PC_TIFF_STATIC_LIBRARIES} PARENT_SCOPE)
      set(TIFF_INCLUDE_DIRNAME ${PC_TIFF_STATIC_INCLUDE_DIRS} PARENT_SCOPE)
    else()
      set(TIFF_LIBNAME ${TIFF_LIBRARIES} PARENT_SCOPE)
      set(TIFF_INCLUDE_DIRNAME ${TIFF_INCLUDE_DIR} PARENT_SCOPE)
    endif()
  else(TIFF_FOUND) # not found
    set(OPJ_HAVE_TIFF_H 0 PARENT_SCOPE)
    set(OPJ_HAVE_LIBTIFF 0 PARENT_SCOPE)
    message(STATUS "TIFF lib not found, activate BUILD_THIRDPARTY if you want build it")
  endif(TIFF_FOUND)
endif(BUILD_THIRDPARTY)

#------------
# Try to find lib LCMS2 (or by default LCMS)
set(OPJ_HAVE_LCMS_H 0 PARENT_SCOPE)
set(OPJ_HAVE_LIBLCMS 0 PARENT_SCOPE)

if( BUILD_THIRDPARTY)
  # Try to build lcms2
  message(STATUS "We will build LCMS2 lib from thirdparty")
  add_subdirectory(liblcms2)
  set(LCMS_LIBNAME lcms2 PARENT_SCOPE)
  set(LCMS_INCLUDE_DIRNAME ${OPENJPEG_SOURCE_DIR}/thirdparty/liblcms2/include PARENT_SCOPE) #
  set(OPJ_HAVE_LCMS2_H 1 PARENT_SCOPE)
  set(OPJ_HAVE_LIBLCMS2 1 PARENT_SCOPE)
else(BUILD_THIRDPARTY)
  find_package(LCMS2)
  # Static only build:
  #   it is necessary to invoke pkg_check_module on lcms2 since it may have
  #   several other dependencies not declared by its cmake module, but they are
  #   in the its pkgconfig module.
  if(PKG_CONFIG_FOUND)
    pkg_check_modules(PC_LCMS2 QUIET lcms2)
  endif(PKG_CONFIG_FOUND)
  if(LCMS2_FOUND)
    message(STATUS "Your system seems to have a LCMS2 lib available, we will use it")
    set(OPJ_HAVE_LCMS2_H 1 PARENT_SCOPE)
    set(OPJ_HAVE_LIBLCMS2 1 PARENT_SCOPE)
    if(BUILD_STATIC_LIBS AND NOT BUILD_SHARED_LIBS)
      # Probably incorrect as PC_LCMS2_STATIC_LIBRARIES will lack the path to the libraries
      # and will only work if they are in system directories
      set(LCMS_LIBNAME ${PC_LCMS2_STATIC_LIBRARIES} PARENT_SCOPE)
      set(LCMS_INCLUDE_DIRNAME ${PC_LCMS2_STATIC_INCLUDE_DIRS} PARENT_SCOPE)
    else()
      set(LCMS_LIBNAME ${LCMS2_LIBRARIES} PARENT_SCOPE)
      set(LCMS_INCLUDE_DIRNAME ${LCMS2_INCLUDE_DIRS} PARENT_SCOPE)
    endif()
  else(LCMS2_FOUND) # not found lcms2
    # try to find LCMS
    find_package(LCMS)
    if(LCMS_FOUND)
      message(STATUS "Your system seems to have a LCMS lib available, we will use it")
      set(OPJ_HAVE_LCMS_H 1 PARENT_SCOPE)
      set(OPJ_HAVE_LIBLCMS 1 PARENT_SCOPE)
      set(LCMS_LIBNAME ${LCMS_LIBRARIES} PARENT_SCOPE)
      set(LCMS_INCLUDE_DIRNAME ${LCMS_INCLUDE_DIRS} PARENT_SCOPE)
    else(LCMS_FOUND) # not found lcms
      set(OPJ_HAVE_LCMS2_H 0 PARENT_SCOPE)
      set(OPJ_HAVE_LIBLCMS2 0 PARENT_SCOPE)
      message(STATUS "LCMS2 or LCMS lib not found, activate BUILD_THIRDPARTY if you want build it")
    endif(LCMS_FOUND)
  endif(LCMS2_FOUND)
endif(BUILD_THIRDPARTY)


#------------
IF (WITH_ASTYLE)
  enable_language(CXX)
  ADD_SUBDIRECTORY(astyle)
ENDIF(WITH_ASTYLE)
