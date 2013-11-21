#!/usr/bin/bash

EXE=../equ_columns.py
SAMPLEDIR=./sample
CONTROLDIR=./control
ROOT=${1}
VERS=${2}
KEY1=${3}
KEY2=${4}
INPUT_FILE=${ROOT}.csv
SAMPLE_FILE=${SAMPLEDIR}/${ROOT}_${VERS}.txt
CONTROL_FILE=${CONTROLDIR}/${ROOT}_${VERS}.txt
STD_OUT=${SAMPLE_FILE}

source ./do_the_test.sh

do_the_test \
    ${EXE}  \
    "${FLAGS} ${KEY1} ${KEY2} ${INPUT_FILE}" \
    ${SAMPLE_FILE}  \
    ${CONTROL_FILE} \
    ${STD_OUT}

exit 0
