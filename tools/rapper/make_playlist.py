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
        self.filter_by_last_played_date()

    ################################################################
    #
    def filter_by_last_played_date(self) :
        """Eliminate songs that were played too recently."""

        max_days = [0, 180, 90, 600, 10, 0]
        now = datetime.datetime.now()
        def fn(t) :
            c = t.get_play_count()
            if c < 5 :
                return True

            r = t.get_rating()
            a = (now - t.get_last_played()).days

            return a >= max_days[r]

        self.tracks = [t for t in self.tracks if fn(t)]

    ################################################################
    #
    def generate_playlist(self) :
        """Make a playlist."""

        # get some of the best tracks
        #
        for x in [5, 4] :
            self.add_to_list(self.get_songs_by_stars(x), 5)

        # keep looping until the list is long enough
        #
        while len(self.tracks) > 0 and len(self.playlist) < self.length :
            #
            # get some tracks from each level of stars that haven't 
            # been played in a while
            #
            for x in range(5,0,-1) :
                self.add_to_list(self.get_oldest_by_stars(x), 5)

            #
            # try some new songs
            #
            self.add_to_list(self.new_songs(), 25)

            #
            # get some tracks from each level of stars 
            #
            for x in range(5,0,-1) :
                self.add_to_list(self.get_songs_by_stars(x), 5)

            #self.add_to_list(self.get_songs_by_playcount(1, 5), 10)

        size = len(self.playlist)
        jitter  = [(x, x + random.randint(1,25)) for x in range(size)]
        jitter.sort(key=lambda x : x[1])
        temp = [self.playlist[x[0]] for x in jitter]
        self.playlist = temp

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
