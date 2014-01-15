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

        basic_list = [
            self.least_recently_played,
            self.truncate(25, 0.25),
            self.randomize,
            self.remove_duplicate_artists,
            self.least_recently_played_stochastic,
            self.truncate(5)
        ]

        pickers = [None] * 6
        for x in range(6) :
            pickers[x] = [self.pick_by_stars(x)]
            pickers[x].extend(basic_list[:])

        temp = [
            self.pick_new,
        ]
        temp.extend(basic_list[:])
        pickers.append(temp)

        testlen = 0
        while len(self.tracks) > 0 and len(self.playlist) < self.length :
            self.extend_playlist(*pickers[0])
            self.extend_playlist(*pickers[5])
            if len(self.playlist) == testlen :
                break
            i = random.randint(1,4)
            self.extend_playlist(*pickers[i])
            testlen = len(self.playlist)

        ixs = list(range(1,5))
        while len(self.tracks) > 0 and len(self.playlist) < self.length :
            random.shuffle(ixs)
            for ix in ixs :
                self.extend_playlist(*pickers[ix])

        if None :
            random.shuffle(pickers)
            for p in pickers[:-2] :
                self.extend_playlist(*p)

        if None :
            a,b = pickers[0],pickers[1:]
            random.shuffle(b)
            pickers = b[:]
            pickers.append(a)
            self.extend_playlist(*a)

    ################################################################
    #
    def least_recently_played_stochastic2(self, tracks) :
        def keyfn(t) :
            score = t.get_age()
            stars = t.get_rating()
            if stars == 0 :
                score = score * 500
            else :
                score = score * 2 * (3.0 ** stars)

            return random.uniform(0, score)

        tracks.sort(key=keyfn, reverse=True)
        return tracks

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
