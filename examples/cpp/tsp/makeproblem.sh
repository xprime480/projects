#!/bin/bash

for i in {1..200}; do
    echo $(($RANDOM % 1000)) $(($RANDOM % 1000))
done
