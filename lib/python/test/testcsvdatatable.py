#!/usr/bin/env python3

import os
import unittest

import datatable
import datatablefactory
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
    def setUp(self) :
        self.factory = datatablefactory.DataTableFactory()
        self.factory.open()

    ################################################################
    #
    def tearDown(self) :
        self.factory.close()
        del(self.factory)

    ################################################################
    #
    def test_read(self) :
        dt = csvdatatable.read('test1', self.factory
)
        
        self.assertCountEqual(
            ['Name', 'Rank', 'Serial Number'],
            dt.get_cols()
        )
        self.assertCountEqual(
            [
                ('Yossarian', 'Captain', '123456'),
                ('Major', 'Major', '888888'),
                ('Tom', 'Major', '987654')
            ], 
            dt.get_rows()
        )

    def test_write(self) :
        dt = self.factory.new_table('test2', ['Good','Bad'])
        dt.add_rows([
            ['Wine', 'Ouzo'],
            ['Batman', 'Joker']
        ])
        csvdatatable.write(dt)

        del dt

        dt = csvdatatable.read('test2', self.factory, ['Good'])
        
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
