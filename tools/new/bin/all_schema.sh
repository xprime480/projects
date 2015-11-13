#!/bin/bash

HC=/home/i809989/SAPDevelop/AFL/git/sys/src/AFL/UDF_CORE/hana_content
things=`ls $HC | grep ^...$`
for x in $things
    do schema.sh $x
done
ls $HC
