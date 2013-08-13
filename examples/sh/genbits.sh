#!/bin/bash

for (( x=1 ; $x <= 25 ; x=$(($x+1)) )); do
	echo $((${RANDOM} % 2))
done | fmt -11
