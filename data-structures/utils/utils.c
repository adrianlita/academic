#include "utils.h"
#include <stdlib.h>

void _my_assert(const char *func, const char* file, const int line, const int abort_all, const char *string)
{
  fprintf(stderr, "%s(%s:%d) %s\n", func, file, line, string);
  if(abort_all)
    exit(1);
}
