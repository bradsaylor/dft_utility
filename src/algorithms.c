#include "../include/algorithms.h"

int dft_algorithms(algorithmMode alg_mode, int input_length,
                   double complex *input_signal,
                   double complex **output_signal) {
  int output_length = 0;
  // mode = 0: Direct
  // mode = 1: FFT - time decimation
  // mode = 2: IFFT - time decimation
  // mode = 3: Goertzel algorithm
  // mode = 5: Benchmark
  switch (alg_mode) {
    case ALG_MODE_DIRECT:
      *output_signal = calloc_output_N(input_length);
      output_length = input_length;
      direct_dft(input_signal, *output_signal, input_length);
      break;
    case ALG_MODE_FFT:
      *output_signal = calloc_output_pow2(input_length, &output_length);
      fft_dit(input_signal, *output_signal, output_length);
      break;
    case ALG_MODE_IFFT:
      *output_signal = calloc_output_pow2(input_length, &output_length);
      ifft_dit(input_signal, *output_signal, input_length, output_length);
      break;
    case ALG_MODE_GOERTZEL:
      *output_signal = calloc_output_N(input_length);
      output_length = input_length;
      gtzl_dft(input_signal, *output_signal, input_length);
      break;
    default:
      printf("Invalid mode selected.\n");
      return -1;
  }
  return output_length;
}

double complex *calloc_output_pow2(int N, int *new_length) {
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

double complex *calloc_output_N(int N) {
  double complex *signal_out = calloc(N, sizeof(double complex));
  return signal_out;
}
