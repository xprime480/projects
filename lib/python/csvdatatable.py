#!/usr/bin/env python3

import csvfileio
import datatable

def read(name, cols=None) :
    f = name + '.csv'
    with csvfileio.CsvFileIo(f, False) as rdr :
        if cols is None :
            cols = rdr.fieldnames
        temp = datatable.DataTable(name, cols)
        temp.add_rows(rdr)
    return temp

def write(table, cols=None) :
    f = table.get_name() + '.csv'
    if cols is None :
        cols = table.get_cols()
    with csvfileio.CsvFileIo(f, True, cols) as rtr :
            rtr.writeheader()
            for row in table :
                rtr.writerow(row.as_dict())

