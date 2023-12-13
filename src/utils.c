#include "../include/utils.h"

/*
  Random generation for each dart
  INPUT : dart struct & seed
*/
void
gen_dart (struct dart *dart, u32 seed)
{
  dart->x = (f64)rand_r (&seed) / (RAND_MAX);
  dart->y = (f64)rand_r (&seed) / (RAND_MAX);
}

/*
  Benchmark function for kernels
  INPUT : void function kernel
*/
void
benchmark (void (*func) (), char *name)
{
  struct timespec t1, t2;
  clock_gettime (CLOCK_MONOTONIC_RAW, &t1);
  func ();
  clock_gettime (CLOCK_MONOTONIC_RAW, &t2);
  printf ("Total elapsed time for %s : %lfsec\n", name,
          (t2.tv_nsec * 1e-9 - t1.tv_nsec * 1e-9));
}
