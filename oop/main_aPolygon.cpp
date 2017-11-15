#include <iostream>
#include "aPolygon/aPolygon.h"
using namespace std;

int main()
{
  cout << "aPolygon sample program" << endl;

  try
  {
    aTriangle a;
    a.setLength(3, 3, 3);
    cout << a << endl;
    cout << "Right: " << a.isRight() << endl;
    cout << "Isosceles: " << a.isIsosceles() << endl;
    cout << "Equilateral: " << a.isEquilateral() << endl;
  }
  catch(const char *msg)
  {
    cout << "Error: " << msg << endl;
  }
  
  cout << "aPolygon finished!" << endl;
  return EXIT_SUCCESS;
}
