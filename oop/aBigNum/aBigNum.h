#pragma once
#include <iostream>

class aBigNum
{
  bool negative;
  char *decimals;
  unsigned int l;

  aBigNum add(const aBigNum& lhs, const aBigNum& rhs) const;          //adds two numbers both positive, (does not take into account the negative part)
  aBigNum substract(const aBigNum& lhs, const aBigNum& rhs) const;    //substracts two numbers, both positive (can be negative, but it won't look at that)
  void add1();        //adds 1 to the this, but does not look at the sign
  void substract1();  //substracts 1 to this, but does not look at the sign

  aBigNum multiply(const char figure, const unsigned int power) const;  //returns this *figure*(10^power). figure is 0..9
  aBigNum divide(const aBigNum& divider, const bool return_remainder) const;
public:
  aBigNum();
  aBigNum(const int nr);
  aBigNum(const char *nr);
  aBigNum(const aBigNum& rhs);
  ~aBigNum();

  unsigned int Length() const;  //number of figures

  aBigNum& operator=(const int nr);
  aBigNum& operator=(const char* nr);
  aBigNum& operator=(const aBigNum& rhs);

  aBigNum operator+(const aBigNum& rhs) const;
  aBigNum operator+(const int rhs) const;

  aBigNum operator-(const aBigNum& rhs) const;
  aBigNum operator-(const int rhs) const;

  aBigNum operator*(const aBigNum& rhs) const;
  aBigNum operator*(const int rhs) const;

  aBigNum operator/(const aBigNum& rhs) const;
  aBigNum operator/(const int rhs) const;

  aBigNum operator%(const aBigNum& rhs) const;
  aBigNum operator%(const int rhs) const;

  aBigNum& operator++();    //prefix ++
  aBigNum operator++(int);  //postfix ++

  aBigNum& operator--();    //prefix --
  aBigNum operator--(int);  //postfix --

  aBigNum operator-() const;
  
  bool operator==(const aBigNum& rhs) const;
  bool operator!=(const aBigNum& rhs) const;
  bool operator>(const aBigNum& rhs) const;
  bool operator>=(const aBigNum& rhs) const;
  bool operator<(const aBigNum& rhs) const;
  bool operator<=(const aBigNum& rhs) const;

  friend std::ostream& operator<<(std::ostream &out, const aBigNum& rhs);
};
