
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "strdup.h"

#include "SqliteDB.h"

using namespace std;

SqliteDB::SqliteDB(char const * const _dbfile)
	: db(NULL)
	, dbfile(strdup(_dbfile))
{
}

bool SqliteDB::open(bool verbose)
{
	db = fopen(dbfile, "rb");
	if ( *this ) {
		return validate(verbose);
	}
	return false;
}

void SqliteDB::close()
{
	if ( *this ) {
		fclose(db);
		db = NULL;
	}
}


bool SqliteDB::validate(bool verbose)
{
	if ( ! *this ) {
		return false;
	}
	if ( ! header.read(db, verbose) ) {
		close();
		return false;
	}
	return true;
}

SqliteDB::operator bool() const
{
	return db != NULL;
}


