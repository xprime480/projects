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
        self.read_base  = 'test1'
        self.write_base = 'test2_keycounter'

    ################################################################
    #
    def setUp(self) :
        self.factory = datatablefactory.DataTableFactory()
        self.factory.open()

    ################################################################
    #
    def tearDown(self) :
        self.factory.close() 

    ################################################################
    #
    def test_old(self) :
        kc = keycounter.KeyCounter(['Name', 'Rank'])
        kc.read(self.read_base + '.csv')
        kc.write(self.write_base + '.csv')

        self.validate()

    ################################################################
    #
    def test_new(self) :
        kc = keycounter.KeyCounterAlt(['Name', 'Rank'], self.factory)
        kc.read(self.read_base)
        kc.write(self.write_base)

        self.validate()

    ################################################################
    #
    def validate(self) :
        dt = csvdatatable.read(self.write_base, self.factory)

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
            [int(x[0]) for x in dt.get_values('Count')]
        )

        os.unlink(self.write_base + '.csv')

################################################################
#
if '__main__' == __name__ :
    """Run the unit tests."""

    unittest.main()
