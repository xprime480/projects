#!/usr/bin/env python3

import os
import unittest

import datatable
import csvdatatable

##################################################################
#
class CsvDataTableTest(unittest.TestCase) :
    """Test CsvDataTable."""

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
            [
                ['Yossarian', 'Captain', '123456'],
                ['Major', 'Major', '888888'],
                ['Tom', 'Major', '987654']
            ], 
            dt.get_values('Name', 'Rank', 'Serial Number')
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
            [['Wine'], ['Batman']], 
            dt.get_values('Good')
        )

        os.unlink('test2.csv')

################################################################
#
if '__main__' == __name__ :
    """Run the unit tests."""

    unittest.main()
