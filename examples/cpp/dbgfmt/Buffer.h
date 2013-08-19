#if ! defined(Buffer_h)
#define Buffer_h 1

#include <cstring>
#include <cstdlib>
#include <stack>
#include <iostream>

static size_t const BUFMAX = 1024;

class Buffer
{
public:


  Buffer()
    : hdr(strdup("<uninitialized>"))
    , pos(0)
    , line(0)
  {
    buf[0] = 0;
  }

  virtual ~Buffer() 
  {
    free(const_cast<char *>(hdr));
  }

  void setHeader(char const * h)
  {
    hdr = strndup(h, 1024);
  }

  size_t append(char const * data)
  {
    size_t limit = BUFMAX - pos - 1;
    if ( limit <= 0 || limit > BUFMAX ) {
      return 0;
    }
    strncpy(buf + pos, data, limit);
    size_t newpos = strlen(buf);
    size_t rv = newpos - pos;
    pos = newpos;
    return rv;
  }

  void writeData()
  {
    if ( (line % 60) == 0 ) {
      write("\n\n");
      write(hdr);
    }
    write(buf);
    ++line;
  }

  void pushState()
  {
    states.push(pos);
  }

  void popState()
  {
    pos = states.top();
    states.pop();
    buf[pos] = '\0';
  }

protected:
  virtual void write(char const * data) = 0;

private:

  std::stack<size_t> states;
  char const *       hdr;
  size_t             pos;
  char               buf[BUFMAX];
  size_t             line;
};

template<typename T> 
class StreamBuffer : public Buffer
{
public:
  StreamBuffer(T & _os)
    : os(_os)
  {
  }

protected:
  virtual void write(char const * data)
  {
    os << data << std::endl;
  }

private:
  T & os;
};

template<typename OS>
Buffer * makeStreamBuffer(OS & os)
{
  return new StreamBuffer<OS>(os);
}

#endif
