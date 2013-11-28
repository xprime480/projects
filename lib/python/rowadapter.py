#!/usr/bin/env python3

from datatableiterator import DataTableIterator
from readonlyadapter import ReadOnlyAdapter

################################################################
#
class RowAdapter(ReadOnlyAdapter) :

    ################################################################
    #
    def __init__(self, name, base, rowids) :
        super().__init__(name, base)
        self.rowids = rowids

    ################################################################
    #
    def __iter__(self) :
        return DataTableIterator(self.table, self.rowids)

    
