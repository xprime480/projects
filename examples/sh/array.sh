#!/bin/bash

declare -a Y=(`ls *.sh`)
Z=0
while [ $Z -lt 10 ]; do
    T=$(($RANDOM % ${#Y[@]}))
    echo ${Y[$T]}
    Z=$(($Z + 1))
done
