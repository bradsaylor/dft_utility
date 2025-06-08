#include "../include/dft_length.h"
#include "../include/logs.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

int set_dft_length(size_t input_length, CliConfiguration *cli_config,
                   double complex **output_signal) {
  
  log_out(LOG_INFO, "Setting DFT length.");
  size_t output_length = 0;
  algorithmMode alg_mode = cli_config->algorithm_mode;
  size_t requested_length = cli_config->requested_length;
  int trunc_ok = cli_config->truncate_ok;

  if (requested_length) {
    if ((input_length > requested_length) && !trunc_ok) {
      printf(
          "Input legth is longer than requested dft length, set --truncate-ok "
          "to "
          "bypass\n");
      return 0;
    }

    if ((alg_mode == ALG_MODE_FFT) || (alg_mode == ALG_MODE_IFFT)) {
      if ((int)log2(requested_length) != log2(requested_length)) {
        printf("FFT and IFFT modes require input length of 2^n\n");
        return 0;
      } else {
        output_length = requested_length;
        *output_signal = calloc_output_N(requested_length);
      }

    } else {
      output_length = requested_length;
      *output_signal = calloc_output_N(requested_length);
    }
  } else {
    if ((alg_mode == ALG_MODE_FFT) || (alg_mode == ALG_MODE_IFFT)) {
      *output_signal = calloc_output_pow2(input_length, &output_length);
    } else {
      output_length = input_length;
      *output_signal = calloc_output_N(output_length);
    }
  }
log_out(LOG_INFO, "DFT output length determined successfully.");
  return output_length;
}

double complex *calloc_output_pow2(size_t N, size_t *new_length) {
  double log2N = log2(N);
  int v = 0;

  if (log2N == (int)log2N) {
    v = (int)log2N;
  } else {
    v = (int)log2N + 1;
  }
  *new_length = (int)pow(2, v);
  double complex *signal_out = calloc((int)pow(2, v), sizeof(double complex));
  return signal_out;
}

double complex *calloc_output_N(size_t N) {
  double complex *signal_out = calloc(N, sizeof(double complex));
  return signal_out;
}
