#!/usr/bin/bash

function do_the_test () {
    EXE=${1}
    ARGS="${2}"
    SAMPLE_FILE=${3}
    CONTROL_FILE=${4}
    
    ${EXE} ${ARGS} > ${STD_OUT} || exit 1
    
    if [ \! -f ${CONTROL_FILE} ]; then
	echo "Control file ${CONTROL_FILE} does not exist."
	exit 1
    fi

    diff -q ${SAMPLE_FILE} ${CONTROL_FILE} || exit 1

    rm ${SAMPLE_FILE} ${STD_OUT} >/dev/null 2>&1
}
