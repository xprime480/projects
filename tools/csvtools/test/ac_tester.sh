#!/usr/bin/bash

EXE=../analyze_columns.py
SAMPLEDIR=./sample
CONTROLDIR=./control
ROOT=${1}


function one_test () {
    EXT=${1}
    FLAGS=${2}
    SAMPLE_FILE=${SAMPLEDIR}/${ROOT}.${EXT}
    CONTROL_FILE=${CONTROLDIR}/${ROOT}.${EXT}

    ${EXE} ${FLAGS} ${ROOT}.csv > ${SAMPLE_FILE} || exit 1
    
    if [ \! -f ${CONTROL_FILE} ]; then
	echo "Control file ${CONTROL_FILE} does not exist."
	exit 1
    fi

    diff -q ${SAMPLE_FILE} ${CONTROL_FILE} || exit 1

    rm ${SAMPLE_FILE}
}

one_test tex
one_test txt '--format=text'

exit 0
