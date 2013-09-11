#!/usr/bin/env python3

import unittest

from counting import *

##################################################################
#
class CountingTest(unittest.TestCase) :
    """Test the Logit functions."""

    ##################################################################
    #
    def __init__(self, n='runTest') :
        unittest.TestCase.__init__(self, n)

    ##################################################################
    #
    def test_factorial(self) :
        self.assertEqual(1,    factorial(0))
        self.assertEqual(1,    factorial(1))
        self.assertEqual(6,    factorial(3))
        self.assertEqual(5040, factorial(7))
        self.assertEqual(8320987112741390144276341183223364380754172606361245952449277696409600000000000000, factorial(60))

    ##################################################################
    #
    def test_choose(self) :
        self.assertEqual(None,  choose(-3, 1))

        self.assertEqual(0,  choose(3, 4))
        self.assertEqual(1,  choose(50, 50))
        self.assertEqual(3,  choose(3, 2))
        self.assertEqual(20, choose(6, 3))
        self.assertEqual(56, choose(8, 3))
