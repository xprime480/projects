#if ! defined(Generator_h)
#define Generator_h 1

class Generator
{
public:
  virtual ~Generator()
  {
  }

  virtual int gen() = 0;
};

#endif // not defined Generator_h
