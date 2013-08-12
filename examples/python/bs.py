#!/usr/bin/env python

from BeautifulSoup import *
from itertools import imap
from xutils import *

strVersion = '^([\.0-9]+).*'
reVersion  = re.compile(strVersion)

def getText(node) :
    l = ''.join(node.fetchText(lambda x : True))
    c = convertEntity(l)
    if len(c) >= 4 and 'NONE' == c[:4] :
        c = '6.66'
    else :
        mVersion = reVersion.match(c)
        if mVersion :
            c = mVersion.group(1)
    return c

def findTable(stream) :
    soup = cookSoup(stream)
    return soup.fetch('td', {'colspan':'4'})[0].parent.parent

def parseTable(table) :
    directory = ''
    files     = []
    
    rows = table.fetch('tr', recursive=False)
    for row in rows[1:]  :
        columns = row.fetch('td', recursive=False)
        count = len(columns)
        if 1 == count :
            directory = columns[0].fetch('i')[0].string
            #print directory
        elif count < 4 :
            raise 'Not enough columns'
        else  :
            file = getText(columns[0])
            old  = getText(columns[1])
            new  = getText(columns[2])
            # print '\t', file, old, new
            files.append((directory, file, old, new))

    return files

def main(args) :
    for f in args :
        for data in parseTable(findTable(open_anything(f))) :
            print data
        print '*' * 64

if '__main__' == __name__ :
    #main(['bs.html', 'bs2.html', 'http://khizilla/cvszilla/transaction.cgi?id=20278'])
    print cookSoup(open_anything('http://contra/doxygen/Research/html/classUsbafKpic.html')).prettify()
