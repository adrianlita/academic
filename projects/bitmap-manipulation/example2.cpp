#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "aBitmap.h"

using namespace std;

int main()
{
  aBitmap a(30, 30);
  
  for(int i = 5; i < a.Height() - 5; i++)
  {
    a(i, i) = aBitmap_Pixel(0, 0, 0);
    a(a.Height() - i - 1, i) = aBitmap_Pixel(0, 0, 0);
  }

  for(int i = 0; i < a.Height(); i++)
  {
    for(int j = 0; j < a.Width(); j++)
    {
      cout << a(i,j).isWhite();
    }
    cout << endl;
  }

  a.SaveToFile("test2.bmp");

  return 0;
}
