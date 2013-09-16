#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sqlite3 as lite
import sys

def test01(con) :
    cur = con.cursor()    
    cur.execute('SELECT SQLITE_VERSION()')
    data = cur.fetchone()
    print ("SQLite version: %s" % data)

def test02(con) :
    cur = con.cursor()    
    cur.execute("DROP TABLE IF EXISTS Cars")
    cur.execute("CREATE TABLE Cars(Id INT, Name TEXT, Price INT)")
    cur.execute("INSERT INTO Cars VALUES(1,'Audi',52642)")
    cur.execute("INSERT INTO Cars VALUES(2,'Mercedes',57127)")
    cur.execute("INSERT INTO Cars VALUES(3,'Skoda',9000)")
    cur.execute("INSERT INTO Cars VALUES(4,'Volvo',29000)")
    cur.execute("INSERT INTO Cars VALUES(5,'Bentley',350000)")
    cur.execute("INSERT INTO Cars VALUES(6,'Citroen',21000)")
    cur.execute("INSERT INTO Cars VALUES(7,'Hummer',41400)")
    cur.execute("INSERT INTO Cars VALUES(8,'Volkswagen',21600)")

def test03(con) :
    cars = [
        (1, 'Audi', 52642),
        (2, 'Mercedes', 57127),
        (3, 'Skoda', 9000),
        (4, 'Volvo', 29000),
        (5, 'Bentley', 350000),
        (6, 'Hummer', 41400),
        (7, 'Volkswagen', 21600)
    ]

    cur = con.cursor()    
    cur.execute("DROP TABLE IF EXISTS Cars")
    cur.execute("CREATE TABLE Cars(Id INT, Name TEXT, Price INT)")
    cur.executemany("INSERT INTO Cars VALUES(?, ?, ?)", cars)

def test04(con) :
    cur = con.cursor()  
    cur.executescript("""
        DROP TABLE IF EXISTS Cars;
        CREATE TABLE Cars(Id INT, Name TEXT, Price INT);
        INSERT INTO Cars VALUES(1,'Audi',52642);
        INSERT INTO Cars VALUES(2,'Mercedes',57127);
        INSERT INTO Cars VALUES(3,'Skoda',9000);
        INSERT INTO Cars VALUES(4,'Volvo',29000);
        INSERT INTO Cars VALUES(5,'Bentley',350000);
        INSERT INTO Cars VALUES(6,'Citroen',21000);
        INSERT INTO Cars VALUES(7,'Hummer',41400);
        INSERT INTO Cars VALUES(8,'Volkswagen',21600);
        """)
    con.commit()

def test05(con) :
    cur = con.cursor()    
    cur.execute("DROP TABLE IF EXISTS Friends")
    cur.execute("CREATE TABLE Friends(Id INTEGER PRIMARY KEY, Name TEXT);")
    cur.execute("INSERT INTO Friends(Name) VALUES ('Tom');")
    cur.execute("INSERT INTO Friends(Name) VALUES ('Rebecca');")
    cur.execute("INSERT INTO Friends(Name) VALUES ('Jim');")
    cur.execute("INSERT INTO Friends(Name) VALUES ('Robert');")
        
    lid = cur.lastrowid
    print ("The last Id of the inserted row is %d" % lid)

def test06(con) :
    cur = con.cursor()    
    cur.execute("SELECT * FROM Cars")
    rows = cur.fetchall()
    for row in rows:
        print (row)

def test07(con) :
    cur = con.cursor()    
    cur.execute("SELECT * FROM Cars")
    while True:
        row = cur.fetchone()
        if row == None:
            break
        print (row[0], row[1], row[2])

def test08(con) :
    con.row_factory = lite.Row
    cur = con.cursor() 
    cur.execute("SELECT * FROM Cars")
    rows = cur.fetchall()
    for row in rows:
        print ("%02d %20s %6d" % (row["Id"], row["Name"], row["Price"]))

def test09(con) :
    con.row_factory = lite.Row
    cur = con.cursor() 
    cur.execute("SELECT * FROM Cars")
    while True:
        row = cur.fetchone()
        if row == None:
            break
        print ("%02d %20s %6d" % (row["Id"], row["Name"], row["Price"]))

def test10(con) :
    uId = 1
    uPrice = 62300 
    cur = con.cursor()    
    cur.execute("UPDATE Cars SET Price=? WHERE Id=?", (uPrice, uId))        
    con.commit()
    print ("Number of rows updated: %d" % cur.rowcount)

if __name__ == '__main__' :
    def runtest(t) :
        try:
            with lite.connect('test.db') as con :
                t(con)
        except lite.Error as e:
            print ("Error %s:" % e.args[0])
            sys.exit(1)

        print (">>> Completed", t.__name__)

#    runtest(test01)        
#    runtest(test02)
#    runtest(test03)
#    runtest(test04)
#    runtest(test05)
#    runtest(test06)
#    runtest(test07)
#    runtest(test08)
#    runtest(test09)
#    runtest(test10)

    print ()
    print (">>> All tests completed")








