#!/usr/bin/env python3

import string
import unittest

from fileutils import *

################################################################
#
class TestOpenAnything(unittest.TestCase) :
    """Test the open_anything function."""

    ################################################################
    #
    def test_open_file(self) :
        """Open a file and get its length"""

        f = 'fileutilstest.py'
        with open(f) as s :
            l = len(s.read())
        with OmniOpener(f) as s :
            self.assertEqual(l, len(s.read()))

    ################################################################
    #
    def test_open_url(self) :
        """Open a url and get its length"""

        f = 'http://google.com'
        with OmniOpener(f) as s :
            p = b'doctype html'
            self.assertEqual(p, s.read(14)[2:])

        f = 'file://localhost/etc/fstab'
        with OmniOpener(f) as s :
            p = b'For a description '
            self.assertEqual(p, s.read(20)[2:])

    ################################################################
    #
    def test_open_string(self) :
        """Open a string and get back the same"""

        f = 'Lousy test string'
        with OmniOpener(f) as s :
            self.assertEqual(f, s.read())

################################################################
#
if '__main__' == __name__ :
    """Run the unit tests."""

    unittest.main()
