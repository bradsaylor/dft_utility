#include "../include/dft_length.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int set_dft_length(size_t input_length, CliConfiguration *cli_config,
                   double complex **output_signal) {
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
      return 1;
    }

    if ((alg_mode == ALG_MODE_FFT) || (alg_mode == ALG_MODE_IFFT)) {
      if ((int)log2(requested_length) != log2(requested_length)) {
        printf("FFT and IFFT modes require input length of 2^n\n");
        return 1;
      } else {
        // VERIFY call calloc N func with requested length
        output_length = requested_length;
        *output_signal = calloc_output_N(requested_length);
      }

    } else {
      // VERIFY call calloc N func with requested length
      output_length = requested_length;
      *output_signal = calloc_output_N(requested_length);
    }
  } else {
    if ((alg_mode == ALG_MODE_FFT) || (alg_mode == ALG_MODE_IFFT)) {
      // VERIFY call pow2 calloc
      *output_signal = calloc_output_pow2(input_length, &output_length);
    } else {
      // VERIFY call N calloc
      output_length = input_length;
      *output_signal = calloc_output_N(requested_length);
    }
  }

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
