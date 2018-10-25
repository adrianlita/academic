#include <iostream>
#include "anotherMatrix/anotherVector.h"
//#include "anotherMatrix/anotherMatrix.h"
using namespace std;

int main()
{
  cout << "anotherVector sample program" << endl;
  anotherVector a(3), b(3);
  a[0] = 1;
  a[1] = 2;
  a[2] = 3;
  cout << a << endl;
  a = anotherVector::zeroVector(3);
  cout << a << endl;
  b[0] = 1;
  b[1] = 2;
  b[2] = 3;
  
  b += a;
  cout << b << endl;
  b = b * 3;
  b /= 1.5;
  cout << b << endl;

  cout << "anotherVector finished!" << endl;

  // cout << "anotherMatrix sample program" << endl;
  // anotherMatrix a(3);
  // cout << a << endl;
  // a = anotherMatrix::identityMatrix(3);
  // cout << a << endl;

  // //testing operators with double
  // try
  // {
  //   a = a + 2;
  //   cout << a << endl;
  //   a = a - 2;
  //   cout << a << endl;
  //   a = a * 2;
  //   cout << a << endl;
  //   a = a / 2.;
  //   cout << a << endl;

  //   a = 2 + a;
  //   cout << a << endl;
  //   a = 2 - a;
  //   cout << a << endl;
  //   a = 2 * a;
  //   cout << a << endl;
  // }
  // catch (const char* msg) {
  //   cerr << "Err: " << msg << endl;
  // }

  
  // int k = 0;
  // anotherMatrix b(3), c;
  // for(int i = 0; i < 3; i++)
  //   for(int j = 0; j < 3; j++)
  //   {
  //     a(i, j) += k;
  //     b(i, j) = k;
  //     k++;
  //   }
  // cout << "A: " << endl << a << endl;
  // cout << "B: " << endl << b << endl;
  // cout << "Inv(A): " << !a << endl;

  // //testing operators with anotherMatrix
  // try
  // {
  //   c = a + b;
  //   cout << c << endl;
  //   c = a - b;
  //   cout << c << endl;
  //   c = a * b;
  //   cout << c << endl;
  //   c = b / a;
  //   cout << c << endl;
  // }
  // catch (const char* msg) {
  //   cerr << "Err: " << msg << endl;
  // }


  // //testing deeper functions
  // anotherMatrix s(3,4);
  // try
  // {
  //   cout << a << endl;
  //   cout << b << endl;
  //   cout << s << endl;

  //   cout << "det(a) = " << a.determinant() << endl;
  //   cout << "det(b) = " << b.determinant() << endl;
  //   cout << "det(s) = " << s.determinant() << endl;
  // }
  // catch (const char* msg) {
  //   cerr << "Err: " << msg << endl;
  // }

  // a *= !a;
  // cout << a << endl;


  // //now let's solve the example here https://www.mathsisfun.com/algebra/matrix-inverse.html (bus and train example)
  // anotherMatrix ticket_price(2), total_price(1, 2), people;
  // ticket_price(0, 0) = 3;       //child - bus
  // ticket_price(0, 1) = 3.5;     //child - train
  // ticket_price(1, 0) = 3.2;     //adult - bus
  // ticket_price(1, 1) = 3.6;     //adult - train

  // total_price(0, 0) = 118.4;    //total bus
  // total_price(0, 1) = 135.2;    //total train

  // people = total_price/ticket_price;
  // cout << people << endl;

  // cout << "anotherMatrix finished!" << endl;
  // return EXIT_SUCCESS;
}
