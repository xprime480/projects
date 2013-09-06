#!/usr/bin/env python3

import csv
import sys

####################################################################
#
csv_dialect = 'pio' 
csv.register_dialect(csv_dialect, skipinitialspace=True)

####################################################################
#
class CsvFilteringWriter(csv.DictWriter) :
    def __init__(self, handle, fieldnames, dialect) :
        csv.DictWriter.__init__(
            self, 
            handle, 
            fieldnames=fieldnames, 
            dialect=dialect
        )
        self.fields = fieldnames

    def writerow(self, row) :
        newrow = row.copy()
        for key in row.keys() :
            if key not in self.fields :
                newrow.pop(key)

        csv.DictWriter.writerow(self, newrow)

####################################################################
#
class CsvFileIo(object) :
    """Wrapper for CsvFileIo which may be existing file stream"""

    def __init__(self, spec, dir_is_output, header=None) :
        self.spec          = spec
        self.dir_is_output = dir_is_output
        self.handle        = None
        self.csv           = None
        self.header        = header

    def __enter__(self) :
        """Create a csv reader/writer"""

        if self.dir_is_output :
            if self.spec :
                self.handle = open(self.spec, 'w')
            else :
                self.handle = sys.stdout

            self.csv = CsvFilteringWriter(
                self.handle, 
                fieldnames=self.header,
                dialect=csv_dialect)

        else :
            if self.spec :
                self.handle = open(self.spec)
            else :
                self.handle = sys.stdin

            self.csv = csv.DictReader(self.handle, dialect=csv_dialect)

        return self.csv

    def __exit__(self, type, value, traceback) :
        """Clean up the csv reader/writer"""
        if self.spec :
            self.handle.close()
        self.handle = None

