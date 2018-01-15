#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const unsigned char zero[5][5] = { {1,1,1,1,1}, {1,0,0,0,1}, {1,0,0,0,1}, {1,0,0,0,1}, {1,1,1,1,1} };
const unsigned char unu[5][5] = { {0,0,0,0,1}, {0,0,0,0,1}, {0,0,0,0,1}, {0,0,0,0,1}, {0,0,0,0,1} };
const unsigned char doi[5][5] = { {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1}, {1,0,0,0,0}, {1,1,1,1,1} };
const unsigned char trei[5][5] = { {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1} };
const unsigned char patru[5][5] = { {1,0,0,0,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {0,0,0,0,1} };
const unsigned char cinci[5][5] = { {1,1,1,1,1}, {1,0,0,0,0}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1} };
const unsigned char sase[5][5] = { {1,1,1,1,1}, {1,0,0,0,0}, {1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1} };
const unsigned char sapte[5][5] = { {1,1,1,1,1}, {0,0,0,0,1}, {0,0,0,0,1}, {0,0,0,0,1}, {0,0,0,0,1} };
const unsigned char opt[5][5] = { {1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1} };
const unsigned char noua[5][5] = { {1,1,1,1,1}, {1,0,0,0,1}, {1,1,1,1,1}, {0,0,0,0,1}, {1,1,1,1,1} };

#pragma pack(1)
struct bmp_fileheader
{
    unsigned char  fileMarker1; /* 'B' */
    unsigned char  fileMarker2; /* 'M' */
    unsigned int   bfSize; /* File's size */
    unsigned short unused1;
    unsigned short unused2;
    unsigned int   imageDataOffset; /* Offset to the start of image data */
};

struct bmp_infoheader
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
};

struct bmp_pixel
{
  unsigned char blue;
  unsigned char green;
  unsigned char red;
};

struct bmp_file
{
  struct bmp_fileheader header;
  struct bmp_infoheader info;
  struct bmp_pixel** bitmap;
};
#pragma pack()

void initBMP(struct bmp_file *bmp)
{
  if(!bmp)
  {
    fprintf(stderr, "error: bitmap pointer empty\n");
    exit(1);
  }

  bmp->bitmap = NULL;
}

void freeBMP(struct bmp_file *bmp)
{
  if(!bmp)
  {
    fprintf(stderr, "error: bitmap pointer empty\n");
    exit(1);
  }

  if(bmp->bitmap)
  {
    //free dynamically allocated memory
    for(int i = 0; i < bmp->info.height; i++)
    {
      free(bmp->bitmap[i]);
    }
    free(bmp->bitmap);
    bmp->bitmap = NULL;
  }
}

void readBMP(const char *fname, struct bmp_file *bmp)
{
  if(!fname)
  {
    fprintf(stderr, "error: fname pointer empty\n");
    exit(1);
  }

  if(!bmp)
  {
    fprintf(stderr, "error: bitmap pointer empty\n");
    exit(1);
  }

  int padding;
  struct bmp_pixel buff_pixel;

  FILE *file;
  file = fopen(fname, "rb");
  if(file == NULL)
  {
    fprintf(stderr, "Error on file open, %s\n", fname);
    exit(1);
  }

  if(bmp->bitmap)
    freeBMP(bmp);

  //read file header
  fread(&bmp->header.fileMarker1, sizeof(bmp->header.fileMarker1),1, file);
	fread(&bmp->header.fileMarker2, sizeof(bmp->header.fileMarker2), 1, file);
	fread(&bmp->header.bfSize, sizeof(bmp->header.bfSize), 1, file);
	fread(&bmp->header.unused1, sizeof(bmp->header.unused1), 1, file);
	fread(&bmp->header.unused2, sizeof(bmp->header.unused2), 1, file);
	fread(&bmp->header.imageDataOffset, sizeof(bmp->header.imageDataOffset), 1, file);

  //read info header
  fread(&bmp->info.biSize, sizeof(bmp->info.biSize), 1, file);
	fread(&bmp->info.width, sizeof(bmp->info.width), 1, file);
	fread(&bmp->info.height, sizeof(bmp->info.height), 1, file);
	fread(&bmp->info.planes, sizeof(bmp->info.planes), 1, file);
	fread(&bmp->info.bitPix, sizeof(bmp->info.bitPix), 1, file);
	fread(&bmp->info.biCompression, sizeof(bmp->info.biCompression), 1, file);
	fread(&bmp->info.biSizeImage, sizeof(bmp->info.biSizeImage), 1, file);
	fread(&bmp->info.biXPelsPerMeter, sizeof(bmp->info.biXPelsPerMeter), 1, file);
	fread(&bmp->info.biYPelsPerMeter, sizeof(bmp->info.biYPelsPerMeter), 1, file);
	fread(&bmp->info.biClrUsed, sizeof(bmp->info.biClrUsed), 1, file);
	fread(&bmp->info.biClrImportant, sizeof(bmp->info.biClrImportant), 1, file);

  // calculating the padding according to the formula  
	padding =  (4 - (bmp->info.width * sizeof(struct bmp_pixel)) % 4) % 4;

  // allocate and read bitmap
  bmp->bitmap = (struct bmp_pixel **)malloc(bmp->info.height * sizeof(struct bmp_pixel *));
  for(int i = 0; i < bmp->info.height; i++)
  {
    bmp->bitmap[i] = (struct bmp_pixel *)malloc(bmp->info.width * sizeof(struct bmp_pixel));
    for(int j = 0; j < bmp->info.width; j++)
    {
      fread(&buff_pixel, sizeof(struct bmp_pixel), 1, file);
      bmp->bitmap[i][j].blue = buff_pixel.blue;
      bmp->bitmap[i][j].green = buff_pixel.green;
      bmp->bitmap[i][j].red = buff_pixel.red;
    }

    //skipping the padding from the file i am reading from    
    fseek(file, padding, SEEK_CUR);
  }

  fclose(file);
}

void writeBMP(const char *fname, struct bmp_file *bmp)
{
  if(!fname)
  {
    fprintf(stderr, "error: fname pointer empty\n");
    exit(1);
  }

  if(!bmp)
  {
    fprintf(stderr, "error: bitmap pointer empty\n");
    exit(1);
  }

  int padding;

  FILE *file;
  file = fopen(fname, "wb");
  if(file == NULL)
  {
    fprintf(stderr, "Error on file open, %s\n", fname);
    exit(1);
  }

  //write headers
  fwrite(&bmp->header, sizeof(struct bmp_fileheader), 1, file);
  fwrite(&bmp->info, sizeof(struct bmp_infoheader), 1, file);

  padding =  (4 - (bmp->info.width * sizeof(struct bmp_pixel)) % 4) % 4;

  //write data
  for(int i = 0; i < bmp->info.height; i++) {
    for(int j = 0; j < bmp->info.width; j++) {
      fwrite(&bmp->bitmap[i][j].blue, 1, 1, file);
      fwrite(&bmp->bitmap[i][j].green, 1, 1, file);
      fwrite(&bmp->bitmap[i][j].red, 1, 1, file);
    }
    //adding the padding for each line in the new file    
    for(int p = 0; p < padding; p++) {
      fputc(0x00, file);
    }
  }

  fclose(file);
}

void copyBMP(struct bmp_file *dest, const struct bmp_file *source)
{
  if(!dest)
  {
    fprintf(stderr, "error: bitmap pointer empty\n");
    exit(1);
  }

  if(!source)
  {
    fprintf(stderr, "error: bitmap pointer empty\n");
    exit(1);
  }

  if(dest->bitmap)
    freeBMP(dest);

  dest->header = source->header;
  dest->info = source->info;
  dest->bitmap = (struct bmp_pixel **)malloc(source->info.height * sizeof(struct bmp_pixel *));
  for(int i = 0; i < source->info.height; i++)
  {
    dest->bitmap[i] = (struct bmp_pixel *)malloc(source->info.width * sizeof(struct bmp_pixel));
    for(int j = 0; j < source->info.width; j++)
    {
      dest->bitmap[i][j] = source->bitmap[i][j];
    }
  }
}

int isWhite(const struct bmp_pixel p)
{
  if((p.red == 255) && (p.green == 255) && (p.blue == 255))
    return 1;
  else
    return 0;
}

void replaceExt(char *dest, const char *original, const char *new_ext) 
{
	int i = strlen(original) - 1;
	strcpy(dest, original);
	while(original[i] != '.') {
		i--;
	}
	dest[i] = 0;
	strcat(dest, new_ext);
}

int mat_equals(const unsigned char a[5][5], const unsigned char b[5][5])
{
  for(int i = 0; i < 5; i++)
  {
    for(int j = 0; j < 5; j++)
    {
      if(a[i][j] != b[i][j])
        return 0;
    }
  }

  return 1;
}

void find_digit(const struct bmp_file *bmp, const unsigned char x, const unsigned char y)
{
  if(!bmp)
  {
    fprintf(stderr, "error: bitmap pointer empty\n");
    exit(1);
  }

  if(!bmp->bitmap)
  {
    fprintf(stderr, "error: bitmap pointer empty\n");
    exit(1);
  }

  if((x < 4) || (y < 4))
  {
    fprintf(stderr, "error: outside border\n");
    exit(1);
  }

  unsigned char m[5][5];
  for(int i = 0; i < 5; i++)
  {
    for(int j = 0; j < 5; j++)
    {
      m[i][j] = bmp->bitmap[x - i][y - 4 + j].red;
      
      if(m[i][j] == 255)
        m[i][j] = 0;
      if(m[i][j] == 10)
        m[i][j] = 1;
    }  
  }

  unsigned char found = 11;

  if(mat_equals(m, zero))
    found = 0;
  else if(mat_equals(m, unu))
    found = 1;
  else if(mat_equals(m, doi))
    found = 2;
  else if(mat_equals(m, trei))
    found = 3;
  else if(mat_equals(m, patru))
    found = 4;
  else if(mat_equals(m, cinci))
    found = 5;
  else if(mat_equals(m, sase))
    found = 6;
  else if(mat_equals(m, sapte))
    found = 7;
  else if(mat_equals(m, opt))
    found = 8;
  else if(mat_equals(m, noua))
    found = 9;


  for(int i = 0; i < 5; i++)
  {
    for(int j = 0; j < 5; j++)
    {
      bmp->bitmap[x - 4 + i][y - 4 + j].red = found;
    }  
  }
}

int beculet(const struct bmp_file *bmp, const unsigned char x, const unsigned char y)
{
  int top = 0, bottom = 0, left = 0, right = 0;

  if(isWhite(bmp->bitmap[x][y]))
    return 0;

  if(x > 0)
  {
    if(!isWhite(bmp->bitmap[x - 1][y]))
      top = 1;
  }

  if(x < bmp->info.height - 1)
  {
    if(!isWhite(bmp->bitmap[x + 1][y]))
      bottom = 1;
  }

  if(y > 0)
  {
    if(!isWhite(bmp->bitmap[x][y - 1]))
      left = 1;
  }

  if(y < bmp->info.width - 1)
  {
    if(!isWhite(bmp->bitmap[x][y + 1]))
      right = 1;
  }

  if((top + bottom + left + right) == 0)
    return 1;
  else
    return 0;
}

int pixelInRange(const int x1, const int y1, const int x2, const int y2)
{
  return (sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)) <= 7.000);
}

int main()
{
  FILE *input_file;
  FILE *text_file;

  //data found in input.txt
  char buffer[100];
  char input_file_name[100];
  char task1_file_name[100];
  char task2_file_name[100];
  char task3_file_name[100];

  unsigned int red, green, blue;
  unsigned char digit_remove[10];
  char bonus_file_name[100];
  char bonus_out_file_name[100];

  
  struct bmp_file image_orig;
  struct bmp_file image_mask;
  struct bmp_file image_taskX;

  initBMP(&image_orig);
  initBMP(&image_mask);
  initBMP(&image_taskX);

  for(int i = 0; i < 10; i++)
    digit_remove[i] = 0;

  input_file = fopen("input.txt", "r");
  if(input_file == NULL)
  {
    fprintf(stderr, "Error on file open, input.txt");
    exit(1);
  }

  fgets(input_file_name, 100, input_file);
  input_file_name[strlen(input_file_name) - 1] = 0; //remove trailing \n

  fgets(buffer, 100, input_file);
  sscanf(buffer, "%d %d %d", &blue, &green, &red);

  fgets(buffer, 100, input_file);
  for(int i = 0; i < strlen(buffer); i++)
  {
    if((buffer[i] >= '0') && (buffer[i] <= '9'))
      digit_remove[buffer[i] - '0'] = 1;
  }

  fgets(bonus_file_name, 100, input_file);
  bonus_file_name[strlen(bonus_file_name) - 1] = 0; //remove trailing \n

  fclose(input_file);
  input_file = NULL;

  //read original image
  readBMP(input_file_name, &image_orig);

  //create mask
  /*
  image_mask[i][j].red =
    - 255 if nothing there
    - 10 digit not characterized yet
    - 0..9 if digit is there

  */
  copyBMP(&image_mask, &image_orig);
  for(int i = 0; i < image_orig.info.height; i++)
  {
    for(int j = 0; j < image_orig.info.width; j++)
    {
      if(!isWhite(image_mask.bitmap[i][j]))
        image_mask.bitmap[i][j].red = 10;
      else
        image_mask.bitmap[i][j].red = 255;

      image_mask.bitmap[i][j].green = 10;
      image_mask.bitmap[i][j].blue = 10;
    }
  }

  //task 1
  copyBMP(&image_taskX, &image_orig);
  for(int i = 0; i < image_orig.info.height; i++)
  {
    for(int j = 0; j < image_orig.info.width; j++)
    {
      if(image_mask.bitmap[i][j].red != 255)
      {
        image_taskX.bitmap[i][j].red = red;
        image_taskX.bitmap[i][j].green = green;
        image_taskX.bitmap[i][j].blue = blue;
      }
    }
  }

  replaceExt(task1_file_name, input_file_name, "_task1.bmp");
  writeBMP(task1_file_name, &image_taskX);

  //task2
  for(int i = image_mask.info.height - 1; i >= 0; i--)
  {
    for(int j = image_mask.info.width - 1; j >= 0; j--)
    {
      if(image_mask.bitmap[i][j].red == 10)
      {
        find_digit(&image_mask, i, j);
      }
    }
  }

  replaceExt(task2_file_name, input_file_name, "_task2.txt");
  text_file = fopen(task2_file_name, "w");

  int top_corner_x[50];
  int top_corner_y[50];
  int top_corner = 0;
  for(int i = 0; i < 50; i++)
  {
    top_corner_x[i] = -1;
    top_corner_y[i] = -1;
  }

  copyBMP(&image_taskX, &image_mask);
  for(int j = 0; j < image_taskX.info.width; j++)
  {
    for(int i = 0; i < image_taskX.info.height; i++)
    {
      if(image_taskX.bitmap[i][j].red < 10)
      {
        top_corner_x[top_corner] = i;
        top_corner_y[top_corner] = j;
        top_corner++;

        fprintf(text_file, "%d", image_taskX.bitmap[i][j].red);
        for(int k = i; k < i + 5; k++)
        {
          for(int l = j; l < j + 5; l++)
          {
            image_taskX.bitmap[k][l].red = 10;
          }
        }
      }
    }
  }
  fclose(text_file);


  //task 3
  replaceExt(task3_file_name, input_file_name, "_task3.bmp");

  //make it white
  for(int j = 0; j < image_mask.info.width; j++)
  {
    for(int i = 0; i < image_mask.info.height; i++)
    {
      image_taskX.bitmap[i][j].red = 255;
      image_taskX.bitmap[i][j].green = 255;
      image_taskX.bitmap[i][j].blue = 255;
    }
  }

  int current_digit = 0;
  for(int j = 0; j < image_mask.info.width; j++)
  {
    for(int i = 0; i < image_mask.info.height; i++)
    {
      if(image_mask.bitmap[i][j].red < 10)
      {
        if(digit_remove[image_mask.bitmap[i][j].red] == 0)
        {
          for(int k = i; k < i + 5; k++)
          {
            for(int l = j; l < j + 5; l++)
            {
              image_mask.bitmap[k][l].red = 10;

              image_taskX.bitmap[top_corner_x[current_digit] - i + k][top_corner_y[current_digit] - j + l].red = image_orig.bitmap[k][l].red;
              image_taskX.bitmap[top_corner_x[current_digit] - i + k][top_corner_y[current_digit] - j + l].green = image_orig.bitmap[k][l].green;
              image_taskX.bitmap[top_corner_x[current_digit] - i + k][top_corner_y[current_digit] - j + l].blue = image_orig.bitmap[k][l].blue;
            }
          }
          current_digit++;
        }
      }
    }
  }
  writeBMP(task3_file_name, &image_taskX);


  //bonus
  freeBMP(&image_mask);
  freeBMP(&image_taskX);
  freeBMP(&image_orig);
  readBMP(bonus_file_name, &image_orig);
  copyBMP(&image_mask, &image_orig);
  
  //find beculete
  for(int i = 0; i < image_orig.info.height; i++)
  {
    for(int j = 0; j < image_orig.info.width; j++)
    {
      if(!beculet(&image_orig, i, j))
      {
        image_mask.bitmap[i][j].red = 255;
        image_mask.bitmap[i][j].green = 255;
        image_mask.bitmap[i][j].blue = 255;   
      }
    }
  }

  copyBMP(&image_taskX, &image_orig);
  for(int i = 0; i < image_orig.info.height; i++)
  {
    for(int j = 0; j < image_orig.info.width; j++)
    {
      if(!isWhite(image_orig.bitmap[i][j]) && !beculet(&image_orig, i, j) )
      {
        unsigned int red_acc = 0, green_acc = 0, blue_acc = 0, acc = 0;

        for(int k = 0; k < image_mask.info.height; k++)
        {
          for(int l = 0; l < image_mask.info.width; l++)
          {
            if(!isWhite(image_mask.bitmap[k][l]))
              if(pixelInRange(i,j,k,l))
              {
                red_acc += image_mask.bitmap[k][l].red;
                green_acc += image_mask.bitmap[k][l].green;
                blue_acc += image_mask.bitmap[k][l].blue;
                acc++;
              }
          }
        }

        red_acc += image_orig.bitmap[i][j].red;
        green_acc += image_orig.bitmap[i][j].green;
        blue_acc += image_orig.bitmap[i][j].blue;
        acc++;
        
        image_taskX.bitmap[i][j].red = red_acc / acc;
        image_taskX.bitmap[i][j].green = green_acc / acc;
        image_taskX.bitmap[i][j].blue = blue_acc / acc;
      }
    }
  }

  replaceExt(bonus_out_file_name, bonus_file_name, "_bonus.bmp");
  writeBMP(bonus_out_file_name, &image_taskX);

  return 0;
}