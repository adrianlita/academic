#include "aString.h"
#include "../utils/utils.h"
#include "../utils/my_string.h"
using namespace std;

void aString::set(const char *x)
{
  if(x)
  {
    s = new char[my_strlen(x) + 1];
    check_if_allocated_correctly(s);
    my_strcpy(s, x);
  }
}

aString::aString()
{
  s = NULL;
}

aString::aString(const int& rhs)
{
  s = NULL;

  char number[22];  //maximum number of digits for int64, including - and \0
  my_inttostr(number, rhs);
  set(number);
}

aString::aString(const char *rhs)
{
  s = NULL;
  set(rhs);
}

aString::aString(const aString& rhs)
{
  s = NULL;
  set(rhs.s);
}

aString::~aString()
{
  if(s)
    delete[] s;
}

unsigned int aString::Length() const
{
  return my_strlen(s);
}

bool aString::isEmpty() const
{
  return (s == NULL);
}

aString& aString::operator=(const int& rhs)
{
  if(s)
    delete[] s;

  s = NULL;

  char number[22];  //maximum number of digits for int64, including - and \0
  my_inttostr(number, rhs);
  set(number);

  return *this;
}

aString& aString::operator=(const char *rhs)
{
  if(this->s != rhs)  //normally shouldn't be checked, but think of this scenario: aString a; a = (char*)a;
  {
    if(s)
      delete[] s;
    
    s = NULL;
    set(rhs);
  }
  return *this;
}

aString& aString::operator=(const aString& rhs)
{
  if(this != &rhs)
  {
    if(s)
      delete[] s;
    
    s = NULL;
    set(rhs.s);
  }
  return *this;
}


char& aString::operator[](const unsigned int i)
{
  if(!s)
    throw "string is null";
  if(i >= Length())
    throw "index out of bounds";
  return s[i];
}

char& aString::operator[](const int i)
{
  if(i < 0)
    throw "index out of bounds";
  return operator[]((const unsigned int)i);
}

aString::operator const char*()
{
  return (const char*)s;
}

aString::operator char*()
{
  return s;
}


aString aString::operator+(const aString& rhs)
{
  aString result;
  unsigned int l = 0;
  if(s)
    l += my_strlen(s);
  if(rhs.s)
    l += my_strlen(rhs.s);
  if(l)
  {
    result.s = new char[l + 1];
    check_if_allocated_correctly(result.s);
    my_strcpy(result.s, "");  //same as result.s[0] = 0;
    if(s)
      my_strcat(result.s, s);
    if(rhs.s)
      my_strcat(result.s, rhs.s);
  }
  return result;
}

aString aString::operator+(const char rhs)
{
  aString result;
  unsigned int l = 1; //rhs is always 1
  if(s)
    l += my_strlen(s);
  
  result.s = new char[l + 1];
  check_if_allocated_correctly(result.s);
  my_strcpy(result.s, "");  //same as result.s[0] = 0;
  if(s)
    my_strcat(result.s, s);
  
  result.s[l - 1] = rhs;
  result.s[l] = 0;  //null termination
  
  return result;
}

aString aString::operator+(const char* rhs)
{
  aString result;
  unsigned int l = 0;
  if(s)
    l += my_strlen(s);
  if(rhs)
    l += my_strlen(rhs);
  if(l)
  {
    result.s = new char[l + 1];
    check_if_allocated_correctly(result.s);
    my_strcpy(result.s, "");  //same as result.s[0] = 0;
    if(s)
      my_strcat(result.s, s);
    if(rhs)
      my_strcat(result.s, rhs);
  }
  return result;
}

aString operator+(const char lhs, const aString& rhs)
{
  aString result;
  unsigned int l = 1; //lhs is always 1
  if(rhs.s)
    l += my_strlen(rhs.s);
  
  result.s = new char[l + 1];
  check_if_allocated_correctly(result.s);
  
  result.s[0] = lhs;
  result.s[1] = 0;  //null termination
  if(rhs.s)
    my_strcat(result.s, rhs.s);
  
  return result;
}

aString operator+(const char* lhs, const aString& rhs)
{
  aString result;
  unsigned int l = 0;
  if(lhs)
    l += my_strlen(lhs);
  if(rhs.s)
    l += my_strlen(rhs.s);
  if(l)
  {
    result.s = new char[l + 1];
    check_if_allocated_correctly(result.s);
    my_strcpy(result.s, "");  //same as result.s[0] = 0;
    if(lhs)
      my_strcat(result.s, lhs);
    if(rhs.s)
      my_strcat(result.s, rhs.s);
  }
  return result;
}

aString& aString::operator+=(const aString& rhs)
{
  unsigned int l = 0;
  if(rhs.s)
    l += my_strlen(rhs.s);

  if(l)
  {
    if(s)
      l += my_strlen(s);

    char *new_s = new char[l + 1];
    check_if_allocated_correctly(new_s);
    my_strcpy(new_s, "");
    if(s)
      my_strcat(new_s, s);
    if(rhs.s)
      my_strcat(new_s, rhs.s);

    if(s)
      delete[] s;

    s = new_s;
  }

  return *this;  
}

aString& aString::operator+=(const char rhs)
{
  unsigned int l = 1;
  
  if(s)
    l += my_strlen(s);

  char *new_s = new char[l + 1];
  check_if_allocated_correctly(new_s);
  my_strcpy(new_s, "");
  if(s)
    my_strcat(new_s, s);

  new_s[l - 1] = rhs;
  new_s[l] = 0;
  
  if(s)
    delete[] s;

  s = new_s;

  return *this;  
}

aString& aString::operator+=(const char* rhs)
{
  unsigned int l = 0;
  if(rhs)
    l += my_strlen(rhs);

  if(l)
  {
    if(s)
      l += my_strlen(s);

    char *new_s = new char[l + 1];
    check_if_allocated_correctly(new_s);
    my_strcpy(new_s, "");
    if(s)
      my_strcat(new_s, s);
    if(rhs)
      my_strcat(new_s, rhs);

    if(s)
      delete[] s;

    s = new_s;
  }

  return *this;  
}

bool aString::operator==(const char *rhs) const
{
  if(s == NULL)
  {
    if(rhs == NULL)
      return true;
    else
      return false;
  }
  else
  {
    if(rhs == NULL)
      return false;
    else
      return (my_strcmp(s, rhs) == 0);
  }
}

bool aString::operator>(const char *rhs) const
{
  if(s == NULL)
  {
    return false;
  }
  else
  {
    if(rhs == NULL)
      return true;
    else
      return (my_strcmp(s, rhs) > 0);
  }
}

bool aString::operator!=(const char *rhs) const
{
  return !operator==(rhs);
}

bool aString::operator>=(const char *rhs) const
{
  return !operator<(rhs);
}

bool aString::operator<(const aString& rhs) const
{
  return operator<(rhs.s);
}

bool aString::operator<=(const char *rhs) const
{
  return !operator>(rhs);
}

bool aString::operator<(const char *rhs) const
{
  if(rhs == NULL)
  {
    return false;
  }
  else
  {
    if(s == NULL)
      return true;
    else
      return (my_strcmp(s, rhs) < 0);
  }
}

bool aString::operator==(const aString& rhs) const
{
  return operator==(rhs.s);
}

bool aString::operator!=(const aString& rhs) const
{
  return !operator==(rhs.s);
}

bool aString::operator>(const aString& rhs) const
{
  return operator>(rhs.s);
}

bool aString::operator>=(const aString& rhs) const
{
  return !operator<(rhs.s);
}

bool aString::operator<=(const aString& rhs) const
{
  return !operator>(rhs.s);
}

bool operator==(const char *lhs, const aString& rhs)
{
  return (rhs == lhs);
}

bool operator!=(const char *lhs, const aString& rhs)
{
  return (rhs != lhs);
}

bool operator>(const char *lhs, const aString& rhs)
{
  return !(rhs <= lhs);
}

bool operator>=(const char *lhs, const aString& rhs)
{
  return !(rhs < lhs);
}

bool operator<(const char *lhs, const aString& rhs)
{
  return !(rhs >= lhs);
}

bool operator<=(const char *lhs, const aString& rhs)
{
  return !(rhs > lhs);
}

ostream& operator<<(ostream& out, const aString& rhs)
{
  if(rhs.s)
    out << rhs.s;

  return out;
}
