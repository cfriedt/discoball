dnl The compilation of software known as DiscoBall is distributed under the
dnl following terms:
dnl
dnl Copyright (c) 2015 Christopher Friedt. All rights reserved.
dnl
dnl Redistribution and use in source and binary forms, with or without
dnl modification, are permitted provided that the following conditions
dnl are met:
dnl 1. Redistributions of source code must retain the above copyright
dnl notice, this list of conditions and the following disclaimer.
dnl 2. Redistributions in binary form must reproduce the above copyright
dnl notice, this list of conditions and the following disclaimer in the
dnl documentation and/or other materials provided with the distribution.
dnl
dnl THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
dnl ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
dnl IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
dnl ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
dnl FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
dnl DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
dnl OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
dnl HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
dnl LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
dnl OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
dnl SUCH DAMAGE.

AC_PREREQ(2.59)
AC_INIT(discoball, 0.1)
AC_PROG_CC
AC_PROG_CXX

AC_CANONICAL_SYSTEM

AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])

LT_INIT

AC_PROG_LIBTOOL

case $host_os in
  darwin* )
    LD_LIBRARY_PATH_VAR="DYLD_LIBRARY_PATH"
    CFLAGS+=' -D_LINUX_ERR_H'
    CFLAGS+=' -D_UAPI_LINUX_TYPES_H'
    CFLAGS+=' -D_LINUX_TYPES_H'
    CFLAGS+=' -D_LINUX_STDDEF_H'
    CFLAGS+=' -D_LINUX_SEQ_FILE_H'
    CFLAGS+=' -D_LINUX_RADIX_TREE_H'
    CFLAGS+=' -D_SECURE__STRING_H_'
    CFLAGS+=' -D_LINUX_LIST_H'
    CFLAGS+=" -include $srcdir/include/linux-types.h"
    ;;
  *)
    LD_LIBRARY_PATH_VAR="LD_LIBRARY_PATH"
    ;;
esac
AC_SUBST(LD_LIBRARY_PATH_VAR)

AC_ARG_ENABLE([pthread], [AS_HELP_STRING([--enable-pthread], [enable POSIX thread support])], [])
AS_IF(
  [test "x$enable_pthread" = xyes -o "x$enable_pthread" != xno],
  [AC_CHECK_HEADERS(
    [pthread.h],
    [AC_SEARCH_LIBS(
      [pthread_create],
      [c pthread],
      [enable_pthread=yes],
      [AS_IF(
        [test "x$enable_pthread" = xyes],
        [AC_MSG_ERROR([pthread.h exists, but cannot find the library containing pthread_create()])]
        [AC_MSG_NOTICE([disabling pthread support])],
      )]
    )],
    [AS_IF(
      [test "x$enable_pthread" = xyes],
      [AC_MSG_ERROR([unable to find pthread.h])],
      [AC_MSG_NOTICE([disabling pthread support])]
    )]
  )],
  []
)
AM_CONDITIONAL([ENABLE_PTHREAD], [test x$enable_pthread = xyes])

dnl -no-undefined is interpreted by libtool per compiler / linker
LDFLAGS+=' -no-undefined'
CFLAGS+=' -I$(top_srcdir)/include -I$(top_srcdir)/include/public'
CXXFLAGS+=' -I$(top_srcdir)/include -I$(top_srcdir)/include/public'

AC_ARG_WITH([linux],[AS_HELP_STRING([--with-linux=PATH],[path to Linux source])],[])
AS_IF([test x"$with_linux" != x -a "x$with_linux" != xno -a "x$with_linux" != xyes],
  LINUX_PATH="$with_linux"
  AC_SUBST(LINUX_PATH)
  LINUX_CFLAGS="-I${LINUX_PATH}/include -I${LINUX_PATH}/include/uapi"
  CFLAGS+=" ${LINUX_CFLAGS}"
)

AC_ARG_WITH([gtest],[AS_HELP_STRING([--with-gtest=PATH],[path to Google Test Framework])],[])
AS_IF([test x"$with_gtest" != x -a "x$with_gtest" != xno -a "x$with_gtest" != xyes],
  GTEST_PATH="$with_gtest"
  ENABLE_GTEST="yes"
  AC_SUBST(ENABLE_GTEST)
  AC_SUBST(GTEST_PATH)
  GTEST_CXXFLAGS="-I${GTEST_PATH}/include"
  AC_SUBST(GTEST_CXXFLAGS)
  GTEST_LDFLAGS="-L${GTEST_PATH}/lib -lgtest -lgtest_main"
  AC_SUBST(GTEST_LDFLAGS)
)
AM_CONDITIONAL([ENABLE_GTEST], [test x$ENABLE_GTEST = xyes])

AC_ARG_ENABLE([debug],[AS_HELP_STRING([--enable-debug],[enable debug symbols])],[])
AS_IF([test "x$enable_debug" = "xyes"], [
    CFLAGS+=' -DDEBUG -O0 -g'
    ENABLE_DEBUG="yes"
    AC_SUBST(ENABLE_DEBUG)
])
AM_CONDITIONAL([ENABLE_DEBUG], [test x$ENABLE_DEBUG = xyes])

AC_CONFIG_FILES(
    Makefile
    include/Makefile
    include/public/Makefile
    src/Makefile
    test/Makefile
)

AC_OUTPUT
