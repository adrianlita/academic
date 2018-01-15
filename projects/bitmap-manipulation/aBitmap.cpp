#include "aBitmap.h"

aBitmap_FileHeader::aBitmap_FileHeader()
{
  fileMarker1 = 0;
  fileMarker1 = 0;
  bfSize = 0;
  unused1 = 0;
  unused2 = 0;
  imageDataOffset = 0;
}

aBitmap_InfoHeader::aBitmap_InfoHeader()
{
  biSize = 0;
  width = 0;
  height = 0;
  planes = 0;
  bitPix = 0;
  biCompression = 0;
  biSizeImage = 0;
  biXPelsPerMeter = 0;
  biYPelsPerMeter = 0;
  biClrUsed = 0;
  biClrImportant = 0;
}

aBitmap_Pixel::aBitmap_Pixel()
{
  blue = 0;
  green = 0;
  red = 0;
}

bool aBitmap_Pixel::isWhite()
{
  return ((red == 255)&&(green == 255)&&(blue == 255));
}

bool aBitmap_Pixel::isBlack()
{
  return ((red == 0)&&(green == 0)&&(blue == 0));
}


aBitmap::aBitmap(const char* filename)
{

}

aBitmap::aBitmap(const unsigned int height, const unsigned int width)
{

}

unsigned int aBitmap::Height()
{
  return 0;
}

unsigned int aBitmap::Width()
{
  return 0;
}

void aBitmap::LoadFromFile(const char* filename)
{

}

void aBitmap::SaveToFile(const char* filename)
{

}

aBitmap_Pixel& aBitmap::Pixel(unsigned int line, unsigned int column)
{
  aBitmap_Pixel a;
  return a;
}

aBitmap_Pixel& aBitmap::operator()(unsigned int line, unsigned int column)
{
  aBitmap_Pixel a;
  return a;
}
