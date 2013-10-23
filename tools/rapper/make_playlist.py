#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import argparse
import sys

import playlist_maker
import rhapdb

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
