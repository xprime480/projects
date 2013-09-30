#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import argparse
import random
import sys

import rhapdb

################################################################
#
def filter_and_sort(items, filterfn, keyfn, reverse=False) :
    """filter some items from a list and sort the rest."""

    temp = [i for i in items if filterfn(i)]
    temp.sort(key=keyfn, reverse=reverse)
    return temp

################################################################
#
class PartialOrder(object) :
    """Provide methods to Create a partial order of tracks."""

    ################################################################
    #
    def __init__(self, db, length) :
        """Create the object."""

        self.db     = db
        self.length = length
        self.reset()

    ################################################################
    #
    def reset(self) :
        """Return to the initial condition."""

        self.tracks = self.db.get_songs(lambda x : x.is_in_library())
        for track in self.tracks :
            track.set_comment('')

        self.order = []
        

    ################################################################
    #
    def make_order(self) :
        """Assign every track in the library a rank."""

        while len(self.tracks) > 0 and len(self.order) < self.length :
            for x in range(5,0,-1) :
                self.add_to_list(self.get_oldest_by_stars(x), 5)

            self.add_to_list(self.new_songs, 25)

            for x in range(5,0,-1) :
                self.add_to_list(self.get_songs_by_stars(x), 5)

                
        size = len(self.order)
        jitter  = [(x, x + random.randint(1,25)) for x in range(size)]
        jitter.sort(key=lambda x : x[1])
        for x in range(size) :
            self.order[jitter[x][0]].set_comment('%05d ??' % (size-x))


    ################################################################
    #
    def add_to_list(self, fn, count) :
        temp = fn()
        self.apply_artist_correction(temp)
        temp = temp[:count]
        self.order.extend(temp)
        for s in temp :
            self.tracks.remove(s)

    ################################################################
    #
    def apply_artist_correction(self, tracks) :
        artists_seen   = []
        tracks_at_front = []
        tracks_at_back  = []

        for track in tracks :
            a = track.get_artist()
            if a in artists_seen :
                tracks_at_back.append(track)
            else :
                tracks_at_front.append(track)
                artists_seen.append(a)

        tracks_at_front.extend(tracks_at_back)
        tracks[:] = tracks_at_front

    ################################################################
    #
    def get_oldest_by_stars(self, stars) :
        """Create a function that filters on rating and sorts by playdate."""

        def fn() :
            filterfn = lambda x : x.is_in_library() and x.get_rating() == stars
            keyfn    = lambda x : x.get_last_played()
            matches = filter_and_sort(self.tracks, filterfn, keyfn, False)

            return matches

        return fn

    ################################################################
    #
    def new_songs(self) :
        """Select songs that have never been played."""

        matches = [t for t in self.tracks if t.get_play_count() == 0]
        random.shuffle(matches) 

        return matches

    ################################################################
    #
    def get_songs_by_stars(self, stars) :
        """Create a function that filters on rating and sorts by playdate."""

        def fn() :
            filterfn = lambda x : x.is_in_library() and x.get_rating() == stars
            matches = [t for t in self.tracks if filterfn(t)]
            random.shuffle(matches)

            return matches

        return fn

################################################################
#
def old_songs(tracks) :
    """Randomly permute the songs."""

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
        default='local3.seb',
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
        o = PartialOrder(db, args.length) 
        o.make_order()

    return 0

################################################################
#
if __name__ == '__main__' :
    sys.exit(main())
