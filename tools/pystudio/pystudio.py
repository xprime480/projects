
import hdb_session

def make_session() :
    def prompt(text, default = "") :
        return raw_input("%s [%s]: " % (text, default)) or default

    sys  = prompt("System", "localhost")
    port = int(prompt("Port", "30215"))
    user = prompt("User", "SYSTEM")
    import getpass
    pwd  = getpass.getpass("Password: ")

    return hdb_session.HdbSession(sys, port, user, pwd)

def dump(resultset, perpage=25) :
    err = resultset.get_error()
    if err :
        query = resultset.get_query()
        print "%s resulted in error %s" % (query, err)
        return

    columns = resultset.get_columns()
    rowcount = resultset.get_row_count()
    column_widths = dict([(c, len(c)) for c in columns])
    rows = resultset.get_rows() 
    for row in rows :
        for col in columns :
            column_widths[col] = max(column_widths[col], len(str(row[col])))

    fmt = ' '.join(["%%(%s)%ds" % (col, column_widths[col]) for col in columns])
    sep = ' '.join(["-" * column_widths[col] for col in columns ])

    while rows :
        page_rows = rows[:perpage]
        rows = rows[perpage:]

        print fmt % dict([(col,col) for col in columns])
        print sep
        for row in page_rows :
            print fmt % row
        print

def test_schemata(session) :
    schemata = session.get_results("SELECT DISTINCT schema_name AS schema FROM sys.tables ORDER BY schema_name ASC")
    dump(schemata)

    tabs = session.get_results("SELECT schema_name, table_name FROM sys.tables ORDER BY schema_name ASC, table_name ASC")
    dump(tabs)

    summary = session.get_results("SELECT schema_name AS schema, count(*) as table_count FROM sys.tables GROUP BY schema_name ORDER BY schema_name ASC")
    dump(summary)

def main(session) :
    print "Connected as %s at %s" % (session.get_user(), session.get_db_time())
    # test_schemata(session)
    stmt = """
SELECT NULL AS nullish FROM dummy
UNION ALL
SELECT 2 AS nullish FROM dummy
"""
    dump(session.get_results(stmt))
    session.end()

if __name__ == '__main__' :
    main(hdb_session.HdbSession("localhost", 30215, "SYSTEM", "manager"))
