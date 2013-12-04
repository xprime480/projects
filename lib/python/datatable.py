#!/usr/bin/python3

import itertools
import sys
import sqlite3 as lite

import datatablebase
import datatableresults

################################################################
#
class RowReference(object) :
    def __init__(self, cols, data) :
        self.cols = cols
        self.data = data

    def __repr__(self) :
        return str(self.data)

    def values(self, cols=None) :
        if not cols :
            cols = self.cols
        row = []
        for col in cols :
            if col in self.cols :
                row.append(self.data[self.cols.index(col)])
            else :
                row.append(None)
        return row

    def as_dict(self) :
        return dict(zip(self.cols, self.data))

################################################################
#
class DataTableIterator(object) :
    def __init__(self, cur) :
        self.cur  = cur
        self.desc = [x[0] for x in self.cur.description]
        if '__ROWID' in self.desc :
            self.desc.remove('__ROWID')

    def __next__(self) :
        data = self.cur.fetchone()
        if not data :
            raise StopIteration
        return RowReference(self.desc, data[1:])
    
################################################################
#
class DataTable(datatablebase.DataTableBase) :
    
    ################################################################
    #
    def __init__(self, factory, con, name, cols=[]) :
        super().__init__(name)
        self.factory = factory
        self.con     = con
        self._extend_cols([('__ROWID', 'INTEGER')])
        self._extend_cols(cols)
        self.row_id  = 0

        self._create_table()

    ################################################################
    #
    def add_cols(self, source) :
        cols    = source.get_cols()
        types   = source.get_types()

        new_cols  = []
        new_types = []
        for i in range(len(cols)) :
            if cols[i] not in self.cols :
                new_cols.append(cols[i])
                new_types.append(types[i])
        self.cols.extend(new_cols)
        self.types.extend(new_types)

        self._alter_table(new_cols, new_types)

        row_ids   = self.get_values('__ROWID')
        
        for col in new_cols :
            new_vals = source.get_values(col)
            if len(row_ids) == 0 :
                for val in new_vals :
                    self._insert_internal(['__ROWID', col], [0, val])

                row_ids   = self.get_values('__ROWID')

            else :
                binds = zip(new_vals, row_ids)
                q = self._quoter(col)
                sql_base = 'UPDATE "%s" SET "%s" = %s WHERE "__ROWID" = %%d' % (self.name, col, q)
                cur = self.con.cursor()
                for bind in binds :
                    if bind[0] :
                        update_sql = sql_base % (str(bind[0]), bind[1])
                        cur.execute(update_sql)

        self.version += 1

    ################################################################
    #
    def add_rows(self, rows) :
        converted = [self._convert_row(row) for row in rows]
        self._bulk_add_rows(converted)
        self.version += 1

    ################################################################
    #
    def add_row(self, values, vers_inc=1) :
        if type(values) == type({}) :
            self._add_from_dict(values)
        elif type(values) == type([]) :
            self._add_from_list(values)
        elif type(values) == type(()) :
            self._add_from_list(list(values))
        elif type(values) == RowReference :
            self._add_from_dict(values.as_dict())
        else :
            raise Exception('Don''t know how to add %s ' % str(values))

        self.version += vers_inc

    ################################################################
    #
    def get_cols(self) :
        return list(self.cols)[1:]

    ################################################################
    #
    def get_types(self) :
        return list(self.types)[1:]

    ################################################################
    #
    def get_name(self) :
        return self.name[:-7]

    ################################################################
    #
    def get_row_count(self) :
        count_sql = 'SELECT count(*) FROM "%s"' % (self.name,)
        cur = self.con.cursor()
        cur.execute(count_sql)
        return cur.fetchone()[0]

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
    def get_values(self, col) :
        if col not in self.cols :
            raise Exception('Column %s not in data' % col)

        select_sql = 'SELECT "%s" FROM "%s" ORDER BY __ROWID ASC' % (col, self.name)
        cur = self.con.cursor()
        cur.execute(select_sql)
        vs = cur.fetchall()
        return [v[0] for v in vs]

    ################################################################
    #
    def get_rows(self, limit=None, hidden=1) :
        if limit is not None :
            select_sql = 'SELECT * FROM "%s" ORDER BY __ROWID ASC LIMIT %d' % (self.name, limit)
        else :
            select_sql = 'SELECT * FROM "%s" ORDER BY __ROWID ASC' % (self.name)

        cur = self.con.cursor()
        cur.execute(select_sql)
        vs = cur.fetchall()
        if hidden :
            vs = [v[hidden:] for v in vs]

        cols = [c[0] for c in cur.description[hidden:]]
        typs = self._cols_to_types(cols)
        ct = list(zip(cols, typs))

        return datatableresults.DataTableResults('temp', ct, vs)

        return vs

    ################################################################
    #
    def get_version(self) :
        return self.version

    ################################################################
    #
    def project(self, name, cols) :
        ct   = [v 
                for v in list(zip(self.get_cols(), self.get_types()))
                if v[0] in cols]

        base_row = dict(zip(cols, itertools.repeat(None)))
        
        def make_new_row(r) :
            values = {}
            values.update(base_row)
            values.update(r.as_dict())
            return values
        new_rows = [make_new_row(row) for row in self]

        new_table = self.factory.new_table(name, ct)
        new_table.add_rows(new_rows)
        return new_table

    ################################################################
    #
    def filter(self, name, filterfn) :
        ct   = list(zip(self.get_cols(), self.get_types()))
        new_rows = [row for row in self if filterfn(row.as_dict())]
        new_table = self.factory.new_table(name, ct)
        new_table.add_rows(new_rows)
        return new_table

    ################################################################
    #
    def select(self, name, *selectors) :
        ct = [(s.get_name(), s.get_type()) for s in selectors]
        new_table = self.factory.new_table(name, ct)
        for row in self :
            d = row.as_dict()
            r = [s(d) for s in selectors]
            new_table._add_from_list(r)
        return new_table

    ################################################################
    #
    def group_by(self, name, keys, *aggregators) :
        ct = [(k.get_name(), k.get_type()) for k in keys]
        ct.extend([(a.get_name(), a.get_type()) for a in aggregators])

        def key_func(row) :
            r = row.as_dict()
            key = tuple([k(r) for k in keys])
            return key
            
        temp = [(key_func(r), r) for r in self]
        temp.sort(key=lambda x : x[0])

        new_data = []
        for key, rows in itertools.groupby(temp, lambda x : x[0]) :
            rvals = [x[1].as_dict() for x in rows]
            new_row = list(key)
            new_row.extend([a(rvals) for a in aggregators])
            new_data.append(new_row)

        return datatableresults.DataTableResults(name, ct, new_data)
                 
    ################################################################
    #
    def order_by(self, name, *selectors) :
        temp = []
        for row in self :
            r = row.as_dict()
            keys = tuple([s(r) for s in selectors])
            temp.append((keys, r))

        temp.sort(key=lambda x : x[0])

        ct = [(s.get_name(), s.get_type()) for s in selectors]
        new_table = self.factory.new_table(name, ct)
        new_table.add_rows([x[1] for x in temp])
        return new_table

    ################################################################
    #
    def __iter__(self) :
        cur = self.con.cursor()
        row_sql = 'SELECT * FROM "%s"' % (self.name,)
        cur.execute(row_sql)
        return DataTableIterator(cur)

    ################################################################
    #
    def _create_table(self) :
        cur = self.con.cursor()
        delete_sql = 'DROP TABLE IF EXISTS "%s"' % self.name
        cur.execute(delete_sql)

        col_sql = ','.join(['"%s" %s' % (self.cols[i], self.types[i])
                            for i in range(len(self.cols))])
        create_sql = 'CREATE TABLE "%s" ( %s );' % (self.name, col_sql)
        cur.execute(create_sql)

    ################################################################
    #
    def _convert_row(self, row) :
        self.row_id += 1
        data = [self.row_id]

        if type(row) == type({}) :
            data.extend(row.get(col, None) for col in self.cols[1:])
        elif type(row) in [type([]), type(())] :
            data.extend(row)
        elif type(row) == RowReference :
            data.extend(row.values())
        else :
            raise Exception(
                'Don''t know how to add row from: %s ' % str(row)
            )

        if len(data) != len(self.cols) :
            raise Exception(
                'Wrong number of values for new row with cols %s: %s' % 
                (str(self.cols), str(data))
                    
            )

        return data

    ################################################################
    #
    def _bulk_add_rows(self, converted) :
        insert_sql = 'INSERT INTO "%s" VALUES (%s)' % (self.name, ','.join(['?'] * len(self.cols)))
        cur = self.con.cursor()
        cur.executemany(insert_sql, converted)
        
    ################################################################
    #
    def _add_from_dict(self, row) :
        data = [row.get(col, None) for col in self.cols]
        self._insert_internal(self.cols, data)
        
    ################################################################
    #
    def _add_from_list(self, row) :
        data        = [0]
        data.extend(row[:len(self.cols)-1])
        cols        = self.cols[:len(data)]
        self._insert_internal(cols, data)

    ################################################################
    #
    def _insert_internal(self, cols, vals) :
        self.row_id += 1
        vals[0] = self.row_id

        if None in vals :
            cvs = list(zip(cols, vals))
            cvs = [cv for cv in cvs if cv[1] is not None]
            cs  = [cv[0] for cv in cvs]
            vs  = [cv[1] for cv in cvs]
        else :
            cs = cols
            vs = vals

        value_sql = ','.join([self._quoter(cols[i]) % str(vs[i]) 
                              for i in range(len(vs))])

        col_sql = ','.join(['"%s"' % c for c in cs])
        insert_sql = 'INSERT INTO "%s" (%s) VALUES (%s)' % (self.name, col_sql, value_sql)
        cur = self.con.cursor()
        cur.execute(insert_sql)
        
    ################################################################
    #
    def _alter_table(self, names, types) :
        cur = self.con.cursor()
        for i in range(min(len(names), len(types))) :
            alter_sql = 'ALTER TABLE "%s" ADD COLUMN "%s" %s' % (self.name, names[i], types[i])
            cur.execute(alter_sql)

    ################################################################
    #
    def _quoter(self, col) :
        j = self.cols.index(col)
        if self.types[j] == 'TEXT' :
            return '"%s"'
        else :
            return '%s'

################################################################
#
if __name__ == '__main__' :
    print ('Run testdatatable.py for unit tests.')
