#!/usr/bin/bash

EXE=../keycounter.py
SAMPLEDIR=./sample
CONTROLDIR=./control
ROOT=${1}
KEYS=${2}
INPUT_FILE=${ROOT}.csv
FILE_BASE=${ROOT}_counts.csv
SAMPLE_FILE=${SAMPLEDIR}/${FILE_BASE}
CONTROL_FILE=${CONTROLDIR}/${FILE_BASE}
STD_OUT=./foo_$$

source ./do_the_test.sh

do_the_test \
    ${EXE}  \
    "--keys=${KEYS} ${INPUT_FILE} ${SAMPLE_FILE} " \
    ${SAMPLE_FILE}  \
    ${CONTROL_FILE} \
    ${STD_OUT}

exit 0
