#!/usr/bin/env python

import sys
import os.path
import ConfigParser

class Mapper(object) :
    def __init__(self, root, data) :
        self.root = root
        self.data = data
        self.kv   = {}

    def run(self) :
        with open(self.data) as data :
            for line in data.readlines() :
                test = line[:-1]
                self.kv[test] = self.find_fut(test)

    def find_fut(self, test) :
        while test :
            value = self.check_for_name(test)
            if value :
                return value
            (test, last) = os.path.split(test)

        return 'None found'

    def check_for_name(self, name) :
        target = os.path.join(self.root, name, 'properties.ini')
        config = ConfigParser.RawConfigParser()

        good = config.read([target])
        if not good :
            return None

        SECTION = 'Main'
        OPTION  = 'functionName'

        if not config.has_section(SECTION) :
            return None

        if not config.has_option(SECTION, OPTION) :
            return None

        return config.get(SECTION, OPTION)

    def report(self) :
        print ('test - function under test')
        print ('-' * 80)
        for kv in self.kv.items() :
            print ('%s - %s' % kv)


def main():
    """Open the data file and loop over it."""

    if len(sys.argv) < 3 :
        print ('Insufficient arguments.  Usage: %s path datafile' % sys.argv[0])
        return 1

    try :
        m = Mapper(sys.argv[1], sys.argv[2])
        m.run()
        m.report()
    except :
        print 'Error executing', sys.exc_info()[0]
        return 1

    return 0
    

if __name__ == '__main__' :
    rv = main()
    sys.exit(rv)
