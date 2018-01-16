#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "aBitmap.h"

using namespace std;

int main()
{
  aBitmap a("example.bmp");
  a.Verbose();

  for(int i = 0; i < a.Height(); i++)
  {
    for(int j = 0; j < a.Width(); j++)
    {
      cout << a(i,j).isWhite();
    }
    cout << endl;
  }

  return 0;
}
