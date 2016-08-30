#!/bin/bash

grep -v '^-*$' $1 |\
	grep -v 'Dynamic List Display' |\
	grep -v '^Properties' |\
	grep -v '|INDEX|' |\
	cut -d'|' -f3- |\
	tr -d ',' |\
	tr -d ' ' |\
	sed -e s'/|$//' |\
	tr '|' '\011'

