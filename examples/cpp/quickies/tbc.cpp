
#include <iostream>

class Tail
{
public : 
  Tail( int _argc, char ** _argv ) 
    : argc(_argc)
    , argv(_argv)
  {
  }

protected :
  int argc;
  char ** argv;
};

template< typename T = Tail >
class A : public T
{
public:
  A( int _argc, char ** _argv ) 
    : T(_argc, _argv)
    , status( false )
  {
  }

  void a() 
  {
    std::cout << "a\n";
    status = true;
  }

  bool huh() const 
  {
    return status;
  }

private : 
  bool status;
};

template< typename T = Tail >
class B : public T
{
public:
  B( int _argc, char ** _argv ) 
    : T(_argc, _argv)
    , status( false )
  {
  }

  void b() 
  {
    std::cout << "b\n";
    status = true;
  }

  bool huh() const 
  {
    return status;
  }

private : 
  bool status;
};

template< typename T = Tail >
class C : public T
{
public:
  C( int _argc, char ** _argv ) 
    : T(_argc, _argv)
    , status( false )
  {
  }

  void c() 
  {
    std::cout << "c\n";
    status = true;
  }

  bool huh() const 
  {
    return status;
  }

private : 
  bool status;
};

template< typename T, typename U >
void report(U const & obj) 
{
    T const & o = dynamic_cast<T const &>(obj);
    std::cout << o.huh() << std::endl;
}


int main( int argc, char ** argv ) 
{
  typedef A< >    T1;
  typedef B< T1 > T2;
  typedef C< T2 > T3;

  T3 obj(argc, argv);

  obj.b();
  obj.a();

  report<T1>(obj);
  report<T2>(obj);
  report<T3>(obj);
  return 0;
}

