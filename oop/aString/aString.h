#pragma once

#include <iostream>

class aString
{
  char *s;

  void set(const char *x);
public:
  aString();
  aString(const int& rhs);
  aString(const char *rhs);
  aString(const aString& rhs);
  ~aString();

  unsigned int Length() const;
  bool isEmpty() const;

  aString& operator=(const int& rhs);
  aString& operator=(const char *rhs);
  aString& operator=(const aString& rhs);

  char& operator[](const unsigned int i);
  char& operator[](const int i);
  operator const char*();
  operator char*();

  aString operator+(const aString& rhs);
  aString operator+(const char rhs);
  aString operator+(const char* rhs);
  friend aString operator+(const char lhs, const aString& rhs);
  friend aString operator+(const char* lhs, const aString& rhs);
  aString& operator+=(const aString& rhs);
  aString& operator+=(const char rhs);
  aString& operator+=(const char* rhs);

  bool operator==(const aString& rhs) const;
  bool operator!=(const aString& rhs) const;
  bool operator>(const aString& rhs) const;
  bool operator>=(const aString& rhs) const;
  bool operator<(const aString& rhs) const;
  bool operator<=(const aString& rhs) const;

  bool operator==(const char *rhs) const;
  bool operator!=(const char *rhs) const;
  bool operator>(const char *rhs) const;
  bool operator>=(const char *rhs) const;
  bool operator<(const char *rhs) const;
  bool operator<=(const char *rhs) const;

  friend bool operator==(const char *lhs, const aString& rhs);
  friend bool operator!=(const char *lhs, const aString& rhs);
  friend bool operator>(const char *lhs, const aString& rhs);
  friend bool operator>=(const char *lhs, const aString& rhs);
  friend bool operator<(const char *lhs, const aString& rhs);
  friend bool operator<=(const char *lhs, const aString& rhs);

  friend std::ostream& operator<<(std::ostream& out, const aString& rhs);
};
