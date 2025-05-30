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

int main(int argc, char *argv[]) {
  Configuration config = {0};
  size_t input_length = 0;
  int output_length = 0;
  complex double *input_signal = NULL;
  complex double *output_signal = NULL;

  // Read and parse command line input
  if (parse_cli(argc, argv, &config)) {
    return 1;
  }

  // Read the input sequence from a file
  read_sequence(config.input_file_name, &input_signal, &input_length, MAX_INPUT);

  printf("Size of sequence: \n\tbytes:\t\t %zu \n\telements:\t %lu\n",
         input_length * sizeof(double complex), input_length);

  if (config.window_mode) {
    window(input_signal, input_length, config.window_mode, config.window_param);
  }

  output_length =
      dft_algorithms(config.algorithm_mode, input_length, input_signal, &output_signal);

  // Output to file
  write_output_file(config.output_file_name, output_dir, config.output_mode,
                    output_signal, output_length);

  // Free allocated memory
  free(input_signal);
  free(output_signal);

  return 0;
}
