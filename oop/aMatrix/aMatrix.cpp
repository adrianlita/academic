#include "aMatrix.h"
using namespace std;

aMatrix::aMatrix()
{
  l = 0;
  c = 0;
  m = NULL;
}

aMatrix::aMatrix(const unsigned int size)
{
  l = 0;
  c = 0;
  m = NULL;

  if(size)
  {
    l = size;
    c = size;
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

aMatrix::aMatrix(const unsigned int lines, const unsigned int columns)
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

aMatrix::aMatrix(const aMatrix& rhs)
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

aMatrix::~aMatrix()
{
  if(m)
  {
    for(int i = 0; i < l; i++)
      if(m[i])
        delete[] m[i];
    delete[] m;
  }
}

unsigned int aMatrix::Lines() const
{
  return l;
}

unsigned int aMatrix::Columns() const
{
  return c;
}

bool aMatrix::isEmpty()
{
  return (m == NULL);
}

aMatrix& aMatrix::operator=(const aMatrix& rhs)
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

double& aMatrix::operator()(unsigned int i, unsigned int j)
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

aMatrix aMatrix::operator+(const aMatrix& rhs)
{
  if(!m || !rhs.m)
    throw "Matrix is empty";
  else
  if(c != rhs.c || l != rhs.l)
    throw "Matrix dimensions do not match";
  
  aMatrix rez = *this;
  for(int i = 0; i < rez.l; i++)
    for(int j = 0; j < rez.c; j++)
      rez.m[i][j] += rhs.m[i][j];

  return rez;
}

aMatrix aMatrix::operator+(const double& rhs)
{
  if(!m)
    throw "Matrix is empty";
 
  aMatrix rez = *this;
  for(int i = 0; i < rez.l; i++)
    for(int j = 0; j < rez.c; j++)
      rez.m[i][j] += rhs;

  return rez;
}

aMatrix& aMatrix::operator+=(const aMatrix& rhs)
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

aMatrix& aMatrix::operator+=(const double& rhs)
{
  if(!m)
    throw "Matrix is empty";

  for(int i = 0; i < l; i++)
    for(int j = 0; j < c; j++)
      m[i][j] += rhs;

  return *this;
}


aMatrix aMatrix::operator-(const aMatrix& rhs)
{
  if(!m || !rhs.m)
    throw "Matrix is empty";
  else
  if(c != rhs.c || l != rhs.l)
    throw "Matrix dimensions do not match";
  
  aMatrix rez = *this;
  for(int i = 0; i < rez.l; i++)
    for(int j = 0; j < rez.c; j++)
      rez.m[i][j] -= rhs.m[i][j];

  return rez;
}

aMatrix aMatrix::operator-(const double& rhs)
{
  if(!m)
    throw "Matrix is empty";
  
  aMatrix rez = *this;
  for(int i = 0; i < rez.l; i++)
    for(int j = 0; j < rez.c; j++)
      rez.m[i][j] -= rhs;

  return rez;
}

aMatrix& aMatrix::operator-=(const aMatrix& rhs)
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

aMatrix& aMatrix::operator-=(const double& rhs)
{
  if(!m)
    throw "Matrix is empty";

  for(int i = 0; i < l; i++)
    for(int j = 0; j < c; j++)
      m[i][j] -= rhs;

  return *this;
}

aMatrix aMatrix::operator*(const aMatrix& rhs)
{
  if(!m || !rhs.m)
    throw "Matrix is empty";

  if(c != rhs.l)
    throw "Matrix dimensions do not match";
  
  aMatrix rez(l, rhs.c);
  for(int i = 0; i < rez.l; i++)
    for(int j = 0; j < rez.c; j++)
      for(int k = 0; k < c; k++)
        rez.m[i][j] += m[i][k]*rhs.m[k][j];

  return rez;
}

aMatrix aMatrix::operator*(const double& rhs)
{
  if(!m)
    throw "Matrix is empty";
  
  aMatrix rez = *this;
  for(int i = 0; i < rez.l; i++)
    for(int j = 0; j < rez.c; j++)
      rez.m[i][j] *= rhs;

  return rez;
}

aMatrix& aMatrix::operator*=(const aMatrix& rhs)
{
  //too lazy... we use the * operator
  aMatrix rez = *this * rhs;

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

aMatrix& aMatrix::operator*=(const double& rhs)
{
  if(!m)
    throw "Matrix is empty";

  for(int i = 0; i < l; i++)
    for(int j = 0; j < c; j++)
      m[i][j] *= rhs;

  return *this;
}

aMatrix aMatrix::operator/(const aMatrix& rhs)
{
  aMatrix inverse = rhs;
  return operator*(!inverse);
}

aMatrix aMatrix::operator/(const double& rhs)
{
  if(!m)
    throw "Matrix is empty";
  
  aMatrix rez = *this;
  for(int i = 0; i < rez.l; i++)
    for(int j = 0; j < rez.c; j++)
      rez.m[i][j] /= rhs;

  return rez;
}

aMatrix& aMatrix::operator/=(const aMatrix& rhs)
{
  aMatrix rez = *this / rhs;

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

aMatrix& aMatrix::operator/=(const double& rhs)
{
  if(!m)
    throw "Matrix is empty";

  for(int i = 0; i < l; i++)
    for(int j = 0; j < c; j++)
      m[i][j] /= rhs;

  return *this;
}

aMatrix aMatrix::operator-()
{
  if(m)
  {
    aMatrix rez(l, c);
    for(int i = 0; i < l; i++)
      for(int j = 0; j < c; j++)
        rez.m[i][j] = -m[i][j];

    return rez;
  }
  else
    return aMatrix();
}

aMatrix aMatrix::operator~()
{
  if(m)
  {
    aMatrix rez(c, l);
    for(int i = 0; i < l; i++)
      for(int j = 0; j < c; j++)
        rez.m[j][i] = m[i][j];

    return rez;
  }
  else
    return aMatrix();
}

aMatrix aMatrix::operator!()
{
  if(!m)
    throw "Matrix is empty";
  if(c != l)
    throw "Matrix is not square";

  double det_final = 0;
  aMatrix minor(l);
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
    
    aMatrix small(l - 1);
    
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



double aMatrix::determinant(const aMatrix& x, const unsigned int level)
{
  if(level == 2)
    return x.m[0][0] * x.m[1][1] - x.m[1][0]*x.m[0][1];
  
  double result = 0;
  aMatrix *n = NULL;
  for(int k = 0; k < level; k++)
  {
    n = new aMatrix(level - 1, level - 1);
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

double aMatrix::determinant()
{
  if(!m)
    throw "Matrix is empty";
  if(Lines() != Columns())
    throw "Matrix is not square";
  else
    return determinant(*this, Lines());
}



/*
  The functions below are not in the aMatrix class
*/

aMatrix operator+(const double& lhs, const aMatrix& rhs)
{
  if(!rhs.m)
    throw "Matrix is empty";
 
  aMatrix rez = rhs;
  for(int i = 0; i < rez.l; i++)
    for(int j = 0; j < rez.c; j++)
      rez.m[i][j] += lhs;

  return rez;
}

aMatrix operator-(const double& lhs, const aMatrix& rhs)
{
  if(!rhs.m)
    throw "Matrix is empty";
  
  aMatrix rez = rhs;
  for(int i = 0; i < rez.l; i++)
    for(int j = 0; j < rez.c; j++)
      rez.m[i][j] -= lhs;

  return rez;
}

aMatrix operator*(const double& lhs, const aMatrix& rhs)
{
  if(!rhs.m)
    throw "Matrix is empty";
  
  aMatrix rez = rhs;
  for(int i = 0; i < rez.l; i++)
    for(int j = 0; j < rez.c; j++)
      rez.m[i][j] *= lhs;

  return rez;
}

ostream& operator<<(ostream& out, const aMatrix& td)
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
