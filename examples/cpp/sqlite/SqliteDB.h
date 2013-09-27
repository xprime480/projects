#if ! defined(SQLITEDB_H)
#define SQLITEDB_H 1

#include <cstdio>

#include "SqliteDbHeader.h"


class SqliteDB {
public:
	SqliteDB(char const * const dbfile);

	bool open(bool verbose = false);
	void close();

	operator bool() const;
protected:
private:
	FILE * db;
	char const * const dbfile;

	SqliteDbHeader header;

	bool validate(bool verbose);
};

#endif
