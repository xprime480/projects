#!/usr/bin/python

import csv
import datetime

fmt = "%Y-%m-%d %H:%M:%S.000000"
addDay = datetime.timedelta(1)
toEndOfDay = datetime.timedelta(1, -1)

def read(filename) :
    headers = ''
    rows = []

    with open(filename) as csvfile :
        contents = csv.reader(csvfile)
        headers = contents.next()
        for row in contents :
            rows.append(row)
    
    return (headers, rows)
            
def fill_internal(headers, rows, proc) :
    if len(rows) == 0 :
        return rows

    newrows = []

    import itertools
    for keys, values in itertools.groupby(rows, lambda row : row[:2]):
        prod_id = keys[0]
        loc_id  = keys[1]

        group = list(values)
        currentDate = datetime.datetime.strptime(group[0][2], fmt)
        nextDate = currentDate + addDay

        for row in group :
            currentDate = datetime.datetime.strptime(row[2], fmt)
            while nextDate < currentDate :
                newrows.append(proc(prod_id, loc_id, nextDate))
                nextDate = nextDate + addDay
            newrows.append(row)
            nextDate = currentDate + addDay

    return newrows

def fill_cons(headers, rows) :
    def proc(prod_id, loc_id, date) :
        return [prod_id, loc_id, date.strftime(fmt),
                (date + toEndOfDay).strftime(fmt), '0.0']
    return fill_internal(headers, rows, proc)

def fill_pos(headers, rows) :
    def proc(prod_id, loc_id, date) :
        return [prod_id, loc_id, date.strftime(fmt),'', 
                (date + toEndOfDay).strftime(fmt), '0.0', '0.0']
    return fill_internal(headers, rows, proc)

def write_one(data) :
    print ','.join(['"%s"' % x for x in data])

def write(headers, rows) :
    write_one(headers)
    for row in rows :
        write_one(row)

def main(filename) :
    headers, rows = read(filename)
    if len(headers) == 5 :
        newrows = fill_cons(headers, rows)
    else :
        newrows = fill_pos(headers, rows)

    write(headers, newrows)

if __name__ == '__main__' :
    import sys
    if len(sys.argv) > 1 :
        main(sys.argv[1])


