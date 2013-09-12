#!/usr/bin/env python3

import unittest

from parameters import *

##################################################################
#
class ParametersTest(unittest.TestCase) :
    """Test the Parameters interface."""

    ##################################################################
    #
    def __init__(self, n='runTest') :
        unittest.TestCase.__init__(self, n)

    ##################################################################
    #
    def test_empty(self) :
        p = Parms('/dev/null')
        self.assertEqual(None, p.get('foo'))

    ##################################################################
    #
    def test_basic(self) :
        p = Parms()
        self.assertEqual('Panama', p.get('location'))
        self.assertEqual('2001-02-17', p.get('date_from'))
        self.assertEqual('2001-12-17', p.get('date_to'))
        self.assertEqual(42.0, p.get('foo'))
        self.assertEqual(17.0, p.get('foo', {'date' : '2001-11-14'}))

    ##################################################################
    #
    def test_manual(self) :
        ctx = { 'a' : 'b' }
        p = Parms('/dev/null')
        p.put('foo', None, 6)
        p.put('foo', ctx,  7)

        self.assertEqual(6, p.get('foo'))
        self.assertEqual(7, p.get('foo', ctx))

################################################################
#
if '__main__' == __name__ :
    """Run the unit tests."""

    unittest.main()
