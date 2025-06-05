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

#endif  // DFT_LENGTH_H