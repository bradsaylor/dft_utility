#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <complex.h>

#include "dft.h"

int dft_algorithms(algorithmMode alg_mode, size_t output_length,
                   size_t input_length, double complex *input_signal,
                   double complex **output_signal);

#endif  // ALGORITHMS_H