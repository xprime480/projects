#!/bin/bash

pushd $SRC
hm init
hm build mrproper
hm build -b Optimized dist
$(HOME)/bin/hm/reinstallHDB.sh
cp build/Optimized/install/installer.wrk/lib/installcfg.dtd /home/i809989/SAPDevelop/AFL/git/sys/src/build/Optimized/gen/product_specific_afls/UDF_installer/installer/packages/installcfg.dtd
$(HOME)/bin/hm/installAFL.sh Optimized
$(HOME)/bin/hm/installPythonTests.sh 
popd
