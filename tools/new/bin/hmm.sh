#!/bin/bash

if [ "$1" = "short" ]; then
    sudo -S rm -rf /usr/sap/MD1/HDB02/exe/testscripts < ~/.spw
    hm build -b Optimized dist
    $HOME/bin/hm/installPythonTests.sh
    exit 0
fi

if [ "$1" = "full" ]; then
    sudo -S rm -rf /usr/sap/MD1/HDB02/exe/testscripts < ~/.spw
    hm build mrproper
    hm build -b Optimized dist
    $HOME/bin/hm/reinstallHDB.sh
    $HOME/bin/hm/installAFL.sh Optimized
    $HOME/bin/hm/installPythonTests.sh
    exit 0
fi

if [ \! -z "$1" ]; then
    echo "Don't understand $@"
    exit 1
fi

PS3="Select an action: "
COMMAND_LIST='init clean build instHDB instAFL instPy finished'

select CMD in $COMMAND_LIST; do
    case $CMD in
	init)
	    hm init
	    ;;
	clean)
	    hm build mrproper
	    ;;
	build)
	    hm build -b Optimized dist
	    ;;
	instHDB)
	    $HOME/bin/hm/reinstallHDB.sh
	    ;;
	instAFL)
	    $HOME/bin/hm/installAFL.sh Optimized
	    ;;
	instPy)
	    $HOME/bin/hm/installPythonTests.sh
	    ;;
	finished)
	    exit 0
	    ;;
	*)
	    echo "Don't understand"
	    ;;
    esac
done