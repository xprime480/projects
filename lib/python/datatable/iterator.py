#!/usr/bin/env python3

################################################################
#
class RowReference(object) :
    def __init__(self, table, rowid) :
        self.table = table
        self.rowid = rowid

    def __repr__(self) :
        row = self.values()
        return str(row)

    def values(self) :
        return self.table.get_row(self.rowid)

    def as_dict(self) :
        cols = self.table.get_cols()
        vals = self.values()

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
    
