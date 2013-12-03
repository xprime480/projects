#!/usr/bin/env python3

import os
import unittest

import datatablefactory
import keycounter
import csvdatatable

##################################################################
#
class KeyCounterTest(unittest.TestCase) :
    """Test KeyCounter class."""

    ##################################################################
    #
    def __init__(self, n='runTest') :
        super().__init__(n)

    ################################################################
    #
    def test_old(self) :
        kc = keycounter.KeyCounter(['Name', 'Rank'])
        kc.read('test1.csv')
        kc.write('test2.csv')

        self.validate()

    ################################################################
    #
    def test_new(self) :
        kc = keycounter.KeyCounterAlt(['Name', 'Rank'])
        kc.read('test1')
        kc.write('test2')

        self.validate()

    ################################################################
    #
    def validate(self) :
        f = datatablefactory.DataTableFactory()
        f.open()
        dt = csvdatatable.read('test2', f)

        self.assertCountEqual(['Name','Rank','Count'], dt.get_cols())
        self.assertEqual(12, dt.get_row_count())
        self.assertCountEqual(
            ['Major', 'Yossarian', 'Tom', '***All***'] * 3,
            dt.get_values('Name')
        )
        self.assertCountEqual(
            ['Major', 'Captain', '***All***'] * 4,
            dt.get_values('Rank')
        )
        self.assertCountEqual(
            [0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 3],
            [int(x) for x in dt.get_values('Count')]
        )

        os.unlink('test2.csv')
        f.close()

################################################################
#
if '__main__' == __name__ :
    """Run the unit tests."""

    unittest.main()
