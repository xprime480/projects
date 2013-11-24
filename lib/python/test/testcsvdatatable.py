#!/usr/bin/env python3

import os
import unittest

import datatable
import csvdatatable

##################################################################
#
class CombinatorTest(unittest.TestCase) :
    """Test DataTable."""

    ##################################################################
    #
    def __init__(self, n='runTest') :
        super().__init__(n)

    ################################################################
    #
    def test_read(self) :
        dt = csvdatatable.read('test1')
        
        self.assertCountEqual(
            ['Name', 'Rank', 'Serial Number'],
            dt.get_cols()
        )
        self.assertCountEqual(
            ['Yossarian', 'Major', 'Tom'], 
            dt.get_values('Name')
        )
        self.assertCountEqual(
            ['Colonel', 'Major', 'Major'],
            dt.get_values('Rank')
        )
        self.assertCountEqual(
            ['123456', '888888', '987654'],
            dt.get_values('Serial Number')
        )

    def test_write(self) :
        dt = datatable.DataTable('test2', ['Good','Bad'])
        dt.add_rows([
            ['Wine', 'Ouzo'],
            ['Batman', 'Joker']
        ])
        csvdatatable.write(dt)

        del dt

        dt = csvdatatable.read('test2', ['Good'])
        
        self.assertCountEqual(
            ['Good'],
            dt.get_cols()
        )
        self.assertCountEqual(
            ['Wine', 'Batman'], 
            dt.get_values('Good')
        )

        os.unlink('test2.csv')

################################################################
#
if '__main__' == __name__ :
    """Run the unit tests."""

    unittest.main()
