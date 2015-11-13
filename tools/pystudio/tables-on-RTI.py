
import pystudio
import hdb_session

def main() :
    stmt = "SELECT schema_name, table_name FROM sys.tables ORDER BY schema_name ASC, table_name ASC"
    session = hdb_session.HdbSession("lddbrti.wdf.sap.corp", 30215, "DAVISMIC", "Base1616B")
    pystudio.dump(session.get_results(stmt))
    session.end()

main()
