#!/usr/bin/bash

EXE=../duplicate_kv.py
SAMPLEDIR=./sample
CONTROLDIR=./control
ROOT=${1}
KEY1=${2}
KEY2=${3}
INPUT_FILE=${ROOT}.csv
FILE_BASE=${ROOT}_dups.csv
SAMPLE_FILE=${SAMPLEDIR}/${FILE_BASE}
CONTROL_FILE=${CONTROLDIR}/${FILE_BASE}
STD_OUT=./foo_$$

source ./do_the_test.sh

do_the_test \
    ${EXE}  \
    "${FLAGS} ${KEY1} ${KEY2} ${INPUT_FILE} ${SAMPLE_FILE} " \
    ${SAMPLE_FILE}  \
    ${CONTROL_FILE} \
    ${STD_OUT}

exit 0
