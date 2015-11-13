#!/bin/bash

LIST=`git names | grep procedure`
for NAME in $LIST; do
    DIR=`echo $NAME | sed -e "s|/sap/is/.*|/sap/is|"`
    PKG=`echo $NAME | sed -e "s|.*/sap/is/\(.*\)\.procedure|\1|"`
    PROC=`echo $NAME | sed -e "s|.*/\(.*\)\.procedure|\1|"`
    CLIENT=`echo $DIR | sed -e "s|^.*/\(.*\)/sap/is|\1|"`
    echo ""
    echo "callers of $PKG in client $CLIENT:"
    find $DIR -name '*.procedure' -exec grep -qi "call.*\b$PROC\b" {} \; -print
done
