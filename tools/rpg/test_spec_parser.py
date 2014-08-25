#!/usr/bin/python3

import unittest

import SpecParser

class TestSpecParser(unittest.TestCase) :
    def setUp(self) :
        self.parser = SpecParser.SpecParser()

    def test_d6(self) :
        result = self.parser.parse("d6")
        self.assertEqual(result.dice_count(), 1)
        self.assertEqual(result.dice_size(), 6)
        self.assertEqual(result.offset(), 0)

    def test_2d4p1(self) :
        result = self.parser.parse("2d4+1")
        self.assertEqual(result.dice_count(), 2)
        self.assertEqual(result.dice_size(), 4)
        self.assertEqual(result.offset(), 1)

    def test_3d6m2(self) :
        result = self.parser.parse("3d6-1")
        self.assertEqual(result.dice_count(), 3)
        self.assertEqual(result.dice_size(), 6)
        self.assertEqual(result.offset(), -1)

if __name__ == '__main__':
    unittest.main()
