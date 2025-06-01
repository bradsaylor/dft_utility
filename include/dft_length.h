#ifndef DFT_LENGTH_H
#define DFT_LENGTH_H

#include <complex.h>
#include <stddef.h>

#include "dft.h"

/**
 * @brief Set the dft length object
 *
 * @param input_length Length of input sequence
 * @param cli_config  Struct of user settings
 * @return int
 */
int set_dft_length(size_t input_length, CliConfiguration *cli_config,
                   double complex **output_signal);

/**
 * @brief Allocates output array for for DFT results,
 * length is 2^v for the nearest power of two greater than N
 *
 * @param N Length of input sequence
 * @param new_length Length of allocated sequence
 * @return double* Returns allocated sequence
 */
double complex *calloc_output_pow2(size_t N, size_t *new_length);

/**
 * @brief Allocates output array for DFT results,
 * length is same as input N.
 *
 * @param N Length of input sequence
 * @return double* Returns allocated sequence
 */
double complex *calloc_output_N(size_t N);

#endif  // DFT_LENGTH_H