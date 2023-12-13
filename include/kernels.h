#ifndef KERNELS_H
#define KERNELS_H
#include "utils.h"

f64 compute_pi (usize dart_inside, usize total_dart);
u8 is_inside (struct dart pos);
void sequential ();
void omp ();
void target ();

#endif
