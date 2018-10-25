#include "anotherMatrix.h"
using namespace std;

anotherMatrix::anotherMatrix()
{
  l = 0;
  m = NULL;
}

anotherMatrix::anotherMatrix(const unsigned int size)
{
  l = 0;
  m = NULL;

  if(size)
  {
    l = size;
    m = new double*[l];
    if(!m)
      throw "allocation problem";
    for(int i = 0; i < l; i++)
    {
      m[i] = new double[c];
      if(!m[i])
        throw "allocation problem";
      for(int j = 0; j < c; j++)
        m[i][j] = 0;
    }
  }
}

anotherMatrix::anotherMatrix(const unsigned int lines, const unsigned int columns)
{
  l = 0;
  c = 0;
  m = NULL;

  if(lines && columns)
  {
    l = lines;
    c = columns;
    m = new double*[l];
    if(!m)
      throw "allocation problem";
    for(int i = 0; i < l; i++)
    {
      m[i] = new double[c];
      if(!m[i])
        throw "allocation problem";
      for(int j = 0; j < c; j++)
        m[i][j] = 0;
    }
  }
}

anotherMatrix::anotherMatrix(const anotherMatrix& rhs)
{
  l = 0;
  c = 0;
  m = NULL;
  if(rhs.l && rhs.c)
  {
    l = rhs.l;
    c = rhs.c;
    m = new double*[l];
    if(!m)
      throw "allocation problem";
    for(int i = 0; i < l; i++)
    {
      m[i] = new double[c];
      if(!m[i])
        throw "allocation problem";
      for(int j = 0; j < c; j++)
        m[i][j] = rhs.m[i][j];
    }
  }
}

anotherMatrix::~anotherMatrix()
{
  if(m)
  {
    for(int i = 0; i < l; i++)
      if(m[i])
        delete[] m[i];
    delete[] m;
  }
}

unsigned int anotherMatrix::Lines() const
{
  return l;
}

unsigned int anotherMatrix::Columns() const
{
  return c;
}

bool anotherMatrix::isEmpty()
{
  return (m == NULL);
}

anotherMatrix& anotherMatrix::operator=(const anotherMatrix& rhs)
{
  if(this != &rhs)
  {
    if(m)
    {
      for(int i = 0; i < l; i++)
        if(m[i])
          delete[] m[i];
      delete[] m;
    }

    l = 0;
    c = 0;
    m = NULL;
    if(rhs.l && rhs.c)
    {
      l = rhs.l;
      c = rhs.c;
      m = new double*[l];
      if(!m)
        throw "allocation problem";
      for(int i = 0; i < l; i++)
      {
        m[i] = new double[c];
        if(!m[i])
          throw "allocation problem";
        for(int j = 0; j < c; j++)
          m[i][j] = rhs.m[i][j];
      }
    }
  }
  return *this;
}

double& anotherMatrix::operator()(unsigned int i, unsigned int j)
{
  if(m == NULL)
    throw "Matrix is empty";
  else if(i >= l)
    throw "Invalid line";
  else if(j >= c)
    throw "Invalid column";
  else
    return m[i][j];
}

anotherMatrix anotherMatrix::operator+(const anotherMatrix& rhs)
{
  if(!m || !rhs.m)
    throw "Matrix is empty";
  else
  if(c != rhs.c || l != rhs.l)
    throw "Matrix dimensions do not match";
  
  anotherMatrix rez = *this;
  for(int i = 0; i < rez.l; i++)
    for(int j = 0; j < rez.c; j++)
      rez.m[i][j] += rhs.m[i][j];

  return rez;
}

anotherMatrix anotherMatrix::operator+(const double& rhs)
{
  if(!m)
    throw "Matrix is empty";
 
  anotherMatrix rez = *this;
  for(int i = 0; i < rez.l; i++)
    for(int j = 0; j < rez.c; j++)
      rez.m[i][j] += rhs;

  return rez;
}

anotherMatrix& anotherMatrix::operator+=(const anotherMatrix& rhs)
{
  if(!m || !rhs.m)
    throw "Matrix is empty";
  else
  if(c != rhs.c || l != rhs.l)
    throw "Matrix dimensions do not match";

  for(int i = 0; i < l; i++)
    for(int j = 0; j < c; j++)
      m[i][j] += rhs.m[i][j];

  return *this;
}

anotherMatrix& anotherMatrix::operator+=(const double& rhs)
{
  if(!m)
    throw "Matrix is empty";

  for(int i = 0; i < l; i++)
    for(int j = 0; j < c; j++)
      m[i][j] += rhs;

  return *this;
}


anotherMatrix anotherMatrix::operator-(const anotherMatrix& rhs)
{
  if(!m || !rhs.m)
    throw "Matrix is empty";
  else
  if(c != rhs.c || l != rhs.l)
    throw "Matrix dimensions do not match";
  
  anotherMatrix rez = *this;
  for(int i = 0; i < rez.l; i++)
    for(int j = 0; j < rez.c; j++)
      rez.m[i][j] -= rhs.m[i][j];

  return rez;
}

anotherMatrix anotherMatrix::operator-(const double& rhs)
{
  if(!m)
    throw "Matrix is empty";
  
  anotherMatrix rez = *this;
  for(int i = 0; i < rez.l; i++)
    for(int j = 0; j < rez.c; j++)
      rez.m[i][j] -= rhs;

  return rez;
}

anotherMatrix& anotherMatrix::operator-=(const anotherMatrix& rhs)
{
  if(!m || !rhs.m)
    throw "Matrix is empty";
  else
  if(c != rhs.c || l != rhs.l)
    throw "Matrix dimensions do not match";

  for(int i = 0; i < l; i++)
    for(int j = 0; j < c; j++)
      m[i][j] -= rhs.m[i][j];

  return *this;
}

anotherMatrix& anotherMatrix::operator-=(const double& rhs)
{
  if(!m)
    throw "Matrix is empty";

  for(int i = 0; i < l; i++)
    for(int j = 0; j < c; j++)
      m[i][j] -= rhs;

  return *this;
}

anotherMatrix anotherMatrix::operator*(const anotherMatrix& rhs)
{
  if(!m || !rhs.m)
    throw "Matrix is empty";

  if(c != rhs.l)
    throw "Matrix dimensions do not match";
  
  anotherMatrix rez(l, rhs.c);
  for(int i = 0; i < rez.l; i++)
    for(int j = 0; j < rez.c; j++)
      for(int k = 0; k < c; k++)
        rez.m[i][j] += m[i][k]*rhs.m[k][j];

  return rez;
}

anotherMatrix anotherMatrix::operator*(const double& rhs)
{
  if(!m)
    throw "Matrix is empty";
  
  anotherMatrix rez = *this;
  for(int i = 0; i < rez.l; i++)
    for(int j = 0; j < rez.c; j++)
      rez.m[i][j] *= rhs;

  return rez;
}

anotherMatrix& anotherMatrix::operator*=(const anotherMatrix& rhs)
{
  //too lazy... we use the * operator
  anotherMatrix rez = *this * rhs;

  for(int i = 0; i < l; i++)
    if(m[i])
      delete[] m[i];
  delete[] m;

  l = rez.l;
  c = rez.c;
  m = new double*[l];
  if(!m)
    throw "allocation problem";
  for(int i = 0; i < l; i++)
  {
    m[i] = new double[c];
    if(!m[i])
      throw "allocation problem";
    for(int j = 0; j < c; j++)
      m[i][j] = rhs.m[i][j];
  }

  for(int i = 0; i < rez.l; i++)
    for(int j = 0; j < rez.c; j++)
      m[i][j] = rez.m[i][j];

  return *this;
}

anotherMatrix& anotherMatrix::operator*=(const double& rhs)
{
  if(!m)
    throw "Matrix is empty";

  for(int i = 0; i < l; i++)
    for(int j = 0; j < c; j++)
      m[i][j] *= rhs;

  return *this;
}

anotherMatrix anotherMatrix::operator/(const anotherMatrix& rhs)
{
  anotherMatrix inverse = rhs;
  return operator*(!inverse);
}

anotherMatrix anotherMatrix::operator/(const double& rhs)
{
  if(!m)
    throw "Matrix is empty";
  
  anotherMatrix rez = *this;
  for(int i = 0; i < rez.l; i++)
    for(int j = 0; j < rez.c; j++)
      rez.m[i][j] /= rhs;

  return rez;
}

anotherMatrix& anotherMatrix::operator/=(const anotherMatrix& rhs)
{
  anotherMatrix rez = *this / rhs;

  for(int i = 0; i < l; i++)
    if(m[i])
      delete[] m[i];
  delete[] m;

  l = rez.l;
  c = rez.c;
  m = new double*[l];
  if(!m)
    throw "allocation problem";
  for(int i = 0; i < l; i++)
  {
    m[i] = new double[c];
    if(!m[i])
      throw "allocation problem";
    for(int j = 0; j < c; j++)
      m[i][j] = rhs.m[i][j];
  }

  for(int i = 0; i < rez.l; i++)
    for(int j = 0; j < rez.c; j++)
      m[i][j] = rez.m[i][j];

  return *this;
}

anotherMatrix& anotherMatrix::operator/=(const double& rhs)
{
  if(!m)
    throw "Matrix is empty";

  for(int i = 0; i < l; i++)
    for(int j = 0; j < c; j++)
      m[i][j] /= rhs;

  return *this;
}

anotherMatrix anotherMatrix::operator-()
{
  if(m)
  {
    anotherMatrix rez(l, c);
    for(int i = 0; i < l; i++)
      for(int j = 0; j < c; j++)
        rez.m[i][j] = -m[i][j];

    return rez;
  }
  else
    return anotherMatrix();
}

anotherMatrix anotherMatrix::operator~()
{
  if(m)
  {
    anotherMatrix rez(c, l);
    for(int i = 0; i < l; i++)
      for(int j = 0; j < c; j++)
        rez.m[j][i] = m[i][j];

    return rez;
  }
  else
    return anotherMatrix();
}

anotherMatrix anotherMatrix::operator!()
{
  if(!m)
    throw "Matrix is empty";
  if(c != l)
    throw "Matrix is not square";

  double det_final = 0;
  anotherMatrix minor(l);
  if(l == 2)
  {
    det_final = determinant();
    minor(0, 0) = m[1][1];
    minor(0, 1) = -m[1][0];
    minor(1, 0) = -m[0][1];
    minor(1, 1) = m[0][0];
  }
  else
  {
    
    anotherMatrix small(l - 1);
    
    for(int i = 0; i < l; i++)
      for(int j = 0; j < l; j++)
      {
        //create new small
        for(int i2 = 0; i2 < l - 1; i2++)
          for(int j2 = 0; j2 < l - 1; j2++)
          {
            if(i2 < i)
            {
              if(j2 < j)
                small.m[i2][j2] = m[i2][j2];
              else
                small.m[i2][j2] = m[i2][j2 + 1];
            }
            else
            {
              if(j2 < j)
                small.m[i2][j2] = m[i2 + 1][j2];
              else
                small.m[i2][j2] = m[i2 + 1][j2 + 1];
            }
          }
        
        minor(i, j) = determinant(small, l - 1);
        if((i + j) % 2 == 1)
          minor(i, j) *= -1;
      }

    //calculate determinant of *this
    for(int i = 0; i < l; i++)
      det_final += m[0][i]*minor(0, i);
  }

  if(det_final == 0)
    throw "Matrix has no inverse";

  minor = minor / det_final;
  return ~minor;
}



double anotherMatrix::determinant(const anotherMatrix& x, const unsigned int level)
{
  if(level == 2)
    return x.m[0][0] * x.m[1][1] - x.m[1][0]*x.m[0][1];
  
  double result = 0;
  anotherMatrix *n = NULL;
  for(int k = 0; k < level; k++)
  {
    n = new anotherMatrix(level - 1, level - 1);
    if(!n)
      throw "allocation problem";

    for(int i = 0; i < level - 1; i++)
      for(int j = 0; j < level - 1; j++)
      {
        if(j < k)
          n->m[i][j] = x.m[i + 1][j];
        else
          n->m[i][j] = x.m[i + 1][j + 1];
      }

    if(k % 2 == 0)
      result += x.m[0][k] * determinant(*n, level - 1);
    else
      result -= x.m[0][k] * determinant(*n, level - 1);

    delete n;
  }

  return result;
}

double anotherMatrix::determinant()
{
  if(!m)
    throw "Matrix is empty";
  if(Lines() != Columns())
    throw "Matrix is not square";
  else
    return determinant(*this, Lines());
}



/*
  The functions below are not in the anotherMatrix class
*/

anotherMatrix operator+(const double& lhs, const anotherMatrix& rhs)
{
  if(!rhs.m)
    throw "Matrix is empty";
 
  anotherMatrix rez = rhs;
  for(int i = 0; i < rez.l; i++)
    for(int j = 0; j < rez.c; j++)
      rez.m[i][j] += lhs;

  return rez;
}

anotherMatrix operator-(const double& lhs, const anotherMatrix& rhs)
{
  if(!rhs.m)
    throw "Matrix is empty";
  
  anotherMatrix rez = rhs;
  for(int i = 0; i < rez.l; i++)
    for(int j = 0; j < rez.c; j++)
      rez.m[i][j] -= lhs;

  return rez;
}

anotherMatrix operator*(const double& lhs, const anotherMatrix& rhs)
{
  if(!rhs.m)
    throw "Matrix is empty";
  
  anotherMatrix rez = rhs;
  for(int i = 0; i < rez.l; i++)
    for(int j = 0; j < rez.c; j++)
      rez.m[i][j] *= lhs;

  return rez;
}

ostream& operator<<(ostream& out, const anotherMatrix& td)
{
  if(td.m)
  {
    for(int i = 0; i < td.l; i++)
    {
      for(int j = 0; j < td.c; j++)
        out << td.m[i][j] << " ";
      out << endl;
    }
  }
  return out;
}
