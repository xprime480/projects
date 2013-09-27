#if ! defined(SqliteDbHeader_H)
#define SqliteDbHeader_H 1

#include <cstdio>

class SqliteDbHeader {
public:
	bool read(FILE * f, bool verbose = false);
	
protected:
private:
	static int const MagicSize = 16;

	char magic[MagicSize];
	unsigned short pageSize;
	unsigned char  writeVersion;
	unsigned char  readVersion;
	unsigned char  unusedSpaceAtEndOfPage;
	unsigned char  embeddedContentFractionMaxIndex;
	unsigned char  embeddedContentFractionMinOverflow;
	unsigned char  embeddedContentFractionMaxOverflow;
	unsigned long  fileChangeCounter;
	unsigned long  freelistTrunkPageStart;
	unsigned long  freePageCount;
	unsigned long  schemaVersion;
	unsigned long  schemaLayerFileFormat;
};


#endif
