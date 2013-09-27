#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import argparse
import itertools
import random
import sqlite3 as lite
import sys

import rhapdb
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
        with rhapdb.RhapsodyDb(args.db) as db :
            songs = []
            fn = lambda x : random.randint(1, 100) == 1
            for x in args.scripts :
                more = db.get_songs(fn)
                songs.extend(more)
            random.shuffle(songs)

            ids = [x.get_id() for x in songs][:25]

            fn = lambda x : args.playlist == x.get_name()
            playlists = db.get_playlists(fn)

            if len(playlists) == 0 :
                if True :
                    playlist = rhapdb.RhapsodyPlaylist()
                    playlist.set_name(args.playlist)
                    plid   = db.add_playlist(playlist)
                    if not plid :
                        print('No playlist found or created')
                        return 1
            else :
                playlist = playlists[0]

            update = playlist.set_tracks(ids)
            print(update, 'rows were updated.')

    except lite.Error as e:
        print("(2) Error %s:" % e)
        return 1

    return 0

if __name__ == '__main__' :
    sys.exit(main())
