
#include <iostream>
#include <cstring>
#include <arpa/inet.h>

#include "SqliteDbHeader.h"

using namespace std;

namespace {
	static char const * const headerPrefix = "SQLite format 3";

	void convert(unsigned char & v)
	{
		// nop
	}

	void convert(unsigned short & v) 
	{
		v = ntohs(v);
	}

	void convert(unsigned long & v) 
	{
		v = ntohl(v);
	}

	template <typename T>
	bool readFromFile(FILE * f, T * data, char const * message)
	{
		size_t nread = fread((void *) data, sizeof(T), 1, f);
		if ( nread != 1 ) {
			cerr << "Not enough bytes in file for " << message
				<< endl;
			cerr << "\tread " << nread << "; wanted "
				<< sizeof(T) << endl;
			return false;
		}
		convert(*data);
		return true;
	}

	template <typename T>
	bool readFromFile(FILE * f, T * data, char const * message, T expected)
	{
		if ( ! readFromFile(f, data, message) ) {
			return false;
		}
		if ( *data != expected ) {
			cerr << message << " has bad data" << endl;
		}
		return true;
	}
}



bool SqliteDbHeader::read(FILE * f, bool verbose)
{
	size_t nread = fread(magic, sizeof (char), MagicSize, f);
	if ( nread != MagicSize ) {
		cerr << "Header too short" << endl;
		return false;
	}

	if ( strncmp(headerPrefix, magic, MagicSize) ) {
		cerr << "Header has bad data" << endl;
		return false;
	}

	if ( ! readFromFile(f, &pageSize, "pageSize") ) {
		return false;
	}
	if ( verbose ) {
		cout << "page size = " << pageSize << endl;
	}

	if ( ! readFromFile(f, &writeVersion, "writeVersion", (unsigned char) 1) ) {
		return false;
	}

	if ( ! readFromFile(f, &readVersion, "readVersion", (unsigned char) 1) ) {
		return false;
	}

	if ( ! readFromFile(f, &unusedSpaceAtEndOfPage, "unusedSpaceAtEndOfPage") ) {
		return false;
	}
	if ( verbose ) {
		cout << "unusedSpaceAtEndOfPage = " << (int) unusedSpaceAtEndOfPage << endl;
	}

	if ( ! readFromFile(f, &embeddedContentFractionMaxIndex, "embeddedContentFractionMaxIndex") ) {
		return false;
	}
	if ( verbose ) {
		cout << "embeddedContentFractionMaxIndex = " << (int) embeddedContentFractionMaxIndex << endl;
	}

	if ( ! readFromFile(f, &embeddedContentFractionMinOverflow, "embeddedContentFractionMinOverflow") ) {
		return false;
	}
	if ( verbose ) {
		cout << "embeddedContentFractionMinOverflow = " << (int) embeddedContentFractionMinOverflow << endl;
	}

	if ( ! readFromFile(f, &embeddedContentFractionMaxOverflow, "embeddedContentFractionMaxOverflow") ) {
		return false;
	}
	if ( verbose ) {
		cout << "embeddedContentFractionMaxOverflow = " << (int) embeddedContentFractionMaxOverflow << endl;
	}

	if ( ! readFromFile(f, &fileChangeCounter, "fileChangeCounter") ) {
		return false;
	}
	if ( verbose ) {
		cout << "fileChangeCounter = " << fileChangeCounter << endl;
	}
 
	if ( ! readFromFile(f, &freelistTrunkPageStart, "freelistTrunkPageStart") ) {
		return false;
	}
	if ( verbose ) {
		cout << "freelistTrunkPageStart = " << freelistTrunkPageStart << endl;
	}
 
	if ( ! readFromFile(f, &freePageCount, "freePageCount") ) {
		return false;
	}
	if ( verbose ) {
		cout << "freePageCount = " << freePageCount << endl;
	}

	if ( ! readFromFile(f, &schemaVersion, "schemaVersion") ) {
		return false;
	}
	if ( verbose ) {
		cout << "schemaVersion = " << schemaVersion << endl;
	}

	if ( ! readFromFile(f, &schemaLayerFileFormat, "schemaLayerFileFormat") ) {
		return false;
	}
	if ( verbose ) {
		cout << "schemaLayerFileFormat = " << schemaLayerFileFormat << endl;
	}

	return true;
}


