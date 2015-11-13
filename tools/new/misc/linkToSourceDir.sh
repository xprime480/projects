#!/bin/bash

# use this script as db admin user and start it from exe/testscripts/UDF_CORE/

DEV_USER=i811383
HOME_SRC=/home/${DEV_USER}/SAPDevelop/AFL/git/sys/src

if [ -d UDF_CORE_CAM__ ]
then
    echo "Backup copy already exists. No links are generated."
    exit 1
fi

mv UDF_CORE_CAM UDF_CORE_CAM__
mv UDF_CORE_RM1 UDF_CORE_RM1__
mv UDF_CORE_RD1 UDF_CORE_RD1__
mv UDF_DDF_CAM UDF_DDF_CAM__
mv UDF_DDF_RM1 UDF_DDF_RM1__
mv UDF_DDF_RD1 UDF_DDF_RD1__
mv UDF_DDF_RD1_newCV UDF_DDF_RD1_newCV__

ln -s ${HOME_SRC}/nutest/testscripts/UDF_CORE/UDF_CORE_CAM
ln -s ${HOME_SRC}/nutest/testscripts/UDF_CORE/UDF_CORE_RM1
ln -s ${HOME_SRC}/nutest/testscripts/UDF_CORE/UDF_CORE_RD1
ln -s ${HOME_SRC}/nutest/testscripts/UDF_CORE/UDF_DDF_CAM
ln -s ${HOME_SRC}/nutest/testscripts/UDF_CORE/UDF_DDF_RM1
ln -s ${HOME_SRC}/nutest/testscripts/UDF_CORE/UDF_DDF_RD1
ln -s ${HOME_SRC}/nutest/testscripts/UDF_CORE/UDF_DDF_RD1_newCV


mv setup/CAM setup/CAM__
mv setup/RM1 setup/RM1__
mv setup/RD1 setup/RD1__
mv setup/RD1_newCV setup/RD1_newCV__

mkdir -p setup/CAM/sap
ln -s ${HOME_SRC}/AFL/UDF_CORE/hana_content/CAM/sap/is setup/CAM/sap/is
mkdir -p setup/RM1/sap
ln -s ${HOME_SRC}/AFL/UDF_CORE/hana_content/RM1/sap/is setup/RM1/sap/is
mkdir -p setup/RD1/sap
ln -s ${HOME_SRC}/AFL/UDF_CORE/hana_content/RD1/sap/is setup/RD1/sap/is
mkdir -p setup/RD1_newCV/sap
ln -s ${HOME_SRC}/AFL/UDF_CORE/hana_content/RD1_newCV/sap/is setup/RD1_newCV/sap/is


mv util/schema_dump/abapTables_CAM.sql util/schema_dump/abapTables_CAM.sql__
mv util/schema_dump/abapTables_RM1.sql util/schema_dump/abapTables_RM1.sql__
mv util/schema_dump/abapTables_RD1.sql util/schema_dump/abapTables_RD1.sql__

ln -s ${HOME_SRC}/AFL/UDF_CORE/dailyBuild/util/schema_dump/abapTables_CAM.sql util/schema_dump/abapTables_CAM.sql
ln -s ${HOME_SRC}/AFL/UDF_CORE/dailyBuild/util/schema_dump/abapTables_RM1.sql util/schema_dump/abapTables_RM1.sql
ln -s ${HOME_SRC}/AFL/UDF_CORE/dailyBuild/util/schema_dump/abapTables_RD1.sql util/schema_dump/abapTables_RD1.sql


mv util/user_roles util/user_roles__

ln -s ${HOME_SRC}/AFL/UDF_CORE/dailyBuild/util/user_roles util/user_roles


mv framework framework__

ln -s ${HOME_SRC}/nutest/testscripts/UDF_CORE/framework

