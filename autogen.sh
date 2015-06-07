#!/bin/sh

SCRIPT="$(basename $0)"
NAME=discoball

if [ "$(grep "AC_INIT(${NAME}" configure.ac)" = "" ]; then
  echo "${SCRIPT} must be run in PWD of ${NAME} source"
  exit 1
fi

if [ "$1" = clean ]; then
  if [ -d tmp ]; then
    rm -Rf tmp
  fi
  if [ -e Makefile ]; then
    make clean &> /dev/null || true
  fi
  for e in la lo lai o so in m4 jar; do
    rm -f $(find . -name "*.${e}" -type f)
  done
  for e in Makefile depcomp INSTALL config.guess config.sub config.log config.status configure install-sh ltmain.sh missing libtool compile; do
    rm -f $(find . -name "${e}" -type f -o -type l)
  done
  for e in autom4te.cache .libs .deps bin; do
    rm -Rf $(find . -name "${e}" -type d)
  done
elif [ "$1" = reconf ]; then
  autoreconf -fi --warnings=none
else
  LIBTOOLIZE="$(which glibtoolize)"
  if [ "${LIBTOOLIZE}x" = "" ]; then
    LIBTOOLIZE="$(which libtoolize)"
  fi
  if [ "${LIBTOOLIZE}x" = "" ]; then
    exit 1
  fi
  ${LIBTOOLIZE} && aclocal && automake --add-missing --warnings=none && autoconf
fi
