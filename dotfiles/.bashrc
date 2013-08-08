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
export PS1='\u@\h: \W \$ '
