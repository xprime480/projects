#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sqlite3 as lite
import sys
import unittest

class Sqlite3UsageTest(unittest.TestCase) :
    ##################################################################
    #
    def __init__(self, n='runTest') :
        super().__init__(n)
    
    def test01(self) :
        with lite.connect('test.db') as con :
            cur = con.cursor()    
            cur.execute('SELECT SQLITE_VERSION()')
            data = cur.fetchone()
            self.assertEqual(('3.7.17',), data)

    def test02(self) :
        with lite.connect('test.db') as con :
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

            cur.execute('SELECT count(*) FROM Cars')
            data = cur.fetchone()
            self.assertEqual((8,), data)

            cur.execute('SELECT * FROM Cars WHERE id = 5')
            data = cur.fetchone()
            self.assertEqual((5, 'Bentley', 350000), data)
            

    def test03(self) :
        cars = [
            (1, 'Audi', 52642),
            (2, 'Mercedes', 57127),
            (3, 'Skoda', 9000),
            (4, 'Volvo', 29000),
            (5, 'Bentley', 350000),
            (6, 'Hummer', 41400),
            (7, 'Volkswagen', 21600)
        ]

        names = [x[1] for x in cars]

        with lite.connect('test.db') as con :
            cur = con.cursor()    
            cur.execute("DROP TABLE IF EXISTS Cars")
            cur.execute("CREATE TABLE Cars(Id INT, Name TEXT, Price INT)")
            cur.executemany("INSERT INTO Cars VALUES(?, ?, ?)", cars)

            cur.execute('SELECT count(*) FROM Cars')
            data = cur.fetchone()
            self.assertEqual((7,), data)

            cur.execute('SELECT * FROM Cars WHERE id = 5')
            data = cur.fetchone()
            self.assertEqual((5, 'Bentley', 350000), data)

            cur.execute("SELECT * FROM Cars")
            rows = cur.fetchall()
            for row in rows:
                self.assertTrue(row in cars)
                cars.remove(row)
            self.assertEqual([], cars)

            con.row_factory = lite.Row
            cur = con.cursor() 
            cur.execute("SELECT * FROM Cars")
            rows = cur.fetchall()
            for row in rows:
                n = row["Name"]
                self.assertTrue(n in names)
                names.remove(n)
            self.assertEqual([], names)

            uId = 1
            uPrice = 62300 
            cur = con.cursor()    
            cur.execute("UPDATE Cars SET Price=? WHERE Id=?", (uPrice, uId))        
            con.commit()
            self.assertEqual(1, cur.rowcount)


    def test04(self) :
        with lite.connect('test.db') as con :
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

            cur.execute('SELECT count(*) FROM Cars')
            data = cur.fetchone()
            self.assertEqual((8,), data)

            cur.execute('SELECT * FROM Cars WHERE Price < 10000')
            data = cur.fetchone()
            self.assertEqual((3, 'Skoda', 9000), data)

    def test05(self) :
        with lite.connect('test.db') as con :
            cur = con.cursor()    
            cur.execute("DROP TABLE IF EXISTS Friends")
            cur.execute("CREATE TABLE Friends(Id INTEGER PRIMARY KEY, Name TEXT);")
            cur.execute("INSERT INTO Friends(Name) VALUES ('Tom');")
            cur.execute("INSERT INTO Friends(Name) VALUES ('Rebecca');")
            cur.execute("INSERT INTO Friends(Name) VALUES ('Jim');")
            cur.execute("INSERT INTO Friends(Name) VALUES ('Robert');")

            lid = cur.lastrowid
            self.assertEqual(4, cur.lastrowid)

if __name__ == '__main__' :
    unittest.main()
