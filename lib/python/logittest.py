#!/usr/bin/env python3

import unittest

from logit import *

##################################################################
#
class LogitTest(unittest.TestCase) :
    """Test the Logit functions."""

    ##################################################################
    #
    def __init__(self, n='runTest') :
        unittest.TestCase.__init__(self, n)

    ##################################################################
    #
    def test_logit(self) :
        self.assertEqual(0.0, p2logit(0.5))
        self.assertEqual(0.5, logit2p(0.0))
        for x in [0.1 * i for i in range(1,10)] :
            self.assertEqual(round(x, 8), round(logit2p(p2logit(x)), 8))
        for x in [0.5 * i for i in range(-20,21)] :
            self.assertEqual(round(x, 8), round(p2logit(logit2p(x)), 8))


    ##################################################################
    #
    def test_db(self) :
        self.assertEqual(0.0, p2db(0.5))
        self.assertEqual(0.5, db2p(0.0))
        self.assertEqual(0.5, db2p(p2db(0.5)))
        for x in [0.1 * i for i in range(1,10)] :
            self.assertEqual(round(x, 8), round(db2p(p2db(x)), 8))
        for x in [0.5 * i for i in range(-20,21)] :
            self.assertEqual(round(x, 8), round(p2db(db2p(x)), 8))


def main() :
    """Execute some tests."""

    for x in range(-10,11) :
        print (logit2p(.5 * x))

    print (logit2p(p2logit(0.1)))

