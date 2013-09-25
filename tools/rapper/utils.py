#!/usr/bin/env python3

"""Rhapsody utilities."""

import sqlite3 as lite

def do_one(con, sql, maxrows) :
    """Execute one script and show return MAXROWS ids."""

    con.row_factory = lite.Row
    cur = con.cursor()    
    cur.execute(sql)

    return [x[1]['track_id'] for x in zip(range(maxrows), cur)]

def scripts_to_ids(con, sqlfiles, maxrows) :
    """Run the scripts and merge the results of each call."""

    results = []
    try:
        for arg in sqlfiles :
            try :
                with open(arg) as f : 
                    ls  = f.readlines()
                    sql = ''.join(ls)
                    results.extend(do_one(con, sql, maxrows))
            except IOError as e:
                print ("(3) Error %s:" % e)
    except lite.Error as e:
        print ("(2) Error %s:" % e)

    return results

def find_playlist_id(con, name, create=False) :
    """Find a playlist id by name.

    If the playlist does not exist then create it if CREATE is True."""

    sql = """
    SELECT playlist_id
      FROM playlist
     WHERE playlist_name = '%s'
    ;
    """ % (name)

    if name :
        cur = con.cursor()    
        cur.execute(sql)
        row = cur.fetchone()
        if row :
            return row[0]
    else :
        return None

    if create :
        pass

    return None
    

def do_update(con, sql, data) :
    """Run update SQL and return number of rows affected."""

    before = con.total_changes
    cur = con.cursor()
    cur.executemany(sql, data)
    con.commit()
    after = con.total_changes
    return (after - before)
