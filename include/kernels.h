#ifndef KERNELS_H
#define KERNELS_H
#include "utils.h"

f64 compute_pi (usize dart_inside, usize total_dart);
u8 is_inside (struct dart pos);
void sequential (i32 coeff);
void omp (i32 coeff);
void target (i32 coeff);

#endif
