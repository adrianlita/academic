#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "aBitmap.h"
#include <ctime>
using namespace std;

//vector of pre-drawn digits, 5x5pixels
const unsigned char digits[10][5][5] = {  { {1,1,1,1,1}, {1,0,0,0,1}, {1,0,0,0,1}, {1,0,0,0,1}, {1,1,1,1,1} },
                                          { {0,0,0,0,1}, {0,0,0,0,1}, {0,0,0,0,1}, {0,0,0,0,1}, {0,0,0,0,1} },
                                          { {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1}, {1,0,0,0,0}, {1,1,1,1,1} },
                                          { {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1} },
                                          { {1,0,0,0,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {0,0,0,0,1} },
                                          { {1,1,1,1,1}, {1,0,0,0,0}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1} },
                                          { {1,1,1,1,1}, {1,0,0,0,0}, {1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1} },
                                          { {1,1,1,1,1}, {0,0,0,0,1}, {0,0,0,0,1}, {0,0,0,0,1}, {0,0,0,0,1} },
                                          { {1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1} },
                                          { {1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1} } };

//copies digit in bmp at position (x,y) with random color
void copy_digit(aBitmap& bmp, const unsigned char digit[5][5], const int x, const int y)
{
  aBitmap_Pixel color;

  color.red = (int)rand()/1.0/RAND_MAX*255;
  color.green = (int)rand()/1.0/RAND_MAX*255;
  color.blue = (int)rand()/1.0/RAND_MAX*255;

  for(int i = 0; i < 5; i++)
    for(int j = 0; j < 5; j++)
    {
      if(digit[i][j])
        bmp(x+i, y+j) = color;
    }
}

int main()
{
  srand((unsigned)time(0));

  int n;
  int *v;
  cout << "How many digits: "; cin >> n;
  v = new int[n];
  if(!v)
    throw "Allocaion error";

  for(int i = 0; i < n; i++)
    v[i] = (int)rand()/1.0/RAND_MAX*10;

  cout << "Generated captcha is: ";
  for(int i = 0; i < n; i++)
    cout << v[i] << " ";
  cout << endl;

  try
  { 
    aBitmap a(30, 7*n);
    int x = 1;
    int y = 12;
    for(int i = 0; i < n; i++)
    {
      copy_digit(a, digits[v[i]], y, x);
      x += 7;
    }

    a.SaveToFile("captcha.bmp");
  }
  catch(const char* e)
  {
    cout << "Exception: " << e << endl;
  }
  

  return 0;
}
