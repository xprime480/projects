#if ! defined(CSVREADER_H)
#define CSVREADER_H 1

class CsvReader
{
public:
  CsvReader(bool hasHeader=true, char quote='"', char sep=',', bool ignoreSpace=true);
  virtual ~CsvReader();

  size_t read();

private:
  bool hasHeader;
  char quote;
  char sep;
  bool ignoreSpace;
};

#endif
