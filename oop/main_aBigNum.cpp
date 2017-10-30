#include <iostream>
#include "aBigNum/aBigNum.h"
using namespace std;

int main()
{
  cout << "aBigNum sample program" << endl;

  aBigNum a(1);
  for(int i = 2; i <= 1000; i++)
    a = a * i;

  cout << a << endl;
  cout << a.Length() << endl;

  cout << "aBigNum finished!" << endl;
  return EXIT_SUCCESS;
}
