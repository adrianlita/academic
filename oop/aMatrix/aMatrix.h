#pragma once

#include <iostream>

class aMatrix
{
  double **m;               //here we will store the actual data
  unsigned int l, c;        //lines and columns. as a rule, whenever l or c is zero, m will be NULL

  double determinant(const aMatrix& x, const unsigned int level);  //internally calculation of matrix determinant
public:
  aMatrix();  //implicit constructor
  aMatrix(const unsigned int size);  //initializiation constructor for square matrix
  aMatrix(const unsigned int lines, const unsigned int columns);  //initializiation constructor for any matrix
  aMatrix(const aMatrix& rhs);  //copy constructor
  ~aMatrix(); //destructor
  aMatrix& operator=(const aMatrix& rhs);  //copy operator

  unsigned int Lines() const; //returns the number of lines
  unsigned int Columns() const; //returns the number of columns
  bool isEmpty(); //returns true if matrix is empty (i.e.: size is zero, false otherwise)

  double& operator()(unsigned int i, unsigned int j); //function operator, used to access matrix elements

  //+ (add) operation
  aMatrix operator+(const aMatrix& rhs);
  aMatrix operator+(const double& rhs);
  friend aMatrix operator+(const double& lhs, const aMatrix& rhs);
  aMatrix& operator+=(const aMatrix& rhs);
  aMatrix& operator+=(const double& rhs);

  //- (substract) operation
  aMatrix operator-(const aMatrix& rhs);
  aMatrix operator-(const double& rhs);
  friend aMatrix operator-(const double& lhs, const aMatrix& rhs);
  aMatrix& operator-=(const aMatrix& rhs);
  aMatrix& operator-=(const double& rhs);

  //* (multiply) operation
  aMatrix operator*(const aMatrix& rhs);
  aMatrix operator*(const double& rhs);
  friend aMatrix operator*(const double& lhs, const aMatrix& rhs);
  aMatrix& operator*=(const aMatrix& rhs);
  aMatrix& operator*=(const double& rhs);

  /// (divide) operation
  aMatrix operator/(const aMatrix& rhs);
  aMatrix operator/(const double& rhs);
  aMatrix& operator/=(const aMatrix& rhs);
  aMatrix& operator/=(const double& rhs);

  aMatrix operator-();  //negation of matrix
  aMatrix operator~();  //transpose of matrix
  aMatrix operator!();  //inverse of matrix

  double determinant();

  friend std::ostream& operator<<(std::ostream& lhs, const aMatrix& rhs);  //allowing the use of std::ostream

  //static functions (can be used without instantiating objects)
  static aMatrix identityMatrix(const unsigned int size)
  {
    aMatrix rez(size, size);
    for(int i = 0; i < size; i++)
      rez.m[i][i] = 1;
    return rez;
  }

  static aMatrix zeroMatrix(const unsigned int size)
  {
    return aMatrix(size);
  }

  static aMatrix zeroMatrix(const unsigned int lines, const unsigned int columns)
  {
    return aMatrix(lines, columns);
  }
};
