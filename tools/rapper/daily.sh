#!/usr/bin/bash

SRC=/cygdrive/c/Users/I809989/AppData/Roaming/Real/rhapsody/1.sqlite/local3.seb
DST=./temp.seb
BAK=./gold.seb
LEN=200

cp ${SRC} ${DST}
cp -p ${DST} ${BAK}
if [ -x temp.py ]; then
    ./temp.py --db ${DST}
fi
if [ -x ./total_order.py ]; then
    ./make_playlist.py --db ${DST} --length=${LEN}
fi

cp ${DST} ${SRC}

sqlite3 -init ${HOME}/.sqliterc ${DST} <<EOF
.read ordering.sql
EOF
