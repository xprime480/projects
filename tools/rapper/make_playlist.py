#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import argparse
import datetime
import random
import sys

import playlist_maker
import rhapdb

################################################################
#
def old_songs(tracks) :
    """Get all previously played songs in random order."""

    matches = [t for t in tracks if t.get_play_count() > 0]
    random.shuffle(matches) 

    return matches

################################################################
#
def cleanup(main, items) :
    """Remove some items from a list."""

    for item in items :
        main.remove(item)

################################################################
#
def main() :
    """Run the top level functionality."""

    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--db",
        help="name of the database to open",
        default='temp.seb',
        nargs='?'
    )
    parser.add_argument(
        "--length",
        help="max number of songs to consider",
        default=300,
        nargs='?',
        type=int
    )

    try :
        args = parser.parse_args()
    except IOError as e :
        print (e)
        return 1

    with rhapdb.RhapsodyDb(args.db) as db :
        o = playlist_maker.PlaylistMaker(db, args.length) 
        o.make_order()

    return 0

################################################################
#
if __name__ == '__main__' :
    sys.exit(main())
