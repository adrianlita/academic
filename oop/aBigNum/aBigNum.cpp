#include "aBigNum.h"
#include <cstring>
#include "../utils/utils.h"
using namespace std;


aBigNum::aBigNum()
{
  negative = false;
  l = 1;
  decimals = new char[l];
  check_if_allocated_correctly(decimals);
  decimals[0] = 0;
}

aBigNum::aBigNum(const int nr)
{
  char s[22];
  int n = nr;

  if(n < 0)
  {
    negative = true;
    n = -n;
  }
  else
    negative = false;

  if(nr != 0)
  {
    l = 0;
    while(n)
    {
      s[l] = n % 10;
      l++;
      n /= 10;
    }
  }
  else
  {
    l = 1;
    s[0] = 0;
  }

  decimals = new char[l];
  check_if_allocated_correctly(decimals);
  for(unsigned int i = 0; i < l; i++)
    decimals[i] = s[i];
}

aBigNum::aBigNum(const char *nr)
{
  negative = false;

  if(nr)
  {
    char *n = (char*)nr;
    unsigned int len = strlen(n);
    if(*n == '-')
    {
      n++;
      len--;
      negative = true;
    }
    
    //remove leading 0s
    while(*n == '0')
    {
      n++;
      len--;
    }

    l = len;
    decimals = new char[l];
    check_if_allocated_correctly(decimals);

    while(len)
    {
      len--;
      decimals[len] = *n - '0';
      n++;
    }
  }
  else
  {
    l = 1;
    decimals = new char[l];
    check_if_allocated_correctly(decimals);
    decimals[0] = 0;
  }
}

aBigNum::aBigNum(const aBigNum& rhs)
{
  if(rhs.l)
  {
    negative = rhs.negative;
    l = rhs.l;
    decimals = new char[l];
    check_if_allocated_correctly(decimals);
    for(unsigned int i = 0; i < l; i++)
      decimals[i] = rhs.decimals[i];
  }
  else
  {
    negative = false;
    l = 1;
    decimals = new char[l];
    check_if_allocated_correctly(decimals);
    decimals[0] = 0;
  }
}

aBigNum::~aBigNum()
{
  if(decimals)
    delete[] decimals;
}

unsigned int aBigNum::Length() const
{
  return l;
}

aBigNum& aBigNum::operator=(const int nr)
{
  if(decimals)
    delete[] decimals;

  char s[22];
  int n = nr;

  if(n < 0)
  {
    negative = true;
    n = -n;
  }
  else
    negative = false;

  if(nr != 0)
  {
    l = 0;
    while(n)
    {
      s[l] = n % 10;
      l++;
      n /= 10;
    }
  }
  else
  {
    l = 1;
    s[0] = 0;
  }

  decimals = new char[l];
  check_if_allocated_correctly(decimals);
  for(unsigned int i = 0; i < l; i++)
    decimals[i] = s[i];

  return *this;
}

aBigNum& aBigNum::operator=(const char* nr)
{
  if(decimals)
    delete[] decimals;
  
  negative = false;
  
  if(nr)
  {
    char *n = (char*)nr;
    unsigned int len = strlen(n);
    if(*n == '-')
    {
      n++;
      len--;
      negative = true;
    }
    
    //remove leading 0s
    while(*n == '0')
    {
      n++;
      len--;
    }

    l = len;
    decimals = new char[l];
    check_if_allocated_correctly(decimals);

    while(len)
    {
      len--;
      decimals[len] = *n - '0';
      n++;
    }
  }
  else
  {
    l = 1;
    decimals = new char[l];
    check_if_allocated_correctly(decimals);
    decimals[0] = 0;
  }

  return *this;
}

aBigNum& aBigNum::operator=(const aBigNum& rhs)
{
  if(this != &rhs)
  {
    if(decimals)
      delete[] decimals;

    if(rhs.l)
    {
      negative = rhs.negative;
      l = rhs.l;
      decimals = new char[l];
      check_if_allocated_correctly(decimals);
      for(unsigned int i = 0; i < l; i++)
        decimals[i] = rhs.decimals[i];
    }
    else
    {
      negative = false;
      l = 1;
      decimals = new char[l];
      check_if_allocated_correctly(decimals);
      decimals[0] = 0;
    }
  }
  return *this;
}

aBigNum aBigNum::add(const aBigNum& lhs, const aBigNum& rhs)
{
  aBigNum result;
  result.l = 0;
  delete[] result.decimals;

  //estimate new l
  if(lhs.l > rhs.l)
    result.l = lhs.l + 1;
  else
    result.l = rhs.l + 1;
  
  result.decimals = new char[result.l];
  check_if_allocated_correctly(result.decimals);
  for(unsigned int i = 0; i < result.l; i++)
    result.decimals[i] = 0;

  for(unsigned int i = 0; i < result.l - 1; i++)
  {
    char t1 = 0;
    char t2 = 0;
    if(i < lhs.l)
      t1 = lhs.decimals[i];
    if(i < rhs.l)
      t2 = rhs.decimals[i];

    result.decimals[i] = result.decimals[i] + t1 + t2;
    if(result.decimals[i] > 9)
    {
      result.decimals[i] %= 10;
      result.decimals[i + 1]++;
    }
  }

  if(result.decimals[result.l - 1] == 0)
  {
    result.l--;
    char *r = new char[result.l];
    check_if_allocated_correctly(r);
    for(unsigned i = 0; i < result.l; i++)
      r[i] = result.decimals[i];
    delete[] result.decimals;
    result.decimals = r;
  }

  return result;
}

aBigNum aBigNum::substract(const aBigNum& lhs, const aBigNum& rhs)
{
  aBigNum result;
  bool neg;
  result.l = 0;
  delete[] result.decimals;

  neg = false;
  aBigNum *lterm = (aBigNum*)&lhs;
  aBigNum *rterm = (aBigNum*)&rhs;
  //have the left term the biggest
  bool lneg = lhs.negative;
  bool rneg = rhs.negative;
  lterm->negative = false;
  rterm->negative = false;
  if(lhs < rhs)
  {
    neg = true;
    lterm = (aBigNum*)&rhs;
    rterm = (aBigNum*)&lhs; 
  }
  lterm->negative = lneg;
  rterm->negative = rneg;

  //estimate new l
  if(lterm->l > rterm->l)
    result.l = lterm->l + 1;
  else
    result.l = rterm->l + 1;
  
  result.decimals = new char[result.l];
  check_if_allocated_correctly(result.decimals);
  for(unsigned int i = 0; i < result.l; i++)
    result.decimals[i] = 0;

  for(unsigned int i = 0; i < result.l; i++)
  {
    char t1 = 0;
    char t2 = 0;
    if(i < lterm->l)
      t1 = lterm->decimals[i];
    if(i < rterm->l)
      t2 = rterm->decimals[i];

    result.decimals[i] = result.decimals[i] + t1 - t2;
    if(result.decimals[i] < 0)
    {
      result.decimals[i] += 10;
      result.decimals[i + 1]--;
    }
  }

  while((result.l - 1) && (result.decimals[result.l - 1] == 0))
    result.l--;

  if(result.decimals[result.l - 1] < 0)
  {
    result.decimals[result.l - 1] = -result.decimals[result.l - 1];
    result.negative = true;
  }

  if(neg)
    result.negative = !result.negative;


  char *r = new char[result.l];
  check_if_allocated_correctly(r);
  for(unsigned int i = 0; i < result.l; i++)
    r[i] = result.decimals[i];
  delete[] result.decimals;
  result.decimals = r;

  return result;
}

aBigNum aBigNum::multiply(const char figure, const unsigned int power)
{
  aBigNum result;
  if(figure)
  {
    result.l = 0;
    delete[] result.decimals;
    result.l = l + power + 1;
    result.decimals = new char[result.l];
    check_if_allocated_correctly(result.decimals);
    for(unsigned int i = 0; i < result.l; i++)
      result.decimals[i] = 0;

    for(unsigned int i = power; i < result.l - 1; i++)
    {
      result.decimals[i] = result.decimals[i] + decimals[i - power] * figure;

      if(result.decimals[i] > 9)
      {
        result.decimals[i + 1] += result.decimals[i] / 10;
        result.decimals[i] %= 10;
      }
    }

    if(result.decimals[result.l - 1] == 0)
    {
      result.l--;
      char *r = new char[result.l];
      for(unsigned int i = 0; i < result.l; i++)
        r[i] = result.decimals[i];
      delete[] result.decimals;
      result.decimals = r;
    }
  }
  return result;
}

aBigNum aBigNum::operator+(const aBigNum& rhs)
{
  aBigNum result;

  if(negative == false)
  {
    if(rhs.negative == false)
      result = add(*this, rhs);
    else
      result = substract(*this, rhs);
  }
  else
  {
    if(rhs.negative == false)
      result = substract(rhs, *this);
    else
    {
      result = add(*this, rhs);
      result.negative = !result.negative;
    }
  }

  return result;
}

aBigNum aBigNum::operator+(const int rhs)
{
  return operator+(aBigNum(rhs));
}

aBigNum aBigNum::operator-(const aBigNum& rhs)
{
  aBigNum result;

  if(negative == false)
  {
    if(rhs.negative == false)
      result = substract(*this, rhs);
    else
      result = add(*this, rhs);
  }
  else
  {
    if(rhs.negative == false)
    {
      result = add(*this, rhs);
      result.negative = !result.negative;
    }
    else
      result = substract(rhs, *this);
      
  }

  return result;
}
aBigNum aBigNum::operator-(const int rhs)
{
  return operator-(aBigNum(rhs));
}

aBigNum aBigNum::operator*(const aBigNum& rhs)
{
  aBigNum result;

  for(unsigned int i = 0; i < rhs.l; i++)
  {
    result = result + multiply(rhs.decimals[i], i);
  }

  if(negative != rhs.negative)
    result.negative = true;

  return result;
}

aBigNum aBigNum::operator*(const int rhs)
{
  return operator*(aBigNum(rhs));
}

aBigNum aBigNum::operator/(const aBigNum& rhs)
{
  aBigNum result;
  
  return result;
}

aBigNum aBigNum::operator/(const int rhs)
{
  aBigNum result;
  
  return result;
}

aBigNum aBigNum::operator%(const aBigNum& rhs)
{
  aBigNum result;
  
  return result;
}

aBigNum aBigNum::operator%(const int rhs)
{
  aBigNum result;
  
  return result;
}

void aBigNum::add1()
{
  decimals[0]++;
  if(l > 1)
  {
    for(unsigned int i = 0; i < l - 1; i++)
    {
      if(decimals[i] > 9)
      {
        decimals[i] %= 10;
        decimals[i + 1]++;
      }
      else
        break;
    }
  }

  if(decimals[l - 1] > 9)
  {
    char *r = new char[l + 1];
    check_if_allocated_correctly(r);
    for(int i = 0; i < l; i++)
      r[i] = decimals[i];

    r[l - 1] %= 10;
    r[l] = 1;
    delete[] decimals;
    decimals = r;
    l++;
  }
}

void aBigNum::substract1()
{
  decimals[0]--;
  if(l > 1)
  {
    for(unsigned int i = 0; i < l; i++)
    {
      if(decimals[i] < 0)
      {
        decimals[i] += 10;
        decimals[i + 1]--;
      }
      else
        break;
    }
  }

  while((l > 1) && (decimals[l - 1] == 0))
    l--;

  char *r = new char[l];
  check_if_allocated_correctly(r);
  for(unsigned int i = 0; i < l; i++)
    r[i] = decimals[i];
  delete[] decimals;
  decimals = r;
}

aBigNum& aBigNum::operator++()
{
  if(negative && (l == 1))
    if(decimals[0] == 1)
    {
      decimals[0]--;
      negative = false;
      return *this;
    }

  if(!negative)
    add1();
  else
    substract1();
  
  return *this;
}

aBigNum aBigNum::operator++(int)
{
  aBigNum result = *this;
  ++*this;
  return result;
}

aBigNum& aBigNum::operator--()
{
  if(l == 1)
    if(decimals[0] == 0)
    {
      decimals[0]++;
      negative = true;
      return *this;
    }

  if(!negative)
    substract1();
  else
    add1();
  return *this;
}

aBigNum aBigNum::operator--(int)
{
  aBigNum result = *this;
  ++*this;
  return result;
}


aBigNum aBigNum::operator-()
{
  aBigNum result = *this;
  result.negative = !result.negative;
  return result;
}

bool aBigNum::operator==(const aBigNum& rhs) const
{
  if(l != rhs.l)
    return false;

  if(negative != rhs.negative)
    return false;

  for(unsigned int i = 0; i < l; i++)
    if(decimals[i] != rhs.decimals[i])
      return false;

  return true;
}

bool aBigNum::operator!=(const aBigNum& rhs) const
{
  return !(*this == rhs);
}

bool aBigNum::operator>(const aBigNum& rhs) const
{
  if(negative && !rhs.negative)
    return false;

  if(!negative && rhs.negative)
    return true;
  
  if(!negative)
  {
    if(l < rhs.l)
      return false;

    unsigned int i = l;
    while(i)
    {
      --i;
      if(decimals[i] != rhs.decimals[i])
        break;
    }
    if(decimals[i] <= rhs.decimals[i])
      return false;
  }
  else
  {
    if(l > rhs.l)
      return false;

    unsigned int i = l;
    while(i)
    {
      --i;
      if(decimals[i] != rhs.decimals[i])
        break;
    }
    if(decimals[i] >= rhs.decimals[i])
      return false;
  }

  return true;
}

bool aBigNum::operator>=(const aBigNum& rhs) const
{
  return !(*this < rhs);
}

bool aBigNum::operator<(const aBigNum& rhs) const
{
  return (rhs > *this);
}

bool aBigNum::operator<=(const aBigNum& rhs) const
{
  return !(*this > rhs);
}

std::ostream& operator<<(std::ostream &out, const aBigNum& rhs)
{
  if(rhs.l)
  {
    if(rhs.negative)
      out << '-';

    unsigned int i = rhs.l;
    while(i)
    {
      i--;
      out << (int)rhs.decimals[i];
    }
  }
  return out;
}
