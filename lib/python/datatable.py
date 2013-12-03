#!/usr/bin/python3

import itertools
import sys
import sqlite3 as lite

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
                row.append(self.data[self.cols.index[col]])
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

    def __next__(self) :
        data = self.cur.fetchone()
        if not data :
            raise StopIteration
        return RowReference(self.desc, data)
    
################################################################
#
class DataTable(object) :
    
    ################################################################
    #
    def __init__(self, factory, con, name, cols=[]) :
        self.factory = factory
        self.con     = con
        self.name    = name
        self.cols    = ['__ROWID']
        self.types   = ['INTEGER']
        self._extend_cols(cols)
        self.row_id = 0

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
        elif type(values) == type(()) :
            self._add_from_list(list(values))
        elif type(values) == RowReference :
            self._add_from_dict(values.as_dict())
        else :
            raise Exception('Don''t know how to add %s ' % str(values))
            
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
        col = self.rows[col]
        if len(col) <= i :
            raise Exception('Table has fewer than %d rows' % i)
        return col[i]

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
    def get_rows(self) :
        select_sql = 'SELECT * FROM "%s" ORDER BY __ROWID ASC' % (self.name)
        cur = self.con.cursor()
        cur.execute(select_sql)
        vs = cur.fetchall()
        return [v[1:] for v in vs]

    ################################################################
    #
    def project(self, name, cols) :
        ct   = [v 
                for v in list(zip(self.get_cols(), self.get_types()))
                if v[0] in cols]
        new_table = self.factory.new_table(name, ct)
        base_row = dict(zip(cols, itertools.repeat(None)))
        for row in self :
            values = {}
            values.update(base_row)
            values.update(row.as_dict())
            new_table.add_row(values)
        return new_table

    ################################################################
    #
    def filter(self, name, filterfn) :
        ct   = list(zip(self.get_cols(), self.get_types()))
        new_table = self.factory.new_table(name, ct)
        for row in self :
            d = row.as_dict()
            if filterfn(d) :
                new_table._add_from_dict(d)
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
        new_table = self.factory.new_table(name, ct)

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
    def display(self, f=sys.stderr) :
        print ('\n\n', file=f)
        print ('Table %s:' % self.name, file=f)

        cur = self.con.cursor()
        row_sql = 'SELECT * FROM "%s"' % (self.name,)
        cur.execute(row_sql)

        cols = [c[0] for c in cur.description]
        print ('Columns:', cols, file=f)
        for row in cur.fetchall() :
            print (' Values:', row, file=f)

        print ('', file=f)
        print ('Row count = %d' % self.get_row_count(), file=f)

    ################################################################
    #
    def _extend_cols(self, cols) :
        for i in range(len(cols)) :
            c = cols[i]
            if type(c) == type('') :
                cname = c
                typef = str
            elif type(c) == type((0,)) :
                if len(c) < 2 :
                    raise Exception('Bad tuple for column definition')
                cname = c[0]
                typef = c[1]

            if self.cols.count(cname) > 0 :
                raise Exception('Duplicate column name: %s' % cname)

            self.cols .append(cname)
            if typef in [int, 'INTEGER'] :
                self.types.append('INTEGER')
            elif typef in [float, 'REAL'] :
                self.types.append('REAL')
            elif typef in [str, 'TEXT'] :
                self.types.append('TEXT')
            else :
                raise Exception('Bad type for column: %s [%s]' % (cname, str(typef)))

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


if __name__ == '__main__' :
    print ('Run testdatatable.py for unit tests.')
