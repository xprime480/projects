#!/bin/bash

if [ -f 20out.csv ]; then
    rm 20out.csv
fi
../datagen.py 20gauss.dgs
