#!/bin/sh
export PS1='\[\033]0;hdbdevuser@lu226919:$(__git_ps1 " %s") \w\007\033[38m\]\u@\h:\[\033[02;34m\]\w\[\033[01;31m\]$(__git_ps1 " (%s)")\[\033[30m\]>\[\033[00m\] '
echo -en "\033]0;hdbdevuser@lu226919\007"
export GREP_OPTIONS='--color=auto'
export REM_DEFAULT_BROWSER=firefox
export OWN=/home/hdbdevuser/AFL
export SRC=$OWN/sys/src

cd $SRC
