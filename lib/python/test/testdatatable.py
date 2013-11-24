#!/usr/bin/env python3

import unittest

from datatable import *
from selectors import *

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
    def test_empty_table(self) :
        dt = DataTable('table')

        self.assertCountEqual([], dt.get_cols())
        self.assertEqual(0, dt.get_row_count())

    def test_duplicate_columns(self) :
        with self.assertRaises(Exception) :
            dt = DataTable('table', ['cat', 'cat'])

    def test_basic(self) :
        dt = self.make_dt_one()
        self.assert_dt_one(dt)

    def test_copy(self) :
        dt = DataTable('table')
        dt.add_cols(self.make_dt_one())
        self.assert_dt_one(dt)

    def test_dup_col_add(self) :
        d5 = DataTable('d5', ['Key', 'More'])
        d5.add_row(['Sam', 'Dave'])
        d5.add_row(['Mike', 'Abby'])
        d5.add_cols(self.make_dt_one())
        d6 = DataTable('d6', ['Not_Used'])
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
        self.assertCountEqual(['dog', 'cat'], dp.get_values('Key'))

    def test_filter(self) :
        dt = self.make_dt_one()
        df = dt.filter('TestFilter', lambda x : x['Key'] == 'dog')

        self.assertEqual(1, df.get_row_count())
        self.assertCountEqual([7], df.get_values('Value'))

    def test_select(self) :
        dt = self.make_dt_one()
        key_selector  = simple_column_selector('Key')
        transformer = lambda x : x['Value']**2+1
        data_selector = NamedSelector('Result', transformer)
        ds = dt.select('TestSelect', key_selector, data_selector)

        self.assertCountEqual(['Key', 'Result'], ds.get_cols())
        self.assertCountEqual(['cat', 'dog'], ds.get_values('Key'))
        self.assertCountEqual([10, 50], ds.get_values('Result'))

    def test_group_by(self) :
        dt = self.make_dt_one()
        dt.add_rows(dt)

        self.assertCountEqual(['Key', 'Value'],   dt.get_cols())
        self.assertCountEqual(['cat', 'dog'] * 2, dt.get_values('Key'))
        self.assertCountEqual([3, 7] * 2,         dt.get_values('Value'))

        dt.add_row(['fish', None])

        key_selector  = simple_column_selector('Key', rename='Bob')
        keys = [key_selector]

        def sum_func(ds) :
            return sum([v for v in [d['Value'] for d in ds] if v])
        sum_aggregator = NamedSelector('Sum_of_Values', sum_func)

        def count_func(ds) :
            return len([d for d in ds])
        count_aggregator = NamedSelector('Count', count_func)

        dg = dt.group_by('TestGroupBy',
                         keys,
                         sum_aggregator,
                         count_aggregator)

        self.assertCountEqual(['Bob', 'Sum_of_Values', 'Count'], dg.get_cols())
        self.assertCountEqual(['cat', 'dog', 'fish'], dg.get_values('Bob'))
        self.assertCountEqual([6, 14, 0], dg.get_values('Sum_of_Values'))
        self.assertCountEqual([2,2,1], dg.get_values('Count'))

        value_selector = simple_column_selector('Value')
        keys.append(value_selector)

        dg2 = dt.group_by('TestGroupBy2',
                          keys,
                          count_aggregator)

        self.assertCountEqual(
            ['Bob', 'Value', 'Count'],
            dg2.get_cols()
        )
        self.assertCountEqual(
            ['cat', 'dog', 'fish'],
            dg2.get_values('Bob')
        )
        self.assertCountEqual(
            [3, 7, None],
            dg2.get_values('Value')
        )
        self.assertCountEqual(
            [2,2,1],
            dg2.get_values('Count')
        )

    def test_order_by(self) :
        dt = self.make_dt_one()

        self.assertEqual([7,3], dt.get_values('Value'))

        value_selector = simple_column_selector('Value')
        ds = dt.order_by('TestOrderBy', value_selector)

        self.assertEqual([3,7], ds.get_values('Value'))

    def make_dt_one(self) :
        dt = DataTable('table', ['Key', 'Value'])
        dt.add_row(['dog', 7])
        dt.add_row(['cat', 3])
        return dt

    def assert_dt_one(self, dt) :
        self.assertCountEqual(['Key', 'Value'], dt.get_cols())
        self.assertCountEqual(['dog', 'cat'], dt.get_values('Key'))
        self.assertCountEqual([7, 3], dt.get_values('Value'))
        self.assertEqual(2, dt.get_row_count())

################################################################
#
if '__main__' == __name__ :
    """Run the unit tests."""

    unittest.main()
