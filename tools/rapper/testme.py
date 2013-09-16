#!/usr/bin/python
# -*- coding: utf-8 -*-

import sqlite3 as lite
import sys

def dump(con, sql, max_ids) :
    cur = con.cursor()    
    cur.execute(sql)
    while True :
        try :
            row = cur.fetchone()
            if row == None :
                break
            print "%06d %35s %35s" % (row[0], row[1], row[2])
        except lite.Error, e: 
            print "(1) Error %s:" % e.args[0]

def merge_results(con, sqlfiles) :
    try:
        for arg in sqlfiles :
            try :
                with open(arg) as f : 
                    sql = ''.join(f.readlines())
                    dump(con, sql, 25)
            except IOError, e:
                print "(3) Error %s:" % e
    except lite.Error, e:
        print "(2) Error %s:" % e

if __name__ == '__main__' :
    try:
        with lite.connect('local3.seb') as con :
            con.text_factory = str
            ids    = merge_results(con, sys.argv[1:])
    except lite.Error, e:
        print "(2) Error %s:" % e
        sys.exit(1)

