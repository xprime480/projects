#if ! defined(TestEnv_h)
#define TestEnv_h 1

template <typename T>
class TestEnv
{
public:
  typedef T                                   formatter_type;
  typedef typename formatter_type::value_type value_type;

  TestEnv(formatter_type & _fmt,
	   char const * fname, 
	   char const ** headers)
    : fmt(_fmt)
    , of(fname)
    , buf(makeStreamBuffer(of))
  {
    init(headers);
  }

  void execute(value_type const & value)
  {
    fmt.format(*buf.get(), value);
  }

private:
  formatter_type      & fmt;
  std::ofstream         of;
  std::auto_ptr<Buffer> buf;

  void init(char const ** headers)
  {
    char hb[1024];
    hb[0] = '\0';
    fmt.makeHeader(hb, headers);
    buf->setHeader(hb);
  }

};

#endif
