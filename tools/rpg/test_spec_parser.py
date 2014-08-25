#!/usr/bin/python3

import unittest

import SpecParser

class TestSpecParser(unittest.TestCase) :
    def test_d6(self) :
        parser = SpecParser.SpecParser("d6")
        result = parser.parse()
        self.assertEqual(result.dice_count(), 1)
        self.assertEqual(result.dice_size(), 6)
        self.assertEqual(result.offset(), 0)

    def test_2d4p1(self) :
        parser = SpecParser.SpecParser("2d4+1")
        result = parser.parse()
        self.assertEqual(result.dice_count(), 2)
        self.assertEqual(result.dice_size(), 4)
        self.assertEqual(result.offset(), 1)

    def test_3d6m2(self) :
        parser = SpecParser.SpecParser("3d6-1")
        result = parser.parse()
        self.assertEqual(result.dice_count(), 3)
        self.assertEqual(result.dice_size(), 6)
        self.assertEqual(result.offset(), -1)

if __name__ == '__main__':
    unittest.main()
