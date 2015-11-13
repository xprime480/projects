
import hdbcli
import dbapi

class QueryResults(object) :
    def __init__(self, conn, stmt) :
        self.results = []
        self.query = stmt
        self.err = None
        cursor = None
        self.columns = []

        if not conn :
            self.err = "No valid connection"
            return

        try :
            cursor = conn.cursor()
            if cursor.execute(stmt) :
                self.columns = [col[0] for col in cursor.description]
                for row in cursor.fetchall() :
                    self.results.append(dict(zip(self.columns, row)))
                self.err  = None
            else :
                self.err = "Could not execute cursor"

        except dbapi.Error as e :
            self.err = "Error: %s" % e[1]
            
        finally :
            if cursor : 
                cursor.close()
            
    def get_error(self) :
        return self.err

    def get_query(self) :
        return self.query

    def get_columns(self) :
        return self.columns[:]

    def get_row_count(self) :
        return len(self.results)

    def get_rows(self) :
        return self.results[:]

    def __call__(self, row, column) :
        if len(self.results) <= row :
            return None
        if column not in self.columns :
            return None
        return self.results[row][column]


        
