#!/usr/bin/bash

for x in `ls *.csv`; do
    base=`basename $x .csv`
    text=${base}.txt
    head -1 ${x} | tr ',' '\012' | nl -ba > ${text}
done

