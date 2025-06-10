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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/algorithms.h"
#include "../include/cli.h"
#include "../include/dft_length.h"
#include "../include/meta_file.h"
#include "../include/output.h"
#include "../include/pad_truncate.h"
#include "../include/read_sequence.h"
#include "../include/window.h"
#include "../include/logs.h"

int main(int argc, char *argv[]) {
  ProgramConfig program_config = {.MAX_INPUT = 1024, .output_dir = "./output/"};
  CliConfiguration cli_config = {0};
  size_t input_length = 0;
  size_t output_length = 0;
  int return_ok = 0;
  complex double *input_signal = NULL;
  complex double *output_signal = NULL;

  // Read and parse command line input
  if (parse_cli(argc, argv, &cli_config)) {
    printf("Could not parse command line input");
    return 1;
  }

  // Read the input sequence from file
  if (read_sequence(cli_config.input_file_name, &input_signal, &input_length,
                    program_config.MAX_INPUT)) {
    printf("Could not read input sequence\n");
    return -1;
  }

//  printf("Size of sequence: \n\tbytes:\t\t %zu \n\telements:\t %lu\n",
 //        input_length * sizeof(double complex), input_length);

  // Determine length of output sequence
  output_length = set_dft_length(input_length, &cli_config, &output_signal);
  if (!output_length) {
    printf("Could not set output length\n");
    return 1;
  }

  // Pad or truncate input sequence as required
  if (cli_config.requested_length) {
    if (pad_and_truncate(&input_signal, cli_config.requested_length,
                         input_length)) {
      printf("Failed Pad/Truncate operation.\n");
      return 1;
    }
  }

  // Perform windowing
  if (cli_config.window_mode) {
    window(input_signal, input_length, cli_config.window_mode,
           cli_config.window_param);
  }

  // Compute DFT
  dft_algorithms(cli_config.algorithm_mode, output_length, input_length,
                 input_signal, &output_signal);

  // Output to file
  //
  // Output DFT
  if (write_output_file(cli_config.output_file_name, program_config.output_dir,
                        cli_config.output_mode, output_signal, output_length)) {
    printf("Error could not write output file\n");
    return -1;
  }
  // Output source file
  if (cli_config.output_source) {
    char src_out_name[50] = {0};
    strcat(src_out_name, "src_");
    strcat(src_out_name, cli_config.output_file_name);
    if (write_output_file(src_out_name, program_config.output_dir,
                          cli_config.output_mode, input_signal, input_length)) {
      printf("Error could not write source file.\n");
      return -1;
    }
  }
  // Output meta file
  if (cli_config.write_meta) {
    if (write_meta_file(&program_config, &cli_config, output_length)) {
      printf("Error could not write meta file\n");
      return -1;
    }
  }

  // Free allocated memory
  free(output_signal);
  free(input_signal);

  return 0;
}
