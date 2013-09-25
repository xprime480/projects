#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import argparse
import itertools
import random
import sqlite3 as lite
import sys

import utils

def update_playlist(con, ids, playlistid) :
    """Update the playlist data."""

    
    sql = """
    UPDATE playlist_track
       SET track_id = ?
     WHERE sequence = ?
       AND playlist_id = ?
    ;
    """

    data = list(zip(
        ids, 
        range(1, 1+len(ids)), 
        itertools.repeat(playlistid)
    ))

    return utils.do_update(con, sql, data)

def main() :
    """Run the top level functionality."""

    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--db",
        help="name of the database to open", 
        default='local3.seb',
        nargs='?'
    )
    parser.add_argument(
        "--playlist",
        help="name of the playlist to create.", 
        nargs='?',
    )
    parser.add_argument(
        "scripts",
        help="names of scripts to run", 
        nargs=argparse.REMAINDER
    )

    try :
        args = parser.parse_args()
    except IOError as e :
        print (e)
        return 1

    try:
        with lite.connect(args.db) as con :
            ids    = utils.scripts_to_ids(con, args.scripts, 25)
            random.shuffle(ids)

            plid   = utils.find_playlist_id(con, args.playlist, True)
            if not plid :
                print('No playlist found or created')
                return 1

            update = update_playlist(con, ids, plid)
            print(update, 'rows were updated.')

    except lite.Error as e:
        print("(2) Error %s:" % e)
        return 1

    return 0

if __name__ == '__main__' :
    sys.exit(main())
