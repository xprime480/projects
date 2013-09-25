#!/usr/bin/env python3

"""Rhapsody utilities."""

import itertools
import sqlite3 as lite

################################################################
#
def do_one(con, sql, maxrows) :
    """Execute one script and show return MAXROWS ids."""

    con.row_factory = lite.Row
    cur = con.cursor()    
    cur.execute(sql)

    return [x[1]['track_id'] for x in zip(range(maxrows), cur)]

################################################################
#
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

################################################################
#
def get_single_value(con, sql) :
    """Get the first row of the first column returned by the SQL."""

    cur = con.cursor()    
    cur.execute(sql)
    row = cur.fetchone()
    if row :
        return row[0]
    else :
        return None



################################################################
#
def get_next_playlist_id(con) :
    """Get the first unused playlist ID."""

    sql = """
    SELECT max(playlist_id) + 1
      FROM playlist
    ;
    """

    return get_single_value(con, sql)

################################################################
#
def create_playlist_entry(con, plid, name) :
    """Create a new row in the playlist table."""

    sql = """
    INSERT INTO playlist
                (
                  playlist_id,
		  playlist_name,
		  playlist_type,
		  sync_state,
		  last_guid_used
		)
    VALUES      ( ?, ?, 0, 0, 0 )
    ;

    """

    return do_update(con, sql, [(plid, name)])

################################################################
#
def create_playlist_tracks(con, plid) :
    """Create slots for playlist tracks."""

    sql = """
    INSERT INTO playlist_track
                (
                  playlist_id,
		  sequence
		)
    VALUES      ( ?, ? )
    ;

    """

    data = list(zip(itertools.repeat(plid), range(1, 1+25)))
    
    return do_update(con, sql, data)

################################################################
#
def create_playlist(con, name) :
    """Create a new playlist with slots for 25 songs."""

    plid = get_next_playlist_id(con)
    if not plid :
        return None

    n = create_playlist_entry(con, plid, name)
    if n < 1 :
        return None
    create_playlist_tracks(con, plid)

    return plid

################################################################
#
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
        plid = get_single_value(con, sql)
        if plid :
            return plid
    else :
        return None

    if create :
        return create_playlist(con, name)

    return None
    
################################################################
#
def do_update(con, sql, data) :
    """Run update SQL and return number of rows affected."""

    before = con.total_changes
    cur = con.cursor()
    cur.executemany(sql, data)
    con.commit()
    after = con.total_changes
    return (after - before)
