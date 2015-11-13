#!/bin/bash

find ~/SAPDevelop/AFL/git/sys/src/nutest/testscripts/UDF_CORE/UDF_DDF_RD1/ -name properties.ini -exec grep -Eqi "\b${1}\b" {} \; -print
