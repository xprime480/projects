#include <set>

#include "TokenStream.h"

using namespace std;
using namespace Sloth;

namespace 
{
}

TokenStream::TokenStream()
  : LazySeq<Token>()
{
}

TokenStream::TokenStream(string const & input)
  : LazySeq<Token>()
  , rest(input)


TokenStream::~TokenStream()
{
}

TokenStream * TokenStream::tail()
{
  return new TokenStream(rest);
}

