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
        """Test the old KeyCounter class."""

        kc = keycounter.KeyCounter(['Name', 'Rank'])
        kc.read(self.read_base + '.csv')
        kc.write(self.write_base + '.csv')

        self.validate()

    ################################################################
    #
    def test_new(self) :
        """Test the new KeyCounter class."""

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
            [
                ['Major', 'Major', 1],
                ['Major', 'Captain', 0],
                ['Major', '***All***', 1],
                ['Yossarian', 'Major', 0],
                ['Yossarian', 'Captain', 1],
                ['Yossarian', '***All***', 1],
                ['Tom', 'Major', 1],
                ['Tom', 'Captain', 0],
                ['Tom', '***All***', 1],
                ['***All***', 'Major', 2],
                ['***All***', 'Captain', 1],
                ['***All***', '***All***', 3]
            ],
            [[row[0], row[1], int(row[2])] for row in dt.get_rows()]
        )

        os.unlink(self.write_base + '.csv')

################################################################
#
if '__main__' == __name__ :
    """Run the unit tests."""

    unittest.main()
