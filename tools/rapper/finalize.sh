#!/usr/bin/bash

sqlite3 -init ${HOME}/.sqliterc ${DST} <<EOF
.read ordering.sql
.read temp.sql
.read temp7.sql
EOF