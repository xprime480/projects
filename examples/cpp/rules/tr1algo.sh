#!/bin/bash

file=$rgv_$(date "+%s").tcl
./tr1algo $@ > $file
chmod 755 $file
./$file
