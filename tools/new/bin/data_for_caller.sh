#!/bin/bash

TARGET=${1:-SP_SR_HPR_GET_PAR_CFG}

DIRS=$(find ~/SAPDevelop/AFL/git/sys/src/nutest/testscripts/UDF_CORE/UDF_{CORE,DDF}_RD1/ -name properties.ini -exec grep -qi ${TARGET} {} \; -print | sed -e 's|/[^/]*$||')
find_data_files.py ${DIRS}
