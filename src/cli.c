/**
 * @file cli.c
 * @author Brad Saylor
 * @brief Functions for parsing and checking command line arguments
 * @version 0.1
 * @date 2025-05-22
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../include/cli.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_cli(int argc, char *argv[], Configuration *config) {
  if (argc < 3) {
    printf("\nError parsing command line, insufficient number of arguments.\n");
    print_usage_help();
    return 1;
  }
  strcpy(config->input_file_name, argv[1]);
  strcpy(config->output_file_name, argv[2]);

  if (argc > 3) {
    for (int i = 3; i < argc; i++) {
      if (!strcmp("--output-mode", argv[i])) {
        if (argc < i + 1) {
          printf("\nMissing output argument\n");
          print_usage_help();
          return 1;
        }

        if (!strcmp("csv", argv[i + 1])) {
          config->output_mode = OUTPUT_CSV;
        } else if (!strcmp("txt", argv[i + 1])) {
          config->output_mode = OUTPUT_TXT;
        } else if (!strcmp("bin", argv[i + 1])) {
          config->output_mode = OUTPUT_BIN;
        } else {
          printf("\nInvalid output format: %s\n", argv[i + 1]);
          print_usage_help();
          return 1;
        }
        i++;
      } else if (!strcmp("--alg-mode", argv[i])) {
        if (argc < i + 1) {
          printf("\nMissing algorithm argument\n");
          print_usage_help();
          return 1;
        }

        if (!strcmp("direct", argv[i + 1])) {
          config->algorithm_mode = ALG_MODE_DIRECT;
        } else if (!strcmp("fft", argv[i + 1])) {
          config->algorithm_mode = ALG_MODE_FFT;
        } else if (!strcmp("ifft", argv[i + 1])) {
          config->algorithm_mode = ALG_MODE_IFFT;
        } else if (!strcmp("gtz", argv[i + 1])) {
          config->algorithm_mode = ALG_MODE_GOERTZEL;
        } else {
          printf("\nInvalid algorithm type: %s\n", argv[i + 1]);
          print_usage_help();
          return 1;
        }
        i++;

      } else if (!strcmp("--window-mode", argv[i])) {
        if (argc < i + 1) {
          printf("Missing window argument\n");
          print_usage_help();
          return 1;
        }

        if (!strcmp("han", argv[i + 1])) {
          config->window_mode = WINDOW_HANNING;
        } else if (!strcmp("ham", argv[i + 1])) {
          config->window_mode = WINDOW_HAMMING;
        } else if (!strcmp("ksr", argv[i + 1])) {
          config->window_mode = WINDOW_KAISER;
        } else if (!strcmp("bhs", argv[i + 1])) {
          config->window_mode = WINDOW_BLACKMAN_HARRIS;
        } else {
          printf("Invalid window type: %s\n", argv[i + 1]);
          print_usage_help();
          return 1;
        }
        i++;

      } else {
        printf("\nInvalid option: %s\n", argv[i]);
        print_usage_help();
        return 1;
      }
    }
  }

  return 0;
}

int print_usage_help() {
  printf("\nUsage: ");
  printf(
      "./dft [../path/to/input/file] [output filename] --option value ...\n");
  printf("Options:\n");
  printf("  --output-mode\n");
  printf("      csv:\tOutput in CSV format\n");
  printf("      txt:\tOutput in ASCII text\n");
  printf("      bin:\tOutput in binary format\n");
  printf("  --alg-mode\n");
  printf("      direct:\tCalculate DFT directly\n");
  printf("      fft:\tCalculate FFT using decimation in time algorithm\n");
  printf("      ifft:\tCalculate IFFT using decimation in time algroithm\n");
  printf("      gtz:\tCalculate DFT using Goertzel algorithm\n");
  printf("  --window-mode\n");
  printf("      han:\tApply Hanning window\n");
  printf("      ham:\tApply Hamming window\n");
  printf("      ksr:\tApply Kaiser window\n");
  printf("      bhs:\tApply Blackman-Harris window\n");
  return 0;
}