#!/bin/bash
echo "SID:"
read SID
echo "HDB instance:"
read HDBInstance
echo "Debug|Optimized|Release:"
read buildType
testPackInstallerDir=$(cat $SRC/build/Optimized/imports/hana_pool | awk '{print $1 "/__installer.HDB"}')
sudo $testPackInstallerDir/../test/python_support_internal/installTestPkg.sh -s $SID $testPackInstallerDir/../test/python_support_internal/python_support_internal.tgz
echo "Python support installed"
sudo -u lroot $SRC/build/$buildType/packages/installTestPkg.sh -s $SID $SRC/build/$buildType/packages/afl_testpack.tgz
echo "Python tests installed"
SID_L=$(echo $SID | awk '{print tolower($0)}')
sudo chown -R ${SID_L}adm /usr/sap/$SID/HDB$HDBInstance/exe/testscripts

exit