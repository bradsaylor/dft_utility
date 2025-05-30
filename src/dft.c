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

#include "../include/algorithms.h"
#include "../include/cli.h"
#include "../include/direct_dft.h"
#include "../include/fft_dit.h"
#include "../include/gtzl_dft.h"
#include "../include/ifft_dit.h"
#include "../include/output.h"
#include "../include/read_sequencev2.h"
#include "../include/window.h"

int main(int argc, char *argv[]) {
  ProgramConfig program_config = {.MAX_INPUT = 1024, .output_dir = "./output/"};
  CliConfiguration cli_config = {0};
  size_t input_length = 0;
  int output_length = 0;
  complex double *input_signal = NULL;
  complex double *output_signal = NULL;

  // Read and parse command line input
  if (parse_cli(argc, argv, &cli_config)) {
    return 1;
  }

  // Read the input sequence from a file
  read_sequence(cli_config.input_file_name, &input_signal, &input_length,
                program_config.MAX_INPUT);

  printf("Size of sequence: \n\tbytes:\t\t %zu \n\telements:\t %lu\n",
         input_length * sizeof(double complex), input_length);

  if (cli_config.window_mode) {
    window(input_signal, input_length, cli_config.window_mode,
           cli_config.window_param);
  }

  output_length = dft_algorithms(cli_config.algorithm_mode, input_length,
                                 input_signal, &output_signal);

  // Output to file
  write_output_file(cli_config.output_file_name, program_config.output_dir,
                    cli_config.output_mode, output_signal, output_length);

  // Free allocated memory
  free(input_signal);
  free(output_signal);

  return 0;
}
