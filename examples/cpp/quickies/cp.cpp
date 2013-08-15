
#include <memory>
#include <iostream>

struct P;
typedef std::shared_ptr< P > PP;

struct P
{
  ~P() 
  {
    std::cout << "die P\n";
  }

  PP other;
};


int main( int, char ** )
{
  PP pp1( new P );
  PP pp2( new P );

  // circular references confound smart pointer
  pp1->other = pp2;
  pp2->other = pp1;
}
