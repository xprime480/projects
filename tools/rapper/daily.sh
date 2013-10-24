#!/usr/bin/bash

SRC=/cygdrive/c/Users/I809989/AppData/Roaming/Real/rhapsody/1.sqlite/local3.seb
DST=./temp.seb
BAK=./gold.seb
LEN=200

cp ${SRC} ${DST}
rm -f ${BAK}
cp -p ${DST} ${BAK}

SCRIPTS='./temp.py ./make_playlist2.py'

for s in ${SCRIPTS} ; do
    if [ -x $s ]; then
	$s --db ${DST} --length=${LEN}
    fi
done

cp ${DST} ${SRC}

sqlite3 -init ${HOME}/.sqliterc ${DST} <<EOF
.read ordering.sql
.read temp.sql
EOF
