#!/usr/bin/env python3

import sys
import unittest

from datatable        import *
from datatableadapter import *
from datatablebase    import DataTableBaseException
from datatablefactory import DataTableFactory

##################################################################
#
class DataTableAdapterTest(unittest.TestCase) :
    """Test DataTableAdapter."""

    ##################################################################
    #
    def __init__(self, n='runTest') :
        super().__init__(n)

    ################################################################
    #
    def setUp(self) :
        self.factory = DataTableFactory()
        self.factory.open()

    ################################################################
    #
    def tearDown(self) :
        self.factory.close()

    ################################################################
    #
    def test_base_functions(self) :
        dt  = self.factory.new_table('void', [('id', int)])
        dt.add_row([101])
        dta = DataTableAdapter('anthrax', dt)

        print('TBF:', dt.get_version(), file=sys.stderr)

        self.assertEqual('anthrax$void', dta.get_name())
        self.assertEqual(1, dta.get_version())

        with self.assertRaises(DataTableBaseException) :
            dta.display()
            dta.add_cols(['new'])
            dta.add_rows([])
            dta.add_row([])
            dta.get_cols()
            dta.get_row_count()
            dta.get_value('id', 0)
            dta.get_values('id')
            dta.project('projection', 'id')
            dta.filter('filter', None)
            dta.select('select')
            dta.group_by('group_by', ['id'])
            dta.order_by('order_by', [])
            for x in dta : 
                print (x, file=sys.stderr)

    def test_passthru(self) :
        dt1 = self.factory.new_table('first', [('id', int)])
        dt1.add_rows([[1], [3], [157]])

        dt2 = self.factory.new_table('second', ['datum'])
        dt2.add_rows([['yes'], ['no']])
        
        dta = DataTablePassthru('window1', dt1)
        dta.add_cols(dt2)
        
        self.assertEqual('window1$first', dta.get_name())
        
        self.check_passthru(dta)
        self.check_passthru(dt1) # should be identical

    def check_passthru(self, dta) :
        self.assertEqual(2, dta.get_version())        
        self.assertEqual(3, dta.get_row_count())
        self.assertCountEqual(['id', 'datum'], dta.get_cols())
        self.assertCountEqual(
            [ (1, 'yes'), (3, 'no'), (157, None) ],
            dta.get_rows()
        )


################################################################
#
if '__main__' == __name__ :
    """Run the unit tests."""

    unittest.main()
