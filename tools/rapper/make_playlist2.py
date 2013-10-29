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

        five_star_list = [
            self.pick_by_stars(5),
            self.randomize,
            self.remove_duplicate_artists,
        ]

        new_list = [
            self.pick_new,
            self.randomize,
            self.truncate(50),
            self.remove_duplicate_artists,
            self.truncate(25)
        ]

        basic_list = [
            self.least_recently_played,
            self.truncate(100),
            self.randomize,
            self.remove_duplicate_artists,
            self.truncate(25)
        ]

        old_by_stars = [None] * 6

        for x in range(6) :
            old_by_stars[x] = [self.pick_by_stars(x)]
            old_by_stars[x].extend(basic_list[:])

        seldom_played = [self.pick_by_playcount(1, 5)]
        seldom_played.extend(basic_list[:])

        #
        # get (almost) all 5 stars.  
        #
        self.extend_playlist(*five_star_list)

        # keep looping until the list is long enough
        #
        while len(self.tracks) > 0 and len(self.playlist) < self.length :
            
            #
            # get some new tracks
            #
            self.extend_playlist(*new_list)
            #self.add_to_list(self.new_songs(), 50, 25)

            #
            # get oldest
            #
            for x in [5, 4, 3, 2] :
                self.extend_playlist(*old_by_stars[x])
                #self.add_to_list(self.get_oldest_by_stars(x), 100, 25)
                
            #
            # get oldest rarely played songs
            #
            #self.extend_playlist(*seldom_played)
            #self.add_to_list(self.get_songs_by_playcount(1, 5, lambda t : t.get_last_played()), 100, 25)

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
