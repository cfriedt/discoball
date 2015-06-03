# The compilation of software known as DiscoBall is distributed under the
# following terms:
# 
# Copyright (c) 2015 Christopher Friedt. All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.
#!/bin/sh

NAME=discoball

if [ "$(grep "AC_INIT(${NAME}" configure.ac)" = "" ]; then
  echo "autogen.sh must be run in PWD of ${NAME} source"
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
