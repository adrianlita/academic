#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "aBitmap.h"
#include <ctime>
using namespace std;

int main()
{
  try
  { 
    aBitmap orig("lena.bmp");

    aBitmap manipulated = orig;
    for(int i = 0; i < manipulated.Height(); i++)
      for(int j = 0; j < manipulated.Width(); j++)
      {
        manipulated(i, j).red = 255 - manipulated(i, j).red;
        manipulated(i, j).green = 255 - manipulated(i, j).green;
        manipulated(i, j).blue = 255 - manipulated(i, j).blue;
      }
    manipulated.SaveToFile("out_negative.bmp");

    manipulated = orig;
    for(int i = 0; i < manipulated.Height(); i++)
      for(int j = 0; j < manipulated.Width() / 2; j++)
      {
        aBitmap_Pixel aux;
        aux = manipulated(i, j);
        manipulated(i, j) = manipulated(i, manipulated.Width() - 1 - j);
        manipulated(i, manipulated.Width() - 1 - j) = aux;
      }
    manipulated.SaveToFile("out_Hflipped.bmp");

    manipulated = orig;
    for(int i = 0; i < manipulated.Height() / 2; i++)
      for(int j = 0; j < manipulated.Width(); j++)
      {
        aBitmap_Pixel aux;
        aux = manipulated(i, j);
        manipulated(i, j) = manipulated(manipulated.Height() - 1 - i, j);
        manipulated(manipulated.Height() - 1 - i, j) = aux;
      }
    manipulated.SaveToFile("out_Vflipped.bmp");

    //transpose
    manipulated.FreeAndCreateNew(orig.Width(), orig.Height());
    for(int i = 0; i < orig.Height(); i++)
      for(int j = 0; j < orig.Width(); j++)
      {
        manipulated(j, i) = orig(i, j);
      }
    manipulated.SaveToFile("out_rot90ccw.bmp");

     manipulated.FreeAndCreateNew(orig.Width(), orig.Height());
    for(int i = 0; i < orig.Height(); i++)
      for(int j = 0; j < orig.Width(); j++)
      {
        manipulated(j, i) = orig(orig.Height() - 1 - i, j);
      }
    manipulated.SaveToFile("out_rot90cw.bmp");


  }
  catch(const char* e)
  {
    cout << "Exception: " << e << endl;
  }
  

  return 0;
}
