#include "../include/kernels.h"

/*
   calcul de P
   P = nb flechette dans le cercle / nb tot de flechette

   calcul de Pi
   Pi = 4 * P
*/
f64
compute_pi (usize dart_inside, usize total_dart)
{
  return (4. * dart_inside / total_dart);
}

/*
  Calcul du théorème de Pythagore
*/
f64
pythag (struct dart pos)
{
  return SQUARE (pos.x) + SQUARE (pos.y);
}

/*
   Vérification de la position de la fléchette
   Si la position de la flechette est, 1 >= a x^2 + y^2
   1 si dans le cercle, 0 sinon
*/
u8
is_inside (struct dart pos)
{
  return pythag (pos) <= 1 ? 1 : 0;
}

/*
  Sequential version
*/
void
sequential (i32 coeff)
{
  usize inside = 0;
  srand (2);
  struct dart dart = { 0, 0 };
  for (usize i = 0; i < TOT_DART * coeff; i++)
    {
      dart.x = (f64)rand () / (RAND_MAX);
      dart.y = (f64)rand () / (RAND_MAX);
      inside += is_inside (dart);
    }
  f64 pi = compute_pi (inside, TOT_DART * coeff);
  printf ("SEQUENTIAL Pi ; %.10lf;", pi);
}

/*
  OMP version
*/
void
omp (i32 coeff)
{
  usize inside, total_threads;
  total_threads = omp_get_num_procs ();
  f64 *inside_omp, *pi_omp, pi;
  ALLOC (inside_omp, total_threads);
  ALLOC (pi_omp, total_threads);
#pragma omp parallel
  {
    struct dart dart;
    i32 id = omp_get_thread_num ();
#pragma omp for
    for (usize i = 0; i < TOT_DART * coeff; i++)
      {
        gen_dart (&dart, (u32)i);
        inside_omp[id] += is_inside (dart);
      }
    pi_omp[id] = compute_pi (inside_omp[id], TOT_DART * coeff);
  }
  for (usize i = 0; i < total_threads; i++)
    pi += pi_omp[i];
  printf ("OMP Pi; %.10lf;", pi);
}

/*
  Kernel for target version
*/
f64
target_kernel (f64 *inside_cuda, f64 pi, usize n)
{
#pragma omp target teams map(to : n, inside_cuda[:n]) map(tofrom : pi)
  {
    i32 block_size = n / omp_get_num_teams ();

#pragma omp distribute
    for (usize i = 0; i < n; i += block_size)
      {
#pragma omp parallel for reduction(+ : pi)
        for (usize j = i; j < i + block_size; j++)
          {
            struct dart dart;
            gen_dart (&dart, (u32)j);
            inside_cuda[j] += is_inside (dart);
            pi += compute_pi (inside_cuda[j], n);
          }
      }
  }
  return pi;
}

/*
  Target version
*/
void
target (i32 coeff)
{
  f64 *inside_cuda, pi = 0;
  ALLOC (inside_cuda, TOT_DART * coeff);

  pi = target_kernel (inside_cuda, pi, TOT_DART * coeff);

  printf ("Target ; %.10lf;", pi);
}
