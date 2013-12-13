
import sys

import datatableadapter

################################################################
#
class ReadOnlyAdapter(datatableadapter.DataTablePassthru) :

    ################################################################
    #
    def __init__(self, name, base) :
        super().__init__(name, base)
        self.original_version = base.version

    ################################################################
    #
    def bad_operation(self, operation) :
        raise DataTableAdapterException(
            'Attempting to run %s on read-only table %s' % 
            (operation, self.get_name())
        )

    ################################################################
    #
    def add_cols(self, source) :
        self.bad_operation(__name__)

    ################################################################
    #
    def add_rows(self, rows) :
        self.bad_operation(__name__)

    ################################################################
    #
    def add_row(self, values, _version_incr=1) :
        self.bad_operation(__name__)
