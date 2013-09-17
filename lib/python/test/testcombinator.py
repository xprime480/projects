#!/usr/bin/env python3

import string
import unittest

from combinator import *

##################################################################
#
class CombinatorTest(unittest.TestCase) :
    """Test the Parser Combinators."""

    ##################################################################
    #
    def __init__(self, n='runTest') :
        unittest.TestCase.__init__(self, n)

        self.cx   = SingleCharMatcher('x')
        self.cy   = SingleCharMatcher('y')
        self.cxy  = AnyOfMatcher(self.cx, self.cy)
        self.cxs0 = ZeroPlusMatcher(self.cx)
        self.cxs1 = OnePlusMatcher(self.cx)
        self.any  = AnyCharMatcher()
        self.all  = ZeroPlusMatcher(self.any)

        self.digits  = CharSetMatcher(string.digits)
        self.digits2 = CharRangeMatcher('0', '9')
        self.num     = OnePlusMatcher(self.digits)
        self.ints    = IntegerMatcher()

        self.alpha   = AnyOfMatcher( CharRangeMatcher('a', 'z'),
                                   CharRangeMatcher('A', 'Z') )
        self.keyword = SequenceMatcher(self.alpha,
                                       ZeroPlusMatcher(
                                           AnyOfMatcher(
                                               self.alpha, 
                                               self.digits2
                                           )))
        self.sm      = StringMatcher("base")

    ##################################################################
    #
    def test_single_char_match(self) :
        self.assertEqual(
            ('x', 'x', 'yz'),
            self.cx.match("xyz")
        )
        self.assertEqual(
            ('x', 'x', 'xxxxy'),
            self.cx.match("xxxxxy")
        )

    ##################################################################
    #
    def test_multi_char_match(self) :
        self.assertEqual(
            ('x', 'x', 'yz'),
            self.cxy.match("xyz")
        )
        self.assertEqual(
            ('y', 'y', 'xz'),
            self.cxy.match("yxz")
        )
        self.assertEqual(
            (None, None, 'zyx'),
            self.cx.match("zyx")
        )

    ##################################################################
    #
    def test_zero_plus_char_match(self) :
        self.assertEqual(
            ('xxxxxxx', ['x', 'x', 'x', 'x', 'x', 'x', 'x'], 'yxxxx'),
            self.cxs0.match("xxxxxxxyxxxx")
        )
        self.assertEqual(
            ('', [], 'nonehere'),
            self.cxs0.match("nonehere")
        )

    ##################################################################
    #
    def test_one_plus_char_match(self) :
        self.assertEqual(
            ('xxxxxxx', ['x', 'x', 'x', 'x', 'x', 'x', 'x'], 'yxxxx'),
            self.cxs1.match("xxxxxxxyxxxx")
        )
        self.assertEqual(
            (None, None, 'nonehere'),
            self.cxs1.match("nonehere")
        )

    ##################################################################
    #
    def test_any_char_match(self) :
        self.assertEqual(
            ('a', 'a', 'bc'),
            self.any.match("abc")
        )
        self.assertEqual(
            (None, None, ''),
            self.any.match("")
        )
        self.assertEqual(
            (None, None, None),
            self.any.match(None)
        )

    ##################################################################
    #
    def test_all_char_match(self) :
        self.assertEqual(
            ('abcdef', ['a', 'b', 'c', 'd', 'e', 'f'], ''),
            self.all.match("abcdef")
        )
        self.assertEqual(
            ('', [], ''),
            self.all.match("")
        )

    ##################################################################
    #
    def test_digit_match(self) :
        self.assertEqual(
            ('623', ['6', '2', '3'], 'x'),
            self.num.match("623x")
        )
        self.assertEqual(
            ('8', '8', '23833xx823'),
            self.digits2.match("823833xx823")
        )

    ##################################################################
    #
    def test_integer_match(self) :
        self.assertEqual(
            ('623', 623, 'x'),
            self.ints.match("623x")
        )
        self.assertEqual(
            ('-1234623', -1234623, 'x'),
            self.ints.match("-1234623x")
        )
        self.assertEqual(
            (None, None, '--1'),
            self.ints.match("--1")
        )

    ##################################################################
    #
    def test_alpha_match(self) :
        self.assertEqual(
            ('D', 'D', 'ogBerry'),
            self.alpha.match("DogBerry")
        )

    ##################################################################
    #
    def test_keyword_match(self) :
        self.assertEqual(
            ('DogBerry99', 'DogBerry99', '$2'),
            self.keyword.match("DogBerry99$2")
        )

    ##################################################################
    #
    def test_string_match(self) :
        self.assertEqual(
            ('base', 'base', 'case'),
            self.sm.match("basecase")
        )
        self.assertEqual(
            (None, None, 'offbase'),
            self.sm.match("offbase")
        )

################################################################
#
if '__main__' == __name__ :
    """Run the unit tests."""

    unittest.main()
