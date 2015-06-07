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

CPY="Copyright (c)"
CPN="COPYING"

TMP1=""
TMP2=""

cleanup() {
  echo "cleaning up"
  if [ "" != "${TMP1}" ]; then
    rm -f ${TMP1}
  fi
  if [ "" != "${TMP2}" ]; then
    rm -f ${TMP2}
  fi
}

trap "cleanup" SIGHUP SIGINT SIGTERM 

apply_copyright() {
	local extensions=${1}
	local prefix=${2}
	local header=${3}
	local footer=${4}
	
  TMP1="$(mktemp -t ${SCRIPT})"
  echo '' > ${TMP1}
  [[ ! -f ${TMP1} ]] && die "${TMP1} is not a file" 
	
	if [ "" != "${header} ]; then
    printf "${header}\n" >> ${TMP1} || die "failed to write header" 
  fi
	
	while $(read line); do
	  printf "${prefix}${line}" >> ${TMP1} || die "failed to write line"
  done < ${CPN}

  if [ "" != "${footer} ]; then
    printf "${footer}\n" >> ${TMP1} || die "failed to write footer"
  fi

  if [ "" = "$(grep "${CPR}" ${TMP1})" ]; then
    false
    die "failed to find '${CPR}' in tmp1"
  fi

	for e in ${extensions}; do
	  for f in $(find * -name "*${e}"); do
	    
	    if [ "" != "$(grep "${CPR}" ${TMP1})" ]; then
	      continue
      fi

	    echo "processing ${f}"

	    TMP2="$(mktemp -t ${SCRIPT})"
	    echo '' > ${TMP2}
	    [[ ! -f ${TMP2} ]] && die "${TMP2} is not a file"
	    
      cat ${TMP1} >> ${TMP2}
      cat ${f} >> ${TMP2}
      mv ${TMP2} ${f}

      rm -f ${TMP2}
      TMP2=""
    done
  done
  
  rm -f ${TMP1}
  TMP1=""
}

# update c-style copyrights
EXT='.c .cpp .h .cc'
PFX=' * '
HDR='/*'
FTR=' */'
apply_copyright "${EXT}" "${PFX}" "${HDR}" "${FTR}" || die "'apply_copyright \"${EXT}\" \"${PFX}\" \"${HDR}\" \"${FTR}\"' failed"

# update shell-style copyrights
EXT='.sh .mk .am'
PFX='# '
HDR=''
FTR=''
apply_copyright "${EXT}" "${PFX}" "${HDR}" "${FTR}" || die "'apply_copyright \"${EXT}\" \"${PFX}\" \"${HDR}\" \"${FTR}\"' failed"

# update autoconf-style copyrights
ACFILES='.ac'
PFX='dnl '
HDR=''
FTR=''
apply_copyright "${EXT}" "${PFX}" "${HDR}" "${FTR}" || die "'apply_copyright \"${EXT}\" \"${PFX}\" \"${HDR}\" \"${FTR}\"' failed"
