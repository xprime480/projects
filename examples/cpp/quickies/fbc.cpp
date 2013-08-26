
#include <iostream>
#include <map>
#include <string>

class CLReader
{
public:

  class Handler
  {
  public:
    virtual bool process(char const * key, char const * value) = 0;
  };

  CLReader(int _argc, char ** _argv, Handler & _default)
   : defaultHandler(_default)
   , argc(_argc)
   , argv(_argv) 
  {
  }

  void registerHandler(char const * key, Handler & handler)
  {
    std::string k(key);
    if ( handlers.find(k) != handlers.end() ) {
      handlers.erase(k);
    }
    handlers.insert(HandlerMap::value_type(k, handler));
  }

  bool process() const
  {
    for ( int idx = 1 ; idx < argc ; ++idx ) {
      std::string k(argv[idx]);
      HandlerMap::const_iterator iter = handlers.find(k);
      bool more = false;
      if ( iter == handlers.end() ) {
	more = defaultHandler.process(argv[idx], 0);
      }
      else {
	more = iter->second.process(argv[idx], (char const *) 0);
      }

      if ( !more ) {
	return false;
      }
    }

    return true;
  }

private:
  typedef std::map<std::string, Handler &> HandlerMap;

  HandlerMap handlers;
  Handler & defaultHandler;

  int argc;
  char ** argv;
};

class AHandler : public CLReader::Handler
{
public:
  virtual bool process(char const * key, char const * value)
  {
    std::cout << "Got option a" << std::endl;
    return true;
  }
};

class AHandlerAlt : public CLReader::Handler
{
public:
  virtual bool process(char const * key, char const * value)
  {
    std::cout << "Got option a [alt handler]" << std::endl;
    return true;
  }
};

class DefaultHandler : public CLReader::Handler
{
public:
  virtual bool process(char const * key, char const * value)
  {
    std::cout << "Using default handler for option " << key << std::endl;
    return false;
  }
};

int main(int argc, char ** argv)
{
  DefaultHandler defaultHandler;
  CLReader clr(argc, argv, defaultHandler);
  AHandler aHandler;
  AHandlerAlt aHandlerAlt;
  clr.registerHandler("a", aHandler);
  clr.registerHandler("a", aHandlerAlt);
  clr.process();
  return 0;
}
