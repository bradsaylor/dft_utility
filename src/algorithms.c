#include "../include/algorithms.h"

#include <stdio.h>

#include "../include/direct_dft.h"
#include "../include/fft_dit.h"
#include "../include/gtzl_dft.h"
#include "../include/ifft_dit.h"

int dft_algorithms(algorithmMode alg_mode, size_t output_length,
                   size_t input_length, double complex *input_signal,
                   double complex **output_signal) {
  // mode = 0: Direct
  // mode = 1: FFT - time decimation
  // mode = 2: IFFT - time decimation
  // mode = 3: Goertzel algorithm
  // mode = 5: Benchmark
  switch (alg_mode) {
    case ALG_MODE_DIRECT:
      direct_dft(input_signal, *output_signal, output_length);
      break;
    case ALG_MODE_FFT:
      fft_dit(input_signal, *output_signal, output_length);
      break;
    case ALG_MODE_IFFT:
      ifft_dit(input_signal, *output_signal, output_length);
      break;
    case ALG_MODE_GOERTZEL:
      gtzl_dft(input_signal, *output_signal, output_length);
      break;
    default:
      printf("Invalid mode selected.\n");
      return -1;
  }
  return output_length;
}
