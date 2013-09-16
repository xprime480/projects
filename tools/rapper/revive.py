#!/usr/bin/python
# -*- coding: utf-8 -*-

import sqlite3 as lite
import sys

def get_ids(con, sql) :
    cur = con.cursor()    
    cur.execute(sql)
    ids = []
    while True :
        try :
            row = cur.fetchone()
            if row == None :
                break
            ids.append(row[0])
        except lite.Error, e: 
            print "(1) Error %s:" % e.args[0]

    return ids

def merge_results(con, sqlfiles) :
    results = []
    try:
        for arg in sqlfiles :
            try :
                with open(arg) as f : 
                    sql = ''.join(f.readlines())
                    tracks = get_ids(con, sql)
                    results.extend(tracks)
            except IOError, e:
                print "(3) Error %s:" % e
    except lite.Error, e:
        print "(2) Error %s:" % e

    return results

def run_script(con, script, ids) :
    try:
        before = con.total_changes
        cur = con.cursor()
        lines = [script % (id,) for id in ids ]
        cur.executescript('\n'.join(lines))
        con.commit()
        after = con.total_changes
        print "%d rows updated" % (after - before)
    except lite.ProgrammingError, e:
        print "(5) Error %s:" % e
    except lite.Error, e:
        print "(4) Error %s:" % e

if __name__ == '__main__' :
    try:
        with lite.connect('local3.seb') as con :
            ids    = merge_results(con, sys.argv[1:])
            t1 = "UPDATE track   SET in_library = 1    WHERE track_id = %d;"
            run_script(con, t1, ids)
            t2 = "UPDATE ratings SET ratings_value = 1 WHERE ratings_local_track_id = %d;"
            run_script(con, t2, ids)
    except lite.Error, e:
        print "(2) Error %s:" % e
        sys.exit(1)

