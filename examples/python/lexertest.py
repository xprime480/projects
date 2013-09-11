#!/usr/bin/env python3

import string
import unittest

from lexer import *

##################################################################
#
class CombinatorTest(unittest.TestCase) :
    """Test the Parser Combinators."""

    ##################################################################
    #
    def __init__(self, n='runTest') :
        unittest.TestCase.__init__(self, n)

    ##################################################################
    #
    def test01(self) :
        self.assertEqual(
            ('+', 'OP', ''),
            ops.match("+")
        )
        self.assertEqual(
            ('set', 'KW', ''),
            kws.match("set")
        )
        self.assertEqual(
            (None, None, 'settle'),
            kws.match("settle")
        )
        self.assertEqual(
            [],
            list(tokenize(""))
        )
        self.assertEqual(
            [('2', 2), ('+', 'OP'), ('2', 2)],
            list(tokenize("2+2"))
        )
        self.assertEqual(
            [('exp', 'KW'), ('3', 3), ('5', 5)],
            list(tokenize("exp 3 5"))
        )
        self.assertEqual(
            [('dogfish99', 'ID')],
            list(tokenize("dogfish99"))
        )
        self.assertEqual(
            [None],
            list(tokenize("..."))
        )
