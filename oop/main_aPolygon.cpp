#include <iostream>
#include "aPolygon/aPolygon.h"
using namespace std;

int main()
{
  cout << "aPolygon sample program" << endl;


  cout << "aPolygon is abstract, we can't instantiate objects" << endl;

  cout << "aTriangle" << endl;
  try
  {
    aTriangle a;
    a.setLength(3, 3, 3);
    cout << a << endl;
    cout << "Perimeter: " << a.Perimeter() << endl;
    cout << "Area: " << a.Area() << endl;
    cout << "isRight?: " << a.isRight() << endl;
    cout << "isIsosceles?: " << a.isIsosceles() << endl;
    cout << "isEquilateral?: " << a.isEquilateral() << endl;
  }
  catch(const char *msg)
  {
    cout << "Error: " << msg << endl;
  }

  cout << "aRectangle" << endl;
  try
  {
    aRectangle a(5, 4);
    cout << a << endl;
    cout << "Perimeter: " << a.Perimeter() << endl;
    cout << "Area: " << a.Area() << endl;
    cout << "isSquare?: " << a.isSquare() << endl;
  }
  catch(const char *msg)
  {
    cout << "Error: " << msg << endl;
  }

  cout << "aSquare" << endl;
  try
  {
    aSquare a(2);
    cout << a << endl;
    cout << "Perimeter: " << a.Perimeter() << endl;
    cout << "Area: " << a.Area() << endl;
    cout << "isSquare?: " << a.isSquare() << endl;  //inherited
  }
  catch(const char *msg)
  {
    cout << "Error: " << msg << endl;
  }


  cout << "Polymorphism example" << endl;
  try
  {
    aPolygon *p[5];
    p[0] = new aTriangle(3, 4, 5);
    p[1] = new aRectangle(4, 8);
    p[2] = new aSquare(1);
    p[3] = new aRectangle(7, 2);
    p[4] = new aTriangle(10, 10, 10);

    for(int i = 0; i < 5; i++)
    {
      cout << "Memory address of element " << i << ": " << p[i] << endl;
      cout << *p[i] << endl;

      cout << "Perimeter: " << p[i]->Perimeter() << endl;
      cout << "Area: " << p[i]->Area() << endl;

      cout << endl;
    }
  }
  catch(const char *msg)
  {
    cout << "Error: " << msg << endl;
  }
  
  cout << "aPolygon finished!" << endl;
  return EXIT_SUCCESS;
}
