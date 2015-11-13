#!/bin/bash

UDF_CORE_DIR=${SRC}/AFL/UDF_CORE
SCHEMA=${1:-RD1}
CONTENT_DIR=${UDF_CORE_DIR}/hana_content/${SCHEMA}
if [ \! -d ${CONTENT_DIR} ]; then
    echo "Content directory ${CONTENT_DIR} is not found"
    exit 1
fi

START_DIR=`pwd`
OFILE=abapTables_${SCHEMA}.sql
IFILE=abapTablesOrangeOnGerrit_UDFv2.sql
DUMP_DIR=${UDF_CORE_DIR}/dailyBuild/util/schema_dump
PYTHON=/usr/sap/hdbclient/Python/bin/python2.6
TOOL=${UDF_CORE_DIR}/tools/dumpAbapSchema/createDMFTablesDump.py

cd ${CONTENT_DIR}
export PYTHONPATH=/usr/sap/hdbclient/hdbcli:/usr/sap/hdbclient
${PYTHON} ${TOOL} -q
if [ -e ${IFILE} ] ; then
    mv ${IFILE} ${DUMP_DIR}/${OFILE}
fi
cd ${START_DIR}

exit 0
