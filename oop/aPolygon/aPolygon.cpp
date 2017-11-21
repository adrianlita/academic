#include "aPolygon.h"
#include "../utils/utils.h"
#include <math.h>
using namespace std;

void aPolygon::set_name(const char *s)
{
  if(name)
    delete[] name;

  name = new char[strlen(s) + 1];
  if(!name)
    throw "memory allocation error";
  strcpy(name, s);
}

aPolygon::aPolygon()
{
  n = 0;
  l = NULL;
  name = NULL;
  set_name("aPolygon");
}

aPolygon::aPolygon(const int ne)
{
  if(ne < 3)
    throw "too few edges";

  n = ne;
  l = new double[n];
  if(!l)
    throw "memory allocation error";
  for(int i = 0; i < n; i++)
    l[i] = 1;
  
  name = NULL;
  set_name("aPolygon");
}

aPolygon::aPolygon(const aPolygon& rhs)
{
  if(rhs.n < 3)
    throw "too few edges";

  n = rhs.n;
  l = new double[n];
  if(!l)
    throw "memory allocation error";
  for(int i = 0; i < n; i++)
    l[i] = rhs.l[i];

  name = NULL;
  set_name("aPolygon");
}

aPolygon::~aPolygon()
{
  delete[] l;

  if(name)
    delete[] name;
}

aPolygon& aPolygon::operator=(const aPolygon& rhs)
{
  if(this != &rhs)
  {
    if(l)
      delete[] l;

    if(name)
      delete[] name;

    if(rhs.n < 3)
      throw "too few edges";
    n = rhs.n;
    l = new double[n];
    if(!l)
      throw "memory allocation error";
    for(int i = 0; i < n; i++)
      l[i] = rhs.l[i];

    set_name("aPolygon");
  }
  return *this;
}

double aPolygon::Edges() const
{
  return n;
}

void aPolygon::setLength(const int edge_no, const double length)
{
  if((edge_no < 0) || (edge_no >= n))
    throw "bad index";

  if(length <= 0)
    throw "invalid length";

  l[edge_no] = length;
}

double aPolygon::Perimeter() const
{
  double s = l[0];
  for(int i = 1; i < n; i++)
    s += l[i];
  return s;
}

double aPolygon::operator[](int i) const
{
  if((i < 0) || (i >= n))
    throw "bad index";
  return l[i];
}

ostream& operator<<(ostream& out, const aPolygon& rhs)
{
  out << "Polygon(" << rhs.n << ") ";
  out << "-" << rhs.name << "-";
  out << ": ";
  for(int i = 0; i < rhs.n; i++)
    out << rhs.l[i] << " ";

  return out;
}

aTriangle::aTriangle() : aPolygon(3)
{
  set_name("aTriangle");
}

aTriangle::aTriangle(const double a, const double b, const double c) : aPolygon(3)
{
  if(a <= 0)
    throw "invalid length";

  if(b <= 0)
    throw "invalid length";

  if(c <= 0)
    throw "invalid length";

  l[0] = a;
  l[1] = b;
  l[2] = c;

  set_name("aTriangle");
}

void aTriangle::setLength(const double a, const double b, const double c)
{
  if(a <= 0)
    throw "invalid length";

  if(b <= 0)
    throw "invalid length";

  if(c <= 0)
    throw "invalid length";

  l[0] = a;
  l[1] = b;
  l[2] = c;
}

double aTriangle::Area() const
{
  double s = this->Perimeter() / 2;
  return sqrt(s*(s-l[0])*(s-l[1])*(s-l[2]));
}

bool aTriangle::isRight() const
{
  double c1 = l[0], c2 = l[0], ip = l[0], aux;
  if(ip < c1)
  {
    aux = ip;
    ip = c1;
    c1 = aux;
  }

  if(ip < c2)
  {
    aux = ip;
    ip = c1;
    c1 = aux;
  }

  //pythagora
  if((c1*c1)+(c2*c2) == (ip*ip))
    return true;
  else
    return false;
}

bool aTriangle::isIsosceles() const
{
  if(l[0] == l[1])
    return true;
  if(l[0] == l[2])
    return true;
  if(l[1] == l[2])
    return true;
  return false;
}

bool aTriangle::isEquilateral() const
{
  if(l[0] == l[1])
    if(l[1] == l[2])
      return true;
  return false;
}

aRectangle::aRectangle() : aPolygon(4)
{
  set_name("aRectangle");
}

aRectangle::aRectangle(const double side0, const double side1) : aPolygon(4)
{
  if(side0 <= 0)
    throw "invalid length";

  if(side1 <= 0)
    throw "invalid length";

  l[0] = l[2] = side0;
  l[1] = l[3] = side1;

  set_name("aRectangle");
}

void aRectangle::setLength(const int edge_no, const double length)
{
  if((edge_no < 0) || (edge_no >= n))
    throw "bad index";

  if(length <= 0)
    throw "invalid length";

  if((edge_no == 0) || (edge_no == 2))
  {
    l[0] = length;
    l[2] = length;
  }
  else
  if((edge_no == 1) || (edge_no == 3))
  {
    l[1] = length;
    l[3] = length;
  }
}

void aRectangle::setLength(const double side0, const double side1)
{
  if(side0 <= 0)
    throw "invalid length";
  
  if(side1 <= 0)
    throw "invalid length";

  l[0] = l[2] = side0;
  l[1] = l[3] = side1;
}

double aRectangle::Perimeter() const
{
  return 2*(l[0]+l[1]);
}

double aRectangle::Area() const
{
  return l[0]*l[1];
}

bool aRectangle::isSquare()
{
  if(l[0] == l[1])
    return true;
  else
    return false;
}

void aSquare::setLength(const double side0, const double side1)
{
  //do nothing, as this is just masked (private, so there can be no usege of it, as it may be wrongfully used)
}

aSquare::aSquare() : aRectangle()
{
  set_name("aSquare");
}

aSquare::aSquare(const double length) : aRectangle(length, length)
{
  set_name("aSquare");
}

void aSquare::setLength(const int edge_no, const double length)
{
  if((edge_no < 0) || (edge_no >= n))
    throw "bad index";

  if(length <= 0)
    throw "invalid length";

  l[0] = length;
  l[1] = length;
  l[2] = length;
  l[3] = length;
}

void aSquare::setLength(const double length)
{
  aRectangle::setLength(length, length);
}

double aSquare::Perimeter() const
{
  return 4*l[0];
}
