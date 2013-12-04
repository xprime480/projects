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
        self.name        = name
        self.version     = 0

    ################################################################
    #
    def __unsupported(self, op) :
        raise DataTableBaseException('Operation %s is not supported.' % op)

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
        self.__unsupported(__name__)

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
    def get_rows(self) :
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
        self.__unsupported(__name__)

