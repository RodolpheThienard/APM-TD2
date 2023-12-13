#include "../include/kernels.h"
#include "../include/utils.h"

i32
main (i32 argc, char *argv[])
{
  printf ("Real Pi value : %lf\n", M_PI);
#ifdef BENCH
  benchmark (sequential, "Sequential");
  benchmark (omp, "OMP");
  benchmark (target, "CUDA");
#else
  sequential ();
  omp ();
  target ();
#endif
  return 0;
}
