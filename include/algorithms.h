#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <complex.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "cli.h"
#include "direct_dft.h"
#include "fft_dit.h"
#include "gtzl_dft.h"
#include "ifft_dit.h"

int dft_algorithms(algorithmMode alg_mode, int input_length,
                   double complex *input_signal, double complex **output_signal);

/**
 * @brief Allocates output array for for DFT results,
 * length is 2^v for the nearest power of two greater than N
 *
 * @param N Length of input sequence
 * @param new_length Length of allocated sequence
 * @return double* Returns allocated sequence
 */
double complex *calloc_output_pow2(int N, int *new_length);

/**
 * @brief Allocates output array for DFT results,
 * length is same as input N.
 *
 * @param N Length of input sequence
 * @return double* Returns allocated sequence
 */
double complex *calloc_output_N(int N);

#endif  // ALGORITHMS_H