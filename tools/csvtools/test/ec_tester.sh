#!/usr/bin/bash

EXE=../equ_columns.py
SAMPLEDIR=./sample
CONTROLDIR=./control
ROOT=${1}
VERS=${2}
KEY1=${3}
KEY2=${4}

function one_test () {
    SAMPLE_FILE=${SAMPLEDIR}/${ROOT}_${VERS}.txt
    CONTROL_FILE=${CONTROLDIR}/${ROOT}_${VERS}.txt

    ${EXE} ${FLAGS} ${KEY1} ${KEY2} ${ROOT}.csv > ${SAMPLE_FILE} || exit 1
    
    if [ \! -f ${CONTROL_FILE} ]; then
	echo "Control file ${CONTROL_FILE} does not exist."
	exit 1
    fi

    diff -q ${SAMPLE_FILE} ${CONTROL_FILE} || exit 1

    rm ${SAMPLE_FILE}
}

one_test 

exit 0
