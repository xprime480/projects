#if ! defined(GENERATOR_H)
#define GENERATOR_H 1

struct GeneratorException {};

template<typename T>
struct Generator
{
  virtual ~Generator()
  {
  }

  virtual T operator()()
  {
    throw GeneratorException();
  }
};

#endif /* GENERATOR_H */
