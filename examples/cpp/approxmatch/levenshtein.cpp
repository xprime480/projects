#include <algorithm>
#include <cstring>

#include "levenshtein.h"

using namespace std;

size_t levenshtein(char const * s, char const * t)
{
  unsigned char d[64][64];

  /**
   * The algorithm was copied from
   * http://en.wikipedia.org/wiki/Levenshtein_distance and modified.
   *
   */

  size_t m = strlen(s);
  size_t n = strlen(t);

  // Make sure m is less than n (less rows and more columns). This
  // will help improve locality.
  //
  if ( m > n ) {
    swap(m, n);
    swap(s, t);
  }

  // for all i and j, d[i,j] will hold the Levenshtein distance between
  // the first i characters of s and the first j characters of t;
  // note that d has (m+1)x(n+1) values

  for ( size_t i = 0 ; i <= m ; ++i )
    d[i][0] = i; // the distance of any first string to an empty second string
  for ( size_t j = 0 ; j <= n ; ++j )
    d[0][j] = j; // the distance of any second string to an empty first string

  // Handle rows first. This offers better locality and reduces page faults.
  // For i, instead of going from 1 to m, it goes from 0 to m - 1.
  // For j, instead of going from 1 to n, it goes from 0 to n - 1.
  for ( size_t i = 0 ; i < m ; ++i ) {
    for ( size_t j = 0 ; j < n ; ++j ) {
      if ( s[i] == t[j] ) {
        d[i + 1][j + 1] = d[i][j];              // no operation required
      }
      else {
        d[i + 1][j + 1] = min(d[i    ][j + 1],  // a deletion
		                  min(d[i + 1][j    ],  // an insertion
			                  d[i    ][j    ]   // a substitution
			                 )) + 1;
      }
    }
  }

  return d[m][n];
}
