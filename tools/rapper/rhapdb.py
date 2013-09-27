#!/usr/bin/env python3

"""Interface to the Rhapsody SQLite database."""

import sqlite3 as lite


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

    def get_rating(self) :
        if not self.rating :
            return 0
        return self.rating['RATINGS_VALUE']

    def is_dirty(self) :
        return self.clean == False

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

        dirty_songs = self.get_songs(lambda x : x.is_dirty())
        if dirty_songs : 
            print(dirty_songs)

        dirty_lists = self.get_playlists(lambda x : x.is_dirty())
        if dirty_lists :
            print(dirty_lists)

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

        try :
            return str(string)
        except Exception :
            pass

        def xvt(x) :
            if x > chr(127) :
                return ' '
            return x

        t = ''.join([xvt(x) for x in string])
        return str(t)

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
if __name__ == '__main__' :

    with RhapsodyDb('temp.seb') as db :
        best = db.get_songs(lambda x : x.get_rating() == 5)
        print(len(best))

        rest = db.get_songs()
        print(len(rest))

        print(db.find_song(123))
