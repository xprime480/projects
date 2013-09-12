#!/usr/bin/env python3

import os
import unittest

from csvfileio import *

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
    def test_read(self) :
        with CsvFileIo('test_in.csv', False) as rdr :
            hdrs = rdr.fieldnames
            rows = [r for r in rdr]

        self.assertEqual(['index', 'name', 'value'], hdrs)
        self.assertEqual(2, len(rows))
        self.assertEqual('1',   rows[0]['index'])
        self.assertEqual('Bob', rows[0]['name'])
        self.assertEqual('17',  rows[0]['value'])

    ##################################################################
    #
    def test_write(self) :
        rows = [
            {'a' : 1, 'b' : 'two', 'c' : 0.25 },
            {'a' : 7, 'b' : 'six', 'c' : 0.01 }
        ]
        hdrs = ['a', 'c']       # skip column b

        ofile = 'test_out.csv'

        with CsvFileIo(ofile, True, hdrs) as wrt :
            wrt.writeheader()
            for r in rows :
                wrt.writerow(r)

        with CsvFileIo(ofile, False) as rdr :
            thdrs = rdr.fieldnames
            trows = [r for r in rdr]

        self.assertEqual(hdrs, thdrs)
        self.assertEqual(len(rows), len(trows))
        self.assertEqual(1,    rows[0]['a'])
        self.assertEqual(0.25, rows[0]['c'])

        os.unlink(ofile)

################################################################
#
if '__main__' == __name__ :
    """Run the unit tests."""

    unittest.main()
