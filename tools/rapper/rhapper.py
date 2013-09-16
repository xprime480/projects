#!/usr/bin/python
# -*- coding: utf-8 -*-

import sqlite3 as lite
import sys

def get_ids(con, sql, max_ids) :
    cur = con.cursor()    
    cur.execute(sql)
    artist_track = {}
    while len(artist_track) < max_ids :
        try :
            row = cur.fetchone()
            if row == None :
                break
            artist_track[row[1]] = row[0]
        except lite.Error, e: 
            print "(1) Error %s:" % e.args[0]

    return artist_track.values()

def merge_results(con, sqlfiles) :
    results = []
    try:
        for arg in sqlfiles :
            try :
                with open(arg) as f : 
                    sql = ''.join(f.readlines())
                    tracks = get_ids(con, sql, 25)
                    results.extend(tracks)
            except IOError, e:
                print "(3) Error %s:" % e
    except lite.Error, e:
        print "(2) Error %s:" % e

    return results

def to_script(ids, playlistid) :
    size = len(ids)
    template = "UPDATE playlist_track SET track_id = %d WHERE sequence = %d AND playlist_id = %d;"
    return '\n'.join([template % (ids[x], x+1, playlistid) for x in xrange(size)])

def run_script(con, script) :
    try:
        before = con.total_changes
        cur = con.cursor()
        con.commit()
        after = con.total_changes
        print "%d rows updated" % (after - before)
    except lite.Error, e:
        print "(4) Error %s:" % e

if __name__ == '__main__' :
    try:
        with lite.connect('local3.seb') as con :
            ids    = merge_results(con, sys.argv[1:])
            script = to_script(ids, 5814)
            run_script(con, script)
    except lite.Error, e:
        print "(2) Error %s:" % e
        sys.exit(1)

