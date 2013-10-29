#!/usr/bin/env python3

import random

from apply_rules import *
import rhapdb

################################################################
#
def filter_and_sort(items, filterfn, keyfn=None, reverse=False) :
    """filter some items from a list and sort the rest."""

    temp = [i for i in items if filterfn(i)]
    if keyfn :
        temp.sort(key=keyfn, reverse=reverse)
    else :
        random.shuffle(temp)
    return temp

################################################################
#
class PlaylistMaker(object) :
    """Provide methods to Create a playlist of tracks."""

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

        self.tracks = self.db.get_songs(lambda x : True)
        for track in self.tracks :
            track.set_comment('')
        self.tracks = self.db.get_songs(lambda x : x.is_in_library())

        self.local_init()

        self.playlist = []

        print (len(self.tracks), 'eligible tracks in library.')

    ################################################################
    #
    def make_playlist(self) :
        """Make a playlist."""
        
        self.generate_playlist()

        size = len(self.playlist)
        for i in range(size) :
            self.playlist[i].set_comment('%05d' % (size-i))

    ################################################################
    #
    def generate_playlist(self) :
        """Generate the entries for the list."""
        
        self.add_to_list(lambda : self.tracks, len(self.tracks))

    ################################################################
    #
    def add_to_list(self, fn, gencount, finalcount=None) :
        """Run the selector function and add results.

        FN         is a callable that returns a list of tracks.
        GENCOUNT   is how many songs to generate
        FINALCOUNT is the desired size of the final list.

        A correction function is run on the results returned by FN.
        If a given artist has multiple songs in the list, the second
        and subsequent tracks are moved to the end of the line in
        case the list is shortened to COUNT."""

        temp = fn()
        temp = temp[:gencount]
        random.shuffle(temp)
        self.apply_artist_correction(temp)
        if finalcount :
            temp = temp[:finalcount]
        self.playlist.extend(temp)
        for s in temp :
            self.tracks.remove(s)

    def extend_playlist(self, *rules) :
        t = apply_rules(self.tracks, *rules)
        self.playlist.extend(t)
        for s in t :
            self.tracks.remove(s)

    ################################################################
    #
    def randomize(self, tracks) :
        random.shuffle(tracks)
        return tracks

    ################################################################
    #
    def least_recently_played(self, tracks) :
        tracks.sort(key=lambda x : x.get_last_played())
        return tracks

    ################################################################
    #
    def apply_artist_correction(self, tracks) :
        """Move duplicate tracks by a given artist to the end of the list."""
        
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

        return tracks

    ################################################################
    #
    def remove_duplicate_artists(self, tracks) :
        artists_seen = []
        keep         = []

        for track in tracks :
            a = track.get_artist()
            if a not in artists_seen :
                artists_seen.append(a)
                keep.append(track)

        return keep

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

        def fn() :
            filterfn = lambda x : x.get_play_count() == 0
            keyfn    = None
            matches = filter_and_sort(self.tracks, filterfn, keyfn, False)

            return matches

        return fn

    def pick_new(self, tracks) :
        temp = [t for t in tracks if t.get_play_count() == 0]
        return temp

    ################################################################
    #
    def truncate(self, count) :
        def fn(tracks) :
            temp = tracks[:count]
            return temp
            
        return fn

    ################################################################
    #
    def get_songs_by_stars(self, stars) :
        """Create a function that filters on rating and sorts by playdate."""

        def fn() :
            filterfn = lambda x : x.is_in_library() and x.get_rating() == stars
            keyfn    = None
            matches = filter_and_sort(self.tracks, filterfn, keyfn, False)

            return matches

        return fn

    def pick_by_stars(self, stars) :
        def fn(tracks) :
            return [t for t in tracks if t.get_rating() == stars]
        return fn

    ################################################################
    #
    def get_songs_by_playcount(self, min_count, max_count, keyfn=None) :
        """Create a function that filters on playcount."""

        def fn() :
            filterfn = lambda x : x.is_in_library() and min_count <= x.get_play_count() <= max_count
            matches = filter_and_sort(self.tracks, filterfn, keyfn, False)

            return matches

        return fn

    def pick_by_playcount(self, min_count, max_count) :
        def fn(tracks) :
            temp = [
                t for t in tracks
                if min_count <= t.get_play_count() <= max_count
            ]
            return temp

        return fn

    ################################################################
    #
    def local_init(self) :
        pass
        

if __name__ == '__main__' :
    with rhapdb.RhapsodyDb('temp.seb') as db :
        o = PlaylistMaker(db, 250) 
        o.make_playlist()
    
