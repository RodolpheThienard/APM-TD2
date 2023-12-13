#include "../include/kernels.h"
#include "../include/utils.h"

i32
main (i32 argc, char *argv[])
{
  i32 coeff = atoi (argv[1]);
  printf ("Real Pi value : %lf\n", M_PI);
#ifdef BENCH
  benchmark (sequential, coeff, "Sequential");
  benchmark (omp, coeff, "OMP");
  benchmark (target, coeff, "CUDA");
#else
  sequential (coeff);
  omp (coeff);
  target (coeff);
#endif
  return 0;
}
