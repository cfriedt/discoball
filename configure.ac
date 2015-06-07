AC_PREREQ(2.59)
AC_INIT(discoball, 0.1)
AC_PROG_CC
AC_PROG_CXX

AC_CANONICAL_SYSTEM

AM_INIT_AUTOMAKE

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
    CFLAGS+=" -include $srcdir/include/public/discoball/linux_types.h"
    ;;
  *)
    LD_LIBRARY_PATH_VAR="LD_LIBRARY_PATH"
    ;;
esac
AC_SUBST(LD_LIBRARY_PATH_VAR)

AC_SEARCH_LIBS([pthread_create], [c pthread], [], [
  AC_MSG_ERROR([unable to find the pthread_create() function])
])

dnl -no-undefined is interpreted by libtool per compiler / linker
LDFLAGS+=' -no-undefined'
CFLAGS+=' -I$(top_srcdir)/include -I$(top_srcdir)/include/public'
CXXFLAGS+=' -I$(top_srcdir)/include -I$(top_srcdir)/include/public'

AC_ARG_WITH([linux],[AS_HELP_STRING([--with-linux=PATH],[path to Linux source])])
AS_IF([test x"$with_linux" != x -a "x$with_linux" != xno -a "x$with_linux" != xyes],
  LINUX_PATH="$with_linux"
  AC_SUBST(LINUX_PATH)
  LINUX_CFLAGS="-I${LINUX_PATH}/include -I${LINUX_PATH}/include/uapi"
  CFLAGS+=" ${LINUX_CFLAGS}"
)

AC_ARG_WITH([gtest],[AS_HELP_STRING([--with-gtest=PATH],[path to Google Test Framework])])
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

AC_ARG_ENABLE([debug],[AS_HELP_STRING([--enable-debug],[enable debug symbols])])
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
