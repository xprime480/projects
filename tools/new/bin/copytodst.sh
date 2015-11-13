#!/bin/bash

DST=${HOME}/tmp/multimodel-2

function FOO () {
    SRC=$1
    DIRPART=$(dirname ${SRC})
    DSTDIR=${DST}/${DIRPART}
    if [ \! -e ${DSTDIR} ]; then
	echo ${DSTDIR}
	mkdir -p ${DSTDIR}
    fi
    cp -p ${SRC} ${DSTDIR}
}

