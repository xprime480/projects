#!/usr/bin/python3

import sys

################################################################
#
class RowReference(object) :
    def __init__(self, table, rowid) :
        self.table = table
        self.rowid = rowid

    def __repr__(self) :
        cols = self.table.get_cols()
        row = []
        for col in cols :
            row.append(self.table.get_value(col, self.rowid))

        return str(row)

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
    def __iter__(self) :
        return DataTableIterator(self, range(self.row_count))

    ################################################################
    #
    def display(self, f) :
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
    d1 = DataTable('d1')
    d1.display(sys.stdout)
    try :
        d2 = DataTable('d2', ['cat', 'cat'])
    except Exception as e :
        pass

    d3 = DataTable('d3', ['Key', 'Value'])
    d3.display(sys.stdout)

    d3.add_row(['dog', 7])
    d3.add_row(['cat', 3])
    
    d3.display(sys.stdout)

    d4 = DataTable('d4')
    d4.add_cols(d3)
    d4.display(sys.stdout)

    d5 = DataTable('d5', ['Key', 'More'])
    d5.add_row(['Sam', 'Dave'])
    d5.add_row(['Mike', 'Abby'])
    d5.add_cols(d3)
    d6 = DataTable('d6', ['Not_Used'])
    d5.add_cols(d6)
    d5.display(sys.stdout)

    for row in d5 :
        print (row, file=sys.stdout)
