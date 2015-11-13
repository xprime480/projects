#!/bin/bash

buildType="$1"
if [ -z "$buildType" ]; then
    echo "Debug|Optimized|Release"
    read buildType
fi
sudo $OWN/sys/src/build/$buildType/gen/product_specific_afls/UDF_installer/installer/hdbinst
exit
