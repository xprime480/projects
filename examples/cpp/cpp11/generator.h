

struct GeneratorException {};

template<typename T>
struct Generator
{
  virtual ~Generator()
  {
  }

  T operator()()
  {
    throw GeneratorException();
  }
};
