#!/bin/bash

SID=${2:-RD1}
DIRS=$(find nutest/testscripts/UDF_CORE/UDF_{CORE,DDF}_${SID} -type d -print | grep -E "$1\$")
find_data_files.py  ${DIRS}
