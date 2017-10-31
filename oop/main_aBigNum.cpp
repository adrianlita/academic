#include <iostream>
#include "aBigNum/aBigNum.h"
using namespace std;

int main()
{
  cout << "aBigNum sample program" << endl;

  //calculate 100! (has 2568 digits, which is similar to a ~8500bits number)
  aBigNum a(1), b, c;
  for(int i = 2; i <= 1000; i++)
    a = a * i;

  cout << "100! = " << endl << a << endl;
  cout << "Length of 100! is = " << a.Length() << endl;

  cout << endl << endl;

  c = 1000;
  //a = 1260257; c = 37;

  b = a / c;
  cout << b << endl;
  
  cout << "aBigNum finished!" << endl;
  return EXIT_SUCCESS;
}
