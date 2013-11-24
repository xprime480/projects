#!/usr/bin/python3

import itertools
import sys

################################################################
#
class RowReference(object) :
    def __init__(self, table, rowid) :
        self.table = table
        self.rowid = rowid

    def __repr__(self) :
        row = self.values()
        return str(row)

    def values(self, cols=None) :
        if not cols :
            cols = self.table.get_cols()
        row = []
        for col in cols :
            row.append(self.table.get_value(col, self.rowid))
        return row

    def as_dict(self) :
        cols = self.table.get_cols()
        vals = self.values(cols)

        return dict(zip(cols, vals))

################################################################
#
class DataTableIterator(object) :
    def __init__(self, table, rows) :
        self.table = table
        self.rows  = rows
        self.curr  = 0

    def __next__(self) :
        if self.curr >= len(self.rows) :
            raise StopIteration
        row = RowReference(self.table, self.rows[self.curr])
        self.curr += 1
        return row
    
################################################################
#
class DataTable(object) :
    
    ################################################################
    #
    def __init__(self, name, cols=[]) :
        self.name = name
        self.cols = list(cols)[:]
        for col in self.cols :
            if self.cols.count(col) > 1 :
                raise Exception('Duplicate column name: %s' % name)

        self.rows      = {}
        for col in self.cols :
            self.rows[col] = []

        self.row_count = 0

    ################################################################
    #
    def add_cols(self, source) :
        cols    = source.get_cols()
        new_cols = set(cols).difference(self.cols)
        self.cols.extend(list(new_cols))
        
        for col in new_cols :
            new_vals = source.get_values(col)
            count = len(new_vals)
            if self.row_count == 0 :
                self.row_count = count
            expected = self.row_count
            if count > expected :
                new_vals = new_vals[:expected]
            elif count < expected :
                new_vals.extend([None] * (expected-count))

            self.rows[col] = new_vals

    ################################################################
    #
    def add_rows(self, rows) :
        for row in rows :
            self.add_row(row)

    ################################################################
    #
    def add_row(self, values) :
        if type(values) == type({}) :
            self._add_from_dict(values)
        elif type(values) == type([]) :
            self._add_from_list(values)
        elif type(values) == RowReference :
            self._add_from_dict(values.as_dict())
        else :
            raise Exception('Don''t know how to add %s ' % str(values))
            
    ################################################################
    #
    def _add_from_dict(self, row) :
        for col in self.cols :
            val = row.get(col, None)
            self.rows[col].append(val)

        self.row_count += 1
        
    ################################################################
    #
    def _add_from_list(self, row) :
        count = len(self.cols)
        inrow = len(row)

        for i in range(min(count, inrow)) :
            col = self.cols[i]
            val = row[i]
            self.rows[col].append(val)

        for i in range(inrow, count) :
            col = self.cols
            self.rows[col].append(None)

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
        col = self.rows[col]
        if len(col) <= i :
            raise Exception('Table has fewer than %d rows' % i)
        return col[i]

    ################################################################
    #
    def get_values(self, col) :
        if col not in self.cols :
            raise Exception('Column %s not in data' % col)
        return self.rows[col][:]

    ################################################################
    #
    def project(self, name, cols) :
        new_table = DataTable(name, cols)
        for col in cols :
            if col in self.cols :
                new_table.rows[col] = self.get_values(col)
            else :
                new_table.rows[col] = [None] * self.row_count
        return new_table

    ################################################################
    #
    def filter(self, name, filterfn) :
        new_table = DataTable(name, self.cols)
        for row in self :
            d = row.as_dict()
            if filterfn(d) :
                new_table._add_from_dict(d)
        return new_table

    ################################################################
    #
    def select(self, name, *selectors) :
        cols = [s.get_name() for s in selectors]
        new_table = DataTable(name, cols)
        for row in self :
            d = row.as_dict()
            r = [s(d) for s in selectors]
            new_table._add_from_list(r)
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
    def display(self, f=sys.stderr) :
        print ('\n\n', file=f)
        print ('Table %s:' % self.name, file=f)

        if not self.cols :
            print ('Table has no columns', file=f)
            return
        
        print ('Columns:', self.cols, file=f)
        for row in self :
            print (' Values:', row, file=f)

        print ('', file=f)
        print ('Row count = %d' % self.row_count, file=f)

if __name__ == '__main__' :
    print ('Run testdatatable.py for unit tests.')
