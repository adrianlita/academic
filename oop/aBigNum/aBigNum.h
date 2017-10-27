#pragma once
#include <iostream>

class aBigNum
{
  unsigned char sign;
  unsigned char *decimals;
  unsigned int l;
public:
  aBigNum();
  aBigNum(const char *nr);
  aBigNum(const aBigNum& rhs);
  ~aBigNum();

  aBigNum operator+(const aBigNum& rhs);
  aBigNum operator+(const char* rhs);
  aBigNum operator+(const int rhs);

  aBigNum operator-(const aBigNum& rhs);
  aBigNum operator-(const char* rhs);
  aBigNum operator-(const int rhs);

  aBigNum operator*(const aBigNum& rhs);
  aBigNum operator*(const char* rhs);
  aBigNum operator*(const int rhs);

  aBigNum operator/(const aBigNum& rhs);
  aBigNum operator/(const char* rhs);
  aBigNum operator/(const int rhs);

  aBigNum operator%(const aBigNum& rhs);
  aBigNum operator%(const char* rhs);
  aBigNum operator%(const int rhs);

  aBigNum operator-();
  
  bool operator==(const aBigNum& rhs) const;
  bool operator!=(const aBigNum& rhs) const;
  bool operator>(const aBigNum& rhs) const;
  bool operator>=(const aBigNum& rhs) const;
  bool operator<(const aBigNum& rhs) const;
  bool operator<=(const aBigNum& rhs) const;

  bool operator==(const char *rhs) const;
  bool operator!=(const char *rhs) const;
  bool operator>(const char *rhs) const;
  bool operator>=(const char *rhs) const;
  bool operator<(const char *rhs) const;
  bool operator<=(const char *rhs) const;
};
