#!/usr/bin/python

import os

subdirs = ['data_input', 'data_ref']


def find_data_files(path) :
    hdr = 'CSV files for %s' % (path)
    print hdr
    print '=' * len(hdr)
    print

    paths = {}
    for sub in subdirs : 
        paths[sub] = {}

    while True :
        parent, last = os.path.split(path)
        if last == 'UDF_CORE' or parent == '' :
            break

        for sub in subdirs : 
            p = os.path.join(path, sub)
            try :
                files = os.listdir(p)
                for f in files :
                    if f[-4:] == '.csv' and not paths[sub].has_key(f) :
                        paths[sub][f] = path
            except OSError :
                pass
        
        path = parent[:]

    for sub in subdirs :
        print sub
        print '-' * len(sub)
        files = [(dir,file) for file,dir in paths[sub].items()]
        files.sort()
        for dir,file in files :
            print os.path.join(dir,sub,file)
        print
        

if __name__ == '__main__' :
    import sys
    for path in sys.argv[1:] :
        find_data_files(path)
