#ifndef DFT_H
#define DFT_H

#include <complex.h>

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

#endif  // DFT_H
