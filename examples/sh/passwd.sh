#!/bin/bash

stty -echo
passwd=xxx
other=xxx
read -p "Password: " passwd
stty echo
echo ""
read -p "Something Else: " other

echo $other
