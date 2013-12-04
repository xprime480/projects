#!/usr/bin/env python3

import datatablebase

################################################################
#
class DataTableResults(datatablebase.DataTableBase) :

    ################################################################
    #
    def __init__(self, name, cols, rows) :
        super().__init__(name)
        self._extend_cols(cols)
        self.rows = rows

    ################################################################
    #
    def get_values(self, col) :
        index = self.cols.index(col)
        return [r[index] for r in self.rows]

    ################################################################
    #
    def get_rows(self, limit=None) :
        if limit is None or limit >= len(self.rows) :
            return self

        tmp = self.rows[:limit]
        return DataTableResults(self.get_name(), self.get_cols(), tmp)

    ################################################################
    #
    def get_row_count(self) :
        return len(self.rows)

    ################################################################
    #
    def __iter__(self) :
        return self.rows.__iter__()
