#pragma once

#include <cstdint>

#pragma pack(1)
struct aBitmap_FileHeader
{
  unsigned char  fileMarker1; /* 'B' */
  unsigned char  fileMarker2; /* 'M' */
  unsigned int   bfSize; /* File's size */
  unsigned short unused1;
  unsigned short unused2;
  unsigned int   imageDataOffset; /* Offset to the start of image data */

  aBitmap_FileHeader();
};

struct aBitmap_InfoHeader
{
  unsigned int   biSize; /* Size of the info header - 40 bytes */
  signed int     width; /* Width of the image */
  signed int     height; /* Height of the image */
  unsigned short planes;
  unsigned short bitPix;
  unsigned int   biCompression;
  unsigned int   biSizeImage; /* Size of the image data */
  int            biXPelsPerMeter;
  int            biYPelsPerMeter;
  unsigned int   biClrUsed;
  unsigned int   biClrImportant;

  aBitmap_InfoHeader();
};

struct aBitmap_Pixel
{
  unsigned char blue;
  unsigned char green;
  unsigned char red;

  aBitmap_Pixel();

  bool isWhite();
  bool isBlack();
};

class aBitmap
{
  aBitmap_FileHeader file_header;
  aBitmap_InfoHeader info_header;

public:
  aBitmap(const char* filename);
  aBitmap(const unsigned int height, const unsigned int width);

  unsigned int Height();
  unsigned int Width();

  void LoadFromFile(const char* filename);
  void SaveToFile(const char* filename);

  aBitmap_Pixel& Pixel(unsigned int line, unsigned int column);
  aBitmap_Pixel& operator()(unsigned int line, unsigned int column);
};
