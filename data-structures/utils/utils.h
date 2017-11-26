#pragma once

#include <stdio.h>

#define EXIT_ON_ASSERT        0   //set to 1 if my_assert() should also exit

//used to log errors to stderr
void _my_assert(const char *func, const char* file, const int line, const int abort_all, const char *string);
#define my_assert(string) _my_assert(__func__,__FILE__, __LINE__, EXIT_ON_ASSERT, string);
#define my_assert_no_exit(string) _my_assert(__func__,__FILE__, __LINE__, 0, string);
#define my_assert_and_exit(string) _my_assert(__func__,__FILE__, __LINE__, 1, string);

/* 
  the following preprocessor macro will assert
  if dynamic allocation failed
*/

#define check_if_allocated_correctly(x) if(x == NULL) my_assert_and_exit("allocation failed\n");
