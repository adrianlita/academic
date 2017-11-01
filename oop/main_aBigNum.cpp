#include <iostream>
#include "aBigNum/aBigNum.h"
using namespace std;

int main()
{
  cout << "aBigNum sample program" << endl;

  //calculate 1000! (has 2568 digits, which is similar to a ~8500bits number)
  aBigNum a(1), b, c(1);
  for(int i = 2; i <= 1000; i++)
    a = a * i;

  cout << "1000! = " << endl << a << endl;
  cout << "Length of 1000! is = " << a.Length() << endl;

  cout << endl << endl;

  //calculate 1000! / 777
  b = a / 777;
  cout << "1000! / 777" << endl;
  cout << b << endl;

  cout << endl << endl;

  //calculate 1000! and skip multipling 777 to test
  for(int i = 2; i <= 1000; i++)
    if(i != 777)
      c = c * i;

  cout << "1000! without 777" << endl;
  cout << c << endl;

  cout << endl << endl;

  cout << "Is b and c equal ? " << ((b == c) ? "yes" : "no") << endl;
  cout << "aBigNum finished!" << endl;
  return EXIT_SUCCESS;
}
