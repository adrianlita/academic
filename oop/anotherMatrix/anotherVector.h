#pragma once

#include <iostream>

class anotherVector
{
  double *v;            //here we will store the actual data
  unsigned int c;       //number of columns
public:
  anotherVector();  //implicit constructor
  anotherVector(const unsigned int size);  //initializiation constructor
  anotherVector(const anotherVector& rhs);  //copy constructor
  ~anotherVector(); //destructor
  anotherVector& operator=(const anotherVector& rhs);  //copy operator
  void setSize(const unsigned int size);  //reinitializes anotherVector

  unsigned int Columns() const; //returns the number of columns
  unsigned int Length() const; //same as above
  bool isEmpty(); //returns true if vector is empty (i.e.: size is zero, false otherwise)

  double& operator[](unsigned int i); //index operator, used to access vector elements

  //+ (add) operation
  anotherVector operator+(const anotherVector& rhs);
  anotherVector operator+(const double& rhs);
  friend anotherVector operator+(const double& lhs, const anotherVector& rhs);
  anotherVector& operator+=(const anotherVector& rhs);
  anotherVector& operator+=(const double& rhs);

  //- (substract) operation
  anotherVector operator-(const anotherVector& rhs);
  anotherVector operator-(const double& rhs);
  friend anotherVector operator-(const double& lhs, const anotherVector& rhs);
  anotherVector& operator-=(const anotherVector& rhs);
  anotherVector& operator-=(const double& rhs);

  //* (multiply) operation
  anotherVector operator*(const double& rhs);
  friend anotherVector operator*(const double& lhs, const anotherVector& rhs);
  anotherVector& operator*=(const double& rhs);

  /// (divide) operation
  anotherVector operator/(const double& rhs);
  anotherVector& operator/=(const double& rhs);

  anotherVector operator-();  //negation of vector
  anotherVector operator~();  //reverse of vector
 
  friend std::ostream& operator<<(std::ostream& lhs, const anotherVector& rhs);  //allowing the use of std::ostream

  //static functions (can be used without instantiating objects)
  static anotherVector zeroVector(const unsigned int size)
  {
    return anotherVector(size);
  }
};
