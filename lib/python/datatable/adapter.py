
import sys

import datatable.base

################################################################
#
class DataTableAdapterException(Exception) :
    def __init__(self, text) :
        super().__init__(text)

################################################################
#
class DataTableAdapter(datatable.base.DataTableBase) :

    ################################################################
    #
    def __init__(self, name, base) :
        super().__init__(name)
        self.base        = base
        self.version     = base.get_version()

    ################################################################
    #
    def get_name(self) :
        return '%s$%s' % (super().get_name(), self.base.get_name())


################################################################
#
class DataTablePassthru(DataTableAdapter) :

    ################################################################
    #
    def __init__(self, name, base) :
        super().__init__(name, base)

    ################################################################
    #
    def add_cols(self, source) :
        return self.base.add_cols(source)

    ################################################################
    #
    def add_rows(self, rows) :
        return self.base.add_rows(rows)

    ################################################################
    #
    def add_row(self, values, _version_incr=1) :
        return self.base.add_row(values, _version_incr)

    ################################################################
    #
    def get_version(self) :
        return self.base.get_version()

    ################################################################
    #
    def get_cols(self) :
        return self.base.get_cols()

    ################################################################
    #
    def get_row_count(self) :
        return self.base.get_row_count()

    ################################################################
    #
    def get_value(self, col, i) :
        return self.base.get_value(col, i)

    ################################################################
    #
    def get_values(self, *cols) :
        return self.base.get_values(*cols)

    ################################################################
    #
    def get_rows(self) :
        return self.base.get_rows()

    ################################################################
    #
    def project(self, name, cols) :
        return self.base.project(name, cols)

    ################################################################
    #
    def filter(self, name, filterfn) :
        return self.base.filter(name, filterfn)

    ################################################################
    #
    def select(self, name, *selectors) :
        return self.base.select(name, *selectors)

    ################################################################
    #
    def group_by(self, name, keys, *aggregators) :
        return self.base.group_by(name, keys, *aggregators)

    ################################################################
    #
    def order_by(self, name, *selectors) :
        return self.base.order_by(name, *selectors)

    ################################################################
    #
    def __iter__(self) :
        return self.base.__iter__()

    ################################################################
    #
    def display(self, f=sys.stderr, row_limit=20) :
        return self.base.display(f, row_limit)
