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
        l = len(open(f).read())
        self.assertEqual(l, len(open_anything(f).read()))

    ################################################################
    #
    def test_open_url(self) :
        """Open a url and get its length"""

        f = 'http://google.com'
        p = b'doctype html'
        self.assertEqual(p, open_anything(f).read(14)[2:])

        f = 'file://localhost/etc/fstab'
        p = b'For a description '
        self.assertEqual(p, open_anything(f).read(20)[2:])

    ################################################################
    #
    def test_open_string(self) :
        """Open a string and get back the same"""

        s = 'Lousy test string'
        self.assertEqual(s, open_anything(s).read())

################################################################
#
if '__main__' == __name__ :
    """Run the unit tests."""

    unittest.main()
