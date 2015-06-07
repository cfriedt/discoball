# The compilation of software known as DiscoBall is distributed under the
# following terms:
#
# Copyright (c) 2015 Christopher Friedt. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution.
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

CPR="Copyright (c)"
CPN="COPYING"

TMP1=""
TMP2=""

cleanup() {
  local r=$?
  echo "cleaning up"
  if [ "" != "${TMP1}" ]; then
    D "removing ${TMP1}"
    rm -f ${TMP1}
  fi
  if [ "" != "${TMP2}" ]; then
    D "removing ${TMP2}"
    rm -f ${TMP2}
  fi
  exit $r
}

sigint() {
  echo ""
  echo "Caught SIGINT. cleaning up..."
  cleanup
}

trap cleanup SIGHUP SIGTERM SIGQUIT SIGABRT || die "failed to install error handler"
trap sigint SIGINT || die "failed to install SIGINT handler"

apply_copyright() {
	local extensions=${1}
	local prefix=${2}
	local header=${3}
	local footer=${4}

	D "extensions = '${extensions}'"
	D "prefix = '${prefix}'"
  D "header = '${header}'"
  D "footer = '${footer}'"

  TMP1="$(mktemp -t ${SCRIPT})"
  [[ ! -f ${TMP1} ]] && die "${TMP1} is not a file"

  D "created tmp1 as ${TMP1}"

	if [ "" != "${header}" ]; then
    D "writing header to tmp1"
    printf "${header}\n" >> ${TMP1} || die "failed to write header"
  fi

	D "populating copyright in tmp1"
	while read line; do
	  printf "${prefix}${line}\n" | awk '{ sub(/[ \t]+$/, ""); print }' >> ${TMP1} || die "failed to write line"
  done < ${CPN}

  if [ "" != "${footer}" ]; then
    D "writing footer to tmp1"
    printf "${footer}\n" >> ${TMP1} || die "failed to write footer"
  fi

  printf "\n" >> ${TMP1}

  if [ "" = "$(grep "${CPR}" ${TMP1})" ]; then
    false
    die "failed to find '${CPR}' in tmp1"
  fi

	for e in ${extensions}; do
	  for f in $(find * -name "*\.${e}"); do

	    D "considering file '${f}'"

	    if [ "" != "$(head -n 10 ${f} | grep "${CPR}")" ]; then
	      continue
      fi

	    D "processing ${f}"

	    TMP2="$(mktemp -t ${SCRIPT})"
	    [[ ! -f ${TMP2} ]] && die "${TMP2} is not a file"

	    D "created tmp2 as ${TMP2}"

      cat ${TMP1} >> ${TMP2} || die "failed to cat tmp1 to tmp2"
      cat ${f} >> ${TMP2} || die "failed to cat ${f} to tmp2"
      mv ${TMP2} ${f} || die "failed to mv tmp2 to ${f}"

      D "removing tmp2"
      rm -f ${TMP2}
      TMP2=""
    done
  done

  D "removing tmp1"
  rm -f ${TMP1}
  TMP1=""
}

# update c-style copyrights
EXT='c cpp h cc'
PFX=' * '
HDR='/*'
FTR=' */'
apply_copyright "${EXT}" "${PFX}" "${HDR}" "${FTR}" || die "'apply_copyright \"${EXT}\" \"${PFX}\" \"${HDR}\" \"${FTR}\"' failed"

# update shell-style copyrights
EXT='sh mk am'
PFX='# '
HDR=''
FTR=''
apply_copyright "${EXT}" "${PFX}" "${HDR}" "${FTR}" || die "'apply_copyright \"${EXT}\" \"${PFX}\" \"${HDR}\" \"${FTR}\"' failed"

# update autoconf-style copyrights
EXT='ac'
PFX='dnl '
HDR=''
FTR=''
apply_copyright "${EXT}" "${PFX}" "${HDR}" "${FTR}" || die "'apply_copyright \"${EXT}\" \"${PFX}\" \"${HDR}\" \"${FTR}\"' failed"

cleanup
