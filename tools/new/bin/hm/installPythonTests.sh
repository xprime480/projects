#!/bin/bash

SID=${1}
if [ -z "${SID}" ]; then
    SID=MD1
    #echo "SID:"
    #read SID
fi

HDBInstance=${2}
if [ -z "${HDBInstance}" ]; then
    HDBInstance=02
    #echo "HDB instance:"
    #read HDBInstance
fi

buildType=${3}
if [ -z "${buildType}" ]; then
    buildType=Optimized
    #echo "Debug|Optimized|Release:"
    #read buildType
fi

testPackInstallerDir=$(cat $SRC/build/Optimized/imports/hana_pool | awk '{print $1 "/__installer.HDB"}')
sudo -S $testPackInstallerDir/../test/python_support_internal/installTestPkg.sh -s $SID $testPackInstallerDir/../test/python_support_internal/python_support_internal.tgz < ~/.spw
echo "Python support installed"
sudo -u lroot $SRC/build/$buildType/packages/installTestPkg.sh -s $SID $SRC/build/$buildType/packages/afl_testpack.tgz
echo "Python tests installed"
SID_L=$(echo $SID | awk '{print tolower($0)}')
sudo chown -R ${SID_L}adm /usr/sap/$SID/HDB$HDBInstance/exe/testscripts

exit