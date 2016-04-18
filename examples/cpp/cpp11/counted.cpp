
#include <iostream>

#include "counted.h"

using std::cout;
using std::endl;

Counted::Counted()
  : serial_number(++counter)
{
  cout << "creating instance #" << serial_number << endl;
}

Counted::~Counted()
{
  cout << "deleting instance #" << serial_number << endl;
}

int Counted::counter(0);

