#!/bin/bash

SERVER_URL=
SYS_NUM=
CLIENT=
USER=
PASSWD=
MAXACTIVECONN=
DBKEY=

#
# read a parameter and make sure that input is not empty
#
function read_input () {
    read $2 -p "Enter $1: " temp
    if [ -z "$temp" ]; then
	echo "Nothing entered for $1"
	exit 1
    fi
}

#
# get the parameters
#
clear
echo Enter the connection parameters:

read_input "Server URL"                   ; SERVER_URL=$temp
read_input "System Number"                ; SYS_NUM=$temp
read_input "Client Number"                ; CLIENT=$temp
read_input "User Name"                    ; USER=$temp
read_input "Password" -s ; echo ""        ; PASSWD=$temp
read_input "Max Active Connections"       ; MAXACTIVECONN=$temp
read_input "DB Key (SystemID:Client Num)" ; DBKEY=$temp

echo Valid Inputs.
