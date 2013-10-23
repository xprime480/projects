#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import argparse
import datetime
import sys

import playlist_maker
import rhapdb

################################################################
#
class LocalPlaylistMaker(playlist_maker.PlaylistMaker) :
    def __init__(self, db, length) :
        super().__init__(db, length)

    def local_init(self) :
        self.filter_by_last_played_date()

    def filter_by_last_played_date(self) :
        """Elimnate songs that were played too recently."""

        max_days = [0, 180, 90, 600, 10, 0]
        now = datetime.datetime.now()
        def fn(t) :
            c = t.get_play_count()
            if c < 5 :
                return True

            r = t.get_rating()
            a = (now - t.get_last_played()).days

            return a >= max_days[r]

        x = [t for t in self.tracks if fn(t)]
        self.tracks = x


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
        o = LocalPlaylistMaker(db, args.length) 
        o.make_order()

    return 0

################################################################
#
if __name__ == '__main__' :
    sys.exit(main())
