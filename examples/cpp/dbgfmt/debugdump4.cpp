
#include <memory>
#include <fstream>

#include "Buffer.h"
#include "DebugFormatter.h"
#include "TestEnv.h"

#include "Point.h"

/*
 * templates to decide whether to use a null formatter or EOL
 */
template<typename T, bool X=false>
struct NullOrEof
{
  typedef NullFormatter<T> type;
};

template<typename T>
struct NullOrEof<T, true>
{
  typedef EolFormatter<T> type;
};

/*
 * various formatter builder templates
 */

/*
 * generic builder
 */
template<typename T, bool X=false>
struct FormatBuilder00
{
  typedef T                                              value_type;
  typedef ItemFormatter<value_type>                      car_type;
  typedef typename NullOrEof<value_type, X>::type        cdr_type;
  typedef DebugFormatter<value_type, car_type, cdr_type> formatter_type;

  formatter_type build()
  {
    return formatter_type();
  }
};

/*
 * template to set up structure for formatting containers of objects
 */
template<typename T, bool X=false>
struct FormatBuilderC00
{
  typedef          T                                      value_type;
  typedef typename value_type::value_type                 item_value_type;
  typedef          ItemFormatter<item_value_type>         car_type;
  typedef typename NullOrEof<item_value_type, X>::type    cdr_type;
  typedef          ContainerFormatter2<value_type, car_type, cdr_type> 
                                                          formatter_type;

  formatter_type build()
  {
    return formatter_type();
  }
};

template<typename T, typename M1, bool X=false>
struct FormatBuilder01
{
  typedef          T                                      value_type;
  typedef          StructFormatter<value_type, M1>        car_type;
  typedef typename NullOrEof<value_type, X>::type         cdr_type;
  typedef          DebugFormatter<value_type, car_type, cdr_type> 
                                                          formatter_type;
  typedef M1 T::*                                         pm1_type;

  formatter_type build(pm1_type pm1)
  {
    car_type car(pm1);
    cdr_type cdr;
    return formatter_type(car, cdr);
  }
};

template<typename T, typename M1, typename M2, bool X=false>
struct FormatBuilder02
{
  typedef T                                               value_type;
  typedef StructFormatter<value_type, M1>                 car_type;
  typedef FormatBuilder01<T, M2, X>                       builder_type;
  typedef typename builder_type::formatter_type           cdr_type;
  typedef DebugFormatter<value_type, car_type, cdr_type>  formatter_type;
  typedef M1 T::*                                         pm1_type;
  typedef M2 T::*                                         pm2_type;

  formatter_type build(pm1_type pm1, pm2_type pm2)
  {
    car_type     car(pm1);
    builder_type builder;
    cdr_type     cdr = builder.build(pm2);
    return formatter_type(car, cdr);
  }
};

//
// unspecialized test, takes any data argument
//
template<typename T>
void test(char const * outfile, 
	  char const ** headers, 
	  T const & data)
{
  typedef          T                                  value_type;
  typedef          FormatBuilder00<value_type, true>  builder_type;
  typedef typename builder_type::formatter_type       formatter_type;
  typedef          TestEnv<formatter_type>            test_env_type;

  builder_type   builder;
  formatter_type formatter = builder.build();
  test_env_type  env(formatter, outfile, headers);
  
  env.execute(data);
}

//
// test specialized for a vector of any type
//
template<typename T>
void test(char const * outfile, 
	  char const ** headers, 
	  std::vector<T> const & data)
{
  typedef          std::vector<T>                     value_type;
  typedef          FormatBuilderC00<value_type, true> builder_type;
  typedef typename builder_type::formatter_type       formatter_type;
  typedef          TestEnv<formatter_type>            test_env_type;

  builder_type   builder;
  formatter_type formatter = builder.build();
  test_env_type  env(formatter, outfile, headers);
  
  env.execute(data);
}

//
// test specialized for a structure with one member variable reported
//
template<typename T, typename M1>
void test(char const * outfile, 
	  char const ** headers, 
	  T const & data,
	  M1 T::* pm1)
{
  typedef          T                                       value_type;
  typedef          M1                                      mem_1_type;
  typedef          FormatBuilder01<value_type, mem_1_type> builder_type;
  typedef typename builder_type::formatter_type            formatter_type;
  typedef          TestEnv<formatter_type>                 test_env_type;

  builder_type   builder;
  formatter_type formatter = builder.build(pm1);
  test_env_type  env(formatter, outfile, headers);
  
  env.execute(data);
}


//
// test specialized for a structure with two member variables reported
//
template<typename T, typename M1, typename M2>
void test(char const * outfile, 
	  char const ** headers, 
	  T const & data,
	  M1 T::* pm1,
	  M2 T::* pm2)
{
  typedef          T                                       value_type;
  typedef          M1                                      mem_1_type;
  typedef          M2                                      mem_2_type;
  typedef          FormatBuilder02<value_type, mem_1_type, mem_2_type, true> 
                                                           builder_type;
  typedef typename builder_type::formatter_type            formatter_type;
  typedef          TestEnv<formatter_type>                 test_env_type;

  builder_type   builder;
  formatter_type formatter = builder.build(pm1, pm2);
  test_env_type  env(formatter, outfile, headers);
  
  env.execute(data);
}

//
// test specialized for a structure with two member variables reported
//
template<typename T, typename U, typename M1, typename M2>
void test(char const * outfile, 
	  char const ** headers, 
	  T const & data,
	  M1 U::* pm1,
	  M2 U::* pm2)
{
  typedef          T                                       value_type;
  typedef          M1                                      mem_1_type;
  typedef          M2                                      mem_2_type;
  typedef          FormatBuilder02<value_type, mem_1_type, mem_2_type, true> 
                                                           builder_type;
  typedef typename builder_type::formatter_type            formatter_type;
  typedef          TestEnv<formatter_type>                 test_env_type;

  builder_type   builder;
  formatter_type formatter = builder.build(pm1, pm2);
  test_env_type  env(formatter, outfile, headers);
  
  env.execute(data);
}



//
// test specialized for a pair type object, such as the value_type of
// a map
// 
template<typename H, typename T>
void test(char const * outfile, 
	  char const ** headers, 
	  std::pair<H,T> const & data)
{
  typedef std::pair<H,T> value_type;
  test(outfile, headers, data, &value_type::first, &value_type::second);
}


//
// TEST FUNCTIONS
//


void test1()
{
  int v = 7;
  char const * h[] = { "single integer", 0 };
  char const * f = "dump3_1.txt";
  test(f, h, v);
}

void test2()
{
  double v = 4.565;
  char const * h[] = { "number", 0 };
  char const * f = "dump3_2.txt";
  test(f, h, v);
}

void test3()
{
  float v = 4.565;
  char const * h[] = { "number", 0 };
  char const * f = "dump3_3.txt";
  test(f, h, v);
}

void test4()
{
  std::string v = "Some very very long and boring text";
  char const * h[] = { "clue", 0 };
  char const * f = "dump3_4.txt";
  test(f, h, v);
}

void test5()
{
  typedef std::pair<int, std::string> test_type;
  auto v = test_type(3, "Some very very long and boring text");
  char const * h[] = { "index", "clue", 0 };
  char const * f = "dump3_5.txt";
  test(f, h, v);
}

void test6()
{
  typedef std::vector<int> test_type;
  test_type v;
  for ( test_type::value_type i = 1 ; i <= 1000 ; ++i ) {
    v.push_back(i);
  }
  char const * h[] = { "N", 0 };
  char const * f = "dump3_6.txt";
  test(f, h, v);
}

void test7()
{
#if 0
  typedef std::vector<Point> test_type;
  test_type v;
  for ( int i = 1 ; i <= 10 ; ++i ) {
    Point p;
    p.x = i/10.0;
    p.y = i/3.0;
    v.push_back(p);
  }
  char const * h[] = { "X", "Y", 0 };
  char const * f = "dump3_7.txt";
  test(f, h, v, &Point::x, &Point::y);
#endif
}

int main(int argc, char ** argv)
{
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();


  return 0;
}
