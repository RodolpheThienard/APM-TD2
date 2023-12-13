#ifndef UTILS_H
#define UTILS_H
#include <math.h>
#include <omp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TOT_DART 1000000

typedef int32_t i32;
typedef uint32_t u32;
typedef uint8_t u8;
typedef size_t usize;
typedef double f64;

struct dart
{
  f64 x;
  f64 y;
};

#define ALLOC(X, Y)                                                           \
  do                                                                          \
    {                                                                         \
      Y = malloc (X);                                                         \
      memset (Y, 0, X);                                                       \
    }                                                                         \
  while (0)

#define SQUARE(X) (X * X)

void gen_dart (struct dart *dart, u32 seed);
void benchmark (void (*func) (), char *name);

#endif
