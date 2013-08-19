#!/bin/bash

n=${1:-5}
low=$(($n * $(($n + 1)) / 2))
high=$(($low+20))


./countem $low $high $n 1 $high | cut -d' ' -f 2 | fmt -1000 | tr ' ' ','
