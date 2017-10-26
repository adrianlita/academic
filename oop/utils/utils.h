#pragma once

#include <cstdio>

/* 
  the following preprocessor macro will exit program and report
  if dynamic allocation failed
*/
#define check_if_allocated_correctly(x) if(x == NULL) \
                                        { printf("%s(%s:%d) allocation failed\n", __func__,__FILE__, __LINE__); exit(EXIT_FAILURE); }

