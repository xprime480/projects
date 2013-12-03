#!/usr/bin/env python3

import unittest

from datatable import *
from selectors import *
from datatablefactory import DataTableFactory

##################################################################
#
class DataTableTest(unittest.TestCase) :
    """Test DataTable."""

    ##################################################################
    #
    def __init__(self, n='runTest') :
        super().__init__(n)

    def setUp(self) :
        self.factory = DataTableFactory()
        self.factory.open()

    def tearDown(self) :
        self.factory.close()

    ################################################################
    #
    def test_empty_table(self) :
        dt = self.factory.new_table('table')

        self.assertCountEqual([], dt.get_cols())
        self.assertEqual(0, dt.get_row_count())

    def test_duplicate_columns(self) :
        with self.assertRaises(Exception) :
            dt = self.factory.new_table('table', ['cat', 'cat'])

    def test_basic(self) :
        dt = self.make_dt_one()
        self.assert_dt_one(dt)

    def test_copy(self) :
        dt = self.factory.new_table('table')
        dt.add_cols(self.make_dt_one())
        self.assert_dt_one(dt)

    def test_dup_col_add(self) :
        d5 = self.factory.new_table('d5', ['Key', 'More'])
        d5.add_row(['Sam', 'Dave'])
        d5.add_row(['Mike', 'Abby'])
        d5.add_cols(self.make_dt_one())
        d6 = self.factory.new_table('d6', ['Not_Used'])
        d5.add_cols(d6)

        all_cols = ['Key', 'More', 'Not_Used', 'Value']
        self.assertCountEqual(all_cols, d5.get_cols())
        self.assertEqual(2, d5.get_row_count())

        for row in d5 :
            d = row.as_dict()
            if d['Key'] == 'Sam' :
                self.assertEqual(7, d['Value'])
            elif d['Key'] == 'Mike' :
                self.assertEqual(3, d['Value'])
            else :
                self.assertFalse(True)

    def test_project(self) :
        dt = self.make_dt_one()
        dp = dt.project('TestProjection', ['Key'])

        self.assertEqual(['Key'], dp.get_cols())
        self.assertCountEqual([['dog'], ['cat']], dp.get_values('Key'))

    def test_filter(self) :
        dt = self.make_dt_one()
        def fn(d) :
            k = d['Key']
            return k == 'dog'

        df = dt.filter('TestFilter', fn)
        self.assertEqual(1, df.get_row_count())
        self.assertCountEqual([[7, 'dog']], df.get_values('Value', 'Key'))

    def test_select(self) :
        dt = self.make_dt_one()
        key_selector  = simple_column_selector('Key', str)
        transformer = lambda x : x['Value']**2+1
        data_selector = NamedSelector('Result', int, transformer)
        ds = dt.select('TestSelect', key_selector, data_selector)

        self.assertCountEqual(['Key', 'Result'], ds.get_cols())
        self.assertCountEqual(
            [['cat', 10], ['dog', 50]], 
            ds.get_values('Key', 'Result')
        )

    def test_group_by(self) :
        dt = self.make_dt_one()
        rows = dt.get_rows()
        dt.add_rows(rows)

        self.assertCountEqual(['Key', 'Value'],   dt.get_cols())
        self.assertCountEqual(
            [['cat', 3], ['dog', 7]] * 2, 
            dt.get_values('Key', 'Value')
        )

        dt.add_rows([['fish', None]])

        key_selector  = simple_column_selector('Key', str, rename='Bob')
        keys = [key_selector]
        dg = dt.group_by('TestGroupBy',
                         keys,
                         sum_aggregator(
                             'Sum_of_Values',
                             simple_column_selector('Value', int)
                         ),
                         count_aggregator())

        self.assertCountEqual(
            ['Bob', 'Sum_of_Values', 'Count'], 
            dg.get_cols()
        )
        self.assertCountEqual(
            [
                ['cat', 6, 2], 
                ['dog', 14, 2], 
                ['fish', 0, 1]
            ], 
            dg.get_values('Bob', 'Sum_of_Values', 'Count')
        )

        value_selector = simple_column_selector('Value', int)
        keys.append(value_selector)

        dg2 = dt.group_by('TestGroupBy2',
                          keys,
                          count_aggregator())

        self.assertCountEqual(
            ['Bob', 'Value', 'Count'],
            dg2.get_cols()
        )
        self.assertCountEqual(
            [
                ['cat',  3,    2], 
                ['dog',  7,    2], 
                ['fish', None, 1]
            ],
            dg2.get_values('Bob', 'Value', 'Count')
        )

    def test_order_by(self) :
        dt = self.make_dt_one()

        self.assertEqual([[7], [3]], dt.get_values('Value'))

        value_selector = simple_column_selector('Value', int)
        ds = dt.order_by('TestOrderBy', value_selector)

        self.assertEqual([[3], [7]], ds.get_values('Value'))

    def make_dt_one(self) :
        dt = self.factory.new_table('table', [('Key'), ('Value', int)])
        dt.add_row(['dog', 7])
        dt.add_row(['cat', 3])
        return dt

    def assert_dt_one(self, dt) :
        self.assertCountEqual(['Key', 'Value'], dt.get_cols())
        self.assertCountEqual(
            [['dog', 7], ['cat', 3]], 
            dt.get_values('Key', 'Value')
        )
        self.assertEqual(2, dt.get_row_count())

################################################################
#
if '__main__' == __name__ :
    """Run the unit tests."""

    unittest.main()
