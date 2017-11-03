#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

void check_stack_growth(const int *second)
{
  int first;
  if (!second)
    check_stack_growth(&first);
  else if (second < &first)
    printf("Stack grows upward\n");
  else
    printf("Stack grows downward\n");
}

int main()
{
  printf("sizeof(char)                %zu\n", sizeof(char));
  printf("sizeof(unsigned char)       %zu\n", sizeof(unsigned char));
  printf("sizeof(short)               %zu\n", sizeof(short));
  printf("sizeof(unsigned short)      %zu\n", sizeof(unsigned short));
  printf("sizeof(int)                 %zu\n", sizeof(int));
  printf("sizeof(unsigned int)        %zu\n", sizeof(unsigned int));
  printf("sizeof(long)                %zu\n", sizeof(long));
  printf("sizeof(unsigned long)       %zu\n", sizeof(unsigned long));
  printf("sizeof(long long)           %zu\n", sizeof(long long));
  printf("sizeof(unsigned long long)  %zu\n", sizeof(unsigned long long));
  printf("sizeof(float)               %zu\n", sizeof(float));
  printf("sizeof(double)              %zu\n", sizeof(double));
  printf("\n");

  unsigned int a = 0x12345678;
  unsigned char *p = (unsigned char*)&a;
  if(*p == 0x78)
    printf("Endianess is little endian\n");
  else
    printf("Endianess is big endian\n");

  check_stack_growth(NULL);

  return EXIT_SUCCESS;
}
