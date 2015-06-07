#!/bin/sh

SCRIPT="$(basename $0)"
NAME=discoball

if [ "$(grep "AC_INIT(${NAME}" configure.ac)" = "" ]; then
  echo "${SCRIPT} must be run in PWD of ${NAME} source"
  exit 1
fi

prepend_file() {
	local copyright="Copyright (c)"
	local extensions="$1"
	local prefix="$2"
	local header="$3"
	local footer="$4"
}

# update c-style copyrights
CFILES="$(find * -name '*.c' -o -name '*.cpp' -o -name '*.h' -o -name '*.cc')"

# update shell-style copyrights
SHFILES="$(find * -name '*.sh')"

# update autoconf-style copyrights
ACFILES="$(find * -name '*.ac')"

# update automake-style copyrights
AMFILES="$(find * -name '*.am')"

