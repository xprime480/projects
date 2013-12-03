#!/usr/bin/python3

import itertools
import sys

import datatablebase
from datatableiterator import DataTableIterator, RowReference
import rowadapter

################################################################
#
class DataTable(datatablebase.DataTableBase) :
    
    ################################################################
    #
    def __init__(self, name, cols=[]) :
        self.name = name
        self.cols = list(cols)[:]
        for col in self.cols :
            if self.cols.count(col) > 1 :
                raise Exception('Duplicate column name: %s' % name)

        self.col_indices = dict(zip(self.cols, range(len(self.cols))))
        self.rows        = []
        self.row_count   = 0
        self.version     = 0

    ################################################################
    #
    def add_cols(self, source) :
        cols     = source.get_cols()
        new_cols = list(set(cols).difference(self.cols))
        self.cols.extend(new_cols)
        self.col_indices = dict(zip(self.cols, range(len(self.cols))))
        
        new_vals = source.get_values(*new_cols)
        count = len(new_vals)

        if self.row_count == 0 :
            self.row_count = count
            for i in range(count) :
                self.rows.append([])

        expected = self.row_count
        if count > expected :
            new_vals = new_vals[:expected]
        elif count < expected :
            extender = [None] * len(new_cols)
            new_vals.extend([extender] * (expected-count))

        for i in range(self.row_count) :
            self.rows[i].extend(new_vals[i])

        self.version += 1

    ################################################################
    #
    def add_rows(self, rows) :
        for row in rows :
            self.add_row(row, 0)

        self.version += 1

    ################################################################
    #
    def add_row(self, values, _version_incr=1) :
        if type(values) == type({}) :
            self._add_from_dict(values)
        elif type(values) == type([]) :
            self._add_from_list(values)
        elif type(values) == RowReference :
            self._add_from_dict(values.as_dict())
        else :
            raise Exception('Don''t know how to add %s ' % str(values))

        self.row_count  = len(self.rows)
        self.version   += _version_incr
            
    ################################################################
    #
    def _add_from_dict(self, row) :
        vals = [row.get(col, None) for col in self.cols]
        self.rows.append(vals)
        
    ################################################################
    #
    def _add_from_list(self, row) :
        count = len(self.cols)
        inrow = len(row)

        rowdata = row[:count]
        if count > inrow :
            rowdata.extend([None] * (count - inrow))
            
        self.rows.append(rowdata)
        self.row_count += 1

    ################################################################
    #
    def get_cols(self) :
        return list(self.cols)[:]

    ################################################################
    #
    def get_name(self) :
        return self.name

    ################################################################
    #
    def get_row_count(self) :
        return self.row_count

    ################################################################
    #
    def get_value(self, col, i) :
        if col not in self.cols :
            raise Exception('Column %s not in data' % col)
        if len(self.rows) <= i :
            raise Exception('Table has fewer than %d rows' % i)
        return self.rows[i][self.col_indices[col]]

    ################################################################
    #
    def get_values(self, *cols) :
        for col in cols :
            if col not in self.cols :
                raise Exception('Column %s not in data' % col)
        col_indices = [self.col_indices[col] for col in cols]
        return [[row[x] for x in col_indices] for row in self.rows]

    ################################################################
    #
    def project(self, name, cols) :
        new_table = DataTable(name, cols)
        new_table.add_rows(self.get_values(*cols))
        return new_table

    ################################################################
    #
    def filter(self, name, filterfn) :
        new_table = DataTable(name, self.cols)
        for row in self :
            d = row.as_dict()
            if filterfn(d) :
                new_table._add_from_dict(d)
                new_table.row_count += 1
        return new_table

    ################################################################
    #
    def alt_filter(self, name, filterfn) :
        accept = []
        new_table = DataTable(name, self.cols)
        for row in self :
            d = row.as_dict()
            if filterfn(d) :
                accept.append(d.rowid)
        return RowFilteredDataTable(self, new_table, accept)

    ################################################################
    #
    def select(self, name, *selectors) :
        cols = [s.get_name() for s in selectors]
        new_table = DataTable(name, cols)
        for row in self :
            d = row.as_dict()
            r = [s(d) for s in selectors]
            new_table._add_from_list(r)
        new_table.version += 1
        return new_table

    ################################################################
    #
    def group_by(self, name, keys, *aggregators) :
        cols = [k.get_name() for k in keys]
        cols.extend(a.get_name() for a in aggregators)
        new_table = DataTable(name, cols)

        def key_func(row) :
            r = row.as_dict()
            key = tuple([k(r) for k in keys])
            return key
            
        temp = [(key_func(r), r) for r in self]
        temp.sort(key=lambda x : x[0])

        for key, rows in itertools.groupby(temp, lambda x : x[0]) :
            rvals = [x[1].as_dict() for x in rows]
            new_row = list(key)
            new_row.extend([a(rvals) for a in aggregators])
            new_table.add_row(new_row)
        
        return new_table
                 
    ################################################################
    #
    def order_by(self, name, *selectors) :
        
        temp = []
        for row in self :
            r = row.as_dict()
            keys = tuple([s(r) for s in selectors])
            temp.append((keys, r))

        temp.sort(key=lambda x : x[0])
        
        new_table = DataTable(name, self.get_cols())
        new_table.add_rows([x[1] for x in temp])
        return new_table

    ################################################################
    #
    def __iter__(self) :
        return DataTableIterator(self, range(self.row_count))

    ################################################################
    #
    def display(self, f=sys.stderr, row_limit=20) :
        #print ('\n\n', file=f)
        print ('Table %s:' % self.get_name(), file=f)

        if not self.get_cols() :
            print ('Table has no columns', file=f)
            return
        
        print ('Columns:', self.get_cols(), file=f)
        rows_printed = 0
        for row in self :
            if rows_printed >= row_limit :
                break
            print (' Values:', row, file=f)
            rows_printed += 1

        print ('', file=f)
        print ('Row count = %d' % self.row_count, file=f)
        print ('Version = %d' % self.version, file=f)


################################################################
#        
class RowFilteredDataTable(object) :
    def __init__(self, table, accept) :
        self.table   = table
        self.accept  = accept
        

if __name__ == '__main__' :
    print ('Run testdatatable.py for unit tests.')
