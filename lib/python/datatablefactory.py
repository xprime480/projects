#!/usr/bin/env python3


import sqlite3 as lite
import datatable

class DataTableFactory(object) :
    def __init__(self, database=':memory:') :
        self.database = database
        self.table_id = 0

    def open(self) :
        self.con = lite.connect(self.database)

    def close(self) :
        self.con.close()
        self.con = None

    def new_table(self, name, cols=[]) :
        self.table_id += 1
        name_with_id = '%s_%06d' % (name, self.table_id)
        return datatable.DataTable(self, self.con, name_with_id, cols)
