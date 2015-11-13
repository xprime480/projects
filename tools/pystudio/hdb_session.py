
import hdbcli
import dbapi

import query_results

class HdbSession(object) :
    def __init__(self, sys, port, user, pwd) :
        self.user = user
        try :
            self.conn = dbapi.connect(sys,port, user, pwd)
            self.err  = None
        except dbapi.Error as e :
            self.conn = None
            self.err = "Login error: %s" % e[1]

    def get_error(self) :
        return self.err

    def get_user(self) :
        return self.user

    def get_db_time(self) :
        stmt = "SELECT current_timestamp AS now FROM dummy";
        results = query_results.QueryResults(self.conn, stmt)
        self.err = results.get_error()
        return results(0, 'NOW')

    def get_results(self, stmt) :
        return query_results.QueryResults(self.conn, stmt)

    def end(self) :
        if self.conn :
            self.conn.close()
        self.conn = None









