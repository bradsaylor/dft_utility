#ifndef OUTPUT_H
#define OUTPUT_H

#include <complex.h>

#include "../include/cli.h"

int write_output_file(char *output_filename, outputMode output_mode,
                      double complex *output_sequence, int output_length);
int write_CSV(char *output_filename, double complex *output_sequence,
              int output_length);
int write_TXT(char *output_filename, double complex *output_sequence,
              int output_length);
int write_BIN(char *output_filename, double complex *output_sequence,
              int output_length);

#endif  // OUTPUT_H