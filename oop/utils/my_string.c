#include "my_string.h"
#include <stddef.h>   //for NULL

unsigned int my_strlen(const char *x)
{
  char *count = (char*)x;
  while(*count++);
  return (unsigned int)(count - x - 1);
}

void my_strcpy(char *d, const char *s)
{
  char *source = (char*)s;
  while(*source)
    *d++ = *source++;
  *d = 0;
}

void my_strncpy(char *d, const char *s, unsigned int n)
{
  char *source = (char*)s;
  unsigned int i = 0;

  while((*source) && (i < n))
  {
    i++;
    *d++ = *source++;
  }
  *d = 0;
}

void my_strcat(char *d, const char *s)
{
  char *source = (char*)s;
  while(*d)
    d++;

  while(*source)
    *d++ = *source++;

  *d = 0;
}

int my_strcmp(const char *s1, const char *s2)
{
  char *ss1 = (char*)s1;
  char *ss2 = (char*)s2;
  while((*ss1 == *ss2) && (*ss1) && (*ss2))
  {
    ss1++;
    ss2++;
  }

  if(*ss1 == *ss2)
    return 0;
  else
  if(*ss1 < *ss2)
    return -1;
  else
    return 1;
}

void my_inttostr(char *d, const int x)
{
  int temp = x;
  int i = 0;

  if(x == 0)
  {
    *d++ = '0';
    *d = 0;
    return;
  }

  while(temp)
  {
    temp /= 10;
    i++;
  }

  temp = x;
  if(temp < 0)
  {
    *d++ = '-';
    temp = -x;
  }
  *(d + i) = 0;
  
  while(temp)
  {
    *(d + i - 1) = (temp % 10) + '0';
    temp /= 10;
    i--;
  }
}

char* my_strstr(const char *needle, const char *haystack)
{
  //naive implementation
  char *h = (char*)haystack, *n;
  while(*h)
  {
    n = (char*)needle;
    while(*h && (*h != *n))
      h++;

    if(!*h)
      return NULL;

    while(*h && (*n == *h))
    {
      h++;
      n++;
      if(!*n)
      {
        return (h - my_strlen(needle));
      }
    }
  }

  return NULL;
}

int my_strpos(const char *needle, const char *haystack)
{
  char *s = my_strstr(needle, haystack);
  if(s)
    return (int)(s - haystack);
  else
    return -1;
}
