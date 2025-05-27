/**
 * @file dft.c
 * @author Brad Saylor
 * @brief Compute DFT from data file by various methods
 * @version 0.1
 * @date 2025-05-19
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../include/dft.h"

#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/cli.h"
#include "../include/direct_dft.h"
#include "../include/fft_dit.h"
#include "../include/gtzl_dft.h"
#include "../include/ifft_dit.h"
#include "../include/output.h"
#include "../include/read_sequencev2.h"
#include "../include/window.h"

int main(int argc, char *argv[]) {
  Configuration config = {0};
  size_t input_length = 0;
  int output_length = 0;
  complex double *signal_out = NULL;

  // Read and parse command line input
  if (parse_cli(argc, argv, &config)) {
    return 1;
  }

  // Read the input sequence from a file
  double complex *signal = NULL;
  read_sequence(config.input_file_name, &signal, &input_length, MAX_INPUT);

  printf("Size of sequence: \n\tbytes:\t\t %zu \n\telements:\t %lu\n",
         input_length * sizeof(double complex), input_length);

  // mode = 0: Direct
  // mode = 1: FFT - time decimation
  // mode = 2: IFFT - time decimation
  // mode = 3: Goertzel algorithm
  // mode = 5: Benchmark
  switch (config.algorithm_mode) {
    case ALG_MODE_DIRECT:
      signal_out = calloc_output_N(input_length);
      output_length = input_length;
      direct_dft(signal, signal_out, input_length);
      break;
    case ALG_MODE_FFT:
      signal_out = calloc_output_pow2(input_length, &output_length);
      fft_dit(signal, signal_out, output_length);
      break;
    case ALG_MODE_IFFT:
      signal_out = calloc_output_pow2(input_length, &output_length);
      ifft_dit(signal, signal_out, input_length, output_length);
      break;
    case ALG_MODE_GOERTZEL:
      signal_out = calloc_output_N(input_length);
      output_length = input_length;
      gtzl_dft(signal, signal_out, input_length);
      break;
    default:
      printf("Invalid mode selected.\n");
      break;
  }

  // Output to file
  write_output_file(config.output_file_name, output_dir, config.output_mode, signal_out,
                    output_length);

  // Free allocated memory
  free(signal);
  free(signal_out);

  return 0;
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
