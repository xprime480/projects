#!/usr/bin/env python3

"""Utilities for file interaction."""

import io
import urllib.request

################################################################
#
class OmniOpener(object) :
    """Open a file, a url, or give back a stream of the original object

    Stolen from an idea in ???
    """

    def __init__(self, name) :
        self.f = open_anything(name)

    def __enter__(self) :
        return self.f

    def __exit__(self, type, value, traceback) :
        if self.f :
            self.f.close()
            self.f = None

################################################################
#
def open_anything(name) :
    """Open a file, a url, or give back a stream of the original object

    Stolen from an idea in ???
    """
    f = None

    try : return open(name)
    except : pass

    try : return urllib.request.urlopen(name)
    except : pass

    try : return io.StringIO(name)
    except : pass

    return name

################################################################
#
if __name__ == '__main__' :
    print ('Run fileutilstest.py for unit tests.')


