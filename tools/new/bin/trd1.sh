#!/bin/bash

pushd /home/i809989/SAPDevelop/AFL/git/sys/src/AFL/UDF_CORE/hana_content/RD1

PYTHONPATH=/usr/sap/hdbclient/hdbcli:/usr/sap/hdbclient /usr/sap/hdbclient/Python/bin/python2.6 ../../tools/dumpAbapSchema/createDMFTablesDump.py
mv /home/i809989/SAPDevelop/AFL/git/sys/src/AFL/UDF_CORE/hana_content/RD1/abapTablesOrangeOnGerrit_UDFv2.sql /home/i809989/SAPDevelop/AFL/git/sys/src/AFL/UDF_CORE/dailyBuild/util/schema_dump/abapTables_RD1.sql

popd
