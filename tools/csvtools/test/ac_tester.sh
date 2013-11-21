#!/usr/bin/bash

EXE=../analyze_columns.py
SAMPLEDIR=./sample
CONTROLDIR=./control
ROOT=${1}
INPUT_FILE=${ROOT}.csv

source ./do_the_test.sh

function one_test () {
    EXT=${1}
    FLAGS=${2}
    SAMPLE_FILE=${SAMPLEDIR}/${ROOT}.${EXT}
    CONTROL_FILE=${CONTROLDIR}/${ROOT}.${EXT}
    STD_OUT=${SAMPLE_FILE}

    do_the_test \
	${EXE}  \
	"${FLAGS} ${INPUT_FILE}" \
	${SAMPLE_FILE}  \
	${CONTROL_FILE} \
	${STD_OUT}
}

one_test tex
one_test txt '--format=text'

exit 0
