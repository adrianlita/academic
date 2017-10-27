#include <iostream>
#include "aString/aString.h"
using namespace std;

int main()
{
  cout << "aString sample program" << endl;

  aString var("aString");

  aString a = "hello";
  aString b = a + ' ' + "world";
  cout << b << endl;

  aString c;
  c = "great " + b + " app";
  c += ' ';
  c += "for demonstrating ";
  c += var;
  cout << c << endl;

  aString d = 5;
  d += " is a number transformed into aString";
  cout << d << endl;

  cout << strlen((char*)d) << endl;

  d = aString(205) + d; //this is not directly implemented, but you can do it this way
  cout << d << endl;

  a = "123456789";
  b = "123456789";
  cout << "A= " << a << endl;
  cout << "B= " << b << endl;
  cout << (a == b) << endl;
  cout << (a != b) << endl;
  cout << (a >= b) << endl;
  cout << (a <= b) << endl;
  cout << (a > b) << endl;
  cout << (a < b) << endl;

  a[8] = '8';
  cout << "A= " << a << endl;
  cout << "B= " << b << endl;
  cout << (a == b) << endl;
  cout << (a != b) << endl;
  cout << (a >= b) << endl;
  cout << (a <= b) << endl;
  cout << (a > b) << endl;
  cout << (a < b) << endl;

  cout << "New batch" << endl;
  cout << ("3" == aString(3)) << endl;
  cout << ("3" > aString(3)) << endl;

  cout << "aString finished!" << endl;
  return EXIT_SUCCESS;
}
