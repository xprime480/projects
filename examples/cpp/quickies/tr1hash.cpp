
//#include <hashtable>
#include <unordered_map>
#include <unordered_set>

#include <string>
#include <iostream>

void test1()
{
  typedef std::unordered_map< std::string, int > DictType;
  typedef DictType::const_iterator                    DI;

  DictType units;

  units.insert( std::make_pair( "dozen", 12 ) );
  units.insert( std::make_pair( "bakersdozen", 13 ) );
  units.insert( std::make_pair( "gross", 144 ) );
  units.insert( std::make_pair( "case", 24 ) );

  DI end = units.end();
  for ( DI pos = units.begin() ; pos != end ; ++pos ) {
    std::cout << pos->first << " " << pos->second << "\n";
  }

  std::cout << units[ "dozen" ] << "\n";
  std::cout << units[ "case" ] << "\n";
}

struct HK
{
  char sk1;
  int  sk2;
};

namespace std {

  template<>
  struct hash< HK >
  {
    std::size_t
    operator()( HK const & hk ) const
    {
      std::size_t result = 0;
      static size_t const shift = (sizeof ( std::size_t ) - 1) * 8;

      result =   static_cast< std::size_t >( hk.sk2 );
      result +=  static_cast< std::size_t >( hk.sk1 ) << shift;

      return result;
    }
  };

}

bool operator==( HK const & hk1, HK const & hk2 )
{
  return hk1.sk1 == hk2.sk1 && hk1.sk2 == hk2.sk2;
}


void test2()
{
  typedef std::unordered_set< HK >  DictType;
  typedef DictType::const_iterator       DI;

  DictType dict;

  HK hk;

  for ( int i = 0 ; i < 26 * 100 ; ++ i ) {
    hk.sk1 = 'a' + i % 26;
    hk.sk2 = i;
    dict.insert( hk );
  }
    
  DI end = dict.end();
  for ( DI pos = dict.begin() ; pos != end ; ++pos ) {
    std::cout << pos->sk1 << "\n";
  }
}



int main( int, char ** )
{
  test1();
  test2();

  return 0;
}
