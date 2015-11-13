# .bashrc

# User specific aliases and functions

# Source global definitions
if [ -f /etc/bashrc ]; then
    . /etc/bashrc
fi

# version control definitions
if [ -f ${HOME}/.vcinit ]; then
    source ${HOME}/.vcinit
fi

# User specific environment and startup programs

if [ -f ${HOME}/.pyinit ]; then
    source ${HOME}/.pyinit
fi

if [ -f ~/.bashalias ]; then
    . ~/.bashalias
fi

HN=`hostname | sed -e 's/\..*$//'`
LOCALRC=.bashrc.${HN}
if [ -e ${LOCALRC} ]; then
    source ${LOCALRC}
fi

if [ -e ${HOME}/.dbinit ]; then
    source ${HOME}/.dbinit
fi 


export LC_ALL=C
export HISTCONTROL=ignoreboth
#export PS1='\u@\h: \W \$ '

# skip this on non -X windows
#
if [ \! -z "${DISPLAY}" ]; then
    #blue
fi

export http_proxy=proxy.phl.sap.corp:8080
#export http_proxy=usscfblue1.scf.sap.corp:8083

export SAP_RETRIEVAL_PATH=/usr/sap/MD1/02/HDB02/llbpal25

# happy make (installed on 2015-10-05 15:37:48.824021)
export HAPPY_MAKE_HOME=/home/i809989/.HappyMake
export HAPPY_MAKE_CACHE="${HAPPY_MAKE_HOME}/cache"
export PATH=/home/i809989/.HappyMake/bin:"${PATH}"
