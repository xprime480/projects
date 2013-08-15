
#include <set>
#include <map>
#include <iostream>
#include <numeric>

/**
 * [ sum ] [ length ] { { set 1 } { set 2 } ... }
 */
class SetOfSets
{
public:
  typedef std::set< int > atom_type;
  typedef std::set< atom_type > group_type;
  typedef std::map< int, group_type > len_type;
  typedef std::map< int, len_type > sum_type;
  typedef sum_type data_type;

  void build()
  {
    group_type working;
    working.insert( atom_type() );
    group_type::const_iterator iter;

    for ( int i = 1 ; i <= 9 ; ++i ) {
      group_type temp;

      for ( iter = working.begin() ; iter != working.end() ; ++iter ) {
	atom_type atom = *iter;
	temp.insert( atom );
	atom.insert( i );
	temp.insert( atom );
      }

      working = temp;
    }

    for ( iter = working.begin() ; iter != working.end() ; ++iter ) {
      add( *iter );
    }
    
  }

  template < typename T >
  void display( T & sink )
  {
    sum_type::const_iterator iter;

    for ( iter = data.begin() ; iter != data.end() ; iter++ ) {
      sink << "Sets totalling " << iter->first << std::endl;
      sink << "--------------------" << std::endl;
      display( sink, iter->second );
      sink << std::endl;
    }
  }

private:
  data_type data;

  void add( atom_type const & item )
  {
    int const len = item.size();

    if ( len <= 2 ) {
      return;
    }

    int const sum = std::accumulate( item.begin(), item.end(), 0 );

    data[ sum ][ len ].insert( item );
  }

  template < typename T > 
  void display( T & sink, len_type const & len ) 
  {
    len_type::const_iterator iter;
    for ( iter = len.begin() ; iter != len.end() ; ++iter ) {
      sink << "Length " << iter->first << ": ";
      display( sink, iter->second );
    }
  }

  template < typename T > 
  void display( T & sink, group_type const & group ) 
  {
    group_type::const_iterator iter;
    for ( iter = group.begin() ; iter != group.end() ; ++iter ) {
      display( sink, *iter );
      sink << " ";
    }
    sink << std::endl;
  }

  template < typename T > 
  void display( T & sink, atom_type const & atom ) 
  {
    atom_type::const_iterator iter;
    sink << "[ ";
    for  ( iter = atom.begin() ; iter != atom.end() ; ++iter ) {
      sink << *iter << " ";
    }
    sink << "]";
  }
};

void test() 
{
  SetOfSets  sets;
  sets.build();
  sets.display(std::cout);
}




int main( int argc, char ** argv ) 
{
  test();
  return 0;
}
