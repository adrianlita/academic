#include "aBitmap.h"
#include <cstdlib>
#include <cstdio>

struct aBitmap_PixelRGB
{
  unsigned char blue;
  unsigned char green;
  unsigned char red;
};

struct aBitmap_PixelRGBA
{
  unsigned char blue;
  unsigned char green;
  unsigned char red;
  unsigned char alpha;
};

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

aBitmap_Pixel::aBitmap_Pixel(unsigned char red, unsigned char green, unsigned char blue)
{
  this->red = red;
  this->green = green;
  this->blue = blue;
}

bool aBitmap_Pixel::isWhite()
{
  return ((red == 255)&&(green == 255)&&(blue == 255));
}

bool aBitmap_Pixel::isBlack()
{
  return ((red == 0)&&(green == 0)&&(blue == 0));
}

void aBitmap::FreeBitmap()
{
  if(bitmap)
  {
    for(int i = 0; i < info_header.height; i++)
      delete [] bitmap[i];
    delete [] bitmap;
    bitmap = NULL;
  }
}

void aBitmap::CopyBitmap(const aBitmap& rhs)
{
  file_header = rhs.file_header;
  info_header = rhs.info_header;
  if(rhs.bitmap)
  {
    bitmap = new aBitmap_Pixel*[rhs.info_header.height];
    if(!bitmap)
      throw "Allocation error";

    for(int i = 0; i < rhs.info_header.height; i++)
    {
      bitmap[i] = new aBitmap_Pixel[rhs.info_header.width];
      if(!bitmap[i])
        throw "Allocation error";

      for(int j = 0; j < rhs.info_header.width; j++)
        bitmap[i][j] = rhs.bitmap[i][j];
    }
  }
}

aBitmap::aBitmap(const char* filename)
{
  bitmap = NULL;
  FreeAndLoadFromFile(filename);
}

aBitmap::aBitmap(const unsigned int height, const unsigned int width)
{
  bitmap = NULL;
  FreeAndCreateNew(height, width);
}

aBitmap::aBitmap(const aBitmap& rhs)
{
  bitmap = NULL;
  CopyBitmap(rhs);
}

aBitmap& aBitmap::operator=(const aBitmap& rhs)
{
  if(this != &rhs)
  {
    FreeBitmap();
    CopyBitmap(rhs);
  }
  return *this;
}

aBitmap::~aBitmap()
{
  FreeBitmap();
}

void aBitmap::Verbose()
{
  printf("File Header\n");
  printf("fileMarker1 = %d\n", file_header.fileMarker1);
  printf("fileMarker2 = %d\n", file_header.fileMarker2);
  printf("bfSize = %d\n", file_header.bfSize);
  printf("unused1 = %d\n", file_header.unused1);
  printf("unused2 = %d\n", file_header.unused2);
  printf("imageDataOffset = %d\n", file_header.imageDataOffset);

  printf("Info Header\n");
  printf("biSize = %d\n", info_header.biSize);
  printf("width = %d\n", info_header.width);
  printf("height = %d\n", info_header.height);
  printf("planes = %d\n", info_header.planes);
  printf("bitPix = %d\n", info_header.bitPix);
  printf("biCompression = %d\n", info_header.biCompression);
  printf("biSizeImage = %d\n", info_header.biSizeImage);
  printf("biXPelsPerMeter = %d\n", info_header.biXPelsPerMeter);
  printf("biYPelsPerMeter = %d\n", info_header.biYPelsPerMeter);
  printf("biClrUsed = %d\n", info_header.biClrUsed);
  printf("biClrImportant = %d\n", info_header.biClrImportant);
}

void aBitmap::FreeAndLoadFromFile(const char* filename)
{
  int padding;

  if(filename == NULL)
    throw "Invalid filename";
  
  FreeBitmap();

  FILE *file;
  file = fopen(filename, "rb");
  if(file == NULL)
    throw "File could not be opened";

  fread(&file_header, sizeof(aBitmap_FileHeader), 1, file);
  fread(&info_header, sizeof(aBitmap_InfoHeader), 1, file); 

  Verbose(); 
  
  // calculating the padding according to the formula  
  padding =  (4 - (Width() * info_header.bitPix/8) % 4) % 4;
  

  // allocate and read bitmap
  bitmap = new aBitmap_Pixel*[Height()];
  if(!bitmap)
    throw "Allocation error";

  for(int i = 0; i < Height(); i++)
  {
    bitmap[i] = new aBitmap_Pixel[Width()];
    if(!bitmap[i])
      throw "Allocation error";

    for(int j = 0; j < Width(); j++)
    {
      if(info_header.bitPix == 32)
      {
        aBitmap_PixelRGBA p;
        fread(&p, sizeof(aBitmap_PixelRGBA), 1, file);
        bitmap[i][j].red = p.red;
        bitmap[i][j].green = p.green;
        bitmap[i][j].blue = p.blue;
      }
      else if(info_header.bitPix == 24)
      {
        aBitmap_PixelRGB p;
        fread(&p, sizeof(aBitmap_PixelRGB), 1, file);
        bitmap[i][j].red = p.red;
        bitmap[i][j].green = p.green;
        bitmap[i][j].blue = p.blue;
      }
    }  

    //skipping the padding from the file i am reading from    
    fseek(file, padding, SEEK_CUR);
  }

  if(info_header.bitPix == 32)
    info_header.bitPix = 24;

  fclose(file);
}

void aBitmap::FreeAndCreateNew(const unsigned int height, const unsigned int width)
{
  if(height == 0)
    throw "Invalid height";

  if(width == 0)
    throw "Invalid width";

  FreeBitmap();
  file_header = aBitmap_FileHeader();
  info_header = aBitmap_InfoHeader();

  info_header.height = height;
  info_header.width = width;
  info_header.bitPix = 24;

  file_header.fileMarker1 = 'B';
  file_header.fileMarker2 = 'M';
  
  info_header.biSize = 40;
  info_header.planes = 1;
  info_header.biCompression = 0;
  info_header.biSizeImage = height*width*(info_header.bitPix / 8);
  file_header.imageDataOffset = 14 + info_header.biSize;
  file_header.bfSize = height*width*(info_header.bitPix / 8) + file_header.imageDataOffset;

  bitmap = new aBitmap_Pixel*[info_header.height];
  if(!bitmap)
    throw "Allocation error";

  for(int i = 0; i < info_header.height; i++)
  {
    bitmap[i] = new aBitmap_Pixel[info_header.width];
    if(!bitmap[i])
      throw "Allocation error";

    for(int j = 0; j < info_header.width; j++)
      bitmap[i][j] = aBitmap_Pixel(255, 255, 255);
  }
}

unsigned int aBitmap::Height()
{
  if(info_header.height >= 0)
    return info_header.height;
  else
    return -info_header.height;
}

unsigned int aBitmap::Width()
{
  return info_header.width;
}

void aBitmap::SaveToFile(const char* filename)
{
  int padding;

  if(filename == NULL)
    throw "Invalid filename";

  if(bitmap == NULL)
    throw "Bitmap is NULL, no save is possible";

  FILE *file;
  file = fopen(filename, "wb");
  if(file == NULL)
    throw "File could not be opened";

  //write headers
  fwrite(&file_header, sizeof(aBitmap_FileHeader), 1, file);
  fwrite(&info_header, sizeof(aBitmap_InfoHeader), 1, file);  
  
  padding =  (4 - (Width() * info_header.bitPix/8) % 4) % 4;

  //write data
  for(int i = 0; i < Height(); i++) {
    for(int j = 0; j < Width(); j++) {
      fwrite(&bitmap[i][j].blue, 1, 1, file);
      fwrite(&bitmap[i][j].green, 1, 1, file);
      fwrite(&bitmap[i][j].red, 1, 1, file);
    }

    //adding the padding for each line in the new file    
    for(int p = 0; p < padding; p++) {
      fputc(0x00, file);
    }
  }

  fclose(file);
}

aBitmap_Pixel& aBitmap::Pixel(unsigned int line, unsigned int column)
{
  if(bitmap == NULL)
    throw "Bitmap empty";

  if(line >= info_header.height)
    throw "Invalid line";

  if(column >= info_header.width)
    throw "Invalid column";

  if(info_header.height >= 0)
  {
    return bitmap[info_header.height - 1 - line][column];
  }
  else
  {
    return bitmap[line][column];
  }
}

aBitmap_Pixel& aBitmap::operator()(unsigned int line, unsigned int column)
{
  return Pixel(line, column);
}
