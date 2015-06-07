#!/bin/sh

NAME="$(basename ${PWD})"
SCRIPT="$(basename $0)"

die() {
  local r=$?
  if [ "" != "$*" ]; then
    echo "$*"
  fi
  exit $r
}

if [ "" = "$(grep "AC_INIT(${NAME}" configure.ac 2>/dev/null)" ]; then
  false
  die "${SCRIPT} must be run in top source directory"
fi

DEBUG=""
D() {
  if [ "" != "${DEBUG}" ]; then
    echo "D/ $*"
  fi
}

grep "^[0-9]" ChangeLog | awk '{split($0,a,"\t"); printf("%s, %s, %s\n", a[1] ,a[2], a[3]);}' | sort -u > AUTHORS
