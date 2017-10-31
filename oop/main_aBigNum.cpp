#include <iostream>
#include "aBigNum/aBigNum.h"
using namespace std;

int main()
{
  cout << "aBigNum sample program" << endl;

  //calculate 100! (has 2568 digits, which is similar to a ~8500bits number)
  aBigNum a(1);
  for(int i = 2; i <= 100; i++)
    a = a * i;

  cout << "100! = " << a << endl;
  cout << "Length of 100! is = " << a.Length() << endl;

  cout << endl << endl;


  aBigNum b, c(1000);
  b = a / c;
  cout << b << endl;
  
  cout << "aBigNum finished!" << endl;
  return EXIT_SUCCESS;
}
