dnl auto configuration script for libimg
dnl to produce your own configure script rather than
dnl the one provided run autoconf

dnl initialize autoconf
AC_INIT([libimg], [0.0.0])

dnl have extra scripts go into build-aux directory
AC_CONFIG_AUX_DIR([build-aux])

dnl tell autoconf the source directory
AC_CONFIG_SRCDIR([.])

dnl tell autoconf the files that should be generating
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])

dnl initialize automake
dnl tell it we are not a gnu product (i.e. foreign)
AM_INIT_AUTOMAKE([foreign -Wall -Werror])

dnl maintainer mode to make life easier
AM_MAINTAINER_MODE

dnl check language, compilers, and programs for installing
AC_LANG([C])
AC_PROG_CC
AC_PROG_CPP
AM_PROG_AR

dnl inistalize libtool
LT_INIT

dnl check standard c headers
AC_HEADER_STDC

dnl check for libraries
dnl starting with libpng
dnl AC_CHECK_LIB([png], [png_read_image], , AC_MSG_ERROR([libpng not found])
LIBS="-lpng"

dnl output files
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
