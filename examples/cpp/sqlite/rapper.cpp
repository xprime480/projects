
#include <iostream>

#include "SqliteDB.h"

using namespace std;

int main(int argc, char ** argv)
{

	SqliteDB db(argv[1]);
	db.open(true);
	if ( db ) {
		cout << "open succeeded" << endl;
	}
	else {
		cout << "open failed" << endl;
	}
	db.close();

	return 0;
	
}

