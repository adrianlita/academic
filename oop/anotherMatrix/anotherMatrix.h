#pragma once

#include <iostream>
#include "anotherVector.h"

class anotherMatrix
{
  anotherVector *m;         //here we will store the actual data
  unsigned int l, c;        //number of lines. as a rule, whenever l is zero, m will be NULL

  double determinant(const anotherMatrix& x, const unsigned int level);  //internally calculation of matrix determinant
public:
  anotherMatrix();  //implicit constructor
  anotherMatrix(const unsigned int size);  //initializiation constructor for square matrix
  anotherMatrix(const unsigned int lines, const unsigned int columns);  //initializiation constructor for any matrix
  anotherMatrix(const anotherMatrix& rhs);  //copy constructor
  ~anotherMatrix(); //destructor
  anotherMatrix& operator=(const anotherMatrix& rhs);  //copy operator

  unsigned int Lines() const; //returns the number of lines
  unsigned int Columns() const; //returns the number of columns
  bool isEmpty(); //returns true if matrix is empty (i.e.: size is zero, false otherwise)

  double& operator[](unsigned int i); //index operator, used to access matrix elements (lines)

  //+ (add) operation
  anotherMatrix operator+(const anotherMatrix& rhs);
  anotherMatrix operator+(const double& rhs);
  friend anotherMatrix operator+(const double& lhs, const anotherMatrix& rhs);
  anotherMatrix& operator+=(const anotherMatrix& rhs);
  anotherMatrix& operator+=(const double& rhs);

  //- (substract) operation
  anotherMatrix operator-(const anotherMatrix& rhs);
  anotherMatrix operator-(const double& rhs);
  friend anotherMatrix operator-(const double& lhs, const anotherMatrix& rhs);
  anotherMatrix& operator-=(const anotherMatrix& rhs);
  anotherMatrix& operator-=(const double& rhs);

  //* (multiply) operation
  anotherMatrix operator*(const anotherMatrix& rhs);
  anotherMatrix operator*(const double& rhs);
  friend anotherMatrix operator*(const double& lhs, const anotherMatrix& rhs);
  anotherMatrix& operator*=(const anotherMatrix& rhs);
  anotherMatrix& operator*=(const double& rhs);

  /// (divide) operation
  anotherMatrix operator/(const anotherMatrix& rhs);
  anotherMatrix operator/(const double& rhs);
  anotherMatrix& operator/=(const anotherMatrix& rhs);
  anotherMatrix& operator/=(const double& rhs);

  anotherMatrix operator-();  //negation of matrix
  anotherMatrix operator~();  //transpose of matrix
  anotherMatrix operator!();  //inverse of matrix

  double determinant();

  friend std::ostream& operator<<(std::ostream& lhs, const anotherMatrix& rhs);  //allowing the use of std::ostream

  //static functions (can be used without instantiating objects)
  static anotherMatrix identityMatrix(const unsigned int size)
  {
    anotherMatrix rez(size, size);
    for(int i = 0; i < size; i++)
      rez.m[i][i] = 1;
    return rez;
  }

  static anotherMatrix zeroMatrix(const unsigned int size)
  {
    return anotherMatrix(size);
  }

  static anotherMatrix zeroMatrix(const unsigned int lines, const unsigned int columns)
  {
    return anotherMatrix(lines, columns);
  }
};
