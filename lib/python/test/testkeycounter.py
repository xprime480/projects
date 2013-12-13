#!/usr/bin/env python3

import os
import unittest

import datatable.csv

from datatable.factory import DataTableFactory
from datatable.keycounter import KeyCounter

##################################################################
#
class KeyCounterTest(unittest.TestCase) :
    """Test KeyCounter class."""

    __do_log_init = True

    ##################################################################
    #
    def __init__(self, n='runTest') :
        super().__init__(n)
        self.read_base  = 'test1'
        self.write_base = 'test2_keycounter'

        if KeyCounterTest.__do_log_init :
            import testapp
            app = testapp.TestApp('testkeycounter')
            KeyCounterTest.__do_log_init = False

    ################################################################
    #
    def setUp(self) :
        self.factory = datatable.factory.DataTableFactory()
        self.factory.open()

    ################################################################
    #
    def tearDown(self) :
        self.factory.close() 

    ################################################################
    #
    def test_new(self) :
        """Test the new KeyCounter class."""

        kc = KeyCounter(['Name', 'Rank'], self.factory)
        kc.read(self.read_base)
        results = kc.get_results()
        #kc.write(self.write_base)
        self.validate(results)

    ################################################################
    #
    def validate(self, dt) :
        """Validate the data results."""

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

################################################################
#
if '__main__' == __name__ :
    """Run the unit tests."""
