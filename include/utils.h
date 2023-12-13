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

#define ALLOC(X, n)                                                           \
  do                                                                          \
    {                                                                         \
      X = malloc (sizeof (*X) * n);                                           \
      if (!X)                                                                 \
        {                                                                     \
          perror ("malloc");                                                  \
          exit (1);                                                           \
        }                                                                     \
      memset (X, 0, sizeof (*X) * n);                                         \
    }                                                                         \
  while (0)

#define SQUARE(X) (X * X)

void gen_dart (struct dart *dart, u32 seed);
void benchmark (void (*func) (i32), i32 coeff, char *name);

#endif
