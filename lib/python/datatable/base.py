#!/usr/bin/env python3

import sys

################################################################
#
class DataTableBaseException(Exception) :
    def __init__(self, text) :
        super().__init__(text)

################################################################
#
class DataTableBase(object) :

    ################################################################
    #
    def __init__(self, name) :
        self.name    = name
        self.version = 0
        self.cols    = []
        self.types   = []
        self.col_type_map = {}

    ################################################################
    #
    def __unsupported(self, op) :
        raise DataTableBaseException('Operation %s is not supported.' % op)

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

            if typef in [int, 'INTEGER'] :
                ctype = 'INTEGER'
            elif typef in [float, 'REAL'] :
                ctype = 'REAL'
            elif typef in [str, 'TEXT'] :
                ctype = 'TEXT'
            else :
                raise Exception('Bad type for column: %s [%s]' % (cname, str(typef)))

            self.cols.append(cname)
            self.types.append(ctype)
            self.col_type_map[cname] = ctype

    ################################################################
    #
    def _cols_to_types(self, cols) :
        return [m[1] for m in self.col_type_map if m[1] in cols]

    ################################################################
    #
    def add_cols(self, source) :
        self.__unsupported(__name__)

    ################################################################
    #
    def add_rows(self, rows) :
        self.__unsupported(__name__)

    ################################################################
    #
    def add_row(self, values, _version_incr=1) :
        self.__unsupported(__name__)

    ################################################################
    #
    def get_version(self) :
        return self.version

    ################################################################
    #
    def get_cols(self) :
        return self.cols[:]

    ################################################################
    #
    def get_name(self) :
        return self.name

    ################################################################
    #
    def get_row_count(self) :
        self.__unsupported(__name__)

    ################################################################
    #
    def get_value(self, col, i) :
        self.__unsupported(__name__)

    ################################################################
    #
    def get_values(self, *cols) :
        self.__unsupported(__name__)

    ################################################################
    #
    def get_rows(self, **kw) :
        self.__unsupported(__name__)

    ################################################################
    #
    def project(self, name, cols) :
        self.__unsupported(__name__)

    ################################################################
    #
    def filter(self, name, filterfn) :
        self.__unsupported(__name__)

    ################################################################
    #
    def select(self, name, *selectors) :
        self.__unsupported(__name__)

    ################################################################
    #
    def group_by(self, name, keys, *aggregators) :
        self.__unsupported(__name__)

    ################################################################
    #
    def order_by(self, name, *selectors) :
        self.__unsupported(__name__)

    ################################################################
    #
    def __iter__(self) :
        self.__unsupported(__name__)

    ################################################################
    #
    def display(self, f=sys.stderr, row_limit=20) :
        print ('Table %s:' % self.get_name(), file=f)

        toprint = self.get_rows(limit=row_limit)
        cols = toprint.get_cols()
        print ('Columns:', cols, file=f)
        rows_printed = 0
        for row in toprint :
            print (' Values:', row, file=f)
            rows_printed += 1
            if rows_printed >= row_limit :
                break

        print ('', file=f)
        print ('Row count = %d' % self.get_row_count(), file=f)
