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
class LocalPlaylistMaker(playlist_maker.PlaylistMaker) :
    """Make a playlist by our rules."""

    ################################################################
    #
    def __init__(self, db, length) :
        super().__init__(db, length)

    ################################################################
    #
    def local_init(self) :
        pass

    ################################################################
    #
    def generate_playlist(self) :
        """Make a playlist."""

        #
        # get all 5 stars.  
        #
        self.add_to_list(self.get_songs_by_stars(5), len(self.tracks))

        # keep looping until the list is long enough
        #
        while len(self.tracks) > 0 and len(self.playlist) < self.length :
            #
            # get oldest 4 and 3 stars
            #
            for x in [4, 3] :
                self.add_to_list(self.get_oldest_by_stars(x), 100, 25)
                
            #
            # get some new tracks
            #
            self.add_to_list(self.new_songs(), 25)

            #
            # get oldest rarely played songs
            #
            self.add_to_list(self.get_songs_by_playcount(1, 5, lambda t : t.get_last_played()), 100, 25)

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
        o.make_playlist()

    return 0

################################################################
#
if __name__ == '__main__' :
    sys.exit(main())
