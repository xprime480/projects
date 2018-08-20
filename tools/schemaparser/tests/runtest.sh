#!/bin/bash

if [ -f 20out.csv ]; then
    rm 20out.csv
fi
../datagen.py 20gauss.dgs
if [ \! -f 20out.csv ]; then
    echo '20out.csv: Expected output was not generated'
fi
