
#include <cstring>
#include <cstdlib>

#include "strdup.h"

using namespace std;

char * strdup(char const * s) 
{
  if ( ! s ) {
    return 0;
  }

  size_t len = strlen(s);
  char * news = (char *) malloc(1 + len);
  strcpy(news, s);

  return news;
}


char * strndup(char const * s, size_t max) 
{
  if ( ! s ) {
    return 0;
  }

  size_t len = strlen(s);
  if ( len >= max ) {
    len = max - 1;
  }

  char * news = (char *) malloc(1 + len);
  strncpy(news, s, len);
  news[len] = '\0';

  return news;
}

