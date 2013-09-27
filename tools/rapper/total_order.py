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
def get_oldest_by_stars(stars) :
    """Create a function that filters on rating and sorts by playdate."""

    def fn(tracks) :
        filterfn = lambda x : x.is_in_library() and x.get_rating() == stars
        keyfn    = lambda x : x.get_last_played()
        matches = filter_and_sort(tracks, filterfn, keyfn, False)

        return matches

    return fn

################################################################
#
def get_songs_by_stars(stars) :
    """Create a function that filters on rating and sorts by playdate."""

    def fn(tracks) :
        filterfn = lambda x : x.is_in_library() and x.get_rating() == stars
        matches = [t for t in tracks if filterfn(t)]
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
def new_songs(tracks) :
    """Randomly permute the songs."""

    matches = [t for t in tracks if t.get_play_count() == 0]
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
def apply_artist_correction(tracks) :
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
def update_order(order, tracks, fn, count) :
    temp = fn(tracks)
    apply_artist_correction(temp)
    temp = temp[:count]
    order.extend(temp)
    for s in temp :
        tracks.remove(s)

################################################################
#
def make_total_order(db, length) :
    """Assign every track in the library a rank."""

    tracks = db.get_songs(lambda x : x.is_in_library())
    for track in tracks :
        track.set_comment('')

    order = []

    while len(tracks) > 0 and len(order) < length :
        for x in range(5,0,-1) :
            update_order(order, tracks, get_oldest_by_stars(x), 5)

        update_order(order, tracks, new_songs, 25)

        for x in range(5,0,-1) :
            update_order(order, tracks, get_songs_by_stars(x), 5)

        

    size = len(order)
    for x in range(size) :
        order[x].set_comment('%05d ??' % (size-x))

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
        make_total_order(db, args.length)

    return 0

################################################################
#
if __name__ == '__main__' :
    sys.exit(main())
