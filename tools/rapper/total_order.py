#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import argparse
import sys

import rhapdb

def main() :
    """Run the top level functionality."""

    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--db",
        help="name of the database to open", 
        default='local3.seb',
        nargs='?'
    )

    try :
        args = parser.parse_args()
    except IOError as e :
        print (e)
        return 1

    with rhapdb.RhapsodyDb(args.db) as db :
        songs = db.get_songs(lambda x : x.is_in_library())

        old_songs = []
        new_songs = []
        for song in songs :
            if song.get_play_count() > 0 and song.get_last_played() is not None :
                old_songs.append(song)
            else :
                new_songs.append(song)

        lpd    = [(s, s.get_last_played()) for s in old_songs]
        oldest = min([x[1] for x in lpd])
        print ([x for x in lpd if x[1] == oldest])

    return 0

if __name__ == '__main__' :
    sys.exit(main())
