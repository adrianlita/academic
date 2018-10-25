#include "anotherVector.h"
using namespace std;

anotherVector::anotherVector()
{
  c = 0;
  v = NULL;
}

anotherVector::anotherVector(const unsigned int size)
{
  c = 0;
  v = NULL;

  if(size)
  {
    c = size;
    v = new double[c];
    if(!v)
      throw "allocation problem";
    for(int i = 0; i < c; i++)
    {
      v[i] = 0;
    }
  }
}

anotherVector::anotherVector(const anotherVector& rhs)
{
  c = 0;
  v = NULL;
  if(rhs.c)
  {
    c = rhs.c;
    v = new double[c];
    if(!v)
      throw "allocation problem";
    for(int i = 0; i < c; i++)
    {
      v[i] = rhs.v[i];
    }
  }
}

anotherVector::~anotherVector()
{
  if(v)
  {
    delete[] v;
  }
}

unsigned int anotherVector::Columns() const
{
  return c;
}

unsigned int anotherVector::Length() const
{
  return c;
}

bool anotherVector::isEmpty()
{
  return (c == 0);
}

anotherVector& anotherVector::operator=(const anotherVector& rhs)
{
  if(this != &rhs)
  {
    if(v)
    {
      delete[] v;
    }

    c = 0;
    v = NULL;
    if(rhs.c)
    {
      c = rhs.c;
      v = new double[c];
      if(!v)
        throw "allocation problem";
      for(int i = 0; i < c; i++)
      {
        v[i] = rhs.v[i];
      }
    }
  }
  return *this;
}

void anotherVector::setSize(const unsigned int size)
{
  if(v)
  {
    delete[] v;
  }

  c = 0;
  v = NULL;

  if(size)
  {
    c = size;
    v = new double[c];
    if(!v)
      throw "allocation problem";
    for(int i = 0; i < c; i++)
    {
      v[i] = 0;
    }
  }
}

double& anotherVector::operator[](unsigned int i)
{
  if(v == NULL)
    throw "Vector is empty";
  else if(i >= c)
    throw "Invalid column";
  else
    return v[i];
}

anotherVector anotherVector::operator+(const anotherVector& rhs)
{
  if(!v || !rhs.v)
    throw "Vector is empty";
  else
  if(c != rhs.c)
    throw "Vector dimensions do not match";
  
  anotherVector rez = *this;
  for(int i = 0; i < rez.c; i++)
    rez.v[i] += rhs.v[i];

  return rez;
}

anotherVector anotherVector::operator+(const double& rhs)
{
  if(!v)
    throw "Vector is empty";
 
  anotherVector rez = *this;
  for(int i = 0; i < rez.c; i++)
    rez.v[i] += rhs;

  return rez;
}

anotherVector& anotherVector::operator+=(const anotherVector& rhs)
{
  if(!v || !rhs.v)
    throw "Vector is empty";
  else
  if(c != rhs.c)
    throw "Vector dimensions do not match";

  for(int i = 0; i < c; i++)
    v[i] += rhs.v[i];

  return *this;
}

anotherVector& anotherVector::operator+=(const double& rhs)
{
  if(!v)
    throw "Vector is empty";

  for(int i = 0; i < c; i++)
    v[i] += rhs;

  return *this;
}


anotherVector anotherVector::operator-(const anotherVector& rhs)
{
  if(!v || !rhs.v)
    throw "Vector is empty";
  else
  if(c != rhs.c)
    throw "Vector dimensions do not match";
  
  anotherVector rez = *this;
  for(int i = 0; i < rez.c; i++)
    rez.v[i] -= rhs.v[i];

  return rez;
}

anotherVector anotherVector::operator-(const double& rhs)
{
  if(!v)
    throw "Vector is empty";
  
  anotherVector rez = *this;
  for(int i = 0; i < rez.c; i++)
    rez.v[i] -= rhs;

  return rez;
}

anotherVector& anotherVector::operator-=(const anotherVector& rhs)
{
  if(!v || !rhs.v)
    throw "Vector is empty";
  else
  if(c != rhs.c)
    throw "Vector dimensions do not match";

  for(int i = 0; i < c; i++)
    v[i] -= rhs.v[i];

  return *this;
}

anotherVector& anotherVector::operator-=(const double& rhs)
{
  if(!v)
    throw "Vector is empty";

  for(int i = 0; i < c; i++)
    v[i] -= rhs;

  return *this;
}

anotherVector anotherVector::operator*(const double& rhs)
{
  if(!v)
    throw "Vector is empty";
  
  anotherVector rez = *this;
  for(int i = 0; i < rez.c; i++)
    rez.v[i] *= rhs;

  return rez;
}

anotherVector& anotherVector::operator*=(const double& rhs)
{
  if(!v)
    throw "Vector is empty";

  for(int i = 0; i < c; i++)
    v[i] *= rhs;

  return *this;
}

anotherVector anotherVector::operator/(const double& rhs)
{
  if(!v)
    throw "Vector is empty";
  
  anotherVector rez = *this;
  for(int i = 0; i < rez.c; i++)
    rez.v[i] /= rhs;

  return rez;
}

anotherVector& anotherVector::operator/=(const double& rhs)
{
  if(!v)
    throw "Vector is empty";

  for(int i = 0; i < c; i++)
    v[i] /= rhs;

  return *this;
}

anotherVector anotherVector::operator-()
{
  if(v)
  {
    anotherVector rez(c);
    for(int i = 0; i < c; i++)
      rez.v[i] = -v[i];

    return rez;
  }
  else
    return anotherVector();
}

anotherVector anotherVector::operator~()
{
  if(v)
  {
    anotherVector rez(c);
    for(int i = 0; i < c; i++)
        rez.v[i] = v[c - 1 - i];

    return rez;
  }
  else
    return anotherVector();
}


/*
  The functions below are not in the anotherVector class
*/

anotherVector operator+(const double& lhs, const anotherVector& rhs)
{
  if(!rhs.v)
    throw "Vector is empty";
 
  anotherVector rez = rhs;
  for(int i = 0; i < rez.c; i++)
    rez.v[i] += lhs;

  return rez;
}

anotherVector operator-(const double& lhs, const anotherVector& rhs)
{
  if(!rhs.v)
    throw "Vector is empty";
  
  anotherVector rez = rhs;
  for(int i = 0; i < rez.c; i++)
    rez.v[i] -= lhs;

  return rez;
}

anotherVector operator*(const double& lhs, const anotherVector& rhs)
{
  if(!rhs.v)
    throw "Vector is empty";
  
  anotherVector rez = rhs;
  for(int i = 0; i < rez.c; i++)
    rez.v[i] *= lhs;

  return rez;
}

ostream& operator<<(ostream& out, const anotherVector& td)
{
  if(td.v)
  {
    for(int i = 0; i < td.c; i++)
      out << td.v[i] << " ";
  }
  return out;
}
