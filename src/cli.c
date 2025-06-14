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

#include "../include/logs.h"

/**
 * @brief Print command usage and option information
 *
 * @return int
 */
int print_usage_help();

int parse_cli(int argc, char *argv[], CliConfiguration *cli_config) {
  log_out(LOG_INFO, "Parsing CLI input.");

  if (argc < 3) {
    printf("\nError parsing command line, insufficient number of arguments.\n");
    print_usage_help();
    return 1;
  }
  strcpy(cli_config->input_file_name, argv[1]);
  strcpy(cli_config->output_file_name, argv[2]);

  if (argc > 3) {
    for (int i = 3; i < argc; i++) {
      if (!strcmp("--log-level", argv[i])) {
        if (argc < i + 1) {
          printf("\nMissing log level argument\n");
          return 1;
        }
        if (!strcmp("all", argv[i + 1])) {
          set_log_level(LOG_ALL);
        } else if (!strcmp("debug", argv[i + 1])) {
          set_log_level(LOG_DEBUG);
        } else if (!strcmp("info", argv[i + 1])) {
          set_log_level(LOG_INFO);
        } else if (!strcmp("warning", argv[i + 1])) {
          set_log_level(LOG_WARNING);
        } else if (!strcmp("error", argv[i + 1])) {
          set_log_level(LOG_ERROR);
        } else if (!strcmp("none", argv[i + 1])) {
          set_log_level(LOG_NONE);
        } else {
          printf("\nInvalid log level format: %s\n", argv[i + 1]);
          return 1;
        }
        i++;

      } else if (!strcmp("--output-mode", argv[i])) {
        if (argc < i + 1) {
          printf("\nMissing output argument\n");
          return 1;
        }
        if (!strcmp("csv", argv[i + 1])) {
          cli_config->output_mode = OUTPUT_CSV;
        } else if (!strcmp("txt", argv[i + 1])) {
          cli_config->output_mode = OUTPUT_TXT;
        } else if (!strcmp("bin", argv[i + 1])) {
          cli_config->output_mode = OUTPUT_BIN;
        } else {
          printf("\nInvalid output format: %s\n", argv[i + 1]);
          return 1;
        }
        i++;

      } else if (!strcmp("--alg-mode", argv[i])) {
        if (argc < i + 1) {
          printf("\nMissing algorithm argument\n");
          return 1;
        }
        if (!strcmp("direct", argv[i + 1])) {
          cli_config->algorithm_mode = ALG_MODE_DIRECT;
        } else if (!strcmp("fft", argv[i + 1])) {
          cli_config->algorithm_mode = ALG_MODE_FFT;
        } else if (!strcmp("ifft", argv[i + 1])) {
          cli_config->algorithm_mode = ALG_MODE_IFFT;
        } else if (!strcmp("gtz", argv[i + 1])) {
          cli_config->algorithm_mode = ALG_MODE_GOERTZEL;
        } else {
          printf("\nInvalid algorithm type: %s\n", argv[i + 1]);
          return 1;
        }
        i++;

      } else if (!strcmp("--window-mode", argv[i])) {
        if (argc < i + 1) {
          printf("Missing window argument\n");
          return 1;
        }
        if (!strcmp("han", argv[i + 1])) {
          cli_config->window_mode = WINDOW_HANNING;
        } else if (!strcmp("ham", argv[i + 1])) {
          cli_config->window_mode = WINDOW_HAMMING;
        } else if (!strcmp("ksr", argv[i + 1])) {
          cli_config->window_mode = WINDOW_KAISER;
        } else if (!strcmp("bhs", argv[i + 1])) {
          cli_config->window_mode = WINDOW_BLACKMAN_HARRIS;
        } else if (!strcmp("flt", argv[i + 1])) {
          cli_config->window_mode = WINDOW_FLAT_TOP;
        } else {
          printf("Invalid window type: %s\n", argv[i + 1]);
          return 1;
        }
        i++;

      } else if (!strcmp("--window-parameter", argv[i])) {
        if (argc < i + 1) {
          printf("Missing window parameter\n");
          return 1;
        }
        cli_config->window_param = atof(argv[i + 1]);
        i++;

      } else if (!strcmp("--fs", argv[i])) {
        if (argc < i + 1) {
          printf("Missing sampling frequency parameter\n");
          return 1;
        }
        cli_config->sampling_freq = atof(argv[i + 1]);
        i++;

      } else if (!strcmp("--dft-length", argv[i])) {
        if (argc < i + 1) {
          printf("Missing dft length parameter\n");
          return 1;
        }
        cli_config->requested_length = atoi(argv[i + 1]);
        i++;

      } else if (!strcmp("--benchmark-iterations", argv[i])) {
        if (argc < i + 1) {
          printf("Missing benchmark iterations parameter\n");
          return 1;
        }
        cli_config->benchmark_iterations = atoi(argv[i + 1]);
        i++;

      } else if (!strcmp("--output-source", argv[i])) {
        cli_config->output_source = 1;

      } else if (!strcmp("--write-meta", argv[i])) {
        cli_config->write_meta = 1;

      } else if (!strcmp("--truncate-ok", argv[i])) {
        cli_config->truncate_ok = true;

      } else if (!strcmp("--run-benchmark", argv[i])) {
        cli_config->run_benchmark = 1;

      } else {
        printf("\nInvalid option: %s\n", argv[i]);
        return 1;
      }
    }
  }
  log_out(LOG_INFO, "Successfully parsed cli input.");

  return 0;
}

int print_usage_help() {
  printf("\nUsage: ");
  printf(
      "./dft [../path/to/input/file] [output filename] --option value ...\n\n");
  printf("Options:\n");
  printf("  --output-mode\n");
  printf("      csv:\tOutput in CSV format\n");
  printf("      txt:\tOutput in ASCII text\n");
  printf("      bin:\tOutput in binary format\n\n");
  printf("  --alg-mode\n");
  printf("      direct:\tCalculate DFT directly\n");
  printf("      fft:\tCalculate FFT using decimation in time algorithm\n");
  printf("      ifft:\tCalculate IFFT using decimation in time algroithm\n");
  printf("      gtz:\tCalculate DFT using Goertzel algorithm\n\n");
  printf("  --window-mode\n");
  printf("      han:\tApply Hanning window\n");
  printf("      ham:\tApply Hamming window\n");
  printf("      ksr:\tApply Kaiser window\n");
  printf("      bhs:\tApply Blackman-Harris window\n");
  printf("      flt:\tApply flat top window\n\n");
  printf("  --log-level\n");
  printf("      all:\tSet log level to ALL\n");
  printf("      debug:\tSet log level to DEBUG\n");
  printf("      info:\tSet log level to INFO\n");
  printf("      warning:\tSet log level to WARNING\n");
  printf("      error:\tSet log level to ERROR\n");
  printf("      none:\tSet log level to NONE\n\n");
  printf("  --window-parameter\n");
  printf(
      "      xxx:\t[double] Beta parameter for Kaiser window, "
      "default=8.60\n\n");
  printf("  --fs\n");
  printf("      xxx:\t[int] Sampling frequency\n\n");
  printf("  --dft-length\n");
  printf("      xxx:\t[int] Requested DFT output length\n\n");
  printf("  --output-source\n");
  printf("      \t\tAlso write source file in specified mode\n\n");
  printf("  --write-meta\n");
  printf(
      "      \t\tOutput accompanying .json file with configuration "
      "details\n\n");
  printf("  --truncate-ok\n");
  printf(
      "      \t\tAllow truncation of input to satisfy requested dft "
      "length\n\n");

  return 0;
}
