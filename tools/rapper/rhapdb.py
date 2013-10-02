#!/usr/bin/env python3

"""Interface to the Rhapsody SQLite database."""

import datetime
import sqlite3 as lite

import utils


################################################################
#
class RhapsodySong(object) :
    """A Song as represented the Rhapsody database."""

    def __init__(self, song) :
        """Initialize an instance."""

        self.song   = dict(song)
        self.rating = None
        self.clean  = True

    def add_rating(self, rating) :
        self.rating = dict(rating)

    def dump(self) :
        t = { 'song' : self.song, 'rating' : self.rating }
        return str(t)

    def get_id(self) :
        return self.song['TRACK_ID']

    def get_title(self) :
        return self.song['TRACK_NAME']

    def get_artist(self) :
        return self.song['ARTIST_NAME']

    def get_rating(self) :
        if not self.rating :
            return 0
        return self.rating['RATINGS_VALUE']
        
    def get_last_played(self) :
        t = self.song['LAST_PLAYED']

        if not t :
            t = '19600117T121500'

        return datetime.datetime.strptime(t, '%Y%m%dT%H%M%S')

    def get_play_count(self) :
        t = self.song['PLAY_COUNT']
        if not t :
            t = 0
        return t

    def is_in_library(self) :
        return self.song['IN_LIBRARY'] == 1

    def is_dirty(self) :
        return self.clean == False

    def get_comment(self) :
        t = self.song['COMMENTS']
        if not t :
            t = ''
        return t

    def set_comment(self, comment) :
        new_comment = str(comment)
        old_comment = self.get_comment()

        if new_comment != old_comment :
            self.song['COMMENTS'] = new_comment
            self.clean = False

    def __repr__(self) :
        try :
            a = self.get_artist()
            t = self.get_title()

            return '[%s] %s' % ( 
                bytes(a, 'ascii').decode('ascii', errors='replace')
                , 
                bytes(t, 'ascii').decode('ascii', errors='replace')
            )
        except UnicodeEncodeError :
            return '? ?'

    def str(self) :
        return self.__repr__()

################################################################
#
class RhapsodyPlaylist(object) :
    """A playlist as represented in the Rhapsody database."""

    _keys = [
        'PLAYLIST_ID', 
        'PLAYLIST_NAME', 
        'RHAPSODY_PLAYLIST_ID', 
        'LAST_GUID_USED', 
        'PLAYLIST_TYPE', 
        'SYNC_STATE', 
        'AUTOPLAYLIST_USE_LOCAL', 
        'AUTOPLAYLIST_USE_STREAM', 
        'AUTOPLAYLIST_SORT_COLUMN', 
        'AUTOPLAYLIST_SORT_ORDER', 
        'AUTOPLAYLIST_LENGTH_UNIT', 
        'AUTOPLAYLIST_LENGTH_VALUE', 
        'AUTOPLAYLIST_ENABLE_CONDITIONS', 
        'AUTOPLAYLIST_CONDITION_LOGIC', 
        'AUTOPLAYLIST_V2_SERIALIZED', 
        'MIMETYPES',
        'HASH'
    ]

    def __init__(self, info=None) :

        if info :
            self.info = dict(info)
        else :
            self.info = dict([(k, None) for k in self._keys])

        self.tracks = []
        self.clean  = True

    def get_id(self) :
        return self.info['PLAYLIST_ID']

    def set_id(self, id) :
        self.info['PLAYLIST_ID'] = id
        self.clean = False

    def get_name(self) :
        return self.info['PLAYLIST_NAME']

    def set_name(self, name) :
        self.info['PLAYLIST_NAME'] = name
        self.clean = False

    def add_track(self, track, from_db=False) :
        t = dict(track)
        t['PLAYLIST_ID'] = self.get_id()
        if not from_db :
            self.clean = False

        self.tracks.append(t)

    def set_tracks(self, tracks) :
        self.tracks = []
        data = zip(range(1,len(tracks)+1), tracks)
        for d in data :
            self.add_track({'TRACK_ID' : d[1], 'SEQUENCE' : d[0] })

        return len(tracks)
            
    def is_dirty(self) :
        return self.clean == False


################################################################
#
class RhapsodyDb(object) :
    """The Rhapsody Database."""

    ################################################################
    #
    def __init__(self, datafile) :
        """Initialize an instance."""

        self.datafile = datafile
        self.con      = None

    ################################################################
    #
    def __enter__(self) :
        """Setup for the with protocol."""

        self.con              = lite.connect(self.datafile)
        self.con.row_factory  = lite.Row
        self.con.text_factory = self.hack_string

        self.get_song_info()
        self.get_playlist_info()

        return self

    ################################################################
    #
    def __exit__(self, type, value, traceback) :
        """Teardown for the with protocol."""

        self.push_comments()

        self.con.close()

    ################################################################
    #
    def get_song_info(self) :
        """Get all songs from the database."""

        sql = """
        SELECT *
          FROM track
         ORDER BY track_id ASC
        ;
        """

        cur = self.con.cursor()
        cur.execute(sql)

        self.songs = dict([(x['TRACK_ID'], RhapsodySong(x)) for x in cur])

        self.get_ratings()

        return len(self.songs)

    ################################################################
    #
    def get_ratings(self) :
        """Get the ratings for songs from the database."""

        sql = """
        SELECT *
          FROM ratings
         ORDER BY ratings_local_track_id ASC
        ;
        """

        cur = self.con.cursor()
        cur.execute(sql)

        for rating in cur :
            song = self.find_song(rating['RATINGS_LOCAL_TRACK_ID'])
            if song :
                song.add_rating(rating)

    ################################################################
    #
    def get_playlist_info(self) :
        """Get playlists from the database."""

        sql = """
        SELECT *
          FROM playlist
         ORDER BY playlist_id ASC
        ;
        """

        cur = self.con.cursor()
        cur.execute(sql)

        t = [(x['PLAYLIST_ID'], RhapsodyPlaylist(x)) for x in cur]
        self.playlists = dict(t)

        self.get_playlist_songs()

        return len(self.playlists)
        
    ################################################################
    #
    def get_playlist_songs(self) :
        """Get the ratings for songs from the database."""

        sql = """
        SELECT *
          FROM playlist_track
         ORDER BY playlist_id ASC, sequence ASC
        ;
        """

        cur = self.con.cursor()
        cur.execute(sql)

        for track in cur :
            playlist = self.find_playlist(track['PLAYLIST_ID'])
            if playlist :
                playlist.add_track(track, True)

    ################################################################
    #
    def hack_string(self, string) :
        """Fix strings however possible."""

        #        try :
        #            return str(string)
        #        except Exception :
        #            pass


        if type(string) == type(b'') :
            return string.decode('ascii', errors='replace')

        raise Exception('Unknown type for <%s>' % (string))

    ################################################################
    #
    def find_song(self, id) :
        """Get a song by ID."""

        return self.songs.get(id)

    ################################################################
    #
    def find_playlist(self, id) :
        """Get a playlist by ID."""

        return self.playlists.get(id)

    ################################################################
    #
    def get_songs(self, pred=lambda x : True) :
        t = [x for x in self.songs.items()]
        return [y[1] for y in t if pred(y[1])]

    ################################################################
    #
    def get_playlists(self, pred=lambda x : True) :
        t = [x for x in self.playlists.items()]
        return [y[1] for y in t if pred(y[1])]

    ################################################################
    #
    def add_playlist(self, playlist) :
        """Add a new playlist to the internal list."""

        new_id = 1 + max(x[1].get_id() for x in self.playlists.items())
        playlist.set_id(new_id)
        self.playlists[new_id] = playlist
        return new_id

    ################################################################
    #
    def push_comments(self) :
        """Push comments to the database."""

        sql = """
        UPDATE track
           SET comments = ?
         WHERE track_id = ?
        ;
        """

        data = [
            (t[1].get_comment(), t[1].get_id()) 
            for t in self.songs.items()
            if t[1].is_dirty()
        ]

        updated = utils.do_update(self.con, sql, data)

        print (updated, 'Comments updated')

    
################################################################
#
if __name__ == '__main__' :

    with RhapsodyDb('temp.seb') as db :
        best = db.get_songs(lambda x : x.get_rating() == 5)
        print(len(best))

        rest = db.get_songs()
        print(len(rest))

        print(db.find_song(123))
