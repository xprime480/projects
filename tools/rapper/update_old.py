#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import datetime
import argparse
import sys

import rhapdb

################################################################
#
class Temp(object) :
    """Temp object."""

    ################################################################
    #
    def __init__(self, db) :
        """Create the object."""

        self.db     = db
        self.tracks = self.db.get_songs(lambda x : x.is_in_library())
        
    ################################################################
    #
    def dump(self) :
        """Print all."""

        for t in self.tracks :
            print(t)

    ################################################################
    #
    def update(self) :
        """Change rating for all tracks that are over a certain age."""

        breaker = datetime.datetime.strptime('20130901', '%Y%m%d')

        for t in self.tracks :
            d = t.get_last_played()
            r = t.get_rating()
            if d < breaker and r in (1,2) :
                t.set_rating(3)
                print(t)

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

    try :
        args = parser.parse_args()
    except IOError as e :
        print (e)
        return 1

    with rhapdb.RhapsodyDb(args.db) as db :
        o = Temp(db) 
        o.update()

    return 0

################################################################
#
if __name__ == '__main__' :
    sys.exit(main())
